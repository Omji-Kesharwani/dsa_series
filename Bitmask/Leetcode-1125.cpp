/*
In a project, you have a list of required skills req_skills, and a list of people. The ith person people[i] contains a list of skills that the person has.

Consider a sufficient team: a set of people such that for every required skill in req_skills, there is at least one person in the team who has that skill. We can represent these teams by the index of each person.

For example, team = [0, 1, 3] represents the people with skills people[0], people[1], and people[3].
Return any sufficient team of the smallest possible size, represented by the index of each person. You may return the answer in any order.

It is guaranteed an answer exists.

 

Example 1:

Input: req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]
Output: [0,2]
Example 2:

Input: req_skills = ["algorithms","math","java","reactjs","csharp","aws"], people = [["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],["reactjs","csharp"],["csharp","math"],["aws","java"]]
Output: [1,2]
 
*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        int numSkills = req_skills.size();
        int numPeople = people.size();
        unordered_map<string,int>skillToIndex;
        for(int i=0;i<numSkills;i++)
        {
            skillToIndex[req_skills[i]]=i;
        }
        vector<int>personSkillMask(numPeople);
        for(int personIndex = 0;personIndex < numPeople ; personIndex++)
        {
            int mask =0;
            for(auto skill :people[personIndex])
            {
                if(skillToIndex.count(skill))
                {
                   mask |= (1<<(skillToIndex[skill]));
                }
            }
            personSkillMask[personIndex] = mask;
        }

        long long INF = 1<<30;
        int total_states = 1<<numSkills;
        vector<long long>minTeamSize(total_states,INF);
        vector<long long >lastPersonAdded(total_states,0);
        vector<long long>previousState(total_states,0);
        minTeamSize[0] = 0;

        for(int curMask = 0;curMask < total_states ; curMask++)
        {
            if(minTeamSize[curMask]==INF) continue;
            for(int personIndex =0 ;personIndex < numPeople ;personIndex++)
            {
                int newMask = curMask | (personSkillMask[personIndex]);
                if(minTeamSize[newMask] > 1+minTeamSize[curMask])
                {
                    minTeamSize[newMask] = 1+minTeamSize[curMask];
                    lastPersonAdded[newMask] = personIndex ;
                    previousState[newMask] = curMask;
                }
            }
        }

        vector<int>team;
        int fullCoverage = total_states-1;
        for(int mask = fullCoverage ;mask !=0 ;mask = previousState[mask])
        {
            team.push_back(lastPersonAdded[mask]);
        }

        return team ;

    }
};