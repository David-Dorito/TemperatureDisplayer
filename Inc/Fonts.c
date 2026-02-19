#include "Fonts.h"

static const uint8_t basicFont_bitmap_spaceSymbol[] = {0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t basicFont_bitmap_exclamationSymbol[] = {0x30, 0xC3, 0x0C, 0x00, 0xC0};
static const uint8_t basicFont_bitmap_quotationSymbol[] = {0x51, 0x40, 0x00, 0x00, 0x00};
static const uint8_t basicFont_bitmap_hashtagSymbol[] = {0x4B, 0xF4, 0x92, 0xFD, 0x20};
static const uint8_t basicFont_bitmap_dollarSymbol[] = {0x21, 0xFA, 0x1E, 0x27, 0xE0};
static const uint8_t basicFont_bitmap_percentSymbol[] = {0xC7, 0x21, 0x08, 0x4E, 0x30};
static const uint8_t basicFont_bitmap_andSymbol[] = {0x72, 0x27, 0x12, 0x89, 0xD0};
static const uint8_t basicFont_bitmap_apostropheSymbol[] = {0x63, 0x00, 0x00, 0x00, 0x00};
static const uint8_t basicFont_bitmap_leftParenthesesSymbol[] = {0x60, 0x40, 0x82, 0x11, 0x80};
static const uint8_t basicFont_bitmap_rightParenthesesSymbol[] = {0x18, 0x84, 0x10, 0x20, 0x60};
static const uint8_t basicFont_bitmap_asteriskSymbol[] = {0x50, 0x85, 0x00, 0x00, 0x00};
static const uint8_t basicFont_bitmap_plusSymbol[] = {0x00, 0x02, 0x1C, 0x20, 0x00};
static const uint8_t basicFont_bitmap_commaSymbol[] = {0x00, 0x00, 0x00, 0x63, 0x00};
static const uint8_t basicFont_bitmap_minusSymbol[] = {0x00, 0x00, 0x1E, 0x00, 0x00};
static const uint8_t basicFont_bitmap_dotSymbol[] = {0x00, 0x00, 0x00, 0x61, 0x80};
static const uint8_t basicFont_bitmap_slashSymbol[] = {0x04, 0x21, 0x08, 0x42, 0x00};
static const uint8_t basicFont_bitmap_0[] = {0x7A, 0x39, 0x69, 0xC5, 0xE0};
static const uint8_t basicFont_bitmap_1[] = {0x31, 0xC1, 0x04, 0x13, 0xF0};
static const uint8_t basicFont_bitmap_2[] = {0x7A, 0x10, 0x8C, 0x43, 0xF0};
static const uint8_t basicFont_bitmap_3[] = {0x7A, 0x10, 0x5E, 0x07, 0xE0};
static const uint8_t basicFont_bitmap_4[] = {0x8A, 0x28, 0xBF, 0x08, 0x20};
static const uint8_t basicFont_bitmap_5[] = {0xFE, 0x0F, 0x81, 0x85, 0xE0};
static const uint8_t basicFont_bitmap_6[] = {0x7E, 0x0B, 0xA1, 0x85, 0xE0};
static const uint8_t basicFont_bitmap_7[] = {0xFC, 0x21, 0x08, 0x41, 0x00};
static const uint8_t basicFont_bitmap_8[] = {0x7A, 0x18, 0x5E, 0x85, 0xE0};
static const uint8_t basicFont_bitmap_9[] = {0x7A, 0x18, 0x5F, 0x05, 0xE0};
static const uint8_t basicFont_bitmap_colonSymbol[] = {0x01, 0x86, 0x00, 0x61, 0x80};
static const uint8_t basicFont_bitmap_semicolonSymbol[] = {0x01, 0x86, 0x00, 0x63, 0x00};
static const uint8_t basicFont_bitmap_smallerSymbol[] = {0x01, 0xFC, 0x30, 0x7C, 0x00};
static const uint8_t basicFont_bitmap_equalsSymbol[] = {0x03, 0xF0, 0x3F, 0x00, 0x00};
static const uint8_t basicFont_bitmap_biggerSymbol[] = {0x03, 0xE0, 0xC3, 0xF8, 0x00};
static const uint8_t basicFont_bitmap_questionMark[] = {0x7A, 0x10, 0x84, 0x00, 0x40};
static const uint8_t basicFont_bitmap_atSymbol[] = {0x7A, 0x1B, 0xEC, 0x85, 0xE0};
static const uint8_t basicFont_bitmap_A[] = {0x7A, 0x18, 0x7F, 0x86, 0x10};
static const uint8_t basicFont_bitmap_B[] = {0xFA, 0x1F, 0xA1, 0x87, 0xE0};
static const uint8_t basicFont_bitmap_C[] = {0x7A, 0x18, 0x20, 0x85, 0xE0};
static const uint8_t basicFont_bitmap_D[] = {0xF2, 0x28, 0x61, 0x8B, 0xC0};
static const uint8_t basicFont_bitmap_E[] = {0xFE, 0x0F, 0x20, 0x83, 0xF0};
static const uint8_t basicFont_bitmap_F[] = {0xFE, 0x0F, 0x20, 0x82, 0x00};
static const uint8_t basicFont_bitmap_G[] = {0x7A, 0x18, 0x27, 0x85, 0xE0};
static const uint8_t basicFont_bitmap_H[] = {0x86, 0x1F, 0xE1, 0x86, 0x10};
static const uint8_t basicFont_bitmap_I[] = {0xFC, 0xC3, 0x0C, 0x33, 0xF0};
static const uint8_t basicFont_bitmap_J[] = {0x1C, 0x20, 0x82, 0x89, 0xC0};
static const uint8_t basicFont_bitmap_K[] = {0x8E, 0x6E, 0x26, 0x8E, 0x10};
static const uint8_t basicFont_bitmap_L[] = {0x82, 0x08, 0x20, 0x83, 0xF0};
static const uint8_t basicFont_bitmap_M[] = {0x87, 0x3B, 0x61, 0x86, 0x10};
static const uint8_t basicFont_bitmap_N[] = {0x87, 0x1A, 0x65, 0x8E, 0x10};
static const uint8_t basicFont_bitmap_O[] = {0x7A, 0x18, 0x61, 0x85, 0xE0};
static const uint8_t basicFont_bitmap_P[] = {0xFA, 0x18, 0x7E, 0x82, 0x00};
static const uint8_t basicFont_bitmap_Q[] = {0x7A, 0x18, 0x61, 0x89, 0xD0};
static const uint8_t basicFont_bitmap_R[] = {0xFA, 0x18, 0x7E, 0x8E, 0x10};
static const uint8_t basicFont_bitmap_S[] = {0x7A, 0x18, 0x1E, 0x07, 0xE0};
static const uint8_t basicFont_bitmap_T[] = {0xFC, 0x82, 0x08, 0x20, 0x80};
static const uint8_t basicFont_bitmap_U[] = {0x86, 0x18, 0x61, 0x85, 0xE0};
static const uint8_t basicFont_bitmap_V[] = {0x86, 0x18, 0x52, 0x48, 0xC0};
static const uint8_t basicFont_bitmap_W[] = {0x86, 0x18, 0x6D, 0xCE, 0x10};
static const uint8_t basicFont_bitmap_X[] = {0x85, 0x23, 0x0C, 0x4A, 0x10};
static const uint8_t basicFont_bitmap_Y[] = {0x86, 0x14, 0x8C, 0x30, 0xC0};
static const uint8_t basicFont_bitmap_Z[] = {0xFC, 0x63, 0x18, 0xC3, 0xF0};

static const uint8_t* basicFontBitMaps[] = {
    basicFont_bitmap_spaceSymbol,
    basicFont_bitmap_exclamationSymbol,
    basicFont_bitmap_quotationSymbol,
    basicFont_bitmap_hashtagSymbol,
    basicFont_bitmap_dollarSymbol,
    basicFont_bitmap_percentSymbol,
    basicFont_bitmap_andSymbol,
    basicFont_bitmap_apostropheSymbol,
    basicFont_bitmap_leftParenthesesSymbol,
    basicFont_bitmap_rightParenthesesSymbol,
    basicFont_bitmap_asteriskSymbol,
    basicFont_bitmap_plusSymbol,
    basicFont_bitmap_commaSymbol,
    basicFont_bitmap_minusSymbol,
    basicFont_bitmap_dotSymbol,
    basicFont_bitmap_slashSymbol,
    basicFont_bitmap_0,
    basicFont_bitmap_1,
    basicFont_bitmap_2,
    basicFont_bitmap_3,
    basicFont_bitmap_4,
    basicFont_bitmap_5,
    basicFont_bitmap_6,
    basicFont_bitmap_7,
    basicFont_bitmap_8,
    basicFont_bitmap_9,
    basicFont_bitmap_colonSymbol,
    basicFont_bitmap_semicolonSymbol,
    basicFont_bitmap_smallerSymbol,
    basicFont_bitmap_equalsSymbol,
    basicFont_bitmap_biggerSymbol,
    basicFont_bitmap_questionMark,
    basicFont_bitmap_atSymbol,
    basicFont_bitmap_A,
    basicFont_bitmap_B,
    basicFont_bitmap_C,
    basicFont_bitmap_D,
    basicFont_bitmap_E,
    basicFont_bitmap_F,
    basicFont_bitmap_G,
    basicFont_bitmap_H,
    basicFont_bitmap_I,
    basicFont_bitmap_J,
    basicFont_bitmap_K,
    basicFont_bitmap_L,
    basicFont_bitmap_M,
    basicFont_bitmap_N,
    basicFont_bitmap_O,
    basicFont_bitmap_P,
    basicFont_bitmap_Q,
    basicFont_bitmap_R,
    basicFont_bitmap_S,
    basicFont_bitmap_T,
    basicFont_bitmap_U,
    basicFont_bitmap_V,
    basicFont_bitmap_W,
    basicFont_bitmap_X,
    basicFont_bitmap_Y,
    basicFont_bitmap_Z
};

GfxLib_Font basicFont = (GfxLib_Font){
    .ppCharBitmaps = basicFontBitMaps,
    .CharCount = sizeof(basicFontBitMaps) / sizeof(basicFontBitMaps[0]),
    .CharHeight = 6,
    .CharWidth = 6,
    .CharSpacing = 1,
    .StartChar = ' '
};