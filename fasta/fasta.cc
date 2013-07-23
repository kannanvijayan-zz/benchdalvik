
#include <sys/time.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

double DoubleTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (((double)tv.tv_usec) / 1000000);
}

static int last = 42;
static int A = 3877;
static int C = 29573;
static int M = 139968;

double rand(int max) {
  last = (last * A + C) % M;
  return max * last / (double)M;
}

const char *ALU =
  "GGCCGGGCGCGGTGGCTCACGCCTGTAATCCCAGCACTTTGG"
  "GAGGCCGAGGCGGGCGGATCACCTGAGGTCAGGAGTTCGAGA"
  "CCAGCCTGGCCAACATGGTGAAACCCCGTCTCTACTAAAAAT"
  "ACAAAAATTAGCCGGGCGTGGTGGCGCGCGCCTGTAATCCCA"
  "GCTACTCGGGAGGCTGAGGCAGGAGAATCGCTTGAACCCGGG"
  "AGGCGGAGGTTGCAGTGAGCCGAGATCGCGCCACTGCACTCC"
  "AGCCTGGGCGACAGAGCGAGACTCCGTCTCAAAAA";

typedef std::unordered_map<char, double> Table;
static Table *IUB = NULL;
static void InitializeIUB() {
    IUB = new Table();
    (*IUB)['a'] = 0.27;
    (*IUB)['c'] = 0.12;
    (*IUB)['g'] = 0.12;
    (*IUB)['t'] = 0.27;
    (*IUB)['B'] = 0.02;
    (*IUB)['D'] = 0.02;
    (*IUB)['H'] = 0.02;
    (*IUB)['K'] = 0.02;
    (*IUB)['M'] = 0.02;
    (*IUB)['N'] = 0.02;
    (*IUB)['R'] = 0.02;
    (*IUB)['S'] = 0.02;
    (*IUB)['V'] = 0.02;
    (*IUB)['W'] = 0.02;
    (*IUB)['Y'] = 0.02;
}

static Table *HomoSap = NULL;
static void InitializeHomoSap() {
    HomoSap = new Table();
    (*HomoSap)['a'] = 0.3029549426680;
    (*HomoSap)['c'] = 0.1979883004921;
    (*HomoSap)['g'] = 0.1975473066391;
    (*HomoSap)['t'] = 0.3015094502008;
}

void makeCumulative(Table *table) {
    char last = '\0';
    for (auto pair : *table) {
        char c = pair.first;
        if (last) {
            (*table)[c] += (*table)[last];
        }
        last = c;
    }
}

static std::string ret;

void fastaRepeat(int n, std::string seq) {
    int seqi = 0;
    int lenOut = 60;
    while (n > 0) {
        if (n<lenOut) lenOut = n;
        if (seqi + lenOut < seq.length()) {
            ret = seq.substr(seqi, lenOut);
            seqi += lenOut;
        } else {
            std::string s = seq.substr(seqi);
            seqi = lenOut - s.length();
            ret = s + seq.substr(0, seqi);
        }
        n -= lenOut;
    }
}

void fastaRandom(int n, Table *table) {
    std::vector<char> line(60);
    makeCumulative(table);
    while (n>0) {
        if (n<line.size()) line = std::vector<char>(n);
        for (int i=0; i<line.size(); i++) {
            double r = rand(1);
            for (auto pair : *table) {
                char c = pair.first;
                if (r < (*table)[c]) {
                    line[i] = c;
                    break;
                }
            }
        }
        ret = std::string(line.begin(), line.end());
        n -= line.size();
    }
}

void runFasta() {
    int count = 7;
    fastaRepeat(2*count*100000, ALU);
    fastaRandom(3*count*1000, IUB);
    fastaRandom(5*count*1000, HomoSap);
}

int main() {
    InitializeIUB();
    InitializeHomoSap();
    double d1 = DoubleTime();
    for (int i = 0; i < 10; i++) {
        runFasta();
    }
    double d2 = DoubleTime();
    std::cerr << "CXX TIME: " << (d2 - d1) << " (count=" << ret << ")" << std::endl;
    return 0;
}
