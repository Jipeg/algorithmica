// https://ru.algorithmica.org/cs/decomposition/rollback/
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
const int inf = 1000000;
void print(const vector<int>& a) {
    for (auto& v : a) {
        cout << v << ' ';
    } cout << '\n';
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int c = 300; // ~= sqrt(q)
const int maxn = 10;
int s[maxn]; // [0, r)

struct query { int l, r, x; };
vector<query> buffer; // запросы, не учтенные в префиксных суммах

int sum(int l, int r) {
    int res = s[r + 1] - s[l];
    for (query q : buffer)
        // пересечем запрос суммы со всеми запросами
        res += q.x * max(0, min(r, q.r) - max(l, q.l));
    return res;
}

void rebuild() {
    vector<int> d(n, 0); // массив дельт

    for (query q : buffer) {
        d[q.l] += x;
        d[q.r + 1] -= x;
    }
    buffer.clear();

    int delta = 0, running_sum = 0;
    for (int i = 1; i <= n; i++) {
        p[i] += running_sum;
        delta += d[i];
        running_sum += delta;
    }
}

void upd(int l, int r, int x) {
    buffer.push_back({ l, r, x });
    if (buffer.size() == c)
        // буфер слишком большой; надо пересчитать префиксные суммы и очистить его
        rebuild();
}

int main()
{
    s[0] = 0;
    for (int i = 0; i < n; i++)
        s[i + 1] = s[i] + a[i];

    std::cout << "Hello World!\n";
}
