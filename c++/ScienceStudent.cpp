#include <iostream>
#include <string>
#include <iomanip>
#include "student.h"
#include "ScienceStudent.h"

using namespace std;

//---CONSTRUCTORS
ScienceStudent::ScienceStudent() : Student() {
	bio = 0.0f;
	chem = 0.0f;
	phy = 0.0f;
}

//---GET & SETS
void ScienceStudent::setBio(float bio_) {
	bio = bio_;
}
float ScienceStudent::getBio() { return bio; }
void ScienceStudent::setChem(float chem_) {
	chem = chem_;
}
float ScienceStudent::getChem() { return chem; }
void ScienceStudent::setPhy(float phy_) {
	phy = phy_;
}
float ScienceStudent::getPhy() { return phy; }

//---FUNCTIONS---
//---Add new science stream student info---
void ScienceStudent::registration(ScienceStudent* student) {
	float subject;

	//---Enter student data---
	Student::registration(student);
	cout << "Biology score: ";
	cin >> subject;
	student->setBio(subject);
	cout << "Chemistry score: ";
	cin >> subject;
	student->setChem(subject);
	cout << "Physics score: ";
	cin >> subject;
	student->setPhy(subject);
	return;
}

//---Edit science stream student score---
void ScienceStudent::modifyScore(ScienceStudent* student) {
	float newScore;
	unsigned int choice;
	//---User input
	cout << "\n---------------------------Select subject to modify---------------------------" << endl;
	cout << "1-BM  2-English  3-Math  4-History  5-Moral  6-Biology  7-Chemistry  8-Physics" << endl;
	cout << "------------------------------------------------------------------------------" << endl;
	cin >> choice;
	while (cin.fail() || choice <1 || choice >8) { //---validate input
		cout << "Invalid. Please input numbers 1-8 only." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> choice; //---Reenter user input
	}
	cout << "Input new score: ";
	newScore = checkScore(); //---Get new score & validate

	switch (choice) { //---Assign new score to subject
	case 1:
		student->setBm(newScore);
		break;
	case 2:
		student->setEnglish(newScore);
		break;
	case 3:
		student->setMath(newScore);
		break;
	case 4:
		student->setHistory(newScore); 
		break;
	case 5:
		student->setMoral(newScore);
		break;
	case 6:
		student->setBio(newScore); 
		break;
	case 7:
		student->setChem(newScore);
		break;
	case 8:
		student->setPhy(newScore);
		break;
	default: //---if not 1-8 numbers
		cout << "Invalid input. Please enter between 1-8." << endl;
		modifyScore(student); //---Rerun function to ask for valid input
	}
	cout << "Modification success. " << endl;
	return;
}

//---Get average of all marks of the student---
float ScienceStudent::calcAve() {
	return (calcTot() / 8);
}

//---Get total of scores---
float ScienceStudent::calcTot() {
	return (getBm() + getEnglish() + getMath() + getHistory() + getMoral() + getBio() + getChem() + getPhy());
}

//---Calculate grade from average score---
char ScienceStudent::getGrade() {
	//---Check if selective subjects failed
	if (getBio() < 60 && getChem() < 60 || getBio() < 60 && getPhy() < 60 || getChem() < 60 && getPhy() < 60) {
		return 'F';
	}
	else { //---Get grade
		Student::getGrade();
	}
}

//---Display all attributes of an object---
void ScienceStudent::display() {
	cout << setw(5) << left << getId() << setw(20) << left << getName() << setw(5) << left << getGender() << endl;
	cout << fixed << setprecision(2) << setw(9) << left << getBm() << setw(9) << getEnglish() << setw(9) << getMath()
		<< setw(9) << getHistory() << setw(9) << getMoral() 
		<< setw(9) << getBio() << setw(9) << getChem() << setw(9) << getPhy() << endl;
}