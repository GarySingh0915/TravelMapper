#ifndef Gary_City_H
#define Gary_City_H

#include <iostream>
#include <string>

using namespace std;

class City {
private:
	string cityName;				//instance variables
	string countryName;
	string latitudeNumber;
	string longitudeNumber;

public:
	City(string cityName, string countryName, string latitudeNumber, string longitudeNumber); //city variables constructor

	void set_cityName(string);						//setters 
	string get_cityName() const;					//getters

	void set_countryName(string);
	string get_countryName() const;

	void set_latitudeNumber(string);
	string get_latitudeNumber() const;

	void set_longitudeNumber(string);
	string get_longitudeNumber() const;
};


#endif // Gary_City_H