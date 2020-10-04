#pragma once

#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <string>
#include <tuple>

using namespace std;

/*!
 *  Meta function same_types.
 *  Is true_type only if all arguments are the same.
 */
template <typename T, typename ...Args>
struct same_types;

template <typename T>
struct same_types<T, T> : true_type {};

template <typename T, typename U, typename ...Args>
struct same_types<T, U, Args...> : false_type {};

template <typename T, typename ...Args>
struct same_types<T, T, Args...> : same_types<T, Args...> {};

/*!
 *  Meta function is_one_of_types.
 *  Is true_type only if one of arguments is the same as first argument.
 */
template <typename T, typename ...Args>
struct is_one_of_types;

template <typename T>
struct is_one_of_types<T> : false_type {};

template <typename T, typename ...Args>
struct is_one_of_types<T, T, Args...> : true_type {};

template <typename T, typename U, typename ...Args>
struct is_one_of_types<T, U, Args...> : is_one_of_types<T, Args...> {};

/*!
 *  Template function print_ip (integral).
 *  This specialization used for cases when argument is integral type.
 */
template <typename T>
typename enable_if<is_integral<T>::value, void>::type print_ip(const T& _ip)
{
    T ip = _ip;
    unsigned char* byte_ptr = reinterpret_cast<unsigned char*>(&ip);
    for (int ix = sizeof(T) - 1; ix >= 0; --ix)
    {
        cout << +byte_ptr[ix] << (ix > 0 ? "." : "");
    }
    cout << endl;
}

/*!
 *  Template function print_ip (vector, list).
 *  This specialization used for cases when argument has vector or list type.
 */
template <typename T>
typename enable_if<is_one_of_types<T, vector<typename T::value_type>, list<typename T::value_type>>::value, void>::type print_ip(const T& _ip)
{
    auto begin = _ip.begin();
    auto end = _ip.end();

    const size_t size = _ip.size();
    size_t ix = 0;
    while (begin != end)
    {
        cout << *begin << (ix < size - 1 ? "." : "");
        ++ix;
        ++begin;
    }
    cout << endl;
}

/*!
 *  Template function print_ip (string).
 *  This specialization used for cases when argument has vector or list type.
 */
template <typename T>
typename enable_if<same_types<T, string>::value, void>::type print_ip(const T& _ip)
{
    cout << _ip << endl;
}

/*!
 *  Template function print_ip (tuple).
 *  This specialization used for cases when argument has vector or list type.
 */
template <typename T>
typename enable_if<same_types<typename tuple_element<0, T>::type,
                              typename tuple_element<1, T>::type,
                              typename tuple_element<2, T>::type,
                              typename tuple_element<3, T>::type>::value, void>::type print_ip(const T& _ip)
{
    using tuple_type = typename tuple_element<0, T>::type;
    tuple_type byte1, byte2, byte3, byte4;
    tie(byte1, byte2, byte3, byte4) = _ip;
    cout << byte1 << '.' << byte2 << '.' << byte3 << '.' << byte4 << endl;
}
