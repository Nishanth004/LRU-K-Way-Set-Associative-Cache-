#include <bits/stdc++.h>
using namespace std;

class Cache {
private:
    int k; // no of lines in set
    int n; 
    int blockSize; 
    vector<vector<int>> cache; 
    vector<list<int>> lru_tracker; 
    int hits; 
    int misses; 
    const int cacheAccessTime = 10; 
    const int mainMemoryAccessTime = 1000; 
    unordered_map<int, int>frame;

public:
    Cache(int cacheSize, int blockSize, int k) {
        this->k = k;
        this->blockSize = blockSize;
        this->n = cacheSize / (k * blockSize); 
        cache.resize(n, vector<int>(k * blockSize, -1)); 
        lru_tracker.resize(n);
        hits = 0;
        misses = 0;
    }
    
    void genframe(int value)
    {
        frame[value]=rand() ;
    }
    void set_zero(int valueToFind) {
        for (auto it = frame.begin(); it != frame.end(); ++it) {
        if (it->second == valueToFind) {
            it->second = 0;
            break; 
        }
    }
    }
    int getSet(int value) {
        return value % n;
    }

    bool isCacheHit(int value) {
        int set = getSet(value);
        for (int i = 0; i < k * blockSize; ++i) {
            if (cache[set][i] == value) {
                return true;
            }
        }
        return false;
    }

    void PutData(int value) {
        if(frame[value]==0)
            genframe(value);
        value=frame[value];
        int set = getSet(value);
        if (!isCacheHit(value)) {
            // insert in empty slot
            misses++;
            bool placed = false;
            for (int i = 0; i < k * blockSize; ++i) {
                if (cache[set][i] == -1) {
                    cache[set][i] = value;
                    lru_tracker[set].push_back(value);
                    placed = true;
                    break;
                }
            }
            if (!placed) {
               // slots full, replace lru
                int lru_value = lru_tracker[set].front();
                lru_tracker[set].pop_front();
                set_zero(value);
                for (int i = 0; i < k * blockSize; ++i) {
                    if (cache[set][i] == lru_value) {
                        cache[set][i] = value;
                        lru_tracker[set].push_back(value);
                        break;
                    }
                }
            }
            cout << "\nCache miss for value " << value  << endl;
            cout<<"\nretrievin data from main memory\n";
        } 
        else 
        {
            // Cache hit, replace lru
            hits++;
            lru_tracker[set].remove(value);
            lru_tracker[set].push_back(value);
            cout << "\nCache hit for value " << value << endl;
        }
        printStats();
    }

    int GetData(int value) {
        if(frame[value]==0)
            genframe(value);
        value=frame[value];
        int set = getSet(value);
        for (int i = 0; i < k * blockSize; ++i) {
            if (cache[set][i] == value) {
                //change lru
                hits++;
                lru_tracker[set].remove(value);
                lru_tracker[set].push_back(value);
                cout << "\nCache hit for value " << value << " (Cache Access Time: " << cacheAccessTime << " ns)" << endl;
                return cache[set][i];
            }
        }
        
        // cout << "Cache miss for value " << value << " (Main Memory Access Time: " << mainMemoryAccessTime << " ns)" << endl;
        PutData( value);
        
        return value;
    }


    void printCache() {
        cout << "Cache contents:" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "Set " << i << ": ";
            for (int j = 0; j < k * blockSize; ++j) {
                if (cache[i][j] == -1) {
                    cout << "- ";
                } else {
                    cout << cache[i][j] << " ";
                }
            }
            cout<<endl;
        }
        cout<<"----------------------------------------------------------"<<endl;
    }

    void printStats() {
        cout<<"----------------------------------------------------------"<<endl;
        cout << "Cache Hits: " << hits << endl;
        cout << "Cache Misses: " << misses << endl;
        int totalAccesses = hits + misses;
        double hitRate = static_cast<double>(hits) / totalAccesses;
        double missRate = static_cast<double>(misses) / totalAccesses;
        double amat = (hitRate * cacheAccessTime) + (missRate * mainMemoryAccessTime);
        cout << "Average Memory Access Time (AMAT): " << amat << " ns" << endl;
    }
};

int main() {
    int cacheSize = 16; 
    int blockSize = 2; 
    int k = 2; 

    Cache cache(cacheSize, blockSize, k);

    vector<int> values = {4, 5, 9, 7};
    
    int key = 5;
    int result = cache.GetData(key);
    cout << "\nData found for value " << key << ": " << result << endl;
    for (int value : values) {
        cout << "\nAccessing value: " << value << endl;
        cache.PutData(value);
        cache.printCache();
        cout << endl;
    }

     key = 5;
     result = cache.GetData(key);
    cout << "\nData found for value " << key << ": " << result << endl;

    cache.printStats();

    return 0;
}
