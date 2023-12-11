
/*


template<
    class Rep,
    class Period = std::ratio<1> // ��λΪ��
> class duration;

Rep���������˿��Դ����ʱ�䵥λ�����ͣ�����Ϊfloat, int, int64�ȵȣ����Ϊfloat��ʾ���Դ���ʱ�䵥λ��һ���֣����紫��1.2��ʾ1.2����ʱ�䵥λ��
Period����������ʱ�䵥λ������Ϊ΢�룬���룬�룬���ӣ�Сʱ�ȣ����������Զ���ĵ�λ������Ϊstd::ratio����


typedef chrono::duration<long long, nano> nanoseconds; // ���� 
typedef chrono::duration<long long, micro> microseconds; // ΢�� 
typedef chrono::duration<long long, milli> milliseconds; // ���� 
typedef chrono::duration<long long> seconds; // �� 
typedef chrono::duration<int, ratio<60> > minutes; // ���� 
typedef chrono::duration<int, ratio<3600> > hours; // Сʱ

�������϶������ǿ��Է���std::chrono::microseconds�����е�Rep��������long long��Period������milli��

ע����Ϊstd::chrono::microseconds�����е�Rep��������long long, ���ǲ���ͨ�����·���������100.5����
std::this_thread::sleep_for(std::chrono::microseconds(100.5)); // ���Ͳ�ƥ�䣬�ᱨ�������
���������100.5���룬���ǿ�����ôд��
std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(100.5f));



auto tp = std::chrono::high_resolution_clock::now();
std::cout << tp.time_since_epoch().count() << std::endl;
�����������һ���Ƚ�С�����֣�high_resolution_clock�ľ��������룬����������ôС�����֡�


1 system_clock
struct system_clock
{	// wraps GetSystemTimePreciseAsFileTime/GetSystemTimeAsFileTime
typedef long long rep;
typedef ratio_multiply<ratio<_XTIME_NSECS_PER_TICK, 1>, nano> period;
typedef chrono::duration<rep, period> duration;
typedef chrono::time_point<system_clock> time_point;
static constexpr bool is_steady = false;
����system_clock���������epoch����1970-01-01 00:00:00 UTC����̶���1��tick��Ҳ����_XTIME_NSECS_PER_TICK���롣

2 high_resolution_clock
typedef steady_clock high_resolution_clock;
high_resolution_clockʵ���Ϻ�steady_clockһ����

3 steady_clock

struct steady_clock
{	// wraps QueryPerformanceCounter
typedef long long rep;
typedef nano period;
typedef nanoseconds duration;
typedef chrono::time_point<steady_clock> time_point;
static constexpr bool is_steady = true;

��Ա����	����
rep	��ʾʱ��ʱ���мƴ�������������
period	��ʾʱ�Ӽƴ����ڵ� std::ratio ���ͣ���λΪ��
duration	std::chrono::duration<rep, period>
time_point	std::chrono::time_point<std::chrono::steady_clock>


steady_clock�Ŀ̶���1���룬��㲢��1970-01-01 00:00:00 UTC��һ����ϵͳ����ʱ�䣬���������Ĺؼ���
steady_clock��������Ϊ�˵õ�����ϵͳʱ���޸Ķ��仯��ʱ���������Է�����õ�����ʱ����÷����Ǵ���ġ�
steady_clock��û��to_time_t()��ʵ�ֵģ���system_clock���еġ�

����ʱ������ʲôʱ��
system_clock��������Ҫ�õ�����ʱ��ĳ���
auto tp = std::chrono::system_clock::now();
std::time_t tt = std::chrono::system_clock::to_time_t(tp);
std::cout << tt << "seconds from 1970-01-01 00:00:00 UTC" << std::endl;

steady_clock��������Ҫ�õ�ʱ�������������ʱ����������Ϊ�޸�ϵͳʱ�����Ӱ��ĳ���
auto tp1 = std::chrono::steady_clock::now();
//do something
auto tp2 = std::chrono::steady_clock::now();
std::cout << std::chrono::duration_cast<std::chrono::microseconds>(tp2 - tp1).count() << "microseconds" << std::endl;


high_resolution_clock��high_resolution_clock��system_clock��steady_clock֮һ���������ʹ��

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
        // ��¼��ʼʱ��
        auto start = std::chrono::steady_clock::now();
        // ��һЩ����
        std::vector<int> v(size, 100);
        sink = std::accumulate(v.begin(), v.end(), 0u); // ȷ���丱ЧӦ
        // ��¼����ʱ��
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
    // ����ʾ��
    for (auto size = 1ull; size < 1000000000ull; size *= 100)
    {
        // ��¼��ʼʱ��
        auto start = std::chrono::steady_clock::now();
        // ��һЩ����
        std::vector<int> v(size, 100);
        sink = std::accumulate(v.begin(), v.end(), 0u); // ȷ���丱ЧӦ
        // ��¼����ʱ��
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << std::fixed << "Time to fill and iterate a vector of "
            << size << " ints : " << diff.count() << " s\n";
    }

    // ����100����
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // or 
    std::this_thread::sleep_for(std::chrono::duration<long long, std::milli>(100));
    // or   
    // typedef ratio<1, 1000> milli; 
    std::this_thread::sleep_for(std::chrono::duration<long long, std::ratio<1, 1000> >(100));

    // ����ת��Ϊ����
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::minutes(3));
    std::cout << "3 minutes equals to " << ms.count() << " milliseconds\n";
    std::cin.get();


    // �Զ��嵥λת��
    three_seconds s = std::chrono::duration_cast<three_seconds>(one_tenth_seconds(3));
    std::cout << "3 [1/10 seconds] equal to " << s.count() << " [3 seconds]\n";
    std::cin.get();

    return 0;
}

