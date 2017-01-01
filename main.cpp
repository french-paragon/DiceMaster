#include <iostream>
#include <QCoreApplication>

#include "consolewatcher.h"

#include "dice.h"
#include "diceset.h"
#include "string_utility.h"

using namespace std;

void treatDiceSet(diceset set){
	cout << set << endl;
}

int main(int argc, char** argv)
{
	srand(time(nullptr)); //seed rand.

	QCoreApplication app(argc, argv);
	ConsoleWatcher watcher(&app);

	QObject::connect(&watcher, &ConsoleWatcher::exitTriggered, &app, &QCoreApplication::exit);
	QObject::connect(&watcher, &ConsoleWatcher::singleDiceExpr, &treatDiceSet);

	watcher.run();

	return app.exec();
}
