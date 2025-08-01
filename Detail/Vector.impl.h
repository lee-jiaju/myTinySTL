#ifndef _VECTOR_IMPL_H_
#define _VECTOR_IMPL_H_

namespace TinySTL {
    template <class T, class Alloc>
    vector<T,Alloc>::~vector(){
     destoryAndDeallocateAll(start_, finish_, endOfStorage_);
    }
    
    template <class T, class Alloc>
    vector<T,Alloc>::vector(const size_type n) {
        allocateAndFillN(n, value_type());
    }

    template <class T, class Alloc>
    vector<T,Alloc>::vector(const size_type n, const value_type& value) {
        allocateAndFillN(n, value);
    }

    template <class T, class Alloc>
    template <class InputIterator>
    vector<T, Alloc>::vector(InputIterator first, InputIterator last) {
        vector_aux(first, last,typename std::is_integral<InputIterator>::type());
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(const vector& vec){
        allocateAndCopy(vec.start_, vec.finish_);
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(vector&& vec){
        start_ = vec.start_;
        finish_ = vec.finish_;
        endOfStorage_ = vec.endOfStorage_;
        vec.start_ = vec.finish_ = vec.endOfStorage_ = nullptr; // Clear the moved-from vector
    }

    template <class T, class Alloc>
    vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& vec) {
        if (this != &vec) {
            allocateAndCopy(vec.start_, vec.finish_);
        }
        return *this;
    }

    template <class T, class Alloc>
    vector<T, Alloc>& vector<T, Alloc>::operator=(vector&& vec) {
        if (this != &vec) {
            destoryAndDeallocateAll();
            start_ = vec.start_;
            finish_ = vec.finish_;
            endOfStorage_ = vec.endOfStorage_;
            vec.start_ = vec.finish_ = vec.endOfStorage_ = nullptr; // Clear the moved-from vector
        }
        return *this;
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::resize(size_type n, const value_type& value) {
        if (n < size()) {
            TinySTL::destroy(finish_ - (size() - n), finish_);
            finish_ = start_ + n;
        } else if (n > size()) {
            if (n > capacity()) {
                auto newCapacity = getNewCapacity(n);
                T* newStart = dataAllocator::allocate(newCapacity);
                T* newFinish = TinySTL::uninitialized_copy(start_, finish_, newStart);
                TinySTL::uninitialized_fill_n(newFinish, n - size(), value);
                destoryAndDeallocateAll();
                start_ = newStart;
                finish_ = newFinish + (n - size());
                endOfStorage_ = start_ + newCapacity;
            } else {
                TinySTL::uninitialized_fill_n(finish_, n - size(), value);
                finish_ += (n - size());
            }
        }
    }

    template <class T, class Alloc>
    void vector<T,Alloc>::reserve(size_type n) {
        if (n > capacity()) {
            T *newStart = dataAllocator::allocate(n);
            T *newFinish = TinySTL::uninitialized_copy(begin(), end(), newStart);
            destroyAndDeallocateAll();

            start_ = newStart;
            finish_ = newFinish;
            endOfStorage_ = start_ + n;
        }
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position)
    {
        return erase(position, position + 1);
    }
    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
    {
        // β������������
        difference_type lenOfTail = end() - last;
        // ɾȥ�Ķ�����Ŀ
        difference_type lenOfRemoved = last - first;
        finish_ = finish_ - lenOfRemoved;
        for (; lenOfTail != 0; --lenOfTail)
        {
            auto temp = (last - lenOfRemoved);
            *temp = *(last++);
        }
        return (first);
    }

    template <class T, class Alloc>
    template <class InputIterator>
    void vector<T, Alloc>::reallocateAndCopy(InputIterator first, InputIterator last) {
        difference_type newCapacity = getNewCapacity(last - first);

        T *newStart = dataAllocator::allocate(newCapacity);
        T *newEndOfStorage = newStart + newCapacity;
        T *newFinish = TinySTL::uninitialized_copy(begin(), position, newStart);
        newFinish = TinySTL::uninitialized_copy(first, last, newFinish);
        newFinish = TinySTL::uninitialized_copy(position, end(), newFinish);

        destroyAndDeallocateAll();
        start_ = newStart;
        finish_ = newFinish;
        endOfStorage_ = newEndOfStorage;
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::reallocateAndFillN(iterator position, const size_type &n, const value_type &val)
    {
        difference_type newCapacity = getNewCapacity(n);

        T *newStart = dataAllocator::allocate(newCapacity);
        T *newEndOfStorage = newStart + newCapacity;
        T *newFinish = TinySTL::uninitialized_copy(begin(), position, newStart);
        newFinish = TinySTL::uninitialized_fill_n(newFinish, n, val);
        newFinish = TinySTL::uninitialized_copy(position, end(), newFinish);

        destroyAndDeallocateAll();
        start_ = newStart;
        finish_ = newFinish;
        endOfStorage_ = newEndOfStorage;
    }

    template <class T, class Alloc>
    template <class InputIterator>
    void vector<T, Alloc>::insert_aux(iterator position,
                                      InputIterator first,
                                      InputIterator last,
                                      std::false_type)
    {
        difference_type locationLeft = endOfStorage_ - finish_; // the size of left storage
        difference_type locationNeed = distance(first, last);   // last - first;

        if (locationLeft >= locationNeed)
        {
            if (finish_ - position > locationNeed)
            {
                TinySTL::uninitialized_copy(finish_ - locationNeed, finish_, finish_);
                std::copy_backward(position, finish_ - locationNeed, finish_);
                std::copy(first, last, position);
            }
            else
            {
                iterator temp = TinySTL::uninitialized_copy(first + (finish_ - position), last, finish_);
                TinySTL::uninitialized_copy(position, finish_, temp);
                std::copy(first, first + (finish_ - position), position);
            }
            finish_ += locationNeed;
        }
        else
        {
            reallocateAndCopy(position, first, last);
        }
    }
    template <class T, class Alloc>
    template <class Integer>
    void vector<T, Alloc>::insert_aux(iterator position, Integer n, const value_type &value, std::true_type)
    {
        assert(n != 0);
        difference_type locationLeft = endOfStorage_ - finish_; // the size of left storage
        difference_type locationNeed = n;

        if (locationLeft >= locationNeed)
        {
            auto tempPtr = end() - 1;
            for (; tempPtr - position >= 0; --tempPtr)
            { // move the [position, finish_) back
                //*(tempPtr + locationNeed) = *tempPtr;//bug
                construct(tempPtr + locationNeed, *tempPtr);
            }
            TinySTL::uninitialized_fill_n(position, n, value);
            finish_ += locationNeed;
        }
        else
        {
            reallocateAndFillN(position, n, value);
        }
    }
    template <class T, class Alloc>
    template <class InputIterator>
    void vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last)
    {
        insert_aux(position, first, last, typename std::is_integral<InputIterator>::type());
    }
    template <class T, class Alloc>
    void vector<T, Alloc>::insert(iterator position, const size_type &n, const value_type &val)
    {
        insert_aux(position, n, val, typename std::is_integral<size_type>::type());
    }
    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator position, const value_type &val)
    {
        const auto index = position - begin();
        insert(position, 1, val);
        return begin() + index;
    }
    template <class T, class Alloc>
    void vector<T, Alloc>::push_back(const value_type &value)
    {
        insert(end(), value);
    }
    //***********�߼��Ƚϲ������*******************
    template <class T, class Alloc>
    bool vector<T, Alloc>::operator==(const vector &v) const
    {
        if (size() != v.size())
        {
            return false;
        }
        else
        {
            auto ptr1 = start_;
            auto ptr2 = v.start_;
            for (; ptr1 != finish_ && ptr2 != v.finish_; ++ptr1, ++ptr2)
            {
                if (*ptr1 != *ptr2)
                    return false;
            }
            return true;
        }
    }
    template <class T, class Alloc>
    bool vector<T, Alloc>::operator!=(const vector &v) const
    {
        return !(*this == v);
    }
    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc> &v1, const vector<T, Alloc> &v2)
    {
        // return v1 == v2;
        return v1.operator==(v2);
    }
    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc> &v1, const vector<T, Alloc> &v2)
    {
        return !(v1 == v2);
    }
    template <class T, class Alloc>
    void vector<T, Alloc>::shrink_to_fit()
    {
        // dataAllocator::deallocate(finish_, endOfStorage_ - finish_);
        // endOfStorage_ = finish_;
        T *t = (T *)dataAllocator::allocate(size());
        finish_ = TinySTL::uninitialized_copy(start_, finish_, t);
        dataAllocator::deallocate(start_, capacity());
        start_ = t;
        endOfStorage_ = finish_;
    }
    template <class T, class Alloc>
    void vector<T, Alloc>::clear()
    {
        dataAllocator::destroy(start_, finish_);
        finish_ = start_;
    }
    template <class T, class Alloc>
    void vector<T, Alloc>::swap(vector &v)
    {
        if (this != &v)
        {
            TinySTL::swap(start_, v.start_);
            TinySTL::swap(finish_, v.finish_);
            TinySTL::swap(endOfStorage_, v.endOfStorage_);
        }
    }
    template <class T, class Alloc>
    void vector<T, Alloc>::pop_back()
    {
        --finish_;
        dataAllocator::destroy(finish_);
    }

    template <class T, class Alloc>
    void vector<T,Alloc>::destoryAndDeallocateAll(){
        if (capacity() > 0) {
            TinySTL::destroy(start_, finish_);
            dataAllocator::deallocate(start_, capacity());
        }
    }
    template <class T, class Alloc>
    void vector<T,Alloc>::allocateAndFillN(size_t n, const T& value) {
        if (n == 0) {
            start_ = finish_ = endOfStorage_ = nullptr;
            return;
        }
        start_ = dataAllocator::allocate(n);
        TinySTL::uninitialized_fill_n(start_, n, value);
        finish_ = endOfStorage_ = start_ + n;
    }

    template <class T, class Alloc>
    template <class InputIterator>
    void vector<T, Alloc>::allocateAndCopy(InputIterator first, InputIterator last) {
        if (first == nullptr || last == nullptr || first > last) {
            throw std::invalid_argument("Invalid iterator range");
        }
        size_t n = last - first;
        start_ = dataAllocator::allocate(n);
        finish_ = TinySTL::uninitialized_copy(first, last, start_);
        endOfStorage_ = finish_;
    }

    template <class T, class Alloc>
    template <class Integer>
    void vector<T, Alloc>::vector_aux(size_t n, const T& value, std::true_type) {
        allocateAndFillN(n, value);
    }

    template <class T, class Alloc>
    template <class InputIterator> 
    void vector<T, Alloc>::vector_aux(InputIterator first, InputIterator last, std::false_type) {
        allocateAndCopy(first, last);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::size_type vector<T, Alloc>::getNewCapacity(size_type len) const
    {
        size_type oldCapacity = endOfStorage_ - start_;
        auto res = TinySTL::max(oldCapacity, len);
        size_type newCapacity = (oldCapacity != 0 ? (oldCapacity + res) : len);
        return newCapacity;
    }
} // namespace TinySTL

