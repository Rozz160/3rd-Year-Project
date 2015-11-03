#ifndef TERRIAN_H
#define TERRIAN_H
#include <GL/GLU.h>
#include "Functions.h"
#include "Car.h"
#include <iostream>
#include <vector>

class Terrian
{
    private:
        unsigned int ground;
        float height;
        float size;
    public:
        std::vector<std::vector<float> > hHeightField;
        Terrian();
        void loadHeightMap(const char*);
        void renderHeightMap();
        void loadGround();
        int BuildList();
        float heightY(float,float);
        float Lerp(float,float,float);
        float getHeight(float,float);
    protected:

};

#endif // TERRIAN_H
