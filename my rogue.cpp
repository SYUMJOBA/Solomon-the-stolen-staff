#include "deps/console_engine.h"

int main(int argc, char const* argv[])
{
    setupGame();

    BOOL running = TRUE;
    int GAME_CHOICE = gameState_menu;
    /*
    -1 represent "exiting"
    0 represents "menu"
    1 represents "new game"
    2 represents "load game"
    3 represents "settings"
    4 represents "credits"
    5 represents "playing"
    */
    while (running)
    {
        if (GAME_CHOICE == gameState_menu)
        {
            short menuChoice = 0;

            while (GAME_CHOICE == gameState_menu)
            {
                drawRectangle(GAME_LORE_PERGAMENE, { 30, 3 }, { 74, 22 });
                paintRectangle(Fg_Olive_Green, { 30, 3 }, { 74+30, 22+3 });
                paintLine(Fg_Black, { 30 + 74, 3 }, { 30 + 74, 22 + 3 });
                paintLine(Fg_Red, { 57, 9 }, 16);
                paintRectangle(Fg_Grey, { 38, 11 }, { 92, 20 });

                coloredText("Solomon", Fg_Red, { 2, 1 });
                coloredText("The stolen staff", Fg_Yellow, { 3, 2 });
                paintRectangle(Fg_Grey, { 5, 5 }, { 16, 5 + 8 });

                coloredText("->", Fg_Light_Blue, { 2, (short)(5 + menuChoice * 2) });
                paintLine(Fg_White, { 5, (short)(5 + menuChoice * 2) }, 10);

                paintText("New game ", { 5, 5 });
                paintText("Load game", { 5, 5 + 2 });
                paintText("Settings ", { 5, 5 + 4 });
                paintText("Credits  ", { 5, 5 + 6 });

                coloredText("Press ESC to exit", Fg_Grey, { 1, 14 });
                paintLine('|', { 20, 0 }, { 20, screen_height });

                if (Input(Key_DOWN) == key_just_pressed)
                {
                    menuChoice = clamp(0, menuChoice + 1, 3);
                }

                if (Input(Key_UP) == key_just_pressed)
                {
                    menuChoice = clamp(0, menuChoice - 1, 3);
                }

                if (Input(Key_ENTER) == key_just_released)
                {
                    GAME_CHOICE = menuChoice + 1;
                }

                if (Input(Key_ESCAPE) == key_just_pressed)
                {
                    screenCapture();
                    BOOL warningPanelRunning = TRUE;
                    int escColor = Fg_Grey;
                    int yesColor = Fg_Bordeaux;
                    while (warningPanelRunning)
                    {
                        coloredText("Are you sure you want to quit?", Fg_Grey, { 24, 10 });
                        frame(Fg_Grey, { 22, 8 }, { 55, 12 });
                        int escState = Input(Key_N);

                        if (escState == key_just_pressed)
                        {
                            escColor = Fg_White;
                        }
                        if (escState == key_just_released)
                        {
                            warningPanelRunning = FALSE;
                        }

                        int yesState = Input(Key_Y);
                        if (yesState == key_just_pressed)
                        {
                            yesColor = Fg_Red;
                        }
                        if (yesState == key_just_released)
                        {
                            warningPanelRunning = FALSE;
                            GAME_CHOICE = -1;
                            running = FALSE;
                        }

                        coloredText("EXITING THE GAME ... REALLY?", Fg_Red, { 23, 5 });
                        coloredText("Go back (n)", escColor, { 35, 11 });
                        coloredText("Yes!    (y)", yesColor, { 35, 12 });
                        updateScreen();
                    }
                    unScreenCapture();
                }

                updateScreen();
            }
        }
        else if (gameState_newGame == GAME_CHOICE)
        {
            char adventurer_name[32] = "";

            BOOL entered = FALSE;
            while (gameState_newGame == GAME_CHOICE)
            {
                coloredText("Who will be the next adventurer?", Fg_White, { 1, 2 });
                textField(adventurer_name, { 2, 3 });

                uiKeyButton("Press ENTER to confirm", Input(Key_ENTER), Fg_Green, Fg_Lime_Green, &entered, TRUE, { 2, 5 });
                uiKeyButton("Press ESCto go back", Input(Key_ESCAPE), Fg_Grey, Fg_White, &GAME_CHOICE, gameState_menu, { 2, 6 });

                if (entered)
                {
                    BOOL result = writeFileFromGame(adventurer_name);
                    while (entered)
                    {
                        if (result)
                        {
                            largeTextBox("File was created!", Fg_Lime_Green);
                            uiKeyButton("Press E to embark!", Input(Key_E), Fg_Green, Fg_Lime_Green, &GAME_CHOICE, gameState_playing, { 4, 10 });
                            entered = GAME_CHOICE == gameState_playing ? FALSE : TRUE;
                        }
                        else
                        {
                            largeTextBox("File could not be opened...", Fg_Red);
                            uiKeyButton("Press ESC to go back", Input(Key_ESCAPE), Fg_Bordeaux, Fg_Red, &entered, FALSE, { 4, 10 });
                        }
                        updateScreen();
                    }
                }
                updateScreen();
            }
        }
        else if (gameState_loadGame == GAME_CHOICE)
        {
            
            BOOL entered = FALSE;
            while (gameState_loadGame == GAME_CHOICE)
            {
                textField(GAME_FILENAME, { 3, 4 });

                coloredText("Enter the file save name", Fg_White, { 3, 2 });

                uiKeyButton("Press ENTER to embark!", Input(Key_ENTER), Fg_Green, Fg_Lime_Green, &entered, TRUE, { 2, 5 });
                uiKeyButton("Press ESC to go back", Input(Key_ESCAPE), Fg_Grey, Fg_White, &GAME_CHOICE, gameState_menu, { 2, 6 });

                if (entered)
                {
                    BOOL loadResult = loadFileInGame(GAME_FILENAME);
                    while (entered)
                    {
                        if (loadResult)
                        {
                            largeTextBox("File was found!", Fg_Lime_Green);
                            uiKeyButton("Press E to embark!", Input(Key_E), Fg_Green, Fg_Lime_Green, &GAME_CHOICE, gameState_playing, { 2, 10 });
                            entered = GAME_CHOICE == gameState_playing ? FALSE : TRUE;
                        }
                        else
                        {
                            largeTextBox("File was not found ...", Fg_Bordeaux);
                            uiKeyButton("Press ESC to go back...", Input(Key_ESCAPE), Fg_Grey, Fg_White, &entered, FALSE, { 2, 10 });
                        }
                        updateScreen();
                    }
                }

                updateScreen();
            }
        }
        else if (GAME_CHOICE == gameState_settings)
        {
            int settingChoice = 0;
            int escColor = Fg_Grey;
            while (GAME_CHOICE == 3)
            {
                coloredText("turns out this game doesn't have any settings!", Fg_White, { 3, 4 });
                coloredText("Press ESC to go to menu", escColor, { 3, 10 });
                int escState = Input(Key_ESCAPE);
                if (escState == key_just_pressed)
                {
                    escColor = Fg_White;
                }
                if (escState == key_just_released)
                {
                    GAME_CHOICE = gameState_menu;
                }

                updateScreen();
            }
        }
        else if (gameState_credits == GAME_CHOICE)
        {
            int escColor = Fg_Grey;
            int x = 3;
            int y = 3;
            while (gameState_credits == GAME_CHOICE)
            {
                coloredText("Press ESC to go to menu", escColor, { 3, 20 });
                int escState = Input(Key_ESCAPE);
                if (escState == key_just_pressed)
                {
                    escColor = Fg_White;
                }
                if (escState == key_just_released)
                {
                    GAME_CHOICE = gameState_menu;
                }

                coloredText("CREDITS", Fg_Light_Blue, { 10, 2 });
                coloredText("Game devved by syumjoba", Fg_Light_Grey, { 7, 4 });
                coloredText("The game was largely inspired by dwarf fortress", Fg_Light_Grey, { 7, 6 });
                coloredText("wich I genuinly reccomend playing as a game itself.", Fg_Light_Grey, { 7, 7 });
                coloredText("For more, you can contact me at: ", Fg_Light_Grey, { 7, 9 });
                coloredText("syumjoba@gmail.com", Fg_Light_Blue, { 10, 10 });

                coloredText("adjust the instagram logo size with 'u', 'm', 'h' and 'k' keys!", Fg_White, {50, 10});
                coloredText("(I'm serious), try it", Fg_Grey, {50, 11});
                if (x != 3 || y != 3)
                    coloredText(x == 5 && y == 3 ? "yep! you got it!" : "you're still not there ...", x == 5 && y == 3 ? Fg_Fucsia : Fg_Purple, { 50, 12 });
                drawRectangle(".___.|  -|| O ||___|", { 10, 12 }, { x, y });
                paintRectangle(Fg_Purple, { 10, 12 }, { 15, 16 });
                paintRectangle(Fg_Fucsia, { 12, 14 }, { 15, 16 });
                coloredText("Follow me on instagram: ", Fg_White, { 17, 14 });
                coloredText("@syumjoba", Fg_Fucsia, { 41, 14 });
                x += handleArrowPosition(Input(Key_H), Input(Key_K));
                y += handleArrowPosition(Input(Key_U), Input(Key_M));
                updateScreen();
            }
        }
        else if (GAME_CHOICE == gameState_playing)
        {
            // Playing
            player.position = { 5, 5 };

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

            // Enumerator for what the player is doing in the game right now
            PLAYER_ACTION = 1;
            /*
                0 : nothing (could be used for dead?)
                1 : moving
                2 : looking
                3 : attacking
                4 : inventory
            */// NOTE : everything is defined in the amazing gameplayer.h header in full detail
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
            addItemToMap(coolBottle, {3, 2});

            for (int y = 0; y < 10; y++)
            {
                for (int x = 0; x < 10; x++)
                {
                    GAME_WALLS[(y + 20) * GAME_MAP_WIDTH + (x + 60)] = createWorldTile(wallTiletype_roughWall, material_cherryWood, material_noMaterial, 0);
                }
            }

            int inventoryChoice = 0; // stores a temporary index that points to an item in the player's inventory
            int chestChoice = 0;     // stores a temporary index that points to the chest that the player is interacting with
            int craftingStructureChoice = structureType_noStructure; //since the structures do not have storage, the stored ID here is the structure TYPE.
            while (gameState_playing == GAME_CHOICE)
            {
                updatePlayerVOF();
                drawPixelInWorld({ char_filledFace, Fg_White }, player.position); // paint the player in the screen
                // registering the key states

                if (Input(Key_ESCAPE) == key_just_released)
                {
                    BOOL miniMenu = TRUE;
                    int miniMenuChoice = 0;
                    screenCapture();
                    while (miniMenu)
                    {
                        paintRectangle({ ' ', Fg_White }, { 10, 5 }, { screen_width - 10, screen_height - 5 });
                        frame(Fg_White, { 10, 5 }, { screen_width - 10, screen_height - 5 });
                        coloredText("M I N I   M E N U", Fg_Fucsia, { 16, 8 });
                        paintText("Resume game", { 14, 10 });
                        paintText("Go to stats", { 14, 12 });
                        paintText("Exit to menu", { 14, 14 });
                        paintRectangle(Fg_Grey, { 14, 10 }, { 30, 14 });
                        paintLine(Fg_White, { 14, 10 + miniMenuChoice * 2 }, 20);
                        if (Input(Key_ESCAPE) == key_just_released)
                            miniMenu = FALSE;

                        if (indexMenuArrow({ 12, 10 }, 3, &miniMenuChoice, Fg_Light_Blue))
                        {
                            switch (miniMenuChoice)
                            {
                            case 2:
                                GAME_CHOICE = gameState_menu;
                                miniMenu = FALSE;
                                break;

                            case 1:
                            {
                                BOOL sub2Running = TRUE;
                                while (sub2Running)
                                {
                                    paintRectangle({ ' ', Fg_White }, { 5, 5 }, { 32, 9 });
                                    coloredText("NIY feature, come back", Fg_Red, { 5, 5 });
                                    coloredText("later for more", Fg_Red, { 5, 6 });

                                    uiKeyButton("Press esc to EXIT", Input(Key_ESCAPE), Fg_Grey, Fg_White, &sub2Running, FALSE, { 5, 8 });
                                    updateScreen();
                                }
                            }
                            break;

                            case 0:
                                miniMenu = FALSE;
                                break;

                            default:
                                break;
                            }
                        }

                        updateScreen();
                    }
                    unScreenCapture();
                }

                // discern what are you moving for
                switch (PLAYER_ACTION)
                {
                case player_moving: // player generally going around
                {
                    Vec2 motion = calculateVec2FromKeys(Input(Key_UP), Input(Key_DOWN), Input(Key_LEFT), Input(Key_RIGHT));
                    Vec2 newPos = { player.position.X + motion.X, player.position.Y + motion.Y };
                    if (!vec2cmp(player.position, newPos))
                        if (!isPlayerSufferingFromEnchant(enchantType_freezing))
                            if (!collidesWithMap(newPos))
                            {
                                int entityID = getEntityIDFromPosition(newPos);
                                if (entityID == operation_failed)
                                {
                                    if (NULL != getSpawnerFromMapPosition(newPos))
                                    {
                                        getSpawnerFromMapPosition(newPos)->hitsTaken++;
                                    }
                                    player.position = newPos;
                                    worldStep();
                                }
                                else
                                {
                                    attackEntity(&MAP_ENTITIES[entityID]);
                                    worldStep();
                                }
                            }
                            else
                            {
                                attemptMiningWall(newPos);
                            }
                        else
                            worldStep();
                    if (Input(Key_DOT) == key_just_pressed) if (getEntityIDFromPosition(player.position) != operation_failed) attackEntity(getEntityAddressFromPosition(player.position));

                    updateMapToScreenOffset({ player.position.X - mapToScreenOffset.X, player.position.Y - mapToScreenOffset.Y });
                }
                break;

                case player_looking: // helper cursor activated, the player can peek
                {
                    {
                        int cursorSpeed = 1;
                        if (Input(Key_SHIFT))
                        {
                            cursorSpeed = 10;
                        }

                        Vec2 cursorMotion = calculateVec2FromKeys(Input(Key_UP), Input(Key_DOWN), Input(Key_LEFT), Input(Key_RIGHT));
                        if (getVismapTile(cursorHelper.position.X + cursorMotion.X * cursorSpeed, cursorHelper.position.Y + cursorMotion.Y * cursorSpeed) == vismap_tileInView)
                        {
                            cursorHelper.position.X += cursorMotion.X * cursorSpeed;
                            cursorHelper.position.Y += cursorMotion.Y * cursorSpeed;
                        }

                        cursorHelper.position = clampPosition(mapToScreenOffset, cursorHelper.position, { mapToScreenOffset.X + screen_width - 1, mapToScreenOffset.Y + screen_height - 1 });
                        interrogateMapLocation(cursorHelper.position);
                        drawPixelInWorld({ 'X', Fg_Yellow }, cursorHelper.position);
                    }
                }
                break;
                case player_inInventory:
                {
                    while (PLAYER_ACTION == player_inInventory)
                    {
                        int d_keyState = Input(Key_D);
                        int f_keyState = Input(Key_F);
                        int n_keyState = Input(Key_N);
                        int h_keyState = Input(Key_H);
                        int inventoryLength = getPlayerInventoryLength();
                        paintRectangle({ ' ', Fg_Grey }, { 5, 5 }, { screen_width - 5, screen_height - 5 });
                        frame(Fg_White, { 5, 5 }, { screen_width - 5, screen_height - 5 });

                        coloredText("I N V E N T O R Y", Fg_Lime_Green, { 13, 6 });
                        coloredText("E Q U I P M E N T", Fg_Lime_Green, { 60, 6 });
                        uiKeyButton("Q to go in equip menu", Input(Key_Q), Fg_Grey, Fg_White, &PLAYER_ACTION, player_equipMenu, { 60, screen_height - 6 });
                        uiKeyButton("H to hold the item", h_keyState, Fg_Grey, Fg_White, NULL, 0, { 60, screen_height - 7 });
                        uiKeyButton("N to unhold the held item", n_keyState, Fg_Grey, Fg_White, NULL, 0, { 60, screen_height - 8 });
                        uiKeyButton("F to equip the item", f_keyState, Fg_Grey, Fg_White, NULL, 0, { 60, screen_height - 9 });
                        uiKeyButton("D to drop the item", d_keyState, Fg_Grey, Fg_White, NULL, 0, { 60, screen_height - 10 });

                        if (n_keyState == key_just_released)
                            if (addItemToInventory(player.rightHand))
                                player.rightHand = createItem(itemType_noItem, 0, 0);
                        if (h_keyState == key_just_released)
                            holdItemInHand(inventoryChoice);
                        if (f_keyState == key_just_released)
                            equipItem(inventoryChoice);
                        if (d_keyState == key_just_released)
                            dropItemOnGrund(inventoryChoice);

                        printEquipmentItems({ 60, 7 });
                        if (inventoryLength == 0)
                        {
                            coloredText("No items in inventory", Fg_White, { 7, 7 });
                        }
                        else
                        {
                            int enter_keyState = Input(Key_ENTER);
                            displayItemArray(player.inventory, maxItems_inventory, { 9, 7 }, 12, inventoryChoice / 12);
                            uiKeyButton("->", enter_keyState, Fg_Purple, Fg_Fucsia, NULL, 0, { 7, 7 + inventoryChoice % 12 });
                            inventoryChoice += handleInstantArrowPosition(Input(Key_UP), Input(Key_DOWN));
                            inventoryChoice = clamp(0, inventoryChoice, inventoryLength - 1);

                            if (enter_keyState == key_just_released)
                            {
                                PLAYER_ACTION = player_peekingItem;
                                Item* peekingItem = &player.inventory[inventoryChoice];

                                while (PLAYER_ACTION == player_peekingItem)
                                {
                                    int f_keyState = Input(Key_F);
                                    int d_keyState = Input(Key_D);
                                    int h_keyState = Input(Key_H);
                                    int u_keyState = Input(Key_U);

                                    blankWindow({ 7, 7 }, { screen_width - 7, screen_height - 7 });

                                    coloredText("-", Fg_Lime_Green, { 9, screen_height - 8 });
                                    coloredText("-", Fg_Lime_Green, { 9, screen_height - 9 });
                                    coloredText("-", Fg_Lime_Green, { 9, screen_height - 10 });
                                    coloredText("-", Fg_Lime_Green, { 9, screen_height - 11 });
                                    coloredText("-", Fg_Lime_Green, { 9, screen_height - 12 });
                                    coloredText("-", Fg_Lime_Green, { 9, screen_height - 13 });
                                    uiKeyButton("ESC to go back", Input(Key_ESCAPE), Fg_Grey, Fg_White, &PLAYER_ACTION, player_inInventory, { 10, screen_height - 8 });
                                    uiKeyButton("D to drop item", d_keyState, Fg_Grey, Fg_White, &PLAYER_ACTION, player_moving, { 10, screen_height - 9 });
                                    uiKeyButton("I to interact with item", Input(Key_I), Fg_Grey, Fg_White, &PLAYER_ACTION, player_interactingWithItem, { 10, screen_height - 10 });
                                    uiKeyButton("F to equip the item", f_keyState, Fg_Grey, Fg_White, &PLAYER_ACTION, player_inInventory, { 10, screen_height - 11 }); // change it later to player_inInventory to see how the UI reponds
                                    uiKeyButton("H to hold the item", h_keyState, Fg_Grey, Fg_White, &PLAYER_ACTION, player_inInventory, { 10, screen_height - 12 });  // change it later to player_inInventory to see how the UI reponds
                                    uiKeyButton("U to use the item", u_keyState, Fg_Grey, Fg_Water_Green, NULL, 0, { 10, screen_height - 13 });

                                    if (key_just_released == f_keyState)
                                        equipItem(inventoryChoice);
                                    if (key_just_released == h_keyState)
                                        holdItemInHand(inventoryChoice);
                                    if (key_just_pressed == u_keyState)
                                        useItemInInventory(inventoryChoice);

                                    showItemFullName(*peekingItem, { 10, 8 });
                                    paintPixel(ITEMS_SPRITES[peekingItem->type], { 8, 8 });
                                    paintPixel(toFgColor(GAME_MATERIALS[peekingItem->materialID].color), { 9, 8 });
                                    coloredText("  name              lvl  chance", Fg_Grey, { screen_width - 40, 8 });
                                    displayItemEnchantInfo(*peekingItem, { screen_width - 40, 9 });
                                    if (d_keyState == key_just_released)
                                        dropItemOnGrund(inventoryChoice);

                                    if (PLAYER_ACTION == player_interactingWithItem)
                                    {
                                        while (PLAYER_ACTION == player_interactingWithItem)
                                        {
                                            uiKeyButton("NIY feature, come back onther time", Input(Key_ESCAPE), Fg_Bordeaux, Fg_Red, &PLAYER_ACTION, player_peekingItem, { 10, 10 });
                                            updateScreen();
                                        }
                                    }

                                    updateScreen();
                                }
                            }
                        }
                        if (Input(Key_ESCAPE) == key_just_released || Input(Key_E) == key_just_released)
                        {
                            PLAYER_ACTION = player_moving;
                        }
                        updateScreen();
                    }
                }
                unScreenCapture();
                break;
                case player_equipMenu:
                {
                    screenCapture();
                    int equipChoice = 0;
                    Item tempNullItem = createItem(itemType_noItem, 0, 0);
                    Item* displayingInfoItem;
                    while (PLAYER_ACTION == player_equipMenu)
                    {
                        int f_keyState = Input(Key_F);
                        blankWindow({ 5, 5 }, { screen_width - 5, screen_height - 5 });
                        coloredText("E Q U I P   M E N U", Fg_Lime_Green, { 20, 6 });

                        printEquipmentItems({ 10, 10 });
                        uiKeyButton("Press ESC to go back", Input(Key_ESCAPE), Fg_Green, Fg_Lime_Green, &PLAYER_ACTION, player_inInventory, { 70, screen_height - 7 });
                        // menu arrow, choice and so on
                        if (Input(Key_UP) == key_just_released && equipChoice > 0)
                            equipChoice--;
                        if (Input(Key_DOWN) == key_just_released && equipChoice < 9)
                            equipChoice++;

                        coloredText("->", Fg_Red, { 8, 10 + equipChoice + (equipChoice / 4) });
                        uiKeyButton("Press F to unequip item", f_keyState, Fg_Grey, Fg_White, NULL, 0, { 15, 23 });

                        displayingInfoItem = getPlayerSlot(equipChoice <= 7 ? equipChoice + 7 : equipChoice - 7);

                        if (f_keyState == key_just_pressed)
                            unEquipItem(equipChoice <= 7 ? equipChoice + 7 : equipChoice - 7);

                        if (displayingInfoItem->type != itemType_noItem)
                        {
                            showItemInfo(*displayingInfoItem, { 70, 10 });
                            displayEnchantInfo(displayingInfoItem->enchants, { 70, 12 }, 8);
                        }
                        else
                        {
                            coloredText("No item to show", Fg_Grey, { 70, 10 });
                        }

                        updateScreen();
                    }
                }
                break;
                case player_inChestMenu:
                {
                    int chestInventoryChoice = 0;
                    int playerInventoryChoice = 0;
                    int sideChosen = 0; // if the player chose the inventory arrow or the chest arrow;
                    /*
                        0 : chest
                        1 : inventory
                    */
                    while (player_inChestMenu == PLAYER_ACTION)
                    {

                        int escape_keyState = Input(Key_ESCAPE);
                        int c_keyState = Input(Key_C);
                        int enter_keyState = Input(Key_ENTER);
                        int left_keyState = Input(Key_LEFT);
                        int right_keyState = Input(Key_RIGHT);
                        int up_keyState = Input(Key_UP);
                        int down_keyState = Input(Key_DOWN);
                        int chestItemsAmount = getChestInventoryLength(chestChoice);
                        int playerItemsAmount = getPlayerInventoryLength();
                        blankWindow({ 5, 5 }, { screen_width - 5, screen_height - 5 });
                        coloredText("C H E S T", Fg_Lime_Green, { 10, 6 });
                        coloredText("I N V E N T O R Y", Fg_Lime_Green, { screen_width - 50, 6 });

                        displayItemArray(MAP_CHESTS[chestChoice].items, maxItems_chestContainer, { 10, 8 }, 12, chestInventoryChoice / 12);
                        displayItemArray(player.inventory, maxItems_inventory, { screen_width - 50, 8 }, 12, playerInventoryChoice / 12);

                        uiKeyButton("press ESC or C to go back", max(c_keyState, escape_keyState), Fg_Green, Fg_Lime_Green, NULL, 0, { 10, screen_height - 6 }); //È IN QUESTO ISTANTE CHE SONO DIVENTATO ZIO
                        sideChosen == 0 ? uiKeyButton("press ENTER to trasfer to inventory", enter_keyState, Fg_Grey, Fg_White, NULL, 0, { 10, screen_height - 7 }) : uiKeyButton("press ENTER to trasfer to chest", enter_keyState, Fg_Grey, Fg_White, NULL, 0, { screen_width - 50, screen_height - 7 });

                        if (escape_keyState == key_just_released || c_keyState == key_just_released)
                            PLAYER_ACTION = player_moving;
                        uiKeyButton("<-", left_keyState, Fg_Grey, Fg_White, NULL, 0, { 55, screen_height - 9 });
                        uiKeyButton("->", right_keyState, Fg_Grey, Fg_White, NULL, 0, { screen_width - 55, screen_height - 9 });
                        if (left_keyState == key_just_pressed && sideChosen == 1)sideChosen = 0;
                        if (right_keyState == key_just_pressed && sideChosen == 0) sideChosen = 1;

                        if (up_keyState == key_just_pressed) sideChosen == 0 ? chestInventoryChoice-- : playerInventoryChoice--;
                        if (down_keyState == key_just_pressed) sideChosen == 0 ? chestInventoryChoice++ : playerInventoryChoice++;

                        chestInventoryChoice = clamp(0, chestInventoryChoice, chestItemsAmount - 1);
                        playerInventoryChoice = clamp(0, playerInventoryChoice, playerItemsAmount - 1);

                        sideChosen == 0 ?
                            chestItemsAmount == 0 ? coloredText("No items to pick here", Fg_Grey, { 8, 7 }) : uiKeyButton("->", enter_keyState, Fg_Purple, Fg_Fucsia, NULL, 0, { 8, 8 + chestInventoryChoice % 12 })
                            :
                            playerItemsAmount == 0 ? coloredText("No items to pick here", Fg_Grey, { screen_width - 52, 7 }) : uiKeyButton("->", enter_keyState, Fg_Purple, Fg_Fucsia, NULL, 0, { screen_width - 52, playerInventoryChoice % 12 + 8 });


                        if (enter_keyState == key_just_pressed)
                            if (sideChosen == 0)
                            {
                                if (moveItemFromChestToInventory(chestChoice, chestInventoryChoice))
                                    playerInventoryChoice = getPlayerInventoryLength();
                            }
                            else
                            {
                                if (moveItemFromInventoryToChest(chestChoice, playerInventoryChoice))
                                    chestInventoryChoice = getChestInventoryLength(chestChoice);
                            }
                        updateScreen();
                    }
                }
                break;
                case player_building:
                {
                    screenCapture();
                    int enter_keyState;
                    int buildCategoryChoice = 0;
                    while (PLAYER_ACTION == player_building)
                    {
                        enter_keyState = Input(Key_ENTER);
                        blankWindow({ 5, 5 }, { screen_width - 5, screen_height - 5 });
                        coloredText("B U I L D I N G", Fg_Lime_Green, { 8, 5 });

                        buildCategoryChoice += handleArrowPosition(Input(Key_UP), Input(Key_DOWN));
                        buildCategoryChoice = clamp(0, buildCategoryChoice, 1);

                        coloredText("Choose building category", Fg_Grey, { 6, 6 });
                        coloredText("Structures", Fg_Grey, { 10, 8 });
                        coloredText("Walls and building", Fg_Grey, { 10, 9 });
                        uiKeyButton("->", enter_keyState, Fg_Purple, Fg_Fucsia, NULL, 0, { 7, 8 + buildCategoryChoice });
                        if (enter_keyState == key_just_released) {
                            int itemBuildingChoice = 0;
                            if (buildCategoryChoice > 0) buildCategoryChoice = 3;
                            int recipesLength = getRecipesLength(buildCategoryChoice);
                            while (buildCategoryChoice > -1)
                            {
                                Attribute color = canListCraftItem(player.inventory, getPlayerInventoryLength(), GAME_CRAFTING_RECIPES[buildCategoryChoice][itemBuildingChoice]) ? Fg_White : Fg_Red;
                                enter_keyState = Input(Key_ENTER);
                                blankWindow({ 5, 5 }, { screen_width - 5, screen_height - 5 });
                                displayCraftingRecipes(buildCategoryChoice, { 10, 8 }, itemBuildingChoice / 12, 12, player.inventory, getPlayerInventoryLength());
                                itemBuildingChoice += handleArrowPosition(Input(Key_UP), Input(Key_DOWN));
                                itemBuildingChoice = clamp(0, itemBuildingChoice, recipesLength - 1);
                                coloredText("->", Fg_Fucsia, { 8, 8 + itemBuildingChoice % 12 });
                                paintLine(color, { 10, 8 + itemBuildingChoice % 12 }, { 40, 8 + itemBuildingChoice % 12 });
                                displayCraftingRecipeIngredientsWHints(GAME_CRAFTING_RECIPES[buildCategoryChoice][itemBuildingChoice], { screen_width - 70, 8 });
                                uiKeyButton("Press ESC to go back", Input(Key_ESCAPE), Fg_Green, Fg_Lime_Green, &buildCategoryChoice, -1, { 7, screen_height - 8 });
                                uiKeyButton(color == Fg_White ? "Press ENTER to build" : "You lack materials", enter_keyState, color == Fg_White ? Fg_Green : Fg_Bordeaux, color == Fg_White ? Fg_Lime_Green : Fg_Red, NULL, 0, { screen_width - 30, screen_height - 8 });

                                if (enter_keyState && color == Fg_White)
                                {
                                    if (canBuildStructureInMapPosition(player.position))
                                    {
                                        addStructureToMap(createStructure(GAME_CRAFTING_RECIPES[buildCategoryChoice][itemBuildingChoice].resultID, player.position));
                                        removeRecipeItemsFromPlayer(GAME_CRAFTING_RECIPES[buildCategoryChoice][itemBuildingChoice]);
                                    }
                                }
                                updateScreen();
                            }
                        }

                        uiKeyButton("Press ESC to go back", Input(Key_ESCAPE), Fg_Green, Fg_Lime_Green, &PLAYER_ACTION, player_moving, { 7, screen_height - 8 });
                        updateScreen();
                    }
                    unScreenCapture();
                }
                break;

                case player_crafting:
                    screenCapture();
                    while (player_crafting == PLAYER_ACTION)
                    {

                        updateScreen();
                    }
                    unScreenCapture();
                    break;

                case player_interacting:
                    screenCapture();
                    //go through all the present structures in the map, and if the player is in one of them (exactly in the center) then open the 
                    //specified crafting menu for that structure specifically 
                    while (PLAYER_ACTION == player_interacting)
                    {

                        updateScreen();
                    }
                    unScreenCapture();
                    break;


                default:
                    break;
                }

                if (Input(Key_L) == key_just_released)
                {
                    cursorHelper.position = player.position;
                    if (PLAYER_ACTION == player_looking)
                    {
                        PLAYER_ACTION = player_moving;
                    }
                    else
                    {
                        PLAYER_ACTION = player_looking;
                    }
                }

                if (Input(Key_E) == key_just_released)
                {
                    PLAYER_ACTION = player_inInventory;
                    screenCapture();
                }

                if (Input(Key_P) == key_just_pressed) pickUpItemFromGround();


                if (Input(Key_C) == key_just_released)
                {
                    if (GAME_WALLS[player.position.X + player.position.Y * GAME_MAP_WIDTH].type == wallTiletype_chest)
                    {
                        chestChoice = GAME_WALLS[player.position.X + player.position.Y * GAME_MAP_WIDTH].containedID;
                        PLAYER_ACTION = player_inChestMenu;
                        screenCapture();
                    }
                }

                if (Input(Key_B) == key_just_released) PLAYER_ACTION = player_building;
                if (Input(Key_X) == key_just_released) PLAYER_ACTION = player_crafting;
                if (Input(Key_U) == key_just_released) {

                }

                if (player.health <= 0)
                {
                    gameOver();
                }


                switchValue(Input(Key_H), &shouldRender_hintsUI);

                if (shouldRender_hintsUI) renderhintsUI();
                showLastAnnouncement();
                updateScreen();
                renderPlayerPerspective();
            }
        }
    }
    return 0;
}
