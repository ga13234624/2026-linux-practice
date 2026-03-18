# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef struct node {
    struct node *next;
    int value;
} node;

//standard traversal
void single_pointer_traversal(node *head){
    node *cur = head;
    long sum = 0;
    while(cur != NULL){
        sum += cur->value;
        cur = cur->next;
    }
    volatile long s = sum;
}

//fast and slow pointer
void fast_and_slow_pointer(node *head){
    node *slow = head;
    node *fast = head;
    long sum = 0;
    while(fast != NULL && fast -> next != NULL){
        sum += fast->value;
        sum += slow->value;
        fast = fast -> next ->next;
        slow = slow -> next;
    }
    volatile long s = sum;
}


int main(int argc, char **argv){

    if(argc < 3){
        printf("Usage: %s <N> <mode: 0 for single, 1 for fast_slow>\n", argv[0]);
        return 1;
    }

    //讀取參數 
    long N = atol(argv[1]);//ascii to long
    int mode = atoi(argv[2]);
    //也可以用 scanf 找 kb in // 互動性

    //修改 rand() 裡面的 seed 為 time(NULL)
    //讓每次 rand 基於不同 seed 產生亂數
    srand(time(NULL));

    //nodes[i] 是一個 node*
    //指標的指標才可以非連續記憶體
    node **nodes = malloc(sizeof(node *) * N);

    //對每個 node 單獨配置
    //還沒串 linkedlist
    for(int i=0; i<N; i++){
        nodes[i] = malloc(sizeof(node));
        nodes[i]-> value = i;//隨意設
        nodes[i]-> next = NULL; //還沒串 linkedlist，避免垃圾值
    }

    //打亂 nodes[i] 中指標存的位址順序
    //再把 i 與 i+1 串起來
    for(long i=N-1; i>0; i--){
        long j = rand() % (i+1);
        node *tmp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = tmp;
    }

    for(int i=0; i<N ; i++){
        nodes[i]-> next = nodes[i+1];
    }

    nodes[N-1]->next = NULL;

    node *head = nodes[0];

    if (mode == 0) {
        for (int r = 0; r < 100; r++) {
            single_pointer_traversal(head);
        }
    } else {
        for (int r = 0; r < 100; r++) {
            fast_slow_pointer_traversal(head);
        }
    }


    for (int i = 0; i < N; i++) free(nodes[i]);
    free(nodes);

    return 0;


}

