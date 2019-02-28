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
#include <math.h>

typedef struct TreeNode{
	struct TreeNode *left;
	struct TreeNode *right;
	int val;
}TreeNode;
int TreeDepth(TreeNode *pRoot)
{
	if(pRoot == NULL) return 0;
	int dep1,dep2;
	dep1 = TreeDepth(pRoot->left);
	dep2 = TreeDepth(pRoot->right);
	return (dep1 > dep2) ? (dep1 + 1) : (dep2 + 1);
}
int main()
{
	printf("%d\n", TreeDepth(NULL));
	return 0;
}
