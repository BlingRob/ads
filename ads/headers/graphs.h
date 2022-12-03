// \\\ file graphs.h
// \\\ There will be graph theory's functions 
#pragma once
#include <vector>
#include <tuple>

namespace ads
{
    namespace structures
    {
        namespace graphs
        {
            template<bool directed = false>
            class adjece_matrix
            {
            public:

                using MatrIT = typename std::vector<bool>::const_iterator;

                adjece_matrix(std::size_t verts = 0)
                {
                    matrix.resize(verts, std::vector<bool>(verts));
                }

                void add_vertex(size_t x)
                {
                    if (matrix.size() < x)
                        matrix.resize(x);
                }

                void add_edge(size_t v1, size_t v2, uint32_t weight = 1)
                {
                    add_vertex(v1);
                    add_vertex(v2);

                    matrix[v1][v2] = weight;
                    if (!directed)
                        matrix[v2][v1] = weight;
                }

                std::pair<MatrIT, MatrIT> get_vertex_edges(std::size_t v)
                {
                    if (v < matrix.size())
                        return { matrix[v].cbegin(),matrix[v].cend() };
                    else
                    {
                        add_vertex(v);
                        return { matrix[v].cbegin(),matrix[v].cend() };
                    }
                }

            private:
                std::vector<std::vector<bool>> matrix;
            };

            template<bool directed = false>
            class adjece_list
            {
                struct node;
            public:

                adjece_list(std::size_t verts = 0)
                {
                    list.resize(verts);
                }

                using listIt = typename std::list<node>::const_iterator;
                void add_vertex(size_t x)
                {
                    if (list.size() < x)
                        list.resize(x);
                }

                void add_edge(size_t v1, size_t v2, int32_t weight = 1)
                {
                    add_vertex(v1);
                    add_vertex(v2);

                    list[v1].push_front({ v2,weight });
                    if (!directed)
                        list[v2].push_front({ v1,weight });
                }

                void del_edge(size_t v1, size_t v2, int32_t weight = 1)
                {
                    list[v1].erase(std::find_if(list[v1].begin(), list[v1].end(), [&v2, &weight](const node& n) {return v2 == n.vertex && weight == n.weight; }));
                    if (!directed)
                        list[v2].erase(std::find_if(list[v2].begin(), list[v2].end(), [&v1, &weight](const node& n) {return v1 == n.vertex && weight == n.weight; }));
                }

                void del_vertex(size_t v)
                {
                    auto [start, end] = get_vertex_edges(v);
                    for (; start != end; ++start)
                        del_edge(v, start->vertex);

                    if (directed)
                        for (auto& vertex : list)
                            vertex.erase(std::find_if(vertex.begin(), vertex.end(), [&v](const node& n) {return v == n.vertex; }));

                }

                std::pair<listIt, listIt> get_vertex_edges(std::size_t v)
                {
                    if (v < list.size())
                        return { list[v].cbegin(),list[v].cend() };
                    else
                    {
                        add_vertex(v);
                        return { list[v].cbegin(),list[v].cend() };
                    }
                }

            private:
                struct node
                {
                    size_t vertex;
                    int32_t weight;
                };

                std::vector<std::list<node>> list;

            };

            template<bool directed = false, typename graph_saver = adjece_matrix<directed>>
            class graph
            {
            public:
                graph(std::size_t verts = 0) :
                    nverts(verts), nedges(0), _graph(verts) {}

                void add_vertex(size_t x)
                {
                    _graph.add_vertex(x);
                }

                void add_edge(size_t v1, size_t v2, uint32_t weight = 1)
                {
                    _graph.add_edge(v1, v2, weight);
                }

                void del_edge(size_t v1, size_t v2, uint32_t weight = 1)
                {
                    _graph.del_edge(v1, v2, weight);
                }

                void del_vertex(size_t v)
                {
                    _graph.del_vertex(v);
                }

                void print()
                {
                    for (size_t i = 0; i < nverts; ++i)
                    {
                        auto [start, finish] = _graph.get_vertex_edges(i);
                        for (; start != finish; ++start)
                            if constexpr (std::is_same<graph_saver, adjece_matrix<directed>>::value)
                                std::cout << *start << " ";
                            else
                                std::cout << "(" << i << ";" << start->weight << ";" << start->vertex << ") ";

                        std::cout << "\n";
                    }
                }

            private:
                std::size_t nverts;
                std::size_t nedges;

                graph_saver _graph;
            };
        }
    }
}