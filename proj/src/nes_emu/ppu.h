#include "lcf_mock.h"
#pragma once
#ifndef PPU_H
#define PPU_H

#include "cartridge.h"

#include <inttypes.h>
#include <stdbool.h>


typedef size_t usize;

typedef struct Color {
    uint8_t red;        // Color red value
    uint8_t green;        // Color green value
    uint8_t blue;        // Color blue value
    uint8_t alpha;        // Color alpha value
} Color;


typedef struct {
    Color *pixels;
    uint16_t width;
    uint16_t height;
} Sprite;

Sprite *SpriteCreate(uint16_t width, uint16_t height);
Color SpriteGetPixel(Sprite *sprite, uint16_t x, uint16_t y);
bool SpriteSetPixel(Sprite *sprite, uint16_t x, uint16_t y, Color color);

typedef union {
    struct {
        uint8_t nametableX : 1;
        uint8_t nametableY : 1;
        uint8_t incrementMode : 1;
        uint8_t patternSprite : 1;
        uint8_t patternBackground : 1;
        uint8_t spriteSize : 1;
        uint8_t slaveMode : 1;   // unused
        uint8_t enableNmi : 1;
    } bits;
    uint8_t reg;
} PpuCtrl;

typedef union {
    struct {
        uint8_t unused : 5;
        uint8_t spriteOverflow : 1;
        uint8_t spriteZeroHit : 1;
        uint8_t verticalBlank : 1;
    } bits;
    uint8_t reg;
} PpuStatus;

typedef union {
    struct {
        uint8_t grayscale : 1;
        uint8_t renderBackgroundLeft : 1;
        uint8_t renderSpritesLeft : 1;
        uint8_t renderBackground : 1;
        uint8_t renderSprites : 1;
        uint8_t enhanceRed : 1;
        uint8_t enhanceGreen : 1;
        uint8_t enhanceBlue : 1;
    } bits;
    uint8_t reg;
} PpuMask;

typedef struct {
    PpuCtrl ctrl;
    PpuStatus status;
    PpuMask mask;
} PpuRegisters;

typedef union {
    struct {
        uint16_t coarseX : 5;
        uint16_t coarseY : 5;
        uint16_t nametableX : 1;
        uint16_t nametableY : 1;
        uint16_t fineY : 3;
        uint16_t unused : 1;
    } bits;
    uint16_t reg;
} LoopyRegister;

typedef struct {
    uint8_t nameTable[2][1024];
    uint8_t paletteTable[32];
    uint8_t patternTable[2][4096];   // This table wont be used in the real emulation. Just keep it here for the moment for the design.
    Color paletteScreen[64];
    Sprite *spriteScreen;
    Sprite *spriteNameTable[2];
    Sprite *spritePatternTable[2];
    int scanline;
    int cycle;
    bool frameCompleted;
    PpuRegisters registers;
    LoopyRegister vramAddr;
    LoopyRegister tramAddr;
    uint8_t addressLatch;
    uint8_t ppuDataBuffer;
    uint8_t fineX;
    uint8_t bgNextTileId;
    uint8_t bgNextTileAttr;
    uint8_t bgNextTileLsb;
    uint8_t bgNextTileMsb;
    uint16_t bgShifterPatternLo;
    uint16_t bgShifterPatternHi;
    uint16_t bgShifterAttribLo;
    uint16_t bgShifterAttribHi;
    bool nmi;
} Ppu2C02;

void ppu_init();

uint8_t cpuBus_readPPU(uint16_t addr);
void cpuBus_writePPU(uint16_t addr, uint8_t data);

uint8_t ppuBus_read(uint16_t addr);
void ppuBus_write(uint16_t addr, uint8_t data);

Ppu2C02 *ppu_get();

void ppu_clock();

Color* ppu_get_screen();

Color get_colorFromPaletteRam(uint8_t palette, uint8_t pixel);
Sprite *get_patternTable(uint8_t i, uint8_t palette);

#endif  // PPU_H