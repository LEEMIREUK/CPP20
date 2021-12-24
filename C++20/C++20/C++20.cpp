#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// Three-Way Comparison 연산자 ( Spaceship Oerator <=> )

struct MyInt
{
    MyInt(int value) : _value(value) {}

    // < <= > >= == !=
    //bool operator<(const MyInt& rhs) const { return _value < rhs._value; }
    // 보통 6개의 비교 연산을 일일이 다 만들어줘야하지만
    // ThreeWayComparison 연산자를 이용하면 한번에 6개의 비교 연산을 지원한다.
    auto operator<=>(const MyInt& rhs) const = default; // 이렇게 만들어주면 6가지의 비교연산을 지원한다.

    // operator<, >, 등등이 operator<=>보다 우선순위가 높아서 만약 연산자가 여러가지가 있다면 <=>연산자 우선순위는 제일 낮다. 

    int _value;
};

struct Strong
{
    std::strong_ordering operator<=>(const Strong&) const = default;
};
struct Weak
{
    std::weak_ordering operator<=>(const Weak&) const = default;
};
struct Partial
{
    std::partial_ordering operator<=>(const Partial&) const = default;
};

struct Test
{
    auto operator<=>(const Test&) const = default;

    Strong s;
    Weak w;
    Partial p;
};
// Test에서의 auto는 자동적으로 partial_ordering 타입이 된다.
// 세가지 Strong, Weak, Partial중에 가장 약한 비교 범주가 Partial 이기 때문에 auto가 strong_ordering이나 weak_ordering으로 반환하지 않는다. (가장 약한 비교 범주를 리턴)

int main()
{
    MyInt a = 1;
    MyInt b = 2;

    bool test = a < b;
    bool test2 = a > b;
    bool test3 = a <= b;

    // ThreeWayComparison의 반환값이 strong_ordering이다.
    // C++표준에서 ordering은 크게 3가지로 구분할 수 있다.
    // strong ordering
    // weak ordering
    // partial ordering

    // 비교 특성 (Relational, Equivalence, Comparable)
    // - Relational : 6종 비교 연산을 모두 지원한다.(==, != ,< , <= , >, >= )
    // - Relational이라고 한다. (==, != ,< , <= , >, >= )
    // - Equivalence : 모든 Equivalent한 값들은 서로 구분되지 않고 완전 똑같다.
    // - Comparable : a < b, a == b, a > b 중 하나는 참이다.
    // ex) float 비교를 할 때, b가 NaN(not a number)면 3연산이 다 true가 아니다.

    // Strong Ordering : Relation(만족), Equivalence(만족), Comparable(만족)
    // Weak Ordering : Relation(만족), Comparable(만족)
    // Partial Ordereing : Relation(만족)

    int a1 = 100;
    int b1 = 200;
    auto ret = (a1 <=> b1);
    if (ret < 0)
        cout << "a < b" << endl;
    else if (ret == 0)
        cout << "a == 0" << endl;
    else if (ret > 0)
        cout << "a > b" << endl;
}