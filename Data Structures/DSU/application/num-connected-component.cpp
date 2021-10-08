for (each edge between a and b) {
  dsu.union_sets(a,b);
}
set<int> st;
for (int i = 0; i < n; ++i) {
  st.insert(dsu.get(i));
}
cout << st.size() close
