#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *Tree;//����TreeNode��ָ���Tree
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
	if (!T) T = NewNode(V);//���TΪNULL���½��ڵ�
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
	while (b){//��ֹ������ͬԪ��
		printf("Please enter %d elements:\n", N);
		for (i = 0; i < N; i++){
			scanf_s("%d", &V);//����Ԫ��
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
	if (T->flag){//���ڽڵ����Ѿ��Ա���ͨ����Ԫ��
		if (V < T->v) return check(T->Left, V);
		else if (V>T->v) return check(T->Right, V);
		else return 0;//���������Ѿ����ڵ�Ԫ�أ��Ͳ��ɶ������ˣ��϶�����false
	}
	else{
		if (V == T->v){
			T->flag = 1;//������V��������ȷλ�ã�����Ҫ����1������Ҫ�ڱ�׼�������λ�ò����Ա�check����Ԫ��
			return 1;
		}
		else return 0;//��Ӧλ���ϵ�Ԫ�ز�һ��������false
	}
}

int Judge(Tree T, int N)
{
	int i, V, flag = 0;//flag==0����Ŀǰ��һ�£�1�����Ѿ���һ�£�������Ҫ�����������������ŷ��Ͻ���ϰ�ߣ�
						//����check���flag��һ���£�
	for (i = 0; i < N; i++){
		scanf_s("%d", &V);
		if ((!flag) && (!check(T, V))) flag = 1;
	}
	if (flag) return 0;
	else return 1;
}

void ResetT(Tree T)// ���T�и�����flag���
{
	if (T->Left) ResetT(T->Left);
	if (T->Right) ResetT(T->Right);
	T->flag = 0;
}

void FreeTree(Tree T)//�ͷ�T�Ŀռ�
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
	scanf_s("%d", &N);//�����һ������Ԫ�ظ���
	while (N){
		printf("Please enter the number of Trees to compare: ");
		scanf_s("%d", &L);//����Ҫ�Աȵ����ĸ���
		T = MakeTree(N);//������׼��T
		for (i = 0; i < L; i++){
			printf("Please enter No.%d array (%d totally):\n", i + 1, L);
			if (Judge(T, N)) printf("Yes,they are same.\n");
			else printf("No, they are different!\n");
			ResetT(T);/*���T�еı��flag*/
		}
		FreeTree(T);//�ͷű�׼��T
		printf("Please enter the number of elements (0 to exist): ");
		scanf_s("%d", &N);//������һ������Ԫ�ظ���
	}
	return 0;
}