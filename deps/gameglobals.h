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
 |      \"God wanted one man,                                        |     \
  |       Gifted by god himself to be the wisest man alive,           |   \
  |       Who ruled gracefully,                                       |   \
  |       Gifting peace and prosperity to every peasant,              |   \
  |       Who did not even ask,                                       |   \
   |       Giving back his respect to the mighty ruler Solomon,        |  \
   |       Who subsequently built the envy of Judas,                   |  \
   |       Who one day,                                                |  \
   |       Stole the mighty staff,                                     |  \
   |       Wich Solomon once held with pride.\"                         |  \
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

#define screen_height 30
#define screen_width 120

#define GAME_MAP_HEIGHT 64
#define GAME_MAP_WIDTH 128


#define maxChests 6
#define game_totalMaterials 64
#define max_mapTraps 20
#define maxItems_chestContainer 30
#define maxItems_barrelContainer 30
#define maxItems_inventory 20

#define maxMapItems 240

#define maxMapEntities 40
#define total_gameEntites 40

#define total_gameStructures 40
#define max_mapStructures 60

#define operation_failed -1

#define maxItem_enchants 8

#define player_blockChance 3

#define max_mapSpawners 30