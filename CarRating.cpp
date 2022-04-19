//CarRating.cpp - a program to sort cars by various criteria
//Documentation for STL algorithms can be found at: http://www.cplusplus.com/reference/algorithm/
//and https://www.cplusplus.com/reference/numeric/
//Documentation for STL containters can be found at: http://www.cplusplus.com/reference/stl/

#include <algorithm>
#include <iostream>
#include <forward_list>
#include <numeric>//accumulate
#include <vector>
#include <string.h>
using namespace std;


double calcRating(double fuelEfficiency,double reliability,double horsePower){
	return  2.0*(reliability-4.1) + 2.0*(12.1-fuelEfficiency) + (horsePower-130.0)/37.0;
}

struct CarRating {
	std::string name;
	std::string country;
	double reliability;
	double fuelEfficiency;
	double horsePower;
};

void processCars(vector<CarRating>& car) {
	//Task 1 - Sort and print out all cars in order of their reliability rating (higher is better).
	{
		//http://www.cplusplus.com/reference/algorithm/sort/ //for sorting
		sort(car.begin(),car.end(),[](const CarRating& tempCar1 ,const CarRating& tempCar2)->bool{
			return tempCar1.reliability>tempCar2.reliability;
		});
		//http://www.cplusplus.com/reference/algorithm/for_each/ //for printing
		for_each(car.begin(),car.end(),[](const CarRating& temp){
			cout << temp.name << ", " << temp.country << "," <<"Reliability "<<temp.reliability<< endl;

		});
		cout<<endl;
	}
	//Task 2 - Sort and print out all cars in order of their fuel efficiency (lower is better).
	{
		sort(car.begin(),car.end(),[](const CarRating& tempCar1 ,const CarRating& tempCar2)->bool{
			return tempCar1.fuelEfficiency<tempCar2.fuelEfficiency;
		});
		for_each(car.begin(),car.end(),[](const CarRating& temp){
			cout << temp.name << ", " << temp.country <<"Fuel efficiency :"<<temp.fuelEfficiency<< "." << endl;

		});
		cout<<endl;
	}
	//Task 3 - Sort and print out all cars in order of their horse power (higher is better).
	{
		sort(car.begin(),car.end(),[](const CarRating& tempCar1 ,const CarRating& tempCar2)->bool{
			return tempCar1.horsePower>tempCar2.horsePower;
		});
		for_each(car.begin(),car.end(),[](const CarRating& temp){
			cout << temp.name << ", " << temp.country <<" Horse Power:"<<temp.horsePower<<"." << endl;

		});
		cout<<endl;
	}
	//Task 4 - Print out the average horse power of all German cars.
	{	
		int count=0;
		auto runningTotal =accumulate(car.begin(),car.end(),0.0,[&](double sum,CarRating& temp){
			if(temp.name=="Germany"){
			count++;
			sum+=temp.horsePower;
			}
			return sum;
		});

		cout<< runningTotal/count <<endl;
		//https://www.cplusplus.com/reference/numeric/accumulate/ //for summing
	}
	//Task 5 - Print out all cars with reliability greater than (or equal to) 8.0.
	{
		for_each(car.begin(),car.end(),[](const CarRating& temp){
			if(temp.reliability>=8.0){
				cout<<temp.name<<endl;
			}
		});
	}
	//Task 6 - Change the country of all American cars from "USA" to "United States".
	{
		transform(car.begin(),car.end(),car.begin(),[](CarRating& temp){
				if(temp.country=="USA"){
					temp.country="United States";
				}
				return temp;
		});
		//http://www.cplusplus.com/reference/algorithm/transform/
	}
	//Task 7 - Reorganize the vector of all cars in order of their rating (higher is better) based on the formula:
	//         rating = 2.0*(reliability-4.1) + 2.0*(12.1-fuelEfficiency) + (horsePower-130.0)/37.0
	{
		sort(car.begin(),car.end(),[](const CarRating& tempCar1 ,const CarRating& tempCar2)->bool{
			double rating1=calcRating(tempCar1.fuelEfficiency,tempCar1.reliability,tempCar1.horsePower);
			double rating2=calcRating(tempCar2.fuelEfficiency,tempCar2.reliability,tempCar2.horsePower);
			return rating1>rating2;

		});
	}
}

int main() {
		// struct CarRating {
		// 	std::string name;
		// 	std::string country;
		// 	double reliability;
		// 	double fuelEfficiency;
		// 	double horsePower;
		// };
	vector<CarRating> car({
		{"Toyota Corolla", "Japan", 9.1, 8.0, 130.0},
		{"Honda Civic", "Japan", 8.8, 7.8, 138.0},
		{"Dodge Charger", "USA", 6.5, 10.8, 300.0},
		{"BMW 330x", "Germany", 7.2, 8.9, 260.0},
		{"Chevrolet Impala", "USA", 8.1, 9.9, 280.0},
		{"BMW 240", "Germany", 7.4, 9.2, 320.0},
		{"Ford Fusion", "USA", 6.8, 9.7, 210.0},
		{"Subaru Impreza", "Japan", 7.9, 8.5, 150.0},
		{"BMW M5", "Germany", 6.9, 12.1, 500.0},
		{"Toyota Camry Hybrid", "Japan", 9.3, 7.0, 205.0},
		{"Audi A4", "Germany", 8.9, 8.8, 255.0},
		{"Dodge P.O.S.", "USA", 4.1, 11.7, 233.0}
		});

	cout << "LIST OF CARS:" << endl;
	for_each(car.begin(), car.end(), [](const CarRating& c) {
		cout << c.name << ", " << c.country << "." << endl;
		});
	cout << endl;

	processCars(car);

	cout << endl;
	cout << "LIST OF CARS ORDERED BY RATING:" << endl;
	for_each(car.begin(), car.end(), [](const CarRating& c) {
		cout << c.name << ", " << c.country << "." << endl;
		});

	return 0;
}