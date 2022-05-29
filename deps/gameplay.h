#define gameState_exiting -1
#define gameState_menu 0
#define gameState_newGame 1
#define gameState_loadGame 2
#define gameState_settings 3
#define gameState_credits 4
#define gameState_playing 5

void setupGame()
{
    setupConsole();
    setupMaterials();
    setupPlayer();
    setupMap();
    map_clear();
    InitStructures();
    setupCrafting();
    setupEntities();
    initSpawners();
}

// quick function to implement movement in any Vec2 when you feel lazy
void movePosition(Vec2 *position)
{
    if (Input(Key_UP) == key_just_pressed)
    {
        position->Y -= 1;
    }
    if (Input(Key_DOWN) == key_just_pressed)
    {
        position->Y += 1;
    }
    if (Input(Key_RIGHT) == key_just_pressed)
    {
        position->X += 1;
    }
    if (Input(Key_LEFT) == key_just_pressed)
    {
        position->X -= 1;
    }
}

void movePosition(Vec2 *position, int multiplier){
        if (Input(Key_UP) == key_just_pressed)
    {
        position->Y -= multiplier;
    }
    if (Input(Key_DOWN) == key_just_pressed)
    {
        position->Y += multiplier;
    }
    if (Input(Key_RIGHT) == key_just_pressed)
    {
        position->X += multiplier;
    }
    if (Input(Key_LEFT) == key_just_pressed)
    {
        position->X -= multiplier;
    }
}

#define cursorMode_godEyeseight -1
#define cursorMode_inactive 0
#define cursorMode_looking 1

typedef struct CursorInfo
{
    Vec2 position;
    Attribute color;
    int mode; // 0 represents absolutely incative, other states may mean otherwise
    /*
    mode:
     1 : "looking"
    */
} CursorInfo, *PCursorInfo;

CursorInfo cursorHelper = {{1, 1}, Fg_Yellow, FALSE};

//raycast, to collision
//ray casting (using DDA algorythm)
Vec2 DDAMapRayCollisionDetection(Vec2 start, Vec2 finish) //returns tile position of the first collision found
{
    //My edit of the DDA line drawing algorythm
    int dx = abs(finish.X - start.X);
    int dy = abs(finish.Y - start.Y);
    int step;

    if (dx >= dy)
    {
        step = dx;
    }
    else {
        step = dy;
    }
    double xin = finish.X > start.X ? (double)dx / (double)step : (double)dx / (double)step * -1;
    double yin = finish.Y > start.Y ? (double)dy / (double)step : (double)dy / (double)step * -1;
    double x = start.X + 0.5;
    double y = start.Y + 0.5;

    int i = 0;
    while (i < step && !collidesWithMap({int(x), int(y)}))
    {
        x += xin;
        y += yin;
        i++;
    }
    return { int(x), int(y) };
}


//player related functions and values
int PLAYER_ACTION;
#define player_moving 1
#define player_looking 2
#define player_attacking 3
#define player_inInventory 4
#define player_peekingItem 5
#define player_interactingWithItem 6
#define player_equipMenu 7
#define player_inChestMenu 8
#define player_building 9
#define player_crafting 10
#define player_interacting 11
#define player_enchanting 12
#define player_smelting 13
Vec2 calculateVec2FromKeys(int upInput, int downInput, int leftInput, int rightInput)
{
    Vec2 resultant = {0, 0};
    if (upInput == key_just_pressed)
    {
        resultant.Y = -1;
    }
    if (downInput == key_just_pressed)
    {
        resultant.Y = 1;
    }
    if (leftInput == key_just_pressed)
    {
        resultant.X = -1;
    }
    if (rightInput == key_just_pressed)
    {
        resultant.X = 1;
    }
    return resultant;
}
void movePlayer(int upInput, int downInput, int leftInput, int rightInput){
    if (upInput == key_just_released)
    {
        if (!collidesWithMap({player.position.X, player.position.Y-1}))
        {
            player.position.Y -= 1;
        }
        
    }
    if (downInput == key_just_released)
    {
        if (!collidesWithMap({player.position.X, player.position.Y+1}))
        {
            player.position.Y += 1;
        }
    }
    if (leftInput == key_just_released)
    {
        if (!collidesWithMap({player.position.X-1, player.position.Y}))
        {
            player.position.X -= 1;
        }
    }
    if (rightInput == key_just_released)
    {
        if (!collidesWithMap({player.position.X+1, player.position.Y}))
        {
            player.position.X += 1;
        }
    }
}
void printInventoryItems(Vec2 startPosition){
    for (int i = 0; i < getPlayerInventoryLength(); i++)
    {
        showItemInfo(player.inventory[i], {startPosition.X, startPosition.Y+i});
    }
}
BOOL pickUpItemFromGround(){
    int playerLocation = player.position.X + player.position.Y * GAME_MAP_WIDTH;
    //check if there is an item on the player's tile
    if (GAME_GROUND[playerLocation].containedID != -1)
    {
        //check if the item isn't actually null
        if (MAP_ITEMS[GAME_GROUND[playerLocation].containedID].type != itemType_noItem)
        {
            //attempt adding the item to the player
            Item mapItem = MAP_ITEMS[GAME_GROUND[playerLocation].containedID];
            if(addItemToInventory(mapItem)){
                removeItemFromMap(player.position);
                return TRUE;
            }
        }
        
    }
    return FALSE;
}
BOOL dropItemOnGrund(int itemID){
    if (addItemToMap(player.inventory[itemID], player.position))
    {
        removeItemFromInventory(itemID);
        return TRUE;
    }
    return FALSE;
}
void printEquipmentItems(Vec2 startPosition){
    coloredText("head    :", Fg_White, startPosition);
    coloredText("torso   :", Fg_White, {startPosition.X , startPosition.Y+1});
    coloredText("leggins :", Fg_White, {startPosition.X , startPosition.Y+2});
    coloredText("boots   :", Fg_White, {startPosition.X , startPosition.Y+3});

    coloredText("Uhead   :", Fg_White, {startPosition.X , startPosition.Y+5});
    coloredText("Utorso  :", Fg_White, {startPosition.X , startPosition.Y+6});
    coloredText("Uleggins:", Fg_White, {startPosition.X , startPosition.Y+7});
    coloredText("Uboots  :", Fg_White, {startPosition.X , startPosition.Y+8});

    coloredText("Lhand   :", Fg_White, {startPosition.X , startPosition.Y+10});
    coloredText("Rhand   :", Fg_White, {startPosition.X , startPosition.Y+11});

    showItemInfo(player.head   , {startPosition.X+11 , startPosition.Y});
    showItemInfo(player.torso  , {startPosition.X+11 , startPosition.Y+1});
    showItemInfo(player.leggins, {startPosition.X+11 , startPosition.Y+2});
    showItemInfo(player.boots  , {startPosition.X+11 , startPosition.Y+3});

    showItemInfo(player.underHead   , {startPosition.X+11 , startPosition.Y+5});
    showItemInfo(player.underTorso  , {startPosition.X+11 , startPosition.Y+6});
    showItemInfo(player.underLeggins, {startPosition.X+11 , startPosition.Y+7});
    showItemInfo(player.underBoots  , {startPosition.X+11 , startPosition.Y+8});

    showItemInfo(player.leftHand, {startPosition.X+11, startPosition.Y+10});
    showItemInfo(player.rightHand, {startPosition.X+11, startPosition.Y+11});
}

#define player_viewDistance 20
#define getVismapTile(x, y) PLAYER_VISMAP[x + y*GAME_MAP_WIDTH]

void updatePlayerVOF()
{
    for (int i = 0; i < GAME_MAP_WIDTH*GAME_MAP_HEIGHT; i++)
    {
        PLAYER_VISMAP[i] = PLAYER_VISMAP[i] ? vismap_tileSeen : vismap_tileUndiscovered;
    }

    int visionAugment = getPlayerEnchantPowerSum(enchantType_vision);

    for (int angle = 0; angle < 360; angle++) //casts a circle of rays
    {
        Vec2f viewDirection = { cos(angle), sin(angle) }; //unitary vector representing the direction of the player's view
        int distance = 1;
        Vec2 currentCheck; //increments the unitary vector by distance, and checks if it collides with the map
        currentCheck.X = player.position.X + (int)(viewDirection.X * (double)distance);
        currentCheck.Y = player.position.Y + (int)(viewDirection.Y * (double)distance);
        while (!collidesWithMap(currentCheck) && distance < player_viewDistance + visionAugment)
        {
            currentCheck.X = player.position.X + (int)(viewDirection.X * (double)distance);
            currentCheck.Y = player.position.Y + (int)(viewDirection.Y * (double)distance);
            getVismapTile(currentCheck.X, currentCheck.Y) = vismap_tileInView;
            distance++;
        }
    }
}


//player.enchant related
void runPlayerEnchant(Enchantment enchant) 
{
    switch (enchant.enchantID)
    {
    case enchantType_regeneration:
        player.health += enchant.strength;
        break;
    case enchantType_poison:
        player.health -= enchant.strength;
        break;
    case enchantType_fiery:
        player.health -= enchant.strength * 2; //yes, fiery is powerful and it burns you alive
    case enchantType_teleporting:
    {
        //move the player to a random location, considered it has to NOT collide with the walls
        Vec2 newMotion = { rand() % enchant.strength, rand() % enchant.strength };
        Vec2 newPos = Vec2sum(player.position, newMotion);
        while (collidesWithMap(newPos))
        {
            newMotion = { rand() % enchant.strength, rand() % enchant.strength };
            newPos = Vec2sum(player.position, newMotion);
        }
        player.position = newPos;
    }
    break;
    case enchantType_clearance:
        for (int i = 0; i < 8; i++)
        {
            player.sufferingEnchants[i].enchantID = enchantType_none;
            player.sufferingEnchants[i].certainity = 0;
        }

    default:
        break;
    }
}
void consumePlayerSufferingEnchants()
{
    for (int i = 0; i < 8; i++)
    {
        if (player.sufferingEnchants[i].enchantID != enchantType_none)
        {
            if (player.sufferingEnchants[i].certainity > 0)
                runPlayerEnchant(player.sufferingEnchants[i]);
            else
                player.sufferingEnchants[i].enchantID = enchantType_none;
            player.sufferingEnchants[i].certainity -= 1;
        }
    }

}
void runPlayerEquipmentEnchants()
{
    if (player.head.type != itemType_noItem)
        for (int i = 0; i < 8; i++)
        {
            if (player.head.enchants[i].enchantID != enchantType_none)
                if (isEnchantPositive(player.head.enchants[i].enchantID))
                    runPlayerEnchant(player.head.enchants[i]);
        }
    if (player.leggins.type != itemType_noItem)
        for (int i = 0; i < 8; i++)
        {
            if (player.leggins.enchants[i].enchantID != enchantType_none)
                if (isEnchantPositive(player.leggins.enchants[i].enchantID))
                    runPlayerEnchant(player.leggins.enchants[i]);
        }
    if (player.torso.type != itemType_noItem)
        for (int i = 0; i < 8; i++)
        {
            if (player.torso.enchants[i].enchantID != enchantType_none)
                if (isEnchantPositive(player.torso.enchants[i].enchantID))
                    runPlayerEnchant(player.torso.enchants[i]);
        }
    if (player.boots.type != itemType_noItem)
        for (int i = 0; i < 8; i++)
        {
            if (player.boots.enchants[i].enchantID != enchantType_none)
                if (isEnchantPositive(player.boots.enchants[i].enchantID))
                    runPlayerEnchant(player.boots.enchants[i]);
        }
    if (player.underHead.type != itemType_noItem)
        for (int i = 0; i < 8; i++)
        {
            if (player.underHead.enchants[i].enchantID != enchantType_none)
                if (isEnchantPositive(player.underHead.enchants[i].enchantID))
                    runPlayerEnchant(player.underHead.enchants[i]);
        }
    if (player.leggins.type != itemType_noItem)
        for (int i = 0; i < 8; i++)
        {
            if (player.leggins.enchants[i].enchantID != enchantType_none)
                if (isEnchantPositive(player.leggins.enchants[i].enchantID))
                    runPlayerEnchant(player.leggins.enchants[i]);
        }
    if (player.underTorso.type != itemType_noItem)
        for (int i = 0; i < 8; i++)
        {
            if (player.underTorso.enchants[i].enchantID != enchantType_none)
                if (isEnchantPositive(player.underTorso.enchants[i].enchantID))
                    runPlayerEnchant(player.underTorso.enchants[i]);
        }
    if (player.underBoots.type != itemType_noItem)
        for (int i = 0; i < 8; i++)
        {
            if (player.underBoots.enchants[i].enchantID != enchantType_none)
                if (isEnchantPositive(player.underBoots.enchants[i].enchantID))
                    runPlayerEnchant(player.underBoots.enchants[i]);
        }
}

//screen-map related functions and values
BOOL isInMapScreen(Vec2 worldPosition)
{
    if (worldPosition.X > mapToScreenOffset.X + screen_width-1 || worldPosition.X < mapToScreenOffset.X || worldPosition.Y < mapToScreenOffset.Y || worldPosition.Y > mapToScreenOffset.Y + screen_height-1)
    {
        return FALSE;
    }
    return TRUE;
}
void drawPixelInWorld(CHAR_INFO data, Vec2 worldPosition)
{
    if (isInMapScreen(worldPosition))
    {
        paintPixel(data, {worldPosition.X - mapToScreenOffset.X, worldPosition.Y - mapToScreenOffset.Y});
    }
}
void interrogateMapLocation(Vec2 position)
{ // prints on the screen useful data on what is present in position `Vec2 position`
    if (GAME_WALLS[position.Y*GAME_MAP_WIDTH+position.X].type == wallTiletype_noWall)
    {
        WorldTile floorTile = GAME_GROUND[position.Y*GAME_MAP_WIDTH+position.X];
        Attribute color = toFgColor(GAME_MATERIALS[floorTile.materialID].color);
        char stringBuffer[32] = "";
        strcat(stringBuffer, GAME_MATERIALS[floorTile.materialID].name);
        strcat(stringBuffer, " ");
        strcat(stringBuffer, getGroundTypeFromEnum(floorTile.type));
        blankWindow({0, 0}, {36, 7});
        coloredText(stringBuffer, color, {2, 2});
        stringBuffer[0] = '\0';
        char itoaStringBuffer[4] = "";
        if (floorTile.containedID != itemType_noItem)
        {
            showItemFullName(MAP_ITEMS[floorTile.containedID], {1, 3});
        }
        //render entity
        Entity entity = getEntityFromPosition(position);
        int eamount = getEntityAmountFromPosition(position);
        if (eamount > 0)
            eamount > 1 ? 
                coloredText(
                    strcat(
                    strcat(
                        strcat(stringBuffer, GAME_ENTITIES[entity.entityType].name),
                        " + "
                        ),
                        _itoa(eamount, itoaStringBuffer, 10)
                    ),
                    GAME_ENTITIES[entity.entityType].color, {2, 4})
                : coloredText(GAME_ENTITIES[entity.entityType].name, GAME_ENTITIES[entity.entityType].color, {2, 4});
        if (getSpawnerFromMapPosition(position) != NULL)
            coloredText("Beware! A spawner", Fg_Fucsia, { 2, 5 });

    } else {
        WorldTile wallTile = GAME_WALLS[position.Y*GAME_MAP_WIDTH+position.X];
        Attribute color = toFgColor(GAME_MATERIALS[wallTile.materialID].color);
        char wallTileDetails[32] = "";
        strcat(wallTileDetails, GAME_MATERIALS[wallTile.materialID].name);
        strcat(wallTileDetails, " ");
        strcat(wallTileDetails, getWallTypeFromEnum(wallTile.type));
        blankWindow({0, 0}, {36, 4});
        coloredText(wallTileDetails, color, {2, 2});
        if (collidesWithMap(position))
        {
            if (wallTile.containedID != material_noMaterial)
            {
                coloredText(GAME_MATERIALS[wallTile.containedID].name, toFgColor(GAME_MATERIALS[wallTile.containedID].color), {2, 3});
                coloredText("ore", toFgColor(GAME_MATERIALS[wallTile.containedID].color), {3+(int)strlen(GAME_MATERIALS[wallTile.containedID].name), 3});
            }
        }
    }
    if (position.X == player.position.X && position.Y == player.position.Y)
    {
        coloredText("Here we have you!", Fg_White, {1, 1});
    }
    
}
void updateMapToScreenOffset(Vec2 screenPosition){
    if (screenPosition.X > (screen_width/4)*3)
    {
        mapToScreenOffset.X += screen_width/2;
    } else if (screenPosition.X < (screen_width/4)*1)
    {
        mapToScreenOffset.X -= screen_width/2;
    }
    
    if (screenPosition.Y > (screen_height/4)*3)
    {
        mapToScreenOffset.Y += screen_height/2;
    } else if (screenPosition.Y < (screen_height/4)*1)
    {
        mapToScreenOffset.Y -= screen_width/2;
    }

    mapToScreenOffset = clampPosition({0, 0}, mapToScreenOffset, {GAME_MAP_WIDTH-screen_width, GAME_MAP_HEIGHT-screen_height});
}

void renderPlayerPerspective()
{
    //everything here now depens on the player vismap
    for (int y = 0; y < screen_height; y++)
    {
        for (int x = 0; x < screen_width; x++)
        {
            
            Vec2 worldPosition = { x + mapToScreenOffset.X, y + mapToScreenOffset.Y };
            switch (getVismapTile(worldPosition.X, worldPosition.Y))
            {
            case vismap_tileInView:
            {
                drawWorldPosition({ x, y }, worldPosition);
                Trap* trap = getTrapFromPosition(worldPosition);
                if (trap != NULL) if (trap->discovered) drawPixelInWorld({ '#', toFgColor(ENCHANTS_DECOS[trap->effect.enchantID].Attributes) }, trap->position);
                Spawner* spawner = getSpawnerFromMapPosition(worldPosition);
                if (NULL != spawner) drawPixelInWorld(SPAWNER_GRAPHIC, worldPosition);
                Entity* entity = getEntityAddressFromPosition(worldPosition);
                if (NULL != entity) drawPixelInWorld({ (WCHAR)GAME_ENTITIES[entity->entityType].sprite, GAME_ENTITIES[entity->entityType].color }, worldPosition);
            }
            break;
            case vismap_tileSeen:
            {
                drawWorldPosition({ x, y }, worldPosition);
                collidesWithMap(worldPosition) ? paintPixel((Attribute)(Bg_Olive_Green | Fg_Black), { x, y }) : paintPixel(Fg_Olive_Green, { x, y });
            }
            break;

            case vismap_tileUndiscovered:
            {
                drawPixelInWorld({ ' ', Fg_Black | Bg_Black }, worldPosition);
            }
            //if the tile is undiscovered, you just won't see it, so leave it blank
            default:
                break;
            }
        }
    }
    
    
}

void debugPlayerRayCasting()
{
    //everything here now depens on the player vismap
    for (int y = 0; y < screen_height; y++)
    {
        for (int x = 0; x < screen_width; x++)
        {
            Vec2 worldPosition = { x + mapToScreenOffset.X, y + mapToScreenOffset.Y };
            switch (getVismapTile(worldPosition.X, worldPosition.Y))
            {
            case vismap_tileInView:
                drawPixelInWorld({ ' ', Bg_Grey }, worldPosition);
                break;
            case vismap_tileSeen:
                drawPixelInWorld({ ' ', Bg_Blue }, worldPosition);
                break;
            case vismap_tileUndiscovered:
                drawPixelInWorld({ ' ', Bg_Bordeaux }, worldPosition);
                break;
            default:
                drawPixelInWorld({ ' ', Bg_Fucsia }, worldPosition);
                break;
            }
        }
    }


}


void renderScene()
{ // Mind that this is one function that wraps up all the graphics for the scene (assuming you're just vieweing the world from above with full visualization on everything)
    drawWorld();

    //draw the traps
    for (int i = 0; i < max_mapTraps; i++)
    {
        if (MAP_TRAPS[i].discovered)
        {
            drawPixelInWorld({'#', toFgColor(ENCHANTS_DECOS[MAP_TRAPS[i].effect.enchantID].Attributes)}, MAP_TRAPS[i].position);
        }
    }
    
    //draw the structures
    for (int i = 0; i < max_mapStructures; i++)
    {
        if (MAP_STRUCTURES[i].structureType != structureType_noStructure)
        {
            for (int p = 0; p < 9; p++)
            {
                if (GAME_STRUCTURES[MAP_STRUCTURES[i].structureType].schematic[p].Char.UnicodeChar != ' ' || GAME_STRUCTURES[MAP_STRUCTURES[i].structureType].schematic[p].Attributes != 0)
                    drawPixelInWorld(GAME_STRUCTURES[MAP_STRUCTURES[i].structureType].schematic[p], {MAP_STRUCTURES[i].positon.X-1+p%3, MAP_STRUCTURES[i].positon.Y -1+p/3});
            }
        }
    }
    
    //draw the spawners
    for (int i = 0; i < max_mapSpawners; i++)
    {
        if (MAP_SPAWNERS[i].entityTypeID != entityType_nothing)
            drawPixelInWorld(SPAWNER_GRAPHIC, MAP_SPAWNERS[i].position);
    }

    //draw the entities
    for (int i = 0; i < maxMapEntities; i++)
    {
        if (MAP_ENTITIES[i].entityType != entityType_nothing)
            drawPixelInWorld({ (WCHAR)GAME_ENTITIES[MAP_ENTITIES[i].entityType].sprite, GAME_ENTITIES[MAP_ENTITIES[i].entityType].color }, MAP_ENTITIES[i].position);
    }

    showLastAnnouncement();
    
}
void debugMapLocation(Vec2 position)
{
    char stringBuffer[10];
    coloredText("Ground:         ", Fg_White, {0, 2});
    coloredText("   type:        ", Fg_Grey, {0, 3});
    _itoa(GAME_GROUND[position.Y * GAME_MAP_WIDTH + position.X].type, stringBuffer, 10);
    coloredText(stringBuffer, Fg_Grey, {18, 3});
    coloredText("   contained: ", Fg_Grey, {0, 4});
    _itoa(GAME_GROUND[position.Y * GAME_MAP_WIDTH + position.X].containedID, stringBuffer, 10);
    coloredText(stringBuffer, Fg_Grey, {18, 4});
    coloredText("   Material:  ", Fg_Grey, {0, 5});
    _itoa(GAME_GROUND[position.Y * GAME_MAP_WIDTH + position.X].materialID, stringBuffer, 10);
    coloredText(stringBuffer, Fg_Grey, {18, 5});

    coloredText("Wall:           ", Fg_White, {0, 7});
    coloredText("   type:        ", Fg_Grey, {0, 8});
    _itoa(GAME_WALLS[position.Y * GAME_MAP_WIDTH + position.X].type, stringBuffer, 10);
    coloredText(stringBuffer, Fg_Grey, {18, 8});
    coloredText("   contained: ", Fg_Grey, {0, 9});
    _itoa(GAME_WALLS[position.Y * GAME_MAP_WIDTH + position.X].containedID, stringBuffer, 10);
    coloredText(stringBuffer, Fg_Grey, {18, 9});
    coloredText("   Material:  ", Fg_Grey, {0, 10});
    _itoa(GAME_WALLS[position.Y * GAME_MAP_WIDTH + position.X].materialID, stringBuffer, 10);
    coloredText(stringBuffer, Fg_Grey, {18, 10});
}
void displayEnchantInfo(Enchantment * enchantArray, Vec2 startPosition, int arrLen){
    int enchantLen = getEnchantsAmountFromArray(enchantArray, arrLen);
    char tmpString[6] = "";
    for (int i = 0; i < enchantLen; i++)
    {
        paintPixel(ENCHANTS_DECOS[enchantArray[i].enchantID], {startPosition.X, startPosition.Y+i});
        coloredText(getEnchantTypeFromEnum(enchantArray[i].enchantID), toFgColor(ENCHANTS_DECOS[enchantArray[i].enchantID].Attributes), {startPosition.X+2, startPosition.Y+i});
        coloredText(_itoa(enchantArray[i].strength, tmpString, 10), toFgColor(ENCHANTS_DECOS[enchantArray[i].enchantID].Attributes), {startPosition.X+20, startPosition.Y+i});
        coloredText(_itoa(enchantArray[i].certainity, tmpString, 10), toFgColor(ENCHANTS_DECOS[enchantArray[i].enchantID].Attributes), {startPosition.X+25, startPosition.Y+i});
    }
}
void displayItemEnchantInfo(Item item, Vec2 startPosition){
    displayEnchantInfo(item.enchants, startPosition, 8);
}
//map only related functions

//map-chests related functions
void printChestItems(int chestID, Vec2 startPosition){
    int chestLen = 0;
    while (chestLen < maxItems_chestContainer && MAP_CHESTS[chestID].items[chestLen].type != itemType_noItem)
    {
        chestLen++;
    }
        for (int j = 0; j < chestLen; j++)
        {
            showItemInfo(MAP_CHESTS[chestID].items[j], {startPosition.X, startPosition.Y+j});
        }
    if (chestLen == 0)
    {
        coloredText("No items to display", Fg_Grey, startPosition);
    }
}

//player-chest related functions
BOOL moveItemFromChestToInventory(int chestId, int itemId)
{
    if (getChestInventoryLength(chestId) < itemId)
        if (addItemToInventory(MAP_CHESTS[chestId].items[itemId]))
        {
            removeItemFromChest(chestId, itemId);
            return TRUE;
        }
    return FALSE;
}
BOOL moveItemFromInventoryToChest(int chestId, int itemId)
{
    if (getPlayerInventoryLength() < itemId)
        if (addItemToChest(chestId, player.inventory[itemId]))
        {
            removeItemFromInventory(itemId);
            return TRUE;
        }
    return FALSE;
}

//map-item related functions
Item createItemFromWall(WorldTile tile, int luck)
{
    Item returningItem = createItem(itemType_noItem, 0, 0);
    int involvedMaterialID;
    if (tile.type != wallTiletype_noWall)
    {
        if (tile.containedID != material_noMaterial)
        {
            involvedMaterialID = tile.containedID;
        }
        else
        {
            involvedMaterialID = tile.materialID;
        }
        returningItem = createItem(GAME_MATERIALS[involvedMaterialID].rawItemID != itemType_noItem ? GAME_MATERIALS[involvedMaterialID].rawItemID : getItemForMaterialType(getMaterialType(GAME_MATERIALS[involvedMaterialID])), involvedMaterialID, rand()%(4+luck/2)+1);
    } else {
        returningItem = createItem(itemType_noItem, material_noMaterial, itemQuality_legendary);
    }
    return returningItem;
}
BOOL mineWall(Vec2 mapPosition, int luck){ //returs result of the operation: 0 if not succesfull, 1 if yes
    //destroy a wall in the map and place an item in the map, the one that should result from `createItemFromWall` function
    Item tmpItem = createItemFromWall(GAME_WALLS[mapPosition.Y*GAME_MAP_WIDTH+mapPosition.X], luck);
    if (isMaterialDestroyable(GAME_MATERIALS[GAME_WALLS[mapPosition.Y*GAME_MAP_WIDTH+mapPosition.X].materialID]))
    {
        GAME_WALLS[mapPosition.Y*GAME_MAP_WIDTH+mapPosition.X].type = wallTiletype_noWall;
        addItemToMap(tmpItem, mapPosition);
        return TRUE;
    }
    return FALSE;
}
BOOL attemptMiningWall(Vec2 mapPosition){
    BOOL isToolCorrect;
    BOOL bewoodLike = isMaterialWoodLike(GAME_MATERIALS[getWorldTile(mapPosition, onWalls).materialID]);
    if (bewoodLike)
        isToolCorrect = player.rightHand.type == itemType_axe;
    else
        isToolCorrect = player.rightHand.type == itemType_pickaxe;

    if (isToolCorrect && getMaterialStrength(GAME_MATERIALS[player.rightHand.materialID]) > getMaterialStrength(GAME_MATERIALS[GAME_WALLS[mapPosition.Y*GAME_MAP_WIDTH+mapPosition.X].materialID])-2)
    {
        int baseDestroyChance = rand() % 10 > 8 - getEnchantInItem(player.rightHand, enchantType_efficiency).strength; //efficiency increases your ability to mine correctly
        if (baseDestroyChance)
        {
            int isPickStrongEnough = rand() % 10 > (10 - getMaterialStrength(GAME_MATERIALS[player.rightHand.materialID]) - 2);
            if (isPickStrongEnough)
            {
                int luck = getEnchantInItem(player.rightHand, enchantType_luck).strength;
                mineWall(mapPosition, luck);
            } else {
                mineWall(mapPosition, -4); //basically you just destroy the wall
            }
            return TRUE;
        }
    }
    return FALSE;
}

//ui related functions and values
BOOL shouldRender_hintsUI = TRUE;
void renderhintsUI(){
    int columnX = screen_width-36;
    blankWindow({screen_width-40, 1}, {screen_width-1, screen_height-2});
    coloredText("Player health", Fg_White, {columnX, 2});
    char stringBuffer[16] = "";
    coloredText(_itoa(player.health, stringBuffer, 10), Fg_Red, { columnX+1, 3 });
    coloredText("\\", Fg_Red, { columnX + 4, 3 });
    coloredText(_itoa(player.maxHealth, stringBuffer, 10), Fg_Red, { columnX + 8, 3 });

    coloredText("Press H to hide this window", Fg_White, {screen_width-38, screen_height-2});
    coloredText("E", Fg_Lime_Green, {columnX, 5});
    coloredText("C", Fg_Lime_Green, {columnX, 6});
    coloredText("U", Fg_Lime_Green, {columnX, 7});
    coloredText("P", Fg_Lime_Green, {columnX, 8});
    coloredText("X", Fg_Lime_Green, {columnX, 9});
    coloredText("B", Fg_Lime_Green, {columnX, 10});
    coloredText("K", Fg_Lime_Green, {columnX, 11});
    coloredText("L", Fg_Lime_Green, {columnX, 12});


    coloredText("-", Fg_Green, {columnX+1, 5});
    coloredText("-", Fg_Green, {columnX+1, 6});
    coloredText("-", Fg_Green, {columnX+1, 7});
    coloredText("-", Fg_Green, {columnX+1, 8});
    coloredText("-", Fg_Green, {columnX+1, 9});
    coloredText("-", Fg_Green, {columnX+1, 10});
    coloredText("-", Fg_Green, {columnX+1, 11});
    coloredText("-", Fg_Green, {columnX+1, 12});


    coloredText("inventory", Fg_White, {columnX+2, 5});
    coloredText("open chest", Fg_White, {columnX+2, 6});
    coloredText("interact", Fg_White, {columnX+2, 7});
    coloredText("pick up item", Fg_White, {columnX+2, 8});
    coloredText("crafting", Fg_White, {columnX+2, 9});
    coloredText("building", Fg_White, {columnX+2, 10});
    coloredText("attack", Fg_White, {columnX+2, 11});
    coloredText("look", Fg_White, {columnX+2, 12});


    coloredText("ArrowKeys", Fg_Lime_Green, {columnX, 14});
    coloredText("move", Fg_White, {columnX+11, 15});

    coloredText("I", Fg_Lime_Green, {columnX, 16});
    coloredText("-", Fg_Green, {columnX+1, 16});
    coloredText("info (player)", Fg_White, {columnX+2, 16});
    stringBuffer[0] = '\0';
    int i2 = 0;
    for (int i = 0; i < 8; i++)
    {
        if (player.sufferingEnchants[i].enchantID != enchantType_none)
        {
            paintPixel(ENCHANTS_DECOS[player.sufferingEnchants[i].enchantID], { columnX, 19 + i2 });
            coloredText(getEnchantTypeFromEnum(player.sufferingEnchants[i].enchantID), toFgColor(ENCHANTS_DECOS[player.sufferingEnchants[i].enchantID].Attributes), { columnX + 1, 19 + i2 });
            i2++;
        }
        //more info is displayed in the player info tab
    }
   coloredText("Affected by: ", Fg_White, { columnX, 18 });
   if (i2 == 0) coloredText(" None", Fg_Grey, { columnX, 19 });
}

//crafting-visual related functions
unsigned int showMaterialFlagInfo(unsigned int materialFlags, Vec2 position, Attribute color) //returs the length of the text
{
    Material tmpMat;
    tmpMat.flags = materialFlags;
    char infoBuffer[256] = "";
    if (isMaterialLiquid(tmpMat))
    {
        strcat(infoBuffer, "liquid ");
    }
    if (isMaterialDeadly(tmpMat))
    {
        strcat(infoBuffer, "deadly ");
    }
    if (isMaterialFlammable(tmpMat)){
        strcat(infoBuffer, "flammable ");
    }
    if (isMaterialIncendiary(tmpMat)){
        strcat(infoBuffer, "incendiary ");
    }
    if (isMaterialDestroyable(tmpMat)){
        strcat(infoBuffer, "destroyable ");
    }
    if (isMaterialEdible(tmpMat)){
        strcat(infoBuffer, "edible ");
    }
    if (isMaterialWaterProof(tmpMat)){
        strcat(infoBuffer, "waterproof ");
    }
    if (isMaterialPoisonous(tmpMat)){
        strcat(infoBuffer, "poisonous ");
    }
    int materialType = getMaterialType(tmpMat);
    if (materialType != materialType_VOID) strcat(infoBuffer, getMaterialTypeFromEnum(materialType));
    if (isMaterialSmeltable(tmpMat)){
        strcat(infoBuffer, "smeltable ");
    }
    coloredText(infoBuffer, color, position);
    return strlen(infoBuffer);
}

void displayCraftingRecipes(int category, Vec2 startPosition, int step, int height, Item * sourceInventory, int invLength)
{
    //step represents what segment of the item array to look at. 
    //suppose you have a 12 item long inventory and you want to display it
    int length = getRecipesLength(category);
    if (length)
    {
        int si = 0; //simple index
        for (int i = height*step; i < clamp(0, height*step+height, length); i++)
        {
            coloredText(GAME_CRAFTING_RECIPES[category][i].name, canListCraftItem(sourceInventory, invLength, GAME_CRAFTING_RECIPES[category][i]) ? Fg_Grey : Fg_Bordeaux, {startPosition.X, startPosition.Y+si});
            si++;
        }
    } else {
        coloredText("No recipes to display", Fg_Grey, startPosition);
    }
    int pagesAmount = length/height+1;
    coloredText("page: ", Fg_White, {startPosition.X, startPosition.Y+height+1});
    char tmpStr[3] = "";
    coloredText(_itoa(step+1, tmpStr, 10), Fg_White, {startPosition.X+6, startPosition.Y+height+1});
    coloredText("/", Fg_White, {startPosition.X+9, startPosition.Y+height+1});
    coloredText(_itoa(pagesAmount, tmpStr, 10), Fg_White, {startPosition.X+10, startPosition.Y+height+1});
}


void displayItemRepresentationInfo(ItemRepresentation representation, Vec2 position, Attribute color)
{
    if (representation.itemType == itemType_undefined)
    {
        // 'any' and then ...[characterstic list] material
        coloredText("any ", color, position);
        int l = showMaterialFlagInfo(representation.flagsRequired, {position.X+4, position.Y}, color);
        coloredText("material", color, {position.X+4+l, position.Y});
    } else {
        int l = showMaterialFlagInfo(representation.flagsRequired, {position.X, position.Y}, color);
        coloredText(getItemTypeFromEnum(representation.itemType), color, {position.X+l, position.Y});
    }
}
void displayCraftingRecipeIngredients(CraftingRecipe recipe, Vec2 startPosition) //without hints on what available and what not
{
    int ingredientID = 0;
    while (recipe.recipe[ingredientID].itemType != itemType_noItem)
    {
        displayItemRepresentationInfo(recipe.recipe[ingredientID], {startPosition.X+4, startPosition.Y+ingredientID}, Fg_Grey);
        int l = paintText(recipe.amounts[ingredientID], {startPosition.X, startPosition.Y+ingredientID});
        paintPixel({'x', Fg_Grey}, {startPosition.X+l, startPosition.Y+ingredientID});
        ingredientID++;
    }
    
}

void displayCraftingRecipeIngredientsWHints(CraftingRecipe recipe, Vec2 startPosition) //without hints on what available and what not
{
    int ingredientID = 0;
    while (recipe.recipe[ingredientID].itemType != itemType_noItem)
    {
        Attribute color = recipe.amounts[ingredientID] > 0 ? 
            getRepresentationMatchingItemsAmountInList(player.inventory, getPlayerInventoryLength(), recipe.recipe[ingredientID]) >= recipe.amounts[ingredientID] ? Fg_White : Fg_Red
            :
            isMatchingItemContained(player.inventory, getPlayerInventoryLength(), recipe.recipe[ingredientID]) ? Fg_White : Fg_Red;
        displayItemRepresentationInfo(recipe.recipe[ingredientID], {startPosition.X+4, startPosition.Y+ingredientID}, color);
        int l = paintText(recipe.amounts[ingredientID], {startPosition.X, startPosition.Y+ingredientID});
        paintLine((Attribute)color, {startPosition.X, startPosition.Y+ingredientID}, {startPosition.X+40, startPosition.Y});
        paintPixel({'x', color}, {startPosition.X+l, startPosition.Y+ingredientID});
        ingredientID++;
    }
}

//item-player related fucntion
BOOL useItemInInventory(int inventoryID) //it supposes that the item is in the inventory : returns TRUE if the item was used succesfully, returns FALSE if the item isn't usable, returns -1 (operation_failed) for any other error that prevented the item from being used
{
    if (inventoryID < getPlayerInventoryLength())
    {
        switch (player.inventory[inventoryID].type)
        {
        case itemType_bottle: // if it's a bottle it will apply all the enchants in it, removing the enchants from the bottle
            for (int i = 0; i < 8; i++)
            {
                if (player.inventory[inventoryID].enchants[i].enchantID != enchantType_none) //when drnking from potions the enchant is not triggerable
                    addEnchantToPlayer(player.inventory[inventoryID].enchants[i]);
            }
            for (int i = 0; i < 8; i++)
            {
                player.inventory[inventoryID].enchants[i] = createEnchant(enchantType_none, 0, 0);
            }
            return TRUE;
        default:
            return FALSE;
        }
        
    }
    return operation_failed;
}
//NOTE: interact will be another thing
/*
example : interact stands with interacting with the whole world using the item, such as filling a bottle with something or feeding a dog a piece of meat
example : using the item means CONSUMING it, such in a way tha a potion gets druk, a loaf of bread eaten and so on ... 
*/

//game cycle related fucntions
void gameOver()
{
    deleteFile(GAME_FILENAME);
    while (true)
    {
        blankWindow({ 10, 5 }, { screen_width - 10, screen_height - 5 });
        coloredText("U R DEAD ... (not big surprise)", Fg_Red, { 20, 7 });
        coloredText("your journey ends here ...", Fg_Water_Green, { 20, 10 });
        updateScreen();
    }
}


void worldStep() //calculate all of the AI's, liquid, physics and etc ... workings
{
    //here there will be AI
    for (int i = 0; i < maxMapEntities; i++)
    {
        if (MAP_ENTITIES[i].entityType != entityType_nothing)
            runEntityAI(&MAP_ENTITIES[i]);
    }
    consumePlayerSufferingEnchants();
    runPlayerEquipmentEnchants();
    player.maxHealth = player.baseMaxHealth + getPlayerEnchantPowerSum(enchantType_healthBoost); //keep in check the player's maximum health
    player.health = clamp(0, player.health, player.maxHealth);
    updateSpawners();
}