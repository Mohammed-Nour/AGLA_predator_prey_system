#include <iostream>
#include <cstdio>
#include <utility>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

const int numOfPoints = 15;
vector<pair<double,double>> points;
double x,y;

#ifdef WIN32
#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"
#else
#define GNUPLOT_NAME "gnuplot -persist"
#endif

int main()
{
    double v0, k0, alphaOne, betaOne, alphaTwo, betaTwo, timeLimit,V0,K0;
    int counts;
    double vi,ki;

    // Input the parameters
    cin >> V0 >> K0 >> alphaOne >> betaOne >> alphaTwo >> betaTwo >> timeLimit >> counts;

    double dt = timeLimit / counts;

    vector<double>victims(counts+1);
    vector<double>killers(counts+1);
    vector<double>times(counts+1);
    v0= V0 -(alphaTwo/betaTwo);
    k0= K0- (alphaOne/betaOne);
    victims[0] = V0;
    killers[0] = K0;
    times[0] = 0;
    double time;
    for (int i = 1; i <= counts; i++)
    {
        time += dt;
        times[i] =time;
        vi= (v0 * cos(sqrt(alphaOne *alphaTwo)*time)) - (k0* ((sqrt(alphaTwo) *betaOne)/(betaTwo *sqrt(alphaOne)) ) * sin(sqrt(alphaOne *alphaTwo) * time));
        ki = (v0 *((sqrt(alphaOne) *betaTwo)/(betaOne *sqrt(alphaTwo)) )*sin(sqrt(alphaOne *alphaTwo)*time)) + (k0*cos(sqrt(alphaOne *alphaTwo) * time ) );
        vi = vi+(alphaTwo/betaTwo);
        ki = ki+(alphaOne/betaOne);
        victims[i]=vi;
        killers[i] = ki;
    }
#ifdef WIN32
    FILE* pipe = _popen(GNUPLOT_NAME, "w");
#else
    FILE* pipe = popen(GNUPLOT_NAME, "w");
#endif

    if (pipe != NULL)
    {
        fprintf(pipe, "set yrange [%f:%f]\n", 0.0,  100.0);
        fprintf(pipe, "set xrange [%f:%f]\n",  0.0, 30.0);
        fprintf(pipe, "set xlabel 't'\n");
        fprintf(pipe, "set ylabel 'Population'\n");
        fprintf(pipe, "set title 'Predator/Prey Populations Over Time'\n");
        fprintf(pipe, "plot '-' using 1:2 title 'Prey population' with lines, '-' using 1:2 title 'Predator population' with lines\n");

        for (int i = 0; i < killers.size(); i++)
        {
            fprintf(pipe, "%f\t%f\n", times[i], killers[i]);
        }



        fprintf(pipe, "e\n");
        fflush(pipe);

        for (int i = 0; i < victims.size(); i++)
        {
            fprintf(pipe, "%f\t%f\n", times[i], victims[i]);
        }
        fprintf(pipe, "e\n");
        fflush(pipe);
#ifdef WIN32
        _pclose(pipe);
#else
        pclose(pipe);
#endif
    }
    return 0;
}
