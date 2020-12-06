#include <bits/stdc++.h>
using namespace std;
#define PI 3.14159265358979323
#define ll long long int
#define vi vector <int>
#define vl vector <ll>
#define all(v) (v).begin(),(v).end()
#define pb push_back
#define ff first
#define ss second
#define MOD 1000000007
ll power(ll a, ll b) { //a^b
	ll res = 1;
	a = a % MOD;
	while (b > 0) {
		if (b & 1) {res = (res * a) % MOD; b--;}
		a = (a * a) % MOD;
		b >>= 1;
	}
	return res;
}

ll gcd(ll a, ll b) {return (b == 0) ? a : gcd(b, a % b);}

ll n, l;
vector <vl> adj;
ll timer = 0;
vl tin, tout;
vector <vl> up;
vl d;

void dfs(ll u, ll v) {
	tin[u] = ++timer;
	up[u][0] = v;
	for (ll i = 1; i <= l; i++) {
		up[u][i] = up[up[u][i - 1]][i - 1];
	}
	for (auto i : adj[u]) {
		if (i == v)
			continue;
		d[i] = d[u] + 1;
		dfs(i, u);
	}
	tout[u] = ++timer;
}

bool is_ancestor(ll u, ll v) {
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}

ll lca(ll u, ll v) {
	if (is_ancestor(u, v))
		return u;
	if (is_ancestor(v, u))
		return v;
	for (ll i = l; i >= 0; i--) {
		if (!is_ancestor(up[u][i], v))
			u = up[u][i];
	}
	return up[u][0];
}

void preprocess(ll root) {
	tin.resize(n);
	tout.resize(n);
	d.resize(n);
	d[root] = 0;
	timer = 0;
	l = ceil(log2(n));
	up.assign(n, vector<ll>(l + 1));
	dfs(root, root);
}

ll dist(ll u, ll v) {
	return d[u] + d[v] - 2 * d[lca(u, v)];
}


int main() {
#ifndef ONLINE_JUDGE
	// for getting input from input.txt
	freopen("input.txt", "r", stdin);
	// for writing output to output.txt
	freopen("output.txt", "w", stdout);
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	adj.resize(n);
	for (ll i = 0; i + 1 < n; i++) {
		ll u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	preprocess(0);
	

}
