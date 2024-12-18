#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256

typedef struct {
    char buffer[MAX_BUFFER];
    int isDataAvailable;
} Dispositivo;

void guardarDatosDisco(Dispositivo *disco) {
    if (disco->isDataAvailable) {
        printf("Disco duro: datos guardados\n");
    } else {
        printf("Disco duro: No hay datos para guardar.\n");
    }
}

void imprimirDatos(Dispositivo *disco) {
    if (disco->isDataAvailable) {
        printf("Impresora: Imprimiendo: %s\n", disco->buffer);
        disco->isDataAvailable = 0;
    } else {
        printf("Impresora: No hay datos para imprimir.\n");
    }
}

void ingresarDatosTeclado(Dispositivo *disco) {
    printf("Teclado: Ingrese el texto a almacenar: ");
    fgets(disco->buffer, MAX_BUFFER, stdin);

    disco->buffer[strcspn(disco->buffer, "\n")] = '\0';
    disco->isDataAvailable = 1;

    guardarDatosDisco(disco);
}

void menu(Dispositivo *disco) {
    int opcion;

    do {
        printf("\nMenu de dispositivos:\n");
        printf("1. Ingresar datos desde el teclado\n");
        printf("2. Imprimir los datos\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch(opcion) {
            case 1:
                ingresarDatosTeclado(disco);
                break;
            case 2:
                imprimirDatos(disco);
                break;
            case 3:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
        }
    } while(opcion != 3);
}

int main() {
    Dispositivo disco = {.isDataAvailable = 0};

    menu(&disco);

    return 0;
}
