// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _EXTRAFIELD_H_
#define _EXTRAFIELD_H_

class Stream;

namespace Zip
{

/// @addtogroup zipint_group
/// @ingroup zip_group
// @{


// Forward Refs
class ExtraField;

// Creation Helpers
typedef ExtraField *(*ExtraFieldCreateFn)();

template<class T> ExtraField * createExtraField()
{
   return new T;
}

// ExtraField base class
class ExtraField
{
   ExtraField *mNext;

protected:
   U16 mID;
   ExtraFieldCreateFn mCreateFn;

public:
   ExtraField()
   {
      mID = 0;
      mCreateFn = NULL;
   }
   ExtraField(U16 id, ExtraFieldCreateFn fnCreate);
   
   virtual ~ExtraField() {}
   
   inline U16 getID()                  { return mID; }

   virtual bool read(Stream *stream) = 0;

   // Run time creation methods
   static ExtraField *create(U16 id);
};

#define  DeclareExtraField(name) \
   name(U16 id, ExtraFieldCreateFn fnCreate) : Parent(id, fnCreate) {}

#define ImplementExtraField(name, id)       \
   name gExtraField##name##instance(id, &createExtraField<name>);

// @}

} // end namespace Zip

#endif // _EXTRAFIELD_H_
