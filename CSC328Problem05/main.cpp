//----------------------------------------------------------------------------
//  3D PolyMan, CSC328 Problem 4
//  Author: Bobby Purcell
//	Description: 
//	Renders and animates a 3d wireframe of a polygon with legs, mouth, etc
//	The "Polyman" walks onto the screen, stops in the middle, opens his mouth,
//	jumps into the air, flips 360 and lands. Then he closes his mouth and
//	walks off stage to the left.
//----------------------------------------------------------------------------
#include<GL\glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

//rotation of whole icon
float theta = 0.0;

//rotation of right and left leg
float thetaRL = 0.0;
float thetaLL = 0.0;

//scaling global
float scale = 1.0;

//translation globals
float dx = 9.0, dy = 1.0, dz = 1.0, tx1 = .01, ty1 = .01;

//key frame, intially 1
int frame = 1;

//camera point to look at, intially (0,0,0), 
//Its modified with the translation vars to create
//a moving camera focal point
float camX = 0.0f, camY = 0.0, camZ = 0.0f;

//is the animation paused? used to freeze the animation when spacebar
// is pressed
bool paused = false;

// if the feet are moving foreward or backward
//this is used to toggle the direction of rotation of the feet
bool backward = true;

//is mouth closed? effects the color and animation of the mouth/"lips"
bool closedMouth = true;

//delcare arrays of points that make up icon
// has to be global to call some of its points in renderscene
float pox[3][10], poy[3][10], poz[3][10];

//prototypes
void ScaleDisplay(int, int);
void myLoadIcon(float[][10], float[][10], float[][10]);
void DrawPolyman(float[][10], float[][10], float[][10]);
void DrawPolywoman(float[][10], float[][10], float[][10]);
void SetTrans(void);
void TimerFunction(int);
void RenderScene(void);
void Keys(unsigned char, int, int);

//------------------------------------------------------------------------
//  Main
//  Initializes glut, defines a window to draw in, creates the window,
//  sets the buffer clear color bit to white, 
//	registers the display and reshape function callbacks, 
//  enables the OpenGL depth buffer,
//	and finally executes glut event processing
//-------------------------------------------------------------------------
int main(int argc, char **argv) {

    //Initialize GLUT toolkit
    glutInit(&argc, argv);
    //define window parameters
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(200, 20);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("3D PolyMan, CSC328 Problem 4 - Bobby Purcell");

    // set gl clear color to white
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // enable the openGL depth buffer
    glEnable(GL_DEPTH_TEST);

    // set the callback functions for display and window resizing

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ScaleDisplay);

    glutKeyboardFunc(Keys);
    // timer func for animation

    glutTimerFunc(30, TimerFunction, 1);

    //  Start GLUT event processing loop
    glutMainLoop();

    return 0;
}
//-------------------------------------------------------------------------
//  RenderScene
//	Clears the color and depth buffers, sets the camera parameters, draws
//	a basic colored box for a back drop
//-------------------------------------------------------------------------
void RenderScene(void) {

    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    // Set the camera at the initial position, aims it at the focal point,
    // tells cam which way is up
    //TODO: Bind camera to mouse and keyboard? Should be straightforeward
    gluLookAt(-4.0f, 3.0f, 8.0f,
              camX + dx, camY + dy, camZ + dz,
              0.0f, 1.0f, 0.0f);

#pragma region "Draw Scene Box"
    //TODO: Wrap this up into a function, could be done much more cleanly

    // Draw ground
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glEnd();

    // Draw ceiling
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0f, 10.0f, -10.0f);
    glVertex3f(-10.0f, 10.0f, 10.0f);
    glVertex3f(10.0f, 10.0f, 10.0f);
    glVertex3f(10.0f, 10.0f, -10.0f);
    glEnd();

    // draw back wall
    glColor3f(0.1f, 0.1f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0f, 10.0f, -10.0f);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glVertex3f(10.0f, 10.0f, -10.0f);
    glEnd();

    // draw right side wall
    glColor3f(0.1f, 0.2f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glVertex3f(10.0f, 10.0f, -10.0f);
    glVertex3f(10.0f, 10.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glEnd();

    // draw left side wall
    glColor3f(0.1f, 0.2f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glVertex3f(-10.0f, 10.0f, 10.0f);
    glVertex3f(-10.0f, 10.0f, -10.0f);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glEnd();

#pragma endregion

    //load the base icon, polyman
    myLoadIcon(pox, poy, poz);

    //setup and transform the body of polyman
    glPushMatrix();
    SetTrans();
    DrawPolyman(pox, poy, poz);
    glPopMatrix();

    //right leg drawing, movement with body and animating
    glPushMatrix();
    SetTrans();
    glRotatef(thetaRL, 0.0, 0.0, 1.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(pox[2][0], poy[2][0], poz[2][0]);
    glVertex3f(pox[2][1], poy[2][1], poz[2][1]);
    glVertex3f(pox[2][2], poy[2][2], poz[2][2]);
    glEnd();
    glPopMatrix();

    //left leg drawing, movement with body and animating
    glPushMatrix();
    SetTrans();
    glRotatef(thetaLL, 0.0, 0.0, 1.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(pox[2][3], poy[2][3], poz[2][3]);
    glVertex3f(pox[2][4], poy[2][4], poz[2][4]);
    glVertex3f(pox[2][5], poy[2][5], poz[2][5]);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

//-------------------------------------------------------------------------
//  myLoadIcon
//	Loads the desired icon's points into arrays of floats for drawing later
//-------------------------------------------------------------------------
void myLoadIcon(float pox[][10], float poy[][10], float poz[][10])
{
    //Polyman's front, drawn counter-clockwise
    pox[0][0] = -.625;		poy[0][0] = .625;	poz[0][0] = .4;//1f
    pox[0][1] = -1;			poy[0][1] = 0;		poz[0][1] = .4;//6f
    pox[0][2] = -.775;		poy[0][2] = -.375;	poz[0][2] = .4;//16af
    pox[0][3] = -.25;		poy[0][3] = 0;		poz[0][3] = .4;//7f
    pox[0][4] = -.785;		poy[0][4] = -.365;	poz[0][4] = .4;//16f
    pox[0][5] = -.625;		poy[0][5] = -.625;	poz[0][5] = .4;//5f
    pox[0][6] = .625;		poy[0][6] = -.625;	poz[0][6] = .4;//4f
    pox[0][7] = 1;			poy[0][7] = 0;		poz[0][7] = .4;//3f
    pox[0][8] = .625;		poy[0][8] = .625;	poz[0][8] = .4;//2f

    //front eye location
    pox[0][9] = -.5;		poy[0][9] = .375;	poz[0][9] = .405;//8f

    //Polyman's back
    pox[1][0] = -.625;		poy[1][0] = .625;	poz[1][0] = -.4;
    pox[1][1] = -1;			poy[1][1] = 0;		poz[1][1] = -.4;
    pox[1][2] = -.775;		poy[1][2] = -.375;	poz[1][2] = -.4;
    pox[1][3] = -.25;		poy[1][3] = 0;		poz[1][3] = -.4;
    pox[1][4] = -.785;		poy[1][4] = -.365;	poz[1][4] = -.4;
    pox[1][5] = -.625;		poy[1][5] = -.625;	poz[1][5] = -.4;
    pox[1][6] = .625;		poy[1][6] = -.625;	poz[1][6] = -.4;
    pox[1][7] = 1;			poy[1][7] = 0;		poz[1][7] = -.4;
    pox[1][8] = .625;		poy[1][8] = .625;	poz[1][8] = -.4;

    //back eye location
    pox[1][9] = -.5;		poy[1][9] = .375;	poz[1][9] = -.405;//8b

    pox[2][0] = 0.0;		poy[2][0] = -.325;	poz[2][0] = -.42;// right leg
    pox[2][1] = 0.0;		poy[2][1] = -.875;	poz[2][1] = -.42;
    pox[2][2] = -.25;		poy[2][2] = -.875;	poz[2][2] = -.42;

    pox[2][3] = 0.0;		poy[2][3] = -.375;	poz[2][3] = .42;//left leg
    pox[2][4] = 0.0;		poy[2][4] = -.875;	poz[2][4] = .42;
    pox[2][5] = -.25;		poy[2][5] = -.875;	poz[2][5] = .42;

    return;
}

//-------------------------------------------------------------------------
//  DrawPolyman
//	Draws the whole of polyman, this icon is used to move the him around
//-------------------------------------------------------------------------
void DrawPolyman(float pox[][10], float poy[][10], float poz[][10])
{
    //set draw color to white
    glColor3f(1.0f, 1.0f, 1.0f);

    //draw polyman, counter-clockwise winding
#pragma region "Front and Back sides"
    glBegin(GL_LINE_STRIP);//front side
    glVertex3f(pox[0][0], poy[0][0], poz[0][0]);
    glVertex3f(pox[0][1], poy[0][1], poz[0][1]);
    glVertex3f(pox[0][2] - tx1, poy[0][2] + ty1, poz[0][2]);
    glVertex3f(pox[0][3], poy[0][3], poz[0][3]);
    glVertex3f(pox[0][4] + tx1, poy[0][4] - ty1, poz[0][4]);
    glVertex3f(pox[0][5], poy[0][5], poz[0][5]);
    glVertex3f(pox[0][6], poy[0][6], poz[0][6]);
    glVertex3f(pox[0][7], poy[0][7], poz[0][7]);
    glVertex3f(pox[0][8], poy[0][8], poz[0][8]);
    glVertex3f(pox[0][0], poy[0][0], poz[0][0]);
    glEnd();

    glBegin(GL_LINE_STRIP);//back side
    glVertex3f(pox[0][0], poy[0][0], poz[1][0]);
    glVertex3f(pox[0][1], poy[0][1], poz[1][1]);
    glVertex3f(pox[0][2] - tx1, poy[0][2] + ty1, poz[1][2]);
    glVertex3f(pox[0][3], poy[0][3], poz[1][3]);
    glVertex3f(pox[0][4] + tx1, poy[0][4] - ty1, poz[1][4]);
    glVertex3f(pox[0][5], poy[0][5], poz[1][5]);
    glVertex3f(pox[0][6], poy[0][6], poz[1][6]);
    glVertex3f(pox[0][7], poy[0][7], poz[1][7]);
    glVertex3f(pox[0][8], poy[0][8], poz[1][8]);
    glVertex3f(pox[0][0], poy[0][0], poz[1][0]);
    glEnd();
#pragma endregion

#pragma region "Face and Mouth"

    glBegin(GL_LINE_STRIP);//forehead
    glVertex3f(pox[0][0], poy[0][0], poz[0][0]);
    glVertex3f(pox[0][0], poy[0][0], poz[1][0]);
    glVertex3f(pox[0][1], poy[0][1], poz[1][1]);
    glVertex3f(pox[0][1], poy[0][1], poz[0][1]);
    glVertex3f(pox[0][0], poy[0][0], poz[0][0]);
    glEnd();

    glBegin(GL_LINE_STRIP);//upper lip
    glVertex3f(pox[0][1], poy[0][1], poz[1][1]);
    glVertex3f(pox[0][2] - tx1, poy[0][2] + ty1, poz[1][2]);
    glVertex3f(pox[0][2] - tx1, poy[0][2] + ty1, poz[0][2]);
    glVertex3f(pox[0][1], poy[0][1], poz[0][1]);
    glVertex3f(pox[0][1], poy[0][1], poz[1][1]);
    glEnd();

    glBegin(GL_LINE_STRIP);//upper mouth
    glVertex3f(pox[0][2] - tx1, poy[0][2] + ty1, poz[1][2]);
    glVertex3f(pox[0][3], poy[0][3], poz[1][3]);
    glVertex3f(pox[0][3], poy[0][3], poz[0][3]);
    glVertex3f(pox[0][2] - tx1, poy[0][2] + ty1, poz[0][2]);
    glVertex3f(pox[0][2] - tx1, poy[0][2] + ty1, poz[1][2]);
    glEnd();


    glBegin(GL_LINE_STRIP);//lower mouth
    glVertex3f(pox[0][4] + tx1, poy[0][4] - ty1, poz[1][4]);
    glVertex3f(pox[0][3], poy[0][3], poz[1][3]);
    glVertex3f(pox[0][3], poy[0][3], poz[0][3]);
    glVertex3f(pox[0][4] + tx1, poy[0][4] - ty1, poz[0][4]);
    glVertex3f(pox[0][4] + tx1, poy[0][4] - ty1, poz[1][4]);
    glEnd();

    glBegin(GL_LINE_STRIP);//lower lip
    glVertex3f(pox[0][2] + tx1, poy[0][4] - ty1, poz[1][4]);
    glVertex3f(pox[0][5], poy[0][5], poz[1][5]);
    glVertex3f(pox[0][5], poy[0][5], poz[0][5]);
    glVertex3f(pox[0][2] + tx1, poy[0][4] - ty1, poz[0][4]);
    glVertex3f(pox[0][2] + tx1, poy[0][4] - ty1, poz[1][4]);
    glEnd();
#pragma endregion

#pragma region "Top and Bottom"

    glBegin(GL_LINE_STRIP);//top
    glVertex3f(pox[0][0], poy[0][0], poz[0][0]);
    glVertex3f(pox[0][8], poy[0][8], poz[0][8]);
    glVertex3f(pox[0][8], poy[0][8], poz[1][8]);
    glVertex3f(pox[0][0], poy[0][0], poz[1][0]);
    glVertex3f(pox[0][0], poy[0][0], poz[0][0]);
    glEnd();

    glBegin(GL_LINE_STRIP);//bottom
    glVertex3f(pox[0][5], poy[0][5], poz[0][5]);
    glVertex3f(pox[0][6], poy[0][6], poz[0][6]);
    glVertex3f(pox[0][6], poy[0][6], poz[1][6]);
    glVertex3f(pox[0][5], poy[0][5], poz[1][5]);
    glVertex3f(pox[0][5], poy[0][5], poz[0][5]);
    glEnd();

#pragma endregion

#pragma region "Back of Head/Body"
    glBegin(GL_LINE_STRIP);//upper back
    glVertex3f(pox[0][8], poy[0][8], poz[0][8]);
    glVertex3f(pox[0][7], poy[0][7], poz[0][7]);
    glVertex3f(pox[0][7], poy[0][7], poz[1][7]);
    glVertex3f(pox[0][8], poy[0][8], poz[1][8]);
    glVertex3f(pox[0][8], poy[0][8], poz[0][8]);
    glEnd();

    glBegin(GL_LINE_STRIP);//lower back
    glVertex3f(pox[0][7], poy[0][7], poz[0][7]);
    glVertex3f(pox[0][6], poy[0][6], poz[0][6]);
    glVertex3f(pox[0][6], poy[0][6], poz[1][6]);
    glVertex3f(pox[0][7], poy[0][7], poz[1][7]);
    glVertex3f(pox[0][7], poy[0][7], poz[0][8]);
    glEnd();
#pragma endregion

#pragma region "Eyes"
    //eye, blue color
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.4f, 0.7f);
    glVertex3f(pox[0][9], poy[0][9], poz[0][9]);
    glVertex3f(pox[0][9] + .03, poy[0][9] + .03, poz[0][9]);
    glVertex3f(pox[0][9] + .09, poy[0][9] + .03, poz[0][9]);
    glVertex3f(pox[0][9] + .1, poy[0][9], poz[0][9]);
    glVertex3f(pox[0][9] + .1, poy[0][9] - .03, poz[0][9]);
    glVertex3f(pox[0][9] + .09, poy[0][9] - .06, poz[0][9]);
    glVertex3f(pox[0][9] + .03, poy[0][9] - .06, poz[0][9]);
    glVertex3f(pox[0][9] + .03, poy[0][9] - .03, poz[0][9]);
    glEnd();

    //back eye
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.4f, 0.7f);
    glVertex3f(pox[0][9], poy[0][9], poz[1][9]);
    glVertex3f(pox[0][9] + .03, poy[0][9] + .03, poz[1][9]);
    glVertex3f(pox[0][9] + .09, poy[0][9] + .03, poz[1][9]);
    glVertex3f(pox[0][9] + .1, poy[0][9], poz[1][9]);
    glVertex3f(pox[0][9] + .1, poy[0][9] - .03, poz[1][9]);
    glVertex3f(pox[0][9] + .09, poy[0][9] - .06, poz[1][9]);
    glVertex3f(pox[0][9] + .03, poy[0][9] - .06, poz[1][9]);
    glVertex3f(pox[0][9] + .03, poy[0][9] - .03, poz[1][9]);
    glEnd();
#pragma endregion

    return;
}

//-------------------------------------------------------------------------
//  SetTrans
//	Sets up the transformations based on values passed in from 
//	parameters set globally, moves all of polyman
//-------------------------------------------------------------------------
void SetTrans()
{
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    glTranslatef(dx, dy, dz);
    glRotated(theta, 0.0, 0.0, 1.0);
    return;
}

//-------------------------------------------------------------------------
//  TimerFunction 
//	Animates the icon by changing its location, scale, and rotation
//	contains a switch statement that switches on key frames
//-------------------------------------------------------------------------
void TimerFunction(int value)
{
    //if paused dont change any variables, just skip to redraw callback
    if (!paused) {
        switch (frame)
        {
            // walk in to scene from right
            case 1:
                //moves whole polyman
                dx -= 0.05;

                //animates right leg rotating back and forth
                if (thetaRL <= 5.0 && backward) {
                    thetaRL += 1;
                }
                else {
                    backward = false;
                }
                if (thetaRL >= -5.0 && !backward) {
                    thetaRL -= 1;
                }
                else {
                    backward = true;
                }

                //animates left leg rotating back and forth
                if (thetaLL <= 5.0 && !backward) {
                    thetaLL += 1;
                }

                if (thetaLL >= -5.0 && backward) {
                    thetaLL -= 1;
                }

                //when were center screen, stop and default vars
                if (dx <= 0.0) {
                    dx = 0.0;
                    thetaRL = 0.0;
                    thetaLL = 0.0;
                    frame = 2;
                }
                break;

                //open mouth
            case 2:
                closedMouth = false;
                tx1 += .016;
                ty1 += .0270;
                if (tx1 > .15) {
                    frame = 3;
                }
                break;

                //rise to top of scene from middle
            case 3:
                dy += 0.2;
                if (dy > 5.0) {
                    dy = 5.0;
                    frame = 4;
                }
                break;
                //flip around 360 at top of scene
            case 4:
                theta -= 12.0;
                if (theta <= -360.0) {
                    theta = 0;
                    frame = 5;
                }
                break;

                //fall to middle center of scene
            case 5:
                dy -= 0.25;
                if (dy < 1.0) {
                    dy = 1.0;
                    dx = 0;
                    frame = 6;
                }
                break;
                //walk off scene to the left
            case 6:
                //translate the whole icon left off screen
                if (dy = 1.0) {
                    dx -= 0.05;
                }
                //animates right leg rotating back and forth
                if (thetaRL <= 5.0 && backward) {
                    thetaRL += 1;
                }
                else {
                    backward = false;
                }
                if (thetaRL >= -5.0 && !backward) {
                    thetaRL -= 1;
                }
                else {
                    backward = true;
                }
                //animates left leg rotating back and forth
                if (thetaLL <= 5.0 && !backward) {
                    thetaLL += 1;
                }

                if (thetaLL >= -5.0 && backward) {
                    thetaLL -= 1;
                }

                //animate closing mouth until its closed
                if (tx1 > .01) {
                    tx1 -= .016;
                    ty1 -= .0270;
                }
                else {
                    tx1 = .01;
                    ty1 = .01;
                    closedMouth = true;
                }
                //stops outside of ortho intentionally so he walks all the way off screen
                if (dx <= -9.0) {
                    dx = 9.0;
                    frame = 1;
                }
                break;
        }
    }
    //redraw scene with current co-ords if not paused
    if (!paused) {
        glutPostRedisplay();
    }
    glutTimerFunc(30, TimerFunction, 1);

}

//-------------------------------------------------------------------------
//  ScaleDisplay
//	Utility function passed to the reshape function and triggered
//	by the display window resizing. This reshapes the viewport and
//	sets the camera perspective
//-------------------------------------------------------------------------
void ScaleDisplay(int width, int height) {

    //calc aspect ratio
    float ratio = ((float)width) / height;

    // switch to projection matrix to change camera perspective
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set viewport same size as window
    glViewport(0, 0, width, height);

    // Set 70 deg FoV, aspect ratio to current window ratio,
    // near clipping to basically zero, and far clipping to 50 units
    gluPerspective(70.0f, ratio, 0.1f, 50.0f);

    // switch back to modelview immediately to prevent errors
    glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------
//  Keys
//	Utility function to handle glutkeybordFunc and triggered
//	when keyboard keys are pressed, assigns actions to keybaord keys
//-------------------------------------------------------------------------
void Keys(unsigned char key, int mouseX, int mouseY) {
    switch (key) {
        //key pressed was spacebar, toggle pause
        case ' ':
            // pause if not paused
            if (!paused) {
                paused = true;
            }
                // unpause if paused
            else {
                paused = false;
            }
            break;
    }
}
