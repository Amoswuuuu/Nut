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

#include "abstractquery.h"
#include "abstractquery_p.h"

NUT_BEGIN_NAMESPACE

AbstractQuery::AbstractQuery(QObject *parent) : QObject(parent)
      , d_ptr(new AbstractQueryPrivate(this))
{

}

Nut::AbstractQueryPrivate::AbstractQueryPrivate(Nut::AbstractQuery *parent) :
      q_ptr(parent), skip(0), take(0)
{

}

Nut::AbstractQueryPrivate::~AbstractQueryPrivate()
{

}

NUT_END_NAMESPACE
