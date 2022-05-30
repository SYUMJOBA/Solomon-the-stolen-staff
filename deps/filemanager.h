char GAME_FILENAME[32] = "";
FILE* GAME_FILEPOINTER = NULL;

#define file_success 1
#define file_insuccess 0
#define file_trouble 2

#define cannot_overWrite 0
#define can_overWrite 1
#define waiting_forwritingPermission 2

void standardizeFileName(char * filename){ //bsaically makes sure the "save" extension is included in the file name
    int i = 0;
    while ((unsigned)i < strlen(filename) && filename[i] != '.')
    {
        i++;
    }
    if ((unsigned)i <= strlen(filename))
    {
        filename[i] = '.';
        filename[i+1] = 's';
        filename[i+2] = 'a';
        filename[i+3] = 'v';
        filename[i+4] = 'e';
        filename[i+5] = '\0';
    }
}

void readString(char* buffer, FILE* filepointer, int len)
{
    char subBuffer[1];
    for (int i = 0; i < len; i++)
    {
        fread(subBuffer, 4, 1, filepointer);
        buffer[i] = subBuffer[0];
    }
}

void writeHeader()
{
    char fileIdentifier[4];
    fileIdentifier[0] = 's';
    fileIdentifier[1] = 'a';
    fileIdentifier[2] = 'v';
    fileIdentifier[3] = 'e';
    fwrite(fileIdentifier, 4, 1, GAME_FILEPOINTER);
    int version[1] = { 1 };
    fwrite(version, sizeof(int), 1, GAME_FILEPOINTER);
    fwrite(&player, sizeof(Player), 1, GAME_FILEPOINTER);
    fwrite(&GAME_CURRENT_LEVEL, sizeof(int), 1, GAME_FILEPOINTER);
    fwrite(&GAME_HIGHEST_LEVEL, sizeof(int), 1, GAME_FILEPOINTER);
}

void readHeader()
{
    char fileIdentifier[4];
    fread(fileIdentifier, 4, 1, GAME_FILEPOINTER);
    int version[1];
    fread(version, sizeof(int), 1, GAME_FILEPOINTER);
    fread(&player, sizeof(Player), 1, GAME_FILEPOINTER);
    fread(&GAME_CURRENT_LEVEL, sizeof(int), 1, GAME_FILEPOINTER);
    fread(&GAME_HIGHEST_LEVEL, sizeof(int), 1, GAME_FILEPOINTER);
}

void writeLevel()
{
    fwrite(GAME_GROUND, sizeof(WorldTile), GAME_MAP_WIDTH * GAME_MAP_HEIGHT, GAME_FILEPOINTER);
    fwrite(GAME_WALLS, sizeof(WorldTile), GAME_MAP_WIDTH * GAME_MAP_HEIGHT, GAME_FILEPOINTER);
    fwrite(MAP_ENTITIES, sizeof(Entity), max_mapEntities, GAME_FILEPOINTER);
    fwrite(MAP_TRAPS, sizeof(Trap), max_mapTraps, GAME_FILEPOINTER);
    fwrite(MAP_ITEMS, sizeof(Item), max_mapItems, GAME_FILEPOINTER);
    fwrite(MAP_CHESTS, sizeof(ChestItemContainer), max_mapChests, GAME_FILEPOINTER);
    fwrite(MAP_SPAWNERS, sizeof(Spawner), max_mapSpawners, GAME_FILEPOINTER);
}

void readLevel()
{
    fread(GAME_GROUND, sizeof(WorldTile), GAME_MAP_WIDTH * GAME_MAP_HEIGHT, GAME_FILEPOINTER);
    fread(GAME_WALLS, sizeof(WorldTile), GAME_MAP_WIDTH * GAME_MAP_HEIGHT, GAME_FILEPOINTER);
    fread(MAP_ENTITIES, sizeof(Entity), max_mapEntities, GAME_FILEPOINTER);
    fread(MAP_TRAPS, sizeof(Trap), max_mapTraps, GAME_FILEPOINTER);
    fread(MAP_ITEMS, sizeof(Item), max_mapItems, GAME_FILEPOINTER);
    fread(MAP_CHESTS, sizeof(ChestItemContainer), max_mapChests, GAME_FILEPOINTER);
    fread(MAP_SPAWNERS, sizeof(Spawner), max_mapSpawners, GAME_FILEPOINTER);
}


BOOL loadFileInGame(){
    standardizeFileName( GAME_FILENAME );
    GAME_FILEPOINTER = fopen(GAME_FILENAME, "rb");
    if (NULL != GAME_FILEPOINTER)
    {
        readHeader();
        readLevel();
        fclose(GAME_FILEPOINTER);
        return TRUE;
    }
    return FALSE;
}

BOOL writeFileFromGame(BOOL overWriteAllowed){
    standardizeFileName(GAME_FILENAME);

    GAME_FILEPOINTER = fopen(GAME_FILENAME, "wb");
    if (NULL != GAME_FILEPOINTER)
    {
        writeHeader();
        writeLevel();
        fclose(GAME_FILEPOINTER);
        return file_success;
    }
    return file_insuccess;
}

void deleteFile()
{
    standardizeFileName(GAME_FILENAME);
    FILE* filepointer = fopen(GAME_FILENAME, "wb");
    fclose(filepointer);
}

/*
FILE STRUCTURE:


-------------header------------- (single time header at the begginning of the file)
4xchar      |   indentifieer
int         |   version
Player      |   player
int         |   currentLevel
int         |   highestLevel
--------------------------------

-------------level data---------- (is repeated for each level discovered by the player)
GAME_GROUND*|   ground
GAME_WALLS* |   walls
Entity*max  |   entities
Traps*max   |   traps
Item*max    |   item
Chest*max   |   chests
Spawner*max |   spawners
---------------------------------

*/
