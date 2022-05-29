//*a-> (-1 is a special value to indicate that there is no item in the slot,
// when looping through the array)

#define itemType_noItem -1
#define itemType_undefined 0 //also counts as "any"
#define itemType_axe 1
#define itemType_sword 2
#define itemType_crossbow 3
#define itemType_bolt 4
#define itemType_steak 5
#define itemType_canteen 6
#define itemType_helmet 7
#define itemType_chestplate 8
#define itemType_leggins 9
#define itemType_boots 10
#define itemType_underHelmet 11
#define itemType_underChestplate 12
#define itemType_underLeggins 13
#define itemType_underBoots 14
#define itemType_logs 15
#define itemType_gemstone 16
#define itemType_ring 17
#define itemType_metalNugget 18
#define itemType_stoneBoulder 19
#define itemType_rawFlesh 20
#define itemType_bars 21
#define itemType_bottle 22
#define itemType_coin 23
#define itemType_pickaxe 24
#define itemType_shards 25
#define itemType_roughGem 26
#define itemType_rock 27
#define itemType_shield 28

//char ITEMS_NAME_REGISTER[]; //all the names of items in the game (se we can avoid using long enum functions that take up a lot of compputin power)


#define enchantType_none 0
#define enchantType_poison 1
#define enchantType_fiery 2
#define enchantType_teleporting 3
#define enchantType_sharpness 4
#define enchantType_freezing 5
#define enchantType_regeneration 6
#define enchantType_efficiency 7
#define enchantType_luck 8
#define enchantType_protection 9
#define enchantType_clearance 10
#define enchantType_healthBoost 11
#define enchantType_vision 12
// #define enchantType_heat 9
// #define enchantType_fire_resistance 10

//registers weather or not the enchantment is a healthy and positive one or not, linked by assosciacion with the enchantType(s)
BOOL ENCHANT_POSITIVITY_REGISTER[32] = { 0, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE };

//positive enchants are the ones that the possessing entity uses at it's own advantage
//negative enchants are the ones that the possessing entity uses to attack the others
//in other words, positive enchants stay where they are while the negative are the ones being transmitted

#define isEnchantPositive(type) ENCHANT_POSITIVITY_REGISTER[type]
#define isEnchantNegative(type) !ENCHANT_POSITIVITY_REGISTER[type]

#define itemQuality_poor 1
#define itemQuality_boring 2
#define itemQuality_regular 3
#define itemQuality_fine 4
#define itemQuality_high 5
#define itemQuality_pristine 6
#define itemQuality_legendary 7

/*
    Possible items in this game:
        axes        : 1
        swords      : 2
        crossbows   : 3
        bolts       : 4
        steak       : 5
        canteen     : 6
        helmet      : 7
        chestplate  : 8
        leggins     : 9
        boots       : 10
        underHelm   : 11
        underChest  : 12
        underLegg   : 13
        underBoot   : 14
*/

typedef struct Enchantment
{
    // this also acts as effects for entites ( a sword can be fiery and an entity can be burning)
    // this struct can be treated as object rather than class
    // the game handles all enchants personally
    // enchants are differentiated only by their unique ID
    char enchantID;  // what enchant this is
    char strength;   // how poweerful it is, acts as leveler
    char certainity; 
    /*
    certainty can have multiple uses:
        when it is being attempted to apply an enchant, it represents the chance that it will be applied (if the situation allows for it) (from 0 to 10)
        when the enchant has already been applied, it represents the duration that the enchant has left (amount of steps left before the player gets rid of it automatically)
        it is ignored in any other case
    */
} Enchantment, *PEnchantment;

// Enchant colors, each Enchant has a color assosciated with it
CHAR_INFO ENCHANTS_DECOS[32] = { {'\\', 0}, {'s', Fg_Lime_Green | Bg_Green}, {char_star, Fg_Yellow | Bg_Red}, {'o', Fg_Black | Bg_White}, {char_upSlope, Fg_Grey | Bg_White}, {char_asterisc, Fg_White | Bg_Light_Blue}, {char_heart, Fg_Red | Bg_Bordeaux}, {(char)0x18, Fg_Yellow | Bg_Green}, {(WCHAR)char_udnerLinedO, Fg_Lime_Green | Bg_Yellow}, {(WCHAR)']', Fg_Light_Blue | Bg_Blue}, {(WCHAR)241, Fg_Yellow | Bg_Lime_Green}, {char_heart, Fg_Yellow | Bg_Red}, {(WCHAR)'\'', Fg_White | Bg_Dark_Blue}};
const char ITEMS_SPRITES[64] = {'0', '/', '|', char_upArrow, char_moreOrEqual, char_alpha, char_delta, '#', '#', '#', '#', '#', '#', '#', '#', char_rectangle, char_rombus, char_degree, char_asterisc, char_infinite, materialSprite_flesh, char_threeParallelLines, char_dollar, char_udnerLinedO, char_tau, (char)169, char_star, char_shiftLeft, ']'};
// Items sprites (indexed by the item types)

typedef struct Item
{
    //in case you wonder why there aren't any additional addons to the items it's because everything is calculated from:
    //material, echantment and quality : DINAMICALLY! (so there isn't even a stable ItemList that registers all possible items in game)
    int type;       // specifies what array to look at : (isSword? isFood?) *a
    int materialID; // what is it made of
    int quality;    // the higher, the better
    Enchantment enchants[maxItem_enchants];
    unsigned int props; //this depends greatly on the  item type. For example, a canteen containes water, like other containers can, 
    //props is used (in such case) to store the maximum amount of items storable and the current amount and material of items stored
} Item, *PItem;

typedef struct ChestItemContainer
{
    BOOL isUsed;                         // flag that specifies wether or not the chest is being used
    Item items[maxItems_chestContainer]; // Act as ID (pointer) to GAME_ITEMS
} ChestItemContainer, *PChestItemContainer;

typedef struct BarrelItemContainer
{
    BOOL isUsed;                          // flag that specifies wether or not the barrel is being used
    Item items[maxItems_barrelContainer]; // Act as ID (pointer) to GAME_ITEMS
} BarrelItemContainer, *PBarrelItemContainer;

Item MAP_ITEMS[maxMapItems];                 // Register for all the items in the map
ChestItemContainer MAP_CHESTS[maxChests];    // Register for all the chsts
//BarrelItemContainer MAP_BARRELS[maxBarrels]; // Register for all the barrels ::: SLATED FOR FUTURE UPDATE (chests are enough)

void assignItem(Item * destination, Item source){
    destination->materialID = source.materialID;
    destination->type = source.type;
    destination->quality = source.quality;
    destination->props = source.props;
    for (int i = 0; i < 8; i++)
    {
        destination->enchants[i].certainity = source.enchants[i].certainity;
        destination->enchants[i].enchantID = source.enchants[i].enchantID;
        destination->enchants[i].strength = source.enchants[i].strength;
    }
    
}
int getEnchantsAmountFromArray(Enchantment * enchantArray, int arrLen){
    int i = 0;
    while (i < arrLen && enchantArray[i].enchantID != enchantType_none)
    {
        i++;
    }
    return i;
}
Enchantment createEnchant(int enchantID, int strength, int effectChance){
    Enchantment tmpEnchant = {(char)enchantID, (char)strength, (char)effectChance};
    return tmpEnchant;
}
int getEnchantsAmountFromItem(Item item){
    return getEnchantsAmountFromArray(item.enchants, 8);
}
BOOL addEnchantToItem(Item * item, Enchantment enchant){
    int i = 0;
    while (i< 8 && (item->enchants[i].enchantID != enchantType_none && item->enchants[i].enchantID != enchant.enchantID))
    {
        i++;
    }
    if (i < 8)
    {
        item->enchants[i] = enchant;
        return TRUE;
    } else {
        return FALSE;
    }
}
BOOL removeEnchantFromItem(Item * item, int enchantID){
    if (enchantID >= 8 || enchantID < 0)
    {
        return FALSE;
    } else {
        item->enchants[enchantID] = createEnchant(enchantType_none, 0, 0);
    }
    return TRUE;
}
BOOL removeLastEnchantFromItem(Item * item){
    return removeEnchantFromItem(item, getEnchantsAmountFromItem(*item)-1);
}
BOOL areItemsEqual(Item item1, Item item2){
    if (item1.type == item2.type && item1.quality == item2.quality && item1.materialID == item2.materialID)
    {
        int i = 0;
        while (i<8 && item1.enchants[i].enchantID != item2.enchants[i].enchantID 
            && item2.enchants[i].strength != item1.enchants[i].strength 
            && item1.enchants[i].certainity != item2.enchants[i].certainity)
        {
            i++;
        }
        if (i<8)
        {
            return FALSE;
        } else {
            return TRUE;
        }
    }
    return FALSE;
}
void setupItems()
{
    for (int i = 0; i < maxMapItems; i++)
    {
        MAP_ITEMS[i].type = -1;
    }
    for (int i = 0; i < maxChests; i++)
    {
        for (int j = 0; j < maxItems_chestContainer; j++)
        {
            MAP_CHESTS[i].items[j].type = -1;
        }
    }
}
const char *getItemTypeFromEnum(int itemType)
{
    switch (itemType)
    {
    case itemType_axe:
        return "axe";
        break;

    case itemType_sword:
        return "sword";
        break;

    case itemType_bolt:
        return "bolt";
        break;

    case itemType_crossbow:
        return "crossbow";
        break;

    case itemType_steak:
        return "steak";
        break;

    case itemType_noItem:
        return "no item, literally void";
        break;

    case itemType_canteen:
        return "canteen";
        break;

    case itemType_helmet:
        return "helmet";
        break;

    case itemType_chestplate:
        return "chestplate";
        break;

    case itemType_leggins:
        return "leggins";
        break;

    case itemType_boots:
        return "boots";
        break;

    case itemType_underHelmet:
        return "under helmet";
        break;

        case itemType_underChestplate:
        return "under chestplate";
        break;

    case itemType_underLeggins:
        return "under leggins";
        break;

    case itemType_underBoots:
        return "under boots";
        break;

    case itemType_logs:
        return "logs";
        break;

    case itemType_gemstone:
        return "gemstone";
        break;

    case itemType_ring:
        return "ring";
        break;

    case itemType_metalNugget:
        return "nugget";
        break;
    
    case itemType_stoneBoulder:
        return "boulder";
        break;

    case itemType_rawFlesh:
        return "raw flesh";
        break;

    case itemType_bars:
        return "bars";
        break;

    case itemType_coin:
        return "coin";
        break;

    case itemType_bottle:
        return "bottle";
        break;

    case itemType_pickaxe:
        return "pickaxe";
        break;

    case itemType_shards:
        return "shards";
        break;

    case itemType_roughGem:
        return "rough gem";
        break;

    case itemType_rock:
        return "rock";
        break;

    case itemType_shield:
        return "shield";
        break;

    default:
        return "UNDEF";
        break;
    }
}
const char *getQualityTypeFromEnum(int quality)
{
    switch (quality)
    {
    case itemQuality_poor:
        return "poor";
        break;

    case itemQuality_boring:
        return "boring";
        break;

    case itemQuality_regular:
        return "regular";
        break;

    case itemQuality_fine:
        return "fine";
        break;

    case itemQuality_high:
        return "high quality";
        break;

    case itemQuality_pristine:
        return "pristine";
        break;

    case itemQuality_legendary:
        return "legendary";
        break;

    default:
        return "V-O-I-D";
        break;
    }
}
const char *getEnchantTypeFromEnum(int enchantType)
{
    switch (enchantType)
    {
    case 0:
        return "nothing"; // it means there is no enchantment whatsoever
    case 1:
        return "poison"; // poisons enemies

    case 2:
        return "fiery"; // sets foes on fire

    case 3:
        return "teleport"; // teleports enemies hit with it

    case 4:
        return "sharpness"; // adds damage to the weapon

    case 5:
        return "freeze"; // freezes the target

    case 6:
        return "regen"; // regens life

    case 7:
        return "efficiency";

    case 8:
        return "luck";

    case 9:
        return "protection";

    case 10:
        return "clearance";

    case 11:
        return "health boost";

    case 12:
        return "vision";

    default:
        return "void? what!?";
    }
}
Item createItem(int itemType, int materialID, int quality){
    Item item;
    item.type = itemType;
    item.materialID = materialID;
    item.quality = quality;
    item.props = 0;
    for (int i = 0; i < 8; i++)
    {
        item.enchants[i].enchantID = enchantType_none;
        item.enchants[i].certainity = 0;
        item.enchants[i].strength = 0;
    }
    return item;
}
void switchItems(Item * item1, Item * item2){
    Item tmpItem = *item1;
    *item1 = *item2;
    *item2 = tmpItem;
}
BOOL isItemArmor(Item item){
    if (item.type >= itemType_helmet && item.type <= itemType_underBoots)
    {
        return TRUE;
    } else  {
        return FALSE;
    }
}
Enchantment * getEnchantInItem(Item * item, int enchantID)
{
    int i = 0;
    while (i < 8 && item->enchants[i].enchantID != enchantID)
    {
        i++;
    }
    if (i < 8)
    {
        return &item->enchants[i];
    } else {
        return NULL;
    }
}
Enchantment getEnchantInItem(Item item, int enchantID)
{
    int i = 0;
    while (i < 8 && item.enchants[i].enchantID != enchantID)
    {
        i++;
    }
    if (i < 8)
    {
        return item.enchants[i];
    } else {
        return createEnchant(enchantType_none, 0, 0);
    }
}
BOOL addEnchantToArray(Enchantment enchant, Enchantment * destination)
{
    int i = 0;
    while (i < 8 && destination[i].enchantID != enchantType_none)
    {
        i++;
    }
    if (i < 8)
    {
        destination[i] = enchant;
        return TRUE;
    }
    else {
        return FALSE;
    }
}

int getChestInventoryLength(int chestId)
{
    int i = 0;
    while (i < maxItems_chestContainer && MAP_CHESTS[chestId].items[i].type != itemType_noItem)
    {
        i++;
    }
    return i;
}
int addNewChest()
{ // returns the index of the new chest, -1 if unsuccesful
    int i = 0;
    while (i < maxChests && MAP_CHESTS[i].isUsed == TRUE)
    {
        i++;
    }
    if (i < maxChests)
    {
        MAP_CHESTS[i].isUsed = TRUE;
        for (int h = 0; h < maxItems_chestContainer; h++)
        {
            MAP_CHESTS[i].items[h].type = -1;
        }

        return i;
    }
    return operation_failed;
}
BOOL addItemToChest(int location, Item item) //returns success
{
    if (location != operation_failed)
    {
        int i = 0;
        while (i < maxItems_chestContainer && MAP_CHESTS[location].items[i].type != -1)
        {
            i++;
        }
        if (i < maxItems_chestContainer)
        {
            assignItem(&MAP_CHESTS[location].items[i], item);
            return TRUE;
        }
    }
    return FALSE;
}
void removeItemFromChest(int chestId, int itemId)
{
    for (int i = itemId; i < getChestInventoryLength(chestId); i++)
    {
        assignItem(&MAP_CHESTS[chestId].items[i], MAP_CHESTS[chestId].items[i+1]);
    }
    MAP_CHESTS[chestId].items[maxItems_chestContainer-1] = createItem(itemType_noItem, 0, 0);    
}

Enchantment getEnchantFromItem(Item item, int enchantID) //returns a 0, 0, 0 enchant if nothing is found
{
    int i = 0;
    while (i < 8 && item.enchants[i].enchantID != enchantID)
    {
        i++;
    }
    if (i < 8)
    {
        return item.enchants[i];
    }
    else {
        return createEnchant(0, 0, 0);
    }
}

int findEnchantInItem(Item item, int enchantType) //returns the index of a found enchantment, if nothing is found it returns operation failed (-1)
{
    int i = 0;
    while (i < 8 && item.enchants[i].enchantID != enchantType)
    {
        i++;
    }
    if (i < 8)
    {
        return i;
    }
    else {
        return operation_failed;
    }
}
void transferPositiveEnchants(Enchantment* source, Enchantment* destination)
{
    for (int i = 0; i < 8; i++)
    {
        if (isEnchantPositive(source[i].enchantID))
            addEnchantToArray(source[i], destination);
    }
}

void transferNegativeEnchants(Enchantment* source, Enchantment* destination)
{
    for (int i = 0; i < 8; i++)
    {
        if (isEnchantNegative(source[i].enchantID))
            addEnchantToArray(source[i], destination);
    }
}
