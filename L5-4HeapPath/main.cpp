#include <stdio.h>

#define MAXN 1001
#define MINH -10001

int H[MAXN], size;

void Create() //建立一个空堆
{
	size = 0;
	H[0] = MINH;//设置哨兵
}

void Insert(int X)//将X插入堆H
{

	int i;

	for (i = ++size; H[i / 2] > X; i /= 2)
		H[i] = H[i / 2];
	H[i] = X;
}

int main()
{
	int n, m, x, i, j;

	printf("Please enter the size of heap and the number of searching times: ");
	scanf_s("%d %d", &n, &m);
	Create();
	printf("Please enter %d elements into the heap:\n",n);
	for (i = 0; i < n; i++){
		scanf_s("%d", &x);
		Insert(x);
	}
	printf("Please enter the %d subscripts to search: ", m);
	for (i = 0; i < m; i++){
		scanf_s("%d", &j);
		printf("The path of script %d is:\n",j);
		while (j>0){
			printf("%d ", H[j]);
			j /= 2;
		}
		printf("\n");
	}


	return 0;
}