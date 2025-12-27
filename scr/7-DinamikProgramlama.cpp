/**
 * Proje: Algoritma Analizi ve Karmaşıklığı Dönem Ödevi
 * Problem 7: Dinamik Programlama (Dynamic Programming)
 * 1. Fibonacci Sayilari (Bottom-Up DP): Yinelemeli hesaplamayi tablo kullanarak O(N)'e dusurmek.
 * 2. Minimum Maliyetli Yol: Bir matriste (0,0)'dan (N-1, N-1)'e en dusuk maliyetle gitmek.
 * 3. Sirt Cantasi Problemi (Knapsack)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> // Tablo duzeni icin
#include <climits> // INT_MAX icin

using namespace std;

// Yardimci Fonksiyon: 2D Tabloyu Ekrana Yazdir
void printTable2D(const vector<vector<int>>& table, string title) {
    cout << "\n   [" << title << " Tablosu]\n";
    for (const auto& row : table) {
        cout << "   ";
        for (int val : row) {
            if (val == -1) cout << setw(5) << "-1"; // Hesaplanmamis
            else if (val == INT_MAX) cout << setw(5) << "INF";
            else cout << setw(5) << val;
        }
        cout << endl;
    }
    cout << endl;
}

// 1. FIBONACCI SAYILARI (BOTTOM-UP DP)
int fibBottomUp(int n) {
    if (n <= 1) return n;

    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {  // Tabloyu Doldur (Bottom-Up)
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    cout << "   [Fibonacci Tablosu]: ";
    for (int x : dp) cout << x << " ";
    cout << endl;

    return dp[n];
}

// 2. MINIMUM MALIYETLI YOL (TOP-DOWN DP / MEMOIZATION)

// Recursive Yardimci Fonksiyon (Memoization ile)
int minCostRec(int i, int j, int N, const vector<vector<int>>& costMatrix, vector<vector<int>>& memo) {
    if (i >= N || j >= N) return INT_MAX;
   
    if (i == N - 1 && j == N - 1) return costMatrix[i][j]; // Hedef Kontrolu (Sag alt kose)
    if (memo[i][j] != -1) return memo[i][j];  // Daha once hesaplandi mi? (Memoization)

    int down = minCostRec(i + 1, j, N, costMatrix, memo); // Recursive Adimlar (sadece Asagi ve Saga)
    int right = minCostRec(i, j + 1, N, costMatrix, memo);

    // Sonucu Kaydet ve Dondur
    if (min(down, right) == INT_MAX) {
         memo[i][j] = INT_MAX;
    } else {
         memo[i][j] = costMatrix[i][j] + min(down, right);
    }
    return memo[i][j];
}

void solveMinCostPath(const vector<vector<int>>& grid) {
    int N = grid.size();
    // Hesaplanmadıysa Memo tablosunu -1 ile baslat
    vector<vector<int>> memo(N, vector<int>(N, -1));

    int result = minCostRec(0, 0, N, grid, memo);

    cout << "   Min Maliyet: " << result << endl;
    printTable2D(memo, "Memoization (Min Cost)");
    cout << "   (Tablodaki -1'ler o hucreye hic gidilmedigini gosterir)\n";
}

// 3. SIRT CANTASI PROBLEMI (KNAPSACK)

// Yapi: Fractional icin veri yapisi
struct Item {
    int id;
    int value;
    int weight;
    double ratio; // Deger / Agirlik
};

// --- YONTEM A: 0-1 (DP - BOTTOM UP) ---
// Esya bolunemez. Ya hep ya hic.
int knapsack01(int W, const vector<int>& weights, const vector<int>& values, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    cout << "   [Yontem 1: 0-1 Knapsack (DP)]\n";
    cout << "   Maksimum Deger: " << dp[n][W] << endl;
    printTable2D(dp, "0-1 Knapsack DP Tablosu");
    
    return dp[n][W];
}

// --- YONTEM B: FRACTIONAL (GREEDY) ---
// Esya bolunebilir
double knapsackFractional(int W, vector<int> weights, vector<int> values, int n) {
    vector<Item> items;
    for(int i=0; i<n; i++) {
        items.push_back({i+1, values[i], weights[i], (double)values[i]/weights[i]});
    }

    // Ratio'ya gore buyukten kucuge sirala
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });

    double totalValue = 0.0;
    int currentWeight = 0;

    cout << "   [Yontem 2: Kesirli Knapsack (Greedy)]\n";
    cout << "   Secim Adimlari:\n";

    for (const auto& item : items) {
        if (currentWeight + item.weight <= W) {
            currentWeight += item.weight;
            totalValue += item.value;
            cout << "   - Esya " << item.id << " (Tamami): " << item.weight << "kg -> Deger: " << item.value << endl;
        } else {
            int remain = W - currentWeight;
            double fractionValue = item.value * ((double)remain / item.weight);
            totalValue += fractionValue;
            cout << "   - Esya " << item.id << " (Kesirli " << remain << "/" << item.weight << "): " << remain << "kg -> Deger: " << fractionValue << endl;
            break;
        }
    }
    cout << "   Maksimum Deger (Kesirli): " << totalValue << endl;
    
    return totalValue;
}

// Not: Fractional Knapsack, DP degil Greedy oldugu icin karsilastirma amacli eklenmistir.

int main() {
    cout << "7: DINAMIK PROGRAMLAMA\n\n";

    // --- 1: FIBONACCI (Bottom-Up) ---
    cout << "1. Fibonacci Sayisi (n=10)\n";
    int fibRes = fibBottomUp(10);
    cout << "   Sonuc F(10): " << fibRes << "\n";
    cout << "------------------------------------------------\n";

    // --- 2: MIN COST PATH (Top-Down) ---
    cout << "2. Minimum Maliyetli Yol (NxN Matris)\n";

    vector<vector<int>> costMatrix = {
        {1, 3, 5, 8},
        {4, 2, 1, 7},
        {4, 3, 2, 3},
        {1, 5, 1, 0} // 0: Hedef maliyeti
    };
    
    cout << "   Giris Matrisi:\n";
    for(auto& row : costMatrix) {
        cout << "   ";
        for(int x : row) cout << x << " ";
        cout << endl;
    }
    cout << endl;
    
    solveMinCostPath(costMatrix);
    cout << "------------------------------------------------\n";

    // 3. Knapsack Karsilastirmasi
    cout << "3. Sirt Cantasi Problemi (0-1 vs Kesirli)\n";
    cout << "   Veri Seti (Ders notlarından alınmıştır.):\n";
    
    vector<int> val = {30, 20, 100, 90, 160};
    vector<int> wt = {5, 10, 20, 30, 40};
    int W = 60;
    int n = val.size();

    cout << "   Kapasite: " << W << "\n";
    cout << "   Esyalar [Deger/Agirlik]: ";
    for(int i=0; i<n; i++) cout << "[" << val[i] << "/" << wt[i] << "] ";
    cout << "\n\n";

    // A) 0-1 (DP) - Sonucu degiskene atiyoruz
    int res01 = knapsack01(W, wt, val, n);
    cout << endl;

    // B) Fractional (Greedy) - Sonucu degiskene atiyoruz
    double resFrac = knapsackFractional(W, wt, val, n);
    
    // Dinamik Sonuc Cumlesi
    cout << "\n   [SONUC]: Kesirli yontem (" << resFrac << "),\n";
    cout << "            0-1 yonteminden (" << res01 << ") daha yuksek veya esit kazanc saglayabilir.\n";
    cout << "------------------------------------------------\n";

    return 0;
}