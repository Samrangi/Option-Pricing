#include <iostream>
#include <math.h>
#include<vector>
#include<string>
#include<numeric>
#include<fstream>
#include<cstdlib>
#include<stdlib.h>
#include<cstring>
#include<locale>
#include<math.h>

using namespace std;

double average(vector<double> price_aug)
{
	//calculating the average rate
	//cout << "The control is at double average" << endl ;
	double avgPrice_aug = accumulate(price_aug.begin(),price_aug.end(), 0.0 )/price_aug.size();
	cout << "The average is : " << avgPrice_aug << endl ;
	return avgPrice_aug; //returning the value of avg back to the main function
}

double PayOffCall(double s, double k, int expo)
{
    double payCall = fmax(pow(s,expo)-k,0);
    return payCall;
}

double PayOffPut(double s, double k, int expo)
{
    double payPut = fmax(k-pow(s,expo),0);
    return payPut;
}



int main()
{

    //cout << "Control is at *" << endl ;
	vector<string> date;	// declaring the vector to store the date
	vector<double> price;	// declaring the vector to store the price

	string date_input;		// declaring the string type variable to input the date
	string price_input;		// declaring the string type variable to input the price

	ifstream infile("./AAPL_close_2015.csv");
	//Checking for file reading error
	if (infile.fail()) {
		cerr << "Error opening the file" ;
		exit(1);	// just a check to exit the program for sure
	}

	//reading the values if file reading is a success
	while(!infile.eof())
	{
		getline(infile,date_input,',');
		getline(infile,price_input,'\n');
		if(isdigit(date_input[0]))
		{
			date.push_back(date_input);
			price.push_back(stod(price_input));
		}
	}

	double s ; // underlying price
	double k ; // strike price
	int expo ; // the power
	cout << "Enter the strike price, underlying price and the power in order:" << endl;
	cin >>k >> s >> expo ;

	int unsigned index= 0;
	vector<double> price_aug;
	for(index=0; index < date.size(); index++)
    {
        if(date[index][0] == '8')
        {
            price_aug.push_back(price[index]);
        }
    }
    double avgPrice = average(price_aug);

    double payEuropeanCall, payEuropeanPut, payAsianCall, payAsianPut;

    payEuropeanCall = round(PayOffCall(s,k,expo));
    payEuropeanPut = round(PayOffPut(s,k,expo));
    payAsianCall = round(PayOffCall(avgPrice,k,1));
    payAsianPut = round(PayOffPut(avgPrice,k,1));

    cout << "The European payoff for call is : " << payEuropeanCall << endl ;
    cout << "The European payoff for put is : " << payEuropeanPut << endl ;
    cout << "The Asian payoff for call is : " << payAsianCall << endl ;
    cout << "The Asian payoff for put is : " << payAsianPut << endl ;

    double strike_new = 105;
    double strike_new_payEuropeanCall, strike_new_payEuropeanPut;
    strike_new_payEuropeanCall = round(PayOffCall(s,strike_new,expo));
    strike_new_payEuropeanPut = round(PayOffPut(s,strike_new,expo));
    cout << "For the new strike price of "<<strike_new<< ", The European payoff for call is : " << strike_new_payEuropeanCall << endl ;
    cout << "For the new strike price of "<<strike_new<< ", The European payoff for put is : " << strike_new_payEuropeanPut << endl ;

    return 0;
}
