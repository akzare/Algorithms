//for more info refer : https://www.spoj.com/problems/MPOW/
#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;
#define N 51
ll mat[51][51],I[51][51];
void show(ll A[][N],int dim)
{
    for(int i=0;i<dim;i++)
    {
        for(int j=0;j<dim;j++)
            cout<<A[i][j]<<" ";
        cout<<"\n";
    }

}
void mul(ll A[][N],ll B[][N],int dim)
{
    ll res[dim][dim];
    for(int i=0;i<dim;i++)
    {

        for(int j=0;j<dim;j++)
        {
            res[i][j]=0;
            for(int k=0;k<dim;k++)
                res[i][j]=(res[i][j]%MOD+(A[i][k]%MOD * B[k][j]%MOD)% MOD)%MOD;
        }
    }
    for(int i=0;i<dim;i++)
    {
        for(int j=0;j<dim;j++)
        {
            A[i][j]=res[i][j];
        }
    }
}
void power(ll A[][N],int dim,int n)
{
    for(int i=0;i<dim;i++)
    {
        for(int j=0;j<dim;j++)
            if(i==j)
            I[i][j]=1;
        else I[i][j]=0;

    }
    while(n)
    {
        if(n%2)
            mul(I,A,dim),n--;
        else
            mul(A,A,dim),n/=2;

    }
    show(I,dim);
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int m,n;
        cin>>m>>n;
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<m;j++)
                cin>>mat[i][j];

        }
        power(mat,m,n);


    }
    return 0;

}
