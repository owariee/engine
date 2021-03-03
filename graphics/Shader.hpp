#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad/glad.h"

class Shader {

    public:
        Shader(const char* name);
        ~Shader(void);

        void use();

    private:
        GLuint program;

        bool errorCheck(GLuint bin, int type);
        GLuint compile(const char* shader, int type);
        const char* load_file(const char* name, const char* extension);

};

#endif//SHADER_HPP

