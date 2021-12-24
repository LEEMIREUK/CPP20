#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// Designated Initialization (지정 초기화)

struct Pos2D
{
    int x;
    int y;
};

class Pos3D
{
public:
    int x;
    int y;
    int z;
};

int main()
{
    // Aggreate Initialization
    // - 직접 만든 생성자가 없어야 함.
    // - 가상 함수가 없어야 함.
    // - private / protected / static인 데이터 변수는 안된다.
    Pos3D pos{ 1,2,3 };

    // ﻿Designated Initialization
    Pos2D pos2d{ .y = 2 };
    Pos3D pos3d{ .x = 2, .z = 3 };

    // Aggreate Initialization의 경우 다른 타입을 넣어주면 축소 변환을 해주지만
    // ﻿Designated Initialization의 경우 오류 출력
}