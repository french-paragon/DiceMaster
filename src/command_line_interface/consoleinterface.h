#ifndef CONSOLEINTERFACE_H
#define CONSOLEINTERFACE_H

#include <QObject>

#include "diceset.h"

class ConsoleWatcher;
class DiceVarsModel;

class ConsoleInterface : public QObject
{
	Q_OBJECT
public:
	explicit ConsoleInterface(QObject *parent = 0);

	void run();

signals:

	void exitTriggered(int status = 0);

public slots:

protected:

	void treatDiceSet(diceset set);
	void treatRegistredDiceSet(QString varName);

	ConsoleWatcher* _watcher;
	DiceVarsModel* _variables;
};

#endif // CONSOLEINTERFACE_H
