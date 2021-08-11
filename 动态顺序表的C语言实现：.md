#  动态顺序表的C语言实现：

```css
正文开始@Assassin
```

@[TOC](目录:)

##  ==什么是顺序表?==
**`顺序表`**是在计算机内存中以`数组`的形式保存的`线性表`，线性表的顺序存储是指用一组地址连续的存储单元**依次存储线性表中的各个元素**，使得线性表中在逻辑结构上相邻的数据元素存储在相邻的物理存储单元中，即通过数据元素物理存储的相邻关系来反映数据元素之间逻辑上的相邻关系，采用顺序存储结构的线性表通常称为顺序表。**顺序表是将表中的结点依次存放在计算机内存中一组地址连续的存储单元中。**


***简言之，顺序表是用一段物理地址连续的存储单元依次存储数据元素的线性结构，一般情况下采用数组存储。在数组上完成数据的增删查改。可以类比vector，简单理解为可以动态增长的数组~~***

**`顺序表一般可以分为：`**
- **`1.静态顺序表(直接定义数组)：存储数据的空间是固定的；`**
  -  **`  导致的问题：开小了不够用，开大了浪费空间，现实中不实用`**
- **`2.动态顺序表(用指针接收malloc动态开辟)：存储数据的空间是可以动态增长的，可以更好的适应于现实中的使用
`**

##  1. 定义顺序表结构体：
首先，我们要创建一个顺序表类型，该顺序表类型包括了顺序表的起始位置、记录顺序表内已有元素个数的计数器(size)，以及记录当前顺序表的容量的变量(capacity)。

```cpp
typedef int SLDataType;//定义一个类型，以便更好的适应每一种数据的存储，这里以存放整型数据为例

typedef struct SeqList
{
	SLDataType* a;//声明了一个指向顺序表的指针
	int size;//记录当前顺序表内元素个数
	int capacity;//记录当前顺序表的最大容量
}SeqList;//C语言中直接使用Seqlist类型

```
##  2. 初始化顺序表：
我们需要一个初始化函数，对顺序表进行初始化。这里多说两句自己的一些理解：有些小伙伴会对结构体直接赋值为0来进行初始化，这种操作虽然编译器不给error，但也会报warning，我们应该注意这一点，因为本身struct中的==指针类型也不能简单的以0来初始化==，实在不想用接口的话，那我建议你用NULL来初始化指针~~当然我们要有意识地去写工程化的代码，每个独立的功能习惯地去用函数封装起来，我们调用接口实现功能。

```cpp
//初始化顺序表
void SeqListInit(SeqList* ps)
{
	assert(ps);//断言
	ps->a = NULL;//刚开始时顺序表为空，顺序表指针为NULL
	ps->size = 0;//起始时元素个数为0
	ps->capacity = 0;//容量为0
	
	/* 或者一开始就开辟空间，给定capacity
	
		ps->a = (SLDateType*)malloc((sizeof(SLDateType)* 4));
	if (ps->a == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	ps->size = 0;
	ps->capacity = 4;
   */
}

```
##  3. 销毁顺序表：
因为顺序表所用的内存空间是动态开辟在堆区的，所以我们在==使用完后需要及时对其进行释放，避免造成内存泄漏。== 一般这个操作放在return之前调用。
**当然，如果想在下次运行前记住当前的一些增删查改，若需要对数据进行保存，可以使用文件操作函数将数据保存到一个文件中，下次使用顺序表的时候先读取文件数据即可。**
```cpp
//销毁顺序表
void SeqListDestory(SeqList* ps)
{
	assert(ps);//断言
	free(ps->a);//释放顺序表指针指向的空间
	ps->a = NULL;//及时置空
	ps->size = 0;//元素个数置0
	ps->capacity = 0;//容量置0
}

```
##  4. 打印顺序表：
打印函数没啥好说的，直接遍历一遍size个数组中的元素即可。

```cpp
//打印顺序表
void SeqListPrint(SeqList* ps)
{
	assert(ps);//断言
	int i = 0;
	//循环打印顺序表指针指向的数据
	for (i = 0; i < ps->size; i++)
	{
		printf("%d ", ps->a[i]);
	}
	printf("\n");
}

```
##  5. 判断容量+扩容：
我们应该意识到，每次需要增加数据的时候，首先都应该先检查顺序表内元素个数是否已达顺序表容量上限。若已达上限，那么我们就需要先对顺序表进行扩容，然后才能增加数据。扩容就要使用到realloc函数。

```cpp
//检查顺序表容量是否已满，若已满，则增容
void SeqCheckCapacity(SeqList* ps)
{
	if (ps->size == ps->capacity)//判断已满，需要增容
	{
		//判断顺序表容量是否为0，若为0，则先开辟用于存放4个元素的空间大小，若不为0，则扩容为原来容量的两倍
		int newcapacity = ps->capacity == 0 ? 4 : 2 * ps->capacity;
		SLDataType* newArr = realloc(ps->a, newcapacity*sizeof(SLDataType));
		if (newArr == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}
		//最好用同一个指针维护较为稳妥，所以我们把newArr赋值给ps
		ps->a = newArr;//开辟成功，将顺序表指针更新
		ps->capacity = newcapacity;//容量更新
	}
}

```
**注意：** 若传入realloc的指针为==空指针(NULL)==，则realloc函数的作用相当于==malloc==函数。

##  6. 头插数据：
要想在顺序表的表头插入数据，那么就需要先将顺序表原有的数据==从后往前==依次向后挪动一位，最后再将数据插入表头。注意一定要依次从后面移动数据，否则会发生==覆盖==。

```cpp
//头插
void SeqListPushFront(SeqList* ps, SLDataType x)
{
	assert(ps);
	SeqCheckCapacity(ps);//检查容量
	int i = 0;
	for (i = ps->size; i > 0; i--)//将数据从后往前依次向后挪
	{
		ps->a[i] = ps->a[i - 1];
	}
	ps->a[0] = x;
	ps->size++;//顺序表元素个数加一
}

```
**注意：** 挪动数据的时候应从后向前依次挪动，若从前向后挪动，会导致后一个数据被覆盖。

##  7. 尾插数据：
尾插相对于头插就比较简单了，直接在表尾的size插入数据即可。记得size也要相应地++

```cpp
//尾插
void SeqListPushBack(SeqList* ps, SLDataType x)
{
	assert(ps);
	SeqCheckCapacity(ps);//检查容量
	ps->a[ps->size] = x;
	ps->size++;//顺序表元素个数加一
}

```
##  8. 指定下标位置插入数据：
要做到在指定下标位置插入数据，首先我们需要得到一个下标位置，然后从该下标位置开始（包括该位置），其后的数据从后往前依次向后挪动一位，最后将数据插入到该下标位置。

```cpp
//指定下标位置插入
void SeqListInsert(SeqList* ps, int pos, SLDataType x)
{
	assert(ps);
	assert(pos >= 0 && pos <= ps->size);//检查输入下标的合法性
	SeqCheckCapacity(ps);//检查容量
	int i = 0;
	for (i = ps->size; i > pos; i--)//从pos下标位置开始，其后的数据从后往前依次向后挪
	{
		ps->a[i] = ps->a[i - 1];
	}
	ps->a[pos] = x;
	ps->size++;//顺序表元素个数加一
}

```
我们可以发现，头插和尾插实际上就是在下标为0的位置和下标为ps->size的位置插入数据，也就意味着我们可以统一使用该函数来实现头插和尾插。
相当于实现了==代码复用==，一定程度上也起到了便于管理的效果。
```cpp
//头插
void SeqListPushFront(SeqList* ps, SLDataType x)
{
	SeqListInsert(ps, 0, x);//在下标为0的位置插入数据
}
//尾插
void SeqListPushBack(SeqList* ps, SLDataType x)
{
	SeqListInsert(ps, ps->size, x);//在下标为ps->size的位置插入数据
}

```
##  9. 删除数据：
删除数据，其实可以理解为：从某个位置开始，数据依次向前覆盖，相应的size做出改变。这样一来，该位置的数据就相当于删除了。

##  10. 尾删数据：
尾删就更简单了，直接将顺序表的元素个数减一即可。把size减一，让其遍历不到最后一个数据，也就是删除了。ps：其实，深入了解的话，操作系统层面上的删除也是如此，你不能访问了，对于OS来说就是删除了~~

```cpp
//尾删
void SeqListPopBack(SeqList* ps)
{
	assert(ps);
	assert(ps->size > 0);//保证顺序表不为空
	ps->size--;//顺序表元素个数减一
}

```
##  11. 指定下标位置删除数据：
要删除指定下标位置的数据，我们只需要从下标位置开始，其后的数据从前向后依次覆盖即可。

```cpp
//指定下标位置删除
void SeqListErase(SeqList* ps, int pos)
{
	assert(ps);
	assert(ps->size > 0);//保证顺序表不为空
	assert(pos >= 0 && pos < ps->size);
	int i = 0;
	for (i = pos; i < ps->size - 1; i++)//从pos下标位置开始，其后的数据从前往后依次向前覆盖
	{
		ps->a[i] = ps->a[i + 1];
	}
	ps->size--;//顺序表元素个数减一
}

```
同理，头删和尾删实际上也就是删除下标为0的位置和下标为ps->size - 1的位置的数据，也就意味着我们可以统一使用该函数来实现头删和尾删。

```cpp
//头删
void SeqListPopFront(SeqList* ps)
{
	SeqListErase(ps, 0);//删除下标为0的位置的数据
}
//尾删
void SeqListPopBack(SeqList* ps)
{
	SeqListErase(ps, ps->size - 1);//删除下标为ps->size - 1的位置的数据
}

```
##  12. 查找数据：
查找数据也相对简单，直接遍历一次顺序表即可，若找到了目标数据，则停止遍历，并返回该数据的下标，否则返回-1。

```cpp
//查找元素，若有，返回下标，否则返回-1
int SeqListFind(SeqList* ps, SLDataType x)
{
	assert(ps);
	int i = 0;
	for (i = 0; i < ps->size; i++)//遍历顺序表进行查找
	{
		if (ps->a[i] == x)
			return i;//找到该数据，返回下标
	}
	return -1;//未找到，返回-1
}

```
##  13. 修改数据：
修改数据，就直接对该位置的数据进行再次赋值即可。

```cpp
//修改指定下标位置元素
void SeqListModify(SeqList* ps, int pos, SLDataType x)
{
	assert(ps);
	assert(pos >= 0 && pos < ps->size);//检查输入下标的合法性
	ps->a[pos] = x;//修改数据
}

```
## 14. 源代码：
###  1. SeqList.h:

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef int SLDatatype;
typedef struct SeqList
{
    SLDatatype *a; //存储数据空间的指针
    int size;      //有效数据的个数
    int capacity;  //容量空间大小
} SeqList;
//顺序表初始化声明
void SeqListInit(SeqList *ps);
//顺序表销毁声明
void SeqListDestory(SeqList *ps);
//检查空间，如果满了，进行空间增容
void CheckCapacity(SeqList *ps);
//顺序表打印声明
void SeqListPrint(SeqList *ps);
//顺序表尾插
void SeqListPushBack(SeqList *ps, SLDatatype x);
//顺序表头插
void SeqListPushFront(SeqList *ps, SLDatatype x);
//顺序表尾删
void SeqListPopBack(SeqList *ps);
//顺序表头删
void SeqListPopFront(SeqList *ps);
//顺序表查找
SLDatatype SeqListFind(SeqList *ps, SLDatatype x);
//顺序表在pos位置插入
void SeqListInsert(SeqList *ps, int pos, SLDatatype x);
//顺序表删除pos位置的值
void SeqListErase(SeqList *ps, int pos);

```
###  2. SeqList.cpp:

```cpp
#include "SeqList.h"
void CheckCapacity(SeqList *ps)
{
    //空间不够，需要增容
    if (ps->size == ps->capacity)
    {
        SLDatatype *tmp = (SLDatatype *)realloc(ps->a, sizeof(SLDatatype) * ps->capacity * 2);
        //如果空间不足，可能增容失败
        if (ps->a == NULL)
        {
            printf("顺序表已满,无法插入\n");
            exit(-1);
        }
        ps->a = tmp;
        ps->capacity *= 2;
    }
}
//顺序表初始化；需要传址
void SeqListInit(SeqList *ps)
{
    ps->a = (SLDatatype *)malloc(sizeof(SLDatatype) * 4);
    //malloc失败
    if (ps->a == NULL)
    {
        printf("malloc fail\n");
        exit(-1);
    }
    memset(ps->a, 0, sizeof(SLDatatype) * 4);
    ps->size = 0;
    ps->capacity = 4;
}
//顺序表销毁；需要传址
void SeqListDestory(SeqList *ps)
{
    free(ps->a);
    ps->a = NULL;
    ps->size = 0;
    ps->capacity = 0;
}
//顺序表打印
void SeqListPrint(SeqList *ps)
{
    for (int i = 0; i < ps->size; ++i)
    {
        printf("%d ", ps->a[i]);
    }
    printf("\n");
}
//顺序表尾插
void SeqListPushBack(SeqList *ps, SLDatatype x)
{
    assert(ps);
    CheckCapacity(ps);
    //空间够了，直接把插入的数据放到a[size]位置处
    ps->a[ps->size] = x;
    ps->size++;
}
//顺序表头插
void SeqListPushFront(SeqList *ps, SLDatatype x)
{
    assert(ps);
    CheckCapacity(ps);
    //从最后一个数的位置开始一个一个往后移
    int end = ps->size - 1;
    while (end >= 0)
    {
        ps->a[end + 1] = ps->a[end];
        --end;
    }
    //x赋值给头位置
    ps->a[0] = x;
    ps->size++;
}
//顺序表尾删
void SeqListPopBack(SeqList *ps)
{
    assert(ps);
    //若无此步骤size为0时再size--为-1
    assert(ps->size > 0);
    ps->size--;
}
//顺序表头删
void SeqListPopFront(SeqList *ps)
{
    assert(ps);
    assert(ps->size > 0);
    int begin = 1;
    //从第二个数的位置开始往前移
    while (begin < ps->size)
    {
        ps->a[begin - 1] = ps->a[begin];
        ++begin;
    }
    ps->size--;
}
//顺序表查找,可以查找一个数在不在数组里，并返回其下标，配合其他接口使用
SLDatatype SeqListFind(SeqList *ps, SLDatatype x)
{
    assert(ps);
    for (int i = 0; i < ps->size; ++i)
    {
        if (ps->a[i] == x)
        {
            return i;
        }
    }
    return -1;
}
//顺序表在pos位置插入
void SeqListInsert(SeqList *ps, int pos, SLDatatype x)
{
    assert(ps);
    assert(pos >= 0 && pos < ps->size);
    CheckCapacity(ps);
    int end = ps->size - 1;
    while (end >= pos)
    {
        ps->a[end + 1] = ps->a[end];
        --end;
    }
    ps->a[pos] = x;
    ps->size++;
}
//顺序表删除pos位置的值
void SeqListErase(SeqList *ps, int pos)
{
    assert(ps);
    assert(pos >= 0 && pos < ps->size);
    while (pos < ps->size - 1)
    {
        ps->a[pos] = ps->a[pos + 1];
        ++pos;
    }
    ps->size--;
}

```
###  3. test.cpp:

```cpp
#include "SeqList.h"
int main()
{
    SeqList Sl;
    //测试顺序表初始化
    SeqListInit(&Sl);
    //测试顺序表尾插
    SeqListPushBack(&Sl, 1);
    SeqListPushBack(&Sl, 2);
    SeqListPushBack(&Sl, 3);
    SeqListPushBack(&Sl, 4);
    SeqListPushBack(&Sl, 5);
    SeqListPrint(&Sl);
    //测试顺序表头插
    SeqListPushFront(&Sl, 0);
    SeqListPrint(&Sl);
    //测试顺序表尾删
    SeqListPopBack(&Sl);
    SeqListPopBack(&Sl);
    SeqListPrint(&Sl);
    //测试顺序表头删
    SeqListPopFront(&Sl);
    SeqListPrint(&Sl);
    SeqListFind(&Sl, 1);
    SeqListPrint(&Sl);
    //测试顺序表在pos位置插入
    SeqListInsert(&Sl, 1, 20);
    SeqListPrint(&Sl);
    //测试顺序表删除pos位置的值
    SeqListErase(&Sl, 0);
    SeqListPrint(&Sl);
    //测试顺序表查找
    int pos = SeqListFind(&Sl, 3);
    if (pos != -1)
    {
        printf("找到了\n");
    }
    //查找配合删除删掉指定的数
    int pos1 = SeqListFind(&Sl, 2);
    if (pos1 != -1)
    {
        SeqListErase(&Sl, pos1);
    }
    SeqListPrint(&Sl);
    //顺序表销毁
    SeqListDestory(&Sl);
    return 0;
}

```
##  15. 测试：
![在这里插入图片描述](https://img-blog.csdnimg.cn/95e8cd2b87274af385edc7e58498e4e4.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JfSW5ncmFt,size_16,color_FFFFFF,t_70)

##  see you next blog~~