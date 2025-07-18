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

    size_t string::find_aux(const_iterator cit, size_t pos, size_t lengthOfS, size_t cond) const
    {
        size_t i, j;
        for (i = pos; i != cond; ++i)
        {
            for (j = 0; j != lengthOfS; ++j)
            {
                if (*(begin() + i + j) != cit[j])
                    break;
            }
            if (j == lengthOfS)
                return i;
        }
        return npos;
    }


    size_t string::find(string& str, size_t pos = 0) const
    {
        if (s == nullptr || *s == '\0')
            return pos < size() ? pos : npos;

        size_t lengthOfS = str.size();
        if (lengthOfS == 0)
            return pos < size() ? pos : npos;

        if (lengthOfS > size() - pos)
            return npos;

        return find_aux(str.cbegin(), pos, lengthOfS, size());
    }


    size_t string::find(const char *s, size_t pos = 0) const{
        return find(s, pos, strlen(s));
    }

    size_t string::find(const char *s, size_t pos = 0,size_t n) const
    {
        //lengthOfS is meaningless here
        size_t lengthOfS = strlen(s);
        if (s == nullptr || *s == '\0')
            return pos < size() ? pos : npos;

        if (n > size() - pos){
            return npos;
        }
        return find_aux(s, pos, n, size());
    }

    size_t string::find(const char c, size_t pos = 0) const {
        for (auto cit = cbegin() + pos; cit != cend(); cit++)
        {
            if (*cit == c)
            {
                return cit - cbegin();
            }
        }
        return npos;
    }

    size_t string::rfind(const char c, size_t pos = npos) const
    {
        for (auto cit = cbegin() + pos; cit != cbegin(); cit--)
        {
            if (*cit == c)
            {
                return cit - cbegin();
            }
        }
        return npos;
    }

    size_t string::rfind_aux(const_iterator cit, size_t pos, size_t lengthOfS, int cond) const
    {
        // 处理空子串的特殊情况（根据需求，可能返回npos或pos）
        if (lengthOfS == 0)
        {
            return npos;
        }
        const size_t str_len = size(); // 原字符串长度
        // 有效起始位置的最大值：原字符串长度 - 子串长度（不能为负）
        const size_t max_valid_pos = str_len >= lengthOfS ? str_len - lengthOfS : 0;
        // 实际查找的起始位置：取pos和max_valid_pos中的较小值（不能超过原字符串范围）
        const size_t start_pos = pos > max_valid_pos ? max_valid_pos : pos;
        // 从start_pos向前递减查找，直到达到cond或0（根据cond的语义调整）
        // 假设cond是允许的最小起始位置（如0），则循环条件为i >= cond
        for (size_t i = start_pos; i >= static_cast<size_t>(cond); --i)
        {
            bool match = true;
            // 检查子串的每个字符是否匹配
            for (size_t j = 0; j < lengthOfS; ++j)
            {
                // 关键：确保i+j不越界（理论上已通过start_pos保证，双重检查更安全）
                if (i + j >= str_len || *(begin() + i + j) != cit[j])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                return i; // 找到匹配，返回起始位置
            }
        }
        return npos; // 未找到
    }

    size_t string::rfind(const string &str, size_t pos = npos) const{
        lengthOfS = str.size();
        pos = changeVarWhenEuqalNPOS(pos,size(),1);
        return rfind_aux(str.cbegin(), pos, lengthOfS, 0);
    }

    size_t string::rfind(const char* s, size_t pos = npos) const{
        size_t lengthOfS = strlen(s);
        pos = changeVarWhenEuqalNPOS(pos,size(),1);
        return rfind(s, pos, lengthOfS);
    }

    size_t string::rfind(const char* s, size_t pos, size_t n) const{
        if (s == nullptr || *s == '\0')
            return pos < size() ? pos : npos;

        if (n > size() - pos)
            return npos;

        return rfind_aux(s, pos, n, 0);
    }

    size_t string::find_first_of(const char* s, size_t pos, size_t n) const{
        if (s == nullptr || *s == '\0')
            return pos < size() ? pos : npos;

        for (auto cit = cbegin() + pos; cit != cend(); cit++){
            if (isContained(*cit, s, s + n)){
                return cit - cbegin();
            }
        }
        return npos;
    }
    size_t string::find_first_of(const char *s, size_t pos) const
    {
        return find_first_of(s, pos, strlen(s));
    }

    size_t string::find_first_of(const string &str, size_t pos) const
    {
        if (str.empty())
            return pos < size() ? pos : npos;

        find_first_of(str.cbegin(), pos, str.size());
    }

    size_t string::find_first_of(char c, size_t pos) const
    {
        return find(c,pos);
    }

    size_t string::find_first_not_of(const char *s, size_t pos, size_t n) const
    {
        if (s == nullptr || *s == '\0'){
            return pos < size() ? pos : npos;
        }
        
        for (size_t i = 0; i < n; i++){
            if(!isContained(s[i], s, s+n)){
                return i;
            }
        }
        return npos;
    }

    size_t string::find_first_not_of(const char *s, size_t pos) const{
        return find_first_not_of(s, pos, strlen(s));
    }

    size_t string::find_first_not_of(const string &str, size_t pos) const{
        return find_first_not_of(str.cbegin(), pos, str.size());
    }

    size_t string::find_first_not_of(char c, size_t pos) const{
        for (auto cit = cbegin() + pos; cit != cend(); cit++){
            if (*cit != c){
                return cit - cbegin();
            }
        }
        return npos;
    }

    size_t string::find_last_of(const char *s, size_t pos, size_t n) const{
        if (s == nullptr || *s == '\0'){
            return pos < size() ? pos : npos;
        }
        for(size_t i = pos; i >= 0; i--){
            if (isContained(s[i], s, s + n)){
                return i;
            }
        }
        return npos;
    }

    size_t string::find_last_of(const char *s, size_t pos) const{
        return find_last_of(s, pos, strlen(s));
    }

    size_t string::find_last_of(const string &str, size_t pos) const{
        if (str.empty())
            return pos < size() ? pos : npos;

        return find_last_of(str.cbegin(), pos, str.size());
    }

    size_t string::find_last_of(char c, size_t pos) const{
        for (auto cit = cbegin() + pos; cit != cbegin(); cit--){
            if (*cit == c){
                return cit - cbegin();
            }
        }
        return npos;
    }

    size_t string::find_last_not_of(const char *s, size_t pos, size_t n) const{
        if (s == nullptr || *s == '\0'){
            return pos < size() ? pos : npos;
        }
        for (size_t i = pos; i >= 0; i--){
            if (!isContained(s[i], s, s + n)){
                return i;
            }
        }
        return npos;
    }

    size_t string::find_last_not_of(const char *s, size_t pos = 0) const{
        return find_last_not_of(s, pos, strlen(s));
    }
    size_t string::find_last_not_of(const string &str, size_t pos = 0) const{
        return find_last_not_of(str.cbegin(), pos, str.size());
    }
    size_t string::find_last_not_of(char c, size_t pos = 0) const{
        for (auto cit = cbegin() + pos; cit != cbegin(); cit--){
            if (*cit != c){
                return cit - cbegin();
            }
        }
        return npos;
    }

    int string::compare_aux(size_t pos, size_t len, const_iterator s,size_t subpos,size_t sublen) const{
        size_t i,j;
        for (j = 0, i = 0; i < len && j < sublen; i++, j++){
            if (s[subpos + j] > *this[pos + i]){
                return 1; // this > s
            }
            else if (s[subpos + j] < *this[pos + i]){
                return -1; // this < s
            }
        }
        if (i == len && j == sublen){
            return 0; // this == s
        }
        else if (i == len){
            return -1; // this < s
        }
        else{
            return 1; // this > s
        } 
    }

    int string::compare(const string &str) const{
        return compare_aux(0, size(), str.cbegin(), 0, str.size());
    }

    int string::compare(size_t pos, size_t len, const string &str) const{
        return compare_aux(pos, len, str.cbegin(), 0, str.size());
    }

    int string::compare(size_t pos, size_t len, const string &str,size_t subpos, size_t sublen) const{
        //sublen = changeVarWhenEuqalNPOS(sublen, str.size(), subpos);
        return compare_aux(pos, len, str.cbegin(), subpos, sublen);
    }

    int string::compare(const char *s) const{
        return compare(0, size(), s, strlen(s));
    }

    int string::compare(size_t pos, size_t len, const char *s) const{
        return compare(pos, len, s, strlen(s));
    }

    int string::compare(size_t pos, size_t len, const char *s, size_t n) const{
        //n = changeVarWhenEuqalNPOS(n, strlen(s), 0);
        return compare_aux(pos, len, s, 0, n);
    }


    string::iterator string::insert_aux_filln(iterator p, size_t t, value_type c)
    {
        size_type newCapacity = getNewCapacity(t);
        iterator newStart = dataAllocator::allocate(newCapacity);
        iterator newFinish = TinySTL::uninitialized_copy(newStart, start_, p);
        newFinish = TinySTL::uninitialized_fill_n(newFinish, t, c);
        auto res = newFinish;
        newFinish = TinySTL::uninitialized_copy(newFInish, p, finish_);

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

    std::ostream& operator<< (std::ostream& os,const string& str){
        for (const auto ch : str){
            os << ch;
        }
        return os;
    }

    std::ostream& operator>> (std::ostream& is,const string& str){
        char ch;
        size_type oldSize = str.size();
        bool hasBlankPre = true;

        while(is.get(ch)){
            if (isblank(ch) || ch = "\n"){
                hasBlankPre = false;
            }
            else
                break;
        }
        is.putback(ch);
        str.clear();
        while (is.get(ch))
        {
            if (ch != EOF && !isblank(ch) && ch != "\n"){
                str.push_back(ch);
            }
            else
                break;
        }
        return is
    }

    string operator+ (string& lstr,string& rstr){
        string res(lstr);
        return lstr += rstr;
    }
    string operator+ (const string& lhs, const char* rhs){
        string res(lhs);
        return res+=rhs;
    }
	string operator+ (const char* lhs, const string& rhs){
        string res(lhs);
        return res+=rhs;
    }
    string operator+ (const string& lhs, char rhs){
        string res(lhs);
        return res+=rhs;
    }
	string operator+ (char lhs, const string& rhs){
        string res(lhs);
        return res+=rhs;
    }
    bool operator== (const string& lhs,const string& rhs){
        if (lhs.size() == rhs.size()){
            for (auto lit = lhs.begin(),rit = rhs.begin();lit != lhs.cend() && rit != rhs.cend(); lit++,rit++){
                if (*lit != *rit){
                    return false;
                }
            }
            return true;            
        }
        return false;
    }
    bool operator== (const char* lhs,const string& rhs){
        if (strlen(lhs) == rhs.size()){
            for (auto lit = lhs ,rit = rhs.begin();lit != lhs + strlen(s) && rit != rhs.cend(); lit++,rit++){
                if (*lit != *rit){
                    return false;
                }
            }
            return true;            
        }
        return false;
    }
    bool operator== (const string& lhs,const char* rhs){
        return rhs == lhs;
    }
    bool operator!= (const string& lhs, const string& rhs){
        return !(lhs==rhs);
    }
	bool operator!= (const char*   lhs, const string& rhs){
        return !(lhs==rhs);
    }
	bool operator!= (const string& lhs, const char*   rhs){
        return !(lhs==rhs);
    }

    bool operator> (const string& lhs, const string& rhs){
        return !(lhs <= rhs);
    }

    bool operator> (const char* lhs, const string& rhs){
        return !(lhs <= rhs);
    }

    bool operator> (const string& lhs, const char* rhs){
        return !(lhs <= rhs);
    }

    bool operator<= (const string& lhs, const string& rhs){
        return isLessEqual(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
    }

	bool operator<= (const char* lhs, const string& rhs){
        return isLessEqual(lhs,lhs+strlen(lhs),rhs.begin(),rhs.end());
    }

	bool operator<= (const string& rhs, const char* rhs){
        return isLessEqual(rhs.begin(),rhs.end(),rhs,rhs+strlen(rhs));
    }

        bool operator> (const string& lhs, const char* rhs){
        return !lhs <= rhs;
    }

    bool operator>= (const string& lhs, const string& rhs){
        return isGreaterEqual(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
    }

	bool operator>= (const char* lhs, const string& rhs){
        return isGreaterEqual(lhs,lhs+strlen(lhs),rhs.begin(),rhs.end());
    }

	bool operator>= (const string& rhs, const char* rhs){
        return isGreaterEqual(rhs.begin(),rhs.end(),rhs,rhs+strlen(rhs));
    }

    bool operator< (const string& lhs, const string& rhs){
        return !(lhs >= rhs);
    }

    bool operator< (const char* lhs, const string& rhs){
        return !(lhs >= rhs);
    }

    bool operator< (const string& lhs, const char* rhs){
        return !(lhs >= rhs);
    }

    friend void swap(string& x, string& y){
        x.swap(y);
    }

    friend std::istream& getline(std::istream& is, string& str, char delim){
        str.clear();
        char ch;
        while(is.get(ch)){
            if (ch != delim){
                str.push_back(ch);
            }
            else
                break;
        }
        return is;
    }
	friend std::istream& getline(std::istream& is, string& str){
        return getline(is,str,'\n');
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

    bool string::isContained(char ch,const_iterator first,const_iterator last) const {
        for (auto cit = first; cit != last; cit++){
            if (*cit == ch){
                return true;
            }
        }
        return false;
    }

    void string::string_aux(size_t n,char c,std::true_type){
        allocateAndFillN(n,c);
    }
};