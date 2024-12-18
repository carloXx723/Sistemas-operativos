#include <stdio.h>
#include <stdlib.h>

#define MAX_CILINDROS 200

int comparar(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void SCAN(int solicitudes[], int numSolicitudes, int cabeza, int direccion) {
    qsort(solicitudes, numSolicitudes, sizeof(int), comparar);
    
    int totalMovimientos = 0;
    int izquierda = 0, derecha = 0;
    int secuenciaMovimiento[numSolicitudes + 2];
    int indice = 0;

    for (int i = 0; i < numSolicitudes; i++) {
        if (solicitudes[i] >= cabeza) {
            derecha = i;
            izquierda = i - 1;
            break;
        }
    }

    if (direccion == 1) {
        for (int i = derecha; i < numSolicitudes; i++) {
            secuenciaMovimiento[indice++] = solicitudes[i];
            totalMovimientos += abs(solicitudes[i] - cabeza);
            cabeza = solicitudes[i];
        }
        totalMovimientos += abs(MAX_CILINDROS - 1 - cabeza);
        cabeza = MAX_CILINDROS - 1;
        for (int i = izquierda; i >= 0; i--) {
            secuenciaMovimiento[indice++] = solicitudes[i];
            totalMovimientos += abs(solicitudes[i] - cabeza);
            cabeza = solicitudes[i];
        }
    } else {
        for (int i = izquierda; i >= 0; i--) {
            secuenciaMovimiento[indice++] = solicitudes[i];
            totalMovimientos += abs(solicitudes[i] - cabeza);
            cabeza = solicitudes[i];
        }
        totalMovimientos += abs(0 - cabeza);
        cabeza = 0;
        for (int i = derecha; i < numSolicitudes; i++) {
            secuenciaMovimiento[indice++] = solicitudes[i];
            totalMovimientos += abs(solicitudes[i] - cabeza);
            cabeza = solicitudes[i];
        }
    }

    printf("\nSecuencia de acceso a los cilindros:\n");
    for (int i = 0; i < numSolicitudes + 1; i++) {
        printf("%d ", secuenciaMovimiento[i]);
    }
    printf("\nTotal de movimientos del cabezal: %d\n", totalMovimientos);
}

int main() {
    int solicitudes[] = {55, 58, 39, 18, 90, 160, 150, 38};
    int numSolicitudes = sizeof(solicitudes) / sizeof(solicitudes[0]);
    int cabeza = 50;
    int direccion = 1;

    printf("Solicitudes de acceso a cilindros: ");
    for (int i = 0; i < numSolicitudes; i++) {
        printf("%d ", solicitudes[i]);
    }
    printf("\n");

    SCAN(solicitudes, numSolicitudes, cabeza, direccion);

    return 0;
}
