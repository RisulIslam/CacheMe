//
// Created by Shafeey on 11/11/2016.
//

#ifndef CACHESIM_CACHE_H
#define CACHESIM_CACHE_H


#include <cstdint>
#include <vector>
#include <list>

class CacheLine {
public:
    CacheLine(uint32_t tag);

    uint32_t tag;

    bool operator==(const CacheLine &rhs) const;
    bool operator!=(const CacheLine &rhs) const;
};

class Cache {
    uint32_t block_size;
    uint32_t num_ways;
    uint32_t num_sets;

    uint32_t m, n, s, b;
    uint32_t index_mask;
    uint32_t tag_mask;

public:
    std::vector<std::list<CacheLine>> cache_sets;

    bool access(uint32_t address);
    Cache(uint32_t cache_size, uint32_t block_size, uint32_t num_ways);
};


#endif //CACHESIM_CACHE_H
