namespace SegmentTree {
    typedef pair<int,int> ii;
    int a[1111111];
    int mntree[4444444];
    int mxtree[4444444];
    void initialize(int node,int s,int e) {
        if ( s == e ) mntree[node] = mxtree[node] = a[s];
        else {
            int mid = (s+e)>>1;
            initialize(2*node,s,mid);
            initialize(2*node+1,mid+1,e);
            mxtree[node] = max(mxtree[2*node],mxtree[2*node+1]);
            mntree[node] = min(mntree[2*node],mntree[2*node+1]);
        }
    }
    ii query(int node,int s,int e,int i,int j) {
        if ( e < i || s > j ) return ii(-1,-1);
        if ( s >= i && e <= j ) return ii(mxtree[node],mntree[node]);
        int mid = (s+e)>>1;
        ii p1 = query(2*node,s,mid,i,j);
        ii p2 = query(2*node+1,mid+1,e,i,j);
        if ( p1 == ii(-1,-1) ) return p2;
        if ( p2 == ii(-1,-1) ) return p1;
        return ii(max(max(0,p1.first),max(0,p2.first)),min(max(0,p1.second),max(0,p2.second)));
    }
    ii update(int node,int s,int e,int idx,int val) {
        if ( e < idx || idx < s ) return ii(mxtree[node],mntree[node]);
        if ( s == e ) return ii(mxtree[node]=val,mntree[node]=val);
        int mid = (s+e)>>1;
        ii p1 = update(2*node,s,mid,idx,val);
        ii p2 = update(2*node+1,mid+1,e,idx,val);
        return ii(mxtree[node]=max(max(0,p1.first),max(0,p2.first)),
                mntree[node]=min(max(0,p1.second),max(0,p2.second)));
    }
}
