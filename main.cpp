#include <iostream>
#include <QCoreApplication>

#include "consoleinterface.h"

#include "dice.h"
#include "diceset.h"
#include "string_utility.h"

using namespace std;

int main(int argc, char** argv)
{
	srand(time(nullptr)); //seed rand.

	QCoreApplication app(argc, argv);
	ConsoleInterface interface(&app);

	QObject::connect(&interface, &ConsoleInterface::exitTriggered, &app, &QCoreApplication::exit);

	interface.run();

	return app.exec();
}
