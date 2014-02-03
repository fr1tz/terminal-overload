//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "windowManager/x11/x11Image.h"
#include "core/fileio.h"
#include "console/console.h"
#include "platformX86UNIX/x86UNIXState.h"
#include <X11/Xlibint.h>
#include <X11/Xutil.h>
#include <X11/extensions/xf86vmode.h>

#pragma pack(2)
typedef struct tagBITMAPFILEHEADER 
{
    unsigned short  bfType;
    unsigned int    bfSize;
    unsigned int    bfReserved;
    unsigned int    bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPCOREHEADER 
{
    unsigned int bcSize; 
    unsigned short bcWidth; 
    unsigned short bcHeight; 
    unsigned short bcPlanes; 
    unsigned short bcBitCount; 
} BITMAPCOREHEADER;

typedef struct tagBITMAPINFOHEADER 
{
    unsigned int biSize; 
    long biWidth; 
    long biHeight; 
    unsigned short biPlanes; 
    unsigned short biBitCount;
    unsigned int biCompression; 
    unsigned int biSizeImage;
    long biXPelsPerMeter; 
    long biYPelsPerMeter; 
    unsigned int biClrUsed; 
    unsigned int biClrImportant; 
} BITMAPINFOHEADER; 
#pragma pack()      // Restore packing

X11Image::X11Image()
{
    mImage = 0;
}

X11Image::~X11Image()
{
    cleanup();
}

static U32 colorShiftCount(U32 mask)
{
    switch( mask )
    {
        case 0xFF000000:
            return 24;
        case 0x00FF0000:
            return 16;
        case 0x0000FF00:
            return 8;
        case 0x000000FF:
        default:
            break;
    }
    return 0;
}

bool X11Image::loadFile(const char* fileName)
{
    bool returnVal = false;
    AssertFatal(x86UNIXState->isXWindowsRunning(), "Can not load pixmaps without being connected to the X server");

    char ext[256];
    dStrncpy(ext, dStrrchr(fileName, '.'), sizeof(ext) - 1);
    if( dStricmp(ext, ".bmp") == 0 )
    {
        // Windows bitmap file
        File file;
        if( file.open(fileName, File::Read) == File::Ok )
        {
            U32 fileSize = file.getSize();
            void* fileData = malloc(fileSize);
            if( file.read(fileSize, (char*)fileData) == File::Ok )
            {
                BITMAPFILEHEADER* bmFileHeader = (BITMAPFILEHEADER*)fileData;
                BITMAPCOREHEADER* bmCoreHeader = (BITMAPCOREHEADER*)(bmFileHeader + 1);

                int depth = 0;
                switch( bmCoreHeader->bcSize )
                {
                    case sizeof(BITMAPCOREHEADER):
                        mWidth = bmCoreHeader->bcWidth;
                        mHeight = bmCoreHeader->bcHeight;
                        depth = bmCoreHeader->bcBitCount;
                        break;
                    case sizeof(BITMAPINFOHEADER):
                        {
                            BITMAPINFOHEADER* bmInfoHeader = (BITMAPINFOHEADER*)bmCoreHeader;
                            mWidth = bmInfoHeader->biWidth;
                            mHeight = bmInfoHeader->biHeight;
                            depth = bmInfoHeader->biBitCount;
                        }
                        break;
                    default:
                        mWidth = -1;
                        mHeight = -1;
                        Con::printf("X11Pixmap::loadFile - Unsupported bitmap header with size: %d", bmCoreHeader->bcSize);
                        break;
                }

                // Kill any existing pixmap
                cleanup();

                // Fill in 32 bit color buffer                
                Display* display = x86UNIXState->getDisplayPointer();
                Visual* vis = DefaultVisual(display, DefaultScreen(display));
                U32 rShift = colorShiftCount(vis->red_mask);
                U32 gShift = colorShiftCount(vis->green_mask);
                U32 bShift = colorShiftCount(vis->blue_mask);

                int texelCount = mWidth * mHeight;
                int colorBufferSize = texelCount * 4;
                void* colorBuffer = malloc(colorBufferSize);
                U32* colorPtr = (U32*)colorBuffer;
                U8* bmpDataPtr = ((U8*)fileData) + bmFileHeader->bfOffBits;
                int rowWidth = (depth / 8) * mWidth;
                if( rowWidth & 1 )
                    rowWidth++; // padding at the end of the row
                for( int y = 0; y < mHeight; y++ )
                {
                    U8* currentBMPLine = bmpDataPtr + (((mHeight - 1) - y) * rowWidth);
                    for( int x = 0; x < mWidth; x++ )
                    {
                        switch( depth )
                        {
                            case 24:
                                {
                                    U32 texel = 0;
                                    texel |= (((U32)currentBMPLine[0] << bShift) & vis->blue_mask);
                                    texel |= (((U32)currentBMPLine[1] << gShift) & vis->green_mask);
                                    texel |= (((U32)currentBMPLine[2] << rShift) & vis->red_mask);
                                    *colorPtr = texel;
                                    currentBMPLine += 3;
                                }
                                break;
                            default:
                                AssertFatal(0, "Non supported bitmap bit depth");
                                *colorPtr = 0;
                                break;
                        }
                        colorPtr++;
                    }
                }

                // Create XImage
                XVisualInfo vi;
                XMatchVisualInfo(display, DefaultScreen(display), 24, TrueColor, &vi);                
                mImage = XCreateImage(display, vi.visual, 24, ZPixmap, 0, (char*)colorBuffer, mWidth, mHeight, 32, 0);      // The color buffer is now owned by the XImage, it will be freed with the call to XDestroyImage
                if( mImage )
                {
                    // All good
                    returnVal = true;
                }
                else
                {
                    Con::printf("X11Pixmap::loadFile - Failed to create XImage: %s", fileName);
                    free(colorBuffer);
                }
            }
            else
            {
                Con::printf("X11Pixmap::loadFile - Failed to read data from file: %s", fileName);
            }
            free(fileData);
            file.close();
        }
        else
        {
            Con::printf("X11Pixmap::loadFile - Failed to open file: %s", fileName);
        }
    }
    else
    {
        Con::printf("X11Pixmap::loadFile - Unsupported file extension: %s", ext);
    }

    return returnVal;
}

void X11Image::cleanup()
{
    if( mImage )
    {
        XDestroyImage(mImage);
        mImage = 0;
    }
}