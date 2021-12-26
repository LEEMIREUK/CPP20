#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// ﻿Conditionally Explicit Constructor (조건부 Explicit 생성자)

struct A
{
	A() = default;
	
	//A(int n)
	//{
	//	cout << n << endl;
	//}

	explicit A(int n)
	{
		cout << n << endl;
	}
};

void TestA(A a)
{

}

struct B
{
	// 받아주는 인자가 여러가지 버전이 있다고해보자.
	// int, float, bool 등등
	// 많은 타입을 받는다고 한다면 template으로 생성자를 만들어 줄 수 있다.
	template<typename T>
	explicit B(T t)
	{

	}
	// 하지만 template으로 생성자를 만들어 준다면 진짜로 모든 타입을 받아주기 때문에 살짝 문제가 될수 도있다.
};

void TestB(B b)
{

}

struct C
{
	// 조건부 Explicit
	// - bool에 의한 간접 변환(Implicit Conversion)은 허용
	// - 그 외에는 Explicit
	template<typename T>
	explicit(!std::is_same<T, bool>::value) C(T t)
	{
		cout << typeid(t).name() << endl;
	}
};

void TestC(C c)
{

}

int main()
{
	A a;
	TestA(a);
	//TestA(10); // 이건 왜 될까? A의 생성자 중에서 정수를 받는 버전이 있기 때문에 간접적으로 임시객체를 만들어 생성자를 호출후 다시 넘겨주고 있는 것이다.
	// A a2(10) 를 만들어 준뒤  Test(a2) 인 느낌이다.
	// 만약 이것을 의도한게 아니고 A객체만 받을 수 있도록 함수를 만들었는데 정수를 넣어도 호출되는게 싫다면 이때 explicit 키워드를 붙이면 된다.

	
	// B의 생성자가 template이기 때문에 모든 타입이 가능하다.
	//TestB(2021);
	//TestB("Hello World");
	// 만약 B의 생성자에 explicit을 추가하면 어떻게 될까?
	// 위 두 함수는 오류가 된다.

	// 결국 explicit : 원하지 않은 형변환이 일어나지 않도록 제한하는 키워드 이다.
	B b(2021);
	TestB(b);

	// 만약 모든 타입을 막는 것이 아니고 조건부적으로 explicit을 붙이고 싶다면 다음과 같은 문법이 있다.
	C c1 = true;
	TestC(c1);
	TestC(true);
	// TestC(10); // 허용이 안되기 때문에 오류
}