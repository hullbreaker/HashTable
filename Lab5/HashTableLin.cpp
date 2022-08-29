#include "HashTableLin.h"
#include <cmath>
#include <iostream>
using namespace std;

// Time complexity n (worst case)
bool isPrime(int n)
{
    if (n <= 1)
        return false;

    for (int i = 2; i < n; i++) {
        if (n % i == 0)
            return false;
    }
        
    return true;
}

// Time complexity 1
// Space complexity n
HashTableLin::HashTableLin(int maxNum, double load)
{
    // Calculate starting point
    double maxd = maxNum;
    int min = ceil(maxd / load);

    // Find prime number larger than min and less than max integer
    for (int i = min; i < INT_MAX; i++) {
        if (isPrime(i) == true) {
            size = i;
            break;
        }
    }

    // Initialize variables
    keyNum = 0;
    maxLoad = load;
    vector<int> myvec(size, 0);
    table = myvec;
}

// Time complexity 1 (best case)
// Time complexity n (rehash/search case)
// Space complexity 1
void HashTableLin::insert(int n)
{
    if (isIn(n) == false) {
        keyNum++;
        double s = size;
        double k = keyNum;
        double quotient = k / s;
        // Check load
        if (quotient > maxLoad) {
            //cout << n << ": " << "load: " << quotient << ", " << "maxload:" << maxLoad << ", " << "keynum: " << keyNum << endl;
            rehash();
        }
        // Check if cell empty
        int i = n % size;
        if (table[i] == 0) {
            table[i] = n;
        }
        else {
            // Linear collison resolution
            while (table[i] != 0) {
                i++;
                if (i == size) {
                    i = 0;
                }
            }
            table[i] = n;
        }
    }
        

}

// Time complexity n
// Space complexity n (worst case)
void HashTableLin::rehash()
{
    // Change max size
    vector<int> temp = table;
    size *= 2;
    for (int i = size; i < INT_MAX; i++) {
        if (isPrime(i) == true) {
            size = i;
            break;
        }
    }

    keyNum = 1;
    vector<int> c(size, 0);
    table = c;

    // Insert all old elements
    for (int i = 0; i < temp.size(); i++) {
        if (temp[i] != 0) {
            insert(temp[i]);
            //keyNum--;
        }
    }
    
}

// Time complexity 1 (best case)
// Space complexity 1
bool HashTableLin::isIn(int n)
{

    int i = n % size;
    while(table[i] != 0){
        if (table[i] == n) {
            return true;
        }
        else {
            i++;
            // Return to index 0
            if (i == size) {
                i = 0;
            }
            else if (i == n % size) {
                return false;
            }
        }
    }
    return false;
}

void HashTableLin::printKeys()
{
    // TODO
    for (int i = 0; i < size; i++) {
        if (table[i] != 0) {
            cout << table[i] << ",";
        }
    }
    cout << endl;
}

void HashTableLin::printKeysAndIndexes()
{
    // TODO
    for (int i = 0; i < size; i++) {
        if (table[i] != 0)
            cout << "i: " << i << " " << table[i] + ",";
    }
    cout << endl;
}

int HashTableLin::getNumKeys() {
    // TODO, change following code after completing this function
    return keyNum;
}

int HashTableLin::getTableSize() {
    // TODO, change following code after completing this function
    return size;
}

double HashTableLin::getMaxLoadFactor() {
    // TODO, change following code after completing this function
    return maxLoad;
}

int HashTableLin::probeTest(int n) {
    int i = n % size;
    int probeCount = 0;
    while (table[i] != 0) {
        probeCount++;
        if (table[i] == n) {
            break;
        }
        else {
            
            i++;
            if (i == size) {
                i = 0;
            }
            else if (i == n % size) {
                break;
            }
        }
    }
    return probeCount;
}

std::vector<double> HashTableLin::simProbeSuccess()
{
    // TODO, change following code after completing this function
    vector<double> result(9);
    int count = 0;
    srand(time(NULL));
    for (double load = 0.1; load <= 0.9; load += 0.1) {
        int testSize = 1000;
        HashTableLin tempHash = HashTableLin(testSize, load);
        vector<int> tempVec;
        double sum = 0;
        for (int i = 0; i < testSize; i++) {
            tempVec.emplace_back(rand() % 100000);
        }
        for (int i = 0; i < testSize; i++) {
            tempHash.insert(tempVec[i]);
        }
        for (int i = 0; i < testSize; i++) {
            sum += tempHash.probeTest(tempVec[rand() % testSize]);
        }
        sum /= 1000.0;
        result[count] = sum;
        count++;
    }
    for (int i = 0; i < 9; i++) {
        //cout << "0." << i + 1 << ": " << result[i] << endl;
    }
    return result;
}

// for bonus
std::vector<double> HashTableLin::simProbeUnsuccess()
{
    vector<double> result(9);
    int count = 0;
    srand(time(NULL));
    for (double load = 0.1; load <= 0.9; load += 0.1) {
        int testSize = 1000;
        HashTableLin tempHash = HashTableLin(testSize, load);
        vector<int> tempVec;
        double sum = 0;
        for (int i = 0; i < testSize; i++) {
            tempVec.emplace_back(rand() % 100000);
        }
        for (int i = 0; i < testSize; i++) {
            
            tempHash.insert(tempVec[i]);
        }
        for (int i = 0; i < testSize; i++) {
            int tempRand = rand() % 100000;
            for (int j = 0; j < testSize; j++) {

                while (tempRand == tempVec[j]) {
                    tempRand = rand() % 100000;
                }
            }
            sum += tempHash.probeTest(tempRand);
        }
        sum /= 1000.0;
        result[count] = sum;
        count++;
    }
    for (int i = 0; i < 9; i++) {
        //cout << "0." << i + 1 << ": " << result[i] << endl;
    }
    return result;
}
