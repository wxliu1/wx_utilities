
/*


template<
    class Rep,
    class Period = std::ratio<1> // 单位为秒
> class duration;

Rep参数代表了可以传入的时间单位的类型，可以为float, int, int64等等，如果为float表示可以传入时间单位的一部分，比如传入1.2表示1.2倍个时间单位。
Period参数代表了时间单位，可以为微秒，毫秒，秒，分钟，小时等（或者其它自定义的单位，类型为std::ratio）。


typedef chrono::duration<long long, nano> nanoseconds; // 纳秒 
typedef chrono::duration<long long, micro> microseconds; // 微秒 
typedef chrono::duration<long long, milli> milliseconds; // 毫秒 
typedef chrono::duration<long long> seconds; // 秒 
typedef chrono::duration<int, ratio<60> > minutes; // 分钟 
typedef chrono::duration<int, ratio<3600> > hours; // 小时

根据以上定义我们可以发现std::chrono::microseconds定义中的Rep的类型是long long，Period类型是milli。

注：因为std::chrono::microseconds定义中的Rep的类型是long long, 我们不能通过如下方法来休眠100.5毫秒
std::this_thread::sleep_for(std::chrono::microseconds(100.5)); // 类型不匹配，会报编译错误。
如果想休眠100.5毫秒，我们可以这么写：
std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(100.5f));



auto tp = std::chrono::high_resolution_clock::now();
std::cout << tp.time_since_epoch().count() << std::endl;
上述代码输出一个比较小的数字，high_resolution_clock的精度是纳秒，不可能是这么小的数字。


1 system_clock
struct system_clock
{	// wraps GetSystemTimePreciseAsFileTime/GetSystemTimeAsFileTime
typedef long long rep;
typedef ratio_multiply<ratio<_XTIME_NSECS_PER_TICK, 1>, nano> period;
typedef chrono::duration<rep, period> duration;
typedef chrono::time_point<system_clock> time_point;
static constexpr bool is_steady = false;
对于system_clock，其起点是epoch，即1970-01-01 00:00:00 UTC，其刻度是1个tick，也就是_XTIME_NSECS_PER_TICK纳秒。

2 high_resolution_clock
typedef steady_clock high_resolution_clock;
high_resolution_clock实际上和steady_clock一样。

3 steady_clock

struct steady_clock
{	// wraps QueryPerformanceCounter
typedef long long rep;
typedef nano period;
typedef nanoseconds duration;
typedef chrono::time_point<steady_clock> time_point;
static constexpr bool is_steady = true;

成员类型	定义
rep	表示时钟时长中计次数的算术类型
period	表示时钟计次周期的 std::ratio 类型，单位为秒
duration	std::chrono::duration<rep, period>
time_point	std::chrono::time_point<std::chrono::steady_clock>


steady_clock的刻度是1纳秒，起点并非1970-01-01 00:00:00 UTC，一般是系统启动时间，这就是问题的关键。
steady_clock的作用是为了得到不随系统时间修改而变化的时间间隔，所以凡是想得到绝对时点的用法都是错误的。
steady_clock是没有to_time_t()的实现的，而system_clock是有的。

三种时钟用在什么时候
system_clock：用在需要得到绝对时点的场景
auto tp = std::chrono::system_clock::now();
std::time_t tt = std::chrono::system_clock::to_time_t(tp);
std::cout << tt << "seconds from 1970-01-01 00:00:00 UTC" << std::endl;

steady_clock：用在需要得到时间间隔，并且这个时间间隔不会因为修改系统时间而受影响的场景
auto tp1 = std::chrono::steady_clock::now();
//do something
auto tp2 = std::chrono::steady_clock::now();
std::cout << std::chrono::duration_cast<std::chrono::microseconds>(tp2 - tp1).count() << "microseconds" << std::endl;


high_resolution_clock：high_resolution_clock是system_clock或steady_clock之一，根据情况使用

*/

#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>

volatile int sink;
int main()
{
    for (auto size = 1ull; size < 1000000000ull; size *= 100)
    {
        // 记录开始时间
        auto start = std::chrono::steady_clock::now();
        // 做一些工作
        std::vector<int> v(size, 100);
        sink = std::accumulate(v.begin(), v.end(), 0u); // 确保其副效应
        // 记录结束时间
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << std::fixed << "Time to fill and iterate a vector of "
            << size << " ints : " << diff.count() << " s\n";
    }
}

#include <vector>
#include <numeric>
#include <iostream> 
#include <thread> 
#include <chrono> 

typedef std::chrono::duration<float, std::ratio<3, 1> > three_seconds;
typedef std::chrono::duration<float, std::ratio<1, 10> > one_tenth_seconds;

int main5()
{
    // 调用示例
    for (auto size = 1ull; size < 1000000000ull; size *= 100)
    {
        // 记录开始时间
        auto start = std::chrono::steady_clock::now();
        // 做一些工作
        std::vector<int> v(size, 100);
        sink = std::accumulate(v.begin(), v.end(), 0u); // 确保其副效应
        // 记录结束时间
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << std::fixed << "Time to fill and iterate a vector of "
            << size << " ints : " << diff.count() << " s\n";
    }

    // 休眠100毫秒
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // or 
    std::this_thread::sleep_for(std::chrono::duration<long long, std::milli>(100));
    // or   
    // typedef ratio<1, 1000> milli; 
    std::this_thread::sleep_for(std::chrono::duration<long long, std::ratio<1, 1000> >(100));

    // 分钟转换为毫秒
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::minutes(3));
    std::cout << "3 minutes equals to " << ms.count() << " milliseconds\n";
    std::cin.get();


    // 自定义单位转换
    three_seconds s = std::chrono::duration_cast<three_seconds>(one_tenth_seconds(3));
    std::cout << "3 [1/10 seconds] equal to " << s.count() << " [3 seconds]\n";
    std::cin.get();

    return 0;
}

