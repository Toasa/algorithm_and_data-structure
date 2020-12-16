// This is implementation of priority queue, which is called heap.
// This simulates perfect binary tree using a array.
// NOTE: This is Min-heap, a parent is always less than or equal children.

#include <stdio.h>
#include <stdlib.h>

const size_t LEN = 15;

typedef struct {
    int q[LEN+1];
    int n;
} priorityQueue;

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

size_t left_i(size_t i) {
    return 2*i + 1;
}

size_t right_i(size_t i) {
    return 2*i + 2;
}

size_t parent_i(size_t i) {
    return (i-1) / 2;
}

void print(priorityQueue *pq) {
    for (size_t i = 0; i < LEN; i++) {
        if (i == pq->n) {
            printf("| ");
        }
        printf("%d ", pq->q[i]);
    }
    printf("\n");
}

void bubble_up(priorityQueue *pq, int i) {
    int p_i = parent_i(i);
    while (i > 0 && (pq->q[p_i] > pq->q[i])) {
        swap(&pq->q[p_i], &pq->q[i]);
        i = p_i;
        p_i = parent_i(i);
    }
}

void insert(priorityQueue *pq, int val) {
    pq->q[pq->n] = val;
    bubble_up(pq, pq->n);
    pq->n++;
}

priorityQueue *new(int arr[LEN]) {
    priorityQueue *pq = calloc(1, sizeof(priorityQueue));
    for (size_t i = 0; i < LEN; i++) {
        insert(pq, arr[i]);
    }
    return pq;
}

void trickle_down(priorityQueue *pq, int i) {
    while (i < pq->n) {
        int j = -1;
        int l_i = left_i(i);
        int r_i = right_i(i);
        if (r_i <= pq->n && pq->q[r_i] < pq->q[i] ) {
            if (pq->q[l_i] < pq->q[r_i]) {
                j = l_i;
            } else {
                j = r_i;
            }
        } else {
            if (l_i < pq->n && pq->q[l_i] < pq->q[i]) {
                j = l_i;
            }
        }
        if (j < 0) {
            return;
        }
        swap(&pq->q[i], &pq->q[j]);
        i = j;
    }
}

void sort(priorityQueue *pq) {
    pq->n--;
    for (int i = pq->n; i > 0; i--) {
        int *min = &pq->q[0];
        int *last = &pq->q[i];
        swap(min, last);
        print(pq);
        pq->n--;
        trickle_down(pq, 0);
    }
}

int main() {
    int arr[LEN] = {
        8, 1, 4, 2, 11,
        9, 0, 3, 14, 10,
        5, 12, 7, 6, 13,
    };

    // Structure of pq->q is already heap.
    // But it is not sorted yet.
    priorityQueue *pq = new(arr);

    sort(pq);
    print(pq);
}
