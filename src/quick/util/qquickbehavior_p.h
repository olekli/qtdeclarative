/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtQml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QQUICKBEHAVIOR_H
#define QQUICKBEHAVIOR_H

#include <private/qtquickglobal_p.h>

#include <private/qqmlpropertyvalueinterceptor_p.h>
#include <qqml.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QQuickAbstractAnimation;
class QQuickBehaviorPrivate;
class Q_AUTOTEST_EXPORT QQuickBehavior : public QObject, public QQmlPropertyValueInterceptor
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QQuickBehavior)

    Q_INTERFACES(QQmlPropertyValueInterceptor)
    Q_CLASSINFO("DefaultProperty", "animation")
    Q_PROPERTY(QQuickAbstractAnimation *animation READ animation WRITE setAnimation)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_CLASSINFO("DeferredPropertyNames", "animation")

public:
    QQuickBehavior(QObject *parent=0);
    ~QQuickBehavior();

    virtual void setTarget(const QQmlProperty &);
    virtual void write(const QVariant &value);

    QQuickAbstractAnimation *animation();
    void setAnimation(QQuickAbstractAnimation *);

    bool enabled() const;
    void setEnabled(bool enabled);

Q_SIGNALS:
    void enabledChanged();

private Q_SLOTS:
    void componentFinalized();
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickBehavior)

QT_END_HEADER

#endif // QQUICKBEHAVIOR_H
