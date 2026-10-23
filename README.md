# Biblioteca de Manipulação de Grafos em C++

Projeto desenvolvido em C++ para implementação de uma biblioteca reutilizável de manipulação de grafos não direcionados, com suporte a diferentes representações e ao algoritmo de Busca em Largura (BFS).

O projeto foi desenvolvido como parte da disciplina de Estrutura de Dados.

## Objetivos

A biblioteca tem como principais objetivos:

- Ler grafos a partir de arquivos de texto;
- Representar grafos utilizando:
  - Lista de adjacência;
  - Matriz de adjacência;
- Calcular o número de vértices e arestas;
- Calcular grau mínimo, máximo e médio;
- Executar Busca em Largura (BFS);
- Construir a árvore de busca em largura;
- Determinar o pai e o nível de cada vértice;
- Calcular distâncias entre vértices;
- Comparar o desempenho das diferentes representações.

## Estrutura do projeto

```text
Estrutura_de_Dados/
│
├── include/
│   └── Graph.h
│
├── include/src/
│   ├── Graph.cpp
│   ├── main.cpp
│   └── data/
│       ├── grafo_1.txt
│       ├── grafo_2.txt
│       ├── grafo_3.txt
│       ├── grafo_4.txt
│       ├── grafo_5.txt
│       └── grafo_6.txt
│
├── estatisticas.txt
└── README.md
```

## Representações utilizadas

### Lista de adjacência

A lista de adjacência é implementada utilizando:

```cpp
std::vector<std::vector<int>>
```

Cada posição representa um vértice e armazena os vértices adjacentes a ele.

Essa representação é especialmente adequada para grafos esparsos, pois armazena apenas as arestas existentes.

### Matriz de adjacência

A matriz é implementada utilizando:

```cpp
std::vector<std::vector<bool>>
```

Cada posição da matriz indica a existência ou não de uma aresta entre dois vértices.

A matriz possui custo de memória quadrático:

```text
O(V²)
```

Por esse motivo, sua utilização se torna impraticável para grafos com milhões de vértices.

## Busca em Largura — BFS

A biblioteca implementa o algoritmo de Busca em Largura (Breadth-First Search).

O BFS recebe um vértice inicial e percorre os vértices alcançáveis utilizando uma fila.

Para cada vértice são armazenadas duas informações:

- `parent`: vértice pai na árvore BFS;
- `level`: nível do vértice em relação à origem.

O vértice inicial possui nível `0`.

Exemplo:

```text
Vértice    Pai    Nível
1          -1       0
2           1       1
3           1       1
4           2       2
```

Quando um vértice possui nível `-1`, significa que ele não foi alcançado pelo BFS a partir da origem escolhida.

## Complexidade

### BFS utilizando lista de adjacência

```text
O(V + E)
```

Como a lista armazena diretamente os vizinhos de cada vértice, o algoritmo percorre os vértices e as arestas existentes.

### BFS utilizando matriz de adjacência

```text
O(V²)
```

Na implementação utilizada, para cada vértice visitado é necessário percorrer sua linha da matriz para identificar seus vizinhos.

Essa diferença torna a lista de adjacência mais adequada para os grafos grandes utilizados neste projeto.

## Grafos utilizados

Foram utilizados seis grafos para os estudos de caso:

| Grafo | Vértices | Arestas |
|---|---:|---:|
| Grafo 1 | 10.000 | 109.977 |
| Grafo 2 | 49.948 | 1.299.794 |
| Grafo 3 | 375.000 | 765.618 |
| Grafo 4 | 375.000 | 8.187.427 |
| Grafo 5 | 4.843.750 | 13.168.928 |
| Grafo 6 | 4.843.750 | 46.469.670 |

Além da quantidade de vértices e arestas, são calculados para cada grafo:

- Grau mínimo;
- Grau máximo;
- Grau médio.

## Experimentos de desempenho

Foram realizadas 100 execuções de BFS para cada grafo utilizando a lista de adjacência.

Os tempos médios obtidos foram:

| Grafo | Tempo médio por BFS |
|---|---:|
| Grafo 1 | 3,13191 ms |
| Grafo 2 | 12,8839 ms |
| Grafo 3 | 125,067 ms |
| Grafo 4 | 289,784 ms |
| Grafo 5 | 1.672,75 ms |
| Grafo 6 | 3.894 ms |

O tempo de leitura dos arquivos e a gravação dos resultados não fazem parte da medição do algoritmo.

### Comparação entre lista e matriz

No Grafo 1 foram comparadas as duas representações.

Resultados:

```text
Lista de adjacência:  3,13191 ms por BFS
Matriz de adjacência: 2307,97 ms por BFS
```

Nesse experimento, a matriz apresentou um tempo aproximadamente 737 vezes maior que a lista de adjacência.

Isso ocorre principalmente porque, na representação por matriz, o BFS precisa percorrer as posições da linha correspondente ao vértice para encontrar seus vizinhos.

## Escalabilidade da matriz

Para os grafos maiores, a matriz de adjacência deixa de ser uma representação viável devido ao crescimento quadrático do consumo de memória.

Por exemplo, para um grafo com 4.843.750 vértices:

```text
V² ≈ 23,46 trilhões de posições
```

Mesmo considerando uma representação de aproximadamente um bit por posição, seriam necessários aproximadamente:

```text
2,93 TB
```

somente para armazenar os bits da matriz, sem considerar o overhead das estruturas utilizadas pelo programa.

Por esse motivo, os experimentos com matriz foram limitados aos grafos nos quais sua alocação era tecnicamente viável.

## Distâncias

As distâncias entre dois vértices são obtidas através dos níveis produzidos pelo BFS.

Para uma origem `s`:

```cpp
distancia(s, v) = level[v]
```

quando `v` é alcançável a partir de `s`.

Caso contrário, o resultado é `-1`, indicando que os vértices pertencem a componentes conexas diferentes.

## Saída

O programa gera um arquivo:

```text
estatisticas.txt
```

contendo informações dos grafos, graus, resultados do BFS, pais, níveis, distâncias e tempos de execução.

A biblioteca também possui a função:

```cpp
saveBFSResult()
```

que permite salvar a árvore BFS e os níveis dos vértices em um arquivo de texto.

## Compilação

O projeto pode ser compilado utilizando o compilador `g++`.

No Windows, após configurar o caminho do compilador:

```powershell
g++ .\include\src\main.cpp .\include\src\Graph.cpp -o grafos.exe
```

## Execução

Após a compilação:

```powershell
.\grafos.exe
```

O programa processará os grafos definidos no `main.cpp` e apresentará os resultados no terminal e no arquivo `estatisticas.txt`.

## Requisitos

- C++17 ou superior;
- Compilador `g++`;
- Sistema operacional Windows ou outro ambiente compatível com C++;
- Memória RAM suficiente para os grafos utilizados.

## Organização da implementação

A classe principal é `Graph`.

Entre suas principais operações estão:

```cpp
Graph(...)
getNumVertices()
getNumEdges()
getMinDegree()
getMaxDegree()
getAverageDegree()
bfs()
saveBFSResult()
```

A implementação foi dividida entre interface (`Graph.h`) e implementação (`Graph.cpp`) para facilitar a reutilização da biblioteca em outros programas.

## Repositório

Código-fonte do projeto:

https://github.com/sousacost/Estrutura_de_Dados

## Autor

**Antonio Sousa**

Projeto acadêmico desenvolvido para a disciplina de Estrutura de Dados.

$env:Path = "C:\Users\Antonio Sousa\Documents\GitHub\ucrt64\bin;" + $env:Path
g++ .\include\src\main.cpp .\include\src\Graph.cpp -o grafos.exe
.\grafos.exe
