#pragma once

// don't sue me mojang :)

typedef struct Player
{
    int health;
    int maxHealth;
    int baseMaxHealth;
    Vec2 position;
    // also add the addon characteristics to link with the Inventory
    Item inventory[maxItems_inventory];
    Item leftHand;  // pointer to value in inventory, -1 represents nothing
    Item rightHand; // pointer to value in inventory, -1 represenst nothing
    // something superior to 19 represents holding something not present in the inventory within your hands.
    // In this case, to get the index (that points directly in GAME_ITEMS) you just have to subtract 19
    Item head;
    Item torso;
    Item leggins;
    Item boots; // all of these are pointers EXCLUSIVELY allowed to point in inventory

    Item underHead;
    Item underTorso;
    Item underLeggins;
    Item underBoots;
    //-1 represents "unoccupied"

    // int temperature /*I really want to add things like temperatures here*/
    //float fullness; // respective to food, how filled the players stomach is? (max: 20)
    //float thirst;
    // regular armor is stuff like jackets, wide shirts and other NON adherent wearables
    // under clothing is stuff like shirts, cloth socks and hoodies ... and so on

    Enchantment sufferingEnchants[8];
} Player, *PPlayer;

Player player;


#define vismap_tileUndiscovered 0
#define vismap_tileSeen 1 
#define vismap_tileInView 2
int PLAYER_VISMAP[GAME_MAP_HEIGHT * GAME_MAP_WIDTH];

void setupPlayer()
{
    for (int i = 0; i < 20; i++)
    {
        player.inventory[i] = createItem(itemType_noItem, material_noMaterial, itemQuality_legendary );
    }
    player.boots.type = itemType_noItem;
    player.leggins.type = itemType_noItem;
    player.torso.type = itemType_noItem;
    player.head.type = itemType_noItem;

    player.underBoots.type = itemType_noItem;
    player.underLeggins.type = itemType_noItem;
    player.underTorso.type = itemType_noItem;
    player.underHead.type = itemType_noItem;

    player.leftHand.type = itemType_noItem;
    player.rightHand.type = itemType_noItem;

    //player.fullness = 20;
    //player.thirst = 20;
    player.maxHealth = 100;
    player.health = 70;
    player.baseMaxHealth = 100;

    for (int i = 0; i < 8; i++)
    {
        player.sufferingEnchants[i] = createEnchant(enchantType_none, 0, 0);
    }

    for (int i = 0; i < GAME_MAP_HEIGHT*GAME_MAP_WIDTH; i++)
    {
        PLAYER_VISMAP[i] = vismap_tileUndiscovered;
    }

}

// in the inventory, all the items are always crushed to starting point of the inventory array
int getPlayerInventoryLength()
{
    int i = 0;
    while (i < maxItems_inventory && player.inventory[i].type != itemType_noItem)
    {
        i++;
    }
    return i;
}
void removeItemFromInventory(int id) // removes the item located at that position in the inventory
{
    if (id == maxItems_inventory - 1)
    {
        player.inventory[id] = createItem(itemType_noItem, material_noMaterial, itemQuality_legendary);
    }
    else {
        for (int i = id; i < getPlayerInventoryLength(); i++)
        {
            assignItem(&player.inventory[i], player.inventory[i + 1]);
        }
    }
}
int findItemFromInventory(Item item)
{
    int i = 0;
    while (i < getPlayerInventoryLength() && !areItemsEqual(player.inventory[i], item))
    {
        i++;
    }
    return i;
}
BOOL addItemToInventory(Item item) // return TRUE if operation is succesfull, FALSE if
{
    int invLen = getPlayerInventoryLength();
    if (invLen < maxItems_inventory)
    {
        player.inventory[invLen] = item;
        return TRUE;
        if (invLen != maxItems_inventory - 1)
            player.inventory[invLen + 1] = createItem(itemType_noItem, material_noMaterial, 0);
    }
    else
    {
        return FALSE;
    }
}

#define playerSlot_leftHand 1
#define playerSlot_rightHand 2
#define playerSlot_helmet 7           //
#define playerSlot_chestplate 8       // - - - - - - - - - - - - - - - - - - - - - -
#define playerSlot_leggins 9          //
#define playerSlot_boots 10           // I purposefully made the armor type IDs the same as the player's (No I don't think I will)
#define playerSlot_underHelmet 11     //
#define playerSlot_underChestplate 12 // - - - - - - - - - - - - - - - - - - - - - -
#define playerSlot_underLeggins 13    //
#define playerSlot_underBoots 14      //

Item *getPlayerSlot(int slot) // future idea : rather than have this huge enumerator, player slots should all be block in an array, and the IDS are the correspondent value
{
    switch (slot)
    {
    case playerSlot_leftHand:
        return &player.leftHand;
        break;

    case playerSlot_rightHand:
        return &player.rightHand;
        break;

    case playerSlot_helmet:
        return &player.head;
        break;

    case playerSlot_chestplate:
        return &player.torso;
        break;

    case playerSlot_leggins:
        return &player.leggins;
        break;

    case playerSlot_boots:
        return &player.boots;
        break;

    case playerSlot_underHelmet:
        return &player.underHead;
        break;

    case playerSlot_underChestplate:
        return &player.underTorso;
        break;

    case playerSlot_underLeggins:
        return &player.underLeggins;
        break;

    case playerSlot_underBoots:
        return &player.underBoots;
        break;

    default:
        return NULL;
        break;
    }
}

BOOL isPlayerEquippingInSlot(int slot)
{
    if (getPlayerSlot(slot)->type == itemType_noItem)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
BOOL isSlotArmor(int slotID) // cecks if specified slot is armor related
{
    if (slotID >= itemType_helmet && slotID <= itemType_underBoots)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
BOOL equipItemInSlot(int id, int slot) // moves an item from the player's inventory to the right hand slot
{
    if (isSlotArmor(slot)) // slot corresponds to armor, not in the slot definitions
    {
        if (player.inventory[id].type == slot)
        {
            switchItems(getPlayerSlot(slot), &player.inventory[id]);
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        switchItems(getPlayerSlot(slot), &player.inventory[id]);
        return TRUE;
    }
}
BOOL equipItem(int inventoryId)
{ // basically a smart version of equipItemInSlot that automatically understands the slot
    if (isItemArmor(player.inventory[inventoryId]))
    {
        if (getPlayerSlot(player.inventory[inventoryId].type)->type != itemType_noItem)
        {
            switchItems(&player.inventory[inventoryId], getPlayerSlot(player.inventory[inventoryId].type));
        }
        else
        {
            if (inventoryId == getPlayerInventoryLength() - 1)
            {
                switchItems(&player.inventory[inventoryId], getPlayerSlot(player.inventory[inventoryId].type));
            }
            else
            {
                assignItem(getPlayerSlot(player.inventory[inventoryId].type), player.inventory[inventoryId]);
                removeItemFromInventory(inventoryId);
            }
        }
        return TRUE;
    }
    else
    {
        if (player.leftHand.type == itemType_noItem)
        {
            if (inventoryId == getPlayerInventoryLength() - 1)
            {
                switchItems(&player.leftHand, &player.inventory[inventoryId]);
            }
            else
            {
                player.leftHand = player.inventory[inventoryId];
                removeItemFromInventory(inventoryId);
            }
        }
        else
        {
            switchItems(&player.leftHand, &player.inventory[inventoryId]);
        }
    }
    return TRUE;
}
BOOL holdItemInHand(int inventoryId)
{
    if (player.rightHand.type == itemType_noItem)
    {
        if (inventoryId == getPlayerInventoryLength() - 1)
        {
            switchItems(&player.rightHand, &player.inventory[inventoryId]);
        }
        else
        {
            player.rightHand = player.inventory[inventoryId];
            removeItemFromInventory(inventoryId);
        }
    }
    else
    {
        switchItems(&player.rightHand, &player.inventory[inventoryId]);
    }
    return TRUE;
}
BOOL unEquipItem(int slot) // takes in the slot and attempts moving the item from the slot to the inventory
{
    if (getPlayerInventoryLength() < maxItems_inventory)
    {
        switchItems(&player.inventory[getPlayerInventoryLength()], getPlayerSlot(slot));
        return TRUE;
    }
    return FALSE;
}
int getInventoryItemAmountOf(Item item) //compares the given item with all of the inventory and returns the amount
{
    int amount = 0;
    int i = 0;
    for (int i = 0; i < getPlayerInventoryLength(); i++)
    {
        if (player.inventory[i].type == item.type && player.inventory[i].materialID == item.materialID)
        {
            amount ++;
        }
    }
    return amount;
}
BOOL removeItemFromInventory(Item item) //removes the first occurrency of such item in the inventory
{
    int i = 0;
    while (i < getPlayerInventoryLength())
    {
        if (player.inventory[i].type != item.type && player.inventory[i].materialID != item.materialID)
        {
            i ++;
        }
        
    }
    if (i < getPlayerInventoryLength())
    {
        removeItemFromInventory(i);
        return TRUE;
    } else {
        return FALSE;
    }
}
int getInventoryItemsAmountOfType(int type)
{
    int amount = 0;
    int i = 0;
    for (int i = 0; i < getPlayerInventoryLength(); i++)
    {
        if (player.inventory[i].type == type)
        {
            amount ++;
        }
        
    }
    return amount;
}

BOOL addEnchantToPlayer(Enchantment enchant)
{
    int i = 0;
    while ((player.sufferingEnchants[i].enchantID != enchantType_none || player.sufferingEnchants[i].enchantID == enchant.enchantID) && i < 8)
    {
        i++;
    }
    if (i < 8)
    {
        player.sufferingEnchants[i] = enchant;
        return TRUE;
    }
    else {
        return FALSE;
    }
}

Enchantment findEnchantInPlayer(int enchantType)
{
    int i = 0;
    while (i < 8 && player.sufferingEnchants[i].enchantID != enchantType)
    {
        i++;
    }
    if (i < 8)
    {
        return player.sufferingEnchants[i];
    }
    else {
        if (player.head.type != itemType_noItem && findEnchantInItem(player.head, enchantType) != operation_failed)
        {
            return player.head.enchants[findEnchantInItem(player.head, enchantType)];
        }
        else if (player.torso.type != itemType_noItem && findEnchantInItem(player.torso, enchantType) != operation_failed)
        {
            return player.torso.enchants[findEnchantInItem(player.torso, enchantType)];
        }
        else if (player.leggins.type != itemType_noItem && findEnchantInItem(player.leggins, enchantType) != operation_failed)
        {
            return player.leggins.enchants[findEnchantInItem(player.leggins, enchantType)];
        } else if (player.boots.type != itemType_noItem && findEnchantInItem(player.boots, enchantType) != operation_failed)
        {
            return player.boots.enchants[findEnchantInItem(player.boots, enchantType)];
        }
    }
    return createEnchant(enchantType_none, 0, 0);
}
BOOL isPlayerSufferingFromEnchant(int enchantType)
{
    int i = 0;
    while (player.sufferingEnchants[i].enchantID != enchantType && i < 8)
        i++;
    return i < 8;
}
int getPlayerEnchantPowerSum(int enchantType)
{
    int amount = 0;
    amount += getEnchantFromItem(player.rightHand, enchantType).strength;
    amount += getEnchantFromItem(player.leftHand, enchantType).strength;
    amount += getEnchantFromItem(player.head, enchantType).strength;
    amount += getEnchantFromItem(player.torso, enchantType).strength;
    amount += getEnchantFromItem(player.leggins, enchantType).strength;
    amount += getEnchantFromItem(player.boots, enchantType).strength;
    amount += getEnchantFromItem(player.underHead, enchantType).strength;
    amount += getEnchantFromItem(player.underTorso, enchantType).strength;
    amount += getEnchantFromItem(player.underLeggins, enchantType).strength;
    amount += getEnchantFromItem(player.underBoots, enchantType).strength;
    amount += findEnchantInPlayer(enchantType).strength;
    return amount;
}
