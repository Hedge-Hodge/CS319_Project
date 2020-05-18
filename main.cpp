// File:     main.cpp
// Author:   Oisin Hodgins 17480216 oisinhodgins1@nuigalway.ie
// Date:     May/2020
// What:     Program which:
//          1.) Prompts user for a country name
//          2.) Extracts data related to COVID-19 deaths in said country
//          3.) Produces a file, containing a lineplot of death rate against time
// See also: country.h & country.cpp

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include "country.h"


using namespace std;

void extract_country_from_csv(string filename, country input, string name); //Function to extract certain data from csv file

int main()
{
    string country_name;
    cout << "Please enter a country name, " << endl;
    cin >>  country_name; //Assign input
    cout << "You have entered: " << country_name << endl;
    cout << "Producing graph now..." << endl;
    country input; //Create instance of the country class
    extract_country_from_csv("/Users/margarethodgins/Downloads/COVID-19_17_05_2020",input, country_name);
    //^^This will populate the new instance of country with data from the csv
    //Plotting also occurs in that function

    return 0;
}

void extract_country_from_csv(string filename, country input, string name){
    string line; //To read each line from csv
    int i=0; //To check later on if we have successfully found data for the country in question
    int line_deaths; //To store current lines deaths
    string line_date; //To store current lines date
    string line_country; //To store current lines country


    ifstream myFile(filename); //Create an input filestream

    if(!myFile.is_open()) throw std::runtime_error("Could not open file"); //Check file is open

    getline(myFile, line); //Disregard the first line of headings

    while(!myFile.eof()){ //for the whole file
        getline(myFile, line); //Read a line
        stringstream ss(line); //Create a stringstream which is equal to the line
        vector<string> strvect; //Create a string vector

        while(ss.good()){ //Iterate over the whole line
            string strline; //dummy string
            getline(ss, strline, ','); //Read until the next comma, assign that value to the dummy
            //cout << strline << endl;
            strvect.push_back(strline); //Append to the vector
        }

        line_date = strvect[0]; //Date will always be the first value in the vector
        line_deaths = stoi(strvect[5]); //Always this index, also convert string to int with stoi()
        line_country = strvect[6]; //Always this index
        if(strvect[6] == name){ //If this the country we are searching for?
                input.setdd(line_date,line_deaths); //If yes, record the info we read from that line of the csv
                i=1; //Set this to 1, so we can be sure some data was found
        }
    }
    if(i==0){ //If no data found, inform user
        cout << "Error invalid Country name, please ensure the name begins with a capital letter" << endl;
    }
    cout << "Extracted data: " << endl;
    input.print(); //Display the vectors containing to the dates and deaths for that country
    cout << "Total deaths recorded: ";
    input.info(); //Display running total
    input.plot(name); //Call plotting function
    myFile.close();
}
