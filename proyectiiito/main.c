#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define contenido_dat "contenido.dat"
#define usuarios_dat  "usuarios.dat"
#define mensajes_dat "mensajes.dat"

///Estructura de Usuario

typedef struct
{

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

typedef struct
{
    int idContenido; // auto incremental
    char titulo[30];
    char descripcion[300];
    char categoria[30];
    int likes;
    int puntosPorCompartir;
    int activo;                     // indica 1 o 0 si el contenido está activo
} stContenido;

///Estructura de Categorias

typedef struct
{
    int id;
    char nombreCat[30];

} stCategoria;

///OPCIONAL
///Estructura de Mensajería

typedef struct
{
    int idUsuarioEmisor;
    int idUsuarioReceptor;
    int idContenidoEnviado;
    char mensaje[300];
    int leido;
    stContenido conten;                  // 1:si 0:no
} stMensajeria;
///

///Titulo del proyecto
void tituloProyecto();
///Menu principal de ejecucion
void menuPrincipal();
void usuarioInicio();
void logueoUsuario(char archivo[]);
stUsuario buscaUserPorUserName(char archivo[], char userName[]);
void creaUserName(char archivo[]);
stUsuario modificaRegistro(char archivo[], char user[]);
int buscaUltimoIdUsuario(char archivo[]);
///contenido
int buscaUltimoIdContenido(char archivo[]);
int creaContenido(char archivo[]);
stUsuario actualizarArregloContenido(char archivo[], stUsuario usuario, int idContenido);
///Mensajeria
stContenido buscaContenidoPorID(char archivo[],int id);
void enviarContenido(stUsuario emisor, const char* usernameDelDestinatario, int idDeContenido);
void VerMensajes(stMensajeria mensajes);
/// Categorias
void crearCategoria (char archivo[]);
void mostrarCategorias(char archivo[]);
void mostrarUnaCategoria(stCategoria a);
int ultimoId(char archivo[]);
void cargarArregloDeCategorias(char archivo[], stCategoria arregloCategorias[], int validos);
void mostrarArreglo (stCategoria arregloCategorias[], int validos);
int cantidadDatosStCategorias(char archivo[]);
void updateArregloAarchivo(stCategoria arregloCategorias[], int validos, char archivo[]);


int main()
{
    menuPrincipal();


    return 0;
}


void tituloProyecto()
{

    printf("\n     ======================================================================\n");
    printf("\t\t\t     PROYECTO FINAL \n");
    printf("\t   CREA TU POST, BUSCALO, EDITALO, ELIMINALO Y DISFRUTALO\n");
    printf("\t\t    freeTime - Alumnos: Jonathan Cardozo, Melisa Zalazar, Lucas Glavina\n");
    printf("     ======================================================================\n");


    printf("\n");
    int numrep= 80;
    char car= '_';
    while(numrep>0)
    {

        printf("%c",car);
        --numrep;
    }


}

void menuPrincipal()
{
    char control = 's';
    int menu;

    tituloProyecto();
    printf("\nBienvenido a la Red Social FreeTime\n\n");
    printf("Elija la opcion correspondiente para ingresar\n");

    do
    {
        printf("1)Ingresar como usuario\n");
        printf("2)Ingresar como administrador\n");
        scanf("%d", &menu);

        switch(menu)
        {
        case 1:
            usuarioInicio();
            break;
        case 2:
            InicioADM();
            break;
        }

        printf("\nDesea continuar en el programa? s/n\n ");
        fflush(stdin);
        control= getch();

    }
    while(control == 's');


}
///logueo o registrarse llama a la funcion


///-/////////////////////////////////////////////////
///-//////////////Usuario////////////////////////////
///-/////////////////////////////////////////////////


void usuarioInicio()
{
    char control = 's';
    int menu;

    do
    {
        system("cls");
        printf("1) Loguearse\n");
        printf("2) Registrarse\n");
        scanf("%d", &menu);

        switch(menu)
        {
        case 1:
            system("cls");
            logueoUsuario("usuarios.dat");
            break;
        case 2:
            system("cls");
            creaUserName("usuarios.dat");
            printf("\Desea continuar en el programa? (s/n)\n ");
            fflush(stdin);
            control= getch();
            break;
        }
    }
    while(control == 's');


}

void logueoUsuario(char archivo[])
{
    stUsuario usuario;
    char user[20];
    char pass[20];
    int existeUser;
    int existePass;

    printf("Ingrese el UserName\n");
    fflush(stdin);
    gets(user);

    printf("Ingrese su Pass\n");
    fflush(stdin);
    gets(pass);

    existeUser = existeUserPorUserName(archivo, user);

    if(existeUser == 1)
    {
        system("cls");

        usuario = buscaUserPorUserName(archivo, user);

        if(strcmp(usuario.password, pass) == 0)
        {

            menuUsuario("usuarios.dat", usuario);

        }
        else
        {
            printf("La contraseña es invalida, intente nuevamente\n");

        }


    }
    else
    {

        printf("El usuario no existe\n");

    }

}

///buscarUserNameName
stUsuario buscaUserPorUserName(char archivo[], char userName[])
{
    stUsuario aux;
    int flag = 0;

    FILE * bufferArchivo = fopen(archivo,"rb");

    if(bufferArchivo!=NULL)
    {

        while(flag == 0 && fread(&aux, sizeof(stUsuario),1, bufferArchivo) > 0 )
        {

            if(strcmp(aux.userName, userName)== 0)
            {
                flag = 1;


            }
        }

        fclose(bufferArchivo);
    }


    return aux;

}

int existeUserPorUserName(char archivo[], char userName[])
{
    stUsuario aux;
    int flag = 0;

    FILE * bufferArchivo = fopen(archivo,"rb");

    if(bufferArchivo!=NULL)
    {

        while(flag == 0 && fread(&aux, sizeof(stUsuario),1, bufferArchivo) > 0 )
        {

            if(strcmp(aux.userName, userName)== 0)
            {
                flag = 1;


            }
        }

        fclose(bufferArchivo);
    }


    return flag;

}

void creaUserName(char archivo[])
{

    stUsuario aux;
    char user[20];
    int existe;

    formularioUsuario(archivo);
}

void formularioUsuario(char archivo[])
{
    stUsuario aux;
    char opcion;
    int id = buscaUltimoIdUsuario(archivo);

    FILE * bufferArchivo = fopen(archivo,"ab");

    if(bufferArchivo != NULL)
    {

        printf("==> userName: ");
        fflush(stdin);
        gets(aux.userName);
        int existeUserName = existeUserPorUserName("usuarios.dat", aux.userName);
        if(existeUserName == 0)
        {
            printf("Completar todos los campos obligatorios\n\n");
            printf("==> Nombre: ");
            fflush(stdin);
            gets(aux.nombre);

            printf("==> Apellido: ");
            fflush(stdin);
            gets(aux.apellido);

            printf("==> password solo se aceptan letras, como maximo 20: ");
            fflush(stdin);
            gets(aux.password);


            printf("==> mail: ");
            fflush(stdin);
            gets(aux.mail);

            printf("==> genero: ");
            fflush(stdin);
            scanf("%c", &aux.genero);

            printf("==> Gracias por registrarse\n");


            aux.activo = 0; ///0 para activos, 1 para inactivos
            aux.rol = 0; /// 0 porque es usuario
            aux.puntaje = 0;///inicio del puntaje
            aux.nivel = 0;
            aux.validosContenidos = 0;
            aux.listadoIdsContenidosGuardados[50];

            id++;
            aux.idUsuario = id;


            fwrite(&aux, sizeof(stUsuario), 1, bufferArchivo);
        }
        else
        {
            printf("El usuario con el username %s ya existe, vuelva a intentarlo \n", aux.userName);
        }

        printf ("cualquier tecla para continuar");
        opcion = getch ();
        system ("cls");
        fclose(bufferArchivo);
    }

}

int buscaUltimoIdUsuario(char archivo[])
{
    stUsuario aux;
    int id = 0;

    FILE * bufferArchivo = fopen(archivo, "r + b");///abro archivo modo lectura

    if(bufferArchivo)
    {

        fseek(bufferArchivo,-1 * sizeof(stUsuario),SEEK_END);

        if(fread(&aux, sizeof(stUsuario),1,bufferArchivo) > 0)
        {
            id = aux.idUsuario;
        }
        fclose(bufferArchivo);
    }
    return id;
}

void menuUsuario(char archivo[], stUsuario usuario)
{

    stUsuario usuarioActualizado;
    usuarioActualizado = usuario;
    char control = 's';
    int menu;
    int existe;
    int idContenido;

    do
    {
        printf("Inicio de sesion correcto\n");
        printf("Que desea hacer?\n");
        printf("1) Modificar\n");//ya esta
        printf("2) Crear Contenido\n");//ya esta
        printf("3) Ver contenido\n");//ya esta
        printf("4) crear mensajes\n");
        printf("5) Ver mensajes\n");
        printf("6) Ver mi perfil\n");//ya esta
        printf("7) Salir\n");
        scanf("%d", &menu);

        switch(menu)
        {
        case 1:
            system("cls");
            usuario = modificaRegistro("usuarios.dat", usuario.userName);
            printf("\Desea continuar en el programa? s/n\n ");
            fflush(stdin);
            control= getch();
            break;
        case 2:
            system("cls");
            idContenido = creaContenido("contenidos.dat");
            usuario = actualizarArregloContenido("usuarios.dat", usuario, idContenido);
            printf("\Desea continuar en el programa? s/n\n ");
            fflush(stdin);
            control= getch();
            break;
        case 3:
            system("cls");
            printf("Ver contenido \n");
            printf("Contenidos: %d \n", usuario.validosContenidos);

            muestraTodosLosContenidoDeUnUsuario("contenidos.dat", usuario);

            printf("\Desea continuar en el programa? s/n\n ");
            fflush(stdin);
            control= getch();
            break;


        case 5:
            printf("VER MENSAJES: ");
            muestraArchivosdeMensajes(usuario);
            break;
        case 6:
            system("cls");
            printf("Mi perfil:");
            muestraUnUsuario(usuario);
            break;
        case 7:
            control = 'n';
            break;
        default:
            printf("La opcion no existe");
            break;

        }
    }
    while(control == 's');



}

stUsuario modificaRegistro(char archivo[], char user[])
{
    char control = 's', modif = 's';
    int menu;
    char nombre[30];
    char apellido[30];
    char password[20];
    char email [30];
    char genero;

    stUsuario usuarioActualizado;
    int pos;


    FILE * bufferArchivo = fopen(archivo, "r+b");

    if(bufferArchivo)
    {
        pos = buscaPosicionUser(archivo, user);
        fseek(bufferArchivo, sizeof(stUsuario) * pos, SEEK_SET);
        printf("\n\t\t\t==> MENU DE MODIFICACION <==\n");
        printf("\n\t\t\t==> Elija una opcion <==\n");

        do
        {
            menu = menuModificaUsuario();

            switch(menu)
            {

            case 1:

                printf("Cambiar nombre:");
                fread(&usuarioActualizado, sizeof(stUsuario), 1, bufferArchivo);
                muestraUnUsuario(usuarioActualizado);


                printf("\n Este es el archivo que queres modificar? s/n: \n");
                fflush(stdin);
                scanf("%c", &modif);

                if(modif == 's')
                {

                    printf("\n\nEscribi el nombre o los nombres: \n");
                    fflush(stdin);
                    gets(nombre);

                    strcpy(usuarioActualizado.nombre, nombre);
                    fseek(bufferArchivo, (-1) * sizeof(stUsuario), SEEK_CUR);
                    fwrite(&usuarioActualizado, sizeof(stUsuario), 1, bufferArchivo);

                }
                break;

            case 2:

                printf("Elegiste cambiar el apellido de: \n");

                fseek(bufferArchivo, sizeof(stUsuario)* pos, SEEK_SET);
                fread(&usuarioActualizado, sizeof(stUsuario), 1, bufferArchivo);
                muestraUnUsuario(usuarioActualizado);

                printf("Este es el archivo que queres modificar? s/n: ");
                fflush(stdin);
                scanf("%c", &modif);
                system("cls");
                if(modif == 's')
                {

                    printf("\n\nEscribi el nuevo apellido: ");
                    fflush(stdin);
                    gets(apellido);
                    strcpy(usuarioActualizado.apellido, apellido);
                    fseek(bufferArchivo, (-1) * sizeof(stUsuario), SEEK_CUR);
                    fwrite(&usuarioActualizado, sizeof(stUsuario), 1, bufferArchivo);
                }
                break;

            case 3:
                printf("Elegiste cambiar el Password");

                fseek(bufferArchivo, sizeof(stUsuario)* pos, SEEK_SET);
                fread(&usuarioActualizado, sizeof(stUsuario), 1, bufferArchivo);
                muestraUnUsuario(usuarioActualizado);

                printf("Este es el archivo que queres modificar? s/n: ");
                fflush(stdin);
                scanf("%c", &modif);
                system("cls");
                if(modif == 's')
                {

                    printf("\n\nEscribi el nuevo Password: ");
                    fflush(stdin);
                    gets(password);
                    strcpy(usuarioActualizado.apellido, apellido);
                    fseek(bufferArchivo, (-1) * sizeof(stUsuario), SEEK_CUR);
                    fwrite(&usuarioActualizado, sizeof(stUsuario), 1, bufferArchivo);
                }
                break;

            case 4:

                printf("Elegiste cambiar el email de: \n");

                fseek(bufferArchivo, sizeof(stUsuario)* pos, SEEK_SET);
                fread(&usuarioActualizado, sizeof(stUsuario), 1, bufferArchivo);
                muestraUnUsuario(usuarioActualizado);

                printf("Este es el archivo que queres modificar? s/n: ");
                fflush(stdin);
                scanf("%c", &modif);
                system("cls");
                if(modif == 's')
                {

                    printf("\n\nEscribi el nuevo email: ");
                    fflush(stdin);
                    gets(email);
                    strcpy(usuarioActualizado.mail, email);
                    fseek(bufferArchivo, (-1) * sizeof(stUsuario), SEEK_CUR);
                    fwrite(&usuarioActualizado, sizeof(stUsuario), 1, bufferArchivo);
                }
                break;

            case 5:
                printf("Elegiste cambiar el genero");

                fseek(bufferArchivo, sizeof(stUsuario)* pos, SEEK_SET);
                fread(&usuarioActualizado, sizeof(stUsuario), 1, bufferArchivo);
                muestraUnUsuario(usuarioActualizado);

                printf("Este es el archivo que queres modificar? s/n: ");
                fflush(stdin);
                scanf("%c", &modif);
                system("cls");

                if(modif == 's')
                {

                    printf("\n\nEscribi el nuevo genero: ");
                    scanf("%gn", &usuarioActualizado.genero);
                    fseek(bufferArchivo, (-1) *sizeof(stUsuario), SEEK_CUR);
                    fwrite(&usuarioActualizado, sizeof(stUsuario), 1, bufferArchivo);
                }
                break;



            case 6:
                printf("Elegiste activar o dar de baja ");

                fseek(bufferArchivo, sizeof(stUsuario)* pos, SEEK_SET);
                fread(&usuarioActualizado, sizeof(stUsuario), 1, bufferArchivo);
                muestraUnUsuario(usuarioActualizado);

                printf("Dar de baja? s/n: ");
                fflush(stdin);
                scanf("%c", &modif);
                system("cls");

                if(modif == 's')
                {
                    do
                    {


                        printf("\n\nPara activar, escribi: 0 ");
                        printf("\n\nPara dar de baja, escribi: 1 \n");

                        scanf("%d", &usuarioActualizado.activo);
                        if (usuarioActualizado.activo <0 || usuarioActualizado.activo >1)
                        {
                            system("cls");
                            printf("Solo se puede escribir 1 o 0. Intentalo de nuevo");
                        }
                    }
                    while(usuarioActualizado.activo <0 || usuarioActualizado.activo >1);


                    if(usuarioActualizado.activo == 0)
                    {

                        printf("Activado");
                    }
                    else
                    {
                        printf("Diste de baja");
                    }

                    fseek(bufferArchivo, (-1) *sizeof(stUsuario), SEEK_CUR);
                    fwrite(&usuarioActualizado, sizeof(stUsuario), 1, bufferArchivo);
                }
                break;

            }

            printf("\nDesea hacer otro cambio ? s/n\n ");
            fflush(stdin);
            control= getch();
            system("cls");

        }
        while(control == 's');
        fclose(bufferArchivo);
    }
    return usuarioActualizado;
}

int menuModificaUsuario()
{

    int control=0;

    printf("1) Nombres\n");
    printf("2) Apellido\n");
    printf("3) Password\n");
    printf("4) Mail\n");
    printf("5) Genero\n");
    printf("6) Dar de baja\n");
    scanf("%d", &control);

    system("cls");

    return control;
}

void muestraUnUsuario(stUsuario aux)
{

    printf("\n  -----------------------------------------------------------------");
    printf("\n  ID                      : %d", aux.idUsuario);
    printf("\n  Nombre                  : %s", aux.nombre);
    printf("\n  Apellido                : %s", aux.apellido);
    printf("\n  Username                : %s", aux.userName);
    printf("\n  Password                : %s", aux.password);
    printf("\n  Email                   : %s", aux.mail);
    printf("\n  Genero                  : %c", aux.genero);
    printf("\n  Puntaje                 : %d", aux.puntaje);
    printf("\n  Nivel                   : %d", aux.nivel);
    printf("\n  Cantidad de contenidos  : %d", aux.validosContenidos);
    printf("\n  Rol                     : %d", aux.rol);
    printf("\n  Baja s/n                : %d\n", aux.activo);
}

void muestraUsuarioArchivo(char archivo[])
{
    stUsuario aux;
    FILE * bufferArchivo = fopen(archivo,"rb");

    if(bufferArchivo!=NULL)
    {

        while(fread(&aux, sizeof(stUsuario), 1, bufferArchivo) > 0)
        {
            muestraUnUsuario(aux);
        }

        fclose(bufferArchivo);

    }
    else
    {
        printf("\nERROR DE APERTURA DE ARCHIVO ");
    }

}

///encontre la solucion al problema estaba enviando mal el argumento user
int buscaPosicionUser(char archivo[], char user[])
{
    int pos = 0;
    int flag = 0;
    stUsuario aux;


    FILE * bufferArchivo = fopen(archivo, "rb");

    if(bufferArchivo)
    {
        while(!feof(bufferArchivo)&& flag == 0)
        {
            if(fread(&aux, sizeof(stUsuario), 1, bufferArchivo) > 0)
            {

                if(strcmp(aux.userName, user) == 0)
                {
                    pos = ftell(bufferArchivo)/sizeof(aux)-1;
                    flag = 1;

                }

            }
        }
        fclose(bufferArchivo);
    }

    return pos;
}

///-////////////////////////////////////////////////
///-//////////////Administrador/////////////////////
///-////////////////////////////////////////////////

///usuarioInicio();
void InicioADM()
{
    char control = 's';
    int menu;

    do
    {
        system("cls");
        printf("\N\N===>INGRESE COMO ADMINISTRADOR<==\n");
        printf("1) Loguearse\n");
        printf("2) Registrarse\n");
        scanf("%d", &menu);

        switch(menu)
        {
        case 1:
            system("cls");
            logueoUsuario("usuarios.dat");
            break;
        case 2:
            system("cls");
            creaUserName("usuarios.dat");
            printf("\Desea continuar en el programa? (s/n)\n ");
            fflush(stdin);
            control= getch();
            break;
        }
    }
    while(control == 's');


}
///LogueoAdmin () admin
void logueoADM(char archivo[])
{
    stUsuario usuario;
    char user[20];
    char pass[20];
    int existeUser;
    int existePass;

    printf("Ingrese el UserName\n");
    fflush(stdin);
    gets(user);

    printf("Ingrese su Pass\n");
    fflush(stdin);
    gets(pass);

    existeUser = existeUserPorUserName(archivo, user);

    if(existeUser == 1)
    {
        system("cls");

        usuario = buscaUserPorUserName(archivo, user);

        if(strcmp(usuario.password, pass) == 0)
        {

            menuUsuario("usuarios.dat", usuario);

        }
        else
        {
            printf("La contraseña es invalida, intente nuevamente\n");

        }


    }
    else
    {

        printf("El usuario no existe\n");

    }

}
///menuAdmin () admin
void menuADM(char archivo[], stUsuario usuario)
{

    stUsuario usuarioActualizado;
    usuarioActualizado = usuario;
    char control = 's';
    int menu;
    int existe;
    int idContenido;

    do
    {
        printf("Inicio de sesion correcto\n");
        printf("Que desea hacer?\n");
        printf("1) Modificar perfil\n");//ya esta
        printf("2) Crear Contenido\n");//ya esta
        printf("3) Ver contenido\n");//ya esta
        printf("4) crear mensajes\n");
        printf("5) Ver mensajes\n");
        printf("6) Ver mi perfil\n");//ya esta
        printf("\N\N===>FUNCIONES DE ADMINISTRADOR<==\n");
        printf("1)Crear usuarios<==\n");
        printf("2)Eliminar usuario <==\n");
        printf("3)Mostrar todos los usuarios <==\n");
        printf("4)Cargar Post <==\n");
        printf("4)Modificar Post <==\n");
        printf("4)Eliminar post <==\n");
        printf("7) Salir\n");


        scanf("%d", &menu);

        switch(menu)
        {
        case 1:
            system("cls");
            usuario = modificaRegistro("usuarios.dat", usuario.userName);
            printf("\Desea continuar en el programa? s/n\n ");
            fflush(stdin);
            control= getch();
            break;
        case 2:
            system("cls");
            idContenido = creaContenido("contenidos.dat");
            usuario = actualizarArregloContenido("usuarios.dat", usuario, idContenido);
            printf("\Desea continuar en el programa? s/n\n ");
            fflush(stdin);
            control= getch();
            break;
        case 3:
            system("cls");
            printf("Ver contenido \n");
            printf("Contenidos: %d \n", usuario.validosContenidos);

            muestraTodosLosContenidoDeUnUsuario("contenidos.dat", usuario);

            printf("\Desea continuar en el programa? s/n\n ");
            fflush(stdin);
            control= getch();
            break;
        case 6:
            system("cls");
            printf("Mi perfil:");
            muestraUnUsuario(usuario);
            break;
        case 7:
            control = 'n';
            break;
        default:
            printf("La opcion no existe");
            break;

        }
    }
    while(control == 's');



}
///formulario de admin lo que cambia es que se añade la funcion valido ADM
void formularioADM(char archivo[])
{
    stUsuario aux;
    char opcion;
    int id = buscaUltimoIdUsuario(archivo);

    FILE * bufferArchivo = fopen(archivo,"ab");

    if(bufferArchivo != NULL)
    {

        printf("==> userName: ");
        fflush(stdin);
        gets(aux.userName);
        int existeUserName = existeUserPorUserName("usuarios.dat", aux.userName);
        if(existeUserName == 0)
        {
            printf("Completar todos los campos obligatorios\n\n");
            printf("==> Nombre: ");
            fflush(stdin);
            gets(aux.nombre);

            printf("==> Apellido: ");
            fflush(stdin);
            gets(aux.apellido);

            printf("==> password solo se aceptan letras, como maximo 20: ");
            fflush(stdin);
            gets(aux.password);


            printf("==> mail: ");
            fflush(stdin);
            gets(aux.mail);

            printf("==> genero: ");
            fflush(stdin);
            scanf("%c", &aux.genero);

            printf("==> Gracias por registrarse\n");


            aux.activo = 0; ///0 para activos, 1 para inactivos
            aux.rol = 1; /// 0 porque es admin
            aux.puntaje = 0;///inicio del puntaje
            aux.nivel = 0;
            aux.validosContenidos = 0;
            aux.listadoIdsContenidosGuardados[50];

            id++;
            aux.idUsuario = id;


            fwrite(&aux, sizeof(stUsuario), 1, bufferArchivo);
        }
        else
        {
            printf("El usuario con el username %s ya existe, vuelva a intentarlo \n", aux.userName);
        }

        printf ("cualquier tecla para continuar");
        opcion = getch ();
        system ("cls");
        fclose(bufferArchivo);
    }

}


///-////////////////////////////////////////////////
///-//////////////contenido/////////////////////////
///-////////////////////////////////////////////////

int creaContenido(char archivo[])
{
    stContenido contenido;

    char opcion;
    int id = buscaUltimoIdContenido(archivo);

    FILE * bufferArchivo = fopen(archivo,"ab");

    if(bufferArchivo != NULL)
    {

        printf("Completar todos los campos obligatorios\n\n");
        printf("==> Titulo: ");
        fflush(stdin);
        gets(contenido.titulo);

        printf("==> Descripcion: ");
        fflush(stdin);
        gets(contenido.descripcion);

        printf("==> Categoria: ");
        fflush(stdin);
        gets(contenido.categoria);



        id++;
        contenido.idContenido = id;
        contenido.likes = 0;
        contenido.puntosPorCompartir = 0;
        contenido.activo = 1;


        fwrite(&contenido, sizeof(stContenido), 1, bufferArchivo);


        printf ( " cualquier tecla para continuar " );
        opcion = getch ();
        system ( " cls " );


        fclose(bufferArchivo);

    }
    return id;

}

int buscaUltimoIdContenido(char archivo[])
{
    stContenido contenido;
    int id = 0;

    FILE * bufferArchivo = fopen(archivo, "r + b");///abro archivo modo lectura

    if(bufferArchivo)
    {

        fseek(bufferArchivo,-1 * sizeof(stContenido),SEEK_END);

        if(fread(&contenido, sizeof(stContenido),1,bufferArchivo) > 0)
        {
            id = contenido.idContenido;
        }
        fclose(bufferArchivo);
    }
    return id;
}

void muestraUnContenido(stContenido contenido)
{

    printf("\n  -----------------------------------------------------------------");
    printf("\n  ID contenido            : %d", contenido.idContenido);
    printf("\n  Titulo                  : %s", contenido.titulo);
    printf("\n  Descripcion             : %s", contenido.descripcion);
    printf("\n  Categoria               : %s", contenido.categoria);
    printf("\n  Likes                   : %d", contenido.likes);
    printf("\n  Puntos Por Compartir    : %d", contenido.puntosPorCompartir);
    printf("\n  Activos                 : %d", contenido.activo);
    printf("\n  -----------------------------------------------------------------\n");
}

void muestraTodosLosContenidoDeUnUsuario(char archivoContenido[], stUsuario usuario)
{
    stContenido contenido;

    FILE * bufferArchivo = fopen(archivoContenido,"rb");

    if(bufferArchivo!=NULL)
    {
        while(fread(&contenido, sizeof(stContenido),1, bufferArchivo) > 0 )
        {
            printf("Id contenido: %d \n", contenido.idContenido);

            for(int i = 0; i < usuario.validosContenidos; i++)
            {
                if(usuario.listadoIdsContenidosGuardados[i] == contenido.idContenido)
                {
                    muestraUnContenido(contenido);
                }
            }
        }
        fclose(bufferArchivo);
    }
    else
    {
        printf("\nERROR DE APERTURA DE ARCHIVO ");
    }
}

void muestraContenidoArchivo(char archivo[])
{
    stContenido contenido;
    FILE * bufferArchivo = fopen(archivo,"rb");

    if(bufferArchivo!=NULL)
    {

        while(fread(&contenido, sizeof(stContenido), 1, bufferArchivo) > 0)
        {
            muestraUnContenido(contenido);
        }

        fclose(bufferArchivo);

    }
    else
    {
        printf("\nERROR DE APERTURA DE ARCHIVO ");
    }

}

stUsuario actualizarArregloContenido(char archivo[], stUsuario usuario, int idContenido)
{
    int pos;

    FILE * bufferArchivo = fopen(archivo, "r+b");
    if(bufferArchivo)
    {

        pos = buscaPosicionUser(archivo, usuario.userName);

        fseek(bufferArchivo, sizeof(stUsuario) * pos, SEEK_SET);

        usuario.listadoIdsContenidosGuardados[usuario.validosContenidos] = idContenido;
        usuario.validosContenidos++;
        usuario.puntaje = usuario.puntaje + 10;
        if(usuario.puntaje % 30 == 0)
        {
            usuario.nivel++;
        }

        fseek(bufferArchivo, (-1) * sizeof(stUsuario), SEEK_CUR);
        int update = fwrite(&usuario, sizeof(stUsuario), 1, bufferArchivo);
    }
    fclose(bufferArchivo);

    return usuario;
}



///-/////////////////////////////////////////////////
///-//////////////mensajeria/////////////////////////
///-/////////////////////////////////////////////////



stContenido buscaContenidoPorID(char archivo[],int id)
{
    stContenido aux;
    int flag = 0;

    FILE * bufferArchivo = fopen(archivo, "rb");

    if(bufferArchivo!=NULL)
    {

        while(flag == 0 && fread(&aux, sizeof(stContenido),1, bufferArchivo) > 0 )
        {

            if(aux.idContenido==id)
            {
                flag = 1;
            }
        }

        fclose(bufferArchivo);
    }


    return aux;

}

void enviarContenido(stUsuario emisor, const char* usernameDelDestinatario, int idDeContenido)
{
    stMensajeria mensajeria;

    FILE* archivoDeMensajes = fopen(mensajes_dat, "ab");
    FILE* archivoDeUsuario = fopen(usuarios_dat, "rb");


    mensajeria.idUsuarioEmisor = emisor.idUsuario;

    stUsuario destinatario = buscaUserPorUserName(usuarios_dat,usernameDelDestinatario);

    mensajeria.idUsuarioReceptor = destinatario.idUsuario;

    stContenido contenido = buscaContenidoPorID(contenido_dat,idDeContenido);
    mensajeria.conten = contenido;
    mensajeria.idContenidoEnviado = contenido.idContenido;
    mensajeria.leido = 0;

    /// función crear mensaje
    strcpy(mensajeria.conten.titulo, contenido.titulo);


    /// mensajeria.mensaje = mensaje creado por el emisor
    printf("Ingrese su mensaje: \n");
    fflush(stdin);
    gets(mensajeria.mensaje);
    /// guardar mensajeria en archivoDeMensajes

    size_t result = fwrite(&mensajeria, sizeof(stMensajeria), 1, archivoDeMensajes);

    if (result != 1)
    {
        printf("Ocurrio un error en enviar el mensaje");
    }
    fclose(archivoDeUsuario);
    fclose(archivoDeMensajes);
}





void muestraArchivosdeMensajes(stUsuario usuario)
{
    stMensajeria mensajes;

    FILE * bufferArchivo = fopen(mensajes_dat,"rb");

    if(bufferArchivo!=NULL)
    {
        while(fread(&mensajes, sizeof(stMensajeria),1, bufferArchivo) > 0 )
        {
            printf("Tu id de usuario: %d \n", usuario.idUsuario);

            if(usuario.idUsuario == mensajes.idUsuarioReceptor)
            {

                VerMensajes(mensajes);
            }

        }
        fclose(bufferArchivo);
    }
    else
    {
        printf("\nERROR DE APERTURA DE ARCHIVO ");
    }
}




void VerMensajes(stMensajeria mensajes)
{
    printf("\n\n  -----------------------------------------------------------------");
    printf("\n  Titulo                  : %s", mensajes.idUsuarioEmisor);
    printf("\n  Descripcion             : %s", mensajes.mensaje);
    printf("\n  Descripcion             : %s", mensajes.mensaje);
    printf("\n  ID contenido            : %d", mensajes.idContenidoEnviado);
    printf("\n  Descripcion             : %s", mensajes.conten.categoria);
    printf("\n  Descripcion             : %s", mensajes.conten.titulo);

    printf("\n\n  -----------------------------------------------------------------");

}


///-/////////////////////////////////////////////////
///-////////////////////CATEGORIAS///////////////////
///-/////////////////////////////////////////////////

void crearCategoria (char archivo[])
{
    stCategoria a;
    FILE*archi;
    char letra='s';
    int i=ultimoId(archivo);
    archi=fopen(archivo, "ab" );
    if (archi!=NULL)
    {
        while(letra=='s')
        {
            printf("\n");
            puts("------------------------------------------------");
            printf("ingrese nombre de la categoria a agregar: ");
            fflush(stdin);
            scanf("%s", &a.nombreCat);
            puts("------------------------------------------------");
            i++;
            a.id=i;
            fwrite(&a, sizeof(stCategoria), 1, archi);
            printf("Desea seguir cargando categorias?(s/n)");
            fflush(stdin);
            scanf("%c", &letra);

        }
        fclose(archi);
    }
}
void mostrarCategorias(char archivo[])
{
    stCategoria a;
    FILE*pArchi = fopen(archivo, "rb");
    if (pArchi)
    {
        while(fread(&a, sizeof(stCategoria), 1, pArchi)>0)
        {
            mostrarUnaCategoria(a);
        }
        fclose(pArchi);
    }

}
void mostrarUnaCategoria(stCategoria a)
{
    printf("\nNombre de la categoria..................:%s (id: %d)", a.nombreCat, a.id);
}
int ultimoId(char archivo[])
{
    FILE *archi  = fopen( archivo, "r+b");
    stCategoria a;
    int ultimoId=0;
    if(archi)
    {
        fseek(archi, -1*sizeof(stCategoria), SEEK_END);
        if (fread(&a, sizeof(stCategoria), 1, archi)>0)
        {
            ultimoId=a.id;
        }
        fclose(archi);
    }
    return ultimoId;
}

void cargarArregloDeCategorias(char archivo[], stCategoria arregloCategorias[], int validos)
{
    stCategoria a;
    FILE *archi = fopen(archivo, "rb");
    if (archi)
    {
        int i=0;
        while(fread(&a, sizeof(stCategoria), 1, archi)>0 && i<validos )
        {
            arregloCategorias[i]=a;
            i++;
        }
        fclose(archi);
    }

}

void mostrarArreglo (stCategoria arregloCategorias[], int validos)
{
    int i=0;
    for (i=0; i<validos; i++ )
    {
        mostrarUnaCategoria(arregloCategorias[i]);
    }
}

int cantidadDatosStCategorias(char archivo[])
{
    stCategoria a;
    int i=0;
    FILE *archi = fopen(archivo, "rb");
    if (archi)
    {
        while(fread(&a, sizeof(stCategoria), 1, archi)>0)
        {
            i++;
        }
        fclose(archi);
    }
    return i;
}

void updateArregloAarchivo(stCategoria arregloCategorias[], int validos, char archivo[])
{
    FILE * archi=fopen(archivo, "wb");
    if(archi)
    {
        int i=0;
        for (i=0; i<validos; i++)
        {
            fwrite(&arregloCategorias[i], sizeof(stCategoria), 1, archi);
        }
        fclose(archi);
    }

}
