#ifndef SCIENCESTUDENT_H
#define SCIENCESTUDENT_H

#include <iostream>
#include <string>
using namespace std;

class ScienceStudent : public Student {
private:
	float bio;
	float chem;
	float phy;

public:
	//constructors
	ScienceStudent();

	//gets and sets
	void setBio(float bio_);
	float getBio();
	void setChem(float chem_);
	float getChem();
	void setPhy(float phy_);
	float getPhy();

	//functions
	void registration(ScienceStudent* student);
	void modifyScore(ScienceStudent* student);
	float calcAve();
	float calcTot();
	char getGrade();
	void display();
};
#endif

