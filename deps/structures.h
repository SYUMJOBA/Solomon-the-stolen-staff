#define structureType_noStructure 0
#define structureType_craftingStation 1
#define structureType_furnaceStation 2
#define structureType_enchantingStation 3
#define structureType_runer 4
#define structureType_kitchen 5
#define structureType_campfire 6

typedef struct StructureSkeleton{
    char name[32];
    CHAR_INFO schematic[9]; //represetnation of the structure's sprite
} StructureSkeleton, *PsTructureSkeleton;
//every game structure has a central point declared as the `position` member,
//every structure is 3x3 tiles big

typedef struct Structure{
    int structureType; //acts as ID
    Vec2 positon;
    unsigned int props; //useful vars defining characteristics of the structures
} Structure, *PStructure;


StructureSkeleton GAME_STRUCTURES[total_gameStructures];
StructureSkeleton createStructureSkeleton(Vec2 size, const char * name)
{
    StructureSkeleton tmpStruct;
    strcpy(tmpStruct.name, name);
    return tmpStruct;
}

Structure MAP_STRUCTURES[max_mapStructures];

Structure createStructure(int type, Vec2 mapPosition){
    Structure tmpStructure;
    tmpStructure.structureType = type;
    tmpStructure.positon = mapPosition;
    return tmpStructure;
}

void InitStructures()
{
    for (int i = 0; i < total_gameStructures; i++)
    {
        strcpy(GAME_STRUCTURES[i].name, "none");
        
    }
    for (int i = 0; i < max_mapStructures; i++)
    {
        MAP_STRUCTURES[i] = createStructure(structureType_noStructure, {-1, -1});
    }
    
    strcpy(GAME_STRUCTURES[1].name, "crafting");
    GAME_STRUCTURES[1].schematic[0] = {' ', Bg_Olive_Green};
    GAME_STRUCTURES[1].schematic[1] = {' ', Bg_Black};
    GAME_STRUCTURES[1].schematic[2] = {' ', Bg_Olive_Green};
    GAME_STRUCTURES[1].schematic[3] = {';', Bg_Olive_Green | Fg_White};
    GAME_STRUCTURES[1].schematic[4] = {' ', Bg_Black};
    GAME_STRUCTURES[1].schematic[5] = {' ', Bg_Black};
    GAME_STRUCTURES[1].schematic[6] = {' ', Bg_Olive_Green};
    GAME_STRUCTURES[1].schematic[7] = {'#', Bg_Olive_Green | Fg_Black};
    GAME_STRUCTURES[1].schematic[8] = {' ', Bg_Black};


    //█ █
    //;
    //█#█

    strcpy(GAME_STRUCTURES[2].name, "furnace");
    GAME_STRUCTURES[2].schematic[0] = {'[', Bg_Black | Fg_Grey};
    GAME_STRUCTURES[2].schematic[1] = {(char)22 /*▬*/, Bg_White | Fg_Red};
    GAME_STRUCTURES[2].schematic[2] = {']', Bg_Black | Fg_Grey};
    GAME_STRUCTURES[2].schematic[3] = {' ', Bg_Black};
    GAME_STRUCTURES[2].schematic[4] = {' ', Bg_Black};
    GAME_STRUCTURES[2].schematic[5] = {' ', Bg_Black};
    GAME_STRUCTURES[2].schematic[6] = {' ', Bg_Grey};
    GAME_STRUCTURES[2].schematic[7] = {'^', Fg_Black | Bg_White};
    GAME_STRUCTURES[2].schematic[8] = {'}', Fg_Grey | Bg_Black};

    //[▬]
    //   
    //█^}

    strcpy(GAME_STRUCTURES[3].name, "enchanting");
    GAME_STRUCTURES[3].schematic[0] = { 0xda, Fg_Light_Blue | Bg_Fucsia};
    GAME_STRUCTURES[3].schematic[1] = {' ', Bg_White | Fg_Red};
    GAME_STRUCTURES[3].schematic[2] = { 0xbf, Bg_Black | Fg_Light_Blue};
    GAME_STRUCTURES[3].schematic[3] = {' ', Bg_Black};
    GAME_STRUCTURES[3].schematic[4] = {(WCHAR)char_threeParallelLines, Fg_White | Bg_Olive_Green};
    GAME_STRUCTURES[3].schematic[5] = {' ', Bg_Black};
    GAME_STRUCTURES[3].schematic[6] = { 0xc0 , Bg_Light_Blue | Fg_Black};
    GAME_STRUCTURES[3].schematic[7] = {' ', Fg_Black};
    GAME_STRUCTURES[3].schematic[8] = { 0xd9, Fg_Light_Blue | Bg_Black};


    strcpy(GAME_STRUCTURES[4].name, "runer");
    GAME_STRUCTURES[4].schematic[0] = {';', Fg_Light_Blue | Bg_Grey};
    GAME_STRUCTURES[4].schematic[1] = {' ', Bg_White | Fg_Red};
    GAME_STRUCTURES[4].schematic[2] = {';', Fg_Light_Blue | Bg_Grey};
    GAME_STRUCTURES[4].schematic[3] = {' ', Bg_Black};
    GAME_STRUCTURES[4].schematic[4] = {(WCHAR)char_bricks1, Fg_Fucsia};
    GAME_STRUCTURES[4].schematic[5] = {' ', Bg_Black};
    GAME_STRUCTURES[4].schematic[6] = {';', Fg_Light_Blue | Bg_Grey};
    GAME_STRUCTURES[4].schematic[7] = {' ', Fg_Black};
    GAME_STRUCTURES[4].schematic[8] = {';', Fg_Light_Blue | Bg_Grey};

    strcpy(GAME_STRUCTURES[5].name, "kitchen");

    strcpy(GAME_STRUCTURES[6].name, "campfire");
    GAME_STRUCTURES[6].schematic[0] = {'-', Fg_Olive_Green};
    GAME_STRUCTURES[6].schematic[1] = {'|', Fg_Olive_Green};
    GAME_STRUCTURES[6].schematic[2] = {'_', Fg_Olive_Green};
    GAME_STRUCTURES[6].schematic[3] = {'-', Bg_Black};
    GAME_STRUCTURES[6].schematic[4] = {char_star, Fg_Red};
    GAME_STRUCTURES[6].schematic[5] = {'-', Fg_Olive_Green};
    GAME_STRUCTURES[6].schematic[6] = {' ', Fg_Olive_Green};
    GAME_STRUCTURES[6].schematic[7] = {'|', Fg_Olive_Green};
    GAME_STRUCTURES[6].schematic[8] = {'-', Fg_Olive_Green};
}

int getStructuresAmount(){
    int amount = 0;
    for (int i = 0; i < max_mapStructures; i++)
    {
        if (MAP_STRUCTURES[i].structureType != structureType_noStructure)
        {
            amount++;
        }
    }
    return amount;
}

BOOL canBuildStructureInMapPosition(Vec2 centralPosition){
    //loop through all the array of map structures and check if 3x3 space is oK; EDIT : time to use AABB
    //when you're sad and depressed, you just have the feeling you're not understanding your surroundigns
    int p = 0;
    while (p < 9 && !collidesWithMap({ centralPosition.X - 1 + p % 3, centralPosition.Y - 1 + p / 3 }))
        p++;
    if (p < 9)
        return FALSE;
    else
    {
        int i = 0;
        while (i < max_mapStructures && !AABB({ MAP_STRUCTURES[i].positon, {3, 3} }, { centralPosition, {3, 3} }))
        {
            i++;
        }
        return (i == max_mapStructures);
    }
}

void removeStructureFromMap(int structureID){
    MAP_STRUCTURES[structureID] = createStructure(structureType_noStructure, {-1, -1});
}

BOOL addStructureToMap(Structure structure)
{
    int i = 0;
    while (i < max_mapStructures && MAP_STRUCTURES[i].structureType != structureType_noStructure)
    {
        i++;
    }
    if (i < max_mapStructures)
    {
        MAP_STRUCTURES[i] = structure;
        return TRUE;
    } else {
        return FALSE;
    }
}
