#ifndef Bagel_Shader_H
#define Bagel_Shader_H 

#include <string>

enum shader_type{
  vertex,
  fragment,
}; 

class Shader{
  private:
    std::string filename; 
    shader_type shader_type; 
    uint32_t shader_id; 
    
    static std::string read_file(const std::string& filename); 

  public:
    explicit Shader(const char* filename, enum shader_type shader_type); 
    bool compile(); 
    uint32_t get_shader_id() const; 
    ~Shader(); 
}; 

#endif
