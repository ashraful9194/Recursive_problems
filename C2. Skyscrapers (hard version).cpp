#include<bits/stdc++.h>
//pbds
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template <typename T>   using orderedSet =tree<T, null_type, greater<T>,rb_tree_tag, tree_order_statistics_node_update>;
#define int long long
typedef unsigned long long ull;
typedef pair<int,int> pii;
#define pb push_back
//BFS+DFS
#define boundary(i,j) (i>=0 && i<n && j>=0 && j<m)
int X[]={-1,1,0,0};
int Y[]={0,0,1,-1};
int n;
int a[500005];
int mn_idx[1500005];
int ans[500005];
void init(int node,int l,int r)
{
    if(l>r) return;
    if(l==r)
    {
        mn_idx[node]=l;
        return;
    }
    int lft=2*node;
    int rt=lft+1;
    int mid=(l+r)/2;
    init(lft,l,mid);
    init(rt,mid+1,r);
    if(a[mn_idx[lft]]<=a[mn_idx[rt]])
        mn_idx[node]=mn_idx[lft];
    else mn_idx[node]=mn_idx[rt];
}
int query(int node,int l,int r,int b,int e)
{
    if(l>e || r<b) return 0;
    if(l>=b && r<=e) return mn_idx[node];
      int lft=2*node;
    int rt=lft+1;
    int mid=(l+r)/2;
   int x= query(lft,l,mid,b,e);
   int y= query(rt,mid+1,r,b,e);
  if(x==0) return y;
  else if(y==0) return x;
  else if(a[x]<=a[y]) return x;
  else return  y;
}
int solve(int l,int r)
{
     if(l>r) return  0;
     if(l==r)
     {
         ans[l]=a[l];
         return  ans[l];
     }
     int idx=query(1,1,n,l,r);
     int op1=a[idx]*(r-idx+1)+solve(l,idx-1);
     int op2=a[idx]*(idx-l+1)+solve(idx+1,r);
     if(op1>=op2)
     {
         for(int i=idx; i<=r; i++)
            ans[i]=a[idx];
     }
     else
     {
          for(int i=l; i<=idx; i++)
            ans[i]=a[idx];
     }
     return  max(op1,op2);
}
int32_t main()
{
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
     cin>>n;
     for(int i=1; i<=n; i++) cin>>a[i];
     init(1,1,n);
     solve(1,n);
     for(int i=1; i<=n; i++) cout<<ans[i]<<" ";
     cout<<endl;

}

