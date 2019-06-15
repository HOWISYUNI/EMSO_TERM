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

	if(size == 0)
		fprintf(fp, "%s", data);	
	else
		fprintf(fp, "\n%s", data);
	
	fclose(fp);

	return 0;	
}

char* refine_data(char type, char cmd, char* data){
	FILE *fp = NULL;
	int temp = 0;
	int lines = 0;
	int rcv_data, i;
	char read_one_line[DATA_LEN] = {0, }; /* temporary for reading text file */
	static char return_data[DATA_LEN];

	rcv_data = atoi(data);

	if(type == 'l')
		fp = fopen("light.txt", "a+");
	else if(type == 's')
		fp = fopen("soil.txt", "a+");
	else if(type == 'a')
		fp = fopen("alert_log.txt", "a+");
	else{
		return_data[0] = '\0';
		return_data[0] = 'f';
		return_data[1] = 'a';
		return_data[2] = 'i';
		return_data[3] = 'l';
		return_data[4] = '0';
		return_data[5] = '\0';
		return_data[6] = '\0';
		printf("return_data(fail0) : %s\n", return_data);

		return return_data;
	}

	/* Count num of Lines */
	fseek(fp, 0L, SEEK_SET);
	while(!feof(fp)){
		fgets(read_one_line, (DATA_LEN - 1), fp);
		lines++;
	}

	printf("Lines : %d\n", lines);
	if(rcv_data > lines){
		return_data[0] = '\0';
		return_data[0] = 'f';
		return_data[1] = 'a';
		return_data[2] = 'i';
		return_data[3] = 'l';
		return_data[4] = '1';
		return_data[5] = '\0';
		return_data[6] = '\0';
		printf("return_Data(fail1) : %s\n", return_data);

		return return_data;
	}

	if(cmd == 'a'){	
		return_data[0] = '\0';
		/* Extract Data */
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
	}
	else if(cmd == 'v'){
		return_data[0] = '\0';
		/* Extract Data */
		fseek(fp, 0L, SEEK_SET);
		while(!feof(fp)){
			fgets(read_one_line, (DATA_LEN - 1), fp);
			lines--;
			if(lines >= 0 && lines < rcv_data) {
				strncat(return_data, read_one_line, strlen(read_one_line));
			}
		}
		printf("return_data : %s\n", return_data);
	}
	else{
		return_data[0] = '\0';
		return_data[0] = 'f';
		return_data[1] = 'a';
		return_data[2] = 'i';
		return_data[3] = 'l';
		return_data[4] = '2';
		return_data[5] = '\0';
		return_data[6] = '\0';
		printf("Failed because cmd is not 'a' or 'v'(fail2) : %s\n",return_data);
	}

	return return_data;
}
