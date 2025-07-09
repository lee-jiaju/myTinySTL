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