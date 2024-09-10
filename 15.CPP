#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <algorithm> // for fill
using namespace std;

typedef pair<int, int> pii;
vector<pii> adjlist[10000];
int dist[10000];

void dijkstra(int source, int dest)
{
    fill(dist, dist + 10000, 0x7FFFFFFF);  // Using fill to initialize the dist array
    priority_queue<pii, vector<pii>, greater<pii> > Q;
    Q.push(make_pair(0, source));
    pii P, P2;
    int i;

    while (!Q.empty())
    {
        P = Q.top();
        Q.pop();
        int n = P.second;
        int d = P.first;

        if (dist[n] <= d)
            continue;
        
        dist[n] = d;
        
        if (n == dest)
            return;

        int N = adjlist[n].size();
        for (i = 0; i < N; i++)
        {
            P2.first = d + adjlist[n][i].first;
            P2.second = adjlist[n][i].second;
            if (dist[P2.second] > P2.first)
                Q.push(P2);
        }
    }
}

int main()
{
    int t, i, j, T, V;
    scanf("%d", &t);

    while (t--)
    {
        map<string, int> names;
        char name[100];  // Increased buffer size for name
        string Name;

        scanf("%d", &V);

        for (i = 0; i < V; i++)
        {
            adjlist[i].clear();
            scanf("%s", name);
            Name = name;
            names[Name] = i;

            int deg;
            scanf("%d", &deg);
            
            for (j = 0; j < deg; j++)
            {
                int x, y;
                scanf("%d %d", &x, &y); 
                x--;  // 1-based to 0-based index
                adjlist[i].push_back(make_pair(y, x));
            }
        }

        scanf("%d", &T);
        while (T--)
        {
            scanf("%s", name);
            Name = name;
            i = names[Name];

            scanf("%s", name);
            Name = name;
            j = names[Name];

            dijkstra(i, j);
            printf("%d\n", dist[j]);
        }
    }

    return 0;
}