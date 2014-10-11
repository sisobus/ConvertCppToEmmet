const int inf = 1<<20;
int d[111][111];
void floyd(int n) {
    for ( int i = 0 ; i < 111 ; i++ ) 
        for ( int j = 0 ; j < 111 ; j++ ) 
            d[i][j] = inf;
    for ( int i = 0 ; i < E ; i++ ) {
        int t1,t2,t3;
        d[t1][t2] = t3;
    }
    for ( int i = 0 ; i < n ; i++ ) 
        d[i][i] = 0;
    for ( int k = 0 ; k <= n ; k++ ) {
        for ( int i = 0 ; i < n ; i++ ) 
            for ( int j = 0 ; j < n ; j++ ) 
                if ( d[i][j] > d[i][k]+d[k][j] ) 
                    d[i][j] = d[i][k]+d[k][j];
    }
}
