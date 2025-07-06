#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include <new>

#include "TypeTraits.h"

namespace TinySTL
{
    /**
     * 在ptr1指向的内存位置上构造一个类型为T1的对象，
     * 并使用value对该对象进行初始化。
     * 通过placement new实现对象的原地构造。
     *
     * @param ptr1 指向预分配内存的指针
     * @param value 用于初始化新构造对象的值
     */
    template <class T1, class T2>
    inline void construct(T1 *ptr1, const T2 &value)
    {
        new (ptr1) T1(value);
    }

    /**
     * 销毁指针ptr所指向的对象，调用其析构函数。
     *
     * @param ptr 指向需要销毁的对象的指针
     */
    template <class T>
    inline void destroy(T *ptr)
    {
        ptr->~T();
    }

    /**
     * 针对POD类型的范围，_destroy不执行任何操作，
     * 因为POD类型不需要显式调用析构函数。
     *
     * @param first 范围起始迭代器
     * @param last 范围结束迭代器
     * @param _true_type 标识该类型为POD类型
     */
    template <class ForwardIterator>
    inline void _destroy(ForwardIterator first, ForwardIterator last, _true_type) {}

    /**
     * 针对非POD类型的范围，逐个调用destroy销毁每个对象，
     * 以确保调用对象的析构函数释放资源。
     *
     * @param first 范围起始迭代器
     * @param last 范围结束迭代器
     * @param _false_type 标识该类型为非POD类型
     */
    template <class ForwardIterator>
    inline void _destroy(ForwardIterator first, ForwardIterator last, _false_type)
    {
        for (; first != last; ++first)
        {
            destroy(&*first);
        }
    }

    template <class ForwardIterator>
    inline void destroy(ForwardIterator first, ForwardIterator last)
    {
        //通过 _type_traits 模板获取迭代器指向类型是否为POD（Plain Old Data，简单数据类型）类型的标识。 
        typedef typename _type_traits<ForwardIterator>::is_POD_type is_POD_type;
        _destroy(first, last, is_POD_type());
    }

}

#endif