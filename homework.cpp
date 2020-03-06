// homework.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<string>
#include<D:\C++ program\homework\homework\big_number_f.h>


// 成员函数定义
string f(int x)
{
	string a = "1", b = "1", c;
	for (int i = 2; i <= x; i++) {
		c = plus_pos(a, b);
		a = b, b = c;
	}
	return a;
}
int main()
{
	for (int i = 1; i <= 200; i++)
	{
		cout << "Fibonacci.of(" << i << ")==" << f(i) << endl;
	}
	return 0;
}


