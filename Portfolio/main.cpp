#include <stdio.h>
#include <iostream>
#include <Python.h>
#include<stdlib.h>
#include "stock.cpp"
#include "algorithms/OLS.cpp"
#include "portfolio.cpp"
#include "stock_list.cpp"
#include <string>
#include <time.h>
#define STOCK_SIZE 100 
#define PAGE_LENGTH 25
#define DEFAULT 1
using namespace std;

void python_rip(string);
void prev_csv_rip(stock);
void current_csv_rip(string, portfolio);
int main(int argc, char* argv[])
{
/*stock delcaration order stock
example
declaration name(stock symbol, current price, industry code)
stock IBM(IBM, 185.89, 2);

portfolio declaration order
example 
delcation name (# of stocks in portfolio, industry code)
*/
srand(time(NULL));

stock IBM("IBM", 185.99, 2);
cout <<IBM.get_cp()<<endl;
double Sap[100];

for(int i = 0; i < STOCK_SIZE; i++)
{
IBM.price_history[i] = rand() % 30 + 180;
}
for(int i = 0; i < STOCK_SIZE; i++)
{
Sap[i] = rand() % 60 + 160;
}
/*
for( int i = 0; i <STOCK_SIZE; i++)
{
cout <<IBM.price_history[i]<<endl;
}
*/

OLS IBM_OLS;
IBM_OLS.sum(IBM.price_history);
IBM_OLS.dot(IBM.price_history,Sap);
IBM_OLS.regression(IBM.price_history,Sap);
portfolio tech(2, 2);
cout<<"sum:"<<IBM_OLS.get_sum()<<" dot:"<<IBM_OLS.get_dot()<<endl;
cout<<"beta:"<<IBM_OLS.get_beta()<< "alpha:" << IBM_OLS.get_alpha()<<endl;
stock_list NYSE("NYSE");
string python_sub = NYSE.get_python();
int port_length = NYSE.get_port_length();
portfolio user_port(PAGE_LENGTH,DEFAULT);
//Removes from Stock List Class and Makes Local Portfolio
user_port = NYSE.get_port(); 
for (int i = 0; i < port_length ; i++)
    {
    cout <<"Local Port"<<endl;
    cout << user_port.group[i].get_name()<<endl;
    }
cout <<"Form for Python Submission "<< python_sub <<endl;
python_rip(python_sub);
current_csv_rip(python_sub, user_port);
for(int i = 0; i < port_length; i++)
    {
    cout <<user_port.group[i].get_cp()<<endl;
    }
for(int i = 0; i<port_length; i++)
    {
    prev_csv_rip(user_port.group[i]);
    }
/*
char * info[3];
info[0] = "IBM";
info[1] = "10";
info[2] = "45";
*/
//cout << info[0] <<endl;
setenv("PYTHONPATH",".",1);
PyObject *pName, *pModule, *pArgs, *pFunc, *pCall;
Py_Initialize();
//Py_INCREF(pName);
//Py_INCREF(pModule);
//Py_INCREF(pFunc);
//pName = PyString_FromString((char*)"simple_plot");
pName = PyString_FromString((char*)"simple_plot");
pModule = PyImport_Import(pName);
PyObject_Print(pModule, stdout, 0);
//pFunc = PyObject_GetAttrString(pModule, (char*)"sim_plot");
pFunc = PyObject_GetAttrString(pModule, (char*)"sim_plot");
string python_string = IBM.get_name();
pArgs = PyTuple_Pack(3,PyString_FromString(python_string.c_str()), PyFloat_FromDouble(IBM_OLS.get_beta()), PyFloat_FromDouble(IBM_OLS.get_alpha()));
pCall = PyObject_CallObject(pFunc, pArgs);
//PySys_SetArgv(argc, argv);
//PyRun_SimpleFile(file, "simple_plot.py");
Py_Finalize();

cout <<"One More Time"<<endl;
}

void python_rip(string python_sub)
{
setenv("PYTHONPATH",".",1);
PyObject *pName, *pModule, *pArgs, *pFunc, *pCall;
Py_Initialize();
pName = PyString_FromString((char*)"data");
pModule = PyImport_Import(pName);
PyObject_Print(pModule, stdout, 0);
pFunc = PyObject_GetAttrString(pModule, (char*)"data");
pArgs = PyTuple_Pack(1,PyString_FromString(python_sub.c_str()));
pCall = PyObject_CallObject(pFunc, pArgs);
Py_Finalize();
}
void prev_csv_rip(stock local)
    {
    setenv("PYTHONPATH",".",1);
    PyObject *pName, *pModule, *pArgs, *pFunc, *pCall;
    Py_Initialize();
    pName = PyString_FromString((char*)"prev_data");
    pModule = PyImport_Import(pName);
    PyObject_Print(pModule, stdout, 0);
    pFunc = PyObject_GetAttrString(pModule, (char*)"data_prev");
    pArgs = PyTuple_Pack(1,PyString_FromString(local.get_symbol().c_str()));
    pCall = PyObject_CallObject(pFunc, pArgs);
    Py_Finalize();
    string submission; 
    submission = local.get_symbol() + ".csv";
    
    std::ifstream inFile(submission.c_str());
    string name;
    int iter = 0; 
    string cp; 
    while(getline(inFile,name, ','))
    {
    cout <<iter<< " Times Through"<<endl;
    getline(inFile, cp);
    if (cp != "N/A")
    {
    local.price_history[iter] = stod(cp); 
    }
    else
    {
    local.price_history[iter] = 0;
    }
    iter++;
    if(iter == STOCK_SIZE -1)
    {
    break;
    //prevents seg fault
    }
    }
cout <<"PRICE HISTORY UPDATED" <<endl;
}
void current_csv_rip(string python_sub, portfolio user_port)
{
int line_number = 0;
string line;
string submission;
submission = python_sub +".csv";
std::ifstream inFile(submission.c_str());
//Allows for strings to be passed
while(getline(inFile,line))
    {
    line_number++;

    }   
inFile.close();
inFile.open(submission.c_str());
int iter = 0;
string name;
string cp;
double current_price;
//array technically begin at list[1]-list[line_number]
while(getline(inFile,name, ','))
    {
    cout <<iter<< " Times Through"<<endl;
    user_port.group[iter].set_name(name);
    getline(inFile, cp);
    if (cp != "N/A")
    {
    current_price = stod(cp); 
    }
    else
    {
    current_price = 0;
    }
    user_port.group[iter].set_cp(current_price);
    //cout << "Company Name: "<<list[iter].name<<endl;
    //cout <<"Ticker: " <<list[iter].symbol <<endl;
    iter++;
    if(iter == line_number)
    {
    break;
    //prevents seg fault
    }
}
cout <<"PORTFOLIO SUCCUESSFULLY UPDATED TO CURRENT PRICE"<<endl;
}
