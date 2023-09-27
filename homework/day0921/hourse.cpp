#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

typedef pair<int, int> P;

const int maxn = 100 + 10;   //棋盘最大的规模
const int dx[8] = { 1,2,2,1,-1,-2,-2,-1 };
const int dy[8] = { 2,1,-1,-2,-2,-1,1,2 };        //移动方位
int vis[maxn][maxn];
int N, sx, sy;                //规模，起点坐标
P ans[maxn * maxn + 10];
int cnt;
vector<P>bad_points;
vector<P>directs;

bool judge(int x, int y)
{
    if (x >= 0 && x < N && y >= 0 && y < N && !vis[x][y])  return true;
    return false;
}

bool cmp(P a1, P a2)
{
    return a1.second < a2.second;     //根据出口排序
}

vector<P> finddirec(int x, int y)
{
    vector<P>direc;
    for (int i = 0; i < 8; i++)
    {
        int xx = x + dx[i], yy = y + dy[i];
        //if (xx == x && yy == y)  continue;
        int count = 0;
        if (judge(xx, yy))
        {
            for (int j = 0; j < 8; j++)
            {
                int xxx = xx + dx[j], yyy = yy + dy[j];
                if (judge(xxx, yyy))  count++;
            }
        }
        direc.push_back(P(i, count));
    }
    sort(direc.begin(), direc.end(), cmp);
    return direc;
}

bool dfs(int x, int y)
{
    if (cnt >= N * N)
    {
        for (int i = 0; i < cnt; i++)
            printf("第%d步：%d %d\n", i, ans[i].first, ans[i].second);
        return true;
    }
    vector<P>directs = finddirec(x, y);
    int len = directs.size();
    for (int i = 0; i < len; i++)
    {
        int xx = x + dx[directs[i].first], yy = y + dy[directs[i].first];
        if (judge(xx, yy))
        {
            vis[xx][yy] = cnt;
            ans[cnt++] = P(xx, yy);
            if (dfs(xx, yy))  return true;   //有一个可行解就返回
            cnt--;
            vis[xx][yy] = false;
        }
    }
    return false;
}

int main()
{
    scanf("%d%d%d", &N, &sx, &sy);
    vis[sx][sy] = true;
    ans[cnt++] = P(sx, sy);
    if (!dfs(sx, sy))  printf("不存在\n");

    return 0;
}