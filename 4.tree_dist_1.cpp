#include<bits/stdc++.h>
using namespace std;

vector<int> tree[200001] ;
vector<int> ans(200001); 
int depth[200001] ;

int eval_depth(int src, int par) {
    int leaf = 1 ;
    int mx_depth = 0 ;
    for(auto child : tree[src]) {
        if(par != child) {
            leaf = 0;
            mx_depth = max(mx_depth, eval_depth(child, src)) ;
        }
    }
    if(leaf) {
        depth[src] =  0;
        return 1;
    }
    depth[src] = mx_depth ;
    return mx_depth + 1 ;
}

void solve(int src, int par, int par_ans){
    vector<int> prefixMax, suffixMax;
    //get depth of child nodes
    for(auto child : tree[src]) {
        if(child != par) {
            prefixMax.push_back(depth[child]) ;
            suffixMax.push_back(depth[child]) ;
        }
    }
    for(int i = 1 ; i < prefixMax.size() ; i++) {
        prefixMax[i] = max(prefixMax[i], prefixMax[i-1]) ;
    }
    for(int i = suffixMax.size() - 2 ; i >= 0 ; i--){
        suffixMax[i] = max(suffixMax[i], suffixMax[i+1]) ;
    }
    int c_no = 0 ;
    for(auto child : tree[src]) {
        if(child != par) {
            int op1 = (!c_no) ? INT_MIN : prefixMax[c_no-1] ;
            int op2 = (c_no == suffixMax.size()-1) ? INT_MIN : suffixMax[c_no+1] ;
            int partial_ans = 1 + max({par_ans, op1, op2}) ;
            solve(child, src, partial_ans) ;
            c_no++;
        }
    }

    ans[src] = 1 + max(par_ans, (prefixMax.empty() ? -1 : prefixMax.back())) ;
}

int main() {
    int n ;
    cin >> n ;
    for(int i = 0 ; i < n - 1 ; i++) {
        int l, r ;
        cin >> l >> r ;
        tree[l].push_back(r) ;
        tree[r].push_back(l) ;
    }
    eval_depth(1, 0) ;
    solve(1, 0, -1) ;
    for(int i = 1 ; i <= n ; i++) {
        cout << ans[i] << ' ' ;
    }

}
 
