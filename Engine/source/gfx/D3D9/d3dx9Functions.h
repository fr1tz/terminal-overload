// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

D3DX_FUNCTION( D3DXCreateBuffer, HRESULT,
               (DWORD NumBytes,
                         LPD3DXBUFFER * ppBuffer) )

D3DX_FUNCTION( D3DXSaveSurfaceToFileA, HRESULT,
               (LPCSTR                    pDestFile,
               D3DXIMAGE_FILEFORMAT      DestFormat,
               LPDIRECT3DSURFACE9        pSrcSurface,
               CONST PALETTEENTRY*       pSrcPalette,
               CONST RECT*               pSrcRect) )

D3DX_FUNCTION( D3DXSaveSurfaceToFileW, HRESULT,
               (LPCWSTR                   pDestFile,
               D3DXIMAGE_FILEFORMAT      DestFormat,
               LPDIRECT3DSURFACE9        pSrcSurface,
               CONST PALETTEENTRY*       pSrcPalette,
               CONST RECT*               pSrcRect) )

D3DX_FUNCTION( D3DXCompileShader, HRESULT,
               (LPCSTR pSrcData,
               UINT srcDataLen,
               CONST D3DXMACRO* pDefines,
               LPD3DXINCLUDE pInclude,
               LPCSTR pFunctionName,
               LPCSTR pProfile,
               DWORD Flags,
               LPD3DXBUFFER* ppShader,
               LPD3DXBUFFER* ppErrorMsgs,
               LPD3DXCONSTANTTABLE * ppConstantTable) )

D3DX_FUNCTION( D3DXGetShaderConstantTable, HRESULT,
               (CONST DWORD*                    pFunction,
               LPD3DXCONSTANTTABLE*            ppConstantTable) )


D3DX_FUNCTION( D3DXLoadSurfaceFromSurface, HRESULT,
               (LPDIRECT3DSURFACE9        pDestSurface,
               CONST PALETTEENTRY*       pDestPalette,
               CONST RECT*               pDestRect,
               LPDIRECT3DSURFACE9        pSrcSurface,
               CONST PALETTEENTRY*       pSrcPalette,
               CONST RECT*               pSrcRect,
               DWORD                     Filter,
               D3DCOLOR                  ColorKey) )

D3DX_FUNCTION( D3DXCreateVolumeTexture, HRESULT,
               (LPDIRECT3DDEVICE9         pDevice,
               UINT                      Width,
               UINT                      Height,
               UINT                      Depth,
               UINT                      MipLevels,
               DWORD                     Usage,
               D3DFORMAT                 Format,
               D3DPOOL                   Pool,
               LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture) )

D3DX_FUNCTION( D3DXCreateTexture, HRESULT, 
               (LPDIRECT3DDEVICE9         pDevice,
               UINT                      Width,
               UINT                      Height,
               UINT                      MipLevels,
               DWORD                     Usage,
               D3DFORMAT                 Format,
               D3DPOOL                   Pool,
               LPDIRECT3DTEXTURE9*       ppTexture) )

#ifdef TORQUE_OS_XENON
D3DX_FUNCTION( D3DXLoadVolumeFromMemory, HRESULT,
               (LPDIRECT3DVOLUME9         pDestVolume,
               CONST PALETTEENTRY*       pDestPalette,
               CONST D3DBOX*             pDestBox,
               LPCVOID                   pSrcMemory,
               D3DFORMAT                 SrcFormat,
               UINT                      SrcRowPitch,
               UINT                      SrcSlicePitch,
               CONST PALETTEENTRY*       pSrcPalette,
               CONST D3DBOX*             pSrcBox,
               BOOL                      SrcParentPacked,
               UINT                      SrcParentWidth,
               UINT                      SrcParentHeight,
               UINT                      SrcParentDepth,
               DWORD                     Filter,
               D3DCOLOR                  ColorKey) )
#else
D3DX_FUNCTION( D3DXLoadVolumeFromMemory, HRESULT,
               (LPDIRECT3DVOLUME9         pDestVolume,
               CONST PALETTEENTRY*       pDestPalette,
               CONST D3DBOX*             pDestBox,
               LPCVOID                   pSrcMemory,
               D3DFORMAT                 SrcFormat,
               UINT                      SrcRowPitch,
               UINT                      SrcSlicePitch,
               CONST PALETTEENTRY*       pSrcPalette,
               CONST D3DBOX*             pSrcBox,
               DWORD                     Filter,
               D3DCOLOR                  ColorKey) )
#endif

D3DX_FUNCTION( D3DXSaveTextureToFileInMemory, HRESULT,
               (LPD3DXBUFFER *ppDestBuf,
               D3DXIMAGE_FILEFORMAT DestFormat,
               LPDIRECT3DBASETEXTURE9 pSrcTexture,
               const PALETTEENTRY *pSrcPalette) )

D3DX_FUNCTION( D3DXGetImageInfoFromFileInMemory, HRESULT,
               (LPCVOID                   pSrcData,
               UINT                      SrcDataSize,
               D3DXIMAGE_INFO*           pSrcInfo) )

D3DX_FUNCTION( D3DXLoadSurfaceFromFileInMemory, HRESULT,
               (LPDIRECT3DSURFACE9 pDestSurface,
               CONST PALETTEENTRY * pDestPalette,
               CONST RECT * pDestRect,
               LPCVOID pSrcData,
               UINT SrcData,
               CONST RECT * pSrcRect,
               DWORD Filter,
               D3DCOLOR ColorKey,
               D3DXIMAGE_INFO * pSrcInfo) )

D3DX_FUNCTION( D3DXSaveSurfaceToFileInMemory, HRESULT,
               (LPD3DXBUFFER*             ppDestBuf,
               D3DXIMAGE_FILEFORMAT      DestFormat,
               LPDIRECT3DSURFACE9        pSrcSurface,
               CONST PALETTEENTRY*       pSrcPalette,
               CONST RECT*               pSrcRect) )
