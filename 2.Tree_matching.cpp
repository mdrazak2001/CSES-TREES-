#include<bits/stdc++.h>
using namespace std;

vector<int> tree[200001] ;
int dp[200001][2] ;

void solve(int src, int par) {
    vector<int> prefix, suffix ;
    bool leaf = 1 ;
    dp[src][0] = dp[src][1] = 0 ;
    for(auto child : tree[src]) {
        if(child != par) {
            leaf = 0;
            solve(child, src) ;
        }
    }
    if(leaf) return ;

    for(auto child : tree[src]) {
        if(child != par){
            prefix.push_back(max(dp[child][0], dp[child][1])) ;
            suffix.push_back(max(dp[child][0], dp[child][1])) ;
        }
    }
    for(int i = 1 ; i < prefix.size() ; i++){
        prefix[i] += prefix[i-1] ;
    }
    for(int i = suffix.size() - 2 ; i >= 0 ; i--){
        suffix[i] += suffix[i+1] ;
    }
    dp[src][0] = suffix[0] ;
    int c_no = 0 ;

    for(auto child : tree[src]) {
        if(child == par) continue;
        int leftChildren = (!c_no) ? 0 : prefix[c_no-1] ;
        int rightChildren = (c_no == (int)suffix.size()-1) ? 0 : suffix[c_no+1] ;
        dp[src][1] = max(dp[src][1], leftChildren + rightChildren + dp[child][0] + 1) ;
        c_no++;
    }
}

int main() {
    int n ;
    cin >> n ;
    for(int i = 0 ; i < n - 1 ; i++){
        int a, b ;
        cin >> a >> b ;
        tree[a].push_back(b) ;
        tree[b].push_back(a) ;
    }

    /******
    //kartik arora : cses 
    so a path can or cannot end @ root
    let 1 be root
    // now let dp[1][0] tell you that root = 1 and end not 1 of any node
    thus dp[1][0] = max -> dp[child1 ... childn][1] and dp[child1....childn][0] 
    cuz all children are independent of their parent 1
    now let dp[1][1] => max match paths such that root is an end pnt
    thus any child can pass to root thus, max of each path of child crossing root;
                           1
                        //  |
                    1       3     5
                  //         \\          
                3   3  4        5
        here 2 paths such that initially child1 crosses root, now rem i+1 are summed as independet and added to result ;
    ************/
   
    solve(1, 0);
    cout << max(dp[1][0], dp[1][1]) ;   
}

