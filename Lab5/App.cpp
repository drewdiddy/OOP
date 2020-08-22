#include <iostream>
#include "App.h"

App* singleton;

void timer(int id){
    // This will get called every 16 milliseconds after
    // you call it once
    
    // If you want to manipulate the app in here
    // do it through the singleton pointer
    float x1 = singleton->bg1->getX();
    float x2 = singleton->bg2->getX();
    float distance = x1-x2;
    singleton->bg1->setX(x1-.035);
    if(x1 < -6 && x1 != -4){
        singleton->bg1->setX(-4);
    }
    glutTimerFunc(16, timer, id);
}


App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
	cat = new AnimatedRect("cat.png", 4, 2, 100, true, true, 0,-.30,.5, .5);
	bg1 = new TexRect("bg.png", -4, 1, 8, 2);
	bg2 = new TexRect("bg.png", -4, 1, 8 , 2);
    
    singleton = this;
    
    timer(1);

}

void App::draw() {
 bg1->draw(0);
 bg2->draw(0);
 cat->draw(1);
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        exit(0);
    }
}

App::~App(){
	delete cat;
	delete bg1;
	delete bg2;
    std::cout << "Exiting..." << std::endl;
}
