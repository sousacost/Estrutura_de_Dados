#include "../Graph.h"

#include <fstream>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <algorithm>
#include <iomanip>

Graph::Graph(const std::string& filename,
             Representation representation)
    : numVertices(0),
      numEdges(0),
      representation(representation) {

    loadFromFile(filename);
}

void Graph::loadFromFile(const std::string& filename) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Nao foi possivel abrir o arquivo: " + filename
        );
    }

    file >> numVertices;

    if (numVertices <= 0) {
        throw std::runtime_error(
            "Numero de vertices invalido."
        );
    }

    if (representation == Representation::ADJACENCY_LIST) {

        adjacencyList.resize(numVertices + 1);

    } else {

        adjacencyMatrix.resize(numVertices + 1);

        for (int i = 0; i <= numVertices; ++i) {
            adjacencyMatrix[i].resize(
                numVertices + 1,
                false
            );
        }
    }

    int u;
    int v;

    while (file >> u >> v) {

        if (u < 1 || u > numVertices ||
            v < 1 || v > numVertices) {

            throw std::runtime_error(
                "Vertice fora do intervalo permitido."
            );
        }

        if (representation == Representation::ADJACENCY_LIST) {
            addEdgeToList(u, v);
        } else {
            addEdgeToMatrix(u, v);
        }

        ++numEdges;
    }

    file.close();
}

void Graph::addEdgeToList(int u, int v) {

    adjacencyList[u].push_back(v);
    adjacencyList[v].push_back(u);
}

void Graph::addEdgeToMatrix(int u, int v) {

    adjacencyMatrix[u][v] = true;
    adjacencyMatrix[v][u] = true;
}

int Graph::getNumVertices() const {
    return numVertices;
}

long long Graph::getNumEdges() const {
    return numEdges;
}

int Graph::degree(int vertex) const {

    if (representation == Representation::ADJACENCY_LIST) {

        return static_cast<int>(
            adjacencyList[vertex].size()
        );
    }

    int degree = 0;

    for (int v = 1; v <= numVertices; ++v) {

        if (adjacencyMatrix[vertex][v]) {
            ++degree;
        }
    }

    return degree;
}

int Graph::getMinDegree() const {

    int minDegree = degree(1);

    for (int v = 2; v <= numVertices; ++v) {

        minDegree = std::min(
            minDegree,
            degree(v)
        );
    }

    return minDegree;
}

int Graph::getMaxDegree() const {

    int maxDegree = degree(1);

    for (int v = 2; v <= numVertices; ++v) {

        maxDegree = std::max(
            maxDegree,
            degree(v)
        );
    }

    return maxDegree;
}

double Graph::getAverageDegree() const {

    if (numVertices == 0) {
        return 0.0;
    }

    long long totalDegree = 0;

    for (int v = 1; v <= numVertices; ++v) {
        totalDegree += degree(v);
    }

    return static_cast<double>(totalDegree)
           / numVertices;
}

BFSResult Graph::bfs(int startVertex) const {

    if (startVertex < 1 ||
        startVertex > numVertices) {

        throw std::invalid_argument(
            "Vertice inicial invalido."
        );
    }

    BFSResult result;

    result.parent.assign(numVertices + 1, -1);
    result.level.assign(numVertices + 1, -1);

    std::queue<int> queue;

    result.parent[startVertex] = -1;
    result.level[startVertex] = 0;

    queue.push(startVertex);

    while (!queue.empty()) {

        int current = queue.front();
        queue.pop();

        // Lista de adjacência
        if (representation == Representation::ADJACENCY_LIST) {

            for (int neighbor : adjacencyList[current]) {

                if (result.level[neighbor] == -1) {

                    result.parent[neighbor] = current;

                    result.level[neighbor] =
                        result.level[current] + 1;

                    queue.push(neighbor);
                }
            }

        }

        // Matriz de adjacência
        else {

            for (int neighbor = 1;
                 neighbor <= numVertices;
                 ++neighbor) {

                if (adjacencyMatrix[current][neighbor] &&
                    result.level[neighbor] == -1) {

                    result.parent[neighbor] = current;

                    result.level[neighbor] =
                        result.level[current] + 1;

                    queue.push(neighbor);
                }
            }
        }
    }

    return result;
}

void Graph::saveBFSResult(
    const BFSResult& result,
    const std::string& filename) const {

    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Nao foi possivel criar o arquivo: " + filename
        );
    }

    file << "Vertice Pai Nivel\n";

    for (int v = 1; v <= numVertices; ++v) {

        file << v << " "
             << result.parent[v] << " "
             << result.level[v] << "\n";
    }

    file.close();
}