#include "Camera.h"
#ifndef M_PI    //if the pi is not defined in the cmath header file
#define M_PI 3.1415926535       //define it
#endif
float camX,camY,camZ;
float camYaw,camPitch;
float camDist;

void Camera::lockCamera()
{
        //set campitch between -90 and 90 and set camyaw between 0 and 360 degrees
        if(camPitch>90)
                camPitch=90;
        if(camPitch<-90)
                camPitch=-90;
        /*if(camYaw<0.0)
                camYaw+=360.0;
        if(camYaw>360.0)
                camYaw-=360;*/
}

//moveCamera is called to rotate around an origin at a distance (dist);
void Camera::moveCamera()
{
    float rad=(camYaw)*M_PI/180.0;      //convert the degrees into radians
    camX=camDist*sin(rad);    //calculate the new coorinate, if you don't understand, draw a right triangle with the datas, you have
    camZ=camDist*cos(rad);    //and try to calculate the new coorinate with trigonometric functions, that should help
}

void Camera::UpdateCamera()
{
    glRotatef(-camPitch,1.0,0.0,0.0);       //rotate the camera (more precisly move everything in the opposit direction)
    glRotatef(-camYaw,0.0,1.0,0.0);
    glTranslatef(-camX,-camY,-camZ);        //move the camera
}


