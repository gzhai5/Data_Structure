#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include "airport.h"
#include "airline.h"
#include "readFromFile.hpp"

/*
 * This function reads a .dat file to a vector of airports
 * The structure of the data should be as follows:
 * (id, fullname, city, country, 3-letter abbr, 4-letter abbr, latitude, longitude, altitude, ...)
 * The real things that matter is (under 0 indexing) the 3-letter abbr is at the fourth place, latitude and lkongitude are at the 6th and 8th places respectively.
 * Under construction, the id is the index in the vector (NOT the one in .dat file) 
 */
std::vector<airport*> file_to_airport(const std::string & filename) {
    std::vector<std::string> lines = read_buffer(filename);
    std::vector<airport*> to_return;
    for (std::string line: lines) {
	unsigned id = to_return.size();
	std::string name;
	double latitude = 1000;
	double longitude = 1000;
	unsigned comma = 0;
	std::string word = "";
	if (line.size()==0) {
	    continue;
	}
	for (size_t i = 0; i < line.size(); i++) {
	    if (line[i] == ',') {
		comma += 1;
		if (comma == 5) {
		    name = word;
		    word = "";
		    continue;
		}
		// sometimes a 3-letter abbr is not defined. In this case, use 4 letter abbr instead
	        if (comma == 6) {
		    if (name=="\\N") {
			name = word;
		    }
		    word = "";
		    continue;
		}
		if (comma == 7) {
		    // the data might be broken, and a conversion to double might fail. In this case, neglect this whole entry
		    try {
			latitude = std::stod(word);
		    } catch (const std::exception & e){
		        latitude = 1000;
		    }
		    word = "";
		    continue;
		}
		if (comma == 8) {
		    //same as above. If the data broke, neglect the entry
		    try{
		        longitude = std::stod(word);
		    } catch (const std::exception & e) {
			longitude = 1000;
		    }
		    word = "";
		    continue;
		}
	    } else {
		if (((comma==4) || (comma==5) || (comma==6) || (comma==7)) && (line[i] != '\"')) {
		    word.push_back(line[i]);
		}
	    }
	}
	if ((name!="") && (name !="\\N") && (latitude!=1000) && (longitude!=1000)) {
	    to_return.push_back(new airport(id,name,latitude,longitude));
	}
    }
    return to_return;
}

std::pair<std::vector<airport*>,std::vector<airline*>> file_to_airline(const std::string & airport_file, const std::string & filename) {
    std::vector<airport*> to_return_1 = file_to_airport(airport_file);
    std::vector<airline*> to_return_2;
    std::vector<std::string> lines = read_buffer(filename);

    for (std::string line : lines) {
	std::string source, destination;
	unsigned comma = 0;
	std::string word = "";
	if (line.size()==0) {
	    continue;
	}
	for (size_t i = 0; i < line.size(); i++) {
	    if (line[i] == ',') {
		comma += 1;
		if (comma == 3) {
		    source = word;
		    word = "";
		    continue;
		}
		if (comma == 5) {
		    destination = word;
		    word = "";
		    continue;
		}
	    } else {
		if ((comma==2) || (comma==4)) {
		    word.push_back(line[i]);
		}
	    }
	}
	// now we know the route is from "source" to "destination"
	// need to do a search in the existing airports
	airport* tmp1 = NULL;
	airport* tmp2 = NULL;
	for (unsigned i = 0; i < to_return_1.size(); i++) {
	    if (to_return_1[i]->name_ == source) {
		tmp1 = to_return_1[i];
	    }
	    if (to_return_1[i]->name_ == destination) {
		tmp2 = to_return_1[i];
	    }
	}
	if ((tmp1!=NULL) && (tmp2!=NULL)) {
	    to_return_2.push_back(new airline(tmp1, tmp2));
	}
    }

    return std::pair<std::vector<airport*>, std::vector<airline*>>(to_return_1, to_return_2);
}

/* 
 * This is a helper function for both read from file functions aboce
 * The purpose for this helper function is to split a file of multiple lines to a vector, each contains a single line
 */
std::vector<std::string> read_buffer(const std::string & filename) {
    std::ifstream text(filename);
	
    std::stringstream strStream;
    if (text.is_open()) {
	strStream << text.rdbuf();
    }
    std::string st = strStream.str();
    std::vector<std::string> v;
    std::string to_put = "";
    for (size_t i = 0; i < st.size(); i++) {
	if (st[i]!='\n') {
	    to_put.push_back(st[i]);
	} else {
	    v.push_back(to_put);
	    to_put = "";
	}
    }
    return v;
}
