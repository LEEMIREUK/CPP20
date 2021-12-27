#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// ﻿using enum in Local Scopes

enum class Color
{
	Red,
	Green,
	Blue,
};

using enum Color;

int main()
{
	Color color = Color::Blue;

	switch (color)
	{
	case Color::Red:
		break;
	case Color::Green:
		break;
	case Color::Blue:
		break;
	}
	// 매번 Color:: 붙이기 싫기 때문에 using enum Color 선언
	

	switch (color)
	{
	case Red:
		break;
	case Green:
		break;
	case Blue:
		break;
	}
	// 하지만 using enum Color를 해버리면 더이상 Color를 사용할 생각이 없음애도 불구하고
	// Red, Green, Blue 는 Color::으로 인식한다.
	// 전역으로 다 해주는 것이 아닌 부분으로 열어줄 수 있는 방법이 C++20 추가되었다.


	switch (color)
	{
	using enum Color;
	case Red:
		break;
	case Green:
		break;
	case Blue:
		break;
	}
	/// using enum Color; 은 switch 범위를 벗어나면 유효하지 않다.
}