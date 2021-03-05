#include <iostream>

// min-heap
template <typename T>
struct PQ {
    T *q;
    int cap;
    int len; // 最後の空き領域のインデックスを指す

    PQ (int cap) {
        q = (T *)(calloc(1, sizeof(T) * cap));
        cap = cap;
        len = 0;
    }

    void insert(T elem) {
        q[len] = elem;
        bubbleUp(len);
        len++;
    }

    T extractMin() {
        T min = q[0];
        q[0] = q[len - 1];
        len--;
        bubbleDown(0);
        return min;
    }

    void bubbleUp(int i) {
        int p;
        if ((p = parent(i)) == -1) {
            return;
        }
        if (q[p] > q[i]) {
            swap(p, i);
            bubbleUp(p);
        }
    }

    void bubbleDown(int i) {
        int l = left(i);
        int r = right(i);

        if (l == -1)
            return;
        if (l != -1 && r == -1) {
            if (q[i] > q[l]) {
                swap(i, l);
            }
            return;
        }

        // i, l, r のインデックスの中で要素が一番小さいものを取得する
        int min_i = i;
        if (q[i] > q[l]) {
            min_i = l;
        }
        if (q[min_i] > q[r]) { // q[i] > q[r] ではないことに注意
            min_i = r;
        }
        
        if (i != min_i) {
            swap(i, min_i);
            bubbleDown(min_i);
        }
    }

    void swap(int i, int j) {
        T tmp = q[i];
        q[i] = q[j];
        q[j] = tmp;
    }

    int parent(int n) {
        if (n == 0) {
            return -1;
        }
        return (n + 1) / 2 - 1;
    }

    int left(int n) {
        int l = n * 2 + 1;
        if (l >= len)
            return -1;
        return l;
    }

    int right(int n) {
        int r = n * 2 + 2;
        if (r >= len)
            return -1;
        return r;
    }

    void print() {
        for (int i = 0; i < len; i++) {
            printf("%d ", q[i]);
        }
        printf("\n");
    }
};

template <typename T>
PQ<T> *make_heap(T *arr, int size) {
    PQ<T> *pq = new PQ<T>(size);
    for (int i = 0; i < size; i++) {
        pq->insert(arr[i]);
    }
    return pq;
}

int main() {
    const int SIZE = 14;
    int arr[SIZE] = {
        50, 100, 25, 5, 70, 40, 75,
        10, 20, 55, 35, 45, 90, 85,
    };

    auto qp = make_heap<int>(arr, SIZE);
    qp->print();

    for (int i = 0; i < SIZE; i++) {
        std::cout << qp->extractMin() << std::endl;
    }
}
