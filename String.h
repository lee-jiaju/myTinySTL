#ifndef _STRING_H
#define _STRING_H

#include "Allocator.h"
#include "ReverseIterator.h"
#include "UninitializedFunctions.h"
#include "Utility.h"

#include <cstring>
#include <type_traits>

namespace TinySTL{
    class String
    {
    public:
        typedef char value_type;
        typedef char* iterator;
        typedef const
        String(/* args */);
        ~String();
    };

}



#endif