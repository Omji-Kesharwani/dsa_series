/*
466. Count The Repetitions

We define str = [s, n] as the string str which consists of the string s concatenated n times.

For example, str == ["abc", 3] =="abcabcabc".
We define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1.

For example, s1 = "abc" can be obtained from s2 = "abdbec" based on our definition by removing the bolded underlined characters.
You are given two strings s1 and s2 and two integers n1 and n2. You have the two strings str1 = [s1, n1] and str2 = [s2, n2].

Return the maximum integer m such that str = [str2, m] can be obtained from str1.
Example 1:

Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
Output: 2
Example 2:

Input: s1 = "acb", n1 = 1, s2 = "acb", n2 = 1
Output: 1
*/

#include <bits/stdc++.h>
using namespace std;
class Solution
{
  public:
  int getMaxRepetitions(string s1, int n1, string s2, int n2){
    int len1 = s1.size();
    int len2 = s2.size();
    unordered_map<int, pair<int, int>> mp; // stores the index of s2 and pair of s1_count and s2_count

    // s1_count : number of times we have traversed s1
    // s2_count : number of times we have traversed s2
    int index =0;
    int s1Count =0;
    int s2Count =0;
    while(s1Count <n1){
      for(char c:s1){
        if(c==s2[index])
        {
          index++;
          if(index == len2)
          {
            index=0;
            s2Count++;
          }
        }
      }
      s1Count++;
      if(mp.find(index)!=mp.end()){
         // found a pattern
          int preS1Count = mp[index].first;
          int preS2Count = mp[index].second;
          int cycleLen = s1Count - preS1Count;
          int cycleCount = (n1 - preS1Count) / cycleLen;
          s1Count = preS1Count + cycleCount * cycleLen;
          s2Count = preS2Count + cycleCount * (s2Count - preS2Count);
      }

      mp[index] = {s1Count, s2Count};
    }
    return s2Count / n2;
  }
};