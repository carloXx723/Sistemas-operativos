#include <stdio.h>
#include <stdlib.h>

#define CAPACIDAD_CACHE 4  

typedef struct Nodo {
    int pagina;              
    struct Nodo* prev;      
    struct Nodo* next;      
} Nodo;


typedef struct CacheLRU {
    int tamaño;              
    Nodo* cabeza;            
    Nodo* cola;               
} CacheLRU;

Nodo* crearNodo(int pagina) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->pagina = pagina;
    nuevo->prev = nuevo->next = NULL;
    return nuevo;
}

CacheLRU* inicializarCacheLRU() {
    CacheLRU* cache = (CacheLRU*)malloc(sizeof(CacheLRU));
    cache->tamaño = 0;
    cache->cabeza = cache->cola = NULL;
    return cache;
}

void moverACabeza(CacheLRU* cache, Nodo* nodo) {
    if (cache->cabeza == nodo) return;

    if (nodo->prev) nodo->prev->next = nodo->next;
    if (nodo->next) nodo->next->prev = nodo->prev;

    if (cache->cola == nodo) cache->cola = nodo->prev;

    nodo->next = cache->cabeza;
    nodo->prev = NULL;
    if (cache->cabeza) cache->cabeza->prev = nodo;
    cache->cabeza = nodo;

    if (cache->tamaño == 1) cache->cola = nodo;
}

void agregarPagina(CacheLRU* cache, int pagina) {
    Nodo* nuevo = crearNodo(pagina);

    if (cache->tamaño == 0) {
        cache->cabeza = cache->cola = nuevo;
    }
    else {
        if (cache->tamaño < CAPACIDAD_CACHE) {
            nuevo->next = cache->cabeza;
            cache->cabeza->prev = nuevo;
            cache->cabeza = nuevo;
        }
        else {
            Nodo* temp = cache->cola;
            cache->cola = temp->prev;
            if (cache->cola) cache->cola->next = NULL;
            printf("Página %d eliminada de la caché.\n", temp->pagina); // Mensaje de eliminación
            free(temp);

            nuevo->next = cache->cabeza;
            cache->cabeza->prev = nuevo;
            cache->cabeza = nuevo;
        }
    }

    if (cache->tamaño < CAPACIDAD_CACHE) cache->tamaño++;
}

void accederPagina(CacheLRU* cache, int pagina) {
    Nodo* temp = cache->cabeza;

    while (temp) {
        if (temp->pagina == pagina) {
            moverACabeza(cache, temp);
            printf("Página %d encontrada y movida a la cabeza.\n", pagina);
            return;
        }
        temp = temp->next;
    }

    printf("Página %d no encontrada, agregando a la caché.\n", pagina);
    agregarPagina(cache, pagina);
}

void mostrarCache(CacheLRU* cache) {
    Nodo* temp = cache->cabeza;
    printf("Contenido de la caché: ");
    while (temp) {
        printf("%d ", temp->pagina);
        temp = temp->next;
    }
    printf("\n");
}


int main() {
    CacheLRU* cache = inicializarCacheLRU();


    accederPagina(cache, 1);
    mostrarCache(cache);
    accederPagina(cache, 2);
    mostrarCache(cache);
    accederPagina(cache, 3);
    mostrarCache(cache);
    accederPagina(cache, 4);
    mostrarCache(cache);
    accederPagina(cache, 1);
    mostrarCache(cache);
    accederPagina(cache, 2);
    mostrarCache(cache);
    accederPagina(cache, 3);
    mostrarCache(cache);
    accederPagina(cache, 1);  
    mostrarCache(cache);
    accederPagina(cache, 5);  
    mostrarCache(cache);

    return 0;
}
