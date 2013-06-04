// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "gfx/gl/gfxGLOcclusionQuery.h"
#include "gfx/gl/ggl/ggl.h"

GFXGLOcclusionQuery::GFXGLOcclusionQuery(GFXDevice* device) : 
   GFXOcclusionQuery(device), mQuery(0)
{
   glGenQueries(1, &mQuery);
}

GFXGLOcclusionQuery::~GFXGLOcclusionQuery()
{
   glDeleteQueries(1, &mQuery);
}

bool GFXGLOcclusionQuery::begin()
{
   glBeginQuery(GL_SAMPLES_PASSED, mQuery);
   return true;
}

void GFXGLOcclusionQuery::end()
{
   glEndQuery(GL_SAMPLES_PASSED);
}

GFXOcclusionQuery::OcclusionQueryStatus GFXGLOcclusionQuery::getStatus(bool block, U32* data)
{
   // If this ever shows up near the top of a profile 
   // then your system is GPU bound.
   PROFILE_SCOPE(GFXGLOcclusionQuery_getStatus);
   
   GLint numPixels = 0;
   GLint queryDone = false;
   
   if (block)
      queryDone = true;
   else
      glGetQueryObjectiv(mQuery, GL_QUERY_RESULT_AVAILABLE, &queryDone);
   
   if (queryDone)
      glGetQueryObjectiv(mQuery, GL_QUERY_RESULT, &numPixels);
   else
      return Waiting;
   
   if (data)
      *data = numPixels;
   
   return numPixels > 0 ? NotOccluded : Occluded;
}

void GFXGLOcclusionQuery::zombify()
{
   glDeleteQueries(1, &mQuery);
   mQuery = 0;
}

void GFXGLOcclusionQuery::resurrect()
{
   glGenQueries(1, &mQuery);
}

const String GFXGLOcclusionQuery::describeSelf() const
{
   // We've got nothing
   return String();
}
