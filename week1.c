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

int length1(char str[]) { // �ݺ� ���� ���ϱ�
	int cnt = 0, index = 0;

	while (str[index++] != NULL) cnt++;

	return cnt;
}

int length2(char str[], int index) { // ��ȯ ���� ���ϱ�
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

void inorder(TreeNode* p) { // ������ȸ
	if (p == NULL) return;
	else {
		inorder(p->left);
		printf("[%d] ", p->key);
		inorder(p->right);
	}
}

int get_height(TreeNode* node) { // Ʈ���� ���� ���ϴ� �Լ�
	int height = 0;

	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));

	return height;
}

TreeNode* delete_All(TreeNode* root) { // ��� ��ü free
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
		printf("[ 0.���� | 1.�ִ�, �ּҰ� ã�� | 2.���ڿ� ���� ���ϱ� | 3.���ϴ� n������ ���� | 4. ����Ž��Ʈ��]\n���� ->");
		scanf("%d", &N);

		if (N == 0) break;

		else if (N == 1) { // �ִ밪 ã��
			int num[10] = { 9,-3,54,23,51,95,12,83,26,11 };
			printf("1. �ִ밪  2. �ּҰ�  ->");
			scanf("%d", &N);
			if(N == 1) printf("�ִ밪 : %d\n\n", Max(num));
			else if(N == 2) printf("�ּҰ� : %d\n\n", Min(num));
		}

		else if (N == 2) { // ���ڿ� ���� ���ϱ� 
			char str[40];
			printf("\n���̸� ���� ���ڿ��� �Է��Ͻÿ�: ");
			scanf("%s", str);

			printf("1. �ݺ�  2. ��ȯ ->");
			scanf("%d", &N);

			if (N == 1) {
				printf("���ڿ��� ���� : %d\n\n", length1(str));
			}

			else if (N == 2) {
				printf("���ڿ��� ���� : %d\n\n", length2(str, 0));
			}
		}

		else if (N == 3) { // ���� ��ȯ
			int n, b, index = 0, res[100] = { 0, };

			printf("��ȯ �� ����:");
			scanf("%d", &n);

			printf("���ϴ� ����:");
			scanf("%d", &b);

			change(n, b, res, &index);

			printf("%d�� %d������ ��ȯ�� ��:", n, b);

			for (int i = index; i >= 0; i--) {
				if (res[i] < 10) printf("%d", res[i]);
				else printf("%c", res[i] + 55);
			}
			printf("(%d)\n\n", b);
		}

		else if (N == 4) { // ����Ž��Ʈ��
			TreeNode* root = NULL;
			int key;

			for (int i = 0; i < 10; i++) {
				printf("����Ž��Ʈ���� ������ ���� �Է�:");
				scanf("%d", &key);
				root = insert(root, key);
			}

			printf("Ʈ���� ���� : %d \n ������ȸ : ", get_height(root));
			inorder(root);
			printf("\n\n");
			delete_All(root);
		}
	}
	return 0;
}