//
// Created by LengTouZai on 2025/9/20.
//
#include <string>

#include "gtest/gtest.h"
#include "base/graph_structure.h"

TEST(AdjacencyListGraphTest, BasicOperations) {
    const std::vector<std::string> vertices = {"A", "B", "C"};
    const std::vector<std::pair<std::pair<std::string, std::string>, int>> edges = {
        {{"A", "B"}, 5},
        {{"B", "C"}, 10}
    };

    // 有向图
    auto* graph = new AdjacencyList<std::string, int>("TestGraph", true);

    graph->build_graph(vertices, edges);

    EXPECT_EQ(graph->get_in_degree("B"), 1);
    EXPECT_EQ(graph->get_out_degree("B"), 1);
    EXPECT_EQ(graph->get_in_degree("A"), 0);
    EXPECT_EQ(graph->get_out_degree("A"), 1);
    EXPECT_EQ(graph->get_in_degree("C"), 1);
    EXPECT_EQ(graph->get_out_degree("C"), 0);

    delete graph;

    // 无向图
    graph = new AdjacencyList<std::string, int>("TestGraph", false);

    graph->build_graph(vertices, edges);

    EXPECT_EQ(graph->get_in_degree("B"), 2);
    EXPECT_EQ(graph->get_out_degree("B"), 2);
    EXPECT_EQ(graph->get_in_degree("A"), 1);
    EXPECT_EQ(graph->get_out_degree("A"), 1);
    EXPECT_EQ(graph->get_in_degree("C"), 1);
    EXPECT_EQ(graph->get_out_degree("C"), 1);

    delete graph;
}