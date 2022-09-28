#include <iostream>

using namespace std;

class list {
public:
private:
    int a;
    list* head;
    list* next;
    list* prev;
public:
    ~list() {
        a = -101;
        head = nullptr;
        next = nullptr;
        prev = nullptr;
    }
    list() {
        a = -101;
        head = nullptr;
        next = nullptr;
        prev = nullptr;
    }
    list(int a) {
        this->a = a;
        head = nullptr;
        next = nullptr;
        prev = nullptr;
    }
    list(int a, list *next) {
        this->a = a;
        head = nullptr;
        this->next = next;
        prev = nullptr;
    }
    list(int a, list* head, list* prev) {
        this->a = a;
        this->head = head;
        this->prev = prev;
        next = nullptr;
    }
    list(int a, list* head, list* next, list* prev) {
        this->a = a;
        this->head = head;
        this->prev = prev;
        this->next = next;
    }
    void push_back(int a); //  O(n)
    void push_front(int a); // O(1)
    void pop_back(); // O(n)
    void pop_front(); // O(1)
    int get_index(int a); // O(n)
    void pop_index(int i); // O(n)
    void add_index(int i, int a); // O(n)
    int get_size(); // O(n)
    void clear(); // O(n)
    void set_index(int i, int a); // O(n)
    bool empty(); // O(1)

    int process(list b); // -1 - нет такого индекса - O(n * m * (m + n))
};

int main()
{
    list a;
    a.push_back(2);
    a.push_back(3);
    a.push_back(3);
    a.push_back(2);
    a.push_back(3);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    
    for (int i = 0; i < a.get_size(); i++) {
        cout << a.get_index(i) << " ";
    }
    cout << endl << endl;
    list b;
    b.push_back(2);
    b.push_back(3);
    b.push_back(4);
    cout << "ans: " << a.process(b) << endl;
    a.clear();
    cout << a.get_size() << endl;
}

int list::process(list b) {
    if (b.get_size() > get_size()) return -1;
    int n = get_size(); // O(n)
    for (int i = 0; i < n; i++) { // 0(n)
        int x = 1;
        for (int j = 0; j < b.get_size(); j++) { // O(m)
            if (i + j >= n) return -1;
            
            if (get_index(i + j) != b.get_index(j)) { // 0(n + m)

                x = 0;
                break;
            }
        }
        if (x) return i;
    }
    return -1; // O(nm(n + m))
}

void list::pop_index(int i) {
    if (i == 0) {
        pop_front();
        return;
    }
    if (i + 1 == get_size()) {
        pop_back();
        return;
    }
    list* cur = head;
    while (i--) cur = cur->next;
    list* p = cur->prev;
    list* p2 = cur->next;
    delete cur;
    p->next = p2;
    p2->prev = p;
}

void list::pop_back() {
    list* cur = head;
    while (cur->next != nullptr) cur = cur->next;
    list* p = cur;
    p = p->prev;
    p->next = nullptr;
    delete cur;
    

}

void list::pop_front() {
    list* tmp = head;
    head = head->next;
    head->prev = nullptr;
    delete tmp;
}

void list::add_index(int i, int a) {
    if (i == 0) {
        push_front(a);
        return;
    }
    if (i + 1 == get_size()) {
        push_back(a);
        return;
    }
    list* cur = head;
    list* p = head;
    while (i--) {
        p = cur;
        cur = cur->next;
    }
    p->next = new list(a, head, p->next, cur->prev);
    cur->prev = p->next;
}

void list::clear() {
    list* cur;
    while (head != nullptr) {
        cur = head;
        head = next;
        delete cur;
    }
}

void list::set_index(int i, int a) {
    list* cur = head;
    while (i--) {
        cur = cur->next;
    }
    cur->a = a;
}

void list::push_front(int a) {
    if (empty) {
        head = new list(a);
        return;
    }
    list* tmp = new list(a, head);
    head->prev = tmp;
    head = tmp;
}

int list::get_size() {
    list* cur = head;
    int ans = 0;
    while (cur != nullptr) {
        ans++;
        cur = cur->next;
    }
    return ans;
}

int list::get_index(int a) {
    list* cur = head;
    while (a--) {
        cur = cur->next;
    }
    return cur->a;
}

void list::push_back(int a) {
    if (empty()) {
        head = new list(a);
        return;
    } 
    list* cur = head;
    while (cur->next != nullptr) cur = cur->next;
    cur->next = new list(a, head, cur);
}

bool list::empty() {
    return head == nullptr;
}
