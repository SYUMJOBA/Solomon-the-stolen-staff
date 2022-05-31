
/*
Copyright [2022] [John Baxter]

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Syumjoba console's game engine
*/
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
#include "level.h"          //Library that simplifies incredibly the process of loading and saving games // EDIT : it overflows stack, so nevermind
#include "mapGeneration.h"  //Library for proceduralGeneration
#include "filemanager.h"    //Library for loading and saving the data
#include "gameplay.h"       //foundamental library for crucial useful things that wrap the game engine complexity, make the code mroe readable and help the dev to not deteriorate his parent relationship

//this project is heavily commented for the sake of explanation
//as this is intended to be a tool that anybody can use