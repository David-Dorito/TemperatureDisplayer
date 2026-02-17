#include "GfxLib.h"

typedef int64_t                             i64;
typedef int32_t                             i32;
typedef int16_t                             i16;
typedef int8_t                              i8;
typedef uint64_t                            u64;
typedef uint32_t                            u32;
typedef uint16_t                            u16;
typedef uint8_t                             u8;

void GfxLib_DrawChar(GfxLib_Handle* pGfxLibHandle, GfxLib_FontChar* pChar, uint16_t posX, uint16_t posY, uint32_t color)
{
    u16 row = 0;
    u16 col = 0;
    for (u32 i = 0; i < pChar->Height*pChar->Width; i++)
    {
        col = i % pChar->Width;
        row = i / pChar->Width;
        u32 pixelIndex = col+row*pChar->Width;
        u8 bitOffset = 7 - (pixelIndex % 8);
        u8 currentPixelActive = (pChar->pBitMap[pixelIndex/8] >> bitOffset) & 1;
        if (currentPixelActive)
            pGfxLibHandle->DrawPixelFunc(pGfxLibHandle->displayHandle, posX+col, posY+row, color);
    }
}

void GfxLib_DrawText(GfxLib_Handle* pGfxLibHandle)
{

}

void GfxLib_DrawLine(GfxLib_Handle* pGfxLibHandle)
{

}

void GfxLib_DrawRect(GfxLib_Handle* pGfxLibHandle)
{

}

void GfxLib_DrawCirc(GfxLib_Handle* pGfxLibHandle)
{

}