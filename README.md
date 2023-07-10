# LifeLib

![Logo](Logo.svg)

## Описание

The Life - игра "Жизнь", придуманна английским математиком Джоном Конвеем в 1970 году. Представляет собой классический пример
клеточных автоматов и считается полной по Тьюрингу. 

## Содержание

* [Правила](#правила)
* [Обзор](#обзор)
* [Сборка](#сборка)
* [Тесты](#тесты)
* [Документация](#документация)

## Правила

Правила развития достаточно просты. Место действия - размеченное на квадраты поле, замкнутое с двух сторон.
Каждая клетка на поле имеет восемь соседей и может находиться в двух состояних: живая(клетка заполнена) и мертвая(клетка пуста).
Распределение клеток на поле до старта называется первым поколением, каждое следующее поколение рассчитывается согласно следующим условиям:
* В пустой клетке, соседями которой являются три живых клетки, зарождается жизнь.
* Если у живой клетки два или три живых соседа, клетка продолжает жить, в противном случае умирает.

## Обзор

## Сборка

Для сборки со всеми реализациями движков вам потребуется компилятор c поддержкой не ниже C++11, установленная библиотека OpenMP и СudaToolSet.
Проект поддерживает условную компиляцию. При остутствии необходимой библиотеки останавливается лишь сборка соответствующего ей движка.

## Тесты

Тестирование реализуется с помощью GTest, GMock и CTest. В каталоге /src/tests распологаются тесты основных компонентов библиотеки.
В корневом /tests располагается программа, реализующая консольный интерфейс к библиотеке для отработки основного поведения.

## Документация

Комментарии в коде соответствуют стилю Doxygen, вы можете сгенерировать собственную документацию используя в файл в разделе /doc
