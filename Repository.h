#pragma once
#include "Writter.h"
#include "Idea.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

class Repository
{
	std::vector<Idea> ideas;
	std::vector<Writter> writters;
public:
	Repository();

	void add(Idea id) { this->ideas.push_back(id); }
	void loadWritters();
	void loadIdeas();

	std::vector<Idea> getAllIdeas() { return this->ideas; }
	std::vector<Writter> getAllWritters() { return this->writters; }

	std::vector<std::string> fragmentate(std::string str, char delimit);

	void sort() {
		std::sort(this->ideas.begin(), this->ideas.end(), [](Idea & i1, Idea & i2) {return i1.getAct() < i2.getAct(); });
	}

	void updateIdea(Idea newIdea) {
		int i;
		for (i = 0; i < this->ideas.size(); i++) {
			if (this->ideas[i] == newIdea) {
				this->ideas[i] = newIdea;
			}
		}
	}
	int getSize() { return this->ideas.size(); }

	std::vector<Idea> getAllAcceptedFromAct(int act);

	
	~Repository();
};

