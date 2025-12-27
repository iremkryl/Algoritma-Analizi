/**
 * Proje: Algoritma Analizi ve Karmaşıklığı
 * Problem 4: Sıralama Algoritmaları (Sorting)
 * Selection, Bubble, Insertion
 * Merge, Quick, Heap
 * Counting (Stable), Radix
 * External Sorting
 */

#include <iostream>
#include <vector>
#include <algorithm> // swap, max_element
#include <chrono>    // zaman ölçümü
#include <queue>     // heap sort ve external sort için
#include <cmath>     // radix sort için

using namespace std;
using namespace std::chrono;

// 1. TEMEL SIRALAMA ALGORİTMALARI O(N^2)
// Selection Sort: En küçüğü bul, başa koy
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(arr[min_idx], arr[i]);
    }
}

// Bubble Sort: Yan yana olanları karşılaştır, büyüğü en sona taşı
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // Eğer iç döngüde hiç değişim olmadıysa dizi sıralıdır.
        if (!swapped) break;
    }
}

// Insertion Sort: Kart gibi, eklendikçe sırala
void insertionSort(vector<int>& a) {
    int j;
    for (int p = 1; p < a.size(); p++) {
        int tmp = a[p];
        for (j = p; j > 0 && tmp < a[j - 1]; j--) {
            a[j] = a[j - 1];
        }
        a[j] = tmp;
    }
}

// 2. GELİŞMİŞ SIRALAMA ALGORİTMALARI O(N log N)
// --- MERGE SORT
// Sol yarim ile sag yarimi "tmpArray" uzerinde birlestirir, sonra ana diziye kopyalar.
void merge(vector<int>& a, vector<int>& tmpArray, int leftPos, int rightPos, int rightEnd) {
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        if (a[leftPos] <= a[rightPos])
            tmpArray[tmpPos++] = a[leftPos++];
        else
            tmpArray[tmpPos++] = a[rightPos++];
    }

    while (leftPos <= leftEnd) //Solu topla
        tmpArray[tmpPos++] = a[leftPos++];

    while (rightPos <= rightEnd) // Sağı topla
        tmpArray[tmpPos++] = a[rightPos++];

    for (int i = 0; i < numElements; i++, rightEnd--)  // Gecici diziyi (tmpArray) ana diziye (a) geri kopyala
        a[rightEnd] = tmpArray[rightEnd];
}
// 2. Rekursif Bolme
void mergeSort(vector<int>& a, vector<int>& tmpArray, int left, int right) {
    if (left < right) {
        int center = (left + right) / 2;
        mergeSort(a, tmpArray, left, center);
        mergeSort(a, tmpArray, center + 1, right);
        merge(a, tmpArray, left, center + 1, right);
    }
}
// 3. Driver Fonksiyon
void mergeSortDriver(vector<int>& a) {
    vector<int> tmpArray(a.size());
    mergeSort(a, tmpArray, 0, a.size() - 1);
}

// --- QUICK SORT
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while (true) {
        while (i <= high && arr[i] <= pivot) { // i'yi saga kaydir: Pivot'tan BUYUK veya ESIT bir sayi bulana kadar
            i++;
        }
        while (j >= low && arr[j] > pivot) {  // 2. j'yi sola kaydir: Pivot'tan KUCUK bir sayi bulana kadar
            j--;
        }
        if (i >= j) break;  // Eger i ve j kesisirse (i > j) donguden cik
        swap(arr[i], arr[j]);  // Kesisme yoksa, buldugun ters elemanlari takas et
    }
    swap(arr[low], arr[j]);
    return j; // Pivotun yeni konumu
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // Diziyi bol ve pivotun yerini al
        quickSort(arr, low, pi - 1);  // Sol parcayi sirala
        quickSort(arr, pi + 1, high);  // Sag parcayi sirala
    }
}

// --- HEAP SORT
inline int leftChild(int i) { // Yardimci Fonksiyon: Sol cocugun indeksini dondurur
    return 2 * i + 1;
}

void percDown(vector<int>& a, int i, int n) { // Aşağı kaydırma Islemi
    int child;
    int tmp;

    for (tmp = a[i]; leftChild(i) < n; i = child) { // tmp, yerlestirmeye calistigimiz eleman (kokteki)
        child = leftChild(i);
        
        // Sag cocuk var mi ve sol cocuktan daha mi buyuk?
        // Oyleyse sag cocugu sec
        if (child != n - 1 && a[child] < a[child + 1])
            child++;
            
        if (tmp < a[child])  // Eger secilen cocuk, tmp'den buyukse; cocugu yukari tasi
            a[i] = a[child];
        else
            break;
    }
    a[i] = tmp;   // tmp'yi dogru konuma yerlestir
}

void heapSort(vector<int>& a) {
    for (int i = a.size() / 2 - 1; i >= 0; i--) // Build Heap (Max-Heap insa et)
        percDown(a, i, a.size());

    for (int j = a.size() - 1; j > 0; j--) { // Delete Max (Sirala)
        swap(a[0], a[j]); // Max'i sona at
        percDown(a, 0, j); // Kalan kismi (0'dan j'ye) tekrar heap yap
    }
}

// 3. ÖZEL SIRALAMA ALGORİTMALARI O(N)
// --- COUNTING SORT 
// Counting Sort (Standart)
int getMax(const vector<int>& arr) {
    int maxVal = arr[0];
    for (int x : arr) if (x > maxVal) maxVal = x;
    return maxVal;
}

void countingSort(vector<int>& arr) {
    if (arr.empty()) return;
    int max_val = getMax(arr);
    vector<int> count(max_val + 1, 0);
    
    for (int x : arr) count[x]++;
    for (int i = 1; i <= max_val; i++) count[i] += count[i-1];
    
    vector<int> output(arr.size());
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for (int i = 0; i < arr.size(); i++) arr[i] = output[i];
}

// --- RADIX SORT ---
// Basamak basamak Counting Sort uygular

int getMax(const vector<int>& arr, int n) { // Dizideki en buyuk sayiyi bulur
    int maxVal = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > maxVal)
            maxVal = arr[i];
    return maxVal;
}

void countSortForRadix(vector<int>& arr, int n, int exp) {
    vector<int> output(n); // Siralanmis dizi
    int count[10] = {0};   // Rakamlar 0-9 arasi oldugu icin boyut 10

    for (int i = 0; i < n; i++) { // O anki basamaktaki rakamlarin frekansini say
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }
    for (int i = 1; i < 10; i++) { // Kumulatif toplam al
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {  // Output dizisini doldur (Stable için sondan başa)
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    for (int i = 0; i < n; i++) { // Gecici output dizisini ana diziye kopyala
        arr[i] = output[i];
    }
}

void radixSort(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return;
    int m = getMax(arr, n); //kaç basamaklı
    for (int exp = 1; m / exp > 0; exp *= 10) { //her basamağa counting
        countSortForRadix(arr, n, exp);
    }
}

// 4. EXTERNAL SORTING SIMULASYONU
// Mantık: Veri belleğe sığmazsa parçalara bölünür,
// her parça ayrı sıralanır ve sonra birleştirilir.
void externalSortSimulated(vector<int>& arr) {
    int n = arr.size();
    // Simülasyon: Belleğimizin sadece 1/10'luk veriyi alabildiğini varsayalım.
    int chunkSize = max(1, n / 10); 
    
    vector<vector<int>> sortedChunks;
    for (int i = 0; i < n; i += chunkSize) { // Parçaları Sırala (Chunks)
        vector<int> chunk;
        for (int j = i; j < min(i + chunkSize, n); j++) {
            chunk.push_back(arr[j]);
        }
        sort(chunk.begin(), chunk.end());  // Bellekteki küçük parçayı sırala
        sortedChunks.push_back(chunk);
    }

    // K-Way Merge (Birleştirme)
    // Pair: <Eleman Değeri, <HangiChunk, ChunkIcindekiIndex>>
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    for (int i = 0; i < sortedChunks.size(); i++) {
        if (!sortedChunks[i].empty())
            pq.push({sortedChunks[i][0], {i, 0}});
    }

    vector<int> finalSorted;
    while (!pq.empty()) {
        pair<int, pair<int, int>> top = pq.top();
        pq.pop();

        int val = top.first;
        int chunkIdx = top.second.first;
        int elemIdx = top.second.second;

        finalSorted.push_back(val);
     
        if (elemIdx + 1 < sortedChunks[chunkIdx].size()) {   // O chunk'tan bir sonraki elemanı alıp kuyruğa at
            pq.push({sortedChunks[chunkIdx][elemIdx + 1], {chunkIdx, elemIdx + 1}});
        }
    }
    arr = finalSorted;    // Sonucu ana diziye kopyala
}

// =============================================================
// MAIN VE TEST FONKSİYONLARI
// =============================================================

// Zaman ölçen yardımcı fonksiyon
// data: Kopya olarak alınır, orijinal veri bozulmaz
void measureTime(string algName, vector<int> data, void (*sortFunc)(vector<int>&)) {
    auto start = high_resolution_clock::now();
    sortFunc(data);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << algName << " -> Sure: " << duration << " ms" << endl;
}

// Wrapperlar (Parametre uyuşmazlığını gidermek için)
void runSelection(vector<int>& a) { selectionSort(a); }
void runBubble(vector<int>& a) { bubbleSort(a); }
void runInsertion(vector<int>& a) { insertionSort(a); }
void runMerge(vector<int>& a) { mergeSortDriver(a); }
void runQuick(vector<int>& a) { quickSort(a, 0, a.size() - 1); }
void runHeap(vector<int>& a) { heapSort(a); }
void runCounting(vector<int>& a) { countingSort(a); }
void runRadix(vector<int>& a) { radixSort(a); }
void runExternal(vector<int>& a) { externalSortSimulated(a); }

int main() {
    int N = 50000; 
    vector<int> masterData(N);
    srand(42);

    for (int i = 0; i < N; i++) {
        masterData[i] = rand() % 50000;
    }

    cout << "4: SIRALAMA ALGORITMALARI (N=" << N << ") \n";
    cout << "---------------------------------------------------------\n";

    // Grup 1: Temel (Yavaş)
    measureTime("1) Selection Sort", masterData, runSelection);
    measureTime("2) Bubble Sort   ", masterData, runBubble);
    measureTime("3) Insertion Sort", masterData, runInsertion);
    
    cout << "---------------------------------------------------------\n";
    
    // Grup 2: Gelişmiş (Hızlı)
    measureTime("4) Merge Sort    ", masterData, runMerge);
    measureTime("5) Quick Sort    ", masterData, runQuick);
    measureTime("6) Heap Sort     ", masterData, runHeap);

    cout << "---------------------------------------------------------\n";

    // Grup 3: Özel/Lineer
    measureTime("7) Counting Sort ", masterData, runCounting);
    measureTime("8) Radix Sort    ", masterData, runRadix);
    measureTime("9) External Sim. ", masterData, runExternal);

    return 0;
}