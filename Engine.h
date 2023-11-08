//
// Created by Andrey on 07.11.2023.
//

#ifndef UNTITLED1_ENGINE_H
#define UNTITLED1_ENGINE_H
#include <iostream>
#include <ctime>
#include <ctime>

#include "SDL.h"
#include<array>



class Engine {
private:
    bool run = false;
    SDL_Window *gWindow = NULL;
    SDL_Renderer *gScreenSurface = NULL;
    SDL_Surface *gHelloWorld = NULL;
    SDL_Event e;
    SDL_Rect sdlRect;
    bool direction;
    int array[100];
    int current;
    int current2 =-1;
    int typesort=1;
public:
    void Run(int SCREEN_WIDTH, int SCREEN_HEIGHT);
private:
    bool Init(int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void Destroy();
    bool Load();
    void Update();
    void Render();
    void Render(SDL_Rect *rect, SDL_Color color1, SDL_Color color2);
    void Handle();
    void BubleSort();
    void ShakerSort();
    void ShakeArray();
};


#endif //UNTITLED1_ENGINE_H
