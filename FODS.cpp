/* Coded by harshcooljn */

#include <bits/stdc++.h>
#include <iostream>
#include <stdint.h>
#include <ios>
#include <iomanip>
#include <numeric>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <queue>
#include <utility>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <string>
using namespace std;
typedef long long int ll;
typedef long double ld;
typedef unsigned long long int ull;
typedef pair<ll, ll> pll;
#define vll vector<ll>
#define vstr vector<string>
#define vvll vector<vector<ll> >
#define vpll vector<pair<ll,ll> >
#define endl '\n'
#define vin(v,a,n) for(ll i=a;i<n;i++){cin>>v[i];}
#define vinp(v,n) for(ll i=0;i<n;i++){ll x;cin>>x;v.push_back(x);}
#define pvec(v) for(auto &e: v){cout << e << " ";}cout<<endl;
#define pvecp(v) for (ll i=0;i<v.size();i++){cout << v[i].first << "," << v[i].second << " \n"[i==v.size()-1];}
#define parr(a,n) for(ll i=0;i<n;i++){cout << a[i] << "";}
#define parr1(a,n) for(ll i=1;i<=n;i++){cout << a[i] << "";}
#define yes cout<<"YES"<<endl;
#define full(v) v.begin(),v.end()
#define debug(x) cout<<x<<", ";
#define print(x) cout<<x<<endl;
#define fr(i,a,n) for(ll i=a;i<n;i++)
#define fr_(i,n,a) for (ll i=n;i>=a;i--)
#define no cout<<"NO"<<endl;
#define spc ' '
#define nline cout<<endl;
#define fileIO freopen("input.txt","r",stdin);freopen("output.txt","w",stdout)
#define fastIO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

void find_closure(set<ll> attributes, map<set<ll>, set<ll> >& fd, set<ll>& closure, ll total, set<set<ll> >& candidate_keys) {
    closure.clear();
    for (auto& e : attributes) {
        closure.insert(e);
    }
    map<set<ll>, set<ll> > already_used;
    while (1) {
        bool over = true;
        for (auto& r : fd) {
            if (already_used.find(r.first) != already_used.end()) {
                continue;
            }
            bool contained = true;
            for (auto& e : r.first) {
                if (attributes.find(e) == attributes.end()) {
                    contained = false;
                    break;
                }
            }
            if (contained) {
                over = false;
                already_used.insert(r);
                for (auto& e : r.second) {
                    closure.insert(e);
                    attributes.insert(e);
                }
            }
        }
        if (over || (closure.size() == total)) {
            break;
        }
    }
}

void test_all_combos(multiset<pair<ll, ll> >& mt, multiset<pair<ll, ll>>::iterator startit, map<set<ll>, set<ll> >& fd, set<set<ll> >& candidate_keys, ll total, set<ll>& cur, set<set<ll> >& found) {
    set<ll> closure;
    for (auto it = startit;it != mt.end();it++) {
        auto p = *it;
        cur.insert(p.second);
        if ((!cur.empty()) && (found.find(cur) == found.end())) {
            find_closure(cur, fd, closure, total, candidate_keys);
            found.insert(cur);
            if (closure.size() == total) {
                candidate_keys.insert(cur);
            }
        }
        ++it;
        test_all_combos(mt, it, fd, candidate_keys, total, cur, found);
        cur.erase(p.second);
        if ((!cur.empty()) && (found.find(cur) == found.end())) {
            find_closure(cur, fd, closure, total, candidate_keys);
            found.insert(cur);
            if (closure.size() == total) {
                candidate_keys.insert(cur);
            }
        }
        test_all_combos(mt, it, fd, candidate_keys, total, cur, found);
        it--;
    }
}


void Solve(ll t10) {
    map<string, ll> hash;
    map<ll, string> unhash;
    ll total;
    // cout << "Enter the number of attributes in the relation: ";
    cin >> total;
    ll hashi = 0;
    fr(i, 0, total) {
        // cout << "Enter attribute: ";
        string att;
        cin >> att;
        // cout << att << ':' << hashi << endl;
        unhash[hashi] = att;
        hash[att] = hashi++;
    }
    ll n;
    // cout << "Enter the number of FDs: ";
    cin >> n;
    map<set<ll>, set<ll> > fd;
    map<ll, ll> lcnt;
    multiset<pair<ll, ll> > mt;
    // given a set of FDs , find the key
    // cout << "Enter FDs: \n";
    fr(i, 0, n) {
        ll l, r;
        // cout << "Enter the number of attributes on LHS of FD: ";
        cin >> l;
        // cout << "Enter the number of attributes on RHS of FD: ";
        cin >> r;
        set<ll> vec1;
        // cout << "Enter " << l << " space seperated attributes (LHS)" << endl;
        while (l--) {
            string lhs;
            cin >> lhs;
            ll eq = hash[lhs];
            auto it = mt.find({ -lcnt[eq],eq });
            if (it != mt.end()) {
                mt.erase(it);
            }
            lcnt[eq]++;
            mt.insert({ -lcnt[eq],eq });
            vec1.insert(eq);
        }
        // cout << "Enter " << r << " space seperated attributes (RHS)" << endl;
        while (r--) {
            string rhs;
            cin >> rhs;
            ll eq = hash[rhs];
            fd[vec1].insert(eq);
        }
    }
    // now we try to find the key
    set<set<ll> > candidate_keys;
    set<set<ll> > found;
    set<ll> cur;
    // now we need to generate all possible combinations
    set<ll> test_attributes = { 0,2 };
    set<ll> closure;
    test_all_combos(mt, mt.begin(), fd, candidate_keys, total, cur, found);
    map<ll, set<set<ll> > > keys_ordered_by_size;
    for (auto& st : candidate_keys) {
        keys_ordered_by_size[st.size()].insert(st);
    }
    cout << "Candidate keys (of minimal size) : " << endl;
    for (auto& st : keys_ordered_by_size.begin()->second) {
        cout << "Key: (";
        for (auto& attribute : st) {
            cout << unhash[attribute] << ' ';
        }
        cout << ')' << endl;
    }
}

int main() {
    fastIO;
    fileIO;
    Solve(1);
    return 0;
}
