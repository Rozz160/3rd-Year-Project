#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#define GL_UNSIGNED_INT_8_8_8_8 0x8035
#define GL_CLAMP_TO_EDGE 0x812F
#ifndef OBJLOADER_H
#define OBJLOADER_H

//This struct contain 3 floats and a constructor, it's used for vertexes and normal vectors
struct coordinate{
        float x,y,z;
        coordinate(float a,float b,float c);
};

//This structure is store every property of a face
struct face{
        int facenum;    //the number of the face (it's start from 1 not 0, so if you use it as an index, subtract 1 from it), it's used for the normal vectors
        bool four;              //if true, than it's a quad else it's a triangle
        int faces[4];   //indexes for every vertex, which makes the face (it's start from 1 not 0, so if you use it as an index, subtract 1 from it)
        int texcoord[4];        //indexes for every texture coorinate that is in the face (it's start from 1 not 0, so if you use it as an index, subtract 1 from it)
        int mat;                                        //the index for the material, which is used by the face
        face(int facen,int f1,int f2,int f3,int t1,int t2,int t3,int m);        //constuctor for triangle
        face(int facen,int f1,int f2,int f3,int f4,int t1,int t2,int t3,int t4,int m);  //-"- for quad
};

//this is a structure, which contain one material
struct material{
        std::string name;       //the name of the material
        float alpha,ns,ni;      //some property, alpha, shininess, and some other, which we not used
        float dif[3],amb[3],spec[3];    //the color property (diffuse, ambient, specular)
        int illum;      //illum - we not use it
        int texture;    //the id for the texture, if there is no texture than -1
        material(const char* na,float al,float n,float ni2,float* d,float* a,float* s,int i,int t);
};

//texture coorinate (UV coordinate), nothing to explain here
struct texcoord{
        float u,v;
        texcoord(float a,float b);
};

//the main class for the object loader
class objloader{



        static void clean();   //free all of the used memory

        public:
        objloader();
        ~objloader();   //free the textures and lists
        static int load(const char* filename); //the main model load function
        static unsigned int loadTexture(const char* filename); //private load texture function
        static int showmenu(SDL_Surface*, TTF_Font*);
};

#endif
