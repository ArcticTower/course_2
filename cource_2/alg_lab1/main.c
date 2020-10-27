#define AR1 2000
#define AR2 5000
#define AR3 6800
//#define AR1 8
//#define AR2 9
//#define AR3 10


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>


//2000 5000 6800

long gethash(long value, long key){
    long res = value%key;
    return res;
}
struct Node{
    long val;
    struct Node* next;
};

int main(){
    struct timeval start_time, end_time;
    struct timeval t_reandomseed;
    long _random;
    int mid_time_build, mid_time_find;
    long milli_time, seconds, useconds, M1, M2;
    int arr_len[3];
    arr_len[0]=AR1;
    arr_len[1]=AR2;
    arr_len[2]=AR3;
    int collision =0;
    for (int num =0;num<3;num++){
            int len = arr_len[num];


            //gen mass
            long *arr = (long *)malloc(sizeof(long)*len);
            for(int i=0;i<len;i++){
                gettimeofday(&t_reandomseed,NULL);
                _random = t_reandomseed.tv_usec;
                srandom(_random);
                arr[i] = random()%1000;
            }
            //gen mass end

            gettimeofday(&start_time,NULL);
            //build hashtable
            //find good key
            long key=0;
            for(int i =0;i<len;i++){
                long lbuf = arr[i]/2;
                if(lbuf>key){
                    key = lbuf;
                }
            }
            //end find good key

            //definding hashtable len
            long ht_index =0;
            for (int i =0;i<len;i++){
                long hash = gethash(arr[i],key);
                if (hash > ht_index){ ht_index=hash;}
            }

            //end definding hashtable len

            //alloc ht
            struct Node* ht = (struct Node*)malloc((sizeof(struct Node))*(ht_index + 1));
            for(long i=0;i <= ht_index;i++){
                ht[i].val=0;
                ht[i].next=NULL;

            }
            //end alloc ht

            //gen table
            for (int i=0;i<len;i++){
                long hash = gethash(arr[i],key);

                if(ht[hash].val==0){
                    ht[hash].val=arr[i];
//                    ht[hash].next=NULL;

                } else{
                    //debug
                    struct Node* cur_ptr = &ht[hash];//ht+sizeof(struct Node)*hash;//&ht[hash];
                    while (cur_ptr->next!=NULL){
                        cur_ptr=cur_ptr->next;
                    }
                    struct Node* buf_ptr = (struct Node*)malloc(sizeof(struct Node));
                    cur_ptr->next=buf_ptr;
                    buf_ptr->val=arr[i];
                    buf_ptr->next=NULL;

                }


            }
            //end gen table
            //end build table


            gettimeofday(&end_time,NULL);
            //time
        seconds = end_time.tv_sec - start_time.tv_sec;
        useconds = end_time.tv_usec - start_time.tv_usec;
        milli_time = (long)((long double) (((long double)seconds) * 1000) + (long double)((long double)useconds/1000.0));
        if(num==0){M1 = milli_time;}
        else{
            M1 = (long)(((long double)M1 +(long double)milli_time)/2);
        }
        printf("time spend:%ld\n",milli_time);
            //end time


            gettimeofday(&start_time,NULL);
            //get value from ht
            for(int i =0;i<len;i++){
                long val = arr[i];
                int collision_tmp=0;
                long hash = gethash(val,key);
                struct Node* cur_ptr =&ht[hash];//ht+sizeof(struct Node)*hash;
                while (cur_ptr!=NULL){
                    printf("%ld, ",cur_ptr->val);
                    cur_ptr=cur_ptr->next;
                    collision_tmp++;
                }
                printf("\n");
                if(collision_tmp>collision){collision=collision_tmp;}
            }
            //end get value from ht
            gettimeofday(&end_time,NULL);
        //time
        seconds = end_time.tv_sec - start_time.tv_sec;
        useconds = end_time.tv_usec - start_time.tv_usec;
        milli_time = (long)((long double) (((long double)seconds) * 1000) + (long double)((long double)useconds/1000.0));
        if(num==0){M2 = milli_time;}
        else{
            M2 = (long)(((long double)M2 +(long double)milli_time)/2);
        }
        printf("2 time spend:%ld\n",milli_time);
        //end time


            //free
            //debug
            printf("size %ld\n",sizeof(struct Node));
            for(long i =ht_index; i >= 0; i--){
                struct Node* ptr;
                struct Node* prev;
                ptr = &ht[i];//ht+sizeof(struct Node)*i;///&ht[i];
//
//                    while (ptr->next!=NULL){
//                        ptr=ptr->next;
//                    }
//                    free(ptr);
                ptr=ptr->next;
                while (ptr!=NULL){
                    prev=ptr;
                    ptr=ptr->next;
                    free(prev);
                }

            }
            free(ht);
            //end free
    }
        //res print
        printf("\nMax collisionn was: %d\n",collision);
        printf("Time for build = %ld",M1);
        printf("Time for find = %ld", M2);

    return 0;
}