#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

const int WIDTH = 1280, HEIGHT = 850;
SDL_Window* window = SDL_CreateWindow("Inconnu - V01 - Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

SDL_Surface* titleImage = NULL;
SDL_Surface* exitImage = NULL;
SDL_Surface* playImage = NULL;
SDL_Surface* windowSurface = NULL;
SDL_Surface* windowSurface2 = NULL;
SDL_Rect playImage_pos;
SDL_Rect exitImage_pos;

bool isOnExit = false;
bool isOnPlay = false;
bool   onMenu = true;

#undef main
int main(int argc, char* argv[])
{
    windowSurface = SDL_GetWindowSurface(window);
    windowSurface2 = SDL_GetWindowSurface(window);

    SDL_Init(SDL_INIT_EVERYTHING);

    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cout << "Could not create window: " << IMG_GetError() << std::endl;
        return 1;
    }

    titleImage = IMG_Load("logo1.png");
    exitImage = IMG_Load("exit_no_pressed.png");
    playImage = IMG_Load("play_no_pressed.png");

    if (NULL == titleImage || NULL == exitImage || NULL == playImage)
    {
        std::cout << IMG_GetError();
        std::cout << "SDL could not load image! SDL Error: " << SDL_GetError() << std::endl;
    }

    SDL_Event event;

    playImage_pos.y = 320;
    exitImage_pos.y = 320;
    exitImage_pos.x = 755;
    playImage_pos.x = -755;

    while (true)
    {
        if (SDL_PollEvent(&event))
        {
            if (SDL_QUIT == event.type)
            {
                break;
            }

            if (SDL_MOUSEMOTION == event.type)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);

                std::cout << "[DEBUG] " << x << " : " << y << std::endl;
                
                if (onMenu)
                {
                    if (x >= 55 && x <= 610 && y >= 369 && y <= 516) {

                        playImage = IMG_Load("play_pressed.png");
                        isOnPlay = true;

                    }
                    else {
                        playImage = IMG_Load("play_no_pressed.png");
                        isOnPlay = false;
                    }

                    if (x >= 650 && x <= 1215 && y >= 369 && y <= 516) {

                        exitImage = IMG_Load("exit_pressed.png");
                        isOnExit = true;
                    }
                    else {
                        exitImage = IMG_Load("exit_no_pressed.png");
                        isOnExit = false;
                    }
                }
         
            }

            if (SDL_MOUSEBUTTONDOWN == event.type)
            {
                if (SDL_BUTTON_LEFT == event.button.button)
                {
                    if (isOnExit) {
                        break;
                    }else if (isOnPlay) {
                        SDL_DestroyWindow(window);
                        load();

                    }
                }
            }
        }

        SDL_BlitSurface(titleImage, NULL, windowSurface, NULL);
        SDL_BlitSurface(exitImage, NULL, windowSurface, &exitImage_pos);
        SDL_BlitSurface(playImage, NULL, windowSurface2, &playImage_pos);

        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
