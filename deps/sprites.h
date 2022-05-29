//http://asciiset.com/ to keep an eye on the ASCII charecters

#define uiSprite_vertical (char)0xba            //║
#define uiSprite_horizontal (char)0xcd          //═
#define uiSprite_pillar (char)0x4f              //O
#define uiSprite_cross (char)0xce               //╬
#define uiSprite_top_right_left (char)0xca      //╩
#define uiSprite_right_bottom_left (char)0xcb   //╗
#define uiSprite_top_bottom_left (char)0xb9     //╣
#define uiSprite_top_right_bottom (char)0xcc    //╠
#define uiSprite_top_right (char)0xc8           //╚
#define uiSprite_top_left (char)0xbc            //╝
#define uiSprite_right_bottom (char)0xc9        //╔
#define uiSprite_bottom_left (char)0xbb         //╗

#define tileSprite_liquidSingle (char)0x7e      //~
#define tileSprite_liquidDouble (char)0xf7      //≈


#define char_pound (char)0x9c
#define char_asterisc (char)0x2a
#define char_degree (char)0xf8
#define char_middleDot (char)0xf9
#define char_alpha (char)0xe0
#define char_beta (char)0xe1
#define char_gamma (char)0xe2
#define char_pi (char)0xe3
#define char_sigmaUpperCase (char)0xe4
#define char_sigmaLowerCase (char)0xe5
#define char_mi (char)0xe6
#define char_tau (char)0xe7
#define char_fi (char)0xe8
#define char_theta (char)0xe9
#define char_omega (char)0xea
#define char_delta (char)0xeb
#define char_infinite (char)0xec
#define char_star       (char)0xf   //☼
#define char_upSlope (char)30       //▲


#define materialSprite_flesh (char)0xd6         //╓


#define char_face  (char)0x1 //☺
#define char_filledFace (char)0x2 //☻
#define char_heart  (char)0x3 //♥
#define char_rombus  (char)0x4 //♦
#define char_flower  (char)0x5 //♣
#define char_spade  (char)0x6 //♠

#define char_male       (char)0xb //♂
#define char_female  (char)0xc //♀
#define char_musicNotes  (char)0xe //♫
#define char_star       (char)0xf //☼
#define char_rightCone  (char)0x10 //►
#define char_leftCone  (char)0x11 //◄
#define char_upDownArrow  (char)0x12 //↕
#define char_doubleExclamationMark  (char)0x13 //‼
#define char_moscaFoot  (char)0x14 //¶
#define char_paragraph  (char)0x15 //§
#define char_rectangle  (char)0x16 //▬
#define char_upDownArrowUnderline  (char)0x17 //↨
#define char_upArrow  (char)0x18 //↑
#define char_downArrow  (char)0x19 //↓
#define char_rightArrow  (char)0x1a //→
#define char_leftArrow  (char)0x1b //←
#define char_THINGHERE  (char)0x1c //∟
#define char_leftRightArrow  (char)0x1d //↔
#define char_upCone  (char)0x1e //▲
#define char_downCone  (char)0x1f //▼
#define char_couldBeNothing  (char)0x20 //
#define char_exclamationMark  (char)0x21 //!
#define char_doubleQuotes  (char)0x22 //"
#define char_hash  (char)0x23 //#
#define char_dollar  (char)0x24 //$
#define char_percent  (char)0x25 //%
#define char_and  (char)0x26 //&
#define char_singleQuote  (char)0x27 //'

/*
#define char_THINGHERE  (char)0x28 // (
#define char_THINGHERE  (char)0x29 // )
#define char_THINGHERE  (char)0x2a // *
#define char_THINGHERE  (char)0x2b // +
#define char_THINGHERE  (char)0x2c // ,
#define char_THINGHERE  (char)0x2d // -
#define char_THINGHERE  (char)0x2e // .
#define char_THINGHERE  (char)0x2f // /
#define char_THINGHERE  (char)0x30 // 0
#define char_THINGHERE  (char)0x31 // 1
#define char_THINGHERE  (char)0x32 // 2
#define char_THINGHERE  (char)0x33 // 3
#define char_THINGHERE  (char)0x34 // 4
#define char_THINGHERE  (char)0x35 // 5
#define char_THINGHERE  (char)0x36 // 6
#define char_THINGHERE  (char)0x37 // 7
#define char_THINGHERE  (char)0x38 // 8
#define char_THINGHERE  (char)0x39 // 9
#define char_THINGHERE  (char)0x3a // :
#define char_THINGHERE  (char)0x3b // ;
#define char_THINGHERE  (char)0x3c // <
#define char_THINGHERE  (char)0x3d // =
#define char_THINGHERE  (char)0x3e // >
#define char_THINGHERE  (char)0x3f // ?
#define char_THINGHERE  (char)0x40 // @
#define char_THINGHERE  (char)0x41 // A
#define char_THINGHERE  (char)0x42 // B
#define char_THINGHERE  (char)0x43 // C
#define char_THINGHERE  (char)0x44 // D
#define char_THINGHERE  (char)0x45 // E
#define char_THINGHERE  (char)0x46 // F
#define char_THINGHERE  (char)0x47 // G
#define char_THINGHERE  (char)0x48 // H
#define char_THINGHERE  (char)0x49 // I
#define char_THINGHERE  (char)0x4a // J
#define char_THINGHERE  (char)0x4b // K
#define char_THINGHERE  (char)0x4c // L
#define char_THINGHERE  (char)0x4d // M
#define char_THINGHERE  (char)0x4e // N
#define char_THINGHERE  (char)0x4f // O
#define char_THINGHERE  (char)0x50 // P
#define char_THINGHERE  (char)0x51 // Q
#define char_THINGHERE  (char)0x52 // R
#define char_THINGHERE  (char)0x53 // S
#define char_THINGHERE  (char)0x54 // T
#define char_THINGHERE  (char)0x55 // U
#define char_THINGHERE  (char)0x56 // V
#define char_THINGHERE  (char)0x57 // W
#define char_THINGHERE  (char)0x58 // X
#define char_THINGHERE  (char)0x59 // Y
#define char_THINGHERE  (char)0x5a // Z
#define char_THINGHERE  (char)0x5b // [
#define char_THINGHERE  (char)0x5c //  '\'
#define char_THINGHERE  (char)0x5d // ]
#define char_THINGHERE  (char)0x5e // ^
#define char_THINGHERE  (char)0x5f // _
#define char_THINGHERE  (char)0x60 // `
#define char_THINGHERE  (char)0x61 // a
#define char_THINGHERE  (char)0x62 // b
#define char_THINGHERE  (char)0x63 // c
#define char_THINGHERE  (char)0x64 // d
#define char_THINGHERE  (char)0x65 // e
#define char_THINGHERE  (char)0x66 // f
#define char_THINGHERE  (char)0x67 // g
#define char_THINGHERE  (char)0x68 // h
#define char_THINGHERE  (char)0x69 // i
#define char_THINGHERE  (char)0x6a // j
#define char_THINGHERE  (char)0x6b // k
#define char_THINGHERE  (char)0x6c // l
#define char_THINGHERE  (char)0x6d // m
#define char_THINGHERE  (char)0x6e // n
#define char_THINGHERE  (char)0x6f // o
#define char_THINGHERE  (char)0x70 // p
#define char_THINGHERE  (char)0x71 // q
#define char_THINGHERE  (char)0x72 // r
#define char_THINGHERE  (char)0x73 // s
#define char_THINGHERE  (char)0x74 // t
#define char_THINGHERE  (char)0x75 // u
#define char_THINGHERE  (char)0x76 // v
#define char_THINGHERE  (char)0x77 // w
#define char_THINGHERE  (char)0x78 // x
#define char_THINGHERE  (char)0x79 // y
#define char_THINGHERE  (char)0x7a // z
#define char_THINGHERE  (char)0x7b // {
#define char_THINGHERE  (char)0x7c // |
#define char_THINGHERE  (char)0x7d // }
#define char_THINGHERE  (char)0x7e // ~
#define char_THINGHERE  (char)0x7f // ⌂
#define char_THINGHERE  (char)0x80 // Ç
#define char_THINGHERE  (char)0x81 // ü
#define char_THINGHERE  (char)0x82 // é
#define char_THINGHERE  (char)0x83 // â
#define char_THINGHERE  (char)0x84 // ä
#define char_THINGHERE  (char)0x85 // à
#define char_THINGHERE  (char)0x86 // å
#define char_THINGHERE  (char)0x87 // ç
#define char_THINGHERE  (char)0x88 // ê
#define char_THINGHERE  (char)0x89 // ë
#define char_THINGHERE  (char)0x8a // è
#define char_THINGHERE  (char)0x8b // ï
#define char_THINGHERE  (char)0x8c // î
#define char_THINGHERE  (char)0x8d // ì
#define char_THINGHERE  (char)0x8e // Ä
#define char_THINGHERE  (char)0x8f // Å
#define char_THINGHERE  (char)0x90 // É
#define char_THINGHERE  (char)0x91 // æ
#define char_THINGHERE  (char)0x92 // Æ
#define char_THINGHERE  (char)0x93 // ô
#define char_THINGHERE  (char)0x94 // ö
#define char_THINGHERE  (char)0x95 // ò
#define char_THINGHERE  (char)0x96 // û
#define char_THINGHERE  (char)0x97 // ù
#define char_THINGHERE  (char)0x98 // ÿ
#define char_THINGHERE  (char)0x99 // Ö
#define char_THINGHERE  (char)0x9a // Ü
#define char_THINGHERE  (char)0x9b // ¢
#define char_THINGHERE  (char)0x9c // £
#define char_THINGHERE  (char)0x9d // ¥
#define char_THINGHERE  (char)0x9e // ₧
#define char_THINGHERE  (char)0x9f // ƒ
#define char_THINGHERE  (char)0xa0 // á
#define char_THINGHERE  (char)0xa1 // í
#define char_THINGHERE  (char)0xa2 // ó
#define char_THINGHERE  (char)0xa3 // ú
#define char_THINGHERE  (char)0xa4 // ñ
#define char_THINGHERE  (char)0xa5 // Ñ
#define char_THINGHERE  (char)0xa6 // ª
*/
#define char_udnerLinedO  (char)0xa7 //º
/*
#define char_THINGHERE  (char)0xa8 //¿
#define char_THINGHERE  (char)0xa9 //⌐
#define char_THINGHERE  (char)0xaa //¬
#define char_THINGHERE  (char)0xab //½
#define char_THINGHERE  (char)0xac //¼
#define char_THINGHERE  (char)0xad //¡
*/
#define char_shiftLeft  (char)0xae //«
#define char_shiftRight  (char)0xaf //»

#define char_bricks1  (char)0xb0 //░
#define char_bricks2 (char)0xb1 //▒
#define char_bricks3  (char)0xb2 //▓
/*
#define char_THINGHERE  (char)0xb3 //│
#define char_THINGHERE  (char)0xb4 //┤
#define char_THINGHERE  (char)0xb5 //╡
#define char_THINGHERE  (char)0xb6 //╢
#define char_THINGHERE  (char)0xb7 //╖
#define char_THINGHERE  (char)0xb8 //╕
#define char_THINGHERE  (char)0xb9 //╣
#define char_THINGHERE  (char)0xba //║
#define char_THINGHERE  (char)0xbb //╗
#define char_THINGHERE  (char)0xbc //╝
#define char_THINGHERE  (char)0xbd //╜
#define char_THINGHERE  (char)0xbe //╛
#define char_THINGHERE  (char)0xbf //┐
#define char_THINGHERE  (char)0xc0 //└
#define char_THINGHERE  (char)0xc1 //┴
#define char_THINGHERE  (char)0xc2 //┬
#define char_THINGHERE  (char)0xc3 //├
#define char_THINGHERE  (char)0xc4 //─
#define char_THINGHERE  (char)0xc5 //┼
#define char_THINGHERE  (char)0xc6 //╞
#define char_THINGHERE  (char)0xc7 //╟
#define char_THINGHERE  (char)0xc8 //╚
#define char_THINGHERE  (char)0xc9 //╔
#define char_THINGHERE  (char)0xca //╩
#define char_THINGHERE  (char)0xcb //╦
#define char_THINGHERE  (char)0xcc //╠
#define char_THINGHERE  (char)0xcd //═
#define char_THINGHERE  (char)0xce //╬
#define char_THINGHERE  (char)0xcf //╧
#define char_THINGHERE  (char)0xd0 //╨
#define char_THINGHERE  (char)0xd1 //╤
#define char_THINGHERE  (char)0xd2 //╥
#define char_THINGHERE  (char)0xd3 //╙
#define char_THINGHERE  (char)0xd4 //╘
#define char_THINGHERE  (char)0xd5 //╒
#define char_THINGHERE  (char)0xd6 //╓
#define char_THINGHERE  (char)0xd7 //╫
#define char_THINGHERE  (char)0xd8 //╪
#define char_THINGHERE  (char)0xd9 //┘
#define char_THINGHERE  (char)0xda //┌
#define char_THINGHERE  (char)0xdb //█
#define char_THINGHERE  (char)0xdc //▄
#define char_THINGHERE  (char)0xdd //▌
#define char_THINGHERE  (char)0xde //▐
#define char_THINGHERE  (char)0xdf //▀
#define char_THINGHERE  (char)0xe0 //α
#define char_THINGHERE  (char)0xe1 //ß
#define char_THINGHERE  (char)0xe2 //Γ
#define char_THINGHERE  (char)0xe3 //π
#define char_THINGHERE  (char)0xe4 //Σ
#define char_THINGHERE  (char)0xe5 //σ
#define char_THINGHERE  (char)0xe6 //µ
#define char_THINGHERE  (char)0xe7 //τ
#define char_THINGHERE  (char)0xe8 //Φ
#define char_THINGHERE  (char)0xe9 //Θ
#define char_THINGHERE  (char)0xea //Ω
#define char_THINGHERE  (char)0xeb //δ
#define char_THINGHERE  (char)0xec //∞
#define char_THINGHERE  (char)0xed //φ
*/
#define char_epsilon  (char)0xee //ε
#define char_intersectionSymbol  (char)0xef //∩
#define char_threeParallelLines  (char)0xf0 //≡
#define char_plusMinus  (char)0xf1 //±
#define char_moreOrEqual  (char)0xf2 //≥
#define char_lessOrEqual  (char)0xf3 //≤
/*
#define char_THINGHERE  (char)0xf4 //⌠
#define char_THINGHERE  (char)0xf5 //⌡
#define char_THINGHERE  (char)0xf6 //÷
#define char_THINGHERE  (char)0xf7 //≈
#define char_THINGHERE  (char)0xf8 //°
#define char_THINGHERE  (char)0xf9 //∙
#define char_THINGHERE  (char)0xfa //·
#define char_THINGHERE  (char)0xfb //√
#define char_THINGHERE  (char)0xfc //ⁿ
#define char_THINGHERE  (char)0xfd //²
#define char_THINGHERE  (char)0xfe //■
*/