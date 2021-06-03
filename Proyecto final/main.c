#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <stdbool.h>




///Estructura de Usuario

typedef struct{

    int idUsuario;                 // auto incremental
    char nombre[30];
    char apellido[30];
    char userName[20];
    char password[20];
    char mail[30];
    char genero;
    int listadoIdsContenidosGuardados[50];
    int validosContenidos;
    int puntaje;
    int nivel;
    //??? contenidosFavoritos ??? ; // pensar como administrarlos
    int rol;           //     ???   // 1: es admin - 0: es comun
    int activo;                   // indica 1 o 0 si el usuario está activo
} stUsuario;

///Estructura de Contenido

typedef struct{
    int idContenido; // auto incremental
    char titulo[30];
    char descripcion[300];
    char categoria[30];
    int likes;
    int puntosPorCompartir;
    int activo;                     // indica 1 o 0 si el contenido está activo
} stContenido;

///Estructura de Mensajería

typedef struct{
    int idUsuarioEmisor;
    int idUsuarioReceptor;
    int idContenidoEnviado;
    char mensaje[300];
    int leido;                      // 1:si 0:no
} stMensajeria;

void menuIngresar();
void escribirArchivoUsuario(stUsuario aux, char archivo[]);
void formularioUsuario(char archivo[]);
int buscaUltimoId(char archivo[]);
void cargaUsuario(char archivo[]);
void muestraUnUsuario(stUsuario aux);
void muestraUsuarioArchivo(char archivo[]);



int main(){

    menuIngresar();


    return 0;
}
void menuIngresar(){
    char control = 's';
    int menu;

    do{
        system("cls");
        printf("\n\t\t\t==> MENU PRINCIPAL <==\n");
        printf("\n\t\t\t==> 1)INGRESAR <==\n");
        printf("\n\t\t\t==> 2)REGISTRARSE <==\n");
        printf("\n\t\t\t==> 3)SALIR <==\n");
        scanf("%d", &menu);

        switch(menu){
        case 1:
            system("cls");
            break;

        case 2:
            system("cls");
            cargaUsuario("usuarios.dat");
            break;



        }




    }while(control == 's');


}

void escribirArchivoUsuario(stUsuario aux, char archivo[]){
    FILE * bufferArchivo = NULL;
    bufferArchivo = fopen(archivo, "ab");///archivo binario para añadir

    if(bufferArchivo != NULL){

        fwrite(&aux, sizeof(stUsuario), 1, bufferArchivo);
        fclose(bufferArchivo);
    }
    else{
        printf("El archivo no se pudo abrir");
    }
}

void formularioUsuario(char archivo[]){
    stUsuario aux;
    char opcion;
    system("cls");

    FILE *PArchiUsuario = fopen(archivo, "ab");

        printf("Completar todos los campos obligatorios\n\n");
        printf("==> Nombre: ");
        fflush(stdin);
        gets(aux.nombre);

        printf("==> Apellido: ");
        fflush(stdin);
        gets(aux.apellido);

        printf("==> userName: ");
        fflush(stdin);
        gets(aux.userName);

        printf("==> password: ");
        fflush(stdin);
        gets(aux.password);


        printf("==> mail: ");
        fflush(stdin);
        gets(aux.mail);

        printf("==> genero: ");
        fflush(stdin);
        scanf("%c", aux.genero);

        printf("==> Gracias por registrarse\n");

        aux.activo = 0; ///0 para activos, 1 para inactivos

}
int buscaUltimoId(char archivo[]){
    stUsuario aux;
    int id = -1;

    FILE * bufferArchivo = fopen(archivo, "rb");///abro archivo modo lectura

    if(bufferArchivo){///Sitúa el puntero en el archivo .Posición al final del archivo

        fseek(bufferArchivo, sizeof(stUsuario)*(-1),SEEK_END);

        if(fread(&aux,sizeof(stUsuario),1,bufferArchivo) > 0){
            id = aux.idUsuario;
        }
        fclose(bufferArchivo);
    }
    return id;
}
void cargaUsuario(char archivo[]){

    stUsuario aux;
    char opcion= 's';

    while(opcion== 's'){

        formularioUsuario(archivo);
        aux.idUsuario = buscaUltimoId(archivo)+1;///hacer para el pedido
        escribirArchivoUsuario(aux, archivo);


        printf("\n\t\t\t==>Deseas continuar cargando clientes? s/n\n");

        fflush(stdin);
        opcion = getch();
        system("cls");

    }
}

void muestraUnUsuario(stUsuario aux){
    printf("\n  -----------------------------------------------------------------");
    printf("\n  ID                      : %d", aux.idUsuario);
    printf("\n  Nombre                  : %s", aux.nombre);
    printf("\n  Apellido                : %s", aux.apellido);
    printf("\n  Username                : %s", aux.userName);
    printf("\n  Password                : %s", aux.password);
    printf("\n  Email                   : %s", aux.mail);
    printf("\n  Genero                  : %c", aux.genero);
    printf("\n  Baja s/n                : %d\n", aux.activo);
}

void muestraUsuarioArchivo(char archivo[]){
    stUsuario aux;
    FILE * bufferArchivo = NULL;
    bufferArchivo = fopen(archivo,"rb");

    if(bufferArchivo!=NULL){
        while(fread(&aux, sizeof(stUsuario), 1, bufferArchivo) > 0){
            muestraUnUsuario(aux);
        }
        fclose(bufferArchivo);
    }
    printf("\n");
}
