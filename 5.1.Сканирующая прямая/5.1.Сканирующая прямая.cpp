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

//Задача.
//Дан набор из n отрезков на прямой, заданных координатами начал и концов. Требуется найти любую точку на прямой, покрытую наибольшим количеством отрезков.

int scanline(vector<pair<int, int>> & segments) {
    struct event {
        int x, type;
    };
    // Работает за O(nlogn)
    vector<event> events;

    for (auto & [l, r] : segments) {
        events.push_back({ l, 1 });
        events.push_back({ r, -1 });
    }

    sort(events.begin(), events.end(), [](event a, event b) {
        return (a.x < b.x || (a.x == b.x && a.type > b.type));
    });

    int cnt = 0, res = 0;

    for (event e : events) {
        cnt += e.type;
        res = max(res, cnt);
    }
    return res;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// #Длина объединения отрезков
// Задача. Дан набор из n отрезков на прямой, заданных координатами начал и концов. Требуется найти суммарную длину их объединения.
int findSumLegth(vector<pair<int, int>>& segments) {
    // Работает за O(nlogn)
    struct event {
        int x, type;
    };
    vector<event> events;

    for (auto& [l, r] : segments) {
        events.push_back({ l, 1 });
        events.push_back({ r, -1 });
    }

    sort(events.begin(), events.end(), [](event a, event b) {
        return (a.x < b.x || (a.x == b.x && a.type > b.type));
        });

    int cnt = 0, res = 0, prev = -inf;

    for (event e : events) {
        if (prev != -inf && cnt > 0)
            res += e.x - prev; // весь отрезок [prev, e.x] покрыт cnt отрезками
        cnt += e.type;
        prev = e.x;
    }
    return res;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
// #Скольким отрезкам принадлежит точка
vector<int> scanline(vector<pair<int, int>> segments, vector<int> queries) {
    struct event {
        int x, type, idx;
    };
    int q = (int)queries.size();

    vector<int> ans(q);
    vector<event> events;

    for (auto [l, r] : segments) {
        events.push_back({ l, 1 });
        events.push_back({ r, -1 });
    }

    for (int i = 0; i < q; i++)
        events.push_back({ queries[i], 0, i });

    // при равенстве координат сначала идут добавления, потом запросы, потом удаления
    sort(events.begin(), events.end(), [](event a, event b) {
        return (a.x < b.x || (a.x == b.x && a.type > b.type));
        });

    int cnt = 0;

    for (event e : events) {
        cnt += e.type;
        if (e.type == 0)
            ans[e.idx] = cnt;
    }
    return ans;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    fstream fcin("input.txt");
    int n;
    fcin >> n;
    vector<pair<int, int>> segments;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        fcin >> x >> y;
        segments.push_back({x,y});
    }
    cout << scanline(segments) << "\n";
    cout << findSumLegth(segments) << "\n";


    fstream fcin2("input2.txt");
    int m;
    fcin2 >> m;
    vector<int> queries;
    for (int i = 0; i < m; i++)
    {
        int x;
        fcin2 >> x;
        queries.push_back(x);
    }
    print(scanline(segments, queries));
}
