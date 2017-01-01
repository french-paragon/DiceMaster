#ifndef CONSOLEWATCHER_H
#define CONSOLEWATCHER_H

#include <QObject>

#include <diceset.h>

class QSocketNotifier;

/*!
 * \brief The ConsoleWatcher class watch stdin and send signals corresponding to input commands.
 */
class ConsoleWatcher : public QObject
{
	Q_OBJECT
public:

	static const std::string exit_cmd;
	static const std::regex exit_regex;

	explicit ConsoleWatcher(QObject *parent = 0);

signals:

	void exitTriggered(int status = 0);
	void singleDiceExpr(diceset set);
	void unregognizedCmd(std::string cmd);

public slots:

	void run();

protected:

	void readCommand();

	bool isExit(std::string const& cmd);

private:

	QSocketNotifier *_notifier;
};

#endif // CONSOLEWATCHER_H
