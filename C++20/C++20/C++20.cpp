#include <iostream>
using namespace std;

// Concept (컨셉)

// Concept 사용 방식 4가지
// 1) Requires Clause (절)
template<typename T>
requires std::integral<T>
void TestConcept1(T number)
{
    cout << number << endl;
}

// 2) Trailing Requires Clause (뒤에 붙는~)
template<typename T>
void TestConcept2(T number) requires std::integral<T>
{
    cout << number << endl;
}

// 3) Constrained Template Parameter (강요된)
template<std::integral T>
void TestConcept3(T number)
{
    cout << number << endl;
}

// 4) Abbreviated Function Template
void TestConcept4(std::integral auto number)
{
    cout << number << endl;
}

// class 테스트
class GameObject
{

};

class Knight : public GameObject
{

};

template<typename T>
requires std::derived_from<T, GameObject> // T(매개변수)가 GameObject 클래스의 파생된 것만 인자로 받을 수 있다.
void TestObj(T* obj)
{

}

// 나만의 컨셉을 만들 수 있다.
template<typename T>
concept MyConcept = !std::is_integral_v<T> && std::derived_from<T, GameObject>;

// 사용자 정의 컨셉(Addable)를 만들 수 있다.
template<typename T>
concept Addable = requires(T a, T b)
{
    a + b;
}; // a + b 가 가능해야 한다를 의미한다.

// == 지원하고 != 도 지원할 때 Equality라는 컨셉이 만족한다.
template<typename T>
concept Equality = requires(T a, T b)
{
    { a == b } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
};

// 이미 만들어진 컨셉도 같이 추가해서 만들 수 있다. 
// 두개의 조건 이용
template<typename T>
concept Integral = std::is_integral_v<T>;
template<typename T>
concept SignedInt = Integral<T> && std::is_signed_v<T>;
int main()
{
    TestConcept4(10);
    //TestConcept4(10.3f);

    TestObj(new Knight);
    //TestObj(new int);
}

/*
언어 관련
- same_as
- derived_from
- convertible_to
- common_reference_with
- common_with
- assignable_from
- swappable

산술 관련
- integral
- signed_integral
- unsigned_integral
- floating_point

생명주기 관련
- destructible
- constructible_from
- default_constructible
- move_constructible
- copy_constructible

비교 관련
- equality_comparable
- totally_ordered

오브젝트 관련
- movable
- copyable
- semiregular
- regular

호출(Callable) 관련
- invocable
- regular_invocable
- predicate

반복자 관련
- input_iterator
- output_iterator
- forward_iterator
- bidirectional_iterator
- random_access_iterator (***)
- contiguous_iterator

알고리즘/범위 관련
- permutable
- mergeable
- sortable
- ranges::input_range
- ranges::random_access_range
...
*/