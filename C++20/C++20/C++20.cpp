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
using namespace std;

// jthread

mutex mut;

atomic<bool> endFlag;

void ThreadMain()
{
	mut.lock();
	while (true)
	{
		// 오래 걸리는 작업
		if (endFlag)
			break;
	}
	mut.unlock();
}

void JThreadMain(std::stop_token stoken)
{
	while (true)
	{
		// 오래 걸리는 작업
		// 토근을 확인해서 멈춰달라고 요청이 왔는지 체크한다.
		if(stoken.stop_requested())
			break;
	}
}

int main()
{
	// C++11에서 thread를 사용할 때
	//thread t1(ThreadMain);
	//t1.join();
	// join을 하지 않으면 
	// 만약 밖에서 terminate같은 함수에 의해 이 스레드가 강제로 종료되었다면
	// 이 lock은 영영 풀어지지 않고 unlock을 안해주기 때문에 전체 시스템에 문제가 될수 있다.
	// 즉, 강제로 다른 스레드를 꺼버리는 작업은 위험한 작업이다.
	// 이것을 방지하고자 join을 한다.

	//vector<thread> threads;
	//for (int i = 0; i < 5; ++i)
	//	threads.push_back(thread(ThreadMain));

	//for (int i = 0; i < 5; ++i)
	//	threads[i].join();

	// 위 코드는 가독성이 별로 안좋고 비효율적으로 코드가 작성된것 같기에
	// C++20에서 자동으로 join이 되는 스레드를 새로 추가되었다.
	
	// Joining Thread
	//jthread jt(ThreadMain);
	jthread jt(JThreadMain);
	// 이렇게 해주면 알아서 소멸이 될때 join을 해준다.
	// 상대방이 종료해줘야 빠져나올 수 있기 때문에
	// 위 스레드는 종료되지 않는다.

	
	// get_stop_source
	// get_stop_token
	// request_stop

	// cooperative interruption
	// 서로 협력해서 멈춘다는 의미
	// 예를 들어 여러개의 스레드를 동시에 멀티스레드 환경에서 작업하고 있는 상황이고
	// 작업하다가 특정 상황이 되면 모든 스레드에게 종료하는 신호를 보내야 한다고 가정해보자.
	// 플래그를 이용해서 신호를 보낼 수 있을 것이다.
	endFlag = false;
	// 다양한 방법이 있다.
	

	// 요청을 한 것인데 상대방이 무시하면 아무일도 일어나지 않는다.(강제성이 없다.)
	jt.request_stop();

	// 원래 source -> token 추출 -> 새로운 스레드에 전달
	// 하지만

	// 결론적으로 복잡한 코드를 사용하지 않고 jthread를 사용하면 필요한 것을 알아서 사용해준다.

	return 0;
}