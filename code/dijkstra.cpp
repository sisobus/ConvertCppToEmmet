typedef pair<int,int> ii;
vector<ii> v[111];
const int inf = 1<<30;
int dijkstra(int st,int ed) {
    int d[111]={};
    fill(d,d+111,inf);
    priority_queue<ii,vector<ii>,greater<ii> > pq;
    d[st] = 0;
    pq.push(ii(d[st],st));
    while ( !pq.empty() ) {
        ii now = pq.top();pq.pop();
        int cur = now.second;
        if ( d[cur] < now.first ) continue;
        for ( int i = 0 ; i < v[cur].size() ; i++ ) {
            ii next = v[cur][i];
            if ( d[next.first] > d[cur]+next.second ) {
                d[next.first] = d[cur]+next.second;
                pq.push(ii(d[next.first],next.first));
            }
        }
    }
    return d[ed];
}
