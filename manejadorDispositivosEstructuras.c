#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DISPOSITIVOS 5

typedef struct {
    char buffer[256];
    int isOpen;
} DispositivoEntrada;

DispositivoEntrada tablaDispositivos[MAX_DISPOSITIVOS];

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

int seleccionarDispositivo() {
    int id;
    printf("\nSeleccione el dispositivo (0 a %d): ", MAX_DISPOSITIVOS - 1);
    scanf("%d", &id);
    getchar();
    if (id < 0 || id >= MAX_DISPOSITIVOS) {
        printf("Dispositivo no válido.\n");
        return -1;
    }
    return id;
}

int main() {
    for (int i = 0; i < MAX_DISPOSITIVOS; i++) {
        tablaDispositivos[i].isOpen = 1;
    }

    int opcion, dispositivoSeleccionado;

    do {
        dispositivoSeleccionado = seleccionarDispositivo();
        if (dispositivoSeleccionado == -1) continue;

        do {
            mostrarMenu();
            scanf("%d", &opcion);
            getchar();

            switch (opcion) {
                case 1:
                    escribirDatos(&tablaDispositivos[dispositivoSeleccionado]);
                    break;
                case 2:
                    leerDatos(&tablaDispositivos[dispositivoSeleccionado]);
                    break;
                case 3:
                    printf("Saliendo del dispositivo seleccionado...\n");
                    break;
                default:
                    printf("Opción no válida, intente nuevamente.\n");
                    break;
            }
        } while (opcion != 3);

    } while (1);
    cerrarDispositivo(&tablaDispositivos[dispositivoSeleccionado]);

    return 0;
}
