#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include "BmpFormat.h"
#define _CRT_SECURE_NO_WARNINGS
BITMAPFILEHEADER_ fileHeader;
BITMAPINFOHEADER infoHeader;

BITMAPFILEHEADER_ fileHeader1;
BITMAPINFOHEADER infoHeader1;
void showBmpHead(BITMAPFILEHEADER_ pBmpHead)
{  // Определяем функцию отображения информации, передаем структуру заголовка файла
    printf("Размер файла BMP:% dkb \n", fileHeader.bfSize/1024);
    printf("Зарезервированные слова должны быть 0:% d \n",  fileHeader.bfReserved1);
    printf("Зарезервированные слова должны быть 0:% d \n",  fileHeader.bfReserved2);
    printf("Смещение байтов фактических данных растрового изображения:% d \n",  fileHeader.bfOffBits);
}
void showBmpInfoHead(BITMAPINFOHEADER pBmpinfoHead)
{// Определяем функцию для отображения информации, структура заголовка информации передается в
   printf("Заголовок информации о растровом изображении: \n" );
   printf("Размер заголовка сообщения:% d \n" ,infoHeader.biSize);
   printf("Ширина растрового изображения:% d \n" ,infoHeader.biWidth);
   printf("Высота растрового изображения:% d \n" ,infoHeader.biHeight);
   printf("Количество плоскостей изображения (количество плоскостей - это количество палитр, по умолчанию 1 палитра):% d \n" ,infoHeader.biPlanes);
   printf("Количество бит на пиксель:% d \n" ,infoHeader.biBitCount);
   printf("Метод сжатия:% d \n" ,infoHeader.biCompression);
   printf("Размер изображения:% d \n" ,infoHeader.biSizeImage);
   printf("Разрешение по горизонтали:% d \n" ,infoHeader.biXPelsPerMeter);
   printf("Вертикальное разрешение:% d \n" ,infoHeader.biYPelsPerMeter);
   printf("Количество использованных цветов:% d \n" ,infoHeader.biClrUsed);
   printf("Количество важных цветов:% d \n" ,infoHeader.biClrImportant);
}

int main(int argc, char * argv[])
{
    double result = 0;
    double result1 = 0;
    int sum_lin = 0;
    int sum = 0;
    setlocale(LC_ALL,"Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    if(argc != 3) {
         printf("Программе передано слишком мало/много аргументов!\n");
         return -5;
    }
    else
    {
        char* fname = argv[1];
        char* fname1 = argv[2];
        FILE* fp;
        FILE* fp1;
        fp = fopen(fname, "rb");   //Читаем файл image.bmp в том же каталоге.
        fp1 = fopen(fname1, "rb");
        if(fp == NULL || fp1 == NULL)
        {
            printf("Не удалось открыть какой-либо из необходимых файлов\n");
            return -1;
        }
        // Если вы сначала не читаете bifType, согласно правилу операции Sizeof для структуры языка C - целое больше суммы частей, что приводит к смещению читаемого файла
        unsigned short  fileType;
        fread(&fileType,1,sizeof (unsigned short), fp);
        if (fileType == 0x4d42)
        {
            fread(&fileHeader, 1, sizeof(BITMAPFILEHEADER), fp);
			//showBmpHead(fileHeader);
			fseek(fp,sizeof(BITMAPFILEHEADER),SEEK_SET);
            fread(&infoHeader, 1, sizeof(BITMAPINFOHEADER), fp);
			showBmpInfoHead(infoHeader);
        }
        else
        {
            printf("Неверная идентификация типа файла!\n");
            return -2;
        }
        unsigned short  fileType1;
        fread(&fileType1,1,sizeof (unsigned short), fp1);
        if (fileType1 == 0x4d42)
        {
            fread(&fileHeader1, 1, sizeof(BITMAPFILEHEADER), fp1);
			//showBmpHead(fileHeader1);
			fseek(fp1,sizeof(BITMAPFILEHEADER),SEEK_SET);
            fread(&infoHeader1, 1, sizeof(BITMAPINFOHEADER), fp1);
			//showBmpInfoHead(infoHeader1);
        }
        else
        {
            printf("Неверная идентификация типа файла!\n");
            return -2;
        }
        bool a = (infoHeader.biHeight   != infoHeader1.biHeight);
        bool b = (infoHeader.biWidth    != infoHeader1.biWidth);
        bool c = (infoHeader.biBitCount != infoHeader1.biBitCount);
        bool e = a || b || c;
        if(e) {
            printf("Формат файлов не совпадает!\n");
            return -3;
        }
        if(infoHeader.biBitCount!=8 && infoHeader.biBitCount!=24) {
            printf("Неверный формат файлов!\n");
            return -4;
        }
        if(infoHeader.biBitCount==8)
        {
			int a = 0;
			int b = 0;
            //int w = infoHeader.biWidth;
            //int h = infoHeader.biHeight;
            /*unsigned char *data = malloc(infoHeader.biSizeImage);
            unsigned char *data_ = malloc(infoHeader1.biSizeImage);*/
			unsigned char **img = malloc(infoHeader.biHeight*sizeof(unsigned char *)+infoHeader.biWidth*infoHeader.biHeight*sizeof(unsigned char));
        	unsigned char* pc = img;
        	pc += infoHeader.biHeight*sizeof(unsigned char *);
        	for (int i=0; i< infoHeader.biHeight; i++)
            	img[i] = pc + i*sizeof(infoHeader.biWidth*sizeof(unsigned char));
			unsigned char **img1 = malloc(infoHeader.biHeight*sizeof(unsigned char *)+infoHeader.biWidth*infoHeader.biHeight*sizeof(unsigned char));
        	unsigned char* pc1 = img1;
        	pc1 += infoHeader.biHeight*sizeof(unsigned char *);
        	for (int i=0; i< infoHeader.biHeight; i++)
            	img1[i] = pc1 + i*sizeof(infoHeader.biWidth*sizeof(unsigned char));
            fseek(fp,fileHeader.bfOffBits,SEEK_SET);
            //fread(data,1,infoHeader.biSizeImage,fp);
            fseek(fp1,fileHeader1.bfOffBits,SEEK_SET);
            //fread(data_,1,infoHeader.biSizeImage,fp1);
			//printf("%d %d %d\n",getc(fp1),getc(fp1),getc(fp1));
            int start_ = 0;
            for(int i=0;i<infoHeader.biHeight;i++)
            {
                for(int j=0;j<infoHeader.biWidth;j++)
                {
					img[i][j] = getc(fp);
					img1[i][j] = getc(fp1);
					sum += pow(img[i][j]-img1[i][j],2);
                    //sum += pow(data[i*infoHeader.biWidth+j+start_]-data_[i*infoHeader.biWidth+j+start_],2);
		    		//printf("img1[%d][%d]=%d %d\n",i,j,data[i*infoHeader.biWidth+j+start_],data_[i*infoHeader.biWidth+j+start_]/*,start_*/);
                }
                start_ += (4-(infoHeader.biWidth % 4)) % 4;
				while(start_!=0) {
					getc(fp);
					getc(fp1);
					start_--;
				}
            }
			/*printf("%d %d %d\n",img[0][0],img[0][1],img[0][2]);
			printf("%d %d %d\n",img[1][0],img[1][1],img[1][2]);
			printf("%d %d %d\n",img[2][0],img[2][1],img[2][2]);
			printf("%d %d %d\n",img1[0][0],img1[0][1],img1[0][2]);
			printf("%d %d %d\n",img1[1][0],img1[1][1],img1[1][2]);
			printf("%d %d %d\n",img1[2][0],img1[2][1],img1[2][2]);*/
            start_ = 0;
            for(int i=0;i<infoHeader.biHeight;i++)
            {
                for(int j=1;j<infoHeader.biWidth;j++)
                {
                    sum_lin += abs(img[i][j-1]-img[i][j]);
                }
                start_ += (4-(infoHeader.biWidth % 4)) % 4;
            }
            if (sum < 0)
            {
                printf("Произошло переполнение, разница между картинками слишком велика!\n");
                return -6;
            }
            else
            {
                result = (double)1.0/(infoHeader.biWidth*infoHeader.biHeight)*sqrt(sum);
                printf("Средний квадрат попиксельной разности: %1.15lf\n",result);
                result1 = (double)sum_lin/((infoHeader.biWidth-1)*infoHeader.biHeight);
                if(result1!=0)
                {
                    result = result/result1;
                    printf("Средний квадрат, деленный на среднюю разность соседних пикселей: %1.15lf\n",result);
                }
                else
                    printf("Средний квадрат, деленный на среднюю разность соседних пикселей рассчитать невозможно(деление на 0)\n");
            }
            //free(data);
            //free(data_);
			free(img1);
			free(img);
            fclose(fp);
            fclose(fp1);
            return 0;
        }
        int widthInBytes = infoHeader.biWidth*(infoHeader.biBitCount/8);
        int paddingSize = (4 - (widthInBytes) % 4) % 4;
        char buff[paddingSize];
        PixelInfo **rgb = malloc(infoHeader.biHeight*sizeof(PixelInfo *)+infoHeader.biWidth*infoHeader.biHeight*sizeof(PixelInfo));
        PixelInfo* pc = rgb;
        pc += infoHeader.biHeight*sizeof(PixelInfo *);
        for (int i=0; i< infoHeader.biHeight; i++)
            rgb[i] = pc + i*sizeof(infoHeader.biWidth*sizeof(PixelInfo));
        for (int i = 0; i < infoHeader.biHeight; i++) {
            for (int j = 0; j < infoHeader.biWidth; j++) {
                rgb[i][j].rgbBlue = getc(fp);
                rgb[i][j].rgbGreen = getc(fp);
                rgb[i][j].rgbRed = getc(fp);
                sum += pow(rgb[i][j].rgbBlue-getc(fp1),2)+pow(rgb[i][j].rgbGreen-getc(fp1),2)+pow(rgb[i][j].rgbRed-getc(fp1),2);
            }
            fread(buff,1,paddingSize,fp);
            fread(buff,1,paddingSize,fp1);
        }
        for(int i=0;i<infoHeader.biHeight;i++)
        {
            for(int j=1;j<infoHeader.biWidth;j++)
            {
                sum_lin += abs(rgb[i][j-1].rgbBlue-rgb[i][j].rgbBlue)+abs(rgb[i][j-1].rgbGreen-rgb[i][j].rgbGreen)+abs(rgb[i][j-1].rgbRed-rgb[i][j].rgbRed);
            }
        }
        if (sum < 0)
        {
            printf("Произошло переполнение, разница между картинками слишком велика!\n");
            return -6;
        }
        else
        {
            result = 1.0/(double)(3*infoHeader.biWidth*infoHeader.biHeight)*sqrt(sum);
            printf("Средний квадрат попиксельной разности: %1.15lf\n",result);
            result1 = (double)sum_lin/(3*(infoHeader.biWidth-1)*infoHeader.biHeight);
            if(result1!=0)
            {
                result = result/result1;
                printf("Средний квадрат, деленный на среднюю разность: %1.15lf\n",result);
            }
            else
                printf("Средний квадрат, деленный на среднюю разность соседних пикселей рассчитать невозможно(деление на 0)\n");
        }
        fclose(fp);
        fclose(fp1);
        free(rgb);
        return 0;
    }
}
