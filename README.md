# Tsunamiforce
Полу-модульный авто шахтер на C++ для Minecraft сервера. Был сделан за 3 дня.

ГИФ

ГИФ

Демонстрация работы – ХХ

## Описание
Этот чит позволяет добывать руду в полностью автоматическом режиме на сервере Lavacraft. Есть 2 режима добычи: «звездой» и «лучом»

![starminer](https://github.com/KachesovVadim/Tsunamiforce/assets/142095950/782360d3-fcc8-44ab-8873-0157aefb522d)

Добыча звездой

![rayminer](https://github.com/KachesovVadim/Tsunamiforce/assets/142095950/b3b04f3f-d5d1-4a65-81a4-5e0a7179de70)

Добыча лучом

Так же, можно добавлять сколько угодно алгоритмов добычи, написав их на любом ЯП и добавив функционал запуска в функцию *ReadCheatMode* (Tsunamiforce.cpp)

## Инструкция
**Для запуска** нужен [Python](https://www.python.org/downloads/) и pyautogui (pip install pyautogui - в консоли). Дозарядка кирки работает только на Easy clans сервере с киркой новичка. Необходимое разрешение - FullHD (1920x1080). Так же, игра должна быть запущена в окне/на весь экран. Если Вы хотите использовать скрипт на других серверах, то нужно самостоятельно модифицировать логику ChargeModule.py Или же отключить функцию дозарядки, поставив у rechargePeriod (Header.h) очень большое значение (>100000000)

### Предметы для работы на сервере: 
- кирка новичка. (Дозарядка работает только с ней)
- дом с названием t под землей ( /sethome t ) 
- Рюкзак шахтера (Сразу добавляет руду в инвентарь. Очень **желателен**)

### Starminer
Если используется **starminer** алгоритм, то важно соблюсти только 2 условия: В точке дома потолок должен быть сразу над головой персонажа. Это нужно, чтобы при взлете персонаж смог упереться в потолок.
А так же, при установке дома взгляд персонажа должен позволять **вскапывать 2 блока за раз**, просто идя по прямой.

### Rayminer 
В случае использования **rayminer** алгоритма, необходимо подготовить тоннель в 500-600 блоков (при настройках по умолчанию) Персонаж будет идти направо, слегка упираясь в заднюю стену, это видно на демо-ролике. По этому нельзя допустить пробоев в 2 блока по высоте на задней стене.

![Снимок экрана (212)](https://github.com/KachesovVadim/Tsunamiforce/assets/142095950/a6463f98-8ac6-46ad-bbd7-4a9ac899e76b)
![Снимок экрана (213)](https://github.com/KachesovVadim/Tsunamiforce/assets/142095950/460e1f32-9405-44a8-bacb-dff75d3ec332)
![Снимок экрана (214)](https://github.com/KachesovVadim/Tsunamiforce/assets/142095950/16fe112c-b8da-436e-9b61-5621b19c52f0)


### Запуск
**Обязательно запускать от имени администратора**. У чита должны быть такие же привилегии, как и у клиента игры. Иначе, чит не сможет взаимодействовать с игрой.

Если Вы хотите запустить чит из **среды разработки**, то необходимо изначально ее открыть от имени администратора.

## Документация 
Tsunamiforce.cpp – В нем дописывать функционал для запуска своих режимов добычи.

Header.h (**только**для starminer алг.)
- udist(X,X) Диапазон в px для поворота персонажа 
- restartPeriod Можно указать любое время для перезапуска добычи руды. Тип данных - std::chrono [литералы](https://en.cppreference.com/w/cpp/symbol_index/chrono_literals)
- rechargePeriod Время в мс, через которое персонаж пойдет на спавн для зарядки кирки


