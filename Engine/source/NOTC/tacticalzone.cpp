// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "tacticalzone.h"

#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "core/stream/bitStream.h"
#include "collision/boxConvex.h"
#include "gfx/gfxDevice.h"
#include "gfx/primBuilder.h"
#include "gfx/gfxStateBlock.h"
#include "math/mathIO.h"
#include "math/mathUtils.h"
#include "scene/sceneRenderState.h"
#include "terrain/terrData.h"
#include "terrain/terrRender.h"
#include "T3D/gameBase/gameConnection.h"
#include "materials/materialManager.h"
#include "materials/baseMatInstance.h"
#include "renderInstance/renderPassManager.h"
#include "lighting/lightQuery.h"

//-----------------------------------------------------------------------------

//#define TACTICALZONE_DEBUG

#ifdef TACTICALZONE_DEBUG
# define DEBUG(x) (Con::errorf x)
#else
# define DEBUG(x)
#endif

//-----------------------------------------------------------------------------

//
//    3-----7    z
//   /|    /|    ^  _ y
//  / |   / |    |  /|
// 1-----5  |    | /
// |  2--|--6    0-->x
// | /   | /
// |/    |/
// 0-----4
//

static Point3F cubePoints[8] = {
	Point3F(-1, -1, -1), // 0
	Point3F(-1, -1,  1), // 1
	Point3F(-1,  1, -1), // 2
	Point3F(-1,  1,  1), // 3
	Point3F( 1, -1, -1), // 4
	Point3F( 1, -1,  1), // 5
	Point3F( 1,  1, -1), // 6
	Point3F( 1,  1,  1)  // 7
};

static U32 cubeFaces[6][4] = {
	{ 0, 2, 6, 4 }, // 0 "bottom"
	{ 0, 2, 3, 1 }, // 1 "left"
	{ 0, 1, 5, 4 }, // 2 "back"
	{ 3, 2, 6, 7 }, // 3 "front"
	{ 7, 6, 4, 5 }, // 4 "right"
	{ 3, 7, 5, 1 }  // 5 "top"
};

static S32 faceToDirMapping[6][2] = {
	// transform matrix column | dir coefficient | face
	{               2,                  -1 },    // 0
	{               0,                  -1 },    // 1
	{               1,                  -1 },    // 2
	{               1,                   1 },    // 3
	{               0,                   1 },    // 4
	{               2,                   1 },    // 5
};

//-----------------------------------------------------------------------------

extern F32 gDecalBias;

namespace
{
	ColorF sDefaultColor(1, 1, 1, 1);

   void writeRangedF32(BitStream * bstream, F32 val, F32 min, F32 max, U32 numBits)
   {
      val = (mClampF(val, min, max) - min) / (max - min);
      bstream->writeInt(val * ((1 << numBits) - 1), numBits);
   }

   F32 readRangedF32(BitStream * bstream, F32 min, F32 max, U32 numBits)
   {
      return(min + (F32(bstream->readInt(numBits)) / F32((1 << numBits) - 1)) * (max - min));
   }
}

//-----------------------------------------------------------------------------

ConsoleMethod( TacticalZone, getNumObjects, S32, 2, 2, "")
{
   return object->getNumTacticalZoneObjects();
}

ConsoleMethod( TacticalZone, getObject, S32, 3, 3, "(int idx)")
{
   S32 index = dAtoi(argv[2]);

   if (index >= object->getNumTacticalZoneObjects() || index < 0)
      return -1;
   else
      return object->getObject(U32(index))->getId();
}

//----------------------------------------------------------------------------

IMPLEMENT_CO_DATABLOCK_V1(TacticalZoneData);

TacticalZoneData::TacticalZoneData()
{
	tickPeriodMS = 100;
	colorChangeTimeMS = 500;

	for(int i = 0; i < MaxColors; i++)
		colors[i] = sDefaultColor;

   terrainMaterialInst = NULL;
   borderMaterialInst = NULL;
   otherMaterialInst = NULL;
}

TacticalZoneData::~TacticalZoneData()
{
   if(terrainMaterialInst)
      SAFE_DELETE(terrainMaterialInst);

   if(borderMaterialInst)
      SAFE_DELETE(borderMaterialInst);

   if(otherMaterialInst)
      SAFE_DELETE(otherMaterialInst);
}



bool TacticalZoneData::onAdd()
{
   if (!Parent::onAdd())
      return false;

   return true;
}

void TacticalZoneData::initPersistFields()
{
	Parent::initPersistFields();

	addField("tickPeriodMS",        TypeS32,      Offset(tickPeriodMS, TacticalZoneData));
	addField("colorChangeTimeMS",   TypeS32,      Offset(colorChangeTimeMS, TacticalZoneData));
	addField("colors",              TypeColorF,   Offset(colors, TacticalZoneData), MaxColors );

   addGroup( "Rendering" );
   addField( "terrainMaterial",    TypeMaterialName, Offset(terrainMaterialString, TacticalZoneData),
      "The name of the material used to render the terrain." );
   addField( "borderMaterial",    TypeMaterialName, Offset(borderMaterialString, TacticalZoneData),
      "The name of the material used to render the borders." );
   addField( "otherMaterial",    TypeMaterialName, Offset(otherMaterialString, TacticalZoneData),
      "The name of the material used to render all other stuff." );
   endGroup( "Rendering" );
}


//--------------------------------------------------------------------------

void TacticalZoneData::packData(BitStream* stream)
{
   Parent::packData(stream);
   stream->write(tickPeriodMS);
   stream->write(colorChangeTimeMS);

	for(int i = 0; i < MaxColors; i++)
	{
		if(stream->writeFlag(colors[i] != sDefaultColor))
		{
			stream->writeFloat(colors[i].red,7);
			stream->writeFloat(colors[i].green,7);
			stream->writeFloat(colors[i].blue,7);
			stream->writeFloat(colors[i].alpha,7);
		}
	}

	stream->write(terrainMaterialString);
	stream->write(borderMaterialString);
   stream->write(otherMaterialString);
}

void TacticalZoneData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);
   stream->read(&tickPeriodMS);
   stream->read(&colorChangeTimeMS);

	for(int i = 0; i < MaxColors; i++)
	{
		if(stream->readFlag())
		{
			colors[i].red = stream->readFloat(7);
			colors[i].green= stream->readFloat(7);
			colors[i].blue = stream->readFloat(7);
			colors[i].alpha = stream->readFloat(7);
		}
	}

	stream->read(&terrainMaterialString);
	stream->read(&borderMaterialString);
   stream->read(&otherMaterialString);
}

bool TacticalZoneData::preload(bool server, String &errorStr)
{
   if(Parent::preload(server, errorStr) == false)
      return false;

   if(server)
      return true;

   if(!terrainMaterialString.isEmpty())
   {
      SAFE_DELETE(terrainMaterialInst);
      terrainMaterialInst = MATMGR->createMatInstance(terrainMaterialString, getGFXVertexFormat<TacticalZone::VertexType>());
      if(!terrainMaterialInst)
         Con::errorf( "TacticalZoneData::preload - no Material called '%s'", terrainMaterialString.c_str() );
   }

   if(!borderMaterialString.isEmpty())
   {
      SAFE_DELETE(borderMaterialInst);
      borderMaterialInst = MATMGR->createMatInstance(borderMaterialString, getGFXVertexFormat<TacticalZone::VertexType>());
      if(!borderMaterialInst)
         Con::errorf( "TacticalZoneData::preload - no Material called '%s'", borderMaterialString.c_str() );
   }

   if(!otherMaterialString.isEmpty())
   {
      SAFE_DELETE(otherMaterialInst);
      otherMaterialInst = MATMGR->createMatInstance(otherMaterialString, getGFXVertexFormat<TacticalZone::VertexType>());
      if(!otherMaterialInst)
         Con::errorf( "TacticalZoneData::preload - no Material called '%s'", otherMaterialString.c_str() );
   }

   return true;
}

//--------------------------------------------------------------------------

S32 TacticalZone::sRenderMode = Full;
bool TacticalZone::sRenderTerrainDebug = false;

IMPLEMENT_CO_NETOBJECT_V1(TacticalZone);
TacticalZone::TacticalZone()
{
   mNetFlags.set(Ghostable | ScopeAlways);

   //mTypeMask = TacticalZoneObjectType; // discard parent masks
   //mTypeMask |= StaticObjectType;
   //mTypeMask |= StaticShapeObjectType;
   mTypeMask |= TacticalZoneObjectType;

   mObjScale.set(1, 1, 1);
   mObjToWorld.identity();
   mWorldToObj.identity();

   mDataBlock = NULL;

	mIgnoreRayCast = true;

   mLastThink = 0;
   mCurrTick  = 0;

	mShowOnMinimap = true;
	mRenderInteriors = true;
	mRenderTerrain = true;
	mRenderTerrainGrid = false;

   for(U32 i = 0; i < Palette::NumSlots; i++)
	   mCurrColor[i].set(0, 0, 0, 0);
   mFlashColor.set(0, 0, 0, 0);
   mFlickerTime = 0;

	for(int i = 0; i < 6; i++)
		mBorderWidth[i] = 5.0f;

	mDebugMode = false;
	mClientComputePolys = false;

   mConvexList = new Convex;
}

TacticalZone::~TacticalZone()
{
   delete mConvexList;
   mConvexList = NULL;
   this->clearGrid();
}

//-----------------------------------------------------------------------------

void TacticalZone::initPersistFields()
{
	Parent::initPersistFields();

	addField("showOnMinimap",    TypeBool, Offset(mShowOnMinimap,TacticalZone));

	addField("renderInteriors",   TypeBool, Offset(mRenderInteriors,TacticalZone));
	addField("renderTerrain",     TypeBool, Offset(mRenderTerrain,TacticalZone));
	addField("renderTerrainGrid", TypeBool, Offset(mRenderTerrainGrid,TacticalZone));

	addField("borderBottom", TypeF32, Offset(mBorderWidth[0],TacticalZone));
	addField("borderLeft",   TypeF32, Offset(mBorderWidth[1],TacticalZone));
	addField("borderBack",   TypeF32, Offset(mBorderWidth[2],TacticalZone));
	addField("borderFront",  TypeF32, Offset(mBorderWidth[3],TacticalZone));
	addField("borderRight",  TypeF32, Offset(mBorderWidth[4],TacticalZone));
	addField("borderTop",    TypeF32, Offset(mBorderWidth[5],TacticalZone));
}

void TacticalZone::consoleInit()
{
	Parent::consoleInit();

	Con::setIntVariable("$TacticalZoneRenderMode::None", None);
	Con::setIntVariable("$TacticalZoneRenderMode::BordersOnly", BordersOnly);
	Con::setIntVariable("$TacticalZoneRenderMode::Full", Full);

	Con::addVariable("Pref::TacticalZone::RenderMode", TypeS32, &sRenderMode);
	Con::addVariable("TacticalZone::RenderTerrainDebug", TypeS32, &sRenderTerrainDebug);
}

//--------------------------------------------------------------------------

void TacticalZone::computePolys()
{
	// Compute world coordinates of points.
	MatrixF mat(getTransform());
	Point3F pos = mat.getPosition();
	Point3F x; mat.getColumn(0,&x); x.normalize(); x *= mObjScale.x;
	Point3F y; mat.getColumn(1,&y); y.normalize(); y *= mObjScale.y;
	Point3F z; mat.getColumn(2,&z); z.normalize(); z *= mObjScale.z;
	for(U32 i = 0; i < 8; i++)
		mPoints[i] = pos + x*cubePoints[i].x + y*cubePoints[i].y + z*cubePoints[i].z;

	// Compute world coordinates of faces.
	Point3F vec;
	for(U32 i = 0; i < 6; i++)
	{
		S32 index = faceToDirMapping[i][0];
		S32 coefficient = faceToDirMapping[i][1];
		mat.getColumn(index,&vec); vec.normalize(); vec *= coefficient;
		mFaces[i].center = pos + vec*mObjScale[index];
		mFaces[i].plane.set(mFaces[i].center, vec);
	}

	// Setup mClippedList.
	mClippedList.clear();
	mClippedList.mPlaneList.setSize(6);
	mClippedList.mPlaneList[0] = mFaces[0].plane;
	mClippedList.mPlaneList[1] = mFaces[1].plane;
	mClippedList.mPlaneList[2] = mFaces[2].plane;
	mClippedList.mPlaneList[3] = mFaces[3].plane;
	mClippedList.mPlaneList[4] = mFaces[4].plane;
	mClippedList.mPlaneList[5] = mFaces[5].plane;

	if(isServerObject())
		return;

	//
	// compute render stuff...
	//

	// compute the clipping planes that define the start of the border
	for(U32 i = 0; i < 6; i++)
	{
		F32 borderWidth = mBorderWidth[i];
		S32 index = faceToDirMapping[i][0];
		S32 coefficient = faceToDirMapping[i][1];
		mat.getColumn(index,&vec); vec.normalize(); vec *= coefficient;
		Point3F center = pos + vec*(mObjScale[index]-borderWidth);
		mBorderClippingPlanes[i].set(center, -vec);
	}

	// clipping planes for the polys
	// - the outer planes are from mFaces
	// - the inner planes are from mBorderClippingPlanes
	// - mFaces normals face outwards
	// - mBorderClippingPlanes normals face inward
	//
	// viewed from top:
	//              2
	//    ---------------------
	//    |        back       |
	//    |...|-----------|...|
	//    |   |           |   |
	//    | l |           | r |
	//    | e |           | i |
	//  1 | f |  center   | g | 4
	//    | t |           | h |
	//    |   |           | t |
	//    |   |           |   |
	//    |...|-----------|...|
	//    |        front      |
	//    ---------------------
    //               3
	//
	// viewed from the side:
	//               5
	//   --------------------------
	//   |   |      top       |   |
	//   |   |----------------|   |
	// 3 |   |    center      |   | 2
	//   |   |----------------|   |
	//   |   |    bottom      |   |
	//   --------------------------
	//               0

	// "bottom" border polys
	mBorderPolys[0].clear();
	if(mBorderWidth[0] > 0.0f)
	{
		mBorderPolys[0].mPlaneList.setSize(6);
		mBorderPolys[0].mPlaneList[0] = mFaces[0].plane;
		mBorderPolys[0].mPlaneList[1] = mBorderClippingPlanes[1];
		mBorderPolys[0].mPlaneList[2] = mBorderClippingPlanes[2];
		mBorderPolys[0].mPlaneList[3] = mBorderClippingPlanes[3];
		mBorderPolys[0].mPlaneList[4] = mBorderClippingPlanes[4];
		mBorderPolys[0].mPlaneList[5] = mBorderClippingPlanes[0];
		// need to flip certain normals...
		mBorderPolys[0].mPlaneList[1].neg();
		mBorderPolys[0].mPlaneList[2].neg();
		mBorderPolys[0].mPlaneList[3].neg();
		mBorderPolys[0].mPlaneList[4].neg();
	}

	// "left" border polys
	mBorderPolys[1].clear();
	if(mBorderWidth[1] > 0.0f)
	{
		mBorderPolys[1].mPlaneList.setSize(6);
		mBorderPolys[1].mPlaneList[0] = mFaces[0].plane;
		mBorderPolys[1].mPlaneList[1] = mFaces[1].plane;
		mBorderPolys[1].mPlaneList[2] = mBorderClippingPlanes[2];
		mBorderPolys[1].mPlaneList[3] = mBorderClippingPlanes[3];
		mBorderPolys[1].mPlaneList[4] = mBorderClippingPlanes[1];
		mBorderPolys[1].mPlaneList[5] = mFaces[5].plane;
		// need to flip certain normals...
		mBorderPolys[1].mPlaneList[2].neg();
		mBorderPolys[1].mPlaneList[3].neg();
	}

	// "back" border polys
	mBorderPolys[2].clear();
	if(mBorderWidth[2] > 0.0f)
	{
		mBorderPolys[2].mPlaneList.setSize(6);
		mBorderPolys[2].mPlaneList[0] = mFaces[0].plane;
		mBorderPolys[2].mPlaneList[1] = mFaces[1].plane;
		mBorderPolys[2].mPlaneList[2] = mFaces[2].plane;
		mBorderPolys[2].mPlaneList[3] = mBorderClippingPlanes[2];
		mBorderPolys[2].mPlaneList[4] = mFaces[4].plane;
		mBorderPolys[2].mPlaneList[5] = mFaces[5].plane;
	}

	// "front" border polys
	mBorderPolys[3].clear();
	if(mBorderWidth[3] > 0.0f)
	{
		mBorderPolys[3].mPlaneList.setSize(6);
		mBorderPolys[3].mPlaneList[0] = mFaces[0].plane;
		mBorderPolys[3].mPlaneList[1] = mFaces[1].plane;
		mBorderPolys[3].mPlaneList[2] = mBorderClippingPlanes[3];;
		mBorderPolys[3].mPlaneList[3] = mFaces[3].plane;
		mBorderPolys[3].mPlaneList[4] = mFaces[4].plane;
		mBorderPolys[3].mPlaneList[5] = mFaces[5].plane;
	}

	// "right" border polys
	mBorderPolys[4].clear();
	if(mBorderWidth[4] > 0.0f)
	{
		mBorderPolys[4].mPlaneList.setSize(6);
		mBorderPolys[4].mPlaneList[0] = mFaces[0].plane;
		mBorderPolys[4].mPlaneList[1] = mBorderClippingPlanes[4];
		mBorderPolys[4].mPlaneList[2] = mBorderClippingPlanes[2];
		mBorderPolys[4].mPlaneList[3] = mBorderClippingPlanes[3];
		mBorderPolys[4].mPlaneList[4] = mFaces[4].plane;
		mBorderPolys[4].mPlaneList[5] = mFaces[5].plane;
		// need to flip certain normals...
		mBorderPolys[4].mPlaneList[2].neg();
		mBorderPolys[4].mPlaneList[3].neg();
	}

	// "top" border polys
	mBorderPolys[5].clear();
	if(mBorderWidth[5] > 0.0f)
	{
		mBorderPolys[5].mPlaneList.setSize(6);
		mBorderPolys[5].mPlaneList[0] = mBorderClippingPlanes[5];
		mBorderPolys[5].mPlaneList[1] = mBorderClippingPlanes[1];
		mBorderPolys[5].mPlaneList[2] = mBorderClippingPlanes[2];
		mBorderPolys[5].mPlaneList[3] = mBorderClippingPlanes[3];
		mBorderPolys[5].mPlaneList[4] = mBorderClippingPlanes[4];
		mBorderPolys[5].mPlaneList[5] = mFaces[5].plane;
		// need to flip certain normals...
		mBorderPolys[5].mPlaneList[1].neg();
		mBorderPolys[5].mPlaneList[2].neg();
		mBorderPolys[5].mPlaneList[3].neg();
		mBorderPolys[5].mPlaneList[4].neg();
	}

	// Interior polys
	mInteriorPolys.clear();
	mInteriorPolys.mPlaneList.setSize(6);
	mInteriorPolys.mPlaneList[0] = mFaces[0].plane;
	mInteriorPolys.mPlaneList[1] = mFaces[1].plane;
	mInteriorPolys.mPlaneList[2] = mFaces[2].plane;
	mInteriorPolys.mPlaneList[3] = mFaces[3].plane;
	mInteriorPolys.mPlaneList[4] = mFaces[4].plane;
	mInteriorPolys.mPlaneList[5] = mFaces[5].plane;

	// Terrain polys
	mTerrainPolys.clear();
	mTerrainPolys.mPlaneList.setSize(6);
	mTerrainPolys.mPlaneList[0] = mBorderClippingPlanes[0];
	mTerrainPolys.mPlaneList[1] = mBorderClippingPlanes[1];
	mTerrainPolys.mPlaneList[2] = mBorderClippingPlanes[2];
	mTerrainPolys.mPlaneList[3] = mBorderClippingPlanes[3];
	mTerrainPolys.mPlaneList[4] = mBorderClippingPlanes[4];
	mTerrainPolys.mPlaneList[5] = mBorderClippingPlanes[5];
	// need to flip certain normals...
	mTerrainPolys.mPlaneList[0].neg();
	mTerrainPolys.mPlaneList[1].neg();
	mTerrainPolys.mPlaneList[2].neg();
	mTerrainPolys.mPlaneList[3].neg();
	mTerrainPolys.mPlaneList[4].neg();
	mTerrainPolys.mPlaneList[5].neg();

	U32 searchMask = StaticShapeObjectType;
	SceneContainer::FindCallback callback = &TacticalZone::objectFound;
	this->getContainer()->findObjects(mWorldBox, searchMask, callback, this);

	//F32 coat = 0.01;
	//mBorderPolys[0].addCoat(coat);
	//mBorderPolys[1].addCoat(coat);
	//mBorderPolys[2].addCoat(coat);
	//mBorderPolys[3].addCoat(coat);
	//mBorderPolys[4].addCoat(coat);
	//mBorderPolys[5].addCoat(coat);
	//mTerrainPolys.addCoat(coat);
	mTerrainPolys.addTexture(4);

   this->createRenderDataTriangles(&mInteriorPolys, &mRenderData[Other]);
   this->createRenderDataTriangles(&mTerrainPolys, &mRenderData[Terrain]);
   this->createRenderDataTriangles(&mBorderPolys[0], &mRenderData[BorderBottom]);
   this->createRenderDataTriangles(&mBorderPolys[1], &mRenderData[BorderLeft]);
   this->createRenderDataTriangles(&mBorderPolys[2], &mRenderData[BorderBack]);
   this->createRenderDataTriangles(&mBorderPolys[3], &mRenderData[BorderFront]);
   this->createRenderDataTriangles(&mBorderPolys[4], &mRenderData[BorderRight]);
   this->createRenderDataTriangles(&mBorderPolys[5], &mRenderData[BorderTop]);
}

static inline F32 getTerrainHeight(TerrainBlock* terrain, Point2F pos)
{
	F32 height = 0;
	Point3F offset;
	terrain->getTransform().getColumn(3, &offset);
    pos -= Point2F(offset.x, offset.y);
	if(terrain->getHeight(pos, &height))
		return height;
	else
		return 0;
}

static inline void getTerrainHeightAndNormal(TerrainBlock* terrain, Point2F pos, F32* height, Point3F* normal)
{
	Point3F offset;
	terrain->getTransform().getColumn(3, &offset);
    pos -= Point2F(offset.x, offset.y);
	if(!terrain->getNormalAndHeight(pos, normal, height, true))
	{
		*height = 0;
		normal->set(0, 0, 1);
	}
}

static inline TexturedPolyList::Vertex createTerrainVertex(TerrainBlock* terrain, Point2F pos)
{
	TexturedPolyList::Vertex vert;
	vert.point.x = pos.x;
	vert.point.y = pos.y;
	getTerrainHeightAndNormal(terrain,
		Point2F(vert.point.x, vert.point.y),
		&vert.point.z,
		&vert.normal);
	return vert;
}


void TacticalZone::computeGrid()
{
#if 0
	typedef Vector<U32> Line;
	typedef Vector<Line*> Lines;

	if(!this->isClientObject())
		return;

	this->computePolys();

	this->clearGrid();

	TerrainBlock* terrBlock = gClientSceneGraph->getCurrentTerrain();
	if(!terrBlock)
		return;

	S32 squareSize = terrBlock->getSquareSize();

	// Estimate number of lines...
	U32 numLinesX = mObjBox.len_x()/squareSize + 2;
	U32 numLinesY = mObjBox.len_y()/squareSize + 2;

	// Assign vertices to x and y grid lines...
	Lines gridLines[2];
	gridLines[0].reserve(numLinesX);
	gridLines[1].reserve(numLinesY);
	int n = mTerrainPolys.mIndexList.size();
	while(n--)
	{
		U32 vertexIndex = mTerrainPolys.mIndexList[n];
		TexturedPolyList::Vertex& vertex = mTerrainPolys.mVertexList[vertexIndex];

		vertex.peakness[0] = 0;
		vertex.peakness[1] = 0;

		for(int i = 0; i <= 1; i++) // 0 = x, 1 = y
		{
			Line* line = NULL;

			if(mFabs(vertex.point[i] - S32(vertex.point[i])) != 0)
				continue;

			if(S32(vertex.point[i]) % squareSize != 0)
				continue;

			for(int j = 0; j < gridLines[i].size(); j++)
			{
				const TexturedPolyList::Vertex& otherVertex = mTerrainPolys.mVertexList[gridLines[i][j]->operator[](0)];

				if(mFabs(vertex.point[i] - otherVertex.point[i]) < 0.1f)
				{
					line = gridLines[i][j];
					break;
				}
			}

			if(line == NULL)
			{
				line = new Line(mTerrainPolys.mIndexList.size());
				gridLines[i].push_back(line);
			}

			line->push_back(vertexIndex);
		}
	}

	mTerrainGridLines.reserve(numLinesX * numLinesY);
	for(int i = 0; i <= 1; i++)
	{
		for(int j = 0; j < gridLines[i].size(); j++)
		{
			Line* line = gridLines[i][j];

			F32 sharedComponent;
			F32 minPos, maxPos;

			// find position of first and last vertex of the line
			for(int k = 0; k < line->size() - 1; k++)
			{
				U32 vertexidx = line->operator[](k);
				TexturedPolyList::Vertex vertex = mTerrainPolys.mVertexList[vertexidx];

				F32 vertexPos = vertex.point[i == 0 ? 1 : 0];

				if(k == 0)
				{
					sharedComponent = vertex.point[i == 0 ? 0 : 1];
					minPos = vertexPos;
					maxPos = vertexPos;
				}
				else
				{
					if(vertexPos > maxPos)
						maxPos = vertexPos;
					else if(vertexPos < minPos)
						minPos = vertexPos;
				}
			}

			U32 lineDirection = i;
			mTerrainGridLines.push_back(lineDirection);
			mTerrainGridLines.push_back(0);
			U32 numVerticesIdx = mTerrainGridLines.size() - 1;

			//
			F32 pos = minPos;
			{
				Point2F point;
				point[i == 0 ? 1 : 0] = pos;
				point[i == 0 ? 0 : 1] = sharedComponent;

				TexturedPolyList::Vertex vert = createTerrainVertex(terrBlock, point);
				mTerrainGridVertexList.push_back(vert);
				U32 vertexIdx = mTerrainGridVertexList.size() - 1;
				mTerrainGridLines.push_back(vertexIdx);
			}
			do
			{
				F32 prevPos = pos;

				S32 mod = S32(pos) % squareSize;
				if(mod == 0)
					pos += squareSize;
				else
					pos = S32(pos) + mAbs(mod);

				F32 lastZ = mTerrainGridVertexList[mTerrainGridVertexList.size()-1].point.z;

				Point2F curPoint;
				curPoint[i == 0 ? 1 : 0] = pos;
				curPoint[i == 0 ? 0 : 1] = sharedComponent;
				TexturedPolyList::Vertex curVert = createTerrainVertex(terrBlock, curPoint);
				if(curVert.point.z != lastZ)
				{
					Point2F prevPoint;
					prevPoint[i == 0 ? 1 : 0] = prevPos;
					prevPoint[i == 0 ? 0 : 1] = sharedComponent;
					TexturedPolyList::Vertex prevVert = createTerrainVertex(terrBlock, prevPoint);
					if(prevVert.point.z == lastZ)
					{
						mTerrainGridVertexList.push_back(prevVert);
						U32 vertexIdx = mTerrainGridVertexList.size() - 1;
						mTerrainGridLines.push_back(vertexIdx);
					}

					mTerrainGridVertexList.push_back(curVert);
					U32 vertexIdx = mTerrainGridVertexList.size() - 1;
					mTerrainGridLines.push_back(vertexIdx);
				}
			} while(pos < maxPos);
			pos = maxPos;
			{
				Point2F point;
				point[i == 0 ? 1 : 0] = pos;
				point[i == 0 ? 0 : 1] = sharedComponent;

				TexturedPolyList::Vertex vert = createTerrainVertex(terrBlock, point);
				mTerrainGridVertexList.push_back(vert);
				U32 vertexIdx = mTerrainGridVertexList.size() - 1;
				mTerrainGridLines.push_back(vertexIdx);
			}

			mTerrainGridLines[numVerticesIdx] = mTerrainGridLines.size() - numVerticesIdx - 1;

			delete line;
		}
	}

	// Fill mTerrainGridVertices and compute vertex peakness...
	mTerrainGridVertices.reserve(mTerrainGridLines.size());
	for(int i = 0; i < mTerrainGridLines.size();)
	{
		U32 lineDirection = mTerrainGridLines[i++];
		U32 numVertices = mTerrainGridLines[i++];

		for(int j = 0; j < numVertices; j++)
		{
			U32 vertexIndex = mTerrainGridLines[i+j];
			mTerrainGridVertices.push_back(vertexIndex);

			// Compute vertex peakness...
			TexturedPolyList::Vertex& vertex = mTerrainGridVertexList[vertexIndex];

			Point3F p1 = vertex.point;
			Point3F p2 = vertex.point;
			if(lineDirection == 0) // equal Xs
			{
				p1.y += 0.5;
				p2.y -= 0.5;
			}
			else // equal Ys
			{
				p1.x += 0.5;
				p2.x -= 0.5;
			}

			p1.z = getTerrainHeight(terrBlock, Point2F(p1.x, p1.y));
			p2.z = getTerrainHeight(terrBlock, Point2F(p2.x, p2.y));

			Point3F v1 = p1 - vertex.point; v1.normalize(); v1 *= 0.5;
			Point3F v2 = p2 - vertex.point; v2.normalize(); v2 *= 0.5;

			p1 = vertex.point + v1;
			p2 = vertex.point + v2;

			vertex.peakness[lineDirection]  = 0;
			vertex.peakness[lineDirection] += vertex.point.z - p1.z;
			vertex.peakness[lineDirection] += vertex.point.z - p2.z;
		}

		i += numVertices;
	}

	// Compute vertex danger scale...
	//for(int i = 0; i < mTerrainGridVertices.size(); i++)
	//{
	//	U32 vertexIndex = mTerrainGridVertices[i];
	//	TexturedPolyList::Vertex& vertex = mTerrainPolys.mVertexList[vertexIndex];

	//	// compute the amount of danger that the vertex is going to be obscured
	//	// by terrain that renders with less-than-full detail...
	//	vertex.dangerScale = 0;

	//	F32 min = getMin(vertex.peakness[0], vertex.peakness[1]);
	//	F32 max = getMax(vertex.peakness[0], vertex.peakness[1]);
	//	F32 shorter = getMin(mFabs(vertex.peakness[0]), mFabs(vertex.peakness[1]));
	//	F32 longer = getMax(mFabs(vertex.peakness[0]), mFabs(vertex.peakness[1]));

	//	bool safe = false;
	//	if(max > 0)
	//	{
	//		if(min > -0.0001)
	//			safe = true;
	//		else if(max > -min*2)
	//			safe = true;
	//	}

	//	vertex.dangerScale = safe ? 0 : 2 - shorter;
	//}

	mRaisedTerrainGridVertexList = mTerrainGridVertexList;
	mRenderTerrainGridVertexList = mRaisedTerrainGridVertexList;
#endif
}

void TacticalZone::clearGrid()
{
	mTerrainGridVertices.clear();
	mTerrainGridLines.clear();
	mRenderTerrainGridLines.clear();
}

//--------------------------------------------------------------------------

bool TacticalZone::onAdd()
{
   if(!Parent::onAdd())
      return false;

   // setup our bounding box...
	mObjBox.minExtents = Point3F(-1,-1,-1);
	mObjBox.maxExtents = Point3F(1,1,1);
	resetWorldBox();

	if(isServerObject())
	{
		scriptOnAdd();
		computePolys();
	}

	addToScene();

	return true;
}

void TacticalZone::onRemove()
{
   mConvexList->nukeList();

   scriptOnRemove();

   removeFromScene();

   Parent::onRemove();
}

bool TacticalZone::onNewDataBlock(GameBaseData* dptr, bool reload)
{
   mDataBlock = dynamic_cast<TacticalZoneData*>(dptr);
   if (!mDataBlock || !Parent::onNewDataBlock(dptr, reload))
      return false;

   scriptOnNewDataBlock();

   return true;
}

void TacticalZone::onDeleteNotify(SimObject* obj)
{
   GameBase* pScene = dynamic_cast<GameBase*>(obj);
   if (pScene != NULL) {
      for (U32 i = 0; i < mObjects.size(); i++) {
         if (pScene == mObjects[i]) {
            mObjects.erase(i);
            Con::executef(mDataBlock, "onLeave", getIdString(), pScene->getIdString());
            break;
         }
      }
   }

   Parent::onDeleteNotify(obj);
}

//--------------------------------------------------------------------------

void TacticalZone::inspectPostApply()
{
	setMaskBits(EditorMask);
}

void TacticalZone::onEditorEnable()
{
	//mDebugMode = true;
}

void TacticalZone::onEditorDisable()
{
	//mDebugMode = false;
}

//--------------------------------------------------------------------------

void TacticalZone::buildConvex(const Box3F& box, Convex* convex)
{
//	if(mCollisionsDisabled)
//		return;

   // These should really come out of a pool
	mConvexList->collectGarbage();

	Box3F realBox = box;
	mWorldToObj.mul(realBox);
	realBox.minExtents.convolveInverse(mObjScale);
	realBox.maxExtents.convolveInverse(mObjScale);

	if (realBox.isOverlapped(getObjBox()) == false)
		return;

	// Just return a box convex for the entire shape...
	Convex* cc = 0;
	CollisionWorkingList& wl = convex->getWorkingList();
	for (CollisionWorkingList* itr = wl.wLink.mNext; itr != &wl; itr = itr->wLink.mNext) {
		if(itr->mConvex->getType() == BoxConvexType && itr->mConvex->getObject() == this)
		{
			cc = itr->mConvex;
			break;
		}
	}
   if(cc)
		return;

   // Create a new convex.
   BoxConvex* cp = new BoxConvex;
   mConvexList->registerObject(cp);
   convex->addToWorkingList(cp);
   cp->init(this);

   mObjBox.getCenter(&cp->mCenter);
   cp->mSize.x = mObjBox.len_x() / 2.0f;
   cp->mSize.y = mObjBox.len_y() / 2.0f;
   cp->mSize.z = mObjBox.len_z() / 2.0f;
}


//------------------------------------------------------------------------------

void TacticalZone::setTransform(const MatrixF & mat)
{
   Parent::setTransform(mat);

	if(isServerObject())
		computePolys();
	else
	{
		this->clearGrid();
		mClientComputePolys = true;
	}
}

ColorF TacticalZone::getZoneColor(U32 slot) const
{
   if(mFlickerTime == 0)
      return mCurrColor[slot];

   U32 time = Platform::getRealMilliseconds();
   if(slot == 0 && (time/mFlickerTime) % 2 == 0)
      return ColorF(0,0,0,0);
   else
      return mCurrColor[slot];
}

void TacticalZone::flash(const ColorF& color)
{
   mFlashColor = color;
   this->setMaskBits(FlashMask);
}

void TacticalZone::setFlicker(U32 flickerTime)
{
   if(mFlickerTime == flickerTime)
      return;
   mFlickerTime = flickerTime;  
	this->setMaskBits(FlickerMask);
}

//--------------------------------------------------------------------------

bool TacticalZone::testObject(GameBase* enter)
{
   mClippedList.clear();

   SphereF sphere;
   sphere.center = getBoxCenter();
   VectorF bv = mWorldBox.maxExtents - sphere.center;
   sphere.radius = bv.len();

   enter->buildPolyList(PLC_Collision, &mClippedList, mWorldBox, sphere);
   return !mClippedList.isEmpty();
}


void TacticalZone::potentialEnterObject(GameBase* enter)
{
   AssertFatal(isServerObject(), "Error, should never be called on the client!");

   for (U32 i = 0; i < mObjects.size(); i++)
	{
      if (mObjects[i] == enter)
         return;
   }

   if(testObject(enter))
	{
      mObjects.push_back(enter);
      deleteNotify(enter);

      Con::executef(mDataBlock, "onEnter", getIdString(), enter->getIdString());
   }
}


void TacticalZone::processTick(const Move* move)
{
	Parent::processTick(move);

   //
	if (mObjects.size() == 0)
		return;

	if(mLastThink + mDataBlock->tickPeriodMS < mCurrTick)
	{
		mCurrTick  = 0;
		mLastThink = 0;

      for (S32 i = S32(mObjects.size() - 1); i >= 0; i--)
		{
         if(!testObject(mObjects[i]))
			{
            GameBase* remove = mObjects[i];
            mObjects.erase(i);
            clearNotify(remove);
            Con::executef(mDataBlock, "onLeave", getIdString(), remove->getIdString());
         }
      }

      if (mObjects.size() != 0)
         Con::executef(mDataBlock, "onTick", getIdString());
   } else {
      mCurrTick += TickMs;
   }
}

void TacticalZone::advanceTime(F32 dt)
{
	Parent::advanceTime(dt);

   for(U32 i = 0; i < Palette::NumSlots; i++)
   {
	   ColorF targetColor = mPalette.colors[i];
	   if(mCurrColor[i] != targetColor)
	   {
		   F32 delta = dt / (F32(mDataBlock->colorChangeTimeMS) / 1000.0f);
		   mCurrColor[i].interpolate(mCurrColor[i], targetColor, delta);
	   }
   }
}

//--------------------------------------------------------------------------

void TacticalZone::createRenderDataTriangles(TexturedPolyList* src, RenderData* dst)
{
   dst->primType = GFXTriangleList;
   dst->numVerts = 0;
   dst->numPrims = 0;

   //
   Vector<U32> vertIdxBuf;
   TexturedPolyList::Poly* p;
   for(p = src->mPolyList.begin(); p < src->mPolyList.end(); p++)
   {
      if(p->vertexCount == 3)
      {
         U32 idx1 = src->mIndexList[p->vertexStart];
         U32 idx2 = src->mIndexList[p->vertexStart + 1];
         U32 idx3 = src->mIndexList[p->vertexStart + 2];

         vertIdxBuf.push_back(idx1);
         vertIdxBuf.push_back(idx2);
         vertIdxBuf.push_back(idx3);
         dst->numPrims++;
      }

      if(p->vertexCount == 4)
      {
         U32 idx1 = src->mIndexList[p->vertexStart];
         U32 idx2 = src->mIndexList[p->vertexStart + 1];
         U32 idx3 = src->mIndexList[p->vertexStart + 2];
         U32 idx4 = src->mIndexList[p->vertexStart + 3];

         vertIdxBuf.push_back(idx1);
         vertIdxBuf.push_back(idx2);
         vertIdxBuf.push_back(idx3);
         dst->numPrims++;

         vertIdxBuf.push_back(idx3);
         vertIdxBuf.push_back(idx4);
         vertIdxBuf.push_back(idx1);
         dst->numPrims++;
      }

      if(p->vertexCount == 5)
      {
         U32 idx1 = src->mIndexList[p->vertexStart];
         U32 idx2 = src->mIndexList[p->vertexStart + 1];
         U32 idx3 = src->mIndexList[p->vertexStart + 2];
         U32 idx4 = src->mIndexList[p->vertexStart + 3];
         U32 idx5 = src->mIndexList[p->vertexStart + 4];

         vertIdxBuf.push_back(idx1);
         vertIdxBuf.push_back(idx2);
         vertIdxBuf.push_back(idx3);
         dst->numPrims++;

         vertIdxBuf.push_back(idx3);
         vertIdxBuf.push_back(idx4);
         vertIdxBuf.push_back(idx5);
         dst->numPrims++;

         vertIdxBuf.push_back(idx1);
         vertIdxBuf.push_back(idx3);
         vertIdxBuf.push_back(idx5);
         dst->numPrims++;
      }
   }

   // Fill the vertex buffer.
   dst->numVerts = vertIdxBuf.size();
   if(dst->numVerts == 0)
      return;
   dst->vertBuf.set(GFX, dst->numVerts, GFXBufferTypeStatic );
   VertexType* pVert = dst->vertBuf.lock();
   for(U16 i = 0; i < dst->numVerts; i++)
   {
      U32 idx = vertIdxBuf[i];
      pVert[i].point    = src->mVertexList[idx].point;
      pVert[i].normal   = Point3F(0, 0, 1);
      pVert[i].texCoord = src->mVertexList[idx].texCoord;
   }
   dst->vertBuf.unlock();

   // Fill the primitive buffer.
   if(dst->numPrims == 0)
      return;
   dst->primBuf.set( GFX, dst->numVerts, dst->numPrims, GFXBufferTypeStatic );
   U16 *pIdx = NULL; dst->primBuf.lock(&pIdx);
   for(U16 i = 0; i < dst->numVerts; i++)
      pIdx[i] = i;
   dst->primBuf.unlock();
}

void TacticalZone::createRenderDataLines(TexturedPolyList* src, RenderData* dst)
{
   dst->primType = GFXLineList;
   dst->numVerts = 0;
   dst->numPrims = 0;

   //
   Vector<U32> vertIdxBuf;
   TexturedPolyList::Poly* p;
   for(p = src->mPolyList.begin(); p < src->mPolyList.end(); p++)
   {
      if(p->vertexCount == 3)
      {
         U32 idx1 = src->mIndexList[p->vertexStart];
         U32 idx2 = src->mIndexList[p->vertexStart + 1];
         U32 idx3 = src->mIndexList[p->vertexStart + 2];

         vertIdxBuf.push_back(idx1);
         vertIdxBuf.push_back(idx2);
         dst->numPrims++;

         vertIdxBuf.push_back(idx2);
         vertIdxBuf.push_back(idx3);
         dst->numPrims++;

         vertIdxBuf.push_back(idx3);
         vertIdxBuf.push_back(idx1);
         dst->numPrims++;
      }

      if(p->vertexCount == 4)
      {
         U32 idx1 = src->mIndexList[p->vertexStart];
         U32 idx2 = src->mIndexList[p->vertexStart + 1];
         U32 idx3 = src->mIndexList[p->vertexStart + 2];
         U32 idx4 = src->mIndexList[p->vertexStart + 3];

         vertIdxBuf.push_back(idx1);
         vertIdxBuf.push_back(idx2);
         dst->numPrims++;

         vertIdxBuf.push_back(idx2);
         vertIdxBuf.push_back(idx3);
         dst->numPrims++;

         vertIdxBuf.push_back(idx3);
         vertIdxBuf.push_back(idx4);
         dst->numPrims++;

         vertIdxBuf.push_back(idx4);
         vertIdxBuf.push_back(idx1);
         dst->numPrims++;
      }

      if(p->vertexCount == 5)
      {
         U32 idx1 = src->mIndexList[p->vertexStart];
         U32 idx2 = src->mIndexList[p->vertexStart + 1];
         U32 idx3 = src->mIndexList[p->vertexStart + 2];
         U32 idx4 = src->mIndexList[p->vertexStart + 3];
         U32 idx5 = src->mIndexList[p->vertexStart + 4];

         vertIdxBuf.push_back(idx1);
         vertIdxBuf.push_back(idx2);
         dst->numPrims++;

         vertIdxBuf.push_back(idx2);
         vertIdxBuf.push_back(idx3);
         dst->numPrims++;

         vertIdxBuf.push_back(idx3);
         vertIdxBuf.push_back(idx4);
         dst->numPrims++;

         vertIdxBuf.push_back(idx4);
         vertIdxBuf.push_back(idx5);
         dst->numPrims++;

         vertIdxBuf.push_back(idx5);
         vertIdxBuf.push_back(idx1);
         dst->numPrims++;
      }
   }

   // Fill the vertex buffer.
   dst->numVerts = vertIdxBuf.size();
   if(dst->numVerts == 0)
      return;
   dst->vertBuf.set(GFX, dst->numVerts, GFXBufferTypeStatic );
   VertexType* pVert = dst->vertBuf.lock();
   for(U16 i = 0; i < dst->numVerts; i++)
   {
      U32 idx = vertIdxBuf[i];
      pVert[i].point    = src->mVertexList[idx].point;
      pVert[i].normal   = Point3F(0, 0, 1);
      pVert[i].texCoord = src->mVertexList[idx].texCoord;
   }
   dst->vertBuf.unlock();

   // Fill the primitive buffer.
   if(dst->numPrims == 0)
      return;
   dst->primBuf.set( GFX, dst->numVerts, dst->numPrims, GFXBufferTypeStatic );
   U16 *pIdx = NULL; dst->primBuf.lock(&pIdx);
   for(U16 i = 0; i < dst->numVerts; i++)
      pIdx[i] = i;
   dst->primBuf.unlock();
}

//--------------------------------------------------------------------------

void TacticalZone::prepRenderImage(SceneRenderState* state)
{
   if(!state->isDiffusePass())
      return;

	if(sRenderMode == None && sRenderTerrainDebug == false)
		return;

	if(isClientObject() && mClientComputePolys)
	{
		computePolys();
		mClientComputePolys = false;
	}

   if(false)
   {
      ObjectRenderInst *ri = state->getRenderPass()->allocInst<ObjectRenderInst>();
      ri->renderDelegate.bind( this, &TacticalZone::render );
      ri->type = RenderPassManager::RIT_Object;
      ri->defaultKey = 0;
      ri->defaultKey2 = 0;
      state->getRenderPass()->addInst(ri);
   }

   const Frustum &frustum = state->getCameraFrustum();

   // Get a handy pointer to our RenderPassmanager
   RenderPassManager* renderPass = state->getRenderPass();

   for(U32 i = 0; i < NumRenderParts; i++)
   {
      RenderData* renderData = &mRenderData[i];

      if(renderData->numVerts == 0)
         continue;

      BaseMatInstance* matInst;

      if(i == Other)
         matInst = mDataBlock->otherMaterialInst;
      else if(i == Terrain)
         matInst = mDataBlock->terrainMaterialInst;
      else
         matInst = mDataBlock->borderMaterialInst;

      if(!matInst)
         continue;

      // If we don't have a material instance after the override then
      // we can skip rendering all together.
      matInst = state->getOverrideMaterial(matInst);
      if(!matInst)
         continue;

      // Allocate an MeshRenderInst so that we can submit it to the RenderPassManager
      MeshRenderInst* ri = renderPass->allocInst<MeshRenderInst>();

      // Set palette.
      ri->palette = this->getPalette();
      for(U32 i = 0; i < Palette::NumSlots; i++)
         ri->palette.colors[i] = this->getZoneColor(i);

      // Set our RenderInst as a standard mesh render
      ri->type = RenderPassManager::RIT_Mesh;

      //If our material has transparency set on this will redirect it to proper render bin
      if(matInst->getMaterial()->isTranslucent())
      {
         ri->type = RenderPassManager::RIT_Translucent;
         ri->translucentSort = true;
      }

      // Make it the sort distance the max distance so that 
      // it renders after all the other opaque geometry in 
      // the prepass bin.
      ri->sortDistSq = F32_MAX;

      // Set up our transforms
      MatrixF objectToWorld = getRenderTransform();
      objectToWorld.scale( getScale() );

      ri->objectToWorld = &MatrixF::Identity;

      ri->worldToCamera = renderPass->allocSharedXform(RenderPassManager::View);

      MatrixF *tempMat = renderPass->allocUniqueXform( MatrixF( true ) );
      MathUtils::getZBiasProjectionMatrix( gDecalBias/2, frustum, tempMat );
      ri->projection = tempMat;
      //ri->projection = renderPass->allocSharedXform(RenderPassManager::Projection);

	   // If our material needs lights then fill the RIs
      // light vector with the best lights.
      if(matInst->isForwardLit() && !ri->lights[0])
      {
         LightQuery query(8);
         query.init( getWorldSphere() );
		   query.getLights( ri->lights, 8);
      }

      // Make sure we have an up-to-date backbuffer in case
      // our Material would like to make use of it
      // NOTICE: SFXBB is removed and refraction is disabled!
      //ri->backBuffTex = GFX->getSfxBackBuffer();

      // Set our Material
      ri->matInst = matInst;

      // Set up our vertex buffer and primitive buffer
      ri->vertBuff = &renderData->vertBuf;
      ri->primBuff = &renderData->primBuf;

      ri->prim = renderPass->allocPrim();
      ri->prim->type = renderData->primType;
      ri->prim->minIndex = 0;
      ri->prim->startIndex = 0;
      ri->prim->numPrimitives = renderData->numPrims;
      ri->prim->startVertex = 0;
      ri->prim->numVertices = renderData->numVerts;

      // We sort by the material then vertex buffer
      ri->defaultKey = matInst->getStateHint();
      ri->defaultKey2 = (U32)ri->vertBuff; // Not 64bit safe!

      // Submit our RenderInst to the RenderPassManager
      state->getRenderPass()->addInst( ri );
   }
}

void TacticalZone::render( ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *overrideMat )
{
   if(overrideMat)
      return;

   GFXStateBlockDesc solidZDisable;
   solidZDisable.setCullMode( GFXCullNone );
   solidZDisable.setZReadWrite( false, false );
   GFXStateBlockRef sb = GFX->createStateBlock( solidZDisable );
   //GFX->setStateBlock( sb );

   PrimBuild::color3i( 255, 0, 255 );

   TexturedPolyList& pList = mTerrainPolys;

   TexturedPolyList::Poly *p;
   Point3F *pnt;

   for ( p = pList.mPolyList.begin(); p < pList.mPolyList.end(); p++ )
   {
      PrimBuild::begin( GFXLineStrip, p->vertexCount + 1 );

      for ( U32 i = 0; i < p->vertexCount; i++ )
      {
         pnt = &pList.mVertexList[pList.mIndexList[p->vertexStart + i]].point;
         PrimBuild::vertex3fv( pnt );
      }

      pnt = &pList.mVertexList[pList.mIndexList[p->vertexStart]].point;
      PrimBuild::vertex3fv( pnt );

      PrimBuild::end();
   }
}

#if 0
bool TacticalZone::prepRenderImage(SceneState* state, const U32 stateKey,
                              const U32 startZone, const bool modifyBaseState)
{
	if(sRenderMode == None && sRenderTerrainDebug == false)
		return false;

	if(isClientObject() && mClientComputePolys)
	{
		computePolys();
		mClientComputePolys = false;
	}

	if(isLastState(state, stateKey))
		return false;

	setLastState(state, stateKey);

	mCameraPos = state->getCameraPosition();

	//
	// insert a render-image for every face that has to be rendered...
	//
	if(state->isObjectRendered(this))
	{
		RayInfo rInfo;
		int startFace = 1;
		if(sRenderMode == Full || sRenderTerrainDebug)
			startFace = 0;
		for(U32 faceidx = startFace; faceidx <= 5; faceidx++)
		{
			Face& face = mFaces[faceidx];
			//Point3F p = mFaces[i].center + mFaces[i].normal*0.1;
			//mIgnoreRayCast = false;
			//bool col = getContainer()->castRay(p,camPos,TacticalZoneObjectType,&rInfo);
			//mIgnoreRayCast = true;
			//if(!col)
			{
				//
				// find point on face that is closest to camera position...
				//

				Point3F p = face.plane.project(mCameraPos);

				F32 bestd = PARALLEL_PLANE;
				for(U32 otherfaceidx = 0; otherfaceidx <= 5; otherfaceidx++)
				{
					if(faceidx == otherfaceidx)
						continue;

					Face& otherface = mFaces[otherfaceidx];

					F32 d = otherface.plane.intersect(face.center, p);

					//Con::printf("%i to %i: %f", faceidx, otherfaceidx, d);

					if(d != PARALLEL_PLANE && d >= 0 && d <= 1 && d < bestd)
						bestd = d;
				}

				//Con::printf("%i bestd: %f", faceidx, bestd);

				if(bestd != PARALLEL_PLANE)
					p = face.center + (p - face.center) * bestd;

				TacticalZoneFaceRenderImage* image = new TacticalZoneFaceRenderImage;
				image->obj = this;
				image->isTranslucent = true;
				image->sortType = SceneRenderImage::Point;
				image->poly[0]  = p;
				image->face = faceidx;

				state->insertRenderImage(image);
			}
		}
   }

   return false;
}
#endif

void
TacticalZone::updateFogCoords(TexturedPolyList& polyList, const Point3F& camPos)
{
#if 0
	TexturedPolyList::Poly* p;
	for(p = polyList.mPolyList.begin(); p < polyList.mPolyList.end(); p++)
	{
		for(U32 i = 0; i < p->vertexCount; i++)
		{
			U32 vertexIndex = polyList.mIndexList[p->vertexStart+i];
			TexturedPolyList::Vertex& vertex = polyList.mVertexList[vertexIndex];
			F32 dist = (vertex.point-camPos).len();

			F32 coord[2];
			gClientSceneGraph->getFogCoordPair(dist, vertex.point.z, coord[0], coord[1]);
			vertex.texCoord.x = coord[0];
			vertex.texCoord.y = coord[1];
		}
	}
#endif
}

#if 0
void TacticalZone::renderObject(SceneState* state, SceneRenderImage* image)
{
	AssertFatal(dglIsInCanonicalState(), "Error, GL not in canonical state on entry");

	TacticalZoneFaceRenderImage* faceImage = dynamic_cast<TacticalZoneFaceRenderImage*>(image);
	if(!faceImage)
		return;

   RectI viewport;
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   dglGetViewport(&viewport);

   // Uncomment this if this is a "simple" (non-zone managing) object
   state->setupObjectProjection(this);

	//----- ACTUAL RENDER CODE FROM HERE -----

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // additive blending

	// Save texture params
	//GLint temp, mag, min, wrapS, wrapT;
	//glGetTexParameteriv ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, &temp ); mag = temp;
	//glGetTexParameteriv ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &temp ); min = temp;
	//glGetTexParameteriv ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, &temp ); wrapS = temp;
	//glGetTexParameteriv ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, &temp ); wrapT = temp;

	//
	//glDepthMask         ( GL_TRUE );
	//glEnable            ( GL_DEPTH_TEST );
	//glDepthFunc         ( GL_LEQUAL );

	glEnable(GL_CULL_FACE);

	// No Z-Fighting!
	glEnable(GL_POLYGON_OFFSET_FILL);
	//glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.0, -25.0);

	U32 face = faceImage->face;

	if(mDebugMode)
	{
		this->renderDebug(faceImage);
	}
	else
	{
		Point3F camPos = state->getCameraPosition();

		if(face == 0)
		{
			if(mRenderInteriors && !mInteriorPolys.isEmpty())
			{
				this->updateFogCoords(mInteriorPolys, camPos);
				this->renderInteriorPolyList(mInteriorPolys);
			}

			if(mRenderTerrain || sRenderTerrainDebug)
				this->renderTerrainPolyList(mTerrainPolys);

			if(mRenderTerrainGrid && !mTerrainGridLines.empty())
			{
				mRenderTerrainGridLines.clear();
				mRenderTerrainGridLines.merge(mTerrainGridLines);

				Point3F camVec(0, 0, 0);
				GameConnection* conn = GameConnection::getConnectionToServer();
				if(conn && conn->getControlObject())
				{
					MatrixF cam;
					conn->getControlCameraTransform(0, &cam);
					cam.getColumn(1, &camVec);
				}

				for(int i = 0; i < mTerrainGridVertices.size(); i++)
				{
					U32 vertexIndex = mTerrainGridVertices[i];

					TexturedPolyList::Vertex&        vertex = mTerrainGridVertexList[vertexIndex];
					TexturedPolyList::Vertex& raised_vertex = mRaisedTerrainGridVertexList[vertexIndex];
					TexturedPolyList::Vertex& render_vertex = mRenderTerrainGridVertexList[vertexIndex];

					Point3F vec = camPos - vertex.point;
					F32 dist = vec.len();
					//dist -= state->getNearPlane();

					F32 coord[2];
					gClientSceneGraph->getFogCoordPair(dist, vertex.point.z, coord[0], coord[1]);
					vertex.texCoord.x = coord[0];
					vertex.texCoord.y = coord[1];

					// This is only needed if the terrain does not render at full detail.
					if(TerrainRender::getScreenError() > 0)
					{
						// vertex may be endangered of being obscured by terrain
						if(true) //vertex.dangerScale > 0)
						{
							// sunken vertices that still have a high peakness are more endangered
							F32 normal_scale = 2; //vertex.dangerScale;

							// scale based on distance...
							normal_scale *= mClampF(dist/100, 0, 1);

							// decrease scale based on viewing angle...
							//if(camVec.z > 0) camVec.z = 0;
							//F32 dot = mDot(-camVec, render_vertex.normal);
							//if(dot < 0) dot = 0;
							//normal_scale *= dot;

							//Point3F p; p.interpolate(render_vertex.point, render_point, 0.1);
							vec.normalize();
							render_vertex.point = raised_vertex.point + vec * normal_scale;
						}
					}
#ifdef TACTICALZONE_DEBUG
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glEnable(GL_POINT_SIZE);
					glColor4f(0, 0, 0, 1);

					F32 min = getMin(vertex.peakness[0], vertex.peakness[1]);
					F32 max = getMax(vertex.peakness[0], vertex.peakness[1]);
					F32 shorter = getMin(mFabs(vertex.peakness[0]), mFabs(vertex.peakness[1]));
					F32 longer = getMax(mFabs(vertex.peakness[0]), mFabs(vertex.peakness[1]));

					if(max > 0)
					{
						if(min > -0.0001)
							glColor4f(1, 1, 1, 0.5);
						else
						{
							if(max > -min*2)
								glColor4f(1, 1, 1, 1);
							else
								glColor4f(1, 0, 0, 1);
						}
					}
					else
					{
						if(longer > 0.01)
							glColor4f(0, 1, 0, 1);
						else
							glColor4f(1, 0, 1, 1);
					}

					glPointSize(4);
					glBegin(GL_POINTS);
					glVertex3fv(render_vertex.point);
					glEnd();

					glColor4f(0, 0, 0, vertex.dangerScale);
					glPointSize(2);
					glBegin(GL_POINTS);
					glVertex3fv(render_vertex.point);
					glEnd();

					glPointSize(1);
					glDisable(GL_POINT_SIZE);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE); // restore additive blending

					Point3F p;

					p = render_vertex.point + render_vertex.normal * vertex.peakness[0] * 10;
					glColor4f(1, 0, 0, 1);
					glBegin(GL_LINES);
					glVertex3fv(render_vertex.point);
					glVertex3fv(p);
					glEnd();

					p = render_vertex.point + render_vertex.normal * vertex.peakness[1] * 10;
					glColor4f(0, 0, 1, 1);
					glBegin(GL_LINES);
					glVertex3fv(render_vertex.point);
					glVertex3fv(p);
					glEnd();
#endif
				}

				if(TerrainRender::getScreenError() == 0)
					this->renderTerrainGridLines(mRaisedTerrainGridVertexList);
				else
					this->renderTerrainGridLines(mRenderTerrainGridVertexList);

			}
		} // if(face == 0)

		if(!mBorderPolys[face].isEmpty())
		{
			this->updateFogCoords(mBorderPolys[face], camPos);
			this->renderBorderPolyList(mBorderPolys[face]);
		}
	}

	glPolygonOffset(0.0, 0.0);
	glDisable(GL_POLYGON_OFFSET_FILL);
	//glDisable(GL_POLYGON_OFFSET_LINE);
	glDepthMask         ( GL_TRUE );
	glDisable           ( GL_CULL_FACE );
	glDisable(GL_BLEND);

	// Restore texture params
	//glTexParameteri      ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag );
	//glTexParameteri      ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min );
	//glTexParameteri      ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS );
	//glTexParameteri      ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT );
	//

	//----- ACTUAL RENDER CODE ENDS HERE -----

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	dglSetViewport(viewport);

	AssertFatal(dglIsInCanonicalState(), "Error, GL not in canonical state on exit");
}

void TacticalZone::renderDebug(TacticalZoneFaceRenderImage* image)
{
	U32 face = image->face;

	switch(face)
	{
		case 0:  glColor4f(1,0,0,0.5); break;
		case 1:  glColor4f(0,1,0,0.5); break;
		case 2:  glColor4f(0,0,1,0.5); break;
		case 3:  glColor4f(1,0,1,0.5); break;
		case 4:  glColor4f(1,1,0,0.5); break;
		case 5:  glColor4f(0,1,1,0.5); break;
		default: glColor4f(1,1,1,0.5); break;
	}

	// faces...
	glBegin(GL_LINE_STRIP);
	glVertex3fv(mPoints[cubeFaces[face][0]]);
	glVertex3fv(mPoints[cubeFaces[face][1]]);
	glVertex3fv(mPoints[cubeFaces[face][2]]);
	glVertex3fv(mPoints[cubeFaces[face][3]]);
	glEnd();

	// normals...
	glBegin(GL_LINES);
	glVertex3fv(mFaces[face].center);
	glVertex3fv(mFaces[face].center+mFaces[face].plane*5);
	glEnd();

	// indicate spot that was used to sort the render image...
	glBegin(GL_LINES);
		for(U32 i = 0; i <= 3; i++)
		{
			glVertex3fv(mPoints[cubeFaces[face][i]]);
			glVertex3f(image->poly[0].x, image->poly[0].y, image->poly[0].z);
		}
	glEnd();
	glEnable(GL_POINT_SIZE);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(3);
	glBegin(GL_POINTS);
		glVertex3f(image->poly[0].x, image->poly[0].y, image->poly[0].z);
	glEnd();
	glPointSize(1.0);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_POINT_SIZE);
}

void TacticalZone::renderInteriorPolyList(TexturedPolyList& polyList)
{
	glColor4fv(this->getRenderColor());

	glEnableClientState ( GL_VERTEX_ARRAY );
	glVertexPointer     ( 3,GL_FLOAT,sizeof(TexturedPolyList::Vertex),polyList.mVertexList.address() );
	glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
	glTexCoordPointer   ( 2, GL_FLOAT, sizeof(TexturedPolyList::Vertex), &(polyList.mVertexList[0].texCoord) );

	glEnable            ( GL_TEXTURE_2D );
	glBindTexture       ( GL_TEXTURE_2D, gClientSceneGraph->getVisTexture().getGLName() );
	glTexEnvi           ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_LINE_WIDTH);
	glLineWidth(4.0);
	TexturedPolyList::Poly* p;
	for (p = polyList.mPolyList.begin(); p < polyList.mPolyList.end(); p++)
	{
		glDrawElements(GL_LINE_LOOP,p->vertexCount,
			GL_UNSIGNED_INT,&polyList.mIndexList[p->vertexStart]);
	}
	glLineWidth(1.0);
	glDisable(GL_LINE_WIDTH);
	glDisable(GL_LINE_SMOOTH);

	glDisable           ( GL_TEXTURE_2D );
	glTexEnvi           ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );

	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );
}

void TacticalZone::renderBorderPolyList(TexturedPolyList& polyList)
{
	glColor4fv(this->getRenderColor());

	glEnableClientState ( GL_VERTEX_ARRAY );
	glVertexPointer     ( 3,GL_FLOAT,sizeof(TexturedPolyList::Vertex),polyList.mVertexList.address() );
	glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
	glTexCoordPointer   ( 2, GL_FLOAT, sizeof(TexturedPolyList::Vertex), &(polyList.mVertexList[0].texCoord) );

	glEnable            ( GL_TEXTURE_2D );
	glBindTexture       ( GL_TEXTURE_2D, gClientSceneGraph->getVisTexture().getGLName() );
	glTexEnvi           ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	TexturedPolyList::Poly* p;
	for (p = polyList.mPolyList.begin(); p < polyList.mPolyList.end(); p++)
	{
		glDrawElements(GL_POLYGON,p->vertexCount,
			GL_UNSIGNED_INT,&polyList.mIndexList[p->vertexStart]);

		if(mDebugMode)
		{
			// render vertex normals...
			glColor4f( 0.0f, 1.0f, 0.0f, 1.0f );
			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_LINE_WIDTH);
			glLineWidth(3.0);
			glBegin(GL_LINES);
			for(U32 i = 0; i < p->vertexCount; i++)
			{
				U32 vertexIndex = polyList.mIndexList[p->vertexStart+i];
				TexturedPolyList::Vertex vertex = polyList.mVertexList[vertexIndex];
				glVertex3fv(vertex.point);
				glVertex3fv(vertex.point + vertex.normal);
			}
			glEnd();
			glLineWidth(1.0);
			glDisable(GL_LINE_WIDTH);
			glDisable(GL_LINE_SMOOTH);
		}
	}

	glTexEnvi            ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
	glDisable            ( GL_TEXTURE_2D );

	glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState ( GL_VERTEX_ARRAY );
}

void TacticalZone::renderTerrainPolyList(TexturedPolyList& polyList)
{
	TextureObject* texture = (TextureObject*)mDataBlock->textureHandle;
	if(texture == 0 && !sRenderTerrainDebug)
		return;

	glColor4fv          ( this->getRenderColor() );

	glEnableClientState ( GL_VERTEX_ARRAY );
	glVertexPointer     ( 3, GL_FLOAT, sizeof(TexturedPolyList::Vertex), &(polyList.mVertexList[0].point) );

	if(texture && !sRenderTerrainDebug)
	{
		glEnable            ( GL_TEXTURE_2D );
		//
		//glBindTexture       ( GL_TEXTURE_2D, gClientSceneGraph->getFogTexture().getGLName() );
		glTexEnvi           ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		glBindTexture       ( GL_TEXTURE_2D, texture->texGLName );
		glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
		glTexCoordPointer   ( 2, GL_FLOAT, sizeof(TexturedPolyList::Vertex), &(polyList.mVertexList[0].texCoord) );
		//glTexParameteri     ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		//glTexParameteri     ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri     ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri     ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		//glMatrixMode        ( GL_TEXTURE );
		//glPushMatrix        ();
		//glLoadIdentity      ();
		//glScalef(0.01, 0.01, 0.01);
		//glTranslatef        ( BaseDriftX, BaseDriftY, 0.0f );									// MM: Added Drift Translation.
		//glRotatef           ( 30.0f, 0.0f, 0.0f, 1.0f );										// MM: Removed Rotation.
		//glColorPointer      ( 4, GL_FLOAT, sizeof(vertex), &(m_pVertex[0].RGBA1a) );			// MM: Removed Colour Array.
		//glColor4f			( 1.0f, 1.0f, 1.0f, 1.0f );
	}

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	TexturedPolyList::Poly* p;
	for (p = polyList.mPolyList.begin(); p < polyList.mPolyList.end(); p++)
	{
		glDrawElements(GL_POLYGON, p->vertexCount,
			GL_UNSIGNED_INT, &polyList.mIndexList[p->vertexStart]);

		//glBegin(GL_POLYGON);
		//for(U32 i = 0; i < p->vertexCount; i++)
		//{
		//	U32 vertexIndex = polyList.mIndexList[p->vertexStart+i];
		//	TexturedPolyList::Vertex vertex = polyList.mVertexList[vertexIndex];
		//	glTexCoord2f(vertex.texCoord.x, vertex.texCoord.y);
		//	glVertex3fv(vertex.point);
		//}
		//glEnd();
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
	glTexEnvi            ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
	glDisable            ( GL_TEXTURE_2D );

	glDisableClientState ( GL_VERTEX_ARRAY );
}

void TacticalZone::renderTerrainGridLines(VertexList& vertexList)
{
	glColor4fv          ( this->getRenderColor() );

	glEnableClientState ( GL_VERTEX_ARRAY );
	glVertexPointer     ( 3, GL_FLOAT, sizeof(TexturedPolyList::Vertex), &(vertexList[0].point) );
	glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
	glTexCoordPointer   ( 2, GL_FLOAT, sizeof(TexturedPolyList::Vertex), &(mTerrainGridVertexList[0].texCoord) );

	glEnable            ( GL_TEXTURE_2D );
	glTexEnvi           ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glBindTexture       ( GL_TEXTURE_2D, gClientSceneGraph->getVisTexture().getGLName() );
	glEnable            ( GL_LINE_SMOOTH );
	glEnable            ( GL_LINE_WIDTH );
	glLineWidth         ( 2.0 );

	for(int i = 0; i < mRenderTerrainGridLines.size();)
	{
		U32 lineDirection = mRenderTerrainGridLines[i++];
		U32 numVertices = mRenderTerrainGridLines[i++];

		glDrawElements(GL_LINE_STRIP, numVertices,
			GL_UNSIGNED_INT, &mRenderTerrainGridLines.operator[](i));

		i += numVertices;
	}


#if 0
	for(int j = 0; j < lines.size(); j++)
	{
		Line* line = lines[j];

		glDrawElements(GL_LINE_STRIP, line->size(),
			GL_UNSIGNED_INT, &line->operator[](0));
	}
#endif

	glLineWidth          ( 1.0 );
	glDisable            ( GL_LINE_WIDTH );
	glDisable            ( GL_LINE_SMOOTH );
	glTexEnvi            ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
	glDisable            ( GL_TEXTURE_2D );

	glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState ( GL_VERTEX_ARRAY );
}
#endif

//--------------------------------------------------------------------------

bool TacticalZone::castRay(const Point3F& start, const Point3F& end, RayInfo* info)
{
	if(/*mCollisionsDisabled ||*/ mIgnoreRayCast)
		return false;

	//
   // collide against object box...
	//

   F32 st,et,fst = 0,fet = 1;
   F32 *bmin = &mObjBox.minExtents.x;
   F32 *bmax = &mObjBox.maxExtents.x;
   const F32* si = &start.x;
   const F32* ei = &end.x;

   for (int i = 0; i < 3; i++) {
      if (*si < *ei) {
         if (*si > *bmax || *ei < *bmin)
            return false;
         F32 di = *ei - *si;
         st = (*si < *bmin)? (*bmin - *si) / di: 0;
         et = (*ei > *bmax)? (*bmax - *si) / di: 1;
      }
      else {
         if (*ei > *bmax || *si < *bmin)
            return false;
         F32 di = *ei - *si;
         st = (*si > *bmax)? (*bmax - *si) / di: 0;
         et = (*ei < *bmin)? (*bmin - *si) / di: 1;
      }
      if (st > fst) fst = st;
      if (et < fet) fet = et;
      if (fet < fst)
         return false;
      bmin++; bmax++;
      si++; ei++;
   }

   info->normal = start - end;
   info->normal.normalizeSafe();
   getTransform().mulV( info->normal );

   info->t = fst;
   info->object = this;
   info->point.interpolate(start,end,fst);
   info->material = 0;
   return true;
}

//--------------------------------------------------------------------------

U32 TacticalZone::packUpdate(NetConnection* con, U32 mask, BitStream* stream)
{
	U32 retMask = Parent::packUpdate(con, mask, stream);

	if(stream->writeFlag(mask & GameBase::InitialUpdateMask))
	{
		stream->writeAffineTransform(mObjToWorld);
		mathWrite(*stream, mObjScale);
	}

	if( stream->writeFlag(mask & EditorMask) )
	{
		stream->writeFlag(mShowOnMinimap);
		stream->writeFlag(mRenderInteriors);
		stream->writeFlag(mRenderTerrain);
		stream->writeFlag(mRenderTerrainGrid);

		for(int i = 0; i < 6; i++)
		{
			if(stream->writeFlag(mBorderWidth[i] > 0.0f))
				stream->write(mBorderWidth[i]);
		}
	}

   if(stream->writeFlag(mask & FlashMask))
      stream->write(mFlashColor);

   if(stream->writeFlag(mask & FlickerMask))
      stream->write(mFlickerTime);

	return retMask;
}

void TacticalZone::unpackUpdate(NetConnection* con, BitStream* stream)
{
   Parent::unpackUpdate(con, stream);

	if( stream->readFlag() )
	{
		MatrixF temp;
		Point3F tempScale;

		// Transform
		stream->readAffineTransform(&temp);
		mathRead(*stream, &tempScale);

		setScale(tempScale);
		setTransform(temp);
	}

	if( stream->readFlag() )
	{
		mShowOnMinimap = stream->readFlag();
		mRenderInteriors = stream->readFlag();
		mRenderTerrain = stream->readFlag();
		mRenderTerrainGrid = stream->readFlag();

		for(int i = 0; i < 6; i++)
		{
			if(stream->readFlag())
				stream->read(&mBorderWidth[i]);
			else
				mBorderWidth[i] = 0.0f;
		}

		mClientComputePolys = true;
	}

	if( stream->readFlag() )
	{
      stream->read(&mFlashColor);
      for(U32 i = 0; i < Palette::NumSlots; i++)
         mCurrColor[i] = mFlashColor;
	}

	if( stream->readFlag() )
      stream->read(&mFlickerTime);
}

void TacticalZone::objectFound(SceneObject* obj, void* key)
{
	TacticalZone* zone = (TacticalZone*)key;

	if(obj->getTypeMask() & TerrainObjectType)
		obj->buildPolyList(PLC_Collision, &zone->mTerrainPolys, zone->mWorldBox, zone->mWorldSphere);
   else
      obj->buildPolyList(PLC_Collision, &zone->mInteriorPolys, zone->mWorldBox, zone->mWorldSphere);

	for(int i = 0; i < 6; i++)
		if(zone->mBorderWidth[i] > 0.0f)
			obj->buildPolyList(PLC_Collision, &zone->mBorderPolys[i], zone->mWorldBox, zone->mWorldSphere);
}

ConsoleMethod( TacticalZone, computeGrid, void, 2, 2, "")
{
	return object->computeGrid();
}

DefineEngineMethod( TacticalZone, flash, void, ( ColorF color ),,
   "@brief Make the zone flash in the specified color.\n\n"
   "@param color The flash color\n\n" )
{
   object->flash(color);
}

DefineEngineMethod( TacticalZone, setFlicker, void, ( S32 time ),,
   "@brief Make the zone flicker.\n\n"
   "@param time The flicker time\n\n" )
{
   object->setFlicker(time);
}
