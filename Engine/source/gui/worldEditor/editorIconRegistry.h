// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _EDITORICONREGISTRY_H_
#define _EDITORICONREGISTRY_H_

#ifndef _GFXTEXTUREHANDLE_H_
#include "gfx/gfxTextureHandle.h"
#endif
#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif 

class SimObject;
class AbstractClassRep;


/// This class is used to find the correct icon file 
/// path for different SimObject class types.  It is
/// typically used by the editors.
class EditorIconRegistry
{
public:

   EditorIconRegistry();
   ~EditorIconRegistry();

   /// Loops thru all the AbstractClassReps looking for icons in the path.
   void loadFromPath( const String &path, bool overwrite );

   /// Adds a single icon to the registry.
   void add( const String &className, const String &imageFile, bool overwrite );

   /// Clears all the icons from the registry.
   void clear();

   /// Looks up an icon given an AbstractClassRep.
   /// Other findIcon methods redirect to this.
   GFXTexHandle findIcon( AbstractClassRep *classRep );

   /// Looks up an icon given a SimObject.
   GFXTexHandle findIcon( const SimObject *object );   

   /// Looks up an icon given a className.
   GFXTexHandle findIcon( const char *className );

   /// Returns true if an icon is defined this object's class.
   /// Does not recurse up the class hierarchy.
   bool hasIconNoRecurse( const SimObject *object );

protected:
 
   typedef HashTable<StringNoCase,GFXTexHandle> IconMap;
   IconMap mIcons;

   /// The default icon returned when no matching icon is found.
   GFXTexHandle mDefaultIcon;
};

/// The global registry of editor icons.
extern EditorIconRegistry gEditorIcons;

#endif // _EDITORICONREGISTRY_H_