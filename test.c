#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Book{
    char *Name, *author, *ISBN, *user;
    int year, pub_num, dup_num;
}Lib[101];

struct Student{
    int account, password;
    int date[101];
}Students[101];

char* getname(FILE *file){
    char* str = (char*)malloc(101 * sizeof(char));
    int idx = 0;
    char tmp;
    fgetc(file);
    fgetc(file);
    while(fscanf(file,"%c",&tmp) != EOF){
        if(idx){
            if(tmp == '&'){
                fscanf(file,"%c",&tmp);
                if(tmp == '\\'){
                    break;
                }else{
                    str[idx++] = '&';
                    str[idx++] = ' ';
                    continue;
                }
            }
        }
        str[idx++] = tmp;
    }
    str[idx] = '\0';
    return str;
}

char* getisbn(FILE *file){
    char* str = (char*)malloc(101 * sizeof(char));
    char tmp;
    int idx = 0;
    while(fscanf(file,"%c",&tmp) != EOF){
        if(tmp == ' ') break;
        str[idx++] = tmp;
    }
    str[idx] = '\0';
    return str;
}


void fbook(int idx, FILE *file_book){
    Lib[idx].Name = getname(file_book);
    fgetc(file_book);
    Lib[idx].author = getname(file_book);
    fscanf(file_book,"%d %d",&Lib[idx].year,&Lib[idx].pub_num);
    fgetc(file_book);
    Lib[idx].ISBN = getisbn(file_book);
    fscanf(file_book,"%d",&Lib[idx].dup_num);
    char c;
    if(fscanf(file_book,"%c",&c) != EOF && c != '\n'){
        int cnt = 0;
        char* str = (char*)malloc(101 * sizeof(char));
        char tmp;
        while(fscanf(file_book,"%c",&tmp) != EOF){
            if(tmp == '\n') break;
            str[cnt++] = tmp;
        }
        str[cnt] = '\0';
        Lib[idx].user = str;
    }
    //printf("%s %s %d %d %s %d %s\n",Lib[idx].Name,Lib[idx].author,Lib[idx].year,Lib[idx].pub_num,Lib[idx].ISBN,Lib[idx].dup_num, Lib[idx].user);
    //printf("--------------------------------------------------\n");   
}

int addbook(int Bcnt){
    char *Name = (char*)malloc(101*sizeof(char)), *author = (char*)malloc(101*sizeof(char)), *ISBN = (char*)malloc(101*sizeof(char));
    int year, pub_num, dup_num;
    char tmp;
    int idx = 0;
    while (scanf("%c", &tmp) != EOF && (tmp == ' ' || tmp == '\n'));
    while(scanf("%c",&tmp)!=EOF){
        if(tmp == '"') break;
        Name[idx++] = tmp;
    }
    Name[idx] = '\0';
    while (scanf("%c", &tmp) != EOF && (tmp == ' ' || tmp == '\n'));
    idx = 0;
    while(scanf("%c",&tmp)!=EOF){
        if(tmp == '"') break;
        author[idx++] = tmp;
    }
    author[idx] = '\0';
    scanf("%d %d %100s %d",&year,&pub_num,ISBN,&dup_num);
    int tag = -1;
    for(int i = 1 ; i <= Bcnt ; i++){
        if(Lib[i].Name == NULL){
            tag = i;
            continue;
        }
        if(!strcmp(Lib[i].ISBN,ISBN) && Lib[i].dup_num == dup_num){
            printf("The duplicate exisit.\n");
            return Bcnt;
        }
    }
    if(tag != -1){
        Lib[tag].Name = Name;
        Lib[tag].author = author;
        Lib[tag].dup_num = dup_num;
        Lib[tag].ISBN = ISBN;
        Lib[tag].pub_num = pub_num;
        Lib[tag].year = year;
        printf("OK\n");
    }else{
        Lib[++Bcnt].Name = Name;
        Lib[Bcnt].author = author;
        Lib[Bcnt].dup_num = dup_num;
        Lib[Bcnt].ISBN = ISBN;
        Lib[Bcnt].pub_num = pub_num;
        Lib[Bcnt].year = year;
        printf("OK\n");
    }
    return Bcnt;
}

int fStudent(int idx,int Bcnt,FILE *file_stu){
    int tmpa, tmpp;
    while(fscanf(file_stu,"%d %d",&tmpa, &tmpp)!=EOF){
        Students[idx].account = tmpa;
        Students[idx].password = tmpp;
        char tmp;
        while(fscanf(file_stu,"%c",&tmp) != EOF){
            if(tmp == '\n') break;
            char *isbn, date;
            isbn = getisbn(file_stu);
            fscanf(file_stu,"%d",&date);
            int flag = 0;
            for(int i = 1 ; i <= Bcnt ; i++){
                if(Lib[i].ISBN == isbn){
                    char* tmps = (char*)malloc(101 * sizeof(char));
                    snprintf(tmps, 101, "%d", tmpa);
                    Lib[i].user = tmps;
                    Students[idx].date[Bcnt] = date;
                }
            }
        }
        idx++;
    }
    return idx;
}

void serchStudent(int Scnt,int Bcnt){
    int account, password;
    scanf("%d",&account);
    scanf("%d",&password);
    int flag = 0;
    for(int j = 0 ; j < Bcnt ; j++){
        if(atoi(Lib[j].user) == account){
            printf("%s %s %d %d %s %d\n",Lib[j].Name,Lib[j].author,Lib[j].year,Lib[j].pub_num,Lib[j].ISBN,Lib[j].dup_num);
            flag = 1;
        }
    }
    if(!flag) printf("No borrowed books\n");
}

void serchBook(int idx){
    char *ISBN = (char *)malloc(101 * sizeof(char));
    scanf("%100s",ISBN);
    int flag = 0;
    for(int i = 1 ; i <= idx ; i++){
        if(Lib[i].Name == NULL) continue;
        if(!strcmp(ISBN,Lib[i].ISBN)){
            printf("%s %s %d %d %s %d %s\n",Lib[i].Name,Lib[i].author,Lib[i].year,Lib[i].pub_num,Lib[i].ISBN,Lib[i].dup_num, Lib[i].user);
            flag = 1;
        }
    }
    if(!flag) printf("Not found!\n");
    free(ISBN);
}

void printBook(int idx){
    for(int i = 1 ; i <= idx ; i++){
        printf("--------------------------------------------------\n");
        printf("%s %s %d %d %s %d %s\n",Lib[i].Name,Lib[i].author,Lib[i].year,Lib[i].pub_num,Lib[i].ISBN,Lib[i].dup_num, Lib[i].user);
    }
    system("pause");
}

void brrowbook(int Bcnt, int Scnt){
    int account, password, dup_num;
    char *ISBN = (char *)malloc( 101 * sizeof(char));
    scanf("%d %d %100s %d",&account,&password,ISBN,&dup_num);
    for(int i = 0 ; i < Scnt ; i++){
        if(Students[i].account == account && Students[i].password == password){
            int cnt = 0;
            int tag = 0;
            for(int j = 1 ; j <= Bcnt ; j++){
                if(Lib[j].dup_num == dup_num && !strcmp(Lib[j].ISBN,ISBN)){
                    tag = j;
                }
                if(atoi(Lib[j].user) == account) cnt++;
            }
            if(cnt > 2){
                printf("Brrow Limit 3\n");
                return;
            }else if(tag){
                char* tmps = (char*)malloc(101 * sizeof(char));
                snprintf(tmps, 101, "%d", account);
                Lib[tag].user = tmps;
                printf("OK\n");
            }
        }
    }
}

void cmd(){
    printf("Borrow Book type  <B>\n"
           "Return Book type  <R>\n"
           "Add New Book type <A>\n"
           "Delete book type  <D>\n"
           "Query book type   <Q>\n"
           "Serch user type   <I>\n"
           "Print book type   <P>\n"
           "End system type   <E>\n");
}

void returnBook(int Bcnt,int Scnt){
    int account, password, dup_num;
    char *ISBN = (char *)malloc( 101 * sizeof(char));
    scanf("%d %d %100s %d",&account,&password,ISBN,&dup_num);
    for(int i = 0 ; i < Scnt ; i++){
        if(Students[i].account == account && Students[i].password == password){
            for(int j = 1 ; j <= Bcnt ; j++){
                if(!strcmp(ISBN,Lib[j].ISBN) && Lib[j].dup_num == dup_num){
                    free(Lib[j].user);
                    Lib[j].user = NULL;
                    printf("OK\n");
                    return;
                }
            }
        }
    }
    free(ISBN);
}

void deleteBook(int idx){
    char *ISBN = (char *)malloc(101 * sizeof(char));
    int dup_num;
    scanf("%100s%d",ISBN,&dup_num);
    for(int i = 1 ; i <= idx ; i++){
        if(dup_num == Lib[i].dup_num && !strcmp(ISBN,Lib[i].ISBN)){
            if(Lib[i].user != NULL){
                printf("This book has been borrowed\n");
                return;
            }else{
                printf("%s %s %d %d %s %d %s\n",Lib[i].Name,Lib[i].author,Lib[i].year,Lib[i].pub_num,Lib[i].ISBN,Lib[i].dup_num, Lib[i].user);
                printf("Do you really want to delete book? <Y> / <N> \n");
                getchar();
                char op;
                scanf("%c",&op);
                if(op == 'Y'){
                    free(Lib[i].Name);
                    free(Lib[i].author);
                    free(Lib[i].ISBN);
                    free(Lib[i].user);
                    Lib[i].Name = NULL;
                    Lib[i].author = NULL;
                    Lib[i].ISBN = NULL;
                    Lib[i].user = NULL;
                    Lib[i].year = 0;
                    Lib[i].pub_num = 0;
                    Lib[i].dup_num = 0;
                    printf("OK!\n");
                    return;
                }
            }
        }
    }
    printf("Not found!\n");
    return;
}


int main(){
    int Scnt = 0, Bcnt = 0;
    FILE *file_book = fopen("Books.txt","r");
    while(!feof(file_book)){
        fbook(++Bcnt,file_book);
    }
    fclose(file_book);
    FILE *file_stu = fopen("Students.txt","r");
    Scnt = fStudent(Scnt,Bcnt,file_stu);
    fclose(file_stu);
    cmd();
    while(1){
        char c;
        scanf("%c",&c);
        switch(c){
            case 'B':
                brrowbook(Bcnt,Scnt);
                break;
            case 'A':
                Bcnt = addbook(Bcnt);
                break;
            case 'I':
                serchStudent(Scnt,Bcnt);
                break;
            case 'Q':
                serchBook(Bcnt);
                break;
            case 'P':
                system("cls");
                printBook(Bcnt);
                system("cls");
                cmd();
                break;
            case 'E':
                return 0;
                break;
            case 'R':
                returnBook(Bcnt,Scnt);
                break;
            case 'D':
                deleteBook(Bcnt);
                break;
            default:
                break;
        }
    }
    
    system("pause");
    
}