// File:     country.cpp
// Author:   Oisin Hodgins 17480216 oisinhodgins1@nuigalway.ie
// Date:     May/2020
// What:     Program which defines functions for country class
// See also: country.h & main.cpp
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <cstdio>
#include "country.h"

using namespace std;

country::country(){
    vector<int> deaths; //Initialise vector
    vector<string> dates; //Initialise vector
}

void country::setdd(string date, int death){
    dates.push_back(date); //Append new value to end of vector
    deaths.push_back(death); //Append new value to end of vector
    tot_death += death; //Increase running total
}

void country::print(void){
    for(int i=0; i < deaths.size(); i++){
        cout << deaths[i] << " " << dates[i] << endl; //Output the vectors deaths & dates
    }
}

void country::plot(string country_name){
    //fprintf requires const arrays as apposed to c++ strings
    //This allowed much easier syntax for the pipe, as variables
    //can be inserted easily into the function
    const char *name  = country_name.c_str(); //Name of country in question
    const char *max_date = dates[0].c_str(); //Most recent available date
    const char *min_date = dates[dates.size()-1].c_str(); //Oldest date with recorded data
    const char *timefmt = "%d/%m/%Y"; //Directly typing %d into fprintf caused the compiler to assign a ?random? int
    //value to it, passing it through %s as a char array works just fine

    ofstream myPlotFile("Output.txt"); //Create a file for gnuplot to read
    for(int i=(deaths.size()-1) ; i>=0 ;i--){ //Counting down as the deaths and dates vectors are backwards
        myPlotFile << "\"" << dates[i] << "\"" << "," << deaths[i] << "\n"; //Populate file with vectors deaths and dates
    }
    myPlotFile.close();

    FILE *gnuplotPipe = popen("gnuplot -persist", "w");  // Open a pipe to gnuplot
    if (gnuplotPipe){ //Only proceed if open
        fprintf(gnuplotPipe, "set title \"%s: COVID-19 Deaths recorded per day\n", name); //Customisation in gnuplot
        fprintf(gnuplotPipe, "set xdata time \n"); //Specify that X-axis is time
        fprintf(gnuplotPipe, "set style data lines \n"); //Customisation in gnuplot
        fprintf(gnuplotPipe, "set term png \n"); //Customisation in gnuplot
        fprintf(gnuplotPipe, "set timefmt \"%s\" \n ", timefmt); //Specify day-month-year
        fprintf(gnuplotPipe, "set format x \"%s\" \n", timefmt); //Specify day-month-year
        fprintf(gnuplotPipe, "set datafile sep\",\"\n"); //Specify that input data is seperated by comma
        fprintf(gnuplotPipe, "set xlabel \"Date\" \n" ); //Customisation in gnuplot
        fprintf(gnuplotPipe, "set ylabel \"Number of deaths attributed to COVID-19 per day\" \n"); //Customisation in gnuplot
        fprintf(gnuplotPipe, "set xtics rotate by 90 right \n"); //Customisation in gnuplot
        fprintf(gnuplotPipe, "set autoscale \n"); //Customisation in gnuplot
        fprintf(gnuplotPipe, "set xrange [\"%s\":\"%s\"] \n",min_date,max_date); //Customisation in gnuplot
        fprintf(gnuplotPipe, "set output \"COVID-19 Country Analysis\" \n "); //Set output file path/name
        fprintf(gnuplotPipe, "plot \"/Users/margarethodgins/Output.txt\" using 1:2 lt rgb 'red' \n"); //Create plot
        cout << "File now available at: \"COVID-19 Country Analysis\"" << endl;
        cout << "Data used available at: \"Output.txt\"" << endl;
    }
}
