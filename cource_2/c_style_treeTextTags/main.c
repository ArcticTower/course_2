//#ifndef TEXTTOTAGSANDLINKS_LIBRARY_H
//#define TEXTTOTAGSANDLINKS_LIBRARY_H
//
//
//#endif //TEXTTOTAGSANDLINKS_LIBRARY_H

#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
typedef struct FNNode{
    char * filename;
    struct FNNode* next;
}FNNode;

typedef struct Tree{
    long id;
    char littera;
    struct Tree* brother;
    struct Tree* child;
    FNNode* first_node;
}Tree;

typedef struct Id_line{
    Tree* node;
    struct Id_line* next;
    struct Id_line* prev;
    long bro_id;
    long child_id;
}Id_line;


int print_tree(Tree* root){
    printf("id:%ld littera:%c\n",root->id,root->littera);
    if(root->brother!=NULL){
        print_tree(root->brother);
    }
    if(root->child!=NULL){
        print_tree(root->child);
    }
    return 0;
}

//work with strings
//id,":", file_name, ", ",.. , ", ", file_name, "\n".
//if there is no string in node, it and id would not we written in file
int save_current_tree_file_names(Tree* current, FILE* file, long int* mov){
    if(file == NULL){
        return 1;
    }
    if(mov == NULL || *mov <0){
        return 2;
    }
    if(current == NULL){
        return 3;
    }
    fseek(file, *mov, SEEK_SET);
    if(current->first_node!=NULL){
        FNNode* current_node = current->first_node;
        fprintf(file,"%ld:",current->id);
        fprintf(file,"%s",current_node->filename);
        current_node=current_node->next;
        while (current_node!=NULL){
            fprintf(file,",%s",current_node->filename);
            current_node=current_node->next;
        }
        fprintf(file,"\n");
    }
    *mov = ftell(file);

    if(current->brother!=NULL){
        int res;
        res = save_current_tree_file_names(current->brother, file, mov);
        if(res != 0){
            return res;
        }
    }

    if(current->child!=NULL){
        int res;
        res = save_current_tree_file_names(current->child,file,mov);
        if(res!=0){
            return res;
        }
    }

    return 0;

}

//data not separated
//id, littera, brother id, child id
//1 - ptr error
//2 - file ptr error
//3 - move value error
int save_current_tree(Tree* current, FILE* file, long int* mov){
    if(current==NULL){
        return 1;
    }
    if (file==NULL){
        return 2;
    }
    if(mov == NULL || *mov<0 ){
        return 3;
    }

    //move to position
    fseek(file,*mov,SEEK_SET);

    //write id
    fwrite(&(current->id),sizeof(current->id),1,file );

    //write littera
    fwrite(&(current->littera),sizeof(current->littera),1,file);

    //write brother id
    if(current->brother!=NULL){
        fwrite(&(current->brother->id),sizeof(current->brother->id),1,file);
    } else{
        long bro_buf = -1;
        fwrite(&bro_buf,sizeof(bro_buf),1,file);
    }

    //write childe id
    if(current->child!=NULL){
        fwrite(&(current->child->id),sizeof(current->child->id),1,file);
    } else{
        long child_buf = -1;
        fwrite(&(child_buf),sizeof(child_buf),1,file);
    }

    // call for bro and child
    long int new_mov = ftell(file);
    *mov = new_mov;
    int res=0;

    if(current->brother!=NULL){
        res = save_current_tree(current->brother, file, mov);
    }
    if(res!=0){return res;}

    if(current->child!=NULL){
        res = save_current_tree(current->child,file,mov);
    }
    if(res!=0){return res;}

    return 0;
}


//bro and child id's is -1 if not exist
//1 - error file open
//2 - error save one of tree node
//3 - error file close
//4 - error save names file
int save_tree_to_file_first_time(Tree* root, char* file_name_id, char* file_name_strings){
    FILE* file;
    long int mov = 0;

    file = fopen(file_name_id,"w+b");
    if(file==NULL){
        return 1;
    }
    fseek(file,mov,SEEK_SET);

    int res;
    res = save_current_tree(root,file,&mov);
    if(res != 0){return 2;}

    if(fclose(file)!=0){
        return 3;
    }

    file = fopen(file_name_strings,"w");
    if(file==NULL){
        return 1;
    }
    mov =0;
    res = save_current_tree_file_names(root,file,&mov);
    if(res !=0){
        return 4;
    }
    if(fclose(file)!=0){
        return 3;
    }
    return 0;

}


//Entry of Id_line** should be NOT NULL
//1 - file pointer is incorrect
//2 - entry Id_line is not NULL
//3, 4, 5 - error of reading element from file
int load_ids_to_line(Id_line** last_node, FILE* file_ids){
    long id;
    long bro_id;
    long child_id;
    char littera;



    if(file_ids == NULL){
        return 1;
    }

    if(last_node == NULL){
        return 2;
    }

//    Tree* tree;
    Id_line* line_node = (Id_line*)malloc(sizeof(Id_line));
    line_node->prev=NULL;


    while (fread(&id,sizeof(id),1,file_ids) == 1){
        if(fread(&littera,sizeof(littera),1,file_ids) !=1 ){
            return 3;
        }
        if(fread(&bro_id,sizeof(bro_id),1,file_ids) != 1){
            return 4;
        }
        if(fread(&child_id,sizeof(child_id),1,file_ids) != 1){
            return 5;
        }

        line_node->child_id = child_id;
        line_node->bro_id = bro_id;

        line_node->node = (Tree*)malloc(sizeof(Tree));
        line_node->node->id= id;
        line_node->node->littera = littera;

        line_node->next = (Id_line*)malloc(sizeof(Id_line));
        line_node->next->prev=line_node;
        line_node = line_node->next;

    }

    line_node = line_node->prev;
    free(line_node->next);
    line_node->next=NULL;
    //now line_node is in the end of line


    *last_node = line_node;

    return 0;
}

// -1 - there is no id
// 1 - pointer error
int find_id_in_line(long int id, Id_line** id_line){

    if(id_line==NULL || *id_line == NULL){
        return 1;
    }
    Id_line* current;

    current = *id_line;

    if(current->node->id == id){
        return 0;
    }

    while (current->next != NULL){
        current = current->next;
        if(current->node->id == id){
            *id_line = current;
            return 0;
        }
    }

    current = *id_line;

    while (current->prev != NULL){
        current=current->prev;
        if(current->node->id==id){
            *id_line = current;
            return 0;
        }
    }


    return -1;
}


//1 - file pointer error
//2 - Id_line pointer error
//3 - not valid id
//4 - there is no valid id
//5 - find_id_line ptr error
//6 - out of mem
int load_strings_to_trees_in_node(Id_line* idLine, FILE* file_strings){
    if(file_strings == NULL){
        return 1;
    }
    if(idLine == NULL){
        return 2;
    }
//    char* line = NULL;
    char line[1000];
//    size_t len = 0;
    long id;

    Id_line* current_id_line = idLine;
    while (fgets(line,1000,file_strings)!=NULL){// i changed it &line

        char* token = strtok(line,":");
        char* end;
        id = strtol(token,&end,10);
        if(*end){
            return 3;
        }
//        id = atol(token);
        if(id<0){
            return 3;
        }
        int res;
        res = find_id_in_line(id, &current_id_line);
        if (res == -1){
            return 4;
        }
        if(res != 0){
            return 5;
        }

        char *string = strtok(NULL, ":");

        if(token!=NULL) {
            token = strtok(string,", ");
            current_id_line->node->first_node = (FNNode*)malloc(sizeof(FNNode));
            if(current_id_line->node->first_node == NULL){return 6;}
            FNNode * current_fnnnode = current_id_line->node->first_node;
            while (token!=NULL){
                current_fnnnode->filename=(char *)malloc(sizeof(char)*(strlen(token)+1));
                if(current_fnnnode->filename==NULL){return 6;}
                strcpy(current_fnnnode->filename,token);
                current_fnnnode->filename[strlen(token)]='\0';
                token = strtok(NULL,", ");
                if(token!=NULL) {
                    current_fnnnode->next = (FNNode *) malloc(sizeof(FNNode));
                    if(current_fnnnode->next == NULL){return 6;}
                    current_fnnnode = current_fnnnode->next;
                } else{
                    current_fnnnode->next=NULL;
                }
            }
        } else{
            current_id_line->node->first_node=NULL;
        }
        //it can contain error
//        free(line);
    }

    return 0;
}

//
//2 - ptr error
//3 - id error
//4 - search error
int load_tree(Tree* root, Id_line* id_line){
    if(root==NULL || id_line == NULL){
        return 2;
    }
//    Id_line id_line_tmp_ptr;
    long bro_id;
    long child_id;
    long this_id;
    int res;
    //find in line
    this_id = root->id;

    res = find_id_in_line(this_id, &id_line);
    if(res == -1 || res == 1){return 3;}
    bro_id = id_line->bro_id;
    child_id = id_line->child_id;
    if(bro_id == -1){
        root->brother=NULL;
    } else{
        res = find_id_in_line(bro_id, &id_line);
        if(res == -1 || res == 1){return 3;}
        root->brother=id_line->node;
        res = load_tree(root->brother,id_line);
        if(res > 0 ){
            return 4;
        }

    }
    if (child_id==-1){
        root->child=NULL;
    } else{
        res = find_id_in_line(child_id, &id_line);
        if(res == -1 || res == 1){return 3;}
        root->child=id_line->node;
        res = load_tree(root->child,id_line);
        if(res > 0 ){
            return 4;
        }
    }
    return 0;
}

//2, 3, 4 - ptr error
//1 - fopen error
//6 - load ids in line error
//5 - fclose error
//7 - load_strings_to_trees_in_node error
//8, 9 - find_id_in_line error
//10 - load_tree error
int load_tree_from_file(Tree** root, char* file_ids, char* file_strings){
    int res;
    FILE* file;

    if(root == NULL){
        return 2;
    }
    if(file_ids == NULL){
        return 3;
    }
    if (file_strings == NULL){
        return 4;
    }

    file = fopen(file_ids,"r+b");
    if(file == NULL){
        return 1;
    }
    Id_line* id_line;

    //convert file info to linear struct
    res = load_ids_to_line(&id_line,file);
    if(res != 0 ){
        return 6;
    }
    res = fclose(file);
    if(res!=0){
        return 5;
    }

    //put strings in tree in line node
    file = fopen(file_strings,"r+");
    if(file==NULL){
        return 1;
    }
    res = load_strings_to_trees_in_node(id_line,file);
    if (res != 0){
        return 7;
    }
    res = fclose(file);
    if(res !=0 ){
        return 1;
    }

    //line struct to tree struct
    long root_id = 0;

    res = find_id_in_line(root_id,&id_line);
    if (res == 1){return 8;}
    if (res == -1){return 9;}

    Tree* root_tree = id_line->node;
    res = load_tree(root_tree,id_line);
    if(res !=0){return 10;}
    *root = root_tree;
    return 0;

}

//1 - ok
//0 - bad
int is_char_ok(char ch, char* allowed_chars){
    unsigned long len = strlen(allowed_chars);
    for(unsigned long i=0;i<len;i++){
        if(ch == allowed_chars[i]){
            return 1;
        }
    }
    return 0;
}

int add_word_to_tree(const char *word, int len,char* file_name,Tree** root){

//    for(int i =0;i<len;i++){
//        printf("%c",word[i]);
//    }printf("X\n");



    Tree* tree = *root;
    for (int i = 0; i < len; i++) {
        while (tree->littera!=word[i]){
            if(tree->brother!=NULL){
                tree=tree->brother;
            } else{
                tree->brother=(Tree*)malloc(sizeof(Tree));
                tree=tree->brother;
                tree->littera=word[i];
                tree->brother=NULL;
                tree->child=NULL;
                tree->first_node=NULL;
            }
        }
        if(i<len-1){
            if (tree->child==NULL){
                tree->child=(Tree*)malloc(sizeof(Tree));
                tree=tree->child;
                tree->child=NULL;
                tree->brother=NULL;
                tree->first_node=NULL;
                tree->littera=word[i+1];
            } else{
                tree=tree->child;
            }
        }
    }
    if (tree->first_node==NULL){
        tree->first_node=(FNNode*)malloc(sizeof(FNNode));
        tree->first_node->next=NULL;
        tree->first_node->filename=(char*)malloc(sizeof(char)*(strlen(file_name)+1));
        strcpy(tree->first_node->filename,file_name);
        tree->first_node->filename[strlen(file_name)]='\0';
    } else{
        FNNode* fnode_cur = tree->first_node;
        FNNode* fnode_next = tree->first_node->next;
        while (fnode_cur!=NULL){
            if(strcmp(file_name,fnode_cur->filename)==0){
                return 0;
            } else{
                if(fnode_next!=NULL){
                    fnode_cur=fnode_next;
                    fnode_next=fnode_cur->next;
                } else{
                    fnode_cur->next=(FNNode*)malloc(sizeof(FNNode));
                    fnode_cur=fnode_cur->next;
                    fnode_cur->next=NULL;
                    fnode_cur->filename=(char*)malloc(sizeof(char)*(strlen(file_name)+1));
                    strcpy(fnode_cur->filename,file_name);
                    fnode_cur->filename[strlen(file_name)]='\0';
                }
            }
        }
    }
    return 0;
}


int add_id_to_tree(Tree* root){
    static long id =0;
    root->id=id;
    id++;
    if(root->brother!=NULL){
        add_id_to_tree(root->brother);
    }
    if(root->child!=NULL){
        add_id_to_tree(root->child);
    }
    return 0;
}

//1 - ptr error
//2 - file is empty
int make_tree_from_file_with_text(Tree** root,char* name_file_with_text, char* allowed_chars){
    if(root == NULL || name_file_with_text == NULL){return 1;}
    FILE *file = fopen(name_file_with_text,"r+");
    fseek(file,0,SEEK_SET);
    char ch = 'A';
    int counter=0;
    char word[100];
    while (ch!=EOF){

        ch = (char)getc(file);
        if(is_char_ok(ch, allowed_chars)==1){
            word[counter]=ch;
            counter++;
        } else{
            if(counter==0){continue;}
            add_word_to_tree(word,counter,name_file_with_text,root);


            counter = 0;
        }
    }
    fclose(file);

    return 0;
}


//
//1 - no word detected
//2, 3, 4 - ptr error
int find_word(Tree* root, char* word, FNNode** node_ptr){
    if(root == NULL){
        return 2;
    }
    if(word == NULL){
        return 3;
    }
    if(node_ptr == NULL){
        return 4;
    }

    Tree *current = root;
    Tree *child = root;

    unsigned long len = strlen(word);

    for(unsigned long i=0;i<len;i++){

        current=child;


            while (current!=NULL && current->littera!=word[i]){
                current=current->brother;
            }

        if(current==NULL){
            return 1;
        }

        child=current->child;

    }

    if(current->first_node!=NULL){
        if(current->first_node->filename!=NULL){

            *node_ptr=current->first_node;

        }
    } else{
        return 1;
    }
    return 0;
}

int free_node(FNNode* node){
    if(node == NULL){
        return 1;
    }
    if(node->next!=NULL){
        free_node(node->next);
    }
    free(node->filename);
    free(node);
    return 0;

}

//1 - ptr error
int free_tree(Tree* root){
    if(root==NULL){
        return 1;
    }

    if(root->child!=NULL){
        free_tree(root->child);
    }
    if(root->brother!=NULL){
        free_tree(root->brother);
    }
    if(root->first_node!=NULL){
        free_node(root->first_node);
    }
    free(root);
    return 0;

}

int main(){
    char folder[] = "/home/tgpsun/repo/cource_2/c_style_treeTextTags/text_tests/\0";
    printf("Testing\n");
    printf("Test folder is: %s\n",folder);
    DIR *d;
    int res;
    Tree *root =(Tree*)malloc(sizeof(Tree));
    root->littera='A';
    root->child=NULL;
    root->brother=NULL;
    root->first_node=NULL;

    //looking for files in dir
    char allowed_chars[]="qwertyuiopasdfghjklzxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM1234567890-'\0";

    struct dirent *dir;
    d = opendir(folder);
    if(d){
        while ((dir = readdir(d)) != NULL){
//            printf("%s\n", dir->d_name);
            if(strcmp(dir->d_name,".")==0 || strcmp(dir->d_name,"..")==0){continue;}
            char* full_file_name = (char*)malloc(sizeof(folder)+sizeof(dir->d_name)+1);
            sprintf(full_file_name,"%s%s\0",folder,dir->d_name);

            //add words to tree
            res = make_tree_from_file_with_text(&root,full_file_name, allowed_chars);
            printf("\n%d\n",res);
        }
        closedir(d);
    }

    //add id's to tree
    add_id_to_tree(root);

    //filenames for saving
    char file_with_id_name[]="ids\0";
    char file_with_string_name[]="names\0";
    char *full_file_with_id_name=(char *)malloc(sizeof(folder)+sizeof(file_with_id_name)+1);
    sprintf(full_file_with_id_name,"%s%s\0",folder,file_with_id_name);
    char *full_file_with_string_name=(char*)malloc(sizeof(folder)+sizeof(file_with_string_name)+1);
    sprintf(full_file_with_string_name,"%s%s\0",folder,file_with_string_name);

    //save tree
    res = save_tree_to_file_first_time(root,full_file_with_id_name,full_file_with_string_name);
    printf("\n%d\n",res);
    print_tree(root);

    //check free
    res=free_tree(root);
    if(res!=0){
        return 7;
    }

    //check load
    printf("\nload tree from files\n");
    Tree *load_root = NULL;
    res = load_tree_from_file(&load_root,full_file_with_id_name,full_file_with_string_name);
    printf("\n%d\n",res);
    printf("\nloaded tree:\n");
    print_tree(load_root);

    //remove saves
    res = remove(full_file_with_id_name);
    if(res<0){return 111;}
    res = remove(full_file_with_string_name);
    if(res<0){return 112;}

    //check find
    char enter[1000];
    printf("Enter word:\n");
    scanf("%s",enter);
    unsigned long rr = strlen(enter);
    if (rr>999){
        return 21;
    }
    printf("\nYou are looking for:\n%s\n",enter);
    FNNode* search_result = NULL;
    int s_res = find_word(load_root,enter,&search_result);
    if(s_res == 1){
        printf("\nThere is no word like this here\n");
    }
    if(s_res == 0){
        FNNode* node_ptr = search_result;
        printf("Search results:\n");
        while (node_ptr != NULL){
            printf("%s\n",node_ptr->filename);
            node_ptr=node_ptr->next;
        }
    }




    return 0;
}
