# Практическое задание 9. Git
## Задание на оценку 5

### 1. Создание ветки branch1
```
git checkout -b branch1
```

### 2. Выполним команду
```
echo "This is a relevant fact" > file.txt
```  
**Она через перенаправление потока вывода создаёт file.txt и записывает в него сообщение из echo**  

### 3. Закоммитим это изменение
```
git add .
git commit -m "file.txt"
```

### 4. Создание такого же файла на ветке main
```
git switch main
echo "This is an indispensable truth!" > file.txt
```

### 5. Коммитим изменение в master
![alt text](./screens/5/5.png)  

### 6. Журнал изменений
![alt text](./screens/5/6.png)  

### 7. Пробуем слить ветки
![alt text](./screens/5/7.png)  
**Получаем конфликт, поскольку в обоих ветках есть file.txt с разным содержимым на одних и тех же строках**  

### 8. git status:
![alt text](./screens/5/8.png)  

### 9. Содержимое файла file.txt
![alt text](./screens/5/9.png)  
**Отображается в каком месте у нас merge conflict, чтобы исправить, ножно убрать маркеры конфликта (<<<<<<<, ========, >>>>>>>), исправить файл и оставить только нужный текст, после этого закоммитить**

### 10. Журнал изменений
![alt text](./screens/5/10.png)  
**Отображается, что мы смержили main с branch1**

### 11. Запушим изменения
```
git push
```

# Merge конфликты для сортировки MergeSort на python.

### 1. Создадим `megesort.py`
![alt text](./screens/5/b1.png)  

### 2. Проиндексируем файл и закоммитим
![alt text](./screens/5/b2.png)  

### 3. Создадим ветку Mergesort-Impl и переключимся на неё
```
git checkout -b Mergesort-Impl
```

### 4. Заменим код из `mergesort.py`
![alt text](./screens/5/b4.png)  

### 5. Коммитим изменения
![alt text](./screens/5/b5.png)  

### 6. Переключаемся на master и меняем все содержимое `mergesort.py` на `lefty.py`
```
git switch main
```   
![alt text](./screens/5/b6.png)  

### 7. Коммитим изменения
![alt text](./screens/5/b7.png)  

### 8. Журнал изменений
![alt text](./screens/5/b8.png)  

### 9. git branch
![alt text](./screens/5/b9.png)  

### 10. Пробуем смержить Mergesort-Impl в main
```
git merge Mergesort-Impl
```  
**Получаем кучу merge-конфликтов**  
![alt text](./screens/5/b10.png)  

**Исправляем конфликт, вручную удаляя ненужные части кода. Я решил оставить реализацию из Mergesort-Impl**  

![alt text](./screens/5/b10.1.png)  

### 11. Запушим в master изменения
![alt text](./screens/5/b11.png)  
```
git push
```

### 12. Запушим документ с результатом работы
```
git add .
git commit -m "отчёт 5"
git push
```  