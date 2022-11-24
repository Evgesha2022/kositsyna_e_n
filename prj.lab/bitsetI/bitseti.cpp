#include<iostream>
#include<sstream>
#include <bitsetI/bitseti.h>
enum class Format
{
    Bin,
    Txt,
};

BitSeti* BitSeti:: ReadBitSetFrom(std::iostream& ostrm)
{
    switch (char r = ostrm.get())
    {
    case 'B':
        //potok.push_back(s.get());//c пробелами разобраться 
        num++;
        int b = ostrm.get();
        char *g  =  new char [b];
        ostrm.get(g, b, ' ');
        ptrs[num - 1] = *g;//???
        break;
    case 'T':
        BitSett ostrm;
        break;
        /* case D:
             break;*/

    }
    return;
}