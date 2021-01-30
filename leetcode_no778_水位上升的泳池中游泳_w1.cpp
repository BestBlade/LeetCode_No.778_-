/* ------------------------------------------------------------------|
在一个 N x N 的坐标方格 grid 中，每一个方格的值 grid[i][j] 表示在位置 (i,j) 的平台高度。

现在开始下雨了。当时间为 t 时，此时雨水导致水池中任意位置的水位为 t 。你可以从一个平台游向四周相邻的任意一个平台，但是前提是此时水位必须同时淹没这两个平台。假定你可以瞬间移动无限距离，也就是默认在方格内部游动是不耗时的。当然，在你游泳的时候你必须待在坐标方格里面。

你从坐标方格的左上平台 (0，0) 出发。最少耗时多久你才能到达坐标方格的右下平台 (N-1, N-1)？

 

示例 1:

输入: [[0,2],[1,3]]
输出: 3
解释:
时间为0时，你位于坐标方格的位置为 (0, 0)。
此时你不能游向任意方向，因为四个相邻方向平台的高度都大于当前时间为 0 时的水位。

等时间到达 3 时，你才可以游向平台 (1, 1). 因为此时的水位是 3，坐标方格中的平台没有比水位 3 更高的，所以你可以游向坐标方格中的任意位置
示例2:

输入: [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
输出: 16
解释:
 0  1  2  3  4
24 23 22 21  5
12 13 14 15 16
11 17 18 19 20
10  9  8  7  6

最终的路线用加粗进行了标记。
我们必须等到时间为 16，此时才能保证平台 (0, 0) 和 (4, 4) 是连通的
 

提示:

2 <= N <= 50.
grid[i][j] 是 [0, ..., N*N - 1] 的排列。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/swim-in-rising-water
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/*
*
*	执行用时：36 ms, 在所有 C++ 提交中击败了69.13%的用户
*	内存消耗：8.5 MB, 在所有 C++ 提交中击败了89.26%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

struct Height {
    int x, y, h;
    Height(int _x, int _y, int _h) :x(_x), y(_y), h(_h) {}
    bool operator< (const Height &that) const {
        return h > that.h;
    }
};

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

int swimInWater(vector<vector<int>>& grid) {
    int now = grid[0][0];
    priority_queue<Height> p;
    int n = grid.size();
    vector<bool> visited(n * n);

    p.emplace(0, 0, now);
    while (!p.empty()) {
        auto [x, y, h] = p.top();
        //Height tmp = p.top();
        //int x = tmp.x;
        //int y = tmp.y;
        //int h = tmp.h;
        if (h > now) {
            now = h;
        }
        p.pop();

        if (x == n - 1 && y == n - 1) {
            break;
        }

        if (visited[x * n + y]) {
            continue;
        }

        visited[x * n + y] = 1;
        for (int i = 0; i < 4; i++) {
            int dx = x + dir[i][0];
            int dy = y + dir[i][1];
            if (dx < n && dx >= 0 && dy < n && dy >= 0) {
                p.emplace(dx, dy, grid[dx][dy]);
            }
        }   
    }
    return now;
}

int main() {
    vector<vector<int>> grid{ {0,1},{2,3} };
    int time = swimInWater(grid);
}