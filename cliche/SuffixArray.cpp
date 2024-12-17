const int maxn = 2e5 + 10;
int suf[maxn], rnk[maxn << 1], cnt[maxn], tmp[maxn], lcp[maxn];
int w;
bool scmp(int x, int y){
	return (rnk[x] == rnk[y]? rnk[x+w] < rnk[y+w]: rnk[x] < rnk[y]);
}
void build_suffix_array(string &s){
	memset(rnk, 0, sizeof rnk);
	int n = s.size();
	for (int i = 0; i < n; i++){
		rnk[i] = s[i] - 'a' + 1;
		suf[i] = i;
	}
	w = 1;
	sort(suf, suf + n, scmp);
	for (;; w <<= 1){
		memset(cnt, 0, sizeof cnt);
		for (int i = 0; i < n; i++) cnt[rnk[i]]++;
		for (int i = 1; i <= max(26, n); i++){
			cnt[i] += cnt[i-1];
		}
		for (int i = n-1; ~i; i--){
			if (suf[i] < w) continue;
			tmp[--cnt[rnk[suf[i]-w]]] = suf[i]-w;
		}
		for (int i = n-w; i < n; i++){
			tmp[--cnt[rnk[i]]] = i;
		}
		for (int i = 0; i < n; i++) suf[i] = tmp[i];
		tmp[suf[0]] = 1;
		for (int i = 1; i < n; i++){
			tmp[suf[i]] = tmp[suf[i-1]] + scmp(suf[i-1], suf[i]);
		}
		for (int i = 0; i < n; i++) rnk[i] = tmp[i];
		if (rnk[suf[n-1]] == n) return;
	}
}
void build_lcp(string &s){
	int k = 0;
	int n = s.size();
	for (int i = 0; i < n; i++){
		if (rnk[i] == n) continue;
		while(i+k < n && k + suf[rnk[i]] < n && s[i+k] == s[suf[rnk[i]]+k]) k++;
		lcp[rnk[i]] = k;
		if (k) k--;
	}
}