Как собрать проект

1. Запустить терминал в папке проекта (например):
    ![alt text](images/1.png)

2. Запустить сам код, предварительно убедившись в наличии следующих библиотек:
    - tkinter
    - psycopg2
    - pandas

    Для простоты можно просто ввести следующие команды в терминал:<br>
        `pip install tkinter`<br>
        `pip install psycopg2`<br>
        `pip install pandas`<br>
    
    Как запустить код:<br>
    ![alt text](images/2.png)<br>
    `python.exe .\main.py`

3. Как пользоваться? (Куда жмать?)

    После запуска кода нас встречает следующий UI: <br>
    <img src="images/3.png" alt="Alt text" width="1000"/> <br>

    Для работы с БД - её нужно создать. Нажав на вполне логичную кнопку `Create DB` нас посетит ошибка. Даже ошибки.<br>
    Их мы **ВНИМАТЕЛЬНО ЧИТАЕМ** и потом переходим к следующему шагу:

    Нас интересует кнопка `Enter Login Form`. После нажатия на нее появится окно подключения.<br>
    Для простоты использования введем следующие данные:

    ![alt text](images/4.png)<br>
    Нам нужен именно СУПЕРПОЛЬЗОВАТЕЛЬ!

    Теперь мы можем нажать на заветную кнопку `Create DB` и увидеть сообщение: <br>
    <img src="images/5.png" alt="Alt text" width="800"/> <br>

    Снова возвращаемся к кнопке `Enter Login Form`, но теперь нам нужно подключаться к новосозданной БД:
    ![alt text](images/6.png)<br>
    Нам опять же нужен именно СУПЕРПОЛЬЗОВАТЕЛЬ!

    Теперь нажимаем на кнопку `Fill DB` и мы должны увидеть сообщение:
    ![alt text](images/7.png)<br>
    
    Теперь мы можем подключиться к БД с новой роли `driving_school_manager` с соответствующим паролем (p.s. его можно найти в файле `role.sql`) и начать вводить запросы от имени этого пользователя.

    Для исполнения введеного в окошке запроса (левое) нажимаем на кнопку `Process Query`

    Для очищения окошка вывода (правое) нажимаем на кнопку `Clear`