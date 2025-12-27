# 📘 Algoritma Analizi ve Karmaşıklığı – Dönem Projesi

Bu proje, **2025-2026 Güz Dönemi Algoritma Analizi ve Karmaşıklığı** dersi kapsamında hazırlanmıştır.  
Projenin temel amacı; algoritma tasarım yaklaşımlarını C++ programlama dili ile
uygulamak, bu algoritmaların zaman ve bellek karmaşıklıklarını analiz etmek ve
farklı çözüm stratejilerini karşılaştırmalı olarak incelemektir.

Bu kapsamda; **Brute Force, Divide & Conquer, Greedy, Heap, Rekürsif ve Dinamik Programlama**
yaklaşımları farklı problemler üzerinde ele alınmıştır.

---

## 🛠️ Kullanılan Ortam

- **Programlama Dili:** C++ (C++11 ve üzeri)
- **IDE:** Visual Studio Code
- **Derleyici:** GCC / MSVC
- **Zaman Ölçümü:** `<chrono>`
- **Standart Kütüphaneler:** `<vector>`, `<algorithm>`, `<queue>`, `<map>`, `<iomanip>`

---

## 👩‍💻 Geliştirici Bilgileri

Bu proje aşağıdaki öğrenci tarafından geliştirilmiştir:

- **Ad Soyad:** İrem KARAYEL  
- **Öğrenci No:** 231307101  
- **Bölüm:** Bilişim Sistemleri Mühendisliği  
- **Ders:** Algoritma Analizi ve Karmaşıklığı  
- **E-posta:** [iremkarayel.ik@gmail.com](mailto:iremkarayel.ik@gmail.com)  
- **GitHub:** [@iremkryl](https://github.com/iremkryl)

---

## 📁 Proje Yapısı

Her problem ayrı bir kaynak dosyası olacak şekilde düzenlenmiştir:

```text
Algoritma-Analizi
│
├── src/
│   ├── 1-MaxSubsequence.cpp
│   ├── 2-RekursifAlgoritma.cpp
│   ├── 3-AramaAlgoritma.cpp
│   ├── 4-SiralamaAlgoritma.cpp
│   ├── 5-HeapYapilari.cpp
│   ├── 6-GreedyAlgoritmalar.cpp
│   └── 7-DinamikProgramlama.cpp
│
├── .gitignore
└── README.md               
```

Bu yapı sayesinde kodlar **modüler**, **okunabilir** ve **bakımı kolay** hale getirilmiştir.

---

## 📂 Proje İçeriği

Proje toplam **7 ana modülden** oluşmaktadır:

---

## 1️⃣ Maximum Subsequence (Max Subarray) Problemi

**Amaç:**  
Bir dizide, toplamı en büyük olan ardışık alt diziyi bulmak.

**Uygulanan Yöntemler:**
1. Brute Force – O(N³)
2. Geliştirilmiş Brute Force – O(N²)
3. Divide & Conquer – O(N log N)
4. Kadane Algoritması – O(N)

**Analiz:**
- Tüm algoritmalar aynı veri seti üzerinde test edilmiştir.
- Çalışma süreleri `chrono` kütüphanesi ile ölçülmüştür.
- Algoritmalar performans ve zaman karmaşıklığı açısından karşılaştırılmıştır.

---

## 2️⃣ Rekürsif Algoritmalar

**Uygulanan Problemler:**
- 1 + 2 + … + N
- Dizi Elemanları Toplamı
- aⁿ Hesaplama
- Fibonacci Sayıları
- Tower of Hanoi
- Recursive Digit Sum (Super Digit)

**Önemli Noktalar:**
- Her problem için rekürsif çağrı sayısı analiz edilmiştir.
- Tower of Hanoi problemi için disk taşıma adımları ayrıntılı olarak yazdırılmıştır.
- Recursive Digit Sum işlemi, sonuç tek basamaklı olana kadar devam ettirilmiştir.

---

## 3️⃣ Arama Algoritmaları

**Uygulanan Algoritmalar:**
- İleri Yönlü Lineer Arama
- Geri Yönlü Lineer Arama
- İkili Arama (Binary Search)

**Analiz:**
- Aynı veri seti üzerinde testler yapılmıştır.
- Lineer ve logaritmik zaman karmaşıklıkları arasındaki farklar gözlemlenmiştir.

---

## 4️⃣ Sıralama Algoritmaları

**Temel Sıralamalar (O(N²)):**
- Selection Sort
- Bubble Sort
- Insertion Sort

**Gelişmiş Sıralamalar (O(N log N)):**
- Merge Sort
- Quick Sort
- Heap Sort

**Özel Sıralamalar:**
- Counting Sort (Stable)
- Radix Sort
- External Sorting (K-Way Merge Simülasyonu)

**Analiz:**
- Her algoritma için çalışma süreleri ölçülmüştür.
- External Sorting, büyük veri kümeleri için bellek kısıtı varsayımıyla simüle edilmiştir.

---

## 5️⃣ Heap Yapıları

**Uygulanan İşlemler:**
- Binary Heap (MinHeap & MaxHeap)
- insert
- findMin
- deleteMin (Heapify)
- buildHeap
- decreaseKey / increaseKey
- deleteKey
- merge (H1, H2)

**Çıktılar:**
- Her işlem sonrası heap yapısı ekrana yazdırılmıştır.
- Heap üzerindeki değişimler adım adım gözlemlenmiştir.

---

## 6️⃣ Greedy Algoritmalar

### 🔹 İş Zamanlama Problemi
- Süreye göre sıralama (Sort)
- Min-Heap kullanımı

Her iki yöntem için:
- İşlerin sıralanışı
- Ortalama tamamlanma süresi hesaplanmıştır.

### 🔹 Aktivite Zamanlama Problemi
- Kısa süreli aktivite seçimi (optimal olmayabilir)
- Erken bitiş zamanına göre seçim (optimal çözüm)

### 🔹 Huffman Kodlama
- Karakter frekanslarının hesaplanması
- Huffman ağacının oluşturulması
- Encode (sıkıştırma)
- Decode (çözme)
- Sabit örnek ve kullanıcı girdisi desteği

---

## 7️⃣ Dinamik Programlama

**Uygulanan Problemler:**
1. Fibonacci Sayıları (Bottom-Up DP)
2. Minimum Maliyetli Yol Problemi (Top-Down DP – Memoization)
3. 0-1 Sırt Çantası Problemi (Bottom-Up DP)

**Önemli Nokta:**
- Her problem için dinamik programlama tabloları ayrıntılı biçimde ekrana yazdırılmıştır.
- 0-1 Knapsack için DP tablosu gösterilerek çözüm adımları açıklanmıştır.
- Kesirli Sırt Çantası problemi, karşılaştırma amacıyla greedy yaklaşım ile eklenmiştir.

---

## 📊 Genel Değerlendirme

- Algoritmalar zaman karmaşıklığı ve performans açısından karşılaştırılmıştır.
- Aynı problemlerin farklı yaklaşımlarla çözülmesi sayesinde:
  - **Greedy vs Dinamik Programlama**
  - **Brute Force vs Optimize Yaklaşımlar**
  arasındaki farklar net biçimde gözlemlenmiştir.

---

## 📝 Sonuç

Bu proje, algoritma tasarımı ve analizi konularında teorik bilgilerin
pratik uygulamalarla pekiştirilmesini sağlamıştır.
Elde edilen sonuçlar, doğru algoritma seçiminin performans üzerindeki
kritik etkisini açıkça göstermektedir.

---

## 🙏 Teşekkür

Bu dersin yürütülmesinde ve algoritma analizine bakış açısı kazanmamda
katkılarından dolayı **Dr. Öğr. Üyesi Seda Balta Kaç**’a teşekkür ederim.

---

📌 **Not:**  
Bu proje akademik amaçlıdır ve ders kapsamında hazırlanmıştır.