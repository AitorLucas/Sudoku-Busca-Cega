#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <chrono>
#include <cmath>
#include <getopt.h>
#include <windows.h>
#include <psapi.h>

using namespace std;

const int N = 9; // Tamanho do tabuleiro do Sudoku

enum Algoritmo {
    DFS,
    BFS
}; // Algoritimos utilizados para resolver o Sudoku

// Função para imprimir o tabuleiro de Sudoku
void imprimirSudoku(const vector<vector<int>>& tabuleiro) {
    for (int i = 0; i < N; i++) {
        if (i % 3 == 0) {
            cout << "+-------+-------+-------+" << endl;
        }
        for (int j = 0; j < N; j++) {
            if (j % 3 == 0) {
                cout << "| ";
            }
            cout << tabuleiro[i][j] << " ";
            if (j == N - 1) {
                cout << "|";
            }
        }
        cout << endl;
    }
    cout << "+-------+-------+-------+" << endl;
    cout << endl;
}

// Função para verificar se é seguro colocar um número em uma posição específica
bool eSeguro(const vector<vector<int>>& tabuleiro, int linha, int coluna, int num) {
    // Verifica se o número está presente na linha ou coluna
    for (int x = 0; x < N; x++) {
        if (tabuleiro[linha][x] == num || tabuleiro[x][coluna] == num) { 
            return false;
        }
    }
    
    // Verifica se o número está presente no quadrado 3x3
    int startRow = linha - linha % 3, startCol = coluna - coluna % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true; // Devolve True se o número não estiver presente na linha, coluna ou quadrado 3x3
}

// Função de busca em profundidade (DFS) para resolver o Sudoku
bool resolverSudokuDFS(vector<vector<int>>& tabuleiro) {
    int linha = -1, coluna = -1;
    bool vazio = false;
    
    // Encontra uma célula vazia
    for (int i = 0; i < N && !vazio; i++) {
        for (int j = 0; j < N && !vazio; j++) {
            if (tabuleiro[i][j] == 0) {
                linha = i;
                coluna = j;
                vazio = true;
            }
        }
    }
    
    // Se não há células vazias, o Sudoku está resolvido
    if (!vazio) {
        return true; 
    }

    // Tenta números de 1 a 9 na célula vazia
    for (int num = 1; num <= 9; num++) {
        if (eSeguro(tabuleiro, linha, coluna, num)) { // Verifica se o número é seguro para ser colocado na célula vazia (ou seja, não está presente na linha, coluna e quadrado 3x3)
            tabuleiro[linha][coluna] = num; // Atribui o número à célula vazia
            if (resolverSudokuDFS(tabuleiro)) { // Chamada da função recursiva para resolver as outras células, se True, o Sudoku está resolvido
                return true;
            }
            tabuleiro[linha][coluna] = 0; // Se a atribuição do número não levar a uma solução, a célula é redefinida para 0
        }
    }

    return false; // Retorna False se não houver solução para a célula vazia. Indicando que não é possível resolver o Sudoku
}

// Função de busca em largura (BFS) para resolver o Sudoku
bool resolverSudokuBFS(vector<vector<int>>& tabuleiro) {
    queue<vector<vector<int>>> fila;
    fila.push(tabuleiro);
    
    while (!fila.empty()) {
        vector<vector<int>> curr = fila.front();
        fila.pop();
        
        int linha = -1, coluna = -1;
        bool vazio = false;
        
        // Encontra uma célula vazia
        for (int i = 0; i < N && !vazio; i++) {
            for (int j = 0; j < N && !vazio; j++) {
                if (curr[i][j] == 0) {
                    linha = i;
                    coluna = j;
                    vazio = true;
                }
            }
        }
        
        // Se não há células vazias, o Sudoku está resolvido
        if (!vazio) {
            tabuleiro = curr;
            return true; 
        }
        
        // Tenta números de 1 a 9 na célula vazia
        for (int num = 1; num <= 9; num++) { 
            if (eSeguro(curr, linha, coluna, num)) { // Verifica se o número é seguro para ser colocado na célula vazia (ou seja, não está presente na linha, coluna e quadrado 3x3)
                vector<vector<int>> novoTabuleiro = curr; // Cria uma cópia do tabuleiro atual
                novoTabuleiro[linha][coluna] = num; // Atribui o número à célula vazia nesse novo tabuleiro
                fila.push(novoTabuleiro); // Adiciona o novo tabuleiro à fila
            }
        }
    }

    return false;
}

// Função para ler o Sudoku de um arquivo .txt
vector<vector<int>> lerSudoku(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    vector<vector<int>> tabuleiro(N, vector<int>(N, 0));
    
    if (arquivo.is_open()) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                arquivo >> tabuleiro[i][j];
            }
        }
        arquivo.close();
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
    
    return tabuleiro;
}

// Função para verificar se o Sudoku está resolvido corretamente
bool verificarSolucao(const vector<vector<int>>& tabuleiro) {
    const set<int> numeros = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    // testa as linhas do tabuleiro do sudoku
    for (int i = 0; i < N; i++) {
        set<int> linha(tabuleiro[i].begin(), tabuleiro[i].end());
        if (linha != numeros) {
            return false;
        }
    }

    // testa as colunas do tabuleiro do sudoku
    for (int i = 0; i < N; i++) {
        set<int> coluna;
        for (int j = 0; j < N; j++) {
            coluna.insert(tabuleiro[j][i]);
        }
        if (coluna != numeros) {
            return false;
        }
    }

    // testa os quadrados do tabuleiro do sudoku
    for (int i = 0; i < N; i += 3) {
        for (int j = 0; j < N; j += 3) {
            set<int> quadrado;
            for (int k = i; k < i + 3; k++) {
                for (int l = j; l < j + 3; l++) {
                    quadrado.insert(tabuleiro[k][l]);
                }
            }
            if (quadrado != numeros) {
                return false;
            }
        }
    }

    return true;
}

// Funcao que chama o algoritmo de resolucao do sudoku e retorna o tempo de execucao (-1 para error)
int resolve(vector<vector<int>> &tabuleiro, bool (*resolverSudoku)(vector<vector<int>>&), bool imprimir, Algoritmo algoritmo) {
    int duracao = -1;
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    string resultadoDoAlgoritimo = "XXXXXXX"; // Se o algoritmo não resolver o Sudoku, o resultado será XXXXXXX
    if (resolverSudoku(tabuleiro)) {
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        duracao = chrono::duration_cast<chrono::microseconds>(end - begin).count();

        if (verificarSolucao(tabuleiro)) {
            resultadoDoAlgoritimo = " OK"; // Se o Sudoku foi resolvido corretamente, o resultado será OK
        } else {
            resultadoDoAlgoritimo = "NOK"; // Se o Sudoku foi resolvido incorretamente, o resultado será NOK
        }
    }

    // Imprimir resultados
    if (imprimir) {
        switch (algoritmo) {
        case DFS:
            cout << "DFS: " << '\t';
            break;
        case BFS:
            cout << "BFS: " << '\t';
            break;
        }

        cout << duracao << " microssegundos" << endl;
        cout << "Resultado: " << resultadoDoAlgoritimo << endl;
        // imprimirSudoku(tabuleiro); // IMPRIMIR TABULEIRO RESOLVIDO
    }

    return duracao;
}

// Função para medir o uso de memória
float usoDeMemoria() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    return static_cast<float>(pmc.PrivateUsage) / 1024.0f; // Converte bytes para KB
}

// Funcao que calculo a media
float media(vector<float> vetor) {
    float soma = 0;
    for (int elemento : vetor) {
        soma += elemento;
    }
    return soma / vetor.size();
}

// Funcao que calcula o desvio padrao
float desvioPadrao(vector<float> vetor, float media) {
    if (vetor.size() == 0) {
        return 0;
    }

    float soma = 0;
    for (int elemento : vetor) {
        soma += pow(elemento - media, 2);
    }
    return sqrt(soma / vetor.size());
}

//  MAIN
//
// Parametros:
// -i: Imprimir tabuleiros e resultados
// -t: Imprimir tempo de execucao
int main(int argc, char *argv[]) {
    int numeroDeTestes = 100;
    vector<float> temposDFS;
    vector<float> temposBFS;
    vector<float> memoriaDFS(numeroDeTestes);
    vector<float> memoriaBFS(numeroDeTestes);
    
    // Processa argumentos da linha de comando
    bool imprimir = false;
    bool imprimirTempo = false;
    int opt;
    while ((opt = getopt(argc, argv, "it")) != -1) {
        switch (opt) {
            case 'i':
                imprimir = true;
                break;
            case 't':
                imprimirTempo = true;
                break;
            default:
                cerr << "Uso: " << argv[0] << " [-i] [-t]" << endl;
                return 1;
        }
    }

    // Executa os testes de Sudoku na pasta testes
    for (int teste = 1; teste <= numeroDeTestes; teste++) {
        string name = "testes/" + to_string(teste) + ".txt";
        vector<vector<int>> tabuleiro = lerSudoku(name);
        
        //  Imprimir o tabuleiro de Sudoku
        if (imprimir || imprimirTempo) {
            cout << "=========================" << endl;
            cout << "\tTeste " << teste << endl;
            cout << "=========================" << endl;
        }
        if (imprimir) {
            imprimirSudoku(tabuleiro);
        }

        vector<vector<int>> tabuleiroDFS = tabuleiro;
        vector<vector<int>> tabuleiroBFS = tabuleiro;

        int tempoResolucaoDFS = resolve(tabuleiroDFS, resolverSudokuDFS, imprimirTempo, DFS);
        if (tempoResolucaoDFS != -1) {
            temposDFS.push_back(tempoResolucaoDFS);
        }
        memoriaDFS[teste - 1] = usoDeMemoria();

        int tempoResolucaoBFS = resolve(tabuleiroBFS, resolverSudokuBFS, imprimirTempo, BFS);
        if (tempoResolucaoBFS != -1) {
            temposBFS.push_back(tempoResolucaoBFS);
        }
        memoriaBFS[teste - 1] = usoDeMemoria();
    }

    // Calculo dos resultados de tempo
    float mediaTempoDFS = media(temposDFS);
    float mediaTempoBFS = media(temposBFS);
    float desvioTempoDFS = desvioPadrao(temposDFS, mediaTempoDFS);
    float desvioTempoBFS = desvioPadrao(temposBFS, mediaTempoBFS);
    // Calculo dos resultados de memoria
    float mediaMemoriaDFS = media(memoriaDFS);
    float mediaMemoriaBFS = media(memoriaBFS);
    float desvioMemoriaDFS = desvioPadrao(memoriaDFS, mediaMemoriaDFS);
    float desvioMemoriaBFS = desvioPadrao(memoriaBFS, mediaMemoriaBFS);

    // Imprime resultados
    cout << endl;
    cout << "==================================================" << endl;
    cout << " Media tempo DFS: " << mediaTempoDFS << " microssegundos" << endl;
    cout << " Desvio padrao tempo DFS: " << desvioTempoDFS << " microssegundos" << endl;
    cout << " Media memoria DFS: " << mediaMemoriaDFS << " KB" << endl;
    cout << " Desvio padrao memoria DFS: " << desvioMemoriaDFS << " KB" << endl;
    cout << endl;
    cout << " Media tempo BFS: " << mediaTempoBFS << " microssegundos" << endl;
    cout << " Desvio padrao tempo BFS: " << desvioTempoBFS << " microssegundos" << endl;
    cout << " Media memoria BFS: " << mediaMemoriaBFS << " KB" << endl;
    cout << " Desvio padrao memoria BFS: " << desvioMemoriaBFS << " KB" << endl;
    cout << "==================================================" << endl;
    cout << endl;

    // Cria um arquivo de saida com os resultados (CSV)
    ofstream arquivoCSV("resultados.csv");
    if(arquivoCSV.is_open()) {
        // Cabeçalho do arquivo CSV
        arquivoCSV << "Dados,DFS Tempo (microssegundos),BFS Tempo (microssegundos),DFS Memoria (KB),BFS Memoria(KB)\n";
        
        // Escrever tempos de execução e uso de memória
        size_t maxSize = max(temposDFS.size(), temposBFS.size());
        for (size_t i = 0; i < 100; ++i) {
            arquivoCSV << "Teste " << i + 1 << ",";
            if (i < temposDFS.size()) {
                arquivoCSV << temposDFS[i];
            }
            arquivoCSV << ",";
            if (i < temposBFS.size()) {
                arquivoCSV << temposBFS[i];
            }
            arquivoCSV << ",";
            if (i < memoriaDFS.size()) {
                arquivoCSV << memoriaDFS[i];
            }
            arquivoCSV << ",";
            if (i < memoriaBFS.size()) {
                arquivoCSV << memoriaBFS[i];
            }
            arquivoCSV << "\n";
        }
        
        // Escrever média e desvio padrão
        arquivoCSV << "Tempo Medio," << mediaTempoDFS << "," << mediaTempoBFS << "\n";
        arquivoCSV << "Tempo Desvio Padrao," << desvioTempoDFS << "," << desvioTempoBFS << "\n";
        arquivoCSV << "Memoria Media," << ",," << mediaMemoriaDFS << "," << mediaMemoriaBFS << "\n";
        arquivoCSV << "Memoria Desvio Padrao," << ",," << desvioMemoriaDFS << "," << desvioMemoriaBFS << "\n";

        // Fechar o arquivo
        arquivoCSV.close();
        cout << "Resultados salvos em resultados.csv" << endl;
    } else {
        cerr<< "Erro ao abrir o arquivo resultados.csv" << endl;
        return -1;
    }

    cout << endl << "[POSSIVEIS OPCOES DE EXECUCAO]" << endl;
    cout <<  "-i" << '\t' << "Imprimir tabuleiros" << endl;
    cout <<  "-t" << '\t' << "Imprimir tempo de execucao" << endl;
    cout << endl;

    return 0;
}