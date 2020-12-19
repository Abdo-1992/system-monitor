#include <string>

#include "format.h"
using std::to_string;
using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    int hours {0} ;
    int min   {0} ; 

    hours = seconds/ 3600 ;
    seconds %= 3600 ;

    min = seconds / 60 ;
    seconds %= 60 ;

    return to_string(hours)+":"+to_string(min)+":"+to_string(seconds); 
}