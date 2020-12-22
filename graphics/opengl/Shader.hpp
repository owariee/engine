

class Shader {

    public:
        Shader(const char* name);
        ~Shader(void);

        void use();

    private:
        int program;

        bool errorCheck(int* bin, int type);
        int* compile(const char* shader, int type);
        const char* load_file(const char* name, const char* extension);

};

