# Отчет по лабораторной работе №3

**Автор**: Наумцев Аелксандр

**Группа**: Б05

# Questions

## Part 1
## Exercise 1
>Compute the response time and turnaround time when running
three jobs of length 200 with the SJF and FIFO schedulers.


```shell
./cpu-sched/scheduler.py -p FIFO -l 200,200,200 -c
ARG policy FIFO
ARG jlist 200,200,200

Here is the job list, with the run time of each job: 
Job 0 ( length = 200.0 )
Job 1 ( length = 200.0 )
Job 2 ( length = 200.0 )


** Solutions **

Execution trace:
[ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
[ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
[ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )

Final statistics:
Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
```


```shell
./cpu-sched/scheduler.py -p SJF -l 200,200,200 -c
ARG policy SJF
ARG jlist 200,200,200

Here is the job list, with the run time of each job: 
Job 0 ( length = 200.0 )
Job 1 ( length = 200.0 )
Job 2 ( length = 200.0 )


** Solutions **

Execution trace:
[ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
[ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
[ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )

Final statistics:
Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
```


## Exercise 2
>Now do the same but with jobs of different lengths: 100, 200, and
>300.

```shell
./scheduler.py -p FIFO -l 100,200,300 -c
ARG policy FIFO
ARG jlist 100,200,300

Here is the job list, with the run time of each job: 
Job 0 ( length = 100.0 )
Job 1 ( length = 200.0 )
Job 2 ( length = 300.0 )


** Solutions **

Execution trace:
[ time   0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
[ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
[ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )
m
Final statistics:
Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00

Average -- Response: 133.33  Turnaround 333.33  Wait 133.33

```

```shell
./scheduler.py -p SJF -l 100,200,300 -c
ARG policy SJF
ARG jlist 100,200,300

Here is the job list, with the run time of each job: 
Job 0 ( length = 100.0 )
Job 1 ( length = 200.0 )
Job 2 ( length = 300.0 )


** Solutions **

Execution trace:
[ time   0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
[ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
[ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )

Final statistics:
Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00

Average -- Response: 133.33  Turnaround 333.33  Wait 133.33
```

## Exercise 3
> Now do the same, but also with the RR scheduler and a time-slice
of 1.

```shell
./scheduler.py -p RR -q 1 -l 100,200,300 -c
ARG policy RR
ARG jlist 100,200,300

Here is the job list, with the run time of each job: 
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job   0 for 1.00 secs
  [ time   1 ] Run job   1 for 1.00 secs
  [ time   2 ] Run job   2 for 1.00 secs
  [ time   3 ] Run job   0 for 1.00 secs
  [ time   4 ] Run job   1 for 1.00 secs
  [ time   5 ] Run job   2 for 1.00 secs
  [ time   6 ] Run job   0 for 1.00 secs
...
  [ time 596 ] Run job   2 for 1.00 secs
  [ time 597 ] Run job   2 for 1.00 secs
  [ time 598 ] Run job   2 for 1.00 secs
  [ time 599 ] Run job   2 for 1.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 298.00  Wait 198.00
  Job   1 -- Response: 1.00  Turnaround 499.00  Wait 299.00
  Job   2 -- Response: 2.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 1.00  Turnaround 465.67  Wait 265.67


```

## Exercise 4
>For what types of workloads does SJF deliver the same turnaround
times as FIFO?

Если подавать процессы на обработку в порядке возрастания длины, то время обработки SJF и FIFO будет одинаковая. Если будет не возрастающая  последвальность длин, то SJF будет иметь меньшее время обработки. 

    ./scheduler.py -p SJF -l 300,200,100 -c
    ./scheduler.py -p FIFO -l 300,200,100 -c

## Exercise 5
>For what types of workloads and quantum lengths does SJF deliver
the same response times as RR?

Простой пример, когда длины всех процессов равны и равны квантому. Тогда время отклика будет у двух алгоритмов одинаковая.


## Exercise 6
>What happens to response time with SJF as job lengths increase?
Can you use the simulator to demonstrate the trend?

Заметим, что если длину умножим на k, то и время отклика увеличится в k раз. Тогда можно предположить, что время  изменяется примерно пропорционально.  

    ./scheduler.py -p SJF -l 1, 2, 3 -c
    ./scheduler.py -p SJF -l 3, 6, 8 -c
    ./scheduler.py -p SJF -l 9, 12, 24 -c

## Exercise 7

>What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?

Если квант времени становится больше чем длина каждого процесса, то время отклика саммого долгого процесса равна сумме длин других процессоров. Если взять q - квант времени, то (N - 1)q - будет ждать отклика последний процесс. 


## Part 2 
## Exercise 1
>Compute the solutions for simulations with 3 jobs and random seeds
of 1, 2, and 3.

```shell
python3 lottery.py -j 3 -s 1 -c
ARG jlist 
ARG jobs 3
ARG maxlen 10
ARG maxticket 100
ARG quantum 1
ARG seed 1

Here is the job list, with the run time of each job: 
  Job 0 ( length = 1, tickets = 84 )
  Job 1 ( length = 7, tickets = 25 )
  Job 2 ( length = 4, tickets = 44 )


** Solutions **

Random 651593 -> Winning ticket 119 (of 153) -> Run 2
...

```

```shell
python3 lottery.py -j 3 -s 2 -c
ARG jlist 
ARG jobs 3
ARG maxlen 10
ARG maxticket 100
ARG quantum 1
ARG seed 2

Here is the job list, with the run time of each job: 
  Job 0 ( length = 9, tickets = 94 )
  Job 1 ( length = 8, tickets = 73 )
  Job 2 ( length = 6, tickets = 30 )


** Solutions **

...

```

```shell 
 python3 lottery.py -j 3 -s 3 -c
ARG jlist 
ARG jobs 3
ARG maxlen 10
ARG maxticket 100
ARG quantum 1
ARG seed 3

Here is the job list, with the run time of each job: 
  Job 0 ( length = 2, tickets = 54 )
  Job 1 ( length = 3, tickets = 60 )
  Job 2 ( length = 6, tickets = 6 )


** Solutions **

Random 13168 -> Winning ticket 88 (of 120) -> Run 1
...

```

## Exercise 2

>Now run with two specific jobs: each of length 10, but one (job 0)
with just 1 ticket and the other (job 1) with 100 (e.g., -l 10:1,10:100).
What happens when the number of tickets is so imbalanced? Will
job 0 ever run before job 1 completes? How often? In general, what
does such a ticket imbalance do to the behavior of lottery scheduling?

Для того чтобы 1 процесс выполнился перед 0 процессом, нужно выпадение 10 подряд нужного билета. (100/101) ^ 10  это примерно 0.9, тогда шанс обратного 0.1. Из-за такого дисбаланса у нас и получается последовательный планировщик.

## Exercise 3
>When running with two jobs of length 100 and equal ticket allocations of 100 (-l 100:100,100:100), how unfair is the scheduler?
Run with some different random seeds to determine the (probabilistic) answer; let unfairness be determined by how much earlier one
job finishes than the other.



```shell

python3 lottery.py -j 2 -l 100:100,100:100 -c -s 1
  
  --> JOB 1 DONE at time 196
  --> JOB 0 DONE at time 200

```
Unfairness Metric = 196/200 = 0.98


```shell
python3 ./lottery.py -j 2 -l 100:100,100:100 -c -s 2

--> JOB 1 DONE at time 190
--> JOB 0 DONE at time 200

```

Unfairness Metric = 190/200 = 0.95


```shell
python3 ./lottery.py -j 2 -l 100:100,100:100 -c -s 3

--> JOB 0 DONE at time 196
--> JOB 1 DONE at time 200

```

Unfairness Metric = 196/200 = 0.98

## Exercise 4

How does your answer to the previous question change as the quantum size (-q) gets larger?

q = 1 Unfairness Metric = 0.98  
q = 2 Unfairness Metric = 0.97  
q = 3 Unfairness Metric = 0.985  
q = 4 Unfairness Metric = 0.94  
q = 5 Unfairness Metric = 0.95  
q = 6 Unfairness Metric = 0.941  
q = 7 Unfairness Metric = 0.866  

Видно, что справедливость падает с увеличением длины квантума.
