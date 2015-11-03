#ifndef SPHERE_H
#define SPHERE_H
#include <GL/GL.h>
#include <GL/GLU.h>
#include <cmath>
#include <vector>

class Sphere
{
    public:
        Sphere(float radius, unsigned int rings, unsigned int sectors);
        void draw(GLfloat x, GLfloat y, GLfloat z);
    private:
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> normals;
        std::vector<GLfloat> texcoords;
        std::vector<GLushort> indices;



};

#endif // SPHERE_H
