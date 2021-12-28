#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <numbers>
#include <numeric>
using namespace std;

int main()
{
	int x = -2;
	unsigned int y = 10;
	// 부호있는 정수와 부호없는 정수를 섞어 사용한다고 가정해보자.
	// 보통 게임에서 음수로 떨어지지 않는 정수가 대부분이다. (ex. 골드, 체력, 능력치 등) 양수
	// 그럼에도 불구하고 unsigned를 사용하지 않고 int로 통일하는 경우가 많다.

	cout << std::boolalpha;
	cout << "-2 < 7 = " << (x < y) << endl;
	cout << "-2 <= 7 = " << (x <= y) << endl;
	cout << "-2 > 7 = " << (x > y) << endl;
	cout << "-2 >= 7 = " << (x >= y) << endl;
	// 생각되는 기대값은 true, true, false, false 이지만
	// 실제로 출력되는 것은 false, false, true, true 이다.

	// 혹시 모르니 auto로 테스트를 해보자.
	auto z = (x < y);
	// 하지만 똑같이 false이다.


	// 위에서 연산 순서는 x를 형변환 후 y와 연산을 하는 것이다.

	unsigned int tempX = (unsigned int)x; // 를 해준 뒤 y와 비교한 것이다.
	// ussigned에서는 마이너스가 존재하지 않기 때문에 동일한 데이터 값을 가지는 상태에서
	// 부호 없는 상태로 숫자를 추출했기 때문에 -2는 엄청 큰 값으로 바뀐다.


	// 그래서 C++20에서 cmp_XX가 추가되었다.
	cout << "-2 < 7 = " << std::cmp_less(x, y) << endl;
	cout << "-2 <= 7 = " << std::cmp_less_equal(x, y) << endl;
	cout << "-2 > 7 = " << std::cmp_greater(x, y) << endl;
	cout << "-2 >= 7 = " << std::cmp_greater_equal(x, y) << endl;
	// 이제는 정상적으로 출력이 된다.

	
	// 만약 non-integer(정수 아닌) 타입을 넣는다면?
	//std::cmp_less(3, 1.4f); // error

	// 정말 비교를하고싶다면
	bool b1 = (3 < 1.4f); // 원래의 방법으로 하면 된다.


	// C++20에서 수학 상수 기호들이 추가되었다.
	// 예를들어 파이의 경우 
	const float PI = 3.14f;
	// 를 선언해서 사용했지만
	std::numbers::pi;	// 파이
	std::numbers::pi_v<float>;	// 파이(float버전)
	std::numbers::sqrt2; // 루트 2
	std::numbers::e; // e (지수함수에서의 e)
	// 위처럼 사용할 수 있다.

	// 중간값이나 보간값을 추출할 수 있는 기능들이 추가되었다.
	// a와 b의 중간값을 추출하고 싶다면
	// 다음과 같이 편리하게 사용가능하다.
	
	// 중간값 (a + (b-a) / 2)
	// [a | b]
	std::midpoint(10, 20); 

	// 선형 보간
	// [a  |    b] (a + t * (b-a))
	constexpr int ler =	std::lerp(10, 20, 0.1); // 10에서 20까지 보간을 하고싶은데 0.1비율로 하겠다. 즉 1:9의 위치를 추출한다. (11 추출)
}
