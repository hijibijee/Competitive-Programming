#include <bits/stdc++.h>
using namespace std;

/*
    This function generates an 2-d array isPalindrome. Where,
    isPalindrome[i][j] = true if s[i..j] is a palindrome.
    Time Complexity: O(n^2) 
*/

vector<vector<bool>> generateIsPalindromeForAllSubstringsOf(string s){
    int n = s.length();
    vector<vector<bool>> isPalindrome(n, vector<bool> (n, 0));
        
    for(int len = 0; len < n; len++){
        for(int i = 0; i + len < n; i++){
            if(len == 0) isPalindrome[i][i] = true;
            else{
                if(s[i] == s[i + len] && (i + 1 > i + len - 1 || isPalindrome[i + 1][i + len - 1]))         
                        isPalindrome[i][i + len] = true;
            }
        }
    }

    return isPalindrome;
}