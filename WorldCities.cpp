#include "std_lib_facilities.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Country { // Parameters for the country name, and a forward_list of all it's cities
    public:
        
        string nameofcountry;
        forward_list<string> citynames;

};

class CountryStats { // Holds a country's name, # of cities, and total population, overloaded << op for printing the info to output stream

    public:
    string name_;
    int numbcitiesinlist_;
    int totalpopulationinlist_;

    friend ostream& operator<<(ostream& os, const CountryStats& cs) {
        
        os << "Country: " << cs.name_ << " Number of Cities in List: " << cs.numbcitiesinlist_ << " Total Population in List: " << cs.totalpopulationinlist_ << endl;
        
        return os;
    }

};

class WorldCities
{
    vector<CountryStats> CSvect; // Holds a CountryStats object for every unique country
    
    forward_list<Country> countrylists_; // holds a Country object for every unique country

    public:

    void compileCountryStats(string file_name) 
    {
        // Compiles a forward list of Country type for all unique countries and a vector of all CountryStats objects, one element for each country
        
        ifstream file;
        file.open(file_name);

        string city; 
        string country;
        string population;

        while(getline(file,city,',')) 
        {
            getline(file,country,',');
            getline(file,population,'\n');

            const char* populationconvert = population.c_str(); // Convert population from string -> int for setting CountryStats parameters
            int citypopulation = atoi(populationconvert); 

            bool unique = true; 
            for(auto &countryinlist: countrylists_)  // Checks if country has been added to countrylists_ yet
            {    
                if(country == countryinlist.nameofcountry) // (Previously Added) City roster and CountryStats for previously created country are updated
                {
                    unique = false;
                    countryinlist.citynames.push_front(city);
                    
                    for(auto &elem: CSvect) 
                    {
                        if(elem.name_ == country)
                        {
                            elem.numbcitiesinlist_ += 1;
                            elem.totalpopulationinlist_ += citypopulation;
                        }
                    }
                }
            }
            if(unique == true) // (New Country) Country obj is initialized, named, added to countrylists_, and the current city is added to its flist
            {
                Country newCountry; 
                newCountry.nameofcountry = country;
                newCountry.citynames.push_front(city);
                countrylists_.push_front(newCountry);

                CountryStats newStats; // A CountryStats obj is initialized, named, parameters are set, added to the CSvect
                newStats.name_ = country;
                newStats.numbcitiesinlist_ = 1;
                newStats.totalpopulationinlist_ = 0;
                newStats.totalpopulationinlist_ += citypopulation;
                CSvect.push_back(newStats);
            }
        }
    }
    
    vector<CountryStats> PrintAllInSameCountry(std::string city, bool allcountries, bool alphabetical)
    {
        compileCountryStats("WorldCities.csv"); // Compiles CSvect and countrylists_ 
        
        vector<CountryStats> CSoutput; // CountryStats of the country/countries containing input city
        vector<Country> CountriesToOutput; // Countries whose cities should be printed
                
        bool CountryFound = false;

        for (auto &country: countrylists_) 
        {                
            // Checks all cities of all countries for one that matches the input city name
            
            if (CountryFound == false) // Prevents more than one country from being added to CountriesToOutput when allcountries == false
            {
                for (auto &countrycity: country.citynames)
                {
                    if (countrycity == city)
                    {
                        CountriesToOutput.push_back(country);
                        if (allcountries == false)
                        {
                            CountryFound = true; 
                        }
                        break;
                    }
                }
            }
        }
        
        if (CountriesToOutput.size() == 0) // No city matching the city input was found
        {
            cout << "The city does not appear in the most populated cities list";
        }
        
        if (alphabetical == true) // Sorts and countries cities alphabetically 
            {
                forward_list<string> TempCountryNames; // Temporary flist used to sort the country names alphabetically 

                vector<Country> AlphabeticalCountries; // Vector that we fill with country names after alphabetically sorted

                for (int i = 0; i < CountriesToOutput.size(); i++)
                {
                    CountriesToOutput[i].citynames.sort();

                    TempCountryNames.push_front(CountriesToOutput[i].nameofcountry);
                }
            
                TempCountryNames.sort();

                for (auto &elem: TempCountryNames)
                {
                    for (int i = 0; i < CountriesToOutput.size(); i++)
                    {
                        if (elem == CountriesToOutput[i].nameofcountry)
                        {
                            AlphabeticalCountries.push_back(CountriesToOutput[i]);
                        }
                    }
                }
                CountriesToOutput = AlphabeticalCountries;
            }

        int NumOutputCities; // Number of cities to print from the current country
        int citiesprinted = 0; // Keeps track of how many cities have been printed from current country
        
        for (int i = 0; i < CountriesToOutput.size(); i++) // Adds CS obj to CSoutput, prints every city, and prints name of country for each Country in CountriesToOutput
        {
            cout << CountriesToOutput[i].nameofcountry << endl; 
            citiesprinted = 0; 
            for (auto &elem: CSvect)  // Adds CountryStats for current country to CSoutput and finds # of cities in current country
            {
                if (elem.name_ == CountriesToOutput[i].nameofcountry)
                {
                    NumOutputCities = elem.numbcitiesinlist_;
                    CSoutput.push_back(elem);
                    break;
                }
            }
    
            for (auto &cityofcountry: CountriesToOutput[i].citynames) // Prints every city of current country
            {
                if (citiesprinted != NumOutputCities-1)
                {
                    citiesprinted++;
                    cout << cityofcountry << ", ";
                }
                else
                {
                    cout << cityofcountry << '\n';
                }
            }
        } 
        /*for (auto& elem: CSoutput) //<-- Just in case you want to test this functionality
        {
            cout << elem << endl;
        }*/
        
        return CSoutput; // Returns the CountryStats objects of the countries that are printed out
    }

    bool ReadCSVFile(string filename="./WorldCities.csv") // Ensures the .csv file was read in properly
    {
        if (filename == "WorldCities.csv")
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    WorldCities wc;

    if (wc.ReadCSVFile("WorldCities.csv"))
    {
        std::ifstream testfile("WorldCitiesTests.txt");
        std::string testline;
        std::string cityname;
        std::string allcountries_str;
        std::string alphabetical_str;
        int allcountries;
        int alphabetical;
        while (std::getline(testfile, testline))
        {
            std::stringstream ss(testline);
            std::getline(ss, cityname, ',');
            std::getline(ss, allcountries_str, ',');
            std::getline(ss, alphabetical_str, ',');
            allcountries = atoi(allcountries_str.c_str());
            alphabetical = atoi(alphabetical_str.c_str());
            wc.PrintAllInSameCountry(cityname, (allcountries != 0), (alphabetical != 0));
        }
       return 0;
    }
}