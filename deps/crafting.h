
typedef struct ItemRepresentation
{
    unsigned int flagsRequired;
    int itemType;
}ItemRepresentation, *PItemRepresentation;

ItemRepresentation createRepresentation(unsigned int flags, int itemType){
    ItemRepresentation tmpRepr;
    tmpRepr.itemType = itemType;
    tmpRepr.flagsRequired = flags;
    return tmpRepr;
}

typedef struct CraftingRecipe
{
    int resultID; //Naturally indicating an item/structure/walltype etc... as result
    char name[32];
    ItemRepresentation recipe[4];
    int amounts[4];
} CraftingRecipe, *PCraftingRecipe;

//SmeltingRecipe is useless as furnace just breaks down nuggets into metal

#define craftingCategory_structures 0
#define craftingCategory_handmade 1
#define craftingCategory_craftbench 2
#define craftingCategory_building 3
#define maxRecipes 24

CraftingRecipe * GAME_CRAFTING_RECIPES[4]; //central register containing all the information necessary for the crafting recipes
CraftingRecipe RECIPES_STRUCTURES[maxRecipes];
CraftingRecipe RECIPES_HANDMADE[maxRecipes];
CraftingRecipe RECIPES_CRAFTBENCH[maxRecipes];
CraftingRecipe RECIPES_BUILDING[maxRecipes];


BOOL isRepresentationMatching(Item item, ItemRepresentation representation)
{
    if ( (representation.flagsRequired & GAME_MATERIALS[item.materialID].flags) == representation.flagsRequired && (item.type == representation.itemType || representation.itemType == itemType_undefined))
    {
        return TRUE;
    }
    return FALSE;
}

int getRepresentationMatchingItemsAmountInList(Item * itemList, int listMaxLength, ItemRepresentation representation)
{
    int amount = 0;
    for (int i = 0; i < listMaxLength; i++)
    {
        if (isRepresentationMatching(itemList[i], representation))
        {
            amount++;
        }
    }
    return amount;
}

BOOL isMatchingItemContained(Item * itemList, int listLen, ItemRepresentation representation)
{
    int i = 0;
    while (i < listLen && !isRepresentationMatching(itemList[i], representation))
    {
        i++;
    }
    if (i < listLen)
    {
        return TRUE;
    }
    return FALSE;
}

int findMatchingItem(Item * itemList, int listLen, ItemRepresentation representation){
    int i = 0;
    while ( i < listLen && !isRepresentationMatching(itemList[i], representation))
    {
        i++;
    }
    if (i < listLen){
        return i;
    } else {
        return operation_failed;
    }
}

BOOL canListCraftItem(Item * itemList, int listMaxLength, CraftingRecipe recipe)
{
    int representationID = 0;
    while (
        representationID < 4 && 
        recipe.recipe[representationID].itemType != itemType_noItem 
        && (recipe.amounts[representationID] > 0 ? 
            getRepresentationMatchingItemsAmountInList(itemList, listMaxLength, recipe.recipe[representationID]) >= recipe.amounts[representationID] : 
            isMatchingItemContained(itemList, listMaxLength, recipe.recipe[representationID]))
        )
    {
        representationID++;
    }
    if ((recipe.recipe[representationID].itemType == itemType_noItem || representationID == listMaxLength) && listMaxLength != 0)
    {
        return TRUE;
    }
    return FALSE;
}

CraftingRecipe createCraftingRecipe(const char * name, int resultID, ItemRepresentation firsrRecipeItem, int firstItemAmount)
{
    CraftingRecipe tmpRecipe;
    tmpRecipe.resultID = resultID;
    strcpy(tmpRecipe.name, name);
    for (int i = 0; i < 4; i++)
    {
        tmpRecipe.recipe[i].itemType = itemType_noItem;
        tmpRecipe.amounts[i] = 0;
    }
    
    tmpRecipe.recipe[0] = firsrRecipeItem;
    tmpRecipe.amounts[0] = firstItemAmount;  
    return tmpRecipe;  
}

BOOL addRecipeItem(CraftingRecipe * craftingRecipe, ItemRepresentation representation, int itemAmount){
    int i = 0;
    while (i < 4 && craftingRecipe->recipe[i].itemType != itemType_noItem)
    {
        i++;
    }
    if (i < 4)
    {
        craftingRecipe->recipe[i] = representation;
        craftingRecipe->amounts[i] = itemAmount;
        return TRUE;
    }
    return FALSE;
}

void setupCrafting()
{
    GAME_CRAFTING_RECIPES[craftingCategory_structures]  = RECIPES_STRUCTURES;
    GAME_CRAFTING_RECIPES[craftingCategory_handmade]    = RECIPES_HANDMADE  ;
    GAME_CRAFTING_RECIPES[craftingCategory_craftbench]  = RECIPES_CRAFTBENCH;
    GAME_CRAFTING_RECIPES[craftingCategory_building]    = RECIPES_BUILDING  ;

    for (int i = 0; i < maxRecipes; i++)
    {
        RECIPES_STRUCTURES[i].resultID = itemType_noItem;
        RECIPES_HANDMADE  [i].resultID = itemType_noItem;
        RECIPES_CRAFTBENCH[i].resultID = itemType_noItem;
        RECIPES_BUILDING  [i].resultID = itemType_noItem;
        strcpy(RECIPES_HANDMADE[i].name, "");
        strcpy(RECIPES_CRAFTBENCH[i].name, "");
        strcpy(RECIPES_BUILDING[i].name, "");
        strcpy(RECIPES_STRUCTURES[i].name, "");

        for (int j = 0; j < 4; j++)
        {
            RECIPES_HANDMADE[i].recipe[j].itemType = itemType_noItem;
            RECIPES_CRAFTBENCH[i].recipe[j].itemType = itemType_noItem;
            RECIPES_STRUCTURES[i].recipe[j].itemType = itemType_noItem;
            RECIPES_BUILDING[i].recipe[j].itemType = itemType_noItem;
            RECIPES_HANDMADE[i].amounts[j] = 0;
            RECIPES_CRAFTBENCH[i].amounts[j] = 0;
            RECIPES_STRUCTURES[i].amounts[j] = 0;
            RECIPES_BUILDING[i].amounts[j] = 0;
        }
    }

    //structure recipes
    RECIPES_STRUCTURES[0] = createCraftingRecipe("build campfire", structureType_campfire, createRepresentation(materialProp_flammable | materialProp_type(materialType_wood), itemType_logs), 3);
    addRecipeItem(&RECIPES_STRUCTURES[0], createRepresentation(materialProp_incendiary | materialProp_type(materialType_rock), itemType_undefined), 0);
    RECIPES_STRUCTURES[1] = createCraftingRecipe("build craftbench", structureType_craftingStation, createRepresentation(materialProp_type(materialType_wood), itemType_logs), 4);
    RECIPES_STRUCTURES[2] = createCraftingRecipe("build furnace ", structureType_furnaceStation, createRepresentation(materialProp_type(materialType_rock), itemType_undefined), 8);
    
    setupLog();
    addDebugLog("requiredFlags: \n");
    addBinaryNumberToLog(GAME_CRAFTING_RECIPES[craftingCategory_structures][0].recipe[0].flagsRequired);
    addDebugLog("water type flags: \n");
    addBinaryNumberToLog(materialProp_type(materialtype_water));
    addDebugLog("wood type flags: \n");
    addBinaryNumberToLog(materialProp_type(materialType_wood));
    closeDebug();

    //handmade recipes

    //craftbench recipes

    //building recipes

}

int getRecipesLength(int category)
{
    int i = 0;
    while (i < maxRecipes && GAME_CRAFTING_RECIPES[category][i].resultID != itemType_noItem)
    {
        i++;
    }
    return i;
}
void removeRecipeItemsFromPlayer(CraftingRecipe recipe){
    int ingredientID = 0;
    while (ingredientID < getPlayerInventoryLength() && recipe.recipe[ingredientID].itemType != itemType_noItem)
    {
        for (int i = 0; i < recipe.amounts[ingredientID]; i++)
        {
            removeItemFromInventory(findMatchingItem(player.inventory, getPlayerInventoryLength(), recipe.recipe[ingredientID]));
        }
        ingredientID++;
    }
}