int a, b, c, d;
double aa, bb, cc, dd;

void arith()
{
//	int a, b, c, d;
	c = a + b;
	d = a << b;
//	double aa, bb, cc, dd;
	cc = aa * bb;
	dd = aa / bb;
}
int pointers(int* pa, int* pb)
{
	c = *pa;
	return c;
}
int function(int a, int b)
{
	arith();
	pointers(&a, &b);
	return 0x50;
}
int loop()
{
	int i;
	int sum = 0;
	for(i = 0; i < 100; i++)
		sum += i;
	return sum;
}
int condition(int a)
{
	if(a > 0)
		b = 1;
	else if(a < -1)
		b = 1;
	else
		b = 0;
	return b;
}
int main()
{
	return 0;
}
