#ifndef _TYPE_TRAITS_H_
#define _TYPE_TRAITS_H_

namespace TinySTL
{

    namespace
    {
        template <bool, class Ta, class Tb>
        struct IfThenElse;
        template <class Ta, class Tb>
        struct IfThenElse<true, Ta, Tb>
        {
            using result = Ta;
        };
        template <class Ta, class Tb>
        struct IfThenElse<false, Ta, Tb>
        {
            using result = Tb;
        };
    }

    // 在模板元编程中，这种空结构体常用来作为布尔值的类型替代，用于在编译期进行条件判断和类型选择。
    //例如，_type_traits 模板中会用这两个类型来标记某个类型是否具有某种特性（如是否是POD类型、是否有平凡构造函数等）。
    struct _true_type
    {
    };
    struct _false_type
    {
    };

    /*
    ** 萃取传入的T类型的类型特性
    ** template <class T> 是泛化模板，template <> 是针对具体类型的特化模板。
    */
    template <class T>
    struct _type_traits
    {
        typedef _false_type has_trivial_default_constructor;
        typedef _false_type has_trivial_copy_constructor;
        typedef _false_type has_trivial_assignment_operator;
        typedef _false_type has_trivial_destructor;
        typedef _false_type is_POD_type;
    };
    /*
    **POD类型是C++中一种特殊的类型，满足以下条件：
    // 是平凡类型（所有构造、拷贝、赋值、析构函数都是平凡的）。
    // 是标准布局类型（standard-layout），即其内存布局符合C语言的结构体规则，没有复杂的继承、多重继承、虚函数等。
    // 不包含非POD类型的成员。
    // POD类型的特点：

    // 可以安全地用C语言的方式操作（如用 memcpy 拷贝）。
    // 可以在C和C++之间无缝传递数据。
    // 其内存布局是连续且可预测的。
    */
    template <>
    struct _type_traits<bool>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<char>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<unsigned char>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<signed char>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<wchar_t>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<short>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<unsigned short>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<int>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<unsigned int>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<long>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<unsigned long>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<long long>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<unsigned long long>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<float>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<double>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<long double>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template <class T>
    struct _type_traits<T *>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <class T>
    struct _type_traits<const T *>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<char *>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<unsigned char *>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<signed char *>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<const char *>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<const unsigned char *>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };
    template <>
    struct _type_traits<const signed char *>
    {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

}
#endif