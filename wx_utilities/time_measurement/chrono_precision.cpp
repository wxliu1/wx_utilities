// time_measurement.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// chrono_precision.cpp

/*
C++11 中提供了一个计时的标准库 <chrono>;
里面有三种时钟 clock : steady_clock， system_clock 和 high_resolution_clock;

区别:
steady_clock 是单调的时钟，相当于教练手中的秒表；只会增长，适合用于记录程序耗时；
system_clock 是系统的时钟；因为系统的时钟可以修改；甚至可以网络对时； 所以用系统时间计算时间差可能不准。
high_resolution_clock 是当前系统能够提供的最高精度的时钟；它也是不可以修改的。相当于 steady_clock 的高精度版本。
在 参考链接[2] 中提供了代码，可以查看自己的机器上三种时钟的时间精度。

建议:
以下是 stackoverflow 上一个大佬给出的建议difference between steady clocl vs system clock

尽量不要使用 count() 方法
尽量不要使用 time_since_epoch()
理由是： 提供了类型安全的机制防止用户进行单位换算的时候出错；但是这两个函数是例外的，起到“紧急出口的作用”，

Such emergencies arise when (for example) the committee neglects to give you all the tools you need to get the job done (such as I/O) for the types, or such as the need to interface with some other timing API via integers

在I/O 或者与其他 通过整数传参数的时间函数接口中使用。


参考:
https://stackoverflow.com/questions/31552193/difference-between-steady-clock-vs-system-clock
C++ Stardard Library:A Tutorial and Reference, 2nd Edition https://www.informit.com/articles/article.aspx?p=1881386&seqNum=2

*/


// copied from http://www.informit.com/articles/article.aspx?p=1881386&seqNum=2;

// Author: Nicolai M. Josuttis


#include <chrono>

#include <iostream>

#include <iomanip>

// ns（nanosecond）：纳秒，时间单位。一秒的十亿分之一，等于10的负9次方秒（1 ns = 1e-9 s）。
// 1 ns = 1e-6 ms

template <typename C>

void printClockData()

{

	using namespace std;


	cout << "- precision: ";

	// if time unit is less or equal one millisecond

	typedef typename C::period P;// type of time unit

	if (ratio_less_equal<P, milli>::value) {

		// convert to and print as milliseconds

		typedef typename ratio_multiply<P, kilo>::type TT;

		cout << fixed << double(TT::num) / TT::den

			<< " milliseconds" << endl;

	}

	else {

		// print as seconds

		cout << fixed << double(P::num) / P::den << " seconds" << endl;

	}

	cout << "- is_steady: " << boolalpha << C::is_steady << endl;

}


int main1()

{

	std::cout << "system_clock: " << std::endl;

	printClockData<std::chrono::system_clock>();

	std::cout << "\nhigh_resolution_clock: " << std::endl;

	printClockData<std::chrono::high_resolution_clock>();

	std::cout << "\nsteady_clock: " << std::endl;

	printClockData<std::chrono::steady_clock>();


#ifdef _WIN32

	system("pause");

#endif

	return 0;

}


//system_clock:
//
//-precision : 0.000100 milliseconds
//
//- is_steady : false
//
//
//high_resolution_clock :
//
//	-precision : 0.000001 milliseconds
//
//	- is_steady : true
//
//
//	steady_clock :
//
//	-precision : 0.000001 milliseconds
//
//	- is_steady : true



//#include <iostream>

//int main()
//{
//    std::cout << "Hello World!\n";
//}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
