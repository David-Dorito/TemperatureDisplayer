#ifndef GFXLIB_H_
#define GFXLIB_H_

#include <stdint.h>

typedef struct {
    const uint16_t Width;
    const uint16_t Height;
    const uint8_t* pBitMap;
} GfxLib_FontChar;

typedef struct {
    uint16_t CharCount;
    GfxLib_FontChar* pFontChars;
} GfxLib_Font;

typedef struct {
    uint16_t FontCount;
    GfxLib_Font* pFonts;
    void* pDisplayHandle;
    void (*DrawPixelFunc)(void* pHandle, uint16_t posX, uint16_t posY, uint32_t color);
} GfxLib_Handle; 

void GfxLib_DrawChar(GfxLib_Handle* pGfxLibHandle, const GfxLib_FontChar* pChar, uint16_t posX, uint16_t posY, uint32_t color);
void GfxLib_DrawText(GfxLib_Handle* pGfxLibHandle);
void GfxLib_DrawLine(GfxLib_Handle* pGfxLibHandle);
void GfxLib_DrawRect(GfxLib_Handle* pGfxLibHandle);
void GfxLib_DrawCirc(GfxLib_Handle* pGfxLibHandle);

#endif