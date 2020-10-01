#include<bits/stdc++.h>
#define ll long long

using namespace std;

ll power(ll a,ll n)
{
    ll res=1;

    while(n)
    {
        if(n&1)
        {
            res=res*a;
            n--;
        }
        a*=a;
        n/=2;
    }
    return res;
}

int main()
{
    ll a,n;
    cin>>a>>n;
    cout<<power(a,n);
    return 0;
}
