#include <iostream>
#include "App.h"

App* singleton;

void timer(int id){
    // This will get called every 16 milliseconds after
    // you call it once
    
    // If you want to manipulate the app in here
    // do it through the singleton pointer
    
    if (singleton->up){
        float ypos = singleton->projectile->getY();
        ypos +=0.05;
        singleton->projectile->setY(ypos);
        singleton->redraw();
        if(ypos > .45){
            singleton->projectile->setY(100);
            singleton->mushroom->setY(100);
            singleton->up = false;
            singleton->explosion->playOnce();
        }
    }
    
    glutTimerFunc(16, timer, id);
}


App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    
    explosion = new AnimatedRect("fireball.bmp", 6, 6, 25, false, false, -.25, .9, .5, .5);
    mushroom = new TexRect("mushroom.png", -0.25, 0.9, 0.5, 0.5);
    projectile = new Rect(-0.05, -0.8, 0.1, 0.1, 1, .64, 0);
    up = false;
    
    singleton = this;
    
    timer(1);
}

void App::draw() {
    mushroom->draw(0.1);
    projectile->draw();
    explosion->draw(0);
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        exit(0);
    }
    if (key == ' '){
        up = true;
    }
}

App::~App(){
    delete projectile;
    delete explosion;
    delete mushroom;
    std::cout << "Exiting..." << std::endl;
}
