// File:     country.h
// Author:   Oisin Hodgins 17480216 oisinhodgins1@nuigalway.ie
// Date:     May/2020
// What:     Header file for country class
// See also: main.cpp & country.cpp
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>

#ifndef _COUNTRY_H_INCLUDED
#define _COUNTRY_H_INCLUDED

using namespace std;

class country{
private:
    vector<int> deaths; //To store the number of COVID-19 deaths each day
    vector<string> dates; //To record the date corresponding to the abpve value
    int tot_death; //Running total of deaths from COVID-19 for a country
public:
    country(); //Constructor
    void info(void){cout<<tot_death<<endl;}; //Output current total
    void setdd(string date,int death); //Set both deaths[i] & dates[i] with a value, for some i
    void print(void); //Output deaths & dates to console output
    void plot(string country_name); //Produce plot
};

#endif
