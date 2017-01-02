#include "consoleinterface.h"

#include "consolewatcher.h"
#include "dicevarsmodel.h"

using namespace  std;

ConsoleInterface::ConsoleInterface(QObject *parent) : QObject(parent)
{
	_watcher = new ConsoleWatcher(this);
	_variables = new DiceVarsModel(this);

	connect(_watcher, &ConsoleWatcher::exitTriggered, this, &ConsoleInterface::exitTriggered);
	connect(_watcher, &ConsoleWatcher::singleDiceExpr, this, &ConsoleInterface::treatDiceSet);

	connect(_watcher, &ConsoleWatcher::registerDiceExpr, _variables, &DiceVarsModel::insertDiceset);
	connect(_watcher, &ConsoleWatcher::triggerDiceExpr, this, &ConsoleInterface::treatRegistredDiceSet);
}

void ConsoleInterface::run() {

	_watcher->run();
}

void ConsoleInterface::treatDiceSet(diceset set) {
	cout << set << endl;
}

void ConsoleInterface::treatRegistredDiceSet(QString varName) {

	try {
		cout << _variables->getSet(varName) << endl;
	} catch (DiceVarsException const& e) {
		cerr << e.what() << endl;
	}
}
