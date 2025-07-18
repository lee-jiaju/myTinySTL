#ifndef _N_VECTOR_
#define _N_VECTOR_

#include <algorithm>
#include <type_traits>

#include "Allocator.h"
#include "Algorithm.h"
#include "Iterator.h"
#include "ReverseIterator.h"
#include "UninitializedFunctions.h"


namespace TinySTL {
    template <class T, class Alloc = TinySTL::allocator<T>>
    class vector {
    private:
        T* start_;
        T* finish_;
        T* endOfStorage_;
        typedef Alloc dataAllocator;
    public:
        typedef T value_type;
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef reverse_iterator_t<T*> reverse_iterator;
        typedef reverse_iterator_t<const T*> const_reverse_iterator;
        typedef iterator pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
    
    public:
        

        // Other member functions and data members...
    };
}
#include "Detail\Vector.impl.h"
#endif