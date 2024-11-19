
/*   Inversion count of an array is the count of all the pairs (i,j) such that i<j and arr[i]>arr[j]    */

#include <bits/stdc++.h>
using namespace std;

// O(n^2) Naive Approach

int InversionCount_Naive(int arr[], int n) {
    int count=0;
    for(int i=1;i<n;i++){
        for(int j=0;j<i;j++) {
            if(arr[j] > arr[i]) {
                count++;
            }
        }
    }
    return count;
}

/*  Next 3 Methods are Divide and Conquer Approaches */



// O(n^2 log(n)) Approach

int Divide_Conquer_Count1(vector<int> arr,int l,int r){
    int Count=0;
    if(l<r){
        int m=l+(r-l)/2;
        Count+=Divide_Conquer_Count1(arr,l,m);
        Count+=Divide_Conquer_Count1(arr,m+1,r);
        for(int i=l;i<=m;i++) {
            for(int j=m+1;j<=r;j++) {
                if(arr[i] > arr[j]) {
                    Count++;
                }
            }
        }
    }
    return Count;
}

// O(nlog^2(n)) Approach

int Divide_Conquer_Count2(vector<int> &arr,int l,int r) {
    int Count=0;
    if(l<r) {
        int m=l+(r-l)/2;
        Count+=Divide_Conquer_Count2(arr,l,m);
        Count+=Divide_Conquer_Count2(arr,m+1,r);
        int i=l,j=m+1;
        sort(arr.begin()+l,arr.begin()+m);
        sort(arr.begin()+m+1,arr.begin()+r);
        while(i<=m && j<=r) {
            if(arr[i] <= arr[j]) i++;
            else {
                j++;
                Count += m-i+1;
            }
        }
        while(i<=m) i++;
        while(j<=r) j++;
    }
    return Count;
}

// O(nlog(n)) Approach

pair<int,vector<int>> inversions(vector<int> arr,int l,int r){
    if(l==r) return {0,{arr[l]}};
    int m=l+(r-l)/2;
    pair<int,vector<int>> L=inversions(arr,l,m);
    pair<int,vector<int>> R=inversions(arr,m+1,r);
    vector<int> ans;
    int cnt=L.first+R.first,i=0,j=0,p=L.second.size(),q=R.second.size();
    while(i<p && j<q){
        if(L.second[i]<=R.second[j]){
            ans.push_back(L.second[i]);
            i++;
        }
        else{
            ans.push_back(R.second[j]);
            j++;
            cnt+=p-i;
        }
    }
    while(i<p) ans.push_back(L.second[i++]);
    while(j<q) ans.push_back(R.second[j++]);
    return {cnt,ans};
}

int Divide_Conquer_Count3(vector<int> arr){
    return inversions(arr,0,arr.size()-1).first;
}