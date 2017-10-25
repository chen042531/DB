#include <iostream>
#include <time.h>
#include "db.h"
#include <stdio.h>
using namespace std;

int main(int argc, char* argv[]){
	//declear db object
	db mydb;

	//init db
	mydb.init();

	//set temp directory
	mydb.setTempFileDir("temp");

	//Import data
	mydb.import("data/2006.csv");
	mydb.import("data/2007.csv");
	mydb.import("data/2008.csv");


	//Create index on one or two columns.
	clock_t tIndex = clock();
	//mydb.createIndex();

	//Do queries
	//These queries are required in your report.
	//We will do different queries in the contest.
	//Start timing
	clock_t tQuery = clock();
	printf("%.2f\n", mydb.query("IAH", "JFK"));
	printf("%.2f\n", mydb.query("IAH", "LAX"));
	printf("%.2f\n", mydb.query("JFK", "LAX"));
	printf("%.2f\n", mydb.query("JFK", "IAH"));
	printf("%.2f\n", mydb.query("LAX", "IAH"));

	//End timing
	clock_t tEnd = clock();
	printf("Time taken for creating index: %.2fs\n", (double)(tEnd - tIndex) / CLOCKS_PER_SEC);
	printf("Time taken for making queries: %.2fs\n", (double)(tEnd - tQuery) / CLOCKS_PER_SEC);

	//Cleanup db object
	mydb.cleanup();
}
