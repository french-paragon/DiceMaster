#include "dicevarsmodel.h"

#include <QString>
#include <QStringList>

// Exception class

DiceVarsException::DiceVarsException(QString const& infos) :
	_infos(infos.toStdString())
{

}

const char* DiceVarsException::what() const throw(){
	return _infos.c_str();
}


//class

DiceVarsModel::DiceVarsModel(QObject *parent): QAbstractItemModel(parent)
{
	_root = new CatNode();
}

DiceVarsModel::~DiceVarsModel() {
	delete _root;
}

QModelIndex DiceVarsModel::index(int row, int column, const QModelIndex &parent) const {

    AbstractNode* ptr = (AbstractNode*) parent.internalPointer();

    if (parent == QModelIndex()) {
        ptr = _root;
    }

    if (column != 0 || row >= ptr->_childrens.size()) {
        return QModelIndex();
    }

    return createIndex(row, column, ptr->_childrens.at(row));

}

QModelIndex DiceVarsModel::parent(const QModelIndex &index) const {

    AbstractNode* ptr = (AbstractNode*) index.internalPointer();

    if (ptr->_parent == _root) {
        return QModelIndex();
    }

    return createIndex(ptr->_parent->_childrens.indexOf(ptr), 0, ptr->_parent);

}

int DiceVarsModel::rowCount(const QModelIndex &parent) const {
    AbstractNode* ptr = (AbstractNode*) parent.internalPointer();

	if (ptr->type() == AbstractNode::NODE_CAT) {
		return ptr->_childrens.size();
	}
	return 0;
}
int DiceVarsModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

QVariant DiceVarsModel::data(const QModelIndex &index, int role) const {

    AbstractNode* ptr = (AbstractNode*) index.internalPointer();

    return ptr->represent(role);

}

bool DiceVarsModel::containVar(QString const& varName) const {
	QStringList list = varName.split('/'); //url.

	AbstractNode* node = _root;

	while (!list.isEmpty()) {

		QString name = list.takeFirst();

		for (AbstractNode* ptr: node->_childrens) {
			if (ptr->_name == name) {
				node = ptr;
				goto no_error;
			}
		}

		return false;

		no_error:

		continue;
	}

	return true;
}

diceset const& DiceVarsModel::getSet(QString const& varName) const {

	QStringList list = varName.split('/'); //url.

	AbstractNode* node = _root;

	while (!list.isEmpty()) {

		QString name = list.takeFirst();

		for (AbstractNode* ptr: node->_childrens) {
			if (ptr->_name == name) {
				node = ptr;
				goto no_error;
			}
		}

		goto error;

		no_error:

		continue;
	}

	if (node->type() != AbstractNode::NODE_SET) {
		goto error;
	}

	{
		DiceNode* dnode = dynamic_cast<DiceNode*>(node);

		return dnode->_set;
	}

	error:

	throw DiceVarsException(QString("Impossible to reach dice variable at %1").arg(varName));

}


void DiceVarsModel::insertDiceset(diceset const& set, QString const& varName) {
	insertDicesetUnder(set, varName, QModelIndex());
}

void DiceVarsModel::insertDicesetUnder(diceset const& set, QString const& varName, const QModelIndex &parent) {

	QStringList list = varName.split('/'); //url.

	AbstractNode* parent_ptr = getNodeByIndex(parent);

	if (!varNameIsValid(varName)) {
		throw DiceVarsException(QString("Invalid var name: %1").arg(varName));
	}

	volatile int s = list.size();
	for (int i = 0; i < s; i++) {

		QString val = list.at(0);

		AbstractNode* new_parent = nullptr;

		for (AbstractNode* ptr : parent_ptr->_childrens) {
			if (ptr->_name == val) {
				new_parent == ptr;
				break;
			}
		}

		if (new_parent == nullptr) { //we reached a new position in the url.

			QModelIndex id_parent = QModelIndex();

			if (parent_ptr != _root) {
				id_parent = createIndex(parent_ptr->getRowFromParent(), 0, parent_ptr);
			}

			beginInsertRows(id_parent,
							parent_ptr->_childrens.size(),
							parent_ptr->_childrens.size());
			createDiceInsertPos(set, list, parent_ptr);
			endInsertRows();
		}

		parent_ptr == new_parent;
		list.pop_front();

	}

	throw DiceVarsException(QString("Trying to create a dice on an existing variable: %1").arg(varName));

}

void DiceVarsModel::createDiceInsertPos(diceset const& set, QStringList & varlist, AbstractNode* parent) {

	CatNode* upperCat = parent->asCatNode();

	if (upperCat == nullptr) {
		throw DiceVarsException(QString("Invalid conversion of category"));
	}

	while (varlist.size() > 1) {
		CatNode* new_node = new CatNode(varlist.takeFirst(), upperCat);
		upperCat->_childrens.push_back(new_node);
		upperCat = new_node;
	}

	DiceNode* dNode = new DiceNode(set, varlist.takeFirst(), upperCat);
	upperCat->_childrens.push_back(dNode);

}

DiceVarsModel::AbstractNode* DiceVarsModel::getNodeByIndex(const QModelIndex &index) const {
	AbstractNode* ptr = (AbstractNode*) index.internalPointer();

	if (index == QModelIndex()) {
		ptr = _root;
	}

	return ptr;
}


bool DiceVarsModel::varNameIsValid(QString const& name) {
	return !name.isEmpty();
}

//*************************************************//
//			       subclasses                      //
//*************************************************//


DiceVarsModel::AbstractNode::AbstractNode(const QString &name, CatNode *parent) :
	_childrens(),
	_name(name)
{
	_parent = parent;

}

DiceVarsModel::AbstractNode::~AbstractNode() {
	for (AbstractNode* ptr : _childrens) {
		delete ptr;
	}
}

int DiceVarsModel::AbstractNode::getRowFromParent() {
	if (_parent == nullptr) {
		return 0;
	}
	return _parent->_childrens.indexOf(this);
}

DiceVarsModel::CatNode* DiceVarsModel::AbstractNode::asCatNode() {
	return nullptr;
}

DiceVarsModel::CatNode::CatNode(QString title, CatNode *parent) :
	AbstractNode(title, parent),
	_color(255, 255, 255, 0)
{

}

DiceVarsModel::DiceNode::DiceNode(const diceset &set, QString title, CatNode* parent) :
	AbstractNode(title, parent),
	_set(set)
{

}


DiceVarsModel::CatNode* DiceVarsModel::CatNode::asCatNode() {
	return this;
}

DiceVarsModel::AbstractNode::NodeType DiceVarsModel::CatNode::type() const {
    return NODE_CAT;
}

DiceVarsModel::AbstractNode::NodeType DiceVarsModel::DiceNode::type() const {
    return NODE_SET;
}


QVariant DiceVarsModel::CatNode::represent(int role) const {

    switch (role) {
    case Qt::DisplayRole:
        return _name;
    case Qt::BackgroundRole:
        return _color;
    default:
        return QVariant();
    }

}

QVariant DiceVarsModel::DiceNode::represent(int role) const {
    switch (role) {
    case Qt::DisplayRole:
		return QString(_set.represent_wnr().c_str());
    case Qt::BackgroundRole:
        return _parent->_color;
    default:
        return QVariant();
    }
}
