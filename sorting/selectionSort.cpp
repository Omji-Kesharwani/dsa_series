#include<bits/stdc++.h>
using namespace std;
void SelectionSort(int arr[],int n)
{
  for(int i=0;i<n-1;i++)
  {
    int min_idx=i;
    for(int j=i+1;j<n;j++)
    {
      if(arr[min_idx]>arr[j])
      min_idx=j;
    }
    if(i!=min_idx)
    swap(arr[i],arr[min_idx]);
  }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Driver program
int main()
{
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    SelectionSort(arr, n);
    cout << "Sorted array: \n";
    printArray(arr, n);
    return 0;
}
//T.C.=O(N^2)
//S.C=O(1)