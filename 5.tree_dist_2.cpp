#include<bits/stdc++.h>
using namespace std;
using ll = long long;
vector<int> tree[200001] ;
ll subtreeSize[200001] ;
ll subtreeAns[200001] ;
ll ans[200001] ;

void preprocess(int src, int par) {
    int numNodes = 1 ;
    ll ans = 0 ;
    for(auto child : tree[src]) {
        if(child != par) {
            preprocess(child, src) ;
            numNodes += subtreeSize[child] ;
            ans += subtreeAns[child] + subtreeSize[child] ;
        }
    }
    subtreeSize[src] = numNodes; 
    subtreeAns[src] = ans ;
}

void solve(int src, int par, ll par_ans, int n) {
    ans[src] = subtreeAns[src] + (par_ans + (n - subtreeSize[src]));
    for(auto child : tree[src]) {
        if(child != par) {
            solve(child, src, ans[src] - (subtreeSize[child] + subtreeAns[child]), n);
        }
    }
}
int main(){
    int n;
    cin >> n ;
    for(int i = 0 ; i < n - 1 ; i++) {
        int l, r; 
        cin >> l >> r ;
        tree[l].push_back(r) ;
        tree[r].push_back(l) ;
    }
    preprocess(1, 0) ;
    solve(1, 0, 0, n) ;
    for(int i = 1 ; i <= n ; i++) {
        cout << ans[i] << ' ' ;
    }
}