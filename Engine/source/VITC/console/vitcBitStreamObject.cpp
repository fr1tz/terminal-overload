// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "VITC/console/vitcBitStreamObject.h"

#include "platform/platform.h"
#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "core/base64.h"
#include "math/mMathFn.h"

IMPLEMENT_CONOBJECT(vitcBitStreamObject);

vitcBitStreamObject::vitcBitStreamObject()
{
	mStream = NULL;
	mBuffer = NULL;
	mBufferSize = 0;
}

vitcBitStreamObject::~vitcBitStreamObject()
{
	if(mBuffer)
		dFree(mBuffer);
}

void vitcBitStreamObject::initBuffer(size_t size)
{
	if (mBuffer)
		dFree(mBuffer);
	mBufferSize = size;
	mBuffer = (U8*)dMalloc(mBufferSize);

	if (mStream)
		delete mStream;
	mStream = new BitStream(mBuffer, mBufferSize);
}

void vitcBitStreamObject::initBufferFromBase64(const char* string)
{
	if(mBuffer)
		dFree(mBuffer);
	mBufferSize = dStrlen(string);
	mBuffer = (U8*)dMalloc(mBufferSize);

	size_t streamLength = base64_decode(string, mBuffer);

#if 0
	for (U32 i = 0; i < streamLength; i++)
		Con::printf("%i: %i", i, mBuffer[i]);
#endif

	if(mStream)
		delete mStream;
	mStream = new BitStream(mBuffer, streamLength);
}

//-----------------------------------------------------------------------------
// Misc methods

DefineEngineMethod(vitcBitStreamObject, initBuffer, void, (S32 size), ,
	"TODO")
{
	object->initBuffer(size);
}

DefineEngineMethod(vitcBitStreamObject, initBufferFromBase64, void, (const char* string), ,
	"TODO" )
{
	object->initBufferFromBase64(string);
}

DefineEngineMethod(vitcBitStreamObject, getStreamSize, S32, (), , "TODO\n")
{
	if (!object->getBitStream())
		return -1;
	return object->getBitStream()->getStreamSize();
}

DefineEngineMethod(vitcBitStreamObject, getBase64, const char*, (), , "TODO\n")
{
	if (!object->getBitStream())
		return "";
	BitStream* bitstream = object->getBitStream();
	String base64data = base64_encode(bitstream->getBuffer(), bitstream->getPosition());
	char* ret = Con::getReturnBuffer(base64data);
	return ret;
}

//-----------------------------------------------------------------------------
// Reading methods

DefineEngineMethod(vitcBitStreamObject, read, const char*, (S32 numBytes), , "TODO\n")
{
	if (!object->getBitStream())
		return "";
	char* ret = Con::getReturnBuffer(numBytes + 1);
	object->getBitStream()->_read(numBytes, ret);
	ret[numBytes] = '\0';
	return ret;
}

DefineEngineMethod(vitcBitStreamObject, readFlag, bool, (), , "TODO\n")
{
	if (!object->getBitStream())
		return -1;
	return object->getBitStream()->readFlag();
}

DefineEngineMethod(vitcBitStreamObject, readU8, S32, (), , "TODO\n" )
{
	if(!object->getBitStream())
		return -1;
	U8 ret;
	object->getBitStream()->read(&ret);
	return ret;
}

DefineEngineMethod(vitcBitStreamObject, readU16, S32, (), , "TODO\n" )
{
	if(!object->getBitStream())
		return -1;
	U16 ret;
	object->getBitStream()->read(&ret);
	return ret;
}

DefineEngineMethod(vitcBitStreamObject, readU32, S32, (), , "TODO\n" )
{
	if(!object->getBitStream())
		return -1;
	U32 ret;
	object->getBitStream()->read(&ret);
	return ret;
}

DefineEngineMethod(vitcBitStreamObject, readS8, S32, (), , "TODO\n" )
{
	if(!object->getBitStream())
		return -1;
	S8 ret;
	object->getBitStream()->read(&ret);
	return ret;
}

DefineEngineMethod(vitcBitStreamObject, readS16, S32, (), , "TODO\n" )
{
	if(!object->getBitStream())
		return -1;
	S16 ret;
	object->getBitStream()->read(&ret);
	return ret;
}

DefineEngineMethod(vitcBitStreamObject, readS32, S32, (), , "TODO\n" )
{
	if(!object->getBitStream())
		return -1;
	S32 ret;
	object->getBitStream()->read(&ret);
	return ret;
}

//-----------------------------------------------------------------------------
// Writing methods

DefineEngineMethod(vitcBitStreamObject, write, bool, (const char* string), , "TODO\n")
{
	if(!object->getBitStream())
		return false;
	return object->getBitStream()->_write(dStrlen(string), string);
}

DefineEngineMethod(vitcBitStreamObject, writeFlag, bool, (bool flag), , "TODO\n")
{
	if(!object->getBitStream())
		return false;
	return object->getBitStream()->writeFlag(flag);
}

DefineEngineMethod(vitcBitStreamObject, writeU8, bool, (S32 val), , "TODO\n")
{
	if(!object->getBitStream())
		return false;
	return object->getBitStream()->write((U8)val);
}

DefineEngineMethod(vitcBitStreamObject, writeU16, bool, (S32 val), , "TODO\n")
{
	if(!object->getBitStream())
		return false;
	return object->getBitStream()->write((U16)val);
}

DefineEngineMethod(vitcBitStreamObject, writeU32, bool, (S32 val), , "TODO\n")
{
	if(!object->getBitStream())
		return false;
	return object->getBitStream()->write((U32)val);
}

DefineEngineMethod(vitcBitStreamObject, writeS8, bool, (S32 val), , "TODO\n")
{
	if(!object->getBitStream())
		return false;
	return object->getBitStream()->write((S8)val);
}

DefineEngineMethod(vitcBitStreamObject, writeS16, bool, (S32 val), , "TODO\n")
{
	if(!object->getBitStream())
		return false;
	return object->getBitStream()->write((S16)val);
}

DefineEngineMethod(vitcBitStreamObject, writeS32, bool, (S32 val), , "TODO\n")
{
	if(!object->getBitStream())
		return false;
	return object->getBitStream()->write((S32)val);
}
