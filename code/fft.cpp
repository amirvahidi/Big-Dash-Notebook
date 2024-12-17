typedef complex<double> point;
const double pi=acos(-1);
const int mod=998244353;
const int N=(1<<20);

int rev[N];

void FFT(point *A, int n, bool inv){
    int lg=__builtin_ctz(n);
    for (int i=1; i<n; i++){
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
        if (rev[i]<i) swap(A[i], A[rev[i]]);
    }
    for (int len=1; len<n; len<<=1){
        double theta=pi/len;
        if (inv) theta*=-1;
        point wn=point(cos(theta), sin(theta));
        for (int i=0; i<n; i+=2*len){
            point w=1;
            for (int j=i; j<i+len; j++){
                point x=A[j], y=w*A[j+len];
                A[j]=x+y;
                A[j+len]=x-y;
                w*=wn;
            }
        }
    }
    if (inv){
        for (int i=0; i<n; i++) A[i]/=n;
    }
}
