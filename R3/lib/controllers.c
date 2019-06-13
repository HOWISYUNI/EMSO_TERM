#include "controllers.h"

int save_data(char type, char *data){
	FILE *fp;
	int size;

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

char* refine_data(char type, char cmd){
	//char *buffer = malloc(sizeof(char) * 20);
	//char *dArr[10] = { NULL, };
	FILE *fp;
	int temp = 0;
	int lines = 0;
	char s[81];
	static char s1[10];

	if(type == 'l'){
		fp = fopen("light.txt", "r");

		if(cmd == 'v'){

			/* Count num of Lines */
			fseek(fp, 0L, SEEK_SET);
			while(!feof(fp)){
				fgets(s, 80, fp);
				lines++;
			}
			printf("Lines : %d\n", lines);

			/* Extract Data  */
			fseek(fp, 0L, SEEK_SET);
			while(!feof(fp)){
				fgets(s, 80, fp);
				lines--;
				if(lines < 10) {
					printf("s : %s\n", s);
					temp += atoi(s);
				}
			}
			sprintf(s1, "%d", temp);
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
