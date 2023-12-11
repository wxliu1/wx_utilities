
// time use

/*
�ر�˵����C/C++ �궨����#��##��#@�ĺ���
һ��#�����þ��ǰѺ���Ĳ�������һ���ַ�����Ҳ����˵��ͬ�ڰѺ���ĺ��������˫����
����##�����ӷ����������������ƴ�ӵ�һ��

#����ʾ����Ӧ�����ַ�����������˵�����൱���ں���������߸�����һ��˫����ʹ����һ���ַ���

##����ʾ�Ѻ��������궨����������еı�ʶ��������һ���γ�һ���µı�ʶ���������Ƿ���ƴ���ţ�����������ƴ���ţ�����������ƴ����

#@����ʾ�����ַ���Ƿ��任Ϊ���ַ������ӵ����š����磺

#define A(x) #@x

��A(a)����a����A(1)����1������A(abc)ȴ������Ч��
��Щ�ط����ᵽ#@���ţ����԰Ѻ���ĺ�����ַ�����Ҳ����˵���ϵ����š��������ǲ��Ƽ�ʹ��������ţ���Ҫ�Ǻܶ�ƽ̨�¶���֧�֡�



#include <stdio.h>
#define trace(x, format) printf(#x " = %" #format "\n", x)
#define trace2(i) trace(x##i, d)

int main(int argc, char* argv[])
{
	int i = 1;
	char *s = "Hello";
	float y = 2.0;

	trace(i, d);                // �൱�� printf("i = %d\n", i)
	trace(y, f);                // �൱�� printf("y = %f\n", y)
	trace(s, s);                // �൱�� printf("s = %s\n", s)

	int x1 = 1, x2 = 2, x3 = 3;
	trace2(1);                  // �൱�� trace(x1, d)
	trace2(2);                  // �൱�� trace(x2, d)
	trace2(3);                  // �൱�� trace(x3, d)

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
