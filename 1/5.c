#include <stdio.h>

int main()
{
	char c1,c2,c3,c4;
	scanf("%c%c", &c1, &c2);
	getchar();
	c3=getchar(); c4=getchar();
	printf("%c %c %c %c\n", c1, c2, c3, c4);
	printf("%c, %d\n", c1, c1);
	printf("%d, %d\n", sizeof(c1), sizeof("1234"));
	return 0;
}
