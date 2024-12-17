#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; //less_equal<int> for multiset
ordered_set s;
s.insert(1);
s.find_by_order(idx) //iterator to the idx
s.order_of_key(key) // index of the key
//implementation with fenwick
const int maxn = 1e5 + 10;
int f[maxn];
void change(int idx, int x) { // x = 1 insert, 0 erase
	for (; idx < maxn; idx += idx & -idx) f[idx] += x;
}
int lg = 20;
int find_by_order(int idx) {
	int res = 0;
	for (int i = lg-1; ~i; i--) {
		int tmp = res + (1 << i);
		if (tmp < maxn && f[tmp] < idx) {
			idx -= f[tmp];
			res = tmp;
		}
	}
	return res + 1; // maxn if not exist
}
int order_of_key(int key) {
	int res = 0;
	for (; key; key -= key & -key) res += f[key];
	return res;
}

