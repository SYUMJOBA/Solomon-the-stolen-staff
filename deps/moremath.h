#pragma once
#define isPosAdj(pos1, pos2)  ( ( abs(pos1.X - pos2.X) + abs(pos1.Y - pos2.Y) ) == 1 ) //if the two position are touching each other (not diagonally) it returns TRUE, else, FALSE
#define Vec2diff(pos1, pos2)    ( abs(pos1.X - pos2.X) + abs(pos1.Y - pos2.Y) )
#define Vec2mul(pos, fac)       {pos.X*fac, pos.Y*fac}
#define Vec2sum(pos1, pos2)     {pos1.X+pos2.X, pos1.Y+pos2.Y}

#define toVec2(vec) {(int)vec.X, (int)vec.Y}
#define toVec2f(vec) {(double)vec.X, (double)vec.Y}

#ifndef max
#define max(a, b) (a > b ? a : b)
#endif

const long double SINCOS_TABLE[] = {
 (long double)0.0,
 (long double)0.01745240643728351,
 (long double)0.03489949670250097,
 (long double)0.05233595624294383,
 (long double)0.0697564737441253,
 (long double)0.08715574274765817,
 (long double)0.10452846326765346,
 (long double)0.12186934340514748,
 (long double)0.13917310096006544,
 (long double)0.15643446504023087,
 (long double)0.17364817766693033,
 (long double)0.1908089953765448,
 (long double)0.20791169081775931,
 (long double)0.224951054343865,
 (long double)0.24192189559966773,
 (long double)0.25881904510252074,
 (long double)0.27563735581699916,
 (long double)0.29237170472273677,
 (long double)0.3090169943749474,
 (long double)0.32556815445715664,
 (long double)0.3420201433256687,
 (long double)0.35836794954530027,
 (long double)0.374606593415912,
 (long double)0.3907311284892737,
 (long double)0.40673664307580015,
 (long double)0.42261826174069944,
 (long double)0.4383711467890774,
 (long double)0.45399049973954675,
 (long double)0.4694715627858908,
 (long double)0.48480962024633706,
 (long double)0.49999999999999994,
 (long double)0.5150380749100542,
 (long double)0.5299192642332049,
 (long double)0.5446390350150271,
 (long double)0.5591929034707469,
 (long double)0.573576436351046,
 (long double)0.5877852522924731,
 (long double)0.6018150231520483,
 (long double)0.6156614753256582,
 (long double)0.6293203910498374,
 (long double)0.6427876096865393,
 (long double)0.6560590289905072,
 (long double)0.6691306063588582,
 (long double)0.6819983600624985,
 (long double)0.6946583704589973,
 (long double)0.7071067811865476,
 (long double)0.7193398003386511,
 (long double)0.7313537016191705,
 (long double)0.7431448254773941,
 (long double)0.754709580222772,
 (long double)0.766044443118978,
 (long double)0.7771459614569708,
 (long double)0.788010753606722,
 (long double)0.7986355100472928,
 (long double)0.8090169943749475,
 (long double)0.8191520442889918,
 (long double)0.8290375725550417,
 (long double)0.8386705679454239,
 (long double)0.8480480961564261,
 (long double)0.8571673007021122,
 (long double)0.8660254037844386,
 (long double)0.8746197071393957,
 (long double)0.8829475928589269,
 (long double)0.8910065241883678,
 (long double)0.898794046299167,
 (long double)0.9063077870366499,
 (long double)0.9135454576426009,
 (long double)0.9205048534524403,
 (long double)0.9271838545667874,
 (long double)0.9335804264972017,
 (long double)0.9396926207859083,
 (long double)0.9455185755993167,
 (long double)0.9510565162951535,
 (long double)0.9563047559630354,
 (long double)0.9612616959383189,
 (long double)0.9659258262890683,
 (long double)0.9702957262759965,
 (long double)0.9743700647852352,
 (long double)0.9781476007338056,
 (long double)0.981627183447664,
 (long double)0.984807753012208,
 (long double)0.9876883405951378,
 (long double)0.9902680687415703,
 (long double)0.992546151641322,
 (long double)0.9945218953682733,
 (long double)0.9961946980917455,
 (long double)0.9975640502598242,
 (long double)0.9986295347545738,
 (long double)0.9993908270190958,
 (long double)0.9998476951563913,
 (long double)1 }; //stores 1 fourth of the full sin function results, from 0� to 90�
//length : 90+1
long double sin(int angle) //feed the degrees in the function
{
    angle = angle % 360;
    if (angle > 180)
    {
        return angle > 270 ? SINCOS_TABLE[90 - (angle - 270)] * -1 : (SINCOS_TABLE[angle - 180]) * -1;
    }
    else {
        return angle > 90 ? SINCOS_TABLE[90 - (angle - 90)] : SINCOS_TABLE[angle];
    }
}
long double cos(int angle) //feed the degrees in the function
{
    angle = angle % 360;
    return sin(angle + 90);
}

//Lehmer for random number generation
unsigned long long int nLehmer_seed = 0;
unsigned long long int LehmerRand() {
    nLehmer_seed += 0xe120fc15;
    unsigned long long int tmp;
    tmp = nLehmer_seed * 0x4a39b70d;
    unsigned long long int m1 = (tmp >> 32) ^ tmp;
    tmp = m1 * 0x12fad5c9;
    unsigned long long int m2 = (tmp >> 32) ^ tmp;
    return m2;
}

unsigned long long int elevate(int number, int power){
    for (int i = 0; i < power; i++)
    {
        number *= number;
    }
    return number;
}

int clamp(int minimum, int value, int maximum)
{
    if (value < minimum)
    {
        return minimum;
    } else if (value > maximum){
        return maximum;
    }
    return value;
}

Vec2 clampPosition(Vec2 minimum, Vec2 value, Vec2 maximum){
    if (value.X < minimum.X)
    {
        value.X = minimum.X;
    } else if (value.X > maximum.X) {
        value.X = maximum.X;
    }

    if (value.Y < minimum.Y)
    {
        value.Y = minimum.Y;
    } else if (value.Y > maximum.Y)
    {
        value.Y = maximum.Y;
    }
    return value;
}

int getVec2distance(Vec2 vertex1, Vec2 vertex2)
{
    return abs( abs(vertex1.X-vertex2.X) + abs(vertex1.Y-vertex2.Y));
}

typedef struct CollisionBox{
    Vec2 position; //position indicates the CENTRAL point
    Vec2 size; //size indicates the X and Y LENGTH, and NOT LENGTH/2
}CollisionBox, *PCollisionBox;

BOOL AABB(CollisionBox rect1, CollisionBox rect2)// returns TRUE if teh CollisionBoxes collide
{
    return 
    (
        rect1.position.X < rect2.position.X + rect2.size.X &&
        rect1.position.X + rect1.size.X > rect2.position.X &&
        rect1.position.Y < rect2.position.Y + rect2.size.Y &&
        rect1.position.Y + rect1.size.Y > rect2.position.Y
    );
}

#define vec2cmp(v1, v2) ( (v1.X - v2.X + v1.Y - v2.Y) == 0)

BOOL isVec2Equal(Vec2 vector1, Vec2 vector2) //returns 1 if the two vectors are the same, 0 if not
{
    if (vector1.X == vector2.X && vector1.Y == vector2.Y){
        return TRUE;
    }
    return FALSE;
}

