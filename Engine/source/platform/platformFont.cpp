// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "platform/platformFont.h"


const char *getCharSetName(const U32 charSet)
{
   switch(charSet)
   {
   case TGE_ANSI_CHARSET:        return "ansi";
   case TGE_SYMBOL_CHARSET:      return "symbol";
   case TGE_SHIFTJIS_CHARSET:    return "shiftjis";
   case TGE_HANGEUL_CHARSET:     return "hangeul";
   case TGE_HANGUL_CHARSET:      return "hangul";
   case TGE_GB2312_CHARSET:      return "gb2312";
   case TGE_CHINESEBIG5_CHARSET: return "chinesebig5";
   case TGE_OEM_CHARSET:         return "oem";
   case TGE_JOHAB_CHARSET:       return "johab";
   case TGE_HEBREW_CHARSET:      return "hebrew";
   case TGE_ARABIC_CHARSET:      return "arabic";
   case TGE_GREEK_CHARSET:       return "greek";
   case TGE_TURKISH_CHARSET:     return "turkish";
   case TGE_VIETNAMESE_CHARSET:  return "vietnamese";
   case TGE_THAI_CHARSET:        return "thai";
   case TGE_EASTEUROPE_CHARSET:  return "easteurope";
   case TGE_RUSSIAN_CHARSET:     return "russian";
   case TGE_MAC_CHARSET:         return "mac";
   case TGE_BALTIC_CHARSET:      return "baltic";
   }

   AssertISV(false, "getCharSetName - unknown charset! Update table in platformString.cc!");
   return "";
}