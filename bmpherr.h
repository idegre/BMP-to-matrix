#ifndef BMPHERR_H_INCLUDED
#define BMPHERR_H_INCLUDED
char* generaHeader(int ancho, int alto);
char* genera_imagen(int ancho, int alto);
int capturaHeader(int* ancho, int* alto,char* ar);
char* genera_imagen_solido(int ancho, int alto, int color);
int*** capturaImagen(int alto, int ancho,char* ar);
#endif // BMPHERR_H_INCLUDED
