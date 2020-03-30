#pragma once
#include <string>

class Idea
{
	std::string description;
	std::string status;
	std::string writter_name;
	int act;
public:
	Idea();

	Idea(std::string desc, std::string stat, std::string wr, int act) {
		this->description = desc;
		this->status = stat;
		this->writter_name = wr;
		this->act = act;
	}

	Idea(const Idea& co) {
		this->description = co.description;
		this->act = co.act;
		this->status = co.status;
		this->writter_name = co.writter_name;
	}

	Idea& setDescription(std::string desc) {
		this->description = desc;
		return *this;
	}

	Idea& setStatus(std::string sta) { this->status = sta; return *this; }

	Idea& setWritter(std::string wr) { this->writter_name = wr; return *this; }

	Idea& setAct(int ac) { this->act = ac; return *this; }

	bool operator==(const Idea& co) {
		if (this->act != co.act) {
			return false;
		}
		if (this->writter_name != co.writter_name) {
			return false;
		}
		if (this->description != co.description) {
			return false;
		}

		return true;
	}
	std::string getDescription() { return this->description; }
	std::string getStatus() { return this->status; }
	std::string getWritter() { return this->writter_name; }
	int getAct() { return this->act; }

	~Idea();
};

