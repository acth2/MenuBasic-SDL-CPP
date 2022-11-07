#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

const int WIDTH = 1280, HEIGHT = 850;
SDL_Window* window = SDL_CreateWindow("Inconnu - V01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);


#undef main
int main(int argc, char* argv[])
{

    SDL_Surface* titleImage = NULL;
    SDL_Surface* exitImage = NULL;
    SDL_Surface* playImage = NULL;
    SDL_Surface* windowSurface = NULL;
    SDL_Surface* windowSurface2 = NULL;
    SDL_Rect playImage_pos;
    SDL_Rect exitImage_pos;

    bool isOnExit = false;
    bool isOnPlay = false;

    SDL_Init(SDL_INIT_EVERYTHING);


    windowSurface = SDL_GetWindowSurface(window);
    windowSurface2 = SDL_GetWindowSurface(window);

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

            if (SDL_MOUSEBUTTONDOWN == event.type)
            {
                if (SDL_BUTTON_LEFT == event.button.button)
                {
                    std::cout << "[DEBUG] Left mouse button is down" << std::endl;
                    if (isOnExit) {
                        break;
                    }

                    if (isOnPlay) {
                        std::cout << "" << std::endl;
                    }
                }
                else if (SDL_BUTTON_RIGHT == event.button.button)
                {
                    std::cout << "[DEBUG] Right mouse button is down" << std::endl;
                }
                else if (SDL_BUTTON_MIDDLE == event.button.button)
                {
                    std::cout << "[DEBUG] Middle mouse button is down" << std::endl;
                }
            }

            if (SDL_MOUSEBUTTONUP == event.type)
            {
                if (SDL_BUTTON_LEFT == event.button.button)
                {
                    std::cout << "[DEBUG] Left mouse button is up" << std::endl;
                }
                else if (SDL_BUTTON_RIGHT == event.button.button)
                {
                    std::cout << "[DEBUG] Right mouse button is up" << std::endl;
                }
                else if (SDL_BUTTON_MIDDLE == event.button.button)
                {
                    std::cout << "[DEBUG] Middle mouse button is up" << std::endl;
                }
            }

            if (SDL_MOUSEWHEEL == event.type)
            {
                if (event.wheel.y > 0)
                {
                    std::cout << "[DEBUG] Mouse wheel is scrolling up" << std::endl;
                }
                else if (event.wheel.y < 0)
                {
                    std::cout << "[DEBUG] Mouse wheel is scrolling down" << std::endl;
                }

                if (event.wheel.x > 0)
                {
                    std::cout << "[DEBUG] Mouse wheel is scrolling right" << std::endl;
                }
                else if (event.wheel.x < 0)
                {
                    std::cout << "[DEBUG] Mouse wheel is scrolling left" << std::endl;
                }
            }

            if (SDL_KEYDOWN == event.type)
            {

                if (SDLK_q == event.key.keysym.sym)
                {
                    std::cout << "[DEBUG] q is down - Move left" << std::endl;
                }
                else if (SDLK_s == event.key.keysym.sym)
                {
                    std::cout << "[DEBUG] S is down - Move down" << std::endl;
                }
                else if (SDLK_d == event.key.keysym.sym)
                {
                    std::cout << "[DEBUG] D is down - Move right" << std::endl;
                }
                else if (SDLK_z == event.key.keysym.sym)
                {
                    std::cout << "[DEBUG] Z is down - Move up" << std::endl;
                }
            }
            else if (SDL_KEYUP == event.type)
            {
                if (SDLK_a == event.key.keysym.sym)
                {
                    std::cout << "[DEBUG] A is up - Stop moving left" << std::endl;
                }
                else if (SDLK_s == event.key.keysym.sym)
                {
                    std::cout << "[DEBUG] S is up - Stop moving down" << std::endl;
                }
                else if (SDLK_d == event.key.keysym.sym)
                {
                    std::cout << "[DEBUG] D is up - Stop moving right" << std::endl;
                }
                else if (SDLK_w == event.key.keysym.sym)
                {
                    std::cout << "[DEBUG] W is up - Stop moving up" << std::endl;
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
