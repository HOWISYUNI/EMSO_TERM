#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	MYSQL mysql;
	MYSQL_RES *myresult;
	MYSQL_ROW row;

	unsigned int num_fields;
	unsigned int num_rows;
	char* string_query;

	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, "localhost", "root", "abcd", "ku_sf", 0, NULL, 0))
		printf("Success!\n");
	else{
		printf("Fail!\n");
		exit(1);
	}	

	string_query = "select * from data";
	mysql_query(&mysql, string_query);
	myresult = mysql_store_result(&mysql);
	while(row = mysql_fetch_row(myresult))
		printf("%s\t %s\n", row[0], row[1]);
	mysql_free_result(myresult);
	mysql_close(&mysql);

	return 0;
}
