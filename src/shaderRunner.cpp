#include "shaderProgram.h" 
#include <GL/glew.h>
#include <iostream>

ShaderRunner::ShaderRunner(const Shader& vertexShader, const Shader& fragmentShader){
  program_id = glCreateProgram();
  glAttachShader(program_id, vertexShader.get_shader_id()); 
  glAttachShader(program_id, fragmentShader.get_shader_id()); 
  glLinkProgram(program_id); 

  int success;
  char log[512]; 
  glGetProgramiv(program_id, GL_LINK_STATUS, &success); 
  if(!success){
    glGetProgramInfoLog(program_id, 512, nullptr, log); 
    std::cerr << "Shader Program linking failed: "<< log << std::endl; 
  }

}

void ShaderRunner::use() const {
  glUseProgram(program_id); 
}

uint32_t ShaderRunner::get_program_id() const {
  return program_id; 
}

ShaderRunner::~ShaderRunner(){
  glDeleteProgram(program_id); 
}
