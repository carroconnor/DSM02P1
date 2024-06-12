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

int main(){                          //h:mm:ss AM/PM                              //hh:mm:ss AM/PM                                   //h:mm AM/PM                       //h:mm:ss (24)                         //hh:mm:ss                                 // h:mm
    std::regex const clockPattern{"^([1-9]{1}):([0-5][0-9]):([0-5][0-9]) (AM|PM)$|^(0[1-9]|1[0-1]):([0-5][0-9]):([0-5][0-9]) (AM|PM)$|^([1-9]{1}):([0-5][0-9]) (AM|PM)$|^([1-9]{1}):([0-5][0-9]):([0-5][0-9])$|^(0[1-9]|1[0-1]):([0-5][0-9]):([0-5][0-9])$|^([1-9]{1}):([0-5][0-9])$"};
    std::smatch match;
    std::string userAnswer;
    const std::string exitKey = "QUIT";
    std::vector<clockType> clocks;

    while(userAnswer != exitKey){
        std::cout << "What is the current time?" << std::endl;
        std::getline(std::cin, userAnswer);
        std::transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::toupper);
        if(userAnswer != exitKey){
            if(std::regex_match(userAnswer, match, clockPattern)){
                std::cout << match[1] << std::endl;
                std::cout << match[2] << std::endl;
                std::cout << match[3] << std::endl;
                std::cout << match[4] << std::endl;
                std::cout << match[5] << std::endl;
                std::cout << match[6] << std::endl;
                std::cout << match[7] << std::endl;
                std::cout << match[8] << std::endl;
                std::cout << match[9] << std::endl;
                std::cout << match[10] << std::endl;
                std::cout << match[11] << std::endl;
                std::cout << match[12] << std::endl;
                std::cout << match[13] << std::endl;
                std::cout << match[14] << std::endl;
                std::cout << match[15] << std::endl;
                std::cout << match[16] << std::endl;
                std::cout << match[17] << std::endl;
                std::cout << match[18] << std::endl;
                std::cout << match[19] << std::endl;

                if(!match[1].str().empty() && !match[4].str().empty()){
                    clockType clock(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]), TWELVE, clockType::strToAmPm.at(match[4]));
                    clocks.push_back(clock);
                }
                else if(!match[5].str().empty() && !match[8].str().empty()){
                    clockType clock(std::stoi(match[5]), std::stoi(match[6]), std::stoi(match[7]), TWELVE, clockType::strToAmPm.at(match[8]));
                    clocks.push_back(clock);
                }
                else if(!match[9].str().empty() && !match[11].str().empty()){
                    clockType clock(std::stoi(match[9]), std::stoi(match[10]), 0, TWELVE, clockType::strToAmPm.at(match[11]));
                    clocks.push_back(clock);
                }
                else if(!match[12].str().empty() && !match[14].str().empty()){
                    clockType clock(std::stoi(match[12]), std::stoi(match[13]), std::stoi(match[14]), TWENTYFOUR, AM);
                    clocks.push_back(clock);
                }
                else if(!match[15].str().empty() && !match[16].str().empty() && !match[17].str().empty()){
                    clockType clock(std::stoi(match[15]), std::stoi(match[16]), std::stoi(match[17]), TWENTYFOUR, AM);
                    clocks.push_back(clock);
                }
                else{
                    clockType clock(std::stoi(match[18]), std::stoi(match[19]), 0, TWENTYFOUR, AM);
                    clocks.push_back(clock);
                }

            }else{
                reset();
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

void reset(){
    std::cout << "You entered an invalid clock format." << std::endl;
    std::cin.clear();
    std::cin.ignore(200, '\n');
}