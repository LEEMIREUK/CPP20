#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <format>
using namespace std;

// Format

int main()
{
	// 출력할 때
	printf("%d + %d = %d", 1, 1, 2);
	// 사용할 때 까다롭다. (타입, 개수 때문에)
	// C++20에서 포맷과 관련된 함수와 기능들이 추가되었다.

	// 언제사용하는가?
	// 로그찍을 때 원하는 포맷에 맞춰 만들어야하기 때문에 그때 사용
	// 로그 시스템에서 응용할 수 있다.

	// format : 포맷 스트링 반환
	// format_to : 결과를 output iterator에 반환
	// format_to_n : 최대 n개 문자를 output iterator에 반환

	cout << format("Hello C++{}", 20) << endl; // Hello C++20 출력된다.
	// 왜 이렇게 하는가?
	// 예를 들어 로그를 찍는다고 한다면 20이라는 간단한 숫자가 아니라 로그를 찍고싶어하는 해당 유저의 DB아이디가 될수 있고
	// 하드 코딩된 값이 아닌 변수의 의해 치환된 값을 넣어줄 수 있다.
	int value = 20;
	cout << format("Hello C++{}", value) << endl;


	string buffer;
	format_to(std::back_inserter(buffer), "Hello C++{}", 20); // buffer에 Hello C++20 저장
	cout << buffer << endl;
	buffer.clear();

	format_to_n(std::back_inserter(buffer), 5, "Hello C++{}", 20); // buffer에 Hello 저장
	cout << buffer << endl;


	// 여기서 보면 {}부분을 치환하고 싶은 위치로 인식하는데
	// 만약 진짜로 로그에 {}를 찍고싶다면 어떻게 하는가?
	// {{ }}, 두개를 사용하면 된다.
	cout << format("{{Hello C++{}}}", value) << endl; // {Hello C++20} 출력된다.

	// C# 스타일과 비슷하게 만들 수 도 있다.
	cout << format("{} {} {}", 10, 20, 30) << endl; // 10, 20, 30 출력
	// 순서를 지정해줄 수 있다.
	cout << format("{2} {0} {1}", 10, 20, 30) << endl; // 30 10 20 출력 10, 20, 30에서 10은 0번째 20은 1번째 30은 2번째이기에 {2}는 30이다.


	// Fill Character (빈칸 채우는 문자 지정 가능. 기본값은 space)
	// Alignment 
	// 정렬할 때
	// -  < left (숫자가 아니라면 left가 default)
	// -  > right (숫자라면 right가 default)
	// -  ^ center

	int num = 100;
	cout << format("{:10}", num) << endl; // 10개의 문자로 채워져 있는데 alignment가 숫자일 때 오른쪽으로 정렬이기 때문에 "       100" 이 출력된다.
	cout << format("{:10}", 'x') << endl; // "x          "
	cout << format("{:*<10}", 'x') << endl; // "x**********"
	cout << format("{:*>10}", 'x') << endl;// "**********x"
	cout << format("{:*^10}", 'x') << endl;// "*****x*****"

	// [부호]
	// 정수나 부동소수점에 사용
	// + (양수면 + 붙이라는 의미)
	// - (음수면 0 붙이라는 의미) default

	cout << format("{0:}, {0:+}, {0:-}, {0: }", 0) << endl;
	cout << format("{0:}, {0:+}, {0:-}, {0: }", 1) << endl;
	cout << format("{0:}, {0:+}, {0:-}, {0: }", -1) << endl;


	// [#]
	// 정수에 대해 0b(이진수), 0(팔진수), 0x(십육진수)
	// 0 : pads with leading zeros

	// {:#015}에서 15는 15칸 출력을 의미한다.
	cout << format("{:#015}", 0x78) << endl; // 000000000000120
	cout << format("{:#015b}", 0x78) << endl; // 0b0000001111000
	cout << format("{:#015x}", 0x78) << endl; // 0x0000000000078

	
	// [with / precision]
	// width : {:n} n은 minimum width
	// precision : .에다가 양수 조합 (string이라면 문자 개수, float라면 formatting precision)

	int i = 123456789;
	double d = 123.456789;

	cout << "---" << format("{}", i) << "---" << endl; 
	cout << "---" << format("{:15}", i) << "---" << endl; // w = 15
	cout << "---" << format("{}", d) << "---" << endl;
	cout << "---" << format("{:15}", d) << "---" << endl; // w = 15

	cout << "---" << format("{:.50}", d) << "---" << endl; // p = 50
	cout << "---" << format("{:.8}", d) << "---" << endl;
	cout << "---" << format("{:.5}", d) << "---" << endl;
	cout << "---" << format("{:.5}", "Hello World") << "---" << endl;

	/*
	---123456789---
	---      123456789---
	---123.456789---
	---     123.456789---
	---123.4567890000000005557012627832591533660888671875---
	---123.45679---
	---123.46---
	*/

	
	// [Type]
	// 대부분 컴파일러가 알아서 어떤 타입인지 추론해주지만
	// 직접 지정할 수 있다.
	// s : string
	// b : binary (2진수)
	// B : b와 같지만 0B로 시작
	// d : decimal (10진수)
	// o : octal (8진수)
	// x : hexadecimal (16진수)
	// X : x와 같지만 0X로 시작
	// 부동소수점 관련 (e, E, f, F, g, G) 등 지수표시하거나 정밀도 등을 표현할 때 사용

	// num = 100;
	cout << format("{:}", num) << endl; // 100
	cout << format("{:d}", num) << endl; // 100
	cout << format("{:b}", num) << endl; // 11000100
	cout << format("{:o}", num) << endl; // 144
	cout << format("{:x}", num) << endl; // 64

	// [User Define Types]
	// std::formatter 클래스를 신규 타입에 대해 특수화
	// - 멤버 함수 parse, format을 구현해야 함
	// 하지만 버그가 있는 것 같다.
}