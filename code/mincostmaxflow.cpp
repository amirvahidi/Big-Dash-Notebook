template <typename F, typename C, int MAXN, int MAXM> struct MinCostMaxFlow {
    struct Edge {
        int from, to;
        F cap;
        C cost;
    };
    Edge E[2 * MAXM];
    int m, par[MAXN], s, t;
    C dist[MAXN], cost = 0, pot[MAXN];
    F mn[MAXN], flow = 0;
    vector<int> adj[MAXN];
    MinCostMaxFlow() { memset(pot, 0, sizeof pot); }
    inline void add_edge(int u, int v, F cap, C cost) {
        adj[u].push_back(m);
        E[m++] = {u, v, cap, cost};
        adj[v].push_back(m);
        E[m++] = {v, u, 0, -cost};
    }
    inline void dijkstra() {
        fill(dist, dist + MAXN, numeric_limits<C>::max());
        fill(par, par + MAXN, -1);
        priority_queue<pair<C, int>, vector<pair<C, int>>, greater<pair<C, int>>> pq;
        dist[s] = 0;
        mn[s] = numeric_limits<F>::max();
        pq.push({dist[s], s});
        while (!pq.empty()) {
            int v = pq.top().Y;
            C d = pq.top().X;
            pq.pop();
            if (d != dist[v]) continue;
            for (int id : adj[v]) {
                int u = E[id].to;
                if (!E[id].cap) continue;
                C d_u = d + pot[v] - pot[u] + E[id].cost;
                if (d_u < dist[u]) {
                    dist[u] = d_u;
                    pq.push({d_u, u});
                    par[u] = id;
                    mn[u] = min(mn[v], E[id].cap);
                }
            }
        }
    }
    inline F solve() {
        dijkstra();
        if (par[t] == -1) return 0;
        F c = min(mn[t], flow), v = t;
        flow -= c;
        cost += c * (dist[t] + pot[t]);
        while (v != s) {
            int id = par[v];
            E[id].cap -= c;
            E[id ^ 1].cap += c;
            v = E[id].from;
        }
        for (int v = 0; v < MAXN; v++)
            if (par[v] != -1)
                pot[v] += dist[v];
        return c;
    }
    inline C min_cost(int _s, int _t, F _flow) {
        s = _s, t = _t, flow = _flow;
        while (true) {
            F c = solve();
            if (c == 0)
                break;
        }
        return cost;
    }
};
