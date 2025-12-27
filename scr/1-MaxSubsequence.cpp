/**
 * Proje: Algoritma Analizi ve Karmaşıklığı Dönem Ödevi
 * Problem 1: Maximum Subsequence Sum Problemi
 * 1. O(n^3) Brute Force
 * 2. O(n^2) İyileştirilmiş Brute Force
 * 3. O(n log n) Divide and Conquer
 * 4. O(n) Kadane Algoritması
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono> // Zaman ölçümü için
#include <random> // Rastgele sayı üretimi için

using namespace std;
using namespace chrono;
// const vector<int>& a: Bir tamsayı dizisi, orijinal ve içini değiştirilemez

// 1. Yaklaşım: Brute Force - O(N^3): Her ihtimali her seferinde en başta alıp okur
int maxSubSum1(const vector<int>& a) {
    int maxSum = 0;
    int n = a.size();

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int thisSum = 0;
            // i'den j'ye kadar olan alt diziyi topla
            for (int k = i; k <= j; ++k) {
                thisSum += a[k];
            }
            if (thisSum > maxSum) {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}

// 2. Yaklaşım: İyileştirilmiş Brute Force - O(N^2): Toplamı her seferinde sıfırlamak yerine biriktirir
int maxSubSum2(const vector<int>& a) {
    int maxSum = 0;
    int n = a.size();

    for (int i = 0; i < n; ++i) {
        int thisSum = 0;
        for (int j = i; j < n; ++j) {
            thisSum += a[j]; // Bir önceki toplamın üzerine ekler
            if (thisSum > maxSum) {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}

// 3. Yaklaşım: Divide and Conquer - O(N log N): Böl ve Fethet ile böler, toplar
int max3(int a, int b, int c) {
    return std::max(a, std::max(b, c));
}

// Recursive parça
int maxSubSumRec(const vector<int>& a, int left, int right) {
    // Base Case (Temel Durum)
    if (left == right) {
        if (a[left] > 0) return a[left];
        else return 0;
    }

    int center = (left + right) / 2;
    
    // Sol ve Sağ kısımları recursive çöz
    int maxLeftSum = maxSubSumRec(a, left, center);
    int maxRightSum = maxSubSumRec(a, center + 1, right);

    // Sol tarafın maxını bul
    int maxLeftBorderSum = 0, leftBorderSum = 0;
    for (int i = center; i >= left; --i) {
        leftBorderSum += a[i];
        if (leftBorderSum > maxLeftBorderSum)
            maxLeftBorderSum = leftBorderSum;
    }

    //Sağ tarafın maxını bul
    int maxRightBorderSum = 0, rightBorderSum = 0;
    for (int i = center + 1; i <= right; ++i) {
        rightBorderSum += a[i];
        if (rightBorderSum > maxRightBorderSum)
            maxRightBorderSum = rightBorderSum;
    }

    // Üç durumdan en büyüğünü döndür: Sol, Sağ veya Ortadan geçen
    return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

// Driver fonksiyon
int maxSubSum3(const vector<int>& a) {
    return maxSubSumRec(a, 0, a.size() - 1);
}

// 4. Yaklaşım: Kadane Algoritması (Linear) - O(N)
int maxSubSum4(const vector<int>& a) {
    int maxSum = 0;
    int thisSum = 0;

    for (int j = 0; j < a.size(); ++j) {
        thisSum += a[j];

        if (thisSum > maxSum) {
            maxSum = thisSum;
        }
        else if (thisSum < 0) {
            thisSum = 0; // Negatifse sıfırla, yeni alt dizi başlat
        }
    }
    return maxSum;
}

    int main() {
        int N = 500;
        vector<int> data(N);
        srand(42); // Aynı test için sabit seed

        for (int i = 0; i < N; i++) {
            data[i] = rand() % 201 - 100; // Rastgele veri üretimi ([-100, 100])
        }

        cout << "Veri Boyutu (N): " << N << endl;

        int r1, r2, r3, r4;

        // 1) O(n^3) - Brute Force
        auto start = high_resolution_clock::now(); // kronometre başlar
        r1 = maxSubSum1(data); // cevabı bulur
        auto end = high_resolution_clock::now(); // kronometre durur
        auto t1 = duration_cast<milliseconds>(end - start).count(); //aradaki milisaniyeyi atar

        cout << "1) O(n^3) Brute Force  -> " << "Sonuc: " << r1 << " | Sure: " << t1 << " ms\n";

        // 2) O(n^2) - İyileştirilmiş Brute Force
        start = high_resolution_clock::now();
        r2 = maxSubSum2(data);
        end = high_resolution_clock::now();
        auto t2 = duration_cast<milliseconds>(end - start).count();

        cout << "2) O(n^2) Improved BF  -> " << "Sonuc: " << r2 << " | Sure: " << t2 << " ms\n";

        // 3) O(n log n) - Divide & Conquer
        start = high_resolution_clock::now();
        r3 = maxSubSum3(data);
        end = high_resolution_clock::now();
        auto t3 = duration_cast<milliseconds>(end - start).count();

        cout << "3) O(n log n) Divide&Conq -> " << "Sonuc: " << r3 << " | Sure: " << t3 << " ms\n";

        // 4) O(n) - Kadane
        start = high_resolution_clock::now();
        r4 = maxSubSum4(data);
        end = high_resolution_clock::now();
        auto t4 = duration_cast<milliseconds>(end - start).count();

        cout << "4) O(n) Kadane        -> " << "Sonuc: " << r4 << " | Sure: " << t4 << " ms\n";

        // Doğruluk kontrolü
        if (r1 == r2 && r2 == r3 && r3 == r4)
            cout << "Tum algoritmalar ayni sonucu verdi.\n\n";
        else
            cout << "\nHATA: Sonuclar farkli! \n\n";

        return 0;
    }