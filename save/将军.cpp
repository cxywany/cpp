#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 全局变量定义
int b[9][9];		// 棋盘状态：0空位，1白棋，2黑棋
int kx[3], ky[3];	// 国王位置：kx[1]白王x坐标，kx[2]黑王x坐标
string p[9][9];		// 棋子类型：存储每个位置的棋子名称
vector<int> g[100]; // 图的邻接表：g[i]存储节点i能移动到的所有节点

/**
 * 位置编码：将二维坐标(x,y)转换为一维节点编号
 * @param x 横坐标 (1-8)
 * @param y 纵坐标 (1-8)
 * @return 节点编号 (范围11-88)
 */
int id(int x, int y)
{
	return x * 10 + y;
}

/**
 * 位置解码：将一维节点编号转换回二维坐标
 * @param i 节点编号
 * @return pair<x,y> 二维坐标
 */
pair<int, int> pos(int i)
{
	return {i / 10, i % 10};
}

/**
 * 添加移动边：在图中添加从(x1,y1)到(x2,y2)的有向边
 * @param x1,y1 起始位置
 * @param x2,y2 目标位置
 * @param c 己方棋子颜色（用于判断是否能移动到目标位置）
 */
void add(int x1, int y1, int x2, int y2, int c)
{
	// 边界检查：目标位置必须在棋盘内
	if (x2 < 1 || x2 > 8 || y2 < 1 || y2 > 8)
		return;
	// 己方棋子冲突检查：不能移动到己方棋子位置
	if (b[x2][y2] == c)
		return;
	// 添加有向边：从起始位置指向目标位置
	g[id(x1, y1)].push_back(id(x2, y2));
}

/**
 * 构建移动图：根据当前棋盘状态，为每个棋子生成所有可能的移动边
 * 核心思想：将棋子移动规则转化为图中的有向边关系
 */
void build()
{
	// 清空之前的图结构
	for (int i = 0; i < 100; i++)
		g[i].clear();

	// 遍历整个棋盘，为每个棋子建立移动边
	for (int x = 1; x <= 8; x++)
	{
		for (int y = 1; y <= 8; y++)
		{
			if (!b[x][y])
				continue; // 跳过空位置

			string s = p[x][y]; // 棋子类型
			int c = b[x][y];	// 棋子颜色

			if (s == "King")
			{
				// 王：向8个方向各移动1格
				for (int dx = -1; dx <= 1; dx++)
					for (int dy = -1; dy <= 1; dy++)
						if (dx || dy) // 排除原地不动的情况
							add(x, y, x + dx, y + dy, c);
			}
			else if (s == "Queen")
			{
				// 后：8个方向无限制移动，直到遇到棋子或边界
				for (int dx = -1; dx <= 1; dx++)
				{
					for (int dy = -1; dy <= 1; dy++)
					{
						if (!dx && !dy)
							continue; // 排除原地不动
						// 沿着当前方向尽可能远地移动
						for (int k = 1; k < 8; k++)
						{
							int nx = x + k * dx, ny = y + k * dy;
							if (nx < 1 || nx > 8 || ny < 1 || ny > 8)
								break; // 超出边界
							if (b[nx][ny])
							{
								// 遇到棋子：如果是对方棋子可以吃掉，然后停止
								if (b[nx][ny] != c)
									add(x, y, nx, ny, c);
								break;
							}
							// 空位置：可以移动，继续向前
							add(x, y, nx, ny, c);
						}
					}
				}
			}
			else if (s == "Rook")
			{
				// 车：4个方向（上下左右）无限制移动
				int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
				for (int d = 0; d < 4; d++)
				{
					for (int k = 1; k < 8; k++)
					{
						int nx = x + k * dx[d], ny = y + k * dy[d];
						if (nx < 1 || nx > 8 || ny < 1 || ny > 8)
							break; // 超出边界
						if (b[nx][ny])
						{
							// 遇到棋子：可以吃对方棋子，然后停止
							if (b[nx][ny] != c)
								add(x, y, nx, ny, c);
							break;
						}
						// 空位置：继续移动
						add(x, y, nx, ny, c);
					}
				}
			}
			else if (s == "Bishop")
			{
				// 象：4个对角方向无限制移动
				int dx[] = {1, 1, -1, -1}, dy[] = {1, -1, 1, -1};
				for (int d = 0; d < 4; d++)
				{
					for (int k = 1; k < 8; k++)
					{
						int nx = x + k * dx[d], ny = y + k * dy[d];
						if (nx < 1 || nx > 8 || ny < 1 || ny > 8)
							break; // 超出边界
						if (b[nx][ny])
						{
							// 遇到棋子：可以吃对方棋子，然后停止
							if (b[nx][ny] != c)
								add(x, y, nx, ny, c);
							break;
						}
						// 空位置：继续移动
						add(x, y, nx, ny, c);
					}
				}
			}
			else if (s == "Knight")
			{
				// 马：8个L型位置，可以跳过其他棋子
				int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
				int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};
				for (int d = 0; d < 8; d++)
					add(x, y, x + dx[d], y + dy[d], c);
			}
			else if (s == "Pawn")
			{
				// 兵：前进1格或斜前方吃子
				if (c == 1)
				{ // 白兵向上移动（y坐标增加）
					// 前进1格（目标位置必须为空）
					if (y + 1 <= 8 && !b[x][y + 1])
						add(x, y, x, y + 1, c);
					// 斜前方吃子（目标位置必须有对方棋子）
					if (x - 1 >= 1 && y + 1 <= 8 && b[x - 1][y + 1] && b[x - 1][y + 1] != c)
						add(x, y, x - 1, y + 1, c);
					if (x + 1 <= 8 && y + 1 <= 8 && b[x + 1][y + 1] && b[x + 1][y + 1] != c)
						add(x, y, x + 1, y + 1, c);
				}
				else
				{ // 黑兵向下移动（y坐标减少）
					// 前进1格
					if (y - 1 >= 1 && !b[x][y - 1])
						add(x, y, x, y - 1, c);
					// 斜前方吃子
					if (x - 1 >= 1 && y - 1 >= 1 && b[x - 1][y - 1] && b[x - 1][y - 1] != c)
						add(x, y, x - 1, y - 1, c);
					if (x + 1 <= 8 && y - 1 >= 1 && b[x + 1][y - 1] && b[x + 1][y - 1] != c)
						add(x, y, x + 1, y - 1, c);
				}
			}
		}
	}
}

/**
 * 检查指定颜色的国王是否被对方攻击（被将军）
 * @param color 要检查的国王颜色（1白2黑）
 * @return 如果国王被攻击返回true，否则返回false
 */
bool attacked(int color)
{
	int x = kx[color], y = ky[color]; // 获取国王位置

	// 遍历棋盘上所有对方棋子
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			// 如果是对方棋子
			if (b[i][j] && b[i][j] != color)
			{
				// 检查该棋子的所有移动边
				for (int to : g[id(i, j)])
				{
					auto [tx, ty] = pos(to); // 解码目标位置
					// 如果目标位置是己方国王，说明国王被攻击
					if (tx == x && ty == y)
						return true;
				}
			}
		}
	}
	return false; // 国王安全
}

/**
 * 检查指定颜色是否被将死
 * 将死条件：
 * 1. 国王当前被将军（被对方攻击）
 * 2. 尝试所有可能的移动都无法解除将军状态
 *
 * @param color 要检查的颜色（1白2黑）
 * @return 如果被将死返回true，否则返回false
 */
bool checkmate(int color)
{
	// 第一步：检查国王是否被将军
	if (!attacked(color))
		return false; // 没被将军就不是将死

	// 第二步：尝试所有己方棋子的所有可能移动
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			// 找到己方棋子
			if (b[i][j] == color)
			{
				// 尝试该棋子的所有可能移动
				for (int to : g[id(i, j)])
				{
					auto [x2, y2] = pos(to); // 解码目标位置

					// === 模拟移动：保存当前状态 ===
					int old = b[x2][y2];	 // 保存目标位置原来的棋子
					string oldp = p[x2][y2]; // 保存目标位置原来的棋子类型

					// === 执行移动 ===
					b[x2][y2] = b[i][j]; // 移动棋子到目标位置
					p[x2][y2] = p[i][j]; // 移动棋子类型
					b[i][j] = 0;		 // 清空原位置
					p[i][j] = "";		 // 清空原位置棋子类型

					// 如果移动的是国王，更新国王位置
					if (p[x2][y2] == "King")
					{
						kx[color] = x2;
						ky[color] = y2;
					}

					// === 重新构建图并检查攻击状态 ===
					build();					  // 重新根据新棋盘状态构建移动图
					bool safe = !attacked(color); // 检查移动后国王是否安全

					// === 恢复棋盘状态 ===
					b[i][j] = b[x2][y2]; // 恢复原位置棋子
					p[i][j] = p[x2][y2]; // 恢复原位置棋子类型
					b[x2][y2] = old;	 // 恢复目标位置原来的状态
					p[x2][y2] = oldp;	 // 恢复目标位置原来的棋子类型

					// 如果刚才移动的是国王，恢复国王位置
					if (p[i][j] == "King")
					{
						kx[color] = i;
						ky[color] = j;
					}

					// 如果找到了安全的移动，说明不是将死
					if (safe)
						return false;
				}
			}
		}
	}

	// 所有移动都尝试了，仍然无法解除将军，确实是将死
	return true;
}

/**
 * 主函数：程序入口，处理输入输出
 */
int main()
{
	int T; // 测试用例数量
	cin >> T;

	// 处理每个测试用例
	while (T--)
	{
		int n, turn; // n：棋子数量，turn：当前轮次（0白1黑，在本题中不影响判定结果）
		cin >> n >> turn;

		// === 初始化棋盘：清空所有位置 ===
		for (int i = 1; i <= 8; i++)
		{
			for (int j = 1; j <= 8; j++)
			{
				b[i][j] = 0;  // 棋盘位置清空
				p[i][j] = ""; // 棋子类型清空
			}
		}

		// === 读取棋子信息并放置到棋盘上 ===
		for (int i = 0; i < n; i++)
		{
			string piece;	 // 棋子类型：King, Queen, Rook, Bishop, Knight, Pawn
			int color, x, y; // color：颜色(0白1黑)，x,y：棋盘坐标
			cin >> piece >> color >> x >> y;

			color++;		 // 转换颜色编码：0白1黑 → 1白2黑（便于数组索引）
			b[x][y] = color; // 在棋盘上标记棋子颜色
			p[x][y] = piece; // 在棋盘上标记棋子类型

			// 如果是国王，记录其位置（用于快速查找）
			if (piece == "King")
			{
				kx[color] = x;
				ky[color] = y;
			}
		}

		// === 构建移动图 ===
		build(); // 根据当前棋盘状态，为每个棋子生成所有可能的移动边

		// === 检查双方将死状态 ===
		bool white = checkmate(1); // 检查白方是否被将死
		bool black = checkmate(2); // 检查黑方是否被将死

		// === 输出结果 ===
		if (white)
			cout << "White\n"; // 白方被将死
		else if (black)
			cout << "Black\n"; // 黑方被将死
		else
			cout << "Not Checkmate\n"; // 双方都没有被将死
	}

	return 0;
}