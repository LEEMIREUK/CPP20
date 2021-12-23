#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <coroutine>
#include "MyCoroutine.h"
using namespace std;

// Coroutine

// 유니티 = 코루틴
// - C#에서 있는 코루틴 문법을 유니티에서 적극적으로 채용해서 제공

struct CoroutineObject
{
	// 1) promise 객체는 다음과 같은 인터페이스를 제공해야 한다.
	// - 기본 생성자 : promise 객체는 기본 생성자로 만들어질 수 있어야 한다.
	// - get_return_object : 코루틴 객체를 반환 (resumable object)
	// - return_value(val) : co_return val에 의해 호출됨 (코루틴이 영구적으로 끝나지 않으면 없어도 됨)
	// - return_void() : co_return에 의해 호출됨 (코루틴이 영구적으로 끝나지 않으면 없어도 됨)
	// - yield_value(val) : co_yield에 의해 호출됨
	// - initial_suspend() : 코루틴이 실행 전에 중단/연기 될 수 있는지
	// - final_suspend() : 코루틴이 종료 전에 중단/연기 될 수 있는지
	// - unhandled_exception() : 예외 처리시 호출됨

	struct promise_type
	{
		CoroutineObject get_return_object() { return {}; }
		std::suspend_never initial_suspend() const noexcept { return {}; }
		std::suspend_never final_suspend() const noexcept { return {}; }
		void return_void() {}
		void unhandled_exception() {}
	};
};

CoroutineObject HelloCoroutine()
{

	// 여기서 co_yield를 했다면 yield_value(val)함수를 만들어줘야 한다.
	co_return;
}

Future<int> CreateFuture()
{
	co_return 2021;
}

Generator<int> GenNumbers(int start = 0, int delta = 1)
{
	int now = start;

	while (true)
	{
		co_yield now; // unity의 yield return
		now += delta;
	}
}

Job PrepareJob()
{
	// co_await [Awaitable]
	co_await std::suspend_never();	// 기다리지 않고 바로 가라는 의미
}

int main()
{
	// 어떤 함수가 코루틴이 되려면
	// - co_return
	// - co_yield
	// - co_await
	// 이 세개중 하나를 필수적으로 사용해야 한다.

	// C++에서 제공하는 것은
	// 코루틴을 사용할 수 있는 Framework를 제공한다.
	// 3가지 요소로 구성
	// - promise 객체
	// - 코루틴 핸들 (밖에서 코루틴을 resume / destroy 할 때 사용. 일종은 리모컨)
	// - 코루틴 프레임 (promise 객체, 코루틴에서 내부적으로 사용하는 인자 등을 포함하는 heap 할당 객체)
	// 함수를 호출할 때 스택 프레임이 만들어지는 것처럼 코루틴을 사용할 때 코루틴 프레임이 만들어진다. (heap에 할당)


	// 하나의 의사코드(흐름)
	// co_yield, co_await, co_return을 함수 안에서 사용하면 그 함수는 코루틴이 된다.
	/*{
		Promise prom; (get_return_object)
		co_await prom.initial_suspend();
		try
		{
			// co_return, co_yield, co_await을 포함하는 코드
		}
		catch(...)
		{
			prom.unhandled_exception();
		}
		co_await prom.final_suspend();
	}*/

	// co_await 플로우
	/*{
		if awaitable.await_ready() returns false;
			suspend coroutine
			awaitable.await_suspend(handle) returns:
				void:
					awaitable.await_suspend(handle);
					coroutine keeps suspended
					return to caller
				bool:
					bool result = awaitable.await_suspend(handle);
					if (result)
						coroutine keeps suspended
						return to caller
					else
						return awaitable.await_resume()
				another coroutine handle:
					anotherCoroutineHandle = awaitable.await_suspend(handle);
					anotherCoroutineHandle.resume();
					return to caller;
		return awaitable.await_resume();
	}*/

	HelloCoroutine();

	auto future = CreateFuture();

	cout << future.get() << endl;

	auto numbers = GenNumbers(0, 1);
	for (int i = 0; i < 20; ++i)
	{
		numbers.next();

		cout << " " << numbers.get();
	}

	auto job = PrepareJob();

	job.start();
}