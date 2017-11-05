/*
 * =====================================================================================
 *
 *       Filename:  3.c
 *
 *    Description:  USTC computer practice 5 code 3
 *
 *        Version:  1.0
 *        Created:  10/31/2017 07:21:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yimin Gu (), guyimin@mail.ustc.edu.cn
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

//int a[15] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987};
int a[15] = {1, 2, 2, 5, 8, 21, 21, 21, 21, 21, 144, 233, 377, 987, 987};
int start, end;
int search(int x)
{
	int l, r, mid;
	l = 0;
	r = 14;
	int ans = -1;
	while(l < r){
		mid = (l + r) / 2;
		if(a[mid] == x){
			ans = mid;
			break;
		}
		if(a[mid] > x) r = mid - 1;
		if(a[mid] < x) l = mid + 1;
	}
	if(a[l] == x) ans = l;
	if(ans == -1) return -1;
	int i = ans;
	while(a[i - 1] == x) i--;
	start = i;
	i = ans;
	while(a[i + 1] == x) i++;
	end = i;
	return ans;
}
int main(void)
{
	int x;
	int pos;
	while(1){
		printf("Enter number to search(-1 to quit)");
		scanf("%d", &x);
		if(x == -1) break;
		if((pos = search(x)) != -1){
			if(start == end) printf("%d found at %d\n", x, pos + 1);
			else printf("%d found between %d and %d\n", x, start + 1, end + 1);
		}
		else printf("Not found\n");
	}
	return 0;
}
