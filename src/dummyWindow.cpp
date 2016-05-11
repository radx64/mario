#include "dummyWindow.hpp"

#include <iostream>

DummyWindow::DummyWindow()
{ }

void DummyWindow::create()
{
    std::cout << "CREATING " << std::endl;

    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    	return;
    }
    window = SDL_CreateWindow( "Mario", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );

    if( window == NULL )
    {
   		std::cout << "Window could not be created! SDL_Error: " <<  SDL_GetError() << std::endl;
   		return;
    }

    screenSurface = SDL_GetWindowSurface( window );

    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
    
    SDL_UpdateWindowSurface(window);

    SDL_Delay(2000);

    SDL_DestroyWindow( window );

    SDL_Quit();  
}
