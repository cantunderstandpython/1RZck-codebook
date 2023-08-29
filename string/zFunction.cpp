template <typename T>
vector<int> zFunction(const T &s) {
    int n = int(s.size());
    if (n == 0) return {};
    vector<int> z(n);
    for (int i = 1, j = 0; i < n; i++) {
        int &k = z[i];
        k = j + z[j] <= i ? 0 : min(j + z[j] - i, z[i - j]);
        while (i + k < n && s[k] == s[i + k]) { k++; }
        if (j + z[j] < i + z[i]) { j = i; }
    }
    z[0] = n;
    return z;
}