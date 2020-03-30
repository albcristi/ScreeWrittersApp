#pragma once
#include "Repository.h"
#include <algorithm>

class Controller
{
	Repository* repo;
public:
	Controller();
	Controller(Repository* rep) { this->repo = rep; }
	
	std::vector<Writter> getAllWritters() { return this->repo->getAllWritters(); }

	std::vector<Idea> getWritterIdeas(std::string name);

	std::vector<Idea> sortIdeasByAct(std::vector<Idea> orig);

	std::vector<Idea> getAllIdeas() { return this->repo->getAllIdeas(); }

	void add(Idea id) {
		this->repo->add(id);
	}

	void update(Idea id) { this->repo->updateIdea(id); }

	bool hasAcceptedIdeas(Writter wr);
	std::vector<Idea> getAprobByAct(int act) { return this->repo->getAllAcceptedFromAct(act); }

	std::vector<Idea> allWritterApprovedIdeas(Writter wr);
	~Controller();
};

