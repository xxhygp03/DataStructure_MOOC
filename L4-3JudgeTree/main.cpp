#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *Tree;//定义TreeNode的指针叫Tree
struct TreeNode{
	int v;
	Tree Left, Right;
	int flag;
};

Tree NewNode(int V)
{
	Tree T = (Tree)malloc(sizeof(struct TreeNode));
	T->v = V;
	T->Left = T->Right = NULL;
	T->flag = 0;
	return T;
}

Tree Insert(Tree T, int V)
{
	if (!T) T = NewNode(V);//如果T为NULL则新建节点
	else{
		if (V > T->v)
			T->Right = Insert(T->Right, V);
		else
			T->Left = Insert(T->Left, V);
	}
	return T;
}

Tree MakeTree(int N)
{
	Tree T;
	int i, j, V, c, b;
	int* Vset = (int*)malloc(sizeof(int)*N);

	b = 1;
	T = NULL;
	while (b){//防止出现相同元素
		printf("Please enter %d elements:\n", N);
		for (i = 0; i < N; i++){
			scanf_s("%d", &V);//输入元素
			Vset[i] = V;
		}

		for (i = 0; i < N; i++){
			V = Vset[i];
			c = 0;
			for (j = 0; j < N; j++){
				if (V == Vset[j]){
					c++;
				}
			}
			if (c>1){
				printf("Error: there are more than one element equals %d, please enter again...\n", V);
				break;
			}
			if (i == N - 1){
				b = 0;
			}
		}
	}

	for (i = 0; i < N; i++){
		T = Insert(T, Vset[i]);
	}
	free(Vset);
	return T;
}

int check(Tree T, int V)
{
	if (T->flag){//所在节点是已经对比且通过的元素
		if (V < T->v) return check(T->Left, V);
		else if (V>T->v) return check(T->Right, V);
		else return 0;//即出现了已经存在的元素，就不成二叉树了，肯定返回false
	}
	else{
		if (V == T->v){
			T->flag = 1;//当发现V出现在正确位置，不仅要返回1，而且要在标准树的这个位置插旗以便check后续元素
			return 1;
		}
		else return 0;//相应位置上的元素不一样，返回false
	}
}

int Judge(Tree T, int N)
{
	int i, V, flag = 0;//flag==0代表目前还一致，1代表已经不一致（但还是要允许把整个数组输完才符合交互习惯）
						//（和check里的flag不一回事）
	for (i = 0; i < N; i++){
		scanf_s("%d", &V);
		if ((!flag) && (!check(T, V))) flag = 1;
	}
	if (flag) return 0;
	else return 1;
}

void ResetT(Tree T)// 清除T中各结点的flag标记
{
	if (T->Left) ResetT(T->Left);
	if (T->Right) ResetT(T->Right);
	T->flag = 0;
}

void FreeTree(Tree T)//释放T的空间
{
	if (T->Left) FreeTree(T->Left);
	if (T->Right) FreeTree(T->Right);
	free(T);
}

int main()
{
	int N, L, i;
	Tree T;

	printf("Please enter the number of elements (0 to exist): ");
	scanf_s("%d", &N);//输入第一棵树的元素个数
	while (N){
		printf("Please enter the number of Trees to compare: ");
		scanf_s("%d", &L);//输入要对比的树的个数
		T = MakeTree(N);//建立标准树T
		for (i = 0; i < L; i++){
			printf("Please enter No.%d array (%d totally):\n", i + 1, L);
			if (Judge(T, N)) printf("Yes,they are same.\n");
			else printf("No, they are different!\n");
			ResetT(T);/*清除T中的标记flag*/
		}
		FreeTree(T);//释放标准树T
		printf("Please enter the number of elements (0 to exist): ");
		scanf_s("%d", &N);//输入下一棵树的元素个数
	}
	return 0;
}
