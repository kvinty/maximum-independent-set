char is_folding(int u) {
    int degree_u = get_degree(u, graph);

    if (degree_u == 2) {
        return 1;
    } else if (degree_u == 3 || degree_u == 4) {
        int *adj_u = graph->adjacency[u];
        for (int i = 0; i < graph->adj_size[u]; i++) {
            int x = adj_u[i];

            if (OUT & graph->mark[x])
                continue;

            for (int j = i + 1; j < graph->adj_size[u]; j++) {
                int y = adj_u[j];

                if (OUT & graph->mark[y])
                    continue;

                if (are_connected(x, y, graph))
                    continue;

                for (int k = j + 1; k < graph->adj_size[u]; k++) {
                    int z = adj_u[k];

                    if (OUT & graph->mark[z])
                        continue;

                    if (are_connected(x, z, graph) || are_connected(y, z, graph))
                        continue;

                    return 0;
                }
            }
        }
        return 1;
    } else {
        return 0;
    }
}

void fold(int v) {
    int old_size = graph->size;

    int *adj_v = graph->adjacency[v];

    for (int i = 0; i < graph->adj_size[v]; i++) {
        int x = adj_v[i];

        if (OUT & graph->mark[x])
            continue;

        graph->mark[x] |= OUT;
        graph->mark[x] |= MARKED;
        push(x, deleted);
    }
    graph->mark[v] |= OUT;
    graph->mark[v] |= MARKED;
    push(v, deleted);

    for (int i = 0; i < graph->adj_size[v]; i++) {
        int x = adj_v[i];

        if (!(MARKED & graph->mark[x]))
            continue;

        for (int j = i + 1; j < graph->adj_size[v]; j++) {
            int y = adj_v[j];

            if (!(MARKED & graph->mark[y]))
                continue;

            if (!are_connected(x, y, graph))
                add_tild(v, x, y);
        }
    }

    for (int i = old_size; i < graph->size; i++) {
        for (int j = i + 1; j < graph->size; j++) {
            add_edge(i, j, graph);
        }
    }

    for (int i = 0; i < graph->adj_size[v]; i++) {
        int x = adj_v[i];
        graph->mark[x] |= MARKED;
        graph->mark[x] ^= MARKED;
    }
    graph->mark[v] ^= MARKED;
}

void add_tild(int v, int x, int y) {
    int xy_tild = add_vertex(graph);
    graph->v[xy_tild] = v;
    graph->x[xy_tild] = x;
    graph->y[xy_tild] = y;

    int *adj_x = graph->adjacency[x];
    int *adj_y = graph->adjacency[y];

    for (int i = 0; i < graph->adj_size[x]; i++) {
        int z = adj_x[i];

        if (OUT & graph->mark[z])
            continue;

        add_edge(z, xy_tild, graph);
        graph->mark[z] |= MARKED;
    }

    for (int j = 0; j < graph->adj_size[y]; j++) {
        int z = adj_y[j];

        if ((OUT & graph->mark[z]) || (MARKED & graph->mark[z]))
            continue;

        add_edge(z, xy_tild, graph);
    }

    int *adj_xy_tild = graph->adjacency[xy_tild];

    for (int k = 0; k < graph->adj_size[xy_tild]; k++) {
        int z = adj_xy_tild[k];
        graph->mark[z] |= MARKED;
        graph->mark[z] ^= MARKED;
        if (TO_CHECK & graph->mark[z])
            continue;
        graph->mark[z] |= TO_CHECK;
        push(z, pile);
    }
    graph->mark[xy_tild] |= TO_CHECK;
    push(xy_tild, pile);
}

void unfold(int v, int mem) {
    while (deleted->size != mem)
        graph->mark[pop(deleted)] ^= OUT;

    int new_size = graph->size;
    while (new_size - 1 >= 0 && graph->v[new_size - 1] == v) {
        new_size--;
        int *adj = graph->adjacency[new_size];
        for (int i = 0; i < graph->adj_size[new_size]; i++)
            graph->adj_size[adj[i]]--;
    }

    graph->size = new_size;
}
