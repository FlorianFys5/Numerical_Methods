#include<iostream>
#include<cmath>
#include<vector>
int main () {
	double x;
    while( std::cin >> x ){
	    std::cout << x <<" "<< std::sin(x) <<" "<< std::cos(x) << std::endl;
	    }
}