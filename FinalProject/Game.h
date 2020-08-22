#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"

class Game: public AppComponent, private Timer{
//    TexRect* mushroom;
//    Rect* projectile;
//
//    bool projectileVisible;
//    bool mushroomVisible;
    bool win;
    
    bool up;
    bool down;
    bool left;
    bool right;
//    bool hit;
//    float theta;
//    float deg;
    AnimatedRect* bunny;
    
    TexRect* car;
    TexRect* car2;
    TexRect* viper;
    TexRect* police;
    TexRect* truck;
    
    TexRect* carrot;
    
    TexRect* road;
    TexRect* road2;
    TexRect* road3;
    TexRect* road4;
    TexRect* road5;
    
    TexRect* sidewalk;
    TexRect* grass;
    TexRect* sky;
    
    AnimatedRect* firework;
    AnimatedRect* firework2;
    AnimatedRect* firework3;
    AnimatedRect* firework4;
    
public:
    
    Game();
    
    void draw() const ;
    void handleKeyDown(unsigned char, float, float);
    void handleKeyUp(unsigned char, float, float);
    
    void action();

    ~Game();

};

#endif 
