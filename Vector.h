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
        vector() : start_(0), finish_(0), endOfStorage_(0) {};
        explicit vector(const size_type n);
        vector(const size_type n, const value_type& value);
        template <class InputIterator>
        vector(InputIterator first, InputIterator last);
        vector(const vector& vec);
        vector(vector&& vec);
        vector &operator=(const vector &v);
        vector &operator=(vector &&v);
        ~vector();

        bool operator==(const vector& v) const;
        bool operator!=(const vector& v) const;

        iterator begin(){ return (start_); }
		const_iterator begin()const{ return (start_); }
		const_iterator cbegin()const{ return (start_); }
		iterator end(){ return (finish_); }
		const_iterator end()const{ return (finish_); }
		const_iterator cend()const{ return (finish_); }
		reverse_iterator rbegin(){ return reverse_iterator(finish_); }
		const_reverse_iterator crbegin()const{ return const_reverse_iterator(finish_); }
		reverse_iterator rend(){ return reverse_iterator(start_); }
		const_reverse_iterator crend()const{ return const_reverse_iterator(start_); }

        difference_type size() const { return finish_ - start_; }
        difference_type capacity() const { return endOfStorage_ - start_; }
        empty() const { return start_ == finish_; }
        void resize(size_type n, const value_type &value);
        void reserve(size_type n);
        void shrink_to_fit();

        reference operator[](size_type n) { return *(begin() + n); }
        const_reference operator[](const size_type n) const { return *(begin() + n); }
        reference front() { return *start_; }
        reference back() { return *(finish_ - 1); }
        pointer data() { return start_; }

        void clear();
        void swap(vector& v);
        void push_back();
        void pop_back();
        iterator insert(iterator position, const value_type &val);
        void insert(iterator position, const size_type &n, const value_type &val);
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last);
        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);

        // �����Ŀռ����������
        Alloc get_allocator() { return dataAllocator; }
        // Other member functions and data memb..

    private:
        void destoryAndDeallocateAll();
        void allocateAndFillN(size_t n, const T& value);
        template <class InputIterator>
        void allocateAndCopy(InputIterator first, InputIterator last);
        template <class Integer>
        void vector_aux(size_t n, const T &value, std::true_type);
        template <class InputIterator>
        void vector_aux(InputIterator first, InputIterator last, std::false_type);
        template <class InputIterator>
        void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);
        template <class Integer>
        void insert_aux(iterator position, Integer n, const value_type &val, std::true_type);
        template <class InputIterator>
        void reallocateAndCopy(iterator position, InputIterator first, InputIterator last);
        void reallocateAndFillN(iterator position, const size_type &n, const value_type &val);
        size_t getNewCapacity(size_t len) const;

    public:
        template <class T, class Alloc>
        friend bool operator==(const vector<T, Alloc> &v1, const vector<T, Alloc> &v2);
        template <class T, class Alloc>
        friend bool operator!=(const vector<T, Alloc> &v1, const vector<T, Alloc> &v2);
    };
}
#include "Detail\Vector.impl.h"
#endif