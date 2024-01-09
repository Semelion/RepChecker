# RepChecker

Приложение, проверяющее PDF-файл на формат опирающийся на ГОСТ 7.32-2017, с возможностью регулировки проверки формата.
Основная направленность проекта: помощь в проверке курсовых и проектных работ.
Не рекомендуется использование для проверки больших документов (> 100 страниц).

## Содержание
- [Функционал](#Функционал)
- [Используемые библиотекиы](#Используемые-библиотеки)
- [Начало работы](#начало-работы)
- [Модули в коде и ответственные за них](#Модули-в-коде-и-ответственные-за-них)

## Функционал
- Проверка размерности полей
- Проверка титульника
- Проверка Содержания
- Проверка нумерации страниц
- Междустрочный интервал
- Проверка шрифтов на размер
- Оформление изображений
- Оформление приложений
- Проверка текста на правописание*
- Оформление формул*
- Оформление таблиц


## Используемые библиотеки
Библиотеки, используемые в проекте, устанавливаемые при помощи vcpkg:

- PkgConfig (определение и плддержка единого интерфейса для запроса установленных библиотек)
- Tesseract (распознавание текста)
- OpenCV (компьютерное зрение)
- Poppler (рендеринг PDF-файлов)
- nlohmann/json (работа с форматом JSON)
- DoxyGen (генерация документации кода проекта)

## Начало Работы
Необходимо установить [используемые библиотекиы](#Используемые-библиотеки), рекомендуем устанавливать через [vcpkg](https://vcpkg.io).
Также потребуется система сборки [CMake](https://cmake.org).

Конфигурация проекта
*PATH_TO_TOOLCHAIN заменить при необходимости на путь до тулчейн файла (например до vcpkg)
```sh
$ cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=PATH_TO_TOOLCHAIN
```

Сборка проекта
```sh
$ cmake --build build --config Release
```

Установка проекта в удобную вам директорию
*PATH заменить на путь до директории куда установить собранный проект, например ./OUTPUT
```sh
$ cmake --install ./build  --prefix PATH
```
Далее в папке куда был инсталирован проект необходимо запустить исполняемый файл, в качестве параметра необходимо передать JSON файл с конфигурацией, пример файла - `example.json`, результат проверки сохраняется в JSON файл, путь и название которого указано в конфигурационном файле

Пример конфигурационного файла:
``` json
{
  "file_path": "test_docs/example.pdf",
  "output_path" : "errors.json",
  "dpi" : 300,

  "indents": {
    "left" : 30,
    "right" : 10,
    "up" : 20,
    "down" : 20,
    "fault" : 5
  },

  "title_admission" : 100.0,
  "format_fault" : 20
}

```


- `file_path` – путь до pdf файла, который необходимо проверить (в папке test_docs лежат pdf файлы для тестовой проверки)

- `output_path` – путь и файл куда будет записан результат
- `dpi` – количество точек на дюйм для рендера страниц

- `indents` – настройка проверки отступов
 - `left` – отступ слева
 - `right` – отступ справа
 - `up` – отступ сверху
 - `down` – отступ снизу
 - `fault` – погрешность

- `title_admission` – погрешность для проверки титульного листа
- `format_fault` – погрешность для проверки формата листа

Запуск программы:
Программу необходимо запустить передав путь до конфигурационного файла формата json, например:

``` bash
  ./main example.json
```


## Модули в коде и ответственные за них

## [Трафняк Семён](https://github.com/Semelion)
[Личное хранилище](https://github.com/Semelion/misis2023f-22-02-trafnyak-s-l)

### Разделитель страниц по заголовкам
Разбиение страниц по составляющим:
- Титульный лист
- Оглавление
- Основная часть
- Список литературы
- Приложения

### оформление изображений
- Проверка наличия подписи к изображению
- Проверка на соответсвие ГОСТ

### сборка модулей в конечное приложение
- написание обработки конфигурационного файла
- вызов проверок с заданными параметрами
- запись итогов проверки в файл
- поддержка архитектуры

## [Бабынина Ирина](https://github.com/irisich)
[Личное хранилище](https://github.com/irisich/misis2023f-22-02-babynina-i-i)

### Проверка соответствия содержания

- Проверка на наличие содержания в начале файла (считывание файла на наличие блока "Содержание", перед которым нет никаких блоков кроме титульника)
- Проверка оформления (все блоки перечисляются в правильном порядке;  нумерация соответствует реальной)
- В оглавлении не пропущены никакие блоки

##### На вход:
- Ссылка на массив cv::Mat с изображениями оглавления
- Первую и последнюю страницы, подходящие под задачу

##### На выход:
- Текст с ошибками

## Чекунова Марьяна
[Личное хранилище](https://github.com/marjana2213/misis2023f-22-02-chekunova-m-m.git)
### Проверка формата листа
- Проверка соотношений сторон каждой страницы

##### На вход:
- Ссылка на массив cv::Mat с изображениями страниц. Дополнительно: погрешность в мм (тип double), DPI (тип double).

##### На выход:
- Вектор значений формата листа (A0, A1, A2, A3, A4, A5, A6, not found), индексы которых соответствуют индексам страниц

### Поля. top, bottom, left, right
- Проверка отступа от полей(снизу, сверху, справа и слева)
- Проверка на соответсвие ГОСТ

##### На вход:
- Ссылка на массив cv::Mat с изображениями страниц. Дополнительно: DPI (тип double).

##### На выход:
- Двумерный вектор, который содержит в себе значения отступов в мм слева, справа, сверху и снизу соответственно для каждой страницы

## Исраилов Элнур
[Личное хранилище](https://github.com/e1graf/misis2023f-22-02-israilov-e-a)

### Проверка таблиц

- Проверка наличия упоминания таблицы и ее расположения (непосредстенно после упоминания в тексте)
- Проверка оформления (нумерация, названия граф и строк, примечания и сноски и др.)

##### На вход:
- Ссылка на массив cv::Mat с изображениями страниц

##### На выход:
- Текст с ошибками

## Теплов Георгий
[Личное хранилище](https://github.com/GTeplov/misis2023f-22-02-teplov-g-k)

### Проверка основных блоков

- Проверка документа на наличие всех основных блоков текста:
  1. заголовок;
  2. авторы;
  3. введение;
  4. основной текст;
  5. заключение;
  6. список источников.

##### На вход:
- Ссылка на массив cv::Mat с изображениями страниц

##### На выход:
- Текст с описанием ошибок

## Ванина Дарья
[Личное хранилище](https://github.com/daryavanina/misis2023f-22-02-vanina-d-a)
### Проверка титульной страницы


- Проверка титульной страницы
- Проверка согласно ГОСТу 7.32-2017
##### На вход:
- Ссылка на std::vector<cv::Rect> с прямоугольниками на первой странице
- Количество столбцов и строк первой страницы
- Погрешность
- dpi

##### На выход:
- Текст с ошибками
- Соответствие ГОСТу

## Клычков Степан
[Личное хранилище](https://github.com/zxccdw/misis2023f-22-03-klychkov-s-s)
### Проверка междустрочного интервала

- Проверка междустрочного интервала
- Проверка согласно ГОСТу 7.32-2017
##### На вход:
- Ссылка на массив cv::Mat с изображениями страниц

##### На выход:
- Текст с указанием страниц с нарушениями


## Петровский Даниил
[Личное хранилище](https://github.com/DaniilPetrovsliy/misis2023f-22-02-petrovskii-d-y)
### Проверить разметку таблиц в PDF файле
- Проверка наличие ошибок
- Проверка согласно ГОСТу 7.32-2017

##### На вход:
- Ссылка на массив cv::Mat с изображениями страниц PDF файла
##### На выходе:
- Текст с ошибками


## Железняк Александра

### Проверка правильного шрифта
- Распознать таймс нью роман
- Распознать высоту шрифта
- Проверка согласно ГОСТу 7.32-2017

##### На вход:
- Ссылка на массив cv::Mat с изображениями страниц PDF файла
##### На выходе:
- Текст с ошибками

## Анашкин Илья
[Личное хранилище](https://github.com/rofeleo/misis2023f-22-02-anashkin-i-a)
### Задача разделения данных зон на помеченные зоны (м. б. меньшего размера) (классификация).

##### На вход:
- Координаты прямоугольников, содержащих в своих границах текст, изображения, таблицы, заголовки и т. д.

##### На выходе:
- тип содержимого зоны.
