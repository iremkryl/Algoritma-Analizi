/**
 * Proje: Algoritma Analizi ve Karmaşıklığı Dönem Ödevi
 * Problem 6: Greedy Algoritmalar
 * 1. İş Zamanlama
 * 2. Aktivite Zamanlama
 * 3. Huffman Kodlama (Sabit + Kullanıcı Girişi)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <string>

using namespace std;

// 1. IS ZAMANLAMA (JOB SCHEDULING)
struct Job {
    string id;
    int time;
};

// Yontem 1: Siralama (Sort)
void jobSchedulingSort(vector<Job> jobs) {
    // Süreye göre küçükten büyüğe göre
    sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        return a.time < b.time;
    });

    cout << "   [Sort Yontemi] Siralama: ";
    int currentTime = 0;
    double totalTime = 0;

    for (const auto& job : jobs) {
        currentTime += job.time;
        totalTime += currentTime;
        cout << job.id << "(" << job.time << ") ";
    }
    cout << "\n   Ortalama Sure: " << totalTime / jobs.size() << endl;
}

// Yontem 2: Min-Heap
void jobSchedulingHeap(vector<Job> jobs) {
    // Min-Heap tanimlama
    auto comp = [](const Job& a, const Job& b) { return a.time > b.time; };
    priority_queue<Job, vector<Job>, decltype(comp)> pq(comp);

    for (const auto& j : jobs) pq.push(j);

    cout << "   [Heap Yontemi] Siralama: ";
    int currentTime = 0;
    double totalTime = 0;
    int n = jobs.size();

    while (!pq.empty()) {
        Job top = pq.top();
        pq.pop();
        
        currentTime += top.time;
        totalTime += currentTime;
        cout << top.id << "(" << top.time << ") ";
    }
    cout << "\n   Ortalama Sure: " << totalTime / n << endl;
}

// 2. AKTIVITE ZAMANLAMA (ACTIVITY SELECTION)
struct Activity {
    int id;
    int start;
    int finish;
};

// Greedy 1: Kısa Sureli Olan İlk Yapılsın (Optimal Degil)
void activitySelectionDuration(vector<Activity> activities) {
    // Sureye gore sirala
    sort(activities.begin(), activities.end(), [](const Activity& a, const Activity& b) {
        return (a.finish - a.start) < (b.finish - b.start);
    });

    vector<Activity> selected;
    vector<int> timeSlots(100, 0); // Basit cakisma kontrolu
    
    for(const auto& act : activities) {
        bool overlap = false;
        for(int t = act.start; t < act.finish; t++) {
            if(timeSlots[t] == 1) overlap = true;
        }
        if(!overlap) {
            selected.push_back(act);
            for(int t = act.start; t < act.finish; t++) timeSlots[t] = 1;
        }
    }

    cout << "   [Greedy 1 - Kisa Sure] Secilenler: ";
    for (const auto& act : selected) cout << "a" << act.id << " ";
    cout << " (Not: Optimal olmayabilir)\n";
}

// Greedy 2: Erken Biten önce çalışsın (Optimal)
void activitySelectionFinishTime(vector<Activity> activities) {
    // 1. Bitis zamanina gore sirala
    sort(activities.begin(), activities.end(), [](const Activity& a, const Activity& b) {
        return a.finish < b.finish;
    });

    vector<Activity> selected;
    if (!activities.empty()) selected.push_back(activities[0]);

    // 2. Digerlerini kontrol et
    int prev = 0;
    for (int i = 1; i < activities.size(); i++) {
        if (activities[i].start >= activities[prev].finish) { // Cakisma yoksa ekle
            selected.push_back(activities[i]);
            prev = i;
        }
    }

    cout << "   [Greedy 2 - Erken Bitis] Secilenler: ";
    for (const auto& act : selected) cout << "a" << act.id << " ";
    cout << " (Optimal Cozum)\n";
}

// 3. HUFFMAN KODLAMA
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;
    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

// Agactan kodlari cikar (Recursive)
void generateCodes(HuffmanNode* root, string code, map<char, string>& huffmanCode) {
    if (!root) return;
    if (!root->left && !root->right) { // Yaprak dugum
        huffmanCode[root->ch] = code;
    }
    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

void huffmanCoding(string text) {
    if (text.empty()) return;

    map<char, int> freq;  //  Frekanslari say
    for (char c : text) freq[c]++;

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq; // Min-Heap olustur
    for (auto pair : freq) pq.push(new HuffmanNode(pair.first, pair.second));

    while (pq.size() != 1) {  // Agaci insa et
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* top = new HuffmanNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        pq.push(top);
    }
    
    map<char, string> huffmanCode;    //  Kodlari uret ve yazdir
    generateCodes(pq.top(), "", huffmanCode);

    cout << "\n   --- Analiz Sonuclari ('" << text << "') ---\n";
    cout << "   Karakter Kodlari:\n";
    for (auto pair : huffmanCode) cout << "   " << pair.first << ": " << pair.second << endl;

    string encodedStr = "";  //  Encode
    for (char c : text) encodedStr += huffmanCode[c];
    cout << "   Encoded (Sikistirilmis): " << encodedStr << endl;

    string decodedStr = "";    // Decode
    HuffmanNode* curr = pq.top();
    for (char bit : encodedStr) {
        curr = (bit == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right) { // Yaprak
            decodedStr += curr->ch;
            curr = pq.top();
        }
    }
    cout << "   Decoded (Cozulmus): " << decodedStr << endl;
}

int main() {
    cout << "6: GREEDY ALGORITMALARI\n\n";

    // 1. Is Zamanlama
    cout << "1. Is Zamanlama Problemi\n";
    vector<Job> jobs = { {"J1", 15}, {"J2", 50}, {"J3", 3}, {"J4", 10} };
    jobSchedulingSort(jobs);
    jobSchedulingHeap(jobs);
    cout << "------------------------------------------------\n";

    // 2. Aktivite Zamanlama
    cout << "2. Aktivite Zamanlama Problemi\n";
    vector<Activity> activities = {
        {1, 1, 4}, {2, 3, 5}, {3, 0, 6}, {4, 5, 7}, {5, 3, 8},
        {6, 5, 9}, {7, 6, 10}, {8, 8, 11}, {9, 8, 12}, {10, 2, 13}, {11, 12, 14}
    };
    activitySelectionDuration(activities);
    activitySelectionFinishTime(activities);
    cout << "------------------------------------------------\n";

    // 3. Huffman
    cout << "3. Huffman Kodlama\n";
    
    // A) Sabit Ornek
    cout << "A) Sabit Ornek:";
    huffmanCoding("abacdaacac");

    // B) Kullanici Girisi
    cout << "\nB) Kullanici Girisi:\n";
    cout << "   Bir kelime girin: ";
    string userInput;
    cin >> userInput;
    huffmanCoding(userInput);

    return 0;
}