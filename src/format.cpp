#include <string>
#include <cmath>
#include "format.h"
#include <sstream>

using std::string;

// Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  int hours, minutes;
  minutes = seconds / 60;
  hours = minutes / 60;
  std::stringstream s;
  std::string hours_s, minutes_s, seconds_s;
  
  if(hours < 10 ){
    hours_s = "0" + std::to_string(hours) + ":";
  } else {
    hours_s = std::to_string(hours) + ":";
  }
 
    if(int(minutes % 60) < 10 ){
    minutes_s = "0" + std::to_string(int(minutes % 60)) + ":";
      
  } else {
    minutes_s = std::to_string(int(minutes % 60)) + ":";
  }

    if(int(seconds % 60) < 10 ){
    seconds_s = "0" + std::to_string(int(seconds % 60));
  } else {
    seconds_s = std::to_string(int(seconds % 60));
  }  
  
  s << hours_s << minutes_s << seconds_s << std::endl;
  return s.str();
}
  