//This dependency includes a the global vars and funcs about the map, as well as structs that specify the world tiles (furniture included)
//with many functions to manage operations within the map (like cheking neightboring tiles given a position)
//as well as a lot of comments for documentation
#pragma once

//For gorund layer
#define groundTiletype_roughFloor 0
#define groundTiletype_smoothGround 1
#define groundTiletype_upSlope 2
#define groundTiletype_downSlope 3
#define groundTileType_liquid 4

//For wall layer
#define wallTiletype_noWall -1
#define wallTiletype_roughWall 0
#define wallTiletype_smoothWall 1
#define wallTiletype_engravedWall 2
#define wallTiletype_bookshelf 3
#define wallTiletype_statue 4
#define wallTiletype_chair 5
#define wallTiletype_table 6
#define wallTiletype_bed 7
#define wallTiletype_door 8
#define wallTiletype_chest 9
#define wallTiletype_barrel 10
#define wallTiletype_downStairs 11
#define wallTiletype_upStairs 12
#define wallTiletype_udStairs 13

//for doors
#define doorState_open 0
#define doorState_closed 1

//for generation
#define onGround 0
#define onWalls 1

char USABLE_ROUGH_GROUND_CHARS[10] = { '.', ',', '`', '\'', '\'', '.', ',', '.', char_middleDot, char_middleDot };
char USABLE_LIQUID_GROUND_CHARS[2] = { tileSprite_liquidDouble, tileSprite_liquidSingle };

typedef struct WorldTile {
    int materialID;
    int type; //If it's -1, there is no tile over there
    int containedID; //If the tile contians some of it (for example, a rough wall containing some metal is automatically an ORE, but a ground tile will point the itemList)
    //If containedID is -1 : there is no material contained
    unsigned int state; //useful variable in many situtations: doors can be opened or closed, rocks can be mined ... and so on
} WorldTile, * PWorldTile;

WorldTile createTile(int mat, int type, int cont, int state)
{
    WorldTile tmpTile;
    tmpTile.materialID = mat;
    tmpTile.type = type;
    tmpTile.containedID = cont;
    tmpTile.state = state;
    return tmpTile;
}

typedef struct Trap {
    BOOL discovered;
    Enchantment effect;
    Vec2 position;
} Trap, * PTrap;

Trap MAP_TRAPS[max_mapTraps];
WorldTile GAME_GROUND[GAME_MAP_HEIGHT * GAME_MAP_WIDTH];
WorldTile GAME_WALLS[GAME_MAP_HEIGHT * GAME_MAP_WIDTH];

#define getMapWall(x, y) GAME_WALLS[(y)*GAME_MAP_WIDTH+(x)]
#define getMapGround(x, y) GAME_GROUND[(y)*GAME_MAP_WIDTH+(x)]

Trap* getTrapFromPosition(Vec2 position)
{
    int i = 0;
    while (i < max_mapTraps && !vec2cmp(MAP_TRAPS[i].position, position))
    {
        i++;
    }
    return i < max_mapTraps ? &MAP_TRAPS[i] : NULL;
}

void clearTraps() {
    for (int i = 0; i < max_mapTraps; i++)
    {
        MAP_TRAPS[i] = { FALSE, {0, 0, 0}, {0, 0} };
    }
}

#define doorSideTop 0
#define doorSideBottom 1
#define doorSideLeft 2
#define doorSideRight 3


//generate a room with a center and a size var, procedural generation is slated for future update
void createMapRectangle(Vec2 center, Vec2 size, int level, WorldTile wt)
{
    Vec2 start = { center.X - size.X / 2, center.Y - size.Y / 2 };
    Vec2 end = { center.X + size.X / 2, center.Y + size.Y / 2 };

    if (level == onGround)
    {
        for (int y = 0; y < size.Y; y++)
        {
            for (int x = 0; x < size.X; x++)
            {
                getMapGround(x + start.X, y + start.Y) = wt;
            }
        }
    }
    else {
        for (int y = 0; y < size.Y; y++)
        {
            for (int x = 0; x < size.X; x++)
            {
                getMapWall(x + start.X, y + start.Y) = wt;
            }
        }
    }
}
void createHollowMapRectangle(Vec2 center, Vec2 size, int level, WorldTile wt)
{
    Vec2 start = { center.X - size.X / 2, center.Y - size.Y / 2 };
    Vec2 end = { center.X + size.X / 2, center.Y + size.Y / 2 };
    if (level == onGround)
    {
        for (int y = 0; y < size.Y; y++)
        {
            getMapGround(start.X, start.Y + y) = wt;
            getMapGround(end.X, start.Y + y) = wt;
        }
        for (int x = 0; x < size.X; x++)
        {
            getMapGround(start.X + x, start.Y) = wt;
            getMapGround(start.X + x, end.Y) = wt;
        }
    }
    else {
        for (int y = 0; y < size.Y; y++)
        {
            getMapWall(start.X, start.Y + y) = wt;
            getMapWall(end.X, start.Y + y) = wt;
        }
        for (int x = 0; x < size.X; x++)
        {
            getMapWall(start.X + x, start.Y) = wt;
            getMapWall(start.X + x, end.Y) = wt;
        }
    }

}
void createRoom(Vec2 center, Vec2 size, int doorSide, int wallType, int material, int groundType, int groundMaterial)
{
    Vec2 start = { center.X - size.X / 2, center.Y - size.Y / 2 };
    Vec2 end = { center.X + size.X / 2, center.Y + size.Y / 2 };
    createHollowMapRectangle(center, size, onWalls, createTile(material, wallType, material_noMaterial, 0));
    createMapRectangle( center, size, onGround, createTile( groundMaterial, groundType, itemType_noItem, 0));
    WorldTile door = createTile(isMaterialRockLike(GAME_MATERIALS[material]) ? material_dolomite : material_cherryWood, wallTiletype_door, itemType_noItem, doorState_closed);
    switch (doorSide)
    {
    case doorSideBottom:
        getMapWall(end.X, center.Y) = door;
        break;

    case doorSideTop:
        getMapWall(center.X, start.Y) = door;
        break;

    case doorSideLeft:
        getMapWall(start.X, center.Y) = door;
        break;

    case doorSideRight:
        getMapWall(end.X, center.Y) = door;
    default:
        break;
    }
}


void clearMap() {
    for (int i = 0; i < GAME_MAP_HEIGHT * GAME_MAP_WIDTH; i++)
    {
        GAME_GROUND[i] = { material_dolomite, groundTiletype_smoothGround, itemType_noItem };
        GAME_WALLS[i] = { material_dolomite, wallTiletype_noWall, -1 };
    }
    for (int i = 0; i < max_mapItems; i++)
    {
        MAP_ITEMS[i] = createItem(itemType_noItem, 0, 0);
    }
    for (int x = 0; x < GAME_MAP_WIDTH; x++)
    {
        GAME_WALLS[x] = createTile(material_dolomite, wallTiletype_smoothWall, itemType_noItem, 0);
        getMapWall(x, GAME_MAP_HEIGHT - 1) = createTile(material_dolomite, wallTiletype_smoothWall, itemType_noItem, 0);
    }
    for (int y = 0; y < GAME_MAP_HEIGHT; y++)
    {
        getMapWall(0, y) = createTile(material_dolomite, wallTiletype_smoothWall, material_noMaterial, 0);
        getMapWall(GAME_MAP_WIDTH, y) = createTile(material_dolomite, wallTiletype_smoothWall, material_noMaterial, 0);
    }
    for (int x = 0; x < GAME_MAP_WIDTH; x++)
    {
        for (int y = 0; y < GAME_MAP_HEIGHT; y++)
        {
            getMapGround(x, y) = createTile(material_dolomite, groundTiletype_smoothGround, -1, 0);
        }
    }
}
/*
how the gorund should display:
███████████████████████████ -.
█',.`,',█++++++++█≈~≈~≈≈~~█  |
█,.`X'.`╪+++++X++█≈≈~~≈~≈≈█  | these are walls instead, part of the WALLS
█',.`,',█++++++++█~~≈~≈~≈~█  |
███████████████████████████ -'
    ^       ^        ^
    |       |        |
  rough   smooth   water

type of ground is defined in: ` <WorldTile>.type `

where (if the material is solid):
 {
     0 : 'rough'
     1 : 'smooth'
     2 : 'upSlope'
     3 : 'downSlope'
     4 : 'liquid'
 }

but if the material is liquid, regardless of `type` the charecter represented will be ~ or ≈

so:
  ground tiles occupied by ground have:
   black background
   charecter depending on Type
   color depending on the original specified background
   if ContainedID is different from -1, it acts as a pointer to GAME_ITEMS, as it means there is *item* on the ground


 the map.h, there's a cool array called rough_ground_symbols[] and it stores all the symbols that a rough ground could have. Each Tile has a random one


how the walls should display:
██████████░████████████████
░▒▓
walls are a little trickier:

 Type accounts for:
 {
     -1: no wall there
     0 : rough wall
     1 : smooth wall
     2 : engraved wall
     3 : bookshelf
     4 : statue
     5 : chair
     6 : table
     7 : bed
     8 : door
     9 : chest
     10 : barrel
 }
 in the case of a rough wall :
  the tile's color is the default background and foreground
  the tile's symbol is the default symbol
  but if there's a contained material:
    the tile's foreground is the default contained foreground
    the tile's symbol is the default contained symbol

 in case of a smooth wall:
  the tile's background is black
  the tile's foreground is the default backgorund
  the tile's symbol is the UI window delimiter charecter, it changes depending on neughbouring cells
   if the tile has only one or zero connections:
    the tile will be a pillar : 'O'
   if the tile has more connections:
    the tile UI component will be the one with those connections

        here's the tileset:  ╔╦╗ O
                             ╠╬╣ ═
                             ╚╩╝ ║

 in case of an engraved wall:
  the internal symbol is 'Θ'
  the Fg color is black
  the Bg color is default

  in any other case:
   color is default color
   symbol is default symbol

  if type is > than 2 : it's probably a piece of furniture
   if chair :
     symbol : ╥
     color : default background to foreground
   if table :
     symbol : ╤
     color : default background to foreground
   if bed :
     symbol : Θ
     color : default background to foreground
   if bookshelf :
     symbol : ≡
     color : default with black foreground
   if chest :
     symbol : Æ
     color : default background to foreground
   if door :
     symbol : |
     color : default with black foreground



the roubgh walls use background to display themselves

*/



//Huge amount of util functions here

void placeInMap(Vec2 worldPosition, WorldTile tile, BOOL level) {
    if (onWalls)
    {
        GAME_WALLS[worldPosition.Y * GAME_MAP_WIDTH + worldPosition.X].type = tile.type;
        GAME_WALLS[worldPosition.Y * GAME_MAP_WIDTH + worldPosition.X].materialID = tile.materialID;
        GAME_WALLS[worldPosition.Y * GAME_MAP_WIDTH + worldPosition.X].containedID = tile.containedID;
    }

}
BOOL collidesWithMap(Vec2 position)
{ //returns true if the specified position happens to be occupied by an impenetrable tile. 
//for a tile to be impenetrable needs to be of a type from a rough wall to a bookShelf
    if (GAME_WALLS[position.Y * GAME_MAP_WIDTH + position.X].type >= wallTiletype_roughWall && GAME_WALLS[position.Y * GAME_MAP_WIDTH + position.X].type <= wallTiletype_bookshelf) {
        return TRUE;
    }
    else {
        if (getMapWall(position.X, position.Y).type == wallTiletype_door)
        {
            return getMapWall(position.X, position.Y).state;
        }
    }
    return FALSE;
}
void map_clear() {
    for (int y = 0; y < GAME_MAP_HEIGHT; y++)
    {
        for (int x = 0; x < GAME_MAP_WIDTH; x++)
        {
            GAME_GROUND[GAME_MAP_WIDTH * y + x].containedID = -1;
            GAME_GROUND[GAME_MAP_WIDTH * y + x].type = 0;
            GAME_GROUND[GAME_MAP_WIDTH * y + x].materialID = 0; //should be rough stone

            GAME_WALLS[GAME_MAP_WIDTH * y + x].containedID = -1;
            GAME_WALLS[GAME_MAP_WIDTH * y + x].materialID = 0;
            GAME_WALLS[GAME_MAP_WIDTH * y + x].type = -1;
        }
    }

    for (int x = 0; x < GAME_MAP_WIDTH; x++)
    {
        GAME_WALLS[x].type = 1; //smooth wall
        getMapWall(x, GAME_MAP_HEIGHT - 1).type = 1;
    }
    for (int y = 0; y < GAME_MAP_HEIGHT; y++)
    {
        GAME_WALLS[y * GAME_MAP_WIDTH].type = 1;
        GAME_WALLS[y * GAME_MAP_WIDTH + GAME_MAP_WIDTH - 1].type = 1;
    }
}
int placeNewChest(Vec2 position, int material)
{
    if (!collidesWithMap(position))
    {
        int location = addNewChest();
        if (location != operation_failed)
        {
            GAME_WALLS[GAME_MAP_WIDTH * position.Y + position.X].type = wallTiletype_chest;
            GAME_WALLS[GAME_MAP_WIDTH * position.Y + position.X].containedID = location;
            GAME_WALLS[GAME_MAP_WIDTH * position.Y + position.X].materialID = material;
        }
    }
    return operation_failed;
}
const char* getGroundTypeFromEnum(int cellType) {
    switch (cellType)
    {
    case groundTileType_liquid:
        return "liquid";
        break;

    case groundTiletype_roughFloor:
        return "rough floor";
        break;

    case groundTiletype_smoothGround:
        return "smooth floor";
        break;

    default:
        return "undefined";
        break;
    }
}
const char* getWallTypeFromEnum(int cellType) {
    switch (cellType)
    {
    case wallTiletype_barrel:
        return "barrel";
        break;

    case wallTiletype_bed:
        return "bed";
        break;

    case wallTiletype_bookshelf:
        return "bookshelf";
        break;

    case wallTiletype_chair:
        return "chair";
        break;

    case wallTiletype_chest:
        return "chest";
        break;

    case wallTiletype_door:
        return "door";
        break;

    case wallTiletype_engravedWall:
        return "engraved wall";
        break;

    case wallTiletype_roughWall:
        return "rough wall";
        break;

    case wallTiletype_smoothWall:
        return "smooth wall";
        break;

    case wallTiletype_statue:
        return "statue";
        break;

    case wallTiletype_table:
        return "table";
        break;

    case wallTiletype_udStairs:
        return "up down stairs";
        break;

    case wallTiletype_downStairs:
        return "down stairs";
        break;

    case wallTiletype_upStairs:
        return "up stairs";
        break;

    default:
        return "undefined";
        break;
    }
}

//low level functions HIGHLY DISCOURAGED TO USE
//the MAP_ITEMS array has values sparsed through all the place
int addItemToItemsInMap(Item item) { //returns the index position result
    int i = 0;
    while (i < max_mapItems && MAP_ITEMS[i].type != -1)
    {
        i++;
    }
    if (i < max_mapItems)
    {
        assignItem(&MAP_ITEMS[i], item);
    }
    return i;
}
BOOL removeItemFromItemsInMap(int itemID) {
    if (itemID < max_mapItems)
    {
        MAP_ITEMS[itemID] = createItem(itemType_noItem, 0, 0);
    }
    return FALSE;
}

BOOL addItemToMap(Item item, Vec2 mapPosition) {
    //checking if the tile isn't occupied already
    if (GAME_GROUND[mapPosition.Y * GAME_MAP_WIDTH + mapPosition.X].containedID == -1)
    {
        int i = addItemToItemsInMap(item);
        if (i != max_mapItems)
        {
            GAME_GROUND[mapPosition.Y * GAME_MAP_WIDTH + mapPosition.X].containedID = i;
            return TRUE;
        }

    }
    return FALSE;
}

void removeItemFromMap(Vec2 mapPosition) {
    MAP_ITEMS[GAME_GROUND[mapPosition.Y * GAME_MAP_WIDTH + mapPosition.X].containedID] = createItem(itemType_noItem, 0, 0);
    GAME_GROUND[mapPosition.Y * GAME_MAP_WIDTH + mapPosition.X].containedID = -1;
}

void interactWithWallTile(Vec2 mapPosition) {
    WorldTile* interactingTile = &GAME_WALLS[mapPosition.X + GAME_MAP_WIDTH * mapPosition.Y];

    switch (interactingTile->type)
    {
    case wallTiletype_door:
        interactingTile->state = !interactingTile->state; //open or close the door
        break;

    case wallTiletype_statue: //statues are foundamental for the game's lore, they can be eventually admired as they have words engraved onto them and they represent figures (NIY) 
    {
        //feature isn't necessary but could be implemented if time is sufficent
    }
    break;
    default:
        break;
    }
}
WorldTile getWorldTile(Vec2 mapPosition, int level)
{
    if (level == onGround)
    {
        return GAME_GROUND[mapPosition.Y * GAME_MAP_WIDTH + mapPosition.X];
    }
    return GAME_WALLS[mapPosition.Y * GAME_MAP_WIDTH + mapPosition.X];
}
