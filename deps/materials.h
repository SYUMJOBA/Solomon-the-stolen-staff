
#define material_noMaterial -1
#define material_dolomite 0
#define material_cherryWood 1
#define material_platinum 2
#define material_lava 3
#define material_water 4
#define material_flesh 5
#define material_beefMeat 6
#define material_gold 7
#define material_glass 8
#define material_flint 9
#define material_lapis 10
#define material_magic 11
#define material_delganium 12 //endgame metal
#define material_birchWood 13
#define material_insectoid 14

#define materialType_VOID 0
#define materialType_wood 1
#define materialType_glass 2
#define materialType_rock 3
#define materialType_metal 4
#define materialtype_water 5
#define materialType_organic 6

typedef struct Material
{
    unsigned short color; // analogous for windows.h 's WORD type
    WCHAR symbol;         // if there isn't any, just put ' ', the symbol is used to represent
    unsigned int flags;   // flags for the material : acid will be treated in a way, lava in another one ... and so on ...
    char name[16];
    unsigned short rawItemID; // flags what item TYPE should the material display as, in case it breaks
} Material, *PMaterial;

Material GAME_MATERIALS[game_totalMaterials];

/* FLAGS in Material:

bit number:     |   meaning
----------------|-------------
32              |   isLiquid?
31              |   deadly?
30              |   burnable?
29              |   burns neighboring things?

28              | _ _ _ _ _ _ _ _ _ _
27              |
26              | these bits compose an unsiged nibble that represents the strength of the material
25              | _ _ _ _ _ _ _ _ _ _

24              | isDestroyable?
23              | isEdible?
22              | isWaterProof?          -
21              | isPoisonous?

20              | _ _ _ _ _ _ _ _ _ _
19              |
18              | these bits compose an unsigned nibble that represets the mass of this material
17              | _ _ _ _ _ _ _ _ _ _

16              |
15              | these bits compose an unsigned nibble that represents the general type of this material (wood? metal? glass? rock?) could be deleted soon
14              | it is highly probably that it will be deleted later
13              |

12              | isSmeltable?
*/

//define all of these
#define materialProp_liquid 0b10000000000000000000000000000000
#define materialProp_deadly 0b1000000000000000000000000000000
#define materialProp_flammable 0b100000000000000000000000000000 //also counts as burnable
#define materialProp_incendiary 0b10000000000000000000000000000
#define materialProp_strength(strength) (strength << 24)
#define materialProp_destroyable 0b100000000000000000000000
#define materialProp_edible 0b10000000000000000000000
#define materialProp_waterProof 0b1000000000000000000000
#define materialProp_poisonous 0b100000000000000000000
#define materialProp_mass(mass) (mass << 16)
#define materialProp_type(type) (type << 12)
#define materialProp_smeltable 0b100000000000

//if you are wondering why we have materialProp definitions as well as a createMaterialProps(), the answer is that with smart parameter suggestion it is harder to forget something using
//the function, since all the parameters mean something and are strictly required

BOOL isMaterialLiquid(Material material)
{
    return material.flags >> 31;
}
BOOL isMaterialDeadly(Material material)
{
    material.flags <<= 1;
    return material.flags >> 31;
}
BOOL isMaterialFlammable(Material material)
{
    material.flags <<= 2;
    return material.flags >> 31;
}
BOOL isMaterialIncendiary(Material material)
{
    material.flags <<= 3;
    return material.flags >> 31;
}
int getMaterialStrength(Material material)
{
    material.flags <<= 4;
    return material.flags >> 28;
}
BOOL isMaterialDestroyable(Material material)
{
    material.flags <<= 8;
    material.flags >>= 31;
    return material.flags;
}
BOOL isMaterialEdible(Material material)
{
    material.flags <<= 9;
    return material.flags >> 31;
}
BOOL isMaterialWaterProof(Material material)
{
    material.flags <<= 10;
    return material.flags >> 31;
}
BOOL isMaterialPoisonous(Material material)
{
    material.flags <<= 11;
    return material.flags >> 31;
}
int getMaterialMass(Material material)
{
    material.flags <<= 12;
    return material.flags >> 28;
}
int getMaterialType(Material material)
{
    material.flags <<= 16;
    return material.flags >> 28;
}
BOOL isMaterialWoodLike(Material material)
{
    return getMaterialType(material) == materialType_wood;
}
BOOL isMaterialMetallic(Material material)
{
    return getMaterialType(material) == materialType_metal;
}
BOOL isMaterialRockLike(Material material)
{
    return getMaterialType(material) == materialType_rock;
}
BOOL isMaterialGlassLike(Material material)
{
    return getMaterialType(material) == material_glass;
}
BOOL isMaterialSmeltable(Material material)
{
    material.flags <<= 20;
    return material.flags >> 31;
}


// Max strength or mass : 17
//this function just doesn't work, and became deprecated with the new flags: slated for removal
unsigned int createMaterialProps(BOOL isLiquid, BOOL isDeadly, BOOL isFlammable, BOOL isIncendiary, unsigned int strength, BOOL isDestroyable, BOOL isEdible, BOOL isWaterProof, BOOL isPoisonous, unsigned int mass, unsigned int materialType, BOOL isSmeltable)
{
    return 
    (
        (unsigned int)(materialProp_liquid*isLiquid |
        materialProp_deadly*isDeadly |
        materialProp_flammable*isFlammable |
        materialProp_incendiary*isIncendiary |
        materialProp_strength(strength) |
        materialProp_destroyable*isDestroyable |
        materialProp_edible*isEdible |
        materialProp_waterProof*isWaterProof |
        materialProp_poisonous*isPoisonous |
        materialProp_mass(mass) |
        materialProp_type(materialType) |
        materialProp_smeltable*isSmeltable)
    );
}
//in an ordered manner, this is the result of the function
/*
addBinaryNumberToLog(createMaterialProps(TRUE , FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE));
addBinaryNumberToLog(createMaterialProps(FALSE, TRUE , FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE));
addBinaryNumberToLog(createMaterialProps(FALSE, FALSE, TRUE , FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE));
addBinaryNumberToLog(createMaterialProps(FALSE, FALSE, FALSE, TRUE , FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE));
addBinaryNumberToLog(createMaterialProps(FALSE, FALSE, FALSE, FALSE, TRUE , FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE));
addBinaryNumberToLog(createMaterialProps(FALSE, FALSE, FALSE, FALSE, FALSE, TRUE , FALSE, FALSE, FALSE, FALSE, FALSE, FALSE));
addBinaryNumberToLog(createMaterialProps(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE , FALSE, FALSE, FALSE, FALSE, FALSE));
addBinaryNumberToLog(createMaterialProps(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE , TRUE , FALSE, FALSE, FALSE, FALSE));
addBinaryNumberToLog(createMaterialProps(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE , FALSE, FALSE, FALSE));
addBinaryNumberToLog(createMaterialProps(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE , FALSE, FALSE));
addBinaryNumberToLog(createMaterialProps(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE , FALSE));
addBinaryNumberToLog(createMaterialProps(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE ));
*/
/*
10000000001000000000000000000000
01000000001000000000000000000000
00100000001000000000000000000000
00010000001000000000000000000000
00000001001000000000000000000000
00000000101000000000000000000000
00000000011000000000000000000000
00000000001100000000000000000000
00000000001000100000000000000000
00000000001000000010000000000000
00000000001000000001000000000000
*/
void setupMaterials()
{
    GAME_MATERIALS[0].color = Bg_Grey;
    GAME_MATERIALS[0].symbol = '\'';
    strcpy(GAME_MATERIALS[0].name, "Dolomite");
    GAME_MATERIALS[0].flags = materialProp_strength(6) | materialProp_type(materialType_rock) | materialProp_destroyable | materialProp_smeltable | materialProp_mass(10);
    GAME_MATERIALS[0].rawItemID = itemType_stoneBoulder;

    GAME_MATERIALS[1].color = Bg_Olive_Green;
    GAME_MATERIALS[1].symbol = ' ';
    strcpy(GAME_MATERIALS[1].name, "cherry wood");
    GAME_MATERIALS[1].flags = materialProp_flammable | materialProp_strength(3) | materialProp_type(materialType_wood) | materialProp_destroyable | materialProp_mass(6);
    GAME_MATERIALS[1].rawItemID = itemType_logs;

    GAME_MATERIALS[2].color = Bg_White;
    GAME_MATERIALS[2].symbol = char_pound;
    strcpy(GAME_MATERIALS[2].name, "platinum");
    GAME_MATERIALS[2].flags = createMaterialProps(FALSE, FALSE, FALSE, FALSE, 11, TRUE, FALSE, TRUE, FALSE, 7, materialType_metal, TRUE);
    GAME_MATERIALS[2].rawItemID = itemType_metalNugget;

    GAME_MATERIALS[3].color = Bg_Red;
    GAME_MATERIALS[3].symbol = tileSprite_liquidDouble;
    strcpy(GAME_MATERIALS[3].name, "lava");
    GAME_MATERIALS[3].flags = createMaterialProps(TRUE, TRUE, FALSE, TRUE, 0, FALSE, FALSE, FALSE, FALSE, 13, materialType_rock, FALSE);
    GAME_MATERIALS[3].rawItemID = itemType_noItem;

    GAME_MATERIALS[4].color = Bg_Blue;
    GAME_MATERIALS[4].symbol = tileSprite_liquidDouble;
    strcpy(GAME_MATERIALS[4].name, "water");
    GAME_MATERIALS[4].flags = createMaterialProps(TRUE, FALSE, FALSE, FALSE, 0, FALSE, TRUE, FALSE, FALSE, 9, materialtype_water, FALSE);
    GAME_MATERIALS[4].rawItemID = itemType_noItem;

    GAME_MATERIALS[5].color = Bg_Bordeaux + Fg_Fucsia;
    GAME_MATERIALS[5].symbol = materialSprite_flesh;
    strcpy(GAME_MATERIALS[5].name, "flesh");
    GAME_MATERIALS[5].flags = createMaterialProps(FALSE, FALSE, TRUE, FALSE, 2, TRUE, TRUE, FALSE, TRUE, 9, materialType_organic, FALSE);
    GAME_MATERIALS[5].rawItemID = itemType_rawFlesh;
    // https://www.quora.com/Is-flesh-flammable

    GAME_MATERIALS[6].color = Bg_Bordeaux + Fg_Red;
    GAME_MATERIALS[6].symbol = char_alpha;
    strcpy(GAME_MATERIALS[6].name, "beef");
    GAME_MATERIALS[6].flags = createMaterialProps(FALSE, FALSE, FALSE, FALSE, 2, TRUE, TRUE, FALSE, FALSE, 10, materialType_organic, FALSE);
    GAME_MATERIALS[6].rawItemID = itemType_steak;

    GAME_MATERIALS[7].color = Bg_Yellow;
    GAME_MATERIALS[7].symbol = char_pound;
    strcpy(GAME_MATERIALS[7].name, "gold");
    GAME_MATERIALS[7].flags = createMaterialProps(FALSE, FALSE, FALSE, FALSE, 7, TRUE, FALSE, TRUE, FALSE, 5, materialType_metal, TRUE);
    GAME_MATERIALS[7].rawItemID = itemType_metalNugget;

    GAME_MATERIALS[8].color = Bg_White;
    GAME_MATERIALS[8].symbol = '\\';
    strcpy(GAME_MATERIALS[8].name, "glass");
    GAME_MATERIALS[8].flags = createMaterialProps(FALSE, FALSE, FALSE, FALSE, 4, TRUE, FALSE, TRUE, FALSE, 4, material_glass, TRUE);
    GAME_MATERIALS[8].rawItemID = itemType_shards;


    GAME_MATERIALS[9].color = Bg_Grey;
    GAME_MATERIALS[9].symbol = '\'';
    strcpy(GAME_MATERIALS[9].name, "flint");
    GAME_MATERIALS[9].flags = createMaterialProps(FALSE, FALSE, FALSE, TRUE, 6, TRUE, FALSE, TRUE, FALSE, 4, materialType_rock, FALSE);
    GAME_MATERIALS[9].rawItemID = itemType_shards;

    GAME_MATERIALS[10].color = Bg_Blue | Fg_Light_Blue;
    GAME_MATERIALS[10].symbol = char_star;
    strcpy(GAME_MATERIALS[10].name, "lapis");
    GAME_MATERIALS[10].flags = createMaterialProps(FALSE, FALSE, FALSE, FALSE, 4, TRUE, FALSE, TRUE, FALSE, 5, materialType_rock, FALSE);
    GAME_MATERIALS[10].rawItemID = itemType_roughGem;

    GAME_MATERIALS[11].color = Bg_Yellow | Fg_Fucsia;
    GAME_MATERIALS[11].symbol = char_bricks1;
    strcpy(GAME_MATERIALS[11].name, "magic");
    GAME_MATERIALS[11].flags = createMaterialProps(FALSE, FALSE, FALSE, FALSE, 12, TRUE, FALSE, FALSE, FALSE, 1, materialType_metal, FALSE);
    GAME_MATERIALS[11].rawItemID = itemType_roughGem;

    GAME_MATERIALS[12].color = Bg_Yellow | Fg_Fucsia;
    GAME_MATERIALS[12].symbol = char_bricks1;
    strcpy(GAME_MATERIALS[12].name, "delganium");
    GAME_MATERIALS[12].flags = createMaterialProps(FALSE, FALSE, FALSE, FALSE, 17, TRUE, FALSE, TRUE, FALSE, 3, materialType_metal, TRUE);
    GAME_MATERIALS[12].rawItemID = itemType_metalNugget;

    GAME_MATERIALS[13].color = Bg_White | Fg_Black;
    GAME_MATERIALS[13].symbol = ' ';
    strcpy(GAME_MATERIALS[13].name, "birch wood");
    GAME_MATERIALS[13].flags = createMaterialProps(FALSE, FALSE, TRUE, FALSE, 3, TRUE, FALSE, TRUE, FALSE, 7, materialType_wood, FALSE);
    GAME_MATERIALS[13].rawItemID = itemType_logs;

    GAME_MATERIALS[14].color = Bg_Grey | Fg_Grey;
    GAME_MATERIALS[14].symbol = '.';
    strcpy(GAME_MATERIALS[14].name, "insectoid");
    GAME_MATERIALS[14].flags = createMaterialProps(FALSE, FALSE, FALSE, FALSE, 5, TRUE, TRUE, TRUE, FALSE, 4, materialType_organic, TRUE);
    GAME_MATERIALS[14].rawItemID = itemType_shards;
}

const char *getMaterialTypeFromEnum(int type)
{
    switch (type)
    {
    case materialtype_water:
        return "waterlike ";
        break;

    case materialType_glass:
        return "glasslike ";
        break;

    case materialType_organic:
        return "organic ";
        break;

    case materialType_rock:
        return "rocky ";
        break;

    case materialType_wood:
        return "wooden ";
        break;

    case materialType_metal:
        return "metallic ";
        break;

    case materialType_VOID:
        return "VOID ";
        break;

    default:
        return "W - H - A - T? ";
        break;
    }
}
int getItemForMaterialType(int materialType){
    switch (materialType)
    {
    case materialtype_water:
        return -1;
        break;
    
    case materialType_glass:
        return itemType_shards;
        break;

    case materialType_metal:
        return itemType_metalNugget;
        break;
    
    case materialType_rock:
        return itemType_stoneBoulder;
        break;

    default:
        return -1;
        break;
    }
}
