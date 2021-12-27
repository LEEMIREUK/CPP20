#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// ﻿Template Parameter for Lambda

auto sumTyped = [](int a, int b) {return a + b; }; // C++11 Typed Lambda

// 두 타입이 달라도 된다.
auto sumGeneric = [](auto a, auto b) {return a + b; }; // C++14 Generic Lambda

// 후자가 전자로 convertible (변환 가능)해야 한다. 만약 a가 int라면 b가 int로 변환이 가능한 타입 중 하나여야 한다.
auto sumDeclType = [](auto a, decltype(a) b) {return a + b; }; // C++14 Generic Lambda

// 두 타입이 같아야 한다.
auto sumTemplate = []<typename T>(T a, T b) { return a + b; }; // C++20 Template Lambda

auto getVectorSize = []<typename T>(const vector<T>& v) {return v.size(); };

int main()
{
	auto res1 = sumTyped(true, 100); // res1 = 101
	auto res2 = sumGeneric(true, 100); // res2 = 101
	auto res3 = sumDeclType(true, 100); // res3 = 2  100이 bool로 바뀌면 true(1)
	auto res4 = sumTemplate(true, true); // 2

	cout << res1 << endl;
	cout << res2 << endl;
	cout << res3 << endl;
	cout << res4 << endl;

	vector<int> v1{ 1, 2 };
	vector<double> v2{ 1.0, 2.0, 3.0 };
	auto s1 = getVectorSize(v1);
	auto s2 = getVectorSize(v2);
	cout << s1 << endl;
	cout << s2 << endl;
}