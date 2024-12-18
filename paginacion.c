#include <stdio.h>
#include <stdlib.h>

#define PAGES 16        // Número total de páginas en la tabla
#define FRAMES 8        // Número total de marcos en la memoria física
#define ACCESOS 20      // Número de accesos aleatorios a páginas

// Estructura para la tabla de páginas
typedef struct {
    int numero_de_marco;  // Marco asignado a la página
    int bit_validez;      // Bit de validez (1 si está en memoria, 0 si no)
} EntradaTablaPagina;

// Función para generar accesos aleatorios a páginas
int accesoAleatorio(int max) {
    return rand() % max;
}

int main() {
    // Inicializar la tabla de páginas (con 16 páginas)
    EntradaTablaPagina tabla_paginas[PAGES];
    for (int i = 0; i < PAGES; i++) {
        tabla_paginas[i].numero_de_marco = -1; // Inicialmente, no asignado
        tabla_paginas[i].bit_validez = 0;     // Inicialmente, inválido
    }

    // Inicializar memoria física (con 8 marcos)
    int memoria_fisica[FRAMES] = {0};
    int marco_actual = 0;

    // Simular accesos a páginas
    for (int i = 0; i < ACCESOS; i++) {
        int pagina = accesoAleatorio(PAGES);  // Seleccionar una página aleatoria
        printf("Acceso a la página %d\n", pagina);

        // Verificar si la página ya está en memoria
        if (tabla_paginas[pagina].bit_validez == 1) {
            printf("La página %d está en el marco %d\n", pagina, tabla_paginas[pagina].numero_de_marco);
        } else {
            printf("Fallo de página para la página %d\n", pagina);

            // Asignar un marco de memoria física a la página
            if (marco_actual < FRAMES) {
                tabla_paginas[pagina].numero_de_marco = marco_actual;
                tabla_paginas[pagina].bit_validez = 1;  // Página cargada en memoria
                memoria_fisica[marco_actual] = pagina;  // La página se asigna al marco
                printf("Asignando página %d al marco %d\n", pagina, marco_actual);
                marco_actual++;  // Pasamos al siguiente marco
            } else {
                printf("No hay marcos disponibles. Reemplazo de página no implementado en este ejemplo.\n");
            }
        }
    }

    return 0;
}
