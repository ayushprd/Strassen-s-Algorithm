#include <stdio.h>

int findpower(int);

int main() {

    int i, j, k, r1, c1, c2, n, m, order = 1, p=1;

    printf("Enter the order of first matrix : \n");
    scanf("%d%d", &r1, &c1);

    printf("Enter the column of seconf matrix \n") ;          //As for multiplication i * j = j *i
    scanf("%d", &c2);

    int atemp[r1][c1], btemp[c1][c2];

    printf("Enter the elements of the first matrix :\n");
    for(i = 0; i < r1; i++){
      for(j = 0; j < c1; j++){
        scanf("%d", &atemp[i][j]);

      }
    }

    printf("Enter the elements of the second matrix :\n");
    for(i = 0; i < c1; i++){
      for(j = 0; j < c2; j++){
        scanf("%d", &btemp[i][j]);
      }
    }

    if(r1 >= c1 && r1 >= c2)
        n = r1;
    else if(c2 >= r1 && c1 >= c2)                  //finding n for calculating the 2^n
        n = c1;
    else
        n = c2;


    while(n > findpower(order)){
      order = order + 1;
    }

    m = findpower(order);

    int a[m][m], b[m][m], c[m][m];

    for(i = 0; i < m; i++){
      for(j = 0; j < m; j++){
        a[i][j] = 0;
        b[i][j] = 0;
        c[i][j] = 0;
      }
    }

    for(i = 0; i < r1; i++){
      for(j = 0; j < c1; j++){
        a[i][j] = atemp[i][j];
      }
    }

    for(i = 0; i < c1; i++){
      for(j = 0; j < c2; j++){
        b[i][j] = btemp[i][j];
      }
    }

    printf("\n First matrix:");
    for(i = 0;i < m; i++){
        printf("\n\n\n");
        for(j= 0; j < m; j++)
            printf("\t%d",a[i][j]);
    }


    printf("\n\n\nThis is the second matrix:");
    for(i=0;i<m;i++){
        printf("\n\n\n");
        for(j=0;j<m;j++)
            printf("\t%d",b[i][j]);
    }

    strassen(a,b,c,m,m);    //Calling the function.

    printf("\n\n\nThis is the result:");
    for(i=0;i<m;i++){
        printf("\n\n\n");
        for(j=0;j<m;j++){
            printf("\t%d",c[i][j]);
          }
    }


  return 0;
}


int findpower(int n){
  int i, p = 1;
  for(i = 1; i <= n; i++){
    p = 2 * p;
  }
  return (p);
}


int strassen(int *atemp, int *btemp, int *C, int m, int n){
    if(m==2){
        int P=(*atemp+*(atemp+n+1))*(*btemp+*(btemp+n+1));  //P=(atemp[0][0]+atemp[1][1])*(btemp[0][0]+btemp[1][1])
        int Q=(*(atemp+n)+*(atemp+n+1))*(*btemp);   //Q=(atemp[1][0]+atemp[1][1])*btemp[0][0]
        int R=(*atemp)*(*(btemp+1)-*(btemp+n+1));   //R=atemp[0][0]*(btemp[0][1]-btemp[1][1])
        int S=(*(atemp+n+1))*(*(btemp+n)-*btemp);   //S=atemp[1][1]*(btemp[1][0]-btemp[0][0])
        int T=(*atemp+*(atemp+1))*(*(btemp+n+1));   //T=(atemp[0][0]+atemp[0][1])*btemp[1][1]
        int U=(*(atemp+n)-*atemp)*(*btemp+*(btemp+1));  //U=(atemp[1][0]-atemp[0][0])*(btemp[0][0]+btemp[0][1])
        int V=(*(atemp+1)-*(atemp+n+1))*(*(btemp+n)+*(btemp+n+1));  //V=(atemp[0][1]-atemp[1][1])*(btemp[1][0]+btemp[1][1]);

        *C=*C+P+S-T+V;  //C[0][0]=P+S-T+V
        *(C+1)=*(C+1)+R+T;  //C[0][1]=R+T
        *(C+n)=*(C+n)+Q+S;  //C[1][0]=Q+S
        *(C+n+1)=*(C+n+1)+P+R-Q+U;  //C[1][1]=P+R-Q+U
    }

    else{
        m=m/2;
        strassen(atemp,btemp,C,m,n);
        strassen(atemp,btemp+m,C+m,m,n);
        strassen(atemp+m,btemp+m*n,C,m,n);
        strassen(atemp+m,btemp+m*(n+1),C+m,m,n);
        strassen(atemp+m*n,btemp,C+m*n,m,n);
        strassen(atemp+m*n,btemp+m,C+m*(n+1),m,n);
        strassen(atemp+m*(n+1),btemp+m*n,C+m*n,m,n);
        strassen(atemp+m*(n+1),btemp+m*(n+1),C+m*(n+1),m,n);
    }
}
