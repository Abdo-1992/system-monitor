#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    calculateUtil();
    return Processor::UtilizationValue; 
}
void  Processor::Utilization(float u){
    Processor::UtilizationValue = u ;
}
void Processor::calculateUtil() {
    std::string path{ LinuxParser::kProcDirectory + LinuxParser::kStatFilename} ;
    std::string line ;
    std::string temp ;
    std::ifstream stream{path};
    std::istringstream words;
    long long int idle , iowait{0} , user{0} , nice{0} , system{0} , irq{0} , softirq{0} , steal{0} ; 
    long long int PrevIdle{0}, PrevNonIdle{0}, Idle{0}, NonIdle{0}, Total{0}, totald{0}, PrevTotal{0} , idled{0};
    float CPU_Percentage = 0; 
    if(stream){
        std::getline(stream,line);
        words.str(line) ;
        words >> temp >> user >> nice >> system >> idle >> iowait >> irq >> softirq ;
        PrevIdle = Processor::previdle + Processor::previowait ;
        Idle = idle + iowait ;
        PrevNonIdle =  Processor::prevuser +  Processor::prevnice +  Processor::prevsystem +  Processor::previrq +  Processor::prevsoftirq +  Processor::prevsteal ;
        NonIdle =  user + nice + system + irq + softirq + steal ;
        PrevTotal = PrevIdle + PrevNonIdle ;
        Total = Idle + NonIdle ;
        totald = Total - PrevTotal ;
        idled = Idle - PrevIdle ;
        Processor::prevuser = user ;
        Processor::prevnice = nice ;
        Processor::prevsystem = system ;
        Processor::previrq = irq ;
        Processor::prevsoftirq = softirq ;
        Processor::prevsteal = steal ;
        Processor::previdle = idle ;
        Processor::previowait = iowait ;
        if(totald)
            CPU_Percentage =1.0*(totald - idled)/totald ; 
    }
    Utilization(CPU_Percentage) ;
}


/*
PrevIdle = previdle + previowait
Idle = idle + iowait

PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
NonIdle = user + nice + system + irq + softirq + steal

PrevTotal = PrevIdle + PrevNonIdle
Total = Idle + NonIdle

# differentiate: actual value minus the previous one
totald = Total - PrevTotal
idled = Idle - PrevIdle

CPU_Percentage = (totald - idled)/totald

*/