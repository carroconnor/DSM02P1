#include "clock.h"
#include <iostream>
#include <regex>
#include <vector>

/* Program name: clock.cpp
* Author: Carr O'Cononr
* Date last updated: 6/11/2024
* Purpose: Use regular expressions to valid user input clock type
*/

// You will be given a class clockType. This class holds time as it is displayed on a clock. An object of this class is one of two types, 
// a 12-hour clock or a 24-hour clock. For all clocks, valid minutes and seconds are in the range of 0 - 59. For a 12-hour clock, 
// hours are in the range from 1- 12 and the time of day is set to AM or PM. For a 24-hour clock the valid hours are in the range of 0 - 23.

// You will write a program that gets times from the user. The time might fit any of the following formats: 

// h:mm:ss AM x
// h:mm:ss PM x
// hh:mm:ss AM x
// hh:mm:ss PM x
// h:mm AM x
// h:mm PM x
// h:mm:ss x
// hh:mm:ss x
// h:mm

// The formats that do not have an AM/PM, represent times for a 24-hour clock. The AM/PM may be entered in uppercase or lowercase. 
// Set up a loop that asks the user for a time. Validate the time using a regular expression, create a clockType object if the time is valid, 
// and add the object to a vector of clockType objects, otherwise, go back and get a new time from the user. 
// If the user enters the word quit then the program should display all the valid times in the vector and exit the program.

std::string trim(const std::string &str, const std::string &whitespace);
void reset();

int main(){
    std::regex const simple24{"^(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])$"}; //hh:mm
    std::regex const simple12{"^(0[0-9]|1[0-2]):([0-5][0-9]) (AM|PM)$"}; //hh:mm AM/PM
    std::regex const complex12{"^(0[1-9]|1[0-2]):([0-5][0-9]):([0-5][0-9]) (AM|PM)$"}; //hh:mm:ss AM/PM
    std::regex const complex24{"^(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])$"}; //hh:mm:ss
    std::regex const singleHourComplex{"^([0-9]):([0-5][0-9]):([0-5][0-9]) (AM|PM)$"}; //h:mm:ss AM/PM
    //below is the pattern if all were combined but I found the above easiest to read and use
    //std::regex const clockPattern = {"^(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])$|^(0[0-9]|1[0-2]):([0-5][0-9]) (AM|PM)$|^(0[1-9]|1[0-2]):([0-5][0-9]):([0-5][0-9]) (AM|PM)$|^(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])$|^([0-9]):([0-5][0-9]):([0-5][0-9]) (AM|PM)$"};
    std::smatch match;
    std::string userAnswer;
    const std::string exitKey = "QUIT";
    std::vector<clockType> clocks;

    while(userAnswer != exitKey){
        std::getline(std::cin, userAnswer);
        std::transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::toupper);
        if(userAnswer != exitKey){
            if(std::regex_match(userAnswer, match, simple24)){
                clockType clock(std::stoi(match[1]), std::stoi(match[2]), 0, TWENTYFOUR, AM);
                clocks.push_back(clock);
            }
            else if(std::regex_match(userAnswer, match, simple12)){
                clockType clock(std::stoi(match[1]), std::stoi(match[2]), 0, TWELVE, clockType::strToAmPm.at(match[3]));
                clocks.push_back(clock);
            }
            else if(std::regex_match(userAnswer, match, complex12)){
                clockType clock(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]), TWELVE, clockType::strToAmPm.at(match[4]));
                clocks.push_back(clock);
            }
            else if(std::regex_match(userAnswer, match, singleHourComplex)){
                clockType clock(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]), TWELVE, clockType::strToAmPm.at(match[4]));
                clocks.push_back(clock);
            }
            else if(std::regex_match(userAnswer, match, complex24)){
                clockType clock(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]), TWENTYFOUR, AM);
                clocks.push_back(clock);
            }
        }
    }

    for(int i = 0; i < clocks.size(); i++){
        std::cout << clocks.at(i).print() << std::endl;
    }

    return 0;
}

std::string trim(const std::string &str,
                 const std::string &whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}