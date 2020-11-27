//масштабирование Каирской решетки

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

//запись координат в файл Wolfram Mathematica
void Wolfram_Mathematica_File(vector <double> coorm, vector <double> mxmy, double c);
//запись конфигурации в файл .mfsys для визуализации
void mfsys_conf(vector <double> coorm, vector <double> mxmy, double c);


int main()
{
    vector <double> coor;   //массив координат элементарной ячейки
    vector <double> coorm;  //массив координат для масштабируемой решетки
    vector <double> mm;     //массив магнитных моментов элементарной ячейки
    vector <double> mxmy;   //массив магнитных моментов масштабируемой решетки
    
    
    /** ------ ЗАПОЛНЕНИЕ ЭЛЕМЕНТАРНОЙ ЯЧЕЙКИ КАИРСКОЙ РЕШЕТКИ ------>>>> */
    //готовим 40 элементов под координаты и магнитные моменты
    coor.resize(40);
    mm.resize(40);
    
    double sin60 = sin(M_PI/3);
    
    //параметры решетки
    double a = 472;
    double b = 344;
    double c = 600; //изменяемый параметр решетки 'c'
    
    double l = 300;
    double yd = (2*a-c)/2; //222
    double xd = yd/2; //111
    
    double period = 816;
    
    //координаты
    //coor
    //     X                           Y
    
    //1
    coor[0]=0;                       coor[1]=0;
    coor[2]=xd+b/2;                  coor[3]=yd*sin60;
    coor[4]=xd+b/2;                  coor[5]=-yd*sin60;
    coor[6]=-xd-b/2;                 coor[7]=-yd*sin60;
    coor[8]=-xd-b/2;                 coor[9]=yd*sin60;
    //**
    //2
    coor[10]=0+period;               coor[11]=0;
    coor[12]=yd*sin60+period;        coor[13]=xd+b/2;
    coor[14]=-yd*sin60+period;       coor[15]=xd+b/2;
    coor[16]=-yd*sin60+period;       coor[17]=-xd-b/2;
    coor[18]=yd*sin60+period;        coor[19]=-xd-b/2;
    
    //3
    coor[20]=0;                      coor[21]=0+period;
    coor[22]=yd*sin60;               coor[23]=xd+b/2+period;
    coor[24]=-yd*sin60;              coor[25]=xd+b/2+period;
    coor[26]=-yd*sin60;              coor[27]=-xd-b/2+period;
    coor[28]=yd*sin60;               coor[29]=-xd-b/2+period;
    
    //4
    coor[30]=0+period;               coor[31]=0+period;
    coor[32]=xd+b/2+period;          coor[33]=yd*sin60+period;
    coor[34]=xd+b/2+period;          coor[35]=-yd*sin60+period;
    coor[36]=-xd-b/2+period;         coor[37]=-yd*sin60+period;
    coor[38]=-xd-b/2+period;         coor[39]=yd*sin60+period;
    //*/
    
    //магнитные моменты
    //mm
    //      X            Y
    
    //1
    mm[0]=l*1;          mm[1]=0;
    mm[2]=l*0.5;        mm[3]=l*sin60;
    mm[4]=l*0.5;        mm[5]=l*(-sin60);
    mm[6]=l*(-0.5);     mm[7]=l*(-sin60);
    mm[8]=l*(-0.5);     mm[9]=l*sin60;
    //**
    //2
    mm[10]=0;           mm[11]=l*1;
    mm[12]=l*sin60;     mm[13]=l*0.5;
    mm[14]=l*(-sin60);  mm[15]=l*0.5;
    mm[16]=l*(-sin60);  mm[17]=l*(-0.5);
    mm[18]=l*sin60;     mm[19]=l*(-0.5);
    
    //3
    mm[20]=0;           mm[21]=l*1;
    mm[22]=l*sin60;     mm[23]=l*0.5;
    mm[24]=l*(-sin60);  mm[25]=l*0.5;
    mm[26]=l*(-sin60);  mm[27]=l*(-0.5);
    mm[28]=l*sin60;     mm[29]=l*(-0.5);
    
    //4
    mm[30]=l*1;         mm[31]=0;
    mm[32]=l*0.5;       mm[33]=l*sin60;
    mm[34]=l*0.5;       mm[35]=l*(-sin60);
    mm[36]=l*(-0.5);    mm[37]=l*(-sin60);
    mm[38]=l*(-0.5);    mm[39]=l*sin60;
    //*/
    /** <<<<------------------------------------------------------------- */
    
    
    
    /** ------ МАСШТАБИРОВАНИЕ РЕШЕТКИ ------>>>> */
    //период решетки
    double period_X=period*2;
    double period_Y=period*2;
    
    int numuc; //общее количество элементарных ячеек
    int numucX = 1; //количество элементарных ячеек по оси X
    int numucY = 1; //количество элементарных ячеек по оси Y
    
    //ввод количества элеметарных ячеек с клавиатуры
    //cout<<"Input Number of Unit Cels in linear dimension "<<endl;
    //cin>>numucX;
    //cin>>numucY;
    
    numuc = numucX*numucY;
    for(int y=0; y<numucY; y++)
    {
        for(int x=0; x<numucX; x++)
        {
            for(unsigned int i=0; i<coor.size(); i+=2)
            {
                coorm.push_back(coor[i] + x*period_X);
                coorm.push_back(coor[i+1] + y*period_Y);
                
                mxmy.push_back(mm[i]);
                mxmy.push_back(mm[i+1]);
            }
        }
    }
    /** <<<<------------------------------------- */
    
    
    //вывод информации на экран
    cout << "C = " << c << endl;
    cout << "Number of spins in the unit cell = " << coor.size()/2 << endl;
    cout << "Total number of unit cells = " << numuc << endl;
    cout << "Total number of spins in the system = " << coorm.size()/2 << endl;
    
    
    /** ------ ЗАПИСЬ КОНФИГУРАЦИИ В ФАЙЛ .mfsys ДЛЯ ВИЗУАЛИЗАЦИИ ------ */
    mfsys_conf(coorm, mxmy, c);
    
    /** ------ ЗАПИСЬ КООРДИНАТ В ФАЙЛ Wolfram Mathematica ------ */
    Wolfram_Mathematica_File(coorm, mxmy, c);
    
    
    cout << "\nOk!\n";
    return 0;
}


//ЗАПИСЬ КОНФИГУРАЦИИ В ФАЙЛ .mfsys ДЛЯ ВИЗУАЛИЗАЦИИ
void mfsys_conf(vector <double> coorm, vector <double> mxmy, double c)
{
    ofstream fout;
    string filename = "cairo";
    filename = filename + "_N" + to_string(coorm.size()/2) + "_c" + to_string((int)c) + ".mfsys";
    fout.open(filename.c_str());
    fout.precision(10);
    
    fout<<"[header]"<<endl;
    fout<<"dimensions=2"<<endl;
    fout<<"size="<<coorm.size()/2<<endl;
    fout<<"state=";
    for(unsigned int i=0; i<coorm.size(); i+=2) fout<<"0";
    fout<<endl;
    fout<<"[parts]"<<endl;
    
    for(unsigned int i=0; i<coorm.size(); i+=2)
    {
        fout<<i/2<<"\t"; //порядковый номер
        fout<<coorm[i]<<"\t"<<coorm[i+1]<<"\t"<<"0"<<"\t"; //координаты x,y,z
        fout<<mxmy[i]<<"\t"<<mxmy[i+1]<<"\t"<<"0"<<"\t"; //магнитные моменты mx,my,mz
        fout<<"0"<<endl;
    }
    fout.close();
}


//ЗАПИСЬ КООРДИНАТ В ФАЙЛ Wolfram Mathematica
void Wolfram_Mathematica_File(vector <double> coorm, vector <double> mxmy, double c)
{
    ofstream fout;
    string filename = "cairo";
    filename = filename + "_N" + to_string(coorm.size()/2) + "_c" + to_string((int)c) + ".nb";
    fout.open(filename.c_str());
    fout.precision(10);
    
    fout << "PlotArrays[lst_] := Graphics[Table[Arrow[lst[[x]]], {x, Length[lst]}]]; (*Функция PlotArrays для построения графика *)" << endl;
    
    //запись магнитных моментов в файл Wolfram Mathematica
    fout << "spins = {" << endl;
    fout << "{";
    
    for(unsigned int i=0; i<coorm.size(); i+=2)
    {
        if(i!=coorm.size()-2)
            fout<<"{{"<<coorm[i]-mxmy[i]/2<<","<<coorm[i+1]-mxmy[i+1]/2<<"},{"<<coorm[i]+mxmy[i]/2<<","<<coorm[i+1]+mxmy[i+1]/2<<"}},";
        else
            fout<<"{{"<<coorm[i]-mxmy[i]/2<<","<<coorm[i+1]-mxmy[i+1]/2<<"},{"<<coorm[i]+mxmy[i]/2<<","<<coorm[i+1]+mxmy[i+1]/2<<"}}";
    }
    
    fout << "}" << endl;
    fout << "};" << endl;
    fout << "fig1 = PlotArrays[spins];" << endl;
    
    fout<<endl;
    
    
    fout << "coord = {" << endl;
    fout << "{";
    
    //запись координат центров спинов в файл для Wolfram Mathematica
    for(unsigned int i=0; i<coorm.size(); i+=2)
    {
        if(i!=coorm.size()-2)
            fout<<"{"<<coorm[i]<<","<<coorm[i+1]<<"},";
        else
            fout<<"{"<<coorm[i]<<","<<coorm[i+1]<<"}";
    }
    
    fout << "}" << endl;
    fout << "};" << endl;
    fout << "fig2 = ListPlot[coord, AspectRatio -> 1/2];" << endl;
    
    
    fout << "Show[fig1,fig2]" << endl;
    fout.close();
}
