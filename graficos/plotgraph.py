import pandas as pd
import matplotlib.pyplot as plt

# Carregar os dados
df = pd.read_csv('tempos.csv')

# Grafico de tempo x tamanho para cada algoritmo
plt.figure(figsize=(12,6))
for algoritmo in df['Algoritmo'].unique():
    subset = df[df['Algoritmo'] == algoritmo]
    plt.plot(subset['Tamanho'], subset['Tempo'], label=algoritmo, marker='o')
    
plt.xlabel('Tamanho da Entrada')
plt.ylabel('Tempo (segundos)')
plt.title('Tempo de execução por algoritmo e tamanho da entrada')
plt.legend()
plt.grid(True)
plt.savefig('tempo_ordenacao.png')
plt.show()