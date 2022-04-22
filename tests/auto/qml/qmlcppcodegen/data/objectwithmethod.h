/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef OBJECTWITHMETOD_H
#define OBJECTWITHMETOD_H

#include <QtCore/qobject.h>
#include <QtCore/qproperty.h>
#include <QtQml/qqml.h>

// Make objectName available. It doesn't exist on the builtin QtObject type
struct QObjectForeignForObjectName {
    Q_GADGET
    QML_FOREIGN(QObject)
    QML_ANONYMOUS
};

class ObjectWithMethod : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int fff MEMBER theThing BINDABLE theThingBindable FINAL)

public:
    ObjectWithMethod(QObject *parent = nullptr) : QObject(parent) { theThing = 5; }

    Q_INVOKABLE int doThing() const { return theThing; }
    QProperty<int> theThing;
    QBindable<int> theThingBindable() { return QBindable<int>(&theThing); }
};

class OverriddenObjectName : public ObjectWithMethod
{
    Q_OBJECT
    Q_PROPERTY(QString objectName READ objectName WRITE setObjectName BINDABLE objectNameBindable)

    // This shouldn't work
    Q_PROPERTY(int fff READ fff BINDABLE nothingBindable)

public:
    OverriddenObjectName(QObject *parent = nullptr) : ObjectWithMethod(parent)
    {
        m_objectName = u"borschtsch"_qs;
        nothing = 77;
    }

    QString objectName() const { return m_objectName.value(); }
    void setObjectName(const QString &objectName) { m_objectName.setValue(objectName); }
    QBindable<QString> objectNameBindable() { return QBindable<QString>(&m_objectName); }
    Q_INVOKABLE QString doThing() const { return u"7"_qs; }

    int fff() const { return nothing.value(); }
    QBindable<int> nothingBindable() { return QBindable<int>(&nothing); }
private:
    QProperty<int> nothing;
    QProperty<QString> m_objectName;
};

#endif // OBJECTWITHMETHOD_H
