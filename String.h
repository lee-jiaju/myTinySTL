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
        void reserve(size_t n);
        void shrink_to_fit(){
            dataAllocator::deallocate(finish_,endOfStorage_ - finish_);
            endOfStorage_ = finish_;
        }

        char& operator[] (size_t pos) {return *(start_ + pos)};
        const char& operator[] (size_t pos)const {return *(start_ + pos)};
        char& back(){return *(finish_ - 1)};
        const char& back()const {return *(finish_ - 1)};
        char& front(){return *(start_)};
        const char& front()const {return *(start_)}; 

        void push_back(char c) {insert(end(),c)};
        string& insert(size_t pos,const string& str);
        string& insert(size_t pos,const string& str,size_t subpos, size_t sublen);
        string& insert(size_t pos,char* str);
        string& insert(size_t pos,size_t n,char c);
        string& insert(iterator p,size_t n,char c);
        string& insert(iterator p,char c);
        template <class InputIterator>
        iterator insert(iterator p, InputIterator first, InputIterator last);
        string& append(string& str);
        string& append(string& str,size_t subpos,size_t sublen);
        string& append(const char* s);
        string& append(const char* s,size_t len);
        string& append(size_t n,char c);
        template <class InputIterator>
	    string& append(InputIterator first, InputIterator last);
        string& operator+= (string& str);
        string& operator+= (char* s);
        string& operator+= (char c);

        void pop_back(){ erase(end()-1,end())};
        iterator erase(iterator first,iterator last);
        iterator erase(iterator p);
        string& erase(size_t pos = 0,size_t len = npos);


        string& replace(pos,len,const string& str);
        string& replace(iterator i1,iterator i2,const string& str);
        template<InputIterator>
        string& replace(iterator i1,iterator i2,InputIterator first,InputIterator last);
        string& replace(size_t pos,size_t len,const string& str,size_t subpos,size_t sublen);
        string& replace(size_t pos,size_t len,const char* s);
        string& replace(iterator i1, iterator i2,const char* s);
        string& replace(size_t pos,size_t len,const char* s,size_t n);
        string& replace(iterator i1,iterator i2,const char* s,size_t n);
        string& replace(size_t pos,size_t len,size_t n,char c);
        string& replace(iterator i1,iterator i2,size_t n,char c);

        void swap(str){
            TinySTL::swap(start_,str.start_);
            TinySTL::swap(finish_,str.finish_);
            TinySTL::swap(endOfStorage_,str.endOfStorage_);
        }

        void copy(const char* s,size_t len,size_t pos = 0){
            auto ptr = TinySTL::uninitialized_copy(begin() + pos, begin() + pos + len, s);
            return size_t(ptr - s);
        }

        size_t find(string& str, size_t pos = 0) const;
        size_t find(const char *s, size_t pos = 0) const;
        size_t find(const char *s, size_t pos = 0, size_t n) const;
        size_t find(char c, size_t pos = 0) const;
        size_t rfind(char c, size_t pos = npos) const;
        size_t rfind(const string& str, size_t pos = npos) const;
        size_t rfind(const char *s, size_t pos, size_t n) const;
        size_t rfind(const char *s, size_t pos = npos) const;
        size_t find_first_of(const char *s, size_t pos, size_t n) const;
        size_t find_first_of(const char *s, size_t pos = 0) const;
        size_t find_first_of(const string& str, size_t pos = 0) const;
        size_t find_first_of(char c, size_t pos = 0) const;
        size_t find_first_not_of(const char *s, size_t pos, size_t n) const;
        size_t find_first_not_of(const char *s, size_t pos = 0) const;
        size_t find_first_not_of(const string &str, size_t pos = 0) const;
        size_t find_first_not_of(char c, size_t pos = 0) const;
        size_t find_last_of(const char *s, size_t pos, size_t n) const;
        size_t find_last_of(const char *s, size_t pos = 0) const;
        size_t find_last_of(const string &str, size_t pos = 0) const;
        size_t find_last_of(char c, size_t pos = 0) const;
        size_t find_last_not_of(const char *s, size_t pos, size_t n) const;
        size_t find_last_not_of(const char *s, size_t pos = 0) const;
        size_t find_last_not_of(const string &str, size_t pos = 0) const;
        size_t find_last_not_of(char c, size_t pos = 0) const;

        string substr(size_t pos = 0, size_t len = npos) const {
            len = changeVarWhenEuqalNPOS(len, size(), pos);
            return string(start_ + pos, start_ + pos + len);
        };

        int compare(const string &str) const;
        int compare(size_t pos, size_t len, const string &str) const;
        int compare(size_t pos, size_t len, const string &str,
                    size_t subpos, size_t sublen = npos) const;
        int compare(const char *s) const;
        int compare(size_t pos, size_t len, const char *s) const;
        int compare(size_t pos, size_t len, const char *s, size_t n) const;
    
    private:
        void moveData(string &str);
        // 插入时空间不足的情况
        template <class InputIterator>
        iterator insert_aux_copy(iterator p, InputIterator first, InputIterator last);
        // 插入时空间不足的情况
        iterator insert_aux_filln(iterator p, size_t n, value_type c);
        size_type getNewCapacity(size_type len) const;
        void allocateAndFillN(size_t n, char c);
        template <class InputIterator>
        void allocateAndCopy(InputIterator first, InputIterator last);
        void string_aux(size_t n, char c, std::true_type);
        template <class InputIterator>
        void string_aux(InputIterator first, InputIterator last, std::false_type);
        void destroyAndDeallocate();
        size_t rfind_aux(const_iterator cit, size_t pos, size_t lengthOfS, int cond) const;
        size_t find_aux(const_iterator cit, size_t pos, size_t lengthOfS, size_t cond) const;
        int compare_aux(size_t pos, size_t len, const_iterator cit, size_t subpos, size_t sublen) const;
        bool isContained(char ch, const_iterator first, const_iterator last) const;
        size_t changeVarWhenEuqalNPOS(size_t var, size_t minuend, size_t minue) const;

    public:
        // 运算符重载
        friend std::ostream& operator<< (std::ostream& os,const string& str);
        friend std::ostream& operator>> (std::ostream& is,const string& str);
        friend string operator+ (string& lstr,string& rstr);
        friend string operator+ (const string& lhs, const char* rhs);
		friend string operator+ (const char* lhs, const string& rhs);
		friend string operator+ (const string& lhs, char rhs);
		friend string operator+ (char lhs, const string& rhs);
        friend bool operator== (const string& lhs,const string& rhs);
        friend bool operator== (const string& lhs,const char* rhs);
        friend bool operator== (const char* lhs,const string& rhs);
        friend bool operator!= (const string& lhs, const string& rhs);
		friend bool operator!= (const char*   lhs, const string& rhs);
		friend bool operator!= (const string& lhs, const char*   rhs);
        friend bool operator>= (const string& lhs, const string& rhs);
		friend bool operator>= (const char*   lhs, const string& rhs);
		friend bool operator>= (const string& lhs, const char*   rhs);
        friend bool operator<= (const string& lhs, const string& rhs);
		friend bool operator<= (const char*   lhs, const string& rhs);
		friend bool operator<= (const string& lhs, const char*   rhs);
        friend bool operator> (const string& lhs, const string& rhs);
        friend bool operator> (const char* lhs, const string& rhs);
        friend bool operator> (const string& lhs, const char* rhs);
        friend bool operator< (const string& lhs, const string& rhs);
        friend bool operator< (const char* lhs, const string& rhs);
        friend bool operator< (const string& lhs, const char* rhs);
        friend void swap(string& x, string& y);
        friend std::istream& getline(std::istream& is, string& str, char delim);
		friend std::istream& getline(std::istream& is, string& str);


    
    };
    
    
    
    template<class Iterator1,class Iterator2>
    bool isLessEqual(Iterator1 first1,Iterator1 last1,Iterator2 first2,Iterator2 first2){
        for (; first1 != last1 && first2 != last2; first1++,first2++){
            if (*first1 < *first2){
                return true;    
            }
            else if (*first1 > *first2){
                return false;
            }
        }
        if ((first1 == last1 && first2 == last2) || first1 == last1){
            return true;
        }
        else{
            return false;
        }
    }

    template<class Iterator1,class Iterator2>
    bool isGreaterEqual(Iterator1 first1,Iterator1 last1,Iterator2 first2,Iterator2 last2){
        for (; first1 != last1 && first2 != last2; first1++,first2++){
            if (*first1 > *first2){
                return true;    
            }
            else if (*first1 < *first2){
                return false;
            }
        }
        if ((first1 == last1 && first2 == last2) || first2 == last2){
            return true;
        }
        else{
            return false;
        }
    }
    
    template <InputIterator>
    string& string::replace(iterator i1, iterator i2, InputIterator first, InputIterator last)
    {
        iterator ptr = erase(i1, i2);
        insert(ptr, first, last);
        return *this;
    }


 
    template <class InputIterator>
	string::string(InputIterator first, InputIterator last){
        return string_aux(first,last,typename std::is_integral<InputIterator>::type());
    }

    template <class InputIterator>
    string::iterator string::insert_aux_copy(iterator p, InputIterator first, InputIterator last){
        size_t lengthOfInsert = last - first;
        auto newCapacity = getNewCapacity(lengthOfInsert);
        iterator newStart = dataAllocator(newCapacity);
        iterator newFinish = TinySTL::uninitialized_copy(start_,p,newStart);
        iterator newFinish = TinySTL::uninitialized_copy(first,last,newfinish);
        auto res = newFinish;
        iterator newFinish = TinySTL::uninitialized_copy(p,finish_,newFinish);

        destroyAndDeallocate();
        start_ = newStart;
        finish_ = newFinish;

        return res;
    }

    template <class InputIterator>
    string::iterator string::insert(iterator p, InputIterator first, InputIterator last){
        auto lengthOfLeft = capacity() - size();
		size_t lengthOfInsert = distance(first, last);
        if(lengthOfInsert <= lengthOfLeft){
            for (iterator it = finish_ - 1; it >= p; it--)
            {
                *(it + lengthOfInsert) = *(it)
            }
            TinySTL::uninitialized_copy(first,last,p);
            finish_ += lengOfInsert;
            return p+ lengthOfInsert;
        }
        else{
            return insert_aux_copy(p,first,last);
        }
    }

    template <class InputIterator>
	string& string::append(InputIterator first, InputIterator last){
        insert(end(),first,last);
        return *this;
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
    string::string_aux(InputIterator first,InputIterator last,std.false_type){
        allocateAndCopy(first,last);
    }

}



#endif