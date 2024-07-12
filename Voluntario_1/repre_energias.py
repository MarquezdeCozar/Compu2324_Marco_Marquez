import matplotlib.pyplot as plt
import numpy as np

def leer_datos(fichero):
    X, K, V, E = [], [], [], []
    with open(fichero, 'r') as file:
        for line in file:
            x, k, v, e = map(float, line.strip().split(','))
            X.append(x)
            K.append(k)
            V.append(v)
            E.append(e)
    return X, K, V, E

def crear_grafica(X, K, V, E):
    fig, ax1 = plt.subplots()

    ax2 = ax1.twinx()
    ax3 = ax1.twinx()

    # Desplaza el tercer eje a la derecha
    ax3.spines['right'].set_position(('outward', 60))
    
    # Grafica las series
    ax1.plot(X, K, 'g-', label='K')
    ax2.plot(X, V, 'b-', label='V')
    ax3.plot(X, E, 'r-', label='E')
    
    ax1.set_xlabel('X')
    ax1.set_ylabel('K', color='g')
    ax2.set_ylabel('V', color='b')
    ax3.set_ylabel('E', color='r')

    # Colores de etiquetas
    ax1.tick_params(axis='y', labelcolor='g')
    ax2.tick_params(axis='y', labelcolor='b')
    ax3.tick_params(axis='y', labelcolor='r')

    # Leyendas
    lines_1, labels_1 = ax1.get_legend_handles_labels()
    lines_2, labels_2 = ax2.get_legend_handles_labels()
    lines_3, labels_3 = ax3.get_legend_handles_labels()
    ax1.legend(lines_1 + lines_2 + lines_3, labels_1 + labels_2 + labels_3, loc='best')

    fig.tight_layout()
    plt.show()

def main():
    fichero = 'energias.txt'  # Cambia esto por el nombre de tu fichero
    X, K, V, E = leer_datos(fichero)
    crear_grafica(X, K, V, E)

if __name__ == "__main__":
    main()