#include <iostream>
#include <vector>
using namespace std;

struct FenwickTree {
    vector<int> bit;
    int size;

    FenwickTree(const vector<int>& input) {
        size = input.size();
        bit.resize(size + 1, 0);

        for (int i = 0; i < size; i++) {
            update(i, input[i]);
        }
    }
    void update(int idx, int value) {
        idx++; //for 1-based system
        while (idx <= size) {
            bit[idx] += value;
            idx += (idx & -idx);
        }
    }

    int prefixSum(int idx) {
        idx++; //for 1-based system
        int result = 0;

        while (idx > 0) {
            result += bit[idx];
            idx -= (idx & -idx);
        }
        return result;
    }

    int queryRange(int l, int r) {
        if (l == 0) {
            return prefixSum(r);
        }
        return prefixSum(r) - prefixSum(l - 1);
    }
};
void printArray(const vector<int>& data) {
    cout << "[ ";
    for(int i = 0; i < data.size(); i++) {
        cout << data[i] << " ";
    }
    cout << "]\n";
}
void applyUpdate(FenwickTree& tree, vector<int>& data, int index, int val) {
    tree.update(index, val);
    data[index] += val;
}
int main() {
    int exmp[] = {3, 2, -1, 6, 5, 4, -3, 3};
    vector<int> arr(exmp, exmp + sizeof(exmp) / sizeof(int));
    FenwickTree ft(arr);

    cout << "Initial array:\n";
    printArray(arr);

    cout << "\nSum 2 to 7: " << ft.queryRange(2, 7) << endl;
    cout << "Sum 0 to 3: " << ft.queryRange(0, 3) << endl;

    cout << "\nUpdating index 3 by adding -2...\n";
    applyUpdate(ft, arr, 3, -2);

    cout << "\nAfter update:\n";
    printArray(arr);
    cout << "Sum 0 to 3: " << ft.queryRange(0, 3) << endl;

    return 0;
}