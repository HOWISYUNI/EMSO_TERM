#include "controllers.h"

int save_data(char type, char *data){

	char *enter = "\n";
	strcat(data, enter);

	switch(type){

		case l:
			FILE *fp = fopen("light.txt", "a");
			fputs(data, fp);
			fclose(fp);

			return 0;
			
		case s:
			FILE *fp = fopen("soil.txt", "a");
			fputs(data, fp);
			fclose(fp);

			return 0;

		case a:
			FILE *fp = fopen("alert_log.txt", "a");
			fputs(data, fp);
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
	char *buffer = malloc(sizeof(char) * 20);
	//char *dArr[10] = { NULL, };
	FILE *fp;

	if(type == 'l'){
		fp = fopen("light.txt", "r");

		if(cmd == 'v'){
			fgets(buffer, sizeof(buffer), fp);
			
			return buffer;
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
