#include <stdio.h>
#include <stdlib.h>

char* generaHeader(int ancho, int alto);
char* genera_imagen(int ancho, int alto);
int main()
{
    char arch[]="c://img.bmp";
    //aca tendria que hacer una protexion para sobreescritura
    int an=5;
    int al=5;
    //int pa=an%4;//mi padding para que
    char* header=generaHeader(an,al);
    char* img=genera_imagen(an,al);
    FILE* fl=fopen(arch,"wb");
    fwrite(header,1,54,fl);
    fwrite(img,1,(an*al*3)+(al*(an%4)),fl);
    fclose(fl);
    free(header);
    free(img);
    return 0;
}

