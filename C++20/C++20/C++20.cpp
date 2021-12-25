#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// consteval / constinit

int SqrRunTime(int n)
{
	return n * n;
}

// C++11
constexpr int SqrRunOrCompileTime(int n)
{
	return n * n;
}

// C++20
consteval int SqrCompileTime(int n)
{
	return n * n;
}


int main()
{
	// 함수 (일반 vs constexpr vs consteval)
	{
		// 컴파일 타임 vs 런타임

		// 빌드를 후 실행하면 컴파일 단계가 된다.
		// C++코드를 컴파일러가 번역해서 바이너리 파일로 만들어 준 뒤 결과물들이
		// 링크 단계를 거쳐 실행파일이 만들어 진다.
		// 그 실행파일을 클릭하면 프로그램이 실행되면서 실행이 되는 프로그램을 런타임단계라고 한다.
		//         컴파일 ->       실행파일(exe)       -> 런타임
		// (프로그램이 만들어지는 과정)        (프로그램이 실행되는 과정)
		// 컴파일타임은 컴파일 단계에서 숫자의 결과물 함수의 결과물이 결정된다.
		// 런타임 까지 간다고하면 뒷부분에 결정된다.
		// 이두가지가 큰차이가 있다.
		// 게임을 만든다고 할때 그 게임이 빠르게 실행되어야 한다고 하면
		// 컴파일이 오래 걸린다고 하더라도 런타임에서 빠르게 동작하면 상관이 없다.

		// 예를 들어보자.
		int val1 = SqrRunTime(10); 
		// 이함수가 만들어질 때는 어떤값으로 들어올지 예측할 수 없기 때문에 int val1 = 100; 으로 바로 치환할 수 없다.
		// 실제로 실행될 때는 SqrRunTime() 호출되면서 스택프레임에 10이라는 값이 들어가고 매개변수를 받아 10*10을 계산후
		// 결과를 스택에 다시 넣어 결과물을 최종적으로 val1에 넣는다. 이는 다 런타임에 일어나는 버전이다. 
		
		
		int val2 = SqrRunOrCompileTime(10);
		// constexpr : 최대한 컴파일 타임에 할 수 있으면 해라.
		// val2는 같은 경우 이 변수가 컴파일 타임에 완료되라는 힌트를 넣지 않았기 때문에 이 함수는 컴파일타임이 아니라 런타임으로 코드를 만들어 줄 수 있다. 
		// constexpr int val2로 한다면 이 변수는 무조건 컴파일 타임에 만들어 주라는 의미이다.
		// 즉, constexpr가 변수앞에 붙으면 무조건 컴파일 타임, 함수 앞에 붙으면 컴파일타임or런타임 둘다 가능하기에 최대한 좋은 쪽으로 해라다.

		int val3 = SqrCompileTime(10);
		// consteval : 무조건 컴파일타임으로 만들어라.
		// 컴파일 타임에 만들었다는 것은 위 코드가 결국 int val3 = 100; 처럼 바뀐 것이다.


		int a = 10;
		int val11 = SqrRunTime(a);
		int val22 = SqrRunOrCompileTime(a); // 만약 constexpr int val22 = SqrRunOrCompileTime(a);이라면 이것은 오류
		//int val33 = SqrCompileTime(a);
		// a가 고정된 값이 아니라 런타임에서 a라는 값이 확정되기 때문에 
		// SqrCompileTime는 오류이다.
	

		// enum같은 경우에는 enum에 들어가 있는 값은 컴파일타임에 무조건 확정되어야 한다.
		enum
		{
			//VAL_1 = SqrRunTime(10), // 이것은 런타임에 확정되기 때문에 이 문법은 오류다.
			VAL_2 = SqrRunOrCompileTime(10),
			VAL_3 = SqrCompileTime(10),
		};
	
		
		// consteval 특징
		// - 조건부 jump, loop 가능
		// - 다수의 명령어로 구성 가능
		// - constexpr 함수 호출 가능
		// - static, thread_local 안 됨
		// - try, goto 안됨
		// - non-consteval 함수 호출 안됨
		// - non-constexpr 데이터 사용 안됨
	}

	// 변수 (const vs constexpr vs constinit)
	{
		// const (컴파일타임/런타임 (상관없음) + constness 있어야 한다. 상수성을 보장해야한다.)
		const int constIntVal = SqrRunTime(10); 
		//constIntVal++;
		// 컴파일타임에 만들어지거나 런타임에 만들어져야 한다는 조건을 강제하는 것이아닌 이 숫자는 변하면 안된다는 것을 의미. 
		// 상수성을 보장해야 한다.
		// const 변수의 초기화는 런타임까지 지연시킬 수 있다.

		// constexpr (컴파일타임 +  constness 있음)
		// 런타임 허용x, 컴파일타임에 결과가 확정되어야 하며 상수성을 보장해야 한다.
		// constexpr 변수는 반드시 컴파일 타임에 초기화가 되어야 한다.
		constexpr int constExprVal = SqrRunOrCompileTime(10);
		//constExprVal++;

		// constinit 특징 (컴파일 타임 + constness 없음 + static/thread_local)
		// - global 변수, static 변수, thread_local 변수를 대상으로 사용
		// ---- 프로그램 시작시 메모리 할당, 프로그램이 끝나면 메모리 해제
		// ---- thread_local 변수는 thread에 종속적, 특정 thread가 해당 데이터를 사용할 때 생성된다.

		constinit thread_local int constInitVal = SqrRunOrCompileTime(10); // constinit은 정적 또는 스레드 저장 기간 변수에만 유효함
		constInitVal++;

		constexpr thread_local int constExprVal1 = SqrRunOrCompileTime(10);
		//constExprVal1++;
	}
}