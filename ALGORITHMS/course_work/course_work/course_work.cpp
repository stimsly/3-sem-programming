#include <cstdio>
#include <string>
#include <cassert>
#include <map>
#include <vector>
#include <string_view>
#include <random>
#include <utility>
#include <tuple>
#include <set>

constexpr int MAX_LEN = 11; // <= 12 for encode function

struct Node {
    int val;
    int rnd; // >= rnd of all nodes in this subtree
    int count; // number of nodes in this subtree including this one
    Node* left;
    Node* right;
};

inline int count(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    else {
        return root->count;
    }
}

inline void update(Node* root) {
    assert(root != nullptr);
    root->count = 1 + count(root->left) + count(root->right);
}

std::pair<Node*, Node*> split(Node* root, int range) { // returns pair(<=val, >val)
    if (root == nullptr) {
        return { nullptr, nullptr };
    }
    else if (root->val <= range) {
        Node* right;
        std::tie(root->right, right) = split(root->right, range);
        update(root);
        return { root, right };
    }
    else {
        Node* left;
        std::tie(left, root->left) = split(root->left, range);
        update(root);
        return { left, root };
    }
}

Node* join(Node* left, Node* right) {
    if (left == nullptr) {
        return right;
    }
    else if (right == nullptr) {
        return left;
    }
    else if (left->rnd > right->rnd) {
        left->right = join(left->right, right);
        update(left);
        return left;
    }
    else {
        right->left = join(left, right->left);
        update(right);
        return right;
    }
}

std::string to_string(Node* root) {
    if (root == nullptr) {
        return "0";
    }
    else {
        return "{" + to_string(root->left) + "}[val=" + std::to_string(root->val) + " rnd=" + std::to_string(root->rnd) + " count=" + std::to_string(root->count) + "]{" + to_string(root->right) + "}";
    }
}

void add(Node*& root, Node* newNode) {
    Node** p = &root;
    while (true) {
        if (*p == nullptr) {
            *p = newNode;
            assert(newNode->count == 1);
            assert(newNode->left == nullptr);
            assert(newNode->right == nullptr);
            break;
        }
        else if (newNode->rnd > (*p)->rnd) {
            std::tie(newNode->left, newNode->right) = split(*p, newNode->val);
            update(newNode);
            *p = newNode;
            break;
        }
        else if (newNode->val < (*p)->val) {
            (*p)->count++;
            p = &(*p)->left;
        }
        else {
            assert(newNode->val > (*p)->val); // !=
            (*p)->count++;
            p = &(*p)->right;
        }
    }
}

void remove(Node*& root, int val) {
    assert(root != nullptr); // val must be in the tree
    Node** p = &root;
    while (true) {
        if (val < (*p)->val) {
            assert((*p)->left != nullptr);
            (*p)->count--;
            p = &(*p)->left;
        }
        else if (val > (*p)->val) {
            assert((*p)->right != nullptr);
            (*p)->count--;
            p = &(*p)->right;
        }
        else {
            // val == (*p)->val
            Node* removed = *p;
            *p = join(removed->left, removed->right);
            removed->left = nullptr;
            removed->right = nullptr;
            removed->count = 1;
            break;
        }
    }
}

int count(Node* root, int first, int last) { // number of val's in [first, last]
    if (first > last) {
        return 0;
    }
    int answer = count(root);
    for (Node* p = root; p != nullptr;) {
        if (p->val < first) {
            answer -= count(p->left) + 1;
            p = p->right;
        }
        else if (p->val > first) {
            p = p->left;
        }
        else {
            // p->val == first;
            answer -= count(p->left);
            break;
        }
    }
    for (Node* p = root; p != nullptr;) {
        if (p->val > last) {
            answer -= count(p->right) + 1;
            p = p->left;
        }
        else if (p->val < last) {
            p = p->right;
        }
        else {
            // p->val == last
            answer -= count(p->right);
            break;
        }
    }
    return answer;
}

int countKmp(std::string_view s, std::string_view sub) {
    static int prefix[100000 + 1]; // [size] -> size
    prefix[0] = 0;
    prefix[1] = 0;
    for (int last = 1; last < (int)sub.size(); last++) {
        int len = prefix[last];
        while (true) {
            if (sub[last] == sub[len]) {
                len++;
                break;
            }
            else if (len == 0) {
                break;
            }
            else {
                len = prefix[len];
            }
        }
        prefix[last + 1] = len;
    }
    int len = 0;
    int answer = 0;
    for (char c : s) {
        while (true) {
            if (sub[len] == c) {
                len++;
                break;
            }
            else if (len == 0) {
                break;
            }
            else {
                len = prefix[len];
            }
        }
        if (len == (int)sub.size()) {
            answer++;
            len = prefix[len];
        }
    }
    return answer;
}

inline long long encode(const std::string& s, int first, int after) {
    long long answer = 0;
    for (int i = first; i < after; i++) {
        answer <<= 5; // 'z' - 'a' + 1 = 26 <= 32 = 2^5
        answer |= s[i] - 'a';
    }
    return answer;
}

struct Query {

    int kind;

    int pos;

    char c;

    int left;

    int right;

    std::string query;
};

int main() {
    char buffer[100000 + 1] = {};
    scanf("%100000s", buffer);
    std::string s(buffer);
    std::set<std::string_view> qs;
    int nQ;
    scanf("%d", &nQ);
    std::vector<Query> queries(nQ);
    for (Query& q : queries) {
        scanf("%d", &q.kind);
        if (q.kind == 1) {
            scanf("%d %c", &q.pos, &q.c);
        }
        else {
            assert(q.kind == 2);
            buffer[0] = 0;
            scanf("%d %d %s", &q.left, &q.right, buffer);
            q.query = buffer;
            qs.insert(q.query);
        }
    }
    std::vector<std::map<long long, Node*>> index(1 + MAX_LEN); // index[query length][encode(query)] -> treap of positions
    std::vector<std::vector<Node>> data(1 + MAX_LEN); // [len][pos] -> Node
    std::mt19937 gen(2156);
    for (int len = 1; len <= MAX_LEN && len <= (int)s.size(); len++) {
        data[len].resize(s.size() + 1 - len, Node{ 0, 0, 0, nullptr, nullptr });
        for (int first = 0; first + len <= (int)s.size(); first++) {
            data[len][first].val = first;
            data[len][first].rnd = gen();
            data[len][first].count = 1;
            if (qs.count(std::string_view(s).substr(first, len)) > 0) {
                long long key = encode(s, first, first + len);
                add(index[len][key], &data[len][first]);
            }
        }
    }
    for (const Query& q : queries) {
        int kind = q.kind;
        if (kind == 1) {
            int pos = q.pos - 1;
            char c = q.c;
            for (int len = 1; len <= MAX_LEN && len <= (int)s.size(); len++) {
                for (int first = std::max(0, pos - len + 1); first <= pos && first + len <= (int)s.size(); first++) {
                    if (qs.count(std::string_view(s).substr(first, len)) > 0) {
                        long long key = encode(s, first, first + len);
                        auto it = index[len].find(key);
                        assert(it != index[len].end());
                        remove(it->second, first);
                    }
                }
            }
            s[pos] = c;
            for (int len = 1; len <= MAX_LEN && len <= (int)s.size(); len++) {
                for (int first = std::max(0, pos - len + 1); first <= pos && first + len <= (int)s.size(); first++) {
                    if (qs.count(std::string_view(s).substr(first, len)) > 0) {
                        long long key = encode(s, first, first + len);
                        assert(data[len][first].val == first);
                        assert(data[len][first].count == 1);
                        assert(data[len][first].left == nullptr);
                        assert(data[len][first].right == nullptr);
                        add(index[len][key], &data[len][first]);
                    }
                }
            }
        }
        else {
            assert(kind == 2);
            int left = q.left - 1;
            int right = q.right - 1;
            const std::string& query = q.query;
            int answer;
            if ((int)query.size() <= MAX_LEN) {
                int len = (int)query.size();
                long long key = encode(query, 0, len);
                auto it = index[len].find(key);
                if (it == index[len].end()) {
                    answer = 0;
                }
                else {
                    answer = count(it->second, left, right - len + 1);
                }
            }
            else {
                answer = countKmp(std::string_view(s).substr(left, right - left + 1), query);
            }
            printf("%d\n", answer);
        }
    }
    return 0;
}

