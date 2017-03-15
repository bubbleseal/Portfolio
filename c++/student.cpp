#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "student.h"

using namespace std;

//---CONSTRUCTORS
Student::Student() {
	id = 0;
	name = "";
	gender = NULL;
	bm = 0.0f;
	english = 0.0f;
	math = 0.0f;
	history = 0.0f;
	moral = 0.0f;
}

//---GET & SETS
void Student::setId(int id_) {
	id = id_;
}
int Student::getId() { return id; }
void Student::setName(string name_) {
	name = name_;
}
string Student::getName() { return name; }
void Student::setGender(char gender_) {
	gender = gender_;
}
char Student::getGender() { return gender; }
void Student::setBm(float bm_) {
	bm = bm_;
}
float Student::getBm() { return bm; }
void Student::setEnglish(float english_) {
	english = english_;
}
float Student::getEnglish() { return english; }
void Student::setMath(float math_) {
	math = math_;
}
float Student::getMath() { return math; }
void Student::setHistory(float history_) {
	history = history_;
}
float Student::getHistory() { return history; }
void Student::setMoral(float moral_) {
	moral = moral_;
}
float Student::getMoral() { return moral; }


//---FUNCTIONS---
//---Add new lower secondary student info---
void Student::registration(Student* student) {
	string name_;
	char gender_;
	float subject;
	
	//---Enter student data---
	cout << "Student name: ";
	getline(cin, name_);
	while (!checkAlpha(name_)) { //---Validate name
		cout << "Invalid. Please enter alphabets only: ";
		getline(cin, name_);
	}
	student->setName(name_);
	cout << "Student gender(M/F/U): ";
	cin >> gender_;
	while (!checkGender(gender_)) { //---Validate gender
		cout << "Invalid gender. Please enter again: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> gender_;
	}
	student->setGender(gender_);
	cout << "Bahasa Malaysia score: ";
	subject = checkScore();
	student->setBm(subject);
	cout << "English score: ";
	subject = checkScore();
	student->setEnglish(subject);
	cout << "Math score: ";
	subject = checkScore();
	student->setMath(subject);
	cout << "History score: ";
	subject = checkScore();
	student->setHistory(subject);
	cout << "Moral score: ";
	subject = checkScore();
	student->setMoral(subject);
	return;
}

//---Edit lower secondary student score---
void Student::modifyDetail(Student* student) {
	string name_;
	char gender_;
	unsigned int choice;
	//---User input
	cout << "\n----------Select detail to modify---------" << endl;
	cout << "     1- Name     2- Gender" << endl;
	cout << "-------------------------------------------" << endl;
	cin >> choice;
	//---validate input
	while (cin.fail() || choice <1 || choice >2) {
		cout << "Invalid. Please input numbers 1-2 only." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> choice; //Reenter user input
	}
	switch (choice) { //---Assign new detail to student
		case 1: {
			cout << "Edit Name: ";
			cin.clear();
			cin.ignore(256, '\n');
			getline(cin, name_);
			while (!checkAlpha(name_)) { //---Validate name
				cout << "Invalid. Please enter alphabets only: ";
				cin.clear();
				cin.ignore(256, '\n');
				getline(cin, name_);
			}
			student->setName(name_);
			break;
		}
		case 2: {
			cout << "Input gender: ";
			cin >> gender;
			while (!checkGender(gender)) { //---Validate gender
				cout << "Invalid gender. Please enter again: " << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cin >> gender;
			}
			student->setGender(gender);
			break;
		}
		default: //---if not 1-2
			cout << "Invalid input. Please enter between 1-2." << endl;
			modifyDetail(student); //---Rerun function to ask for valid input
	}
	cout << "Modification success. " << endl;
	return;
}

//---Edit lower secondary student score---
void Student::modifyScore(Student* student) {
	float newScore;
	unsigned int choice;
	//---User input
	cout << "\n-----------------Select subject to modify----------------" << endl;
	cout << "1- BM   2- English  3- Math   4- History   5- Moral" << endl;
	cout << "---------------------------------------------------------" << endl;
	cin >> choice;
	//---validate input
	while (cin.fail() || choice <1 || choice >5) {
		cout << "Invalid. Please input numbers 1-5 only." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> choice; //Reenter user input
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
	default: //---if not 1-5 numbers
		cout << "Invalid input. Please enter between 1-5." << endl;
		modifyScore(student); //---Rerun function to ask for valid input
	}
	cout << "Modification success. " << endl;
	return;
}

// Check if user input is a valid type & range
float Student::checkScore() {
	float input;
	cin >> input;
	while (cin.fail() || input < 0 || input > 100) { //loop if user input is not integer
		cout << "Invalid. Please re-enter score (0-100): ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> input; //Get input again if input was invalid
	}
	return input;
}

//---Get average of all marks of the student---
float Student::calcAve() {
	return (totalScore() / 5);
}

//---Get total of scores---
float Student::totalScore() {
	return (getBm() + getEnglish() + getMath() + getHistory() + getMoral());
}

//---Calculate grade from average score---
char Student::getGrade() {
	//---Check if core subjects failed---
	if (getBm() < 60 || getEnglish() < 60 || getMath() < 60 || getHistory() < 60 || getMoral() < 60) {
		return 'F';
	}
	//---Get grade---
	else {
		float ave = totalScore() / 5;
		if (ave > 89) {
			return 'A';
		}
		else if (ave > 79) {
			return 'B';
		}
		else if (ave > 69) {
			return 'C';
		}
		else if (ave > 59) {
			return 'D';
		}
	}
}

//---Display all attributes of student---
void Student::display() {
	cout << setw(5) << left << getId() << setw(20) << left << getName() << setw(5) << left << getGender() << endl;
	cout << fixed << setprecision(2) << setw(9) << getBm() << setw(9) << left << getEnglish() << setw(9) << getMath()
		<< setw(9) << getHistory() << setw(9) << getMoral() << endl;
}

//---Validate if input is string of alphabets and spaces
bool Student::checkAlpha(const string str) {
	for (int i = 0; i < str.size(); i++) {
		if (isalpha(str[i]) || isspace(str[i])) {}
		else {
			return false;
		}
	}
	return true;
}

//---Validate gender---
bool Student::checkGender(const char gender) {
	if (gender == 'M' || gender == 'm') {
		return true;
	}
	else if (gender == 'F' || gender == 'f') {
		return true;
	}
	else if (gender == 'U' || gender == 'u') {
		return true;
	}
	else {
		return false;
	}
}

//---Overload << to display student details and core subject scores---
ostream& operator<<(std::ostream& out, Student const& student) {
	out << student.id << ";" << student.name << ";" << student.gender << ";"
		<< student.bm << ";" << student.english << ";" << student.math << ";" << student.history << ";" << student.moral;
	return out;
}