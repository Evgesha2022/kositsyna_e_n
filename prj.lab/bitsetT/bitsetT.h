#pragma once
#ifndef BITSETT_BITSETT_H_20220309
#define  BITSETT_ BITSETT_H_20220309
#include <iostream>
#include <sstream>
#include <vector>
using T = int64_t;
template<typename T>
class BitsetT
{
public:
    class BitHolder
    {
    public:
        friend class BitsetT;
        BitHolder& operator=(const bool rhs);
        BitHolder() = default;
        ~BitHolder() = default;
        operator bool()const;
        explicit BitHolder(BitsetT& data_,T position = 0);
        T& bits;
        T posit = 0;
    };

    explicit BitsetT(const T size = 0, const bool filler = false);
    //BitsetT(const std::string& n_format);
    BitsetT(const BitsetT& copy);

    BitsetT<T>& operator= (const BitsetT& rhs);
    BitsetT<T>& operator&= (const BitsetT& rhs);
    BitsetT& operator|= (const BitsetT& rhs);
    BitsetT& operator^= (const BitsetT& rhs);
    BitsetT& operator<<= (const T rhs);
    BitsetT& operator>>= (const T rhs);

    ~BitsetT();
    BitsetT operator~() const;

    bool operator==(const BitsetT& rhs) const;
    bool operator!=(const BitsetT& rhs) const;

    bool operator[](const int position)const;
    BitHolder operator[](const int position);

    T size() const;
    void resize(const int64_t size, const bool filler);

    std::ostream& WriteTo(std::ostream& ostream) const;
    std::istream& ReadFrom(std::istream& istream);

    void Swap(BitsetT& other) noexcept;
    static const T Cluster_Number = { 8 };
    static const T Cluster_Size = { sizeof(T) * Cluster_Number };
    T size_l = { 0 };
    std::vector<T> data_;
    T clusters_number = { 0 };
};

BitsetT<T> operator&(const BitsetT<T>& lhs, const BitsetT<T>& rhs);
BitsetT<T> operator|(const BitsetT<T>& lhs, const BitsetT<T>& rhs);
BitsetT<T> operator^(const BitsetT<T>& lhs, const BitsetT<T>& rhs);
BitsetT<T> operator<<(const BitsetT<T>& lhs, const T rhs);
BitsetT<T> operator>>(const BitsetT<T>& lhs, const T rhs);

std::ostream& operator<<(std::ostream& ostream, const BitsetT<T>& data);
std::istream& operator>>(std::istream& istream, BitsetT<T>& data);

template <typename T>
BitsetT<T>::BitHolder::BitHolder(BitsetT& BitsetT, T position)
    : bits(BitsetT.data_[posit / Cluster_Size]),
    posit(position% Cluster_Size)
{
    if (posit < 0) { throw(std::invalid_argument("BitHolder error : negative position is undefined")); }
    return;
}
template <typename T>
typename BitsetT<T>::BitHolder& BitsetT<T>::BitHolder::operator= (const bool rhs)
{
    T x = (T(1) << (*this).posit);
    if (rhs == true) (*this).bits |= x;
    else (*this).bits &= ~(x);
    return *this;
}
template <typename T>
BitsetT<T>::BitHolder::operator bool() const
{
    return bits >> (posit % (Cluster_Size)) & 1;
}
template <typename T>
BitsetT<T>::BitsetT(const T size, const bool filler)
    : data_(std::vector<T>((size + Cluster_Size - 1) / Cluster_Size))
    , size_l(0)
{
    if (size < 0) throw(std::invalid_argument("BitsetT error: BitsetT size can not be negative"));

    data_.resize(size);
    if (filler)
    {
        for (auto i = 0; i < size_l; ++i)
            data_[i] = 1;
    }
    return;
}
/*BitsetT<T>::BitsetT(const std::string& n_format)
    : data_(std::vector<T>(0)), size_l(0)
{
    for (int64_t i = 0; i < size_l; ++i)
    {
        if (n_format[size_l - i - 1] != '0' && n_format[size_l - i - 1] != '1')
        {
            throw(std::invalid_argument("BitsetT error: BitsetT must consist of 0 or 1 only"));
        }
        //data[i / Cluster_Size] |= n_format[];
    }
    return;
}*/
template <typename T>
BitsetT<T>::BitsetT(const BitsetT<T>& copy)
{
    size_l = copy.size_l;
    data_.resize(copy.data_.size());
}
template <typename T>
BitsetT<T>& BitsetT<T> ::  operator= (const BitsetT& rhs)
{
    BitsetT tmp(rhs);
    this->Swap(tmp);
    return *this;
}
template <typename T>
BitsetT<T>& BitsetT <T>:: operator&= (const BitsetT& rhs)
{
    if ((*this).size() != rhs.size()) throw(std::logic_error("BitsetT error: sizes of operands do not match"));
    for (int64_t i = 0; i < data_.size(); ++i)
    {
        data_[i] &= rhs.data_[i];
    }
    return *this;
}
template <typename T>
BitsetT<T>& BitsetT <T>:: operator|= (const BitsetT& rhs)
{
    if ((*this).size() != rhs.size()) throw(std::logic_error("BitsetT error: sizes of operands do not match"));
    for (int64_t i = 0; i < data_.size(); ++i)
    {
        data_[i] |= rhs.data_[i];
    }
    return *this;
}
template <typename T>
BitsetT<T>& BitsetT<T> :: operator^= (const BitsetT& rhs)
{
    if ((*this).size() != rhs.size()) throw(std::logic_error("BitsetT error: sizes of operands do not match"));
    for (int64_t i = 0; i < data_.size(); ++i)
    {
        data_[i] ^= rhs.data_[i];
    }
    return *this;
}
template <typename T>
BitsetT<T>& BitsetT <T>:: operator<<= (const T rhs)
{
    if (rhs < 0) throw(std::invalid_argument("BitsetT error : bitwise shift by negative count is undefined"));
    int64_t cluster_otncdv = (rhs / Cluster_Size);
    int64_t bit_posincl = (rhs % Cluster_Size);
    {
        int64_t i = clusters_number - 1;
        for (; i > cluster_otncdv; --i)
        {
            data_[i] = (data_[i - cluster_otncdv] << bit_posincl);
            data_[i] |= (data_[i - cluster_otncdv - 1] >> (sizeof(int64_t) - bit_posincl));
        }
        data_[i] = data_[i - 1] << bit_posincl;
        i--;
        for (; i >= 0; --i)
        {
            data_[i] = 0;
        }
        return *this;
    }
}
template <typename T>
BitsetT<T>& BitsetT <T>:: operator>>= (const T rhs)
{
    if (rhs < 0) throw(std::invalid_argument("BitsetT error : bitwise shift by negative count is undefined"));
    int64_t cluster_dop = (rhs / Cluster_Size);
    int64_t bit_pos = (rhs % Cluster_Size);
    {
        int64_t i = 0;
        for (; i < clusters_number - cluster_dop - 1; ++i)
        {
            data_[i] = data_[i + cluster_dop] >> bit_pos;
            data_[i] |= data_[i + cluster_dop + 1] << (Cluster_Size - bit_pos);
        }
        data_[i] = data_[i + cluster_dop] >> bit_pos;
        i--;
        for (; i < clusters_number; ++i)
        {
            data_[i] = 0;
        }
    }
    return *this;
}
template<typename T>
BitsetT<T>::~BitsetT() = default;
template <typename T>
BitsetT<T> BitsetT<T>::operator~() const
{
    BitsetT lhs(*this);
    for (int64_t i = 0; i < lhs.data_.size(); ++i)
    {
        lhs.data_[i] = ~(lhs.data_[i]);
    }
    if (size_l != Cluster_Number * Cluster_Size)
    {
        ///???
    }
    return *this;
}
template <typename T>
bool   BitsetT<T>::operator==(const BitsetT & rhs) const
{
    if ((*this).size() != rhs.size()) { return false; }
    for (int64_t i = 0; i < rhs.size(); ++i)
    {
        if ((*this)[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}
template<typename T>
bool BitsetT<T>::operator!=(const BitsetT<T> &rhs) const
{
    return !((*this) == rhs);
}
template<typename T>
bool BitsetT<T>::operator[](const int position)const
{
    if (position<0 || position>=(*this).size()) throw(std::out_of_range("BitsetT error : index out of range"));
    return (this->data_[position / Cluster_Size] >> (position % Cluster_Size) & 1);
}
template <typename T>
typename BitsetT<T>::BitHolder BitsetT<T>::operator[](const int position)
{
    if (position<0 || position>=(*this).size()) throw(std::out_of_range("BitsetT error : index out of range"));
    return BitHolder((*this), position);

}
template<typename T>
T BitsetT<T>::size() const
{
    return size_l;
}
template <typename T>
void BitsetT<T>::resize(const int64_t size, const bool filler)
{
    BitsetT tmp(size, filler);
    this->Swap(tmp);
    return;
}
template <typename T>
std::ostream& BitsetT<T>::WriteTo(std::ostream & ostream) const
{
    for (int i = size_l - 1; i >= 0; --i)
    {
        ostream << ((data_[i / Cluster_Size] >> i % Cluster_Size) & 1);
    }
    return (ostream);
}
template <typename T>
std::istream& BitsetT<T>::ReadFrom(std::istream & istream)
{
    std::string potok(" ");
    while (istream.peek() == '0' || istream.peek() == '1')
    {
        potok.push_back(istream.get());
    }
    if (potok.size() > 0)
    {
        data_.insert(data_.begin(), potok.begin(), potok.end());
    }
    else
    {
        istream.setstate(std::ios_base::failbit);
    }
    return istream;
}
template<typename T>
void BitsetT<T>::Swap(BitsetT & other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_l, other.size_l);
    std::swap(clusters_number, other.clusters_number);
    return;
}template <typename T>
BitsetT<T> operator&(const BitsetT<T>&rhs, const  BitsetT<T>&lhs)
{
    BitSet<T> rhs_copy(rhs);
    return rhs_copy &= lhs;
}
template <typename T>
BitsetT<T> operator|(const BitsetT<T>&rhs, const  BitsetT<T>&lhs)
{
    BitSet<T> rhs_copy(rhs);
    return rhs_copy |= lhs;
}
template <typename T>
BitsetT<T> operator^(const BitsetT<T>&rhs, const  BitsetT<T>&lhs)
{
    BitSet<T> rhs_copy(rhs);
    return rhs_copy ^= lhs;
}
template <typename T>
BitsetT<T> operator<<(const BitsetT<T>&lhs, const T rhs)
{
    BitSet<T> lhs_copy(lhs);
    return lhs_copy <<= rhs;
}
template <typename T>
BitsetT<T> operator>>(const BitsetT<T>&lhs, const T rhs)
{
    BitSet<T> lhs_copy(lhs);
    return lhs_copy >>= rhs;
}
template <typename T>
std::ostream& operator<<(std::ostream & ostream, const BitsetT<T>&data)
{
    return data.WriteTo(ostream);
}
template <typename T>
std::istream& operator>>(std::istream & istream, BitsetT<T>&data)
{
    return data.ReadFrom(istream);
}
#endif
