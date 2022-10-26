#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1e6; // max array size
int a[N];
int b[2*N];

void make_test(vector <int>(&a), int n) {
    for (int i = 0; i < n; i++) a[i] = rand() % 1000000;
}

void make_test(int(&a)[N], int n){
    for (int i = 0; i < n; i++) a[i] = rand() % 1000000;
}

void insertion_sort(int(&a)[N], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (a[j] < a[j - 1]) {
                int t = a[j];
                a[j] = a[j-1];
                a[j-1] = t;
            }
        }
    }
}

void selection_sort(int(&a)[N], int n) {
    for (int i = 0; i < n; i++) {
        int nmin = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[nmin]) nmin = j;
        }
        int t = a[i];
        a[i] = a[nmin];
        a[nmin] = t;
    }
}

void bubble_sort(int (&a)[N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[i]) {
                int t = a[j];
                a[j] = a[i];
                a[i] = t;
            }
        }
    }
}

void merge_sort(int(&a)[N], int l, int r) {
    if (r - l == 1) return;

    int m = (l + r) / 2;
    merge_sort(a, l, m);
    merge_sort(a, m, r);
    
    int left = l;
    int right = (l + r) / 2;

    for (int i = l; i < r; i++) {
        if (left == m) {
            b[i] = a[right++];
        }
        else if (right == r) {
            b[i] = a[left++];
        }
        else {
            if(a[right] < a[left]) b[i] = a[right++];
            else b[i] = a[left++];
        }
    }
    
    for (int i = l; i < r; i++) {
        a[i] = b[i];
    }

    
}

void shell_sort(int (&a)[N], int n) {
    int h = 1;
    while (h < n / 3) {
        h = 3 * h + 1;
    }
    while (h > 0) {
        for (int i = 0; i < h; i++) {
            for (int j = i + h; j < n; j += h) {
                if (a[j] < a[j - h]) {
                    for (int k = j; k >= h; k -= h) {
                        if (a[k] > a[k - h]) break;
                        int t = a[k];
                        a[k] = a[k-h];
                        a[k-h] = t;
                    }
                }
                
            }
        }
        h /= 3;
    }
}

void quick_sort(int (&a)[N], int l, int r) {
    if (l + 1 >= r) return;
    
    int pivot = a[r - 1];
    int left = l;

    for (int i = l; i < r; i++) {
        if (a[i] < pivot) {
            int t = a[i];
            a[i] = a[left];
            a[left++] = t;
        }
    }
    int t = a[r - 1];
    a[r - 1] = a[left];
    a[left] = t;
    quick_sort(a, l, left);
    quick_sort(a, left + 1, r);
}

int sizes[] = { 10000, 50000, 100000, 200000, 500000, 1000000 };
int sizes_sqr[] = { 100, 500, 1000, 5000, 10000, 25000 };

int main()
{
    srand(time(0));
    for (int i = 3; i < 6; i++) {

        int work_time = 0; // total time
        int best_time = 9999999;
        int worst_time = 0;
        int n = sizes_sqr[i]; // array size
        int tests = 100; // test amount

        for (int test = 1; test <= tests; test++) {
            make_test(a, n);

            int start = clock();
            bubble_sort(a, n);
            int end = clock();

            for (int i = 1; i < n; i++) {
                if (a[i] < a[i - 1]) cout << "Wrong test\n";

            }
            work_time += end - start;
            worst_time = max(worst_time, end - start);
            best_time = min(best_time, end - start);
            cout << "Test #" << test << " works for " << end - start << "ms.\n";
        }
        cout << "\n\nBest case for " << n << " is " << best_time << "ms." << endl;
        cout << "Avarage case for " << n << " is " << work_time / tests << "ms." << endl;
        cout << "Worst case for " << n << " is " << worst_time << "ms.\n\n" << endl;
    }
}