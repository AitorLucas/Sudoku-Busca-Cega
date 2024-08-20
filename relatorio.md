# Relatório Métodos de Busca Cega (BFS e DFS)
**Estudante: Aitor Eler Lucas**

## Introdução

Este relatório apresenta uma análise de desempenho de dois algoritmos utilizados para resolver o problema do Sudoku: Busca em Profundidade (DFS) e Busca em Largura (BFS). Os dados foram obtidos a partir da execução do código [`sudoku.cpp`](sudoku.cpp), que implementa ambos os algoritmos e mede o tempo de execução para cada um deles.

## Descrição Geral do Problema

O Sudoku é um jogo de lógica que consiste em preencher uma grade 9x9 com números de 1 a 9, de forma que cada linha, coluna e cada uma das nove subgrades 3x3 contenham todos os números de 1 a 9 sem repetição. A implementação do código [`sudoku.cpp`](sudoku.cpp) inclui as seguintes funcionalidades principais:

1. **Leitura do Tabuleiro**: A função `lerSudoku` lê o tabuleiro de um arquivo de texto.
2. **Verificação de Segurança**: A função `eSeguro` verifica se é seguro colocar um número em uma posição específica.
3. **Impressão do Tabuleiro**: A função `imprimirSudoku` imprime o tabuleiro de Sudoku.
4. **Resolução do Sudoku**: A função `resolve` direciona a resolução para o parametro a função (algoritmo) que será utilizado para obter o resultado e mede o tempo de execução dos algoritmos, podendo ser os algoritmos: `resolverSudokuDFS` ou `resolverSudokuBFS`.
5. **Verificação da Solução**: A função `verificarSolucao` verifica se o Sudoku foi resolvido corretamente.
6.  **Cálculos de resultado**: As funções `usoDeMemoria`, `media` e `desvioPadrao` são usadas para retornar dados de resultado dos algoritmos.

## Dados de Desempenho

Os dados de desempenho foram coletados a partir de 100 execuções de cada algoritmo. Os tempos de execução (em microssegundos) e o uso de memória (em KB) foram registrados e armazenados no arquivo [`resultados.csv`](resultados.csv). Abaixo estão os resultados resumidos:

| Dados                       | DFS       | BFS       |
|-----------------------------|-----------|-----------|
| Média Tempo (µs)            | 40.88     | 1205.89   |
| Desvio Padrão Tempo (µs)    | 88.868    | 2597.69   |
| Média Memória (KB)          | 1220.40   | 1225.64   |
| Desvio Padrão Memória (KB)  | 96.6354   | 97.9928   |

## Análise de Desempenho

### Tempo
### Busca em Profundidade (DFS)

A Busca em Profundidade (DFS) é um algoritmo que explora o máximo possível cada ramo antes de retroceder. No contexto do Sudoku, o DFS tenta preencher cada célula vazia com um número válido e avança para a próxima célula. Se encontrar um impasse, ele retrocede e tenta um número diferente.

- **Média de Tempo de Execução**: 40.88 µs
- **Desvio Padrão**: 88.868 µs

O DFS apresentou um tempo de execução médio relativamente baixo, indicando que, na maioria dos casos, ele consegue resolver o Sudoku rapidamente. No entanto, o desvio padrão relativamente alto sugere que há variação significativa no tempo de execução dependendo da configuração inicial do tabuleiro.

### Busca em Largura (BFS)

A Busca em Largura (BFS) é um algoritmo que explora todos os nós em um nível antes de passar para o próximo nível. No contexto do Sudoku, o BFS tenta preencher cada célula vazia com todos os números possíveis e avança para a próxima célula, explorando todas as possibilidades em paralelo.

- **Média de Tempo de Execução**: 1205.89 µs
- **Desvio Padrão**: 2597.69 µs

O BFS apresentou um tempo de execução médio significativamente maior em comparação com o DFS. Isso ocorre porque o BFS explora todas as possibilidades em paralelo, o que pode ser computacionalmente mais intensivo. O desvio padrão ainda maior indica que o tempo de execução do BFS é ainda mais sensivel a configuração inicial do tabuleiro.

### Memória
**Comparação Geral**

Os dados obtidos para memória foram muito proximos nos dois algoritmos, o que implica que talvez o metódo de obtenção desses dados não está mostrando dados muito preciso pois de uma maneira geral os algoritmos se comportam da seguinte forma:
- **DFS**: Geralmente, o DFS tende a usar menos memória do que o BFS, pois ele explora um caminho até o fim antes de retroceder, mantendo menos estados intermediários na memória ao mesmo tempo.
- **BFS**: O BFS tende a usar mais memória do que o DFS, pois ele mantém todos os estados intermediários de um nível na memória antes de passar para o próximo nível. Isso pode levar a um uso significativo de memória em tabuleiros complexos.

## Dados iniciais
Os dados iniciais são gerados pelo código [`sudoku_generator.cpp`](sudoku_generator.cpp). Este código cria tabuleiros de Sudoku com um número variável de elementos vazios, que são então utilizados para testar os algoritmos DFS e BFS. A geração dos tabuleiros é feita de forma aleatória, garantindo uma variedade de configurações iniciais para os testes.