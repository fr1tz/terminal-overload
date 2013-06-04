// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "lighting/common/scenePersist.h"

#include "lighting/lightingInterfaces.h"
#include "scene/sceneManager.h"
#include "lighting/lightManager.h"


U32 PersistInfo::smFileVersion   = 0x11;

PersistInfo::~PersistInfo()
{
	for(U32 i = 0; i < mChunks.size(); i++)
		delete mChunks[i];
}

//------------------------------------------------------------------------------
bool PersistInfo::read(Stream & stream)
{
	U32 version;
	if(!stream.read(&version) || version != smFileVersion)
		return(false);

	U32 numChunks;
	if(!stream.read(&numChunks))
		return(false);

	if(numChunks == 0)
		return(false);

	// read in all the chunks
	for(U32 i = 0; i < numChunks; i++)
	{
		U32 chunkType;
		if(!stream.read(&chunkType))
			return(false);

		// MissionChunk must be first chunk
		if(i == 0 && chunkType != PersistChunk::MissionChunkType)
			return(false);
		if(i != 0 && chunkType == PersistChunk::MissionChunkType)
			return(false);

      // Create the right chunk for the system 
      bool bChunkFound = false; 
      SceneLightingInterfaces sli = LIGHTMGR->getSceneLightingInterface()->mAvailableSystemInterfaces;
      for(SceneLightingInterface** itr = sli.begin(); itr != sli.end() && !bChunkFound; itr++)
      {
         PersistInfo::PersistChunk* pc = (*itr)->createPersistChunk(chunkType);
         if (pc != NULL)
         {
            mChunks.push_back(pc);
            bChunkFound = true;            
         }
      }
         
      if (!bChunkFound)
      {
		   // create the chunk
		   switch(chunkType)
		   {
		   case PersistChunk::MissionChunkType:
			   mChunks.push_back(new PersistInfo::MissionChunk);
			   break;

		   default:
			   return(false);
			   break;
		   }
      }

		// load the chunk info
		if(!mChunks[i]->read(stream))
			return(false);
	}

	return(true);
}

bool PersistInfo::write(Stream & stream)
{
	if(!stream.write(smFileVersion))
		return(false);

	if(!stream.write((U32)mChunks.size()))
		return(false);

	for(U32 i = 0; i < mChunks.size(); i++)
	{
		if(!stream.write(mChunks[i]->mChunkType))
			return(false);
		if(!mChunks[i]->write(stream))
			return(false);
	}

	return(true);
}

//------------------------------------------------------------------------------
// Class SceneLighting::PersistInfo::PersistChunk
//------------------------------------------------------------------------------
bool PersistInfo::PersistChunk::read(Stream & stream)
{
	if(!stream.read(&mChunkCRC))
		return(false);
	return(true);
}

bool PersistInfo::PersistChunk::write(Stream & stream)
{
	if(!stream.write(mChunkCRC))
		return(false);
	return(true);
}

//------------------------------------------------------------------------------
// Class SceneLighting::PersistInfo::MissionChunk
//------------------------------------------------------------------------------
PersistInfo::MissionChunk::MissionChunk()
{
	mChunkType = PersistChunk::MissionChunkType;
}