/**
 * Proje: Algoritma Analizi ve Karmaşıklığı Dönem Ödevi
 * Problem 3: Arama Algoritmaları
 * 1. İleri Yönlü Lineer Arama
 * 2. Geri Yönlü Lineer Arama
 * 3. İkili Arama (Binary Search)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

   // 1) Ileri Yonlu Lineer Arama
int countForward = 0;
int forwardLinearSearch(const vector<int>& a, int key) {
    int i = 0;
    int n = a.size();
    while (i < n) {
        countForward++;
        if (a[i] == key)
            return i;
        i++;
    }
    return -1;
}

  // 2) Geri Yonlu Lineer Arama
int countBackward = 0;
int backwardLinearSearch(const vector<int>& a, int key) {
    int i = a.size() - 1;
    while (i >= 0) {
        countBackward++;
        if (a[i] == key)
            return i;
        i--;
    }
    return -1;
}

   // 3) Ikili Arama
int countBinary = 0;
int binarySearch(const vector<int>& a, int key) {
    int left = 0;
    int right = a.size() - 1;
    while (left <= right) {
        countBinary++;
        int mid = (left + right) / 2;
        if (a[mid] == key)
            return mid;
        else if (a[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main() {

    cout << "3- ARAMA ALGORITMALARI\n\n";
    vector<int> data = {3, 7, 12, 18, 25, 31, 42, 56, 68, 79};
    int key = 31;

    cout << "Dizi: ";
    for (int x : data) cout << x << " ";
    cout << endl;

    cout << "Aranan Eleman: " << key << "\n\n";

    // 1) Ileri Yonlu Lineer Arama
    int pos1 = forwardLinearSearch(data, key);
    cout << "1) Ileri Yonlu Lineer Arama\n";
    cout << "   Bulunan Indeks: " << pos1 << " | Karsilastirma Sayisi: " << countForward << "\n\n";

    // 2) Geri Yonlu Lineer Arama
    int pos2 = backwardLinearSearch(data, key);
    cout << "2) Geri Yonlu Lineer Arama\n";
    cout << "   Bulunan Indeks: " << pos2 << " | Karsilastirma Sayisi: " << countBackward << "\n\n";

    // 3) Ikili Arama
    int pos3 = binarySearch(data, key);
    cout << "3) Ikili Arama (Binary Search)\n";
    cout << "   Bulunan Indeks: " << pos3 << " | Karsilastirma Sayisi: " << countBinary << "\n\n";

    return 0;
}
