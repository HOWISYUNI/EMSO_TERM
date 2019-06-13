#include "controllers.h"

int save_data(char type, char *data){
	FILE *fp = NULL;
	int size;

	printf("Here!!!!\n");
	printf("Here!!!!\n");
	switch(type){

		case 'l':
			fp = fopen("light.txt", "a+");
			if(fp < 0){
				printf("File open Fail!!\n");
				return -1;
			}
			fseek(fp, 0L, SEEK_END);
			size = ftell(fp);

			if (size == 0)
				fprintf(fp, "%s", data);
			else
				fprintf(fp, "\n%s", data);
			//fwrite(data1, 1, sizeof(data1), fp);
			//fputs(data1, fp);

			fclose(fp);

			return 0;
	
		case 's':
			fp = fopen("soil.txt", "a+");
			if(fp < 0){
				printf("File open Fail!!\n");
				return -1;
			}
			fseek(fp, 0L, SEEK_END);
			size = ftell(fp);

			if (size == 0)
				fprintf(fp, "%s", data);
			else
				fprintf(fp, "\n%s", data);
			//fwrite(data1, 1, sizeof(data1), fp);
			//fputs(data1, fp);

			fclose(fp);

			return 0;

		case 'a':
			fp = fopen("alert_log.txt", "a+");
			if(fp < 0){
				printf("File open Fail!!\n");
				return -1;
			}
			fseek(fp, 0L, SEEK_END);
			size = ftell(fp);

			if (size == 0)
				fprintf(fp, "%s", data);
			else
				fprintf(fp, "\n%s", data);
			//fwrite(data1, 1, sizeof(data1), fp);
			//fputs(data1, fp);

			fclose(fp);

			return 0;

			/*
		case DIST:
			FILE *fp = fopen("ulsn.txt", "w");
			fputs(data, fp);
			fclose(fp);

			return 0;
			*/

		default:
			return -1;
	}
}

//void refine_data(char type, char cmd){
char* refine_data(char type, char cmd){
	//char *buffer = malloc(sizeof(char) * 20);
	//char *dArr[10] = { NULL, };
	FILE *fp = NULL;
	int temp = 0;
	int lines = 0;
	char s[10] = {0, }; /* temporary for reading text file */
	static char s1[10];

	printf("Hello!?\n");
	if(type == 'l'){
		fp = fopen("light.txt", "r");

		if(cmd == 'v'){

			/* Count num of Lines */
			fseek(fp, 0L, SEEK_SET);
			while(!feof(fp)){
				fgets(s, 9, fp);	//4 = sizeof s[5] - 1
				lines++;
			}
			printf("Lines : %d\n", lines);

			/* Extract Data  */
			fseek(fp, 0L, SEEK_SET);
			while(!feof(fp)){
				fgets(s, 9, fp);
				lines--;
				if(lines < 10) {
					printf("s : %s\n", s);
					temp += atoi(s);
				}
			}
			sprintf(s1, "%d", temp);
			//itoa(temp, buf, 10);
			printf("abc : %s\n", s1);

			return s1;
		}

		else if(cmd == 'a'){

		}
		else if(cmd == 's'){
			
		}
	}
	else if(type == 's'){
		fp = fopen("soil.txt", "r");

		if(cmd == 'v'){

		}
		else if(cmd == 'a'){

		}
		else if(cmd == 's'){

		}
	}
	else if(type == 'a'){
		fp = fopen("alert_log.txt", "r");

	}
	else{
		
	}
}
