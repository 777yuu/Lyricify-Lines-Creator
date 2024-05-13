#pragma once

#include <chrono>
#include <future>
#include <thread>

class TaskHelper
{
public:
	/// <summary>
	/// ����������ָͣ��������
	/// �÷�: Delay(ms).wait();
	/// </summary>
	/// <param name="milliseconds">Ҫ��ͣ�ĺ�����</param>
	static std::future<void> Delay(int milliseconds);
};
