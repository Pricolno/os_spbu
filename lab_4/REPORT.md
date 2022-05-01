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