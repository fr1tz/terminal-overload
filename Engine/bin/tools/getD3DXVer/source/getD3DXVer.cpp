// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// getD3DXVer.exe
//
// Checks for the existance of the correct D3DX library.  Automatically
// uses the D3DX library version this executable was compiled against.
// (As contained in D3dx9core.h)
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include <D3dx9core.h>
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
   // Method documented at http://msdn.microsoft.com/en-us/library/bb172717(VS.85).aspx
   // NOTE: Went with a different check below as this one requires linking with
   // the correct D3DX library to begin with.
   //if ( !D3DXCheckVersion(D3D_SDK_VERSION, D3DX_SDK_VERSION) )
   //{
   //   return 1;
   //}

   // Perform a simple LoadLibrary to check for the correct D3DX
   _TCHAR name[64];
   _stprintf(name, _T("d3dx9_%d.dll"), D3DX_SDK_VERSION);
   HINSTANCE hinstLib = LoadLibrary(name);
   if( !hinstLib )
   {
      //_tprintf(_T("'%s' lib NOT found"), name);
      return 1;
   }

   FreeLibrary(hinstLib);

   //_tprintf(_T("'%s' lib was found"), name);
   return 0;
}

