#include "GfxLib.h"

typedef int64_t                             i64;
typedef int32_t                             i32;
typedef int16_t                             i16;
typedef int8_t                              i8;
typedef uint64_t                            u64;
typedef uint32_t                            u32;
typedef uint16_t                            u16;
typedef uint8_t                             u8;

void GfxLib_DrawChar(GfxLib_Handle* pGfxLibHandle, char character, uint16_t posX, uint16_t posY, uint32_t color)
{
    u16 row = 0;
    u16 col = 0;
    for (u32 i = 0; i < pGfxLibHandle->pFont->CharHeight*pGfxLibHandle->pFont->CharWidth; i++)
    {
        col = i % pGfxLibHandle->pFont->CharWidth;
        row = i / pGfxLibHandle->pFont->CharWidth;
        u32 pixelIndex = col+row*pGfxLibHandle->pFont->CharWidth;
        u8 bitOffset = 7 - (pixelIndex % 8);
        u8 currentPixelActive = (pGfxLibHandle->pFont->ppCharBitmaps[character - pGfxLibHandle->pFont->StartChar][pixelIndex/8] >> bitOffset) & 1;
        if (currentPixelActive)
            pGfxLibHandle->pTransport->DrawPixelFunc(pGfxLibHandle->pDisplayHandle, posX+col, posY+row, color);
    }
}

void GfxLib_DrawString(GfxLib_Handle* pGfxLibHandle, char* text, uint16_t posX, uint16_t posY, uint32_t color)
{
    for (u16 i = 0; text[i] != '\0'; i++)
        GfxLib_DrawChar(pGfxLibHandle, text[i], posX+i*(pGfxLibHandle->pFont->CharWidth + pGfxLibHandle->pFont->CharSpacing), posY, color);
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