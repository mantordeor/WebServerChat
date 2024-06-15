#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
struct Book{
    char name[101], author[101], pub_year[101], num[101], ISBN[101], dup_ISBN[101];
}Library[101];

struct User{
    char account[101], password[101];
    struct Book Cabin[101];
	char date[101];
    int idx;
}Users[101];

int add_book(int idx){
	for(int i = 0 ; i < idx ; i++){
		if(Library[i].name == '\0'){
    		scanf("%s%s%s%s%s%s",Library[i].name,Library[i].author,Library[i].pub_year,Library[i].num,Library[i].ISBN,Library[i].dup_ISBN);
			return 0;
		}
	}
	scanf("%s%s%s%s%s%s",Library[idx].name,Library[idx].author,Library[idx].pub_year,Library[idx].num,Library[idx].ISBN,Library[idx].dup_ISBN);
	return 1;
}

void move_book(int idx){
	char ISBN[101], dup_ISBN[101];
	scanf("%s%s",ISBN,dup_ISBN);
	printf("Wanna move this book? Y ? N ? \n");
	char choice;
	cs:
	scanf("%c",&choice);
	if(choice == 'Y'){
		for(int i = 0 ; i < idx ; i++){
			if(Library[i].name == '\0') continue;
			if(Library[i].ISBN == ISBN && Library[i].dup_ISBN == dup_ISBN){
				memset(Library[i].name, 0 ,sizeof Library[i].name);
				memset(Library[i].author, 0 ,sizeof Library[i].author);
				memset(Library[i].pub_year, 0 ,sizeof Library[i].pub_year);
				memset(Library[i].num, 0 ,sizeof Library[i].num);
				memset(Library[i].ISBN, 0 ,sizeof Library[i].ISBN);
				memset(Library[i].dup_ISBN, 0 ,sizeof Library[i].dup_ISBN);
				break;
			}
		}
	}else if(choice == 'N'){
		return;
	}else{
		goto cs;
	}
}

void brrows_book(char account[101], char password[101]){
	printf("Input your wanna brrow bookName.\n");
	char book_name[101];
	scanf("%s",book_name);
	printf("Input your wanna brrow bookName.\n");
	time_t timer;
	struct tm *Now;
	time(&timer);
	Now = localtime(&timer);
	printf("date : \n %s",asctime(Now));
	int flag = 0;
	int i = 0;
	for(; i < sizeof Users ; i++){
		if(strcmp(account,Users[i].account) && strcmp(password,Users[i].password)){
			flag = 1;
			
		}
	}
	if(!flag){

	}
}

int main(){
	int is_active = 0;
    while(1){
		printf("A D Q I P E?\n");
		char choice;
		scanf("%c",&choice);
		system("cls");
		int idx = 0;
		switch(choice){
            char str[101];
			case 'B':
				if(!is_active){
					printf("Account :\n");
					scanf("%s",str);
					printf("Password :\n");
					is_active = 1;
				}else{
					scanf("%s",str);
					printf("Log out.\n");
					if(str == "Logout"){
						is_active = 0;
						continue;
					}
				}
				break;
			case 'R':
                printf("Input Book Name or Book Number\n");
                scanf("%s",str);
                printf("Input Book dup_Num\n");
                scanf("%s",str);
				printf("Log out.\n");
				break;
			case 'A':
				idx += add_book(idx);
				break;
			case 'D':
				move_book(idx);
				break;
			case 'Q':
				//search_book();
				break;
			case 'I':
				//search_user();
				break;
			case 'P':
				//print_book();
				break;
			case 'E':
				return 0;
            default:
                break;
        }
	}
}
