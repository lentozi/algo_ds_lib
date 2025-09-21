//
// Created by LengTouZai on 2025/9/19.
//
#pragma once
#include <string>
#include <vector>

template<typename V, typename E>
class GraphStructure {
protected:
    std::string name = "graph_structure";

    virtual void print() const = 0;

public:
    explicit GraphStructure(std::string name) : name(std::move(name)) {}

    virtual ~GraphStructure() = default;

    virtual void build_graph(const std::vector<V> &vertices, const std::vector<std::pair<std::pair<V, V>, E>> &edges) = 0;

    virtual int get_degree(const V &vertex) const = 0;
    virtual int get_in_degree(const V &vertex) const = 0;
    virtual int get_out_degree(const V &vertex) const = 0;

    virtual bool adjacent(const V &v1, const V &v2) const = 0;
    virtual std::set<V> neighbors(const V &vertex) const = 0;

    virtual void insert_vertex(const V &vertex) = 0;
    virtual void remove_vertex(const V &vertex) = 0;
    virtual void insert_edge(const V &v1, const V &v2, const E &edge) = 0;
    virtual void remove_edge(const V &v1, const V &v2) = 0;

    virtual E get_edge(const V &v1, const V &v2) const = 0;
    virtual void set_edge(const V &v1, const V &v2, const E &edge) = 0;
};

#include "graph/matrix_graph.h"
#include "graph/adjacency_list_graph.h"
