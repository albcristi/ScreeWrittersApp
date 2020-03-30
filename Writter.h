#pragma once
#include <string>

class Writter
{
	std::string name;
	std::string expertise;
public:
	Writter() { this->name = ""; this->expertise = ""; }
	Writter(std::string n, std::string ex) { this->name = n; this->expertise = ex; }
	Writter(const Writter& co) { this->name = co.name; this->expertise = co.expertise; }
	
	std::string getName() { return this->name; }
	std::string getExpertise() { return this->expertise; }

	Writter& setName(std::string n) { this->name = n; return *this; }
	Writter& setExpertise(std::string e) { this->expertise = e; return *this; }

	bool operator==(const Writter& wr) { return this->name == wr.name; }
	~Writter() {}
};

