import pandas as pd
import matplotlib.pyplot as plt

# Carregar os dados
df = pd.read_csv('tempos.csv')

# Criar figura com 2 subplots
plt.figure(figsize=(14, 10))

# Gráfico 1: Tempo de execução
plt.subplot(2, 1, 1)  # 2 linhas, 1 coluna, posição 1
for algoritmo in df['Algoritmo'].unique():
    subset = df[df['Algoritmo'] == algoritmo]
    plt.plot(subset['Tamanho'], subset['Tempo'], label=algoritmo, marker='o', linestyle='-')
    
plt.xlabel('Tamanho da Entrada')
plt.ylabel('Tempo (segundos)')
plt.title('Comparação de Algoritmos de Ordenação: Tempo de Execução')
plt.legend()
plt.grid(True)

# Gráfico 2: Número de Trocas (cada unidade = 10k trocas)
plt.subplot(2, 1, 2)  # 2 linhas, 1 coluna, posição 2
for algoritmo in df['Algoritmo'].unique():
    subset = df[df['Algoritmo'] == algoritmo]
    # Multiplicar por 10k para mostrar o valor real aproximado
    plt.plot(subset['Tamanho'], subset['Trocas (cada 10 mil)']*10000, 
             label=algoritmo, marker='s', linestyle='--')

plt.xlabel('Tamanho da Entrada')
plt.ylabel('Número de Trocas (×10,000)')
plt.title('Comparação de Algoritmos de Ordenação: Quantidade de Trocas')
plt.legend()
plt.grid(True)

# Ajustar layout e salvar
plt.tight_layout()
plt.savefig('comparacao_algoritmos.png')
plt.show()