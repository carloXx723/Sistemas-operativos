#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo {
    int prioridad;         
    char nombre[100];        
    struct Nodo* siguiente; 
} Nodo;

typedef struct {
    Nodo* frente;
} ColaPrioridad;

Nodo* crearNodo(int prioridad, char* nombre) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->prioridad = prioridad;
    strcpy(nuevoNodo->nombre, nombre);
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

void inicializarCola(ColaPrioridad* cola) {
    cola->frente = NULL;
}

void insertar(ColaPrioridad* cola, int prioridad, char* nombre) {
    Nodo* nuevoNodo = crearNodo(prioridad, nombre);

    if (cola->frente == NULL || prioridad < cola->frente->prioridad) {
        nuevoNodo->siguiente = cola->frente;
        cola->frente = nuevoNodo;
    } else {
        Nodo* actual = cola->frente;
        while (actual->siguiente != NULL && actual->siguiente->prioridad <= prioridad) {
            actual = actual->siguiente;
        }
        nuevoNodo->siguiente = actual->siguiente;
        actual->siguiente = nuevoNodo;
    }
    printf("'%s' insertado con prioridad %d \n",  nombre,prioridad);
}

void eliminar(ColaPrioridad* cola) {

    Nodo* temp = cola->frente;
    printf("'%s' eliminado.\n", temp->nombre);
    cola->frente = cola->frente->siguiente;
    free(temp);
}

void mostrar(ColaPrioridad* cola) {
    if (cola->frente == NULL) {
        printf("La cola está vacía.\n");
        return;
    }
    Nodo* actual = cola->frente;
    printf("Cola de prioridad: \n");
    while (actual != NULL) {
        printf("[%s, Prioridad: %d] -> ",actual->nombre,actual->prioridad);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}

int main() {
    ColaPrioridad cola;
    inicializarCola(&cola);

    insertar(&cola, 3, "p1");
    insertar(&cola, 1, "p2");
    insertar(&cola, 2, "p3");
    insertar(&cola, 4, "p4");

    mostrar(&cola);

    eliminar(&cola);
    mostrar(&cola);

    eliminar(&cola);
    mostrar(&cola);

    eliminar(&cola);
    mostrar(&cola);

    eliminar(&cola);
    mostrar(&cola);

    return 0;
}
