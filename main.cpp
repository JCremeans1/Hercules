#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <time.h>
#include <numeric>
#define JCRAND ((double)rand()/RAND_MAX)

using namespace std;


int k = 9;


class individual

{
public:

    double mu1;
    double mu2;
    double sigma1;
    double sigma2;
    double ypost;
    double fitness;
    double error;

    vector <double> vecx, vecy;

    void initialize();
    void mutate();
    void evaluate();
    void downselect();
    void readfile();

};

class population{
public:

    vector<individual> pop;

    void kill();
    void repop();
    void readfile();

};

int mu1init;
double x, y;

void individual::readfile()
{

ifstream myfile;

myfile.open("curve2.txt");

for (int i = 0; i < 18; i++){
    if ( i%2 == 0 ){
        myfile >> x;
        vecx.push_back(x);
    }

    else{
       myfile >> y;
       vecy.push_back(y);
        }

}
myfile.close();
cout << "Read File" << endl;
cout << " " << endl;

mu1init = vecx.at(2);

for (int i = 0; i < 9; i++){
cout << vecx.at(i)<< " "<< vecy.at(i) << endl;
}
}

void individual::initialize()
{

    mu1 = 0;
    //cout << mu1 << endl;   // Use x values to creat upper and lower bounds / guess
    mu2 = 0;
    sigma1 = 10;
    sigma2 = 10;
    ypost = 0;
    fitness = 0;
    error = 0;
    mutate();
}


void individual::mutate()
{

    double small = 1; /// JCJC PARAM
    mu1 = mu1 + (JCRAND-JCRAND);
    mu2 = mu2 + (JCRAND-JCRAND);
    sigma1 = abs(sigma1 + (JCRAND - JCRAND)*small);
    sigma2 = abs(sigma2 + (JCRAND - JCRAND)*small);
    cout<< mu1 << " " << mu2 << sigma1 << " " << sigma2 << endl;


}

void individual::evaluate()
{
    double partialfitness = 0;
    double SQ;

    for (int i = 0; i < k; i++){
    SQ = ((vecx.at(i)-mu1)/sigma1)*((vecx.at(i)-mu1)/sigma1);
    ypost = (1/sigma1)*exp(-3.1415*SQ);
    //cout << (1/sigma1) << endl;
    //cout << exp(-3.1415*SQ) << endl;

    partialfitness = vecy.at(i) - ypost;
    fitness  = fitness + partialfitness;

    //cout<< "SQ " << SQ << "ypost " << ypost << "partialfitness " << partialfitness << endl;

    cout << "Created Fitness: " << fitness << endl;
    cout << " " << endl;
    }
}

void population::kill(){


}
void individual::downselect(){

double sum = accumulate(P.pop.indivdual.at(abs(fitness)).begin(), abs(fitness).end(), 0);

if (abs(fitness) > (sum / k)){
    cout << "Down" << endl;
    cout << " " << endl;

}

else{
    cout<< "Up" << endl;
    cout << " " << endl;
}


}


int main()
{


    population P;

    individual A;

    A.readfile();

    srand(time(NULL));


    for (int i = 0; i < k; i++)
    {
        cout << "Inittializing " << i << " Element" << endl;
        cout << " " << endl;

        A.initialize();

        P.pop.push_back(A);

    }

    for (int i = 0; i < k; i++){


        //cout<< P.pop.at(i).ypost << endl;

    }

    for (int i = 0; i < k; i++)
    {

        cout << "Cloning " << i << " Element" << endl;
        cout << " " << endl;
//This next line acts as a cloning function.
        A = P.pop.at(i);

        P.pop.push_back(A);

    }

    cout << "Current size of Population Vector: " << P.pop.size()<< endl;
//Evaluate these indivudals via fitness

//Modify them via a loop? I believe this is wrong
    for (int i = 0; i < k; i++)
    {
        cout << "Mutating " << i << " Element" << endl;


        P.pop.at(i).mutate();
        cout << " " << endl;

    }

    for (int i = 0; i < k; i++)
    {
//        double sim;
//        indvidual(A).vecy(i)-individual(A).ypost = sim;
//        individual(A).fitness = individual(A).fitness + sim;
        P.pop.at(i).evaluate();
    }

    for (int i = 0; i < k; i++)
    {
        cout << "Downselecting " << i << " Element" << endl;
        cout << " " << endl;
        //ypost = (1/sigma1)*(individua(A).vecx.at(i)-mu1/sigma1);
        P.pop.at(i).downselect();

    }

    for(int i = 0; i < k; i++){
        cout << individual(A).vecx.at(i) << " " <<  individual(A).vecy.at(i) << endl;


    }


    system("PAUSE");
    return 0;
}

