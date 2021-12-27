#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// Attribute
  
[[noreturn]]
int Func()
{
	return 10;
}

class Knight
{
public:
	[[nodiscard("생성자 버리지 마세요")]]
	Knight(int hp) : _hp(hp)
	{

	}
	
	int _hp;
};

enum class [[nodiscard("ErrorCode 사용하세요")]] ErrorCode
{
	None,
	Warning,
	Critical,
};

[[nodiscard]]
ErrorCode GetError()
{
	return ErrorCode::Critical;
}

int Sum(vector<int>& v)
{
	int ret = 0;

	for (int i = 0; i < v.size(); ++i)
	{
		// 최적화
		if (v[i] < 0)
		{
			[[likely]] // 컴파일러가 이쪽 조건문으로 올 확률이 높다는 것을 판별하여 코드 최적화를 할 수 있다.
			ret -= v[i];
		}
		else
		{
			ret += v[i];
		}
	}

	return ret;
}

struct Empty {};

struct NoUniqueAddress
{
	int d;

	[[no_unique_address]]
	Empty e;
};

int main()
{
	// [[noreturn]] C++11  : 함수가 return하지 않아야하는데 return하는 경우 경고 출력
	// [[deprecated]] C++14  : 어떤 함수를 더이상 사용하지 않는 경우 사용하게 되면 경고 출력
	
	int val = Func();
	
	// [[nodiscard]] C++17  : 반환하는 함수인데 사용되지 않을 때 경고출력
	// [[nodiscard("사유")]] C++20  : 사유를 적을 수 있게 되었다.
	// 생성자에서 [[nodiscard]]를 붙일 수 있게 되었다.
	// enumclass에도 [[nodiscard]]를 붙일 수 있게 되었다.

	// [[nodiscard]]를 여러개 사용하면 어디서 문제인지 잘 모른다.
	// 그때 사유를 잘 적으면 어떤 부분이 문제인지 알 수 있다.

	Knight(100);
	GetError();


	// [[likely]] / [[unlikely]]  : 일어날것 같다 / 일어나지 않을 것 같다. 힌트 
	// 즉, 어느쪽이 많이 일어날지 힌트를 줘서 최적화된 코드를 만들어준다.

	// [[no_unique_address]]  :  모든 객체들이 다 각기 다른 주소를 활용할 필요 없이
	// 공용으로 사용해도 된다는 힌트를 주고 있다.
	NoUniqueAddress n1, n2, n3;
	cout << &n1.e << endl;
	cout << &n2.e << endl;
	cout << &n3.e << endl;
}