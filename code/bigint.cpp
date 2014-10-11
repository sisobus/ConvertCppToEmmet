class Natural {
    static const int BASE = 100000000;
    static const int BASEDIGS = 8;
    int ndigs;
    int *digs;
    void init(int n,const int *d) {
        while(n>0 && d[n-1]==0) --n;
        ndigs=n;
        digs=new int[n];
        for(int i=0;i<n;++i) digs[i]=d[i];
    }
    Natural(int n,const int *d) { init(n,d); }
    Natural operator<<(int sh) const {
        int n=sh+ndigs;
        int d[n];
        REP(i,sh) d[i]=0;
        REP(i,ndigs) d[i+sh]=digs[i];
        return Natural(n,d);
    }
    public:
    Natural(int x=0) {
        int d[2];
        d[0]=x%BASE;
        d[1]=x/BASE;
        init(2,d);
    }
    Natural(const Natural& a) {
        init(a.ndigs,a.digs);
    }
    Natural(const char *s) {
        int n=strlen(s);
        int nd=n/BASEDIGS+1;
        int d[nd];
        REP(i,nd) {
            d[i]=0;
            FORD(j,BASEDIGS-1,0) {
                int poz=i*BASEDIGS+j;
                if(poz<n) d[i]=10*d[i]+s[n-1-poz]-'0';
            }
        }
        init(nd,d);
    }
    ~Natural() { delete[] digs; }
    Natural &operator=(const Natural& a) {
        delete[] digs;
        init(a.ndigs,a.digs);
        return *this;
    }
    Natural operator+(const Natural& a) const {
        int n=max(ndigs,a.ndigs)+1;
        int d[n];
        REP(i,n) d[i]=0;
        REP(i,n) {
            if(i<ndigs) d[i]+=digs[i];
            if(i<a.ndigs) d[i]+=a.digs[i];
            if(d[i]>=BASE) { d[i]-=BASE; ++d[i+1]; }
        }
        return Natural(n,d);
    }
    Natural &operator+=(const Natural& a) {
        return *this = *this + a;
    }
    Natural operator-(const Natural& a) const {
        int d[ndigs];
        REP(i,ndigs) d[i]=digs[i];
        REP(i,ndigs) {
            if (i < a.ndigs) d[i]-=a.digs[i];
            if (d[i] < 0) {
                d[i]+=BASE;
                --d[i+1];
            }
        }
        return Natural(ndigs,d);
    }
    Natural &operator-=(const Natural& a) {
        return *this = *this - a;
    }
    Natural operator*(const Natural& a) const {
        int n=ndigs+a.ndigs;
        int d[n];
        REP(i,n) d[i]=0;
        REP(i,ndigs) {
            int p=0;
            REP(j,a.ndigs) {
                long long v=(long long)(digs[i])*a.digs[j];
                int v1=v/BASE,v0=v%BASE;
                d[i+j]+=v0+p;
                p=v1+d[i+j]/BASE;
                d[i+j]%=BASE;
            }
            for(int j=i+a.ndigs;p>0;++j) {
                d[j]+=p;
                p=d[j]/BASE;
                d[j]%=BASE;
            }
        }
        return Natural(n,d);
    }
    Natural &operator*=(const Natural&a) {
        return *this = *this * a;
    }
    Natural operator/(const Natural& a) const {
        int n=max(ndigs-a.ndigs+1,0);
        int d[n];
        Natural prod;
        FORD(i,n-1,0) {
            int l=0, r=BASE-1;
            while(l<r) {
                int m=(l+r+1)/2;
                if (*this<prod+(a*m<<i))
                    r=m-1;
                else
                    l=m;
            }
            prod+=a*l<<i;
            d[i]=l;
        }
        return Natural(n,d);
    }

    Natural &operator/=(const Natural& a) {
        return *this = *this / a;
    }
    Natural operator%(const Natural&a) const {
        return *this - *this/a*a;
    }
    Natural &operator%=(const Natural&a) {
        return *this = *this % a;
    }
    Natural sqrt() const {
        int n=(ndigs+1)/2;
        int d[n];
        REP(i,n) d[i]=0;
        Natural sq;
        FORD(i,n-1,0) {
            Natural a(n,d);
            int l=0, r=BASE-1;
            while(l<r) {
                int m=(l+r+1)/2;
                if (*this<sq+(a*2*m<<i)+(Natural(m)*m<<2*i))
                    r=m-1;
                else
                    l=m;
            }
            sq+=(a*2*l<<i)+(Natural(l)*l<<2*i);
            d[i]=l;
        }
        return Natural(n,d);
    }
    Natural operator*(int x) const {
        int n=ndigs+1;
        int d[n];
        long long a=0;
        REP(i,ndigs) {
            a+=digs[i]*(long long)x;
            d[i]=a%BASE;
            a/=BASE;
        }
        d[ndigs]=a;
        return Natural(n,d);
    }
    Natural &operator*=(int x) {
        return *this = *this * x;
    }
    Natural operator/(int x) const {
        int d[ndigs];
        long long a=0;
        FORD(i,ndigs-1,0) {
            a=BASE*a+digs[i];
            d[i]=a/x;
            a%=x;
        }
        return Natural(ndigs,d);
    }
    Natural &operator/=(int x) {
        return *this = *this / x;
    }
    int operator%(int x) const {
        long long a=0;
        FORD(i,ndigs-1,0) {
            a=BASE*a+digs[i];
            a%=x;
        }
        return a;
    }
    bool operator<(const Natural& a) const {
        if(ndigs<a.ndigs) return true;
        if(ndigs>a.ndigs) return false;
        FORD(i,ndigs-1,0) {
            if(digs[i]<a.digs[i]) return true;
            if(digs[i]>a.digs[i]) return false;
        }
        return false;
    }
    bool operator==(const Natural&a) const {
        if(ndigs!=a.ndigs) return false;
        REP(i,ndigs) {
            if(digs[i]!=a.digs[i]) return false;
        }
        return true;
    }
    bool operator>(const Natural&a) const { return a<*this; }
    bool operator<=(const Natural&a) const { return !(a<*this); }
    bool operator>=(const Natural&a) const { return !(*this<a); }
    bool operator!=(const Natural&a) const { return !(*this==a); }
    void write() const {
        if(ndigs==0) printf("0");
        else {
            printf("%d",digs[ndigs-1]);
            FORD(i,ndigs-2,0) printf("%0*d",BASEDIGS,digs[i]);
        }
    }
    void write(char *buf) const {
        if(ndigs==0) sprintf(buf,"0");
        else {
            int pos=0;
            pos+=sprintf(buf,"%d",digs[ndigs-1]);
            FORD(i,ndigs-2,0) pos+=sprintf(buf+pos,"%0*d",BASEDIGS,digs[i]);
        }
    }
};
