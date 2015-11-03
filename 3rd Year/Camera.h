#ifndef CAMERA_H
#define CAMERA_H
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <cmath>
#include <iostream>

class Camera
{
    public:
        float camX,camY,camZ;
        float camYaw,camPitch;
        float camDist;
        void lockCamera();
        void moveCamera();
        void UpdateCamera();
};

#endif // CAMERA_H
