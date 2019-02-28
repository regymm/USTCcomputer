#include <stdio.h>

int main(int argc,char **argv) {
	FILE *logfp;
	if(!(logfp = fopen("run.log","w")))
		return 1;
	fprintf(logfp,"hello");
	fclose(logfp);
	return 0;
}
