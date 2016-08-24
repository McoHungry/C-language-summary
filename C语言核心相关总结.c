零：声明、定义、初始化 和 数据类型
	
	声明：extern 可以放在变量或者函数的前面，提示编译器如果遇到这个变量或者函数的时候，是在其他模块寻找。

		extern int a; // 我在b.c有个全局变量int a = 10,我可以在a.c里用这个方式声明这个全局变量，并不代表我重新定义了一个a，而是b.c的a

		extern int func(int a, float b); // 也是函数声明，意义等同于 上面的例子
		// 一般默认进行函数声明的时候，extern 可以省略的不写的。

	定义：没有加 extern 就是定义。定义后的变量是有存储空间的，可以获取到变量的地址。

		int a;
		int arr[10];

	初始化： 给一个没有值的变量，进行第一次赋值操作。
		int a = 10;
		float b;
		b = 3.14;

	数据类型：
	在C语言里，数据类型分为四大种：

	1. 基本类型：
					Linux64		Windows64 		linux32		Windows32
		(字符型)
		char			1			1				1			1

		(整型)
		short			2			2				2			2
		int				4			4				4			4
		long			8			4				4			4
		long long		8			8				8			8
		size_t			8			8				4			4

		(实型、浮点型)
		float			4			4				4			4
		double			8			8				8			8


	2. 构造类型：
		数组：[]; 存储了n个相同数据类型的数据。
			char str1[5] = "haha";
			char str2[5] = {'h', 'a', 'h', 'a', 'h'};

		结构体：struct;可以存储n个不相同的数据类型的数据。

		联合体/共同体：union;可以存储n个不相同的数据类型的数据，但是所有数据共享一块内存空间，这块空间的大小就是最大数据类型大小。

		枚举：enum;存储n个相同基本数据类型的数据，每次使用时候只能取出一个值，这个值大小是 sizeof(int);

	3. 指针类型：  32位下4个字节，64位下8个字节
		就是专门存储数据类型的地址，包括指针。
		int *p;			// 一级指针
		int a = 10;
		p = &a;
		int **p = &p;	// 二级指针
		char *str = "haha";	// 字符指针
		printf("%s\n", str);

		*(str + 1) = 'm';	// 这个是错误的，字符串在常量区，不允许修改里面的值。

	4. 空类型：
		void 普通变量： 表示这是一个空类型变量，不接受任何数据。
		void 函数：表示这个函数没有返回值。
		void 指针：表示可以接收任何类型的指针;


一、字符串函数： #include <string.h>

1 strlen(char *str);
	这个函数的返回值是一个字符串的有效长度(不包括'\0')；有别于 sizeof() 运算符;

2 strnlen(char *str, int maxlen);
	这个函数的返回值是maxlen长度以内、且不包括'\0'的长度。

3 strcat(char *str1, char *str2);
	将参数 str2 追加到 参数str1 后面，但是会覆盖 str1 最后 '\0';

4 strncat(char* str1, char* str2, int maxlen);
	将参数 str2 追加到 参数str1 后面，但是只追加 str2 的前 maxlen 个字符，同时也会覆盖 str1 最后 '\0';

5 strcmp(char* str1, char* str2);
	这个函数会按字符比较两个字符串，直到遇到不同的字符为止：
	如果 str1 大于 str2 ，会返回一个正数(Windows下返回 1， Linux下返回两个字符的ASCII码差值)
	如果 str1 小于 str2, 会返回一个负数(Windows下返回 -1， Linux下返回两个字符的ASCII码差值)
	如果相等，都是返回 0

6 strncmp(char* str1, char* str2, int maxlen);
	跟 strcmp()返回值相同，但是只比较前 maxlen 个字符;

7 strcpy(char* str1, char* str2);
	将 str2 里的数据拷贝到 str1 里，拷贝的数据不包括'\0'。 char str1[10] = { 0 };   char *str2 = "12345";   strcpy(str1, str2);

8 strncpy(char* str1, char* str2, int maxlen);
	跟 strcpy() 大致相同，只不过只拷贝了前 maxlen 个字符;

9 strchr(char* str, char ch);
	在str字符串里查找指定字符 ch，如果找到的话返回这个字符在 str 里的地址；如果没有找到，返回 NULL ((void *)0);

10 strstr(char* str1, char* str2);
	在 str1 里查找 str2 ，如果找到的话返回 str2 在str1 里的首地址；如果没找到，返回 NULL 

11 strtok(char *str, char delim);
	分解字符串 str 为一组字符串子串，用 delim 做为字符串的分隔符。
	注意，strtok()会破坏原来的字符串，函数每次分隔的时候，会把 delim 的位置替换为 '\0', 这样就会丢失原来的字符串。
	（更推荐用 sscanf() );

12 sscanf(char *str, char* format, arugment.....);
	scanf() 函数 是从键盘上获取用户输入，然后把值写到 变量 里;
	sscanf() 函数 是从 str 里获取数据，按照 format 格式，然后把值写到 变量 里，返回值是 成功写入数据的数量;

	int a, b , c;
	char s1[10] = { 0 };
	char s2[10] = { 0 };
	char s3[10] = { 0 };

	sscanf("2016-08-24", "%d-%d-%d", &a, &b, &c);
	// 把分隔符之外的数据，按照 %d-%d-%d 的格式分隔，分别赋值给a, b c;

	sscanf("2016 - 08 - 24", "%s - %s - %s", s1, s2, s3);
	// 如果用 %s - %s - %s的格式分隔，是把2016、08、24分别赋值给 s1, s2, s3
	// % 匹配一串非空白字符串，从输入的第一个字符到第一个非空白字符 开始匹配；直到遇到一个空白字符为止，匹配结束。

	sscanf("2016 - 08 - 24", "%4s - %2s - %2s", s1, s2, s3);
	// 也可以匹配指定的宽度，参数都是字符串，后面会有 '\0'

12 sprintf(char *str, char* format, arugment.....);
	printf() 函数是把格式化后的结果输出到输出设备;
	sprintf() 函数 就把格式化后的结果输出到 str 里;

	char i[10] = "I";
	char you[10] = "You";
	char str[10] = { 0 };

	sprintf(str, "%s love %s", i, you);
	// 会输出字符串 "I love You" 到 str 里。

	sprintf(str, "%10.3f", 0.1234567);
	// 输出字符串"     0.123"到字符串 str 里。

13 字符串转换函数( #include <stdlib.h>)
	atoi();
		把一个 char 类型的字符串转换成一个 int，里面的每个元素都是数字
			char *str = "12345";
			int a = atoi(str);
		itoa();
			 把一个 int 类型的数据转换成 char 类型的字符串（只能在Visual C++ 编译器下使用）;

	atoll();
		把一个 char 类型的字符串转换成一个 long long，里面每个元素都是数字。

	atof();
		把一个 char 类型的字符串转换成一个 double，里面每个元素都是浮点数。


	char str[10] = "....." // int, float, long long
	int / double / long long a = atoi(str) / atof(str) / atoll(str);
	printf("%d / %lf / %ld. \n", n);


二、函数参数的进栈顺序 和 运算顺序（引申出各个平台编译器的不同）

1 大端对齐 和 小端对齐
	
	unsigned int num = 0x12345678;

	大端对齐： 数值的高位数据放到内存的地位地址上，数值的低位数据放在内存的高位地址上。

		地址： 0xff1100 	0xff1101	0xff1102	0xff1103
		数值：     0x12 		0x34		0x56		0x78	

	小端对齐： 数值的高位数据放在内存的高位地址上，数值的低位数据放到内存的低位地址上。

		地址： 0xff1100 	0xff1101	0xff1102	0xff1103
		数值：     0x78 		0x56		0x34		0x12


	大端对齐：IBM、SUN的服务器CPU都是大端对齐，早期苹果的PowerMac也是大端对齐。

	小端对齐：x86/AMD64 架构(复杂指令集)的CPU， ARM 架构(精简指令集) 都是小端对齐。

2 函数的进栈顺序

#include <stdio.h>
void func(int a, int b, int c)
{
	printf("a = %d : %p\n", a, &a);
	printf("b = %d : %p\n", b, &b);
	printf("c = %d : %p\n", c, &c);
}

int main(void)
{
	func(100, 200, 300);
	return 0;
}

// Microsoft Visual C++下
a = 100 : 0x00BCFE1C	+4
b = 200 : 0x00BCFE20	+4
c = 300 : 0x00BCFE24

// Ubuntu12.04 gcc 下
a = 100 : 0xbfba89c0	+4
b = 200 : 0xbfba89c4	+4
c = 300 : 0xbfba89c8

// Macintosh LLVM Clang下
a = 100 : 0x7fff09ac	-4
b = 200 : 0x7fff09a8	-4
c = 300 : 0x7fff09a4

C程序在执行的时候，
先入栈的数据在栈底， 为高地址；
后入栈的数组在栈顶， 为低地址。

从上面的例子看出： 
在GCC 和 VC++ 下，函数参数的进栈顺序是"从右往左"。
在LLVM Clang下，函数参数的进栈顺序是"从左往右"。

3 函数参数的计算顺序

// 1.
#include <stdio.h>
int main(void)
{
	int a = 10, b = 20, c = 30;
	printf("%d, %d, %d\n", a + b + c, b = b * 2, c = c * 2);
	return 0;
}

// Visual C++下 ：
110, 40, 60

// Ubuntu GCC 下：
110, 40, 60

// LLVM Clang下：
60，40，60

// 2.
#include <stdio.h>
int a()
{
	printf("a\n");
	return 1;
}

int b()
{
	printf("b\n");
	return 2;
}

int main(void)
{
	printf("%d, %d\n", a(), b());
	return 0;
}

// MSVC下：
b
a
1,2

// GCC下：
b
a
1,2

// LLVM Clang下：
a
b
1,2


4 函数的默认参数：
#include <stdio.h>
void func(int a = 100, int b = 200, int c = 300)
{
	printf("a = %d : %p\n", a, &a);
	printf("b = %d : %p\n", b, &b);
	printf("c = %d : %p\n", c, &c);
}

int main(void)
{
	func(100, 200, 300);
	return 0;
}

GCC 和 MSVC 下支持函数默认参数，可以在函数内赋值

LLVM Clang 下 不支持函数默认参数，不允许在函数内赋值

C编译器：
Microsoft Visual C++ / GUN GCC / LLVM Clang / ICC (intel CPU 下会优化代码) / Turbo C 

"Undefined Behavior" 行为/性质未定义，"UB语句"
简单来说，就是如果你的程序违反了C标准的某些规则，但是程序具体执行结果是什么，C没有定义，可能会出现一些奇怪值。

short num = 35789472349571349579; 整数溢出，值是随机值

C标准提供很多种可选方案，但是没有告诉你具体用哪一种，

比如说，函数参数的进栈顺序和计算顺序，就是这样。

还有各种奇葩语句：
int a = 10;
int b = 20;
int c = a++ + ++b + c++ + b++ + a;

总结： 我们以后在写代码的时候，尽量避免写出 'UB语句'。
要多写"代码优美，清晰明了，逻辑严谨"的代码。


三、一级指针：
1 指针的使用：32 位系统下 4 字节， 64位系统下 8 字节。

2 指针的普通定义：
	1） 在定义的时候用 * ，表示这个变量是一个指针类型
		int a = 10;
		int *p = &a;

	2） 在配合表达式使用 * ,就是取址运算符， 表示取出这个地址的值
		printf("%d\n", *p);

3 指针的特殊定义：

	1) int * const p;
		指针常量： p 是 int *类型，const 修饰的是 p，所以 p 是常量，表示 p 指向的地址不可修改。
					p 不能再指向别的地址了，但是可以修改 p 指向的这个地址里的值。
		int a = 10;
		int b = 20;
		int * const p = &a;
		p = &b; 	// 错误
		*p = 100;	// 允许

	2)  int const *p;
		const int *p;
		常量指针： p 是 int * 类型，const 修饰的是 *p, 所以 *p 是常量，表示 p 指向的地址里的值不可修改。
					p 里的值是常量，不能修改，但是 p 可以指向其他地址。
		int a = 10;
		int b = 20;
		int const *p = &a;
		p = &b;		// 允许
		*p = 100;	// 错误

	3) const int * const p;
		常量指针常量：p 是 int * 类型， 两个 const 分别修饰了 *p 和 p，表示p指向的地址和地址里的值不可变。
					p 是常量，*p也是常量，既不能指向其他地址，而且地址里的值也不能修改。

		int a = 10;
		int b = 20;
		const int * const p = &a;
		p = &b;		// 错误
		*p = 100;	// 错误

《C Primer Plus》：我认为的最好的C语言入门书和参考书。
	"自由的代价，是永远的警惕。"

你定义了一个指针，那就一定要知道这个指针指向了何处，而且要保证这个指针是真实有效，否则，我就用程序崩溃来惩罚你！


四、多级指针：

#include <stdio.h>
int main(void)
{
	int a = 10;			// 定义一个整型变量 a， 里面的值是 10
	int *p = &a;		// 定义一个一级整型指针变量p， 里面的值是 a 的地址
	int **pp = &p;		// 定义一个二级整型指针变量pp, 里面的值是 p 的地址
	int ***ppp = &pp;	// 定义一个三级整型指针变量ppp,里面的值是 pp 的地址

	printf("%p, %p, %p, %p\n", &a, &p, &pp, &ppp);
	// 分别打印各个变量自身所在的内存地址

	printf("%p, %p, %p, %p\n", &a, p, pp, ppp);
	// &a, 取出a所在的地址，并打印
	// p, 取出p储存的值， 也就a 的地址，并打印
	// pp, 取出pp存储的值，也就是p的地址，并打印
	// ppp, 取出ppp存储的值，也就是pp的地址，并打印

	printf("%p, %p, %p, %p\n", &a, p, *pp, **ppp);
	// &a, 取出a所在的地址，并打印  ，a的地址
	// p, 取出p储存的值， 也就a 的地址，并打印 ，a 的地址
	// *pp, pp存储的是 p 的地址， *pp 就是取出 p 的地址里的值， a的地址
	// **ppp, ppp 存储的是 pp 的地址, *ppp 取出的是 pp 地址里的值，**ppp 就是取出pp地址里的 p的地址的值， a的地址

	printf("%d, %d, %d, %d\n", a, *p, **pp, ***ppp);
	// a, 打印 a 存储的值  10
	//*p, p 存储的是a的地址， *p 就是取出这个地址里的值 10
	// **pp, pp 存储的是 p 的地址， *pp 是取出 p 的值（a的地址)， **pp 就是根据a的地址取值，就是 10
	// ***ppp，ppp存储的 pp 的地址 *ppp就是取出 pp 存储的值(p的地址)，**ppp就是根据p的地址取值，就是 a的地址, ***ppp就是根据a的地址，取出里面的值， 10

	return 0;
}


五、指针 和 数组 
	
	int num[5] = {10, 20, 30, 40, 50};
	int *p = num;

		打印的值 		打印后再*p的值  	数组里的源值

// 操作地址
*p++	   10				20					10
*(p++)			
		
		*和++的优先级相同，但是结合性是从右往左，那么p先和后自增运算符++结合。
		后自增运算符++的特性是表达式完成之后，才会进行自增，那么就是取出 p 地址里的值后，p的下标后移一位(4个字节)

*++p 		20				20					10
*(++p)
		*和++的优先级相同，但是结合性是从右往左，那么p先和前自增运算符++结合。
		前自增运算符++的特性是执行表达式时会立即执行，那么p先将下标后移一位，然后再取出 p 指向的地址的值。 

//操作数值

(*p)++		10				11					11

		小括号优先级最高，所以*和p先结合，取出值后再和后自增运算符++结合。
		因为是后自增，所以先打印 p 里的值，然后再对 (*p) 里的值自增1

++*p 		11				11					11
++(*p)
		*和++的优先级相同，但是结合性是从右往左，那么p先和*先结合，取出值后再和前自增运算符++结合。
		因为是前自增，取出值后，自增操作会立即执行，将值自增1后，再打印出来

总结：如果一个表达式里面有多个运算符，则先进行优先级比较，先执行优先级高的运算符；
		如果运算符优先级相同，那就看结合性，根据结合方向来做运算。


结合性： 从左往右： 
			小括号()、中括号[]、成员选择.、成员选择->、双目运算符、逗号运算符,
		 从右往左：
		 	单目运算符、三目运算符、赋值类运算符

++a;	直接从变量 a 所在的内存地址取值，然后放到寄存器，直接让CPU进行自增1的操作，然后再返回寄存器，再放回内存

a++;	先把变量a的值保存在一个临时寄存器里，然后直接执行整个表达式的运算，运算结束后，再把a的值自增1，再放回内存。

速度比：
CPU > 寄存器 > 缓存(L1/L2/L3) > 内存 > 硬盘

数据交换：
CPU 只和寄存器做数据交换，对于重复操作的数据会放在缓存里，不管是寄存器还是缓存，他们的数据都来自于内存。


六、指针数组 和 数组指针

1. 指针数组：
	定义形式 : int *p[n] = { 0 };
		[]优先级高于*，那么p 先和 [n]结合，表示这个是一个有n个元素的数组。
		再和 int *结合，表示这个数组里的每个元素都是一个 整型指针，每个指针都能保存一个地址。

1)  使用指针数组保存多个元素的地址：

#include <stdio.h>
int main(void)
{
	int num[3] = {10, 20, 30};
	int *p[3] = { 0 };

	for(int i = 0; i < 3; ++i)
		p[i] = &num[i];

	for(int i = 0; i < 3; ++i)
	{
		printf("%p ", p[i]);
		printf("%d ", *p[i]);
	}
	return 0;
}


2)	使用指针数组保存多个字符串的首地址
#include <stdio.h>
int main(void)
{
	char *str[5] = 
	{
		"ISO/IEC9899:2011",
		"Programming",
		"Dennis Ritchie",
		"c",
		"linux"
	};

	char *str1 = str[1];		// 取出"Programming"这个字符串
	char *str2 = *(str + 3);	// 取出 "c" 这个字符串

	char ch1 = *(*(str + 4) + 2);	// 取出 "linux" 字符串里的 'n' 字符
	char ch2 = (*str + 5)[7];		// 取出第一个字符串的第一个列元素，然后后移5位，然后依此为行首，再往后去7为 '2'
	char ch3 = *str[0] + 6;			// 先取出第一个字符串的第一个元素，'I'，然后将其ASCII码加6， 'O'

	printf("%s\n", str1); 
	printf("%s\n", str2); 
	printf("%c\n", ch1); 
	printf("%c\n", ch2); 
	printf("%c\n", ch3); 

	return 0;
}


2. 数组指针：(行指针)
	定义形式：
	int num[n];		int num[n][m];			int num[l][n][m];
	int *p = num;   int (*p)[m] = num; 		int (*p)[n][m] = num;
	(一维数组)			(二维数组)				(三维数组)				....


1) 

#include <stdio.h>

void func(int (*p)[3]);

int main(void)
{
	int num[2][3] = {{10, 20, 30}, {40, 50, 60}};

	func(num);
	return 0;
}

void func(int p[2][3]);
void func(int p[][3]);
void func(int (*p)[3])
{
	printf("%d\n", p[1][2]);
	// 取出第二行的第三个元素 ： 60

	printf("%d\n", **p);
	// p是行指针，*p是表示这一行这一列的列地址， **p就是取出这一行的这一列里的元素：10

	printf("%d\n", (*p + 1)[2]);
	// p是行指针，*p是表示这一行这一列的列地址，加1表示后移一位(一个int),再以这一列为行首，取出后面第二个元素的值： 40

	printf("%d\n", *(*(p + 1)));
	// p是行指针，p + 1是往后移动一行，*p是取出这一行这一列的列地址，再*取值，就是取出这个地址里的值： 40

	printf("%d\n", *(*p + 1));
	// p是行指针， *p是确定了这一行这一列地址，然后再后移一位(1个int)，再对这个地址取值： 20

	printf("%d\n", *(p[1] + 2));
	// p是行指针，p[1] 表示下一行的列地址，往后移动两位(2个int)，然后再根据这个地址取值：60

	printf("%d\n", * ((*p + 1) + 2) );
	// p是行指针，*p是确定了这一行这一列的地址，先后移一位(1个int)，然后又后移2位(2个int)，然后再根据这个地址取值：40

	printf("%d\n", *(*p + 1) + 2);
	// p是行指针，*p是确定这一行这一列的地址，先后移一位(1个int)，然后根据这个地址取值：20， 打印的就是20 加 2的值

}


2)
#include <stdio.h>

void func(int (*p)[3][4])
{
	printf("%d\n", *(*(*(p + 0) + 1) + 2));	// 70
}

int main(void)
{
	int num[2][3][4] = 
					{
						10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 123,
						10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 123
					};

	func(num);
	return 0;
}



对一维数组某个元素取值： 要么 1个 *， 要么 1个 []

对二维数组某个元素取值： 要么 2个 *， 要么 2个 []， 要么 1个* 一个[]


总结：
	1. 指针数组： 就是一个数组，只是这个数组里的每个元素都是一个指针，这个数组占用了n个指针大小。
	2. 数组指针： 就是一个指针，只是这个指针指向一个数组，这个指针在内存里占用了 4、8 个字节。
	3. 一级指针p 和 一维数组p 的区别：
		int *p : 这是一个整型的一级指针，这个p是一个可变的句柄，我们可以让这个指针指向任何我们想让他指向的地方。

		int p[n];	这是一个整型的一维数组，这个p是一个不可变的句柄，他在内存空间里代表一段n个整型元素的内存，
					这个p在定义时候就被确定了，而且不能再改变，他一辈子都只能待着这里了。



七、内存四区：
	
	stack 栈区： 是由编译器自己分配和释放的，主要存储函数的参数，局部变量（数组等）。

	heap 堆区：是由程序员自己申请和释放的，什么都能存。mallco() 、calloc()、 realloc() 来申请， free()释放

	data 数据区：
		静态(全局)区：static 就是定义一个静态变量的。
			静态变量的生命周期是整个源程序，而且只有第一次初始化有效，之后赋值无效。
				如果不赋值，数值类会默认初始化为 0， 字符类会默认初始化为 ' '。 

		常量区：
			这里保存的数据都是只读的，不能修改，常量和字符串都保存在这里。
			（不包括字符数组类型的字符串，他们是在栈区的）
			除了第一次初始化外，常量区的数据在程序执行的时候不允许再次赋值。

		整个data区的数据： 在程序结束后，由系统统一销毁。

	code 代码区：用来存放编译后的可执行代码，二进制码，机器码。


	static 关键字详解：
		static 在C语言里既可以修饰变量，也可以修饰函数。

		static 变量： 
			1. 静态局部变量： 在函数中定义的，生命周期是整个源程序，但是他的作用域范围和普通变量没区别。
							都是在定义这个变量的函数内使用，而且静态变量在定义的时候就被初始化了，
							而且之后的赋值操作会被跳过。函数结束后，没法直接使用了，但是可以返回这个变量的地址，再次利用这个变量。

			2。 静态全局变量： 全局变量本身就是静态存储的，但是和静态全局变量有区别。
					1)：全局变量：作用域是整个源程序，其他文件也可以用，生命周期也是整个源程序。
					2)：静态全局变量： 作用域被限制在当前文件内，其他文件不可用，生命周期也是整个源程序。

		static 函数：(内部函数)
			静态函数只能在当前文件内被调用，不能被其他文件的函数调用。 （主要是区分普通函数：外部函数）

作用域： 变量或者函数在运行时候的有效作用范围。
生命周期： 变量或者函数在运行时被销毁和回收的存活时间。

							 生命周期 			作用域

	局部变量：				所在函数结束 		所在代码块内

	全局变量：				程序执行结束		所有文件内

	静态局部变量：			程序执行结束 		所在代码块内

	静态全局变量：			程序执行结束 		当前文件内

	普通函数：				程序执行结束 		所有文件内

	静态函数： 				程序执行结束 		当前文件内


八、堆区内存：

#include <stdlib.h>

1. void* malloc(n * sizeof(int));
	请求n个连续的、每个长度是一个int的堆空间，如果创建成功，将返回这个堆空间的首地址；如果创建失败，将返回 NULL.
	(申请成功后，这个堆空间里的值不确定，不会帮你初始化);

2. void* calloc(n, sizeof(int));
	请求n个连续的、每个长度是一个int的堆空间，如果创建成功，将返回这个堆空间的首地址；如果创建失败，将返回 NULL,
	(申请成功后，这个堆空间里的值会被初始化为 0 );

3. void* realloc(p, n * sizeof(int));
	给一个已经分配地址的指针 p 重新分配空间，p是原来的空间地址，n * sizeof(int) 是重新分配的大小;
	1) 如果当前内存段后面有足够的内存空间，那么就直接往后扩展空间，返回 p 原来的首地址;
	2) 如果当前内存段后面没有足够的内存空间了，那么系统会重新向内存树申请一段合适的内存空间，
		然后返回这个新的内存空间的地址，同时释放原来的内存空间。
	3) 如果创建失败，返回 NULL，此时原来的指针p 依然有效。

4. void free();
	1) free(p) 只是释放了申请的内存，但是不会帮你清空这块内存。然后系统将这块内存标记为可用而已，放回内存树上。
	2）p 指向的内存空间被释放了，所以其他程序有可能会用到这块内存，相当于指向了一个未知的区域，里面的数据也是未知的。
		这种情况，就叫野指针。
	3) 避免野指针的方法，就是在 free(p);之后，再多写一句 p = NULL; (void*)0
		逻辑上free(p)之后，编译器不会帮你清空内存，只是告诉操作系统这块内存可以被使用了而已。


例子： 如何释放自定义函数内申请的堆空间。

#include <stdio.h>
#include <stdlib.h>

char *funcA()
{
	char *p = (char*)malloc(20);
	strcpy(p, "Hello World!\n");

	return p;
}

char *funcB()
{
	char *p = funcA();
	return p;
}


int main(void)
{
	char *p = funcB();
	printf("%d\n", p);

	free(p);
	p = NULL;

	return 0;
}

论分配速度：
栈区略微快一步： 栈一个直接从内存里拿值，堆多一个寻址的步骤。

论访问速度：
是一样的，都是寻址。


九、文件操作： 操作 iostream -> sstream -> fstream 


#include <stdio.h>

1 fopen() 打开文件：
	函数原型 (FILE *)fopen(char *filename, char *mode);

	参数：
		filename : 需要打开的文件
		mode： 打开文件的方式
 
	r  r+  rb	rb+  (前提是文件必须存在)

	w  w+  wb   wb+  (文件存在清空文件，文件不存在新建文件)

	a  a+  ab   ab+	 (文件存在在文件末尾追加数据，文件不存在新建文件)


r (read) : 读
w (write)：写
b (binary): 二进制文件
a (append): 追加
+ (plus): 配合r、w、a来用的，完善读写，但是不会改变主导mode
t (text): 是文本文件，默认可以不写

FILE *fp = fopen("C:\\code\\text.c", "w");
if(NULL == fp)
{
	// 如果你不小心少写了一个等号，编译器会提示你语法错误，
	// 因为NULL 是常量，不允许赋值，fp则会直接赋值为NULL，接着做后面判断
}

2 fgetc(); 和 fputc();

1) fgetc() 文件字符读取函数
	原型：int fgetc(FILE * stream);
	参数： stream 文件流
	返回值： 成功读取会返回这个字符的 ASCII码值，失败返回 EOF ,就是(-1)
	举例： 
		char ch = fgetc(fp);
		printf("%c\n", ch); 	// 从fp指向的文件流里接收文件的第一个字符

2)fputc() 文件字符写入函数
	原型： int fputc(int ch, FILE * stream);
	参数： ch 就是要写入的字符，函数执行的时候，会自动把ch 转换成 ASCII码。
			stream 文件流
	返回值： 成功会返回写入的字符，失败返回 EOF (-1);
	举例：
		fputc(ch, fp);	// 将字符ch写入到fp指向的文件流里。

3 fgets(); 和 fputs();

1) fgets() 文件字符串读取函数
	原型： char * fgets(char *str, int size, FILE* fp);
	参数： str 就是保存从文件指针fp指向的文件流里读取的第一行字符串
			size 从文件里读取的字符串不超过 size 个字符。(size - 1,保留一个 '\n')
			fp  文件指针
	返回值： 成功返回 读取的字符串所在内存的首地址，失败返回 EOF 
	举例： 
		char str[20] = { 0 };
		fgets(str, 20 - 1, fp);	// 从fp指向的文件流里读取一行20 - 1个字符的字符串，放到 str 里，然后fp会跳转到下一行


2) fputs() 文件字符串写入函数
	原型： char *fputs(char *str, FILE *fp);
	参数： str 就是要写入到文件里的字符串
			fp 文件指针
	返回值： 成功返回 成功写入的字符串的个数，失败返回EOF
	举例：
		char str[20] = "Hello World!";
		fputs(str, fp);	 	// 向fp指向的文件流写入一个字符，写入成功会跳转到下一行

4 fscanf(); 和 fprintf();

1) fscanf() 从文件流里获取格式化的数据写入到输入流里
	原型： int fscanf(FILE *stream, char * format, arugment...);

	举例： 
	int i;
	float f;
	char ch;
	char str[20] = { 0 };
	fscanf(fp, "%d, %f", &i, &f);
	// 如果不需要从文件里面获取字符串，那么就可以用逗号或者其他符号来分隔  10,3.14

	fscanf(fp, "%s %c", str, &ch);			
	// 如果需要从文件里写获取字符串，那么就必须用空格或者回车来分隔 abcd a

2) fprintf() 从输入流里获取格式化的数据写入到文件流里
	原型： int fprintf(FILE* stream, char *format, arugment...);

	举例：
		int i = 10;
		float f = 3.14;
		char ch = 'C';
		char str[20] = "Hello World!";
		fprintf(fp, "%d %f %c %s", i, f, ch, str);	
		// 将各个数据按照格式化写入到文件流里


5 fread(); 和 fwrite();

	二进制文件读写函数：
		函数原型： 
				size_t fread(void *ptr, size_t size, size_t count, FILE * fp);
				size_t fwrite(void *ptr, size_t size, size_t count, FILE * fp);

		参数解释：
				ptr 是一个指针：
					对于 fread()来说，就是从文件里读取数据后存放的地址;
					对于 fwrite() 来说，就是写入到文件里的数据存放的地址;

				size ：每次要读/写的字节数
				count: 读/写的次数
				fp： 需要操作的文件指针
		返回值： 成功读/写 的字节数

		举例：
			char str[10] = { 0 };
			fread(str, sizeof(char) * 10, 1, fp);
			// 每次从fp指向的文件中读取10个字节大小的数据，放到 str中，总共读 1 次
			fwrite(str, sizeof(char) * 10, 1, fp);
			// 每次从 str里获取10个字节大小的数据，写入到 fp 指向的文件中，总共写 1次

6 fseek(); 文件指针操作函数

	函数原型： size_t fseek(FILE *fp, long offset, int whence);
	参数： fp 文件指针
			offset : 偏移量，基于文件起始位置偏移了 offset 个字节
			whence ：起始点（三个）：
					SEEK_SET 0  文件开头位置
					SEEK_CUR 1  文件指针当前位置
					SEEK_END 2  文件结尾位置

	举例：
		fseek(fp, 0, SEEK_END);
		// 将文件指针指向文件结尾，并且偏移了 0 个字节

		fseek(fp, -10, 1);
		// 将当前文件指针位置向前偏移 10 个字节

7 ftell(); 获取文件指针当前位置
	函数原型： long ftell(FILE* fp);
	返回值： 返回文件指针当前位置，基于文件开头的偏移字节数。

	举例： long len = ftell(fp);
		// 返回文件指针fp 当前位置，距离文件开头 len 个字节。

8 rewind(); 文件指针位置重置 
	函数原型： void rewind(FILE* fp);
	举例：
		rewind(fp);
		// 将文件指针fp 重新指向文件开头(IO流开头)


	stream > (istream / ostream) -> fstream / sstream


6、7、8 大栗子：

#include <stdio.h>

int main(void)
{
	FILE *fp = fopen("C:\\code\\test.txt", "r+");
	fseek(fp, 0, SEEK_END); // 先将文件指针指向文件结尾
	long len = ftell(fp);	// 获取文件指针位置，返回文件的字节大小(Byte)
	rewind(fp);		// 再把文件指针重新指向文件开头
	printf("文件大小是：%d 字节！\n", len);
	fclose(fp);
	return 0;
}

9 feof(); 判断文件指针是否到达文件结尾
	
	原型： int feof(FILE* fp);
	返回值： 一旦文件指针指向文件结尾，就返回一个真值；否则返回非真(0);
		if(!feof(fp))
	1. 这个函数在到达文件结尾的时候是返回真值，所以我们在做判断的时候，要注意使用 if(!feof(fp))
	2. 如果要这个函数生效，必须对文件进行一次读写操作，哪怕这个文件是空的，你不做读写，都没用。
		feof() 返回的是一个标识符，每次对文件读写，都会改变这个文件标志符的位置，对文件读写一次之后才能找到这个标识符。
		有了文件标识符才能对 feof() 做出返回操作;

10  fclose();
	原型：int fclose(fp);
	返回值： 成功释放返回 0，失败返回 EOF (-1);
	fclose(fp); 表示释放文件指针和相关的文件缓冲区，文件指针不再合法指向原来的那块内存，但是不代表里面的内容被清空。
	进行过 fclose()之后，系统会把内存里的数据内容写到磁盘文件里，也就是说 fclose()之后，文件操作才会生效。



编码格式：

UTF-8 ： 一个汉字 3 个字节 
GBK ： 一个汉字 2 个字节

#include <stdio.h>
#include <string.h>

// GBK 可以在VS上测试
int main(void)
{
	char str[] = "你好地球";
	int len = strlen(str);
	for(int i = len - 1; i > 0; i-=2)
	{
		printf("%c%c", str[i - 1], str[i]);
	} 
	printf("\n");
	return 0;
}

// UTF-8 Linux下GCC 测试
int main(void)
{
	char str[] = "你坏世界";
	int len = strlen(str);
	for(int i = len - 1; i > 0; i-=3)
	{
		printf("%c%c%c", str[i - 2], str[i - 1], str[i]);
	} 
	return 0;
}


十、结构体字节对齐：

1. 结构体字节对齐：
	在C语言里面，一个结构体变量里的成员所占的内存是连续的，但是各个成员之间的地址不一定是连续的，因为会有填充字节的存在。

	1)结构体变量的大小，一定是其最大的成员的数据类型的整数倍。
			
	2)结构体变来那个的地址，一定和其第一个成员的地址是相同的。

2. 示例：

#include <stdio.h>
#include <string.h>

struct Box
{
	int height;		// int 是4， 为了字节对齐 double 填充了 4， 也就是 8
	double width;	// 最大的 8
	char ch[10];	// 分解成 8 + 2， 2会跟后面的数据类型做字节填空，填空满8个，如果不满8个，自我填充到8个， 就是 16
	char type;		// 
};

int main(void)
{
	struct Box box;
	box.height = 4;
	box.width = 5.5;
	strcpy(ch, "haha");
	box.type = 'A';

	printf("box = %p\n", &box);
	printf("box.height = %p\n", &box.height);		
	printf("box.width = %p\n", &box.width);
	printf("box.ch = %p\n", box.ch);
	printf("box.type = %p\n", &box.type);

	printf("box = %d\n", sizeof(box);		// 总 4+4 + 8 + 8+8 = 32   

	return 0;
}


2. 初识链表：

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student
{
	char *name;				// 姓名
	int age;				// 年龄
	struct Student *next;	// 允许
	//struct Student next; 	// 错误

	// next 是一个结构体成员，他的类型是 struct Student *类型，表示这个一个结构体指针。
	// 用来指向某个 struct Student 类型的结构体变量的。

	// 结构体你可以看做是一个自定义的数据类型，而且结构体可以嵌套，但是嵌套有条件：
	// 结构体可以嵌套定义其他结构体变量，也可以定义自身类型的结构体指针变量，
	// 但是绝对不可以定义自身结构体的普通变量
};

int main(void)
{
	struct Student stu, *stup;	// 定义了一个结构体普通变量 stu 和一个结构体指针变量 stup

	stu.name = (char *)malloc(10 * sizeof(char));// 给 stu.name 分配了一个10字节的堆空间，可以存储字符串
	strcpy(stu.name, "damao");		// 拷贝字符串"damao"给stu.name
	stu.age = 18;					// 年龄18

	stup = (struct Student *)malloc(1 * sizeof(struct Studnet)); 	// 给 stup 分配了一个 struct Student 大小的堆空间
	stup->name = (char *)malloc(10 * sizeof(char));				// 给 stup->name 分配了一个10字节的堆空间，可以存储字符串
	strcpy(stup->name, "ermao");	// 拷贝字符串"ermao" 给 stup->name
	stup->age = 16;			// 年芳16

	stu.next = stup;		// stu.next 指向了 stup 这个结构体变量 的首地址， 连接成功！

	stup->next = NULL;		// 没有"sanmao"了，所有 stup->next 就可以置为NULL

	free(stup->name);
	free(stup);
	free(stu.name);

	return 0;			// 程序结束~ 
}

End。。。。 

好好学习，天天向上！
