#include "bmpherr.h"
#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include "herramientas.h"
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
    *(head+30)=(int)0;//compresion
    *(head+34)=(int)((ancho*alto*3)+(alto*(ancho%4)));//tamaño de la imagen en bytes, todo incluido
    *(head+38)=(int)2835;
    *(head+42)=(int)2835;
    return head;
}
char* genera_imagen_solido(int ancho, int alto, int color)
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
            *(arr+pos+color)=0xFF;
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
char* genera_imagen_vec(int ancho,int alto,int*** img)
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
            *(arr+pos)=*(*(*(img+l)+a)+2);
            *(arr+pos+1)=*(*(*(img+l)+a)+1);
            *(arr+pos+2)=*(*(*(img+l)+a));
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

int capturaHeader(int* ancho, int* alto,char* ar)
{
    int a;
    char flag;
    FILE* fl=fopen(ar,"rb");
    rewind(fl);
    fread(&flag,sizeof(char),1,fl);
    //printf("%c",flag);
    if(flag!='B')//chequea que sea un bmp de windows
        return 1;
    fseek(fl,30,SEEK_SET);
    fread(&a,sizeof(int),1,fl);
    printf("%d",a);
    if(a!=0)return 2;//tiene algun tipo e compresion y no lo puedo usar
    fseek(fl,18,SEEK_SET);
    fread(ancho,4,1,fl);
    fread(alto,4,1,fl);
    fclose(fl);
    return 0;
}
int*** capturaImagen(int alto, int ancho,char* ar)//estaria genial capturarlas al revez asi podes usar todas las funciones de la matrices de ints
{
    FILE* fl=fopen(ar,"rb");
    fseek(fl,54,SEEK_SET);//se mueve al principio de la imagen
    int padd=ancho%4;
    int*** vec=(int**)calloc(alto,sizeof(int*));
    int i,j,c;
    for(i=0;i<alto;i++)//fila a fila
    {
        *(vec+i)=(int**)calloc(ancho,sizeof(int*));//aloco la clumna
        for(j=0;j<ancho;j++)//columna a columna(pixel a pixel
        {
            *(*(vec+i)+j)=(int)calloc(sizeof(int),3);//este tiene para los 3 colores!
            fread((int)(*(*(vec+i)+j)+2),1,1,fl);//azul
            fread((int)(*(*(vec+i)+j)+1),1,1,fl);//verde
            fread((int)(*(*(vec+i)+j)),1,1,fl);//rojo
        }
        fseek(fl,padd,SEEK_CUR);//me salteo el padding
    }
    fclose(fl);
    return vec;
}
/*int*** capturaImagen(int alto, int ancho,char* ar)
{
    FILE* fl=fopen(ar,"rb");
    fseek(fl,54,SEEK_SET);//se mueve al principio de la imagen
    int padd=ancho%4;
    int*** vec=(int***)malloc(3*sizeof(int**));
    int i,j,c;
    //for(c=0;c<3;c++)//primero los 3 colores
    {
        *(vec+c)=(int**)malloc(alto*sizeof(int*));
        for(i=0;i<alto;i++)
        {
            *(*(vec+c)+i)=(int*)calloc((ancho+padd),sizeof(int));
            for(j=0;j<ancho;j++)
            {
                /*fseek(fl,c,SEEK_CUR);//me salteo los colores que no necesito
                fread((int)(*(*(vec+c)+i)+j),1,1,fl);
                fseek(fl,1-c,SEEK_CUR);//me salteo los colores que no necesito*/
                /*fread((int)(*(*(vec+0)+i)+j),1,1,fl);//azul
                fread((int)(*(*(vec+1)+i)+j),1,1,fl);//verde
                fread((int)(*(*(vec+2)+i)+j),1,1,fl);//rojo
            }
            fseek(fl,padd,SEEK_CUR);//me salteo el padding
        }
    }
    return vec;
}*/
void printimgarr(int color, int alto, int ancho, int*** img)//colo 0 para rojo, 1 para verde 2 para azul
{
    int i,j;
    for(i=0;i<alto;i++)
    {
        for(j=0;j<ancho;j++)
        {

            printf("%d ",*(*(*(img + i) + j)+color));
        }
        printf("\n");
    }
}
void freeimgvec()
{

}
