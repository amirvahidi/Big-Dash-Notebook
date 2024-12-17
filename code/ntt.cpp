ll powmod(ll a, ll b){
    ll res=1;
    for (; b; b>>=1, a=a*a%mod) if (b&1) res=res*a%mod;
    return res;
}
inline void fix(ll &x){
    if (x<0) x+=mod;
    if (x>=mod) x-=mod;
}
void NTT(ll *A, int n, bool inv){
    int lg=__builtin_ctz(n);
    for (int i=1; i<n; i++){
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
        if (rev[i]<i) swap(A[i], A[rev[i]]);
    }
    for (int len=1; len<n; len<<=1){
        ll wn=powmod(5, mod/2/len);
        if (inv) wn=powmod(wn, mod-2);
        for (int i=0; i<n; i+=2*len){
            ll w=1;
            for (int j=i; j<i+len; j++){
                ll x=A[j], y=w*A[j+len]%mod;
                fix(A[j]=x+y);
                fix(A[j+len]=x-y);
                w=w*wn%mod;
            }
        }
    }
    if (inv){
        ll nn=powmod(n, mod-2);
        for (int i=0; i<n; i++) A[i]=A[i]*nn%mod;
    }
}