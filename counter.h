#pragma once

#include <sstream>

template <typename T>
struct counter
{
    counter() = default;
    virtual ~counter() {}

    counter(const counter& c) { _t = c._t; ++copy_ctor; }
    counter& operator=(const counter& c) { _t = c._t; ++copy_assign; return *this; }

    counter(counter&& c) : _t(std::move(c._t)) { ++move_ctor; }
    counter& operator=(counter&& c) {  _t = std::move(c._t); ++move_assign; return *this; }

    static void reset()
    {
        copy_ctor = 0;
        copy_assign = 0;
        move_ctor = 0;
        move_assign = 0;
    }

    static int copy_ctor;
    static int copy_assign;
    static int move_ctor;
    static int move_assign;

private:
    T _t;
};

template <typename T>
int counter<T>::copy_ctor = 0;

template <typename T>
int counter<T>::copy_assign = 0;

template <typename T>
int counter<T>::move_ctor = 0;

template <typename T>
int counter<T>::move_assign = 0;

template <typename T>
std::ostream& operator<<(std::ostream& os, const counter<T>& a)
{
    return os << " copy_ctor=" << a.copy_ctor << " copy_assign=" << a.copy_assign <<
                 " move_ctor=" << a.move_ctor << " move_assign=" << a.move_assign;
}
