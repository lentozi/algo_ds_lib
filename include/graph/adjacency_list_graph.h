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

    void find_vertex(const V &vertex, int &index) const;

public:
    explicit AdjacencyList(std::string name, bool has_direction = false);
    ~AdjacencyList() override;

    void build_graph(const std::vector<V> &vertices, const std::vector<std::pair<std::pair<V, V>, E>> &edges) override;
    int get_degree(const V &vertex) const override;
    int get_in_degree(const V &vertex) const override;
    int get_out_degree(const V &vertex) const override;

    bool adjacent(const V &v1, const V &v2) const override;
    std::set<V> neighbors(const V &vertex) const override;

    void insert_vertex(const V &vertex) override;
    void remove_vertex(const V &vertex) override;
    void insert_edge(const V &v1, const V &v2, const E &edge) override;
    void remove_edge(const V &v1, const V &v2) override;

    E get_edge(const V &v1, const V &v2) const override;
    void set_edge(const V &v1, const V &v2, const E &edge) override;

    // 广度优先遍历的非递归实现
    void bfs_dis_rec() const;
    // 深度优先遍历的非递归实现
    void dfs_dis_rec() const;
};

#include "adjacency_list_graph.tpp"
