module; // global module fragment

// 각종 외부 헤더 추가
#include <vector>

// module 시작
export module math;

// import module...
export import math.time; // submodule 문법, math.time을 import해서 다시 math 모듈에 포함해서 export

// 모듈 사용 문법

// 1) 함수 앞에다가 export 선언하는 방법
export int Add(int a, int b)
{
	return a + b;
}

// 2) export하고 싶은 함수들을 따로 묶어주는 방법
export
{
	void TestExport()
	{

	}
}

// 3) namespace를 지정하는 방법
export namespace math
{
	void TestExport2()
	{

	}
}