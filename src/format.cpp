#include <string>
#include <cmath>
#include "format.h"

using std::string;

// Not Tested: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 

    long hour = std::floor(seconds/3600);
    seconds -= hour*3600;
    long minutes = std::floor(seconds/60);
    seconds -= minutes*60;

    std::string time = std::to_string(hour) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);   
    
    return time; }