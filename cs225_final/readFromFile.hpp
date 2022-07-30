#include <string>
#include <iostream>
#include "airport.h"
#include "airline.h"

/*
 * This function reads a .dat file to a vector of airports
 * The structure of the data should be as follows:
 * (id, fullname, city, country, 3-letter abbr, 4-letter abbr, latitude, longitude, altitude, ...)
 * The real things that matter is (under 0 indexing) the 3-letter abbr is at the fourth place, latitude and lkongitude are at the 6th and 8th places respectively.
 * Under construction, the id is the index in the vector (NOT the one in .dat file) 
 */
std::vector<airport*> file_to_airport(const std::string & filename);
std::pair<std::vector<airport*>,std::vector<airline*>> file_to_airline(const std::string & airport_file, const std::string & filename);


/* 
 * This is a helper function for both read from file functions aboce
 * The purpose for this helper function is to split a file of multiple lines to a vector, each contains a single line
 */
std::vector<std::string> read_buffer(const std::string & filename);
