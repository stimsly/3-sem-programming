#include <iostream>
#include <map>
#include <random>
#include <ctime>

using namespace std;

const int N = 100000 + 10;

mt19937 gen(time(0));
uniform_int_distribution<int> distr(0, 1000000000);
struct item {
    int key, prior;
    int cnt;
    item* l = nullptr, * r = nullptr, * root = nullptr;
    item() { }
    item(int key) : key(key), prior(distr(gen)), l(NULL), r(NULL), root(NULL), cnt(1) { }
    typedef item* pitem;
    int cnt1(pitem t) {
        return t ? t->cnt : 0;
    }

    void upd_cnt(pitem t) {
        if (t)
            t->cnt = 1 + cnt1(t->l) + cnt1(t->r);
    }

    void split(pitem t, int key, pitem& l, pitem& r) {
        if (!t) {
            l = r = NULL;
            return;
        }
        if (key > t->key) {
            split(t->r, key, t->r, r);
            l = t;
        }
        else {
            split(t->l, key, l, t->l);
            r = t;
        }
        upd_cnt(r);
        upd_cnt(l);
        upd_cnt(t);
    }

    
    void insert(int x) {
        pitem less, greater;
        split(root, x, less, greater);
        merge(greater, new item(x), greater);
        merge(root, less, greater);
    }

    void merge(pitem& t, pitem l, pitem r) {
        if (!l || !r) {
            t = l ? l : r;
            return;
        }
        if (l->prior > r->prior) {
            merge(l->r, l->r, r);
            t = l;
        }
        else {
            merge(r->l, l, r->l);
            t = r;
        }
        upd_cnt(l);
        upd_cnt(r);
        upd_cnt(t);
    }

    void erase(int x) {
        pitem less, equal, greater;
        split(root, x, less, greater);
        split(greater, x + 1, equal, greater);
        merge(root, less, greater);
    }

    int sum(int x) {
        pitem less, greater;
        split(root, x + 1, less, greater);
        int ans = cnt1(less);
        merge(root, less, greater);
        return ans;
    }
};

std::map <std::string, item> short_str;
std::string s;
int kmp[N];
int n;
const int str_n = 5;
void precalc() {
    for (int len = 1; len <= std::min(str_n, n); len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            short_str[s.substr(i, len)].insert(i);
            // cout << i << " " << s.substr(i, len) << " " << short_str[s.substr(i, len)].sum(n-1) << "\n";
        }
    }
}

void update(int k, char c) {
    for (int i = 1; i <= str_n; i++) {
        for (int j = max(0, k - i + 1); j <= k; j++) {
            if (j + i <= n) short_str[s.substr(j, i)].erase(j);
            else break;
        }
    }
    s[k] = c;
    for (int i = 1; i <= str_n; i++) {
        for (int j = max(0, k - i + 1); j <= k; j++) {
            if (j + i <= n) short_str[s.substr(j, i)].insert(j);
            else break;
        }
    }
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

#define cout(x) std::cout << "\x1b[32m" << (x) << "\x1b[0m\n"; 

int main()
{
    std::cin >> s;
    n = s.size();

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
            update(i, c);
        }
        else {
            int l, r;
            std::string y;
            std::cin >> l >> r >> y;
            l--;
            r--;
            if (y.size() <= str_n) {
                int ans = 0;
                ans = short_str[y].sum(r - y.size() + 1);
               // cout << "d: " << r - y.size() + 1 << " " << l - 1 << endl;
                //cout << ans << ' ';
                ans -= short_str[y].sum(l - 1);
                cout << max(0, ans) << endl;
            }
            else {
                int ans = calc_kmp(y, l, r);
                cout << ans << endl;
            }
        }
    }
}