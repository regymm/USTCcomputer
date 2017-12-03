/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  mini ACM on nowcoder.com, USTC
 *
 *        Version:  1.0
 *        Created:  12/03/2017 01:55:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>

#define MAX 50010
int n;//num of table
int a[MAX];//max people of each table
short istaken[MAX] = {0};//is table taken?
int m;//number of client
int b[MAX];//number of people in each client
int c[MAX];//price of each cilent
double avg[MAX];
int main()
{
	scanf("%d%d", &n, &m);
	int i, j;
	for(i = 0; i < n; i++)
		scanf("%d", a + i);
	for(i = 0; i < m; i++)
		scanf("%d%d", b + i, c + i);
	for(i = 0; i < m; i++)
		avg[i] = (double)c[i] / b[i];
	//sort avg[i]
	for(i = 0; i < m - 1; i++)
		for(j = m - 1; j > i; j--)
			if(avg[j] > avg[j - 1]){
				double t = avg[j];
				avg[j] = avg[j - 1];
				avg[j - 1] = t;
				int tt = b[j];
				b[j] = b[j - 1];
				b [j - 1] = tt;
				tt = c[j];
				c[j] = c[j - 1];
				c [j - 1] = tt;
//				b[j] ^= b[j - 1];
//				b[j - 1] ^= b[j - 1];
//				b[j] ^= b[j - 1];
//				c[j] ^= c[j - 1];
//				c[j - 1] ^= c[j - 1];
//				c[j] ^= c[j - 1];

			}
	for(i = 0; i < m; i++)
		printf("%d,", b[i]);
	printf("\n");
	for(i = 0; i < m; i++)
		printf("%d,", c[i]);
	printf("\n");
	for(i = 0; i < m; i++)
		printf("%lf,", avg[i]);
	printf("\n");
	int bigger;
	int biggerid;
	int ans = 0;
	for(i = 0; i < m; i++){
		bigger = 100000;
		for(j = 0; j < n; j++){
			if(!istaken[j] && b[i] <= a[j]){
				//can sit
				if(a[j] - b[i] < bigger){
					bigger = a[j] - b[i];
					biggerid = j;
				}
			}
		}
		if(bigger != 100000){
			//sit the client
			ans += c[i];
			istaken[biggerid] = 1;
		}
	}
	printf("%d\n", ans);

	return 0;
}
