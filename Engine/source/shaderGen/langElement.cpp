// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "core/strings/stringFunctions.h"
#include "core/util/str.h"

#include "langElement.h"

//**************************************************************************
// Language element
//**************************************************************************
Vector<LangElement*> LangElement::elementList( __FILE__, __LINE__ );

//--------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------
LangElement::LangElement()
{
   elementList.push_back( this );

   static U32 tempNum = 0;
   dSprintf( (char*)name, sizeof(name), "tempName%d", tempNum++ );
}

//--------------------------------------------------------------------------
// Find element of specified name
//--------------------------------------------------------------------------
LangElement * LangElement::find( const char *name )
{
   for( U32 i=0; i<elementList.size(); i++ )
   {
      if( !dStrcmp( (char*)elementList[i]->name, name ) )
      {
         return elementList[i];
      }
   }
   
   return NULL;
}

//--------------------------------------------------------------------------
// Delete existing elements
//--------------------------------------------------------------------------
void LangElement::deleteElements()
{
   for( U32 i=0; i<elementList.size(); i++ )
   {
      delete elementList[i];
   }
   
   elementList.setSize( 0 );

}

//--------------------------------------------------------------------------
// Set name
//--------------------------------------------------------------------------
void LangElement::setName(const char* newName )
{
   dStrncpy( ( char* ) name, newName, sizeof( name ) );
   name[ sizeof( name ) - 1 ] = '\0';
}

//**************************************************************************
// Variable
//**************************************************************************
U32 Var::texUnitCount = 0;

Var::Var()
{
   dStrcpy( (char*)type, "float4" );
   structName[0] = '\0';
   uniform = false;
   vertData = false;
   connector = false;
   sampler = false;
   mapsToSampler = false;
   texCoordNum = 0;
   constSortPos = cspUninit;
   arraySize = 1;
}

Var::Var( const char *inName, const char *inType )
{
   structName[0] = '\0';
   uniform = false;
   vertData = false;
   connector = false;
   sampler = false;
   mapsToSampler = false;
   texCoordNum = 0;
   constSortPos = cspUninit;
   arraySize = 1;

   setName( inName );
   setType( inType );
}

void Var::setUniform(const String& constType, const String& constName, ConstantSortPosition sortPos)
{ 
   uniform = true;
   setType(constType.c_str());
   setName(constName.c_str());   
   constSortPos = cspPass;      
}

//--------------------------------------------------------------------------
// Set struct name
//--------------------------------------------------------------------------
void Var::setStructName(const char* newName )
{
   dStrncpy( ( char* ) structName, newName, sizeof( structName ) );
   structName[ sizeof( structName ) - 1 ] = '\0';
}

//--------------------------------------------------------------------------
// Set connect name
//--------------------------------------------------------------------------
void Var::setConnectName(const char* newName )
{
   dStrncpy( ( char* ) connectName, newName, sizeof( connectName ) );
   connectName[ sizeof( connectName ) - 1 ] = '\0';
}

//--------------------------------------------------------------------------
// Set type
//--------------------------------------------------------------------------
void Var::setType(const char *newType )
{
   dStrncpy( ( char* ) type, newType, sizeof( type ) );
   type[ sizeof( type ) - 1 ] = '\0';
}

//--------------------------------------------------------------------------
// print
//--------------------------------------------------------------------------
void Var::print( Stream &stream )
{
   if( structName[0] != '\0' )
   {
      stream.write( dStrlen((char*)structName), structName );
      stream.write( 1, "." );
   }

   stream.write( dStrlen((char*)name), name );
}

//--------------------------------------------------------------------------
// Get next available texture unit number
//--------------------------------------------------------------------------
U32 Var::getTexUnitNum(U32 numElements)
{
   U32 ret = texUnitCount;
   texUnitCount += numElements;
   return ret;
}

//--------------------------------------------------------------------------
// Reset
//--------------------------------------------------------------------------
void Var::reset()
{
   texUnitCount = 0;
}

//**************************************************************************
// Multi line statement
//**************************************************************************
void MultiLine::addStatement( LangElement *elem )
{
   AssertFatal( elem, "Attempting to add empty statement" );

   mStatementList.push_back( elem );
}

//--------------------------------------------------------------------------
// Print
//--------------------------------------------------------------------------
void MultiLine::print( Stream &stream )
{
   for( U32 i=0; i<mStatementList.size(); i++ )
   {
      mStatementList[i]->print( stream );
   }
} 