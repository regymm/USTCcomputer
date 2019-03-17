void arith()
{
	int a, b, c, d;
	c = a + b;
	d = a << b;
	double aa, bb, cc, dd;
	cc = aa * bb;
	dd = aa / bb;
}
int pointers(int* a, int* b)
{
	int c;
	c = *a;
	*b = *a;
	return c;
}
int function(int a, int b)
{
	arith();
	int c;
	c = a + b;
	return c;
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
	int b;
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
