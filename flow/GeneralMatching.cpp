struct GeneralMatching {
  int n;
  vector<vector<int>> adj;
  vector<int> match;
  GeneralMatching(int n) : n(n), adj(n), match(n, -1) {}
  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  int maxMatching() {
    vector<int> vis(n), link(n), f(n), dep(n);
    auto find = [&](int u) { 
      while (f[u] != u) { u = f[u] = f[f[u]]; }
      return u;
    };
    auto lca = [&](int u, int v) {
      u = find(u);
      v = find(v);
      while (u != v) {
        if (dep[u] < dep[v]) { swap(u, v); }
        u = find(link[match[u]]);
      }
      return u;
    };
    queue<int> q;
    auto blossom = [&](int u, int v, int p) {
      while (find(u) != p) {
        link[u] = v;
        v = match[u];
        if (vis[v] == 0) {
          vis[v] = 1;
          q.push(v);
        }
        f[u] = f[v] = p;
        u = link[v];
      }
    };
    auto augment = [&](int u) {
      while (!q.empty()) { q.pop(); }
      iota(f.begin(), f.end(), 0);
      fill(vis.begin(), vis.end(), -1);
      q.push(u), vis[u] = 1, dep[u] = 0;
      while (!q.empty()){
        int u = q.front();
        q.pop();
        for (auto v : adj[u]) {
          if (vis[v] == -1) {
            vis[v] = 0;
            link[v] = u;
            dep[v] = dep[u] + 1;
            if (match[v] == -1) {
              for (int x = v, y = u, tmp; y != -1; x = tmp, y = x == -1 ? -1 : link[x]) {
                tmp = match[y], match[x] = y, match[y] = x;
              }
              return true;
            }
            q.push(match[v]), vis[match[v]] = 1, dep[match[v]] = dep[u] + 2;
          } else if (vis[v] == 1 && find(v) != find(u)) {
            int p = lca(u, v);
            blossom(u, v, p), blossom(v, u, p);
          }
        }
      }
      return false;
    };
    int res = 0;
    for (int u = 0; u < n; ++u) { if (match[u] == -1) { res += augment(u); } }
    return res;
  }
};
