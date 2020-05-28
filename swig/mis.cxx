#include "mis.hxx"

std::vector<int> solve(int n, std::vector<std::array<int, 2>> edges) {
    Graph *graph = init_graph(n);
    for (const auto &pair : edges) {
        add_edge(pair[0], pair[1], graph);
    }
    Array *independent_set = mis(graph);
    free_graph(graph);
    sort_array(independent_set);
    std::vector<int> result;
    for (int i = 0; i != independent_set->size; ++i) {
        result.push_back(independent_set->t[i]);
    }
    free_array(independent_set);
    return result;
}
