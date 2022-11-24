#pragma once
#ifndef BITSET_BITSET_H_20220309
#define  BITSET_ BITSET_H_20220309
#include <iostream>
#include <sstream>
#include <vector>


class Bitset
{
public:
    class BitHolder
    {

    public:

        friend class Bitset;
        BitHolder& operator=(const bool rhs);
        BitHolder() = default;
        ~BitHolder() = default;
        operator bool()const;
        explicit BitHolder( int position , Bitset& data_);
        int64_t& bits;
        int64_t  posit = 0;

    };
    explicit Bitset(const int64_t size = 0, const bool filler = false);
    Bitset(const std::string& n_format);
    Bitset(const Bitset& copy);

    Bitset& operator= (const Bitset& rhs);
    Bitset& operator&= (const Bitset& rhs);
    Bitset& operator|= (const Bitset& rhs);
    Bitset& operator^= (const Bitset& rhs);
    Bitset& operator<<= (const int64_t rhs);
    Bitset& operator>>= (const int64_t rhs);

    ~Bitset() =  default;
    Bitset operator~() const;
    
    bool operator==(const Bitset& rhs) const;
    bool operator!=(const Bitset& rhs) const;

    bool operator[](const int64_t position)const; 
    BitHolder operator[](const int64_t position);

    int64_t size() const;
    void resize(const int64_t size, const bool filler=false);

    std::ostream& WriteTo(std::ostream& ostream) const;
    std::istream& ReadFrom(std::istream& istream);

    Bitset operator&(const Bitset& lhs) const;

static std::string establ()
{
    return "B";
}

private:
    static const int64_t Cluster_Number={8};
    static const int Cluster_Size = sizeof(int64_t)*8;
    int64_t size_l = { 0 };
    std::vector<int64_t> data_;
};


Bitset operator|(const Bitset& lhs, const Bitset& rhs);
Bitset operator^(const Bitset& lhs, const Bitset& rhs);
Bitset operator<<(const Bitset& lhs, const int64_t rhs);
Bitset operator>>(const Bitset& lhs, const int64_t rhs);

inline std::ostream& operator<<(std::ostream& ostream, const Bitset& rhs)
{
    return rhs.WriteTo(ostream);
}
inline std::istream& operator>>(std::istream& istream, Bitset& rhs)
{
    return rhs.ReadFrom(istream);
}

//std::ostream& WriteTo(std::ostream& ostrm, const Bitseti::Format&)
//{
//    ostrm << Bitset::establ << std::endl;
//    return ostrm;
//}
//std::istream& ReadFrom(std::istream& ostrm, const  Bitseti::Format&)
//{
//    return ostrm;
//}
#endif
