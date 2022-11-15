#include <bits/stdc++.h>

using namespace std;

int main() {

    map <long long, long long> s, ans;

    int q;
    cin >> q;
    s[0]++;

    while (q--) {
        char c;
        long long a;
        cin >> c >> a;
        if (c == '+') s[a]++;
        else {
            while (s[a * ans[a]]) ans[a]++;
            cout << ans[a] * a << endl;
        }
    }
    return 0;
}