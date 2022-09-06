#include <stdio.h>
#include <stdlib.h>

int Max(int num[]) {
	int max = num[0];
	for (int i = 1; i < 10; i++) {
		if (max < num[i]) max = num[i];
	}
	return max;
}

int Min(int num[]) {
	int min = num[0];
	for (int i = 1; i < 10; i++) {
		if (min > num[i]) min = num[i];
	}
	return min;
}

int length1(char str[]) { // 반복 실이 구하기
	int cnt = 0, index = 0;

	while (str[index++] != NULL) cnt++;

	return cnt;
}

int length2(char str[], int index) { // 순환 길이 구하기
	if (str[index] == NULL) return 0;
	return 1 + length2(str, index + 1);
}

void change(int n, int b, int str[], int* index) {
	while (n >= b) {
		str[(*index)++] = n % b;
		n /= b;
	}
	str[*index] = n;
}

typedef struct TreeNode {
	int key;
	struct TreeNode* left, * right;
}TreeNode;

TreeNode* new_node(int item) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert(TreeNode* node, int item) {
	if (node == NULL) return new_node(item);

	if (item > node->key) node ->right = insert(node->right, item);

	else node->left = insert(node->left, item);

	return node;
}

void inorder(TreeNode* p) { // 중위순회
	if (p == NULL) return;
	else {
		inorder(p->left);
		printf("[%d] ", p->key);
		inorder(p->right);
	}
}

int get_height(TreeNode* node) { // 트리의 높이 구하는 함수
	int height = 0;

	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));

	return height;
}

TreeNode* delete_All(TreeNode* root) { // 노드 전체 free
	if (root == NULL) return root;

	root->left = delete_All(root->left);
	if (root->left != NULL) {
		free(root->left);
		root->left = NULL;
	}

	root->right = delete_All(root->right);
	if (root->right != NULL) {
		free(root->right);
		root->right = NULL;
	}

	return root;
}

int main() {
	while (1) {
		int N;
		printf("[ 0.종료 | 1.최대, 최소값 찾기 | 2.문자열 길이 구하기 | 3.원하는 n진수로 변경 | 4. 이진탐색트리]\n선택 ->");
		scanf("%d", &N);

		if (N == 0) break;

		else if (N == 1) { // 최대값 찾기
			int num[10] = { 9,-3,54,23,51,95,12,83,26,11 };
			printf("1. 최대값  2. 최소값  ->");
			scanf("%d", &N);
			if(N == 1) printf("최대값 : %d\n\n", Max(num));
			else if(N == 2) printf("최소값 : %d\n\n", Min(num));
		}

		else if (N == 2) { // 문자열 길이 구하기 
			char str[40];
			printf("\n길이를 구할 문자열을 입력하시오: ");
			scanf("%s", str);

			printf("1. 반복  2. 순환 ->");
			scanf("%d", &N);

			if (N == 1) {
				printf("문자열의 길이 : %d\n\n", length1(str));
			}

			else if (N == 2) {
				printf("문자열의 길이 : %d\n\n", length2(str, 0));
			}
		}

		else if (N == 3) { // 진수 변환
			int n, b, index = 0, res[100] = { 0, };

			printf("변환 할 숫자:");
			scanf("%d", &n);

			printf("원하는 진수:");
			scanf("%d", &b);

			change(n, b, res, &index);

			printf("%d를 %d진수로 변환한 수:", n, b);

			for (int i = index; i >= 0; i--) {
				if (res[i] < 10) printf("%d", res[i]);
				else printf("%c", res[i] + 55);
			}
			printf("(%d)\n\n", b);
		}

		else if (N == 4) { // 이진탐색트리
			TreeNode* root = NULL;
			int key;

			for (int i = 0; i < 10; i++) {
				printf("이진탐색트리에 삽입할 숫자 입력:");
				scanf("%d", &key);
				root = insert(root, key);
			}

			printf("트리의 높이 : %d \n 중위순회 : ", get_height(root));
			inorder(root);
			printf("\n\n");
			delete_All(root);
		}
	}
	return 0;
}