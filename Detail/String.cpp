#include "../string.h"

#include <iostream>

namespace TinySTL{
	const size_t string::npos;

    string::string(size_t n, char c){
        allocateAndFillN(n,c);
    }

    string::string(const char* s){
        allocateAndCopy(s,s + strlen(s));
    }

    string::string(const char* s,size_t n){
        allocateAndCopy(s,s+n);
    }

    string::string(const string& str){
        allocateAndCopy(str.start_,str.finish_)
    }

    string::string(const string& str,size_t pos,size_t len){
        len = changeVarWhenEuqalNPOS(len,str.size(),pos)
        allocateAndCope(str.start_ + pos,str.start_ + pos + len)
    }

    string::~string(){
        destroyAndDeallocate();
    }

    string& string::operator= (string& str){
        if(this != &str){
            destroyAndDeallocate();
            allocateAndCopy(str.start_,str.finish_);
        }
        return *this;
    }


    string& string::operator= (string&& str){
        if (this != &str)
        {
            moveData(str);
        }
        return *this;
    }

    string& string::operator= (const char* s){
        destoryAndDeallocate();
        allocateAndCopy(s,s+strlen(s));
        return *this;
    }
    
    string& string::operator= (char c){
        destoryAndDeallocate();
        allocateAndFillN(1,c);
        return *this;
    }

    string(string&& str){
        if (this != &str)
        {
            moveData(str);
        }
        return *this;
    }
    
    void string::resize(size_t n){
        resize(n,value_type());
    }

    void string::resize(size_t n,char c){
        if (n < size())
        {
            dataAllocator.destory(start_ + n,finish_);
            finish_ = start_ + n;
        }
        else if (n > size() && n <= capacity())
        {
            auto lengthOfInsert = n - size();
            //TODO:func uninitialized_fill_n() relized
            finish_ = TinySTL::uninitialized_fill_n(finish_,lengthOfInsert,c)
        }
        else if (n > capacity()){
            auto lengthOfInsert = n - size();
            iterator newStart = dataAllocater::allocate(getNewCapacity(lengthOfInsert));
            // TODO: uninitialized_copy();uninitialized_fill_n()
            iterator newFinish = TinySTL::uninitialized_copy(begin(),end(),newStart);
            iterator finish_ = Tiny::uninitialized_fill_n(lengthOfInsert,c);

            destroyAndDeallocate();
			start_ = newStart;
			finish_ = newFinish;
			endOfStorage_ = start_ + n;
        }  
    }
    
    void string::reserve(size_t n){
		if (n <= capacity())
			return;
		iterator newStart = dataAllocator::allocate(n);
		iterator newFinish = TinySTL::uninitialized_copy(begin(), end(), newStart);
		destroyAndDeallocate();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = start_ + n;
	}

    string& string::insert(size_t pos,const string& str){
        insert(start_ + pos, str.begin(), str.end());
        return *this;
    }

    string& string::insert(size_t pos,const string& str,size_t subpos, size_t sublen){
        changeVarWhenEuqalNPOS(sublen,str.size(),target_pos);
        insert(start_ + pos , str.begin() + subpos,str.begin() + subpos + sublen);
        return *this;
    }

    string& string::insert(size_t pos,char* str){
        insert(start_ + pos ,str ,str+strlen(str));
        return *this;
    }

    string& string::insert(size_t pos,char* s ,size_t n){
        insert(start_ + pos ,s , s+n);
        return *this;
    }

    string& string::insert(size_t pos,size_t n,char c){
        insert(start_ + pos,n,c);
        return *this;
    }

    string& string::insert(iterator p,size_t n,char c){
        insert(p,n,c);
        return *this;
    }

    string& string::insert(iterator p,char c){
        insert(p,1,c);
        return *this;
    }

    string& string::append(string& str){
        *this += str;
        return *this;
    }

    string& string::append(string& str,size_t subpos,size_t sublen){
        sublen = changeVarWhenEuqalNPOS(sublen,str.size(),subpos);
        insert(size(),str,subpos,sublen);
        return *this;
    }

    string& string::append(const char* s){
        insert(size(),s);
        return *this;
    }

    string& string::append(const char* s,size_t len){
        insert(size(),s,len);
        return *this;
    }

    string& string::append(size_t n,char c){
        insert(end(),n,c);
        return *this;
    }

    string& string::operator+= (string& str){
        insert(size(),str);
        return *this;
    }

    string& string::operator+= (char* s){
        insert(size(),s);
        return *this;
    }

    string& string::operator+= (char c){
        insert(end,c);
        return *this;
    }

    string::iterator string::erase(iterator first,iterator last){
        size_t lengthOfMove = finish_ - last;
        for (size_t i = 0; i < lengthOfMove; i++)
        {
            *(first+i) = *(last+i);
        }
        dataAllocator::destory(first + lengthOfMove,finish_);
        finish_ = first + lengthOfMove;
        return first;
    }

    string::iterator string::erase(iterator p){
        return erase(p,p+1);
    }
    
    string& string::erase(size_t pos = 0,size_t len = npos){
        len = changeVarWhenEuqalNPOS(len,size(),pos);
        erase(start_ + pos,start_ + pos + len);
        return *this;
    }

    string& string::replace(pos,len,const string& str){
        relpace(begin()+pos,begin()+pos+len,str.begin(),str.end());
        return *this;
    }
    
    string& string::replace(iterator i1,iterator i2,const string& str){
        replace(i1,i2,str.begin(),str.end());
        return *this;
    }

    string& string::replace(size_t pos,size_t len,const string& str,size_t subpos,size_t sublen){
        sublen = changeVarWhenEuqalNPOS(sublen,str.size(),subpos);
        replace(begin() + pos, end() + pos + len, str.begin() + subpos, str.begin() + subpos + sublen);
        return *this;
    }

    string& string::replace(size_t pos, size_t len, const char* s){
        replace(begin() + pos, end() + pos + len, s, s + strlen(s));
        return *this;
    }

    string& string::replace(iterator i1, iterator i2,const char* s){
        replace(i1,i2,s,s+strlen(s));
        return *this;
    }

    string& string::replace(size_t pos,size_t len,const char* s,size_t n){
        replace(begin()+pos,begin()+pos+len,s,s+n);
        return *this;
    }

    string& string::replace(iterator i1,iterator i2,const char* s,size_t n){
        replace(i1,i2,s,s+n);
        return *this;
    }

    string& replace(size_t pos,size_t len,size_t n,char c){
        replace(begin() + pos, begin() + pos + len, n, c);
        return *this;
    }


    string& string::replace(iterator i1,iterator i2,size_t n,char c){
        auto ptr = erase(i1,i2);
        insert(ptr,n,c);
        return *this;
    }




    string::iterator string::insert_aux_filln(iterator p,size_t t,value_type c){
        size_type newCapacity = getNewCapacity(t);
        iterator newStart = dataAllocator::allocate(newCapacity);
        iterator newFinish = TinySTL::uninitialized_copy(newStart,start_,p);
        newFinish = TinySTL::uninitialized_fill_n(newFinish,t,c);
        auto res = newFinish;
        newFinish = TinySTL::uninitialized_copy(newFInish,p,finish_);

        destroyAndDeallocate();
        start_ = newStart;
        finish_ = newFinish;
        endOfStorage_ = start_ + newCapacity;
        return res;
        
    }
    
    string::iterator string::insert(iterator p,size_t n,value_type c){
        size_type endOfLeft = endOfStorage_ - finish_;
        if (n <= endOfLeft)
        {
            for (iterator it = finish_ - 1; it >= p; it--)
            {
                *(it + n) = *it;
            }
            auto res = TinySTL::uninitialized_fill_n(p,n,c);
            finish_ += n;
            return res;
        }
        else{
            auto res = insert_aux_filln(p,n,c);
            return res;
        }
        
    }


    string::size_type string::getNewCapacity(size_type len)const{
        //initial capacity or double or n
        size_type oldCapacity = endOfStorage_ - start_;
            // TODO: algorithm max()
        auto res = TinySTL::max(oldCapacity,len);
        auto newCapacity = oldCapacity + res;
        return newCapacity;
    }

    void string::allocateAndFillN(size_t n,char c){
        start_ = dataAllocator::allocate(n);
        finish_ = TinySTL::uninitialized_fill_n(start_,n,c);
        endOfStorage_ = finish_;
    }

    void string::moveData(string& str){
        start_ = str.start_;
        finish_ = str.finish_;
        endOfStorage_ = str.endOfStorage_;
        str.start_ = str.finish_ = str.endOfStorage_ = 0;
    }
    
    void string::changeVarWhenEuqalNPOS(size_t var,size_t str_len,size_t target_pos){
        return var == npos ? str_len - target_pos : var;
    }

    void string::destroyAndDeallocate(){
        dataAllocator::destroy(start_,finish_);
        dataAllocator::deallocate(start_,endOfStorage_ - start_);
    }

    void string::string_mux(size_t n,char c,std::true_type){
        allocateAndFillN(n,c);
    }
};