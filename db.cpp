#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include "db.h"
using namespace std;

void db::init(){
	//Do your db initialization.
}

void db::setTempFileDir(std::string) {}

void db::import(string csvFileName){
	//Inport a csv file to your database.
    cout<<"start import"<<endl;
    FILE *data;
    FILE *tmp;
    int linecnt = 0, commacnt;
    int p_arrdelay = 0, p_origin = 0, p_dest = 0;
    char inputtmp[1024];
    string origin;
    string dst;
    string time;
    string output;
    tmp=fopen("temp/temp.txt","a");
    data=fopen(csvFileName.c_str(), "r");
    if(!data){
        printf("no exist\n");
    }

    while (fscanf(data, " %[^\n]s", inputtmp) != EOF && ++linecnt)
    {
        if (linecnt == 1)  continue;

        // printf("%s\n", inputtmp);

        commacnt = 0;
        p_arrdelay = p_origin = p_dest = 0;

        for (int i = 0; i < 1024; i++)
        {
            if (inputtmp[i] == ',')  commacnt++, inputtmp[i] = '\0';

            if (commacnt == 14)  !p_arrdelay ? p_arrdelay = i + 1 : 0;
            if (commacnt == 16)  !p_origin ? p_origin = i + 1 : 0;
            if (commacnt == 17)  !p_dest ? p_dest = i + 1 : 0;
        }

        if (strcmp(&inputtmp[p_arrdelay], "NA"))
            fprintf(tmp, "%s %s %s\n", &inputtmp[p_origin], &inputtmp[p_dest], &inputtmp[p_arrdelay]);
    }

    fclose(tmp);
    fclose(data);
    cout<<"end import"<<endl;

}



double db::query(string origin, string dest){
    //Do the query and return the average ArrDelay of flights from origin to dest.
	//This method will be called multiple times.
    double ans=0;
    double tmptime;


    int blank=0;
    string ori;
    string dst;
    string time;
    int p_arrdelay = 0, p_origin = 0, p_dest = 0, sum_delay = 0, cnt_delay = 0;
    FILE *data;
    FILE *t;
    char corigin[5], cdest[5];
    int delay;
    data=fopen("temp/temp.txt", "r");
    while (fscanf(data, "%s %s %d", corigin, cdest, &delay) != EOF )
    {
        if (string{corigin} == origin && string{cdest} == dest)
            sum_delay += delay, cnt_delay++;
    }

   // return ans/counter; //Remember to return your result.

   return (double)sum_delay/cnt_delay;
}

void db::cleanup(){
    //Release memory, close files and anything you should do to clean up your db class.
}
