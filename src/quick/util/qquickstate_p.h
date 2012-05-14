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

#ifndef QQUICKSTATE_H
#define QQUICKSTATE_H

#include <qqml.h>
#include <qqmlproperty.h>
#include <QtCore/qobject.h>
#include <QtCore/qsharedpointer.h>
#include <private/qtquickglobal_p.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QQuickActionEvent;
class QQmlAbstractBinding;
class QQmlBinding;
class QQmlExpression;
class QQuickAction
{
public:
    QQuickAction();
    QQuickAction(QObject *, const QString &, const QVariant &);
    QQuickAction(QObject *, const QString &,
                       QQmlContext *, const QVariant &);

    bool restore:1;
    bool actionDone:1;
    bool reverseEvent:1;
    bool deletableToBinding:1;

    QQmlProperty property;
    QVariant fromValue;
    QVariant toValue;

    QQmlAbstractBinding *fromBinding;
    QWeakPointer<QQmlAbstractBinding> toBinding;
    QQuickActionEvent *event;

    //strictly for matching
    QObject *specifiedObject;
    QString specifiedProperty;

    void deleteFromBinding();
};

class Q_AUTOTEST_EXPORT QQuickActionEvent
{
public:
    virtual ~QQuickActionEvent();

    enum EventType { Script, SignalHandler, ParentChange, AnchorChanges };
    enum Reason { ActualChange, FastForward };

    virtual EventType type() const = 0;

    virtual void execute(Reason reason = ActualChange);
    virtual bool isReversable();
    virtual void reverse(Reason reason = ActualChange);
    virtual void saveOriginals() {}
    virtual bool needsCopy() { return false; }
    virtual void copyOriginals(QQuickActionEvent *) {}

    virtual bool isRewindable() { return isReversable(); }
    virtual void rewind() {}
    virtual void saveCurrentValues() {}
    virtual void saveTargetValues() {}

    virtual bool changesBindings();
    virtual void clearBindings();
    virtual bool override(QQuickActionEvent*other);
};

//### rename to QQuickStateChange?
class QQuickStateGroup;
class QQuickState;
class QQuickStateOperationPrivate;
class Q_QUICK_PRIVATE_EXPORT QQuickStateOperation : public QObject
{
    Q_OBJECT
public:
    QQuickStateOperation(QObject *parent = 0)
        : QObject(parent) {}
    typedef QList<QQuickAction> ActionList;

    virtual ActionList actions();

    QQuickState *state() const;
    void setState(QQuickState *state);

protected:
    QQuickStateOperation(QObjectPrivate &dd, QObject *parent = 0);

private:
    Q_DECLARE_PRIVATE(QQuickStateOperation)
    Q_DISABLE_COPY(QQuickStateOperation)
};

typedef QQuickStateOperation::ActionList QQuickStateActions;

class QQuickTransition;
class QQuickStatePrivate;
class Q_QUICK_PRIVATE_EXPORT QQuickState : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QQmlBinding *when READ when WRITE setWhen)
    Q_PROPERTY(QString extend READ extends WRITE setExtends)
    Q_PROPERTY(QQmlListProperty<QQuickStateOperation> changes READ changes)
    Q_CLASSINFO("DefaultProperty", "changes")
    Q_CLASSINFO("DeferredPropertyNames", "changes")

public:
    QQuickState(QObject *parent=0);
    virtual ~QQuickState();

    QString name() const;
    void setName(const QString &);
    bool isNamed() const;

    /*'when' is a QQmlBinding to limit state changes oscillation
     due to the unpredictable order of evaluation of bound expressions*/
    bool isWhenKnown() const;
    QQmlBinding *when() const;
    void setWhen(QQmlBinding *);

    QString extends() const;
    void setExtends(const QString &);

    QQmlListProperty<QQuickStateOperation> changes();
    int operationCount() const;
    QQuickStateOperation *operationAt(int) const;

    QQuickState &operator<<(QQuickStateOperation *);

    void apply(QQuickTransition *, QQuickState *revert);
    void cancel();

    QQuickStateGroup *stateGroup() const;
    void setStateGroup(QQuickStateGroup *);

    bool containsPropertyInRevertList(QObject *target, const QString &name) const;
    bool changeValueInRevertList(QObject *target, const QString &name, const QVariant &revertValue);
    bool changeBindingInRevertList(QObject *target, const QString &name, QQmlAbstractBinding *binding);
    bool removeEntryFromRevertList(QObject *target, const QString &name);
    void addEntryToRevertList(const QQuickAction &action);
    void removeAllEntriesFromRevertList(QObject *target);
    void addEntriesToRevertList(const QList<QQuickAction> &actions);
    QVariant valueInRevertList(QObject *target, const QString &name) const;
    QQmlAbstractBinding *bindingInRevertList(QObject *target, const QString &name) const;

    bool isStateActive() const;

Q_SIGNALS:
    void completed();

private:
    Q_DECLARE_PRIVATE(QQuickState)
    Q_DISABLE_COPY(QQuickState)
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickStateOperation)
QML_DECLARE_TYPE(QQuickState)

QT_END_HEADER

#endif // QQUICKSTATE_H
