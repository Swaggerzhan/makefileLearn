# MakeFile


### make工作方式

使用make命令使得在当前目录下寻找一个叫Makefile或者makefile的文件。

找到这个文件，第一个目标文件(这里我们叫它target)即为最终输出文件。

如果target不存在，则我们通过命令来生成它，也就是依赖。

如果所依赖的文件也不存在，则我们再向下找，直到找到生成这个依赖文件的命令。

整个寻找的过程就是一个依赖的过程，通过层层依赖，最终生成目标文件，如果某个依赖没有找到，则就失败。

makefile的命令行必定要以/tab开头！

* 变量命名

```makefile
# makefile_01
# 普通版本的makefile
chapter01 : A.o B.o Bind.o
	g++ -o chapter01 A.o B.o Bind.o main.cc

A.o 	: include/A.h src/A.cc
	g++ -c include/A.h src/A.cc

B.o 	: include/B.h src/B.cc
	g++ -c include/B.h src/B.cc

Bind.o 	: A.o B.o include/Bind.h src/Bind.cc
	g++ -c include/Bind.h src/Bind.cc
```

这种方式有一个缺点，就是当某个.o文件需要跟新其依赖的时候，很多地方的依赖都需要修改，当文件较小的时候，可以手动修改，当文件过大的时候，手动修改就非常的费时，所以这时就需要变量。

将makefile修改成以下版本: 

```makefile
depends = main.cc A.o B.o Bind.o
A_depends = include/A.h src/A.cc
B_depends = include/B.h src/B.cc
Bind_depends = include/Bind.h src/Bind.cc include/A.h include/B.h \
	src/A.cc src/B.cc

chapter01: $(depends)
	g++ -o chapter01 $(depends)
    
A.o: $(A_depends)
	g++ -c $(A_depends)
    
B.o: $(B_depends)
	g++ -c $(B_depends)
    
Bind.o: $(Bind_depends)
	g++ -c $(Bind_depends)

clean:
	rm A.o B.o Bind.o chapter01
```

在写clean动作的时候，需要将其放到最后，避免clean动作被当成默认动作，并且，`rm`改为`-rm` 。

```makefile
clean:
    -rm target $(depends) # -rm可以忽略某些文件出现问题
```

### 五大重要的makefile东西

* 显示规则: 显示规则说明了如克生成或者多个目标文件
* 隐晦规则: make自动推导功能
* 变量: 我们可以定义一系列变量来简化书写makefile，类似C语言中的字符串类型变量
* 文件指示: 引用其他makefile，类似C语言中的include
* 注释: 类似C的//，不过makefile一般使用#

文件指示使用

```makefile
include <filename> # 引用文件 filename，如以下使用
include foo.make # 引用文件 foo.make
include *.make # 引用当前目录下所有make文件
# include前面可以有空格，但绝对不能是/tab
-include <filename> # 无视错误，如果找不到filename，就忽略
```

include的实现方式就跟C里面的define指令一样，直接将对应makefile文件中的字符串复制到include指令处。


### 建议书写方式

```makefile
foo.o: foo.c defs.h # foo 模块
    cc -c -g foo.c
```

语法是: 

```makefile
target : prerequisites
    command # 前面为table
    ...
# 又或者使用分号
target : prerequisites; command
...
```


