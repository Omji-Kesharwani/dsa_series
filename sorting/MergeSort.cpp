#include <bits/stdc++.h>
using namespace std;

//Best Case: O(n log n)
//Average Case: O(n log n)
//Worst Case: O(n log n)

void merge(vector<int>& arr,int left,int mid,int right)
{
int n1=mid-left+1;
int n2=right-mid;
vector<int>L(n1),R(n2);
for(int i=0;i<n1;i++)
{
  L[i]=arr[left+i];
}
for(int j=0;j<n2;j++)
{
  R[j]=arr[mid+1+j];
}
int i=0,j=0;
int k=left;
while(i<n1 && j<n2)
{
  if(L[i]<=R[j])
  {
  arr[k++]=L[i++];
  }
  else{
    arr[k++]=R[j++];
  }
}
while(i<n1)
{
  arr[k++]=L[i++];
}
while(j<n2)
{
  arr[k++]=L[j++];
}

}

void MergeSort(vector<int>& arr, int left, int right)
{
 if(left>=right)
 return;
 int mid=(left+right)>>1;
 MergeSort(arr,left,mid);
 MergeSort(arr,mid+1,right);
 merge(arr,left,mid,right);
}

void printVector(vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Driver code
int main()
{
    vector<int> arr = { 12, 11, 13, 5, 6, 7 };
    int n = arr.size();

    cout << "Given vector is \n";
    printVector(arr);

    MergeSort(arr, 0, n - 1);

    cout << "\nSorted vector is \n";
    printVector(arr);
    return 0;
}