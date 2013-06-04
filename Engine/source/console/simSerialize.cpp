// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"

#include "console/console.h"
#include "console/simBase.h"
#include "core/stream/bitStream.h"
#include "core/stream/fileStream.h"
#include "console/engineAPI.h"


//-----------------------------------------------------------------------------
// SimObject Methods
//-----------------------------------------------------------------------------

bool SimObject::writeObject(Stream *stream)
{
   stream->writeString(getName() ? getName() : "");

   // Static fields
   AbstractClassRep *rep = getClassRep();
   AbstractClassRep::FieldList &fieldList = rep->mFieldList;
   AbstractClassRep::FieldList::iterator itr;
   
   U32 savePos = stream->getPosition();
   U32 numFields = fieldList.size();
   stream->write(numFields);

   for(itr = fieldList.begin();itr != fieldList.end();itr++)
   {
      if( itr->type >= AbstractClassRep::ARCFirstCustomField )
      {
         numFields--;
         continue;
      }

      const char *field = getDataField(itr->pFieldname, NULL);
      if(field == NULL)
         field = "";

      stream->writeString(itr->pFieldname);
      stream->writeString(field);
   }

   // Dynamic Fields
   if(mCanSaveFieldDictionary)
   {
      SimFieldDictionary * fieldDictionary = getFieldDictionary();
      for(SimFieldDictionaryIterator ditr(fieldDictionary); *ditr; ++ditr)
      {
         SimFieldDictionary::Entry * entry = (*ditr);

         stream->writeString(entry->slotName);
         stream->writeString(entry->value);
         numFields++;
      }
   }

   // Overwrite the number of fields with the correct value
   U32 savePos2 = stream->getPosition();
   stream->setPosition(savePos);
   stream->write(numFields);
   stream->setPosition(savePos2);

   return true;
}

bool SimObject::readObject(Stream *stream)
{
   const char *name = stream->readSTString(true);
   if(name && *name)
      assignName(name);

   U32 numFields;
   stream->read(&numFields);

   for(S32 i = 0;i < numFields;i++)
   {
      const char *fieldName = stream->readSTString();
      const char *data = stream->readSTString();

      setDataField(fieldName, NULL, data);
   }
   return true;
}

//-----------------------------------------------------------------------------
// SimSet Methods
//-----------------------------------------------------------------------------

bool SimSet::writeObject( Stream *stream )
{
   if(! Parent::writeObject(stream))
      return false;

   stream->write(size());
   for(SimSet::iterator i = begin();i < end();++i)
   {
      if(! Sim::saveObject((*i), stream))
         return false;
   }
   return true;
}

bool SimSet::readObject( Stream *stream )
{
   if(! Parent::readObject(stream))
      return false;

   U32 numObj;
   stream->read(&numObj);

   for(U32 i = 0;i < numObj;i++)
   {
      SimObject *obj = Sim::loadObjectStream(stream);
      if(obj == NULL)
         return false;

      addObject(obj);
   }

   return true;
}

//-----------------------------------------------------------------------------
// Sim Functions
//-----------------------------------------------------------------------------

namespace Sim
{

bool saveObject(SimObject *obj, const char *filename)
{
   FileStream *stream;
   if((stream = FileStream::createAndOpen( filename, Torque::FS::File::Write )) == NULL)
      return false;

   bool ret = saveObject(obj, stream);
   delete stream;

   return ret;
}

bool saveObject(SimObject *obj, Stream *stream)
{
   stream->writeString(obj->getClassName());
   return obj->writeObject(stream);
}

//-----------------------------------------------------------------------------

SimObject *loadObjectStream(const char *filename)
{
   FileStream * stream;
   if((stream = FileStream::createAndOpen( filename, Torque::FS::File::Read )) == NULL)
      return NULL;

   SimObject * ret = loadObjectStream(stream);
   delete stream;
   return ret;
}

SimObject *loadObjectStream(Stream *stream)
{
   const char *className = stream->readSTString(true);
   ConsoleObject *conObj = ConsoleObject::create(className);
   if(conObj == NULL)
   {
      Con::errorf("Sim::restoreObjectStream - Could not create object of class \"%s\"", className);
      return NULL;
   }

   SimObject *simObj = dynamic_cast<SimObject *>(conObj);
   if(simObj == NULL)
   {
      Con::errorf("Sim::restoreObjectStream - Object of class \"%s\" is not a SimObject", className);
      delete simObj;
      return NULL;
   }

   if( simObj->readObject(stream)
       && simObj->registerObject() )
      return simObj;

   delete simObj;
   return NULL;
}

} // end namespace Sim

//-----------------------------------------------------------------------------
// Console Functions
//-----------------------------------------------------------------------------

DefineEngineFunction(saveObject, bool, ( SimObject *object, const char *filename ),,
				"@brief Serialize the object to a file.\n\n"
				"@param object The object to serialize.\n"
				"@param filename The file name and path.\n"
				"@ingroup Console\n")
{
   return object && Sim::saveObject(object, filename);
}

DefineEngineFunction(loadObject, SimObject*, ( const char *filename ),,
				"@brief Loads a serialized object from a file.\n\n"
				"@param Name and path to text file containing the object\n"
				"@ingroup Console\n")
{
   return Sim::loadObjectStream(filename);
}
