vector<P<T>> convexHull(vector<P<T>> a) {
    int n = a.size();
    if (n <= 1) { return a; }
    sort(a.begin(), a.end());
    vector<P<T>> b(2 * n);
    int j = 0;
    for (int i = 0; i < n; b[j++] = a[i++]) {
        while (j >= 2 && side(b[j - 2], b[j - 1], a[i]) <= 0) { j--; }
    }
    for (int i = n - 2, k = j; i >= 0; b[j++] = a[i--]) {
        while (j > k && side(b[j - 2], b[j - 1], a[i]) <= 0) { j--; }
    }
    b.resize(j - 1);
    return b;
}
vector<P<T>> convexHullNonStrict(vector<P<T>> a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    int n = a.size();
    if (n == 1) { return a; }
    vector<P<T>> b(2 * n);
    int j = 0;
    for (int i = 0; i < n; b[j++] = a[i++]) {
        while (j >= 2 && side(b[j - 2], b[j - 1], a[i]) < 0) { j--; }
    }
    for (int i = n - 2, k = j; i >= 0; b[j++] = a[i--]) {
        while (j > k && side(b[j - 2], b[j - 1], a[i]) < 0) { j--; }
    }
    b.resize(j - 1);
    return b;
}