#include <cmath>
#include <matplot/matplot.h>
#include <stdio.h>
#include<iostream>
#include <stdlib.h>
#include<vector>
#include<chrono>
#include <unordered_set>
#include <algorithm>  
#include <iterator>
using namespace std;
int n = 1;
int m = 1;
std::vector<int> x;
std::vector<int> as(200001, -1);

int create_m()
{
    if (m <= 20001)
    {
        m = ceil(n * 1.5);
    }
    return m;
}

std::vector<double> rv;
std::vector<int> a;
std::vector<int> use;
double all_time_duration(void f())
{
    auto begin = std::chrono::system_clock::now();
    f();
    auto end = std::chrono::system_clock::now();
    double elapsed_ms = (std::chrono::duration<double, std::milli>(end - begin)).count();
    return elapsed_ms;
}

void reader_1()
{
    ifstream f2("myfile.txt");
    f2 >> n;
    for (int i = 0; i < n; i += 1) 
    {
        int  idx = 0;
        f2 >> idx;
        use.push_back(idx);
    }
    f2.close();
}
double time_duration_reader_1(void f())
{
    auto begin = std::chrono::system_clock::now();
    f();
    auto end = std::chrono::system_clock::now();
    double elapsed_ms = (std::chrono::duration<double, std::milli>(end - begin)).count();
    return elapsed_ms;
}
void stat(std::vector<int>& cheak, bool a)
{
    if (a)
    {
        //option_1(cheak);
    }
    else
    {
        //option_2(cheak);
    }
}
void option_1()
{
    for (int i = 0; i < m; i += 1)
    {
        int  idx = 0;

        as[use[i]] = m - i - 1;

    }
     std::cout << std::distance(as.begin(), std::max_element(as.begin(), as.end())); 
}
void option_2() //data_1 -> use
{
       std::unordered_set<int> unique;
       unique.reserve(200000);
       int idx_unique = m;
       for (int i = m - 1; 0 <= i; i -= 1) 
       {
            if (unique.find(use[i])!=unique.end()) 
            {
                idx_unique = use[i];
                unique.insert(idx_unique);
            }
        }
        std::cout << idx_unique;
    }

std::vector<double> rand_val()
{ 
    
    for (int i = 0; i < m; i++)
    {
        rv.push_back((i + std::rand()) % (n+1));
    }
    x.push_back(rv.size());
    return rv;
}

void files() 
{
    string path = "myfile.txt";
    ofstream f1;	//переменная f1 отвечает за запись в файл
    f1.open(path, std::ios::out | std::ios::in);      //Открываем файл для записи
    if (!f1.is_open()) {
        std::cout << "Ошибка открытия файла" << endl;
    }
    std::vector<double> vals = rand_val();
    f1 << vals.size() << ' ';
    for (auto& i : vals) {
        f1 << i <<' ';
    }
    f1.close();
    //, std::ios::out | std::ios::in
};