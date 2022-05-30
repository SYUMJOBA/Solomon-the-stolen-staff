#pragma once
//This dependency includes the global variables for the program to work
//and that the software will keep referencing, like the screen_width and height

const char* GAME_LORE_PERGAMENE = "\
                                             _______________________      \
   _______________________-------------------                       `\\    \
 /:--__                                                              |    \
||< > |                                   ___________________________/    \
| \\__/_________________-------------------                         |      \
|                                                                  |      \
 |                         The Stolen Staff                        |      \
 |                                                                  |     \
 |      \"In the bountiful land of Caanan                            |     \
  |       once ruled a bright old man                                |    \
  |       Solomon his name, and great his fame,                      |    \
  |       no other king was ever the same.                           |    \
  |       To lead his people on the right path,                      |    \
   |       god granted him a wondrous staff.                          |   \
   |       It brought him riches untold                               |   \
   |       and dazzling mountains of gold                             |   \
   |       Until Judas, the traitor, out of spite                     |   \
   |       stole it to challenge the lord's might.\"                   |  \
  |                                              _____________________|   \
  |  ___________________-------------------------                      `\\ \
  |/`--_                                                                 |\
  ||[ ]||                                            ____________________/\
   \\===/___________________--------------------------                     ";

typedef struct Vec2{
    int X;
    int Y;
} Vec2, *PVec2;

typedef struct Vec2f {
    long double X;
    long double Y;
} Vec2f, *PVec2f;

int GAME_CURRENT_LEVEL = 0;
int GAME_HIGHEST_LEVEL = 0;

#define screen_height 30
#define screen_width 120

#define GAME_MAP_HEIGHT 64
#define GAME_MAP_WIDTH 128


#define max_mapChests 6
#define game_totalMaterials 64
#define max_mapTraps 20
#define maxItems_chestContainer 30
#define maxItems_barrelContainer 30
#define maxItems_inventory 20

#define max_mapItems 240

#define max_mapEntities 40
#define total_gameEntites 40

#define total_gameStructures 40
#define max_mapStructures 60

#define operation_failed -1

#define maxItem_enchants 8

#define player_blockChance 3

#define max_mapSpawners 30