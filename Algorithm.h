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
    
    template<class RandomAccessIterator, class Compare>
    static void up(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator head,Compare comp){
        if (first != last){
            int index = last - head;
            auto parentIndex = (index - 1) / 2;
            for (auto cur = last; cur != head && parentIndex >= 0; parentIndex = (index - 1) / 2){
                auto parent = head + parentIndex;
                if (comp(*parent, *cur)){
                    TinySTL::swap(*parent, *cur);
                }
                cur = parent;
                index = cur - head;
            }
        }
    }

    template<class RandomAccessIterator, class Compare>
    static void down(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator head,Compare comp){
        if (first != last){
            int index = first - head;
            auto leftChildIndex = 2 * index + 1;
            for (auto cur = first; leftChildIndex < (last - head + 1) && cur != head; leftChildIndex = 2 * index + 1){
                auto child = head + leftChildIndex;
                if (child + 1 < last && (child + 1)>*child){
                    child++;
                }
                if (comp(*cur, *child))
                    TinySTL::swap(*cur, *child);
                cur = child;
                index = cur - head;
            }
        }
    }

    template <class RandomAccessIterator, class Compare>
    void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp){
        make_heap(first, last, typename TinySTL::less<TinySTL::iterator_traits<RandomAccessIterator>::value_type>());
    }

    template<class RandomAccessIterator, class Compare>
    void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp){
        auto range = last - first;
        for (auto cur = first + range/2 - 1; cur >= first; cur--){
            TinySTL::cur, last - 1, first, comp);
        }
        if (cur == first){
            return;
        }
    }

    template<class RandomAccessIterator>
    void push_heap(RandomAccessIterator first, RandomAccessIterator last){
        push_heap(first, last, typename TinySTL::less<TinySTL::iterator_traits<RandomAccessIterator>::value_type>());
    }

    template<class RandomAccessIterator, class Compare>
    void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp){
        if (last - first > 1){
            auto cur = last - 1;
            TinySTL::up(first, last, cur, comp);
        }
    }

    template<class RandomAccessIterator>
    void pop_heap(RandomAccessIterator first, RandomAccessIterator last){
        pop_heap(first, last, typename TinySTL::less<TinySTL::iterator_traits<RandomAccessIterator>::value_type>());
    }

    template<class RandomAccessIterator, class Compare>
    void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp){
        if (last - first > 1){
            auto cur = last - 1;
            TinySTL::swap(*first, *cur);
            TinySTL::down(first, cur-1, first, comp);
        }
    }

    template<class RandomAccessIterator>
    void sort_heap(RandomAccessIterator first, RandomAccessIterator last){
        sort(first, last, typename TinySTL::less<TinySTL::iterator_traits<RandomAccessIterator>::value_type>());
    }

    template<class RandomAccessIterator, class Compare>
    void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp){
        for (auto cur = last; cur != first; cur--){
            TinySTL::pop_heap(first, cur, comp);
        }
    }

    template<class RandomAccessIterator>
    bool is_heap(RandomAccessIterator first, RandomAccessIterator last){
        return is_heap(first, last, typename TinySTL::less<TinySTL::iterator_traits<RandomAccessIterator>::value_type>());
    }

    template<class RandomAccessIterator, class Compare>
    bool is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp){
        auto index = (first - last) / 2 - 1;
        for (auto cur = first + index; cur >= first; cur--,index--){
            auto leftChildIndex = 2 * index + 1;
            auto rightChildIndex = 2 * index + 2;
            if (leftChildIndex < (last - first) && comp(*(first + leftChildIndex), *cur)){
                return false;
            }
            if (rightChildIndex < (last - first) && comp(*(first + rightChildIndex), *cur)){
                return false;
            }
            if (cur == first){
                break;
            }
        }
        return true;
    }

    template <class InputIterator, class UnaryPredicate>
    bool all_of(InputIterator first, InputIterator last, UnaryPredicate pred)
    {
        for (; first != last; ++first)
        {
            if (!pred(*first))
                return false;
        }
        return true;
    }
    //********** [any_of] *************************
    //********* [Algorithm Complexity: O(N)] ****************
    template <class InputIterator, class UnaryPredicate>
    bool any_of(InputIterator first, InputIterator last, UnaryPredicate pred){
        for (; first != last; ++first)
        {
            if (pred(*first))
                return true;
        }
        return false;
    }
    //********** [none_of] *************************
    //********* [Algorithm Complexity: O(N)] ****************
    template <class InputIterator, class UnaryPredicate>
    bool none_of(InputIterator first, InputIterator last, UnaryPredicate pred){
        for (; first != last; ++first)
        {
            if (pred(*first))
                return false;
        }
        return true;
    }

    template <class InputIterator,class Function>
    Function for_each(InputIterator first, InputIterator last, Function fn)
    {
        for (; first != last; ++first){
            fn(*first);
        }
        return fn;
    }

    template <class InputIterator, class T>
    InputIterator find_of(InputIterator first, InputIterator last, const T& value){
        for (; first != last; ++first){
            if (*first == value)
                return true;
        }
        return false;
    }

    template <class InputIterator, class UnaryPredicate>
    InputIterator find_if(InputIterator first, InputIterator last, UnaryPredicate pred)
    {
        for (; first != last; ++first){
            if (pred(*first))
                return true;
        }
        return false;
    }

    template <class InputIterator, class UnaryPredicate>
    InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate pred)
    {
        for (; first != last; ++first)
        {
            if (pred(*first))
                return false;
        }
        return true;
    }

    template <class ForwardIterator1, class ForwardIterator2>
    ForwardIterator1 find_end(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 s_first, ForwardIterator2 s_last)
    {
        if (s_first == s_last)
            return last;
        ForwardIterator1 result = last;
        for (; first != last; ++first)
        {
            if (*first == *s_first)
            {
                auto it1 = first;
                auto it2 = s_first;
                while (it1 != last && it2 != s_last && *it1 == *it2)
                {
                    ++it1;
                    ++it2;
                }
                if (it2 == s_last)
                    result = first;
            }
        }
        return result;
    }

    template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
    ForwardIterator1 find_end(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 s_first, ForwardIterator2 s_last,BinaryPredicate pred)
    {
        if (s_first == s_last)
            return last;
        ForwardIterator1 result = last;
        for (; first != last; ++first)
        {
            if (pred(*first, *s_first))
            {
                auto it1 = first;
                auto it2 = s_first;
                while (it1 != last && it2 != s_last && pred(*it1, *it2))
                {
                    ++it1;
                    ++it2;
                }
                if (it2 == s_last)
                    result = first;
            }
        }
        return result;
    }

    template <class ForwardIterator1, class ForwardIterator2>
    ForwardIterator1 find_first_of(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 s_first, ForwardIterator2 s_last){
        for (; first != last; first++){
            for (auto it = s_first; it != s_last; ++it){
                if (*first == *it)
                    return first;
            }
        }
        return last; 
    }

    template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
    ForwardIterator1 find_first_of(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 s_first, ForwardIterator2 s_last, BinaryPredicate pred){
        for (; first != last; first++){
            for (auto it = s_first; it != s_last; ++it){
                if (pred(*first, *it))
                    return first;
            }
        }
        return last;
    }

    
}
#endif