/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the V4VM module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef QMLJS_MANAGED_H
#define QMLJS_MANAGED_H

#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QDebug>
#include <wtf/Platform.h>
#include "qv4global.h"

namespace QQmlJS {

namespace VM {

class MemoryManager;
struct String;
struct Object;
struct ObjectPrototype;
struct ExecutionContext;
struct ScriptFunction;

struct BooleanObject;
struct NumberObject;
struct StringObject;
struct ArrayObject;
struct DateObject;
struct FunctionObject;
struct RegExpObject;
struct ErrorObject;
struct ArgumentsObject;
struct JSONObject;
struct ForeachIteratorObject;

struct Q_V4_EXPORT Managed
{
private:
    void *operator new(size_t);
    Managed(const Managed &other);
    void operator = (const Managed &other);

protected:
    Managed()
        : markBit(0)
        , inUse(1)
        , extensible(1)
        , isNonStrictArgumentsObject(0)
        , isBuiltinFunction(0)
        , needsActivation(0)
        , usesArgumentsObject(0)
        , strictMode(0)
        , type(Type_Invalid)
        , subtype(0)
        , stringIdentifier(0)
#if CPU(X86_64)
        , unused(0)
#endif
    {}
    virtual ~Managed();

public:
    void *operator new(size_t size, MemoryManager *mm);
    void operator delete(void *ptr);

    inline void mark() {
        if (markBit)
            return;
        markBit = 1;
        if (type != Type_String)
            markObjects();
    }

    enum Type {
        Type_Invalid,
        Type_String,
        Type_Object,
        Type_ArrayObject,
        Type_FunctionObject,
        Type_BooleanObject,
        Type_NumberObject,
        Type_StringObject,
        Type_DateObject,
        Type_RegExpObject,
        Type_ErrorObject,
        Type_ArgumentsObject,
        Type_JSONObject,
        Type_MathObject,
        Type_ForeachIteratorObject
    };

    String *asString() { return reinterpret_cast<String *>(this); }
    Object *asObject() { return reinterpret_cast<Object *>(this); }
    ArrayObject *asArrayObject() { return type == Type_ArrayObject ? reinterpret_cast<ArrayObject *>(this) : 0; }
    FunctionObject *asFunctionObject() { return type == Type_FunctionObject ? reinterpret_cast<FunctionObject *>(this) : 0; }
    BooleanObject *asBooleanObject() { return type == Type_BooleanObject ? reinterpret_cast<BooleanObject *>(this) : 0; }
    NumberObject *asNumberObject() { return type == Type_NumberObject ? reinterpret_cast<NumberObject *>(this) : 0; }
    StringObject *asStringObject() { return type == Type_StringObject ? reinterpret_cast<StringObject *>(this) : 0; }
    DateObject *asDateObject() { return type == Type_DateObject ? reinterpret_cast<DateObject *>(this) : 0; }
    RegExpObject *asRegExpObject() { return type == Type_RegExpObject ? reinterpret_cast<RegExpObject *>(this) : 0; }
    ErrorObject *asErrorObject() { return type == Type_ErrorObject ? reinterpret_cast<ErrorObject *>(this) : 0; }
    ArgumentsObject *asArgumentsObject() { return type == Type_ArgumentsObject ? reinterpret_cast<ArgumentsObject *>(this) : 0; }
    JSONObject *asJSONObject() { return type == Type_JSONObject ? reinterpret_cast<JSONObject *>(this) : 0; }
    ForeachIteratorObject *asForeachIteratorObject() { return type == Type_ForeachIteratorObject ? reinterpret_cast<ForeachIteratorObject *>(this) : 0; }

    bool isArrayObject() const { return type == Type_ArrayObject; }
    bool isStringObject() const { return type == Type_StringObject; }

    QString className() const;

protected:
    virtual void markObjects() {}

    union {
        Managed *nextFree;
        struct {
            quintptr markBit :  1;
            quintptr inUse   :  1;
            quintptr extensible : 1; // used by Object
            quintptr isNonStrictArgumentsObject : 1;
            quintptr isBuiltinFunction : 1; // used by FunctionObject
            quintptr needsActivation : 1; // used by FunctionObject
            quintptr usesArgumentsObject : 1; // used by FunctionObject
            quintptr strictMode : 1; // used by FunctionObject
            quintptr type : 5;
            mutable quintptr subtype : 3;
            quintptr stringIdentifier : 16;
#if CPU(X86_64)
            quintptr unused  : 32;
#endif
        };
    };

private:
    friend class MemoryManager;
    friend struct ExecutionContext;
};

}
}

#endif
