#include "Controller.h"



Controller::Controller()
{
}

std::vector<Idea> Controller::getWritterIdeas(std::string name)
{
	std::vector<Idea> ids;
	for (auto id : this->repo->getAllIdeas()) {
		if (id.getWritter() == name) {
			ids.push_back(id);
		}
	}

	return ids;
}

std::vector<Idea> Controller::sortIdeasByAct(std::vector<Idea> orig)
{
	std::sort(orig.begin(), orig.end(), [](Idea & i1, Idea & i2) {return i1.getAct() < i2.getAct(); });
	return orig;
}

bool Controller::hasAcceptedIdeas(Writter wr)
{
	for (auto id : this->getWritterIdeas(wr.getName())) {
		if (id.getStatus() == "accepted") {
			return true;
		}
	}
	return false;
}

std::vector<Idea> Controller::allWritterApprovedIdeas(Writter wr)
{
	std::vector<Idea> res;
	for (auto i : this->repo->getAllIdeas()) {
		if (i.getWritter() == wr.getName() && i.getStatus() == "accepted")
			res.push_back(i);
	}
	return res;

}

Controller::~Controller()
{
}
