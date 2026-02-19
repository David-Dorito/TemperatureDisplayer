#ifndef GFXLIB_H_
#define GFXLIB_H_

#include <stdint.h>

typedef struct {
    const uint8_t** ppCharBitmaps;
    uint16_t CharCount;
    uint16_t CharWidth;
    uint16_t CharHeight;
    uint8_t CharSpacing;
    char StartChar;
} GfxLib_Font;

typedef struct {
    GfxLib_Font* pFont;
    void* pDisplayHandle;
    void (*DrawPixelFunc)(void* pHandle, uint16_t posX, uint16_t posY, uint32_t color);
} GfxLib_Handle; 

void GfxLib_DrawChar(GfxLib_Handle* pGfxLibHandle, char character, uint16_t posX, uint16_t posY, uint32_t color);
void GfxLib_DrawString(GfxLib_Handle* pGfxLibHandle, char* string, uint16_t posX, uint16_t posY, uint32_t color);
void GfxLib_DrawLine(GfxLib_Handle* pGfxLibHandle);
void GfxLib_DrawRect(GfxLib_Handle* pGfxLibHandle);
void GfxLib_DrawCircle(GfxLib_Handle* pGfxLibHandle);

#endif