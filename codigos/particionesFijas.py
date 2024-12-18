class MemoriaFija:
    def __init__(self, particiones):
        self.particiones = [{"tamaño": tamaño, "proceso": None} for tamaño in particiones]

    def mostrarEstado(self):
        print("\nEstado de la Memoria:")
        for i, particion in enumerate(self.particiones):
            estado = f"Proceso {particion['proceso']}" if particion['proceso'] else "Libre"
            print(f"Partición {i + 1} (Tamaño: {particion['tamaño']} MB): {estado}")
        print("")

    def asignarProceso(self, idProceso, tamañoProceso, particionSeleccionada):
        if particionSeleccionada < 1 or particionSeleccionada > len(self.particiones):
            print("Error: Partición seleccionada no es válida.")
            return

        particion = self.particiones[particionSeleccionada - 1]

        if particion["proceso"] is None and particion["tamaño"] >= tamañoProceso:
            particion["proceso"] = idProceso
            print(f"Proceso {idProceso} asignado a la Partición {particionSeleccionada}")
        else:
            print(f"No se pudo asignar el Proceso {idProceso} a la Partición {particionSeleccionada}.")
            print(f"Partición ocupada o tamaño insuficiente.")
        
        self.mostrarEstado()

    def liberarProceso(self, idProceso):
        for i, particion in enumerate(self.particiones):
            if particion["proceso"] == idProceso:
                particion["proceso"] = None
                print(f"Proceso {idProceso} liberado de la Partición {i + 1}")
                self.mostrarEstado()
                return
        print(f"No se encontró el Proceso {idProceso} en ninguna partición.")
        self.mostrarEstado()


def menu():
    print("1. Asignar proceso")
    print("2. Liberar proceso")
    print("3. Salir")


def main():
    particiones = [100, 100, 100, 100, 100]  
    memoria = MemoriaFija(particiones)

    memoria.mostrarEstado()

    while True:
        menu()
        opcion = input("Selecciona una opción: ")

        if opcion == "1":
            idProceso = input("Ingresa el ID del proceso: ")
            tamañoProceso = input("Ingresa el tamaño del proceso: ")
            tamañoProceso = int(tamañoProceso)

            particionSeleccionada = int(input(f"Selecciona la partición a la que asignar el proceso : "))
            memoria.asignarProceso(idProceso, tamañoProceso, particionSeleccionada)

        elif opcion == "2":
            idProceso = input("Ingresa el ID del proceso a liberar: ")
            memoria.liberarProceso(idProceso)

        elif opcion == "3":
            print("Saliendo del programa...")
            break

        else:
            print("Opción inválida. Inténtalo de nuevo.")
            memoria.mostrarEstado()


if __name__ == "__main__":
    main()
