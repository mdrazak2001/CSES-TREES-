#include<bits/stdc++.h>
using namespace std;

vector<int> tree[200001] ;
int ans = 0;

int solve(int src, int par) {
    vector<int> v ;
    bool leaf = 1;
    //Get 2 maximum depths of children (Hypothsis)
    for(auto child : tree[src]) {
        int t ;
        if(child != par) {
            leaf = 0 ;
            t = solve(child, src) ;
            v.push_back(t) ;
        }
    }
    if(leaf) return 1 ; 
    sort(v.begin(), v.end()) ;
    int mx1 = (v.size()-1 >= 0) ? v[v.size()-1] : 0 ;
    int mx2 = (v.size()-2 >= 0) ? v[v.size()-2] : 0 ;
    //A path that passes thru curr src root = 2 max depths summation
    ans = max(ans, mx1 + mx2) ;
    //Return the max depth to parent
    return max(mx1, mx2) + 1;
}

int main() {
    int n;
    cin >> n ;
    for(int i = 0 ; i < n - 1 ; i++) {
        int a, b;
        cin >> a >> b ;
        tree[a].push_back(b) ;
        tree[b].push_back(a) ;
    }
    solve(1, 0) ;
    cout << ans ;
}