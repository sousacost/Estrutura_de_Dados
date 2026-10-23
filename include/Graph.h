#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

enum class Representation {
    ADJACENCY_LIST,
    ADJACENCY_MATRIX
};

struct BFSResult {
    std::vector<int> parent;
    std::vector<int> level;
};

class Graph {
private:
    int numVertices;
    long long numEdges;
    Representation representation;

    // Lista de adjacência
    std::vector<std::vector<int>> adjacencyList;

    // Matriz de adjacência
    std::vector<std::vector<bool>> adjacencyMatrix;

public:
    // Construtor
    Graph(const std::string& filename, Representation representation);

    // Informações básicas
    int getNumVertices() const;
    long long getNumEdges() const;

    int getMinDegree() const;
    int getMaxDegree() const;
    double getAverageDegree() const;

    // BFS
    BFSResult bfs(int startVertex) const;

    // Salva o resultado da BFS em arquivo
    void saveBFSResult(const BFSResult& result,
                       const std::string& filename) const;

private:
    // Leitura do arquivo
    void loadFromFile(const std::string& filename);

    // Operações específicas de cada representação
    void addEdgeToList(int u, int v);
    void addEdgeToMatrix(int u, int v);

    int degree(int vertex) const;
};

#endif