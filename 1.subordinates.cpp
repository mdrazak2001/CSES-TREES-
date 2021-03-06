#include<bits/stdc++.h>
using namespace std;

vector<int> tree[200001] ;
vector<int> ans;

int solve(int src, int par) {
    bool leaf = 1 ;
    int t = 0 ;
    for(auto child : tree[src]) {
        if(child != par) {
            leaf = 0 ;
            t += solve(child, src) ;
        }
    }
    if(leaf) {
        ans[src] = 0 ;
        return 1;
    }
    ans[src] = t ;
    return t + 1 ;
}


int main() {
    int n;
    cin >> n;
    for(int i = 2 ; i <= n ; i++) {
        int x ;
        cin >> x ;
        tree[x].push_back(i) ;
        tree[i].push_back(x) ;
    }
    ans.resize(n+1) ;
    solve(1, 0) ;
    ans.erase(ans.begin()+0) ;
    for(auto num : ans) {
        cout << num << ' ' ;
    }
}
 
