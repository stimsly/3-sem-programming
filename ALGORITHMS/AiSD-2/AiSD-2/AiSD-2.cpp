#include <iostream>
#include <algorithm>
#include <fstream>
#include <Windows.h>
#include <vector>

using namespace std;

ifstream fin("input.txt");

struct p {
    int x, y;
}a[100000], b[100000];

bool is_ans_exist = 1;
int total_ans = 9999999;

bool sortf(p a, p b) {

    return a.x < b.x or (a.x == b.x and a.y < b.y);
}

int dist(p a, p b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}


int find(int l, int r, p (&a)[100000]) {
    if(r - l <= 2){
        if (a[r - 1].y < a[l].y) swap(a[r - 1], a[l]);// sort по y
        if (r - l == 1) return 9999999;
        else return dist(a[l], a[r - 1]);
    }

    int h1 = find(l, (l + r) / 2, a);
    int h2 = find((l + r) / 2, r, a);
    int h = min(h1, h2); // получаем минимум
    if (total_ans > h) {
        total_ans = h;
    }


    int left = l;
    int middle = (l + r) / 2;

    for (int i = l; i < r; i++) {
        if (left == (l + r) / 2) b[i] = a[middle++];
        else if (middle == r) b[i] = a[left++];
        else if(a[middle].y < a[left].y) b[i] = a[middle++];
        else b[i] = a[left++];
    }
    //cout << "New group\n";
    for (int i = l; i < r; i++) {
        a[i] = b[i];
      //  cout << a[i].x << " " << a[i].y << endl;
    }
   // cout << "H: " << h << endl << a[(l+r)/2].x << endl;
    vector <p> B;
    //cout << "B:\n";
    for (int i = l; i < r; i++) {
        if (abs(a[(l + r) / 2].x - a[i].x) <= h) {
            B.push_back(a[i]);
      //      cout << a[i].x << " " << a[i].y << endl;
        }
    }

    int ans = h;

    for (int i = 0; i < B.size(); i++) {
        int x = 0;
        for (int j = i + 1; j < B.size(); j++) {
            if (abs(B[i].y - B[j].y) <= h) {
                ans = min(ans, dist(B[i], B[j]));
                total_ans = min(ans, total_ans);
                if (total_ans == ans) x++;
            }
            else break;
        }
        for (int j = i - 1; j >= 0; j--) {
            if (abs(B[i].y - B[j].y) <= h) {
                ans = min(ans, dist(B[i], B[j]));
                total_ans = min(ans, total_ans);
                if (total_ans == ans) x++;
            }
            else break;
        }
        if (x > 1) {
            is_ans_exist = 0;
        }
        else is_ans_exist = 1;
    }
    return min(ans, h);


}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> a[i].x >> a[i].y;
    }
    
    sort(a, a + n, sortf); // sort по x

    int ans = find(0, n, a);

    if (is_ans_exist == 1) {
        cout << "Total ans in sqr: ";
        cout << (total_ans + .0);
        cout << "\nTotal ans: ";
        cout << sqrt(total_ans * 1.0 / 2);
    }
    else {
        cout << "Ответа нет";
    }
    return 0;
}