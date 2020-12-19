#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"
#include "process.h"


class Processor {
 public:
    float Utilization();  // TODO: See src/processor.cpp
    void Utilization(float) ;
    void calculateUtil() ;
  // TODO: Declare any necessary private members
 private:
    float UtilizationValue ;
    long long int prevuser{0}, prevnice{0}, prevsystem{0}, previrq{0}, prevsoftirq{0}, prevsteal{0}, previdle{0} , previowait{0}; 
};

#endif