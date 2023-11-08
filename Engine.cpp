//
// Created by Andrey on 07.11.2023.
//


#include "Engine.h"

bool Engine::Init(int SCREEN_WIDTH, int SCREEN_HEIGHT) {
    bool success = true;
    if (SDL_SetHint("OpenGL", "OpenGL")) {

    }
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << std::endl;
        success = false;
    } else {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            gScreenSurface = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawColor(gScreenSurface, 0xFF, 0xFF, 0xFF, 0xFF);

        }
    }
    ShakeArray();

    return success;
}

void Engine::ShakerSort() {

    int left = 0;
    int right = std::size(array) - 1;
    while (left <= right) {
        for (int i = right; i > left; --i) {
            if (array[i - 1] > array[i]) {
                int tmp = 0;
                tmp = array[i];
                array[i] = array[i - 1];
                array[i - 1] = tmp;
                current = i;
                break;
            }
        }
        ++left;
        for (int i = left; i < right; ++i) {
            if (array[i] > array[i + 1]) {
                int tmp = 0;
                tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
                current2 = i;
                return;
            }
        }
        --right;
    }
    return;
}

void Engine::ShakeArray() {
    std::srand(std::time(nullptr));
    for (int i = 0; i < std::size(array); i++)
        array[i] = std::rand() % 60;
}

bool Engine::Load() {
    //Loading success flag
    bool success = true;

    //Load splash image
    gHelloWorld = SDL_LoadBMP("hello_world.bmp");
    if (gHelloWorld == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        success = false;
    }

    return success;
}

void Engine::Render() {
    SDL_SetRenderDrawColor(gScreenSurface, 0, 0, 0, 0);
    SDL_RenderClear(gScreenSurface);

    for (int i = 0; i < std::size(array); i++) {
        const SDL_Rect *rect = new SDL_Rect{i * 8, 0, 6, array[i] * 10};

        if (i == current) {
            SDL_SetRenderDrawColor(gScreenSurface, 255, 0, 0, 15);
        } else if (i == current2) {
            SDL_SetRenderDrawColor(gScreenSurface, 0, 255, 0, 15);
        } else {
            SDL_SetRenderDrawColor(gScreenSurface, 0, 0, 255, 15);
        }
        SDL_RenderFillRect(gScreenSurface, rect);

        delete rect;
    }
    SDL_RenderPresent(gScreenSurface);
}

void Engine::Render(SDL_Rect *rect, SDL_Color color1, SDL_Color color2) {
    SDL_SetRenderDrawColor(gScreenSurface, 0, 0, 0, 0);
    SDL_RenderClear(gScreenSurface);

    for (int i = 0; i < std::size(array); i++) {
        const SDL_Rect *rect = new SDL_Rect{i * 8, 0, 6, array[i] * 10};

        if (i == current) {
            SDL_SetRenderDrawColor(gScreenSurface, color1.r, color1.g, color1.b, color1.b);
        } else if (i == current2) {
            SDL_SetRenderDrawColor(gScreenSurface, color2.r, color2.g, color2.b, color2.b);
        } else {
            SDL_SetRenderDrawColor(gScreenSurface, 0, 0, 255, 15);
        }
        SDL_RenderFillRect(gScreenSurface, rect);

        delete rect;
    }
    SDL_RenderPresent(gScreenSurface);


}

void Engine::Destroy() {

    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = nullptr;
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    SDL_Quit();
}

void Engine::Handle() {
    while (SDL_PollEvent(&e)) {
        if (e.key.keysym.sym == SDLK_ESCAPE || (e.type == SDL_QUIT)) {
            std::cout << "Pressed" << std::endl;
            run = true;
        }
        if (e.key.keysym.sym == SDLK_1) {
            ShakeArray();
            current2 = -1;
            typesort = 1;
        }
        if (e.key.keysym.sym == SDLK_2) {
            ShakeArray();
            current2 = -1;
            typesort = 2;
        }
    }
}

void Engine::BubleSort() {
    for (int i = 1; i < std::size(array); ++i) {
        for (int r = 0; r < std::size(array) - i; r++) {
            if (array[r] < array[r + 1]) {
                current = r;
                int temp = array[r];
                array[r] = array[r + 1];
                array[r + 1] = temp;
                return;
            }
        }
    }
}

void Engine::Update() {
    switch (typesort) {
        case 1:
            BubleSort();
            break;
        case 2:
            ShakerSort();
            break;
    }
}

void Engine::Run(int SCREEN_WIDTH, int SCREEN_HEIGHT) {
    unsigned int a;
    unsigned int b = SDL_GetTicks();
    double delta;
    this->Init(SCREEN_WIDTH, SCREEN_HEIGHT);
    this->Load();
    SDL_Delay(1000);
    while (!this->run) {
        a = SDL_GetTicks();
        delta = a - b;
        if (delta > 1000 / 144.0) {
            std::cout << "fps: " << 1000 / delta << std::endl;
            b = a;
            this->Render();
            this->Handle();
            this->Update();
        }
    }
    this->Destroy();
}