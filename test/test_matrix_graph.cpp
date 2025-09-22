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

    // 测试添加和删除
    graph->insert_vertex("D");
    graph->insert_edge("C", "D", 15);
    EXPECT_EQ(graph->get_in_degree("D"), 1);
    EXPECT_EQ(graph->get_out_degree("C"), 1);

    // 测试 BFS
    graph->insert_edge("A", "D", 15);
    graph->insert_vertex("E");
    graph->insert_edge("C", "E", 10);
    graph->bfs_dis_rec();

    // 测试 DFS
    graph->insert_vertex("F");
    graph->insert_edge("E", "F", 10);
    graph->dfs_dis_rec();

    delete graph;
}