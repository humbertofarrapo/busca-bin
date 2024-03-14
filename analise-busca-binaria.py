import random
import time

def gerar_sequencia(n):
    return [random.randint(0, 50) for _ in range(n)]

def gerar_chave(q):
    return [random.randint(0, 50) for _ in range(q)]

# Métodos de busca para os experimentos
def busca_sequencial(V, chave):
    for i, elemento in enumerate(V):
        if elemento == chave:
            return i
    return -1

def busca_sequencial_otimizada(V, chave):
    for i, elemento in enumerate(V):
        if elemento > chave:
            return -1
        if elemento == chave:
            return i
    return -1

def busca_binaria(V, chave):
    inicio = 0
    fim = len(V) - 1
    while inicio <= fim:
        meio = (inicio + fim) // 2
        if V[meio] == chave:
            return meio
        elif V[meio] < chave:
            inicio = meio + 1
        else:
            fim = meio - 1
    return -1
    
# Função para executar os experimentos
def executar_experimentos(n, q, num_exec):
    sequencia = gerar_sequencia(n)
    chaves = gerar_chave(q)

    sequencia.sort()

    def medir_tempo(busca):
        tempo_inicio = time.time()
        for chave in chaves:
            busca(sequencia, chave)
        return (time.time() - tempo_inicio) / num_exec

    tempo_busca_sequencial = medir_tempo(busca_sequencial)
    tempo_busca_sequencial_otimizada = medir_tempo(busca_sequencial_otimizada)
    tempo_busca_binaria = medir_tempo(busca_binaria)

    print("# n =", n)
    print("# q =", q)
    print("# num_exec =", num_exec)
    print("# busca_sequencial =", tempo_busca_sequencial)
    print("# busca_sequencial_otimizada =", tempo_busca_sequencial_otimizada)
    print("# busca_binaria =", tempo_busca_binaria)
    print("\n")

# Parâmetros do experimento
valores_n = [10**4, 10**5, 10**6, 10**7]
valores_q = [10**2, 10**3, 10**4, 10**5]

# Número de execuções para calcular o tempo médio
num_exec = 5 

# Execução do experimento
for n in valores_n:
    for q in valores_q:
        executar_experimentos(n, q, num_exec)

