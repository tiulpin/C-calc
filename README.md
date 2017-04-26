# Калькулятор 0.3 (S2)

В качестве курсового проекта требуется написать программу — калькулятор,
умеющий вычислять значение арифметических выражений, которые задаются
пользователем в виде строки текста: `"3 * 2.5 / (2 + 2 * 7)"`.
Полное условие задания с актуальными изменениями доступно по ссылке:
[Калькулятор выражений](https://sites.google.com/site/yap1057/ii-semestr/kursovik).
* [data.c](https://github.com/iamm-pro/calc-tiulpin/blob/master/data.c) - модуль работы со стэком и обработки выражения в обратную польскую нотацию
* [other.c](https://github.com/iamm-pro/calc-tiulpin/blob/master/other.c) - модуль вспомогательных функций
* [calc.c](https://github.com/iamm-pro/calc-tiulpin/blob/master/calc.c) - модуль калькулятора выражений
* [main.c](https://github.com/iamm-pro/calc-tiulpin/blob/master/main.c) - функция main

[other.h](https://github.com/iamm-pro/calc-tiulpin/blob/master/other.h) | [calc.h](https://github.com/iamm-pro/calc-tiulpin/blob/master/calc.h) | [data.h](https://github.com/iamm-pro/calc-tiulpin/blob/master/data.h)
```
AM code style.
stage00:
- ок, идём дальше
stage01:
- ок, идем дальше (20 пройдено)
stage02:
- ок, идем дальше (143 пройдено)
stage03:
- ошибка, неверный ответ в выражении
- возможная причина - проблемы с унарным минусом, проверьте 3.3.1
- на тесте № 8 (строка 11)
```
https://github.com/iamm-pro/calc-tiulpin/archive/master.zip
