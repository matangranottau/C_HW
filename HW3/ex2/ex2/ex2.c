#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>


#define MAX_LEN 10
#define MAX_POOL 20


void make_it_lower(char* str) {
	/*
	check if the character is letter anf if indeed make it lower */
	while (*str) {
		*str = tolower(*str);
		str++ ;
	}
}

void sort_str(char* str) {
	/* 
	sort the string according to ascii table*/
}

int is_permutation(char* str1, char* str2) {
	/* 
	after sortinf check if the strings are equal
	(see the function strcmp that he talked about in  recitation 6)*/
}

int main() {
	char search_string[MAX_LEN + 1];
	char pool[MAX_POOL][MAX_LEN + 1];
	int pool_size = 0;
	int count = 0;

	printf("Enter the search string:\n"); /* get the search string*/
	scanf("%10s", search_string);
	make_it_lower(search_string);

	
	printf("Enter the strings pool:\n"); /*entering the pool until EOF*/
	while (pool < MAX_LEN && scanf("%10s", pool[pool_size]) != EOF) {
		make_it_lower(pool[pool_size]);
		pool_size++;


	}
	char sorted_search[MAX_LEN + 1]; /* sort every pool*/
	strcpy(sorted_search, search_string);
	sort_str(sorted_search);

	for (int i = 0; i < pool; i++) { /* if is permutation add 1*/
		char temp[MAX_LEN + 1];
		strcpy(temp, pool[i]);
		if (is_permutation(sorted_search, temp)) {
			count++;
		}

	}

	printf("Number of permutations of \"%s\" in the strings pool is: %d\n", search_string, count);

	return 0;




}