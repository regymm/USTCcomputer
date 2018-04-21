int calc(long x)
{
	if(x == 0)
		return 0;
	else
		return (x & 1) + calc(x >> 1);
}
