#pragma once
#ifndef  BITSETI_BITSETI_H_20220309
#define BITSETI_BITSETI_H_20220309
#include <iostream>
#include <sstream>
#include <vector>
#include <bitset/bitset.h>
class BitSeti
{
public:
    enum class Format
    {
    Bin,
    Txt,
    };
    int num=0;
    virtual std::istream& ReadFrom(std::istream& ostrm, const Format&) ;
    virtual std::ostream& WriteTo(std::ostream& ostrm, const Format&) const;
    BitSeti* ReadBitSetFrom(std::iostream& s);
    int *ptrs = new int [num];
    
};

class BitSett :  public BitSeti
{
//#include <bitsetT/bitsetT.h>
    static const int bitsett;

};
std::istream& BitSeti::ReadFrom(std::istream& istrm, const Format&) { return istrm; }
std::ostream& BitSeti::WriteTo(std::ostream& ostrm, const Format&) const { return ostrm; }

class BitSet : public BitSeti
{

    static const int bitset;
};

class  BitSetP
{
    ~BitSetP(){};
}
#endif 
