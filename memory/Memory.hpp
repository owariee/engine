#ifndef MEMORY_HPP
#define MEMORY_HPP

namespace Memory
{
    //private:
        typedef struct 
        { 
            int size;
            bool isFree;
        } BlockZoneT;

        int allocatedSize = 0;
        BlockZoneT* firstBlock;

        void SanitizeCheck(void);

    //public:
        void ZoneInit(int bytes);
        void* ZoneAlloc(int bytes);
        void ZoneFree(void* pointer);
       
};

#endif//MEMORY_HPP
