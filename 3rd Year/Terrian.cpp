#include "Terrian.h"
unsigned int ground;
float height;
float size;

Terrian::Terrian()
{

}
//Makes a 2d vector array for storing the heightmap Y and each pixel.
std::vector<std::vector<float> > hHeightField;


void Terrian::loadHeightMap(const char* name)
{
    SDL_Surface* img=SDL_LoadBMP(name);
    if(!img)
    {
        std::cout << "image is not loaded" << std::endl;
        return;
    }
    std::vector<float> tmp;
    for(int i=0; i<img->h;i++)
    {
        tmp.clear();
        for(int j=0; j<img->w; j++)
        {
            Uint32 pixel = ((Uint32*)img->pixels)[i*img->pitch/4 + j];
            Uint8 r,g,b; //unsigned char
            SDL_GetRGB(pixel,img->format,&r,&g,&b);
            tmp.push_back((float)r/255.0);
        }
        hHeightField.push_back(tmp);
    }
}
//loads the ground texture.
void Terrian::loadGround()
{
     ground = objloader::loadTexture("Texture/desert2.bmp");
}

//Draws out the height map with textures.
void Terrian::renderHeightMap()
{
    //Sets the tile height and size of the terrain
    height=400;
    size=10;
    //Sets the limits of the heightmap
    int hmWidth = hHeightField.size();
    int hmHeight = hHeightField[0].size();
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    //Binds texture to all of the heightmap (Stretched among the whole terrain).
    glBindTexture(GL_TEXTURE_2D, ground);
	for (int hMapX = 0; hMapX < hmWidth-1; hMapX++){

		for (int hMapZ = 0; hMapZ < hmHeight-1; hMapZ++){
			glBegin(GL_TRIANGLE_STRIP);

                glColor3f(hHeightField[hMapX][hMapZ],hHeightField[hMapX][hMapZ],hHeightField[hMapX][hMapZ]);
                //glTexCoord2f(0,0);
				glTexCoord2f((float)hMapX / hmWidth, (float)hMapZ / hmHeight);
				glVertex3f(hMapX*size, hHeightField[hMapX][hMapZ]*height, hMapZ*size);

                //glTexCoord2f(0,1);
				glTexCoord2f((float)hMapX / hmWidth, (float)(hMapZ + 1) / hmHeight);
				glVertex3f(hMapX*size, hHeightField[hMapX][hMapZ + 1]*height, (hMapZ+1)*size);

                //glTexCoord2f(1,0);
				glTexCoord2f((float)(hMapX + 1) / hmWidth, (float)hMapZ / hmHeight);
				glVertex3f((hMapX+1)*size, hHeightField[hMapX + 1][hMapZ]*height, hMapZ*size);

                //glTexCoord2f(1,1);
				glTexCoord2f((float)(hMapX + 1) / hmWidth, (float)(hMapZ + 1) / hmHeight);
				glVertex3f((hMapX+1)*size, hHeightField[hMapX + 1][hMapZ + 1]*height, (hMapZ+1)*size);

			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

//Build a display list for the heightmap with textures.
int Terrian::BuildList()
{
    loadHeightMap("height/Terrain1.bmp");
    unsigned int list1 = glGenLists(1);
    glNewList(list1, GL_COMPILE);
       renderHeightMap();
    glEndList();
    std::cout << "Heightmap List Built." << std::endl;
    return list1;
}

//Returns the Y position from getting the points x1 and z1;
float Terrian::heightY(float x1, float z1)
{
    return (hHeightField[x1][z1]*(height/2));
}
//Returns the Interpol of 2 points but t amount.
float Terrian::Lerp (float a, float b, float t)
{
    return a + t * (b - a);
}
//Returns the accurate position of a point of certain quad or triangle etc.
float Terrian::getHeight(float posX, float posZ)
{
    float gridSize = size;

    float xpos = posX/gridSize;
    float ypos = posZ/gridSize;

    double intpart;
    modf(xpos, &intpart);
    float modX = (posX - intpart * gridSize) / gridSize;
    modf(ypos, &intpart);
    float modY = (posZ - intpart * gridSize) / gridSize;

    float TopLin = Lerp(heightY((int)xpos, (int)ypos),
        heightY((int)xpos + 1, (int)ypos), modX);
    float BotLin = Lerp(heightY((int)xpos, (int)ypos+1),
        heightY((int)xpos + 1,(int) ypos+1), modX);
    return Lerp(TopLin, BotLin, modY);
}

