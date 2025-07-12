#ifndef _ALGORITHM_N_
#define _ALGORITHM_N_
namespace TinySTL
{
    
    template<ForwardIterator Iterator,class T>
    void fill(Iterator first,Iterator last,const T& value){
        for (; first != last; first++){
            *first = value;
        }  
    }
    inline void fill(char* first,char* last,const char value){
        memset(first,static_cast<unsigned char>(value),last-first);
    }

    inline void fill(wchar_t* first,wchar_t* last,const wchar_t value){
        memset(first,static_cast<unsigned char>(value),(last-first)*sizeof(wchar_t));
    }

    template<OutputIterator iterator,class Size,class T>
    iterator fill_n(iterator first,Size n,const T& value){
        for (; n > 0; n--,first++){
            *first = value;
        }
        return first;
    }

    template<class Size>
    char* fill(char* first,Size n,const char& value){
        memset(first, static_cast<unsigned char>(value), n);
		return first + n;
    }

    template<class Size>
    wchar_t* fill(wchar_t* first,Size n,const wchar_t& value){
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
    }

    template<class T>
    T min(const T& a,const T& b){
        return !(a < b) ? b : a;
    }

    template<class T,class Compare>
    const T& min(const T& a,const T& b,Compare comp){
        return comp(a,b) ? a : b;
    }

    template<class T>
    const T& max(const T& a,const T& b){
        return !(a < b) ? a : b;
    }

    template<class T,class Compare>
    const T& max(const T& a,const T& b,Compare comp){
        return comp(a,b) ? a : b;
    }
}
#endif