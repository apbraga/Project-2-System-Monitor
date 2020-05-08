#include <string>
#include <cmath>
#include "format.h"

using std::string;

// Not Tested: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    //get number of hours from totoal number of seconds
    long hour = std::floor(seconds/3600);
    seconds -= hour*3600;
    // get number of minutes from total number os seconds
    long minutes = std::floor(seconds/60);
    //get number of seconds
    seconds -= minutes*60;
    //convert to HH:MM:SS formating
    std::string time = std::to_string(hour) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);   
    
    return time; }