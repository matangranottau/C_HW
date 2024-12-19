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
		if (isalpha(*str)) {
			*str = tolower(*str);
		}
		str++;
	}
}

void sort_str(char str[]) {
	/* 
	sort the string according to ascii table*/
	// create a hist array for all ascii chars (32 - 126)
	char hist[94] = { 0 };
	char idx;
	char* temp = str;
	// load hist
	while (*temp) {
		idx = *temp - ' ';
		hist[idx]++;
		temp++;
	}
	//unload hist
	for (int i = 0; i < 94; i++) {
		while (hist[i] > 0) {
			*str = 32 + i;
			hist[i]--;
			str++;
		}
	}
}

int is_permutation(char* str1, char* str2) {
	/* 
	after sortinf check if the strings are equal
	(see the function strcmp that he talked about in  recitation 6)*/
	if (0 == strcmp(str1, str2)) {
		return 1;
	}
	return 0;
}
void remove_newline(char* str) {
	size_t len = strlen(str);
	if (len > 0 && str[len - 1] == '\n') {
		str[len - 1] = '\0';
	}
}

/*Tests*/
#if 0
int main(){
	char str[10] = "matan";
	sort_str(str);
	printf("%d", is_permutation(str, "aamnt"));
	return 0;
}
#endif

/*Actual Main*/
#if 1
int main() {
	char search_string[MAX_LEN + 1];
	char pool[MAX_POOL][MAX_LEN + 1];
	int pool_size = 0;
	int count = 0;

	printf("Enter the search string:\n"); /* get the search string*/
	//scanf(" %[^\n]", search_string); // no need to validate. scanf reads spaces now
	fgets(search_string,MAX_LEN,stdin);
	remove_newline(search_string);
	make_it_lower(search_string);


	printf("Enter the strings pool:\n"); /*entering the pool until EOF*/
	while (fgets(pool[pool_size], MAX_LEN, stdin) != NULL) {
		remove_newline(pool[pool_size]);
		make_it_lower(pool[pool_size]);

		pool_size++;


	}
	char sorted_search[MAX_LEN + 1]; /* sort every pool*/
	strcpy(sorted_search, search_string);
	sort_str(sorted_search);
	for (int i = 0; i < pool_size; i++) { /* if is permutation add 1*/
		char temp[MAX_LEN + 1];
		strcpy(temp, pool[i]);
		sort_str(temp);
		if (is_permutation(sorted_search, temp)) {
			count++;
		}

	}

	printf("Number of permutations of \"%s\" in the strings pool is: %d\n", search_string, count);

	return 0;




}
#endif // 0

