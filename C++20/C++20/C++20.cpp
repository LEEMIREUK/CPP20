#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;

// Calendar 

using namespace chrono;

int main()
{
	// C++에 추가된 Time 라이브러리
	// - time point
	// - time duration
	// - clock


	// C++11 chrono
	// C++20 calendar, time_zone


	// - calendar

	// C++20
	// hh_mm_ss : duration since midnight, split into hours, minutes, seconds, fractional seconds  
	// 자정 12시 이후 경과된 시간을 몇시간 몇분 몇초 나눈다. (시간 + 분 + 초)

	auto timeOfDay = std::chrono::hh_mm_ss(10.5h + 32min + 1004s + 0.6s); // h, min, s 를 조합해서 시간 넣어줄 수 있다.

	//cout << timeOfDay << endl; // 11:18:44
	cout << timeOfDay.hours() << endl; // 11h
	cout << timeOfDay.minutes() << endl; // 18min
	cout << timeOfDay.seconds() << endl; // 44s
	cout << timeOfDay.subseconds() << endl; // 0.6s
	cout << timeOfDay.to_duration() << endl; // 총 더해진 시간 40724.6s

	// Calendar Data
	chrono::year_month_day ymd1{ year(2022), month(11), day(10) };
	chrono::year_month_day ymd2{ year(2022) / month(11) / day(10) };
	chrono::year_month_day ymd3{ 2022y, November, 10d };
	//cout << ymd1 << endl; // 2020-14-10


	// year / month / day
	// day / month / year
	// month / day / year 
	// 순서로 해도 상관없다.

	// 어떤 년도, 달의 마지막 날을 알고 싶다면? (28인지, 29, 30인지 31인지)
	std::chrono::year_month_day_last ymdl1 = 2022y / November / last;
	std::chrono::year_month_day_last ymdl2 = last / November / 2022y;
	std::chrono::year_month_day_last ymdl3 = November / last / 2022y;

	auto d1 = ymdl1.day();
	chrono::year_month_day ymd4{ ymdl1 };

	// 만약 어떤 년도, 달의 네번째 금요일은 무슨요일인지?
	std::chrono::year_month_weekday ymwkd1{ year(2022) / November / Friday[4] };
	chrono::year_month_day ymd5{ ymwkd1 };

	// 이전의 기능과 추가된 기능을 왔다갔다 사용 가능(변환)
	// timepoint
	time_point timePoint = chrono::sys_days(ymd1);

	// Cute Syntax
	// 2021y, 30d, January, February, ... December

	// Validation
	// 어떤 날짜, 어떤 연도 등이 잘못되었을 때
	std::chrono::day d{ 31 };
	d++;
	bool valid = d.ok(); // 32일은 유효하지 않은 day이기 때문에 .ok()로 유효한 날짜, 연도인지 체크할 수 있다.

	// Test
	auto leapYear2000{ year(2000) / 2 / 29 };
	auto leapYear2001{ year(2001) / 2 / 29 };
	auto leapYear2002{ year(2002) / 2 / 29 };

	bool valid2 = leapYear2000.ok(); // true
	bool valid3 = leapYear2001.ok(); // false
	bool valid4 = leapYear2002.ok(); // false

	// 두가지 날짜 사이의 시간차를 계산할 수 있다.
	auto now = std::chrono::system_clock::now();
	auto diff = floor<chrono::hours>(now) - sys_days(1997y / May / 27d);
	cout << diff << endl;

	// - time_zone

	// 온라인 게임은 다양한 나라에서 서비스할 수 있다.
	// 나라들마다 시차가 다른데 게임 이벤트의 경우 정해진 시간에 열리기 때문에 계산을 잘해야 한다. 까다롭다.
	// DB에 저장할 때에도 로컬시간을 저장할 지 UTC 시간을 저장할지 기준점이 달라진다.

	// UTC (Coordinated Universal Time 협정 세계 시) <-> Local Time (실행환경)
	// - 영국은 UTC+0.00 (Greenwich Mean Time, GMT)
	// - 한국은 UTC+9.00
	// - 뉴욕은 UTC-5:00

	cout << "UTC" << endl;
	auto utcTime = system_clock::now();
	//cout << utcTime << endl; // 현재 UTC시간 (영국시간을 기준이기 때문에 한국시간으로 변환하려면 +9시간을 더해야 한다.)


	// C++20 zoned_time
	cout << "Local" << endl;
	auto localTime = zoned_time(current_zone(), utcTime); // 현재 한국 시간
	auto localTime2 = zoned_time("Asia/Shanghai"s, utcTime);
	// cout << localTime << endl; 

	auto offset = localTime.get_info().offset;
	cout << offset << endl; // 몇시간 차이나는지 초로 반환

	// C++ 서버 <-> C# 클라
	// 서버에서 시간을 보내준다고 하면 어떻게 할까
	// UNIX Epoch (유닉스 시간)
	// 유닉스 시간은 시간을 나타내는 방식
	// POSIX 시간이나 Epoch 시간이라고 부르기도 한다.
	// 1970년 1월 1일 00:00::00 협정 세계시(UTC) 부터의 경과 시간을 초로 환산하여 정수로 나타낸 것이다.
	__int64 hoursSinceUtc = duration_cast<hours>(utcTime.time_since_epoch()).count();
	cout << "Hours : " << hoursSinceUtc << endl;
	__int64 utcEpoch = duration_cast<seconds>(utcTime.time_since_epoch()).count();
	cout << "Epoch : " << utcEpoch << endl;
	// 클라이언트에게 보내줄 때 유닉스 시간을 보내주면 서로 통신하기 편하다.
	// 유닉스 시간을 다시 필요에 따라 UTC시간으로 변환하면 되기 때문에
}