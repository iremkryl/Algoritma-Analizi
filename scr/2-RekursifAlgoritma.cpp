/**
 * Proje: Algoritma Analizi ve Karmaşıklığı Dönem Ödevi
 * Problem 2: Rekürsif Algoritmalar
 * 1. 1'den N'e Kadar Toplam (Sum 1..N)
 * 2. Dizi Toplamı (Array Sum)
 * 3. Üs Alma (Power Function - a^n)
 * 4. Fibonacci Serisi
 * 5. Hanoi Kuleleri (Tower of Hanoi)
 * 6. Recursive Digit Sum (Super Digit)
 */

#include <iostream>
#include <vector>

using namespace std;
// const vector<int>& a: A tamsayı dizisi, orijinal ve içini değiştirilemez

  // 1) 1 + 2 + ... + N
int countSumN = 0;
int sumN(int n) {
    countSumN++;
    if (n <= 0) 
        return 0;
    return n + sumN(n - 1);
}

    // 2) Dizi Toplamı
int countArraySum = 0;
int arraySum(const vector<int>& a, int n) {
    countArraySum++;
    if (n <= 0) 
        return 0;
    return a[n - 1] + arraySum(a, n - 1);
}

    // 3) a^n
int countPower = 0;
int power(int a, int n) {
    countPower++;
    if (n == 0) 
        return 1;
    return a * power(a, n - 1);
}

    // 4) Fibonacci
int countFib = 0;
int fib(int n) {
    countFib++;
    if (n <= 1) 
        return n;
    return fib(n - 1) + fib(n - 2);
}

    // 5) Tower of Hanoi
int countHanoi = 0;
void hanoi(int n, char from, char to, char aux) {
    countHanoi++;
    if (n == 1) {
        cout << "    Disk 1 : " << from << " -> " << to << endl;
        return;
    }
    hanoi(n - 1, from, aux, to);
    cout << "    Disk " << n << " : " << from << " -> " << to << endl;
    hanoi(n - 1, aux, to, from);
}

    // 6) Recursive Digit Sum / Super Digit
int countDigitSumOnce = 0;
int digitSumOnce(int n) {    // İşçi: Sayının rakamlarını bir tur toplar
    countDigitSumOnce++;
    if (n == 0)
        return 0;
    return (n % 10) + digitSumOnce(n / 10);
}
int countDigitSum = 0;
int superDigit(int n) { // Tek basamağa düşene kadar devam eder
    countDigitSum++;
    if (n < 10)
        return n;
    return superDigit(digitSumOnce(n));
}

int main() {
    cout << "2- REKURSIF ALGORITMALAR\n\n";
     // 1) 1+2+...+N
    int N = 10;
    cout << "1) 1+2+...+N, N = " << N << endl;
    cout << "   Sonuc: " << sumN(N) << " | Cagri Sayisi: " << countSumN << "\n";

    // 2) Dizi Toplami
    vector<int> arr = {1, 2, 3, 4, 5};
    cout << "2) Dizi Toplami, Dizi = ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    cout << "   Sonuc: " << arraySum(arr, arr.size()) << " | Cagri Sayisi: " << countArraySum << "\n";

    // 3) a^n
    int a = 2, n = 10;
    cout << "3) a^n, a = " << a << ", n = " << n << endl;
    cout << "   Sonuc: " << power(a, n) << " | Cagri Sayisi: " << countPower << "\n";

    // 4) Fibonacci
    int f = 10;
    cout << "4) Fibonacci, n = " << f << endl;
    cout << "   Sonuc: " << fib(f) << " | Cagri Sayisi: " << countFib << "\n";

    // 5) Tower of Hanoi: Diskleri sıraya dizme
    int disks = 3;
    cout << "5) Tower of Hanoi, Disk Sayisi = " << disks << endl;
    hanoi(disks, 'A', 'C', 'B');
    cout << "   Toplam Cagri Sayisi: " << countHanoi << "\n";

    // 6) Recursive Digit Sum: Basamaklar toplamı
    int num = 9875;
    cout << "6) Recursive Digit Sum, Sayi = " << num << endl;
    cout << "   Sonuc: " << superDigit(num) << " | Ana Cagri: " << countDigitSum << " | Alt Cagri: " << countDigitSumOnce << "\n\n";

    return 0;
}