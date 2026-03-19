#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    struct node *next;
    int value;
} node;

// Mode 0: 單指標兩輪走訪 (第一輪算長度，第二輪找中點)
node* find_middle_two_pass(node *head) {
    node *cur = head;
    int n = 0;
    
    // 第一輪：走訪全體計算長度
    while (cur) {
        ++n;
        cur = cur->next;
    }
    
    // 第二輪：重新從頭走 N/2 步
    int k = 0;
    cur = head;
    while (k < n / 2) {
        ++k;
        cur = cur->next;
    }
    return cur; // 返回中點
}

// Mode 1: 快慢指標單輪走訪
node* find_middle_fast_slow(node *head) {
    node *slow = head;
    node *fast = head;
    
    // 同時進行，slow 的 reuse distance 非常短
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow; // 返回中點
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <N> <mode: 0 for Two-Pass, 1 for Fast-Slow>\n", argv[0]);
        return 1;
    }

    long N = atol(argv[1]);
    int mode = atoi(argv[2]);

    srand(time(NULL));

    // 1. 配置與初始化節點
    node **nodes = malloc(sizeof(node *) * N);
    for (int i = 0; i < N; i++) {
        nodes[i] = malloc(sizeof(node));
        nodes[i]->value = i;
        nodes[i]->next = NULL;
    }

    // 2. 隨機打亂以破壞空間局部性 (Spatial Locality)
    for (long i = N - 1; i > 0; i--) {
        long j = rand() % (i + 1);
        node *tmp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = tmp;
    }

    // 3. 串接 Linked List
    for (int i = 0; i < N - 1; i++) {
        nodes[i]->next = nodes[i + 1];
    }
    nodes[N - 1]->next = NULL;
    node *head = nodes[0];

    // 4. 執行實驗
    // 使用 volatile 指標防止編譯器將「未使用的結果」優化掉
    volatile node *mid = NULL;

    if (mode == 0) {
        for (int r = 0; r < 100; r++) {
            mid = find_middle_two_pass(head);
        }
    } else {
        for (int r = 0; r < 100; r++) {
            mid = find_middle_fast_slow(head);
        }
    }

    // 5. 釋放記憶體
    for (int i = 0; i < N; i++) free(nodes[i]);
    free(nodes);

    return 0;
}