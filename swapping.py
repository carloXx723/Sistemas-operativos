import random
import time
from collections import deque

capacidadMemoria = 3
disco = []

def swapOut(memoria):
    procesoSacado = memoria.pop(0)
    print(f"Intercambiando proceso {procesoSacado} de memoria al disco.")
    disco.append(procesoSacado)

def agregarAMemoria(memoria, proceso):
    if len(memoria) < capacidadMemoria:
        memoria.append(proceso)
        print(f"Proceso {proceso} agregado a memoria.")
    else:
        swapOut(memoria)
        memoria.append(proceso)
        print(f"Proceso {proceso} agregado a memoria.")

def simularSwap():
    memoria = []
    procesos = ['P1', 'P2', 'P3', 'P4', 'P5', 'P6', 'P7']
    
    for i in range(10):
        procesoNuevo = random.choice(procesos)
        print(f"\nAgregando proceso {procesoNuevo}")
        
        agregarAMemoria(memoria, procesoNuevo)
        
        print(f"Estado de memoria: {memoria}")
        print(f"Estado del disco: {disco}")
        
        time.sleep(1)

simularSwap()
