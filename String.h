#ifndef _STRING_H
#define _STRING_H

#include "Allocator.h"
#include "ReverseIterator.h"
#include "UninitializedFunctions.h"
#include "Utility.h"

#include <cstring>
#include <type_traits>

namespace TinySTL{
    class string
    {
    public:
        typedef char                            value_type;
        typedef char*                           iterator;
        typedef const char* const_iterator;
        typedef reverse_iterator_t<char*>       reverse_iterator;
        typedef reverse_iterator_t<const char*> const_reverse_iterator;
        typedef char&                           reference;
        typedef const char&                     const_reference;
        typedef size_t                          size_type;
        typedef ptrdiff_t                       difference_type;
        static const size_t npos = -1;

    private:
        char* start_;
        char* finish_;
        char* endOfStorage_;

        typedef TinySTL::allocator<char> dataAllocator;

    public:
        string() :start_(0), finish_(0), endOfStorage_(0){}
        string(size_t n, char c);
        string(const char* s);
        string(const char* s,size_t n);
        string(string&& str);
        string(const string& str);
        string(const string& str,size_t pos,size_t len);
        template <class InputIterator>
		string(InputIterator first, InputIterator last);

        ~string()
        

        string& operator= (string& str);
        string& operator= (string&& str);
        string& operator= (const char* s);
        string& operator= (char c);

        iterator begin() {return start_};
        const_iterator begin()const {return start_};
        iterator end() {return finish_};
        const_iterator end()const {return finish_};
        reverse_iterator rbegin() {return reverse_iterator(finish_)};
        const_reverse_iterator rbegin()const {return const_reverse_iterator(finish_)};
        reverse_iterator rend() {return reverse_iterator(start_)};
        const_reverse_iterator rend()const {return const_reverse_iterator(start_)};
        const_iterator cbegin() const {return start_};
        const_iterator cend() const {return finish_};
        const_reverse_iterator crbegin() const {return const_reverse_iterator(finish_)};
        const_reverse_iterator crend() const {return const_reverse_iterator(start_)};
        size_t size()const {return finish_ - start_};
        size_t length()const {return size()};
        size_t capacity()const {return endOfStorage_ - start_};

        void clear(){
            //destroyAndDeallocate();
            dataAllocator::destroy(start_, finish_);
            finish_ = start_;
        }
        
        void empty()const {return finish_ == start_};
        void resize(size_t n);
        void resize(size_t n,char c);

        


        
    };


    template <class InputIterator>
	string(InputIterator first, InputIterator last){
        return string_mux(first,last,typename std::is_integral<InputIterator>::type());
    }

    template<class InputIterator>
    string::iterator string::insert(iterator p, InputIterator first, InputIterator last){
        auto lengthOfLeft = capacity() - size();
		size_t lengthOfInsert = distance(first, last);
        if(lengthOfInsert <= lengthOfLeft){
            for (iterator it = finish_ - 1; it >= p; it--)
            {
                *(it + lengthOfInsert)
            }
            
        }
    }

    template<class InputIterator>
    void string::allocateAndCopy(InputIterator first, InputIterator last){
        if (first == nullptr || last == nullptr || first > last) {
            throw std::invalid_argument("Invalid iterator range");
        }
        start_ = allocator::allocate(last - first);
        finish_ TinySTL::uninitialized_copy(first,last,start_);
        endOfStorage_ = finish_;
    }

    template <class InputIterator>
    string::string_mux(InputIterator first,InputIterator last,std.false_type){
        allocateAndCopy(first,last);
    }

}



#endif