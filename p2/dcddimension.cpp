// #include "dcddimension.hpp"

// set<vector<T>> DCDDIMENSION<class T>::no_dominados_recursive(set<vector<T>> entrada, int coordenada)
// {
//     // Calculamos la media de la coordenada
//     double media = 0;
//     for (auto const &punto : entrada)
//         media += punto[coordenada];

//     media /= entrada.size();

//     // Dividimos el conjunto de puntos en dos conjuntos
//     set<vector<T>> conjunto1, conjunto2;
//     for (auto const &punto : entrada)
//     {
//         if (punto[coordenada] <= media)
//             conjunto1.insert(punto);
//         else
//             conjunto2.insert(punto);
//     }

//     // Llamamos a la función recursiva para cada conjunto con una coordenada distinta
//     if (conjunto1.size() != 1)
//         conjunto1 = no_dominados_recursive(conjunto1, (coordenada + 1) % K_DIMENSION);
//     if (conjunto2.size() != 1)
//         conjunto2 = no_dominados_recursive(conjunto2, (coordenada + 1) % K_DIMENSION);

//     // Combinamos los conjuntos añadiendo solo no dominados

//     set<vector<T>> resultado;
//     resultado = combinar(conjunto1, conjunto2);

//     // Devolvemos la lista resultante
//     return resultado;
// }

// bool DCDDIMENSION<class T>::primera_condicion(const vector<T> i, const vector<T> &j)
// {
//     for (int k = 0; k < K_DIMENSION; ++k)
//     {
//         if (i[k] < j[k])
//         {
//             return false;
//         }
//     }
//     // Es >=
//     return true;
// }

// bool DCDDIMENSION<class T>::segunda_condicion(const vector<T> i, const vector<T> &j)
// {
//     for (int k = 0; k < K_DIMENSION; ++k)
//     {
//         if (i[k] > j[k])
//         {
//             return true;
//         }
//     }
//     return false;
// }

// bool DCDDIMENSION<class T>::domina(const vector<T> &i, const vector<T> &j)
// {
//     return primera_condicion(i, j) && segunda_condicion(i, j);
// }

// set<vector<T>> DCDDIMENSION<class T>::combinar(set<vector<T>> conjunto1, set<vector<T>> conjunto2)
// {
//     set<vector<T>> resultado;
//     bool no_dominado = false;

//     // Metemos en resultado el conjunto 1
//     for (auto const &punto : conjunto1)
//         resultado.insert(punto);

//     // Comparamos todos los de conjunto2 con los de el resultado
//     for (auto const &punto : conjunto2)
//     {
//         no_dominado = true;

//         set<vector<T>>::iterator it = resultado.begin();
//         while (it != resultado.end())
//         {
//             if (domina(punto, *it))
//             {
//                 // El punto domina al de resultado, lo borramos y continuamos para comprobar si domina a otro o es dominado
//                 it = resultado.erase(it);
//             }
//             else if (domina(*it, punto))
//             {
//                 // El punto de resultado domina al de conjunto2, no lo añadimos y salimos del bucle
//                 no_dominado = false;
//                 break;
//             }
//             else
//             {
//                 ++it;
//             }
//         }
//     }

//     return resultado;
// }

// void DCDDIMENSION<class T>::puntos_no_dominados()
// {
//     no_dominados.clear();
//     no_dominados = no_dominados_recursive(componentes, 0);
// }

// void DCDDIMENSION<class T>::print_problem()
// {
//     if (no_dominados.size() == 0)
//     {
//         cerr << "No se ha ejecutado el método gen_non_dominated " << endl;
//     }
//     else
//     {
//         cout << "All problem: " << endl;
//         for (auto const &punto : componentes)
//         {
//             cout << "Componente: "
//                  << " ";
//             for (int j = 0; j < K_DIMENSION; j++)
//             {
//                 cout << " " << punto[j] << " ";
//             }
//             cout << endl;
//         }

//         cout << "No dominados: " << endl;
//         for (auto const &punto : no_dominados)
//         {
//             cout << "Componente: "
//                  << " ";
//             for (int j = 0; j < K_DIMENSION; j++)
//             {
//                 cout << " " << punto[j] << " ";
//             }
//             cout << endl;
//         }
//     }
// }