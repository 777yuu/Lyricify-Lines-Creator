/************************************************************************
 * Filename:    TaskHelper.h
 * Description: ��������ඨ��
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

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
