## Как собрать проект

1. Скачать `docker-compose.yml`<br>
2. Прописать в терминале `docker-compose up -d`<br>


## Как пользоваться? (Куда жмать?)

1. Нас интересует кнопка `Enter Login Form`. После нажатия на нее появится окно подключения.<br>
Для использования БД введем следующие данные:

| Поле              | Что ввести   |
| :---------------- | -----------: |
| Host              |   database   |
| Port              |   5432   |
| Database          |  driving_school   |
| User              |  driving_school_manager   |
| Password          |  pswrd   |

Теперь мы можем начать вводить запросы от имени этого пользователя.

Для исполнения введеного в окошке запроса (левое) нажимаем на кнопку `Process Query`

Для очищения окошка вывода (правое) нажимаем на кнопку `Clear`

## Проблемы

На Windows 10 наш контейнер не будет работать, так как у Docker нету окна вывода. Для использования проекта нам понадобится ПО `VcXsrv`<br>
Установив `VcXsrv` и запустив `XLaunch`, нам нужно будет выбрать следующие параметры:

| Параметр              | Что Выбрать   |
| :---------------- | -----------: |
| Select display settings | One large window |
| Display Number | -1 |
| Переходим на | следующую страницу |
| Start no client |  |
| Переходим на | следующую страницу |
| Disable access control | Необходимо, чтобы Docker мог подключится к виртуальному экрану |
| Переходим на | следующую страницу |
| Нажимаем на | "Finish" |

После всего этого мы можем запустить все контейнеры и начать пользоваться проектом
