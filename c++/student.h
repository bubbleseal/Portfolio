#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
	int id;
	string name;
	char gender;
	float bm;
	float english;
	float math;
	float history;
	float moral;

public:
	//constructors
	Student();

	//gets and sets
	void setId(int id_);
	int getId();
	void setName(string name_);
	string getName();
	void setGender(char gender_);
	char getGender();
	void setBm(float bm_);
	float getBm();
	void setEnglish(float english_);
	float getEnglish();
	void setMath(float math_);
	float getMath();
	void setHistory(float history_);
	float getHistory();
	void setMoral(float moral_);
	float getMoral();

	//functions
	virtual void registration(Student* student);
	void modifyDetail(Student* student);
	virtual void modifyScore(Student* student);
	float checkScore();
	virtual float calcAve();
	float totalScore();
	virtual char getGrade();
	virtual void display();
	bool checkAlpha(const string str);
	bool checkGender(const char gender);
	friend ostream& operator<<(ostream& out, Student const& student);
};
#endif

