# ifndef BMP_H
# define BMP_H
/*
 Формат BMP
 Данные в этом формате разделены на три-четыре части в следующем порядке:
 Заголовок информации о файле (14 байт) содержит тип файла, размер файла и другую информацию.
 Заголовок информации об изображении (40 байт) хранит размер изображения, индекс цвета, номер битовой плоскости и другую информацию.
 Палитра (определяется количеством цветовых индексов) [может не содержать этой информации]
 Здесь хранится информация о растровых данных (определяемых размером изображения) для каждого пикселя.

 Общее изображение BMP составляет 24 бита, что соответствует истинному цвету. Каждые 8 ​​бит представляют собой байт, а 24 бита используют три байта для хранения информации о каждом пикселе.Три байта соответствуют данным трех основных цветов r, g и b.
 Диапазон хранения каждого байта - 0-255. Затем по аналогии 32-битное изображение хранит четыре типа данных: r, g, b, a (альфа-канал, прозрачность памяти) на пиксель. 8-битное изображение - это только информация в градациях серого,
 Также существует двоичное изображение, которое имеет только два цвета, черный или белый.
*/
// Структура заголовка информации о файле
typedef struct tagBITMAPFILEHEADER__
{
    // unsigned short bfType; // 19778, должна быть строка BM, соответствующее шестнадцатеричное значение - 0x4d42, десятичное - 19778, иначе это не файл формата BMP
    unsigned int   bfSize;        // Размер файла в байтах (2-5 байтов)
    unsigned short bfReserved1;   // Зарезервировано, должно быть установлено на 0 (6-7 байтов)
    unsigned short bfReserved2;   // Зарезервировано, должно быть установлено в 0 (8-9 байтов)
    unsigned int   bfOffBits;     // Смещение от заголовка файла к пиксельным данным (10-13 байтов)
} BITMAPFILEHEADER_;

// Структура заголовка информации об изображении
typedef struct tagBITMAPINFOHEADER__
{
    unsigned int    biSize;          // Размер этой структуры (14-17 байт)
    long            biWidth;         // Ширина изображения (18-21 байт)
    long            biHeight;        // Высота изображения (22-25 байт)
    unsigned short  biPlanes;        // Указывает атрибут плоскости изображения bmp. Очевидно, что дисплей имеет только одну плоскость, поэтому она всегда равна 1 (26-27 байтов)
    unsigned short  biBitCount;      // Количество бит, занимаемых пикселем, обычно 24 (28-29 байтов)
    unsigned int    biCompression;   // Описать тип сжатия данных изображения, 0 означает отсутствие сжатия. (30-33 байта)
    unsigned int    biSizeImage;     // Размер данных пикселя, это значение должно быть равно bfSize-bfOffBits (34-37 байтов) в структуре заголовка файла выше
    long            biXPelsPerMeter; // Опишите разрешение по горизонтали, выраженное в пикселях / метр. Обычно 0 (38-41 байт)
    long            biYPelsPerMeter; // Опишите разрешение по вертикали, выраженное в пикселях / метр. Обычно 0 (42-45 байтов)
    unsigned int    biClrUsed;       // Описать количество индексов цвета в таблице цветов, фактически используемых растровым изображением (если установлено в 0, это означает, что используются все элементы палитры). (46-49 байт)
    unsigned int    biClrImportant;  // Объясните количество цветовых индексов, которые имеют важное значение для отображения изображения. Если он равен 0, это означает, что все важны. (50-53 байта)
} BITMAPINFOHEADER_;

// информационная структура 24 битовых пикселей, а именно палитра
typedef struct PixelInfo {
    unsigned char rgbBlue;   // Синий компонент цвета (диапазон значений 0-255)
    unsigned char rgbGreen;  // Зеленый компонент цвета (диапазон значений 0-255)
    unsigned char rgbRed;    // Красная составляющая цвета (диапазон значений 0-255)
    unsigned char rgbReserved;// зарезервировано, должно быть 0
} PixelInfo;

#endif
