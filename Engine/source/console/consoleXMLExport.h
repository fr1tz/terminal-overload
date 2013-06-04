// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _CONSOLEXMLEXPORT_H_
#define _CONSOLEXMLEXPORT_H_

#ifndef _TORQUE_STRING_H_
#include "core/util/str.h"
#endif

class SimXMLDocument;

/// @defgroup console_reflection Reflection
/// @ingroup console_system Console System
///
/// Exports console information to XML representation
/// @{

namespace Con {

   class XMLExport
   {

   public:

      XMLExport();
      ~XMLExport();

      // writes console information in XML format to  the file specified
      void exportXML(String& str);

   private:

      void exportBaseTypes();
      void exportEntryTypes();
      void exportNamespaces();

      SimXMLDocument *mXML;

   };

};

/// @}

#endif _CONSOLEXMLEXPORT_H_
