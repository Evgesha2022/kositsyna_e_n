#include <sstream>
#include <iostream>

class Set
{
public:
    Set(int* r, int n)
    {
        for (int i = 0; i < this->n; i++)
        {
            this->r[i] = r[i];
        }
    }
    ~Set() = default;

    void zapoln(Set& r, Set& n)
    {
        std::cout << "Введите количество элементов" << std::endl;
        for (int i = 0; i < this->n; i++)
        {
            std::cin >> this->r[i];
        }
    }
    void general(Set& t, Set& rhs)
    {

    }
    void peresech(Set& r, Set& rhs)
    {
        for (int i = 0; i < this->n;)
        {

        }
    }
private:
    int n;
    int* r = new int[n];
};


int main()
{
    int  t2 = 9;
    int  t1 = 8;
    int* num1 = new int[t1];
    int* num2 = new int[t2];
    Set(num2, t2);
    Set(num1, t1);
    Set::zapoln( num2, const &t2);
    Set::zapoln(num1, t1);
    for (int i = 0; i < t1; t1++)
    {
        std::cout << num1[i] << std::endl;
    }
    return 0;

}