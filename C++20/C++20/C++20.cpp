#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <array>
#include <map>
#include <set>
using namespace std;

// Container

// C++20
// 1. vector, string 등에 constexpr 사용 가능
// algorithm 헤더에 있는 100개 이상의 함수들이 constexpr를 사용하도록 바뀌었다.
// 즉, 함수가 컴파일 타임에 연산이 될 수 있다는 뜻이다.

constexpr int Test()
{
	std::vector<int> v{ 1,4,5,2,3 };  // 원래는 C++20 이전에 이 코드는 런타임에 만들어지는 코드이다보니까 컴파일 타임에 함수의 결과물이 결정될수가 없었다.
	std::sort(v.begin(), v.end());
	return v.back();
}

template<typename T>
struct ArrayDeleter
{
	void operator()(const T* ptr)
	{
		delete[] ptr;
	}
};

int main()
{
	//int ret = Test(); // 반드시 런타임만 실행해서 알수 있었는데
	constexpr int ret = Test(); // constexpr로 바뀐 덕분에 컴파일 하지않고도 컴파일 타임에 이미 결정된 것이다. 그래서 의미가 있다.

	enum
	{
		VALUE = ret
	};
	// 그래서 enum으로 만들어도 오류없이 가능하다.


	// 2. std::array 만드는 방법이 추가되었다. (std::to_array)

	// 사이즈가 고정이라면 array를 사용하는 것이 좋다.
	// 새로 추가된 to_array로 편리하게 만들 수 있다.
	auto arr1 = std::to_array("Hello World");
	for (auto ch : arr1)
		cout << ch;
	cout << endl;
	// 여기서는 auto로 해서 암시적으로 타입을 추론했지만


	// 명시적으로 타입을 정해줄 수 있다.
	auto arr2 = std::to_array<int>({ 1,2,3,4,5 });
	for (auto ch : arr2)
		cout << ch;
	cout << endl;


	// 3. std::make_shared로 shared_ptr 배열 생성이 가능하다.
	// 
	// 동적할당: new - delete 짝을 맞춰야 한다.
	int* arr3 = new int[10];
	delete[] arr3;

	// 동적으로 배열을 만들어 준 뒤 shared_ptr에 관리를 하도록 해준다면 다음과 같이 해줄 수 있다.
//	std::shared_ptr<int> sp(new int[10]);
	// 아쉬운 부분은 delete 방식으로 삭제를 해야하는데 기존 shared_ptr에서는 이러한 처리가 안되기 때문에 정상적으로 삭제가 안된다.
	// 그래서 shared_ptr 두번째 인자로 어떻게 삭제할지 받을 수 있다.
	// 깔끔하게 삭제를 하고싶다면 템플릿이나 람다를 이용하면 된다.

	std::shared_ptr<int> sp(new int[10], ArrayDeleter<int>());

	// 이 방법이 너무 복잡하고 귀찮아서 C++20에서 개선하는 문법이 나왔다.

	// shared_ptr를 만들때 배열을 받아주는 버전이 생겼다.
	std::shared_ptr<double[]> shared_arr = std::make_shared<double[]>(1024);
	shared_arr[1] = 1.0;


	//4. erase, erase_if
	
	vector<int> vec{ -1, 2, -3, 4, -5 };
	// 음수를 삭제하는 방법

	// 기존의 방법
	for (auto it = vec.begin(); it != vec.end();)
	{
		int value = *it;
		if (value < 0)
			it = vec.erase(it);
		else
			++it;
	}

	// 가독성을 높인 버전 erase + std::remove_if
	vec.erase(remove_if(vec.begin(), vec.end(), [](int num) { return num < 0; }), vec.end());
	// 하지만 혼동할 수 있고 해석하는데 시간이 걸릴 수있다.


	// C++20 에서 erase와 erase_if가 추가되었다. 가독성을 더 높인 버전
	std::erase(vec, 2);	// vec에서 2 삭제
	std::erase_if(vec, [](int num) { return num < 0; }); // vec에서 음수 삭제



	// 5. contains + prefix / suffix checking
	
	// contains
	// map이나 set같은 컨테이너를 활용한다고 해보자
	
	std::set s{ 1,2,3,4,5 };
	// 특정 키값에 해당하는 데이터를 찾고 싶다면
	auto findIt = s.find(2);
	if (findIt != s.end())
		cout << "찾음" << endl;
	//이렇게 할 수 있다.

	// 위 방법은 iterator를 찾아서 비교하는 코드이지만
	// 좀더 가독성을 높이기 위해 C++20에서는 contains라는 문법이 추가되었다.
	if (s.contains(2))
		cout << "찾음" << endl;

	// map
	std::map<int, int> m{ {1, 1000}, {2, 2000} };
	if (m.contains(2))
		cout << "찾음" << endl;


	// string의 prefix/suffix (starts_with, ends_with) 추가
	std::string str = "Hello World";
	// 만약 str에서 특정 문자열로 시작하는지 체크하고 싶다면 다음과 같이 할 수 있다.
	bool b1 = str.starts_with("Hello");
	// 반대로 특정 문자열로 끝나는지도 체크 할수 있다.
	bool b2 = str.ends_with("World");
}