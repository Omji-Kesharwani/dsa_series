#include <bits/stdc++.h>
using namespace std;

//T.C.=O(N^2)
//S.C=O(1)


void BubbleSort(int arr[],int n)
{
  int i,j;
  bool swapped;
  for(int i=0;i<n-1;i++)
  {
    swapped=false;
    for(int j=0;j<n-i-1;j++)
    {
      if(arr[j]>arr[j+1])
      {
        swap(arr[j],arr[j+1]);
        swapped=true;
      }
    }
    if(swapped==false)
    break;
  }
}
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << " " << arr[i];
}

// Driver program to test above functions
int main()
{
    int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    int N = sizeof(arr) / sizeof(arr[0]);
    BubbleSort(arr, N);
    cout << "Sorted array: \n";
    printArray(arr, N);
    return 0;
}