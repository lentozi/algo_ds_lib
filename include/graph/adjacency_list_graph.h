//
// Created by LengTouZai on 2025/9/20.
//
#pragma once
#include "utils/expand_list.h"
#include "node/graph_node.h"

template<typename V, typename E>
class AdjacencyList final : public GraphStructure<V, E> {
    // TODO 用哈希表优化
    ExpandList<VNode<V, E>>* vertex_table;
    size_t vertex_count = 0; // 顶点数量
    size_t edge_count = 0; // 边数量
    bool has_direction;

    void print() const override;

public:
    explicit AdjacencyList(std::string name, bool has_direction = false);
    ~AdjacencyList() override;

    void build_graph(const std::vector<V> &vertices, const std::vector<std::pair<std::pair<V, V>, E>> &edges) override;
    int get_degree(const V &vertex) const override;
    int get_in_degree(const V &vertex) const override;
    int get_out_degree(const V &vertex) const override;
};

#include "adjacency_list_graph.tpp"
