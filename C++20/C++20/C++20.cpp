#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <format>
#include <source_location>
#include <functional>
using namespace std;

// 기타 함수

void PrintLog(const char* filename, int line)
{
    cout << format("{} Line({})", filename, line) << endl;
}

int Add(int a, int b)
{
    return a + b;
}

void Test()
{
    if (std::is_constant_evaluated())
    {
        // 컴파일 타임
    }
    else
    {
        // 런타임
    }
}

int main()
{
    // source_location
    // - 로그 남길 때
    // - 멀티쓰레드 환경에서 데드락 탐지
    // - 메모리 누수를 잡기 위해서 할당/헤제 
    // 할 때 사용

    // 기존의 방법
    PrintLog(__FILE__, __LINE__);

    // 추가된 기능
    auto src = std::source_location::current();
    PrintLog(src.file_name(), src.line());

    // bind_front
    // Add(10, 20);
    using namespace std::placeholders;
    auto func = std::bind(Add, 10, _1);

    cout << func(20) << endl;

    auto func2 = std::bind_front(Add, 10);
    cout << func2(20) << endl;

    auto func3 = [](int b) {return Add(10, b); };
    cout << func3(20) << endl;
    // 보통 바인드보단 람다를 사용한다.


    // is_constant_evaluated
    // - 어떤 함수가 컴파일 타임에 실행이 되는지 여부를 함수 내부에서 판별할 수 있다.
    
    // consteval 붙은 함수는 컴파일 타임에 실행됨
    // constexpr 붙은 함수는 컴파일/런타임 둘다 됨
    // 보통 함수 런타임

    // constexpr경우 둘다 가능하기 때문에 is_constant_evaluated로 체크하여
    // 구분할 수 있다.
}