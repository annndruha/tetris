## УСТАНОВКА OpenCV через Visual Studio для C++
#### В системе:
**ПанельУпр/Система/ДопПараметрыСистемы/ПеременныеСреды/СистемныеПеременные/Патч/Изменить**
добавить: `"C:\opencv\build\x64\vc14\bin"`

#### В Visual Studio:
ОТЛАДЧИК СРАЗУ ПЕРЕКЛЮЧИТЬ НА Х64
Конфигурация Активная Дебаг

**Каталоги VC++/Каталоги библиотек**

`C:\opencv\build\x64\vc14\lib;$(LibraryPath)`

**С++/Общее/Доп каталоги включаемых файлов**

`C:\opencv\build\include\opencv;C:\opencv\build\include\opencv2;C:\opencv\build\include;$(IncludePath);%(AdditionalIncludeDirectories)`

**Компоновщик/Общие/Доп каталоги библиотек**
`C:\opencv\build\x64\vc14\lib;%(AdditionalLibraryDirectories)`

**Компоновщик/Ввод/Доп зависимости--ПРОВЕРИТЬ ВЕРСИЮ И ДЕБАГ(d)**
`opencv_world400d.lib;%(AdditionalDependencies)`


```c++
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
```

#### Убрать консоль при запуски программы только с графическим интерфейсом
**Компоновщик/Система/Подсистема**
Выбрать **Windows (/SUBSYSTEM:WINDOWS).**

**Компоновщик/Дополнительно/Точка входа**
Вписать **mainCRTStartup**