#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

struct Tree{

    long value;

    struct Tree* left;
    struct Tree* right;
    struct Tree* per;
};

struct Node{
    long value;
    struct Node* next;
};

struct Tree_Node{
    struct Tree* tree;
    struct Tree_Node* next;
};

//make balanced tree
int make_Tree(struct Node* node, struct Tree_Node* tn) {

    struct Node* curret_node = node;

    struct Tree_Node *this_th = tn;

    struct Tree_Node* new_node_root = (struct Tree_Node*)malloc(sizeof(struct Tree_Node));
    struct Tree_Node* new_node_cur = new_node_root;
    struct Tree_Node* new_node_prev = new_node_root;
    struct Tree* buf;
    int counter =0;


    while (this_th != NULL){
        if(curret_node!=NULL){
            counter++;
            this_th->tree->value=curret_node->value;
            curret_node = curret_node->next;


            if(new_node_cur==NULL) {
                new_node_cur = (struct Tree_Node*)malloc(sizeof(struct Tree_Node));
                new_node_prev->next=new_node_cur;
            }

            this_th->tree->left=(struct Tree*)malloc(sizeof(struct Tree));
            this_th->tree->left->per=this_th->tree;
            new_node_cur->tree=this_th->tree->left;
            new_node_cur->next=(struct Tree_Node*)malloc(sizeof(struct Tree_Node));
            new_node_cur=new_node_cur->next;

            this_th->tree->right=(struct Tree*)malloc(sizeof(struct Tree));
            this_th->tree->right->per=this_th->tree;
            new_node_cur->tree=this_th->tree->right;
            new_node_prev = new_node_cur;
            new_node_cur->next=NULL;
            new_node_cur = new_node_cur->next;

            this_th=this_th->next;
        } else {
            buf = this_th->tree->per;
            this_th=this_th->next;
            if(counter%2==0){
                free(buf->left);
                buf->left=NULL;
                free(buf->right);
                buf->right=NULL;
            } else{
                free(buf->right);
                buf->right=NULL;
            }
            while (this_th!=NULL){

                buf = this_th->tree->per;

                if(this_th->next!=NULL){
                    this_th=this_th->next;
                }
                this_th=this_th->next;

                free(buf->left);
                buf->left=NULL;

                free(buf->right);
                buf->right=NULL;
            }

            while (new_node_root!=NULL){
                struct Tree* nbuf = new_node_root->tree->per;

                if(new_node_root->next!=NULL){
                    new_node_root=new_node_root->next;
                }
                new_node_root=new_node_root->next;

                free(nbuf->left);
                nbuf->left=NULL;
                free(nbuf->right);
                nbuf->right=NULL;

            }

            return 0;
        }

    }


    if(curret_node==NULL){
//        buf = new_node_root->tree->per;
//        new_node_root=new
        while (new_node_root!=NULL){
            buf = new_node_root->tree->per;

            if(new_node_root->next!=NULL){
                new_node_root=new_node_root->next;
            }
            new_node_root=new_node_root->next;
            free(buf->left);
            buf->left=NULL;

            free(buf->right);
            buf->right=NULL;
        }
        return 0;
    }
    make_Tree(curret_node,new_node_root);
    return 0;
}

int get_from_Tree_prefix(struct Tree* tree){

    printf("%ld ",tree->value);
    if(tree->left!=NULL){
        get_from_Tree_prefix(tree->left);
    }
    if(tree->right!=NULL){
        get_from_Tree_prefix(tree->right);
    }


    return 0;
}

int get_from_Tree_infix(struct Tree* tree){


    if(tree->left!=NULL){
        get_from_Tree_prefix(tree->left);
    }
    printf("%ld ",tree->value);
    if(tree->right!=NULL){
        get_from_Tree_prefix(tree->right);
    }


    return 0;
}

int get_from_Tree_postfix(struct Tree* tree){


    if(tree->left!=NULL){
        get_from_Tree_prefix(tree->left);
    }
    printf("%ld ",tree->value);
    if(tree->right!=NULL){
        get_from_Tree_prefix(tree->right);
    }
    printf("%ld ",tree->value);

    return 0;
}

struct Node* restruct_tree(struct Tree* root, struct Node* node){
    node->value=root->value;


    if(root->left!=NULL){
        node->next=(struct Node*)malloc(sizeof(struct Node));
        node=node->next;
        node = restruct_tree(root->left, node);
    }

    if (root->right!=NULL){
        node->next=(struct Node*)malloc(sizeof(struct Node));
        node=node->next;
        node = restruct_tree(root->right, node);
    }
    return node;
}

int count_n(int n){
    if(n<1){
        return 0;
    }
    return n+count_n(n-1);
}

int cleartext()
{

    if (printf("\033[2J") < 0)
    {
        return 1;
    }
    if (printf("\033[0;0H")<0){
        return 1;
    }
    return 0;
}
////Todo: remove goto
////Todo: add comments
int main() {
    struct timeval start_time, end_time;
    long seconds, useconds,milli_time;
    struct timeval t_reandomseed;
    long _random;
    int A ;
    int chos;

    menu:
    cleartext();
    printf("\n");
    A=1;
    int ch2=0;
    chos=0;

    printf("MENU:\n");
    printf("1 - Build unbalanced Tree\n");
    printf("2 - Build balanced Tree\n");
    printf("3 - Count sum\n");
    printf("4 - exit\n");


    scanf("%d",&chos);
    cleartext();
    if(chos==4){exit(0);}
    if(chos==1 || chos == 2) {
        entA:
        printf("Enter number uf elements:\n");
        scanf("%d", &A);
        if(A<1){
            printf("\n Not valid");
            goto entA;
        }
        cleartext();

        printf("Generate %d random numbers:\n",A);
        long arr[A];
        struct Node *node = malloc(sizeof(struct Node));
        struct Node *root_node = node;
        struct Node *prev = node;

        //gen massive and node
        for (int i = 0; i < A; i++) {
            if (node == NULL) {
                node = (struct Node *) malloc(sizeof(struct Node));
                prev->next = node;
            }
            gettimeofday(&t_reandomseed, NULL);
            _random = t_reandomseed.tv_usec;
            srandom(_random);
            arr[i] = random() % 1000;
            node->value = arr[i];
            node->next = NULL;
            prev = node;
            node = node->next;
            printf("%ld ", arr[i]);
        }
        printf("\n");
        printf("\n");
        //end gen massive and node


        //build tree
        //8, 10, 12
        struct Tree *root = (struct Tree *) malloc(sizeof(struct Tree));
        struct Tree_Node *container = (struct Tree_Node *) malloc(sizeof(struct Tree_Node));
        container->tree = root;
        container->next = NULL;
        make_Tree(root_node, container);
        //end build tree
        tree:
        printf("\n");
        ch2=0;

        printf("Tree:\n");
        printf("1 - prefix count\n");
        printf("2 - infix count\n");
        printf("3 - postfix count\n");
        printf("4 - rebalance Tree\n");
        printf("5 - back\n");
        scanf("%d",&ch2);

        switch (ch2) {
            case 1:
                gettimeofday(&start_time,NULL);
                get_from_Tree_prefix(root);
                gettimeofday(&end_time,NULL);

                break;
            case 2:
                gettimeofday(&start_time,NULL);
                get_from_Tree_infix(root);
                gettimeofday(&end_time,NULL);
                break;
            case 3:
                gettimeofday(&start_time,NULL);
                get_from_Tree_postfix(root);
                gettimeofday(&end_time,NULL);
                break;
            case 4:
                gettimeofday(&start_time,NULL);
                while (root_node!=NULL){
                    prev = root_node;
                    root_node=root_node->next;
                    free(prev);
                }
                root_node = (struct Node*)malloc(sizeof(struct Node));
                node = restruct_tree(root,root_node);
                node->next=NULL;
                container=(struct Tree_Node *) malloc(sizeof(struct Tree_Node));
                container->tree = root;
                container->next = NULL;
                make_Tree(root_node, container);
                gettimeofday(&end_time,NULL);
                break;
            case 5:
                goto menu;
                break;
            default:
                goto menu;
        }
        //time
        seconds = end_time.tv_sec - start_time.tv_sec;
        useconds = end_time.tv_usec - start_time.tv_usec;
        milli_time = (long)((long double) (((long double)seconds) * 1000) + (long double)((long double)useconds/1000.0));

        printf("Time spend:%ld\n",milli_time);
        //end time

        goto tree;
    } else if(chos==3){
        int ch3;
        int n;
        int sum;
        cleartext();
        sum:
        sum =0;
        ch3 = 0;
        printf("\n");
        printf("Count sum like:\n");
        printf("1 - cycle\n");
        printf("2 - in function\n");
        printf("3 - back\n");
        scanf("%d",&ch3);
        if(ch3 ==1 || ch3 == 2){
            N:
            printf("Enter n:\n");
            scanf("%d",&n);
            if(n<1){
                printf("Invalid value\n");
                goto N;
            }
        }
        switch (ch3) {
            case 1:
                sum =0;
                gettimeofday(&start_time,NULL);
                for(int i =0;i<n;i++){
                    sum+=i;
                }
                gettimeofday(&end_time,NULL);
                printf("Sum is %d\n",sum);

                break;
            case 2:

                gettimeofday(&start_time,NULL);
                sum = count_n(n);
                gettimeofday(&end_time,NULL);

                printf("Sum is %d\n",sum);
                break;
            case 3:
                goto menu;
            default:
                goto sum;

        }
        //time
        seconds = end_time.tv_sec - start_time.tv_sec;
        useconds = end_time.tv_usec - start_time.tv_usec;
        milli_time = (long)((long double) (((long double)seconds) * 1000) + (long double)((long double)useconds/1000.0));
        printf("Time spend:%ld\n",milli_time);
        //end time
        goto sum;
    } else{goto menu;}
}
