# RepChecker

Приложение, проверяющее PDF-файл на формат опирающийся на ГОСТ 7.32-2017, с возможностью регулировки проверки формата.
Основная направленность проекта: помощь в проверке курсовых и проектных работ.
Не рекомендуется использование для проверки больших документов (> 100 страниц).

## Содержание
- [Функционал](#Функционал)
- [Используемые библиотекиы](#Используемые-библиотеки)
- [Начало работы](#начало-работы)
- [TO do](#To-do)
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

## To do
- [ ] Добавить крутое README
- [ ] Составить список задач заново
- [ ] Всё переписать
- [ ] Написать хоть что-то
- [ ] ...

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

## Бабынина Ирина 

### Проверка списка литературы

- Проверка на наличие списка литературы в конце файла (считывание файла на наличие блока "Список литературы", после которого нет никаких блоков, отличных от Приложений)
- Проверка оформления (ссылки идут в алфавитном порядке;  все юридические документы перечислены в начале (при наличии))
- Описание книг и статей соответствует правилам ( Заголовок (Ф. И. О. автора); Основное заглавие: сведения, относящиеся к заглавию (учебники, учебные пособия, справочники и др.) / сведения об ответственности(авторы, составители, редакторы идр.);  Сведения о переиздании (2-е  изд,   прераб. и  доп.); Место издания (город);  Издательство, год издания;  Объем (кол-во страниц))

##### На вход:
- Ссылка на массив cv::Mat с изображениями страниц
- Первую и последнюю страницы, подходящие под задачу

##### На выход:
- Текст с ошибками

## Чекунова Марьяна
[Личное хранилище](https://github.com/marjana2213/misis2023f-22-02-chekunova-m-m.git)
### Проверка формата листа
- Проверка соотношений сторон каждой страницы 
  
##### На вход:
- Ссылка на массив cv::Mat с изображениями страниц

##### На выход:
- Массив булевых значений, индексы которых соответсвуют индексам страниц

### Поля. top, bottom, left, right
- Проверка отступа от полей(снизу, сверху, справа и слева)
- Проверка на соответсвие ГОСТ

##### На вход:
- Ссылка на массив cv::Mat с изображениями страниц

##### На выход:
- Массив булевых значений, индексы которых соответсвуют индексам страниц

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

### Проверка текста на правописание

- Проверка на наличие грамматических ошибок в документе
- Проверка пунктуационных ошибок
  
##### На вход:
- Текст документа

##### На выход:
- Описание ошибок

- ## Ванина Дарья
[Личное хранилище](https://github.com/daryavanina/misis2023f-22-02-vanina-d-a)
### Проверка оформления приложений

- Проверка на наличие приложений в конце файла (считывание файла на наличие блока "Приложения")
- Проверка согласно ГОСТу 7.32-2017
##### На вход:
- Ссылка на массив cv::Mat с изображениями страниц
- Страницы, подходящие под задачу

##### На выход:
- Текст с ошибками

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
