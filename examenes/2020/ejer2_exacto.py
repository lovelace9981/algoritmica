

def Multiplorio(C):
    mul = 1
    for i in C:
        mul = mul * i
    return mul

def backtrackMultiplorio(N, C, SC, actual):
    """
    N Es el numero maximo que no debemos pasarnos
    C Es el conjunto de numeros que debemos multiplicar
    SC es el subcojunto actual
    actual es el numero siguiente al que debemos elegir
    """
    # Caso base, comprobamos que los numeros que se vayan a introducir, no sobrepasen los disponibles
    if (Multiplorio(SC) > N):
        return False
    if (Multiplorio(SC) == N):
        return True

    # Backtrack, cogemos cada caso de 
    for i in range(actual, len(C)):
        # Introducimos el numero al subconjunto SC
        SC.append(C[i])
        # Generamos un backtrack nuevo, buscamos por la rama
        if (backtrackMultiplorio(N,C,SC,i+1)):
            # Caso en el que encontramos solucion
            return True
        else:
            # Quitamos el numero del SC y seguimos intentando
            SC.pop()
    
    # Se han probado todos
    return False

def main():
    C = [4,4,12,3]
    N = 36 # EXACTO
    SC = []
    actual = 0
    
    backtrackMultiplorio(N, C, SC, actual)
    for i in range(len(SC)):
        print(SC[i], end=" ")
    print(f"\n MUL: {Multiplorio(SC)}")
    
if __name__ == "__main__":
    main()