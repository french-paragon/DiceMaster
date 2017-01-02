#ifndef DICEVARSMODEL_H
#define DICEVARSMODEL_H

#include <QObject>
#include <QColor>
#include <QAbstractItemModel>

#include <exception>

#include "diceset.h"

class DiceVarsException : public std::exception {

public:
	DiceVarsException(QString const& infos);

	virtual const char* what() const throw();

protected:

	std::string _infos;

};

class DiceVarsModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	DiceVarsModel(QObject * parent);
	~DiceVarsModel();

	virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	virtual QModelIndex parent(const QModelIndex &index) const;

	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

	virtual QVariant data(const QModelIndex &index, int role) const;

	bool containVar(QString const& varName) const;
	diceset const& getSet(QString const& varName) const;

public slots:

	void insertDiceset(diceset const& set, QString const& varName);
	void insertDicesetUnder(diceset const& set, QString const& varName, const QModelIndex &parent);

protected:

	class CatNode;
	class AbstractNode;

	AbstractNode* getNodeByIndex(const QModelIndex &index) const;

	void createDiceInsertPos(diceset const& set, QStringList & varName, AbstractNode* parent);

	bool varNameIsValid(QString const& name);

	class AbstractNode {

	public:

		AbstractNode(QString const& name, CatNode* parent = nullptr);
		virtual ~AbstractNode();

		enum NodeType{
			NODE_CAT,
			NODE_SET
		};

		virtual NodeType type() const = 0;
		virtual QVariant represent(int role = Qt::DisplayRole) const = 0;
		int getRowFromParent();

		virtual CatNode* asCatNode();

		CatNode* _parent;
		QVector<AbstractNode*> _childrens;
		QString _name;

	};

	class CatNode : public AbstractNode {

	public:

		CatNode(QString title = tr("collection"), CatNode* parent = nullptr);

		NodeType type() const;
		QVariant represent(int role = Qt::DisplayRole) const;

		virtual CatNode* asCatNode();

		QColor _color;

	};

	class DiceNode : public AbstractNode {

	public:

		DiceNode(diceset const& set, QString title = tr("set"), CatNode* parent = nullptr);

		NodeType type() const;
		QVariant represent(int role = Qt::DisplayRole) const;

		diceset _set;

	};

	AbstractNode* _root;

};

#endif // DICEVARSMODEL_H
