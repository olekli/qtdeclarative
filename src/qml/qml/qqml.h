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

#ifndef QQML_H
#define QQML_H

#include <QtQml/qqmlprivate.h>
#include <QtQml/qqmlparserstatus.h>
#include <QtQml/qqmlpropertyvaluesource.h>
#include <QtQml/qqmllist.h>

#include <QtCore/qbytearray.h>
#include <QtCore/qmetaobject.h>

QT_BEGIN_HEADER

#define QML_VERSION     0x020000
#define QML_VERSION_STR "2.0"

#define QML_DECLARE_TYPE(TYPE) \
    Q_DECLARE_METATYPE(TYPE *) \
    Q_DECLARE_METATYPE(QQmlListProperty<TYPE>) 

#define QML_DECLARE_TYPE_HASMETATYPE(TYPE) \
    Q_DECLARE_METATYPE(QQmlListProperty<TYPE>) 

#define QML_DECLARE_INTERFACE(INTERFACE) \
    QML_DECLARE_TYPE(INTERFACE)

#define QML_DECLARE_INTERFACE_HASMETATYPE(INTERFACE) \
    QML_DECLARE_TYPE_HASMETATYPE(INTERFACE)

enum { /* TYPEINFO flags */
    QML_HAS_ATTACHED_PROPERTIES = 0x01
};

#define QML_DECLARE_TYPEINFO(TYPE, FLAGS) \
QT_BEGIN_NAMESPACE \
template <> \
class QQmlTypeInfo<TYPE > \
{ \
public: \
    enum { \
        hasAttachedProperties = (((FLAGS) & QML_HAS_ATTACHED_PROPERTIES) == QML_HAS_ATTACHED_PROPERTIES) \
    }; \
}; \
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE


class QQmlPropertyValueInterceptor;

template<typename T>
int qmlRegisterType()
{
    QByteArray name(T::staticMetaObject.className());

    QByteArray pointerName(name + '*');
    QByteArray listName("QQmlListProperty<" + name + '>');

    QQmlPrivate::RegisterType type = {
        0, 

        qRegisterMetaType<T *>(pointerName.constData()),
        qRegisterMetaType<QQmlListProperty<T> >(listName.constData()),
        0, 0,
        QString(),

        0, 0, 0, 0, &T::staticMetaObject,

        QQmlPrivate::attachedPropertiesFunc<T>(),
        QQmlPrivate::attachedPropertiesMetaObject<T>(),

        QQmlPrivate::StaticCastSelector<T,QQmlParserStatus>::cast(), 
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueSource>::cast(),
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueInterceptor>::cast(),

        0, 0,

        0,
        0
    };

    return QQmlPrivate::qmlregister(QQmlPrivate::TypeRegistration, &type);
}

int Q_QML_EXPORT qmlRegisterTypeNotAvailable(const char *uri, int versionMajor, int versionMinor, const char *qmlName, const QString& message);

template<typename T>
int qmlRegisterUncreatableType(const char *uri, int versionMajor, int versionMinor, const char *qmlName, const QString& reason)
{
    QByteArray name(T::staticMetaObject.className());

    QByteArray pointerName(name + '*');
    QByteArray listName("QQmlListProperty<" + name + '>');

    QQmlPrivate::RegisterType type = {
        0,

        qRegisterMetaType<T *>(pointerName.constData()),
        qRegisterMetaType<QQmlListProperty<T> >(listName.constData()),
        0, 0,
        reason,

        uri, versionMajor, versionMinor, qmlName, &T::staticMetaObject,

        QQmlPrivate::attachedPropertiesFunc<T>(),
        QQmlPrivate::attachedPropertiesMetaObject<T>(),

        QQmlPrivate::StaticCastSelector<T,QQmlParserStatus>::cast(),
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueSource>::cast(),
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueInterceptor>::cast(),

        0, 0,

        0,
        0
    };

    return QQmlPrivate::qmlregister(QQmlPrivate::TypeRegistration, &type);
}

template<typename T>
int qmlRegisterType(const char *uri, int versionMajor, int versionMinor, const char *qmlName)
{
    QByteArray name(T::staticMetaObject.className());

    QByteArray pointerName(name + '*');
    QByteArray listName("QQmlListProperty<" + name + '>');

    QQmlPrivate::RegisterType type = {
        0, 

        qRegisterMetaType<T *>(pointerName.constData()),
        qRegisterMetaType<QQmlListProperty<T> >(listName.constData()),
        sizeof(T), QQmlPrivate::createInto<T>,
        QString(),

        uri, versionMajor, versionMinor, qmlName, &T::staticMetaObject,

        QQmlPrivate::attachedPropertiesFunc<T>(),
        QQmlPrivate::attachedPropertiesMetaObject<T>(),

        QQmlPrivate::StaticCastSelector<T,QQmlParserStatus>::cast(), 
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueSource>::cast(),
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueInterceptor>::cast(),

        0, 0,

        0,
        0
    };

    return QQmlPrivate::qmlregister(QQmlPrivate::TypeRegistration, &type);
}

template<typename T, int metaObjectRevision>
int qmlRegisterType(const char *uri, int versionMajor, int versionMinor, const char *qmlName)
{
    QByteArray name(T::staticMetaObject.className());

    QByteArray pointerName(name + '*');
    QByteArray listName("QQmlListProperty<" + name + '>');

    QQmlPrivate::RegisterType type = {
        1,

        qRegisterMetaType<T *>(pointerName.constData()),
        qRegisterMetaType<QQmlListProperty<T> >(listName.constData()),
        sizeof(T), QQmlPrivate::createInto<T>,
        QString(),

        uri, versionMajor, versionMinor, qmlName, &T::staticMetaObject,

        QQmlPrivate::attachedPropertiesFunc<T>(),
        QQmlPrivate::attachedPropertiesMetaObject<T>(),

        QQmlPrivate::StaticCastSelector<T,QQmlParserStatus>::cast(),
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueSource>::cast(),
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueInterceptor>::cast(),

        0, 0,

        0,
        metaObjectRevision
    };

    return QQmlPrivate::qmlregister(QQmlPrivate::TypeRegistration, &type);
}

template<typename T, int metaObjectRevision>
int qmlRegisterRevision(const char *uri, int versionMajor, int versionMinor)
{
    QByteArray name(T::staticMetaObject.className());

    QByteArray pointerName(name + '*');
    QByteArray listName("QQmlListProperty<" + name + '>');

    QQmlPrivate::RegisterType type = {
        1,

        qRegisterMetaType<T *>(pointerName.constData()),
        qRegisterMetaType<QQmlListProperty<T> >(listName.constData()),
        sizeof(T), QQmlPrivate::createInto<T>,
        QString(),

        uri, versionMajor, versionMinor, 0, &T::staticMetaObject,

        QQmlPrivate::attachedPropertiesFunc<T>(),
        QQmlPrivate::attachedPropertiesMetaObject<T>(),

        QQmlPrivate::StaticCastSelector<T,QQmlParserStatus>::cast(),
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueSource>::cast(),
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueInterceptor>::cast(),

        0, 0,

        0,
        metaObjectRevision
    };

    return QQmlPrivate::qmlregister(QQmlPrivate::TypeRegistration, &type);
}


template<typename T, typename E>
int qmlRegisterExtendedType()
{
    QByteArray name(T::staticMetaObject.className());

    QByteArray pointerName(name + '*');
    QByteArray listName("QQmlListProperty<" + name + '>');

    QQmlPrivate::RegisterType type = {
        0, 

        qRegisterMetaType<T *>(pointerName.constData()),
        qRegisterMetaType<QQmlListProperty<T> >(listName.constData()),
        0, 0,
        QString(),

        0, 0, 0, 0, &T::staticMetaObject,

        QQmlPrivate::attachedPropertiesFunc<T>(),
        QQmlPrivate::attachedPropertiesMetaObject<T>(),

        QQmlPrivate::StaticCastSelector<T,QQmlParserStatus>::cast(), 
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueSource>::cast(),
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueInterceptor>::cast(),

        QQmlPrivate::createParent<E>, &E::staticMetaObject,

        0,
        0
    };

    return QQmlPrivate::qmlregister(QQmlPrivate::TypeRegistration, &type);
}

template<typename T, typename E>
int qmlRegisterExtendedType(const char *uri, int versionMajor, int versionMinor, 
                            const char *qmlName)
{
    QByteArray name(T::staticMetaObject.className());

    QByteArray pointerName(name + '*');
    QByteArray listName("QQmlListProperty<" + name + '>');

    QQmlAttachedPropertiesFunc attached = QQmlPrivate::attachedPropertiesFunc<E>();
    const QMetaObject * attachedMetaObject = QQmlPrivate::attachedPropertiesMetaObject<E>(); 
    if (!attached) {
        attached = QQmlPrivate::attachedPropertiesFunc<T>();
        attachedMetaObject = QQmlPrivate::attachedPropertiesMetaObject<T>();
    }

    QQmlPrivate::RegisterType type = {
        0, 

        qRegisterMetaType<T *>(pointerName.constData()),
        qRegisterMetaType<QQmlListProperty<T> >(listName.constData()),
        sizeof(T), QQmlPrivate::createInto<T>,
        QString(),

        uri, versionMajor, versionMinor, qmlName, &T::staticMetaObject,

        attached,
        attachedMetaObject,

        QQmlPrivate::StaticCastSelector<T,QQmlParserStatus>::cast(), 
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueSource>::cast(),
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueInterceptor>::cast(),

        QQmlPrivate::createParent<E>, &E::staticMetaObject,

        0,
        0
    };

    return QQmlPrivate::qmlregister(QQmlPrivate::TypeRegistration, &type);
}

template<typename T>
int qmlRegisterInterface(const char *typeName)
{
    QByteArray name(typeName);

    QByteArray pointerName(name + '*');
    QByteArray listName("QQmlListProperty<" + name + '>');

    QQmlPrivate::RegisterInterface qmlInterface = {
        0,

        qRegisterMetaType<T *>(pointerName.constData()),
        qRegisterMetaType<QQmlListProperty<T> >(listName.constData()),

        qobject_interface_iid<T *>()
    };

    return QQmlPrivate::qmlregister(QQmlPrivate::InterfaceRegistration, &qmlInterface);
}

template<typename T>
int qmlRegisterCustomType(const char *uri, int versionMajor, int versionMinor, 
                          const char *qmlName, QQmlCustomParser *parser)
{
    QByteArray name(T::staticMetaObject.className());

    QByteArray pointerName(name + '*');
    QByteArray listName("QQmlListProperty<" + name + '>');

    QQmlPrivate::RegisterType type = {
        0, 

        qRegisterMetaType<T *>(pointerName.constData()),
        qRegisterMetaType<QQmlListProperty<T> >(listName.constData()),
        sizeof(T), QQmlPrivate::createInto<T>,
        QString(),

        uri, versionMajor, versionMinor, qmlName, &T::staticMetaObject,

        QQmlPrivate::attachedPropertiesFunc<T>(),
        QQmlPrivate::attachedPropertiesMetaObject<T>(),

        QQmlPrivate::StaticCastSelector<T,QQmlParserStatus>::cast(), 
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueSource>::cast(),
        QQmlPrivate::StaticCastSelector<T,QQmlPropertyValueInterceptor>::cast(),

        0, 0,

        parser,
        0
    };

    return QQmlPrivate::qmlregister(QQmlPrivate::TypeRegistration, &type);
}

class QQmlContext;
class QQmlEngine;
class QJSValue;
class QJSEngine;
Q_QML_EXPORT void qmlExecuteDeferred(QObject *);
Q_QML_EXPORT QQmlContext *qmlContext(const QObject *);
Q_QML_EXPORT QQmlEngine *qmlEngine(const QObject *);
Q_QML_EXPORT QObject *qmlAttachedPropertiesObjectById(int, const QObject *, bool create = true);
Q_QML_EXPORT QObject *qmlAttachedPropertiesObject(int *, const QObject *, const QMetaObject *, bool create);

template<typename T>
QObject *qmlAttachedPropertiesObject(const QObject *obj, bool create = true)
{
    static int idx = -1;
    return qmlAttachedPropertiesObject(&idx, obj, &T::staticMetaObject, create);
}

Q_QML_EXPORT void qmlRegisterBaseTypes(const char *uri, int versionMajor, int versionMinor);

inline int qmlRegisterModuleApi(const char *uri, int versionMajor, int versionMinor,
                                QJSValue (*callback)(QQmlEngine *, QJSEngine *))
{
    QQmlPrivate::RegisterModuleApi api = {
        0,

        uri, versionMajor, versionMinor,

        callback, 0, 0
    };

    return QQmlPrivate::qmlregister(QQmlPrivate::ModuleApiRegistration, &api);
}

inline int qmlRegisterModuleApi(const char *uri, int versionMajor, int versionMinor,
                                QObject *(*callback)(QQmlEngine *, QJSEngine *))
{
    QQmlPrivate::RegisterModuleApi api = {
        0,

        uri, versionMajor, versionMinor,

        0, callback, 0 // unknown QObject instance type
    };

    return QQmlPrivate::qmlregister(QQmlPrivate::ModuleApiRegistration, &api);
}

template <typename T>
inline int qmlRegisterModuleApi(const char *uri, int versionMajor, int versionMinor,
                                QObject *(*callback)(QQmlEngine *, QJSEngine *))
{
    QQmlPrivate::RegisterModuleApi api = {
        1,

        uri, versionMajor, versionMinor,

        0, callback, &T::staticMetaObject
    };

    return QQmlPrivate::qmlregister(QQmlPrivate::ModuleApiRegistration, &api);
}

QT_END_NAMESPACE

QML_DECLARE_TYPE(QObject)
Q_DECLARE_METATYPE(QVariant)

QT_END_HEADER

#endif // QQML_H
