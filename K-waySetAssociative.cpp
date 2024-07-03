#include <bits/stdc++.h>
using namespace std;

class Cache {
private:
    int k; // associativity
    int v; // number of sets
    vector<vector<int>> cache;

public:
    Cache(int k, int v)   {
        this->k=k;
        this->v=v;
        cache.resize(v, vector<int>(k, -1)); // Initialize cache with -1 (empty)
    }

    int getSet(int j) {
        return j % v;
    }

    bool isCacheHit(int address) {
        int set = getSet(address);
        for (int i = 0; i < k; ++i) {
            if (cache[set][i] == address) {
                return true;
            }
        }
        return false;
    }

    void accessMemory(int address) {
        int set = getSet(address);
        if (!isCacheHit(address)) {
            // Cache miss, find an empty slot or replace
            bool placed = false;
            for (int i = 0; i < k; ++i) {
                if (cache[set][i] == -1) {
                    cache[set][i] = address;
                    placed = true;
                    break;
                }
            }
            if (!placed) {
                // All slots are full, replace the first one (better replacement policy can be implemented)
                cache[set][0] = address;
            }
            cout << "Cache miss for address " << address << endl;
        } else {
            cout << "Cache hit for address " << address << endl;
        }
    }

    void printCache() {
        cout << "Cache contents:" << endl;
        for (int i = 0; i < v; ++i) {
            cout << "Set " << i << ": ";
            for (int j = 0; j < k; ++j) {
                if (cache[i][j] == -1) {
                    cout << "- ";
                } else {
                    cout << cache[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    int k = 2; // 2-way set associative
    int v = 4; // 4 sets

    Cache cache(k, v);

    vector<int> memoryReferences = {4, 5, 9, 7};

    for (int address : memoryReferences) {
        cout << "Accessing memory address: " << address << endl;
        cache.accessMemory(address);
        cache.printCache();
        cout << endl;
    }

    return 0;
}
