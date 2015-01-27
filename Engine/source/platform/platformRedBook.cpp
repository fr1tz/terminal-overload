// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "core/strings/stringFunctions.h"
#include "console/console.h"
#include "console/engineAPI.h"
#include "platform/platformRedBook.h"

//------------------------------------------------------------------------------
// Class: RedBookDevice
//------------------------------------------------------------------------------
RedBookDevice::RedBookDevice()
{
   mAcquired = false;
   mDeviceName = 0;
}

RedBookDevice::~RedBookDevice()
{
   delete [] mDeviceName;
}

//------------------------------------------------------------------------------
// Class: RedBook
//------------------------------------------------------------------------------
Vector<RedBookDevice *>    RedBook::smDeviceList(__FILE__, __LINE__);
RedBookDevice *            RedBook::smCurrentDevice;
char                       RedBook::smLastError[1024];

//------------------------------------------------------------------------------
void RedBook::init()
{
}

void RedBook::destroy()
{
   close();

   for( Vector<RedBookDevice*>::iterator i = smDeviceList.begin( ); i != smDeviceList.end( ); i++ ) {
	   delete *i;
   }

   smDeviceList.clear( );
}

//------------------------------------------------------------------------------
void RedBook::installDevice(RedBookDevice * device)
{
   smDeviceList.push_back(device);
}

RedBookDevice * RedBook::getCurrentDevice()
{
   return(smCurrentDevice);
}

U32 RedBook::getDeviceCount()
{
   return(smDeviceList.size());
}

const char * RedBook::getDeviceName(U32 idx)
{
   if(idx >= getDeviceCount())
   {
      setLastError("Invalid device index");
      return("");
   }
   return(smDeviceList[idx]->mDeviceName);
}

void RedBook::setLastError(const char * error)
{
   if(!error || dStrlen(error) >= sizeof(smLastError))
      setLastError("Invalid error string passed");
   else
      dStrcpy(smLastError, error);
}

const char * RedBook::getLastError()
{
   return(smLastError);
}

void RedBook::handleCallback(U32 type)
{
   switch(type)
   {
      case PlayFinished:
         Con::executef("RedBookCallback", "PlayFinished");
         break;
   }
}

//------------------------------------------------------------------------------
bool RedBook::open(const char * deviceName)
{
   if(!deviceName)
   {
      setLastError("Invalid device name");
      return(false);
   }

   for(U32 i = 0; i < smDeviceList.size(); i++)
      if(!dStricmp(deviceName, smDeviceList[i]->mDeviceName))
         return(open(smDeviceList[i]));

   setLastError("Failed to find device");
   return(false);
}

bool RedBook::open(RedBookDevice * device)
{
   if(!device)
   {
      setLastError("Invalid device passed");
      return(false);
   }

   close();
   smCurrentDevice = device;
   return(smCurrentDevice->open());
}

bool RedBook::close()
{
   if(smCurrentDevice)
   {
      bool ret = smCurrentDevice->close();
      smCurrentDevice = 0;
      return(ret);
   }

   setLastError("No device is currently open");
   return(false);
}

bool RedBook::play(U32 track)
{
   if(!smCurrentDevice)
   {
      setLastError("No device is currently open");
      return(false);
   }
   return(smCurrentDevice->play(track));
}

bool RedBook::stop()
{
   if(!smCurrentDevice)
   {
      setLastError("No device is currently open");
      return(false);
   }
   return(smCurrentDevice->stop());
}

bool RedBook::getTrackCount(U32 * trackCount)
{
   if(!smCurrentDevice)
   {
      setLastError("No device is currently open");
      return(false);
   }
   return(smCurrentDevice->getTrackCount(trackCount));
}

bool RedBook::getVolume(F32 * volume)
{
   if(!smCurrentDevice)
   {
      setLastError("No device is currently open");
      return(false);
   }
   return(smCurrentDevice->getVolume(volume));
}

bool RedBook::setVolume(F32 volume)
{
   if(!smCurrentDevice)
   {
      setLastError("No device is currently open");
      return(false);
   }
   return(smCurrentDevice->setVolume(volume));
}

//------------------------------------------------------------------------------
// console methods
//------------------------------------------------------------------------------

ConsoleFunctionGroupBegin( Redbook, "Control functions for Redbook audio (ie, CD audio).");

DefineConsoleFunction( redbookOpen, bool, (const char * device), (""), "(string device=NULL)"
				"@brief Deprecated\n\n"
				"@internal")
{
   if(dStrcmp(device,"")==0)
      return(RedBook::open(RedBook::getDeviceName(0)));
   else
      return(RedBook::open(device));
}

DefineConsoleFunction( redbookClose, bool, (), , "Close the current Redbook device."
				"@brief Deprecated\n\n"
				"@internal")
{
   return(RedBook::close());
}

DefineConsoleFunction( redbookPlay, bool, (S32 track), , "(int track) Play the selected track."
				"@brief Deprecated\n\n"
				"@internal")
{
   return(RedBook::play(track));
}

DefineConsoleFunction( redbookStop, bool, (), , "Stop playing."
				"@brief Deprecated\n\n"
				"@internal")
{
   return(RedBook::stop());
}

DefineConsoleFunction( redbookGetTrackCount, S32, (), , "Return the number of tracks."
				"@brief Deprecated\n\n"
				"@internal")
{
   U32 trackCount;
   if(!RedBook::getTrackCount(&trackCount))
      return(0);
   return(trackCount);
}

DefineConsoleFunction( redbookGetVolume, F32, (), , "Get the volume."
				"@brief Deprecated\n\n"
				"@internal")
{
   F32 vol;
   if(!RedBook::getVolume(&vol))
      return(0.f);
   else
      return(vol);
}

DefineConsoleFunction( redbookSetVolume, bool, (F32 volume), , "(float volume) Set playback volume."
				"@brief Deprecated\n\n"
				"@internal")
{
   return(RedBook::setVolume(volume));
}

DefineConsoleFunction( redbookGetDeviceCount, S32, (), , "get the number of redbook devices."
				"@brief Deprecated\n\n"
				"@internal")
{
   return(RedBook::getDeviceCount());
}

DefineConsoleFunction( redbookGetDeviceName, const char *, (S32 index), , "(int index) Get name of specified Redbook device."
				"@brief Deprecated\n\n"
				"@internal")
{
   return(RedBook::getDeviceName(index));
}

DefineConsoleFunction( redbookGetLastError, const char *, (), , "Get a string explaining the last redbook error."
				"@brief Deprecated\n\n"
				"@internal")
{
   return(RedBook::getLastError());
}

ConsoleFunctionGroupEnd( Redbook );
