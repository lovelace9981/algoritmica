# Disenio de un algoritmo que pueda expresare o no ocmo producto de 3 numeros naturales consecutivos
# N = Y * (Y+1) * (Y+2)
def puede_ser_producto(N):
    # Calcula la cubo raíz entera de N
    Y = int(round(N ** (1. / 3)))

    # Verifica si N es producto de tres números naturales consecutivos
    return Y * (Y + 1) * (Y + 2) == N or (Y - 1) * Y * (Y + 1) == N

N = 3  # Ejemplo de número que es producto de tres números consecutivos
print(puede_ser_producto(N))
