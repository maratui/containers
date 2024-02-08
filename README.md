# containers (Linux, Mac)

- Программа разработана на языке C++.
- Код программы находится в папке src.
- При написании кода придерживался Google Style.
- Использовал итераторы.
- Классы шаблонные.
- Подготовлено полное покрытие unit-тестами методов контейнерных классов c помощью библиотеки GTest.
- Соблюдена логика работы стандартной библиотеки шаблонов (STL) (в части проверок, работы с памятью и поведения в нештатных ситуациях)

### Реализация библиотеки containers.h

Реализовал классы: `list` (список), `map` (словарь), `queue` (очередь), `set` (множество), `stack` (стек), `vector` (вектор).
- Оформил решение в виде заголовочного файла `s21_containers.h`, который включает в себя другие заголовочные файлы с реализациями необходимых контейнеров (`s21_list.h`, `s21_map.h` и т.д.).
- Предусмотрен Makefile для тестов написанной библиотеки (с целями clean, test).

### Реализация библиотеки containersplus.h

Реализовал классы: `array` (массив), `multiset` (мультимножество).
- Оформил решение в виде заголовочного файла `s21_containersplus.h`, который включает в себя другие заголовочные файлы с реализациями необходимых контейнеров (`s21_array.h`, `s21_multiset.h`)
- Предусмотрен Makefile для тестов написанной библиотеки (с целями clean, test).
