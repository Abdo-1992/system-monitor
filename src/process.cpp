#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;




// TODO: Return this process's ID
int Process::Pid() { return  Process::PidValue ; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return Process::CpuUtilizationValue; }

// TODO: Return the command that generated this process
string Process::Command() { return Process::CommandValue; }

// TODO: Return this process's memory utilization
string Process::Ram() { return Process::RamValue; }

// TODO: Return the user (name) that generated this process
string Process::User() { return Process::UserValue; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return Process::UpTimeValue; }

void Process::Pid(int p){
    Process::PidValue = p ;
}          
void Process::User(std::string s){
    Process::UserValue = s ;
}                
void Process::Command(std::string s){
    Process::CommandValue = s ;
}               
void Process::CpuUtilization(float f){
    Process::CpuUtilizationValue = f ;
}              
void Process::Ram(std::string s){
    Process::RamValue = s ;
}                 
void Process::UpTime(long int i){
    Process::UpTimeValue = i ; 
}                 

void Process::updateParameters(int pid){
    Process::PidValue = pid ;
    Process::UpTimeValue = findUpTimeValue(pid) ;
    Process::UserValue = findUser(pid) ;
    Process::CommandValue = findCommandValue(pid) ;
    Process::CpuUtilizationValue = FindCpuUtilizationValue(pid);
    Process::RamValue = findRamValue(pid) ; 
    
}

std::string Process::findCommandValue(int pid){
    std::string path{ LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kCmdlineFilename} ;
    std::string line ;
    std::string temp ;
    std::ifstream stream{path};
    std::istringstream words;
    if(stream){
        std::getline(stream,line);
        words.str(line);
        words >> temp ;
    }
    stream.close();
    return temp ;
}


long int Process::findUpTimeValue(int pid){
    std::string path{ LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatFilename} ;
    std::string line ;
    std::string temp ;
    std::ifstream stream{path};
    std::istringstream words;
    long up_time = 0 ;
    if(stream){
        std::getline(stream,line);
        int i = 0 ;
        words.str(line);
        while(i<22){
            i++ ;
            words >> temp ;
        }
        words >> up_time ;
    //    std::cout << up_time ;
        stream.close();

    }
    return up_time ;
}


std::string Process::findRamValue(int pid){
    std::string path{ LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatusFilename} ;
    std::string line ;
    std::string temp ;
    std::string result ;
    std::ifstream stream{path};
    std::istringstream words;

    if(stream){
        while(std::getline(stream,line)){
            words.str(line) ;
            words >> temp ;
            if(temp == "VmSize:"){
                words >> result ;
                result += " " ;
                temp.clear();
                words >> temp ;
                result += temp ;
            }
            temp.clear();
        }
    }
    stream.close();
    return result ;
}


float Process::FindCpuUtilizationValue(int pid){
    std::string path{ LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatFilename} ;
    std::string line ;
    std::string temp ;
    std::ifstream stream{path};
    std::istringstream words;
    int utime = 0 ;
    int stime = 0 ;
    int cutime = 0 ;
    int cstime = 0 ;
    int starttime = 0 ;
    int totlaTime = 0 ;
    float seconds = 0 ;
    int Hertz = 0 ;
    int up_time = LinuxParser::UpTime();
    float result = 0 ;
    if(stream){
        std::getline(stream,line);
        int i = 0 ;
        words.str(line);
        while(i++ < 13){
            temp.clear();
            words >> temp;
        }
        words >> utime >> stime >> cutime >> cstime ;
        i = 0 ;
        while(i++ < 4){
            temp.clear();
            words >> temp;
        }       
        words >> starttime ;
        Hertz =  sysconf(_SC_CLK_TCK) ;
        if(Hertz){
            totlaTime = utime + stime ;
            totlaTime = totlaTime + cutime + cstime ;
            return seconds = up_time - (1.0*starttime / Hertz) ;
            if(seconds){
                result = (100.0 * ((totlaTime / Hertz) / seconds)) ;
                return result ;
            }
        }
    }
    stream.close();
    return 0 ;
}

std::string Process::findUser(int pid){

    std::string userName ;
    std::string uid;
    std::string path{ LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatusFilename} ;
    std::string line ;
    std::string temp ;
    std::string dump ;
    std::ifstream stream{path};
    std::istringstream words;
    if(stream){
        while(std::getline(stream,line)){
            words.str(line) ;
            words >> temp   ;
            if(temp == "Uid:"){
                words >> temp ;
                break ;
            }
            temp.clear();
        }
    }
        path.clear();
        line.clear();
        stream.clear();
        stream.close();
        if(temp.length()){
            stream.open(LinuxParser::kPasswordPath);
            if(stream){
                while(std::getline(stream,line)){
                    std::replace(line.begin(), line.end(), ':', ' ');
                    words.str(line) ;
                    words >> userName >> dump >> uid;
                    if(uid == temp)
                        return userName ;
                    words.clear();
                }
            }
        }
        stream.close();
        return std::string();
}




// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    return (this->CpuUtilizationValue<a.CpuUtilizationValue); 
}