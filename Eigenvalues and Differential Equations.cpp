#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

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
    cout<<"t: \n";
    cout << fixed<<setprecision(2);
    for (int i = 0; i <= counts; i++)
    {
        cout<<times[i]<<" ";
    }
    cout<<endl;
    cout<<"v: \n";
    cout << fixed<<setprecision(2);
    for (int i = 0; i <= counts; i++)
    {
        cout<<victims[i]<<" ";
    }
    cout<<endl;
    cout<<"k: \n";
    cout << fixed<<setprecision(2);
    for (int i = 0; i <= counts; i++)
    {
        cout<<killers[i]<<" ";
    }

    return 0;
}
