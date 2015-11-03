#include "Car.h"

#ifndef M_PI    //if the pi is not defined in the cmath header file
#define M_PI 3.1415926535       //define it
#endif
float carX,carY,carZ;
float carPitch,carYaw,carRoll, YawSpeed, CarSpeed, MaxSpeed;
bool Forward, Reverse, up, down, left, right;
float w1X,w1Z,w2X,w2Z,w3X,w3Z,w4X,w4Z;


std::vector<wheel> w;
//The Constuctor sets some variables needed at creation.
Car::Car()
{
    camPitch = -20.0;
    camDist = 100;
    carX=200;
    carZ=200;

    MaxSpeed=1;
}

void Car::moveCar(float dist,float dir)
{
    //convert the degrees into radians
    float rad=(carYaw+dir)*M_PI/180.0;
    carX-=sin(rad)*dist;    //calculate the new coorinate, if you don't understand, draw a right triangle with the datas, you have
    carZ-=cos(rad)*dist;    //and try to calculate the new coorinate with trigonometric functions, that should help
}

//Contains the logic to move the car.
void Car::Control(bool canControl)
{
    //If the car isnt in the air.
    if(canControl)
    {
        if(up)
        {
            //If pressed forward while going backwards, decrease speed.
            if(Reverse==true && CarSpeed >0)
            {
                CarSpeed-=0.01;
                moveCar(CarSpeed,180.0);
            }else //If pressed forward and not reversing, move.
            {
                Reverse=false;
                Forward = true;
                if(CarSpeed < MaxSpeed)
                    CarSpeed+=0.008;
                moveCar(CarSpeed,0.0);
            }
        }else if(down)
        {
            if(Forward==true && CarSpeed >0)
            {
                CarSpeed-=0.02;
                moveCar(CarSpeed,0.0);
            }else
            {
                Forward=false;
                Reverse = true;
                if(CarSpeed < MaxSpeed)
                    CarSpeed+=0.006;
                moveCar(CarSpeed,180.0);
            }
        }
        //Can only turn car when moving forward or backwards.
        if(Forward == true)
        {
            if(left)       //move left
                carYaw+=2;
            else if(right)  //move right
                carYaw-=2;
        }else if(Reverse == true)
        {
            if(left)       //move left
                carYaw-=2;
            else if(right)  //move right
                carYaw+=2;
        }
    }

    //Decrease the car speed when above 0 speed.
    if(CarSpeed >0)
    {
        CarSpeed-=0.002;
        if(Forward)
            moveCar(CarSpeed,0.0);
        else if(Reverse)
            moveCar(CarSpeed,180.0);
    }else
    {
        Forward=false;
        Reverse=false;
    }
    moveCamera();
}
void Car::rotCarPitch()
{
    glRotatef(carPitch,1.0,0.0,0.0);
}

void Car::rotCar()
{
    glRotatef(carYaw,0.0,1.0,0.0);
}
void Car::UpdateCar()
{
    glTranslatef(-carX,-carY,-carZ);
}
