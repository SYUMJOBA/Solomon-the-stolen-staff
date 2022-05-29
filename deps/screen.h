#pragma once

/*
A bit of words to standardize stuff

starting word  |    intended use   |
---------------|-------------------|
  draw         |using an value present in memory and draw it onto the game screen
  paint        |writing on the screen values given in the function (like creatign a __red__ line, rather than "draw this predefined rectangle on the screen from memory")
  generate     |creating in real time a value and using it fo draw on the screen (yes, procedural generation)

*/

CHAR_INFO game_screen[screen_height * screen_width]; // will be treated later as a matrix with some funky pointer arithmetic

COORD write_start = {0, 0};
COORD write_size = {screen_width, screen_height};

SMALL_RECT write_region = {0, 0, screen_width, screen_height};

#define getPixel(x, y) game_screen[y*screen_width+x]


// I'm afrain of a segmentation fault right here ... NAD NO THERE WON'T BE!
HANDLE h;

CHAR_INFO screenshot_register[screen_height * screen_width];
// CONSOLE_FONT_INFOEX consoleInfo;

BOOL isScreenCaptureActive = FALSE;

BOOL setupConsole()
{
    for (int i = 0; i < screen_height * screen_width; i++)
    {
        screenshot_register[i].Char.UnicodeChar = ' ';
        screenshot_register[i].Attributes = 0x0f;
    }
    h = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    // GetCurrentConsoleFontEx(h, TRUE, &consoleInfo);
    // SetCurrentConsoleFontEx(h, TRUE, &consoleInfo);
    return SetConsoleActiveScreenBuffer(h);
}

void updateScreen()
{
    WriteConsoleOutput(h, game_screen, write_size, write_start, &write_region);

    write_region.Right = screen_width;
    write_region.Bottom = screen_height;
    if (isScreenCaptureActive)
    {
        for (int i = 0; i < screen_height * screen_width; i++)
        {
            game_screen[i].Char.UnicodeChar = screenshot_register[i].Char.UnicodeChar;
            game_screen[i].Attributes = screenshot_register[i].Attributes;
        }
    }
    else
    {
        for (int i = 0; i < screen_height * screen_width; i++)
        {
            game_screen[i].Char.UnicodeChar = ' ';
            game_screen[i].Attributes = 0x0f;
        }
    }
}

void paintText(const char *message, Vec2 start)
{
    /*
    Takes the message to be painted and writes it from "start" point (be wary, whitespace wraps)
    */
    for (int x = start.X; (unsigned)x < strlen(message) + start.X; x++)
    {
        game_screen[start.Y * screen_width + x].Char.UnicodeChar = message[x - start.X];
    }
}

int paintText(int number, Vec2 start) //returns the length of the printed char array
{
    char text[10] = "";
    _itoa(number, text, 10);
    for (int x = 0; (unsigned)x < strlen(text); x++)
    {
        game_screen[start.Y * screen_width + start.X + x].Char.UnicodeChar = text[x];
    }
    return strlen(text);
}

void paintText(double number, Vec2 start)
{
    char text[10];
    _gcvt(number, 6, text);
    for (int x = 0; (unsigned)x < strlen(text); x++)
    {
        game_screen[start.Y * screen_width + start.X + x].Char.UnicodeChar = text[x];
    }
}


void drawRectangle(CHAR_INFO *rectangle, Vec2 position, Vec2 size)
{
    for (int y = 0; y <= size.Y; y++)
    {
        for (int x = 0; x <= size.X; x++)
        {
            game_screen[y * screen_width + x].Char.UnicodeChar = rectangle[size.Y * y + x].Char.UnicodeChar;
            game_screen[y * screen_width + x].Attributes = rectangle[size.Y * y + x].Attributes;
        }
    }
}

void drawRectangle(const char *rectangle, Vec2 position, Vec2 size)
{
    for (int y = 0; y <= size.Y; y++)
    {
        for (int x = 0; x <= size.X; x++)
        {
            game_screen[(y + position.Y) * screen_width + x + position.X].Char.UnicodeChar = rectangle[y * size.X + x];
        }
    }
}

void drawRectangle(Attribute *rectangle, Vec2 position, Vec2 size)
{
    /*
    Takes the rectangle's pointer in memory, draws it from a starting point
    respecting the sizes specified in the "size"
    */
    for (int y = 0; y <= size.Y; y++)
    {
        for (int x = 0; x <= size.X; x++)
        {
            game_screen[y * screen_width + x].Attributes = rectangle[size.Y * y + x];
            game_screen[y * screen_width + x].Attributes = rectangle[size.Y * y + x];
        }
    }
}

void paintRectangle(Attribute attribute, Vec2 Vertex1, Vec2 Vertex2)
{
    /*
    Takes a start vertex and an end vertex, creates a rectangle on the screen
    that occupies the space within the 2 verticies (extremises included)
    */
    for (int y = Vertex1.Y; y <= Vertex2.Y; y++)
    {
        for (int x = Vertex1.X; x <= Vertex2.X; x++)
        {
            game_screen[y * screen_width + x].Attributes = attribute;
        }
    }
}

void paintRectangle(char charecter, Vec2 Vertex1, Vec2 Vertex2)
{
    /*
    Takes a start vertex and an end vertex, creates a rectangle on the screen
    that occupies the space within the 2 verticies
    */
    for (int y = Vertex1.Y; y <= Vertex2.Y; y++)
    {
        for (int x = Vertex1.X; x <= Vertex2.X; x++)
        {
            game_screen[y * screen_width + x].Char.UnicodeChar = charecter;
        }
    }
}

void paintRectangle(CHAR_INFO data, Vec2 Vertex1, Vec2 Vertex2)
{
    /*
    Takes a start vertex and an end vertex, creates a rectangle on the screen
    that occupies the space within the 2 verticies
    */
    for (int y = Vertex1.Y; y <= Vertex2.Y; y++)
    {
        for (int x = Vertex1.X; x <= Vertex2.X; x++)
        {
            game_screen[y * screen_width + x].Attributes = data.Attributes;
            game_screen[y * screen_width + x].Char.UnicodeChar = data.Char.UnicodeChar;
        }
    }
}

//My edit of the DDA line drawing algorythm
void paintDDALine(CHAR_INFO data, Vec2 start, Vec2 finish)
{
    int dx = abs(finish.X - start.X);
    int dy = abs(finish.Y - start.Y);
    int step;

    if (dx >= dy)
    {
        step = dx;
    }
    else {
        step = dy;
    }
    double xin = finish.X > start.X ? (double)dx / (double)step : (double)dx / (double)step * -1;
    double yin = finish.Y > start.Y ? (double)dy / (double)step : (double)dy / (double)step * -1;
    double x = start.X + 0.5;
    double y = start.Y + 0.5;

    for (int i = 0; i < step; i++)
    {
        x += xin;
        y += yin;
        game_screen[(int)y * screen_width + (int)x] = data;
    }
}

void paintLine(Attribute attribute, Vec2 start, Vec2 end)
{
    // Function takes a starting point, and end point, and draws a line that goes from one to the other

    if (start.X == end.X) // Vertical
    {
        for (int y = start.Y; y < end.Y; y++)
        {
            game_screen[y * screen_width + start.X].Attributes = attribute;
        }
    }
    else if (start.Y == end.Y) // Horizontal
    {
        for (int x = start.X; x < end.X; x++)
        {
            game_screen[screen_width * start.Y + x].Attributes = attribute;
        }
    } //diagonal not needed, really
}

void paintLine(char charecter, Vec2 start, Vec2 end)
{
    // Function takes a starting point, and end point, and draws a line that goes from one to the other

    if (start.X == end.X) // Vertical
    {
        for (int y = start.Y; y < end.Y; y++)
        {
            game_screen[y * screen_width + start.X].Char.UnicodeChar = charecter;
        }
    }
    else if (start.Y == end.Y) // Horizontal
    {
        for (int x = start.X; x < end.X; x++)
        {
            game_screen[screen_width * start.Y + x].Char.UnicodeChar = charecter;
        }
    } //diagonal not needed, really
}

void paintLine(Attribute attribute, Vec2 start, int length)
{
    /*
    function paints a horizontal line beginning from "start", as long as "length" with "attribute"
    */
    for (int x = 0; x < length; x++)
    {
        game_screen[start.Y * screen_width + x + start.X].Attributes = attribute;
    }
}

void coloredText(const char *text, Attribute color, Vec2 start)
{
    // function paints horizontally some text, also applying the color, from start point
    for (int i = 0; (unsigned)i < strlen(text); i++)
    {
        int i2 = start.Y * screen_width + i + start.X;
        game_screen[i2].Char.UnicodeChar = text[i];
        game_screen[i2].Attributes = color;
    }
}

void paintPixel(char charecter, Vec2 position)
{
    game_screen[screen_width * position.Y + position.X].Char.UnicodeChar = charecter;
}

void paintPixel(Attribute attribute, Vec2 position)
{
    game_screen[screen_width * position.Y + position.X].Attributes = attribute;
}

void paintPixel(CHAR_INFO data, Vec2 position)
{
    game_screen[screen_width * position.Y + position.X].Attributes = data.Attributes;
    game_screen[screen_width * position.Y + position.X].Char.UnicodeChar = data.Char.UnicodeChar;
}

// If you want the screen to paint a certain frame in the background rather than the default spaces with the black background, you can call
// screeCapture() to set the current frame as the next background, and it will be used until you call unScreenCapture()
// calling screeCapture() multiple times without unScreenCapture() will just result in an updated bg
void screenCapture()
{
    for (int i = 0; i < screen_height * screen_width; i++)
    {
        screenshot_register[i].Char.UnicodeChar = game_screen[i].Char.UnicodeChar;
        screenshot_register[i].Attributes = game_screen[i].Attributes;
    }
    isScreenCaptureActive = TRUE;
}

void unScreenCapture()
{
    isScreenCaptureActive = FALSE;
}

Vec2 mapToScreenOffset = { 0, 0 };

void drawGroundWorldTile(Vec2 screenPosition, Vec2 worldPosition)
{
    WorldTile tile = GAME_GROUND[worldPosition.Y*GAME_MAP_WIDTH+worldPosition.X];
    int screenLocation = screenPosition.Y * screen_width + screenPosition.X;
    if (tile.containedID == itemType_noItem)
    {
        switch (tile.type)
        {
        case groundTiletype_roughFloor:
        {
            nLehmer_seed = (mapToScreenOffset.Y + screenPosition.Y) * GAME_MAP_WIDTH + screenPosition.X + mapToScreenOffset.X;
            game_screen[screenLocation].Char.UnicodeChar = USABLE_ROUGH_GROUND_CHARS[LehmerRand() % 10];
            game_screen[screenLocation].Attributes = toFgColor(getBgColor(GAME_MATERIALS[tile.materialID].color));
            break;
        }

        case groundTiletype_smoothGround:
        {
            game_screen[screenLocation].Char.UnicodeChar = '+';
            game_screen[screenLocation].Attributes = toFgColor(getBgColor(GAME_MATERIALS[tile.materialID].color));
            break;
        }

        case groundTileType_liquid:
        {
            game_screen[screenLocation].Char.UnicodeChar = USABLE_LIQUID_GROUND_CHARS[rand() % 2];
            game_screen[screenLocation].Attributes = toFgColor(getBgColor(GAME_MATERIALS[tile.materialID].color));
            break;
        }

        default:
        {
            game_screen[screenLocation].Char.UnicodeChar = GAME_MATERIALS[tile.materialID].symbol;
            game_screen[screenLocation].Attributes = GAME_MATERIALS[tile.materialID].color;
            break;
        }
    }
    } else {
        game_screen[screenLocation].Attributes = toFgColor(GAME_MATERIALS[MAP_ITEMS[tile.containedID].materialID].color);
        game_screen[screenLocation].Char.UnicodeChar = ITEMS_SPRITES[MAP_ITEMS[tile.containedID].type];
    }
}
void drawWallWorldTile(Vec2 screenPosition, Vec2 worldPosition)
{   
    WorldTile tile = GAME_WALLS[worldPosition.Y*GAME_MAP_WIDTH+worldPosition.X];
    if (tile.type != -1) // If the wall exists
    {
        int mapLocation = worldPosition.Y*GAME_MAP_WIDTH+worldPosition.X;
        int screenLocation = screenPosition.Y*screen_width+screenPosition.X;
        switch (tile.type)
        {
        case wallTiletype_roughWall:
            if (-1 != tile.containedID) // Contained material checking
            {
                // There is a contained material in the wall
                game_screen[screenLocation].Attributes = getBgColor(GAME_MATERIALS[tile.materialID].color) + toFgColor(getBgColor(GAME_MATERIALS[tile.containedID].color));
                game_screen[screenLocation].Char.UnicodeChar = GAME_MATERIALS[tile.containedID].symbol;
            }
            else
            {
                // There is no contained material in the wall, so you shall render it plainly
                game_screen[screenLocation].Char.UnicodeChar = GAME_MATERIALS[tile.materialID].symbol;
                game_screen[screenLocation].Attributes = GAME_MATERIALS[tile.materialID].color;
            }
            break;
        case wallTiletype_smoothWall:
        {
            game_screen[screenLocation].Attributes = toFgColor(getBgColor(GAME_MATERIALS[tile.materialID].color));
            // This codeblock will calculate what and wich neighboring blocks are there
            unsigned int dirFlags = 0b0000;
            /*bit   | relation ---> for the flags to work
                1. top
                2. right
                3. bottom
                4. left
            */
            if (GAME_WALLS[mapLocation - GAME_MAP_WIDTH].type == wallTiletype_smoothWall)
            { // Above
                dirFlags = dirFlags | 0b1000;
            }
            if (GAME_WALLS[mapLocation + 1].type == wallTiletype_smoothWall)
            { // Right
                dirFlags = dirFlags | 0b0100;
            }
            if (GAME_WALLS[mapLocation + GAME_MAP_WIDTH].type == wallTiletype_smoothWall)
            { // Below
                dirFlags = dirFlags | 0b0010;
            }
            if (GAME_WALLS[mapLocation - 1].type == wallTiletype_smoothWall)
            { // Left
                dirFlags = dirFlags | 0b0001;
            }
            /*
                    here's the tileset:  ╔╦╗ O
                                         ╠╬╣ ═
                                         ╚╩╝ ║
            */
            // Now, depending on the neighbours, a different char will be placed
            switch (dirFlags)
            {
            case 0b0011: // left & bottom
            {
                game_screen[screenLocation].Char.UnicodeChar = uiSprite_bottom_left; // + '╗'
                break;
            }

            case 0b0101: // right & left
            {
                game_screen[screenLocation].Char.UnicodeChar = uiSprite_horizontal; // + '═'
                break;
            }

            case 0b0110: // right & bottom
            {
                game_screen[screenLocation].Char.UnicodeChar = uiSprite_right_bottom; // + '╔'
                break;
            }

            case 0b1001: // top & left
            {
                game_screen[screenLocation].Char.UnicodeChar = uiSprite_top_left; // + '╝'
                break;
            }

            case 0b1100: // top & right
            {
                game_screen[screenLocation].Char.UnicodeChar = uiSprite_top_right; // + '╚'
                break;
            }

            case 0b1010: // top & bottom
            {
                game_screen[screenLocation].Char.UnicodeChar = uiSprite_vertical; // + '║'
                break;
            }

            case 0b1110: // top & bottom & right
            {
                game_screen[screenLocation].Char.UnicodeChar = uiSprite_top_right_bottom; // + '╠'
                break;
            }

            case 0b1011: // top & bottom & left
            {
                game_screen[screenLocation].Char.UnicodeChar = uiSprite_top_bottom_left; // + '╣'
                break;
            }

            case 0b0111: // left & bottom & right
            {
                game_screen[screenLocation].Char.UnicodeChar = uiSprite_right_bottom_left; // + '╦'
                break;
            }

            case 0b1101: // top & bottom & left
            {
                game_screen[screenLocation].Char.UnicodeChar = uiSprite_top_right_left; // + '╩'
                break;
            }

            case 0b1111:
            {
                game_screen[screenLocation].Char.UnicodeChar = uiSprite_cross; // + '╬'
                break;
            }
            default: // Only not tested cases depend on a single bit ON, wich all mean a Pillar
            {
                game_screen[screenLocation].Char.UnicodeChar = uiSprite_pillar; // + 'O'
            }
            }
            break;
        }
        // If the wall is engraved
        case wallTiletype_engravedWall:
        {
            game_screen[screenLocation].Char.UnicodeChar = (char)0x1; //+ 'º';
            game_screen[screenLocation].Attributes = getBgColor(GAME_MATERIALS[tile.materialID].color) + Fg_Black;
            break;
        }

        case wallTiletype_bookshelf:
        {
            game_screen[screenLocation].Attributes = getBgColor(GAME_MATERIALS[tile.materialID].color) + Fg_Black;
            break;
        }

        case wallTiletype_statue:
        {
            game_screen[screenLocation].Attributes = toFgColor(getBgColor(GAME_MATERIALS[tile.materialID].color));
            game_screen[screenLocation].Char.UnicodeChar = (char)0xea; // + 'Ω';
            break;
        }

        case wallTiletype_chair:
        {
            game_screen[screenLocation].Attributes = toFgColor((getBgColor(GAME_MATERIALS[tile.materialID].color)));
            game_screen[screenLocation].Char.UnicodeChar = (char)0xd2; // + '╥';
            break;
        }

        case wallTiletype_table:
        {
            game_screen[screenLocation].Attributes = toFgColor((getBgColor(GAME_MATERIALS[tile.materialID].color)));
            game_screen[screenLocation].Char.UnicodeChar = (char)0xd1; // + '╤';
            break;
        }
        case wallTiletype_bed:
        {
            game_screen[screenLocation].Attributes = toFgColor((getBgColor(GAME_MATERIALS[tile.materialID].color)));
            game_screen[screenLocation].Char.UnicodeChar = (char)0xe9; // + 'Θ';
            break;
        }
        case wallTiletype_door:
        {
            game_screen[screenLocation].Attributes = (getBgColor(GAME_MATERIALS[tile.materialID].color)) + Fg_Black;
            game_screen[screenLocation].Char.UnicodeChar = (char)0xb3; // + '│';
            break;
        }
        case wallTiletype_chest:
        {
            game_screen[screenLocation].Attributes = toFgColor((getBgColor(GAME_MATERIALS[tile.materialID].color)));
            game_screen[screenLocation].Char.UnicodeChar = (char)0x92; // + 'Æ';
            break;
        }

        case wallTiletype_udStairs:
        {
            game_screen[screenLocation].Attributes = toFgColor((getBgColor(GAME_MATERIALS[tile.materialID].color)));
            game_screen[screenLocation].Char.UnicodeChar = 'X';
        }

        case wallTiletype_upStairs:
        {
            game_screen[screenLocation].Attributes = toFgColor((getBgColor(GAME_MATERIALS[tile.materialID].color)));
            game_screen[screenLocation].Char.UnicodeChar = '>';
        }

        case wallTiletype_downStairs:
        {
            game_screen[screenLocation].Attributes = toFgColor((getBgColor(GAME_MATERIALS[tile.materialID].color)));
            game_screen[screenLocation].Char.UnicodeChar = '<';
        }
        default:
            break;
        }
    }
}

void drawWorldPosition(Vec2 screenPosition, Vec2 worldPosition){
    if (GAME_WALLS[worldPosition.Y*GAME_MAP_WIDTH + worldPosition.X].type != wallTiletype_noWall)
    {
        drawWallWorldTile(screenPosition, worldPosition);
    } else {
        drawGroundWorldTile(screenPosition, worldPosition);
    }
}

// This function draws the entire world on the screen, fetching the GAME_GROUND and GAME_WALLS, layering them
// Using a X and Y offset
void drawWorld() // this function is separate from a "drawEntites" function
{                //'draw' is something that comes from memory
    for (int y = 0; y < screen_height; y++)
    {
        for (int x = 0; x < screen_width; x++)
        {

            // Calling that sweet function
            drawWorldPosition({x, y}, {x + mapToScreenOffset.X, y + mapToScreenOffset.Y});
        }
    }
}

void paintCirle(CHAR_INFO graphicData, Vec2 fulcrus, int radius, int start, int finish)
{
    for (int i = start; i < finish; i++)
    {
        getPixel(
            (int)(cos(i) * radius + fulcrus.X),
            (int)(sin(i) * radius + fulcrus.Y)
        ) = graphicData;
    }

}