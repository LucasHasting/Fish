#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

const   int     MICRO               = 1000000;
const   int     WIDTH               = 640;                      //MAX: 20, 32x32 tiles
const   int     HEIGHT              = 480;                      //MAX: 15, 32x32 tiles
const   int     TILE_SIZE           = 32;
const   int     TILE_AREA_SIZE      = TILE_SIZE * TILE_SIZE;
const   double  FPS                 = (1/30) * (MICRO);         //30 FPS
const   int     ASCII_SHIFT         = -48;
const   char    TITLE[5]            = "Fish";                   //char array is 1 more to account for null byte

//positions
const   float   FIRST_TILE_CENTER_X = -304.f;
const   float   FIRST_TILE_CENTER_Y = -224.f;
const   float   CENTER_X            = 0.f;
const   float   CENTER_Y            = 0.f;
#endif
