#include <iostream>
#include <map>
#include <random>

const int N = 100000 + 10;

struct tree {
    int y;
    int index;
    int size;
    tree* root;
    tree* left;
    tree* right;
    void add(int i) {
        y = rand();

    }
    void remove(int i) {
        y = rand();
    }
    int sum(int i) {
        return 1;
    }
};

std::map <std::string, tree> short_str;
std::string s;
int kmp[N];
int n;

void precalc() {
    for (int len = 1; len < std::min(11, n); len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            short_str[s.substr(i, len)].add(i);
        }
    }
}

void update(int i) {

}

int calc_kmp(std::string y, int l, int r) {
    int ans = 0;
    int len = 0;
    int ny = y.size();
    y += '&';
    kmp[0] = -1;
    for (int i = 1; i < ny; i++) {
        len = kmp[i];
        while (len != -1 and y[i] != y[len]) len = kmp[len];
        kmp[i + 1] = len + 1; 
    }
    len = 0;
    for (int i = l; i < r + 1; i++) {
        while (len != -1 and s[i] != y[len]) len = kmp[len];
        len++;
        if (len == ny) ans++;
    }
    return ans;
}

int main()
{
    std::cin >> s;
    int n = s.size();

    int q;
    std::cin >> q;

    precalc();

    for (; q; q--) {
        int t;
        std::cin >> t;
        if (t == 1) {
            int i;
            char c;
            std::cin >> i >> c;
            i--;
            s[i] = c;
            update(i);
        }
        else {
            int l, r;
            std::string y;
            std::cin >> l >> r >> y;
            l--;
            r--;
            if (y.size() <= 0) {
                int ans = short_str[y].sum(r);
                if (l > 0) ans -= short_str[y].sum(l - 1);
                std::cout << ans << "\n";
            }
            else {
                int ans = calc_kmp(y, l, r);
                std:: cout << ans << "\n";
            }
        }
    }
}
