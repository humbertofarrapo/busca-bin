#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Função de busca sequencial
int busca_sequencial(std::vector<int>& V, int x) {
    for (int i = 0; i < V.size(); i++) {
        if (V[i] == x) {
            return i;
        }
    }
    return -1;
}

// Função de busca sequencial otimizada
int busca_sequencial_otimizada(std::vector<int>& V, int x) {
    for (int i = 0; i < V.size(); i++) {
        if (V[i] == x) {
            return i;
        }
        else if (V[i] > x) {
            return -1;
        }
    }
    return -1;
}

// Função de busca binária
int busca_binaria(std::vector<int>& V, int x) {
    int baixo = 0, alto = V.size() - 1;
    while (baixo <= alto) {
        int meio = (baixo + alto) / 2;
        if (V[meio] == x) {
            return meio;
        }
        else if (V[meio] < x) {
            baixo = meio + 1;
        }
        else {
            alto = meio - 1;
        }
    }
    return -1;
}

// Função para gerar uma sequência aleatória
void gerar_sequencia(std::vector<int>& V, int n) {
    V.clear(); // Limpa o vetor, se houver algum conteúdo anterior
    for (int i = 0; i < n; i++) {
        V.push_back(rand() % 101); // números aleatórios entre 0 e 100
    }
}

// Gerar chaves aleatórias
void gerar_chave(std::vector<int>& V, int q) {
    V.clear(); // Limpa o vetor, se houver algum conteúdo anterior
    for (int i = 0; i < q; i++) {
        V.push_back(rand() % 101); // números aleatórios entre 0 e 100
    }
}

// Função para executar uma busca e medir o tempo
double executar_busca(std::vector<int>& V, int q, int tipo_busca) {
    clock_t inicio, fim;
    double tempo_total = 0;

    // Realizar 1000 execuções e calcular o tempo médio
    for (int k = 0; k < 1000; k++) {
        // Gerar chaves aleatórias
        gerar_chave(V, q);

        inicio = clock();
        for (int i = 0; i < q; i++) {
            if (tipo_busca == 0) {
                busca_sequencial(V, V[i]);
            }
            else if (tipo_busca == 1) {
                busca_sequencial_otimizada(V, V[i]);
            }
            else {
                busca_binaria(V, V[i]);
            }
        }
        fim = clock();

        tempo_total += ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    }

    return tempo_total / 1000;
}

int main() {
    std::vector<int> sequencia;
    std::vector<int> chaves;

    // Tamanho da sequência e número de consultas
    std::vector<int> tamanhos_sequencia = {10000, 100000, 1000000, 10000000};
    std::vector<int> num_consultas = {100, 1000, 10000, 100000};

    for (int i = 0; i < tamanhos_sequencia.size(); i++) {
        for (int j = 0; j < num_consultas.size(); j++) {
            int n = tamanhos_sequencia[i];
            int q = num_consultas[j];

            // Gerar sequência aleatória
            gerar_sequencia(sequencia, n);

            // Busca sequencial
            double tempo_medio_seq = executar_busca(sequencia, q, 0);

            // Busca sequencial otimizada
            double tempo_medio_seq_otim = executar_busca(sequencia, q, 1);

            // Ordenar sequência para busca binária
            std::sort(sequencia.begin(), sequencia.end());

            // Busca binária
            double tempo_medio_binaria = executar_busca(sequencia, q, 2);

            std::cout << "Experimentos para n = " << n << ", q = " << q << "\n";
            std::cout << "Tempo médio da busca sequencial: " << tempo_medio_seq << " segundos\n";
            std::cout << "Tempo médio da busca sequencial otimizada: " << tempo_medio_seq_otim << " segundos\n";
            std::cout << "Tempo médio da busca binária: " << tempo_medio_binaria << " segundos\n";
        }
    }

    return 0;
}
