#include <iostream>
#include <string>
#include <iomanip>
#include "student.h"
#include "ArtStudent.h"

using namespace std;

//---CONSTRUCTORS
ArtStudent::ArtStudent() : Student() {
	econ = 0.0f;
	comm = 0.0f;
	art = 0.0f;
}

//---GET & SETS
void ArtStudent::setEcon(float econ_) {
	econ = econ_;
}
float ArtStudent::getEcon() { return econ; }
void ArtStudent::setComm(float comm_) {
	comm = comm_;
}
float ArtStudent::getComm() { return comm; }
void ArtStudent::setArt(float art_) {
	art = art_;
}
float ArtStudent::getArt() { return art; }

//---FUNCTIONS---
//---Add new art stream student info---
void ArtStudent::registration(ArtStudent* student) {
	float subject;

	//---Enter student data---
	Student::registration(student);
	cout << "Economics score: ";
	cin >> subject;
	student->setEcon(subject);
	cout << "Commerce score: ";
	cin >> subject;
	student->setComm(subject);
	cout << "Art score: ";
	cin >> subject;
	student->setArt(subject);
	return;
}

//---Edit art stream student score---
void ArtStudent::modifyScore(ArtStudent* student) {
	float newScore;
	unsigned int choice;
	//---User input
	cout << "\n---------------------------Select subject to modify---------------------------" << endl;
	cout << "1-BM  2-English  3-Math  4-History  5-Moral  6-Economics  7-Commerce  8-Art" << endl;
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
		student->setEcon(newScore); 
		break;
	case 7:
		student->setComm(newScore);
		break;
	case 8:
		student->setArt(newScore); 
		break;
	default: //---if not 1-8 numbers
		cout << "Invalid input. Please enter between 1-8." << endl;
		modifyScore(student); //---Rerun function to ask for valid input
	}
	cout << "Modification success. " << endl;
	return;
}

//---Get average of all marks of the student---
float ArtStudent::calcAve() {
	return (calcTot() / 8);
}

//---get total of scores---
float ArtStudent::calcTot() {
	return (getBm() + getEnglish() + getMath() + getHistory() + getMoral() + getEcon() + getComm() + getArt());
}

//---Calculate grade from average score---
char ArtStudent::getGrade() {
	//---Check if selective subjects failed
	if (getEcon() < 60 && getComm() < 60 && getArt() < 60) {
		return 'F';
	}
	else { //---Get grade
		Student::getGrade();
	}
}

//---Display all attributes of an object---
void ArtStudent::display() {
	cout << setw(5) << left << getId() << setw(20) << left << getName() << setw(5) << left << getGender() << endl;
	cout << fixed << setprecision(2) << setw(9) << left << getBm() << setw(9) << getEnglish() << setw(9) << getMath()
		<< setw(9) << getHistory() << setw(9) << getMoral() 
		<< setw(9) << getEcon() << setw(9) << getComm() << setw(9) << getArt() << endl;
}