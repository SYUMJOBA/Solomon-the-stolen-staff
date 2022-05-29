#pragma once
#define Attribute WORD

#define color_undefined -1

#define Fg_Black         (Attribute)0x00
#define Fg_Dark_Blue     (Attribute)0x01
#define Fg_Green         (Attribute)0x02
#define Fg_Water_Green   (Attribute)0x03
#define Fg_Bordeaux      (Attribute)0x04
#define Fg_Purple        (Attribute)0x05
#define Fg_Olive_Green   (Attribute)0x06
#define Fg_Light_Grey    (Attribute)0x07
#define Fg_Grey          (Attribute)0x08
#define Fg_Blue          (Attribute)0x09
#define Fg_Lime_Green    (Attribute)0x0a
#define Fg_Light_Blue    (Attribute)0x0b
#define Fg_Red           (Attribute)0x0c
#define Fg_Fucsia        (Attribute)0x0d
#define Fg_Yellow        (Attribute)0x0e
#define Fg_White         (Attribute)0x0f

#define Bg_Black         (Attribute)0x00
#define Bg_Dark_Blue     (Attribute)0x10
#define Bg_Green         (Attribute)0x20
#define Bg_Water_Green   (Attribute)0x30
#define Bg_Bordeaux      (Attribute)0x40
#define Bg_Purple        (Attribute)0x50
#define Bg_Olive_Green   (Attribute)0x60
#define Bg_Light_Grey    (Attribute)0x70
#define Bg_Grey          (Attribute)0x80
#define Bg_Blue          (Attribute)0x90
#define Bg_Lime_Green    (Attribute)0xa0
#define Bg_Light_Blue    (Attribute)0xb0
#define Bg_Red           (Attribute)0xc0
#define Bg_Fucsia        (Attribute)0xd0
#define Bg_Yellow        (Attribute)0xe0
#define Bg_White         (Attribute)0xf0

//these two functions finally work
Attribute getBgColor(Attribute color){
    return (color>>4)<<4;
}

Attribute getFgColor(Attribute color){
    return color - getBgColor(color);
}

Attribute toBgColor(Attribute color){
    return color<<4;
}

Attribute toFgColor(Attribute color){
    return color>>4;
}