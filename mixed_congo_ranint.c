#include<stdio.h>
#include<conio.h>
int main(){
    int x0,x1,a,c,m,i,n;
    int array[20];

    printf("Enter the number of random number to be generated:");
    scanf("%d",&n);
    printf("\n");

    printf("Enter the seed value x0:");
    scanf("%d",&x0);
    printf("\n");

    printf("Enter the constant multiplier a:");
    scanf("%d",&a);
    printf("\n");

    printf("Enter the increment c:");
    scanf("%d",&c);
    printf("\n");

    printf("Enter the modulus m:");
    scanf("%d",&m);
    printf("\n");

    for ( i = 1; i <=n ; i++)
    {
        x1=(a*x0+c)%m;
        array[i]=x1;
        x0=x1;
    }
    
    printf("The generated random numbers are:");
    for ( i = 1; i <=n; i++)
    {
        printf("%d",array[i]);
        printf("\t");
    }

    getch();
    return 0;
    
}