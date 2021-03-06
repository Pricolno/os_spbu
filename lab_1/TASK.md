# Лабораторная работа №1: C, язык ассемблера, инструментарий и загрузка ПК

Эта лабораторная работа полностью основывается на материалах [первой лабораторной
работы](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-828-operating-system-engineering-fall-2012/labs/MIT6_828F12_lab1.pdf) 
курса [MIT 6.828 Operating System Engineering](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-828-operating-system-engineering-fall-2012)
за некоторыми изменениями. В частности, в рамках работы необходимо выполнить все 
упражнения (см. Exercise 1–12 в PDF-файле). Процесс выполнения должен быть отражен 
в файле отчета `REPORT.md`, там же должны содержаться ответы на все вопросы, 
ставящиеся в упражнениях. 

## Изменения по сравнению с инструкциями MIT 6.828

Мы запускаем учебное ядро JOS в эмуляторе [QEMU](https://www.qemu.org/), который в свою очередь запускается в
системе Linux из [Docker](https://www.docker.com/) контейнера, находящегося под управлением [Vagrant](https://www.vagrantup.com/).
Такой способ запуска позволяет выполнять задания лабораторной работы независимо
от операционной системы, установленной на вашем компьютере. Мы поддерживаем Windows 10
(со всеми установленными обновлениями), Mac OS X последних версий и любые дистрибутивы Linux.

Это отличается от инфраструктуры, предлагаемой в MIT 6.828, поэтому соответствующие
инструкции изменяются.

### Развёртывание инфраструктуры лабораторной работы

Перед началом работы вы должны убедиться, что на вашей машине установлены
актуальные версии программного обеспечения:

- [Docker Desktop](https://docs.docker.com/get-docker/)
- [Vagrant](https://www.vagrantup.com/downloads)

Для запуска подготовленного образа системы Linux в docker-контейнере необходимо выполнить следующую команду в корневом
каталоге репозитория (при этом выполняются инструкции в файле `Vagrantfile`):
```
$ vagrant up
...
==> default: Machine booted and ready!
```
Эта команда скачивает необходимый docker-образ Linux со всем предустановленным
программным обеспечением (первый запуск может занять
продолжительное время) и запускает его в контейнере.

*Замечание*. В зависимости от способа установки Docker Desktop в Linux команды
Vagrant могут требовать прав суперпользователя. В этом случае их следует запускать 
через `sudo`, например: `sudo vagrant up`. 

### Подключение к docker-контейнеру по SSH

Далее мы подключаемся к работающему контейнеру по SSH и попадаем 
в командную строку контейнера:
```
$ vagrant ssh
vagrant@ea787ee71fde:~$ 
```

Именно в этой командной строке мы работаем с эмулятором QEMU. Каталог
`lab` текущей ветки синхронизирован с каталогом `/home/vagrant/lab` docker-контейнера.
SSH-сеанс стартует в каталоге `/home/vagrant`, поэтому сначала нужно перейти
в каталог с файлами лабораторной работы:
```
vagrant@ea787ee71fde:~$ cd lab
```

### Запуск ядра JOS в эмуляторе и под отладчиком gdb

Для компиляции и запуска ядра JOS в эмуляторе необходимо выполнить команду:
```
vagrant@ea787ee71fde:~/lab$ make qemu-nox
```

Для компиляции и запуска ядра JOS в эмуляторе под отладчиком `gdb` необходимо выполнить команду:
```
vagrant@ea787ee71fde:~/lab$ make qemu-nox-gdb
```

После этого следует запустить новый SSH-сеанс (`vagrant ssh`), 
перейти в каталог `lab` и запустить отладчик `gdb`.

Выход из gdb выполняется командой **quit**. Выход из QEMU — последовательностью
нажатий **Ctrl-a** и **x** (латиница!). Выход из SSH-сеанса — команда `exit`.

### Действия в процессе выполнения работы и отправка задания на проверку

В процессе выполнения упражнений вы должны заполнять отчёт в файле `REPORT.md`
и редактировать требуемые в упражнениях файлы.

Для проверки корректности выполнения упражнений последней части можно 
выполнить команду `make grade`.

По ходу выполнения работы изменённые файлы следует фиксировать 
в git-репозитории (add/commit) с соответствующими смыслу изменений 
сообщениями коммитов.
В конце работы все зафиксированные изменения должны быть отправлены 
на GitHub командой `git push origin lab1-dev`. Для отправки работы на проверку 
создайте пулл-реквест с ветки `lab1-dev` на ветку `lab1`.

### Остановка контейнера

Чтобы контейнер не потреблял ресурсы компьютера, пока вы не заняты выполнением
лабораторной работы, его следует останавливать:
```
$ vagrant destroy
    default: Are you sure you want to destroy the 'default' VM? [y/N] y
==> default: Stopping container...
==> default: Deleting the container...
```

Все изменения в файлах из репозитория при этом сохраняются.

Когда контейнер снова понадобится, достаточно будет выполнить `vagrant up` 
и подключиться к нему по SSH (`vagrant ssh`).