#pragma once
#include <string>
#include <SDL.h>

//Texture wrapper class
class Texture
{
public:
    //Initializes variables
    Texture();

    //Deallocates memory
    ~Texture();

    //Loads image at specified path
    bool loadFromFile(SDL_Renderer* r, std::string path);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(SDL_Renderer* r, int x, int y);
    //Renders texture at given point and streches into given width and height
    void render(SDL_Renderer* r, int x, int y, int width, int height);

    //Gets image dimensions
    inline int getWidth() const { return mWidth; }
    inline int getHeight() const { return mHeight; }

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};