# MakeFile

### 前

```shell
g++ -M main.cc # 打印依赖关系
g++ -MM main.cc # 打印依赖关系
```

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

或者，我们也可以通过伪目标来实现，由于target是一个真实目标，所以makefile会生成它，使用伪目标，会让makefile明白，不需要生成这个目标，需要进行显示指定才能运行！

```makefile
.PHONY : clean # .PHONY是一个特殊的makefile标示，它使得后面的目标成为伪目标
clean : # clean操作，使用方式为make clean
    -rm -f *.o 
```

<font color=F0000> clean中的命令使用的是当前的shell来执行的，makefile在执行的时候也可以使用-n或者--just-print来调试执行了什么命令，它会打印命令，并且不会执行对应的命令，使用-s或者--silent全面禁止命令显示。makefile一行行执行命令，如过出现命令错误或者失败，直接中断，使用-符号可以使得makefile无视一些错误继续执行。 </font>

```makefile
clean1:
    echo "正在执行make clean1..."
    -rm -f *.o
    
clean2:
    @echo "正在执行make clean2..."
    -rm -f *.o
```

上面的两个echo指令区别在于第一个不仅会打印echo的内容，连命令都会被打印出来，也就是

```shell
echo "正在执行make clean1..."
正在执行make clean1...
```

而第二个clean命令将只输出字符串内容

```shell
正在执行make clean2...
```


### 五大重要的makefile东西

* 显示规则: 显示规则说明了如克生成或者多个目标文件
* 隐晦规则: make自动推导功能
* 变量: 我们可以定义一系列变量来简化书写makefile，类似C语言中define指令

```makefile
objects = *.o # 这个变量数值真的为"*.o"，而不是所有.o文件
objects := $(wildcard *.o) # 变量数值为全部到.o文件
```

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

### 文件搜索

makefile中有些特殊的变量，其中有个变量名为 `VPATH` 代表makefile在生成文件时所寻找的依赖文件所在的目录，当然最高优先级还是在当前目录下。

```makefile
VPATH = src:include
```

如果标明VPATH，那么makefile将在当前目录下找不到的情况下，按顺序在src和include中进行依赖文件的查找。即，引出chapter01的另外一个版本。

```makefile
VPATH = src:include
depends = main.cc A.o B.o Bind.o
A_depends = A.h A.cc
B_depends = B.h B.cc
Bind_depends = Bind.h Bind.cc A.h B.h \
    A.cc B.cc

chapter01: $(depends)
    g++ -o chapter01 $(depends)
    
A.o: $(A_depends)
    g++ -c $(A_depends)
    
B.o: $(B_depends)
    g++ -c $(B_depends)
    
Bind.o: $(Bind_depends)
    g++ -c $(Bind_depends)

clean:
    -rm -f A.o B.o Bind.o
```

### 自动变量

使用vpath关键字的时候，更多时候需要makefile来为我们自动补全路径信息，这就需要用到自动变量

```makefile
$@ # 表示规则的目标文件名字

target1 : $(depends)
    command...
    
# 以上$@如果在command中使用，得到的就将是target1
```

```makefile
$^ # 表示依赖的所有文件，如果需要加入路径信息，则自动加入

target2 : $(depends)
    command...
    
# 以上$^使用在command中将得到$(depends)中的所有文件，并且会自动加入路径信息
```

```makefile
$< # 表示依赖的第一个文件！类似$^，只不过没有那么多文件

target3 : $(depends)
    command...
    
# 以上$< 使用后将得到$(depends)的第一依赖文件
```

```makefile
$? # 所有比目标文件更 新的依赖文件

target4 : $(depends)
    command...
    
# 以上如果使用了$?，$(depends)中有文件更新了，那么将使得$?等同于更新的文件

```






