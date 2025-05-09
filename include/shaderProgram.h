#ifndef Bagel_ShaderRunner_H
#define Bagel_ShaderRunner_H

#include "shader.h"

class ShaderRunner{ 
  private:
    uint32_t program_id;

  public:
    ShaderRunner(const Shader& vertexShader, const Shader& fragmentShader); 
    void use() const; 
    uint32_t get_program_id() const; 
    ~ShaderRunner(); 
}; 

#endif
