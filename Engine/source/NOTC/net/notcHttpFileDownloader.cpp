// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "NOTC/net/notcHttpFileDownloader.h"

#include "platform/platform.h"
#include "core/stream/fileStream.h"
#include "console/simBase.h"
#include "console/consoleInternal.h"
#include "console/engineAPI.h"

IMPLEMENT_CONOBJECT(notcHttpFileDownloader);

#if 0
ConsoleDocClass( notcHttpFileDownloader,
   "@brief Allows communications between the game and a server using HTTP.\n\n"
   
   "notcHttpFileDownloader is derrived from TCPObject and makes use of the same callbacks for dealing with "
   "connections and received data.  However, the way in which you use notcHttpFileDownloader to connect "
   "with a server is different than TCPObject.  Rather than opening a connection, sending data, "
   "waiting to receive data, and then closing the connection, you issue a get() or post() and "
   "handle the response.  The connection is automatically created and destroyed for you.\n\n"
   
   "@tsexample\n"
      "// In this example we'll retrieve the weather in Las Vegas using\n"
      "// Google's API.  The response is in XML which could be processed\n"
      "// and used by the game using SimXMLDocument, but we'll just output\n"
      "// the results to the console in this example.\n\n"

      "// Define callbacks for our specific notcHttpFileDownloader using our instance's\n"
      "// name (WeatherFeed) as the namespace.\n\n"

      "// Handle an issue with resolving the server's name\n"
      "function WeatherFeed::onDNSFailed(%this)\n"
      "{\n"
      "   // Store this state\n"
      "   %this.lastState = \"DNSFailed\";\n\n"

      "   // Handle DNS failure\n"
      "}\n\n"

      "function WeatherFeed::onConnectFailed(%this)\n"
      "{\n"
      "   // Store this state\n"
      "   %this.lastState = \"ConnectFailed\";\n\n"
      "   // Handle connection failure\n"
      "}\n\n"

      "function WeatherFeed::onDNSResolved(%this)\n"
      "{\n"
      "   // Store this state\n"
      "   %this.lastState = \"DNSResolved\";\n\n"
      "}\n\n"

      "function WeatherFeed::onConnected(%this)\n"
      "{\n"
      "   // Store this state\n"
      "   %this.lastState = \"Connected\";\n\n"

      "   // Clear our buffer\n"
      "   %this.buffer = \"\";\n"
      "}\n\n"

      "function WeatherFeed::onDisconnect(%this)\n"
      "{\n"
      "   // Store this state\n"
      "   %this.lastState = \"Disconnected\";\n\n"

      "   // Output the buffer to the console\n"
      "   echo(\"Google Weather Results:\");\n"
      "   echo(%this.buffer);\n"
      "}\n\n"

      "// Handle a line from the server\n"
      "function WeatherFeed::onLine(%this, %line)\n"
      "{\n"
      "   // Store this line in out buffer\n"
      "   %this.buffer = %this.buffer @ %line;\n"
      "}\n\n"

      "// Create the notcHttpFileDownloader\n"
      "%feed = new notcHttpFileDownloader(WeatherFeed);\n\n"

      "// Define a dynamic field to store the last connection state\n"
      "%feed.lastState = \"None\";\n\n"

      "// Send the GET command\n"
      "%feed.get(\"www.google.com:80\", \"/ig/api\", \"weather=Las-Vegas,US\");\n"
	"@endtsexample\n\n" 
   
   "@see TCPObject\n"

   "@ingroup Networking\n"
);
#endif

IMPLEMENT_CALLBACK(notcHttpFileDownloader, onDownloadComplete, void, (),(),
   "Called when download has finished successfully.\n"
   );

//--------------------------------------

notcHttpFileDownloader::notcHttpFileDownloader()
{
   mHostName = 0;
   mPath = 0;
   mQuery = 0;
   mPost = 0;
   mBufferSave = 0;
   mFileStream = NULL;
}

notcHttpFileDownloader::~notcHttpFileDownloader()
{
   dFree(mHostName);
   dFree(mPath);
   dFree(mQuery);
   dFree(mPost);

   SAFE_DELETE(mFileStream);

   mHostName = 0;
   mPath = 0;
   mQuery = 0;
   mPost = 0;
   dFree(mBufferSave);
}

//--------------------------------------
//--------------------------------------
bool notcHttpFileDownloader::download(const char *host, const char *path, const char* file, const char *query)
{
   if(mHostName)
      dFree(mHostName);
   if(mPath)
      dFree(mPath);
   if(mQuery)
      dFree(mQuery);
   if(mPost)
      dFree(mPost);
   if(mBufferSave)
      dFree(mBufferSave);

   SAFE_DELETE(mFileStream);
   if((mFileStream = FileStream::createAndOpen(file, Torque::FS::File::Write)) == NULL)
      return false;

   mBufferSave = 0;
   mHostName = dStrdup(host);
   mPath = dStrdup(path);
   if(query)
      mQuery = dStrdup(query);
   else
      mQuery = NULL;
   mPost = NULL;

   this->connect(host);
}

static char getHex(char c)
{
   if(c <= 9)
      return c + '0';
   return c - 10 + 'A';
}

static S32 getHexVal(char c)
{
   if(c >= '0' && c <= '9')
      return c - '0';
   else if(c >= 'A' && c <= 'Z')
      return c - 'A' + 10;
   else if(c >= 'a' && c <= 'z')
      return c - 'a' + 10;
   return -1;
}

void notcHttpFileDownloader::expandPath(char *dest, const char *path, U32 destSize)
{
   static bool asciiEscapeTableBuilt = false;
   static bool asciiEscapeTable[256];
   if(!asciiEscapeTableBuilt)
   {
      asciiEscapeTableBuilt = true;
      U32 i;
      for(i = 0; i <= ' '; i++)
         asciiEscapeTable[i] = true;
      for(;i <= 0x7F; i++)
         asciiEscapeTable[i] = false;
      for(;i <= 0xFF; i++)
         asciiEscapeTable[i] = true;
      asciiEscapeTable[static_cast<U32>('\"')] = true;
      asciiEscapeTable[static_cast<U32>('_')] = true;
      asciiEscapeTable[static_cast<U32>('\'')] = true;
      asciiEscapeTable[static_cast<U32>('#')] = true;
      asciiEscapeTable[static_cast<U32>('$')] = true;
      asciiEscapeTable[static_cast<U32>('%')] = true;
      asciiEscapeTable[static_cast<U32>('&')] = false;
      asciiEscapeTable[static_cast<U32>('+')] = true;
      asciiEscapeTable[static_cast<U32>('-')] = true;
      asciiEscapeTable[static_cast<U32>('~')] = true;
   }

   U32 destIndex = 0;
   U32 srcIndex = 0;
   while(path[srcIndex] && destIndex < destSize - 3)
   {
      char c = path[srcIndex++];
      if(asciiEscapeTable[static_cast<U32>(c)])
      {
         dest[destIndex++] = '%';
         dest[destIndex++] = getHex((c >> 4) & 0xF);
         dest[destIndex++] = getHex(c & 0xF);
      }
      else
         dest[destIndex++] = c;
   }
   dest[destIndex] = 0;
}

//--------------------------------------
void notcHttpFileDownloader::onConnected()
{
   Parent::onConnected();
   char expPath[8192];
   char buffer[8192];

   if(mQuery)
   {
      dSprintf(buffer, sizeof(buffer), "%s?%s", mPath, mQuery);
      expandPath(expPath, buffer, sizeof(expPath));
   }
   else
      expandPath(expPath, mPath, sizeof(expPath));

   char *pt = dStrchr(mHostName, ':');
   if(pt)
      *pt = 0;
   dSprintf(buffer, sizeof(buffer), "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", expPath, mHostName);
   if(pt)
      *pt = ':';

   send((U8*)buffer, dStrlen(buffer));
   mParseState = ParsingStatusLine;
   mChunkedEncoding = false;
   mContentLength = -1;
}

void notcHttpFileDownloader::onConnectFailed()
{
   dFree(mHostName);
   dFree(mPath);
   dFree(mQuery);
   mHostName = 0;
   mPath = 0;
   mQuery = 0;
   Parent::onConnectFailed();
}


void notcHttpFileDownloader::onDisconnect()
{
   dFree(mHostName);
   dFree(mPath);
   dFree(mQuery);
   mHostName = 0;
   mPath = 0;
   mQuery = 0;
   if(mFileStream)
      SAFE_DELETE(mFileStream);
   Parent::onDisconnect();
}

bool notcHttpFileDownloader::processLine(UTF8 *line)
{
   if(mParseState == ParsingStatusLine)
   {
      mParseState = ParsingHeader;
   }
   else if(mParseState == ParsingHeader)
   {
      if(!dStricmp((char*)line, "transfer-encoding: chunked"))
      {
         mChunkedEncoding = true;
      }
      else if(!dStrnicmp((char*)line, "content-length:", 15))
      {
         mContentLength = dAtoi((char*)line+15);
      }
      else if(line[0] == 0)
      {
         if(mChunkedEncoding)
            mParseState = ParsingChunkHeader;
         else
            mParseState = ProcessingBody;
         return true;
      }
   }
   else if(mParseState == ParsingChunkHeader)
   {
      if(line[0]) // strip off the crlf if necessary
      {
         mChunkSize = 0;
         S32 hexVal;
         while((hexVal = getHexVal(*line++)) != -1)
         {
            mChunkSize *= 16;
            mChunkSize += hexVal;
         }
         if(mBufferSave)
         {
            mBuffer = mBufferSave;
            mBufferSize = mBufferSaveSize;
            mBufferSave = 0;
         }
         if(mChunkSize)
            mParseState = ProcessingBody;
         else
         {
            mParseState = ProcessingDone;
            finishLastLine();
         }
      }
   }

   return true;
}

U32 notcHttpFileDownloader::onDataReceive(U8 *buffer, U32 bufferLen)
{
   if(mFileStream)
   {
      mFileStream->write(bufferLen, buffer);
      if(mContentLength > 0)
      {
         mContentLength -= bufferLen;
         if(mContentLength <= 0)
         {
            SAFE_DELETE(mFileStream);
            onDownloadComplete_callback();
            this->disconnect();
         }
      }
   }
   return bufferLen;
}

//--------------------------------------

U32 notcHttpFileDownloader::onReceive(U8 *buffer, U32 bufferLen)
{
   if(mParseState == ProcessingBody)
   {
      if(mChunkedEncoding && bufferLen >= mChunkSize)
      {
         U32 ret = this->onDataReceive(buffer, mChunkSize);
         mChunkSize -= ret;
         if(mChunkSize == 0)
         {
            if(mBuffer)
            {
               mBufferSaveSize = mBufferSize;
               mBufferSave = mBuffer;
               mBuffer = 0;
               mBufferSize = 0;
            }
            mParseState = ParsingChunkHeader;
         }
         return ret;
      }
      else
      {
         U32 ret = this->onDataReceive(buffer, bufferLen);
         mChunkSize -= ret;
         return ret;
      }
   }
   else if(mParseState != ProcessingDone)
   {
      U32 start = 0;
      parseLine(buffer, &start, bufferLen);
      return start;
   }
   return bufferLen;
}

//--------------------------------------

DefineEngineMethod( notcHttpFileDownloader, download, bool, ( const char* Address, const char* requirstURI, const char* file, const char* query ), ( "" ),
   "@brief Fetch and write remote file to local file.\n\n"

   "@param Address HTTP web address to send this get call to. Be sure to include the port at the end (IE: \"www.garagegames.com:80\").\n"
   "@param requirstURI Specific location on the server to access (IE: \"index.php\".)\n"
   "@param file Local file to write\n"
   "@param query Optional. Actual data to transmit to the server. Can be anything required providing it sticks with limitations of the HTTP protocol. "
   "If you were building the URL manually, this is the text that follows the question mark.  For example: http://www.google.com/ig/api?<b>weather=Las-Vegas,US</b>\n"
   
   "@tsexample\n"
	   "// Create an HTTP object for communications\n"
	   "%httpObj = new notcHttpFileDownloader();\n\n"
	   "// Specify a URL to transmit to\n"
      "%url = \"www.garagegames.com:80\";\n\n"
	   "// Specify a URI to communicate with\n"
	   "%URI = \"/index.php\";\n\n"
	   "// Specify a query to send.\n"
	   "%query = \"\";\n\n"
	   "// Send the GET command to the server\n"
	   "%httpObj.get(%url,%URI,%query);\n"
   "@endtsexample\n\n"
   )
{
   if( !query || !query[ 0 ] )
		return object->download(Address, requirstURI, file, NULL);
   else
		return object->download(Address, requirstURI, file, query);
}
