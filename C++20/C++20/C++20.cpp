#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <array>
using namespace std;

// ﻿Non-Type Template Parameter

// Non-Type     
// - int, enum
// - 포인터, 참조값
// - nullptr_t

// 일반적으로 템플릿을 사용할 때 template<typename T>으로 하는데
// typename이 아니라 경우에 따라 int, enum 등 위의 3가지 종류만 들어갔다.

// 추가적으로 C++20 부터
// - 부동소수점 (floating-point)
// - Literal Type (types of constexpr variables)
// - String Literal

template<double d>
auto GetDouble()
{
    return d;
}

struct ClassType
{
    constexpr ClassType(int) {}
};

template<ClassType c>
auto GetClassType()
{
    return c;
}

template<int N>
class StringLiteral
{
public:
    constexpr StringLiteral(char const (&str)[N])
    {
        std::copy(str, str + N, _data);
    }

    char _data[N];
};

template<StringLiteral str>
class ClassTemplate {};

template<StringLiteral str>
void FunctionTemplate()
{
    cout << str._data << endl;
}

int main()
{
    auto d1 = GetDouble<5.5>();

    // Non-type parameter를 사용하는 경우?
    // std::array사용할 때 사용
    std::array<int, 5> arr; // 여기서 size가 들어가는 곳이 Non-type으로 되어있다.

    auto c1 = GetClassType<ClassType(2021)>();

    ClassTemplate<"Hello World"> cls1;
    FunctionTemplate<"Hello World">();


}