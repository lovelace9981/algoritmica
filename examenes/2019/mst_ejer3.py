# Implementacion del ejercicio 3 del examen de Junio de 2019

# ALGORITMO https://www.scaler.com/topics/prims-and-kruskal-algorithm/
# Se pide.
'''
La empresa X ha decidido instalar una red de fibra óptica para interconectar sus seis
centros de trabajo. El coste (positivo) del tendido de cable entre ellos aparece en la figura siguiente.
Especificad un algoritmo que sea capaz de encontrar la forma de interconectar todos los centros con
un coste mı́nimo, y aplicadlo para resolver el problema de la figura, describiendo el proceso paso a
paso.
'''

def printMST(parent, matrix):
    print(f"EDGES \t - \t WEIGHTS")
    for i in range(1, len(matrix)):
        print(i)
        print(f"{parent[i]} - {i} \t + \t V: {matrix[i][parent[i]]}")


# Funcion que busca de los no visitados cual es el que tiene el valor mas pequenio
# una vez obtenido el valor mas pequenio se construye el arbol a partir de ahi
def minVisitedKey(values, setMST):
    min = 10000000000
    min_index = -1
    for i in range(len(setMST)):
        if setMST[i] == False and values[i] < min:
            min = values[i]
            min_index = i

    return min_index

# Se usa el algoritmo de PRIM, ya que su enfoque en nodos, es el mejor. Al evitar tener que analizar los ciclos.
def primMST(matrix):
    # Tamanio del problema
    n = len(matrix)
    # minimum Spanning Tree marcador de los visitados
    setMST = [False] * n
    # Inicializamos las raices a -1
    parent = [100000000000] * n
    # Valor minimal
    values = [100000000000] * n


    # INICIO DEL PROBLEMA
    # Introducimos el 0 como inicio -1
    parent[0] = -1
    # inicializamos al principio y lo marcamos como visitado
    values[0] = 0
    # Bucle -- Iteramos sobre la matriz
    for i in range(n):
        # Indicamos que lo hemos visitado, por defecto primero se escoge el 0
        key = minVisitedKey(values, setMST)
        setMST[key] = True

        # Iteramos sobre los vertices de la matriz de adyacencia de i, buscamos el minimal
        for j in range(n):
            if matrix[key][j] != 0 and matrix[key][j] < values[j] and setMST[j] == False:
                parent[j] = key
                values[j] = matrix[key][j]

    printMST(parent, matrix)


def main():
    # Adjacency Matrix with weights positive
    matrix_adj = [
        [0,3,0,7,0,3],
        [3,0,4,8,0,6],
        [0,4,0,9,0,5],
        [0,0,0,8,0,6],
        [3,6,5,0,6,0]
    ]

    graph = [
        [ 0, 2, 0, 6, 0 ],
        [ 2, 0, 3, 8, 5 ],
        [ 0, 3, 0, 0, 7 ],
        [ 6, 8, 0, 0, 9 ],
        [ 0, 5, 7, 9, 0 ] 
    ]

    primMST(graph)

if __name__ == "__main__":
    main()