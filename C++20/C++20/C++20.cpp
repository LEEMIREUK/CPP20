#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <atomic>
#include <thread>
#include <semaphore>
#include <latch>
#include <barrier>
#include <mutex>
#include <syncstream>
using namespace std;

// synchronized output

void ThreadMain(int threadId)
{
	while(true)
	{
		// accumulate output in an internal buffer and write their content in an atomic step
		std::osyncstream syncStream(std::cout);
		cout << format("Hi ! I am thread {}", threadId) << endl;
		this_thread::sleep_for(1ms);
	}

	// 원래 cout이 thread-safe를 해주지만 출력되는 것을 보면
	// 결과물을 보면 전체 문자열이 출력하고 다음줄에 출력되는것이 대부분은 되지만
	// 안되는 경우가 있다.

	// 이것을 해결하는 방법으로는 여러가지가 있다.
	// 로그만 전용으로 호출하는 스레드를 할당해서 로그를 찍을 때는 항상 그 스레드에게 일감을 주는 방식으로 할 수 있다.
	// 로그는 한 스레드만 담당하는 느낌으로 할 수 있다.

	// 또는 lock을 거는 방법도 있다.
	// 하지만 이것은 비효율적인 방법이다.

	// 그래서 결과적으로 C++20에 추가된 기능이 있다.
	// std::osyncstream

}

int main()
{
	// 싱크를 맞춰서 출력하는 방법을 알아보자.
	
	vector<jthread> threads;

	for (int i = 0; i < 10; ++i)
	{
		threads.push_back(jthread(ThreadMain, i));
	}

	return 0;
}