#  范围for语句/(range for statement)

*写在开篇：C++中有很多语法糖，现代C++倾向于让我们各种繁杂的操作变得更为简洁，==范围for==算是其中的典型。在 C++98/03 中，不同的容器和数组遍历的方式不尽相同，写法不统一，也不够简洁，而 C++11 基于范围的 for 循环可以以简洁、统一的方式来遍历容器和数组，用起来也更方便了。*
```css
正文开始@Assassin
```

@[TOC](目录:)



 ##  1. for 循环新语法：
 在介绍新语法之前，先来看一个使用迭代器遍历容器的例子：


```cpp
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6};
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
    system("pause");

    return 0;
}

```
**运行结果如下：**
![在这里插入图片描述](https://img-blog.csdnimg.cn/360c544a39d3459697e7ce29d0b0c5e4.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JfSW5ncmFt,size_16,color_FFFFFF,t_70)
我们在遍历的过程中需要给出容器的两端：==开头（begin）== 和 ==结尾（end）==，因为这种遍历方式不是基于范围来设计的。**`在基于范围的for循环中，不需要再传递容器的两端，循环会自动以容器为范围展开，并且循环中也屏蔽掉了迭代器的遍历细节，直接抽取容器中的元素进行运算，使用这种方式进行循环遍历会让编码和维护变得更加简便。`**

**C++98 中普通的 for 循环，语法格式：**

```cpp
for(表达式 1; 表达式 2; 表达式 3)
{
    // 循环体
}
```
**C++11 基于范围的 for 循环，语法格式：**

```cpp
for (declaration : expression)
{
    // 循环体
}
```
在上面的语法格式中 ==declaration== 表示遍历声明，在遍历过程中，当前被遍历到的元素会被存储到声明的变量中。==expression== 是要遍历的对象，它可以是 **`表达式`** 、**`容器`**、**`数组`**、**`初始化列表`** 等。


使用基于范围的 for 循环遍历容器，示例代码如下：

```cpp
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main(void)
{
    vector<int> v = {1, 2, 3, 4, 5, 6};
    for (auto value : v)
    {
        cout << value << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}

```
**运行结果如下：**
![在这里插入图片描述](https://img-blog.csdnimg.cn/c6e664d2bec84929a2c98ae02ab378ad.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JfSW5ncmFt,size_16,color_FFFFFF,t_70)
在上面的例子中，**`是将容器中遍历的当前元素拷贝到了声明的变量 value 中，因此无法对容器中的元素进行写操作，如果需要在遍历过程中修改元素的值，需要使用引用。`**

```cpp
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main(void)
{
    vector<int> v = {1, 2, 3, 4, 5, 6};
    cout << "遍历修改之前的容器: ";
    for (auto &value : v)
    {
        cout << value++ << " ";
    }
    cout << endl << "遍历修改之后的容器: ";

    for (auto &value : v)
    {
        cout << value << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}
```
**运行结果如下：**
![在这里插入图片描述](https://img-blog.csdnimg.cn/36b97dcd74c8460bb6d73d97277a0c2e.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JfSW5ncmFt,size_16,color_FFFFFF,t_70)
对容器的遍历过程中，如果只是读数据，不允许修改元素的值，可以使用 ==const== 定义保存元素数据的变量，在定义的时候建议使用 ==const auto &== ，这样相对于 ==const auto== 效率要更高一些。


```cpp
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main(void)
{
    vector<int> v = {1, 2, 3, 4, 5, 6};
    for (const auto &value : v)
    {
        cout << value << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}

```
**运行结果如下：**
![在这里插入图片描述](https://img-blog.csdnimg.cn/638575f8c4e94d7ea10a85f7ee58f692.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JfSW5ncmFt,size_16,color_FFFFFF,t_70)

##  2. 使用细节：
###  2.1 关系型容器：
使用基于范围的 for 循环有一些需要注意的细节，先来看一下对关系型容器 map 的遍历：

```cpp
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <map>
using namespace std;

int main(void)
{
    map<int, string> m = {{1, "wangyuan"}, {2, "cdc"}, {3, "lzh"}};

    // 基于范围的for循环方式
    for (auto &it : m)
    {
        cout << "id: " << it.first << ", name: " << it.second << endl;
    }

    cout << endl;
    // 普通的for循环方式
    for (auto it = m.begin(); it != m.end(); ++it)
    {
        cout << "id: " << it->first << ", name: " << it->second << endl;
    }

    cout << endl;
    system("pause");
    return 0;
}

```
**运行结果如下：**
![在这里插入图片描述](https://img-blog.csdnimg.cn/3516d3a766f847afb41dc72de3759fc5.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JfSW5ncmFt,size_16,color_FFFFFF,t_70)
在上面的例子中使用两种方式对 map 进行了遍历，通过对比有两点需要注意的事项：

**1. 使用普通的 for 循环方式（基于迭代器）遍历关联性容器， auto 自动推导出的是一个迭代器类型，需要使用迭代器的方式取出元素中的键值对（和指针的操作方法相同）：**

- ==it->first==
- ==it->second==

**2. 使用基于访问的 for 循环遍历关联性容器，auto 自动推导出的类型是容器中的 value_type，相当于一个对组（std::pair）对象，提取键值对的方式如下：**


- ==it.first==
- ==it.second==
###  2.2 元素只读:
通过对基于范围的 for 循环语法的介绍可以得知，在 for 循环内部声明一个变量的引用就可以修改遍历的表达式中的元素的值，但是这并不适用于所有的情况，**`对应 set 容器来说，内部元素都是只读的，这是由容器的特性决定的，因此在 for 循环中 auto & 会被视为 const auto & 。`**


```cpp
#include <iostream>
#include <cstdlib>
#include <set>
using namespace std;

int main(void)
{
    set<int> st = {1, 2, 3, 4, 5, 6};
    for (auto &item : st)
    {
        cout << item++ << endl; // error, 不能给常量赋值
    }

    system("pause");
    return 0;
}

```
perror: 表达式必须是==可修改的左值==
![在这里插入图片描述](https://img-blog.csdnimg.cn/c3c84d3c6b24417f9bc627a09fec030d.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JfSW5ncmFt,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/fda9f773ecb1417fbd12f3967383b67d.png)
除此之外，**`在遍历关联型容器时也会出现同样的问题，基于范围的for循环中，虽然可以得到一个std::pair引用，但是我们是不能修改里边的first值的，也就是key值。`**

```cpp
#include <iostream>
#include <string>
#include <map>
using namespace std;

int main(void)
{
    map<int, string> m = {{1, "lucy"}, {2, "lily"}, {3, "tom"}};

    for (auto &item : m)
    {
        // item.first 是一个常量
        cout << "id: " << item.first++ << ", name: " << item.second << endl; // error
    }

    return 0;
}

```
perror: 表达式必须是==可修改的左值==
![在这里插入图片描述](https://img-blog.csdnimg.cn/83835fed154d46539e4dd767bbd19886.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JfSW5ncmFt,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/65fb97705eac4a50bc2a1b1c7bec882b.png)
###  2.3 访问次数:
基于范围的 for 循环遍历的对象可以是一个表达式或者容器 / 数组等。假设我们对一个容器进行遍历，在遍历过程中 for 循环对这个容器的访问频率是一次还是多次呢？我们通过下面的例子验证一下：

```cpp
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

vector<int> v = {1, 2, 3, 4, 5, 6};
vector<int> &getRange()
{
    cout << "get vector range..." << endl;
    return v;
}

int main(void)
{
    for (auto val : getRange())
    {
        cout << val << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}

```
**运行结果如下：**
![在这里插入图片描述](https://img-blog.csdnimg.cn/7326dc4c9de94145a8d32a37439369dd.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JfSW5ncmFt,size_16,color_FFFFFF,t_70)
从上面的结果中可以看到，不论基于范围的 for 循环迭代了多少次，函数 getRange () 只在第一次迭代之前被调用，得到这个容器对象之后就不会再去重新获取这个对象了。


==结论：==


**对应基于范围的 for 循环来说，冒号后边的表达式只会被执行一次。在得到遍历对象之后会先确定好迭代的范围，基于这个范围直接进行遍历。如果是普通的 for 循环，在每次迭代的时候都需要判断是否已经到了结束边界。**



###  2.4 issue：
**在基于范围的for循环中使用声明的变量**
**question:** 在下面的示例中，i具有功能范围。 但似乎我不能在第二个for循环中使用i。 为什么 ==for (i : v1)== 不起作用，但是 ==for (int i : v1)== 有效？
```cpp
#include<iostream>
#include<string>
#include<vector>

int main()
{
    std::vector<int> v1;
    int i;
    while(std::cin>>i)
    {
        v1.push_back(i);
    }

    for(i : v1) //for (int i:v1) works
        std::cout<<i<<"\t";
    cout<<std::endl;
    return 0;
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/dca430ffec6a4c71b30a04d22ff08b66.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JfSW5ncmFt,size_16,color_FFFFFF,t_70)
[点我跳转到解决方案！！](https://www.itranslater.com/qa/details/2582481931048846336)

 ###  see you next blog~~