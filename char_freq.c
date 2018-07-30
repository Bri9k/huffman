#include <stdio.h>
#include <stdlib.h>
#define SIZE 256

int freq_array[SIZE] = {0, };
int encoding_array[SIZE];
int ep = 0;
int huff_size = 0;
int count = 0;

typedef struct node {
	char discovered;
	char bit;
	char internal;
	int ascii;
	unsigned int freq;
	struct node *left;
	struct node *right;
} node;

node *huff_array[SIZE];



int anylyse_frequency() {
	int c;

	while ((c = getchar()) != EOF) {
		++freq_array[c];
	}
}

int insert_huff_node(node *key, node *huff_array[], int size) {
	int k = size; 
	int j;
	if (size == 0) {
		huff_array[0] = key;
		return 1;
	}
	for (j = k; j > 0 && key->freq > huff_array[j - 1]->freq; --j) {
		huff_array[j] = huff_array[j - 1];
	}
	huff_array[j] = key;
	++k;
	return k;
}

int build_array(int * freq_array) {

	node *temp;
	int i, j, k;
	int flag = 0;

	for (i = 0; i < SIZE; ++i) {

		if (freq_array[i] > 0) {
			temp = (node *)malloc(sizeof(node));
			temp->bit = 2;
			temp->internal = 0;
			temp->ascii = i;
			temp->freq = freq_array[i];
			temp->left = NULL;
			temp->right = NULL;
			huff_size = insert_huff_node(temp, huff_array, huff_size);
		}

	}
	/* now we have an unsorted array of !internal nodes for all characters having nonzero freqency */
}


int reduce(node *huff_array[], int size) {

	int top = size;
	node *internal;

	while (size > 1) {
		internal = (node *)malloc(sizeof(node));
		internal->bit = 2;
		internal->internal = 1;
		internal->ascii = '#';

		printf("%d:%c:%d\t%d:%c:%d\n", size - 1, huff_array[size - 1]->ascii, huff_array[size - 1]->freq, size - 2, huff_array[size - 2]->ascii, huff_array[size - 2]->freq);
		internal->freq = huff_array[size - 1]->freq + huff_array[size - 2]->freq;

		internal->left = huff_array[size - 2];
		internal->left->bit = 0;

		internal->right = huff_array[size - 1];
		internal->right->bit = 1;

		size -= 1;

		top = insert_huff_node(internal, huff_array, top);
		printf("\n");
		/*for (int i = 0; i < 50; ++i) {
			printf("%c:%d\n", huff_array[i]->ascii, huff_array[i]->freq);
		}
		printf("\n");
		*/
	}
	return top;

}



int traverse(node *arm) {
	if (arm->left != NULL || arm->right != NULL) {
		if (arm->left != NULL) {
			traverse(arm->left);
		}
		if (arm->right != NULL) {
			traverse(arm->right);
		}
		encoding_array[ep++] = 
		printf("%d-%c %d\n", count++, arm->ascii, arm->freq);
	}
	else {
		printf("%d-%c %d\n", count++, arm->ascii, arm->freq);
	}
}






int main()
{
	node *arm;

	anylyse_frequency();
	build_array(freq_array);

	for (int i = 0; i < huff_size; ++i) {
		printf("%d-%c\t%d\n", i, huff_array[i]->ascii, huff_array[i]->freq);
	}
	printf("\n");

	huff_size = reduce(huff_array, huff_size);

	arm = huff_array[0];

	traverse(arm);
	
	for (int i = 0; i < huff_size; ++i) {
		printf("%d-%c\t%d\n", i, huff_array[i]->ascii, huff_array[i]->freq);
	}
	printf("\n");
	// traverse(&huff_array[0]);
	return 0;
}
