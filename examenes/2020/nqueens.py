# Problema de N Queens resuelto con backtracking
# https://www.geeksforgeeks.org/n-queen-problem-backtracking-3/
def isSafe(tablero, fila, col, N):
    """
        Comprobar si una reina se puede colocar en la fila y columna
    """
    # Comprobacion horizontal, cogemos la misma fila de parametro
    for i in range(col):
        # Comprobamos si existe una reina
        if (tablero[fila][i] == 1):
            return False

    # Comprobacion vertical
    for i in range(fila):
        if (tablero[i][col] == 1):
            return False
        
    # Doble comprobacion diagonal
    # Comprobacion diagonal, descendente (superior izquierda a inferior derecha)
    for i, j in zip(range(fila,-1,-1), range(col,-1,-1)):
        if (tablero[i][j] == 1):
            return False
    # Comprobacion diagonal, descendente (inferior izquierda a superior derecha)
    for i, j in zip(range(fila,N,1), range(col,-1,-1)):
        if (tablero[i][j]==1):
            return False
        
    return True

def NQueensBack(tablero, col, N):
    """
        Funcion recursiva
        tablero: Matriz de NxN
        col: Columna actual, empezando por 0
        N: Tamanio del problema o NQueens
    """
    # Caso base, se han puesto todas las reinas, se retorna que es una solucion
    if (col >= N):
        return True

    # Considerando en la columna en la que estamos, vamos a intentar introducir todas las reinas, 
    # en las filas respectivas una por una
    for i in range(N):
        # Col se obtiene solo del subproblema, por lo que comprobamos si es seguro introducir una reina en la misma columna pero en distinta fil
        if isSafe(tablero, i, col,N):
            # Seguro, colocamos reina
            tablero[i][col] = 1

            # Hacemos llamada recursiva, desplazandonos a la columna de la derecha
            if (NQueensBack(tablero,col+1,N)):
                # Solucion
                return True

            # Si no lleva a una solucion, es decir, esta rama de columnas se pone a cero
            tablero[i][col] = 0
    
    # Si la Reina no puede ser puesta en cualquier fila een esta columna, se retorna Falso
    return False


def main():
    tablero = [
        [0,0,0,0],
        [0,0,0,0],
        [0,0,0,0],
        [0,0,0,0]
    ]
    col = 0
    N = 4

    if (NQueensBack(tablero, col, N)):
        for i in range(N):
            for j in range(N):
                print(tablero[i][j], end=" ")
            print("")
    else:
        print("No hay solucion")

if __name__ == "__main__":
    main()