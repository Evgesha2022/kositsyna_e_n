#include <iostream>
#include <ostream>
#include <bitset/bitset.h>

Bitset::BitHolder::BitHolder( int position, Bitset& Bitset)
    : bits(Bitset.data_[posit / Cluster_Size]),
    posit(position% Cluster_Size) 
{
    if (posit < 0) { throw(std::invalid_argument("BitHolder error : negative position is undefined")); }
    return;
}

Bitset::BitHolder& Bitset::BitHolder::operator= (const bool rhs)
{
    int64_t x = (int64_t(1) << (*this).posit);
    if (rhs == true) 
        (*this).bits |= x;
    else (*this).bits &= ~(x);
    return *this;
}

Bitset::BitHolder::operator bool() const
{
    return bits >> (posit % (Cluster_Size)) & 1;
}

Bitset::Bitset(const int64_t size, const bool filler) 
    : data_(std::vector<int64_t>((size + Cluster_Size - 1) / Cluster_Size))
    ,size_l(0)
{
    if (size<0) throw(std::invalid_argument("Bitset error: Bitset size can not be negative"));
    data_.resize(size);
    if (size == 0)
    {
     data_.resize(1,0);
    }
    if (filler==true)
    {
        for (int i = 0; i < (*this).size(); i++)
            data_[i] = '1';
    }
    else
    {
        for (int i = 0; i < (*this).size(); i++)
            data_[i] = 0;
    }
}


Bitset::Bitset(const Bitset& copy)

    :data_(copy.data_),
    size_l(copy.size_l)
{
}

Bitset& Bitset ::  operator= (const Bitset& rhs) = default;

Bitset& Bitset :: operator&= (const Bitset& rhs) 
{
    if (size_l != rhs.size_l) throw(std::logic_error("Bitset error: sizes of operands do not match"));
    for (int64_t i = 0; i < data_.size(); i++)
    {
        data_[i] &= rhs.data_[i];
    }
    return *this;
}

Bitset& Bitset :: operator|= (const Bitset& rhs) 
{
    if (size_l != rhs.size_l) throw(std::logic_error("Bitset error: sizes of operands do not match"));
    for (int64_t i = 0; i < data_.size(); i++)
    {
        data_[i] |= rhs.data_[i];
    }
    return *this;
}

Bitset& Bitset :: operator^= (const Bitset& rhs) 
{
    if (size_l != rhs.size_l) throw(std::logic_error("Bitset error: sizes of operands do not match"));
    for (int64_t i = 0; i < data_.size(); i++)
    {
        data_[i] ^= rhs.data_[i];
    }
    return *this;
}

Bitset& Bitset :: operator<<= (const int64_t rhs) 
{
    if (rhs < 0) throw(std::invalid_argument("Bitset error : bitwise shift by negative count is undefined"));
    int64_t cluster_otncdv = (rhs / Cluster_Size);
    int64_t bit_posincl = (rhs % Cluster_Size);
    {
        int64_t i = data_.size() - 1;
        for (; i > cluster_otncdv; --i)
        {
            data_[i] = (data_[i - cluster_otncdv] << bit_posincl);
            data_[i] |= (data_[i - cluster_otncdv - 1] >> (sizeof(int64_t) - bit_posincl));
        }
        data_[i] = data_[i - 1] << bit_posincl;
        i--;
        for(;i>=0;i--)
        { 
            data_[i] = 0;
        }
        return *this;
    }
}
Bitset& Bitset :: operator>>= (const int64_t rhs)
{
    if (rhs < 0) throw(std::invalid_argument("Bitset error : bitwise shift by negative count is undefined"));
    int64_t cluster_dop = (rhs / Cluster_Size);
    int64_t bit_pos = (rhs % Cluster_Size);
    {
        int64_t i = 0;
        for (;i<data_.size()-cluster_dop-1;++i)
        {
            data_[i] = data_[i + cluster_dop] >> bit_pos;
            data_[i] |= data_[i+cluster_dop+1] << (Cluster_Size-bit_pos);
        }
        data_[i] = data_[i + cluster_dop] >> bit_pos;
        i--;
        for (; i < data_.size(); ++i)
        {
            data_[i] = 0;
        }
    }
    return *this;
}



Bitset Bitset::operator~() const
{
    Bitset lhs(*this);
    for (int64_t i = 0; i < lhs.data_.size(); ++i)
    {
        lhs.data_[i] = ~(lhs.data_[i]);
    }
    return lhs;
}

bool   Bitset::operator==(const Bitset& rhs) const
{
    if ((*this).size() != rhs.size()) { return false; }
    for (int i = 0; i < rhs.size(); ++i)
    {
        if ((*this)[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}
bool Bitset::operator!=(const Bitset& rhs) const
{
    return !((*this) == rhs);
}
bool Bitset::operator[](const int64_t position) const
{
    if (position<0 || position>=(*this).size()) throw(std::logic_error("Bitset error : index out of "));
    return ((data_[position/Cluster_Size]>>position%Cluster_Size)&1);
}

Bitset::BitHolder Bitset::operator[](const int64_t position)
{
    if (position<0 || position>=(*this).size()) throw (std::logic_error("Bitset error : index "));
    return BitHolder( position, (*this));
}

int64_t Bitset::size() const
{
    return (*this).size_l;
}
void Bitset::resize(const int64_t size, const bool filler)
{
    if (size < 0) throw(std::invalid_argument("Bitset error: Bitset size can not be negative"));
    int64_t past_size = int64_t((*this).size());
    int64_t new_size= (past_size+Cluster_Size-1) / Cluster_Size;
    data_.resize(new_size);
    size_l = size;
    if (past_size < size_l)
    {
        for (int i = past_size; i < size; ++i)
        {
            (*this)[i] = bool(filler);
        }
    }
}
std::ostream& Bitset::WriteTo(std::ostream& ostream) const
{
    for (int64_t i = size_l - 1; i >= 0; --i)
    {
        ostream << (*this)[i];
    }
    return (ostream);
}
std::istream& Bitset::ReadFrom(std::istream& istream)
{
    std::string potok("");
    while (istream.peek() == '0' || istream.peek() == '1')
    {
        potok.push_back(istream.get());
    }
    if (potok.size() > 0)
    {
        (*this) = Bitset(potok);
      
    }
    else
    {
        istream.setstate(std::ios_base::failbit);
    }
    return istream;
}

Bitset::Bitset(const std::string& normal)
    :data_(std::vector<int64_t>(0)), size_l(0)
{
    Bitset tmp(normal.size());
    for (int i = 0; i < normal.size(); ++i)
        tmp[normal.size() - 1 - i] = ('1' == normal[i]);

    data_ = tmp.data_;
    size_l = tmp.size();
}
Bitset Bitset::operator&(const Bitset& rhs) const
{
    Bitset tmp = *this;
    tmp &= rhs;
    return tmp;
}
Bitset operator|(const Bitset& rhs, const Bitset& lhs)
{
    Bitset rhs_copy(rhs);
    return rhs_copy |= lhs;
}
Bitset operator^(const Bitset& rhs, const Bitset& lhs)
{
    Bitset rhs_copy(rhs);
    return rhs_copy ^= lhs;
}
Bitset operator<<(const Bitset& lhs, const int64_t rhs)
{
    Bitset lhs_copy(lhs);
    return lhs_copy <<= rhs;
}
Bitset operator>>(const Bitset& lhs, const int64_t rhs)
{
    Bitset lhs_copy(lhs);
    return lhs_copy >>= rhs;
}
