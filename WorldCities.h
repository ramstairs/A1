#include "std_lib_facilities.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Country {
    public:
        string nameofcountry;
        forward_list<string> citynames; 

};
class CountryStats {

    public:
    string name_;
    int numbcitiesinlist_;
    int totalpopulationinlist_;

    friend ostream& operator<<(ostream& os, const CountryStats& cs)
    {
        os << "Country: " << cs.name_ << " Number of Cities in List: " << cs.numbcitiesinlist_ << " Total Population in List: " << cs.totalpopulationinlist_ << endl;
        return os;
    }
};

class WorldCities
{
    public:
    
    vector<CountryStats> CSvect; // Holds a CountryStats object for every unique country
    forward_list<Country> countrylists_; // holds a Country object for every unique country


    void compileCountryStats(string file_name) {}; // Reads the given .csv file and fills CSvect & countrylists_

/* Outputs all cities in the same country (countries) as city to standard output. The country name
should first be output to a single line and then all cities in that country on the next line, each city name
separated by a comma from the next, except for the last city, which is followed by a newline character.
If allcountries is true, then all cities in all countries where a city by the same name appears in the list,
should be output to standard output in the same format as just described above. Otherwise, any country
with that city name should have all its cities output to standard output.
If alphabetical is true, then the cities in each country should be output to standard output in standard
alphabetical order
If alphabetical is false, then the cities for each country can be output to standard output in any order,
though cities in the same country should still be grouped together.
If both allcountries and alphabetical are true, then the cities in each country should be output to
standard output in standard alphabetical order, while the ordering of countries should also be
alphabetical.
If the city is not present in the CSV file, then the following message should be output to standard
output: “The city does not appear in the most-populated cities list”
*/
vector<CountryStats> PrintAllInSameCountry(std::string city, bool allcountries, bool alphabetical);
// Returns true if filename was a valid CSV file and was read in correctly
// Returns false otherwise
bool ReadCSVFile(string filename="./WorldCities.csv");
};

