/*
3D Racing Demo
Slava Feoktistov    10336661
Conor Murphy        59511580
*/

#include <SDL/SDL.h>
#include "SDL/SDL_thread.h"
#include "SDL/SDL_mutex.h"
#include "SDL/SDL_ttf.h"
#include <GL/gl.h>
#include "Car.h"
#include "Timer.h"
#include "Skybox.h"
#include "Functions.h"
#include "Terrian.h"
#include <iostream>
#include <string>
#include <sstream>
#ifndef M_PI    //if the pi is not defined in the cmath header file
#define M_PI 3.1415926535       //define it
#endif


//Create Object variables.
Skybox sky = Skybox();
Car car = Car();
Terrian level = Terrian();
//Create car variables.
float w1,w2,w3,w4;
bool canControl;
float fSpd1,fSpd2,fSpd3,fSpd4;

//Creates Font variables for use in menu.
TTF_Font *font;
SDL_Surface *screen = NULL;

//Create the Threads and Mutex
SDL_mutex* console_mutex;
SDL_Thread *thread1;
SDL_Thread *thread2;

//Create timer objects.
Timer update;
Timer fps;

//Set variables.
bool isRunning;
bool init_video=false;
int frame;
int frame2;
unsigned int list1, objWheel, objCar;

//Variables for fps limitation.
bool cap = true;
const int FRAMES_PER_SECOND = 60;

//Matrix array for storing matrix for use with matrix manipulation functions.
GLfloat matrix1[16];
GLfloat matrix2[16];


//Initiate SDL and Create mutex
void init_SDL()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    screen = SDL_SetVideoMode(1200,800,32,SDL_SWSURFACE);
    font = TTF_OpenFont("Texture/lazy.ttf",30);
    console_mutex = SDL_CreateMutex();
    remove("Log.txt");
    freopen("Log.txt","w",stdout);
    std::cout << "SDL Initiated." << std::endl;
}

//Render thread that controls all the rendering in OpenGL.
int render(void *data)
{
    //Create window with set resolution 1200x800 using a software surface on the SDL side and obtain Context using SDL_OPENGL.
    SDL_SetVideoMode(1200,800,32,SDL_SWSURFACE|SDL_OPENGL);
    SDL_WM_SetCaption("3D Desert Racer", NULL);
    std::cout << "Video Initiated." << std::endl;
    const char* vendor = (const char*)glGetString( GL_VENDOR );
    const char* renderer = (const char*)glGetString( GL_RENDERER );
    const char* version = (const char*)glGetString( GL_VERSION );
    //General info about the users Video card and current installed openGL.
    std::cout << "OPENGL Version:  " << version << std::endl;
    std::cout << "OPENGL Renderer:  " << renderer << std::endl;
    std::cout << "OPENGL Vendor:  " << vendor << std::endl;

    glClearColor(0.0,0.0,0.0,1.0);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Sets Perspectivefor the camera.
    gluPerspective(45,1200.0/800.0,1.0,3000.0);
    //Enable all the required GL drawing parameters.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    //Sets lighting properties.
    float dif[] = {1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    float amb[] = {0.2,0.2,0.2,1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);

    //Load car Objects and Textures.
    level.loadGround();
    objWheel = objloader::load("Texture/Wheel2.obj");
    objCar = objloader::load("Texture/Chassis.obj");

    list1 = level.BuildList();
    //sets the matrixmode to ModelView matrix.
    glMatrixMode(GL_MODELVIEW);

    std::cout << "Video Initiated." << std::endl;
    init_video=true;

    //Main render thread loop.
    while(isRunning)
    {
        //Lock Mutex
        SDL_LockMutex(console_mutex);
        //std::cout << "Render thread started." << std::endl;
        fps.start();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        float pos[] = {200.0,300.0,200.0,1.0};

        //Resets Matrix to all 0's.
        glLoadIdentity();
        //Does all the translations and rotates for the drawings.
        car.UpdateCamera();
        //Draws the skybox.
        sky.draw();
        glPushMatrix();
            car.UpdateCar();
            glLightfv(GL_LIGHT0, GL_POSITION, pos);
            //Render call to the list that contains the terrain heightmap.
            glCallList(list1);
        glPopMatrix();
        car.rotCar();
        //Draw the chassis of the car with translations/rotations.
        glPushMatrix();
            glTranslatef(0.2,car.carY+2,0.0);
            glRotatef(car.carPitch,1.0,0.0,0.0);
            glRotatef(car.carRoll,0.0,0.0,1.0);

            glRotatef(77,0.0,1.0,0.0);
            glRotatef(25,1.0,0.0,0.0);
            glScalef(0.6,0.6,0.6);
            glCallList(objCar);
        glPopMatrix();
        //Draw and translate/rotate the wheels.
        glPushMatrix();
        glTranslatef(1.5,w1+1,-1.8);
        glRotatef(90,0.0,1.0,0.0);
        glRotatef(car.carRoll,0.0,0.0,1.0);
        glScalef(0.6,0.6,0.6);
        glCallList(objWheel);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-1.5,w2+1,1.5);
        glRotatef(90,0.0,1.0,0.0);
        glRotatef(car.carRoll,0.0,0.0,1.0);
        glScalef(0.6,0.6,0.6);
        glCallList(objWheel);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(1.5,w3+1,1.5);
        glRotatef(90,0.0,1.0,0.0);
        glRotatef(car.carRoll,0.0,0.0,1.0);
        glScalef(0.6,0.6,0.6);
        glCallList(objWheel);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-1.5,w4+1,-1.8);
        glRotatef(90,0.0,1.0,0.0);
        glRotatef(car.carRoll,0.0,0.0,1.0);
        glScalef(0.6,0.6,0.6);
        glCallList(objWheel);
        glPopMatrix();

        //This bit gets the Position 1.5,1.8 and -1.5,1.5 after rotations for the exact x,z positions of the wheels.
        //matrix1 will contain the new (x,y,z) at rotation/translation in (matrix1[12],matrix1[13],matrix[14]);
        glPushMatrix();
            glLoadIdentity();
            car.rotCar();
            glTranslatef(1.5,0.0,1.8);
            glGetFloatv (GL_MODELVIEW_MATRIX, matrix1);
            glLoadIdentity();
            car.rotCar();
            glTranslatef(-1.5,0.0,1.5);
            glGetFloatv (GL_MODELVIEW_MATRIX, matrix2);
        glPopMatrix();
        //Swaps the drawing buffers.
        SDL_GL_SwapBuffers();
        //Counts the rendering frames for the fps count in the logic thread.
        frame2++;
        //Unlocks the mutex.
        SDL_UnlockMutex(console_mutex);
        //std::cout << "Render thread end loop." << std::endl;
        //Sets a delay so each run of the loops lasts 1/60 of a second, makes the max fps of the thread to be 60 per second.
        if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
        { //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }

    }
    return(0);
}

//Logic Thread, used for physics and positioning.
int logic(void *data)
{
    //Waits til the Render thread initiated & loaded everything
    while(init_video==false)
        SDL_Delay(20);
    while(isRunning)
    {
        //Locks Mutex.
        SDL_LockMutex(console_mutex);
        //std::cout << "Logic thread started." << std::endl;
        float jump = ((w1+w4)/2)-((w2+w3)/2);
        //Used to calculate physics for each of the wheels.
        if(w1 > level.getHeight(car.carX-matrix2[12],car.carZ-matrix2[14]))
        {
            //Basic gravity of the car.
            fSpd1+=0.01;
            w1-=fSpd1;
            //sets the limit each wheel can move in the Y axis in relation to w1.
            if(w1 > w2+2)
                w1=w2+2;
            else if(w1 > w3+2)
                w1=w3+2;
            else if(w1 > w4+0.5)
                w1=w4+0.5;
        }else if(w1 < level.getHeight(car.carX-matrix2[12],car.carZ-matrix2[14]))
        {
            //Sets the car wheel to the height of the terrain at that point and resets fall Speed (fSpd);
            w1 = level.getHeight(car.carX-matrix2[12],car.carZ-matrix2[14]);
            fSpd1=car.CarSpeed*jump*0.025;
        }

        if(w4 > level.getHeight(car.carX-matrix1[12],car.carZ-matrix1[14]))
        {
            fSpd4+=0.01;
            w4-=fSpd4;
            if(w4 > w2+2)
                w4=w2+2;
            else if(w4 > w3+2)
                w4=w3+2;
            else if(w4 > w1+0.5)
                w4=w1+0.5;
        }else if(w4 < level.getHeight(car.carX-matrix1[12],car.carZ-matrix1[14]))
        {
            w4 = level.getHeight(car.carX-matrix1[12],car.carZ-matrix1[14]);
            fSpd4=car.CarSpeed*jump*0.025;
        }

        if(w3 > level.getHeight(car.carX+matrix1[12],car.carZ+matrix1[14]))
        {
            fSpd3+=0.01;
            w3-=fSpd3;
            if(w3 > w2+0.5)
                w3=w2+0.5;
            else if(w3 > w1+2)
                w3=w1+2;
            else if(w3 > w4+2)
                w3=w4+2;
        }else if(w3 < level.getHeight(car.carX+matrix1[12],car.carZ+matrix1[14]))
        {
            w3 = level.getHeight(car.carX+matrix1[12],car.carZ+matrix1[14]);
            fSpd3=car.CarSpeed*jump*0.025;
        }

        if(w2 > level.getHeight(car.carX+matrix2[12],car.carZ+matrix2[14]))
        {
            fSpd2+=0.01;
            w2-=fSpd2;
            if(w2 > w1+2)
                w2=w1+2;
            else if(w2 > w3+0.5)
                w2=w3+0.5;
            else if(w2 > w4+2)
                w2=w4+2;
        }else if(w2 < level.getHeight(car.carX+matrix2[12],car.carZ+matrix2[14]))
        {
            w2 = level.getHeight(car.carX+matrix2[12],car.carZ+matrix2[14]);
            fSpd2=car.CarSpeed*jump*0.025;
        }

        canControl=true;
        //Movements for the car.
        car.Control(canControl);

        //Controlls the Y of the car in relation to the average of all the wheels.
        car.carY=(w1+w2+w3+w4)/4;
        //Makes cam height equal to the car height + 10.
        car.camY=car.carY+10;

        //Uses pythagorises theorim to calculate the angle between the front and back wheels.
        float opp1 = ((w1+w4)/2)-((w2+w3)/2);
        float hyp1 = 3.3;
        //sets carPitch to the angle found.
        car.carPitch = asin(opp1/hyp1)*(180/M_PI);

        //Uses pythagorises theorim to calculate the angle between the Left and Right side wheels.
        float opp2 = ((w1+w3)/2)-((w2+w4)/2);
        float hyp2 = 3;
        //sets carRoll to the angle found.
        car.carRoll = asin(opp2/hyp2)*(180/M_PI);

        //increases the distance of the car the faster the car goes.
        car.camDist=car.CarSpeed+20;
        //Sets the YawSpeed to be large the further the angle between the cam yaw and car yaw
        car.YawSpeed = car.camYaw - car.carYaw;

        //Changes the Yaw of the camera gradually.
        if(car.YawSpeed<90)
        {
            car.camYaw-=car.YawSpeed/5;
        }else if(car.YawSpeed>90)
        {
            car.camYaw+=car.YawSpeed/5;
        }

        frame++;
        //std::cout << "Logic thread end loop." << std::endl;
        //Unlocks the mutex
        SDL_UnlockMutex(console_mutex);
        //delays the thread.
        SDL_Delay(1000/60);
        //Writes the fps of both threads to the top of the window.
        if( update.get_ticks() > 1000 )
        {
            std::stringstream caption;
            caption << "3D Desert Racer, FPS Main: " << frame << ",   FPS Rendering: " << frame2 << std::endl;
            //Restart the update timer.
            update.start();
            frame=0;
            frame2=0;
            SDL_WM_SetCaption( caption.str().c_str(), NULL );
        }
    }
    return(0);
}

int main(int argc, char* args[])
{
    init_SDL();
    //Starts the menu screen, i==1 is Quit, else turn on the game.
    int i = objloader::showmenu(screen, font);
    if(i==1)
    {
        isRunning=false;
        SDL_Quit();
    }else
    {
        screen = NULL;
        isRunning=true;
    }
    //lets isRunning to true;
    update.start();
    //Creates the threads .
    thread1 = SDL_CreateThread(render, NULL);
    thread2 = SDL_CreateThread(logic, NULL);
    //Create a new Event call object.
    SDL_Event event;
    while(isRunning)
    {
        //Set certain keys to have events attached to them.
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_RETURN)
                {
                    cap = ( !cap );
                }
                else if(event.key.keysym.sym == SDLK_e)
                {
                    //Scrolls throught the skybox
                    sky.currentSkybox++;
                    if(sky.currentSkybox > 4)
                    {
                        sky.currentSkybox = 0;
                    }
                }
                if(event.key.keysym.sym == SDLK_w)
                {
                    car.up=true;
                }else if(event.key.keysym.sym == SDLK_s)
                {
                    car.down=true;
                }
                if(event.key.keysym.sym == SDLK_a)
                {
                    car.left=true;
                }else if(event.key.keysym.sym == SDLK_d)
                {
                    car.right=true;
                }
            }
            if(event.type == SDL_KEYUP)
            {
                if(event.key.keysym.sym == SDLK_w)
                {
                    car.up=false;
                }else if(event.key.keysym.sym == SDLK_s)
                {
                    car.down=false;
                }
                if(event.key.keysym.sym == SDLK_a)
                {
                    car.left=false;
                }else if(event.key.keysym.sym == SDLK_d)
                {
                    car.right=false;
                }
            }
        }

        SDL_Delay(1000/60);
    }
    //Waits til the threads site
    SDL_WaitThread(thread1, NULL);
    SDL_WaitThread(thread2, NULL);
    //Cleanup handler.
    glDeleteLists(list1, 1);
    glDeleteLists(objCar, 1);
    glDeleteLists(objWheel, 1);
    TTF_CloseFont(font);
    TTF_Quit();
    sky.killSkybox();
    //Exits SDL
    SDL_Quit();

    return(0);
}
