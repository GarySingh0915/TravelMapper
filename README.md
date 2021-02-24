# TravelMapper
Problem: Given a list of world cities with their latitudes and longitudes, find the cities closest to a userselected city.

The Assignment: Design, develop and test an Object-Oriented C++ program that will allow the user to
select a city from a list, and then will list the five cities (from the same list) that are closest to the
selected city, based on Great Circle calculations.

Discussion: The shortest distance between two points on the surface of a sphere is called the Great Circle
Distance. Given the latitude and longitude of two cities, that distance can be calculated by use of a
publicly-available formula (see reference below). Consider the following ideas in preparing your
solution to this problem.

• Develop a user-defined class named City that stores and manages information about a single city,
including at least the city’s name, country, and location as instance variables. Provide constructor(s)
and appropriate methods to manage this information.

• Read, parse, and save the contents of the worldcities.csv file into a collection of City variables.

• Repeat the following until the user enters “Quit” or “quit”.

  o Ask the user to pick a city, by name or by index, from all available cities. The user must be
  able to enter a city number or a city name – both options must be available.

  o Calculate the Great Circle Distance from the selected city to each of the other cities in the
  collection.

  o Find the five cities closest to the one selected, based on the calculated distances.

  o Display the list of five closest cities, along with the great circle distance to each in miles. The
  list must be sorted in ascending order by distance, with the closest city first.

  o Save the list of five closest cities, along with the great circle distance to each in miles. The
  file output must be formatted exactly the same as the console output. 
