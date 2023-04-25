# TODO
- [ ] Hacer clase de nodo
  - [X] Tendrá una lista de nodos adyacentes, es decir, las aristas que tiene.
  - [X] Una función para eliminar una arista (conexión con nodo adyacente).
  - [X] Función que devuelve el número de aristas incidentes (usada para la heurística)
  - [X] Función toString
- [ ] Hacer array de nodos (Grafo) en el main
- [ ] Lectura de un grafo desde un archivo
  - [ ] Especificar un formato de grafo en archivo de texto
- [ ] Hacer main, recibe como argumento el nombre de un archivo con un grafo y devuelve el camino de Euler.
  - [ ] Leer de fichero
  - [ ] Comprobar precondiciones y mostrarlo
  - [ ] Realizar algoritmo

# HEURÍSTICA
Como heurística tomamos el número de aristas incidentes que tiene el nodo, por eso se especifica la función para obtener el número de aristas que inciden en el nodo.
# PRECONDICIONES
- El grafo es conexo, es decir, todos los vértices están conectados
- Todos los vértices tienen un número de aristas par.

Éstas precondiciones se da por hecho que ya se cumplen al dar un input de un grafo, pero para hacer el programa más completo se sugiere comprobarlo antes de ejecutar el algoritmo y mostrar en consola que está todo correcto.

# FORMATO DE ARCHIVO .GRAPH
