# Dado un vector de ganancias/perdidas de longitud N, se desea encontrar el subvector sohbre el cual se consegue el beneficio total maximo
# https://apuntes.de/golang-estructuras-de-datos-y-algoritmos/arreglos-encontrar-la-maxima-suma-de-una-submatriz-consecutiva/#gsc.tab=0
def kadane(v):
    mejor = []
    suma_mejor = 0

    actual = []
    suma_actual = 0

    for i in range(len(v)):
        # Registramos mientras no sea negativo
        # SUBVECTOR al encontrar un numero negativo
        if (v[i] < 0):
            # Hay un registro mejor, lo comprobamos
            if (suma_actual > suma_mejor):
                mejor = actual
                suma_mejor = suma_actual
            # Reiniciamos el subvector
            suma_actual = 0
            actual = []
            
        else:
            # No es negativo
            actual.append(v[i])
            suma_actual = suma_actual + v[i]

    # Comprueba la última suma actual después del bucle
    if (suma_actual > suma_mejor):
        mejor = actual
        suma_mejor = suma_actual

    return mejor

def main():
    v = [29,-7,14,21,30,-44,1,7,-39,23,-20,-36,-41,27,-34,7,48,35,-46,-16,32,18,5,-33,27,28,-22,1,-20,-42]

    mejor = kadane(v)

    for i in mejor:
        print(i, end=" ")
    print("---")


if __name__ == "__main__":
    main()