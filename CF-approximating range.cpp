#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
class SegmentTree{
private:
    vector<int>tree_max , tree_min , a;
    void buildTree_min(int index, int start, int end)
    {
        //base case
        if(start > end)
        {
            return;
        }
        //reached leaf node
        if(start == end)
        {
            tree_min[index] = a[start];
            return ;
        }
        //now build the segment tree in bottom up manner
        int m = start + (end - start)/2;
        buildTree_min(2 * index, start, m);
        buildTree_min(2 * index + 1,m + 1, end);
        tree_min[index] = min(tree_min[2 * index],tree_min[2 * index + 1]);
    }
    void buildTree_max(int index, int start, int end)
    {
        //base case
        if(start > end)
        {
            return;
        }
        //reached leaf node
        if(start == end)
        {
            tree_max[index] = a[start];
            return ;
        }
        //now build the segment tree in bottom up manner
        int m = start + (end - start)/2;;
        buildTree_max(2 * index, start, m);
        buildTree_max(2 * index + 1,m + 1, end);
        tree_max[index]= max(tree_max[2 * index],tree_max[2 * index + 1]);
    }

    bool f(int index,int s,int e,int si,int n)
    {
        for(int i = 0; i <= n - si;i++)
        {
            if((query_max(index,s,e,i,i+si-1) - query_min(index,s,e,i,i + si - 1)) <= 1)
            {
                return true;
            }
        }
        return false;
    }
public:
    SegmentTree(int n, vector<int>& arr) {
        a = arr;
        tree_max.resize(4 * n, 0);
        tree_min.resize(4 * n, 0);
        buildTree_min(1, 0, n - 1);
        buildTree_max(1, 0, n - 1);
    }
    int query_min(int index, int start, int end, int l, int r)
    {
        //base case: if query range is outside the node range
        if(l > end || start > r) {
            return INT_MAX;
        }
        //complete overlap
        if(start >= l && end <= r) {
            return tree_min[index];
        }
        //now partial overlap case is executed
        int m = start + (end - start)/2;
        int left_ans = query_min(2 * index, start, m, l, r);
        int right_ans = query_min(2 * index + 1,m + 1, end, l, r);
        return min(left_ans,right_ans);
    }
    //function to query the segment tree for RMQ
    int query_max(int index, int start, int end, int l, int r)
    {
        //base case: if query range is outside the node range
        if(l > end || start > r) {
            return INT_MIN;
        }
        //complete overlap
        if(start >= l && end <= r) {
            return tree_max[index];
        }
        //now partial overlap case is executed
        int m = start + (end - start)/2;
        int left_ans = query_max(2 * index, start, m, l, r);
        int right_ans = query_max(2 * index + 1,m + 1, end, l, r);
        return max(left_ans,right_ans);
    }
    int b_search(int index,int s,int e,int n)
    {
        int low = 1,high = n, res;
        while(low<=high)
        {
            int mid = low + (high - low)/2;
            if(f(index,s,e,mid,n))
            {
                res = mid;
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return res;
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    SegmentTree segtree(n , a);
    int res = segtree.b_search(1 , 0 , n - 1 , n);
    cout<<res<<endl;
    return 0;
}
