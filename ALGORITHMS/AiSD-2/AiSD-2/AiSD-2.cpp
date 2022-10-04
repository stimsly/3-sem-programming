#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("input.txt");

struct p {
    int x, y;
}a[100000], b[100000];

bool sortf(p a, p b) {

    return a.x < b.x or (a.x == b.x and a.y < b.y);
}

int dist(p a, p b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}


int find(int l, int r, p (&a)[100000]) {
    if(r - l <= 2){
        if (a[r - 1].y < a[l].y) swap(a[r - 1], a[l]);// sort по y
       // cout << "len: " << r - l << "\na: " << a[l].x << " " << a[l].y << endl << a[r - 1].x << " " << a[r - 1].y << endl;;
        if (r - l == 1) return 9999999;
        else return dist(a[l], a[r - 1]);
    }

    int h1 = find(l, (l + r) / 2, a);
    int h2 = find((l + r) / 2, r, a);
    int h = min(h1, h2); // получаем минимум
    
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
       // cout << a[i].x << " " << a[i].y << endl;
        a[i] = b[i];
    }
   // cout << "h: " << h1 << " " << h2 << endl;

    vector <p> B;
    
   // cout << "B:\n";
    for (int i = l; i < r; i++) {
        if (abs(a[(l + r) / 2].x - a[i].x) < h) {
            B.push_back(a[i]);
           // cout << a[i].x << " " << a[i].y << endl;
        }
    }

    int ans = 9999999;

    for (int i = 0; i < B.size(); i++) {
        for (int j = i + 1; j < B.size(); j++) {
            if (abs(B[i].y - B[j].y) < h) ans = min(ans, dist(B[i], B[j]));
            else break;
        }
    }
   // cout << "ans: " << ans << endl;

    return min(ans, h);


}

int main()
{
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> a[i].x >> a[i].y;
    }
    
    sort(a, a + n, sortf); // sort по x

    int ans = find(0, n, a);

    cout << "Total ans: ";
    cout << ans;
    cout << "\nTotal ans: ";
    cout << sqrt(ans * 1.0);

    return 0;
}