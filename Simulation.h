//
// Created by Shafeey on 10/30/2016.
//

#ifndef BRANCHPREDICTIONSIMULATOR_SIMULATION_H
#define BRANCHPREDICTIONSIMULATOR_SIMULATION_H


#include <string>
#include <vector>
#include "Cache.h"

class MemAccess {
public:
    MemAccess(char type, uint32_t address);

    char type;
    uint32_t address;
};

class Trace {

public:
    std::vector<MemAccess> trace;
    std::string file_name;

    void load(std::string file_name);

};

class SimStats{
public:
    unsigned long num_hits = 0;
    unsigned long total = 0;
};

class Simulation {
    Cache *pCache;
    Trace *pTrace;
    SimStats stats;

public:
    Simulation(Trace *pTrace, Cache *cache);
    void simulate();

};

#endif //BRANCHPREDICTIONSIMULATOR_SIMULATION_H
