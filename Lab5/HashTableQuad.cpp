#include "HashTableQuad.h"
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <time.h>

// Time complexity n (worst case)
bool HashTableQuad::isPrime(int n)
{
    if (n <= 1)
        return false;

    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;

    return true;
}

// Time complexity 1
// Space complexity n
HashTableQuad::HashTableQuad(int maxNum, double load)
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
void HashTableQuad::insert(int n)
{
    int count = 0;

    if (isIn(n) == false) {

        keyNum++;
        double s = size;
        double k = keyNum;
        double quotient = k / s;
        int flag = 0;
        int i = n % size;
        // Check if possible to insert
        for (int k = 0; k < size; k++) {
            int index = (i + k * k) % size;
            if (table[index] == 0) {
                flag = 1;
                break;
            }
        }
        // Rehash if exceeds maxload
        if (quotient > maxLoad && flag == 1) {
            //cout << n << ": " << "load: " << quotient << ", " << "maxload:" << maxLoad << ", " << "keynum: " << keyNum << endl;
            rehash();
        }
        
        i = n % size;
        if (table[i] == 0) {
            table[i] = n;
        }
        else {
            // Quadratic collision
            for (int k = 0; k < size; k++) {
                int index = (i + k * k) % size;
                if (table[index] == 0) {
                    table[index] = n;
                    flag = 1;
                    break;
                }
            }
            // If not inserted
            if (flag == 0) {
                keyNum--;
            }
            
        }
    }

}

// Time complexity n
// Space complexity n (worst case)
void HashTableQuad::rehash()
{
    //cout << "called" << endl;

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

    for (int i = 0; i < temp.size(); i++) {
        if (temp[i] != 0) {
            insert(temp[i]);
        }
    }
}

// Time complexity 1 (best case)
// Space complexity 1
bool HashTableQuad::isIn(int n)
{
    int i = n % size;
    for (int k = 0; k < size; k++) {
        i = (n % size + k * k) % size;
        if (table[i] == n)
            return true;
    }
    return false;
}

void HashTableQuad::printKeys()
{
    // TODO
    for (int i = 0; i < size; i++) {
        if (table[i] != 0)
            cout << table[i] + ",";
    }
    cout << endl;
}

void HashTableQuad::printKeysAndIndexes()
{
    // TODO
    for (int i = 0; i < size; i++) {
        if (table[i] != 0)
            cout << "i: " << i << " " << table[i] + ",";
    }
    cout << endl;
}

int HashTableQuad::getNumKeys() {
    // TODO, change following code after completing this function
    return keyNum;
}

int HashTableQuad::getTableSize() {
    // TODO, change following code after completing this function
    return size;
}

double HashTableQuad::getMaxLoadFactor() {
    // TODO, change following code after completing this function
    return maxLoad;
}

int HashTableQuad::probeTest(int n)
{
    bool success = false;
    int probeCount = 0;
    int i = n % size;
    for (int k = 0; k < size; k++) {
        i = (n % size + k * k) % size;
        probeCount++;
        if (table[i] == n) {
            success = true;
            break;
        }
    }
    return probeCount;

}

std::vector<double> HashTableQuad::simProbeSuccess()
{
    // TODO, change following code after completing this function
    vector<double> result(9);
    int count = 0;
    srand(time(NULL));
    for (double load = 0.1; load <= 0.9; load += 0.1) {
        int testSize = 1000;
        HashTableQuad tempHash = HashTableQuad(testSize, load);
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
        //cout << i << ": " << result[i] << endl;
    }
    return result;
}
