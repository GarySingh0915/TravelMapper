#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#include <chrono>
#include <thread>
#include <math.h>
#include <stdio.h>
#include "City.h"

#ifndef M_PI
#	define M_PI 3.14159265358979323846				//pi number for calculation of distance
#endif

ofstream output_file;

using namespace std;


static const double earthRadiusKm = 6371.0;

const string cities_file = "worldcities.csv";

vector<City> read_cities_from_file() {					//extracting data from worldcities.csv
	vector<City> cities;

	ifstream input_file(cities_file);
	if (input_file) {		// if file opened successfully
		string line;
		
		getline(input_file, line);
		while (getline(input_file, line)) {
			stringstream ss(line);
			string cityName;
			string countryName;
			string latitudeNumber;
			string longitudeNumber;

			
			getline(ss, cityName, ',');						//using comma as a delimeter
			getline(ss, countryName, ',');
			getline(ss, latitudeNumber, ',');
			getline(ss, longitudeNumber, ',');
			

			cities.push_back(City(cityName, countryName, latitudeNumber, longitudeNumber));
		}
		input_file.close();
	}
	return cities;
}

void view_cities(const vector<City>& cities) {						//prints out cities on console 
	int col_width = 10;

	int number = 1;
	cout << left
		<< setw(col_width / 2) << "#"
		<< setw(col_width * 2) << "City"
		<< setw(col_width * 2) << "Country"
		<< setw(col_width * 2) << "Latitude"
		<< setw(col_width * 2) << "Longitude" << endl;
	for (City city : cities) {
		cout << left 
			<< setw(col_width / 2) << number
			<< setw(col_width * 2) << city.get_cityName()
			<< setw(col_width * 2) << city.get_countryName()
			<< setw(col_width * 2) << city.get_latitudeNumber()
			<< setw(col_width * 2) << city.get_longitudeNumber() << endl;
		++number;	
	}
	cout << endl;
}



bool check_number(string str) {								//checks if a string has an int in it
	for (int i = 0; i < str.length(); i++)
		if (str[i] == '-' || isdigit(str[i]) == false)
		{
			return false;
		}
		else
		{
			return true;
		}

}

void show_cityInfo(const City& c) {					//prints out what user chose on screen
	cout << "\nYOU CHOSE " << c.get_cityName() << ", " << c.get_countryName() << " WITH COORDINATES OF (" << c.get_latitudeNumber() << ", " << c.get_longitudeNumber() << ")" << endl;
	output_file << "\nYOU CHOSE " << c.get_cityName() << ", " << c.get_countryName() << " WITH COORDINATES OF (" << c.get_latitudeNumber() << ", " << c.get_longitudeNumber() << ")" << endl;
}

string to_upper(string str) {					//converts lowercase string to uppercase
	string str_upper;
	for (char c : str) {
		str_upper.push_back(toupper(c));
	}
	return str_upper;
}

int compare_cityName(const vector<City>& cities, string cityNameInput) {			//allows blank embedded and case insensitive input from user
	vector<string> citiesSpaceless;
	for (City city : cities) {
		string str = city.get_cityName();
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		citiesSpaceless.push_back(str);
	}
	cityNameInput.erase(remove(cityNameInput.begin(), cityNameInput.end(), ' '), cityNameInput.end());
	
	int index = 1;
	for (string newCity : citiesSpaceless) {
		
		if (to_upper(cityNameInput) == to_upper(newCity)) {
			break;
		}
		else {
			index++;
		}
	}
	if (index < 0 || index > 134) {
		index = 0;
	}
	return index;
}

double deg2rad(double deg)
{
	return (deg * M_PI / 180.0);
}

double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {			//calculates great circle distance
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(lat1d);
	lon1r = deg2rad(lon1d);
	lat2r = deg2rad(lat2d);
	lon2r = deg2rad(lon2d);
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);
	return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}


map<string,double> greatCircle_distance(const vector<City>& cities, const City& c) {		//gathers great circle distance for all city variables
	map<string,double> distanceLatLong;
	for (City city : cities) {
		double distance = distanceEarth(stoi(c.get_latitudeNumber()), stoi(c.get_longitudeNumber()), stoi(city.get_latitudeNumber()), stoi(city.get_longitudeNumber()));
		string cityInfo = city.get_cityName() + " in " + city.get_countryName() + " (" + city.get_latitudeNumber() + ", " + city.get_longitudeNumber() + ")";
		distanceLatLong[cityInfo] = distance;
		
	}
	return distanceLatLong;
}

double km_toMiles(double km) {				//converts km to miles
	return km * 0.621371;
}
void closest_cities(const vector<City>& cities, map<string,double> distanceCities) {				//finds closest cities.
	int col_width = 20;
	// Declaring the type of Predicate that accepts 2 pairs and return a bool
	typedef std::function<bool(std::pair<std::string, int>, std::pair<std::string, int>)> Comparator;

	// Defining a lambda function to compare two pairs. It will compare two pairs using second field
	Comparator compFunctor =
		[](std::pair<std::string, int> elem1, std::pair<std::string, int> elem2)
	{
		return elem1.second < elem2.second;
	};

	// Declaring a set that will store the pairs using above comparision logic
	set<pair<string, double>, Comparator> setOfWords(distanceCities.begin(), distanceCities.end(), compFunctor);

	// Iterate over a set using range base for loop
	// It will display the items in sorted order of values
	//for (std::pair<std::string, double> element : setOfWords)
		//std::cout << element.first << " :: " << element.second << std::endl;

	// Create a map iterator and point to beginning of map
	set<pair<string, double>, Comparator>::iterator it = setOfWords.begin();

	++it;
	// Iterate over the map using Iterator till end.
	
	for (int x = 0; x < 5; x++)
	{
		// Accessing KEY from element pointed by it.
		std::string word = it->first;

		// Accessing VALUE from element pointed by it.
		int count = it->second;

		cout << left << setw(col_width*3) << word << " ==>           " << right << count << " km / " << km_toMiles(count) << " miles."<< endl;
		output_file << left << setw(col_width * 3) << word << " ==>           " << right << count << " km / " << km_toMiles(count) << " miles." << endl;
		// Increment the Iterator to point to next entry
		it++;
	}
	
	
}

void farthest_cities(const vector<City>& cities, map<string, double> distanceCities) {		//finds farthest cities.
	int col_width = 20;
	// Declaring the type of Predicate that accepts 2 pairs and return a bool
	typedef std::function<bool(std::pair<std::string, int>, std::pair<std::string, int>)> Comparator;

	// Defining a lambda function to compare two pairs. It will compare two pairs using second field
	Comparator compFunctor =
		[](std::pair<std::string, int> elem1, std::pair<std::string, int> elem2)
	{
		return elem1.second > elem2.second;
	};

	// Declaring a set that will store the pairs using above comparision logic
	set<pair<string, double>, Comparator> setOfWords(distanceCities.begin(), distanceCities.end(), compFunctor);

	// Create a map iterator and point to beginning of map
	set<pair<string, double>, Comparator>::iterator it = setOfWords.begin();

	// Iterate over the map using Iterator till end.
	
	for (int x = 0; x < 5; x++)
	{
		// Accessing KEY from element pointed by it.
		string word = it->first;

		// Accessing VALUE from element pointed by it.
		int count = it->second;

		cout << left << setw(col_width * 3) << word << " ==>           " << right << count << " km / " << km_toMiles(count) << " miles." << endl;
		
		output_file << left << setw(col_width * 3) << word << " ==>           " << right << count << " km / " << km_toMiles(count) << " miles." << endl;
		

		// Increment the Iterator to point to next entry
		it++;
	}
	

}

void display_menu() {
	int col_width = 70;
	cout << right
		<< setw(col_width) << "Welcome To The City Locater Program\n"
		<< setw(col_width+30) << "This program will find cities nearest and farthest away from your current chosen city.\n\n\n";
	cout << left
		<<"PLEASE WAIT 5 SECONDS WHILE THE LIST OF ALL THE CITIES ARE LISTED BELOW. THANKS FOR YOUR PATIENCE...\n";
		auto start = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::seconds(10));
}


int main() {
	output_file.open("results.txt", ios::out | ios::trunc);			//creates a file named results.txt
	vector<City> cities = read_cities_from_file();
	display_menu();
	view_cities(cities);
	
	while (true) {
		
		string cityNameInput;
		cout << "\nPLEASE ENTER A CITY, BY NAME OR INDEX(1 - 134), FROM THE LIST ABOVE: ";
		getline(cin, cityNameInput);
		output_file << "\nPLEASE ENTER A CITY, BY NAME OR INDEX(1 - 134), FROM THE LIST ABOVE: " << cityNameInput;
		if (to_upper(cityNameInput) == "QUIT") {
			break;
		}
		if (cityNameInput[0] == '-') {
			cout << "Number must be greater than 1. Try again.\n";
		}

		if (check_number(cityNameInput)) {
			
			int number = stoi(cityNameInput);
			if (number < 1 || number < 0) {
				cout << "Number must be greater than 1. Try again.\n";
			}
			else if (number > cities.size()) {
				cout << "Number must be less than 134 or less\n";
			}
			else {
				
				City city = cities[number - 1];
				show_cityInfo(city);
				map <string, double> distanceCities = greatCircle_distance(cities, city);
				cout << "\n\n****THE 5 CITIES CLOSEST TO " << city.get_cityName() << " are: ****\n\n";
				output_file << "\n\n****THE 5 CITIES CLOSEST TO " << city.get_cityName() << " are: ****\n\n";
				closest_cities(cities, distanceCities);
				cout << "\n\n****THE 5 CITIES FARTHEST AWAY FROM " << city.get_cityName() << " are: ****\n\n";
				output_file << "\n\n****THE 5 CITIES FARTHEST AWAY FROM " << city.get_cityName() << " are: ****\n\n";
				farthest_cities(cities, distanceCities);
				cout << "\nRESULTS FROM ALL CITIES ARE APPENDED IN FILE 'RESULTS.TXT' IN PROJECT FOLDER.\n";
					
			}
		}

		else {
			int number = compare_cityName(cities, cityNameInput);
			if (number == 0) {
				cout << "No Match Found. Please Try Again\n";
			}
			else {
				City city = cities[number - 1];
				show_cityInfo(city);
				map <string, double> distanceCities = greatCircle_distance(cities, city);
				cout << "\n\n****THE 5 CITIES CLOSEST TO " << city.get_cityName() << " are: ****\n\n";
				output_file << "\n\n****THE 5 CITIES CLOSEST TO " << city.get_cityName() << " are: ****\n\n";
				closest_cities(cities, distanceCities);
				cout << "\n\n****THE 5 CITIES FARTHEST AWAY FROM " << city.get_cityName() << " are: ****\n\n";
				output_file << "\n\n****THE 5 CITIES FARTHEST AWAY FROM " << city.get_cityName() << " are: ****\n\n";
				farthest_cities(cities, distanceCities);
				cout << "\nRESULTS FROM ALL CITIES ARE APPENDED IN FILE 'RESULTS.TXT' IN PROJECT FOLDER.\n";
			}
		}
	}
	output_file.close();
	return 0;
}
