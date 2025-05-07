#include <iostream>
#include <SDL3/SDL.h> 
#include <SDL3/SDL_main.h> 

int main (int argc, char* argv[])
{
  std::cout << "Hello World!" << std::endl; 
	if(SDL_Init(SDL_INIT_VIDEO) != true){
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL: %s\n" , SDL_GetError());  
		return -1; 
	}
	SDL_Window* window = SDL_CreateWindow("3d-GameEngine", 1280, 720,SDL_WINDOW_OPENGL);
	if(window==NULL)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError()); 
    return -1; 
	}
  SDL_Surface* surface = SDL_GetWindowSurface(window); 
  if(surface == NULL)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create surface: %s\n", SDL_GetError()); 
		return -1; 
	}

	SDL_UpdateWindowSurface(window);
	SDL_Delay(5000); 
  bool done = false; 
  
  while(!done)
  {//gameloop
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_EVENT_QUIT){
        done = true;  
      }
    }  
    // insert game logic here 
  }  
  SDL_DestroyWindow(window); 
  SDL_Quit();  // clean up window etc here 
  return 0; 
}

