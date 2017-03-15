#ifndef ARTSTUDENT_H
#define ARTSTUDENT_H

#include <iostream>
#include <string>
using namespace std;

class ArtStudent : public Student {
private:
	float econ;
	float comm;
	float art;

public:
	//constructors
	ArtStudent();

	//gets and sets
	void setEcon(float econ_);
	float getEcon();
	void setComm(float comm_);
	float getComm();
	void setArt(float art_);
	float getArt();

	//functions
	void registration(ArtStudent* student);
	void modifyScore(ArtStudent* student);
	float calcAve();
	float calcTot();
	char getGrade();
	void display();
};
#endif

