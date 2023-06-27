# https://www.geeksforgeeks.org/breadth-first-traversal-bfs-on-a-2d-array/
# https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
# https://www.hackerearth.com/practice/algorithms/graphs/breadth-first-search/tutorial/

import queue

def valid(lab, visited, fil, col, size_f, size_c):
    if(((0 <= fil < size_f) and (0 <= col < size_c)) and (lab[fil][col] == 't' or lab[fil][col] == 's')):
        if(not visited[fil][col]):
            return True
    
    return False

def solutioN(lab, fil, col):
    if(lab[fil][col] == 's'):
        return True

def bfsMatrix(laberinto, visited, prev, fil_init, col_init, size_f, size_c):
    """
    laberinto: Matriz del laberinto
    visited: Matriz de elementos visitados
    prev: Matriz de celdas, que almacena las coordenadas de la celda padre
    fil_init: Punto de partida fila
    col_init: Punto de partida columna
    size_f: Tamanio de las filas
    size_c: Tamanio de las columnas

    La lista [(-1, 0), (1, 0), (0, -1), (0, 1)] representa los cambios de posición en la fila y la columna que se deben hacer para visitar cada una de las celdas vecinas (arriba, abajo, izquierda, derecha) de una celda dada. En otras palabras, representa los posibles movimientos desde una celda en la cuadrícula a sus celdas vecinas en las direcciones Norte, Sur, Este y Oeste, respectivamente.

    Cuando haces i = f + df y j = c + dc para cada uno de estos pares (df, dc), estás visitando cada una de las celdas vecinas de la celda (f, c).

    Específicamente:

    (-1, 0) representa moverse una celda hacia arriba (Norte).
    (1, 0) representa moverse una celda hacia abajo (Sur).
    (0, -1) representa moverse una celda a la izquierda (Oeste).
    (0, 1) representa moverse una celda a la derecha (Este).

    Esto asume que las filas se cuentan de arriba a abajo (por lo que subir es restar 1) y las columnas de izquierda a derecha (por lo que moverse a la derecha es sumar 1).
    """

    dirVectorRow = [-1,0,1,0]
    dirVectorCol = [0,1,0,-1]
    # Introducimos el primero que es fil_init y col_init
    pending = queue.Queue()

    # comprobamos que es valido antes que nada y lo marcamos como true
    if (valid(laberinto, visited, fil_init, col_init, size_f, size_c)):
        pending.put((fil_init, col_init))
        visited[fil_init][col_init] = True
        
        if(solutioN(laberinto, fil_init, col_init)):
            print("Solution found at: ", new_f, new_c)
            return

    # Mientras queden puntos por analizar
    while(not pending.empty()):
        # Quitamos de los pendientes a analizar
        casilla = pending.get()
        # Obtenemos las coordenadas matriciales
        f,c = casilla

        for i in range(len(dirVectorCol)):
            new_f = f + dirVectorRow[i]
            new_c = c + dirVectorCol[i]

            if (valid(laberinto, visited, new_f, new_c, size_f, size_c)):
                # Introducimos en la cola el paso
                pending.put((new_f,new_c))
                visited[new_f][new_c] = True
                # Matriz de previos, almacena la celda padre desde donde hemos venido
                prev[new_f][new_c] = (f,c)

                if(solutioN(laberinto, new_f, new_c)):
                    print("Solution found at: ", new_f, new_c)
                    return [new_f, new_c]
        
def main():
    laberinto = [
        ["t","t","n","s"],
        ["n","t","t","t"],
        ["t","t","n","t"],
        ["n","n","n","n"]
    ]

    visited = [[False for _ in range(len(laberinto[0]))] for _ in range(len(laberinto))]
    prev = [[None for _ in range(len(laberinto[0]))] for _ in range(len(laberinto))]
    
    result = bfsMatrix(laberinto, visited, prev, 0, 0, len(laberinto), len(laberinto[0]))
    
    # Reconstruimos el camino
    path = []
    target = result
    while target is not None:
        path.append(target)
        target = prev[target[0]][target[1]]
    path.reverse()
    print("Path: ", path)

if __name__ == "__main__":
    main()