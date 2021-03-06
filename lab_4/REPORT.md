# Отчет по лабораторной работе №4

**Автор**: Наумцев Александр

**Группа**: Б05

# Questions

## Part 1
## Exercise 1
>First, write a simple program called null.c that creates a pointer
to an integer, sets it to NULL, and then tries to dereference it. Compile this into an executable called null. What happens when you
run this program?

```shell

#include <stdio.h>

int main()
{
	int* a = NULL;
	//*a;
	int c = *a;


	printf("Hello\n");
	return 0;
}
```

Если разыминовать и присвоить,то получим 

```shell
	Segmentation fault (core dumped)
```

но, если не присваивать, а просто разыминовать, то это работает. Это отличный пример, что работает - не значит правильно. (Возможно компилятор просто пропускает эту строчку, так как она ни на что не влияет (в каком-то смысле))

```shell

#include <stdio.h>

int main()
{
	int* a = NULL;
	*a;
	//int c = *a;


	printf("Hello\n");
	return 0;
}
```


## Exercise 2
> Next, compile this program with symbol information included (with
the -g flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information
about variable names and the like. Run the program under the debugger by typing gdb null and then, once gdb is running, typing
run. What does gdb show you?

```shell
Program received signal SIGSEGV, Segmentation fault.
0x0000555555555161 in main () at null.c:9
9		int c = *a;

```

## Exercise 3
>Finally, use the valgrind tool on this program. We’ll use the memcheck
tool that is a part of valgrind to analyze what happens. Run
this by typing in the following: valgrind --leak-check=yes
null. What happens when you run this? Can you interpret the
output from the tool?

Не получается считать 4 бита под int,  потому что null (0x0) хранит 0 байт информации (от него нельзя смещаться)

```shell
==360578== Invalid read of size 4
==360578==    at 0x109161: main (null.c:9)
==360578==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
```

## Exercise 4
>Write a simple program that allocates memory using malloc() but
forgets to free it before exiting. What happens when this program
runs? Can you use gdb to find any problems with it? How about
valgrind (again with the --leak-check=yes flag)?

Исполняемый файл запускается без ошибок, также и под gdb. 
Под valgrind находит утечку 4 * 50 байт (50  int - как и ожидалось)

```shell
==361402== 200 bytes in 1 blocks are definitely lost in loss record 1 of 1
==361402==    at 0x4843839: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==361402==    by 0x10918C: main (q4.c:9)

```


## Exercise 5
>Write a program that creates an array of integers called data of size
100 using malloc; then, set data[100] to zero. What happens
when you run this program? What happens when you run this
program using valgrind? Is the program correct?

Программа завершится без ошибки, но valgrind скажет, что 
* записать 4 бита не получилось (int -> data[100]) 

```shell
==361736== Invalid write of size 4
==361736==    at 0x1091A5: main (q5.c:11)
==361736==  Address 0x4a8e1d0 is 0 bytes after a block of size 400 alloc'd
==361736==    at 0x4843839: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==361736==    by 0x10918C: main (q5.c:9)
==361736== 
Hello

```

* и не освободили память, выделного массива в конце 

```shell
400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==361736==    at 0x4843839: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==361736==    by 0x10918C: main (q5.c:9)

```

Программа написано с ошибкой, нужно очистить массив в конце и изменять значения только в зарезервированной памяти (Тонкий вопрос, так как мы могли попасть на другой кусок зарезервированной памяти, но это должно наверное отслеживаться, что мы прыгнули дальше от чего смещались - так как внутри хранятся таблица с началами и длиной выделенной памяти). 

И перезатирать чужую память плохо.

## Exercise 6
>Create a program that allocates an array of integers (as above), frees
them, and then tries to print the value of one of the elements of
the array. Does the program run? What happens when you use
valgrind on it?

Программа запускается корректно и выводит 0. Но valgrind говорит, что есть проблема чтения 4 байт (data[5]). Действительно, мы обращаемся к уже освобождённой и не нашей памяти. И теперь, в конце нету утечек.

```shell
==362570== Invalid read of size 4
==362570==    at 0x1091E5: main (q6.c:12)
==362570==  Address 0x4a8e054 is 20 bytes inside a block of size 400 free'd
==362570==    at 0x484621F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362570==    by 0x1091DC: main (q6.c:11)
==362570==  Block was alloc'd at
==362570==    at 0x4843839: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==362570==    by 0x1091CC: main (q6.c:9)

```

## Exercise 7

>Now pass a funny value to free (e.g., a pointer in the middle of the
array you allocated above). What happens? Do you need tools to
find this type of problem?

Запуск программы возращает ошибку при free() и падает(Видимо, очищать можно только парно с malloc()). Поэтому пользоваться другими инструментами нету необходимости.

```shell
free(): invalid pointer
Aborted (core dumped)

```

## Exercise 8

>Try out some of the other interfaces to memory allocation. For example, create a simple vector-like data structure and related routines that use realloc() to manage the vector. Use an array to
store the vectors elements; when a user adds an entry to the vector, use realloc() to allocate more space for it. How well does
such a vector perform? How does it compare to a linked list? Use
valgrind to help you find bugs.

Главная идея vector - это динамическое изменения памяти, если нужно увеличить размер массива, то увеличиваем в 2 раза (будем поддерживать равным степени 2). sz - настоящий размер, cp = 2^k - размер выделенной памяти. Тогда память и время выделённое на перевыделение и перекопирование линейное с const = 2. 

Короткая реализация лежит в vector.c vector.h пользуемся,

* realloc
* calloc
* malloc

Для очищения памяти, не забываем реализовать функция удаления.


## Part 2
## Exercise 1
>Generate random addresses with the following arguments: -s 0
-n 10, -s 1 -n 10, and -s 2 -n 10. Change the policy from
FIFO, to LRU, to OPT. Compute whether each access in said address
traces are hits or misses.

```shell 
./paging-policy.py -s 0 -n 10 -c
./paging-policy.py -s 0 -n 10 -c --policy=LRU
./paging-policy.py -s 0 -n 10 -c --policy=OPT

```


```shell
./paging-policy.py -s 1 -n 10 -c
./paging-policy.py -s 1 -n 10 -c --policy=LRU
./paging-policy.py -s 1 -n 10 -c --policy=OPT

```


```shell
./paging-policy.py -s 2 -n 10 -c
./paging-policy.py -s 2 -n 10 -c --policy=LRU
./paging-policy.py -s 2 -n 10 -c --policy=OPT

```

## Exercise 2
>For a cache of size 5, generate worst-case address reference streams
for each of the following policies: FIFO, LRU, and MRU (worst-case
reference streams cause the most misses possible. For the worst case
reference streams, how much bigger of a cache is needed to improve
performance dramatically and approach OPT?

```shell
./paging-policy.py --addresses=0,1,2,3,4,5,0,1,2,3,4,5 --policy=FIFO --cachesize=5 -c


FINALSTATS hits 0   misses 12   hitrate 0.00
```

```shell
./paging-policy.py --addresses=0,1,2,3,4,5,0,1,2,3,4,5 --policy=LRU --cachesize=5 -c

FINALSTATS hits 0   misses 12   hitrate 0.00
```

```shell
./paging-policy.py --addresses=0,1,2,3,4,5,4,5,4,5,4,5 --policy=MRU --cachesize=5 -c

FINALSTATS hits 0   misses 12   hitrate 0.00
```

Увеличить кеш-память до кол-во адресов.

## Exercise 3
>Generate a random trace (use python or perl). How would you
expect the different policies to perform on such a trace?


Примерно одинакого все отстают до OPT, но RAND и FIFO  работают чуть лучше остальных. (На конкретной строке)

```shell 
./paging-policy.py -s 20 -n 100 -c
FINALSTATS hits 33   misses 67   hitrate 33.00

./paging-policy.py -s 20 -n 100 -c --policy=LRU
FINALSTATS hits 28   misses 72   hitrate 28.00

./paging-policy.py -s 20 -n 100 -c --policy=OPT
FINALSTATS hits 50   misses 50   hitrate 50.00

./paging-policy.py -s 20 -n 100 -c --policy=RAND
FINALSTATS hits 34   misses 66   hitrate 34.00

./paging-policy.py -s 20 -n 100 -c --policy=CLOCK
FFINALSTATS hits 28   misses 72   hitrate 28.00


```

## Exercise 4
>Now generate a trace with some locality. How can you generate
such a trace? How does LRU perform on it? How much better than
RAND is LRU? How does CLOCK do? How about CLOCK with
different numbers of clock bits?

Зафиксируем trace со "свойством локальности" (после обращения к адресу, большая вероятность обратится к нему же скоро). (./gen-trace.py - например, с вероятностью probPass выбирает равновероятно из последних lastCnt адресов) 

```shell 
python3 ./gen-trace.py 
8,8,4,4,5,5,3,8,5,3,8,8,0,7,6,7,7,2,8,9,8,5,5,5,5,0,0,0,0,8
```

```shell
./paging-policy.py --addresses=8,8,4,4,5,5,3,8,5,3,8,8,0,7,6,7,7,2,8,9,8,5,5,5,5,0,0,0,0,8 --policy=OPT -c

FINALSTATS hits 19   misses 11   hitrate 63.33


./paging-policy.py --addresses=8,8,4,4,5,5,3,8,5,3,8,8,0,7,6,7,7,2,8,9,8,5,5,5,5,0,0,0,0,8 --policy=LRU -c
FINALSTATS hits 17   misses 13   hitrate 56.67


./paging-policy.py --addresses=8,8,4,4,5,5,3,8,5,3,8,8,0,7,6,7,7,2,8,9,8,5,5,5,5,0,0,0,0,8 --policy=RAND -c

FINALSTATS hits 15   misses 15   hitrate 50.00

./paging-policy.py --addresses=8,8,4,4,5,5,3,8,5,3,8,8,0,7,6,7,7,2,8,9,8,5,5,5,5,0,0,0,0,8 --policy=CLOCK -c -b 2

FINALSTATS hits 16   misses 14   hitrate 53.33


./paging-policy.py --addresses=8,8,4,4,5,5,3,8,5,3,8,8,0,7,6,7,7,2,8,9,8,5,5,5,5,0,0,0,0,8 --policy=CLOCK -c -b 1

FINALSTATS hits 15   misses 15   hitrate 50.00

python3 ./paging-policy.py --addresses=8,8,4,4,5,5,3,8,5,3,8,8,0,7,6,7,7,2,8,9,8,5,5,5,5,0,0,0,0,8 --policy=CLOCK -c -b 4

FINALSTATS hits 19   misses 11   hitrate 63.33

```