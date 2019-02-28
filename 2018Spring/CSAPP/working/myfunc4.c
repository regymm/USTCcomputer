// csapp bomblab phase_4 func4
#include <stdio.h>

// a:edi  b:esi  c:edx
int func4(int a, int b, int c)
{
	int d = c;//d:eax
	d = d - b;
	int e = d;//e:ebx
//	if(e > 0)
//		e = 1;
//	else if(e == 0)
//		e = 0;
//	else
//		e = -1;
	e = e >> 31;
	e = e + d;
	e = e >> 1;
	e = e + b;
	if(a < e){
		c = e - 1;
		return func4(a, b, c) + e;
	}
	else{
		if(a > e){
			b = e + 1;
			return func4(a, b, c) + e;
		}
		else{
			return e;
		}
	}
}

int main(){
	int i;
	for(i = 0; i < 14; i++){
		printf("%d:\n", i);
		printf("%d\n", func4(i, 0x0, 0xe));
	}
}
