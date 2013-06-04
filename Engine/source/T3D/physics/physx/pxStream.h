// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _T3D_PHYSICS_PXSTREAM_H_
#define _T3D_PHYSICS_PXSTREAM_H_

#ifndef _PHYSX_H_
#include "T3D/physics/physX/px.h"
#endif
#ifndef _MEMSTREAM_H_
#include "core/stream/memStream.h"
#endif


class PxMemStream : public NxStream
{
public:
   
   PxMemStream();
	virtual ~PxMemStream();
			
   void resetPosition();

   // NxStream
	NxU8 readByte() const;
	NxU16	readWord() const;
	NxU32	readDword() const;
	float	readFloat()	const;
	double readDouble() const;
	void readBuffer( void *buffer, NxU32 size ) const;
	NxStream& storeByte( NxU8 b );
	NxStream& storeWord( NxU16 w );
	NxStream& storeDword( NxU32 d );
	NxStream& storeFloat( NxReal f );
	NxStream& storeDouble( NxF64 f );
	NxStream& storeBuffer( const void* buffer, NxU32 size );

protected:

   mutable MemStream mMemStream;
};


class PxConsoleStream : public NxUserOutputStream
{
protected:

   // NxUserOutputStream
   void reportError( NxErrorCode code, const char *message, const char* file, int line );
   NxAssertResponse reportAssertViolation( const char *message, const char *file, int line );
   void print( const char *message );

public:

   PxConsoleStream();
   ~PxConsoleStream();
};

#endif // _T3D_PHYSICS_PXSTREAM_H_