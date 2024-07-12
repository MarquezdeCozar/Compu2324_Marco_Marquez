import matplotlib.pyplot as plt
from collections import defaultdict

# Función para leer el archivo y obtener las series de datos
def leer_datos(nombre_archivo):
    x_vals = []
    series = defaultdict(list)
    with open(nombre_archivo, 'r') as archivo:
        for linea in archivo:
            partes = linea.strip().split(', ')
            x = int(partes[0])
            y = float(partes[1])
            z = float(partes[2])
            a = float(partes[3])
            x_vals.append(x)
            series[1].append(y)
            series[2].append(z)
            series[3].append(a)
    return x_vals, series

# Función para representar las series de datos en un gráfico
def graficar_series(x_vals, series, etiquetas):
    for serie, y_vals in series.items():
        plt.plot(x_vals, y_vals, label=etiquetas[serie])
    plt.axhline(0, color='black', linewidth=0.5)  # Dibuja el eje y = 0
    plt.xlabel('Pasos Montecarlo')
    plt.ylabel('Magnetizacion Promedia')
    plt.title('T = 2.2269, n*n = 1000')
    plt.legend()
    plt.show()

# Nombre del archivo de datos
nombre_archivo = 'magnetizacion.txt'

# Etiquetas para las series
etiquetas = {
    1: "Mitad superior",
    2: "Mitad inferior",
    3: "Magnetización total"
}

# Leer los datos del archivo
x_vals, series = leer_datos(nombre_archivo)

# Graficar las series
graficar_series(x_vals, series, etiquetas)
