#include <GL/GLU.h>
#include "Functions.h"
#include <iostream>
#ifndef SKYBOX_H
#define SKYBOX_H


class Skybox
{
    public:
        int currentSkybox;
        Skybox();
        void loadSkybox1();
        void loadSkybox2();
        void loadSkybox3();
        void loadSkybox4();
        void loadSkybox5();
        void drawSkybox(float,unsigned int sky[]);
        void killSkybox();
        void draw();
    private:
        enum {SKY_LEFT, SKY_BACK, SKY_RIGHT, SKY_FRONT, SKY_TOP, SKY_BOTTOM};
        unsigned int skybox[5][6];
        bool loadedSkybox[5];
};

#endif // SKYBOX_H
