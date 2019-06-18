/**************************************************************************
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

#include "table.h"
#include "database.h"
#include "tablesetbase_p.h"
#include "databasemodel.h"
#include "tablesetbasedata.h"

NUT_BEGIN_NAMESPACE

TableSetBase::TableSetBase(Database *parent) : QObject(parent),
    data(new TableSetBaseData(parent))
{
    parent->add(this);
}

TableSetBase::TableSetBase(Table *parent) : QObject(parent),
    data(new TableSetBaseData(parent))
{
    parent->add(this);
}

TableSetBase::~TableSetBase()
{
    foreach (Table *t, data->tables)
        t->setParentTableSet(nullptr);
}

int TableSetBase::save(Database *db, bool cleanUp)
{
    int rowsAffected = 0;
    TableModel *masterModel = nullptr;
    if (data->table)
        masterModel = db->model().tableByClassName(data->table->metaObject()->className());

    foreach (Row<Table> t, data->childRows) {
        if(data->table)
            t->setParentTable(data->table,
                              masterModel,
                              db->model().tableByClassName(t->metaObject()->className()));

        if(t->status() == Table::Added
                || t->status() == Table::Modified
                || t->status() == Table::Deleted){
            rowsAffected += t->save(db);

            if(cleanUp)
                t->deleteLater();
        }
    }

    if (cleanUp)
        data->childRows.clear();

    return rowsAffected;
}

void TableSetBase::clearChilds()
{
#ifndef NUT_SHARED_POINTER
    foreach (Table *t, data->_childRows)
        t->deleteLater();
#endif
    data->childRows.clear();
}

void TableSetBase::add(Row<Table> t)
{
    if(!data->tables.contains(t.data())){
        data->tables.insert(t.data());
        data->childRows.append(t);
    }
}

void TableSetBase::remove(Row<Table> t)
{
    data->tables.remove(t.data());
    data->childRows.removeOne(t);
}

QString TableSetBase::childClassName() const
{
    return data->childClassName;
}

Database *TableSetBase::database() const
{
    return data->database;
}

void TableSetBase::setDatabase(Database *database)
{
    data->database = database;
}

NUT_END_NAMESPACE
