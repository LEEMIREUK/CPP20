#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>
using namespace std;

// Range

// 커스텀 뷰
template<std::ranges::input_range Range>
requires std::ranges::view<Range>
class ContainerView : public std::ranges::view_interface<ContainerView<Range>>
{
public:
    ContainerView() = default;

    constexpr ContainerView(Range r) : _range(std::move(r)), _begin(std::begin(r)), _end(std::end(r))
    {

    }

    constexpr auto begin() const { return _begin; }
    constexpr auto end() const { return _end; }

private:
    Range _range;
    std::ranges::iterator_t<Range> _begin;
    std::ranges::iterator_t<Range> _end;
};

template<typename Range>
ContainerView(Range&& range)->ContainerView<std::ranges::views::all_t<Range>>;

int main()
{
    // Range는 C#의 LINQ 문법과 비슷하다.
    
    vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    vector<int> v2;
    // 짝수를 추출해서
    for (int n : v1)
        if (n % 2 == 0)
            v2.push_back(n);

    // 2를 곱해준다.
    for (int& n : v2)
        n = n * 2;
    
    // 위처럼 STL 컨테이너들을 하나씩 순회하면서 코드를 만드는 사람이 많을 것이다.
    // 하지만 가독성차원에서
    // std::for_each();
    // std::find_if();
    // std::any_of();
    // 이러한 애들을 사용하는 것을 권장한다.

    // 위의 짝수 추출과 2곱하는 것을 Range를 이용해서 만든다면
    auto results = v1 | std::views::filter([](int n) {return n % 2 == 0; }) // 짝수 추출  (먼저 실행)
                    | std::views::transform([](int n) {return n * 2; }); // 2곱하기 (필터 이후 실행)

    for (auto n : results)
        cout << n << " ";
    cout << endl;
    // Range : Range란 순회할 수 있는 아이템 그룹 (ex. STL Container)
    // View : Range에 대해서 적용할 수 있는 연산
    
    // std::views::all		
    // std::ranges::filter_view / std::views::filter (조건 만족하는거 추출)
    // std::ranges::transform_view / std::views::transform (각 요소를 변환)
    // std::ranges::take_view / std::views::take (n개 요소를 추출)
    // std::ranges::take_while_view / std::views::take_while (조건 만족할 때까지 요소 추출)
    // std::ranges::drop_view / std::views::drop (n개 요소를 스킵)
    // std::ranges::drop_while_view / std::views::drop_while (조건 만족할 때까지 요소 스킵)
    // std::ranges::join_view / std::views::join (view 를 병합)
    // std::ranges::split_view / std::views::split (split)
    // std::ranges::reverse_view / std::views::reverse (역순서로 순회)
    // std::ranges::elements_view / std::views::elements (튜플의 n번째 요소를 대상으로 view 생성)
    // std::ranges::keys_view / std::views::keys (pair-like value의 첫번째 요소를 대상으로 view 생성)
    // std::ranges::values_view / std::views::values (pair-like value의 두번째 요소를 대상으로 view 생성)

    auto results2 = v1 | std::views::filter([](int n) { return n % 2 == 0; })
        | std::views::transform([](int n) { return n * 2; })
        | std::views::take(3);


    std::ranges::sort(v1);

    struct Knight
    {
        std::string name;
        int         id;
    };

    vector<Knight> knights =
    {
        {"Kim" , 1},
        {"Lee", 2},
        {"Park", 3},
        {"Jung" , 4},
    };

    std::ranges::sort(knights, {}, &Knight::name);   // ascending by name
    std::ranges::sort(knights, std::ranges::greater(), &Knight::name);   // descending by name
    std::ranges::sort(knights, {}, &Knight::id);   // ascending by id
    std::ranges::sort(knights, std::ranges::greater(), &Knight::name);   // descending by id

    map<string, int> m =
    {
        {"Kim" , 1},
        {"Lee", 2},
        {"Park", 3},
        {"Jung" , 4},
    };

    for (const auto& name : std::views::keys(m) | std::views::reverse)
        cout << name << endl;

    // 0~100 사이의 숫자중에 소수인 5개의 숫자를 추출해라
   
    auto isPrime = [](int num)
    {
        if (num <= 1)
            return false;
        for (int n = 2; n * n <= num; ++n)
            if (num % n == 0)
                return false;

        return true;
    };
    
    std::vector<int> v3;

    // std::views::iota(a, b) : a부터 시작해서 1씩 증가하고 b개를 만들어 준다.

    for (int n : std::views::iota(0, 100) | std::views::filter(isPrime) | std::views::take(5))
    {
        v3.push_back(n);
    }

    // 커스텀 뷰 (std::ranges::view_interface)
    std::vector<int> myVec{ 1,2,3,4,5 };
    auto myView = ContainerView(myVec);

    for (auto n : myView)
        cout << n << endl;
}