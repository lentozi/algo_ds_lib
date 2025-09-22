//
// Created by LengTouZai on 2025/9/19.
//
#pragma once
#include <optional>
#include <iostream>
#include <stdexcept>
#include "base/queue_structure.h"
#include "base/stack_structure.h"

template<typename V, typename E>
MatrixGraph<V, E>::MatrixGraph(std::string name, const bool has_direction)
    : GraphStructure<V, E>(name), has_direction(has_direction), _vertices(nullptr), _edges(nullptr) {}

template<typename V, typename E>
MatrixGraph<V, E>::~MatrixGraph() {
    if (_vertices) {
        delete[] _vertices;
        _vertices = nullptr;
    }
    if (_edges) {
        for (size_t i = 0; i < vertex_count; ++i) {
            delete[] _edges[i];
        }
        delete[] _edges;
        _edges = nullptr;
    }
}

template<typename V, typename E>
void MatrixGraph<V, E>::build_graph(const std::vector<V> &vertices, const std::vector<std::pair<std::pair<V, V>, E> > &edges) {
    vertex_count = vertices.size();
    edge_count = edges.size();

    // 初始化顶点数组
    _vertices = new V[vertex_count];
    for (size_t i = 0; i < vertex_count; ++i) {
        _vertices[i] = vertices[i];
    }

    // 初始化邻接矩阵
    _edges = new std::optional<E> *[vertex_count];
    for (size_t i = 0; i < vertex_count; ++i) {
        _edges[i] = new std::optional<E>[vertex_count];
        for (size_t j = 0; j < vertex_count; ++j) {
            _edges[i][j] = std::nullopt; // 假设std::nullopt表示无边
        }
    }

    for (const auto& edge : edges) {
        // 查找顶点的索引
        int start_index = -1, end_index = -1;
        find_vertex_index(edge.first.first, start_index);
        find_vertex_index(edge.first.second, end_index);
        _edges[start_index][end_index] = edge.second;
        if (!has_direction) {
            _edges[end_index][start_index] = edge.second; // 无向
        }
    }
}

// 获取入度，从列方向统计
template<typename V, typename E>
int MatrixGraph<V, E>::get_in_degree(const V &vertex) const {
    if (!_vertices || !_edges) {
        throw std::runtime_error("Graph not built");
    }
    int degree = 0;
    // 查找该顶点在数组中的索引
    int vertex_index = -1;
    find_vertex_index(vertex, vertex_index);

    for (int i = 0; i < vertex_count; ++i) {
        if (_edges[i][vertex_index].has_value()) {
            degree++;
        }
    }

    return degree;
}

template<typename V, typename E>
int MatrixGraph<V, E>::get_out_degree(const V &vertex) const {
    if (!_vertices || !_edges) {
        throw std::runtime_error("Graph not built");
    }
    int degree = 0;
    int vertex_index = -1;
    find_vertex_index(vertex, vertex_index);

    for (int j = 0; j < vertex_count; ++j) {
        if (_edges[vertex_index][j].has_value()) {
            degree++;
        }
    }

    return degree;
}


template<typename V, typename E>
int MatrixGraph<V, E>::get_degree(const V &vertex) const {
    if (!_vertices || !_edges) {
        throw std::runtime_error("Graph not built");
    }
    if (has_direction) {
        return get_in_degree(vertex) + get_out_degree(vertex);
    }
    return get_out_degree(vertex);
}

template<typename V, typename E>
void MatrixGraph<V, E>::print() const {
    if (!_vertices || !_edges) {
        std::cout << "Graph not built" << std::endl;
        return;
    }
    std::cout << "Graph: " << this->name << std::endl;
    std::cout << "Vertices: ";
    for (size_t i = 0; i < vertex_count; ++i) {
        std::cout << _vertices[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Edges: " << std::endl;
    for (size_t i = 0; i < vertex_count; ++i) {
        for (size_t j = 0; j < edge_count; ++j) {
            if (_edges[i][j].has_value()) {
                std::cout << "(" << _vertices[i] << " -> " << _vertices[j] << " : " << _edges[i][j].value() << ")" << std::endl;
            }
        }
    }
}

template<typename V, typename E>
bool MatrixGraph<V, E>::adjacent(const V &v1, const V &v2) const {
    if (!_vertices || !_edges) {
        throw std::runtime_error("Graph not built");
    }
    // 查找节点所在索引
    int start_index = -1, end_index = -1;
    find_vertex_index(v1, start_index);
    find_vertex_index(v2, end_index);

    return _edges[start_index][end_index].has_value();
}

template<typename V, typename E>
std::set<V> MatrixGraph<V, E>::neighbors(const V &vertex) const {
    int vertex_index = -1;
    find_vertex_index(vertex, vertex_index);
    std::set<V> neighbor_vertices;
    for (size_t j = 0; j < vertex_count; ++j) {
        if (_edges[vertex_index][j].has_value()) {
            neighbor_vertices.insert(_vertices[j]);
        }
    }
    if (has_direction) {
        for (size_t i = 0; i < vertex_count; ++i) {
            if (_edges[i][vertex_index].has_value()) {
                neighbor_vertices.insert(_vertices[i]);
            }
        }
    }
    return neighbor_vertices;
}

template<typename V, typename E>
void MatrixGraph<V, E>::insert_vertex(const V &vertex) {
    vertex_count += 1;
    V *new_vertices = new V[vertex_count];
    for (size_t i = 0; i < vertex_count - 1; ++i) {
        new_vertices[i] = _vertices[i];
    }
    new_vertices[vertex_count - 1] = vertex;
    delete[] _vertices;
    _vertices = new_vertices;

    auto **new_edges = new std::optional<E> *[vertex_count];
    for (size_t i = 0; i < vertex_count; ++i) {
        new_edges[i] = new std::optional<E>[vertex_count];
        for (size_t j = 0; j < vertex_count; ++j) {
            if (i < vertex_count - 1 && j < vertex_count - 1) {
                new_edges[i][j] = _edges[i][j];
            } else {
                new_edges[i][j] = std::nullopt; // 新增的行和列初始化为无边
            }
        }
    }
    for (size_t i = 0; i < vertex_count - 1; ++i) {
        delete[] _edges[i];
    }
    delete[] _edges;
    _edges = new_edges;
}

template<typename V, typename E>
void MatrixGraph<V, E>::remove_vertex(const V &vertex) {
    int vertex_index = -1;
    find_vertex_index(vertex, vertex_index);

    // 删除顶点
    V *new_vertices = new V[vertex_count - 1];
    for (size_t i = 0, j = 0; i < vertex_count; ++i) {
        if (static_cast<int>(i) != vertex_index) {
            new_vertices[j++] = _vertices[i];
        }
    }
    delete[] _vertices;
    _vertices = new_vertices;

    // 删除对应的行和列
    auto **new_edges = new std::optional<E> *[vertex_count - 1];
    for (size_t i = 0, new_i = 0; i < vertex_count; ++i) {
        // i 和 new_i 同步增加，除非 i 是被删除的行，被删除行之前 i 和 new_i 相同，之后 new_i 比 i 小 1
        if (static_cast<int>(i) == vertex_index) continue;
        new_edges[new_i] = new std::optional<E>[vertex_count - 1];
        for (size_t j = 0, new_j = 0; j < vertex_count; ++j) {
            if (static_cast<int>(j) == vertex_index) continue;
            new_edges[new_i][new_j++] = _edges[i][j];
        }
        new_i++;
    }
    for (size_t i = 0; i < vertex_count; ++i) {
        delete[] _edges[i];
    }
    delete[] _edges;
    _edges = new_edges;

    vertex_count -= 1;
}

template<typename V, typename E>
void MatrixGraph<V, E>::insert_edge(const V &v1, const V &v2, const E &edge) {
    int start_index = -1, end_index = -1;
    find_vertex_index(v1, start_index);
    find_vertex_index(v2, end_index);

    if (_edges[start_index][end_index].has_value()) {
        throw std::runtime_error("Edge already exists");
    }
    _edges[start_index][end_index] = edge;
    if (!has_direction) {
        _edges[end_index][start_index] = edge; // 无向
    }
}

template<typename V, typename E>
void MatrixGraph<V, E>::remove_edge(const V &v1, const V &v2) {
    int start_index = -1, end_index = -1;
    find_vertex_index(v1, start_index);
    find_vertex_index(v2, end_index);

    if (!_edges[start_index][end_index].has_value()) {
        throw std::runtime_error("Edge does not exist");
    }

    _edges[start_index][end_index] = std::nullopt;
    if (!has_direction) {
        _edges[end_index][start_index] = std::nullopt; // 无向
    }
}

template<typename V, typename E>
E MatrixGraph<V, E>::get_edge(const V &v1, const V &v2) const {
    int start_index = -1, end_index = -1;
    find_vertex_index(v1, start_index);
    find_vertex_index(v2, end_index);

    if (!_edges[start_index][end_index].has_value()) {
        throw std::runtime_error("Edge does not exist");
    }

    return _edges[start_index][end_index].value();
}

template<typename V, typename E>
void MatrixGraph<V, E>::set_edge(const V &v1, const V &v2, const E &edge) {
    int start_index = -1, end_index = -1;
    find_vertex_index(v1, start_index);
    find_vertex_index(v2, end_index);

    if (!_edges[start_index][end_index].has_value()) {
        throw std::runtime_error("Edge does not exist");
    }

    _edges[start_index][end_index] = edge;
    if (!has_direction) {
        _edges[end_index][start_index] = edge; // 无向
    }
}

// 时间复杂度为 O(V^2)
template<typename V, typename E>
void MatrixGraph<V, E>::bfs_dis_rec() const {
    if (vertex_count == 0) {
        return;
    }
    auto* queue = new SqQueue<int>("vertex_queue");
    auto *visited = new int[vertex_count];
    // 初始化 visited 数组
    for (size_t i = 0; i < vertex_count; ++i) {
        visited[i] = 0;
    }

    for (int i = 0; i < vertex_count; ++i) {
        if (!visited[i]) {
            // 该节点还没有被访问
            queue->enqueue(i);
            visited[i] = 1;
            while (!queue->empty()) {
                int current_index;
                queue->dequeue(current_index);
                std::cout << _vertices[current_index] << " ";
                visited[current_index] = 2;
                for (int j = 0; j < vertex_count; ++j) {
                    // 找到所有未被访问的邻接节点
                    if (_edges[current_index][j].has_value() && !visited[j]) {
                        queue->enqueue(j);
                        visited[j] = 1;
                    }
                }
            }
        }
    }
    std::cout << std::endl;

    delete[] visited;
    delete queue;
}

// 时间复杂度为 O(V^2)
template<typename V, typename E>
void MatrixGraph<V, E>::dfs_dis_rec() const {
    if (vertex_count == 0) {
        return;
    }
    auto* stack = new SqStack<int>("vertex_stack");
    // 0 表示未被访问、1 表示正在被访问、2 表示已经被访问
    auto *visited = new int[vertex_count];
    for (int i = 0; i < vertex_count; ++i) {
        visited[i] = 0; // 初始化所有节点为未访问
    }

    for (int i = 0; i < vertex_count; ++i) {
        if (!visited[i]) {
            stack->push(i);
            visited[i] = 1;
            while (!stack->empty()) {
                int current_index;
                stack->pop(current_index);
                std::cout << _vertices[current_index] << " ";
                visited[current_index] = 2;
                for (int j = 0; j < vertex_count; ++j) {
                    // 寻找没有被访问过的邻接点
                    if (_edges[current_index][j].has_value() && !visited[j]) {
                        stack->push(j);
                        visited[j] = 1;
                    }
                }
            }
        }
    }

    delete[] visited;
    delete stack;
}

template<typename V, typename E>
void MatrixGraph<V, E>::find_vertex_index(const V &vertex, int &index) const {
    index = -1;
    for (size_t i = 0; i < vertex_count; ++i) {
        if (_vertices[i] == vertex) {
            index = static_cast<int>(i);
            return;
        }
    }
    throw std::invalid_argument("Vertex not found");
}