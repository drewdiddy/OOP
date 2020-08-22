#include <iostream>
#include <cmath>
#include <vector>
#include <utility>	//allows pair

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

using namespace std;

struct Color{
    float red;
    float green;
    float blue;
    
    Color(){
        red = 1.0;
        green = 0.0;
        blue = 0.0;
    }
    
    Color(float red, float green, float blue){
        this->red = red;
        this->green = green;
        this->blue = blue;
    }
};

struct Lines{
	vector<pair<float, float> > lines;	//the complete line that has been drawn
	Color color;						//color of the line that has been drawn

	Lines(){
		color = Color();
	}
	Lines(float r, float g, float b){
		this->color = Color(r, g, b);
	}
}red, green, blue, black;

//store individual coordinates in pair data structure
pair<float, float> point;

// Store the width and height of the window
int width = 640, height = 640;

int redCounter = 0;
int blueCounter = 0;
int greenCounter = 0;
int blackCounter = 0;
string color = "red";

//-------------------------------------------------------
// A function to draw the scene
//-------------------------------------------------------
void appDrawScene() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPointSize(12);
    glBegin(GL_POINTS);
    float x, y;

    for(int i = 0; i < blackCounter; i++){
    	glColor3f(black.color.red, black.color.green, black.color.blue);
    	x = black.lines[i].first;
    	y = black.lines[i].second;
    	glVertex2f(x, y);
    }
    for(int i = 0; i < redCounter; i++){
    	glColor3f(red.color.red, red.color.green, red.color.blue);
    	x = red.lines[i].first;
    	y = red.lines[i].second;
    	glVertex2f(x, y);
    }
    for(int i = 0; i < greenCounter; i++){
    	glColor3f(green.color.red, green.color.green, green.color.blue);
    	x = green.lines[i].first;
    	y = green.lines[i].second;
    	glVertex2f(x, y);
    }
    for(int i = 0; i < blueCounter; i++){
    	glColor3f(blue.color.red, blue.color.green, blue.color.blue);
    	x = blue.lines[i].first;
    	y = blue.lines[i].second;
    	glVertex2f(x, y);
    }

    glEnd();

	// We have been drawing everything to the back buffer
	// Swap the buffers to see the result of what we drew
	glFlush();
	glutSwapBuffers();
}

//-------------------------------------------------------
// A function to convert window coordinates to scene
// We use it when a mouse event is handled
// Arguments: 	
//	x, y - the coordinates to be updated
//-------------------------------------------------------
void windowToScene(float& x, float& y) {
	x = (2.0f*(x / float(width))) - 1.0f;
	y = 1.0f - (2.0f*(y / float(height)));
}

//-------------------------------------------------------
// A function to handle window resizing
// Called every time the window is resized
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appReshapeFunc(int w, int h) {
	// Window size has changed
	width = w;
	height = h;

	double scale, center;
	double winXmin, winXmax, winYmin, winYmax;

	// Define x-axis and y-axis range
	const double appXmin = -1.0;
	const double appXmax = 1.0;
	const double appYmin = -1.0;
	const double appYmax = 1.0;

	// Define that OpenGL should use the whole window for rendering
	glViewport(0, 0, w, h);

	// Set up the projection matrix using a orthographic projection that will
	// maintain the aspect ratio of the scene no matter the aspect ratio of
	// the window, and also set the min/max coordinates to be the disered ones
	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;

	if ((appXmax - appXmin) / w < (appYmax - appYmin) / h) {
		scale = ((appYmax - appYmin) / h) / ((appXmax - appXmin) / w);
		center = (appXmax + appXmin) / 2;
		winXmin = center - (center - appXmin)*scale;
		winXmax = center + (appXmax - center)*scale;
		winYmin = appYmin;
		winYmax = appYmax;
	}
	else {
		scale = ((appXmax - appXmin) / w) / ((appYmax - appYmin) / h);
		center = (appYmax + appYmin) / 2;
		winYmin = center - (center - appYmin)*scale;
		winYmax = center + (appYmax - center)*scale;
		winXmin = appXmin;
		winXmax = appXmax;
	}

	// Now we use glOrtho to set up our viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(winXmin, winXmax, winYmin, winYmax, -1, 1);
}


//-------------------------------------------------------
// A function to handle mouse clicks
// Called every time the mouse button goes up or down
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appMouseFunc(int b, int s, int x, int y) {
	// Convert from Window to Scene coordinates
	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);

    
	// Redraw the scene by calling appDrawScene above
	// so that the point we added above will get painted
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle mouse dragging
// Called every time mouse moves while button held down
// Arguments: 	
//	x, y - current coordinates of the mouse
//-------------------------------------------------------
void appMotionFunc(int x, int y) {

	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);

	if(color == "red"){
		point.first = mx;
		point.second = my;
		red.lines.push_back(point);
		redCounter++;
	}
	else if(color == "green"){
		point.first = mx;
		point.second = my;
		green.lines.push_back(point);
		greenCounter++;
	}
	else if(color == "blue"){
		point.first = mx;
		point.second = my;
		blue.lines.push_back(point);
		blueCounter++;
	}
	else if(color == "black"){
		point.first = mx;
		point.second = my;
		black.lines.push_back(point);
		blackCounter++;
	}
	// Again, we redraw the scene
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle keyboard events
// Called every time a key is pressed on the keyboard
// Arguments: 	
//	key  - the key that was pressed
//	x, y - coordinates of the mouse when key is pressed
//-------------------------------------------------------
void appKeyboardFunc(unsigned char key, int x, int y) {	
    switch (key) {
        case 27:
            exit(0);
            break;
        case 98:
        	//blue color change
        	blue.color = Color(0.0, 0.0, 1.0);
        	color = "blue";
        	break;
        case 101:
        	//eraser (black clolor)
        	black.color = Color(0.0, 0.0, 0.0);
        	color = "black";
        	break;
        case 103:
        	//green color change
        	green.color = Color(0.0, 1.0, 0.0);
        	color = "green";
        	break;
        case 114:
        	//red color change
        	red.color = Color(1.0, 0.0, 0.0);
        	color = "red";
        	break;
        default:
            break;
    }

	// After all the state changes, redraw the scene
	glutPostRedisplay();
}


void idle() {

}

int main(int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Setup window position, size, and title
	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width, height);
	glutCreateWindow("MS Paint Clone");

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
    
	// Set callback for drawing the scene
	glutDisplayFunc(appDrawScene);

	// Set callback for resizing th window
    glutReshapeFunc(appReshapeFunc);

	// Set callback to handle mouse clicks
	glutMouseFunc(appMouseFunc);

	// Set callback to handle mouse dragging
	glutMotionFunc(appMotionFunc);

	// Set callback to handle keyboad events
	glutKeyboardFunc(appKeyboardFunc);
    
    glutIdleFunc(idle);

	// Start the main loop
	glutMainLoop();
}
