#pragma once

void wallOut()
{
    for (int y = 0; y < GAME_MAP_HEIGHT; y++)
    {
            getMapWall(0, y).type = wallTiletype_roughWall;
            getMapWall(GAME_MAP_WIDTH-1, y).materialID = materialType_VOID;
    }

    for (int x = 0; x < GAME_MAP_WIDTH; x++)
    {
        getMapWall(x, 0).type = wallTiletype_roughWall;
        getMapWall(x, GAME_MAP_HEIGHT-1).materialID = materialType_VOID;

    }
}

void clearRegisters()
{
    initSpawners();
    setupPlayer();
    clearMap();
    clearTraps();
    for (int i = 0; i < max_mapEntities; i++)
    {
        MAP_ENTITIES[i].entityType = entityType_nothing;
    }

}

void cleanRegisters()
{
    for (int i = 0; i < max_mapItems; i++)
    {
        int x = 0;
        BOOL found = FALSE;
        while (x < GAME_MAP_WIDTH && !found)
        {
            int y = 0;
            while (y < GAME_MAP_HEIGHT && !found)
            {
                if (getMapGround(x, y).containedID == i && (getMapGround(x, y).type == groundTiletype_roughFloor || getMapGround(x, y).type == groundTiletype_smoothGround))
                    found = TRUE;
                y++;
            }
            x++;
        }
        if (!found)
        {
            MAP_ITEMS[i].type = itemType_noItem;
        }
    }

    for (int i = 0; i < max_mapChests; i++)
    {
        int y = 0;
        BOOL found = FALSE;
        while (y < GAME_MAP_HEIGHT && !found)
        {
            int x = 0;
            while (x < GAME_MAP_WIDTH && !found)
            {
                if (getMapWall(x, y).type == wallTiletype_chest && getMapWall(x, y).containedID == i)
                    found = TRUE;
                x++;
            }
            y++;
        }
        if (!found)
        {
            MAP_CHESTS[i].isUsed = FALSE;
        }
    }

    

    for (int i = 0; i < max_mapTraps; i++)
    {
        if (MAP_TRAPS[i].position.X != -1 && MAP_TRAPS[i].position.Y != -1)
            if (getMapWall(MAP_TRAPS[i].position.X, MAP_TRAPS[i].position.Y).type != wallTiletype_noWall)
                MAP_TRAPS[i].discovered = FALSE;
                MAP_TRAPS[i].effect.enchantID = enchantType_none;
                MAP_TRAPS[i].position = { -1, -1 }; //effectively nullifies the trap 
    }

}

void createDemoLevel()
{
    clearRegisters();
    createRoom({ 10, 10 }, { 10, 10 }, doorSideRight, wallTiletype_roughWall, material_dolomite, groundTiletype_smoothGround, material_birchWood);
    addItemToMap(createItem(itemType_sword, material_platinum, itemQuality_fine), { 10, 10 });
    addItemToMap(createItem(itemType_helmet, material_platinum, itemQuality_fine), { 10, 10 });
    Item bottle = createItem(itemType_bottle, material_glass, itemQuality_pristine);
    addEnchantToItem(&bottle, createEnchant(enchantType_vision, 10, 30));
    addItemToMap(bottle, { 10, 12 });
    createRoom({ 20, 15 }, { 20, 5 }, doorSideBottom, wallTiletype_smoothWall, material_gold, groundTiletype_smoothGround, material_cherryWood);
    addSpawner(createSpawner(entityType_spider, 1, 10, { 20, 15 }, 10, 0));
    int chest1Location = placeNewChest({ 20, 16 }, material_dolomite);
    addEnchantToItem(&bottle, createEnchant(enchantType_regeneration, 1, 10));
    addItemToChest(chest1Location, bottle);
    addItemToChest(chest1Location, createItem(itemType_coin, material_gold, itemQuality_high));
    addItemToChest(chest1Location, createItem(itemType_coin, material_gold, itemQuality_high));
    addItemToMap(createItem(itemType_pickaxe, material_platinum, itemQuality_high), {7, 7});

    int i = 0;
    while (i < GAME_MAP_HEIGHT-10)
    {
        for (int x = 0; x < GAME_MAP_WIDTH; x++)
        {
            getMapWall(x, i) = createTile(rand() % 2, wallTiletype_roughWall, rand() % 20 < 2 ? rand() % 5 : -1, 0);
            if (rand() % 20 == 1) {getMapWall(x, i).type = wallTiletype_door; getMapWall(x, i).state = doorState_closed;}
        }
        i += rand() % 20;
    }
    i = 0;
    while (i < 120)
    {
        for (int y = 0; y < GAME_MAP_HEIGHT; y++)
        {
            getMapWall(i, y) = createTile(rand() % 2, wallTiletype_roughWall, rand() % 20 < 2 ? rand() % 5 : -1, 0);
            if (rand() % 20 == 1) { getMapWall(i, y).type = wallTiletype_door; getMapWall(i, y).state = doorState_closed; }
        }
        i += rand() % 20;
    }

    for (int i = 0; i < 20; i++)
    {
        createMapRectangle({ rand() % GAME_MAP_WIDTH, rand() % GAME_MAP_HEIGHT }, { rand() % 20, rand() % 15 }, onWalls, createTile(wallTiletype_noWall, wallTiletype_noWall, -1, -1) );
    }

    for (int i = 0; i < 20; i++)
    {
        addSpawner(createSpawner(entityType_spider, 1, 10, { rand() % GAME_MAP_WIDTH, rand() % GAME_MAP_HEIGHT }, rand() % 20, 7));
    }

    for (int i = 0; i < 10; i++)
    {
        addSpawner(createSpawner(rand()%4+1, 1, 10, {rand() % GAME_MAP_WIDTH, rand() % GAME_MAP_HEIGHT}, rand() % 20, 7));
    }

    addItemToInventory(createItem(itemType_pickaxe, material_platinum, itemQuality_regular));
    addItemToInventory(createItem(itemType_axe, material_platinum, itemQuality_regular));

    for (int i = 0; i < 40; i++)
    {
        int chestLocation = placeNewChest({ rand() % 20 + 10 * 10, rand() % 60 }, rand() % 4);

        for (int j = 0; j < rand() % 4 + 1; j++)
        {
            Item item = createItem(rand() % 25, rand() % 10, rand() % 7);
            if (rand() % 6 < 2)
            {
                addEnchantToItem(&item, createEnchant(rand() % 12, rand() % 3, rand() % 6));
            }
            addItemToChest(chestLocation, item);
        }
    }

    for (int i = 0; i < 120; i++)
    {
        createRoom({ rand() % 20 + 10 * 10, rand() % 60 }, { rand() % 10 + 2, rand() % 10 + 2 }, rand() % 4, rand() % 2 + 1, rand() % 4, rand() % 2 + 1, rand() % 3);
        Item item = createItem(rand() % 25, rand() % 10, rand() % 7);
        if (rand() % 6 < 2)
        {
            addEnchantToItem(&item, createEnchant(rand() % 12 + 1, rand() % 3 + 1, rand() % 6 + 1));
        }
        addItemToMap(item, { rand() % 20 + 10 * 10, rand() % 60 });
    }

    Vec2 goalRoomPos = { rand() % 110 + 10, rand() % 40 + 10 };
    createRoom({ rand() % 110 + 10, rand() % 40 + 10 }, { 5, 5 }, doorSideLeft, wallTiletype_smoothWall, material_delganium, groundTiletype_smoothGround, material_platinum);
    Vec2 startingPositon = { rand() % (GAME_MAP_WIDTH - 20) + 10, rand() % (GAME_MAP_HEIGHT - 20) + 10 };
    player.position = startingPositon;
    createRoom(startingPositon, { 5, 5 }, doorSideBottom, wallTiletype_roughWall, material_quartz, groundTiletype_smoothGround, material_cherryWood);
    createMapRectangle(startingPositon, { 3, 3 }, onWalls, createTile(material_noMaterial, wallTiletype_noWall, material_noMaterial, 0));
    addItemToMap(createItem(itemType_stolenStaff, material_delganium, itemQuality_legendary), goalRoomPos);

    wallOut();
    cleanRegisters();
}

void createTestingLevel()
{
    int chest_location = placeNewChest({ 3, 6 }, material_cherryWood); // material wood
    addItemToChest(chest_location, { 0, 1, -1 });

    for (int y = 10; y < 20; y++)
    {
        for (int x = 10; x < 20; x++)
        {
            GAME_WALLS[y * GAME_MAP_WIDTH + x].type = 1;
            GAME_WALLS[y * GAME_MAP_WIDTH + x].containedID = -1;
            GAME_WALLS[y * GAME_MAP_WIDTH + x].materialID = 0;
        }
    }
    for (int y = 25; y < 35; y++)
    {
        for (int x = 40; x < 50; x++)
        {
            GAME_WALLS[y * GAME_MAP_WIDTH + x].type = wallTiletype_roughWall;
            GAME_WALLS[y * GAME_MAP_WIDTH + x].materialID = material_dolomite;
            GAME_WALLS[y * GAME_MAP_WIDTH + x].containedID = material_gold;
        }
    }

    Item coolPick = createItem(itemType_pickaxe, material_platinum, itemQuality_pristine);
    addEnchantToItem(&coolPick, createEnchant(enchantType_efficiency, 8, 10));
    addEnchantToItem(&coolPick, createEnchant(enchantType_luck, 4, 10));
    addItemToMap(coolPick, { 10, 2 });
    addItemToMap(createItem(itemType_axe, material_platinum, itemQuality_fine), { 10, 6 });
    addItemToMap(createItem(itemType_chestplate, material_gold, itemQuality_pristine), { 15, 3 });
    addItemToMap(createItem(itemType_pickaxe, material_dolomite, itemQuality_regular), { 2, 3 });
    addItemToMap(createItem(itemType_pickaxe, material_platinum, itemQuality_regular), { 3, 3 });

    Item coolArmor = createItem(itemType_chestplate, material_platinum, itemQuality_high);
    addEnchantToItem(&coolArmor, createEnchant(enchantType_fiery, 7, 7));
    addEnchantToItem(&coolArmor, createEnchant(enchantType_teleporting, 3, 6));
    addItemToMap(coolArmor, { 30, 8 });
    coolArmor.type = itemType_helmet;
    addItemToMap(coolArmor, { 30, 9 });
    coolArmor.type = itemType_leggins;
    addEnchantToItem(&coolArmor, createEnchant(enchantType_regeneration, 4, 10));
    addItemToMap(coolArmor, { 30, 10 });
    coolArmor.type = itemType_boots;
    addItemToMap(coolArmor, { 30, 11 });
    // add some armor items and test them in the new menu

    addStructureToMap(createStructure(structureType_craftingStation, { 30, 6 }));
    addStructureToMap(createStructure(structureType_furnaceStation, { 30, 13 }));

    addItemToMap(createItem(itemType_logs, material_birchWood, itemQuality_fine), { 40, 4 });
    addItemToMap(createItem(itemType_logs, material_birchWood, itemQuality_fine), { 40, 5 });
    addItemToMap(createItem(itemType_logs, material_cherryWood, itemQuality_fine), { 40, 6 });
    addItemToMap(createItem(itemType_logs, material_birchWood, itemQuality_fine), { 40, 7 });
    addItemToMap(createItem(itemType_rock, material_flint, itemQuality_fine), { 40, 8 });

    addEntityToMap(createEntity(entityType_troll, { 40, 5 }));
    addEntityToMap(createEntity(entityType_spider, { 32, 9 }));

    addSpawner(createSpawner(entityType_goblin, 6, 0, { 12, 3 }, 3, 0));
    Item coolBottle = createItem(itemType_bottle, material_glass, itemQuality_fine);
    addEnchantToItem(&coolBottle, createEnchant(enchantType_freezing, 3, 7));
    addItemToMap(coolBottle, { 3, 2 });

    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            GAME_WALLS[(y + 20) * GAME_MAP_WIDTH + (x + 60)] = createTile(wallTiletype_roughWall, material_cherryWood, material_noMaterial, 0);
        }
    }
}

