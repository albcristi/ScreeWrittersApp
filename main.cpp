#include "ScreenWritters.h"
#include <QtWidgets/QApplication>
#include "Controller.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Repository* repo = new Repository();
	repo->loadIdeas();
	repo->loadWritters();
	Controller con{ repo };
	myTableModel* model = new myTableModel(repo);

	repo->sort();
	//ScreenWritters* ss = new ScreenWritters(Writter("dan","da"), con, model);
	std::vector<ScreenWritters*> wnd;
	for (auto wr : con.getAllWritters()) {
		wnd.push_back(new ScreenWritters(wr, con, model));
	}
	for (auto w : wnd) {
		w->show();
	}
	return a.exec();
}
