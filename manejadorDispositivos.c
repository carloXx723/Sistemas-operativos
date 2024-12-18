#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char buffer[256];
    int isOpen;
} DispositivoEntrada;

int abrirDispositivo(DispositivoEntrada* dispositivo) {
    if (dispositivo->isOpen) {
        printf("El dispositivo ya está abierto.\n");
        return -1;
    }
    dispositivo->isOpen = 1;
    printf("Dispositivo abierto con éxito.\n");
    return 0;
}

void cerrarDispositivo(DispositivoEntrada* dispositivo) {
    if (!dispositivo->isOpen) {
        printf("El dispositivo ya está cerrado.\n");
        return;
    }
    dispositivo->isOpen = 0;
    printf("Dispositivo cerrado con éxito.\n");
}

int leerDatos(DispositivoEntrada* dispositivo) {
    if (!dispositivo->isOpen) {
        printf("El dispositivo no está abierto.\n");
        return -1;
    }
    
    printf("Datos en el buffer: %s\n", dispositivo->buffer);
    return 0;
}

int escribirDatos(DispositivoEntrada* dispositivo) {
    if (!dispositivo->isOpen) {
        printf("El dispositivo no está abierto.\n");
        return -1;
    }
    
    printf("Escriba los datos para almacenar en el buffer: ");
    fgets(dispositivo->buffer, sizeof(dispositivo->buffer), stdin);
    
    size_t len = strlen(dispositivo->buffer);
    if (len > 0 && dispositivo->buffer[len - 1] == '\n') {
        dispositivo->buffer[len - 1] = '\0';
    }

    printf("Datos escritos en el buffer: %s\n", dispositivo->buffer);
    return 0;
}

void mostrarMenu() {
    printf("\nMenu \n");
    printf("1. Escribir en el buffer\n");
    printf("2. Leer del buffer\n");
    printf("3. Salir\n");
    printf("Seleccione una opción: ");
}

int main() {
    DispositivoEntrada dispositivo = { .isOpen = 0 };
    int opcion;
    
    if (abrirDispositivo(&dispositivo) != 0) {
        return -1;
    }

    do {
        mostrarMenu();
        scanf("%d", &opcion);
        getchar();
        
        switch (opcion) {
            case 1:
                escribirDatos(&dispositivo);
                
                break;
            case 2:
                leerDatos(&dispositivo);
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida, intente nuevamente.\n");
                break;
        }
    } while (opcion != 3);

    cerrarDispositivo(&dispositivo);
    return 0;
}
