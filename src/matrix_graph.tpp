//
// Created by LengTouZai on 2025/9/19.
//
#pragma once
#include <optional>
#include <iostream>
#include <stdexcept>

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
        for (size_t i = 0; i < vertex_count; ++i) {
            if (_vertices[i] == edge.first.first) {
                start_index = static_cast<int>(i);
            }
            if (_vertices[i] == edge.first.second) {
                end_index = static_cast<int>(i);
            }
        }
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
    for (size_t i = 0; i < vertex_count; ++i) {
        if (_vertices[i] == vertex) {
            vertex_index = static_cast<int>(i);
            break;
        }
    }

    if (vertex_index == -1) {
        throw std::invalid_argument("Vertex not found");
    }

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
    for (size_t i = 0; i < vertex_count; ++i) {
        if (_vertices[i] == vertex) {
            vertex_index = static_cast<int>(i);
            break;
        }
    }

    if (vertex_index == -1) {
        throw std::invalid_argument("Vertex not found");
    }

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
    if (has_direction)
        return get_in_degree(vertex) + get_out_degree(vertex);
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