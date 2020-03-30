#include "Repository.h"



Repository::Repository()
{
}

void Repository::loadWritters()
{
	std::ifstream content("writters.txt");
	std::vector<std::string> fragm;
	Writter w{};
	std::string line;

	while (content >> line) {
		fragm = this->fragmentate(line, ',');

		w.setExpertise(fragm[1]);
		w.setName(fragm[0]);
		this->writters.push_back(w);

	}

	content.close();
}

void Repository::loadIdeas()
{
	std::ifstream content("ideas.txt");
	std::vector<std::string> fragm;
	std::string line;
	Idea id{};
	while (content >> line) {
		fragm = this->fragmentate(line, ',');
		if (fragm.size() == 4) {
			id.setWritter(fragm[0]);
			id.setDescription(fragm[1]);
			id.setStatus(fragm[2]);
			id.setAct(std::stoi(fragm[3]));
			this->ideas.push_back(id);
		}
	}

	content.close();
}


std::vector<std::string> Repository::fragmentate(std::string str, char delimit)
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;

	while (getline(ss, token, delimit)) {
		result.push_back(token);
	}

	return result;
}

std::vector<Idea> Repository::getAllAcceptedFromAct(int act)
{
	std::vector<Idea> plot;
	for(auto id:this->ideas)
		if (id.getAct() == act && id.getStatus() == "accepted") {
			plot.push_back(id);
		}
	return plot;
}

Repository::~Repository()
{
}
