// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _FIELDBRUSHOBJECT_H_
#define _FIELDBRUSHOBJECT_H_

#ifndef _SIM_H_
   #include "console/simObject.h"
#endif
#ifndef _SIMFIELDDICTIONARY_H_
   #include "console/simFieldDictionary.h"
#endif
#ifndef _CONSOLEINTERNAL_H_
   #include "console/consoleInternal.h"
#endif
#ifndef _TDICTIONARY_H_
   #include "core/util/tDictionary.h"
#endif


//-----------------------------------------------------------------------------
// Field Brush Object.
//-----------------------------------------------------------------------------

/// FieldBrushObject for static-field copying/pasting.
///
class FieldBrushObject : public SimObject
{
private:
    typedef SimObject Parent;

    // Destroy Fields.
    void destroyFields( void );

    StringTableEntry    mDescription;                   ///< Description.
    StringTableEntry    mSortName;                      ///< Sort Name.

public:
    FieldBrushObject();

    void copyFields( SimObject* pSimObject, const char* fieldList );
    void pasteFields( SimObject* pSimObject );
    
    static bool setDescription( void *object, const char *index, const char *data ) 
      { static_cast<FieldBrushObject*>(object)->setDescription(data); return false; };
    void setDescription( const char* description )  { mDescription = StringTable->insert(description); }
    StringTableEntry getDescription(void) const     { return mDescription; }

    static bool setSortName( void *object, const char *index, const char *data ) 
      { static_cast<FieldBrushObject*>(object)->setSortName(data); return false; };
    void setSortName( const char* sortName )  { mSortName = StringTable->insert(sortName); }
    StringTableEntry getSortName(void) const     { return mSortName; }

    static void initPersistFields();                    ///< Persist Fields.
    virtual void onRemove();                            ///< Called when the object is removed from the sim.

    DECLARE_CONOBJECT(FieldBrushObject);
};

#endif