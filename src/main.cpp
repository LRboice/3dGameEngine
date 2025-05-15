#include <iostream>
#include <SDL3/SDL.h> 
#include <SDL3/SDL_main.h> 
#include <GL/glew.h> 
#include <GL/gl.h>
#include "shader.h" 
#include "shaderProgram.h"
int main (int argc, char* argv[])
{
  std::cout << "Hello World!" << std::endl; 
	if(SDL_Init(SDL_INIT_VIDEO) != true){
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL: %s\n" , SDL_GetError());  
		return -1; 
	}

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); 
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6); 
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); 
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); 
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); 


	SDL_Window* window = SDL_CreateWindow("Bagel3D", 1280, 720,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if(window==NULL)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError()); 
    return -1; 
	}
  SDL_GLContext mainContext = SDL_GL_CreateContext(window) ;
  SDL_GL_SetSwapInterval(1); 
  
  glewExperimental = GL_TRUE; 
  if(glewInit() != GLEW_OK)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "GLEW Not OK!: %s\n", SDL_GetError()); 
		return -1; 
	}
  
  glViewport(0,0,1280,720); 
  
  float vertices[]={
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f, 
    -0.5f,-0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
  };

  unsigned int indices[]={
    0, 1, 3,
    1, 2, 3
  }; 

  Shader vertexShader("../assets/shaders/passthrough.vs", shader_type::vertex); 
  Shader fragmentShader("../assets/shaders/passthrough.fs", shader_type::fragment); 
  if(!vertexShader.compile() || !fragmentShader.compile()){
      std::cerr << "Failed to compile shaders" << std::endl; 
      return -1; 
  }


  ShaderRunner shaderRunner(vertexShader, fragmentShader); 
  GLuint vbo, vao, ebo;

  glGenVertexArrays(1, &vao); 
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo); 
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);  
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); 
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

  glEnableVertexAttribArray(0); 
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0); 
  
  bool done = false; 
  
  while(!done)
  {//gameloop
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_EVENT_QUIT){
        done = true;  
      }
    }  
    glClearColor(0,0,0,1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    shaderRunner.use(); 
    glBindVertexArray(vao); 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
    glBindVertexArray(0); 
    SDL_GL_SwapWindow(window);
  }  
  glDeleteVertexArrays(1, &vao); 
  glDeleteBuffers(1, &vbo); 
  SDL_GL_DestroyContext(mainContext); 
  SDL_DestroyWindow(window); 
  SDL_Quit();  // clean up window etc here 
  return 0; 
}

