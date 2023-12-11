
/*
 C++11 chrono头文件提供了3个标准时钟可以用来计时：

system_clock - 系统提供的实时时钟
high_resolution_clock - 当前系统时钟周期最短的时钟
steady_clock - 不会被调整的单调时钟

如果你想要测量某段代码的执行时间，你基本上应该使用steady_clock，它是一个不会被系统调整的单调时钟。chrono的其他两个时钟偶尔会被调整，因此连续的两个时间点t0 < t1的差值并不总是正数。

chrono头文件提供了一些函数来查看时钟的精度，给定时钟的特定实现是否稳定(即不被调整)。因为特定时钟的实现细节依赖于编译器以及操作系统，所以测试这些属性总是好的：
*/

/*
为了测量一段代码的执行时间，我们可以使用now()函数：
 auto start = chrono::steady_clock::now();

 //
 //  Insert the code that will be timed
 //

 auto end = chrono::steady_clock::now();

 // Store the time difference between start and end
 auto diff = end - start;


 如果你想要打印start和end的差值，你可以使用：
 cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;

 如果你更喜欢纳秒，你使用：
 cout << chrono::duration <double, nano> (diff).count() << " ns" << endl;

 diff变量的值可以被截断成整数，结果如下：
 diff_sec = chrono::duration_cast<chrono::nanoseconds>(diff);
cout << diff_sec.count() << endl;
*/

#include <iostream>
#include <chrono>

using namespace std;


int main3() 
{
    cout << "system_clock" << endl;
    cout << chrono::system_clock::period::num << endl;
    cout << chrono::system_clock::period::den << endl;
    cout << "steady = " << boolalpha << chrono::system_clock::is_steady << endl << endl;

    cout << "high_resolution_clock" << endl;
    cout << chrono::high_resolution_clock::period::num << endl;
    cout << chrono::high_resolution_clock::period::den << endl;
    cout << "steady = " << boolalpha << chrono::high_resolution_clock::is_steady << endl << endl;

    cout << "steady_clock" << endl;
    cout << chrono::steady_clock::period::num << endl;
    cout << chrono::steady_clock::period::den << endl;
    cout << "steady = " << boolalpha << chrono::steady_clock::is_steady << endl << endl;

    auto start = chrono::steady_clock::now();
    for (int i = 0; i < 100000000; i++)
    {
        i* i;

    }
    auto end = chrono::steady_clock::now();
    auto diff = end - start;

    cout << chrono::duration <double, milli>(diff).count() << " ms" << endl;
    cout << chrono::duration <double, nano>(diff).count() << " ns" << endl;

    //auto diff_sec = chrono::duration_cast<chrono::nanoseconds>(diff);
    auto diff_sec = chrono::duration_cast<chrono::milliseconds>(diff);
    cout << diff_sec.count() << endl;


    typedef std::chrono::duration<double>           dd1;
    typedef std::chrono::duration<int64_t, std::ratio<1, 1000000>> dd2;
    //std::chrono::duration_cast<dd>(_end - _begin);
    auto diff1 = std::chrono::duration_cast<dd1>(diff);
    auto diff2 = std::chrono::duration_cast<dd2>(diff);
    cout << "diff1:" << diff1.count() << " seconds" << std::endl << "diff2:" << diff2.count() << " microseconds" << std::endl;

    return 0;
}
/*
// 以上代码在Mac OSX用clang-4.1编译，输出如下：
system_clock
1
1000000
steady = false

high_resolution_clock
1
1000000000
steady = true

steady_clock
1
1000000000
steady = true
*/