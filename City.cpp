#include "City.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

City::City(string cityName, string countryName, string latitudeNumber, string longitudeNumber) {		//constructor
	set_cityName(cityName);
	set_countryName(countryName);
	set_latitudeNumber(latitudeNumber);
	set_longitudeNumber(longitudeNumber);
}

void City::set_cityName(string cityName_param) {		//setters
	cityName = cityName_param;
}

string City::get_cityName() const{						//getters
	return cityName;
}

void City::set_countryName(string countryName_param) {
	countryName = countryName_param;
}

string City::get_countryName() const{
	return countryName;
}

void City::set_latitudeNumber(string latitudeNumber_param) {
	latitudeNumber = latitudeNumber_param;
}

string City::get_latitudeNumber() const{
	return latitudeNumber;
}

void City::set_longitudeNumber(string longitudeNumber_param) {
	longitudeNumber = longitudeNumber_param;
}

string City::get_longitudeNumber() const{
	return longitudeNumber;
}
