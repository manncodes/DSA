#include <bits/stdc++.h>
using namespace std;
j
// N: the maximum size of array
// M: ceil(log2(N)).

// The array to compute it's sparse table
int n,a[N];

// Sparse table related variables
//
// ST[j][i] : the sparse table value(min,max,...etc)
//            in the interval [i,i + pow(2,j) -1)].
// LOG[i]   : floor(log2(i))
int ST[M][N], LOG[N];

/**
* Builds the sparse table for computing min/max/gcd/lcm/...etc
 * for any contiguous sub-segment of the array.
 * 
 * This is an example of computing the index of the minimum value.
 * 
 * Complexity: O(n.log(n))
 */

void buildST(){
    LOG[0] = -1;
    for(int i=0; i<n;++i){
        ST[0][i] = i;
        LOG[i+1] = LOG + !(i&(i+1));
    }

    for(int j=1;(1<<j)<n;++j){
        for(int i=0;(i+(1<<j))<=n; ++i){
            int x = ST[j-1][i];
            int y = ST[j-1][1+(1<<(j-1))];

            ST[j][i] = ((a[x] <= a[y])? x : y);
        }
    }
}

/**
 * Queries the sparse table for the value of the interval [l, r]
 * (i.e. from l to r inclusive).
 * 
 * Complexity: O(1)
 * 
 * @param l the left index of the range (inclusive).
 * @param r the right index of the range (inclusive).
 * 
 * @return the computed value of the given interval.
 */
int query(int l,int r){
    int g = LOG[r-l+1];
    int x = ST[g][l];
    int y = ST[g][r-(1<<g) + 1];
    return ((a[x] <= a[y]) ? x : y);
}