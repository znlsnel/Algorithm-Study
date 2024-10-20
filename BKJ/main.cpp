﻿#include <iostream>
#include<vector>
#include <algorithm>
using namespace std;

int solution(vector<int> A, vector<int> B)
{

        sort(A.begin(), A.end());
        sort(B.begin(), B.end(), [](int a, int b) {return a > b; });

        int answer = 0;

        for (int i = 0; i < A.size(); i++)
                answer += A[i] * B[i];


        return answer;
}