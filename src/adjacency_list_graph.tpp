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
        find_vertex(start_vertex, start_index);
        find_vertex(end_vertex, end_index);

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
    find_vertex(vertex, vertex_index);

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

template<typename V, typename E>
bool AdjacencyList<V, E>::adjacent(const V &v1, const V &v2) const {
    int start_index = -1, end_index = -1;
    find_vertex(v1, start_index);
    find_vertex(v2, end_index);
    auto* arc = vertex_table->at(start_index).first_arc;
    while (arc) {
        if (arc->adjvex == end_index) {
            return true;
        }
    }
    return false;
}

template<typename V, typename E>
std::set<V> AdjacencyList<V, E>::neighbors(const V &vertex) const {
    int start_index = -1;
    find_vertex(vertex, start_index);
    std::set<V> result;
    auto* arc = vertex_table->at(start_index).first_arc;
    while (arc) {
        result.insert(vertex_table->at(arc->adjvex).data);
        arc = arc->next;
    }

    if (has_direction) {
        for (int i = 0; i < vertex_count; ++i) {
            if (i == start_index) continue;
            auto* _arc = vertex_table->at(i).first_arc;
            while (_arc) {
                if (_arc->adjvex == start_index) {
                    result.insert(vertex_table->at(i).data);
                    break;
                }
                _arc = _arc->next;
            }
        }
    }
    return result;
}

template<typename V, typename E>
void AdjacencyList<V, E>::insert_vertex(const V &vertex) {
    // 检查顶点是否存在
    for (int i = 0; i < vertex_count; ++i) {
        if (vertex_table->at(i).data == vertex) {
            throw std::runtime_error("Vertex already exists");
        }
    }

    VNode<V, E> vnode(vertex);
    (*vertex_table)[vertex_count] = vnode;
    vertex_count++;
}

template<typename V, typename E>
void AdjacencyList<V, E>::remove_vertex(const V &vertex) {
    int vertex_index = -1;
    find_vertex(vertex, vertex_index);

    // 删除该顶点的所有出边
    auto* arc = vertex_table->at(vertex_index).first_arc;
    while (arc) {
        auto* temp = arc;
        arc = arc->next;
        delete temp;
        edge_count--;
    }
    (*vertex_table)[vertex_index].first_arc = nullptr;

    // 删除该顶点的所有入边
    for (int i = 0; i < vertex_count; ++i) {
        if (i == vertex_index) continue;
        auto* _arc = vertex_table->at(i).first_arc;
        ArcNode<int, E>* prev = nullptr;
        while (_arc) {
            if (_arc->adjvex == vertex_index) {
                // 删除该弧节点
                if (prev) {
                    prev->next = _arc->next;
                } else {
                    (*vertex_table)[i].first_arc = _arc->next;
                }
                auto* temp = _arc;
                _arc = _arc->next;
                delete temp;
                edge_count--;
            } else {
                prev = _arc;
                _arc = _arc->next;
            }
        }
    }

    // 删除顶点
    for (int i = vertex_index; i < vertex_count - 1; ++i) {
        (*vertex_table)[i] = (*vertex_table)[i + 1];
        // 更新弧节点的邻接点索引
        auto* _arc = vertex_table->at(i).first_arc;
        while (_arc) {
            if (_arc->adjvex > vertex_index) {
                _arc->adjvex -= 1;
            }
            _arc = _arc->next;
        }
    }
    vertex_count--;
}

template<typename V, typename E>
void AdjacencyList<V, E>::insert_edge(const V &v1, const V &v2, const E &edge) {
    int start_index = -1, end_index = -1;
    find_vertex(v1, start_index);
    find_vertex(v2, end_index);

    // 检查边是否存在
    auto* arc = vertex_table->at(start_index).first_arc;
    while (arc) {
        if (arc->adjvex == end_index) {
            throw std::runtime_error("Edge already exists");
        }
        arc = arc->next;
    }

    // 插入弧节点到起始节点的弧链表头部
    auto* new_arc = new ArcNode<int, E>(end_index, edge);
    new_arc->next = vertex_table->at(start_index).first_arc;
    (*vertex_table)[start_index].first_arc = new_arc;
    edge_count++;

    if (!has_direction) {
        auto* reverse_arc = new ArcNode<int, E>(start_index, edge);
        reverse_arc->next = vertex_table->at(end_index).first_arc;
        (*vertex_table)[end_index].first_arc = reverse_arc;
        edge_count++;
    }
}

template<typename V, typename E>
void AdjacencyList<V, E>::remove_edge(const V &v1, const V &v2) {
    int start_index = -1, end_index = -1;
    find_vertex(v1, start_index);
    find_vertex(v2, end_index);
    // 删除起始节点的弧链表中的对应弧节点
    auto* prev =  vertex_table->at(start_index).first_arc;
    auto* arc = prev->next;
    if (!prev) {
        throw std::runtime_error("Edge not found");
    }
    while (arc) {
        prev = arc;
        arc = arc->next;
        if (arc->adjvex == end_index) {
            prev->next = arc->next;
            delete arc;
            break;
        }
    }

    if (!has_direction) {
        prev = vertex_table->at(end_index).first_arc;
        arc = prev->next;
        if (!prev) {
            throw std::runtime_error("Edge not found");
        }
        while (arc) {
            prev = arc;
            arc = arc->next;
            if (arc->adjvex == start_index) {
                prev->next = arc->next;
                delete arc;
                break;
            }
        }
    }
    edge_count--;
}

template<typename V, typename E>
E AdjacencyList<V, E>::get_edge(const V &v1, const V &v2) const {
    int start_index = -1, end_index = -1;
    find_vertex(v1, start_index);
    find_vertex(v2, end_index);

    auto* arc = vertex_table->at(start_index).first_arc;
    while (arc) {
        if (arc->adjvex == end_index) {
            return arc->value;
        }
        arc = arc->next;
    }
    throw std::runtime_error("Edge not found");
}

template<typename V, typename E>
void AdjacencyList<V, E>::set_edge(const V &v1, const V &v2, const E &edge) {
    int start_index = -1, end_index = -1;
    find_vertex(v1, start_index);
    find_vertex(v2, end_index);

    auto* arc = vertex_table->at(start_index).first_arc;
    while (arc) {
        if (arc->adjvex == end_index) {
            arc->value = edge;
            return;
        }
        arc = arc->next;
    }
    throw std::runtime_error("Edge not found");
}


template<typename V, typename E>
void AdjacencyList<V, E>::find_vertex(const V &vertex, int &index) const {
    index = -1;
    for (int i = 0; i < vertex_count; ++i) {
        if (vertex_table->at(i).data == vertex) {
            index = i;
            return;
        }
    }
    throw std::invalid_argument("Vertex not found");
}