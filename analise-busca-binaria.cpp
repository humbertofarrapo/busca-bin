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

// Função para executar os experimentos
void executar_experimentos(std::vector<int>& V, int q) {
    srand(time(NULL)); // inicializar semente para geração de números aleatórios

    double tempo_sequencial = 0, tempo_sequencial_otimizada = 0, tempo_binaria = 0;

    // Realizar 10 execuções e calcular o tempo médio para cada tipo de busca
    for (int k = 0; k < 10; k++) {
        // Gerar chaves aleatórias
        gerar_chave(V, q);

        // Busca sequencial
        clock_t inicio = clock();
        for (int i = 0; i < q; i++) {
            busca_sequencial(V, V[i]);
        }
        clock_t fim = clock();
        tempo_sequencial += ((double) (fim - inicio)) / CLOCKS_PER_SEC;

        // Busca sequencial otimizada
        inicio = clock();
        for (int i = 0; i < q; i++) {
            busca_sequencial_otimizada(V, V[i]);
        }
        fim = clock();
        tempo_sequencial_otimizada += ((double) (fim - inicio)) / CLOCKS_PER_SEC;

        // Ordenar sequência para busca binária
        std::sort(V.begin(), V.end());

        // Busca binária
        inicio = clock();
        for (int i = 0; i < q; i++) {
            busca_binaria(V, V[i]);
        }
        fim = clock();
        tempo_binaria += ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    }

    std::cout << "Tempo médio da busca sequencial: " << tempo_sequencial / 10 << " segundos\n";
    std::cout << "Tempo médio da busca sequencial otimizada: " << tempo_sequencial_otimizada / 10 << " segundos\n";
    std::cout << "Tempo médio da busca binária: " << tempo_binaria / 10 << " segundos\n";
}

int main() {
    // Tamanho da sequência e número de consultas
    std::vector<int> tamanhos_sequencia = {10000, 100000, 1000000, 10000000};
    std::vector<int> num_consultas = {100, 1000, 10000, 100000};

    // Executar experimentos para diferentes tamanhos e consultas
    for (int i = 0; i < tamanhos_sequencia.size(); i++) {
        for (int j = 0; j < num_consultas.size(); j++) {
            int n = tamanhos_sequencia[i];
            int q = num_consultas[j];

            // Alocar memória para a sequência e as chaves
            std::vector<int> sequencia;
            std::vector<int> chaves;

            // Gerar sequência aleatória
            gerar_sequencia(sequencia, n);

            // Executar experimentos e calcular a média do tempo de 10 execuções
            std::cout << "Experimentos para n = " << n << ", q = " << q << "\n";
            executar_experimentos(sequencia, q);
        }
    }

    return 0;
}
