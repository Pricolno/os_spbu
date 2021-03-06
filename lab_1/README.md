# Операционные системы 2022 (МКН СПбГУ)
## Репозиторий для лабораторных работ

### Общая структура репозитория и порядок работы с ним

Этот репозиторий предназначен для получения заданий и
выполнения лабораторных работ по курсу операционных систем
на факультете МКН СПбГУ. Склонируйте его любым образом на локальную машину.

Задания лабораторных работ будут публиковаться в ветках `labN`, где `N` — номер лабораторной работы.
Решения необходимо помещать в ветки `labN-dev`. Для отправки
решения достаточно создать пулл-реквест с ветки `labN-dev` на ветку `labN`.

Текст задания конкретной лабораторной работы находится в файле `TASK.md` соответствующей ветки.
Все выполненные лабораторные работы должны сопровождаться файлом отчёта `REPORT.md`, из которого должно быть понятно, 
кем, что и в каком порядке выполнялось в рамках работы. Там же следует приводить ответы на все вопросы, содержащиеся 
в упражнениях. Необходимо следить за аккуратностью оформления отчёта и тем, как он выглядит на GitHub 
(используйте [Github-flavored Markdown](https://github.github.com/gfm/)).
Полнота и качество отчёта влияет на итоговый балл за лабораторную работу.

#### Пример: начало работы с первой лабораторной работой

```
$ git checkout -b lab1-dev origin/lab1     # создаем ветку для работы с лабораторной работой №1
```

#### Пример: завершение работы с первой лабораторной работой

После завершения работы над лабораторной работой ветку с зафиксированным решением (add/commit) следует отправить на сервер: 
```
$ git push origin lab1-dev
```

После этого достаточно создать пулл-реквест с ветки `lab1-dev` (`compare: lab1-dev`) на ветку `lab1` (`base: lab1`), 
чтобы проверяющему стали видны все ваши изменения.