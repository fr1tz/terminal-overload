// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXTYPES_H_
#define _SFXTYPES_H_

#ifndef _CONSOLETYPES_H_
   #include "console/consoleTypes.h"
#endif


/// @file
/// Additional SFX console types.


class BitStream;
class SFXTrack;
class SFXEnvironment;
class SFXDescription;
class SFXState;
class SFXAmbience;
class SFXSource;


///
DefineConsoleType( TypeSFXSourceName, SFXSource* );

/// Name of an SFXParameter.  Resolved to SFXParamter instances on the
/// client when creating a source.
///
/// This is a separate type so that the inspector can provide meaningful
/// popups.
DefineConsoleType( TypeSFXParameterName, StringTableEntry );

/// SFXDescription datablock reference.  May be client-only.
DefineConsoleType( TypeSFXDescriptionName, SFXDescription* );

/// SFXTrack datablock reference.  May be client-only.
DefineConsoleType( TypeSFXTrackName, SFXTrack* );

/// SFXEnvironment datablock reference.  May be client-only.
DefineConsoleType( TypeSFXEnvironmentName, SFXEnvironment* );

/// SFXState datablock reference.  May be client-only.
DefineConsoleType( TypeSFXStateName, SFXState* );

/// SFXAmbience datablock reference.  May be client-only.
DefineConsoleType( TypeSFXAmbienceName, SFXAmbience* );


/// @name Datablock Network I/O
///
/// The following functions allow to transmit datablock references over the network
/// even when the referenced datablocks are not networked ("client-only" datablocks).
///
/// The write functions write a reference to the bitstream.
///
/// The read functions read a reference from the bitstream and store it in a non-resolved
/// form, i.e. the resulting pointer will not yet be valid.  This is necessary as during
/// datablock transmission, the referenced datablock may actually only be transmitted
/// later in the stream and cannot thus be immediately looked up on the client.
///
/// The resolve functions take an unresolved datablock reference and resolve them to
/// valid pointers.
///
/// @{

void sfxWrite( BitStream* stream, SFXSource* source );
void sfxWrite( BitStream* stream, SFXDescription* description );
void sfxWrite( BitStream* stream, SFXTrack* track );
void sfxWrite( BitStream* stream, SFXEnvironment* environment );
void sfxWrite( BitStream* stream, SFXState* state );
void sfxWrite( BitStream* stream, SFXAmbience* ambience );

void sfxRead( BitStream* stream, SFXDescription** description );
void sfxRead( BitStream* stream, SFXTrack** track );
void sfxRead( BitStream* stream, SFXEnvironment** environment );
void sfxRead( BitStream* stream, SFXState** state );
void sfxRead( BitStream* stream, SFXAmbience** ambience );

bool sfxResolve( SFXDescription** description, String& errorString );
bool sfxResolve( SFXTrack** track, String& errorString );
bool sfxResolve( SFXEnvironment** environment, String& errorString );
bool sfxResolve( SFXState** state, String& errorString );
bool sfxResolve( SFXAmbience** ambience, String& errorString );

bool sfxReadAndResolve( BitStream* stream, SFXSource** source, String& errorString );

inline bool sfxReadAndResolve( BitStream* stream, SFXDescription** description, String& errorString )
{
   sfxRead( stream, description );
   return sfxResolve( description, errorString );
}

inline bool sfxReadAndResolve( BitStream* stream, SFXTrack** track, String& errorString )
{
   sfxRead( stream, track );
   return sfxResolve( track, errorString );
}

inline bool sfxReadAndResolve( BitStream* stream, SFXEnvironment** environment, String& errorString )
{
   sfxRead( stream, environment );
   return sfxResolve( environment, errorString );
}

inline bool sfxReadAndResolve( BitStream* stream, SFXState** state, String& errorString )
{
   sfxRead( stream, state );
   return sfxResolve( state, errorString );
}

inline bool sfxReadAndResolve( BitStream* stream, SFXAmbience** ambience, String& errorString )
{
   sfxRead( stream, ambience );
   return sfxResolve( ambience, errorString );
}

/// @}

#endif // !_SFXTYPES_H_
