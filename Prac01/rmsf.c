/*Práctica_01
Alumnos: Claudia y Carlos*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>  
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){ //argc es el numero de argumentos y argv es el arreglo de argumentos
    struct stat st = {0}; //estructura que contiene informacion sobre el archivo
    struct passwd *pw = getpwuid(getuid()); //obtiene la informacion del usuario
    char *homedir = pw->pw_dir; //obtiene el directorio home del usuario
    char *path = "/.trash/"; //ruta de la carpeta .trash
    char *dir = strcat(homedir, path); //concatena el directorio home con la ruta de la carpeta .trash

    opendir(dir); //abre la carpeta .trash
    setuid(0); //establece el id del usuario en 0 (root) para que pueda crear la carpeta .trash

    if (getuid() != 0){ //si el usuario no es root
        setuid(0); //establece el id del usuario en 0 (root)
    }
    
    if (stat(dir, &st) == -1) { //si la carpeta .trash no existe
        mkdir(dir, 0700); //crea la carpeta .trash
    }
   
    if (errno == ENOENT){ //si no se puede abrir la carpeta .trash
        perror("opendir"); //imprime mensaje de error si no se puede abrir la carpeta .trash
        exit(1); //termina el programa
    }
    
    if (argc == 2){ //si se ingresa un argumento
        char *file = argv[1]; //obtiene el nombre del archivo
        // Comprobar si es un archivo o directorio
        struct stat s;
        if (stat(file, &s) == 0){
            if (s.st_mode & S_IFDIR){
                printf("This is a directory");
                //check if the directory is empty
                DIR *dir;
                struct dirent *ent;
                if ((dir = opendir (file)) != NULL) {
                    while ((ent = readdir (dir)) != NULL) {
                        printf ("%s ", ent->d_name);
                    }
                    closedir (dir);
                } else {
                    perror ("");
                    return EXIT_FAILURE;
                }
            } else if (s.st_mode & S_IFREG){
                printf("This is a file");
            }
        } else {
            perror("stat");
            return EXIT_FAILURE;
        }
        char *newfile = strcat(dir, file); //concatena la ruta de la carpeta .trash con el nombre del archivo
        rename(file, newfile); //mueve el archivo a la carpeta .trash
    }

    if (argc == 3){ //si se ingresa otro argumento
        char *file = argv[2]; //obtiene el nombre del archivo
        char *newfile = strcat(dir, file); //concatena la ruta de la carpeta .trash con el nombre del archivo
        char *option = argv[1]; //obtiene la opcion ingresada
        if (isatty(fileno(stdin))){ //si el dispositivo de entrada estándar es una terminal
            if (strcmp(option, "-i") == 0){ //si la opcion es -i
                char *answer = malloc(10); //variable para guardar la respuesta del usuario
                printf("¿Está seguro que desea eliminar el %s? (si/no): " , argv[2]); //imprime mensaje para solicitar confirmacion
                scanf("%s", answer); //guarda la respuesta del usuario
                if (strcmp(answer, "si") == 0){ //si la respuesta es si
                    rename(file, newfile); //mueve el archivo a la carpeta .trash
                }
                else if (strcmp(answer, "no") == 0){ //si la respuesta es no
                    printf("El archivo no se ha eliminado de forma segura. \n"); //imprime mensaje de que el archivo no se ha eliminado
                }
                else{ //si la respuesta es cualquier otra cosa
                    printf("Respuesta no válida. \n"); //imprime respuesta no valida
                }
            }
        }

        
    }
    return 0;
}











