// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"

#include "NOTC/gui/notcGuiBitmapCtrl.h"

#include "console/console.h"
#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "gfx/gfxDevice.h"
#include "gfx/gfxDrawUtil.h"


IMPLEMENT_CONOBJECT(notcGuiBitmapCtrl);

ConsoleDocClass( notcGuiBitmapCtrl,
   "@brief A gui control that is used to display an image.\n\n"
   
   "The image is stretched to the constraints of the control by default. However, the control can also\n"
   "tile the image as well.\n\n"

   "The image itself is stored inside the notcGuiBitmapCtrl::bitmap field. The boolean value that decides\n"
   "whether the image is stretched or tiled is stored inside the notcGuiBitmapCtrl::wrap field.\n"
   
   "@tsexample\n"
   "// Create a tiling notcGuiBitmapCtrl that displays \"myImage.png\"\n"
   "%bitmapCtrl = new notcGuiBitmapCtrl()\n"
   "{\n"
   "   bitmap = \"myImage.png\";\n"
   "   wrap = \"true\";\n"
   "};\n"
   "@endtsexample\n\n"
   
   "@ingroup GuiControls"
);

notcGuiBitmapCtrl::notcGuiBitmapCtrl(void)
 : mBitmapName(),
   mStartPoint(0, 0),
   mWrap(false),
   mFlipX(false),
   mFlipY(false),
   mCrisp(false)
{	
}

bool notcGuiBitmapCtrl::setBitmapName( void *object, const char *index, const char *data )
{
   // Prior to this, you couldn't do bitmap.bitmap = "foo.jpg" and have it work.
   // With protected console types you can now call the setBitmap function and
   // make it load the image.
   static_cast<notcGuiBitmapCtrl *>( object )->setBitmap( data );

   // Return false because the setBitmap method will assign 'mBitmapName' to the
   // argument we are specifying in the call.
   return false;
}

void notcGuiBitmapCtrl::initPersistFields()
{
   addGroup( "Bitmap" );
   
      addProtectedField( "bitmap", TypeImageFilename, Offset( mBitmapName, notcGuiBitmapCtrl ),
         &setBitmapName, &defaultProtectedGetFn,
         "The bitmap file to display in the control." );
      addField( "wrap",   TypeBool,     Offset( mWrap, notcGuiBitmapCtrl ),
         "If true, the bitmap is tiled inside the control rather than stretched to fit." );
      addField( "flipX",   TypeBool,    Offset( mFlipX, notcGuiBitmapCtrl ),
         "If true, the bitmap is flipped horizontally" );
      addField( "flipY",   TypeBool,    Offset( mFlipY, notcGuiBitmapCtrl ),
         "If true, the bitmap is flipped vertically." );
      addField( "crisp",   TypeBool,    Offset( mCrisp, notcGuiBitmapCtrl ),
         "If true, the bitmap won't become blurry as it's scaled up" );      

   endGroup( "Bitmap" );

   Parent::initPersistFields();
}

bool notcGuiBitmapCtrl::onWake()
{
   if (! Parent::onWake())
      return false;
   setActive(true);
   setBitmap(mBitmapName);
   return true;
}

void notcGuiBitmapCtrl::onSleep()
{
   if ( !mBitmapName.equal("texhandle", String::NoCase) )
      mTextureObject = NULL;

   Parent::onSleep();
}

//-------------------------------------
void notcGuiBitmapCtrl::inspectPostApply()
{
   // if the extent is set to (0,0) in the gui editor and appy hit, this control will
   // set it's extent to be exactly the size of the bitmap (if present)
   Parent::inspectPostApply();

   if (!mWrap && (getExtent().x == 0) && (getExtent().y == 0) && mTextureObject)
   {
      setExtent( mTextureObject->getWidth(), mTextureObject->getHeight());
   }
}

void notcGuiBitmapCtrl::setBitmap( const char *name, bool resize )
{
   mBitmapName = name;
   if ( !isAwake() )
      return;

   if ( mBitmapName.isNotEmpty() )
	{
      if ( !mBitmapName.equal("texhandle", String::NoCase) )
		   mTextureObject.set( mBitmapName, &GFXDefaultGUIProfile, avar("%s() - mTextureObject (line %d)", __FUNCTION__, __LINE__) );

      // Resize the control to fit the bitmap
      if ( mTextureObject && resize )
      {
         setExtent( mTextureObject->getWidth(), mTextureObject->getHeight() );
         updateSizing();
      }
   }
   else
      mTextureObject = NULL;

   setUpdate();
}

void notcGuiBitmapCtrl::updateSizing()
{
   if(!getParent())
      return;
   // updates our bounds according to our horizSizing and verSizing rules
   RectI fakeBounds( getPosition(), getParent()->getExtent());
   parentResized( fakeBounds, fakeBounds);
}

void notcGuiBitmapCtrl::setBitmapHandle(GFXTexHandle handle, bool resize)
{
   mTextureObject = handle;

   mBitmapName = String("texhandle");

   // Resize the control to fit the bitmap
   if (resize) 
   {
      setExtent(mTextureObject->getWidth(), mTextureObject->getHeight());
      updateSizing();
   }
}

void notcGuiBitmapCtrl::onRender(Point2I offset, const RectI &updateRect)
{
   if (mTextureObject)
   {
      GFX->getDrawUtil()->setBitmapModulation(mProfile->mFillColor);

      GFXBitmapFlip flip = GFXBitmapFlip_None;
      if(mFlipX && mFlipY)
      {
         flip = GFXBitmapFlip_XY;
      }
      else
      {
         if(mFlipX)
            flip = GFXBitmapFlip_X;
         if(mFlipY)
            flip = GFXBitmapFlip_Y;
      }

      GFXTextureFilterType filter = GFXTextureFilterLinear;
      if(mCrisp)
         filter = GFXTextureFilterPoint;

		if(mWrap)
		{
         // We manually draw each repeat because non power of two textures will 
         // not tile correctly when rendered with GFX->drawBitmapTile(). The non POT
         // bitmap will be padded by the hardware, and we'll see lots of slack
         // in the texture. So... lets do what we must: draw each repeat by itself:
 			GFXTextureObject* texture = mTextureObject;
			RectI srcRegion;
			RectI dstRegion;
			F32 xdone = ((F32)getExtent().x/(F32)texture->mBitmapSize.x)+1;
			F32 ydone = ((F32)getExtent().y/(F32)texture->mBitmapSize.y)+1;

			S32 xshift = mStartPoint.x%texture->mBitmapSize.x;
			S32 yshift = mStartPoint.y%texture->mBitmapSize.y;
			for(S32 y = 0; y < ydone; ++y)
				for(S32 x = 0; x < xdone; ++x)
				{
		 			srcRegion.set(0,0,texture->mBitmapSize.x,texture->mBitmapSize.y);
  					dstRegion.set( ((texture->mBitmapSize.x*x)+offset.x)-xshift,
								      ((texture->mBitmapSize.y*y)+offset.y)-yshift,
								      texture->mBitmapSize.x,
								      texture->mBitmapSize.y);
               GFX->getDrawUtil()->drawBitmapStretchSR(texture,dstRegion, srcRegion, flip, filter);
				}

		}
		else
      {
         RectI rect(offset, getExtent());
         GFX->getDrawUtil()->drawBitmapStretch(mTextureObject, rect, flip, filter, false);
      }

      GFX->getDrawUtil()->clearBitmapModulation();
   }

   if (mProfile->mBorder || !mTextureObject)
   {
      RectI rect(offset.x, offset.y, getExtent().x, getExtent().y);
      GFX->getDrawUtil()->drawRect(rect, mProfile->mBorderColor);
   }

   renderChildControls(offset, updateRect);
}

void notcGuiBitmapCtrl::setValue(S32 x, S32 y)
{
   if (mTextureObject)
   {
		x += mTextureObject->getWidth() / 2;
		y += mTextureObject->getHeight() / 2;
  	}
  	while (x < 0)
  		x += 256;
  	mStartPoint.x = x % 256;

  	while (y < 0)
  		y += 256;
  	mStartPoint.y = y % 256;
}

DefineEngineMethod( notcGuiBitmapCtrl, setValue, void, ( S32 x, S32 y ),,
   "Set the offset of the bitmap within the control.\n"
   "@param x The x-axis offset of the image.\n"
   "@param y The y-axis offset of the image.\n")
{
   object->setValue(x, y);
}


//

static ConsoleDocFragment _snotcGuiBitmapCtrlSetBitmap1(
   "@brief Assign an image to the control.\n\n"
   "Child controls with resize according to their layout settings.\n"
   "@param filename The filename of the image.\n"
   "@param resize Optional parameter. If true, the GUI will resize to fit the image.",
   "notcGuiBitmapCtrl", // The class to place the method in; use NULL for functions.
   "void setBitmap( String filename, bool resize );" ); // The definition string.

static ConsoleDocFragment _snotcGuiBitmapCtrlSetBitmap2(
   "@brief Assign an image to the control.\n\n"
   "Child controls will resize according to their layout settings.\n"
   "@param filename The filename of the image.\n"
   "@param resize A boolean value that decides whether the ctrl refreshes or not.",
   "notcGuiBitmapCtrl", // The class to place the method in; use NULL for functions.
   "void setBitmap( String filename );" ); // The definition string.


//"Set the bitmap displayed in the control. Note that it is limited in size, to 256x256."
DefineConsoleMethod( notcGuiBitmapCtrl, setBitmap, void, ( const char * fileRoot, bool resize), ( false),
   "( String filename | String filename, bool resize ) Assign an image to the control.\n\n"
   "@hide" )
{
   char filename[1024];
   Con::expandScriptFilename(filename, sizeof(filename), fileRoot);
   object->setBitmap(filename, resize );
}
