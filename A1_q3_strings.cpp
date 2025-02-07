#include <iostream>
#include <cctype> // string functions (like tolower , isalpha)
using namespace std;

int main() {
    string str;
    cout << "Enter a string: ";
    getline(cin, str);

    // Palindrome Check (ignoring spaces and case)
    int left = 0, right = str.length() - 1;
    bool isPalin = true;
    while (left < right) {
        if (tolower(str[left]) != tolower(str[right])) 
        {
            isPalin = false;
            break;
        }
        left++;
        right--;
    }
    if (isPalin) {
        cout << "The string is a palindrome." << endl;
    } else {
        cout << "The string is not a palindrome." << endl;
    }

    // Count Character Frequency (assuming - case insensitive)
    int frequency[26] = {0};  // Array for counting letters from a to z
    for (int i = 0; i < str.length(); i++) {
        if (isalpha(str[i])) {
            char ch = tolower(str[i]);
            frequency[ch - 'a']++;  // Increment frequency of the character
        }
    }
    cout << "Character frequencies (case-insensitive):" << endl;
    for (int i = 0; i < 26; i++) {
        if (frequency[i] > 0) {
            cout << char(i + 'a') << ": " << frequency[i] << endl;
        }
    }
    // Replace Vowels with '*'
    for (int i = 0; i < str.length(); i++) {
        char ch = tolower(str[i]);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            str[i] = '*';  // Replace vowel with '*'
        }
    }
    cout << "Modified string : " << str << endl;
    return 0; //b_s
}
