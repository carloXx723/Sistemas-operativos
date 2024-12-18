#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARCHIVOS 5
#define MAX_SECTORES 5
#define TAMANIO_SECTOR 128

typedef struct {
    char contenido[TAMANIO_SECTOR];
    int ocupado;
    int archivoID;
} Sector;

typedef struct {
    Sector sectores[MAX_SECTORES];
} Disco;

typedef struct {
    int archivoID;
    int sectorInicio;
    int sectoresTotales;
} Archivo;

void inicializarDisco(Disco *disco) {
    for (int i = 0; i < MAX_SECTORES; i++) {
        disco->sectores[i].ocupado = 0;
        disco->sectores[i].archivoID = -1;
    }
}

void escribirArchivo(Disco *disco, Archivo *archivo, const char *contenido) {
    for (int i = 0; i < archivo->sectoresTotales; i++) {
        int sectorIndex = archivo->sectorInicio + i;
        if (sectorIndex < MAX_SECTORES) {
            strncpy(disco->sectores[sectorIndex].contenido, contenido, TAMANIO_SECTOR);
            disco->sectores[sectorIndex].ocupado = 1;
            disco->sectores[sectorIndex].archivoID = archivo->archivoID;
        }
    }
    printf("Archivo %d escrito en el disco.\n", archivo->archivoID);
}

void leerArchivo(Disco *disco, Archivo *archivo) {
    printf("Leyendo archivo %d desde el disco...\n", archivo->archivoID);
    for (int i = 0; i < archivo->sectoresTotales; i++) {
        int sectorIndex = archivo->sectorInicio + i;
        if (sectorIndex < MAX_SECTORES && disco->sectores[sectorIndex].ocupado) {
            printf("Sector %d: %s\n", sectorIndex, disco->sectores[sectorIndex].contenido);
        } else {
            printf("Sector %d vacío.\n", sectorIndex);
        }
    }
}

Archivo* buscarArchivo(Disco *disco, int archivoID) {
    static Archivo archivoEncontrado;
    for (int i = 0; i < MAX_SECTORES; i++) {
        if (disco->sectores[i].ocupado && disco->sectores[i].archivoID == archivoID) {
            archivoEncontrado.archivoID = archivoID;
            archivoEncontrado.sectorInicio = i;
            archivoEncontrado.sectoresTotales = 1;
            return &archivoEncontrado;
        }
    }
    return NULL;
}

int main() {
    Disco disco;
    inicializarDisco(&disco);

    int archivoID;
    char contenido[TAMANIO_SECTOR];

    Archivo archivo1 = {1, 0, 1};
    Archivo archivo2 = {2, 1, 1};
    Archivo archivo3 = {3, 2, 1};

    escribirArchivo(&disco, &archivo1, "Contenido del archivo 1");
    escribirArchivo(&disco, &archivo2, "Contenido del archivo 2");
    escribirArchivo(&disco, &archivo3, "Contenido del archivo 3");

    int opcion;

    do {
        printf("\nMenu:\n");
        printf("1. Buscar archivo por ID\n");
        printf("2. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();

        if (opcion == 1) {
            printf("Ingrese el ID del archivo a buscar: ");
            scanf("%d", &archivoID);

            Archivo *archivoEncontrado = buscarArchivo(&disco, archivoID);

            if (archivoEncontrado != NULL) {
                leerArchivo(&disco, archivoEncontrado);
            } else {
                printf("Archivo con ID %d no encontrado.\n", archivoID);
            }
        }
    } while (opcion != 2);

    return 0;
}
