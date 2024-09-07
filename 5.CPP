#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Function to mirror the first half of the string
string mirrorLeftHalf(string s) {
    int len = s.size();
    for (int i = 0; i < len / 2; ++i) {
        s[len - i - 1] = s[i];
    }
    return s;
}

// Function to increment the first half and mirror it
string incrementAndMirror(string s) {
    int len = s.size();
    int mid = (len - 1) / 2;
    
    // Add 1 to the middle element and propagate carry if necessary
    while (mid >= 0 && s[mid] == '9') {
        s[mid] = '0';
        mid--;
    }
    
    // If mid < 0, that means all digits were 9, so we need to add 1 at the beginning
    if (mid < 0) {
        s = '1' + s;
        s[s.size() - 1] = '1';
    } else {
        s[mid] += 1;
    }
    
    return mirrorLeftHalf(s);
}

// Function to find the next palindrome greater than the given number
string nextPalindrome(string num) {
    int len = num.size();
    
    // Special case: if the number is all 9s, the result is "100...001"
    if (all_of(num.begin(), num.end(), [](char c) { return c == '9'; })) {
        return "1" + string(len - 1, '0') + "1";
    }

    // Get the mirrored version of the current number
    string mirrored = mirrorLeftHalf(num);
    
    // If the mirrored number is greater than the input, return it
    if (mirrored > num) {
        return mirrored;
    }
    
    // Otherwise, increment the first half and mirror again
    return incrementAndMirror(num);
}

int main() {
    int t;
    cin >> t;  // Number of test cases
    
    while (t--) {
        string K;
        cin >> K;  // Input number as a string
        
        // Find the smallest palindrome greater than K
        string result = nextPalindrome(K);
        
        // Output the result
        cout << result << endl;
    }
    
    return 0;
}
