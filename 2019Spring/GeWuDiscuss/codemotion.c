void set_row(double *a, double *b, long i, long n)
{
	long j;
	for(j = 0; j < n; j++)
		a[n * i + j] = b[j];
}

/* Sum neighbors of i,j */
long sum(int* val, long i, long j, long n)
{
	long up,down, left, right, sum;
	up =    val[(i-1)*n + j  ];
	down =  val[(i+1)*n + j  ];
	left =  val[i*n     + j-1];
	right = val[i*n     + j+1];
	sum = up + down + left + right;
	return sum;
}

