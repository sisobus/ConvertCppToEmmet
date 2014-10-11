bool binarySearch(int key,int *a,int n) {
    int le = 0,ri = n-1;
    while ( le <= ri ) {
        int mid = (le+ri)>>1;
        if ( a[mid] == key ) return true;
        else if ( a[mid] > key ) ri = mid-1;
        else le = mid+1;
    }
    return false;
}
