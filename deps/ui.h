void frame(Attribute color, Vec2 Pos1, Vec2 Pos2){
        paintLine( (char)0xBA, {Pos1.X, Pos1.Y}, {Pos1.X, Pos2.Y});
        paintLine( (char)0xBA, {Pos2.X, Pos1.Y}, {Pos2.X, Pos2.Y});
        paintLine( (char)0xCD, {Pos1.X, Pos1.Y}, {Pos2.X, Pos1.Y});
        paintLine( (char)0xCD, {Pos1.X, Pos2.Y}, {Pos2.X, Pos2.Y});
        paintPixel((char)0xC9, {Pos1.X, Pos1.Y});
        paintPixel((char)0xC8, {Pos1.X, Pos2.Y});
        paintPixel((char)0xBB, {Pos2.X, Pos1.Y});
        paintPixel((char)0xBC, {Pos2.X, Pos2.Y});

        paintLine( color, {Pos1.X, Pos1.Y}, {Pos1.X, Pos2.Y});
        paintLine( color, {Pos2.X, Pos1.Y}, {Pos2.X, Pos2.Y});
        paintLine( color, {Pos1.X, Pos1.Y}, {Pos2.X, Pos1.Y});
        paintLine( color, {Pos1.X, Pos2.Y}, {Pos2.X, Pos2.Y});
        paintPixel(color, {Pos1.X, Pos1.Y});
        paintPixel(color, {Pos1.X, Pos2.Y});
        paintPixel(color, {Pos2.X,Pos1.Y});
        paintPixel(color, {Pos2.X, Pos2.Y});
};

void showItemFullName(Item item, Vec2 startPosition){
    char itemInfo[64] = "";
    strcat(itemInfo, " ");
    strcat(itemInfo, getQualityTypeFromEnum(item.quality));
    strcat(itemInfo, " ");
    strcat(itemInfo, GAME_MATERIALS[item.materialID].name);
    strcat(itemInfo, " ");
    strcat(itemInfo, getItemTypeFromEnum(item.type));
    coloredText(itemInfo, toFgColor(GAME_MATERIALS[item.materialID].color), startPosition);
}
void showItemInfo(Item item, Vec2 startPosition){
    if (item.type != itemType_noItem)
    {
        char tmpString[36] = "";
        strcat(tmpString, getQualityTypeFromEnum(item.quality));
        strcat(tmpString, " ");
        strcat(tmpString, GAME_MATERIALS[item.materialID].name);
        strcat(tmpString, " ");
        strcat(tmpString, getItemTypeFromEnum(item.type));
        coloredText(tmpString, toFgColor(GAME_MATERIALS[item.materialID].color), startPosition);
        for (int i = 0; i < getEnchantsAmountFromItem(item); i++)
        {
            paintPixel(ENCHANTS_DECOS[item.enchants[i].enchantID], {startPosition.X+36+i, startPosition.Y});
        }
    } else {
        coloredText("None", Fg_Grey, startPosition);
    }
}

void largeTextBox(const char * text, Attribute textColor){
    //Basically it will be a textbox with padding
    //Padding will always be 2, border will always be 1
    int startBoxX = (int)(screen_width/2 - strlen(text)/2-3);
    int startBoxY = (int)(screen_height/2 - 1)-3;
    int boxHeight = 5;
    int boxWidth = 3*2 + (int)strlen(text);

    paintRectangle({' ', Fg_Grey}, {startBoxX, startBoxY}, {(startBoxX+boxWidth), (startBoxY+boxHeight)});
    frame(Fg_Grey, {startBoxX, startBoxY}, {(startBoxX+boxWidth), (startBoxY+boxHeight)});
    
    coloredText(text, textColor, {(startBoxX+3), (startBoxY+3)});
}

void textField(char *inputField, Vec2 position){
    coloredText(inputField, Fg_White, {position.X+1, position.Y});
    coloredText("`", Fg_White, {position.X, position.Y});
    coloredText("`", Fg_White, {(int)strlen(inputField)+position.X+2, position.Y});
    coloredText("_", Fg_White, {int(strlen(inputField))+position.X+1, position.Y});

    handleStringInput(inputField);
}

int switchKeyColor(int keyState, Attribute target1, Attribute target2){
    if (keyState == key_pressed)
    {
        return target2;
    }
    return target1;
}

void uiKeyButton(const char * text, int keyState, Attribute color1, Attribute color2, int *targetContainer, int targetValue, Vec2 position){
    //automatically creates and runs a button without you having to singlehandly write the code for each button UI keystroke component yoruself
    switch (keyState)
    {
    case key_pressed:
            coloredText(text, color2, position); 
        break;
    
    case key_just_released:
        if (targetContainer != NULL)
        {
            *targetContainer = targetValue;
        }
        break;

    default:
            coloredText(text, color1, position);
        break;
    }
}

int handleArrowPosition(int forIncrement, int forDecrement){
    if (forIncrement == key_just_released)
    {
        return -1;
    }
    if (forDecrement == key_just_released)
    {
        return 1;
    }
    return 0;
}
int handleInstantArrowPosition(int forIncrement, int forDecrement){
    if (forIncrement == key_just_pressed)
    {
        return -1;
    }
    if (forDecrement == key_just_pressed)
    {
        return 1;
    }
    return 0;
}
void displayItemArray(Item * items, int itemLength, Vec2 startPosition, int height, int step) //graphical only
{
    //step represents what segment of the item array to look at. 
    //suppose you have a 12 item long inventory and you want to display it
    int itemAmount = 0;
    while (itemAmount < itemLength && items[itemAmount].type != itemType_noItem)
    {
        itemAmount++;
    }
    if (itemAmount)
    {
        int si = 0; //simple index
        for (int i = height*step; i < clamp(0, height*step+height, itemAmount); i++)
        {
            showItemInfo(items[i], {startPosition.X, startPosition.Y+si});
            si++;
        }
    } else {
        coloredText("No items to display", Fg_Grey, startPosition);
    }
    int pagesAmount = itemAmount/height+1;
    coloredText("page: ", Fg_White, {startPosition.X, startPosition.Y+height+1});
    char tmpStr[3] = "";
    coloredText(_itoa(step+1, tmpStr, 10), Fg_White, {startPosition.X+6, startPosition.Y+height+1});
    coloredText("/", Fg_White, {startPosition.X+9, startPosition.Y+height+1});
    coloredText(_itoa(pagesAmount, tmpStr, 10), Fg_White, {startPosition.X+10, startPosition.Y+height+1});
}
BOOL indexMenuArrow(Vec2 startPos, int choiceMax, int *currentPosition, Attribute color)
{
    //function draws an arrow, very useful for menus and choices lists, on the screen. startPos is where the theoritical list begins
    //if the user presses enter, the function returns TRUE, if not, returns FALSE

    *currentPosition += handleArrowPosition(Input(Key_UP), Input(Key_DOWN));
    *currentPosition = clamp(0, *currentPosition, choiceMax-1);
    coloredText("->", color, {startPos.X, startPos.Y + (*currentPosition)*2});
    
    if (Input(Key_ENTER) == key_just_released)
    {
        return TRUE;
    }
    return FALSE;
}
BOOL indexMenuArrow(Vec2 startPos, int choiceMax, int *currentPosition, Attribute color, int step){
    //function draws an arrow, very useful for menus and choices lists, on the screen. startPos is where the theoritical list begins
    //if the user presses enter, the function returns TRUE, if not, returns FALSE

    *currentPosition += handleArrowPosition(Input(Key_UP), Input(Key_DOWN));
    *currentPosition = clamp(0, *currentPosition, choiceMax-1);
    coloredText("->", color, {startPos.X, startPos.Y + (*currentPosition)*step});
    
    if (Input(Key_ENTER) == key_just_released)
    {
        return TRUE;
    }
    return FALSE;
}
BOOL indexMenuItemsArrow(Item * items, int itemLength, int * currentIndexChoice, int height, Vec2 startPosition)
{
    int enter_keyState = Input  (Key_ENTER);
    int itemsAmount = 0;
    while (items[itemsAmount].type != itemType_noItem && itemsAmount < itemLength)
    {
        itemsAmount++;
    }
    *currentIndexChoice += handleArrowPosition(Input(Key_UP), Input(Key_DOWN));
    *currentIndexChoice = clamp(0, *currentIndexChoice, itemsAmount-1);
    displayItemArray(items, itemLength, startPosition, height, (*currentIndexChoice)/height);
    uiKeyButton("->", enter_keyState, Fg_Purple, Fg_Fucsia, NULL, 0, {startPosition.X-2, startPosition.Y+(*currentIndexChoice)%height});
    if (enter_keyState == key_just_pressed)
    {
        return TRUE;
    }
    return FALSE;
}

//the strign that tells you what the last operation's result was
typedef struct ColoredLine{
    char text[64];
    Attribute color;
} ColoredLine, *PColoredLine;
ColoredLine lastAnnouncement;

void showLastAnnouncement()
{
    int i = 0;
    if (strcmp(lastAnnouncement.text, "") != 0)
    {
        while (lastAnnouncement.text[i] != '\0' && i < 64)
        {
            game_screen[screen_height*screen_width-screen_width + 10 + i].Char.UnicodeChar = lastAnnouncement.text[i];
            game_screen[screen_height*screen_width-screen_width + 10 + i].Attributes = lastAnnouncement.color;
            i++;
        }
    }
}
void updateLastAnnouncmenet(const char * newText, Attribute newColor)
{
    strcpy(lastAnnouncement.text, newText);
    lastAnnouncement.color = newColor;
}

void blankWindow(Vec2 startPosition, Vec2 endPosition)
{
    paintRectangle({' ', Fg_White}, startPosition, endPosition);
    frame(Fg_White, startPosition, endPosition);
}

void bossBar(Vec2 startPosition, int width, CHAR_INFO fg_char, CHAR_INFO bg_char, int currentAmount, int maxAmount)
{
    // currentAmount : maxAmount = bossBarFilling : width => bossBarFilling = (width*currentAmount)/maxAmount

    for (int x = startPosition.X; x < startPosition.X+width; x++)
    {
        game_screen[x+startPosition.Y*screen_width] = bg_char;
    }
    for (int x = startPosition.X; x < startPosition.X+ ((width*currentAmount)/maxAmount); x++)
    {
        game_screen[x+startPosition.Y*screen_width] = fg_char;
    }
    
}

void bossBar(Vec2 startPosition, int width, CHAR_INFO fg_char, CHAR_INFO bg_char, float currentAmount, int maxAmount){
    // currentAmount : maxAmount = bossBarFilling : width => bossBarFilling = (width*currentAmount)/maxAmount

    for (int x = startPosition.X; x < startPosition.X+width; x++)
    {
        game_screen[x+startPosition.Y*screen_width] = bg_char;
    }
    for (int x = startPosition.X; x < startPosition.X+ ((width*(int)currentAmount)/maxAmount); x++)
    {
        game_screen[x+startPosition.Y*screen_width] = fg_char;
    }
}
