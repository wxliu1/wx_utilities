
/*
 C++11 chronoͷ�ļ��ṩ��3����׼ʱ�ӿ���������ʱ��

system_clock - ϵͳ�ṩ��ʵʱʱ��
high_resolution_clock - ��ǰϵͳʱ��������̵�ʱ��
steady_clock - ���ᱻ�����ĵ���ʱ��

�������Ҫ����ĳ�δ����ִ��ʱ�䣬�������Ӧ��ʹ��steady_clock������һ�����ᱻϵͳ�����ĵ���ʱ�ӡ�chrono����������ʱ��ż���ᱻ�������������������ʱ���t0 < t1�Ĳ�ֵ��������������

chronoͷ�ļ��ṩ��һЩ�������鿴ʱ�ӵľ��ȣ�����ʱ�ӵ��ض�ʵ���Ƿ��ȶ�(����������)����Ϊ�ض�ʱ�ӵ�ʵ��ϸ�������ڱ������Լ�����ϵͳ�����Բ�����Щ�������Ǻõģ�
*/

/*
Ϊ�˲���һ�δ����ִ��ʱ�䣬���ǿ���ʹ��now()������
 auto start = chrono::steady_clock::now();

 //
 //  Insert the code that will be timed
 //

 auto end = chrono::steady_clock::now();

 // Store the time difference between start and end
 auto diff = end - start;


 �������Ҫ��ӡstart��end�Ĳ�ֵ�������ʹ�ã�
 cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;

 ������ϲ�����룬��ʹ�ã�
 cout << chrono::duration <double, nano> (diff).count() << " ns" << endl;

 diff������ֵ���Ա��ضϳ�������������£�
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
// ���ϴ�����Mac OSX��clang-4.1���룬������£�
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