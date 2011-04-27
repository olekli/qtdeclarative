/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtDeclarative module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QDECLARATIVELISTACCESSOR_H
#define QDECLARATIVELISTACCESSOR_H

#include <QtCore/QVariant>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Declarative)

class QDeclarativeEngine;
class Q_AUTOTEST_EXPORT QDeclarativeListAccessor
{
public:
    QDeclarativeListAccessor();
    ~QDeclarativeListAccessor();

    QVariant list() const;
    void setList(const QVariant &, QDeclarativeEngine * = 0);

    bool isValid() const;

    int count() const;
    QVariant at(int) const;

    enum Type { Invalid, StringList, VariantList, ListProperty, Instance, Integer };
    Type type() const { return m_type; }

private:
    Type m_type;
    QVariant d;
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // QDECLARATIVELISTACCESSOR_H
