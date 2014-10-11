bool b[11111111];
void era() {
    fill(b,b+1111111,true);
    b[0] = b[1] = false;
    for ( long long  i = 2 ; i < 1111111 ; i++ ) 
        if ( b[i] ) 
            for ( long long  j = i*i ; j < 1111111 ; j+=i ) 
                b[j] = false;
}
