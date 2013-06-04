// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "console/consoleParser.h"

#include "core/strings/stringFunctions.h"
#include "console/console.h"


namespace Compiler
{

static ConsoleParser *gParserList = NULL;
static ConsoleParser *gDefaultParser = NULL;

void freeConsoleParserList(void)
{
	while(gParserList)
	{
      ConsoleParser * pParser = gParserList;
		gParserList = pParser->next;
		delete pParser;
	}

	gDefaultParser = NULL;
}

bool addConsoleParser(char *ext, fnGetCurrentFile gcf, fnGetCurrentLine gcl, fnParse p, fnRestart r, fnSetScanBuffer ssb, bool def)
{
	AssertFatal(ext && gcf && gcl && p && r, "AddConsoleParser called with one or more NULL arguments");

	ConsoleParser * pParser = new ConsoleParser;
	if(pParser != NULL)
	{
		pParser->ext = ext;
		pParser->getCurrentFile = gcf;
		pParser->getCurrentLine = gcl;
		pParser->parse = p;
		pParser->restart = r;
		pParser->setScanBuffer = ssb;

		if(def)
			gDefaultParser = pParser;

		pParser->next = gParserList;
		gParserList = pParser;

		return true;
	}
	return false;
}

ConsoleParser * getParserForFile(const char *filename)
{
	if(filename == NULL)
		return gDefaultParser;

	char *ptr = dStrrchr((char *)filename, '.');
	if(ptr != NULL)
	{
		ptr++;

		ConsoleParser *p;
		for(p = gParserList; p; p = p->next)
		{
			if(dStricmp(ptr, p->ext) == 0)
				return p;
		}
	}

	return gDefaultParser;
}

} // end namespace Con
