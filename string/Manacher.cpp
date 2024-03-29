// returns radius of t, length of s : rad(t) - 1, radius of s : rad(t) / 2
vector<int> manacher(string s) {
  string t = "#";
  for (auto c : s) { t += c, t += '#'; }
  int n = t.size();
  vector<int> r(n);
  for (int i = 0, j = 0; i < n; i++) {
    if (2 * j - i >= 0 && j + r[j] > i) { r[i] = min(r[2 * j - i], j + r[j] - i); }
    while (i - r[i] >= 0 && i + r[i] < n && t[i - r[i]] == t[i + r[i]]) { r[i]++; }
    if (i + r[i] > j + r[j]) { j = i; }
  }
  return r;
}
