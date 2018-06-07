/*!
 * \file
 * \brief Заголовочный файл с шаблонной функцией print_ip()
 * \author Aleksei Dovgal <altdaedroth@gmail.com>
 *
 * Выводит на печать условный ip-адрес
 * Может принимать на вход:
 *  - произвольный целочисленный тип - выводит побайтово, начиная со старшего, с символом "." в качестве разделителя
 *  - std::string - выводит без изменений
 *  - контейнеры std::list и std::vector - выводит поэлементно с символом "." в качестве разделителя
 *  - std::tuple, содержащие элементы одного типа
 */

#pragma once

#include <type_traits>
#include <iostream>
#include <tuple>

namespace my
{
//! Шаблон, проверяющий наличие у типа const_iterator'а
template<typename T>
struct has_const_iterator
{
private:
    typedef char                      one;
    typedef struct { char array[2]; } two;

    template<typename C> static one test(typename C::const_iterator*);
    template<typename C> static two test(...);
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(one);
    typedef T type;
};
//! Шаблон, проверяющий наличие у типа итераторов begin и end
template <typename T>
struct has_begin_end
{
    struct Dummy { typedef void const_iterator; };
    typedef typename std::conditional<has_const_iterator<T>::value, T, Dummy>::type TType;
    typedef typename TType::const_iterator iter;

    struct Fallback { iter begin() const; iter end() const; };
    struct Derived : TType, Fallback { };

    template<typename C, C> struct ChT;

    template<typename C> static char (&f(ChT<iter (Fallback::*)() const, &C::begin>*))[1];
    template<typename C> static char (&f(...))[2];
    template<typename C> static char (&g(ChT<iter (Fallback::*)() const, &C::end>*))[1];
    template<typename C> static char (&g(...))[2];

    static bool const beg_value = sizeof(f<Derived>(0)) == 2;
    static bool const end_value = sizeof(g<Derived>(0)) == 2;
};
//! Шаблон, проверяющий является ли тип контейнером
template <typename T>
struct is_container
{
    static const bool value = has_const_iterator<T>::value &&
            has_begin_end<T>::beg_value && has_begin_end<T>::end_value;
};
//---
//! Перегрузка для std::string
void print_ip(const std::string& t)
{
    std::cout << t << std::endl;
}

//! Перегрузка для контейнеров
template<typename Container>
std::enable_if_t<is_container<Container>::value, void> print_ip(const Container& c)
{
    for (auto it = std::begin(c); it != std::end(c); ++it) {
        if (it != std::begin(c))
            std::cout << ".";
        std::cout << *it;
    }
    std::cout<< std::endl;
}

//! Перегрузка для целочисленных типов
template<typename T>
std::enable_if_t<std::is_integral<T>::value, void> print_ip(const T& t)
{
    union bytes
    {
        unsigned char b[sizeof(t)];
        T val;
    } bi;

    bi.val = t;
    for (auto i = 1; i <= sizeof(t); ++i) {
        if (i != 1)
            std::cout << ".";
        std::cout << (int)bi.b[sizeof(t) - i];
    }
    std::cout << std::endl;
}
//---
//! Вывод кортежа
template<typename Type, size_t N, size_t Last>
struct print_tuple
{
    static void print(const Type& value)
    {
        std::cout << std::get<N>(value) << ".";
        print_tuple<Type, N+1, Last>::print(value);
    }
};

template<typename Type, size_t N>
struct print_tuple<Type, N, N>
{
    static void print(const Type& value)
    {
        std::cout << std::get<N>(value);
    }
};
//! Проверка содержит ли кортеж только одинаковые типы
template<typename... Args>
struct all_same: std::false_type{};

template<typename T>
struct all_same<T>: std::true_type{};

template<typename T, typename... Args>
struct all_same<T, T, Args...>: all_same<T, Args...> {};
//! Перегрузка для кортежей
template<typename... Types>
std::enable_if_t<all_same<Types...>::value, void> print_ip(const std::tuple<Types...>& value)
{
    print_tuple<std::tuple<Types...>, 0, sizeof...(Types) - 1>::print(value);
    std::cout<< std::endl;
}

}   // namespace my
