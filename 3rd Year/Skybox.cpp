#include "Skybox.h"

enum {SKY_LEFT=0, SKY_BACK, SKY_RIGHT, SKY_FRONT, SKY_TOP, SKY_BOTTOM};

unsigned int skybox[5][6];
int currentSkybox = 0;
bool loadedSkybox[5];

Skybox::Skybox()
{
    //ctor
}

//Loads each side of the Texture into the 2d array and sets loadedSkybox[i] to true;
void Skybox::loadSkybox1()
{
    //skybox1
    skybox[0][SKY_LEFT]=objloader::loadTexture("Skybox/s3/skyrender0004.bmp");
    skybox[0][SKY_BACK]=objloader::loadTexture("Skybox/s3/skyrender0002.bmp");
    skybox[0][SKY_RIGHT]=objloader::loadTexture("Skybox/s3/skyrender0001.bmp");
    skybox[0][SKY_FRONT]=objloader::loadTexture("Skybox/s3/skyrender0005.bmp");
    skybox[0][SKY_TOP]=objloader::loadTexture("Skybox/s3/skyrender0003.bmp");
    skybox[0][SKY_BOTTOM]=objloader::loadTexture("Skybox/s3/skyrender0006.bmp");
    loadedSkybox[0] = true;
}

void Skybox::loadSkybox2()
{
    //skybox2
    skybox[1][SKY_LEFT]=objloader::loadTexture("Skybox/s2/skyrender0004.bmp");
    skybox[1][SKY_BACK]=objloader::loadTexture("Skybox/s2/skyrender0002.bmp");
    skybox[1][SKY_RIGHT]=objloader::loadTexture("Skybox/s2/skyrender0001.bmp");
    skybox[1][SKY_FRONT]=objloader::loadTexture("Skybox/s2/skyrender0005.bmp");
    skybox[1][SKY_TOP]=objloader::loadTexture("Skybox/s2/skyrender0003.bmp");
    skybox[1][SKY_BOTTOM]=objloader::loadTexture("Skybox/s2/skyrender0006.bmp");
    loadedSkybox[1] = true;
}

void Skybox::loadSkybox3()
{
    //skybox2
    skybox[2][SKY_LEFT]=objloader::loadTexture("Skybox/halo1/halo_sky2rt.bmp");
    skybox[2][SKY_BACK]=objloader::loadTexture("Skybox/halo1/halo_sky2bk.bmp");
    skybox[2][SKY_RIGHT]=objloader::loadTexture("Skybox/halo1/halo_sky2lf.bmp");
    skybox[2][SKY_FRONT]=objloader::loadTexture("Skybox/halo1/halo_sky2ft.bmp");
    skybox[2][SKY_TOP]=objloader::loadTexture("Skybox/halo1/halo_sky2up.bmp");
    skybox[2][SKY_BOTTOM]=objloader::loadTexture("Skybox/halo1/halo_sky2dn.bmp");
    loadedSkybox[2] = true;
}

void Skybox::loadSkybox4()
{
    //skybox2
    skybox[3][SKY_LEFT]=objloader::loadTexture("Skybox/halo2/halo_sky1rt.bmp");
    skybox[3][SKY_BACK]=objloader::loadTexture("Skybox/halo2/halo_sky1bk.bmp");
    skybox[3][SKY_RIGHT]=objloader::loadTexture("Skybox/halo2/halo_sky1lf.bmp");
    skybox[3][SKY_FRONT]=objloader::loadTexture("Skybox/halo2/halo_sky1ft.bmp");
    skybox[3][SKY_TOP]=objloader::loadTexture("Skybox/halo2/halo_sky1up.bmp");
    skybox[3][SKY_BOTTOM]=objloader::loadTexture("Skybox/halo2/halo_sky1dn.bmp");
    loadedSkybox[3] = true;
}

void Skybox::loadSkybox5()
{
    //skybox2
    skybox[4][SKY_LEFT]=objloader::loadTexture("Skybox/real1/sky55rt.bmp");
    skybox[4][SKY_BACK]=objloader::loadTexture("Skybox/real1/sky55bk.bmp");
    skybox[4][SKY_RIGHT]=objloader::loadTexture("Skybox/real1/sky55lf.bmp");
    skybox[4][SKY_FRONT]=objloader::loadTexture("Skybox/real1/sky55ft.bmp");
    skybox[4][SKY_TOP]=objloader::loadTexture("Skybox/real1/sky55up.bmp");
    skybox[4][SKY_BOTTOM]=objloader::loadTexture("Skybox/real1/sky55dn.bmp");
    loadedSkybox[4] = true;
}

//Draws the skybox, must be given the size of the skybox and the unsigned int location
//of where the texture for the certain terrain is kept.
void Skybox::drawSkybox(float size, unsigned int sky[])
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,sky[SKY_BACK]);  //use the texture we want
    glBegin(GL_QUADS);      //and draw a face
        //back face
        glColor3f(255,255,255);
        glTexCoord2f(0,0);      //use the correct texture coordinate
        glVertex3f(size/2,size/2,size/2);       //and a vertex
        glTexCoord2f(1,0);      //and repeat it...
        glVertex3f(-size/2,size/2,size/2);
        glTexCoord2f(1,1);
        glVertex3f(-size/2,-size/2,size/2);
        glTexCoord2f(0,1);
        glVertex3f(size/2,-size/2,size/2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,sky[SKY_LEFT]);
    glBegin(GL_QUADS);
        //left face
        glColor3f(255,255,255);
        glTexCoord2f(0,0);
        glVertex3f(-size/2,size/2,size/2);
        glTexCoord2f(1,0);
        glVertex3f(-size/2,size/2,-size/2);
        glTexCoord2f(1,1);
        glVertex3f(-size/2,-size/2,-size/2);
        glTexCoord2f(0,1);
        glVertex3f(-size/2,-size/2,size/2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,sky[SKY_FRONT]);
    glBegin(GL_QUADS);
        //front face
        glColor3f(255,255,255);
        glTexCoord2f(1,0);
        glVertex3f(size/2,size/2,-size/2);
        glTexCoord2f(0,0);
        glVertex3f(-size/2,size/2,-size/2);
        glTexCoord2f(0,1);
        glVertex3f(-size/2,-size/2,-size/2);
        glTexCoord2f(1,1);
        glVertex3f(size/2,-size/2,-size/2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,sky[SKY_RIGHT]);
    glBegin(GL_QUADS);
        //right face
        glColor3f(255,255,255);
        glTexCoord2f(0,0);
        glVertex3f(size/2,size/2,-size/2);
        glTexCoord2f(1,0);
        glVertex3f(size/2,size/2,size/2);
        glTexCoord2f(1,1);
        glVertex3f(size/2,-size/2,size/2);
        glTexCoord2f(0,1);
        glVertex3f(size/2,-size/2,-size/2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,sky[SKY_TOP]);
    glBegin(GL_QUADS);
        glColor3f(255,255,255);//top face
        glTexCoord2f(1,0);
        glVertex3f(size/2,size/2,size/2);
        glTexCoord2f(0,0);
        glVertex3f(-size/2,size/2,size/2);
        glTexCoord2f(0,1);
        glVertex3f(-size/2,size/2,-size/2);
        glTexCoord2f(1,1);
        glVertex3f(size/2,size/2,-size/2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,sky[SKY_BOTTOM]);
    glBegin(GL_QUADS);
        //bottom face
        glColor3f(255,255,255);
        glTexCoord2f(1,1);
        glVertex3f(size/2,-size/2,size/2);
        glTexCoord2f(0,1);
        glVertex3f(-size/2,-size/2,size/2);
        glTexCoord2f(0,0);
        glVertex3f(-size/2,-size/2,-size/2);
        glTexCoord2f(1,0);
        glVertex3f(size/2,-size/2,-size/2);
    glEnd();
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
}

//Clean up handler for the skybox.
void Skybox::killSkybox()
{
    if(loadedSkybox[0] == true){
        glDeleteTextures(6,&skybox[0][0]);
        std::cout << "Skybox1 texture Deleted" << std::endl;
    }else if(loadedSkybox[1] == true){
        glDeleteTextures(6,&skybox[1][0]);
        std::cout << "Skybox2 texture Deleted" << std::endl;
    }else if(loadedSkybox[2] == true){
        glDeleteTextures(6,&skybox[2][0]);
        std::cout << "Skybox3 texture Deleted" << std::endl;
    }else if(loadedSkybox[3] == true){
        glDeleteTextures(6,&skybox[3][0]);
        std::cout << "Skybox4 texture Deleted" << std::endl;
    }else if(loadedSkybox[4] == true){
        glDeleteTextures(6,&skybox[4][0]);
        std::cout << "Skybox5 texture Deleted" << std::endl;
    }
    for(int i=0;i<=4;i++)
        loadedSkybox[i]=false;
}

//Draws the skyBox if there is a skybox loaded already or cleans up the current skybox and loads again.
void Skybox::draw()
{
    if(currentSkybox == 0){
        if(loadedSkybox[0] == true)
            drawSkybox(2000.0, skybox[0]);
        else{
            killSkybox();
            loadSkybox1();
        }
    }else if(currentSkybox == 1){
        if(loadedSkybox[1] == true)
            drawSkybox(2000.0, skybox[1]);
        else{
            killSkybox();
            loadSkybox2();
        }
    }else if(currentSkybox == 2){
        if(loadedSkybox[2] == true)
            drawSkybox(2000.0, skybox[2]);
        else{
            killSkybox();
            loadSkybox3();
        }
    }else if(currentSkybox == 3){
        if(loadedSkybox[3] == true)
            drawSkybox(2000.0, skybox[3]);
        else{
            killSkybox();
            loadSkybox4();
        }
    }else if(currentSkybox == 4){
        if(loadedSkybox[4] == true)
            drawSkybox(2000.0, skybox[4]);
        else{
            killSkybox();
            loadSkybox5();
        }
    }
}
