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
};

#include "graph/matrix_graph.h"
#include "graph/adjacency_list.h"