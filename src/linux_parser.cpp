#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
    filestream.close();
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel , version , result;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel >> version;
  }
  result = os + " " + kernel + " " + version ;
  stream.close();
  return result;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
    std::string path{ LinuxParser::kProcDirectory  + LinuxParser::kMeminfoFilename} ;
    std::string line ;
    std::string temp ;
    std::ifstream stream{path};
    std::istringstream words;
    float memUtil = 0 ;
    long int total{0}, free{0};
    if(stream){
        std::getline(stream,line);
        words.str(line);
        words>> temp >> total ;
        words.clear();
        std::getline(stream,line);
        words.str(line);
        words >> temp >> free ;
        stream.close();
    }
    memUtil = 1 - (float)(free)/total ;

  return memUtil; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
    std::string path{ LinuxParser::kProcDirectory  + LinuxParser::kUptimeFilename} ;
    std::string line ;
    std::string temp ;
    std::ifstream stream{path};
    std::istringstream words;
    long int withSus{0}, withoutSus{0};
    if(stream){
        std::getline(stream,line);
        words.str(line);
        words>> withoutSus>> temp >> withSus ;
        stream.close();
    }
  return (withoutSus);//sysconf(_SC_CLK_TCK); 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
    std::string path{ LinuxParser::kProcDirectory + LinuxParser::kStatFilename} ;
    std::string line ;
    std::string temp ;
    std::string result ;
    std::ifstream stream{path};
    std::istringstream words;
    int totalProc = 0 ;
    if(stream){
        while(std::getline(stream,line)){
            words.str(line) ;
            words >> temp ;
            if(temp == "processes"){
                words >> totalProc ;
            }
            words.clear();
        }
    }
  stream.close();
  return  totalProc; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
    std::string path{ LinuxParser::kProcDirectory + LinuxParser::kStatFilename} ;
    std::string line ;
    std::string temp ;
    std::string result ;
    std::ifstream stream{path};
    std::istringstream words;
    int runningProc = 0 ;
    if(stream){
        while(std::getline(stream,line)){
            words.str(line) ;
            words >> temp ;
            if(temp == "procs_running"){
                words >> runningProc ;
            }
            words.clear();
        }
    }
  stream.close();
  return  runningProc; 
}

