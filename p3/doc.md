# TODO
- [ ] Hacer clase de nodo
  - [ ] Tendrá una lista de nodos adyacentes, es decir, las aristas que tiene.
  - [ ] Una función para eliminar una arista (conexión con nodo adyacente).
  - [ ] Función que devuelve el número de aristas incidentes (usada para la heurística)
  - [ ] Función toString
- [ ] Hacer array de nodos (Grafo) en el main
- [ ] Lectura de un grafo desde un archivo
  - [ ] Especificar un formato de grafo en archivo de texto
- [ ] Hacer main, recibe como argumento el nombre de un archivo con un grafo y devuelve el camino de Euler.

# PRECONDICIONES
- El grafo es conexo, es decir, todos los vértices están conectados
- Todos los vértices tienen un número de aristas par.

Éstas precondiciones se da por hecho que ya se cumplen al dar un input de un grafo, pero para hacer el programa más completo se sugiere comprobarlo antes de ejecutar el algoritmo y mostrar en consola que está todo correcto.