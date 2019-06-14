#include "controllers.h"

int save_data(char type, char *data){
	FILE *fp = NULL;
	int size;

	if(type == 'l')
		fp = fopen("light.txt", "a+");
	else if(type == 's')
		fp = fopen("soil.txt", "a+");
	else if(type == 'a')
		fp = fopen("alert_log.txt", "a+");
	else
		return -1;
	
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
	fclose(fp);

	return 0;	
}

//void refine_data(char type, char cmd){
char* refine_data(char type, char cmd, char* data){
	//char *buffer = malloc(sizeof(char) * 20);
	//char *dArr[10] = { NULL, };
	FILE *fp = NULL;
	int temp = 0;
	int lines = 0;
	int rcv_data;
	char read_one_line[DATA_LEN] = {0, }; /* temporary for reading text file */
	static char return_data[10];

	printf("Hello!?\n");

	rcv_data = atoi(data);
	if(type == 'l'){
		fp = fopen("light.txt", "r");

		if(cmd == 'a'){

			/* Count num of Lines */
			fseek(fp, 0L, SEEK_SET);
			while(!feof(fp)){
				fgets(read_one_line, (DATA_LEN - 1), fp);
				lines++;
			}

			lines--;
			printf("Lines : %d\n", lines);

			/* Extract Data  */
			fseek(fp, 0L, SEEK_SET);
			while(!feof(fp)){
				fgets(read_one_line, (DATA_LEN - 1), fp);
				lines--;
				if(lines >= 0 && lines < rcv_data) {
					printf("DATA : %s\n", read_one_line);
					temp += atoi(read_one_line);
				}
			}
			temp = temp / rcv_data;
			sprintf(return_data, "%d", temp);	//itoa
			printf("return_data : %s\n", return_data);

			return return_data;
		}

		else if(cmd == 'v'){

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
