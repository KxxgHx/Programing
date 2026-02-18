#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(string s) {
    string renewal = "";
    for (char c : s)
    {
        if(c != ' ')
            renewal += c;
    }
    int left = 0;
    int right = renewal.size() - 1;
    while (left < right)
    {
        if(renewal[left] != renewal[right])
            return false;
        left++;
        right--;
    }
    return true;
}

int main() {
    string input;
    cout << "문자열 입력: ";
    getline(cin, input);

    if (isPalindrome(input))
        cout << "→ 회문입니다." << endl;
    else
        cout << "→ 회문이 아닙니다." << endl;

    return 0;
}
