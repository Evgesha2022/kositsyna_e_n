#include <cmath>
#include <matplot/matplot.h>
#include <stdio.h>
#include<main/main.h>
#include <stdlib.h>
#include <ctime> 
#include<vector>
#include<fstream> 
////#include <unistd.h>
//std::vector<std::pair<size_t, size_t>> get_edges();

using namespace matplot;

int main() {
    string path = "graph_1";
    string path1 = "graph_1";
    m = create_m();
    std::vector< double> y;
     
    for (int i = 0; i < 1000; i++)
    {
        files();
        y.push_back(time_duration_reader_1(reader_1) /n);
    }
    std::vector< double> y1;
    
    plot(x, y);
    show();
    save("graph_1.png");
    save("graph_1.jpg");

    for (int i = 0; i < 1000; i++)
    {
        y1.push_back(all_time_duration(option_1) / n);
    }
    plot(x, y1);
    show();
    save("graph_2.png");
    save("graph_2.jpg");
    std::vector< double> y2;
    for (int i = 0; i < 1000; i++)
    {
        y2.push_back(all_time_duration(option_2) / n);
    }
    plot(x, y2);
    show();
    save("graph_3.png");
    save("graph_3.jpg");
    string pathс = "Косицына_Евгения_БПМ-21-3.md";
    std::ofstream f;	//переменная f1 отвечает за запись в файл
    f.open(pathс);      //Открываем файл для записи
    if (!f.is_open()) 
    {
        std::cout << "Ошибка открытия файла" << endl;
    }
    f << "Ссылка на github" << "https://github.com/Evgesha2022/kositsyna_e_n" << endl;
    f << "График зависимости t/n от n : n- набор номеров столовых " << endl;
     f << "Расчет значений о скорости считывания данных" << std::endl;
     f << "![[graph_1.jpg]]"<<std::endl;
     f << "Расчет значений о выполнении расчетов Вариантом программы 1" << std::endl;
     f << "![[graph_2.jpg]]"<<std::endl;
     f << "Расчет значений о выполнении расчетов Вариантом программы 2" << std::endl;
     f << "![[graph_3.jpg]]"<<std::endl;
    f.close();
    return 0;
}
