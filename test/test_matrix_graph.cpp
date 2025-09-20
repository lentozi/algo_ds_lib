//
// Created by LengTouZai on 2025/9/19.
//
#include <string>

#include "gtest/gtest.h"
#include "base/graph_structure.h"

TEST(MatrixGraphTest, BasicOperations) {
    auto* graph = new MatrixGraph<std::string, int>("TestGraph", true);

    const std::vector<std::string> vertices = {"A", "B", "C"};
    const std::vector<std::pair<std::pair<std::string, std::string>, int>> edges = {
        {{"A", "B"}, 5},
        {{"B", "C"}, 10}
    };

    graph->build_graph(vertices, edges);

    EXPECT_EQ(graph->get_in_degree("B"), 1);
    EXPECT_EQ(graph->get_out_degree("B"), 1);
    EXPECT_EQ(graph->get_in_degree("A"), 0);
    EXPECT_EQ(graph->get_out_degree("A"), 1);
    EXPECT_EQ(graph->get_in_degree("C"), 1);
    EXPECT_EQ(graph->get_out_degree("C"), 0);

    delete graph;
}