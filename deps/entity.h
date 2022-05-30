
#define entityType_nothing -1
#define entityType_WHAT 0
#define entityType_zombie 1
#define entityType_rattleSnake 2
#define entityType_golem 3
#define entityType_monk 4
#define entityType_dragon 5
#define entityType_troll 6
#define entityType_spider 7
#define entityType_rat 8
#define entityType_goblin 9
#define entityType_armedGoblin 10
#define entityType_goblinBrute 11

//add loot tables
//naah don't do it

//pathFinding and AI stuff

/*
A* description : 
each step it picks up a node/cell with value 'f'
    where f = g + h
    
g : movement cost to get from start to current node/cell (follows path)
h : movement cost to get from current node/cell to end (linedraw)
|_this is the famous 'heuristic'
*/

typedef struct AStarCell {
    int g;
    int h;
    int f;
} AStarCell, *PAstarCell;

void cleanAstarArray(AStarCell* AStarArray, int len) //list is considered to be empty only when the 'f' param of the first element in the array is -1 (wich doesn't make real sense as the distance can't possibly be -1)
{
    for (int i = 0; i < len; i++)
    {
        AStarArray[i] = { 0, 0, 0 };
    }
}

AStarCell createAStarNode(int h, int f)
{
    return { 0, h, f };
}

void AStarPathFind(Vec2 source, Vec2 goal)
{
    AStarCell openNodes[128];
    AStarCell closedNodes[128];
    cleanAstarArray(openNodes, 128);
    cleanAstarArray(closedNodes, 128);

}
//Astar pathfinding slated for future update, monsters are as smart as they can be with raycasting alone

Vec2 castRay(Vec2 start, Vec2 destination) //traces a line from start to destination, returns what Vec2 position has the casted ray stopped at, uses map basic collision scheme and DDA algorythm
{
        int deltaX = abs(destination.X - start.X);
        int deltaY = abs(destination.Y - start.Y);
        int majorSegment;

        if (deltaX >= deltaY)
        {
            majorSegment = deltaX;
        }
        else {
            majorSegment = deltaY;
        }
        double stepX = destination.X > start.X ? (double)deltaX / (double)majorSegment : (double)deltaX / (double)majorSegment * -1;
        double stepY = destination.Y > start.Y ? (double)deltaY / (double)majorSegment : (double)deltaY / (double)majorSegment * -1;
        double x = start.X + 0.5;
        double y = start.Y + 0.5;

        int distanceTraveled = 0;
        while (!collidesWithMap({ (int)x, (int)y }) && distanceTraveled < majorSegment)
        {
            x += stepX;
            y += stepY;
            distanceTraveled++;
        }
        Vec2 arrival = { (int)x, (int)y };
        return arrival;
}

typedef struct EntitySkeleton{ //description and types of entites (the interface)
    int materialID;
    Enchantment possessedEffects[8];
    int effectImmunities[8];
    int maxHealth;

    int defence;
    int agility; //on a scale from 0 to 20
    int force;
    char name[16];
    char sprite;
    int eyesight;
    Attribute color;

} EntitySkeleton, *PEntitySkeleton;
EntitySkeleton GAME_ENTITIES[total_gameEntites];

typedef struct Entity{
    Vec2 position;
    int entityType;
    int health;
    Enchantment sufferingEffects[8];
    Vec2 goalPosition; //the last target place that the entity remembers seeing the player in, so the one that it will pathfind to
} Entity, *PEntity;
Entity MAP_ENTITIES[max_mapEntities];

EntitySkeleton createEntityType(int maxHealth, int defence, int agility, int force, const char * name, char sprite, Attribute color, int materialID, int eyesight){
    EntitySkeleton tmpEntitySkeleton;
    for (int i = 0; i < 8; i++)
    {
        tmpEntitySkeleton.possessedEffects[i] = Enchantment {0, 0};
        tmpEntitySkeleton.effectImmunities[i] = 0;
    }
    tmpEntitySkeleton.maxHealth = maxHealth;
    tmpEntitySkeleton.defence = defence;
    tmpEntitySkeleton.force = force;
    strcpy(tmpEntitySkeleton.name, name);
    tmpEntitySkeleton.sprite = sprite;
    tmpEntitySkeleton.color = color;
    tmpEntitySkeleton.materialID = materialID;
    tmpEntitySkeleton.agility = agility;
    tmpEntitySkeleton.eyesight = eyesight;
    return tmpEntitySkeleton;
}


BOOL addEnchantToEntityType(EntitySkeleton * entityType, Enchantment enchant){ //returns TRUE if succesful
    int i = 0;
    while (entityType->possessedEffects[i].enchantID != 0 && i < 8)
    {
        i++;
    }
    
    if (i < 8)
    {
        entityType->possessedEffects[i] = enchant;
        return TRUE;
    } else {
        return FALSE;
    }
} //enchant to entityType adds the effect in the entity skeleton

BOOL addEnchantToEntity(Entity * entity, Enchantment enchant){
    int i = 0;
    while (entity->sufferingEffects->strength != 0 && i < 8)
    {
        i++;
    }

    if (i < 8)
    {
        entity->sufferingEffects[i] = enchant;
        return TRUE;
    } else {
        return FALSE;
    }
} //enchant to entity adds in the effect in suffering enchant

/*
#define entityType_spider 7
#define entityType_rat 8
#define entityType_goblin 9
#define entityType_armedGoblin 10
#define entityType_goblinBrute 11
*/
void setupEntities(){
    GAME_ENTITIES[1] = createEntityType(6, 1, 1, 2, "Zombie", 'z', Fg_Olive_Green, material_flesh, 8);
    GAME_ENTITIES[2] = createEntityType(4, 0, 3, 1, "Rattle snake", 's', Fg_Lime_Green, material_flesh, 5);
    addEnchantToEntityType(&GAME_ENTITIES[1], {enchantType_poison, 3});
    GAME_ENTITIES[3] = createEntityType(10, 4, 0, 5, "Golem", 'G', Fg_White, material_dolomite, 8);
    GAME_ENTITIES[4] = createEntityType(16, 6, 4, 7, "Monk", 'm', Fg_Yellow, material_flesh, 15);
    GAME_ENTITIES[5] = createEntityType(100, 20, 2, 20, "Dragon", 'D', Fg_Green, material_flesh, 30);
    addEnchantToEntityType(&GAME_ENTITIES[5], createEnchant(enchantType_fiery, 2, 5));
    GAME_ENTITIES[6] = createEntityType(20, 4, 2, 8, "Troll", 'T', Fg_Grey, material_flesh, 8);
    for (int i = 0; i < max_mapEntities; i++)
    {
        MAP_ENTITIES[i].entityType = entityType_nothing;
    }

    GAME_ENTITIES[7] = createEntityType(5, 0, 3, 1, "spider", 's', Fg_Grey, material_insectoid, 7);
    addEnchantToEntityType(&GAME_ENTITIES[7], createEnchant(enchantType_poison, 1, 3));
    GAME_ENTITIES[8] = createEntityType(6, 0, 5, 2, "rat", 'r', Fg_Olive_Green, material_flesh, 8);
    GAME_ENTITIES[9] = createEntityType(15, 1, 6, 1, "Goblin", 'g', Fg_Lime_Green, material_flesh, 7);
    GAME_ENTITIES[10] = createEntityType(15, 4, 4, 4, "Armed Goblin", 'g', Fg_Green, material_flesh, 8);
    GAME_ENTITIES[11] = createEntityType(30, 8, 2, 8, "Goblin Brute", 'G', Fg_Green, material_flesh, 5);
}

void attackPlayer(Entity * attacker)
{   
    BOOL bootsPresence = player.boots.type != itemType_noItem;
    int bootsProt = bootsPresence ? getMaterialStrength(GAME_MATERIALS[player.boots.materialID]) : 0;
    int bootsEnchantProt = bootsPresence ? getEnchantFromItem(player.boots, enchantType_protection).strength : 0;
    BOOL chestPresence = player.torso.type != itemType_noItem;
    int chestProt = chestPresence ? getMaterialStrength(GAME_MATERIALS[player.torso.materialID]) : 0;
    int chestEnchantProt = chestPresence ? getEnchantFromItem(player.torso, enchantType_protection).strength : 0;
    BOOL legginsPresence = player.leggins.type != itemType_noItem;
    int legginstProt = legginsPresence ? getMaterialStrength(GAME_MATERIALS[player.leggins.materialID]) : 0;
    int legginsEnchantProt = legginsPresence ? getEnchantFromItem(player.leggins, enchantType_protection).strength : 0;
    BOOL helmPresence = player.head.type != itemType_noItem;
    int helmProt = helmPresence ? getMaterialStrength(GAME_MATERIALS[player.head.materialID]) : 0;
    int helmEnchantProt = helmPresence ? getEnchantFromItem(player.head, enchantType_protection).strength : 0;
    
    int armorProt = bootsProt + bootsEnchantProt + chestEnchantProt + chestEnchantProt + legginsEnchantProt + legginsEnchantProt + helmPresence + helmEnchantProt;
    
    //(it's a 3 out of 10')                                           //chance applied here
    int shieldProt = player.leftHand.type == itemType_shield ? (rand() % 10 < player_blockChance) * getMaterialStrength(GAME_MATERIALS[player.leftHand.materialID]) + getEnchantFromItem(player.leftHand, enchantType_protection).strength : 0;

    int totalProp = armorProt + shieldProt;
    
    int damageDealt = 0;

    if (totalProp < GAME_ENTITIES[attacker->entityType].force)
        player.health -= GAME_ENTITIES[attacker->entityType].force - damageDealt;


    int eamount = getEnchantsAmountFromArray(GAME_ENTITIES[attacker->entityType].possessedEffects, 8);
    //apply the effects of the entity to the player
    for (int i = 0; i < 8; i++)
    {
        if (GAME_ENTITIES[attacker->entityType].possessedEffects[i].enchantID != enchantType_none)
        {
            if (rand()%100 < GAME_ENTITIES[attacker->entityType].possessedEffects[i].certainity)
                addEnchantToPlayer(GAME_ENTITIES[attacker->entityType].possessedEffects[i]);
        }
    }

    //apply the effects of the player's armor to the attacker
    transferNegativeEnchants(player.head.enchants, attacker->sufferingEffects);
    transferNegativeEnchants(player.torso.enchants, attacker->sufferingEffects);
    transferNegativeEnchants(player.leggins.enchants, attacker->sufferingEffects);
    transferNegativeEnchants(player.boots.enchants, attacker->sufferingEffects);
}

void moveTowardsPosition(Vec2 * pos, Vec2* goal)
{
    int deltaX = abs(pos->X - goal->X);
    int deltaY = abs(pos->Y - goal->Y);

    Vec2 motion;
    if (deltaX > deltaY)
        goal->X > pos->X ? motion = {1, 0} : motion = {-1, 0};
    else
        goal->Y > pos->Y ? motion = {0, 1} : motion = {0, -1};
    
    Vec2 newPos = { pos->X + motion.X, pos->Y + motion.Y };
    if (!collidesWithMap(newPos))
        *pos = newPos;
}

void runEntityAI(Entity * entity) //pathfinding and stuff
{
    int diff1 = abs(entity->position.X - player.position.X);
    int diff2 = abs(entity->position.Y - player.position.Y);

    if ((diff1 + diff2) == 1)
        attackPlayer(entity);
    else { //raycast and follow
        if (abs(player.position.X - entity->position.X) <= GAME_ENTITIES[entity->entityType].eyesight && abs(player.position.Y - entity->position.Y) <= GAME_ENTITIES[entity->entityType].eyesight) //if the player is close enough
            if (vec2cmp(castRay(entity->position, player.position), player.position))
                entity->goalPosition = castRay(entity->position, player.position);
        Vec2 toIgnore = { -1, -1 };
        if (!vec2cmp(entity->goalPosition, toIgnore))
            moveTowardsPosition(&entity->position, &entity->goalPosition);
        else
            if (rand() % 20 < GAME_ENTITIES[entity->entityType].agility)
                entity->goalPosition = castRay(entity->position, {
                    entity->position.X + rand() % (GAME_ENTITIES[entity->entityType].agility * 2) - GAME_ENTITIES[entity->entityType].agility, 
                    entity->position.Y + rand() % (GAME_ENTITIES[entity->entityType].agility * 2) - GAME_ENTITIES[entity->entityType].agility
                });
        if ( vec2cmp(entity->goalPosition, entity->position) )
            entity->goalPosition = { -1, -1 };
    }
}

BOOL addEntityToMap(Entity entity) //loops through the map entities register, checks a free slot, then inserts the entity in it and returns true, if not found, it returs false
{
    int i = 0;
    while (i < max_mapEntities && MAP_ENTITIES[i].entityType != entityType_nothing)
    {
        i++;
    }
    if (i < max_mapEntities)
    {
        MAP_ENTITIES[i] = entity;
        return TRUE;
    }
    else {
        return FALSE;
    }
}
void killEntity(Entity * entity)
{
    entity->entityType = entityType_nothing;
    entity->position = { -1, -1 };
}

BOOL attackEntity(Entity * entity) //returns if the entity died or not
{
    //1 is the default punching power

    int damage = (player.rightHand.type == itemType_sword || player.rightHand.type == itemType_axe) ? getMaterialStrength(GAME_MATERIALS[player.rightHand.materialID]) + getEnchantFromItem(player.rightHand, enchantType_sharpness).strength : 2;
    int evadeChanceRoll = rand() % 20;
    int minEvadeBet = GAME_ENTITIES[entity->entityType].agility;
    BOOL hasEntityNotEvaded = evadeChanceRoll > minEvadeBet;
    if (GAME_ENTITIES[entity->entityType].defence < damage && hasEntityNotEvaded) //use the entity's defence and agilty property
        entity->health -= damage+GAME_ENTITIES[entity->entityType].defence;

    //apply the effects of the sword (or anything the player is holding) to the entity, the enchants are always appliead whatsoever
    transferNegativeEnchants(player.rightHand.enchants, entity->sufferingEffects);
    for (int i = 0; i < 8; i++)
    {
        if (player.rightHand.enchants[i].enchantID != enchantType_none)
            if (rand() % 100 < player.rightHand.enchants[i].certainity)
                addEnchantToEntity(entity, player.rightHand.enchants[i]);
    }

    if (entity->health <= 0)
    {
        killEntity(entity);
        return TRUE;
    }
    return FALSE;
}
Entity createEntity(int type, Vec2 position)
{
    Entity entity;
    entity.entityType = type;
    entity.goalPosition = { -1, -1 };
    entity.health = GAME_ENTITIES[type].maxHealth;
    entity.position = position;
    for (int i = 0; i < 8; i++)
    {
        entity.sufferingEffects[i] = createEnchant(enchantType_none, 0, 0);
    }
    return entity;
}

int getEntityAmountFromPosition(Vec2 positon)
{
    int amount = 0;
    for (int i = 0; i < max_mapEntities; i++)
    {
        if (MAP_ENTITIES[i].entityType != entityType_nothing && vec2cmp(positon, MAP_ENTITIES[i].position))
            amount++;
    }
    return amount;
}

Entity getEntityFromPosition(Vec2 position)
{
    int i = 0;
    while (i < max_mapEntities && !(MAP_ENTITIES[i].position.X == position.X && MAP_ENTITIES[i].position.Y == position.Y))
        i++;
    return i < max_mapEntities ? MAP_ENTITIES[i] : createEntity(entityType_nothing, { -1, -1 });
}

Entity * getEntityAddressFromPosition(Vec2 position)
{
    int i = 0;
    while (i < max_mapEntities && !(MAP_ENTITIES[i].position.X == position.X && MAP_ENTITIES[i].position.Y == position.Y))
        i++;
    return i < max_mapEntities ? &MAP_ENTITIES[i] : NULL;
}

int getEntityIDFromPosition(Vec2 position)
{
    int i = 0;
    while (i < max_mapEntities && !(MAP_ENTITIES[i].position.X == position.X && MAP_ENTITIES[i].position.Y == position.Y))
        i++;
    return i < max_mapEntities ? i : operation_failed;
}