//
// Created by LengTouZai on 2025/9/20.
//
#pragma once

template<typename V, typename E>
AdjacencyList<V, E>::AdjacencyList(std::string name, bool has_direction)
    : GraphStructure<V, E>(name), vertex_table(nullptr), has_direction(has_direction) {
}

template<typename V, typename E>
AdjacencyList<V, E>::~AdjacencyList() {
    if (vertex_table) {
        for (int i = 0; i < vertex_count; ++i) {
            auto& vnode = vertex_table->at(i);
            auto* arc = vnode.first_arc;
            while (arc) {
                auto* temp = arc;
                arc = arc->next;
                delete temp;
            }
        }
        delete vertex_table;
        vertex_table = nullptr;
    }
}

template<typename V, typename E>
void AdjacencyList<V, E>::build_graph(const std::vector<V> &vertices, const std::vector<std::pair<std::pair<V, V>, E> > &edges) {
    vertex_count = vertices.size();
    edge_count = edges.size();

    // 初始化顶点表
    vertex_table = new ExpandList<VNode<V, E>>(vertex_count);
    for (int i = 0; i < vertices.size(); ++i) {
        VNode<V, E> vnode(vertices[i]);
        (*vertex_table)[i] = vnode;
    }

    // 初始化边表
    for (const auto& edge : edges) {
        const V& start_vertex = edge.first.first;
        const V& end_vertex = edge.first.second;
        const E& edge_value = edge.second;

        // 查找起始节点和终止节点的索引
        int start_index = -1, end_index = -1;
        for (size_t i = 0; i < vertex_count; ++i) {
            if (vertex_table->at(i).data == start_vertex) {
                start_index = static_cast<int>(i);
            }
            if (vertex_table->at(i).data == end_vertex) {
                end_index = static_cast<int>(i);
            }
        }

        if (start_index == -1 || end_index == -1) {
            throw std::invalid_argument("Vertex not found");
        }

        // 插入弧节点到起始节点的弧链表头部
        auto* new_arc = new ArcNode<int, E>(end_index, edge_value);
        new_arc->next = vertex_table->at(start_index).first_arc;
        (*vertex_table)[start_index].first_arc = new_arc;

        if (!has_direction) {
            auto* reverse_arc = new ArcNode<int, E>(start_index, edge_value);
            reverse_arc->next = vertex_table->at(end_index).first_arc;
            (*vertex_table)[end_index].first_arc = reverse_arc;
        }
    }
}

template<typename V, typename E>
int AdjacencyList<V, E>::get_in_degree(const V &vertex) const {
    // 查找顶点所在位置
    int vertex_index = -1;
    for (int i = 0; i < vertex_count; ++i) {
        if (vertex_table->at(i).data == vertex) {
            vertex_index = i;
            break;
        }
    }
    if (vertex_index == -1) {
        throw std::invalid_argument("Vertex not found");
    }

    int degree = 0;
    for (int i = 0; i < vertex_count; ++i) {
        // 跳过自身顶点
        if (vertex_table->at(i).data == vertex) {
            continue;
        }
        // 对其他顶点遍历边表
        auto* arc = vertex_table->at(i).first_arc;
        while (arc) {
            if (arc->adjvex == vertex_index) {
                degree++;
            }
            arc = arc->next;
        }
    }
    return degree;
}

template<typename V, typename E>
int AdjacencyList<V, E>::get_out_degree(const V &vertex) const {
    int degree = 0;
    for (int i = 0; i < vertex_count; ++i) {
        // 找到该顶点即可
        if (vertex_table->at(i).data == vertex) {
            auto* arc = vertex_table->at(i).first_arc;
            while (arc) {
                degree++;
                arc = arc->next;
            }
            break;
        }
    }
    return degree;
}

template<typename V, typename E>
int AdjacencyList<V, E>::get_degree(const V &vertex) const {
    if (has_direction) {
        return get_in_degree(vertex) + get_out_degree(vertex);
    }
    return get_out_degree(vertex); // 无向图入度等于出度
}

template<typename V, typename E>
void AdjacencyList<V, E>::print() const {
    std::cout << "AdjacencyList: " << this->name << std::endl;
    for (int i = 0; i < vertex_count; ++i) {
        const auto& vnode = vertex_table->at(i);
        std::cout << vnode << ": ";
        auto* arc = vnode.first_arc;
        while (arc) {
            std::cout << arc << " ";
            arc = arc->next;
        }
        std::cout << std::endl;
    }
}
