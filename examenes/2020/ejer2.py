# https://www.geeksforgeeks.org/subset-sum-problem/ 

def Multiplorio(C):
    mul = 1
    for i in C:
        mul = mul * i
    return mul

def backtrackMultiplorio(N, C, SC, actual, MEJORSC):
    """
    N Es el numero maximo que no debemos pasarnos
    C Es el conjunto de numeros que debemos multiplicar
    SC es el subcojunto actual
    actual es el numero siguiente al que debemos elegir
    MEJORSC, Subconjunto que indica el mejor caso
    """
    # Caso base, comprobamos que los numeros que se vayan a introducir, no sobrepasen los disponibles
    # Backtrack, cogemos cada caso de 
    # Mientras sea una solución hace llamadas recursivas hasta agotar el conjunto o que no se cumpla alguna condición, lo que ocurra antes
    for i in range(actual, len(C)):
        # Introducimos el numero al subconjunto SC
        SC.append(C[i])
        # Verificamos si el nuevo producto excede N
        if (Multiplorio(SC) <= N):
            # Si es así, actualizamos el mejor subconjunto si el nuevo producto es mejor
            if Multiplorio(SC) > Multiplorio(MEJORSC):
                MEJORSC.clear()
                MEJORSC.extend(SC)
            # Generamos un backtrack nuevo, buscamos por la rama
            backtrackMultiplorio(N, C, SC, i+1, MEJORSC)
        # Quitamos el numero del SC y seguimos intentando
        SC.pop()
    
    # Se han probado todos

def main():
    C = [4,4,12,3]
    N = 37
    SC = []
    MEJORSC = []
    actual = 0

    backtrackMultiplorio(N, C, SC, actual, MEJORSC)
    for i in range(len(MEJORSC)):
        print(MEJORSC[i], end=" ")
    print(f"\n MUL: {Multiplorio(MEJORSC)}")
    
if __name__ == "__main__":
    main()