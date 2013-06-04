// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "console/simBase.h"
#include "core/util/tVector.h"

class SimXMLDocument;

///
class Settings : public SimObject
{
private:
   FileName         mFile;
   Vector<String>   mGroupStack;
	S32              mSearchPos;
	Vector<String>   mSearchResults;

public:
   Settings();
   virtual ~Settings();

   // Required in all ConsoleObject subclasses.
   typedef SimObject Parent;
   DECLARE_CONOBJECT(Settings);
   static void initPersistFields();

   /// These will set and get the values, with an option default value passed in to the get 
   void setDefaultValue(const UTF8 *settingName, const UTF8 *settingValue, const UTF8 *settingType="");
   void setValue(const UTF8 *settingName, const UTF8 *settingValue = "");
   const UTF8 *value(const UTF8 *settingName, const UTF8 *defaultValue = "");
   void remove(const UTF8 *settingName, bool includeDefaults = false);
   void clearAllFields();
   bool write();
   bool read();
   void readLayer(SimXMLDocument *document, String groupStack = String(""));

   void beginGroup(const UTF8 *groupName, bool fromStart = false);
   void endGroup();
   void clearGroups();
   
   void buildGroupString(String &name, const UTF8 *settingName);
   const UTF8 *getCurrentGroups();

	//S32 buildSearchList(const char* pattern, bool deepSearch = false, bool defaultsSearch = false);
	const char* findFirstValue(const char* pattern, bool deepSearch = false, bool includeDefaults = false);
	const char* findNextValue();
};

class SettingSaveNode
{
public:
   Vector<SettingSaveNode*> mGroupNodes;
   Vector<SettingSaveNode*> mSettingNodes;

   String mName;
   String mValue;
   bool mIsGroup;

   SettingSaveNode(){};
   SettingSaveNode(const String &name, bool isGroup = false)
   {
      mName = name;
	   mIsGroup = isGroup;
   }
   SettingSaveNode(const String &name, const String &value)
   {
      mName = name;
	   mValue = value;
	   mIsGroup = false;
   }
   ~SettingSaveNode()
   {
      clear();
   }

   void addValue(const UTF8 *name, const UTF8 *value);
   S32 getGroupCount(const String &name);
   String getGroup(const String &name, S32 num);
   String getSettingName(const String &name);
   void buildDocument(SimXMLDocument *document, bool skipWrite = false);

   void clear();
};

#endif