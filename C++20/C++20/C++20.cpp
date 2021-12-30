#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <atomic>
#include <thread>
#include <semaphore>
using namespace std;

// semaphore

counting_semaphore<1> sem(0);
vector<int> vec;

void PrepareWork()
{
	vec.insert(vec.end(), { 1,2,3,4,5 });
	this_thread::sleep_for(1s);

	cout << "데이터 준비됨" << endl;
	sem.release();
}

void CompleteWork()
{
	cout << "데이터 기다리는중..." << endl;
	sem.acquire();

	cout << "데이터 출력중... " << endl;

	for (auto n : vec)
		cout << n << endl;
}

int main()
{
	// mutex
	// 화장실 키
	// [키]
	// 상호베타적인 특성을 보장하기 위해서 사용하는게 mutex다

	// semaphore
	// 화장실
	// [키][키][키]
	// mutex와 같지만 최대 카운터가 1이 아니라 지정할 수 있는 n개이다.
	
	//counting_semaphore<3>
	//binary_semphore = counting_semaphore<1>

	//max(); // 최대 카운터 값
	//acquire(); // counter를 1만큼 감소 (counter = 0 이면 양수가 될 때까지 대기한다.)
	//release(update = 1); // counter를 update만큼을 증가시킨다. (대기하던 쓰레드가 있으면 풀어줌)
	//try_acquire(); // counter가 0보다 크면 1 감소하려고 시도
	//try_acquire_for(relTime); // 최대 relTime만큼 counter를 1감소하려고 시도
	//try_acquire_until(absTime); // 최대 absTime까지 counter를 1감소하려고 시도

	thread t1(PrepareWork);
	thread t2(CompleteWork);

	t1.join();
	t2.join();

	return 0;
}