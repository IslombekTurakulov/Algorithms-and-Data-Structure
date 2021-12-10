/*
#include <cstdio>
#include <string>
#include <set>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

#define mp make_pair
typedef long long LL;

const int N = 1000;
const int B = 33;
const int M1 = 1000000007;
const int M2 = 1000000021;
const int M3 = 1000000033;
const int LIMIT = 10;

char in[N];
int len;

int get(int mod, int base) {
    LL p = 1, h = 0;
    for (int i = len - 1; i >= 0; --i) {
        h += p * (in[i] - 'a' + 1) % mod;
        p = (p * base) % mod;
    }
    return h;
}

set<pair<int, int> > hashes;
set<string> strs;

bool generate() {
    len = 31;
    for (int i = 0; i < len; ++i)
        in[i] = 'a' + rand() % 26;
    in[len] = 0;
    printf("%s\n", in);
    if (strs.count(in)) {
        printf("safe colision\n");
        return true;
    }
    strs.insert(in);
    pair<int, int> p = mp(get(M1, B), get(M2, B));
    if (hashes.count(p)) {
        printf("%s\n", in);
        return false;
    }
    hashes.insert(p);
    if (hashes.size() == LIMIT) return false;
    return true;
}

int main() {
    srand(time(NULL));
    while (generate());
    printf("%d\n", (int) hashes.size());
}*/
