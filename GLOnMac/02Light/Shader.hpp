//
//  Shader.hpp
//  GLOnMac
//
//  Created by 王志远 on 2017/3/23.
//  Copyright © 2017年 王志远. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <fstream>
#include <iostream>
#include <sstream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
class Shader{
public:
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void Use();
    GLint Program;
};

#endif /* Shader_hpp */
