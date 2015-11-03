#include "Ground.h"

Ground::Ground()
{
    //ctor
}

void Ground::loadGround()
{
     ground = loadTexture("Texture/grass1.jpg");
}
void Ground::drawGround(float size)
{
    glBindTexture(GL_TEXTURE_2D,ground);
    glBegin(GL_QUADS);
        glTexCoord2f(1,1);
        glVertex3f(size/2,-5.0,size/2);
        glTexCoord2f(0,1);
        glVertex3f(-size/2,-5.0,size/2);
        glTexCoord2f(0,0);
        glVertex3f(-size/2,-5.0,-size/2);
        glTexCoord2f(1,0);
        glVertex3f(size/2,-5.0,-size/2);
    glEnd();
}
