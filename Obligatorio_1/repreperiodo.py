import matplotlib.pyplot as plt
from collections import defaultdict

# Función para leer el archivo y obtener las series de datos
def leer_datos(nombre_archivo):
    series = defaultdict(list)
    with open(nombre_archivo, 'r') as archivo:
        for linea in archivo:
            partes = linea.strip().split(', ')
            serie = int(partes[0])
            x = int(partes[1])
            y = float(partes[2])
            series[serie].append((x, y))
    return series

# Función para representar las series de datos en un gráfico
def graficar_series(series):
    for serie, datos in series.items():
        x_vals, y_vals = zip(*datos)
        plt.plot(x_vals, y_vals, label=f"Serie {serie}")
    plt.xlabel('Eje X')
    plt.ylabel('Eje Y')
    plt.title('Series de Datos')
    plt.legend()
    plt.show()

# Nombre del archivo de datos
nombre_archivo = 'periodo.txt'

# Leer los datos del archivo
series = leer_datos(nombre_archivo)

# Graficar las series
graficar_series(series)
