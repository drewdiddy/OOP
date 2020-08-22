#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#define INFINT_USE_EXCEPTIONS
#include "Game.h"

Game::Game(){

    bunny = new AnimatedRect("bunny.png", 1, 8, 225, true, true, -.075, -.75, .15, .15);
    
    road = new TexRect("road.png",-1, -.5, 2.2, 0.25);
    road2 = new TexRect("road.png", -1, -0.25, 2.2, .25);
    road3 = new TexRect("road.png", -1, 0.0, 2.2, .25);
    road4 = new TexRect("road.png",-1, .5, 2.2, 0.25);
	road5 = new TexRect("road.png",-1, .75, 2.2, 0.25);

    sidewalk = new TexRect("sidewalk.jpeg", -1, -.75, 2.2, .25);
    grass = new TexRect("grass.png", -1, 0.4, 2.4, .55);
    sky = new TexRect("sky.png", -1, 1, 2.2, 0.26);

    carrot = new TexRect("carrot.png", -.125, 1, .25, .25);
 

    car = new TexRect("taxi.png", -.5,-.5, 0.25,0.2);
    truck = new TexRect("truck.png", .5,-.25, 0.40, 0.2);
    car2 = new TexRect("orange_car.png", .9, 0.0, .25, .2);
    viper = new TexRect("viper.png", .9, 0.5, .25, .2);
    police = new TexRect("police.png", -.9, 0.75, .25, .2);
    
    firework = new AnimatedRect("redshot.png", 1, 8, 100, false, false, .65, 1, .35, .35);
    firework2 = new AnimatedRect("violetshot.png", 1, 8, 100, false, false, -.4, 1, .35, .35);
    firework3 = new AnimatedRect("yellowshot.png", 1, 8, 100, false, false, .05, 1, .35, .35);
    firework4 = new AnimatedRect("redshot.png", 1, 8, 100, false, false, -.8, 1, .35, .35);
    
    win = false;
    
    up = false;
    down = false;
    left = false;
    right = false;
    
    bunny->pause();
    
    setRate(1);
    start();
}

void Game::action(){
    
    //where to place animal at the bottom of the screen
    float baseX = -.075;
    float baseY = -.75;
    
    //size of the animal
    float sizeOfBox = 0.15;
    
    float bunnyYLoc = bunny->getY();
    float bunnyXLoc = bunny->getX();
    
    float x1 = car->getX();
    float x2 = truck->getX();
    float x3 = car2->getX();
    float x4 = viper->getX();
    float x5 = police->getX();
    
    car->setX(x1 - .001);
    if(x1 < -1.5){
        car->setX(1);
    }
    truck->setX(x2 + .00225);
    if(x2 > 1){
        truck->setX(-1.5);
    }
    car2->setX(x3 - .002);
    if(x3 < -1.5){
        car2->setX(1);
    }
    viper->setX(x4 + .001);
    if(x4 > 1){
        viper->setX(-1.3);
    }
    police->setX(x5 - .00189);
    if (x5 < -1.3){
        police->setX(1.3);
    }
    
    
    if(up == true){
        if(bunnyYLoc < 1)
            bunny->setY(bunnyYLoc + .0005);
    }
    if(down == true){
        if(bunnyYLoc - sizeOfBox > -1)
            bunny->setY(bunnyYLoc - .0005);
    }
    if(left == true){
        if(bunnyXLoc > -1)
            bunny->setX(bunnyXLoc - .0005);
    }
    if(right == true){
        if(bunnyXLoc + sizeOfBox < 1)
            bunny->setX(bunnyXLoc + .0005);
    }
    
    
    if(car->contains(bunnyXLoc + sizeOfBox/2, bunnyYLoc - sizeOfBox/2)){
        bunny->setX(baseX);
        bunny->setY(baseY);
    }
    if(truck->contains(bunnyXLoc + sizeOfBox/2, bunnyYLoc - sizeOfBox/2)){
        //std::cout << "tagged!" << std::endl;
        bunny->setX(baseX);
        bunny->setY(baseY);
    }
    if(car2->contains(bunnyXLoc + sizeOfBox/2, bunnyYLoc - sizeOfBox/2)){
        bunny->setX(baseX);
        bunny->setY(baseY);
    }
    if(viper->contains(bunnyXLoc + sizeOfBox/2, bunnyYLoc - sizeOfBox/2)){
        bunny->setX(baseX);
        bunny->setY(baseY);
    }
    if(police->contains(bunnyXLoc + sizeOfBox/2, bunnyYLoc - sizeOfBox/2)){
        bunny->setX(baseX);
        bunny->setY(baseY);
    }
    if(carrot->contains(bunnyXLoc + sizeOfBox/2, bunnyYLoc - sizeOfBox/2)){
        firework->playLoop();
        firework2->playLoop();
        firework3->playLoop();
        firework4->playLoop();
    }
}

void Game::draw() const {

    road->draw(0);
    road2->draw(0);
    road3->draw(0);
    road4->draw(0);
    road5->draw(0);
    
    sidewalk->draw(0);
    grass->draw(0);
    sky->draw(0);
    
    carrot->draw(.1);
    
    car->draw(.1);
    truck->draw(.1);
    car2->draw(.1);
    viper->draw(.1);
    police->draw(.1);
    
    bunny->draw(.3);
    
    firework->draw(.2);
    firework2->draw(.2);
    firework3->draw(.2);
    firework4->draw(.2);

}

void Game::handleKeyDown(unsigned char key, float x, float y){
    if (key == 'w'){
        up = true;
        bunny->resume();
    }
    else if(key == 's'){
        down = true;
        bunny->resume();
    }
    else if(key == 'a'){
        left = true;
        bunny->resume();
    }
    else if(key == 'd'){
        right = true;
        bunny->resume();
    }
    
    
//    else if (key == 'p'){
//        stop();
//    }
//    else if (key == 'r'){
//        start();
//    }
}

void Game::handleKeyUp(unsigned char key, float x, float y){
    if (key == 'w'){
        up = false;
        bunny->pause();
    }
    else if(key == 's'){
        down = false;
        bunny->pause();
    }
    else if(key == 'a'){
        left = false;
        bunny->pause();
    }
    else if(key == 'd'){
        right = false;
        bunny->pause();
    }
}

Game::~Game(){
    stop();
    delete bunny;
    
    delete road;
    delete road2;
    delete road3;
    delete road4;
    delete road5;
    
    delete sidewalk;
    delete grass;
    delete sky;
    
    delete carrot;
    
    delete car;
    delete car2;
    delete viper;
    delete police;
    delete truck;
    
    delete firework;
    delete firework2;
    delete firework3;
    delete firework4;
}
