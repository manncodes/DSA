/**
 * @problem: https://codeforces.com/contest/475/problem/D
 * 
 * We solve this problem using sparse table.
 */

#include<bits/stdc++.h>
using namespace std;

#define N 100100
int a[N]; // array to compute sparse table
int st[N][18];// 18  = ceil(log2(N))
int lg[N]; //floor(log2(i))

// the duplicate invariant function, in our case: gcd()
inline int gcd(int a, int b) { if (b == 0) return a; return gcd(b, a % b); }

inline int query(int l,int r){
    int g = lg[r-l+1];
    int x = st[l][g];
    int y = st[r - (1<<g) + 1][g];
    return gcd(x,y);
}

inline void builtST(int n){
    lg[0] = -1;

    for(int i=0;i<n;i++){
        st[i][0] = a[i];
        lg[i+1] = lg[i] + !(i&(i+1));
    }

    int x,y;
    for(int j=1;(1<<j)<=n;j++){
        for(int i=0;(i+(1<<j))<=n;i++){
            x = st[i][j-1];
            y = st[i + (1<<(j-1))][j-1];
            st[i][j] = gcd(x,y);
        }
    }
}


int main(){
    int n;
    cin>>n;
    map<int, long long> ans;
    for(int i=0;i<n;i++) cin>>a[i];
    //build sparse tree
    builtST(n);

    int l,r,s,m,g;
    for(int i=0;i<n;i++){
        l = i;
        while(l<n){
            s = l;
            g = query(i,s);
            r = n - 1;
            while(l<r){
                m = (l+r+1)/2;
                if(query(i,m)>=g){
                    l = m;
                }else{
                    r = m - 1;
                }
            }
            l = r + 1;
            ans[g] += l - s;
        }
    }

    //run queries O(1)
    int q,qq;
    cin>>q;
    while(q--){
        cin>>qq;
        cout<<ans[qq]<<'\n';
    }

    return 0;
}
