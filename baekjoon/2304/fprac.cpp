#include <iostream>
#include <queue>
#include <map>

using namespace std;

typedef struct s_node
{
	int height;
	int coordinate;

	s_node(int h, int c) : height(h), coordinate(c) {}

	bool operator<(const s_node node) const
	{
		return (this->height > node.height);
	}
} t_node;

int n;
int area = 0;
map<int, int> coorInOrder;
priority_queue<t_node> heightInOrder;

void getMinArea(int depth)
{
	
}

int main(void)
{
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		int coor, hei;
		cin >> coor >> hei;

		coorInOrder.insert({coor, hei});
		t_node newNode(hei, coor);
		heightInOrder.push(newNode);
	}

	// for (int i = 0; i < n; i++)
	// {
	// 	t_node newNode = heightInOrder.top();
	// 	heightInOrder.pop();
	// 	cout << newNode.height << ", " << newNode.coordinate << endl;
	// }
	getMinArea(0);
}