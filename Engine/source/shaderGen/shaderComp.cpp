// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#include "shaderComp.h"

//**************************************************************************
// Connector Struct Component
//**************************************************************************

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
ShaderConnector::ShaderConnector()
{
   mCurTexElem = 0;
}

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
ShaderConnector::~ShaderConnector()
{
   // Elements freed by LangElement::freeElements()
}

