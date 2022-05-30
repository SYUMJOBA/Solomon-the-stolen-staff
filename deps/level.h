#pragma once

//NOTE : the file version is 1 for now

//luckily, because of the use of stacked memory, the program data is extremely easy to save XD

//this code is now working bad overflows memory stack, you can still use this for file structures 

#ifdef GAME_MODE_EXPERIMENTAL

typedef struct GameLevel{
	WorldTile GAME_GROUND[GAME_MAP_HEIGHT * GAME_MAP_WIDTH];
	WorldTile GAME_WALLS[GAME_MAP_HEIGHT * GAME_MAP_WIDTH];
	
	Entity MAP_ENTITIES[max_mapEntities];
	Structure MAP_STRUCTURES[max_mapStructures];
	Trap MAP_TRAPS[max_mapTraps];
	Item MAP_ITEMS[max_mapChests];
	ChestItemContainer MAP_CHESTS[max_mapChests];
	Spawner MAP_SPAWNERS[max_mapSpawners];

} GameLevel, *PGameLevel;
typedef struct GameSaveFile {
	//fileHeader
	char fileIdentifier[4];
	int fileVersion;
	//player data
	Player playerData;
	//level list header
	int currentLevel;
	int highestLevel; //for now it will be just 1 as a default till next multiLevelUpdate
	//GameLevel list
	GameLevel levels[1]; //for now it is capped to one
	//ideally the levels array length should be the same length of "highestLEvel" variable
}GameSaveFile, *PGameSaveFile;

GameLevel getCurrentLevelData()
{
	GameLevel level;
	for (int i = 0; i < GAME_MAP_HEIGHT * GAME_MAP_WIDTH; i++)
	{
		level.GAME_GROUND[i] = GAME_GROUND[i];
		level.GAME_WALLS[i] = GAME_WALLS[i];
	}

	for (int i = 0; i < max_mapEntities; i++)
	{
		 level.MAP_ENTITIES[i] = MAP_ENTITIES[i];
	}

	for (int i = 0; i < max_mapItems; i++)
	{
		level.MAP_ITEMS[i] = MAP_ITEMS[i];
	}

	for (int i = 0; i < max_mapChests; i++)
	{
		level.MAP_CHESTS[i] = MAP_CHESTS[i];
	}
	for (int i = 0; i < max_mapSpawners; i++)
	{
		level.MAP_SPAWNERS[i] = MAP_SPAWNERS[i];
	}
	for (int i = 0; i < max_mapTraps; i++)
	{
		level.MAP_TRAPS[i] = MAP_TRAPS[i];
	}
	for (int i = 0; i < max_mapStructures; i++)
	{
		level.MAP_STRUCTURES[i] = MAP_STRUCTURES[i];
	}
	return level;
}
void writeLevelToGame(GameLevel level)
{
	for (int i = 0; i < GAME_MAP_HEIGHT * GAME_MAP_WIDTH; i++)
	{
		GAME_GROUND[i] = level.GAME_GROUND[i];
		GAME_WALLS[i] = level.GAME_WALLS[i];
	}

	for (int i = 0; i < max_mapEntities; i++)
	{
		MAP_ENTITIES[i] = level.MAP_ENTITIES[i];
	}

	for (int i = 0; i < max_mapItems; i++)
	{
		MAP_ITEMS[i] = level.MAP_ITEMS[i];
	}

	for (int i = 0; i < max_mapChests; i++)
	{
		MAP_CHESTS[i] = level.MAP_CHESTS[i];
	}
	for (int i = 0; i < max_mapSpawners; i++)
	{
		MAP_SPAWNERS[i] = level.MAP_SPAWNERS[i];
	}
	for (int i = 0; i < max_mapTraps; i++)
	{
		MAP_TRAPS[i] = level.MAP_TRAPS[i];
	}
	for (int i = 0; i < max_mapStructures; i++)
	{
		MAP_STRUCTURES[i] = level.MAP_STRUCTURES[i];
	}
}
void loadFromGameSaveToGame(GameSaveFile saveData)
{
	player = saveData.playerData;
	GAME_CURRENT_LEVEL = saveData.currentLevel;
	//I will just ignore file version for now, as it is kinda useless
	writeLevelToGame(saveData.levels[saveData.currentLevel]);
}

GameSaveFile saveCurrentGame()
{
	char name[4];
	name[0] = 's';
	name[1] = 'a';
	name[2] = 'v';
	name[3] = 'e';
	GameSaveFile saveFile;
	for (int i = 0; i < 4; i++)
	{
		saveFile.fileIdentifier[i] = name[i];
	}
	saveFile.highestLevel = GAME_HIGHEST_LEVEL;
	saveFile.currentLevel = GAME_CURRENT_LEVEL;
	saveFile.fileVersion = 1;
	saveFile.levels[GAME_CURRENT_LEVEL] = getCurrentLevelData();
	saveFile.playerData = player;
	return saveFile;
}
#endif

//if you wonder why do these structures lay here without any reason to exist, actually, they'll be used for future updates