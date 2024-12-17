inline void FWHT(ll* A, bool inv) {
	for (int b = 0; b < m; b++) {
		for (int i = 0; i < (1 << m); i++) {
			if (i & (1 << b)) {
				ll y = A[i], x = A[i ^ (1 << b)];
				mkey(A[i ^ (1 << b)] = x + y);
				mkey(A[i] = x - y);
			}
		}
	}
	
	if (inv) {
		for (int i = 0; i < (1 << m); i++)
			A[i] >>= m;
	}
}