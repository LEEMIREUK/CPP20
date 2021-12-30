#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <atomic>
#include <thread>
using namespace std;

// atomic

int main()
{
	// atomic_ref
	int value = 0;

	//int& ref = value;
	atomic_ref<int> ref(value);

	// 멀티쓰레드 환경에서
	thread t1([&ref]()
		{
			for (int i = 0; i < 1000000; ++i)
				ref++;
		}
	);

	thread t2([&ref]()
		{
			for (int i = 0; i < 1000000; ++i)
				ref--;
		}
	);

	t1.join();
	t2.join();


	// 멀티쓰레드 환경이기 때문에 값이 0이 되지 않는다.
	// atomic_ref를 사용하면 0이된다.
	cout << ref << endl;

	
	// atomic shared_ptr

	// shared_ptr (C++ 스마트 포인터 권장)
	// [resource(data)][control block﻿(ref count)]
	// 
	// - control block은 Thread-Safe한게 맞다.
	//

	class User
	{
	public:
		int id = 0;
		int hp = 0;
	};

	shared_ptr<User> targetUser = make_shared<User>();


	targetUser = make_shared<User>();

	targetUser = make_shared<User>();

	// 교체하는 작업은(바꿔치기하는 것은) thread-safe하지 않다.
	// 그래서 C++20에서
	// atomic_shared_ptr과 atomic_weak_ptr이 제안되었다.
	// 문법 : atomic<shared_ptr<T>>, atomic<weak_ptr<T>> 
	// shared_ptr과 weak_ptr이 atmoic하게 활용할 수 있다
	atomic<shared_ptr<User>> atomicSharedPtr = make_shared<User>();
	//atomicSharedPtr.compare_exchange_strong()

	// LockFree 프로그래밍에서 유용
	// 일상에서는 잘 사용x
}