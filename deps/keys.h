// Keyboard controller V 0.9 beta (added some control keys)
#pragma once

#define VK_Key_0 0x30
#define VK_Key_1 0x31
#define VK_Key_2 0x32
#define VK_Key_3 0x33
#define VK_Key_4 0x34
#define VK_Key_5 0x35
#define VK_Key_6 0x36
#define VK_Key_7 0x37
#define VK_Key_8 0x38
#define VK_Key_9 0x39

#define VK_Key_A 0x41
#define VK_Key_B 0x42
#define VK_Key_C 0x43
#define VK_Key_D 0x44
#define VK_Key_E 0x45
#define VK_Key_F 0x46
#define VK_Key_G 0x47
#define VK_Key_H 0x48
#define VK_Key_I 0x49
#define VK_Key_J 0x4A
#define VK_Key_K 0x4B
#define VK_Key_L 0x4C
#define VK_Key_M 0x4D
#define VK_Key_N 0x4E
#define VK_Key_O 0x4F
#define VK_Key_P 0x50
#define VK_Key_Q 0x51
#define VK_Key_R 0x52
#define VK_Key_S 0x53
#define VK_Key_T 0x54
#define VK_Key_U 0x55
#define VK_Key_V 0x56
#define VK_Key_W 0x57
#define VK_Key_X 0x58
#define VK_Key_Y 0x59
#define VK_Key_Z 0x5A

#define key_inactive 0
#define key_pressed 1
#define key_just_pressed 2
#define key_just_released 3

#define total_keys_amount 38

typedef struct KEY_INFO
{
    BOOL is_pressed;
    int keyCode;
} KEY_INFO, *PKEY_INFO;

KEY_INFO Base_Key_0 = {FALSE, 0x30};
KEY_INFO Base_Key_1 = {FALSE, 0x31};
KEY_INFO Base_Key_2 = {FALSE, 0x32};
KEY_INFO Base_Key_3 = {FALSE, 0x33};
KEY_INFO Base_Key_4 = {FALSE, 0x34};
KEY_INFO Base_Key_5 = {FALSE, 0x35};
KEY_INFO Base_Key_6 = {FALSE, 0x36};
KEY_INFO Base_Key_7 = {FALSE, 0x37};
KEY_INFO Base_Key_8 = {FALSE, 0x38};
KEY_INFO Base_Key_9 = {FALSE, 0x39};
KEY_INFO Base_Key_A = {FALSE, 0x41};
KEY_INFO Base_Key_B = {FALSE, 0x42};
KEY_INFO Base_Key_C = {FALSE, 0x43};
KEY_INFO Base_Key_D = {FALSE, 0x44};
KEY_INFO Base_Key_E = {FALSE, 0x45};
KEY_INFO Base_Key_F = {FALSE, 0x46};
KEY_INFO Base_Key_G = {FALSE, 0x47};
KEY_INFO Base_Key_H = {FALSE, 0x48};
KEY_INFO Base_Key_I = {FALSE, 0x49};
KEY_INFO Base_Key_J = {FALSE, 0x4A};
KEY_INFO Base_Key_K = {FALSE, 0x4B};
KEY_INFO Base_Key_L = {FALSE, 0x4C};
KEY_INFO Base_Key_M = {FALSE, 0x4D};
KEY_INFO Base_Key_N = {FALSE, 0x4E};
KEY_INFO Base_Key_O = {FALSE, 0x4F};
KEY_INFO Base_Key_P = {FALSE, 0x50};
KEY_INFO Base_Key_Q = {FALSE, 0x51};
KEY_INFO Base_Key_R = {FALSE, 0x52};
KEY_INFO Base_Key_S = {FALSE, 0x53};
KEY_INFO Base_Key_T = {FALSE, 0x54};
KEY_INFO Base_Key_U = {FALSE, 0x55};
KEY_INFO Base_Key_V = {FALSE, 0x56};
KEY_INFO Base_Key_W = {FALSE, 0x57};
KEY_INFO Base_Key_X = {FALSE, 0x58};
KEY_INFO Base_Key_Y = {FALSE, 0x59};
KEY_INFO Base_Key_Z = {FALSE, 0x5A};
KEY_INFO Base_Key_UP = {FALSE, VK_UP};
KEY_INFO Base_Key_DOWN = {FALSE, VK_DOWN};
KEY_INFO Base_Key_LEFT = {FALSE, VK_LEFT};
KEY_INFO Base_Key_RIGHT = {FALSE, VK_RIGHT};
KEY_INFO Base_Key_ENTER = {FALSE, VK_RETURN};
KEY_INFO Base_Key_SHIFT = {FALSE, VK_SHIFT};
KEY_INFO Base_Key_ALT = {FALSE, VK_MENU};
KEY_INFO Base_Key_CTRL = {FALSE, VK_CONTROL};
KEY_INFO Base_Key_ESCAPE = {FALSE, VK_ESCAPE};
KEY_INFO Base_Key_BACK = {FALSE, VK_BACK};
KEY_INFO Base_Key_TAB = {FALSE, VK_TAB};
KEY_INFO Base_Key_SPACE = {FALSE, VK_SPACE};
KEY_INFO Base_Key_DOT = {FALSE, VK_OEM_PERIOD};

PKEY_INFO Key_0 = &Base_Key_0;
PKEY_INFO Key_1 = &Base_Key_1;
PKEY_INFO Key_2 = &Base_Key_2;
PKEY_INFO Key_3 = &Base_Key_3;
PKEY_INFO Key_4 = &Base_Key_4;
PKEY_INFO Key_5 = &Base_Key_5;
PKEY_INFO Key_6 = &Base_Key_6;
PKEY_INFO Key_7 = &Base_Key_7;
PKEY_INFO Key_8 = &Base_Key_8;
PKEY_INFO Key_9 = &Base_Key_9;
PKEY_INFO Key_A = &Base_Key_A;
PKEY_INFO Key_B = &Base_Key_B;
PKEY_INFO Key_C = &Base_Key_C;
PKEY_INFO Key_D = &Base_Key_D;
PKEY_INFO Key_E = &Base_Key_E;
PKEY_INFO Key_F = &Base_Key_F;
PKEY_INFO Key_G = &Base_Key_G;
PKEY_INFO Key_H = &Base_Key_H;
PKEY_INFO Key_I = &Base_Key_I;
PKEY_INFO Key_J = &Base_Key_J;
PKEY_INFO Key_K = &Base_Key_K;
PKEY_INFO Key_L = &Base_Key_L;
PKEY_INFO Key_M = &Base_Key_M;
PKEY_INFO Key_N = &Base_Key_N;
PKEY_INFO Key_O = &Base_Key_O;
PKEY_INFO Key_P = &Base_Key_P;
PKEY_INFO Key_Q = &Base_Key_Q;
PKEY_INFO Key_R = &Base_Key_R;
PKEY_INFO Key_S = &Base_Key_S;
PKEY_INFO Key_T = &Base_Key_T;
PKEY_INFO Key_U = &Base_Key_U;
PKEY_INFO Key_V = &Base_Key_V;
PKEY_INFO Key_W = &Base_Key_W;
PKEY_INFO Key_X = &Base_Key_X;
PKEY_INFO Key_Y = &Base_Key_Y;
PKEY_INFO Key_Z = &Base_Key_Z;
PKEY_INFO Key_UP = &Base_Key_UP;
PKEY_INFO Key_DOWN = &Base_Key_DOWN;
PKEY_INFO Key_LEFT = &Base_Key_LEFT;
PKEY_INFO Key_RIGHT = &Base_Key_RIGHT;
PKEY_INFO Key_ENTER = &Base_Key_ENTER;
PKEY_INFO Key_SHIFT = &Base_Key_SHIFT;
PKEY_INFO Key_ALT = &Base_Key_ALT;
PKEY_INFO Key_CTRL = &Base_Key_CTRL;
PKEY_INFO Key_ESCAPE = &Base_Key_ESCAPE;
PKEY_INFO Key_BACK = &Base_Key_BACK;
PKEY_INFO Key_TAB = &Base_Key_TAB;
PKEY_INFO Key_SPACE = &Base_Key_SPACE;
PKEY_INFO Key_DOT = &Base_Key_DOT;

PKEY_INFO Alphabetic_keysKeyboard[total_keys_amount] = {
    Key_0,
    Key_1,
    Key_2,
    Key_3,
    Key_4,
    Key_5,
    Key_6,
    Key_7,
    Key_8,
    Key_9,
    Key_A,
    Key_B,
    Key_C,
    Key_D,
    Key_E,
    Key_F,
    Key_G,
    Key_H,
    Key_I,
    Key_J,
    Key_K,
    Key_L,
    Key_M,
    Key_N,
    Key_O,
    Key_P,
    Key_Q,
    Key_R,
    Key_S,
    Key_T,
    Key_U,
    Key_V,
    Key_W,
    Key_X,
    Key_Y,
    Key_Z,
    Key_SPACE,
    Key_DOT
};

char alphabetical_chars[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char numerical_chars[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char other_chars[2] = {' ', '.'};

int Input(PKEY_INFO inputKey)
{
    if (GetAsyncKeyState(inputKey->keyCode))
    {
        if (!inputKey->is_pressed)
        {
            // Just pressed
            inputKey->is_pressed = TRUE;
            return key_just_pressed;
        }
        return key_pressed;
    }
    else
    {
        if (inputKey->is_pressed)
        {
            // Just released
            inputKey->is_pressed = FALSE;
            return key_just_released;
        }
        return key_inactive;
    }
}

char getCharFromUser() //returns 0 if unsuccessful, returns any other char value if something got fetched from the user
{
    int shiftState = Input(Key_SHIFT);
    int i = 0;
    while (i < total_keys_amount && Input(Alphabetic_keysKeyboard[i]) != key_just_pressed)
    {
        i++;
    }
    if (i < total_keys_amount)
    {
        if (i < 10)
        {
            return numerical_chars[i];
        } else if (i<36)
        {
            if (shiftState == key_pressed)
            {
                return alphabetical_chars[i-10] - 32;
            }
            return alphabetical_chars[i-10];
        } else {
            return other_chars[i-36];
        }
        
    }
    return 0;
}

//P.S. I know this function is unsafe, but I'll accept it for the time being
void handleStringInput( char * destination ){  //takes a char pointer as parameter and handles it depending on the user input
    if (Input(Key_BACK) == key_just_pressed)
    {
        destination[strlen(destination)-1] = '\0';
    } else {
        char adding = getCharFromUser();
        if (0 != adding)
        {
            destination[strlen(destination)] = adding;
            destination[strlen(destination)+1] = '\0';
        }
    }
}

void switchValue(int keyState, BOOL * value){
    if (keyState == key_just_pressed)
    {
        *value = !(*value);
    }
}

void switchValue(int keyState, BOOL * value, int value1, int value2)
{
    if (keyState == key_just_pressed)
    {
        if (*value == value1)
        {
            *value = value2;
        } else {
            *value = value1;
        }
        
    }
}
