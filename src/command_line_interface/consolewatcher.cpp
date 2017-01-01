#include "consolewatcher.h"

#include <iostream>
#include <string>
#include <QSocketNotifier>

using namespace std;

const string ConsoleWatcher::exit_cmd("exit");
const regex ConsoleWatcher::exit_regex("( )*exit\\(\\)( )*");

ConsoleWatcher::ConsoleWatcher(QObject *parent) : QObject(parent)
{
	_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
}

void ConsoleWatcher::run() {
	cout << ">" << flush;
	connect(_notifier, &QSocketNotifier::activated, this, &ConsoleWatcher::readCommand);
}

void ConsoleWatcher::readCommand() {

	string cmd;
	getline(cin, cmd);

	if(isExit(cmd)) {
		emit exitTriggered();
	} else if (regex_match(cmd.c_str(), diceset::diceset_regex)) {
		diceset d(cmd);

		emit singleDiceExpr(d);
	} else {
		emit unregognizedCmd(cmd);
	}
	cout << ">" << flush;

}

bool ConsoleWatcher::isExit(string const& cmd){
	return regex_match(cmd, exit_regex);
}
