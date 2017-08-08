#include "bmpherr.h"
#include<string.h>
#include <stdio.h>
#include <stdlib.h>

char* generaHeader(int ancho, int alto)
{
    char* head=(char*)calloc(54*sizeof(char),1);
    *head='B';
    *(head+1)='M';//estos son fijos, tienen que estar para que windows reconozca el archivo
    *(head+2)=(int)54+(ancho*alto*3)+(alto*(ancho%4));//tamaño archivo
    //*(head+6)=(int)0;
    //*(head+8)=(int)0;//tienen que estar asi
    //*(head+10)=(long)54;//offset hasta la imagen(fijo)
    int n=54;
    memcpy(head+10,&n,4);
    //empieza el DIB header
    *(head+14)=(int)40;
    *(head+18)=(int)ancho;//ancho en pixeles
    *(head+22)=(int)alto;//alto en pixeles
    *(head+26)=(short)1;
    *(head+28)=(short)24;
    *(head+30)=(int)0;
    *(head+34)=(int)((ancho*alto*3)+(alto*(ancho%4)));//tamaño de la imagen en bytes, todo incluido
    *(head+38)=(int)2835;
    *(head+42)=(int)2835;
    return head;
}
char* genera_imagen(int ancho, int alto)
{
    int l,a,p;
    long pos;
    pos=0;
    char* arr=calloc((ancho*alto*3)+(alto*(ancho%4)),1);
    for(l=0;l<alto;l++)
    {
        //printf("fila N%d\n",l);
        for(a=0;a<ancho;a++)
        {
            *(arr+pos)=0x0;
            *(arr+pos+1)=0x0;
            *(arr+pos+2)=0xFF;
            pos+=3;
        }
        for(p=0;p<(ancho%4);p++) //paddling...
        {
            *(arr+pos)=0x0;
            pos++;
        }
    }
    return arr;
}
