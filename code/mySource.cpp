#include <cstdio>
#include <ctime>
#define MAX_SIZE 100
#define NO_TIME
#define SOLVE_FAST

const bool DEBUG = false;
int solve() {
    int ret = 0;
    for ( int i = 1 ; i <= MAX_SIZE ; i++ ) 
        if ( !(i%5) || !(i%8) ) {
            ret += i;
            if ( DEBUG ) 
                printf("%d ",i);
        }
    return ret;
}
int solveFast() {
    int ret = 0;
    for ( int i = 5 ; i <= MAX_SIZE ; i += 5 ) 
        ret += i ;
    for ( int i = 8 ; i <= MAX_SIZE ; i += 8 ) 
        if ( (i%5) != 0 ) 
            ret += i;
    return ret;
}

int main() {
    clock_t before,after;
    double calculateTime;
    int ans;

#ifndef SOLVE_FAST
    before = clock();
    ans    = solve();
    after  = clock();
    calculateTime = (double)(after-before)/CLOCKS_PER_SEC;
    printf("%d\n",ans);
    #ifndef NO_TIME
        printf("time : %lf\n",calculateTime);
    #endif
#endif

#ifdef SOLVE_FAST
    before = clock();
    ans    = solveFast();
    after  = clock();
    calculateTime = (double)(after-before)/CLOCKS_PER_SEC;
    printf("%d\n",ans);
    #ifndef NO_TIME
        printf("time : %lf\n",calculateTime);
    #endif
#endif
    return 0;
}
