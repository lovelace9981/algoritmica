# Ejercicio 5: Monedas, dar numero minimal de monedas posible 
def sumMonedasUsadas(v, VU):
    sum = 0
    for i in range(len(VU)):
        sum = sum + (VU[i] * v[i])

    return sum

def devolverDP(v,c,M,DP):
    # COPIAMOS C, monedas disponibles
    copy_C = []

    for i in range(len(c)):
        copy_C.append(c[i])

    # Hacemos matriz de listas de monedas usadas.
    monedas_usadas = [[[0 for _ in range(len(c))] for _ in range(M+1)] for _ in range(len(c))]

    for i in range(len(v)):
        for j in range(M+1): # Para llegar a 8
            if (i == 0):
                if ((sumMonedasUsadas(v, monedas_usadas[i][j-1]) + v[i]) <= j and monedas_usadas[i][j-1][i] + 1 <= c[i]):
                    DP[i][j] =  DP[i][j-v[i]] + 1
                    monedas_usadas[i][j] = monedas_usadas[i][j-v[i]].copy()
                    monedas_usadas[i][j][i] += 1
                else:
                    DP[i][j] = DP[i][j-1]
                    monedas_usadas[i][j] = monedas_usadas[i][j-1].copy()
            elif (sumMonedasUsadas(v, monedas_usadas[i][j-1]) + v[i] <= j and monedas_usadas[i][j][i] + 1 <= c[i]): # Se puede introducir monedas, de la fila actual
                print(f"Entra en {i} {j}")
                # Calculo introduciendo una moneda mas, calculamos el minimal
                DP[i][j] = min(DP[i-1][j], DP[i][j-v[i]] + 1)
                
                if (DP[i-1][j] < DP[i][j-v[i]] + 1):
                    # Simplemente copiamos las monedas de la fila anterior, al tener un minimal mejor
                    monedas_usadas[i][j] = monedas_usadas[i-1][j].copy()
                else:
                    # Cogemos las monedas de la fila actual con la recurrencia y le aniadimos una mas
                    monedas_usadas[i][j] = monedas_usadas[i][j-v[i]].copy()
                    monedas_usadas[i][j][i] += 1
            else:
                print(f"Col anterior {i} {j}")
                DP[i][j] = DP[i][j-1]
                monedas_usadas[i][j] = monedas_usadas[i][j-1].copy()
                    
    for i in range(len(v)):
        for j in range(M+1):
            print(DP[i][j], end=" ")
        print("")
        
def main():
    # monedas
    v = [2,4,6]
    # cantidad de monetas
    c = [3,1,2]
    # Cantidad a devolver 
    M = 8
    # Matriz de programacion dinamica
    DP = [[0 for _ in range(M+1)] for _ in range(len(v))]
    # CALL
    devolverDP(v,c,M,DP)

if __name__ == "__main__":
    main()