#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// ﻿Ranged-Based For With Initializer

struct User
{
	int id;
};

User* GetUser()
{
	return nullptr;
}

int main()
{
	// C++17
	// if w/ Initializer
	// 이 문법이 유용하다.
	if (int a = 10; a == 10)
	{
		cout << a << endl;
	}

	//User* user = GetUser();
	//if (user == nullptr || user->id == 0)
	//	return;

	// 여기서 저 user 변수명이 이미 사용되었기 때문에 추가적으로 user 이름을 사용하고 싶어도 못한다.
	// 이때 C++17에 추가된 if w/ Initializer 문법을 이용하면 깔끔하다.
	//if (User* user = GetUser(); user == nullptr || user->id == 0)
	//	return;
	// 이렇게 한다면 user 변수명은 이 조건식 범위를 벗어나면 user라는 변수명을 새롭게 사용할 수 있기 때문에 좋다.

	// Switch w/ Initializer
	switch (int b = 3; b)
	{
	case 2:
		break;
	case 3:
		cout << "이게 되네?" << endl;
		break;
	}

	// Range-Based for
	vector<int> vec{ 1,2,3 };
	for (auto v : vec)
	{
		cout << v << endl;
	}

	// Range-Based for + Initializer
	for (vector<int> vec{ 1,2,3 }; auto v : vec)
	{
		cout << v << endl;
	}

}