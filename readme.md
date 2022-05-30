** SOLOMON : | THE STOLEN STAFF | :**

Sia che tu voglia giocare il gioco o aiutare nello sviluopo, due cose ti serviranno sapere
    1. Questo progetto è una demo, è già giocabile, ma manca un apparato complesso per la generazione procedurale, e il pathfinding (vedi di più in "proiezioni future")
    2. Questo roguelike è fatto con uno spirito e una prospettiva diversa

inoltre, per compilarlo non serve nessuno strumento extra oltre ad un compilatore standard C++ e un sistema operativo Windows (nelle dipendeze si vede perché)

Background e storyline

Il videogioco si svolge in un mondo parallelo (cristiano) dove dio dona a Salomone uno scettro che gli garantisce un gran simbolo. 
Giuda di conseguenza (dal traditore sfrenato che è) la ruba improvvisamente ed è qui che il nostro eroe parte sottoterra, piano piano, fino ada rrivare all'inferno e strappare di mano lo scettro a Giuda


Contenuti e sistemi che animano il gioco
    per spiegare meglio come il gioco è sviluppato, andiamo attraverso tutte le dipendenze presenti nel gioco, vediamo il header principale che include tutto l'engine (che si trova in `.\deps`)



"console_engine.h"
//NOTE : da notare la licenza in "console_engine.h", tutto questo progetto è sotto la licenza apache 2.0

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>        //Base system library|api
#include "debugginglogs.h"  //A library to print things on a txt file for debugging
#include "gameglobals.h"    //global values settings (static, as there is no dynamic memory)
#include "keys.h"           //input system (included string input)
#include "moremath.h"       //some mathematical utility functions
#include "colors.h"         //helper and definer for colors and utilitiy functions
#include "sprites.h"        //for code readibility, predefines char values for the game
#include "items.h"          //Library and register system for the items
#include "materials.h"      //library contianing all the things for the materials in the game
#include "player.h"         //Player functions and characteristics library
#include "map.h"            //Library for the map with procedural generation
#include "entity.h"         //Entity functions and characteristics
#include "structures.h"     //Library for the structures in the game, crafting stations, tombs and so on
#include "crafting.h"       //Library with recipe structures, categories, types and more for crafting
#include "spawners.h"       //Library that adds spawners to the game, so you can procedurally add spawners, and not entites, this makes your life SOOOO EASIER (remember : that's why the Twilight Forest always used spawners, not spawnrules)
#include "screen.h"         //Library for graphics
#include "ui.h"             //Library for UI and quick interfaces
#include "level.h"          //Library that simplifies incredibly the process of loading and saving games
#include "mapGeneration.h"  //Library for proceduralGeneration
#include "filemanager.h"    //Library for loading and saving the data
#include "gameplay.h"       //foundamental library for crucial useful things that wrap the game engine complexity, make the code mroe readable and help the dev to not deteriorate his parent relationship

```
sdtio.h
    standard library (usato solo per gestire i file)

windows.h
    header per le funzioni windows (per questo motivo)

### debugginglog.h
debugginglogs.h
    header per debuggare, molto utile quando si vogliono controllare dei dati nel gioco e stampare info in un file che di default si chiama "debug.txt"
    setupLog()                  : inizializza il file
    addDebugLog(const char *)   : utile per inserire una stringa
    addBinaryNumberToLog(uint)  : utile per stampare un intero bit per bit 
    closeDebug()                : chiudi e salva il debug

    (ci sono alcuni sistemi che vanno a flag binarie), addBinaryNumberToLog() è incredibilmente utile

### gameglobals.h
gameglobals.h
    header contenete variabili globali per l'esecuzione del programma
    //NOTE : siccome non è stata usata memoria dinamica, tutti i contenuti nella mappa soffrono di un limite quantitativo pratico
    //       di conseguenza tutti i massimi sono definiti qui sottoforma di macro

    esempi sono:
        max_mapItems
        max_mapChests
        max_mapEntities
        ...
        
        screen_width
        screen_height

        GAME_MAP_WIDTH
        GAME_MAP_HEIGHT
    
    inserisce anche due struct per i Vettori2D:
        Vec2 (int)      //usato il più possibile per questioni di prestazioni
        Vec2f (double)  //usato in raycasting, dato che l'algoritmo scelto è il DDA

### keys.h
keys.h
    header per gestire input

    questo header è inteso per essere il più semplice possibile, solo due funzioni servono
    1. Input(PKEY_INFO)             : può ritornare quattro stati
                                        key_just_released   3 
                                        key_just_pressed    2   
                                        key_pressed         1         
                                        key_incative        0          
    2. handleStringInput(char *)    : dove il parametro è la destinazione, controlla tutti le struct di KEY_INFO
    questo header inoltre crea tutte le KEY_INFO che possono servire
    tutte sono definite come PKEY_INFO (puntatori di KEY_INFO) e seguono la nomenclatura di:
        Key_ "nome del tasto"
        Key_ESCAPE
        Key_ENTER
        Key_A
        Key_B
        Key_BACK (backspace)
        ...
    
    quindi nel codice si vede solo questo

   ```c
    if ( Input(Key_W) == key_just_pressed ) moveForward(); 
   ```
   il che è semplicemente soddisfacente

moremath.h
    come si può notare, questo header non include "math.h", tutte le funzioni e macro matematiche sono definite qui
    qui troviamo diverse cose fondamentali, tra le quali:
        diverse macro per vare calcolo vettoriale (da usare con discrezione, non in concatenazione)
       ```c
            isPosAdj(pos1, pos2) //restiusce 1 se questi due vettori si stanno toccando
            Vec2diff(pos1, pos2)
            Vec2mul(pos, fac)   
            Vec2sum(pos1, pos2) 
       ```
    
    trovaimo anche
        sin()
        cos()
    funzioni trigonometriche più performanti

    i risultati sono preinsteriti in un tabellone in memoria (che include solo un quarto del cerchio trigonometrico unitario), poi sin() e cos() prendono un angolo risorsa (in gradi) e accederà ad uno specifico indice a seconda di esso; queste due funzioni ci permettono di fare raycasting con prestazioni nettamente superiori

    abbiamo anche
        AABB(COLLISION_BOX, COLLISION_BOX) //axis aligned bounding boxes, ritorna 1 se le due COLLISION_BOX collidono, 0 se si toccano o sono più distanti
        LehmerRand() //funzione estremamente veloce per generazione CONSISTENTE (resettando il seme costantemente), usata per renderizzarizzare texture procedurali
                    //nome strabello per indicare il comportamento grafico del pavimento non levigato
        nLehmer_seed //seme per lehmer (che in realtà si comporta più come offset)
        clamp(min, value, max) : int //ritorna "value" compreso tra min e max
        clampPosition(min, vallue, max) : Vec2 //la stessa cosa di clamp() ma con i vettori
        isVec2Equal(Vec2, Vec2) //ritorna se i due vettori sono uguali o no

### colors.h
colors.h
    questo progetto è interamente in console, e sfrutta i colori nel miglior modo possibile
    questo header definise in macro tutti i colori per la console,
    individualmente sia per:
        Foreground  : colore testo          : `Fg_<colorName>`
        Background  : colore evidenziazione : `Bg_<colorName>`

    //NOTE : il tipo di dato per il colore è definito nel codice come : `Attribute`

    inoltre ci sono quattro utili funzioni:
    getBgColor(Attribute)
    getFgColor(Attribute)
    ToBgColor(Attribute)
    ToFgColor(Attribute)

### sprites.h
sprites.h
    ha molti caratteri di ASCII Esxtended definiti come macro
    esempi sono:
        char_heart
        char_alpha
        ...

        uiSprite_cross
        uiSprite_top_right
        ...

        tileSprite_liquidSingle
        tileSprite_liquidDouble
        //per "tilesprite" non ce ne sono altre, sono immesse nel gioco di per sé

### items.h
items.h
    iniziando ad andare più nella pasta vera e propria del gioco
    `typedef struct Item {} Item, *PItem;` contiene tutti i dati necessari per un singolo Item,
    ci sono introle incantamenti, 

    tutti i "type" sono differenziati con ristretti ID, sia per incantamenti che per item
    //NOTE : il material dentro ad un Item è molto importante, in qaunto le prorietà di un item vengono calcolate da
        1. materiale
        2. qualità
        3. incantamenti
    il "tipo" indica solo _cosa deve fare_

    ```c
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
    ```

    ci sono inoltre diverse funzioni importanti come
    createItem()                                            //agisce come da costruttuttore per Item
    createEnchant()                                         //agisce come da costruttuttore per Enchantment                              
    const char *getItemTypeFromEnum(int itemType)           : }
    const char *getQualityTypeFromEnum(int quality)         :   fondamentali, ritornano la stringa descrittiva associata al tipo
    const char *getEnchantTypeFromEnum(int enchantType)     : } 
    void transferPositiveEnchants(Enchantment* source, Enchantment* destination)    : }
    void transferNegativeEnchants(Enchantment* source, Enchantment* destination)    : } abbastanza importanti, queste funzioni servono per infliggere incantamenti al giocatore o qualunque altro corpo possedente un'array di enchant (passando l'array di enchant dentro)


    //ci sono poi molte utility che possono tornare utili come
    BOOL isItemArmor(Item item)
    addItemToChest()
    getChestInventoryLength()
    ...
    più o meno qualunque cosa di base che serva c'è

    registri che contengono informazioni sono 
    CHAR_INFO ENCHANTS_DECOS[32]    //tutti associati per indice "enchantID"
    const char ITEMS_SPRITES[64]    //tutti associati per indice "type"
    ENCHANT_POSITIVITY_REGISTER[32] //tutti associati per indice "enchantID"

    nota qeste due macro:
   ```c
    #define isEnchantPositive(type) ENCHANT_POSITIVITY_REGISTER[type]
    #define isEnchantNegative(type) !ENCHANT_POSITIVITY_REGISTER[type]
   ```

    questi sono tutti i tipi di item presenti nel gioco per ora (non tutti hanno interazioni completatate, le interazioni sono in una dipendenza finale : "gameplay")
    ```c
    #define itemType_noItem -1
    #define itemType_undefined 0 //also counts as 'any'
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
    #define itemType_underChestplate 
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
    #define itemType_stolenStaff 29
   ```
   questi sono tutti i tipi di incantamenti:(tutti funzionano correttamente nelle meccaniche del gioco)
  ```c
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
  ```

  REGISTRO FONDAMENTALE:
    Item MAP_ITEMS[] è la lista contenete tutti gli item presenti nella mappa, la mappa poi punta ad essa con la proprietà interna (alla Tile della mappa) `containedID` che sarà mostrata dopo in map.h

### materials.h
materials.h
    questo header contiene tutte le informazioni relative ai materiali
   ```c
    typedef struct Material
    {
    unsigned short color; // analogous for windows.h 's WORD type
    WCHAR symbol;         // if there isn't any, just put ' ', the symbol is used to represent
    unsigned int flags;   // flags for the material : acid will be treated in a way, lava in another one ... and so on ...
    char name[16];
    unsigned short rawItemID; // flags what item TYPE should the material display as, in case it breaks
    } Material, *PMaterial;

    Material GAME_MATERIALS[game_totalMaterials]; //game materials register
   ```

    è in GAME_MATERIALS[] che stanno tutte le informazioni, ogni MaterialID punta qui

   tutti i materiali hanno "proprietà", sia grafiche che fisiche
   
    queste sono tutte le flag presenti in `Material{};`
    FLAGS in Material: 
    //NOTE : le flag sono un `unsigned int`, qui si indicano tutte le proprietà possibili, a seconda della posizione del bit
    
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

    unsigned int createMaterialProps(...props[]) //questa funzione di permette di celermente 

    setupMaterials() è la funzione chiamata in fase _load_ del gioco, per inserire tutte le proprietà dei materiali necessarie per il gioco
    
    ci sono anche un paio di funzioni utili per l'enumerazione:
    const char *getMaterialTypeFromEnum(int type)
    int getItemForMaterialType(int materialType)


### Player
   ```c
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
   ```

    il giocatore ha diverse proprietà, più alcune pensate per piani futuri (come hunger e thirst)
    ho preferito focalizzarmi sulla parte grafica e gestionale che la fame e la sete, credo che
    un punto di forza di questo gicoo è la possiblità di esplorare, ed essere limitati da fame e 
    sete che ti salgono addosso credo sia una limitazione

    PLAYER_VISMAP[GAME_MAP_HEIGHT * GAME_MAP_WIDTH]; il giocatore ha la sua VISMAP, che viene aggiornata da una funzione in "gameplay.h"
    è a seconda di VISMAP cosa vada e non vada visualizzato
    vismap è un array di int, e può contenere tre stati (la cambierò sicuramente a char o un datatype più piccolo se non serve a nulla)
   ```c
    #define vismap_tileUndiscovered 0   //non renderizzato
    #define vismap_tileSeen 1           //renderizzato ma senza entità e altri oggetti in movimento
    #define vismap_tileInView 2         //renderizzato completamente
   ```
   l'incantamento VISION incrementa la visibilità (il gicoatore vede più lontano)


    setupPlayer() //inizializza il giocatore
    qui ci sono inoltre diverse funzioni per gestire l'inventario e ricavare info dal player
        BOOL addItemToInventory(Item item) // return TRUE if operation is succesfull, FALSE if
        int findItemFromInventory(Item item)
        void removeItemFromInventory(int id) // removes the item located at that position in the inventory
        int getPlayerInventoryLength()

    inoltre, il giocatore ha i suoi slot, per l'equipaggamento
        Item *getPlayerSlot(int slot) //per prendere il puntanto allo slot
        BOOL equipItem(int inventoryId) equipaggia un item dal suo inventario
        BOOL unEquipItem(int slot) // rimuove un oggetto dall'equipaggiamento, sotituendolo

       ```c
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
       ```
    
### map.h
map.h
    definizioni e utility:
   ```c
    
    //For gorund layer
    #define groundTiletype_roughFloor 0
    #define groundTiletype_smoothGround 1
    #define groundTiletype_upSlope 2
    #define groundTiletype_downSlope 3
    #define groundTileType_liquid 4

    //For wall layer
    #define wallTiletype_noWall -1
    #define wallTiletype_roughWall 0
    #define wallTiletype_smoothWall 1
    #define wallTiletype_engravedWall 2
    #define wallTiletype_bookshelf 3
    #define wallTiletype_statue 4
    #define wallTiletype_chair 5
    #define wallTiletype_table 6
    #define wallTiletype_bed 7
    #define wallTiletype_door 8
    #define wallTiletype_chest 9
    #define wallTiletype_barrel 10
    #define wallTiletype_downStairs 11
    #define wallTiletype_upStairs 12
    #define wallTiletype_udStairs 13

    //for doors
    #define doorState_open 0
    #define doorState_closed 1

    //for generation
    #define onGround 0
    #define onWalls 1

    char USABLE_ROUGH_GROUND_CHARS[10] = {'.', ',', '`', '\'', '\'', '.', ',', '.', char_middleDot, char_middleDot};
    char USABLE_LIQUID_GROUND_CHARS[2] = {tileSprite_liquidDouble, tileSprite_liquidSingle};

   ```
   come potete vedere tutti le proprietà hanno la loro utilità, sono tutti possibili valori da mettere negli enumeratori della struct WorldTile
  ```c
    WorldTile createTile(int mat, int type, int cont, int state)
    {
        WorldTile tmpTile;
        tmpTile.materialID = mat;
        tmpTile.type = type;
        tmpTile.containedID = cont;
        tmpTile.state = state;
        return tmpTile;
    }

    typedef struct Trap {
        BOOL discovered;
        Enchantment effect; 
        Vec2 position;
    } Trap, *PTrap;

    Trap MAP_TRAPS[max_mapTraps];
    WorldTile GAME_GROUND[GAME_MAP_HEIGHT*GAME_MAP_WIDTH];  //registro con le Tile per il pavimento
    WorldTile GAME_WALLS[GAME_MAP_HEIGHT*GAME_MAP_WIDTH];   //registro con le Tile per il muro
  ```

        ```c
        /*
        how the gorund should display:
        ███████████████████████████ -.
        █',.`,',█++++++++█≈~≈~≈≈~~█  |
        █,.`X'.`╪+++++X++█≈≈~~≈~≈≈█  | these are walls instead, part of the WALLS
        █',.`,',█++++++++█~~≈~≈~≈~█  |
        ███████████████████████████ -'
            ^       ^        ^
            |       |        |
        rough   smooth   water

        type of ground is defined in: ` <WorldTile>.type `

        where (if the material is solid):
        {
            0 : 'rough'
            1 : 'smooth'
            2 : 'upSlope'
            3 : 'downSlope'
            4 : 'liquid'
        }

        but if the material is liquid, regardless of `type` the charecter represented will be ~ or ≈

        so:
        ground tiles occupied by ground have:
        black background
        charecter depending on Type
        color depending on the original specified background
        if ContainedID is different from -1, it acts as a pointer to GAME_ITEMS, as it means there is *item* on the ground


        the map.h, there's a cool array called rough_ground_symbols[] and it stores all the symbols that a rough ground could have. Each Tile has a random one


        how the walls should display:
        ██████████░████████████████
        ░▒▓
        walls are a little trickier:
        
        Type accounts for:
        {
            -1: no wall there
            0 : rough wall
            1 : smooth wall
            2 : engraved wall
            3 : bookshelf
            4 : statue
            5 : chair
            6 : table
            7 : bed
            8 : door
            9 : chest
            10 : barrel //SLATED FOR FUTURE UPDATE
        }
        in the case of a rough wall : 
        the tile's color is the default background and foreground
        the tile's symbol is the default symbol
        but if there's a contained material:
            the tile's foreground is the default contained foreground
            the tile's symbol is the default contained symbol
        
        in case of a smooth wall:
        the tile's background is black
        the tile's foreground is the default backgorund
        the tile's symbol is the UI window delimiter charecter, it changes depending on neughbouring cells
        if the tile has only one or zero connections:
            the tile will be a pillar : 'O'
        if the tile has more connections:
            the tile UI component will be the one with those connections

                here's the tileset:     ╔╦╗ O
                                        ╠╬╣ ═
                                        ╚╩╝ ║

        in case of an engraved wall:
        the internal symbol is 'Θ'
        the Fg color is black
        the Bg color is default

        in any other case:
        color is default color
        symbol is default symbol

        if type is > than 2 : it's probably a piece of furniture
        if chair : 
            symbol : ╥
            color : default background to foreground
        if table : 
            symbol : ╤
            color : default background to foreground
        if bed :
            symbol : Θ
            color : default background to foreground
        if bookshelf : 
            symbol : ≡ 
            color : default with black foreground
        if chest :
            symbol : Æ
            color : default background to foreground
        if door :
            symbol : |
            color : default with black foreground



        the roubgh walls use background to display themselves
        */
        ```

    questi sono tutti i dettagli della mappa
    nell'header map.h ci sono anche le seguenti funzioni:
        pulisci (resetta) le trappe o la mappa
            clearMap() / clearTraps()

        void createMapRectangle(Vec2 center, Vec2 size, int level, WorldTile wt)                                                //crea un rettangolo nella mappa 
        void createHollowMapRectangle(Vec2 center, Vec2 size, int level, WorldTile wt)                                          //crea un rettangolo vuoto nella mappa
        void createRoom(Vec2 center, Vec2 size, int doorSide, int wallType, int material, int groundType, int groundMaterial)   //crea una stanza (rettangolo per terra con un rettangolo vuoto nei muri)

        BOOL collidesWithMap(Vec2 position) //verifica se la tile presa da questa posizione collide (una porta chiusa o un muro)
        
        int placeNewChest(Vec2 position, int material) //alloca una nuova cesta nel registro per le ceste, e assegna alla tile in `position` l'id che corrisponde alla cesta (effettivamente installando una cesta in quella tile). ritorna l'indice della cesta nel registro o, se ci sono stati errori, `operation_failed` (#define operation_failed 1)
        

