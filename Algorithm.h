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

    template <class ForwardIterator>
    ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last){
        return adjacent_find(first, last, typename TinySTL::equal_to<typename TinySTL::iterator_traits<ForwardIterator>::value_type>());
    }

    template <class ForwardIterator, class BinaryPredicate>
    ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last,BinaryPredicate pred)
    {
        for (; first != last;first++)
        {
            if ((first+1) != last && pred(*first, *(first + 1)))
                break;
        }      
        return first;
    }

    template <class ForwardIterator, class T>
    typename iterator_traits<ForwardIterator>::difference_type count(ForwardIterator first, ForwardIterator last, const T& value)
    {
        typename iterator_traits<ForwardIterator>::difference_type n = 0;
        for (; first != last; ++first)
        {
            if (*first == value)
                ++n;
        }
        return n;
    }

    template <class ForwardIterator, class UnaryPredicate>
    typename iterator_traits<ForwardIterator>::difference_type count_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)
    {
        typename iterator_traits<ForwardIterator>::difference_type n = 0;
        for (; first != last; ++first)
        {
            if (pred(*first))
                ++n;
        }
        return n;
    }

    template <class ForwardIterator1, class ForwardIterator2>
    pair<ForwardIterator1, ForwardIterator2> mismatch(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            if (*first1 != *first2)
                break;
        }
        return TinySTL::make_pair(last1, first2);
    }

    template <class ForwardIterator1, class ForwardIterator2,class BinaryPredicate>
    pair<ForwardIterator1, ForwardIterator2> mismatch(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, BinaryPredicate pred)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            if (!pred(*first1, *first2))
                break;
        }
        return TinySTL::make_pair(last1, first2);
    }

    template <class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        return equal(first1, last1, first2, typename TinySTL::equal_to<typename TinySTL::iterator_traits<InputIterator1>::value_type>());
    }

    template <class InputIterator1, class InputIterator2,class BinaryPredicate>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,BinaryPredicate pred)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            if (!pred(*first1, *first2))
                return false;
        }
        return true;
    }

    template <class InputIterator1, class InputIterator2>
    bool is_permutation(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2){
        return is_permutation(first1, last1, first2, typename TinySTL::equal_to<typename TinySTL::iterator_traits<InputIterator1>::value_type>());
    }

    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool is_permutation(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
    {
        // find the first position that is not equal
        auto res = TinySTL::mismatch(first1, last1, first2, pred);
        first1 = res.first, first2 = res.second;
        if (first1 == last1)
            return true;
        auto last2 = first2;
        std::advance(last2, std::distance(first1, last1));
        for (auto it1 = first1; it1 != last1; ++it1)
        {
            if (TinySTL::find_if(first1, it1, [&](decltype(*first1) val)
                                 { return pred(val, *it1); }) == it1)
            {
                auto n = TinySTL::count(first2, last2, *it1);
                if (n == 0 || TinySTL::count(it1, last1, *it1) != n)
                    return false;
            }
        }
        return true;
    }

    template <class ForwardIterator1, class ForwardIterator2>
    ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2){
        return search(first1, last1, first2, last2, typename TinySTL::equal_to<typename TinySTL::iterator_traits<ForwardIterator1>::value_type>());
    }

    template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
    ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred)
    {
        while (first1 != last1)
        {
            auto it1 = first1;
            auto it2 = first2;
            while (it1 != last1 && it2 != last2 && pred(*it1, *it2))
            {
                ++it1;
                ++it2;
            }
            if (it2 == last2)
                return first1;
            if (it1 == last1)
                return last1;
            ++first1;
        }
        return last1;      
    }

    namespace{
        template <class InputIterator, class Distance>
        void _advance(InputIterator &it, Distance n, input_iterator_tag)
        {
            assert(n >= 0);
            while (n--){
                ++it;
            }
        }

        template <class BidirectionalIterator, class Distance>
        void _advance(BidirectionalIterator &it, Distance n, bidirectional_iterator_tag)
        {
            if (n < 0)
                while (n++){
                --it;
            }
            else{
                while(n--){
                    ++it;
                }
            }    
        }

        template <class RandomAccessIterator, class Distance>
        void _advance(RandomAccessIterator &it, Distance n, random_access_iterator_tag){
            if (n < 0){
                it -= -n;
            }
            else{
                it += n;
            }
        }

    }

    template <class InputIterator, class Distance>
    void advance(InputIterator &it, Distance n){
        typedef typename TinySTL::iterator_traits<InputIterator>::iterator_category category;
        _advance(it, n, category());
    }
    namespace{
        template <class InputIterator, class BinaryPredicate>
        typename TinySTL::iterator_traits<InputIterator>::value_type> mid3(InputIterator first, InputIterator last, BinaryPredicate comp)
        {
            auto mid = first + (last - first) / 2;
            if (comp(*mid, *first))
                TinySTL::swap(*mid, *first);
            if (comp(*last, *mid))
                TinySTL::swap(*last, *mid);
            if (comp(*last, *first))
                TinySTL::swap(*mid, *last);

            auto ret = *mid;
            swap(*mid, *(last - 1));
            return ret;
        }

        template <class RandomAccessIterator, class BinaryPredicate>
        void bubble_sort(RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate comp){
            if (first == last)
                return;
            for (auto i = first; i != last - 1; ++i){
                bool swaped = false;
                for (auto j = first; j != last - 1 - (i - first); ++j){
                    if (comp(*(j + 1), *j)){
                        TinySTL::swap(*j, *(j + 1));
                        swaped = true;
                    }
                }
                if (!swapped){
                    break
                }
            }
        }
    }

    template <class RandomAccessIterator, class BinaryPredicate>
    void sort(RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate comp){
        if (first == last)
            return;
        if (last - first <= 16){
            bubble_sort(first, last, comp);
            return;
        }
        auto pivot = mid3(first, last - 1, comp);
        auto left = first;
        auto right = last - 2;
        while (left <= right){
            while (comp(*left, pivot))
                ++left;
            while (comp(pivot, *right))
                --right;
            if (left < right){
                TinySTL::swap(*left, *right);
                ++left;
                --right;
            }
            else if (left == right){
                ++left;
            }
        }
        TinySTL::sort(first, right + 1, comp);
        TinySTL::sort(left, last, comp);
    }

    template <class InputIterator, class Function>
    void generate(InputIterator first, InputIterator last, Function gen)
    {
        for (; first != last; ++first)
        {
            *first = gen();
        }
    }

    template <class InputIterator, class Size, class Function>
    InputIterator generate_n(InputIterator first, Size n, Function gen){
        while (n--)
        {
            *first = gen();
            ++first;
        }
    }

    template <class InputIterator>
    typename iterator_traits<InputIterator>::difference_type _distance(InputIterator first, InputIterator last,input_iterator)
    {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        for (; first != last; ++first)
        {
            ++n;
        }
        return n;
    }

    template <class RandomAccessIterator>
    typename iterator_traits<RandomAccessIterator>::difference_type _distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator)
    {
        return last - first;
    }

    template <class Iterator>
    typename iterator_traits<Iterator>::difference_type distance(Iterator first, Iterator last)
    {
        typedef typename iterator_traits<Iterator>::iterator_category category;
        return _distance(first, last, category());
    }

    template <class InputIterator,class OutputIterator>
    OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result,_true_type){
        auto dis = distance(first, last);
        memcpy(result, first, (last - first) * sizeof(*first));
        advance(result, dis);
        return result;
    }

    template <class InputIterator, class OutputIterator>
    OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result,_false_type){
        for (; first != last; ++first, ++result)
        {
            *result = *first;
        }
        return result;
    }

    template <class InputIterator, class OutputIterator,class T>
    OutputIterator _copy(InputIterator first, InputIterator last, OutputIterator result,T*)
    {
        typedef typename TinySTL::_type_traits<T>::is_POD_type is_pod;
        return __copy(first, last, result, is_pod());
    }

    template <class InputIterator, class OutputIterator>
    OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result){
        return __copy(first, last, result,value_type(first));
    }

    template <>
    inline char* copy(char* first, char* last, char* result){
        auto dis = last - first;
        memcpy(result, first, dis*sizeof(*first));
        return result + dis;
    }

    template <>
    inline wchar_t* copy(wchar_t* first, wchar_t* last, wchar_t* result){
        auto dis = last - first;
        memcpy(result, first, dis * sizeof(*first));
        return result + dis;
    }
}
#endif