module; // global module fragment

// ���� �ܺ� ��� �߰�
#include <vector>

// module ����
export module math;

// import module...
export import math.time; // submodule ����, math.time�� import�ؼ� �ٽ� math ��⿡ �����ؼ� export

// ��� ��� ����

// 1) �Լ� �տ��ٰ� export �����ϴ� ���
export int Add(int a, int b)
{
	return a + b;
}

// 2) export�ϰ� ���� �Լ����� ���� �����ִ� ���
export
{
	void TestExport()
	{

	}
}

// 3) namespace�� �����ϴ� ���
export namespace math
{
	void TestExport2()
	{

	}
}