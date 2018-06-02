
//
//  main.c
//  Runge-Kutta四阶
//
//  Created by WH on 2018/6/1.
//  Copyright © 2018年 WH. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#define f(x,y)(x/y)//dy/dx=f(x,y)
int main() {
    int m,i;
    double a,b,y0;
    double xn,yn,yn1;
    double k1,k2,k3,k4;
    double h;
    printf("\nInput the begin and end of x: ");
    scanf("%lf%lf",&a,&b);
    printf("Input the y value at %f: ",a);
    scanf("%lf",&y0);
    printf("Input m value [divide(%f,%f)]: ",a,b);
    scanf("%d",&m);
    if(m<=0){
        printf("Please input a number larger than 1.\n");
        return 1;
    }
    h=(b-a)/m;
    xn=a;
    yn=y0;
    for(i=1;i<=m;i++){
        k1=f(xn,yn);
        k2=f((xn+h/2),(yn+h*k1/2));
        k3=f((xn+h/2),(yn+h*k2/2));
        k4=f((xn+h),(yn+h*k3));
        yn1=yn+h/6*(k1+2*k2+2*k3+k4);
        xn+=h;
        printf("x%d=%f,y%d=%f\n",i,xn,i,yn1);
        yn=yn1;
    }
    return 0;
}
