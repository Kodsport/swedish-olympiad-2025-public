#include <iostream>
#include <vector>
#include <set> 
#include <unordered_map>
#include <map>
#include <algorithm>
#include <cmath>
#include <chrono>

#define all(x)  (x).begin(), (x).end()
#define rall(x)  (x).rbegin(), (x).rend()

using namespace std;

typedef long long ll;

ll linf = 1e15+1;

inline void scoobydoobydoo(){
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

const int MAXN = 2e5+1;
ll arr[MAXN];
ll arrBIT[MAXN];
ll setarrBIT[MAXN];
ll n;

void update_arrBIT(ll node, ll value){
    while (node < MAXN){
        arrBIT[node] += value;
        node += node&(~node+1);
    }
}
ll internal_query_arrBIT(ll node){
    ll sum = 0;
    while (node){
        sum += arrBIT[node];
        node -= node&(~node+1);
    }
    return sum;
}
ll query_arrBIT(ll l, ll r){
    return internal_query_arrBIT(r)-internal_query_arrBIT(l);
}
void initialize_arrBIT(){
    for (ll i = 1; i <= n; i++)update_arrBIT(i, arr[i]);
}


ll lastr = -1;

ll BIT1[20*MAXN], BIT2[20*MAXN];
pair<ll, ll> BITp[4*MAXN];
ll leftOf[4*MAXN], rightOf[4*MAXN];
ll idToNode[4*MAXN];




void update_BIT1(ll id, ll node, ll value){
    node += -leftOf[idToNode[id]]+1;
    ll extra = BITp[id].first;
    ll maxin = BITp[id].second;
    while (node <= maxin-extra+1 && node < 10*MAXN){
        BIT1[node+extra] += value;
        node += node&(~node+1);
    }
}

void update_BIT2(ll id, ll node, ll value){
    node += -leftOf[idToNode[id]]+1;
    ll extra = BITp[id].first;
    ll maxin = BITp[id].second;
    while (node <= maxin-extra+1 && node < 10*MAXN){
        BIT2[node+extra] += value;
        node += node&(~node+1);
    }
}

ll internal_query_BIT1(ll id, ll node){
    ll sum = 0;
    ll extra = BITp[id].first;
    if (node > BITp[id].second-extra+1)node = BITp[id].second-extra+1;
    while (node){
        sum += BIT1[node+extra];
        node -= node&(~node+1);
    }
    return sum;
}

ll query_BIT1(ll id, ll l, ll r){
    return internal_query_BIT1(id, r-leftOf[idToNode[id]]+1)-internal_query_BIT1(id, l-leftOf[idToNode[id]]+1);
}

ll internal_query_BIT2(ll id, ll node){
    ll sum = 0;
    ll extra = BITp[id].first;
    if (node > BITp[id].second-extra+1)node = BITp[id].second-extra+1;
    while (node){
        sum += BIT2[node+extra];
        node -= node&(~node+1);
    }
    return sum;
}

ll query_BIT2(ll id, ll l, ll r){
    return internal_query_BIT2(id, r-leftOf[idToNode[id]]+1)-internal_query_BIT2(id, l-leftOf[idToNode[id]]+1);
}

struct Node {
    ll id;
    set<pair<ll, ll> > LS; //value, position
    set<pair<ll, ll> > RS;
};

Node ST[4*MAXN];
ll indexToNode[MAXN];
ll counter = 1;

Node merge(Node n1, Node n2, ll id){
    Node N; N.id = id;
    auto n1it = n1.LS.end(); n1it--;
    auto n2it = n2.LS.end(); n2it--;
    ll n1m = (*n1it).first;
    ll n2m = (*n2it).first;

    if (n1m == n2m){
        //Lika stora, n1LS bevaras, n2RS bevaras
        N.LS = n1.LS;
        N.RS = n2.RS;
        pair<ll, ll> last = {-1, -1};
        for (auto p1 : N.LS){
            pair<ll, ll> p = p1;
            if (last.first == -1){
                last = p;
                continue;
            }
            ll val = last.first;
            ll diff = p.second-last.second;
            update_BIT1(N.id, p.second, val*diff);
            last = p;
        }
        last = {-1, -1};
        for (auto p1 : N.RS){
            pair<ll, ll> p = p1;
            p.second *= -1;
            if (last.first == -1){
                last = p;
                continue;
            }
            ll val = last.first;
            ll diff = last.second - p.second;
            update_BIT2(N.id, p.second, val*diff);
            last = p;
        }
    }
    else if (n1m > n2m){
        //Vänster är större -> LS bevaras, RS blir till en merge.
        N.LS = n1.LS;
        auto it = n1.RS.lower_bound({n2m, 1000000});

        set<pair<ll, ll> > nRS = n2.RS;
        while (it != n1.RS.end()){
            nRS.insert(*it);
            it++;
        }

        N.RS = nRS;

        pair<ll, ll> last = {-1, -1};
        for (auto p1 : N.LS){
            pair<ll, ll> p = p1;
            if (last.first == -1){
                last = p;
                continue;
            }
            ll val = last.first;
            ll diff = p.second-last.second;
            update_BIT1(N.id, p.second, val*diff);
            last = p;
        }
        last = {-1, -1};
        for (auto p1 : N.RS){
            pair<ll, ll> p = p1;
            p.second *= -1;
            if (last.first == -1){
                last = p;
                continue;
            }
            ll val = last.first;
            ll diff = last.second - p.second;
            update_BIT2(N.id, p.second, val*diff);
            last = p;
        }

    }
    else {
        //Högre är större -> RS bevaras, LS blir merge
        N.RS = n2.RS;

        auto it = n2.LS.lower_bound({n1m, 1000000});

        set<pair<ll, ll> > nLS = n1.LS;
        while (it != n2.LS.end()){
            nLS.insert(*it);
            it++;
        }

        N.LS = nLS;

        pair<ll, ll> last = {-1, -1};
        for (auto p : N.LS){
            if (last.first == -1){
                last = p;
                continue;
            }
            ll val = last.first;
            ll diff = p.second - last.second;
            update_BIT1(N.id, p.second, val*diff);
            last = p;
        }
        last = {-1, -1};
        for (auto p1 : N.RS){
            pair<ll, ll> p = p1;
            p.second *= -1;
            if (last.first == -1){
                last = p;
                continue;
            }
            ll val = last.first;
            ll diff = last.second - p.second;
            update_BIT2(N.id, p.second, val*diff);
            last = p;
        }
    }

    return N;
}

void init_ST(ll l = 1, ll r = n, ll node = 1){
    leftOf[node] = l; rightOf[node] = r;
    if (l == r){
        ST[node].id = ++counter;
        idToNode[counter] = node;

        ST[node].LS.insert({arr[l], l});
        ST[node].RS.insert({arr[l], -l});
        indexToNode[l] = node;
        BITp[ST[node].id] = {lastr+1, lastr+r-l+1};
        lastr = lastr+r-l+1;

        return;
    }
    ll mid = (l+r)>>1;
    init_ST(l, mid, 2*node);
    init_ST(mid+1, r, 2*node+1);
    counter++;
    idToNode[counter] = node;
    BITp[counter] = {lastr+1, lastr+r-l+1};
    lastr = lastr+r-l+1;
    ST[node] = merge(ST[2*node], ST[2*node+1], counter);
}

ll mother_sauce = 0;

vector<Node*> find_mother_nodes(ll l, ll r, ll node = 1){
    mother_sauce++;
    if (leftOf[node] == l && rightOf[node] == r){
        return {&ST[node]};
    }
    ll a = 2*node, b = node*2+1;
    if (r <= rightOf[a])return find_mother_nodes(l, r, a);
    if (l >= leftOf[b])return find_mother_nodes(l, r, b);
    vector<Node*> ret = find_mother_nodes(l, rightOf[a], a);
    vector<Node*> temp = find_mother_nodes(leftOf[b], r, b);
    for (auto e : temp)ret.push_back(e);
    return ret;
}

ll query(ll l, ll r){ //inklusive
    vector<Node*> mothers = find_mother_nodes(l, r); 

    ll maxi = -1;
    for (Node* N : mothers){ //logN
        auto comp_it = N->LS.end(); comp_it--;
        maxi = max(maxi, (*comp_it).first);
    }

    ll vm = -1;
    ll counter = 0;
    for (Node* N : mothers){ //logN
        auto comp_it = N->LS.end(); comp_it--; //O(1)
        if ((*comp_it).first == maxi){
            vm = counter;
            break;
        }
        counter++;
    }

    ll hm = -1;
    counter = 0;
    for (Node* N : mothers){ //logN
        auto comp_it = N->LS.end(); comp_it--;
        if ((*comp_it).first == maxi)hm = counter;
        counter++;
    }

    pair<ll, ll> last = {0, 0};
    ll lsum = 0;
    for (int i = 0; i <= vm; i++){ //logN
        Node* M = mothers[i];
        auto it = M->LS.lower_bound({last.first, 10000000}); //logN
        if (it == M->LS.end())continue;
        pair<ll, ll> p = *it;
        lsum += (p.second-last.second)*last.first;
        it = M->LS.end();
        it--;
        last = *it;
        lsum += query_BIT1(M->id, p.second, last.second); //logN
    }

    last = {0, 0};
    ll rsum = 0;
    for (int i = mothers.size()-1; i >= hm; i--){ //logN
        Node* M = mothers[i];
        auto it = M->RS.lower_bound({last.first, 10000000}); //logN
        if (it == M->RS.end())continue;
        pair<ll, ll> p = *it;
        rsum += (p.second-last.second)*last.first;
        it = M->RS.end();
        it--;
        last = *it;
        rsum += query_BIT2(M->id, -last.second-1, -p.second-1); //logN
    }

    Node* M1 = mothers[vm];
    Node* M2 = mothers[hm];
    auto vit = M1->LS.end(); vit--;
    auto hit = M2->RS.end(); hit--;

    ll msum = 0;
    if ((*vit).second != -(*hit).second){
        msum = (-(*hit).second-(*vit).second)*(*vit).first;
    }
    ll lq = query_arrBIT(l-1, r);

    return lsum+rsum+msum-lq+maxi; //logN
}

int lastwhereis = 0;
pair<ll, ll> lastoo = {0, 0};

void update(ll index, ll increment){
    lastoo = {index, increment};
    ll oldval = query_arrBIT(index-1, index);
    update_arrBIT(index, increment);
    ll nval = oldval+increment;

    for (ll node = indexToNode[index]; node; node /= 2){
        auto lsmax_it = ST[node].LS.end(); 
        lsmax_it--;
        pair<ll, ll> lsmax = *lsmax_it;

        auto rsmax_it = ST[node].RS.end(); 
        rsmax_it--;
        pair<ll, ll> rsmax = *rsmax_it;

        rsmax.second *= -1;

        int where_is = 0;
        // 0 -> LS, 1 -> Mitten, 2 -> RS, 3 -> LS & RS
        if (rsmax == lsmax){
            if (index == rsmax.second)where_is = 3;
            else if (index <= rsmax.second)where_is = 0;
            else where_is = 2;
        }
        else {
            if (index < rsmax.second && index > lsmax.second)where_is = 1;
            else if (index <= lsmax.second)where_is = 0;
            else where_is = 2;
        }
        
        lastwhereis = where_is;

        if (where_is == 1){ //mitten
            //cout << "MITTEN" << endl;
            if (nval > lsmax.first){
                ST[node].LS.insert({nval, index});
                update_BIT1(ST[node].id, index, abs(index-lsmax.second)*lsmax.first);
                ST[node].RS.insert({nval, -index});
                update_BIT2(ST[node].id, index, abs(rsmax.second-index)*rsmax.first);
            } 
        }
        else if (where_is == 3){ //LS och RS, samma värde, ensamt max
            ST[node].LS.erase({oldval, index});
            ST[node].RS.erase({oldval, -index});
            ST[node].LS.insert({nval, index});
            ST[node].RS.insert({nval, -index});
        }
        else if (where_is == 0){
            ll mb1 = query_BIT1(ST[node].id, index-1, index);
            update_BIT1(ST[node].id, index, -mb1);
            auto does_exist = ST[node].LS.find({oldval, index});
            if (does_exist != ST[node].LS.end()) ST[node].LS.erase(does_exist);
            ST[node].LS.insert({nval, index});
            auto it = ST[node].LS.find({nval, index});
            if (it == ST[node].LS.end())cout << "Något har gått fel!" << endl;
            auto lit = it;
            if (it != ST[node].LS.begin()){
                lit--;
                pair<ll, ll> plit = *lit;
                if (plit.first == nval){
                    ST[node].LS.erase(ST[node].LS.find({nval, index}));
                    continue;
                }
            }

            vector<pair<ll, ll> > to_remove;

            lit = it;
            lit++;
            if (lit != ST[node].LS.end()){
                if ((*lit).second < index){
                    ST[node].LS.erase(ST[node].LS.find({nval, index}));
                    continue;
                }
                else if ((*lit).first == nval){
                    to_remove.push_back(*lit);
                }
            }

            lit = ST[node].LS.find({nval, index});
            while (lit != ST[node].LS.begin()){
                lit--;
                if ((*lit).second > index)to_remove.push_back(*lit);
                else break;
            }
            lit = ST[node].LS.find({nval, index});

            for (pair<ll, ll> p : to_remove){
                if (ST[node].LS.find(p) == ST[node].LS.end())cout << "ye" << endl;
                ST[node].LS.erase(p);
                ll mb1 = query_BIT1(ST[node].id, p.second-1, p.second);
                update_BIT1(ST[node].id, p.second, -mb1);
            }


            it = ST[node].LS.find({nval, index});
            if (it == ST[node].LS.end()){
                continue;
            }

            it++;

            if (it == ST[node].LS.end()){
                it--;
                if (it != ST[node].LS.begin()){
                    it--;
                    pair<ll, ll> toleft = *it;
                    update_BIT1(ST[node].id, index, abs(index-toleft.second)*toleft.first);
                    it++;       
                }
                if (nval > rsmax.first){
                    ST[node].RS.insert({nval, -index});
                    ll mb2 = query_BIT2(ST[node].id, index-1, index);
                    update_BIT2(ST[node].id, index, abs(rsmax.second - index)*rsmax.first-mb2);
                } 
            } 
            else {
                pair<ll, ll> toright = *it;
                ll mb1 = query_BIT1(ST[node].id, toright.second-1, toright.second);
                update_BIT1(ST[node].id, toright.second, abs(toright.second-index)*nval-mb1);
                it--;
                if (it != ST[node].LS.begin()){
                    it--;
                    pair<ll, ll> toleft = *it;
                    update_BIT1(ST[node].id, index, abs(index-toleft.second)*toleft.first);
                }
            } 
        }
        else {
            ll mb2 = query_BIT2(ST[node].id, index-1, index);
            update_BIT2(ST[node].id, index, -mb2);
            auto does_exist = ST[node].RS.find({oldval, -index});
            if (does_exist != ST[node].RS.end()) ST[node].RS.erase(does_exist);
            ST[node].RS.insert({nval, -index});
            auto it = ST[node].RS.find({nval, -index});
            if (it == ST[node].RS.end())cout << "Något har gått fel!" << endl;
            auto lit = it;
            if (it != ST[node].RS.begin()){
                lit--;
                pair<ll, ll> plit = *lit;
                if (plit.first == nval){
                    ST[node].RS.erase(ST[node].RS.find({nval, -index}));
                    continue;
                }
            }

            vector<pair<ll, ll> > to_remove;

            lit = ST[node].RS.find({nval, -index});;
            lit++;
            if (lit != ST[node].RS.end()){
                if (-(*lit).second > index){
                    ST[node].RS.erase(ST[node].RS.find({nval, -index}));
                    continue;
                }
                else if ((*lit).first == nval){
                    to_remove.push_back(*lit);
                }
            }
            
            lit = ST[node].RS.find({nval, -index});;

            while (lit != ST[node].RS.begin()){
                lit--;
                if (-(*lit).second < index)to_remove.push_back(*lit);
                else break;
            }
            lit = ST[node].RS.find({nval, -index});;

            for (pair<ll, ll> p : to_remove){
                auto temp_it = ST[node].RS.find(p);
                if (temp_it == ST[node].RS.end())continue;
                ST[node].RS.erase(temp_it);
                ll mb2 = query_BIT2(ST[node].id, -p.second-1, -p.second);
                update_BIT2(ST[node].id, -p.second, -mb2);
            }

            it = ST[node].RS.find({nval, -index});
            it++;
            if (it == ST[node].RS.end()){
                it--;
                if (it != ST[node].RS.begin()){
                    it--;
                    pair<ll, ll> toleft = *it;
                    update_BIT2(ST[node].id, index, abs(index+toleft.second)*toleft.first);
                    it++;
                }
                if ((*it).first > lsmax.first){
                    ST[node].LS.insert({nval, index});
                    ll mb1 = query_BIT1(ST[node].id, index-1, index);
                    update_BIT1(ST[node].id, index, abs(lsmax.second - index)*lsmax.first-mb1);
                }
            } 
            else {
                pair<ll, ll> toright = *it;
                ll mb2 = query_BIT2(ST[node].id, -toright.second-1, -toright.second);
                update_BIT2(ST[node].id, -toright.second, abs(-toright.second-index)*nval-mb2);
                it--;
                if (it != ST[node].RS.begin()){
                    it--;
                    pair<ll, ll> toleft = *it;
                    update_BIT2(ST[node].id, index, abs(index+toleft.second)*toleft.first);                
                }
            } 
        }
    }
    return;
}

int main(){
    scoobydoobydoo();
    ll q; cin >> n >> q;
    for (ll i = 1; i <= n; i++)cin >> arr[i];
    initialize_arrBIT();
    init_ST();


    while (q--){
        ll k, l, r; cin >> k >> l >> r;
        if (k == 2) update(l, r);
        else {
            ll ans = query(l, r);
            if (ans <= -1)cout << 0 << "\n";
            else cout << ans << "\n";
        }
    }
 
    


    return 0;
}