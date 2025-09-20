//
// Created by LengTouZai on 2025/9/19.
//
// 无向图
#pragma once
#include <optional>
#include <string>

template<typename V, typename E>
class MatrixGraph final : public GraphStructure<V, E> {
    bool has_direction = false; // 是否有向图
    V *_vertices = nullptr; // 顶点数组
    std::optional<E> **_edges = nullptr; // 邻接矩阵
    size_t vertex_count = 0; // 顶点数量
    size_t edge_count = 0; // 边数量

    void print() const override;

public:
    explicit MatrixGraph(std::string name, bool has_direction = false);

    ~MatrixGraph() override;

    void build_graph(const std::vector<V> &vertices, const std::vector<std::pair<std::pair<V, V>, E>> &edges) override;

    int get_degree(const V &vertex) const override;

    int get_in_degree(const V &vertex) const override;
    int get_out_degree(const V &vertex) const override;
};


#include "matrix_graph.tpp"
