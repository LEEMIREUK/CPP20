#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <span>
using namespace std;

// std::span

void PrintArray(int* arr)
{
}

void PrintArray(int* arr, int len)
{
	cout << "array size() = " << len << endl;
	for (int i = 0; i < len; ++i)
		cout << arr[i] << endl;
}

void Print(std::span<int> container)
{
	cout << "container size() = " << container.size() << endl;
	for (int i = 0; i < container.size(); ++i)
		cout << container[i] << endl;
}

int main()
{
	// std::span = C배열, std::array, std::vector, std::string 등의
	// 연이은 객체 시퀀스 (contiguous sequence of objects)를 참조(refer)할 때 사용한다.
	// C배열, std::array, std::vector, std::string 등을 인자로 넘기지 않고 std::span으로 넘긴다.


	// C타입 배열
	int arr[] = { 1,2,3,4,5 };
	const int size = sizeof(arr);
	const int len = sizeof(arr) / sizeof(int);
	PrintArray(arr); // 배열의 주소를 넘겨준 것이지 배열에 대한 정보(size, len 등)을 추가적으로 넘기지 않았기 때문에
	// 위 함수내에서 더이상 기능을 만들 수 없다.

	// 그래서 결국 배열을 넘기고 싶을 때는 추가적으로 배열의 요소가 몇개가 있는지 같이 넘겨줘야 한다.
	PrintArray(arr, len);

	// 지저분하기 때문에 std::span 이용하면 된다.
	// <type T, size_t Extent = dynamic_extent>
	// std::span을 사용할 때는 extent를 두가지 중 하나로 골라주게 된다.
	// - static_extent = 컴파일 타임에 크기가 정해진 경우 (array)
	// - dynamic_extent = 컴파일 타임에 정해지지 않는 경우 (동적배열, vector 등)
	// std::span은 포인터 + 크기 두가지 정보만 가지고 있다.

	vector<int> myVec{ 1,2,3,4,5 };
	vector<int> myVec2{ 6,7,8,9,10 };

	std::span<int> dynamicSpan(myVec);
	std::span<int, 5> staticSpan(myVec2);

	Print(dynamicSpan);
	Print(staticSpan);

	dynamicSpan = staticSpan;
	// staticSpan = dynamicSpan; // error staticSpan은 고정적인 길이인데 가변적인 길이를 나타나는 애를 덮어쓰려고 하니 오류 출력


	// span 생성 방법
	// 포인터/사이즈를 이용해서 span 생성
	std::span<int> span1(myVec.data(), myVec.size());
	Print(span1);

	// 부분적으로 잘라서 만들기
	std::span<int> span2(span1.subspan(1, span1.size() - 3));
	Print(span2);

	// span을 이용해서 데이터를 조작할 수 있다.

	// transform : (인자 위치) 1~2 범위 대상으로 4함수 실행한 다음 3에 기록
	std::transform(span1.begin(), span1.end(), span1.begin(), [](int i) {return i * i; });
	Print(span1);
	Print(myVec); // span은 복사가 아니라 실제 원본 데이터가 수정된다.
	Print(span2); // span2또한 span1에서 가져온 것이기에 span1이 수정되어서 span2의 원본 데이터도 수정된다.

}