#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <stdexcept>
#include "student.h"
#include "ArtStudent.h"
#include "ScienceStudent.h"

using namespace std;

//---GLOBAL VARIABLES---
string file;
unsigned int choice = 0;
vector <Student> students;
vector <ScienceStudent> scstudents;
vector <ArtStudent> artstudents;
int totalStudents = 0;
Student *student = NULL;

//---FUNCTIONS---
void menu();
void modifyMenu();
bool compare(int id_);
void addStudent();
void search(int id_);
void search(string name);
void save();
bool checkAlpha(const string str);


int main() {
	
	std::ifstream fs;
	fs.exceptions(ifstream::failbit | ifstream::badbit);
	try {
		fs.open("studentlist.txt", ifstream::in);
	}
	// if file fails to open
	catch (ifstream::failure e) {
		cout << "File Not Found!" << endl;
		exit(EXIT_FAILURE);
	}

	cout << "\n-----Student Score System-----" << endl;
		//---Retrive data in file---
		char line[256];
		//---Load file into vector---
		while (!fs.eof()) {
			fs.getline(line, 256, ';');
			if (atoi(line) == 1) {
				ArtStudent newStudent;
				fs.getline(line, 256, ';');
				newStudent.setId(atoi(line));
				fs.getline(line, 256, ';');
				newStudent.setName(line);
				fs.getline(line, 256, ';');
				newStudent.setGender(line[0]);
				fs.getline(line, 256, ';');
				newStudent.setBm(atof(line));
				fs.getline(line, 256, ';');
				newStudent.setEnglish(atof(line));
				fs.getline(line, 256, ';');
				newStudent.setMath(atof(line));
				fs.getline(line, 256, ';');
				newStudent.setHistory(atof(line));
				fs.getline(line, 256, ';');
				newStudent.setMoral(atof(line));
				fs.getline(line, 256, ';');
				newStudent.setEcon(atof(line));
				fs.getline(line, 256, ';');
				newStudent.setComm(atof(line));
				fs.getline(line, 256, '\n');
				newStudent.setArt(atof(line));
				artstudents.push_back(newStudent);
			}
			else if (atoi(line) == 2) {
				ScienceStudent newStudent;
				fs.getline(line, 256, ';');
				newStudent.setId(atoi(line));
				fs.getline(line, 256, ';');
				newStudent.setName(line);
				fs.getline(line, 256, ';');
				newStudent.setGender(line[0]);
				fs.getline(line, 256, ';');
				newStudent.setBm(atof(line));
				fs.getline(line, 256, ';');
				newStudent.setEnglish(atof(line));
				fs.getline(line, 256, ';');
				newStudent.setMath(atof(line));
				fs.getline(line, 256, ';');
				newStudent.setHistory(atof(line));
				fs.getline(line, 256, ';');
				newStudent.setMoral(atof(line));
				fs.getline(line, 256, ';');
				newStudent.setBio(atof(line));
				fs.getline(line, 256, ';');
				newStudent.setChem(atof(line));
				fs.getline(line, 256, '\n');
				newStudent.setPhy(atof(line));
				scstudents.push_back(newStudent);
			}
			else {
				Student newStudent;
				fs.getline(line, 256, ';');
				newStudent.setId(atoi(line));
				fs.getline(line, 256, ';');
				newStudent.setName(line);
				fs.getline(line, 256, ';');
				newStudent.setGender(line[0]);
				fs.getline(line, 256, ';');
				newStudent.setBm(atof(line));
				fs.getline(line, 256, ';');
				newStudent.setEnglish(atof(line));
				fs.getline(line, 256, ';');
				newStudent.setMath(atof(line));
				fs.getline(line, 256, ';');
				newStudent.setHistory(atof(line));
				fs.getline(line, 256, '\n');
				newStudent.setMoral(atof(line));
				students.push_back(newStudent);
			}
		}
		fs.close();

	//---display menu & get user input---
	menu(); 
	while (true) {
		switch (choice) {
		case 1: //---Add student
			addStudent();
			save();
			break;
		case 2: //---Search & modify student data
			cout << "Input using   1- ID   2- name\n ";
			cin >> choice;
			while (cin.fail() || choice != 1 && choice != 2) { //---validate input
				cout << "Invalid. Please input numbers 1 or 2 only." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cin >> choice;
			}
			cin.ignore();
			if (choice == 1) { //---if student ID was chosen
				cout << "Enter student ID: ";
				int id;
				cin >> id;
				while (cin.fail()|| id == 0) { //---Validate input
					cout << "Invalid. Please enter numbers (1 onwards) only: ";
					cin.clear();
					cin.ignore(256, '\n');
					cin >> id; 
				}
				search(id);
			}
			else { //---If student name was chosen
				cout << "Enter student name: ";
				string name;
				getline(cin, name);
				while (!checkAlpha(name)) { //---Validate input
					cout << "Invalid. Please enter alphabets only: ";
					getline(cin, name);
				}
				search(name);
			}
			save();
			break;
		case 3:
			cout << "-------------------------------Student List-------------------------------" << endl;
			cout << "------------------------------Lower Secondary------------------------------" << endl;
			cout << fixed << setprecision(2) << setw(9) << left << "BM" << setw(9) << "ENG" << setw(9) << "MATH" <<
				setw(9) << "HIST" << setw(9) << "MORAL" <<  endl;
			cout << "---------------------------------------------------------------------------" << endl;
			//Loops through array elements to display their values
			for (unsigned int i = 0; i < students.size(); i++) {
				student = &(students[i]);
				student->display();
				cout << fixed << setprecision(2) << setw(7) << left << "Total:" << setw(8) << student->totalScore()
					<< setw(10) << "Average: " << setw(8) << student->calcAve() << setw(8) << "Grade: " << setw(1) << student->getGrade() << endl << endl;
			}
			cout << "------------------------Upper Secondary (Science Stream)------------------------" << endl;
			cout << fixed << setprecision(2) << setw(9) << left << "BM" << setw(9) << "ENG" << setw(9) << "MATH" <<
				setw(9) << "HIST" << setw(9) << "MORAL" << setw(9) << "BIO" << setw(9) << "CHEM" << setw(9) << "PHY" << endl;
			cout << "-------------------------------------------------------------------------------" << endl;
			for (unsigned int i = 0; i < scstudents.size(); i++) {
				student = &(scstudents[i]);
				student->display();
				cout << fixed << setprecision(2) << setw(7) << left << "Total:" << setw(8) << student->totalScore()
					<< setw(10) << "Average: " << setw(8) << student->calcAve() << setw(8) << "Grade: " << setw(1) << student->getGrade() << endl << endl;
			}
			cout << "--------------------------Upper Secondary (Art Stream)--------------------------" << endl;
			cout << fixed << setprecision(2) << setw(9) << left << "BM" << setw(9) << "ENG" << setw(9) << "MATH" <<
				setw(9) << "HIST" << setw(9) << "MORAL" << setw(9) << setw(9) << "ECON" << setw(9) << "COMM" << setw(9) << "ART" << endl;
			cout << "-------------------------------------------------------------------------------" << endl;
			for (unsigned int i = 0; i < artstudents.size(); i++) {
				student = &(artstudents[i]);
				student->display();
				cout << fixed << setprecision(2) << setw(7) << left << "Total:" << setw(8) << student->totalScore()
					<< setw(10) << "Average: " << setw(8) << student->calcAve() << setw(8) << "Grade: " << setw(1) << student->getGrade() << endl << endl;
			}
			break;
		case 4:
			exit(0);
		}
		menu();
	}
	
}

//---Main Menu---
void menu() {
	cout << "1 - Register new record" << endl;
	cout << "2 - Modify record" << endl;
	cout << "3 - Display records" << endl;
	cout << "4 - Exit program" << endl;
	cout << "------------------------------" << endl;
	cin >> choice;
	//---Validate input---
	while (cin.fail() || choice <1 || choice >4) {
		cout << "Invalid. Please input numbers 1-4 only." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> choice;
	}
}

void modifyMenu() {
	cout << "1- Edit student details" << endl;
	cout << "2- Edit student score" << endl;
	cin >> choice;
	//---Validate input---
	while (cin.fail() || choice <1 || choice >2) {
		cout << "Invalid. Please input numbers 1-2 only." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> choice;
	}
}

//---Check if ID exist in list---
bool compare(int id_) {
	for (unsigned int i = 0; i < students.size(); i++) {
		if (students[i].getId() == id_) {
			return false;
		}
	}
	for (unsigned int i = 0; i < scstudents.size(); i++) {
		if (scstudents[i].getId() == id_) {
			return false;
		}
	}
	for (unsigned int i = 0; i < artstudents.size(); i++) {
		if (artstudents[i].getId() == id_) {
			return false;
		}
	}
	return true;
}

//Add a new student record into the list 
void addStudent() {
	int id;
	bool notExist = false;

	//---Input student class---
	cout << "1- Lower secondary" << endl;
	cout << "2- Science stream" << endl;
	cout << "3- Art stream" << endl;
	cout << "Enter number: ";
	cin >> choice;
	while (cin.fail() || choice <1 || choice >3) { //---Check if input is valid
		cout << "Invalid input. " << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Enter number again: ";
		cin >> choice;
	}

	//---Input data for new student record---
	while (!notExist) {
		cout << "Enter student ID: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> id;
		//---Validate input---
		while (cin.fail()|| id == 0) {
			cout << "Invalid. Numbers (1 onwards): ";
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Enter number again: ";
			cin >> id;
		}
		//---Check if ID exist---
		notExist = compare(id);
		if (!notExist) {
			cout << "ID already exist." << endl;
		}
	}
	cin.clear();
	cin.ignore();

	//---Create student object & input details---
	switch (choice) {
		case 1:
		{
			Student newStudent; 
			Student* student_ptr = &newStudent;
			student_ptr->setId(id);
			student_ptr->registration(&newStudent);
			students.push_back(newStudent);
			break;
		}
		case 2:
		{
			
			ScienceStudent newStudent;
			ScienceStudent* science_ptr = &newStudent;
			science_ptr->setId(id);
			science_ptr->registration(&newStudent);
			scstudents.push_back(newStudent);
			break;
		}
		case 3:
		{
			ArtStudent newStudent;
			ArtStudent* art_ptr = &newStudent;
			art_ptr->setId(id);
			art_ptr->registration(&newStudent);
			artstudents.push_back(newStudent);
			break;
		}
	}
	cout << "New record added." << endl;
}

//---Search for student ID---
void search(int id_) {
	bool exist = false;
	//---Search in lower secondary students---
	for (unsigned int i = 0; i < students.size(); i++) {
		if (students[i].getId() == id_) {
			exist = true;
			Student* ptr = &students[i];
			ptr->display();
			modifyMenu();
			if (choice == 1) {
				ptr->modifyDetail(&students[i]);
			}
			else {
				ptr->modifyScore(&students[i]);
			}
			ptr->display();
		}
	}
	//---Search in science stream students---
	for (unsigned int i = 0; i < scstudents.size(); i++) {
		if (scstudents[i].getId() == id_) {
			exist = true;
			Student* main_ptr = &scstudents[i];
			scstudents[i].display();
			modifyMenu();
			if (choice == 1) {
				main_ptr->modifyDetail(&scstudents[i]);
			}
			else {
				ScienceStudent* ptr = dynamic_cast<ScienceStudent*>(main_ptr);
				ptr->modifyScore(&scstudents[i]);
			}
			scstudents[i].display();
		}
	}
	//---Search in art stream students---
	for (unsigned int i = 0; i < artstudents.size(); i++) {
		if (artstudents[i].getId() == id_) {
			exist = true;
			Student* main_ptr = &artstudents[i];
			artstudents[i].display();
			modifyMenu();
			if (choice == 1) {
				main_ptr->modifyDetail(&artstudents[i]);
			}
			else {
				ArtStudent* ptr = dynamic_cast<ArtStudent*>(main_ptr);
				ptr->modifyScore(&artstudents[i]);
			}
			artstudents[i].display();
		}
	}
	//---If student ID doesn't exist---
	if (!exist) {
		cout << "No such id." << endl;
	}
}

//---Search for student name---
void search(string name_) {
	bool exist = false;
	//---Search in lower secondary students---
	for (unsigned int i = 0; i < students.size(); i++) {
		if (students[i].getName() == name_) {
			exist = true;
			Student* ptr = &students[i];
			ptr->display();
			modifyMenu();
			if (choice == 1) {
				ptr->modifyDetail(&students[i]);
			}
			else {
				ptr->modifyScore(&students[i]);
			}
			ptr->display();
		}
	}
	//---Search in science stream students---
	for (unsigned int i = 0; i < scstudents.size(); i++) {
		if (scstudents[i].getName() == name_) {
			exist = true;
			Student* main_ptr = &scstudents[i];
			scstudents[i].display();
			modifyMenu();
			if (choice == 1) {
				main_ptr->modifyDetail(&scstudents[i]);
			}
			else {
				ScienceStudent* ptr = dynamic_cast<ScienceStudent*>(main_ptr);
				ptr->modifyScore(&scstudents[i]);
			}
			scstudents[i].display();
		}
	}
	//---Search in art stream students---
	for (unsigned int i = 0; i < artstudents.size(); i++) {
		if (artstudents[i].getName() == name_) {
			exist = true;
			Student* main_ptr = &artstudents[i];
			artstudents[i].display();
			modifyMenu();
			if (choice == 1) {
				main_ptr->modifyDetail(&artstudents[i]);
			}
			else {
				ArtStudent* ptr = dynamic_cast<ArtStudent*>(main_ptr);
				ptr->modifyScore(&artstudents[i]);
			}
			artstudents[i].display();
		}
	}
	//---If student name doesn't exist---
	if (!exist) {
		cout << "No such student name." << endl;
	}
}

//---Save all students into file---
void save() {
	ofstream out;
	out.open("studentlist.txt", fstream::out);
	//---Write lower secondary students to file---
	for (unsigned int i = 0; i < students.size(); i++) {
		if (artstudents.size() == 0 && scstudents.size() == 0 && (students.size() - 1) == i) {
			out << "0;" << students[i];
		}
		else {
			out << "0;" << students[i] << endl;
		}
	}
	//---Write art stream students to file---
	for (unsigned int i = 0; i < artstudents.size(); i++) {
		if (scstudents.size() == 0 && (artstudents.size() - 1) == i) {
			out << "1;" << artstudents[i] << ";" << artstudents[i].getEcon() << ";"
				<< artstudents[i].getComm() << ";" << artstudents[i].getArt();
		}
		else {
			out << "1;" << artstudents[i] << ";" << artstudents[i].getEcon() << ";"
				<< artstudents[i].getComm() << ";" << artstudents[i].getArt() << endl;
		}
	}
	//---Write science stream students to file---
	for (unsigned int i = 0; i < scstudents.size(); i++) {
		if ((scstudents.size() - 1) == i) {
			out << "2;" << scstudents[i] << ";" << scstudents[i].getBio() << ";"
				<< scstudents[i].getChem() << ";" << scstudents[i].getPhy();
		}
		else {
			out << "2;" << scstudents[i] << ";" << scstudents[i].getBio() << ";"
				<< scstudents[i].getChem() << ";" << scstudents[i].getPhy() << endl;
		}
	}
	cout << "" << endl;
	out.close();
}

//---Validate if input is string of alphabets and spaces
bool checkAlpha(const string str) {
	for (unsigned int i = 0; i < str.size(); i++) {
		if (isalpha(str[i]) || isspace(str[i])) {}
		else {
			return false;
		}
	}
	return true;
}