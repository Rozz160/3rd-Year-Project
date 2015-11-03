#ifndef CAR_H
#define CAR_H
#include "Camera.h"
#include <GL/gl.h>
#include <cmath>
#include <vector>

struct wheel
{
    float x,y,z;
};

class Car: public Camera
{

    public:
        float carX,carY,carZ;
        float carPitch,carYaw,carRoll,YawSpeed,CarSpeed,MaxSpeed;

        float w1X,w1Z,w2X,w2Z,w3X,w3Z,w4X,w4Z;
        Car();
        void moveCar(float,float);
        void Control(bool);
        void UpdateCar();
        void rotCarPitch();
        void rotCar();
        void updateCam();
        bool Forward, Reverse, up, down, left, right;

    private:

};

#endif // CAR_H
