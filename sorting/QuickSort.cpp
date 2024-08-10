#include <bits/stdc++.h>
using namespace std;
int partition(vector<int>& arr,int low,int high)
{
  int pivot=arr[high];
  int i=low-1;
  for(int j=low;j<=high-1;j++)
  {
    if(arr[pivot]>arr[j])
    {
      i++;
      swap(arr[i],arr[j]);
    }
  }
  swap(arr[i+1],arr[high]);
  return i+1;
}
 void QuickSort(vector<int>& arr ,int low,int high)
 {
  if(low<high)
  {
    int pi=partition(arr,low,high);
    QuickSort(arr,low,pi-1);
    QuickSort(arr,pi+1,high);
  }
 }

 int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();
    QuickSort(arr, 0, n - 1);
    cout << "Sorted Array\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}