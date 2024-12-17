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
