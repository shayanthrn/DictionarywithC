#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void showmenu(){
	printf("Please Choose one of the items below:\n");
	printf("1) Add a word\n\n");
	printf("2) Remove a word\n\n");
	printf("3) Take a test\n\n");
	printf("4) Exit\n\n");
}
void addword(FILE *fp){
	printf("\n Enter a word:\n");
	char word[20];
	scanf("%s",word);
	printf("\nEnter its synonym:\n");
	char synonym[20];
	scanf("%s",synonym);
	fseek(fp,0,SEEK_END);
	if(ftell(fp)==0){
		fprintf(fp,"%s %s",word,synonym);
	}
	else{
	fprintf(fp,"\n%s %s",word,synonym);
	}
}

FILE * removeword(FILE *fp){
	char word[20],dummy[20];
	printf("\n Enter a word:\n");
	char answer[20];
	scanf("%s",answer);
	fseek(fp,0,SEEK_SET);
	int counter=0,counter2=0;
	int linescount=0;
	int flag=0;
	int i;
	char temp[100];
	while(feof(fp)==0){
		fgets(temp,100,fp);
		linescount++;
	}
	fseek(fp,0,SEEK_SET);
	while(feof(fp)==0){
		fscanf(fp,"%s %s",word,dummy);
		counter++;
		if(strcmp(word,answer)==0){
			flag=2;
			break;
		}
	}
	if(flag!=2){
		printf("Not found!\n");
	}
	else{
		FILE * tmp=fopen("temp.txt","w");
		fseek(fp,0,SEEK_SET);
		if(counter==linescount){
			for(i=0;i<linescount-1;i++){
				fgets(temp,100,fp);
				if(i==linescount-2){
					temp[strlen(temp)-1]='\0';
				}
				fputs(temp,tmp);
			}
		}
		else{
			while(fgetc(fp)!=EOF){
				fseek(fp,-1,SEEK_CUR);
				if(feof(fp)==0){
				counter2++;
				fgets(temp,100,fp);
			}
				if(counter2==counter){
					continue;
				}
				fputs(temp,tmp);		
			}
		}
		fclose(tmp);
		fclose(fp);
		remove("dictionary.txt");  		// remove the original file 
        rename("temp.txt", "dictionary.txt"); 	// rename the temporary file to original name
	}
	FILE *fp2=fopen("dictionary.txt","a+");
	return fp2;
}
void taketest(FILE *fp){
	printf("\nEnter the number of words that you want to test:\n");
	int n;
	int i;
	int j;
	int linescount=0;
	char temp[100];
	char word[20];
	char answer[20];
	char synonym[20];
	scanf("%d",&n);
	fseek(fp,0,SEEK_SET);
	while(feof(fp)==0){
		fgets(temp,100,fp);
		linescount++;
	}
	int questionlines[n];
	fseek(fp,0,SEEK_SET);
	srand(time(0));
	for(i=0;i<n;i++){
		questionlines[i]=(rand()%linescount);
	}
	for(i=0;i<n;i++){
		for(j=0;j<questionlines[i];j++){
			fgets(temp,100,fp);
		}
		fscanf(fp,"%s %s",word,synonym);
		printf("\nthe Word is:%s\n",word);
		printf("enter synonym:\n");
		scanf("%s",answer);
		if(strcmp(answer,synonym)==0){
			printf("Correct!");
		}
		else{
			printf("Wrong!");
		}
	}
}

int main(int argc, char *argv[]) {
	FILE* fp=fopen("dictionary.txt","a+");  //bayad address desktop ro qabl az dictionary.txt bedim
	int answer;
	char s[20];
	int exitflag=0;
//	sleep(2);
	printf("Hi! Glad to See U!\n");
//	sleep(2);
	while(1){                            //while ke ravande koli barnamas
		showmenu();                      //function neshan dadan menu
		scanf("%d",&answer);
		switch(answer){                  //barresi javab va anjam eqdamat lazem
			case 1:
				addword(fp);break;
			case 2:
				fp=removeword(fp);break;
			case 3:
				taketest(fp);break;
			case 4:
				exitflag=1;break;         //kharej shodan az barname
			default:
				printf("you enter a wrong number,enter another:\n");
		}
		if(exitflag==1){
			break;
		}
	}
	fclose(fp);
//	sleep(1);
	printf("See u Later;)");
//	sleep(1);
	return 0;
}
