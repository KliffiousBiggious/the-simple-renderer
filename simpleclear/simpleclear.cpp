/*
 * Copyright © 2012-2015 Graham Sellers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#include "sb7.h"
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
//Global compile shaders function
GLuint compile_shaders(void);
std::string readShaders(const char* filename);
class my_application :public sb7::application
{
public:
    void startup(void)
    {
        rendering_program = compile_shaders();
        glCreateVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);
      

    }

    void shutdown(void )
    {
        glDeleteVertexArrays(1, &vertex_array_object);
        glDeleteProgram(rendering_program);
        glDeleteVertexArrays(1, &vertex_array_object);
    }
    // Implements the render method
    void render(double currentTime)//Contains the number of seconds since the app begins execution
    { 
        
            //define color , first value as red,green,blue,alpha
            static const GLfloat color[] = { 0.0f,0.0f,0.0f,1.0f };
            //clears the buffer specified by the first parameter to the value specified in the third parameter, the second parameter is the index of draw buffer
            glClearBufferfv(GL_COLOR, 0, color);
            //Use the program object we created earlier for rendering
            glUseProgram(rendering_program);
            //
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            //
            glDrawArrays(GL_PATCHES, 0, 3);
            //Size
            int i;
            std::cin >> i;
        
     
    }

private:
    GLuint rendering_program, vertex_array_object;
   
};
DECLARE_MAIN(my_application);//instantiate and run the run method of the object of the class in quote

GLuint compile_shaders(void) {

    GLuint vertex_shader, fragment_shader,
    tessellation_control_shader,tessellation_evaluation_shader,
    program ;
    
    std::string vertex_shader_input, tessellation_control_shader_input, tessellation_evaluation_shader_input,fragment_shader_input;
    vertex_shader_input = readShaders("shaders/vertexShaderInput.glsl");
    tessellation_control_shader_input = readShaders("shaders/tessellationControlShaderInput.glsl");
    tessellation_evaluation_shader_input = readShaders("shaders/tessellationEvaluationShaderInput.glsl");
    fragment_shader_input = readShaders("shaders/fragmentShaderInput.glsl");

    static const GLchar* vertex_shader_source[] = { vertex_shader_input.c_str() };
    /*    
    static const GLchar* vertex_shader_source[] = {
    " #version 450 core                                                                       \n "
    " layout (location = 0) in vec4 offset;                                             \n "
    " layout (location = 0) in vec4 color;                                             \n "
     " out vec4 vs_color;                                             \n "
    "void main (void)                                                                           \n "
    "{const vec4 vertices [3] = vec4[3]  (vec4(0.25, -0.25, 0.5, 1.0), \n"
    "vec4(-0.25, -0.25, 0.5, 1.0),                                                         \n"
     "vec4(0.25, 0.25, 0.5, 1.0));                                                         \n "
    " gl_Position = vertices[gl_VertexID]+offset;                                  \n "
    "vs_color=color;                                                                            \n "
    " }                                                                                                 \n "
    "                                                                                                  \n "
    "                                                                                                  \n "

    };
    */
    static const GLchar* tessellation_control_shader_source[] = { tessellation_control_shader_input.c_str() };
    static const GLchar* tessellation_evaluation_shader_source[] = { tessellation_evaluation_shader_input.c_str() };
    static const GLchar* fragment_shader_source[] = { fragment_shader_input.c_str() };
   /* 
   static const GLchar* fragment_shader_source[] = {
        "#version 450 core                                                          \n"
        "in  vec4 vs_color;                                                            \n"  
        "out vec4 color;                                                               \n"
        "void main(void)                                                              \n"
        "{                                                                                     \n"
        " color= vs_color;                                                            \n"
        " }                                                                                    \n"
        "                                                                                       \n"
    };
    */
  
   vertex_shader= glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
   glCompileShader(vertex_shader);
  
   tessellation_control_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
   glShaderSource(tessellation_control_shader, 1, tessellation_control_shader_source, NULL);
   glCompileShader(tessellation_control_shader);

   tessellation_evaluation_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
   glShaderSource(tessellation_evaluation_shader, 1, tessellation_evaluation_shader_source, NULL);
   glCompileShader(tessellation_evaluation_shader);

   fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
   glCompileShader(fragment_shader);

   program = glCreateProgram();
   glAttachShader(program, vertex_shader);
   glAttachShader(program, tessellation_control_shader);
   glAttachShader(program, tessellation_evaluation_shader);
   glAttachShader(program, fragment_shader);
   glLinkProgram(program);
   glDeleteShader(vertex_shader);
   glDeleteShader(tessellation_control_shader);
   glDeleteShader(tessellation_evaluation_shader);
   glDeleteShader(fragment_shader);

   return program;
}
std::string readShaders(const char* filename) {
    std::ifstream file{ filename };
    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}


































//ORIGINAL CMAKE MADE PROJECT CODE
/* #include <sb7.h>
#include <math.h>
class simpleclear_app : public sb7::application
{
    void init()
    {
        static const char title[] = "Nigga";

        sb7::application::init();

        memcpy(info.title, title, sizeof(title));
    }

    virtual void render(double currentTime)
    {
        const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f,
        (float)cos(currentTime) * 0.5f + 0.5f,
        0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, color);
    }
};

DECLARE_MAIN(simpleclear_app)




GLuint compile_shaders(void)
{
    GLuint vertex_shader, fragment_shader, program;

    static GLchar* vertex_shader_source[] =
    {
        "#version 450 core                                         \n"
        "void main(void)                                              \n"
        "{                                                                    \n"
        "gl_Position= vec4(0.0,0.0,0.5,1.0);               \n"
        "}                                                                   \n"
    };

    static GLchar* fragment_shader_source[] =
    {
        "#version 450 core                                      \n"
        "out vec4 color;                                                \n"
        "void main(void)                                              \n"
        "{                                                                    \n"
        "color= vec4(1.0,0.0,0.5,1.0);               \n"
        "}                                                                   \n"
    };
//Create and compile vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    //Create and compile fragment shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, fragment_shader_source, 0);
    glCompileShader(fragment_shader);
    //Attach shader
    program=glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;
}






*/
