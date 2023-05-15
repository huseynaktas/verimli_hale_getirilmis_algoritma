#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define A_SIZE 20
#define G_SIZE 10
#define MAX_W 10

// Max deger icin sonsuz sayi
#define INF INT_MAX

// Rastgele bir dizi oluşturur.
void generate(int a[], int size);

// Diziyi sıralar.
void sort_array(int a[], int size);

// Dizideki ortalama en büyük toplamı hesaplar.
int calculate_average_max_sum(int a[], int size);

// Verilen graf üzerinde en kısa yolları hesaplar.
void calculate_shortest_paths(int g[][G_SIZE], int d[][G_SIZE], int size);

// Diziyi ekrana yazdırır.
void print_array(int a[], int size);

// Grafı ekrana yazdırır.
void print_graph(int g[][G_SIZE], int size);

// Belirli bir eşik değerinden daha kısa olan yolları ekrana yazdırır.
void print_shortest_paths(int d[][G_SIZE], int size, int t);

int main() {
    int a[A_SIZE];
    int g[G_SIZE][G_SIZE] = {
    { 0, 10,  3,  0,  0,  5,  0, 17,  0, 22},
    {10,  0,  5,  0,  2,  0, 13,  0,  0,  0},
    { 3,  5,  0,  2,  0,  4,  0, 21,  0, 11},
    { 0,  0,  2,  0,  7,  0,  6,  0,  0,  0},
    { 0,  2,  0,  7,  0,  6,  0,  0, 19,  0},
    { 5,  0,  4,  0,  6,  0,  9,  3,  0,  0},
    { 0, 13,  0,  6,  0,  9,  0,  4,  0,  0},
    {17,  0, 21,  0,  0,  3,  4,  0,  8,  0},
    { 0,  0,  0,  0, 19,  0,  0,  8,  0,  5},
    {22,  0, 11,  0,  0,  0,  0,  0,  5,  0}
    };
    int d[G_SIZE][G_SIZE];
    int t;

    // Rastgele sayi uretici icin seed
    srand(time(NULL));

    // Calisma suresinin hesaplanmasi
    clock_t start, end;
    double time;

    start = clock();

    generate(a, A_SIZE);
    printf("A:\n");
    print_array(a, A_SIZE);

    sort_array(a, A_SIZE);
    printf("\nSorted Array:\n");
    print_array(a, A_SIZE);

    t = calculate_average_max_sum(a, A_SIZE);
    printf("\nAverage Max Sum: %d\n", t);

    printf("\nGraph:\n");
    print_graph(g, G_SIZE);

    calculate_shortest_paths(g, d, G_SIZE);
    printf("\nShortest Paths:\n");
       print_graph(d, G_SIZE);

    printf("\nPaths shorter than %d:\n", t);
    print_shortest_paths(d, G_SIZE, t);

    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nExecution Time: %f seconds\n", time);

    return 0;
}

void generate(int a[], int size) {
    // Verilen boyutta bir dizi oluşturur ve rastgele değerlerle doldurur.
    for (int i = 0; i < size; i++) {
        a[i] = rand() % (2 * MAX_W) - MAX_W;
    }
}

void sort_array(int a[], int size) {
    // Diziyi sıralamak için bubble sort algoritmasını kullanır.
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

int calculate_average_max_sum(int a[], int size) {
    // Dizideki en büyük toplamı ve ortalamasını hesaplar.
    int t = 0, current_sum = 0, count = 0;
    for (int i = 0; i < size; i++) {
        if (current_sum + a[i] > 0) {
            current_sum = current_sum + a[i];
        }
        else {
            current_sum = 0;
        }
        if (current_sum > t) {
            t = current_sum;
            count++;
        }
    }
    return t / count;
}

void calculate_shortest_paths(int g[][G_SIZE], int d[][G_SIZE], int size) {
    // Verilen graf üzerinde en kısa yolları hesaplamak için Floyd-Warshall algoritmasını kullanır.
    // Başlangıçta, d matrisi g matrisine eşitlenir ve ardından algoritma uygulanır.
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                d[i][j] = 0;
            }
            else if (g[i][j] != 0) {
                d[i][j] = g[i][j];
            }
            else {
                d[i][j] = INF;
            }
        }
    }
     for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (d[i][k] != INF && d[k][j] != INF &&
                    d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}
void print_array(int a[], int size) {
    // Diziyi ekrana yazdırır. Her 10 elemandan sonra bir satır başına geçer.
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
}

void print_graph(int g[][G_SIZE], int size) {
    // Grafı ekrana yazdırır. Sonsuz değeri olan hücreler "INF" olarak yazdırılır.
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (g[i][j] == INF) {
                printf("INF ");
            }
            else {
                printf("%3d ", g[i][j]);
            }
        }
        printf("\n");
    }
}

void print_shortest_paths(int d[][G_SIZE], int size, int t) {
    // Belirli bir eşik değerinden daha kısa olan yolları ekrana yazdırır.
    for (int i = 0; i < size; i++) {
         for (int j = 0; j < size; j++) {
            if (d[i][j] < t) {
                printf("(%d, %d): %d\n", i, j, d[i][j]);
            }
        }
    }
}

