template <int MAXN, int MAXM, typename T> // NOT TESTED
struct Dinic {
    int dist[MAXN], ptr[MAXN], m, from[MAXM << 2], to[MAXM << 2];
    T cap[MAXM << 2], f[MAXM << 2];
    vector<int> adj[MAXN];
      Dinic() {}
      int add_edge(int u, int v, T c) {
        cap[m] = c;
        from[m] = u, to[m] = v;
        adj[u].push_back(m);
        m++;
          cap[m] = 0;
        from[m] = v, to[m] = u;
        adj[v].push_back(m);
        m++;

        return m - 2;
    }
      void BFS(int v) {
        memset(ptr, 0, sizeof ptr);
        memset(dist, 63, sizeof dist);
          queue<int> q;
        q.push(v);
        dist[v] = 0;
        while (!q.empty()) {
            v = q.front();
            q.pop();
              for (int ind : adj[v]) {
                int u = from[ind] ^ to[ind] ^ v;
                if (cap[ind] && dist[u] > dist[v] + 1) {
                    dist[u] = dist[v] + 1;
                    q.push(u);
                }
            }
        }
    }

    T dfs(int v, int t, T max_cap) {
        if (v == t)
            return max_cap;

        T ans = 0;
        while (ptr[v] < int(adj[v].size())) {
            int ind = adj[v][ptr[v]++];
            int u = from[ind] ^ to[ind] ^ v;
            if (dist[u] != dist[v] + 1 || !cap[ind])
                continue;
              T tmp = dfs(u, t, min(max_cap, cap[ind]));
            max_cap -= tmp;
            cap[ind] -= tmp, cap[ind ^ 1] += tmp;
            ans += tmp;
              if (max_cap == 0) break;
        }
          return ans;
    }
      T max_flow(int s, int t) {
        ll ans = 0;
        while (true) {
            BFS(s);
            if (dist[t] > MAXN + 5)
                break;
            ans += dfs(s, t, numeric_limits<T>::max());
        }
          return ans;
    }
};

// O(n ^ 2 * m)
// tested on: https://cses.fi/problemset/result/3308880/
// TODO: fix pointers!

template <typename T, int MAXN, int MAXM> struct Flow { // O(n^2 * m)
    int m = 0, dist[MAXN], from[MAXM << 1], to[MAXM << 1];
    T cap[MAXM << 1];
    vector<int> adj[MAXN];

    Flow() {}

    inline void add_edge(int u, int v, T c) {
        adj[u].push_back(m);
        from[m] = u;
        to[m] = v;
        cap[m++] = c;

        adj[v].push_back(m);
        from[m] = v;
        to[m] = u;
        cap[m++] = 0;
    }

    inline bool BFS(int source, int sink) {
        memset(dist, 63, sizeof dist);
        dist[source] = 0;

        queue<int> q;
        q.push(source);
        while (!q.empty()) {
            int v = q.front();
            q.pop();

            int d = dist[v] + 1;
            for (int id : adj[v]) {
                int u = to[id];
                if (cap[id] && dist[u] > d) {
                    dist[u] = d;
                    q.push(u);
                }
            }
        }

        return dist[sink] < MAXN;
    }

    T dfs(int v, int sink, T flow) {
        if (!flow || v == sink)
            return flow;

        T ans = 0;
        for (int id : adj[v]) {
            int u = to[id];
            if (dist[u] == dist[v] + 1 && cap[id]) {
                T flow_e = dfs(u, sink, min(flow - ans, cap[id]));
                ans += flow_e;
                cap[id] -= flow_e;
                cap[id ^ 1] += flow_e;
            }
        }

        return ans;
    }

    T max_flow(int source, int sink) {
        T ans = 0;
        while (BFS(source, sink))
            ans += dfs(source, sink, numeric_limits<T>::max());

        return ans;
    }
};

// O(max_flow * m))
// tested on: gym103439E
template <typename T, int MAXN, int MAXM> struct Flow { // O(max_flow * m))
    int m = 0, vis[MAXN], from[MAXM << 1], to[MAXM << 1];
    T cap[MAXM << 1], f, x;
    vector<int> adj[MAXN];

    Flow() {}

    inline void add_edge(int u, int v, T c) {
        adj[u].push_back(m);
        from[m] = u;
        to[m] = v;
        cap[m++] = c;

        adj[v].push_back(m);
        from[m] = v;
        to[m] = u;
        cap[m++] = 0;
    }

    bool dfs(int v, int sink) {
        if (v == sink)
            return true;

        vis[v] = x;
        for (int id : adj[v]) {
            int u = to[id];
            if (cap[id] && vis[u] != x && dfs(u, sink)) {
                cap[id] -= 1;
                cap[id ^ 1] += 1;
                return true;
            }
        }

        return false;
    }

    inline T max_flow(int s, int t) {
        x++;
        while (dfs(s, t))
            f++, x++;
        return f;
    }
};

// O(max_flow * nm) ?????
// tested on: 362E
// TODO: time complexity

template <typename F, typename C, int MAXN, int MAXM> struct MinCostMaxFlow {
    struct Edge {
        int from, to;
        F cap;
        C cost;
    };

    Edge E[2 * MAXM];
    int m, par[MAXN], s, t;
    C dist[MAXN], k;
    F mn[MAXN];
    vector<int> adj[MAXN];

    inline void add_edge(int u, int v, F cap, C cost) {
        adj[u].push_back(m);
        E[m++] = {u, v, cap, cost};
        adj[v].push_back(m);
        E[m++] = {v, u, 0, -cost};
    }

    inline void SPFA() {
        fill(dist, dist + MAXN, numeric_limits<C>::max());
        fill(par, par + MAXN, -1);
        queue<int> q;

        dist[s] = 0;
        q.push(s);
        mn[s] = numeric_limits<F>::max();

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int id : adj[v]) {
                int u = E[id].to;
                if (!E[id].cap)
                    continue;

                if (dist[u] > dist[v] + E[id].cost) {
                    dist[u] = dist[v] + E[id].cost;
                    q.push(u);
                    par[u] = id;
                    mn[u] = min(mn[v], E[id].cap);
                }
            }
        }
    }

    inline F solve() {
        SPFA();

        if (dist[t] > k)
            return 0;
        F c = min(mn[t], dist[t] == 0 ? mn[t] : k / dist[t]), v = t;
        k -= dist[t] * c;

        while (v != s) {
            int id = par[v];
            E[id].cap -= c;
            E[id ^ 1].cap += c;
            v = E[id].from;
        }

        return c;
    }

    inline F max_flow(int _s, int _t, C _k) {
        s = _s, t = _t, k = _k;
        F ans = 0;

        while (true) {
            F c = solve();
            if (c)
                ans += c;
            else
                return ans;
        }
    }
};

// MinCostMaxFlow + Johnson algorithm(dijkstra instead of spfa)
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
        priority_queue<pair<C, int>, vector<pair<C, int>>,
                       greater<pair<C, int>>>
            pq;

        dist[s] = 0;
        mn[s] = numeric_limits<F>::max();
        pq.push({dist[s], s});

        while (!pq.empty()) {
            int v = pq.top().Y;
            C d = pq.top().X;
            pq.pop();
            if (d != dist[v])
                continue;

            for (int id : adj[v]) {
                int u = E[id].to;
                if (!E[id].cap)
                    continue;
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

        if (par[t] == -1)
            return 0;
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
    is

        inline C
        min_cost(int _s, int _t, F _flow) {
        s = _s, t = _t, flow = _flow;
        while (true) {
            F c = solve();
            if (c == 0)
                break;
        }

        return cost;
    }
};
// TODO: LR Flow
// TODO: Flow with capacity scaling
