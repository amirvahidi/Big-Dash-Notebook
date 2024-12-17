const int MOD = 998244353;
const int LG = 16; // IF YOU WANT TO CONVOLVE TWO ARRAYS OF LENGTH N AND M CHOOSE LG IN SUCH A WAY THAT 2^LG > n + m
const int MAX = (1 << LG);
const int ROOT = 44759; // ENSURE THAT ROOT^2^(LG - 1) = MOD - 1
int bpow(int a, int b){
	int ans = 1;
	while (b){
		if (b & 1)
			ans = 1LL * ans * a % MOD;
		b >>= 1;
		a = 1LL * a * a % MOD;
	}
	return ans;
}
void ntt(int *a, bool inv){
	for (int mask = 0; mask < MAX; mask++){
		int rev = 0;
		for (int i = 0; i < LG; i++)
			if ((1 << i) & mask)
				rev |= (1 << (LG - 1 - i));
		if (mask < rev)
			swap(a[mask], a[rev]);
	}
	for (int len = 2; len <= MAX; len *= 2){
		int wn = bpow(ROOT, MAX / len);
		if (inv)
			wn = bpow(wn, MOD - 2);
		for (int i = 0; i < MAX; i += len){
			int w = 1;
			for (int j = 0; j < len / 2; j++){
				int l = a[i + j];
				int r = 1LL * w * a[i + j + len / 2] % MOD;
				a[i + j] = (l + r);
				a[i + j + len / 2] = l - r + MOD;
				if (a[i + j] >= MOD)
					a[i + j] -= MOD;
				if (a[i + j + len / 2] >= MOD)
					a[i + j + len / 2] -= MOD;
				w = 1LL * w * wn % MOD;
			}
		}
	}
	if (inv){
		int x = bpow(MAX, MOD - 2);
		for (int i = 0; i < MAX; i++)
			a[i] = 1LL * a[i] * x % MOD;
	}
}

// sohsoh ntt
const ll ROOT = 3; // primitive root of MOD
const ll MOD = 998244353;

inline void NTT(ll* A, int n, bool inv) {
	int lg = __builtin_ctz(n);
	for (int i = 1; i < n; i++) {
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
		if (rev[i] < i) swap(A[i], A[rev[i]]);
	}

	for (int len = 1; len < n; len <<= 1) {
		ll wn = poww(ROOT, MOD / 2 / len);
		if (inv) wn = poww(wn, MOD - 2);

		for (int i = 0; i < n; i += 2 * len) {
			ll w = 1;
			for (int j = i; j < i + len; j++) {
				ll x = A[j], y = w * A[j + len] % MOD;
				A[j] = (x + y) % MOD;
				A[j + len] = (x - y + MOD) % MOD;
				w = w * wn % MOD;
			}
		}
	}

	if (inv) {
		ll n_inv = poww(n, MOD - 2);
		for (int i = 0; i < n; i++)
			A[i] = A[i] * n_inv % MOD;
	}
}