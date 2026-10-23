
#include <iostream>
#include "../Graph.h"

int main() {
    try {
        Graph grafo(
            "include/src/data/grafo_1.txt",
            Representation::ADJACENCY_LIST
        );

        std::cout << "Grafo carregado com sucesso!\n";
        std::cout << "Vertices: " << grafo.getNumVertices() << '\n';
        std::cout << "Arestas: " << grafo.getNumEdges() << '\n';
        std::cout << "Grau minimo: " << grafo.getMinDegree() << '\n';
        std::cout << "Grau maximo: " << grafo.getMaxDegree() << '\n';
        std::cout << "Grau medio: " << grafo.getAverageDegree() << '\n';

        BFSResult resultado = grafo.bfs(1);
        grafo.saveBFSResult(resultado, "resultado_bfs.txt");

        std::cout << "Resultado da BFS salvo em resultado_bfs.txt\n";
    }
    catch (const std::exception& erro) {
        std::cerr << "Erro: " << erro.what() << '\n';
        return 1;
    }

    return 0;
}
