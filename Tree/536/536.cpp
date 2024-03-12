#include <cstdio>
#include <cstring>
using namespace std;

//用preorder與inorder建postorder

char preorder[30];
char inorder[30];

void postorder(int preL, int preR, int inL, int inR)
{
	if (preL > preR)
		return;
	int root;
	for (root = inL; preorder[preL] != inorder[root]; ++root);
	postorder(preL + 1, preL + root - inL, inL, root - 1);
	postorder(preL + root - inL + 1, preR, root + 1, inR);
	printf("%c", inorder[root]);
	
}

int main()
{
//	freopen("./in.txt", "r", stdin);
//	freopen("./out.txt", "w", stdout);
	while (scanf("%s %s", preorder, inorder) != EOF)
	{
		int len = strlen(preorder);
		postorder(0, len - 1, 0, len - 1);
		puts("");
	}
	return 0;
}