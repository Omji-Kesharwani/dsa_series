#include <bits/stdc++.h>
using namespace std;

// Time Complexity: O(N^2)
// Auxiliary Space: O(1)

void InsertionSort(int arr[],int n)
{
  for(int i=1;i<n;i++)
  {
    int key=arr[i];
    int j=i-1;
    while(j>=0 && arr[j]>key)
    {
      arr[j+1]=arr[j];
      j--;
    }
    arr[j+1]=key;
  }

}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

// Driver method
int main()
{
    int arr[] = { 12, 11, 13, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    InsertionSort(arr, n);
    printArray(arr, n);

    return 0;
}