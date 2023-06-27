# CUENTA POR M EUROS
# CANTIDAD ILIMITADA DE MONEDAS DE N TIPOS
# C[i] VALOR DE LA MONEDA
# QUEREMOS PAGAR O LA CANTIDAD EXACTA O LA MINIMA CANTIDAD MAYOR POSIBLE DE M
# https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
# https://www.geeksforgeeks.org/coin-change-dp-7/

def pagoMinimal(M, c):
    # AJUSTAMOS M con la moneda maxima, poruqe podemos pagar de mas
    M_AJUSTADO = M + min(c)

    # EN DP se considera + 1 porque cuando vale 0 es 0 no se introduce ningun elemento
    # Se pone a infinito ya que estamos minimizando
    DP = [[float('inf') for _ in range(M_AJUSTADO+1)] for _ in range(len(c)+1)]
    
    # INICIO DP
    for i in range(len(c)+1):
        for w in range(M_AJUSTADO+1):
            # CASOS DONDE NO SE METE NINGUN VALOR
            if i == 0 or w == 0:
                DP[i][w] = 0
            else: # CASO EN EL QUE UNA POSIBLE MONEDA SE PUEDE METER
                # Combinacion de una moneda actual, con la fila anterior
                anterior_combinado_actual = DP[i-1][w - c[i-1]] + c[i-1]
                if (anterior_combinado_actual > w):
                    anterior_combinado_actual = DP[i][w-1]

                # Fila anterior del mismo tipo
                fila_anterior = DP[i-1][w]
                if (fila_anterior > w):
                    fila_anterior = DP[i][w-1]

                # Combinacion todas las monedas del mismo tipo
                actual = DP[i][w-1] + c[i-1]

                if (actual > w):
                    actual = DP[i][w-1]


                # SI el pago es mayor que M minimizamos, si el pago es menor maximizamos
                if w > M:
                    if (M-anterior_combinado_actual < M-fila_anterior):
                        if(M-anterior_combinado_actual < M-actual):
                            DP[i][w] = anterior_combinado_actual
                        else:
                            DP[i][w] = actual
                    else:
                        if(M-fila_anterior < M-actual):
                            DP[i][w] = fila_anterior
                        else:
                            DP[i][w] = actual
                else:
                    DP[i][w] = max(anterior_combinado_actual, fila_anterior, actual)
        
    for i in range(M_AJUSTADO+1):
        print(i, end="\t")
    print("")

    for i in range(len((c))+1):
        for j in range(M_AJUSTADO+1):
            print(f"{DP[i][j]}", end="\t")
        print(f"\n")
    


def pagoMinimal2(M, c):
    max_val = M + max(c)
    DP = [0] + [float('inf')] * max_val

    for i in range(len(c)):
        for j in range(c[i], max_val + 1):
            DP[j] = min(DP[j], DP[j - c[i]] + 1)
    
    return min(DP[M:])

def main():
    # Pago adeudado
    M = 11
    # MONEDAS
    c = [5,7,13]
    
    pagoMinimal(M,c)

if __name__ == "__main__":
    main()