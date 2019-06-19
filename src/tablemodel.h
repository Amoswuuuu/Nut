﻿/**************************************************************************
**
** This file is part of Nut project.
** https://github.com/HamedMasafi/Nut
**
** Nut is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Nut is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with Nut.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#ifndef TABLESCHEEMA_H
#define TABLESCHEEMA_H

#include <QtCore/QVariant>
#include <QDebug>
#include "defines.h"

class QJsonObject;

NUT_BEGIN_NAMESPACE

class TableModel;
struct FieldModel{
    explicit FieldModel() : name(QString()), length(0), defaultValue(QString()),
        notNull(false), isPrimaryKey(false), isAutoIncrement(false), isUnique(false)
    {

    }

    explicit FieldModel(const QJsonObject &json);

    QString name;
    QMetaType::Type type;
    QString typeName;
    int length;
    QString defaultValue;
    bool notNull;
    bool isPrimaryKey;
    bool isAutoIncrement;
    bool isUnique;
    QString displayName;

    bool operator ==(const FieldModel &f) const{

        bool b = name.toLower() == f.name.toLower()
                && type == f.type
                && length == f.length
                && defaultValue == f.defaultValue
                && notNull == f.notNull;

        return b;
    }

    bool operator !=(const FieldModel &f) const{
        return !(*this == f);
    }

    QJsonObject toJson() const;
};

struct RelationModel{
    RelationModel() : localColumn(QString()), localProperty(QString()),
        slaveTable(nullptr), foreignColumn(QString()), masterTable(nullptr),
        masterClassName(QString())
    {}
    explicit RelationModel(const QJsonObject &obj);

    //slave
    QString localColumn;
    QString localProperty;
    TableModel *slaveTable;
    //master
    QString foreignColumn;
    TableModel *masterTable;

    QString masterClassName;

    QJsonObject toJson() const;
};

bool operator ==(const RelationModel &l, const RelationModel &r);
bool operator !=(const RelationModel &l, const RelationModel &r);

class NUT_EXPORT TableModel
{
public:
    explicit TableModel(int typeId, const QString &tableName = QString());
    explicit TableModel(const QJsonObject &json, const QString &tableName);
    virtual ~TableModel();

    QJsonObject toJson() const;

    FieldModel *field(int n) const;
    FieldModel *field(const QString &name) const;
    RelationModel *foregionKey(const QString &otherTable) const;
    RelationModel *foregionKeyByField(const QString &fieldName) const;

    QString toString() const;

    QString primaryKey() const;
    bool isPrimaryKeyAutoIncrement() const;

    QString name() const;
    void setName(const QString &name);

    QString className() const;
    void setClassName(const QString &className);

    int typeId() const;
    void setTypeId(const int &typeId);
    QList<FieldModel *> fields() const;
    QList<RelationModel *> foregionKeys() const;
    QStringList fieldsNames() const;

    bool operator ==(const TableModel &t) const;
    bool operator !=(const TableModel &t) const;

private:
    QString _name;
    QString _className;
    int _typeId;
    QList<FieldModel*> _fields;
    QList<RelationModel*> _foreignKeys;

    Q_DECL_DEPRECATED
    static QSet<TableModel*>_allModels;
};

NUT_END_NAMESPACE

#endif // TABLESCHEEMA_H
