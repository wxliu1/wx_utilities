
// time use

/*
特别说明：C/C++ 宏定义中#、##、#@的含义
一个#的作用就是把后面的参数当做一个字符串，也就是说等同于把后面的宏变量加上双引号
两个##是连接符，即把两个宏变量拼接到一起

#：表示将对应变量字符串化，简单来说就是相当于在宏变量的两边各加上一个双引号使其变成一个字符串

##：表示把宏参数名与宏定义代码序列中的标识符连接在一起，形成一个新的标识符。可以是符号拼符号，可以是数字拼符号，可以是数字拼数字

#@：表示将单字符标记符变换为单字符，即加单引号。例如：

#define A(x) #@x

则A(a)即’a’，A(1)即’1’，但A(abc)却不甚有效。
有些地方会提到#@符号，可以把后面的宏变量字符化，也就是说加上单引号’’，但是不推荐使用这个符号，主要是很多平台下都不支持。



#include <stdio.h>
#define trace(x, format) printf(#x " = %" #format "\n", x)
#define trace2(i) trace(x##i, d)

int main(int argc, char* argv[])
{
	int i = 1;
	char *s = "Hello";
	float y = 2.0;

	trace(i, d);                // 相当于 printf("i = %d\n", i)
	trace(y, f);                // 相当于 printf("y = %f\n", y)
	trace(s, s);                // 相当于 printf("s = %s\n", s)

	int x1 = 1, x2 = 2, x3 = 3;
	trace2(1);                  // 相当于 trace(x1, d)
	trace2(2);                  // 相当于 trace(x2, d)
	trace2(3);                  // 相当于 trace(x3, d)

	return 0;
}

*/

#include <chrono>


#define TIMERSTART(tag) auto tag##_start = std::chrono::steady_clock::now(),tag##_end = tag##_start

#define TIMEREND(tag) tag##_end = std::chrono::steady_clock::now()

#define DURATION_s(tag) printf("%s costs %d s\n",#tag,std::chrono::duration_cast<std::chrono::seconds>(tag##_end - tag##_start).count())

#define DURATION_ms(tag) printf("%s costs %d ms\n",#tag,std::chrono::duration_cast<std::chrono::milliseconds>(tag##_end - tag##_start).count());

#define DURATION_us(tag) printf("%s costs %d us\n",#tag,std::chrono::duration_cast<std::chrono::microseconds>(tag##_end - tag##_start).count());

#define DURATION_ns(tag) printf("%s costs %d ns\n",#tag,std::chrono::duration_cast<std::chrono::nanoseconds>(tag##_end - tag##_start).count());

int main2(int argc, char* argv[])
{
	// usage:
	TIMERSTART(for_loop);

	//for (int i = 0; i < 100000; i++)
	for (int i = 0; i < 100000000; i++)
	{
		i*i;

	}

	TIMEREND(for_loop);
	DURATION_ms(for_loop);
	DURATION_us(for_loop);
	DURATION_ns(for_loop);

	return 0;
}
