#ifndef DEBUG_HPP
#define DEBUG_HPP

#ifdef _DEBUG

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError(); x; ASSERT(GLCheckError(#x, __FILE__, __LINE__))

#else

#define ASSERT(x) x
#define GLCall(x) x

#endif

namespace Debug 
{
    void GLClearError();
    bool GLCheckError(const char* func, const char* file, int line);
};

#endif//DEBUG_HPP
