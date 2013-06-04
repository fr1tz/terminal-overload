// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// The various functions we need to grab from DSound.dll
DS_FUNCTION( DirectSoundEnumerateA, HRESULT, (LPDSENUMCALLBACKA pDSEnumCallback, LPVOID pContext) )
DS_FUNCTION( DirectSoundEnumerateW, HRESULT, (LPDSENUMCALLBACKW pDSEnumCallback, LPVOID pContext) )
DS_FUNCTION( DirectSoundCreate8, HRESULT, (LPCGUID pcGuidDevice, LPDIRECTSOUND8 *ppDS8, LPUNKNOWN pUnkOuter) )

