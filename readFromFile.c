#include <stdio.h>
#include <string.h>
#include "pbc/pbc.h"
#include "gmp.h"
#include "gcrypt.h"
#include <time.h>

int main(void)
{
	FILE *fp=fopen("zhangParam.txt", "r");
	if (fp == NULL){
  	fprintf(stderr, "Can't open file %s!\n", "zhangParam");
  	exit(1);
	}

	int length =270;
	char *name, *value, line[length];
	const char s[2] = "=";
	for (int count = 0; count < 4; count++){
   if (fgets(line,length,fp)==NULL)
      break;
   else {

      name = strtok(line, s);
      value = strtok(NULL, s);
  	}
		printf("name :%s\n", name);
		printf("value :%s\n", value);
	}

	printf("success\n");
	fclose(fp);
	return 0;
}
