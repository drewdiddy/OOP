#include <iostream>
#include <cmath>
#include <vector>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

using namespace std;



struct Rectangle {
    float x;
    float y;
    float w;
    float h;
    string shape;
    bool occupied;
    
    Rectangle (){
        x = -0.5;
        y = 0.5;
        w = 0.5;
        h = 0.5;
        shape = "";
        occupied = false;
    }
    
    Rectangle (float x, float y, float w, float h){
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        occupied = false;
    }
    
    bool contains(float mx, float my){
        return mx >= x && mx <= x + w && my <= y && my >= y - h;
    }
    
    void draw(){

        if(shape == "X"){
        	glLineWidth(8.0);
        	glColor3f(.04, .03, .96);
        	glBegin(GL_LINES);
        	glVertex2f(x+w, y);
        	glVertex2f(x, y-h);

        	glVertex2f(x,y);
        	glVertex2f(x+w, y-h);

        }
        else if(shape == "O"){
        	//CIRCLES
    		float theta = 0;
    		float thetaInc = M_PI/100;
    		float radius = 0.0;
    		float xOffset = 0.0;
    		float yOffset = 0.0;
   
        	//INNER O
        	glColor3f(0.0, 0.0, 0.0);
    
        	theta = 0;
        	thetaInc = M_PI/100;
        	radius = 0.1;
        	xOffset = ((.5)*w) + x;
        	yOffset = -((.5)*h) + y;
    
        	glBegin(GL_POLYGON);
    
        	for (theta; theta < 2*M_PI; theta+=thetaInc) {
        	    glVertex2f(radius * cos(theta) + xOffset, radius * sin(theta) + yOffset);
        	}

        	glEnd();

	        //OUTER O
	        glColor3f(.96, .03, .2);    
    
        	theta = 0;
        	thetaInc = M_PI/100;
        	radius = 0.2;
        	xOffset = ((.5)*w) + x;
        	yOffset = -((.5)*h) + y;
    
        	glBegin(GL_POLYGON);
    
        	for (theta; theta < 2*M_PI; theta+=thetaInc) {
        	    glVertex2f(radius * cos(theta) + xOffset, radius * sin(theta) + yOffset);
        	}

        	glEnd();
    	}

    	glColor3f(0.75, 0.75, 0.75);
        glBegin(GL_POLYGON);
        
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y - h);
        glVertex2f(x, y - h);
        
        glEnd();
    }
};    



// Store the width and height of the window
int width = 640, height = 640;
// Store which mode we are playing
int mode = 0;

bool player1 = true;
bool game_over = false;
string check = "";
int click_offset = 1;
float x_coordinate, y_coordinate;


//Rectangle rect = Rectangle(0.3, 0.5, 0.5, 0.5);

vector<Rectangle> grid;

string winCheck(){
	int i;
	//horizontal check
	for(i = 0; i <= 6; i = i+3){
		//cout<< "CHECK: " << i << endl;
		if(grid[i].shape == grid[i+1].shape && grid[i].shape == grid[i+2].shape){
			if(grid[i].shape == "X"){
				game_over = true;
				return "X";
			}
			else if(grid[i].shape == "O"){
				game_over = true;
				return "O";
			}
		}
	}
	//verticle check
	for(i = 0; i <= 2; i++){
		if(grid[i].shape == grid[i+3].shape && grid[i].shape == grid[i+6].shape){
			if(grid[i].shape == "X"){
				game_over = true;
				return "X";
			}
			else if(grid[i].shape == "O"){
				game_over = true;
				return "O";
			}
		}
	}
	//diagonal check
	if(grid[0].shape == grid[4].shape && grid[0].shape == grid[8].shape){
			if(grid[0].shape == "X"){
				game_over = true;
				return "X";
			}
			else if(grid[0].shape == "O"){
				game_over = true;
				return "O";	
			}
	}
	if(grid[2].shape == grid[4].shape && grid[2].shape == grid[6].shape){
			if(grid[2].shape == "X"){
				game_over = true;
				return "X";
			}
			else if(grid[2].shape == "O"){
				game_over = true;
				return "O";	
			}
	}
	return "not yet buddy :)";		
}

void compDecision(){
	int i;
	bool takenTurn = false;
	//horizontal check
	for(i = 0; i <= 6; i = i+3){
		if(grid[i].shape == grid[i+1].shape && grid[i].shape == grid[i+2].shape){
			if(grid[i].shape == ""){
				grid[i].shape = "O";
				grid[i].occupied = true;
				takenTurn = true;
				break;
			}
		}
	}
	if(takenTurn == false){
	//verticle check
		for(i = 0; i <= 2; i++){
			if(grid[i].shape == grid[i+3].shape && grid[i].shape == grid[i+6].shape){
				if(grid[i].shape == ""){
					grid[i].shape = "O";
					grid[i].occupied = true;
					takenTurn = true;
					break;
				}
			}
		}
	}	
	if(takenTurn == false){
		//diagonal check
		if(grid[0].shape == grid[4].shape && grid[0].shape == grid[8].shape){
			if(grid[0].shape == ""){
				grid[0].shape = "O";
				grid[i].occupied = true;
				takenTurn = true;
			}
		}
	}
	if(takenTurn == false){
		if(grid[2].shape == grid[4].shape && grid[2].shape == grid[6].shape){
			if(grid[2].shape == ""){
				grid[2].shape = "O";
				grid[i].occupied = true;
				takenTurn = true;
			}
		}		
	}
	if(takenTurn == false){
		for (int i = 0; i < grid.size(); i++){
			if(grid[i].occupied == false){
				grid[i].shape = "O";
				grid[i].occupied = true;
				takenTurn = true;
				break;
			}
		}
	}
	player1 = true;
}

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

	// Draw squares for our grid
    if(game_over ==false){
    	for (int i = 0; i < grid.size(); i++) {
    	   grid[i].draw();
    	}
	}
	if(click_offset % 2 == 1){
    	check = winCheck();
    	if(game_over == true){
    		if(check == "X"){
    	 		cout << "X's won!\n";
    		}
    		else if(check == "O"){
    	 		cout << "O's won!\n";
    		}
    	}
    }
    click_offset++;
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
    
    if (b == 0){
        if (s == 0){
           // I clicked the left button
        	if(mode == 1 && player1 == false){	//computer's turn
           	    compDecision();
           }
           	for (int i = 0; i < grid.size(); i++){
           	    if (grid[i].contains(mx, my)){
           	        if (!grid[i].occupied){
           	            if (player1) grid[i].shape = "X";
           	            else grid[i].shape = "O";
           	            cout << "Clicked on position " << i << endl;
           	            grid[i].occupied = true;
           	            if(mode == 1)
           	            	player1 = false;
           	            else
           	            	player1 = !player1;

           	        }
           	    }
            }	
        }
    }

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
        default:
            break;
    }

	// After all the state changes, redraw the scene
	glutPostRedisplay();
}


void idle() {

}


int main(int argc, char** argv) {
	cout << "Single Player Mode (1) or Two Player Mode (2)?\n";
	cin >> mode;
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Setup window position, size, and title
	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width, height);
	glutCreateWindow("CSE165 TIC TAC TOE");

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

    grid.push_back(Rectangle(-0.8, 0.8, 0.4, 0.4));
    grid.push_back(Rectangle(-0.2, 0.8, 0.4, 0.4));
    grid.push_back(Rectangle(0.4, 0.8, 0.4, 0.4));
    
    grid.push_back(Rectangle(-0.8, 0.2, 0.4, 0.4));
    grid.push_back(Rectangle(-0.2, 0.2, 0.4, 0.4));
    grid.push_back(Rectangle(0.4, 0.2, 0.4, 0.4));
    
    grid.push_back(Rectangle(-0.8, -0.4, 0.4, 0.4));
    grid.push_back(Rectangle(-0.2, -0.4, 0.4, 0.4));
    grid.push_back(Rectangle(0.4, -0.4, 0.4, 0.4));
    
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
