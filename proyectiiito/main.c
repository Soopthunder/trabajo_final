#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <stdbool.h>




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
    int rol;             /// 1: es admin - 0: es comun
    int activo;          /// indica 1 o 0 si el usuario está activo
} stUsuario;






///Estructura de Contenido

typedef struct
{
    int dia;
    int mes;
    int anio;
    int idContenido; // auto incremental
    char titulo[30];
    char descripcion[300];
    char categoria[30];
    int likes;
    int puntosPorCompartir;
    int activo;                     // indica 1 o 0 si el contenido está activo
} stContenido;



///Definimos estructura de POSTEOS
typedef struct
{

    int id;
    int dia;
    int mes;
    int anio;
    char titulo[30];
    char post [30][30];
    int likes;


} stPost;
p




///Estructura de Mensajería

typedef struct
{
    int idUsuarioEmisor;
    int idUsuarioReceptor;
    int idContenidoEnviado;
    char mensaje[300];
    int leido;                      // 1:si 0:no
} stMensajeria;

///titulo proyecto despliega los nombres de los alumnos en todo el trabajo.
void tituloProyecto();

///El menu de admin gestiona las tareas basicas del admin: Gestion de usuarios, gestion de post.
void menuAdministrador();
///Entrar gestiona el ingreso si es user o admin.
void entrar(char archivo[]);

///Gestiona el primer ingreso y podras seleccionar que tarea realizar.
void menuIngresar();

///Crea un usuario nuevo.
void formularioUsuario(char archivo[]);

///Retorna el ultimo ID, para su posterior uso.
int buscaUltimoId(char archivo[]);

///
void cargaUsuario(char archivo[]);

///Muestra todo el contenido de un usuario.
void muestraUnUsuario(stUsuario aux);

///Muestra todos los usuarios de un archivo.
void muestraUsuarioArchivo(char archivo[]);

///
int cuentaRegistro(char archivo[], int tamanioSt);

///Permite buscar el strig y retorna un flag 1 o 0.
int buscaIgualString(char archivo[], char palabra[]);

///Verifica si el usuario existe y sino, lo crea.
void creaUserName(char archivo[]);

///Modifica a los usuarios.
void modificaRegistro(char archivo[], char user[]);

///Es el menu para modificar el usuario.
int menuModificaUsuario();

/// Devuelve la posicion del usuario.
int buscaPosicion(char archivo[], char user[]);









int main()
{
    int validos=0;

    stUsuario usuario[1000];
    int usuarioValidos = 0;
    menuIngresar();


    CrearPost("post.dat");
    mostrarPosts("post.dat");




    return 0;
}




///MELISA ////////////////////////////////////////////////////////////////////////////////////////////
///-////////////////////////////////////////////////////////////////////////////////////////////
///-////////////////////////////////////////////////////////////////////////////////////////////



void menuIngresar()
{
    char control = 's';
    int menu;
    char user;
    stUsuario aux;
    int existe;


    do
    {

        system("cls");
        tituloProyecto();
        printf("\n\t======================================================\n");
        printf("\n\t\t\t\n");
        printf("\n\t\t\t==> MENU PRINCIPAL <==\n");
        printf("\n\t\t\t==> 1) Entrar<==\n");
        printf("\n\t\t\t==> 2)REGISTRARSE <==\n");
        printf("\n\t\t\t==> 3)mostrar <==\n");
        printf("\n\t\t\t==> 4)modificar <==\n");
        printf("\n\t\t\t\n");
        printf("\n\t======================================================\n");
        printf("\n\tINGRESE UN NUMERO CORRESPONDIENTE AL MENU: ");
        scanf("%d", &menu);

        switch(menu)
        {
        case 1:

            system("cls");
            printf("Entrar\n");

            entrar("usuarios.dat");
            break;

        case 2:
            system("cls");
            creaUserName("usuarios.dat");

            //    formularioUsuario("usuarios.dat");

            break;
        case 3:
            system("cls");
            muestraUsuarioArchivo("usuarios.dat");
            break;

        case 4:

            system("cls");
            printf("Ingrese el user para hacer cambios\n");
            fflush(stdin);
            gets(aux.userName);
            existe = buscaIgualString("usuarios.dat", aux.userName);

            if(existe == 1)
            {

                system("cls");
                printf("==> El User ingresado EXISTE. Esta listo para ser modificado <==\n\n");

                modificaRegistro("usuarios.dat", aux.userName);

            }
            else
            {

                printf("==> El user ingresado NO existe, por lo tanto no se puede modificar <==\n\n");

            }

            break;



        }

        printf("\nDesea continuar en el programa? s/n\n ");
        fflush(stdin);
        control= getch();




    }
    while(control == 's');


}


void formularioUsuario(char archivo[])
{
    stUsuario aux;
    char opcion= 0;
    int id = buscaUltimoId(archivo);

    FILE * bufferArchivo = fopen(archivo,"ab");

    if(bufferArchivo != NULL)
    {
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
        scanf("%c", &aux.genero);

        aux.activo = 1;

        printf("==> Gracias por registrarse\n");


        aux.activo = 0; ///0 para activos, 1 para inactivos

        id++;
        aux.idUsuario = id;

        fwrite(&aux, sizeof(stUsuario), 1, bufferArchivo);

        printf ( " cualquier tecla para continuar " );
        opcion = getch ();
        system ( " cls " );


        fclose(bufferArchivo);

    }

}


int buscaUltimoId(char archivo[])
{
    stUsuario aux;
    int id = 0;

    FILE * bufferArchivo = fopen(archivo, "r + b");///abro archivo modo lectura

    if(bufferArchivo) ///Sitúa el puntero en el archivo .Posición al final del archivo
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
    printf("\n  Baja s/n                : %d\n", aux.activo);
}


int cuentaRegistro(char archivo[], int tamanioSt)
{
    int total = 0 ;

    FILE * bufferArchivo = fopen(archivo,"r + b");

    if(bufferArchivo!=NULL)
    {

        fseek (bufferArchivo, 0, SEEK_END); //desplazamiendo a partir del final

        total = ftell(bufferArchivo) / tamanioSt;//devuelve cantidad de bytes

        fclose(bufferArchivo);
    }


    return total;
}

int buscaIgualString(char archivo[], char palabra[])
{
    stUsuario aux;
    int flag = 0;

    FILE * bufferArchivo = fopen(archivo,"rb");

    if(bufferArchivo!=NULL)
    {

        while(flag == 0 && fread(&aux, sizeof(stUsuario),1, bufferArchivo) > 0 )
        {

            if(strcmp(aux.userName, palabra)== 0)
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

    printf("Ingrese el UserName\n");
    fflush(stdin);
    gets(user);

    existe = buscaIgualString(archivo, user);

    if(existe == 1)
    {

        printf("ese username ya esta en uso\n");


    }
    else
    {
        formularioUsuario(archivo);

    }
}

void modificaRegistro(char archivo[], char user[])
{

    char control = 's', modif = 's';
    int menu;
    char nombre[30];
    char apellido[30];
    char password[20];
    char email [30];
    char genero;

    stUsuario aux;
    int pos = 0;
    pos = buscaPosicion(archivo, user);

    FILE * bufferArchivo = fopen(archivo, "r+b");

    if(bufferArchivo)
    {

        fseek(bufferArchivo, sizeof(stUsuario) *pos, SEEK_SET);
        printf("\n\t\t\t==> MENU DE MODIFICACION <==\n");
        printf("\n\t\t\t==> Elija una opcion <==\n");

        do
        {
            menu = menuModificaUsuario();

            switch(menu)
            {

            case 1:

                printf("Elegiste cambiar el nombre de:");
                fseek(bufferArchivo, sizeof(stUsuario)* pos, SEEK_SET);
                fread(&aux, sizeof(stUsuario), 1, bufferArchivo);
                muestraUnUsuario(aux);

                //system("cls");
                printf("Este es el archivo que queres modificar? s/n: ");
                fflush(stdin);
                scanf("%c", &modif);
                //system("cls");
                if(modif == 's')
                {

                    printf("\n\nEscribi el nombre o los nombres: \n");
                    fflush(stdin);
                    gets(nombre);


                    strcpy(aux.nombre, nombre);
                    fseek(bufferArchivo, (-1) * sizeof(stUsuario), SEEK_CUR);
                    fwrite(&aux, sizeof(stUsuario), 1, bufferArchivo);

                }
                break;

            case 2:

                printf("Elegiste cambiar el apellido de: \n");

                fseek(bufferArchivo, sizeof(stUsuario)* pos, SEEK_SET);
                fread(&aux, sizeof(stUsuario), 1, bufferArchivo);
                muestraUnUsuario(aux);

                printf("Este es el archivo que queres modificar? s/n: ");
                fflush(stdin);
                scanf("%c", &modif);
                system("cls");
                if(modif == 's')
                {

                    printf("\n\nEscribi el nuevo apellido: ");
                    fflush(stdin);
                    gets(apellido);
                    strcpy(aux.apellido, apellido);
                    fseek(bufferArchivo, (-1) * sizeof(stUsuario), SEEK_CUR);
                    fwrite(&aux, sizeof(stUsuario), 1, bufferArchivo);
                }
                break;

            case 3:
                printf("Elegiste cambiar el Password");

                fseek(bufferArchivo, sizeof(stUsuario)* pos, SEEK_SET);
                fread(&aux, sizeof(stUsuario), 1, bufferArchivo);
                muestraUnUsuario(aux);

                printf("Este es el archivo que queres modificar? s/n: ");
                fflush(stdin);
                scanf("%c", &modif);
                system("cls");
                if(modif == 's')
                {

                    printf("\n\nEscribi el nuevo Password: ");
                    fflush(stdin);
                    gets(password);
                    strcpy(aux.apellido, apellido);
                    fseek(bufferArchivo, (-1) * sizeof(stUsuario), SEEK_CUR);
                    fwrite(&aux, sizeof(stUsuario), 1, bufferArchivo);
                }
                break;

            case 4:

                printf("Elegiste cambiar el email de: \n");

                fseek(bufferArchivo, sizeof(stUsuario)* pos, SEEK_SET);
                fread(&aux, sizeof(stUsuario), 1, bufferArchivo);
                muestraUnUsuario(aux);

                printf("Este es el archivo que queres modificar? s/n: ");
                fflush(stdin);
                scanf("%c", &modif);
                system("cls");
                if(modif == 's')
                {

                    printf("\n\nEscribi el nuevo email: ");
                    fflush(stdin);
                    gets(email);
                    strcpy(aux.mail, email);
                    fseek(bufferArchivo, (-1) * sizeof(stUsuario), SEEK_CUR);
                    fwrite(&aux, sizeof(stUsuario), 1, bufferArchivo);
                }
                break;

            case 5:
                printf("Elegiste cambiar el genero");

                fseek(bufferArchivo, sizeof(stUsuario)* pos, SEEK_SET);
                fread(&aux, sizeof(stUsuario), 1, bufferArchivo);
                muestraUnUsuario(aux);

                printf("Este es el archivo que queres modificar? s/n: ");
                fflush(stdin);
                scanf("%c", &modif);
                system("cls");

                if(modif == 's')
                {

                    printf("\n\nEscribi el nuevo genero: ");
                    scanf("%gn", &aux.genero);
                    fseek(bufferArchivo, (-1) *sizeof(stUsuario), SEEK_CUR);
                    fwrite(&aux, sizeof(stUsuario), 1, bufferArchivo);
                }
                break;



            case 6:
                printf("Elegiste activar o dar de baja ");

                fseek(bufferArchivo, sizeof(stUsuario)* pos, SEEK_SET);
                fread(&aux, sizeof(stUsuario), 1, bufferArchivo);
                muestraUnUsuario(aux);

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

                        scanf("%d", &aux.activo);
                        if (aux.activo <0 || aux.activo >1)
                        {
                            system("cls");
                            printf("Solo se puede escribir 1 o 0. Intentalo de nuevo");
                        }
                    }
                    while(aux.activo <0 || aux.activo >1);


                    if(aux.activo == 0)
                    {

                        printf("Activado");
                    }
                    else
                    {
                        printf("Diste de baja");
                    }

                    fseek(bufferArchivo, (-1) *sizeof(stUsuario), SEEK_CUR);
                    fwrite(&aux, sizeof(stUsuario), 1, bufferArchivo);
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

int buscaPosicion(char archivo[], char user[])
{
    int pos = 0;
    int flag= 0;
    stUsuario aux;

    FILE * bufferArchivo = fopen(archivo, "rb");

    if(bufferArchivo)
    {
        while(!feof(bufferArchivo)&& flag==0)
        {
            if(fread(&aux, sizeof(stUsuario), 1, bufferArchivo) > 0)
            {
                if(aux.userName == user)
                {
                    pos = ftell(bufferArchivo)/sizeof(stUsuario )-1;
                    flag = 1;
                }
            }
        }
        fclose(bufferArchivo);
    }

    return pos;
}




///JONY ////////////////////////////////////////////////////////////////////////////////////////////
///-////////////////////////////////////////////////////////////////////////////////////////////
///-////////////////////////////////////////////////////////////////////////////////////////////





//FUNCION PARA CREAR POSTEOS
void CrearPost(char misPosts[])
{

    char opcion;
    int i=0;
    stPost p;
    FILE *pArchiMisPost=fopen(misPosts, "ab");
    if(pArchiMisPost)
    {
        do
        {

            printf("\n");
            printf("\n dia:..............");
            scanf("%d", &p.dia);
            printf("\n mes:..............");
            scanf("%d", &p.mes);
            printf("\n año:..............");
            scanf("%d", &p.anio);
            fflush(stdin);
            printf("\n titulo:...........");
            scanf("%s", p.titulo);
            fflush(stdin);
            printf("\n escriba su post: \n");
            scanf("%s", p.post);
            p.id=i;
            i++;
            fwrite(&p, sizeof(stPost), 1, pArchiMisPost);
            printf("ESC para salir, cualquier tecla para continuar");
            opcion=getch();

        }
        while(opcion!=27);

        fclose(pArchiMisPost);
    }
}

///FUNCION PARA CREAR MOSTRAR POSTEOS
void mostrarPosts (char ArchiMisPost[])
{

    FILE *pPost=fopen(ArchiMisPost,"rb");
    stPost p;
    if (pPost)
    {

        while(fread(&p, sizeof(stPost), 1, pPost)>0)
        {
            mostrarUnPost(p);
        }


        fclose(pPost);
    }

}

///FUNCION PARA MOSTRAR UN POST
void mostrarUnPost(stPost p)
{

    printf("\n FECHA: %d/%d/%d", p.dia, p.mes, p.anio);
    printf("\n TITULO: %s", p.titulo);
    printf("\n POST: %s\n", p.post);
    printf("\n--------------------------------------------------");



}






///Lucas////////////////////////////////////////////////////////////////////////////////////////////
///-////////////////////////////////////////////////////////////////////////////////////////////////
///-////////////////////////////////////////////////////////////////////////////////////////////////


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


void entrar(char archivo[])
{
    stUsuario aux;
    char user[20];
    char pass[20];
    int existeUser;
    int existePass;
    char SuperUser[]="admin";
    char SuperUserPass[]="admin";
    char control = 's';



    printf("Ingrese el UserName\n");
    fflush(stdin);
    gets(user);

    printf("Ingrese su Pass\n");
    fflush(stdin);
    gets(pass);

    existeUser = buscaIgualString(archivo, user);
    existePass = buscaIgualString(archivo, pass);


    aux.rol=0;

    if(existeUser == 1 && existePass == 1)
    {
        if(strcmp(SuperUser,user)==0)
        {

            aux.rol = 1;
        }


        if(aux.rol==1)
        {
            tituloProyecto();
            printf("Registrado correctamente como admin\n");

            printf("\nDesea continuar al menu de ADMIN? s/n");
            scanf("%c", &control);

            if(control=='s')
            {
                menuAdministrador(); ///aca va menu admin
            }


        }
        else
        {
            tituloProyecto();
            printf("Registrado correctamente como usuario\n");
            printf("\nDesea continuar al menu ? s/n");
            scanf("%c", &control);

            if(control=='s')
            {
                menuAdministrador(); ///aca va el menu de usuario
            }



        }


    }
    else
    {

        printf("No se encontro en la base de datos. Registrese:\n");


    }


}


void menuAdministrador()
{


    char control = 's';
    int menu;
    char user;
    stUsuario aux;
    int existe;


    do
    {
        tituloProyecto();
        system("cls");
        printf("\n\t\t\t==> MENU PRINCIPAL <==\n");
        printf("\n\t\t\t==> 1)Crear usuarios<==\n");
        printf("\n\t\t\t==> 2)Eliminar usuario <==\n");
        printf("\n\t\t\t==> 3)Mostrar todos los usuarios <==\n");
        printf("\n\t\t\t==> 4)Cargar Post <==\n");
        printf("\n\t\t\t==> 4)Modificar Post <==\n");
        printf("\n\t\t\t==> 4)Eliminar post <==\n");
        scanf("%d", &menu);

        switch(menu)
        {
        case 1:

            system("cls");
            tituloProyecto();
            printf("Carga un usuario:\n");
            creaUserName("usuarios.dat");
            break;

        case 2:
            system("cls");
            char controls = 's';

            int iDUser;
            stUsuario aux;
            int vUsers = 0;
            vUsers=
            printf("ELIMINA UN USUARIO, COLOCANDO EL ID, EN CASO DE QUE NO LO SEPAS TE RECOMENDAMOS BUSCAR AL USUARIO Y LUEGO VOLVER\n");
            printf("\n YA TENGO EL ID ( PRESIONA LA TELCA: n) - DESEO BUSCARLO(PRESIONA LA TELCA: s)----Presiona S/n para continuar ");
            scanf("%c", &controls);


            if(controls =='s')
            {

                muestraUsuarioArchivo("usuarios.dat");
                printf("si ya encontro el id que buscaba vuelva al programa: press S para continuar: ");
                scanf("%c", &controls);
                if(controls=='s')
                {
                  ViewUsuarios(aux, vUsers);
                }

            }
            else
            {
                int validos = 0;
                printf("\nELIMINA UN USUARIO: ");
                scanf("%d", &iDUser);
                baja("usuarios.dat", validos,iDUser);

            }



            //    formularioUsuario("usuarios.dat");

            break;
        case 3:
            system("cls");
            muestraUsuarioArchivo("usuarios.dat");
            break;

        case 4:

            system("cls");
            printf("Ingrese el user para hacer cambios\n");
            fflush(stdin);
            gets(aux.userName);
            existe = buscaIgualString("usuarios.dat", aux.userName);

            if(existe == 1)
            {

                system("cls");
                printf("==> El User ingresado EXISTE. Esta listo para ser modificado <==\n\n");

                modificaRegistro("usuarios.dat", aux.userName);

            }
            else
            {

                printf("==> El user ingresado NO existe, por lo tanto no se puede modificar <==\n\n");

            }

            break;



        }

        printf("\nDesea continuar en el programa? s/n\n ");
        fflush(stdin);
        control= getch();




    }
    while(control == 's');




}


void muestraUsuarioArchivo(char archivo[])
{
    stUsuario aux;
    FILE * bufferArchivo = fopen(archivo,"rb");

    if(bufferArchivo!=NULL)
    {

        while(fread(&aux,sizeof(stUsuario),1,bufferArchivo)>0)
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


void baja(stUsuario archivo[], int validos, int id)
{
    stUsuario aux;
    int i=0;
    FILE * fp = fopen(archivo,"r+b");
    if (fp != NULL)
    {
        while (fread(&aux,sizeof(stUsuario),1,fp) > 0 && (id!=aux.idUsuario) )
        {
            i++;
        }
        if (i < validos)
        {
            archivo[i].activo=1; ///baja logica por que se que NO DEBERIA EXISTIR ya que esta el campo en 1
            fseek(fp,(-1)*sizeof(stUsuario),SEEK_CUR);
            fwrite(&archivo[i],sizeof(stUsuario),1,fp);
            printf("El dato se dio de baja con exito en el archivo");
        }
        else
        {
            printf("El dato no existe en el archivo");

        }
        fclose(fp);
    }
}


void ViewUsuarios(stUsuario a[], int v){
    for(int i=0;i<v;i++){
        muestraUnUsuario(a[i]);
    }
}



///-/////////////////////////////////////////////////////////////////////////////////////////////////////////
///-////////////////////////////////CONTENIDO////////////////////////////////////////////////////////////////
///-/////////////////////////////////////////////////////////////////////////////////////////////////////////


///FUNCION PARA MOSTRAR CONTENIDOS
void mostrarContenidos (char ArchiMisContenidos[])
{

    FILE *pContenido=fopen(ArchiMisContenidos,"rb");
    stContenido p;
    if (pContenido)
    {

        while(fread(&p, sizeof(stContenido), 1, pContenido)>0)
        {
            mostrarContenido(p);
        }


        fclose(pContenido);
    }

}

///MUESTRA UNICAMENTE UN SOLO POST Y SU CONTENIDO
void mostrarContenido(stContenido p)
{


printf("\n  -----------------------------------------------------------------");
    printf("\n  FECHA                   :%d/%d/%d", p.dia, p.mes, p.anio);
    printf("\n  Id                      : %s", p.titulo);
    printf("\n  Titulo                  : %s", p.titulo);
    printf("\n  Descripcion             : %s", p.descripcion);
    printf("\n  Categoria               : %s", p.categoria);
    printf("\n  Puntos                  : %d", p.puntosPorCompartir);
    printf("\n  Email                   : %d", p.likes);
    printf("\n  Baja s/n                : %d", p.activo);

}



