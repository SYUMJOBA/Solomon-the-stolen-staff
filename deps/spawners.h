//these are small (destroyable) cages, that in the game periodically spawn enemies, or that spawn enemies once after the player comes close enough


#define spawner_maxChanceRoll 20

typedef struct Spawner
{
	int spawnChance; // if 0, the spawner is a one time spawning device that sets off and automatically destroys itself as soon as the player is close enough
	//chance is to calulcate wuth scale from 1 to 20
	int hitsTaken; //the moment it reaches 3, the spawner is destroyed
	int entityTypeID; //indicates what EntitySkeleton to spawn (found using this value as index for GAME_ENTITES)
	// if entityTypeID is -1, the spawner is considered to be NULL or inexistent
	int requiredDistance; //if the Vec2 distance from the player and the spawner is less than this, the spawner triggers, set to {-1, -1} if no distance is needed for activation
	Vec2 position; //where the spawner is
	int spawnsLeft; //indicates how many entities can the spawner still spawn (acts like a maximum that slowly decreases)
	int clockLeft; //this indicates how much time does the spawner need before activation, this incremented every step
} Spawner, *PSpawner;

Spawner MAP_SPAWNERS[max_mapSpawners];

Spawner createSpawner(int entityType, int chance, int minimumDistance, Vec2 position, int maxSpawns, int timeToStart)
{
	Spawner spawner;
	spawner.hitsTaken = 0;
	spawner.spawnsLeft = maxSpawns;
	spawner.spawnChance = chance;
	spawner.position = position;
	spawner.requiredDistance = minimumDistance;
	spawner.clockLeft = timeToStart;
	spawner.entityTypeID = entityType;
	return spawner;
}

CHAR_INFO SPAWNER_GRAPHIC = { '^', Fg_White };

BOOL addSpawner(Spawner newSpawner)
{
	int i = 0;
	while (i < max_mapSpawners && MAP_SPAWNERS[i].entityTypeID != entityType_nothing)
		i++;
	if (i < max_mapSpawners)
	{
		MAP_SPAWNERS[i] = newSpawner;
		return TRUE;
	}
	return FALSE;
}

void removeSpawner(Spawner * spawner)
{
	spawner->entityTypeID = entityType_nothing;
	spawner->position = { -1, -1 };
}

Spawner * getSpawnerFromMapPosition(Vec2 mapPosition)
{
	int i = 0;
	while (i < max_mapSpawners && !isVec2Equal(MAP_SPAWNERS[i].position, mapPosition))
	{
		i++;
	}
	return i < max_mapSpawners ? &MAP_SPAWNERS[i] : NULL;
}

void initSpawners()
{
	for (int i = 0; i < max_mapSpawners; i++)
	{
		removeSpawner(&MAP_SPAWNERS[i]);
	}
}

void updateSpawners()
{
	for (int i = 0; i < max_mapSpawners; i++)
	{
		if (MAP_SPAWNERS[i].entityTypeID != entityType_nothing)
		{
			if (MAP_SPAWNERS[i].hitsTaken > 3)
				removeSpawner(&MAP_SPAWNERS[i]);
			else //run the spawning sequence
				if (MAP_SPAWNERS[i].spawnChance) //if it is a randomNess spawner rather than a triggerable one
				{
					if (MAP_SPAWNERS[i].clockLeft > 0)
						MAP_SPAWNERS[i].clockLeft--;
					else
					if (MAP_SPAWNERS[i].spawnsLeft > 0)
					{
						if (rand() % 20 < MAP_SPAWNERS[i].spawnChance)
						{
							addEntityToMap(createEntity(MAP_SPAWNERS[i].entityTypeID, { MAP_SPAWNERS[i].position.X, MAP_SPAWNERS[i].position.Y }));
							MAP_SPAWNERS[i].spawnsLeft--;
						}
					}
					else
						removeSpawner(&MAP_SPAWNERS[i]);
				}
				else //if it's a triggerable one
					if (MAP_SPAWNERS[i].requiredDistance <= Vec2diff(MAP_SPAWNERS[i].position, player.position))
					{
						MAP_SPAWNERS[i].clockLeft--;
						if (MAP_SPAWNERS[i].clockLeft < 0)
						{
							addEntityToMap(createEntity(MAP_SPAWNERS[i].entityTypeID, MAP_SPAWNERS[i].position));
							removeSpawner(&MAP_SPAWNERS[i]);
						}
					}
		}
	}
}
