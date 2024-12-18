#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Función que manejará las interrupciones (señales)
void manejador_interrupcion(int signal_number) {
    printf("\n[Interrupción] Señal recibida: %d\n", signal_number);
    if (signal_number == SIGINT) {
        printf("[Interrupción] Finalizando programa de manera segura...\n");
        exit(0); // Salir del programa
    } else if (signal_number == SIGUSR1) {
        printf("[Interrupción] Tarea especial activada por el usuario.\n");
    } else if (signal_number == SIGALRM) {
        printf("[Interrupción] Se recibió un temporizador (alarma).\n");
    }
}

// Configurar los manejadores de señales
void configurar_manejadores() {
    signal(SIGINT, manejador_interrupcion);  // Ctrl+C
    signal(SIGUSR1, manejador_interrupcion); // Señal del usuario
    signal(SIGALRM, manejador_interrupcion); // Alarma de temporizador
}

// Función que simula la ejecución de tareas
void ejecutar_tareas() {
    printf("Iniciando simulación de tareas...\n");
    while (1) {
        printf("[Simulación] Ejecutando tarea principal...\n");
        sleep(2); // Simula el tiempo que toma una tarea
        printf("[Simulación] Esperando por interrupciones o eventos...\n");

        // Simular condiciones especiales para enviar señales manualmente
        // Por ejemplo, programar una alarma
        alarm(5); // Activar alarma en 5 segundos
    }
}

int main() {
    configurar_manejadores();
    ejecutar_tareas();
    return 0;
}