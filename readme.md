# Solomon - the stolen staff
## discover, fight, revenge
---

```c++
const char* GAME_LORE_PERGAMENE = "\
                                             _______________________      \
   _______________________-------------------                       `\\    \
 /:--__                                                              |    \
||< > |                                   ___________________________/    \
| \\__/_________________-------------------                         |      \
|                                                                  |      \
 |                         The Stolen Staff                        |      \
 |                                                                  |     \
 |      \"In the bountiful land of Caanan                            |     \
  |       once ruled a bright old man                                |    \
  |       Solomon his name, and great his fame,                      |    \
  |       no other king was ever the same.                           |    \
  |       To lead his people on the right path,                      |    \
   |       god granted him a wondrous staff.                          |   \
   |       It brought him riches untold                               |   \
   |       and dazzling mountains of gold                             |   \
   |       Until Judas, the traitor, out of spite                     |   \
   |       stole it to challenge the lord's might.\"                   |  \
  |                                              _____________________|   \
  |  ___________________-------------------------                      `\\ \
  |/`--_                                                                 |\
  ||[ ]||                                            ____________________/\
   \\===/___________________--------------------------                     ";

   //special thanks to Leonardo Ronchi for this small poem!
```

### Why this game?
I always loved exploration and creation games: Terraria, Minecraft, The Blockheads, Space Engineers and Dwarf Fortress have been on my gaming list for years at this point (although dwarf fortress is the latter).
*The Stolen Staff* is my idea of a roguelike, it involves many ideas from these games, trying to reinvent the wheel of the roguelike genre.

This game does not have much to do with the general nieche's characteristics, as this game also has as goals a *crafting and enchanting system* alongside an (already present) mining system and a lot of diversity within the game itself, as it already offers a pretty complex system of materials, entities and enchantments.


### Let's guide you thorugh the creation of a game:
From the main menu, go in "new game" and the game will ask you a name for your dear adventurer. After that, you should be able to dive into the game!


### how to play:
    Once you are in the game, you should be able to move around using the arrow keys.

    Once you spawn you are immediately equipped with a pickaxe and an axe, they will be VERY useful, as you'll have to mine stone and chop wood to go forward in the ddungeon.

    To be able to mine / chop, you have to hold the specific item your player's right hand.

    To hold it first open your inventory, then press 'H' on your keyboard and you should now be seeing your dear axe in your right hand. Now if you try to walk over a woodlike wall, you should chop the wooden wall after some attempts (to increase the efficiency you have enchantments, later on this one)

    "walking over" is the way to interact with many things

this is what happens when you try to walk against specific things:
- walk against entity: you attack it
- walk against wall: you mine it (depending on wht you hold in your hand)
- walk against spawner : you destroy it after three times walking on it

### how to INTERACT with the map:
    you can interact with some tiles of the map, as tiles are indeed STATEFUL. For now, the only tile that actually uses state is the DOOR tile
    The general game principle is: you interact with the map while holding shift and pressing the arrow keys

so: to open a door

- walk next to the door, hold down shift and press the arrow key required to walk towards the door, you'll see the door opening.
- then, unpress the SHIFT key, and you should be able to walk around normally again


BEWARE: if you walk against a door with an axe or a pickaxe (depending on the material of the door) you'll mine it! (except when shifting)

    HINT: you can also use your axe as a weapon (I initally coded axes as if they were battle axes)

look at the player help menu, you should see the keystrokes you're able to punch in the game to do something.

To hide that panel, just press 'H' 

if you press ESC at any moment, you'll see the game mini-menu, where you can 
- exit the game (without saving)
- save the game
- see stats (niy)
- resume the game

watch out for your player health
P.S. you do not have a hunger or thirst system (yet) but you cannot regenerate health points, unless with a regeneration enchantment

### Enchantments:

there are many enchantments, and they work as you'd expect
    
    weapons can inflict enchants on entities
    some entities are immune to some enchants, while most are vulnerable to anything
    enchants affect damage, behaviour and other quirks

## poison
    slowly wears off health
## fiery
    burns the hell out of you (but also aouto-smelts ores if on a pickaxe)
## teleporting
    randomly teleports you somewhere else
## sharpness
    increases the damage dealt from your weapon (also works on ranged)
## freezing
    freezes soemthing in place 
## regeneration
    regens health (this is the only way to regen health)
## efficiency
    increases your chance to destroy a tile
## luck
    increases the possibility to retrieve good stuff from a wall or entity
## protection
    increases armor effictiveness
## clearance
    removes ALL enchants 
## healthBoost
    boosts your health (increases the maximum you have)
## vision
    boosts the distance at wich you can see

Enchants are effective when on armor / equipment or anything really.

An armor can have regeneration on it and you will be affected by it, but if it has poison, it just waits for an entity to attack to inflict the enchant on the entity. (it depends wether or not it is a positive or negative enchat)

NOTE: any item, entity, armor etc... has a maximum of 8 enchants for it

Enchants have an
- type 
- strength
- chance    (only if on a weapon)

pick up a few things and press 'E' again to see your inventory, you can select an item, and peek it when pressing ENTER. Every item has it's quirks defined in the code

## and now, you're good to go
Your goal in the game is to find the "stolen staff", wich is somewhere in the map, it is in a specific room built with "delganium" a specific material reserved for the staff itself.

The moment you pick the item up you immediately won the game.
