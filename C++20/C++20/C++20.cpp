#include <iostream>
using namespace std;

import math;

import MathPartition;
// Module

int main()
{
	// 빌드 단계
	// 전처리
	// - #include, #define ... 처리
	// 컴파일
	// - 오브젝트 파일 생성 (.obj)
	// 링크
	// - 오브젝트 파일들을 라이브러리와 하나로 묶어 연결
	
	// 기존에 사용하던 방법의 문제점
	// 1) 빌드 속도
	// 너무 느리다.
	int sum = Add(1, 2);
	TestExport();
	math::TestExport2();
	MathTimeFunc();

	MyFunc1();
	MyFunc2();
}