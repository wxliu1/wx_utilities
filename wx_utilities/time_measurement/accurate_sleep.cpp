
// std::chrono::steady_clock 实现精准休眠

#include <iostream>
#include <chrono>
#include <thread>
#include <ratio>
#include <cstdlib>

class timer
{
    typedef std::chrono::steady_clock::time_point   tp;
    //typedef std::chrono::duration<double>           dd;
    typedef std::chrono::steady_clock               sc;
    typedef std::chrono::duration<int64_t, std::ratio<1, 1000000>> dd; // 表示 1/1000000 秒,即微秒
private:
    tp _begin;
    dd _span;
public:
    int64_t decl = 0;
public:
    timer()
        : _begin(tp()), _span(dd(0)) {}
    void start()
    {
        _begin = sc::now();
    }

    void pause()
    {
        tp _end = sc::now();
        _span += std::chrono::duration_cast<dd>(_end - _begin);
    }

    void stop(std::string head = std::string(),
        std::string tail = std::string())
    {
        tp _end = sc::now();
        _span += std::chrono::duration_cast<dd>(_end - _begin);
        std::cout << head << _span.count() << " microseconds" << tail << std::endl;
        decl += _span.count();
        _span = dd(0);
    }
    ~timer()
    {}
};

int main4() {
    std::cout << "Hello, World!" << std::endl;
    timer t, timer; // 定义一个计时器

    int count = 0;
    int64_t real = 0;
    bool flag1 = false, flag2 = false;
    float k = 1.0;
    while (1) {
        count++;
        t.start(); // 开始计时
        if ((t.decl - real) > 0) { //1s
            //std::cout << "---1  k:" << k<< std::endl;
            if (!flag1) {
                k = 1.0;
                flag1 = true;
            }
            else {
                int n = ((t.decl - real) >= 100) ? (t.decl - real) : (100);
                k -= 0.001 * n * 0.01;
            }

            flag2 = false;
            std::this_thread::sleep_for(std::chrono::microseconds((int)(10000 * k)));
        }
        else if ((t.decl - real) < 0) { //1s
         //std::cout << "---2  k:" << k<< std::endl;
            if (!flag2) {
                k = 1.0;
                flag2 = true;
            }
            else {
                int n = ((real - t.decl) >= 100) ? (real - t.decl) : (100);
                k += 0.001 * n * 0.01;
            }

            flag1 = false;
            std::this_thread::sleep_for(std::chrono::microseconds((int)(10000 * k)));
        }
        else {
            flag1 = false;
            flag2 = false;
            k = 0.98;
            std::this_thread::sleep_for(std::chrono::microseconds((int)(10000 * k)));
        }

        timer.start();
        int randa = rand() % 10000;
        for (int i = 0; i < 400 * randa; i++);
        timer.stop(std::string("for takes "), std::string("-----"));

        t.stop(std::string("It takes "), std::string("."));
        real += 10000;
        std::cout << t.decl / count << ", decl:" << t.decl << ", real:" << real << ", count:" << count << ",k:" << k << ",randa:" << randa << std::endl;

    }

    return 0;
}