#include <bits/stdc++.h>
using namespace std;


//  time complexity of O(d * (n + b)), where d is the number of digits, n is the number of elements, and b is the base of the number system being used

// Radix sort also has a space complexity of O(n + b), where n is the number of elements and b is the base of the number system. 

int getMax(int arr[],int n)
{
  int mx=*max_element(arr,arr+n);
  return mx;
}
void countSort(int arr[],int n,int exp)
{
  int output[n];
  int i,count[10]={0};
  for(i=0;i<n;i++)
  {
    count[(arr[i]/exp)%10]++;
  }
  for(i=1;i<10;i++)
  {
    count[i]+=count[i-1];
  }
  for(int i=n-1;i>=0;i--)
  {
    output[count[(arr[i]/exp)%10]-1]=arr[i];
    count[(arr[i]/exp)%10]--;
  }
  for(i=0;i<n;i++)
  arr[i]=output[i];
}
void radixSort(int arr[],int n)
{
  int m=getMax(arr,n);
  for(int exp=1;m/exp>0;exp*=10)
  countSort(arr,n,exp);
}

void print(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
}

// Driver Code
int main()
{
    int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
    int n = sizeof(arr) / sizeof(arr[0]);

    // Function Call
    radixSort(arr, n);
    print(arr, n);
    return 0;
}