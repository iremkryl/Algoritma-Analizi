/**
 * Proje: Algoritma Analizi ve Karmaşıklığı Dönem Ödevi
 * Problem 5: Heap Yapıları (Binary Heap)
 * insert, deleteMin, findMin
 * BuildHeap (MinHeap ve MaxHeap)
 * decreaseKey, increaseKey, deleteKey
 * Merge(H1, H2)
 */

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class MinHeap {
private:
    vector<int> H; // 1-indexli heap
    int N;

    int parent(int i) { return i / 2; }
    int left(int i) { return 2 * i; }
    int right(int i) { return 2 * i + 1; }

    // Aşağı doğru itme (DeleteMin & BuildHeap için)
    void percolateDown(int i) {
        int child;
        int tmp = H[i];

        while (left(i) <= N) {
            child = left(i);

            if (child != N && H[child + 1] < H[child])
                child++;

            if (H[child] < tmp) {
                H[i] = H[child];
                i = child;
            } else
                break;
        }
        H[i] = tmp;
    }

    // Yukarı doğru çıkarma (Insert, DecreaseKey için)
    void percolateUp(int i) {
        int tmp = H[i];
        while (i > 1 && tmp < H[parent(i)]) {
            H[i] = H[parent(i)];
            i = parent(i);
        }
        H[i] = tmp;
    }

public:
    MinHeap(int capacity = 100) {
        H.resize(capacity + 1);
        H[0] = INT_MIN; // Sentinel
        N = 0;
    }

    int findMin() {
        if (N == 0) throw runtime_error("Heap empty");
        return H[1];
    }

    void insertHeap(int key) {
        if (N + 1 >= H.size())
            H.resize(H.size() * 2);

        int hole = ++N;
        while (key < H[hole / 2]) {
            H[hole] = H[hole / 2];
            hole /= 2;
        }
        H[hole] = key;
    }

    int deleteMin() {
        if (N == 0) throw runtime_error("Heap empty");

        int minItem = H[1];
        H[1] = H[N--];
        percolateDown(1);
        return minItem;
    }

    void buildHeap(const vector<int>& arr) {  // (Bottom-Up) → O(N)
        N = arr.size();
        H.resize(N + 1);
        H[0] = INT_MIN;

        for (int i = 0; i < arr.size(); i++)
            H[i + 1] = arr[i];

        for (int i = N / 2; i >= 1; i--)
            percolateDown(i);
    }

    void decreaseKey(int pos, int delta) {
        if (pos < 1 || pos > N) return;
        H[pos] -= delta;
        percolateUp(pos);
    }

    void increaseKey(int pos, int delta) {
        if (pos < 1 || pos > N) return;
        H[pos] += delta;
        percolateDown(pos);
    }

    void deleteKey(int pos) {
        if (pos < 1 || pos > N) return;
        H[pos] = H[N--];
        percolateDown(pos);
        percolateUp(pos);
    }

    void mergeHeap(MinHeap& H2) {   // Merge (O(N) BuildHeap ile)
        vector<int> merged;
        for (int i = 1; i <= N; i++)
            merged.push_back(H[i]);
        for (int i = 1; i <= H2.N; i++)
            merged.push_back(H2.H[i]);

        buildHeap(merged);
    }

    void printHeap() {
        for (int i = 1; i <= N; i++)
            cout << H[i] << " ";
        cout << endl;
    }
};

int main() {
    cout << "\n5: HEAP YAPILARI\n";

    cout << "1) MinHeap'e Eleman Ekleme (insert)\n";
    MinHeap H1;
    cout << "   Eklenenler: 10, 5, 30, 2\n";
    H1.insertHeap(10);
    H1.insertHeap(5);
    H1.insertHeap(30);
    H1.insertHeap(2);
    cout << "   MinHeap (H1): ";
    H1.printHeap();
    cout << endl;

    cout << "2) deleteMin Islemi\n";
    int minVal = H1.deleteMin();
    cout << "   En Kucuk Eleman (Min): " << minVal << endl;
    cout << "   deleteMin Sonrasi H1: ";
    H1.printHeap();
    cout << endl;

    cout << "3) BuildHeap (MaxHeap)\n";
    vector<int> data = {10, 20, 5, 30, 40};
    cout << "   Giris Verisi: ";
    for (int x : data) cout << x << " ";
    cout << endl;

    MinHeap maxHeap;
    vector<int> negData;
    for (int x : data) negData.push_back(-x);
    maxHeap.buildHeap(negData);

    cout << "   Olusturulan MaxHeap: ";
    for (int i = 1; i <= data.size(); i++) {
        cout << -maxHeap.deleteMin() << " "; 
    }
    cout << "\n\n";

    cout << "4) Guncelleme Islemleri (H1)\n";

    cout << "   decreaseKey:\n";
    cout << "   Islem: decreaseKey(Index=2, Delta=25)\n";
    cout << "   Aciklama: 30 - 25 = 5\n";
    H1.decreaseKey(2, 25);
    cout << "   Sonuc Heap: ";
    H1.printHeap();
    cout << endl;

    cout << "   increaseKey:\n";
    cout << "   Islem: increaseKey(Index=1, Delta=50)\n";
    cout << "   Aciklama: 5 + 50 = 55\n";
    H1.increaseKey(1, 50);
    cout << "   Sonuc Heap: ";
    H1.printHeap();
    cout << endl;

    cout << "   deleteKey:\n";
    cout << "   Islem: deleteKey(Index=1)\n";
    H1.deleteKey(1);
    cout << "   Sonuc Heap: ";
    H1.printHeap();
    cout << endl;

    cout << "5) Heap Birlestirme (Merge)\n";
    MinHeap H2;
    cout << "   H2 Heap: 1 100 50\n";
    H2.insertHeap(1);
    H2.insertHeap(100);
    H2.insertHeap(50);

    H1.mergeHeap(H2);
    cout << "   H1 ve H2 Birlestirildi\n";
    cout << "   Yeni Heap: ";
    H1.printHeap();

    return 0;
}