#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void manejadorInterrupcion(int numeroSenal) {
    printf("\nSeñal recibida: %d\n", numeroSenal);
    if (numeroSenal == SIGINT) {
        printf("Finalzando proceso\n");
        exit(0);
    } else if (numeroSenal == SIGUSR1) {
        printf("Proceso iniciado por el usuario.\n");
    } else if (numeroSenal == SIGALRM) {
        printf("Se recibió un temporizador (alarma).\n");
    }
}

void configurarManejadores() {
    signal(SIGINT, manejadorInterrupcion);  // Ctrl+C
    signal(SIGUSR1, manejadorInterrupcion); //  kill -SIGUSR1 <PID>
    signal(SIGALRM, manejadorInterrupcion); // senal automatica
}

void ejecutarTareas() {
    while (1) {
        printf("Ejecutando proceso principal\n");
        sleep(2); 
        printf("Esperando interrupcion\n");

        alarm(3); 
    }
}

int main() {
    configurarManejadores();
    ejecutarTareas();
    return 0;
}
