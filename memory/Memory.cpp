#include "Memory.hpp"

#include "Debug.hpp"

#include <cstdlib>

void Memory::ZoneInit(int bytes)
{
    Memory::firstBlock = (BlockZoneT*)std::malloc(bytes); 
    Memory::firstBlock->size = bytes - sizeof(Memory::BlockZoneT);
    Memory::firstBlock->isFree = true;
    Memory::allocatedSize = bytes;
    return;
}

void* Memory::ZoneAlloc(int bytes)
{
    int memoryOffset = 0x0;

    while(true)
    {
        Memory::BlockZoneT* tmp = (BlockZoneT*) Memory::firstBlock + memoryOffset;

        if(tmp >= (Memory::firstBlock + Memory::allocatedSize))
        {
            break;
        }

        if(tmp->isFree)
        {
            if(tmp->size > (bytes + sizeof(Memory::BlockZoneT)))
            {
                Memory::BlockZoneT* tmp2 = (BlockZoneT*) tmp + sizeof(Memory::BlockZoneT) + bytes;
                tmp2->size = tmp->size - bytes - sizeof(Memory::BlockZoneT);
                tmp2->isFree = true;
                tmp->size = bytes;
                tmp->isFree = false;
                return (void*) tmp + sizeof(Memory::BlockZoneT);
            }
            else if(tmp->size >= bytes)
            {
                tmp->isFree = false;
                return (void*) tmp + sizeof(Memory::BlockZoneT);
            }
        }

        memoryOffset += tmp->size + sizeof(Memory::BlockZoneT);
    }
    
    Debug::print(Debug::Flags::Error,
                 Debug::Subsystem::Memory,
                 "Insufficient Memory Size");
    return 0x0;
}

void Memory::ZoneFree(void* pointer)
{
    Memory::BlockZoneT* tmp = (BlockZoneT*) pointer - sizeof(Memory::BlockZoneT);
    tmp->isFree = true;
    Memory::SanitizeCheck();
    return;
}

void Memory::SanitizeCheck(void)
{
    int memoryOffset = 0x0;
    int memoryOffsetBackward = 0x0;
    bool oldBlockIsFree = false;

    while(true)
    {
        Memory::BlockZoneT* tmp = (BlockZoneT*) Memory::firstBlock + memoryOffset;

        if(tmp->isFree) 
        {
            if(oldBlockIsFree)
            {
                Memory::BlockZoneT* tmp2 = (BlockZoneT*) Memory::firstBlock + memoryOffsetBackward;
                tmp2->size += tmp->size + sizeof(Memory::BlockZoneT);
                tmp = tmp2;
                memoryOffset = tmp - Memory::firstBlock;
            }
            else
            {
                oldBlockIsFree = true;
            }
        }
        else
        {
            oldBlockIsFree = false;
        }
        
        memoryOffsetBackward = memoryOffset;
        memoryOffset += tmp->size + sizeof(Memory::BlockZoneT);
    }
}
