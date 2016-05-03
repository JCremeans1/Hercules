#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <time.h>
#include <numeric>
#include <algorithm>
#define JCRAND ((double)rand()/RAND_MAX)

using namespace std;
//GOOD Graph: Average as a function of iteration, finishing population fitness, finishing mu1 sigma1 mu2 sigma2, interesting things


//**********Global Variables**********\\
//************************************\\

string curvefile;
double sumfitness = 0; //This is the temporary holder of the summed fitness prior to average being computed
double average = 0; //This is to calculate the average fitness from all points of a specific mu value of an individual
double x, y; //These are the variables put into the vectors for the x and y inputs
int populationsize = 20; //This the arbitrary population size which can be changed
int k; //This relates to the number of points for input.
int flag = 0;

//**********CLASSES**********\\
//***************************\\

class individual
{
public:

    double mu1; //This is the value for the mode of the normal distribution function.  Each individual has a mu value which is evaluated to find Y values.
    double mu2; //This is for the second mode.  Same as above.
    double sigma1; //This is the standard deviation for the first modes normal distribution.
    double sigma2; //This is the standard deviation for the second mode.
    double ypost; //This is the Y value pulled from the normal distribution function via the above mode and standard deviation
    double fitness; //This is the difference between the known Y values and our guesstimated Y values summed for all points on the curve
    double error; //Unused variable
    double selector; //A thumbs up or down value to tell the program to remove or keep the vector entry.
    double big; //JCJC PARAM\\ This is a multiplier to change the rate at which the values of mu are modified
    double small; //JCJC PARAM\\ This is a multiplier to change the rate at which the values of mu are modified
    double partialfitness; //Used for summing the individual fitnesses to create fitness.
    double SQ1; //This is calculated value for the normal distribution function of curve 1.
    double SQ2; //This is calculated value for the normal distribution function of curve 2.
    double mag1; //This is the magnitude value for the equation of the normal distribution curve one.
    double mag2; //This is the magnitude value for the equation of the normal distribution curve two.

    vector <double> vecx, vecy; //These vectors hold the x and y values of the input from the file read.
    vector <double> vecypost1, vecypost2; //This stores all created Y values for the individual.

    void initialize(); // Sets initial values prior to running the main function.
    void mutate(); // This modifies the values of mu and sigma.
    void evaluate(); // This determines fitness.
    void readfile(); // This reads the file input.
    void downselect(); // This compares fitness to the average and deletes the vector entry if it is below.

};

class population{
public:

    vector<individual> pop;
};

//**********CLASS FUNCTIONS**********\\
//***********************************\\

void individual::readfile()
{
cout<< "Read File: "<< endl;
cout << " " << endl;

ifstream myfile;

myfile.open("curve7.txt");

for (int i = 0; i < 2*k; i++){
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

cout << " " << endl;

cout << "File Read Complete!"<< endl;
cout << " " << endl;
_sleep(300);

//cout<<vecx.size()<< " " << vecy.size() << endl;
//for (int i = 0; i < k; i++){
//cout << vecx.at(i)<< " "<< vecy.at(i) << endl;

//}
cout << "Evolutionary Algorithm Started: " << endl;

cout << " " << endl;

cout << "Please wait while the values are calculated..." << endl;
}

void individual::initialize()
{

    mu1 = int(vecx.at(k-1)/4);
    mu2 = int(vecx.at(k-1)/(4/3));
    sigma1 = 5;
    sigma2 = 10;
    mag1 = int(vecy.at(k-1)/4);
    mag2 = int(vecy.at(k-1)/(4/3));
    ypost = 0;
    fitness = 1;
    error = 0;
    big = 1; //JCJC PARAM
    small = 8; // JCJC PARAM
    partialfitness = 0;
    SQ1 = 0;
    SQ2 = 0;
    mutate();
}


void individual::mutate()
{

    mu1 = (mu1 + (JCRAND - JCRAND)*big);

    mu2 = mu2 + (JCRAND - JCRAND)*big;

    sigma1 = fabs(sigma1 + (JCRAND - JCRAND)*small);

    sigma2 = abs(sigma2 + (JCRAND - JCRAND)*small);

    mag1 = mag1 + (JCRAND - JCRAND);

    mag2 = mag2 + (JCRAND - JCRAND);

}

void individual::evaluate()
{

    for (int i = 0; i < k; i++){

        SQ1 = ((vecx.at(i)-mu1)/sigma1)*((vecx.at(i)-mu1)/sigma1);

        ypost = mag1*exp(-3.1415*SQ1);

        //vecypost1.push_back(ypost);

        SQ2 = ((vecx.at(i)-mu2)/sigma2)*((vecx.at(i)-mu2)/sigma2);

        ypost += mag2*exp(-3.1415*SQ2);

        vecypost1.push_back(ypost/2);

        partialfitness = fabs(vecy.at(i) - ypost);

        fitness  += partialfitness;
    }
}

void individual::downselect(){

    //cout << "The Current Average: " << average << endl;

    if (fitness > average){

        selector = 0;
    }
    else if ( fitness == average){

        selector = 0;
    }
    else{

        selector = 1;
    }
}

//**********MAIN FUNCTION**********\\
//*********************************\\

int main()
{

    cout << "Please Enter the Number of Data Points from you data file: ";
    cin >> k;
    cout << " " << endl;
    cout << "Please Enter your Data File Name Exactly as it is written: ";
    cin >> curvefile;
    cout << " " << endl;

    //curvefile.append(""curvefile, ".txt""");

    population P;

    individual A;

    A.readfile();

    srand(time(NULL));


    for (int i = 0; i < populationsize; i++)
    {

        A.initialize();

        P.pop.push_back(A);

    }

ofstream myfile;

myfile.open ("Average_Fitness.txt");

myfile.clear();

for (int i = 0; i < 5000; i++){

    for (int i = 0; i < P.pop.size(); i++){

        if(P.pop.at(i).fitness < 0.1){

            flag =1;
        }

    }
    if (flag ==1){

        break;
    }

    for (int i = 0; i < P.pop.size(); i++){

        P.pop.at(i).fitness = 0;

        P.pop.at(i).partialfitness = 0;
    }

    for (int i = 0; i < populationsize; i++)
    {
        //This next line acts as a cloning function.

        if (P.pop.size() < populationsize){

            A = P.pop.at(i);

            A.mutate();

            P.pop.push_back(A);

        }

    }

    for (int i = 0; i < populationsize; i++)
    {
        P.pop.at(i).vecypost1.clear();

        P.pop.at(i).vecypost2.clear();

        P.pop.at(i).evaluate();

    }

//************Calculating Average value of fitness for sorting**********\\
//**********************************************************************\\

    average = 0;
    sumfitness = 0;

    for (int i = 0; i < P.pop.size(); i++){

        sumfitness = sumfitness + P.pop.at(i).fitness;

    }

    average = sumfitness / P.pop.size();

    myfile << average << " \n";

    for (int i = 0; i < P.pop.size(); i++)
    {

        P.pop.at(i).downselect();

        if (P.pop.at(i).selector == 0){

            P.pop.erase(P.pop.begin()+i);

                if ( i > 0){

                    i--;
            }

        }

    }

}
cout << "Ending Population Size is: " << P.pop.size() << endl;

for (int i = 0; i < P.pop.size(); i++){

    cout << "Fitness for Element " << i << ": " << P.pop.at(i).fitness << endl;


}
double lowfitness = P.pop.at(0).fitness >= P.pop.at(1).fitness?P.pop.at(1).fitness:P.pop.at(0).fitness;

for (int i = 2; i < P.pop.size(); i++){


    if (lowfitness > P.pop.at(i).fitness){

        lowfitness = P.pop.at(i).fitness;
    }

}
ofstream myfile1;

myfile1.open ("Ypost.txt");

myfile1.clear();

ofstream myfile2;

myfile2.open ("Ypost2.txt");

myfile2.clear();



for (int i = 0; i < P.pop.size(); i++){

    //cout << "Sigma1: " << P.pop.at(i).sigma1 << endl;
    //cout << " " << endl;

        if (P.pop.at(i).fitness == lowfitness){

            for (int j = 0; j < P.pop.at(i).vecypost1.size(); j++){

                myfile1 << P.pop.at(i).vecypost1.at(j)<< " \n";

                cout << "Created Y value of Curve One for Element " << j << ": " << P.pop.at(i).vecypost1.at(j) << endl;
            }
            for (int j = 0; j < P.pop.at(i).vecypost2.size(); j++){

                myfile2 << P.pop.at(i).vecypost2.at(j)<< " \n";

                cout << "Created Y value of Curve Two for Element " << j << ": " << P.pop.at(i).vecypost2.at(j) << endl;
        }
    }

    else {

        P.pop.at(i).vecypost1.clear();

        P.pop.at(i).vecypost2.clear();

    }

}

myfile.close();

myfile1.close();

cout << " " << endl;
cout << "The Lowest Generated Fitenss: " << lowfitness << endl;
cout << "Please See the Output File ""Sample Data"" for information!" << endl;

    system("PAUSE");
    return 0;


}








