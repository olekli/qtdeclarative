/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the test suite of the Qt Toolkit.
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


#include <QtTest/QtTest>

#include <qjsengine.h>
#include <qjsvalueiterator.h>
#include <qgraphicsitem.h>
#include <qstandarditemmodel.h>
#include <QtCore/qnumeric.h>
#include <stdlib.h>

Q_DECLARE_METATYPE(QList<int>)
Q_DECLARE_METATYPE(QObjectList)

// The JavaScriptCore GC marks the C stack. To try to ensure that there is
// no JSObject* left in stack memory by the compiler, we call this function
// to zap some bytes of memory before calling collectGarbage().
static void zapSomeStack()
{
    char buf[4096];
    memset(buf, 0, sizeof(buf));
}

static void collectGarbage_helper(QJSEngine &eng)
{
    zapSomeStack();
    eng.collectGarbage();
}

class tst_QJSEngine : public QObject
{
    Q_OBJECT

public:
    tst_QJSEngine();
    virtual ~tst_QJSEngine();

private slots:
    void constructWithParent();
#if 0 // FIXME: no QScriptContext
    void currentContext();
    void pushPopContext();
#endif
#if 0 // FIXME: No prototype API in QScriptEngine
    void getSetDefaultPrototype_int();
    void getSetDefaultPrototype_customType();
#endif
#if 0 // FIXME: no QScriptContext
    void newFunction();
    void newFunctionWithArg();
    void newFunctionWithProto();
#endif
    void newObject();
    void newArray();
    void newArray_HooliganTask218092();
    void newArray_HooliganTask233836();
    void newVariant();
#if 0 // FIXME: No prototype API in QScriptEngine
    void newVariant_defaultPrototype();
#endif
#if 0 // ###FIXME: No QVariant object promotion API
    void newVariant_promoteObject();
    void newVariant_replaceValue();
#endif
    void newVariant_valueOfToString();
#if 0 // ###FIXME: No QVariant object promotion API
    void newVariant_promoteNonObject();
    void newVariant_promoteNonQScriptObject();
#endif
    void newRegExp();
    void jsRegExp();
    void newDate();
    void jsParseDate();
    void newQObject();
    void newQObject_ownership();
    void newQObject_promoteObject();
    void newQObject_sameQObject();
#if 0 // FIXME: No prototype API in QScriptEngine
    void newQObject_defaultPrototype();
#endif
    void newQObject_promoteNonObject();
    void newQObject_promoteNonQScriptObject();
#if 0 // ### FIXME: No QScript Metaobject support right now
    void newQMetaObject();
    void newActivationObject();
#endif
#if 0 // ###FIXME: No setGlobalObject support - yay
    void getSetGlobalObjectSimple();
    void getSetGlobalObject();
#endif
    void globalObjectProperties();
    void globalObjectEquals();
    void globalObjectProperties_enumerate();
    void createGlobalObjectProperty();
    void globalObjectGetterSetterProperty();
#if 0 // ###FIXME: No support for setting the global object
    void customGlobalObjectWithPrototype();
#endif
    void globalObjectWithCustomPrototype();
    void builtinFunctionNames_data();
    void builtinFunctionNames();
#if 0 // ###FIXME: No syntax checking result
    void checkSyntax_data();
    void checkSyntax();
#endif
#if 0 // ###FIXME: No support for canEvaluate
    void canEvaluate_data();
    void canEvaluate();
#endif
    void evaluate_data();
    void evaluate();
#if 0 // ###FIXME: no support for c-style callbacks
    void nestedEvaluate();
#endif
#if 0 // ### FIXME: No c-style callbacks
    void uncaughtException();
#endif
    void errorMessage_QT679();
    void valueConversion_basic();
#if 0 // FIXME: No API for custom types
    void valueConversion_customType();
    void valueConversion_sequence();
#endif
    void valueConversion_QVariant();
#if 0 // FIXME: No support for custom types
    void valueConversion_hooliganTask248802();
#endif
    void valueConversion_basic2();
    void valueConversion_dateTime();
    void valueConversion_regExp();
#if 0 // FIXME: No qScriptValueFromValue
    void qScriptValueFromValue_noEngine();
#endif
#if 0 // ###FIXME: No QScriptContext
    void importExtension();
    void infiniteRecursion();
#endif
#if 0 // FIXME: No support for default prototypes
    void castWithPrototypeChain();
#endif
    void castWithMultipleInheritance();
    void collectGarbage();
#if 0 // ###FIXME: no reportAdditionalMemoryCost API
    void reportAdditionalMemoryCost();
#endif
    void gcWithNestedDataStructure();
#if 0 // ###FIXME: No processEvents handling
    void processEventsWhileRunning();
    void processEventsWhileRunning_function();
    void throwErrorFromProcessEvents_data();
    void throwErrorFromProcessEvents();
    void disableProcessEventsInterval();
#endif
    void stacktrace();
    void numberParsing_data();
    void numberParsing();
    void automaticSemicolonInsertion();
#if 0 // ###FIXME: no abortEvaluation API
    void abortEvaluation_notEvaluating();
    void abortEvaluation_data();
    void abortEvaluation();
    void abortEvaluation_tryCatch();
    void abortEvaluation_fromNative();
    void abortEvaluation_QTBUG9433();
#endif
#if 0 // ###FIXME: no QScriptEngine::isEvaluating
    void isEvaluating_notEvaluating();
    void isEvaluating_fromNative();
    void isEvaluating_fromEvent();
#endif
#if 0 // ###FIXME: depracated
    void printFunctionWithCustomHandler();
    void printThrowsException();
#endif
    void errorConstructors();
    void argumentsProperty_globalContext();
    void argumentsProperty_JS();
#if 0 // ###FIXME: no QScriptContext API
    void argumentsProperty_evaluateInNativeFunction();
#endif
    void jsNumberClass();
    void jsForInStatement_simple();
    void jsForInStatement_prototypeProperties();
    void jsForInStatement_mutateWhileIterating();
    void jsForInStatement_arrays();
    void jsForInStatement_nullAndUndefined();
    void jsFunctionDeclarationAsStatement();
    void stringObjects();
    void jsStringPrototypeReplaceBugs();
    void getterSetterThisObject_global();
    void getterSetterThisObject_plain();
    void getterSetterThisObject_prototypeChain();
#if 0 // ###FIXME: no QScriptContext API
    void getterSetterThisObject_activation();
#endif
    void jsContinueInSwitch();
    void jsShadowReadOnlyPrototypeProperty();
    void jsReservedWords_data();
    void jsReservedWords();
    void jsFutureReservedWords_data();
    void jsFutureReservedWords();
    void jsThrowInsideWithStatement();
#if 0 // ###FIXME: No QScriptEngineAgent API
    void getSetAgent_ownership();
    void getSetAgent_deleteAgent();
    void getSetAgent_differentEngine();
#endif
#if 0 // ###FIXME: No QScriptString API
    void reentrancy_stringHandles();
#endif
#if 0 // ###FIXME: No processEventsInterval API
    void reentrancy_processEventsInterval();
#endif
#if 0 // FIXME: No support for custom types
    void reentrancy_typeConversion();
#endif
    void reentrancy_globalObjectProperties();
    void reentrancy_Array();
    void reentrancy_objectCreation();
    void jsIncDecNonObjectProperty();
#if 0 // ###FIXME: no installTranslatorFunctions API
    void installTranslatorFunctions();
    void translateScript_data();
    void translateScript();
    void translateScript_crossScript();
    void translateScript_callQsTrFromNative();
    void translateScript_trNoOp();
    void translateScript_callQsTrFromCpp();
    void translateWithInvalidArgs_data();
    void translateWithInvalidArgs();
    void translationContext_data();
    void translationContext();
    void translateScriptIdBased();
    void translateScriptUnicode_data();
    void translateScriptUnicode();
    void translateScriptUnicodeIdBased_data();
    void translateScriptUnicodeIdBased();
    void translateFromBuiltinCallback();
#endif
#if 0 // ###FIXME: No QScriptValue::scope API
    void functionScopes();
#endif
#if 0 // ###FIXME: No QScriptContext API
    void nativeFunctionScopes();
#endif
#if 0 // ###FIXME: No QScriptProgram API
    void evaluateProgram();
    void evaluateProgram_customScope();
    void evaluateProgram_closure();
    void evaluateProgram_executeLater();
    void evaluateProgram_multipleEngines();
    void evaluateProgram_empty();
#endif
#if 0 // ###FIXME: No QScriptContext API
    void collectGarbageAfterConnect();
    void collectGarbageAfterNativeArguments();
    void promoteThisObjectToQObjectInConstructor();
#endif
#if 0 // ###FIXME: No QScript MetaObject API
    void scriptValueFromQMetaObject();
#endif

    void qRegExpInport_data();
    void qRegExpInport();
#if 0 // ###FIXME: No QScriptContext API
    void reentrency();
#endif
#if 0 // ###FIXME: No QSCriptDeclarativeClass API
    void newFixedStaticScopeObject();
    void newGrowingStaticScopeObject();
#endif
    void dateRoundtripJSQtJS();
    void dateRoundtripQtJSQt();
    void dateConversionJSQt();
    void dateConversionQtJS();
    void functionPrototypeExtensions();
    void threadedEngine();
};

tst_QJSEngine::tst_QJSEngine()
{
}

tst_QJSEngine::~tst_QJSEngine()
{
}

void tst_QJSEngine::constructWithParent()
{
    QPointer<QJSEngine> ptr;
    {
        QObject obj;
        QJSEngine *engine = new QJSEngine(&obj);
        ptr = engine;
    }
    QVERIFY(ptr == 0);
}

#if 0 // FIXME: no QScriptContext
void tst_QJSEngine::currentContext()
{
    QScriptEngine eng;
    QScriptContext *globalCtx = eng.currentContext();
    QVERIFY(globalCtx != 0);
    QVERIFY(globalCtx->parentContext() == 0);
    QCOMPARE(globalCtx->engine(), &eng);
    QCOMPARE(globalCtx->argumentCount(), 0);
    QCOMPARE(globalCtx->backtrace().size(), 1);
    QVERIFY(!globalCtx->isCalledAsConstructor());
    QVERIFY(!globalCtx->callee().isValid());
    QCOMPARE(globalCtx->state(), QScriptContext::NormalState);
    QVERIFY(globalCtx->thisObject().strictlyEquals(eng.globalObject()));
    QVERIFY(globalCtx->activationObject().strictlyEquals(eng.globalObject()));
    QVERIFY(globalCtx->argumentsObject().isObject());
}

void tst_QJSEngine::pushPopContext()
{
    QScriptEngine eng;
    QScriptContext *globalCtx = eng.currentContext();
    QScriptContext *ctx = eng.pushContext();
    QVERIFY(ctx != 0);
    QCOMPARE(ctx->parentContext(), globalCtx);
    QVERIFY(!ctx->isCalledAsConstructor());
    QVERIFY(!ctx->callee().isValid());
    QVERIFY(ctx->thisObject().strictlyEquals(eng.globalObject()));
    QCOMPARE(ctx->argumentCount(), 0);
    QCOMPARE(ctx->backtrace().size(), 2);
    QCOMPARE(ctx->engine(), &eng);
    QCOMPARE(ctx->state(), QScriptContext::NormalState);
    QVERIFY(ctx->activationObject().isObject());
    QVERIFY(ctx->argumentsObject().isObject());

    QScriptContext *ctx2 = eng.pushContext();
    QVERIFY(ctx2 != 0);
    QCOMPARE(ctx2->parentContext(), ctx);
    QVERIFY(!ctx2->activationObject().strictlyEquals(ctx->activationObject()));
    QVERIFY(!ctx2->argumentsObject().strictlyEquals(ctx->argumentsObject()));

    eng.popContext();
    eng.popContext();
    QTest::ignoreMessage(QtWarningMsg, "QScriptEngine::popContext() doesn't match with pushContext()");
    eng.popContext(); // ignored
    QTest::ignoreMessage(QtWarningMsg, "QScriptEngine::popContext() doesn't match with pushContext()");
    eng.popContext(); // ignored
}

static QScriptValue myFunction(QScriptContext *, QScriptEngine *eng)
{
    return eng->nullValue();
}

static QScriptValue myFunctionWithVoidArg(QScriptContext *, QScriptEngine *eng, void *)
{
    return eng->nullValue();
}

static QScriptValue myThrowingFunction(QScriptContext *ctx, QScriptEngine *)
{
    return ctx->throwError("foo");
}

static QScriptValue myFunctionThatReturns(QScriptContext *, QScriptEngine *eng)
{
    return QScriptValue(eng, 42);
}

static QScriptValue myFunctionThatReturnsWithoutEngine(QScriptContext *, QScriptEngine *)
{
    return QScriptValue(1024);
}

static QScriptValue myFunctionThatReturnsWrongEngine(QScriptContext *, QScriptEngine *, void *arg)
{
    QScriptEngine* wrongEngine = reinterpret_cast<QScriptEngine*>(arg);
    return QScriptValue(wrongEngine, 42);
}

static QScriptValue sumFunction(QScriptContext *context, QScriptEngine *engine)
{
    int sum = 0;

    for (int i = 0; i < context->argumentCount(); i++) {
        QScriptValue n = context->argument(i);
        if (n.isNumber())
            sum += n.toInteger();
    }

    return QScriptValue(engine, sum);
}

void tst_QJSEngine::newFunction()
{
    QScriptEngine eng;
    {
        QScriptValue fun = eng.newFunction(myFunction);
        QCOMPARE(fun.isValid(), true);
        QCOMPARE(fun.isCallable(), true);
        QCOMPARE(fun.isObject(), true);
        QCOMPARE(fun.scriptClass(), (QScriptClass*)0);
        // a prototype property is automatically constructed
        {
            QScriptValue prot = fun.property("prototype", QScriptValue::ResolveLocal);
            QVERIFY(prot.isObject());
            QVERIFY(prot.property("constructor").strictlyEquals(fun));
            QCOMPARE(fun.propertyFlags("prototype"), QScriptValue::Undeletable | QScriptValue::SkipInEnumeration);
            QCOMPARE(prot.propertyFlags("constructor"), QScriptValue::SkipInEnumeration);
        }
        // prototype should be Function.prototype
        QCOMPARE(fun.prototype().isValid(), true);
        QCOMPARE(fun.prototype().isCallable(), true);
        QCOMPARE(fun.prototype().strictlyEquals(eng.evaluate("Function.prototype")), true);

        QCOMPARE(fun.call().isNull(), true);
        QCOMPARE(fun.callAsConstructor().isObject(), true);
    }
}

void tst_QJSEngine::newFunctionWithArg()
{
    QScriptEngine eng;
    {
        QScriptValue fun = eng.newFunction(myFunctionWithVoidArg, (void*)this);
        QVERIFY(fun.isCallable());
        QCOMPARE(fun.scriptClass(), (QScriptClass*)0);
        // a prototype property is automatically constructed
        {
            QScriptValue prot = fun.property("prototype", QScriptValue::ResolveLocal);
            QVERIFY(prot.isObject());
            QVERIFY(prot.property("constructor").strictlyEquals(fun));
            QCOMPARE(fun.propertyFlags("prototype"), QScriptValue::Undeletable | QScriptValue::SkipInEnumeration);
            QCOMPARE(prot.propertyFlags("constructor"), QScriptValue::SkipInEnumeration);
        }
        // prototype should be Function.prototype
        QCOMPARE(fun.prototype().isValid(), true);
        QCOMPARE(fun.prototype().isCallable(), true);
        QCOMPARE(fun.prototype().strictlyEquals(eng.evaluate("Function.prototype")), true);

        QCOMPARE(fun.call().isNull(), true);
        QCOMPARE(fun.callAsConstructor().isObject(), true);
    }
}

void tst_QJSEngine::newFunctionWithProto()
{
    QScriptEngine eng;
    {
        QScriptValue proto = eng.newObject();
        QScriptValue fun = eng.newFunction(myFunction, proto);
        QCOMPARE(fun.isValid(), true);
        QCOMPARE(fun.isCallable(), true);
        QCOMPARE(fun.isObject(), true);
        // internal prototype should be Function.prototype
        QCOMPARE(fun.prototype().isValid(), true);
        QCOMPARE(fun.prototype().isCallable(), true);
        QCOMPARE(fun.prototype().strictlyEquals(eng.evaluate("Function.prototype")), true);
        // public prototype should be the one we passed
        QCOMPARE(fun.property("prototype").strictlyEquals(proto), true);
        QCOMPARE(fun.propertyFlags("prototype"), QScriptValue::Undeletable | QScriptValue::SkipInEnumeration);
        QCOMPARE(proto.property("constructor").strictlyEquals(fun), true);
        QCOMPARE(proto.propertyFlags("constructor"), QScriptValue::SkipInEnumeration);

        QCOMPARE(fun.call().isNull(), true);
        QCOMPARE(fun.callAsConstructor().isObject(), true);
    }
    // whether the return value is correct
    {
        QScriptValue fun = eng.newFunction(myFunctionThatReturns);
        QCOMPARE(fun.isValid(), true);
        QCOMPARE(fun.isCallable(), true);
        QCOMPARE(fun.isObject(), true);

        QScriptValue result = fun.call();
        QCOMPARE(result.isNumber(), true);
        QCOMPARE(result.toInt(), 42);
    }
    // whether the return value is assigned to the correct engine
    {
        QScriptValue fun = eng.newFunction(myFunctionThatReturnsWithoutEngine);
        QCOMPARE(fun.isValid(), true);
        QCOMPARE(fun.isCallable(), true);
        QCOMPARE(fun.isObject(), true);

        QScriptValue result = fun.call();
        QCOMPARE(result.engine(), &eng);
        QCOMPARE(result.isNumber(), true);
        QCOMPARE(result.toInt(), 1024);
    }
    // whether the return value is undefined when returning a value with wrong engine
    {
        QScriptEngine wrongEngine;

        QScriptValue fun = eng.newFunction(myFunctionThatReturnsWrongEngine, reinterpret_cast<void *>(&wrongEngine));
        QCOMPARE(fun.isValid(), true);
        QCOMPARE(fun.isCallable(), true);
        QCOMPARE(fun.isObject(), true);

        QTest::ignoreMessage(QtWarningMsg, "QScriptValue::call(): Value from different engine returned from native function, returning undefined value instead.");
        QScriptValue result = fun.call();
        QCOMPARE(result.isValid(), true);
        QCOMPARE(result.isUndefined(), true);
    }
    // checking if arguments are passed correctly
    {
        QScriptEngine wrongEngine;

        QScriptValue fun = eng.newFunction(sumFunction);
        QCOMPARE(fun.isValid(), true);
        QCOMPARE(fun.isCallable(), true);
        QCOMPARE(fun.isObject(), true);

        QScriptValue result = fun.call();
        QCOMPARE(result.isNumber(), true);
        QCOMPARE(result.toInt(), 0);

        result = fun.call(QScriptValue(), QScriptValueList() << 1);
        QCOMPARE(result.isNumber(), true);
        QCOMPARE(result.toInt(), 1);

        result = fun.call(QScriptValue(), QScriptValueList() << 1 << 2 << 3);
        QCOMPARE(result.isNumber(), true);
        QCOMPARE(result.toInt(), 6);

        result = fun.call(QScriptValue(), QScriptValueList() << 1 << 2 << 3 << 4);
        QCOMPARE(result.isNumber(), true);
        QCOMPARE(result.toInt(), 10);
    }
}
#endif

void tst_QJSEngine::newObject()
{
    QJSEngine eng;
    QJSValue object = eng.newObject();
    QCOMPARE(object.isValid(), true);
    QCOMPARE(object.isObject(), true);
    QCOMPARE(object.isCallable(), false);
// ###FIXME: No QScriptClass    QCOMPARE(object.scriptClass(), (QScriptClass*)0);
    // prototype should be Object.prototype
    QCOMPARE(object.prototype().isValid(), true);
    QCOMPARE(object.prototype().isObject(), true);
    QCOMPARE(object.prototype().strictlyEquals(eng.evaluate("Object.prototype")), true);
}

void tst_QJSEngine::newArray()
{
    QJSEngine eng;
    QJSValue array = eng.newArray();
    QCOMPARE(array.isValid(), true);
    QCOMPARE(array.isArray(), true);
    QCOMPARE(array.isObject(), true);
    QVERIFY(!array.isCallable());
// ###FIXME: No QScriptClass    QCOMPARE(array.scriptClass(), (QScriptClass*)0);
    // prototype should be Array.prototype
    QCOMPARE(array.prototype().isValid(), true);
    QCOMPARE(array.prototype().isArray(), true);
    QCOMPARE(array.prototype().strictlyEquals(eng.evaluate("Array.prototype")), true);
}

void tst_QJSEngine::newArray_HooliganTask218092()
{
    QJSEngine eng;
    {
        QJSValue ret = eng.evaluate("[].splice(0, 0, 'a')");
        QVERIFY(ret.isArray());
        QCOMPARE(ret.property("length").toInt(), 0);
    }
    {
        QJSValue ret = eng.evaluate("['a'].splice(0, 1, 'b')");
        QVERIFY(ret.isArray());
        QCOMPARE(ret.property("length").toInt(), 1);
    }
    {
        QJSValue ret = eng.evaluate("['a', 'b'].splice(0, 1, 'c')");
        QVERIFY(ret.isArray());
        QCOMPARE(ret.property("length").toInt(), 1);
    }
    {
        QJSValue ret = eng.evaluate("['a', 'b', 'c'].splice(0, 2, 'd')");
        QVERIFY(ret.isArray());
        QCOMPARE(ret.property("length").toInt(), 2);
    }
    {
        QJSValue ret = eng.evaluate("['a', 'b', 'c'].splice(1, 2, 'd', 'e', 'f')");
        QVERIFY(ret.isArray());
        QCOMPARE(ret.property("length").toInt(), 2);
    }
}

void tst_QJSEngine::newArray_HooliganTask233836()
{
    QJSEngine eng;
    {
        // According to ECMA-262, this should cause a RangeError.
        QJSValue ret = eng.evaluate("a = new Array(4294967295); a.push('foo')");
        QVERIFY(ret.isError() && ret.toString().contains(QLatin1String("RangeError")));
    }
    {
        QJSValue ret = eng.newArray(0xFFFFFFFF);
        QEXPECT_FAIL("", "The maximum length of arrays is defined by v8 currently and differs from QtScript", Abort);
        QCOMPARE(ret.property("length").toUInt(), uint(0xFFFFFFFF));
        ret.setProperty(0xFFFFFFFF, 123);
        QCOMPARE(ret.property("length").toUInt(), uint(0xFFFFFFFF));
        QVERIFY(ret.property(0xFFFFFFFF).isNumber());
        QCOMPARE(ret.property(0xFFFFFFFF).toInt(), 123);
        ret.setProperty(123, 456);
        QCOMPARE(ret.property("length").toUInt(), uint(0xFFFFFFFF));
        QVERIFY(ret.property(123).isNumber());
        QCOMPARE(ret.property(123).toInt(), 456);
    }
}

void tst_QJSEngine::newVariant()
{
    QJSEngine eng;
    {
        QJSValue opaque = eng.newVariant(QVariant());
        QCOMPARE(opaque.isValid(), true);
        QCOMPARE(opaque.isVariant(), true);
        QVERIFY(!opaque.isCallable());
        QCOMPARE(opaque.isObject(), true);
        QCOMPARE(opaque.prototype().isValid(), true);
        QEXPECT_FAIL("", "FIXME: newly created QObject's prototype is an JS Object", Continue);
        QCOMPARE(opaque.prototype().isVariant(), true);
        QVERIFY(opaque.property("valueOf").callWithInstance(opaque).isUndefined());
    }
}

#if 0 // FIXME: No prototype API in QScriptEngine
void tst_QJSEngine::newVariant_defaultPrototype()
{
    // default prototype should be set automatically
    QScriptEngine eng;
    {
        QScriptValue proto = eng.newObject();
        eng.setDefaultPrototype(qMetaTypeId<QString>(), proto);
        QScriptValue ret = eng.newVariant(QVariant(QString::fromLatin1("hello")));
        QVERIFY(ret.isVariant());
// ###FIXME: No QScriptClass        QCOMPARE(ret.scriptClass(), (QScriptClass*)0);
        QVERIFY(ret.prototype().strictlyEquals(proto));
        eng.setDefaultPrototype(qMetaTypeId<QString>(), QScriptValue());
        QScriptValue ret2 = eng.newVariant(QVariant(QString::fromLatin1("hello")));
        QVERIFY(ret2.isVariant());
        QVERIFY(!ret2.prototype().strictlyEquals(proto));
    }
}
#endif

#if 0 // ###FIXME: No QVariant object promotion API
void tst_QJSEngine::newVariant_promoteObject()
{
    // "promote" plain object to variant
    QScriptEngine eng;
    {
        QScriptValue object = eng.newObject();
        object.setProperty("foo", eng.newObject());
        object.setProperty("bar", object.property("foo"));
        QVERIFY(object.property("foo").isObject());
        QVERIFY(!object.property("foo").isVariant());
        QScriptValue originalProto = object.property("foo").prototype();
        QSKIP("It is not possible to promote plain object to a wrapper");
        QScriptValue ret = eng.newVariant(object.property("foo"), QVariant(123));
        QVERIFY(ret.isValid());
        QVERIFY(ret.strictlyEquals(object.property("foo")));
        QVERIFY(ret.isVariant());
        QVERIFY(object.property("foo").isVariant());
        QVERIFY(object.property("bar").isVariant());
        QCOMPARE(ret.toVariant(), QVariant(123));
        QVERIFY(ret.prototype().strictlyEquals(originalProto));
    }
}

void tst_QJSEngine::newVariant_replaceValue()
{
    // replace value of existing object
    QScriptEngine eng;
    {
        QScriptValue object = eng.newVariant(QVariant(123));
        for (int x = 0; x < 2; ++x) {
            QScriptValue ret = eng.newVariant(object, QVariant(456));
            QVERIFY(ret.isValid());
            QVERIFY(ret.strictlyEquals(object));
            QVERIFY(ret.isVariant());
            QCOMPARE(ret.toVariant(), QVariant(456));
        }
    }
}
#endif

void tst_QJSEngine::newVariant_valueOfToString()
{
    // valueOf() and toString()
    QJSEngine eng;
    {
        QJSValue object = eng.newVariant(QVariant(123));
        QJSValue value = object.property("valueOf").callWithInstance(object);
        QVERIFY(value.isNumber());
        QCOMPARE(value.toInt(), 123);
        QCOMPARE(object.toString(), QString::fromLatin1("123"));
        QCOMPARE(object.toVariant().toString(), object.toString());
    }
    {
        QJSValue object = eng.newVariant(QVariant(QString::fromLatin1("hello")));
        QJSValue value = object.property("valueOf").callWithInstance(object);
        QVERIFY(value.isString());
        QCOMPARE(value.toString(), QString::fromLatin1("hello"));
        QCOMPARE(object.toString(), QString::fromLatin1("hello"));
        QCOMPARE(object.toVariant().toString(), object.toString());
    }
    {
        QJSValue object = eng.newVariant(QVariant(false));
        QJSValue value = object.property("valueOf").callWithInstance(object);
        QVERIFY(value.isBool());
        QCOMPARE(value.toBool(), false);
        QCOMPARE(object.toString(), QString::fromLatin1("false"));
        QCOMPARE(object.toVariant().toString(), object.toString());
    }
    {
        QJSValue object = eng.newVariant(QVariant(QPoint(10, 20)));
        QJSValue value = object.property("valueOf").callWithInstance(object);
        QVERIFY(value.isObject());
        QVERIFY(value.strictlyEquals(object));
        QCOMPARE(object.toString(), QString::fromLatin1("QVariant(QPoint)"));
    }
}

#if 0 // ###FIXME: No QVariant object promotion API
void tst_QJSEngine::newVariant_promoteNonObject()
{
    QScriptEngine eng;
    {
        QVariant var(456);
        QScriptValue ret = eng.newVariant(123, var);
        QVERIFY(ret.isVariant());
        QCOMPARE(ret.toVariant(), var);
    }
}

void tst_QJSEngine::newVariant_promoteNonQScriptObject()
{
    QSKIP("This test relay on limitation of QtScript JSC implementation");
    QScriptEngine eng;
    {
        QTest::ignoreMessage(QtWarningMsg, "QScriptEngine::newVariant(): changing class of non-QScriptObject not supported");
        QScriptValue ret = eng.newVariant(eng.newArray(), 123);
        QVERIFY(!ret.isValid());
    }
}
#endif

void tst_QJSEngine::newRegExp()
{
    QSKIP("Test failing - QTBUG-22238");
    QJSEngine eng;
    for (int x = 0; x < 2; ++x) {
        QJSValue rexp;
        if (x == 0)
            rexp = eng.newRegExp("foo", "bar");
        else
            rexp = eng.newRegExp(QRegExp("foo"));
        QCOMPARE(rexp.isValid(), true);
        QCOMPARE(rexp.isRegExp(), true);
        QCOMPARE(rexp.isObject(), true);
        QVERIFY(rexp.isCallable()); // in JSC, RegExp objects are callable
        // prototype should be RegExp.prototype
        QCOMPARE(rexp.prototype().isValid(), true);
        QCOMPARE(rexp.prototype().isObject(), true);
        QCOMPARE(rexp.prototype().isRegExp(), false);
        QCOMPARE(rexp.prototype().strictlyEquals(eng.evaluate("RegExp.prototype")), true);

        QCOMPARE(rexp.toRegExp().pattern(), QRegExp("foo").pattern());
    }
}

void tst_QJSEngine::jsRegExp()
{
    QSKIP("Test failing - QTBUG-22238");

    // See ECMA-262 Section 15.10, "RegExp Objects".
    // These should really be JS-only tests, as they test the implementation's
    // ECMA-compliance, not the C++ API. Compliance should already be covered
    // by the Mozilla tests (qscriptjstestsuite).
    // We can consider updating the expected results of this test if the
    // RegExp implementation changes.

    QJSEngine eng;
    QJSValue r = eng.evaluate("/foo/gim");
    QVERIFY(r.isRegExp());
    QCOMPARE(r.toString(), QString::fromLatin1("/foo/gim"));

    QJSValue rxCtor = eng.globalObject().property("RegExp");
    QJSValue r2 = rxCtor.call(QJSValueList() << r);
    QVERIFY(r2.isRegExp());
    QVERIFY(r2.strictlyEquals(r));

    QJSValue r3 = rxCtor.call(QJSValueList() << r << "gim");
    QVERIFY(r3.isError());
    QVERIFY(r3.toString().contains(QString::fromLatin1("TypeError"))); // Cannot supply flags when constructing one RegExp from another

    QJSValue r4 = rxCtor.call(QJSValueList() << "foo" << "gim");
    QVERIFY(r4.isRegExp());

    QJSValue r5 = rxCtor.callAsConstructor(QJSValueList() << r);
    QVERIFY(r5.isRegExp());
    QCOMPARE(r5.toString(), QString::fromLatin1("/foo/gim"));
    // In JSC, constructing a RegExp from another produces the same identical object.
    // This is different from SpiderMonkey and old back-end.
    QVERIFY(!r5.strictlyEquals(r));

    QEXPECT_FAIL("", "V8 and jsc ignores invalid flags", Continue); //https://bugs.webkit.org/show_bug.cgi?id=41614
    QJSValue r6 = rxCtor.callAsConstructor(QJSValueList() << "foo" << "bar");
    QVERIFY(r6.isError());
    // QVERIFY(r6.toString().contains(QString::fromLatin1("SyntaxError"))); // Invalid regular expression flag


    QJSValue r7 = eng.evaluate("/foo/gimp");
    /*  v8 and jsc ignores invalid flags
    QVERIFY(r7.isError());
    QVERIFY(r7.toString().contains(QString::fromLatin1("SyntaxError"))); // Invalid regular expression flag
    */

    // JSC doesn't complain about duplicate flags.
    QJSValue r8 = eng.evaluate("/foo/migmigmig");
    QVERIFY(r8.isRegExp());
    QCOMPARE(r8.toString(), QString::fromLatin1("/foo/gim"));

    QJSValue r9 = rxCtor.callAsConstructor();
    QVERIFY(r9.isRegExp());
    QCOMPARE(r9.toString(), QString::fromLatin1("/(?:)/"));

    QJSValue r10 = rxCtor.callAsConstructor(QJSValueList() << "" << "gim");
    QVERIFY(r10.isRegExp());
    QCOMPARE(r10.toString(), QString::fromLatin1("/(?:)/gim"));

    QJSValue r11 = rxCtor.callAsConstructor(QJSValueList() << "{1.*}" << "g");
    QVERIFY(r11.isRegExp());
    QCOMPARE(r11.toString(), QString::fromLatin1("/{1.*}/g"));
}

void tst_QJSEngine::newDate()
{
    QJSEngine eng;

    {
        QJSValue date = eng.newDate(0);
        QCOMPARE(date.isValid(), true);
        QCOMPARE(date.isDate(), true);
        QCOMPARE(date.isObject(), true);
        QVERIFY(!date.isCallable());
        // prototype should be Date.prototype
        QCOMPARE(date.prototype().isValid(), true);
        QCOMPARE(date.prototype().isDate(), true);
        QCOMPARE(date.prototype().strictlyEquals(eng.evaluate("Date.prototype")), true);
    }

    {
        QDateTime dt = QDateTime(QDate(1, 2, 3), QTime(4, 5, 6, 7), Qt::LocalTime);
        QJSValue date = eng.newDate(dt);
        QCOMPARE(date.isValid(), true);
        QCOMPARE(date.isDate(), true);
        QCOMPARE(date.isObject(), true);
        // prototype should be Date.prototype
        QCOMPARE(date.prototype().isValid(), true);
        QCOMPARE(date.prototype().isDate(), true);
        QCOMPARE(date.prototype().strictlyEquals(eng.evaluate("Date.prototype")), true);

        QCOMPARE(date.toDateTime(), dt);
    }

    {
        QDateTime dt = QDateTime(QDate(1, 2, 3), QTime(4, 5, 6, 7), Qt::UTC);
        QJSValue date = eng.newDate(dt);
        // toDateTime() result should be in local time
        QCOMPARE(date.toDateTime(), dt.toLocalTime());
    }
}

void tst_QJSEngine::jsParseDate()
{
    QJSEngine eng;
    // Date.parse() should return NaN when it fails
    {
        QJSValue ret = eng.evaluate("Date.parse()");
        QVERIFY(ret.isNumber());
        QVERIFY(qIsNaN(ret.toNumber()));
    }

    // Date.parse() should be able to parse the output of Date().toString()
    {
        QJSValue ret = eng.evaluate("var x = new Date(); var s = x.toString(); s == new Date(Date.parse(s)).toString()");
        QVERIFY(ret.isBool());
        QCOMPARE(ret.toBool(), true);
    }
}

void tst_QJSEngine::newQObject()
{
    QJSEngine eng;

    {
        QJSValue qobject = eng.newQObject(0);
        QCOMPARE(qobject.isValid(), true);
        QCOMPARE(qobject.isNull(), true);
        QCOMPARE(qobject.isObject(), false);
        QCOMPARE(qobject.toQObject(), (QObject *)0);
    }
    {
        QJSValue qobject = eng.newQObject(this);
        QCOMPARE(qobject.isValid(), true);
        QCOMPARE(qobject.isQObject(), true);
        QCOMPARE(qobject.isObject(), true);
        QCOMPARE(qobject.toQObject(), (QObject *)this);
        QVERIFY(!qobject.isCallable());
        // prototype should be QObject.prototype
        QCOMPARE(qobject.prototype().isValid(), true);
        QEXPECT_FAIL("", "FIXME: newly created QObject's prototype is an JS Object", Continue);
        QCOMPARE(qobject.prototype().isQObject(), true);
// ###FIXME: No QScriptClass        QCOMPARE(qobject.scriptClass(), (QScriptClass*)0);
    }
}

void tst_QJSEngine::newQObject_ownership()
{
    QJSEngine eng;
    {
        QPointer<QObject> ptr = new QObject();
        QVERIFY(ptr != 0);
        {
            QJSValue v = eng.newQObject(ptr);
        }
        collectGarbage_helper(eng);
        if (ptr)
            QGuiApplication::sendPostedEvents(ptr, QEvent::DeferredDelete);
        QVERIFY(ptr == 0);
    }
    {
        QPointer<QObject> ptr = new QObject(this);
        QVERIFY(ptr != 0);
        {
            QJSValue v = eng.newQObject(ptr);
        }
        QObject *before = ptr;
        collectGarbage_helper(eng);
        QVERIFY(ptr == before);
        delete ptr;
    }
    {
        QObject *parent = new QObject();
        QObject *child = new QObject(parent);
        QJSValue v = eng.newQObject(child);
        QCOMPARE(v.toQObject(), child);
        delete parent;
        QCOMPARE(v.toQObject(), (QObject *)0);
    }
    {
        QPointer<QObject> ptr = new QObject();
        QVERIFY(ptr != 0);
        {
            QJSValue v = eng.newQObject(ptr);
        }
        collectGarbage_helper(eng);
        // no parent, so it should be like ScriptOwnership
        if (ptr)
            QGuiApplication::sendPostedEvents(ptr, QEvent::DeferredDelete);
        QVERIFY(ptr == 0);
    }
    {
        QObject *parent = new QObject();
        QPointer<QObject> child = new QObject(parent);
        QVERIFY(child != 0);
        {
            QJSValue v = eng.newQObject(child);
        }
        collectGarbage_helper(eng);
        // has parent, so it should be like QtOwnership
        QVERIFY(child != 0);
        delete parent;
    }
}

void tst_QJSEngine::newQObject_promoteObject()
{
#if 0 // ### FIXME: object promotion is not supported
    QScriptEngine eng;
    // "promote" plain object to QObject
    {
        QScriptValue obj = eng.newObject();
        QScriptValue originalProto = obj.prototype();
        QScriptValue ret = eng.newQObject(obj, this);
        QVERIFY(ret.isValid());
        QVERIFY(ret.isQObject());
        QVERIFY(ret.strictlyEquals(obj));
        QVERIFY(obj.isQObject());
        QCOMPARE(ret.toQObject(), (QObject *)this);
        QVERIFY(ret.prototype().strictlyEquals(originalProto));
        QScriptValue val = ret.property("objectName");
        QVERIFY(val.isString());
    }
    // "promote" variant object to QObject
    {
        QScriptValue obj = eng.newVariant(123);
        QVERIFY(obj.isVariant());
        QScriptValue originalProto = obj.prototype();
        QScriptValue ret = eng.newQObject(obj, this);
        QVERIFY(ret.isQObject());
        QVERIFY(ret.strictlyEquals(obj));
        QVERIFY(obj.isQObject());
        QCOMPARE(ret.toQObject(), (QObject *)this);
        QVERIFY(ret.prototype().strictlyEquals(originalProto));
    }
    // replace QObject* of existing object
    {
        QScriptValue object = eng.newVariant(123);
        QScriptValue originalProto = object.prototype();
        QObject otherQObject;
        for (int x = 0; x < 2; ++x) {
            QScriptValue ret = eng.newQObject(object, &otherQObject);
            QVERIFY(ret.isValid());
            QVERIFY(ret.isQObject());
            QVERIFY(ret.strictlyEquals(object));
            QCOMPARE(ret.toQObject(), (QObject *)&otherQObject);
            QVERIFY(ret.prototype().strictlyEquals(originalProto));
        }
    }
#endif
}

void tst_QJSEngine::newQObject_sameQObject()
{
#if 0 // ###FIXME: No QObjectWrapOptions API
    QSKIP("This test strongly relies on strictlyEquals feature that would change in near future");
    QScriptEngine eng;
    // calling newQObject() several times with same object
    for (int x = 0; x < 2; ++x) {
        QObject qobj;
        // the default is to create a new wrapper object
        QScriptValue obj1 = eng.newQObject(&qobj);
        QScriptValue obj2 = eng.newQObject(&qobj);
        QVERIFY(!obj2.strictlyEquals(obj1));

        QScriptEngine::QObjectWrapOptions opt = 0;
        bool preferExisting = (x != 0);
        if (preferExisting)
            opt |= QScriptEngine::PreferExistingWrapperObject;

        QScriptValue obj3 = eng.newQObject(&qobj, QScriptEngine::AutoOwnership, opt);
        QVERIFY(!obj3.strictlyEquals(obj2));
        QScriptValue obj4 = eng.newQObject(&qobj, QScriptEngine::AutoOwnership, opt);
        QCOMPARE(obj4.strictlyEquals(obj3), preferExisting);

        QScriptValue obj5 = eng.newQObject(&qobj, QScriptEngine::ScriptOwnership, opt);
        QVERIFY(!obj5.strictlyEquals(obj4));
        QScriptValue obj6 = eng.newQObject(&qobj, QScriptEngine::ScriptOwnership, opt);
        QCOMPARE(obj6.strictlyEquals(obj5), preferExisting);

        QScriptValue obj7 = eng.newQObject(&qobj, QScriptEngine::ScriptOwnership,
                                           QScriptEngine::ExcludeSuperClassMethods | opt);
        QVERIFY(!obj7.strictlyEquals(obj6));
        QScriptValue obj8 = eng.newQObject(&qobj, QScriptEngine::ScriptOwnership,
                                           QScriptEngine::ExcludeSuperClassMethods | opt);
        QCOMPARE(obj8.strictlyEquals(obj7), preferExisting);
    }
#endif
}

#if 0 // FIXME: No prototype API in QScriptEngine
void tst_QJSEngine::newQObject_defaultPrototype()
{
    QScriptEngine eng;
    // newQObject() should set the default prototype, if one has been registered
    {
        QScriptValue oldQObjectProto = eng.defaultPrototype(qMetaTypeId<QObject*>());

        QScriptValue qobjectProto = eng.newObject();
        eng.setDefaultPrototype(qMetaTypeId<QObject*>(), qobjectProto);
        {
            QScriptValue ret = eng.newQObject(this);
            QVERIFY(ret.prototype().equals(qobjectProto));
        }
        QScriptValue tstProto = eng.newObject();
        int typeId = qRegisterMetaType<tst_QJSEngine*>("tst_QJSEngine*");
        eng.setDefaultPrototype(typeId, tstProto);
        {
            QScriptValue ret = eng.newQObject(this);
            QVERIFY(ret.prototype().equals(tstProto));
        }

        eng.setDefaultPrototype(qMetaTypeId<QObject*>(), oldQObjectProto);
        eng.setDefaultPrototype(typeId, QScriptValue());
    }
}
#endif

void tst_QJSEngine::newQObject_promoteNonObject()
{
#if 0 // ### FIXME: object promotion is not supported
    QScriptEngine eng;
    {
        QScriptValue ret = eng.newQObject(123, this);
        QVERIFY(ret.isQObject());
        QCOMPARE(ret.toQObject(), this);
    }
#endif
}

void tst_QJSEngine::newQObject_promoteNonQScriptObject()
{
#if 0 // ### FIXME: object promotion is not supported
    QSKIP("Promotion of non QScriptObjects kind of works (there is not difference between Object and Array, look at comments in newQObject implementation).");
    QScriptEngine eng;
    {
        QTest::ignoreMessage(QtWarningMsg, "QScriptEngine::newQObject(): changing class of non-QScriptObject not supported");
        QScriptValue ret = eng.newQObject(eng.newArray(), this);
        QVERIFY(!ret.isValid());
    }
#endif
}

#if 0 // ### FIXME: No QScript Metaobject support right now
QT_BEGIN_NAMESPACE
Q_SCRIPT_DECLARE_QMETAOBJECT(QObject, QObject*)
Q_SCRIPT_DECLARE_QMETAOBJECT(QWidget, QWidget*)
QT_END_NAMESPACE

static QScriptValue myConstructor(QScriptContext *ctx, QScriptEngine *eng)
{
    QScriptValue obj;
    if (ctx->isCalledAsConstructor()) {
        obj = ctx->thisObject();
    } else {
        obj = eng->newObject();
        obj.setPrototype(ctx->callee().property("prototype"));
    }
    obj.setProperty("isCalledAsConstructor", QScriptValue(eng, ctx->isCalledAsConstructor()));
    return obj;
}

static QScriptValue instanceofJS(const QScriptValue &inst, const QScriptValue &ctor)
{
    return inst.engine()->evaluate("(function(inst, ctor) { return inst instanceof ctor; })")
        .call(QScriptValueList() << inst << ctor);
}

void tst_QJSEngine::newQMetaObject()
{
    QScriptEngine eng;
#if 0
    QScriptValue qclass = eng.newQMetaObject<QObject>();
    QScriptValue qclass2 = eng.newQMetaObject<QWidget>();
#else
    QScriptValue qclass = qScriptValueFromQMetaObject<QObject>(&eng);
    QScriptValue qclass2 = qScriptValueFromQMetaObject<QWidget>(&eng);
#endif
    QCOMPARE(qclass.isValid(), true);
    QCOMPARE(qclass.isQMetaObject(), true);
    QCOMPARE(qclass.toQMetaObject(), &QObject::staticMetaObject);
    QCOMPARE(qclass.isCallable(), true);
    QVERIFY(qclass.property("prototype").isObject());

    QCOMPARE(qclass2.isValid(), true);
    QCOMPARE(qclass2.isQMetaObject(), true);
    QCOMPARE(qclass2.toQMetaObject(), &QWidget::staticMetaObject);
    QCOMPARE(qclass2.isCallable(), true);
    QVERIFY(qclass2.property("prototype").isObject());

    // prototype should be QMetaObject.prototype
    QCOMPARE(qclass.prototype().isObject(), true);
    QCOMPARE(qclass2.prototype().isObject(), true);

    QScriptValue instance = qclass.callAsConstructor();
    QCOMPARE(instance.isQObject(), true);
    QCOMPARE(instance.toQObject()->metaObject(), qclass.toQMetaObject());
    QEXPECT_FAIL("", "FIXME:  newQMetaObject not implemented properly yet", Abort);
    QVERIFY(instance.instanceOf(qclass));
    QVERIFY(instanceofJS(instance, qclass).strictlyEquals(true));

    QScriptValue instance2 = qclass2.callAsConstructor();
    QCOMPARE(instance2.isQObject(), true);
    QCOMPARE(instance2.toQObject()->metaObject(), qclass2.toQMetaObject());
    QVERIFY(instance2.instanceOf(qclass2));
    QVERIFY(instanceofJS(instance2, qclass2).strictlyEquals(true));
    QVERIFY(!instance2.instanceOf(qclass));
    QVERIFY(instanceofJS(instance2, qclass).strictlyEquals(false));

    QScriptValueList args;
    args << instance;
    QScriptValue instance3 = qclass.callAsConstructor(args);
    QCOMPARE(instance3.isQObject(), true);
    QCOMPARE(instance3.toQObject()->parent(), instance.toQObject());
    QVERIFY(instance3.instanceOf(qclass));
    QVERIFY(instanceofJS(instance3, qclass).strictlyEquals(true));
    QVERIFY(!instance3.instanceOf(qclass2));
    QVERIFY(instanceofJS(instance3, qclass2).strictlyEquals(false));
    args.clear();

    QPointer<QObject> qpointer1 = instance.toQObject();
    QPointer<QObject> qpointer2 = instance2.toQObject();
    QPointer<QObject> qpointer3 = instance3.toQObject();

    QVERIFY(qpointer1);
    QVERIFY(qpointer2);
    QVERIFY(qpointer3);

    // verify that AutoOwnership is in effect
    instance = QScriptValue();
    collectGarbage_helper(eng);

    QVERIFY(!qpointer1);
    QVERIFY(qpointer2);
    QVERIFY(!qpointer3); // was child of instance

    QVERIFY(instance.toQObject() == 0);
    QVERIFY(instance3.toQObject() == 0); // was child of instance
    QVERIFY(instance2.toQObject() != 0);
    instance2 = QScriptValue();
    collectGarbage_helper(eng);
    QVERIFY(instance2.toQObject() == 0);

    // with custom constructor
    QScriptValue ctor = eng.newFunction(myConstructor);
    QScriptValue qclass3 = eng.newQMetaObject(&QObject::staticMetaObject, ctor);
    QVERIFY(qclass3.property("prototype").equals(ctor.property("prototype")));
    {
        QScriptValue ret = qclass3.call();
        QVERIFY(ret.isObject());
        QVERIFY(ret.property("isCalledAsConstructor").isBool());
        QVERIFY(!ret.property("isCalledAsConstructor").toBool());
        QVERIFY(ret.instanceOf(qclass3));
        QVERIFY(instanceofJS(ret, qclass3).strictlyEquals(true));
        QVERIFY(!ret.instanceOf(qclass));
        QVERIFY(instanceofJS(ret, qclass).strictlyEquals(false));
    }
    {
        QScriptValue ret = qclass3.callAsConstructor();
        QVERIFY(ret.isObject());
        QVERIFY(ret.property("isCalledAsConstructor").isBool());
        QVERIFY(ret.property("isCalledAsConstructor").toBool());
        QVERIFY(ret.instanceOf(qclass3));
        QVERIFY(instanceofJS(ret, qclass3).strictlyEquals(true));
        QVERIFY(!ret.instanceOf(qclass2));
        QVERIFY(instanceofJS(ret, qclass2).strictlyEquals(false));
    }

    // subclassing
    qclass2.setProperty("prototype", qclass.callAsConstructor());
    QVERIFY(qclass2.callAsConstructor().instanceOf(qclass));
    QVERIFY(instanceofJS(qclass2.callAsConstructor(), qclass).strictlyEquals(true));

    // with meta-constructor
    QScriptValue qclass4 = eng.newQMetaObject(&QObject::staticMetaObject);
    {
        QScriptValue inst = qclass4.callAsConstructor();
        QVERIFY(inst.isQObject());
        QVERIFY(inst.toQObject() != 0);
        QCOMPARE(inst.toQObject()->parent(), (QObject*)0);
        QVERIFY(inst.instanceOf(qclass4));
        QVERIFY(instanceofJS(inst, qclass4).strictlyEquals(true));
        QVERIFY(!inst.instanceOf(qclass3));
        QVERIFY(instanceofJS(inst, qclass3).strictlyEquals(false));
    }
    {
        QScriptValue inst = qclass4.callAsConstructor(QScriptValueList() << eng.newQObject(this));
        QVERIFY(inst.isQObject());
        QVERIFY(inst.toQObject() != 0);
        QCOMPARE(inst.toQObject()->parent(), (QObject*)this);
        QVERIFY(inst.instanceOf(qclass4));
        QVERIFY(instanceofJS(inst, qclass4).strictlyEquals(true));
        QVERIFY(!inst.instanceOf(qclass2));
        QVERIFY(instanceofJS(inst, qclass2).strictlyEquals(false));
    }
}
#endif

#if 0 // ###FIXME: No activation object support
void tst_QJSEngine::newActivationObject()
{
    QSKIP("internal function not implemented in JSC-based back-end");
    QScriptEngine eng;
    QScriptValue act = eng.newActivationObject();
    QEXPECT_FAIL("", "", Continue);
    QCOMPARE(act.isValid(), true);
    QEXPECT_FAIL("", "", Continue);
    QCOMPARE(act.isObject(), true);
    QVERIFY(!act.isCallable());
    QScriptValue v(&eng, 123);
    act.setProperty("prop", v);
    QEXPECT_FAIL("", "", Continue);
    QCOMPARE(act.property("prop").strictlyEquals(v), true);
    QCOMPARE(act.scope().isValid(), false);
    QEXPECT_FAIL("", "", Continue);
    QVERIFY(act.prototype().isNull());
}
#endif

#if 0 // ###FIXME: No setGlobalObject support - yay
void tst_QJSEngine::getSetGlobalObjectSimple()
{
    QScriptEngine engine;
    QScriptValue object = engine.newObject();
    object.setProperty("foo", 123);
    engine.evaluate("var bar = 100");
    engine.setGlobalObject(object);
    engine.evaluate("rab = 100");
    QVERIFY(engine.globalObject().property("rab").isValid());
    QVERIFY(engine.globalObject().property("foo").isValid());
    QVERIFY(!engine.globalObject().property("bar").isValid());
}

void tst_QJSEngine::getSetGlobalObject()
{
    QScriptEngine eng;
    QScriptValue glob = eng.globalObject();
    glob = QScriptValue(); // kill reference to old global object
    collectGarbage_helper(eng);

    glob = eng.globalObject();
    QCOMPARE(glob.isValid(), true);
    QCOMPARE(glob.isObject(), true);
    QVERIFY(!glob.isCallable());
    QVERIFY(eng.currentContext()->thisObject().strictlyEquals(glob));
    QVERIFY(eng.currentContext()->activationObject().strictlyEquals(glob));
    QEXPECT_FAIL("", "FIXME: Do we really want to enforce this? ECMA standard says that it is implementation dependent, skipping for now", Continue);
    QCOMPARE(glob.toString(), QString::fromLatin1("[object global]"));
    // prototype should be Object.prototype
    QCOMPARE(glob.prototype().isValid(), true);
    QCOMPARE(glob.prototype().isObject(), true);
    QEXPECT_FAIL("", "FIXME: Do we really want to enforce this? ECMA standard says that it is implementation dependent, skipping for now", Continue);
    QCOMPARE(glob.prototype().strictlyEquals(eng.evaluate("Object.prototype")), true);

    eng.setGlobalObject(glob);
    QVERIFY(eng.globalObject().equals(glob));
    eng.setGlobalObject(123);
    QVERIFY(eng.globalObject().equals(glob));

    QScriptValue obj = eng.newObject();
    eng.setGlobalObject(obj);
    QVERIFY(eng.globalObject().strictlyEquals(obj));
    QVERIFY(eng.currentContext()->thisObject().strictlyEquals(obj));
    QVERIFY(eng.currentContext()->activationObject().strictlyEquals(obj));
    QVERIFY(eng.evaluate("this").strictlyEquals(obj));
    QEXPECT_FAIL("", "FIXME: Do we really want to enforce this? ECMA standard says that it is implementation dependent, skipping for now", Continue);
    QCOMPARE(eng.globalObject().toString(), QString::fromLatin1("[object global]"));

    collectGarbage_helper(eng);
    glob = QScriptValue(); // kill reference to old global object
    collectGarbage_helper(eng);
    obj = eng.newObject();
    eng.setGlobalObject(obj);
    QVERIFY(eng.globalObject().strictlyEquals(obj));
    QVERIFY(eng.currentContext()->thisObject().strictlyEquals(obj));
    QVERIFY(eng.currentContext()->activationObject().strictlyEquals(obj));

    collectGarbage_helper(eng);
    QVERIFY(eng.globalObject().strictlyEquals(obj));
    QVERIFY(eng.currentContext()->thisObject().strictlyEquals(obj));
    QVERIFY(eng.currentContext()->activationObject().strictlyEquals(obj));

    QVERIFY(!obj.property("foo").isValid());
    eng.evaluate("var foo = 123");
    {
        QScriptValue ret = obj.property("foo");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 123);
    }

    QVERIFY(!obj.property("bar").isValid());
    eng.evaluate("bar = 456");
    {
        QScriptValue ret = obj.property("bar");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 456);
    }

    QVERIFY(!obj.property("baz").isValid());
    eng.evaluate("this['baz'] = 789");
    {
        QScriptValue ret = obj.property("baz");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 789);
    }

    {
        QScriptValue ret = eng.evaluate("(function() { return this; })()");
        QVERIFY(ret.strictlyEquals(obj));
    }

    // Delete property.
    {
        QScriptValue ret = eng.evaluate("delete foo");
        QVERIFY(ret.isBool());
        QVERIFY(ret.toBool());
        QVERIFY(!obj.property("foo").isValid());
    }

    // Getter/setter property.
    //the custom global object have an interceptor
    QVERIFY(eng.evaluate("this.__defineGetter__('oof', function() { return this.bar; })").isUndefined());
    QVERIFY(eng.evaluate("this.__defineSetter__('oof', function(v) { this.bar = v; })").isUndefined());
    QVERIFY(eng.evaluate("this.__lookupGetter__('oof')").isCallable());
    QVERIFY(eng.evaluate("this.__lookupSetter__('oof')").isCallable());
    eng.evaluate("oof = 123");
    QVERIFY(eng.evaluate("oof").equals(obj.property("bar")));

    // Enumeration.
    {
        QScriptValue ret = eng.evaluate("a = []; for (var p in this) a.push(p); a");
        QCOMPARE(ret.toString(), QString::fromLatin1("bar,baz,oof,p,a"));
    }
}
#endif

#if 0 // ###FIXME: no c-style callbacks
static QScriptValue getSetFoo(QScriptContext *ctx, QScriptEngine *)
{
    if (ctx->argumentCount() > 0)
        ctx->thisObject().setProperty("foo", ctx->argument(0));
    return ctx->thisObject().property("foo");
}
#endif

void tst_QJSEngine::globalObjectProperties()
{
    QSKIP("Test failing - QTBUG-22238");
    // See ECMA-262 Section 15.1, "The Global Object".

    QJSEngine eng;
    QJSValue global = eng.globalObject();

    QVERIFY(global.property("NaN").isNumber());
    QVERIFY(qIsNaN(global.property("NaN").toNumber()));
    QCOMPARE(global.propertyFlags("NaN"), QJSValue::SkipInEnumeration | QJSValue::Undeletable);

    QVERIFY(global.property("Infinity").isNumber());
    QVERIFY(qIsInf(global.property("Infinity").toNumber()));
    QCOMPARE(global.propertyFlags("NaN"), QJSValue::SkipInEnumeration | QJSValue::Undeletable);

    QVERIFY(global.property("undefined").isUndefined());
    QCOMPARE(global.propertyFlags("undefined"), QJSValue::SkipInEnumeration | QJSValue::Undeletable);

    QVERIFY(global.property("eval").isCallable());
    QCOMPARE(global.propertyFlags("eval"), QJSValue::SkipInEnumeration);

    QVERIFY(global.property("parseInt").isCallable());
    QCOMPARE(global.propertyFlags("parseInt"), QJSValue::SkipInEnumeration);

    QVERIFY(global.property("parseFloat").isCallable());
    QCOMPARE(global.propertyFlags("parseFloat"), QJSValue::SkipInEnumeration);

    QVERIFY(global.property("isNaN").isCallable());
    QCOMPARE(global.propertyFlags("isNaN"), QJSValue::SkipInEnumeration);

    QVERIFY(global.property("isFinite").isCallable());
    QCOMPARE(global.propertyFlags("isFinite"), QJSValue::SkipInEnumeration);

    QVERIFY(global.property("decodeURI").isCallable());
    QCOMPARE(global.propertyFlags("decodeURI"), QJSValue::SkipInEnumeration);

    QVERIFY(global.property("decodeURIComponent").isCallable());
    QCOMPARE(global.propertyFlags("decodeURIComponent"), QJSValue::SkipInEnumeration);

    QVERIFY(global.property("encodeURI").isCallable());
    QCOMPARE(global.propertyFlags("encodeURI"), QJSValue::SkipInEnumeration);

    QVERIFY(global.property("encodeURIComponent").isCallable());
    QCOMPARE(global.propertyFlags("encodeURIComponent"), QJSValue::SkipInEnumeration);

    QVERIFY(global.property("Object").isCallable());
    QCOMPARE(global.propertyFlags("Object"), QJSValue::SkipInEnumeration);
    QVERIFY(global.property("Function").isCallable());
    QCOMPARE(global.propertyFlags("Function"), QJSValue::SkipInEnumeration);
    QVERIFY(global.property("Array").isCallable());
    QCOMPARE(global.propertyFlags("Array"), QJSValue::SkipInEnumeration);
    QVERIFY(global.property("String").isCallable());
    QCOMPARE(global.propertyFlags("String"), QJSValue::SkipInEnumeration);
    QVERIFY(global.property("Boolean").isCallable());
    QCOMPARE(global.propertyFlags("Boolean"), QJSValue::SkipInEnumeration);
    QVERIFY(global.property("Number").isCallable());
    QCOMPARE(global.propertyFlags("Number"), QJSValue::SkipInEnumeration);
    QVERIFY(global.property("Date").isCallable());
    QCOMPARE(global.propertyFlags("Date"), QJSValue::SkipInEnumeration);
    QVERIFY(global.property("RegExp").isCallable());
    QCOMPARE(global.propertyFlags("RegExp"), QJSValue::SkipInEnumeration);
    QVERIFY(global.property("Error").isCallable());
    QCOMPARE(global.propertyFlags("Error"), QJSValue::SkipInEnumeration);
    QVERIFY(global.property("EvalError").isCallable());
    QCOMPARE(global.propertyFlags("EvalError"), QJSValue::SkipInEnumeration);
    QVERIFY(global.property("RangeError").isCallable());
    QCOMPARE(global.propertyFlags("RangeError"), QJSValue::SkipInEnumeration);
    QVERIFY(global.property("ReferenceError").isCallable());
    QCOMPARE(global.propertyFlags("ReferenceError"), QJSValue::SkipInEnumeration);
    QVERIFY(global.property("SyntaxError").isCallable());
    QCOMPARE(global.propertyFlags("SyntaxError"), QJSValue::SkipInEnumeration);
    QVERIFY(global.property("TypeError").isCallable());
    QCOMPARE(global.propertyFlags("TypeError"), QJSValue::SkipInEnumeration);
    QVERIFY(global.property("URIError").isCallable());
    QCOMPARE(global.propertyFlags("URIError"), QJSValue::SkipInEnumeration);
    QVERIFY(global.property("Math").isObject());
    QVERIFY(!global.property("Math").isCallable());
    QCOMPARE(global.propertyFlags("Math"), QJSValue::SkipInEnumeration);
}

void tst_QJSEngine::globalObjectEquals()
{
    QJSEngine eng;
    QJSValue o = eng.globalObject();
    QVERIFY(o.strictlyEquals(eng.globalObject()));
    QVERIFY(o.equals(eng.globalObject()));
}

void tst_QJSEngine::globalObjectProperties_enumerate()
{
    QSKIP("Test failing - QTBUG-22238");
    QJSEngine eng;
    QJSValue global = eng.globalObject();

    QSet<QString> expectedNames;
    expectedNames
        << "isNaN"
        << "parseFloat"
        << "String"
        << "EvalError"
        << "URIError"
        << "Math"
        << "encodeURIComponent"
        << "RangeError"
        << "eval"
        << "isFinite"
        << "ReferenceError"
        << "Infinity"
        << "Function"
        << "RegExp"
        << "Number"
        << "parseInt"
        << "Object"
        << "decodeURI"
        << "TypeError"
        << "Boolean"
        << "encodeURI"
        << "NaN"
        << "Error"
        << "decodeURIComponent"
        << "Date"
        << "Array"
        << "escape"
        << "unescape"
        << "SyntaxError"
        << "undefined"
        // JavaScriptCore
        << "JSON"
        // V8
        << "execScript" //execScript for IE compatibility.
        ;
    QSet<QString> actualNames;
    {
        QJSValueIterator it(global);
        while (it.hasNext()) {
            it.next();
            actualNames.insert(it.name());
        }
    }

    QSet<QString> remainingNames = actualNames;
    {
        QSet<QString>::const_iterator it;
        for (it = expectedNames.constBegin(); it != expectedNames.constEnd(); ++it) {
            QString name = *it;
            QVERIFY(actualNames.contains(name));
            remainingNames.remove(name);
        }
    }
    QVERIFY(remainingNames.isEmpty());
}

void tst_QJSEngine::createGlobalObjectProperty()
{
    QJSEngine eng;
    QJSValue global = eng.globalObject();
    // create property with no attributes
    {
        QString name = QString::fromLatin1("foo");
        QVERIFY(!global.property(name).isValid());
        QJSValue val(123);
        global.setProperty(name, val);
        QVERIFY(global.property(name).equals(val));
        QVERIFY(global.propertyFlags(name) == 0);
        global.setProperty(name, QJSValue());
        QVERIFY(!global.property(name).isValid());
    }
    // create property with attributes
#if 0 // ###FIXME: setProperty with flags is not supported
    {
        QString name = QString::fromLatin1("bar");
        QVERIFY(!global.property(name).isValid());
        QScriptValue val(QString::fromLatin1("ciao"));
        QScriptValue::PropertyFlags flags = QScriptValue::ReadOnly | QScriptValue::SkipInEnumeration;
        global.setProperty(name, val, flags);
        QVERIFY(global.property(name).equals(val));
        //QEXPECT_FAIL("", "QTBUG-6134: custom Global Object properties don't retain attributes", Continue);
        QCOMPARE(global.propertyFlags(name), flags);
        global.setProperty(name, QScriptValue());
        QVERIFY(!global.property(name).isValid());
    }
#endif
}

void tst_QJSEngine::globalObjectGetterSetterProperty()
{
#if 0 // ###FIXME: No c-style callbacks
    QScriptEngine engine;
    QScriptValue global = engine.globalObject();
    global.setProperty("bar", engine.newFunction(getSetFoo),
                       QScriptValue::PropertySetter | QScriptValue::PropertyGetter);
    global.setProperty("foo", 123);
    QVERIFY(global.property("bar").equals(global.property("foo")));
    QVERIFY(engine.evaluate("bar").equals(global.property("foo")));
    global.setProperty("bar", 456);
    QVERIFY(global.property("bar").equals(global.property("foo")));

    engine.evaluate("__defineGetter__('baz', function() { return 789; })");
    QVERIFY(engine.evaluate("baz").equals(789));
    QVERIFY(global.property("baz").equals(789));
#endif
}

#if 0 // ###FIXME: No support for setting the global object
void tst_QJSEngine::customGlobalObjectWithPrototype()
{
    for (int x = 0; x < 2; ++x) {
        QScriptEngine engine;
        QScriptValue wrap = engine.newObject();
        QScriptValue global = engine.globalObject();
        QScriptValue originalGlobalProto = global.prototype();
        if (!x) {
            // Set prototype before setting global object
            wrap.setPrototype(global);
            QVERIFY(wrap.prototype().strictlyEquals(global));
            engine.setGlobalObject(wrap);
        } else {
            // Set prototype after setting global object
            engine.setGlobalObject(wrap);
            wrap.setPrototype(global);
            QVERIFY(wrap.prototype().strictlyEquals(global));
        }
        {
            QScriptValue ret = engine.evaluate("print");
            QVERIFY(ret.isCallable());
            QVERIFY(ret.strictlyEquals(wrap.property("print")));
        }
        {
            QScriptValue ret = engine.evaluate("this.print");
            QVERIFY(ret.isCallable());
            QVERIFY(ret.strictlyEquals(wrap.property("print")));
        }
        {
            QScriptValue ret = engine.evaluate("hasOwnProperty('print')");
            QVERIFY(ret.isBool());
            if (x) QEXPECT_FAIL("", "Why?", Continue);
            QVERIFY(!ret.toBool());
        }
        {
            QScriptValue ret = engine.evaluate("this.hasOwnProperty('print')");
            QVERIFY(ret.isBool());
            if (x) QEXPECT_FAIL("", "Why?", Continue);
            QVERIFY(!ret.toBool());
        }

        QScriptValue anotherProto = engine.newObject();
        anotherProto.setProperty("anotherProtoProperty", 123);
        global.setPrototype(anotherProto);
        {
            QScriptValue ret = engine.evaluate("print");
            QVERIFY(ret.isCallable());
            QVERIFY(ret.strictlyEquals(wrap.property("print")));
        }
        {
            QScriptValue ret = engine.evaluate("anotherProtoProperty");
            QVERIFY(ret.isNumber());
            QVERIFY(ret.strictlyEquals(wrap.property("anotherProtoProperty")));
        }
        {
            QScriptValue ret = engine.evaluate("this.anotherProtoProperty");
            QVERIFY(ret.isNumber());
            QVERIFY(ret.strictlyEquals(wrap.property("anotherProtoProperty")));
        }

        wrap.setPrototype(anotherProto);
        {
            QScriptValue ret = engine.evaluate("print");
            QVERIFY(ret.isError());
            QCOMPARE(ret.toString(), QString::fromLatin1("ReferenceError: print is not defined"));
        }
        {
            QScriptValue ret = engine.evaluate("anotherProtoProperty");
            QVERIFY(ret.isNumber());
            QVERIFY(ret.strictlyEquals(wrap.property("anotherProtoProperty")));
        }
        QVERIFY(global.prototype().strictlyEquals(anotherProto));

        global.setPrototype(originalGlobalProto);
        engine.setGlobalObject(global);
        {
            QScriptValue ret = engine.evaluate("anotherProtoProperty");
            QVERIFY(ret.isError());
            QVERIFY(ret.toString().startsWith("ReferenceError: "));
        }
        {
            QScriptValue ret = engine.evaluate("print");
            QVERIFY(ret.isCallable());
            QVERIFY(ret.strictlyEquals(global.property("print")));
        }
        QVERIFY(!anotherProto.property("print").isValid());
    }
}
#endif

void tst_QJSEngine::globalObjectWithCustomPrototype()
{
    QJSEngine engine;
    QJSValue proto = engine.newObject();
    proto.setProperty("protoProperty", 123);
    QJSValue global = engine.globalObject();
    QJSValue originalProto = global.prototype();
    global.setPrototype(proto);
    {
        QJSValue ret = engine.evaluate("protoProperty");
        QEXPECT_FAIL("", "Replacing the prototype of the global object is currently unsupported (see also v8 issue 1078)", Abort);
        QVERIFY(ret.isNumber());
        QVERIFY(ret.strictlyEquals(global.property("protoProperty")));
    }
    {
        QJSValue ret = engine.evaluate("this.protoProperty");
        QVERIFY(ret.isNumber());
        QVERIFY(ret.strictlyEquals(global.property("protoProperty")));
    }
    {
        QJSValue ret = engine.evaluate("hasOwnProperty('protoProperty')");
        QVERIFY(ret.isBool());
        QVERIFY(!ret.toBool());
    }
    {
        QJSValue ret = engine.evaluate("this.hasOwnProperty('protoProperty')");
        QVERIFY(ret.isBool());
        QVERIFY(!ret.toBool());
    }

    // Custom prototype set from JS
    {
        QJSValue ret = engine.evaluate("this.__proto__ = { 'a': 123 }; a");
        QVERIFY(ret.isNumber());
        QVERIFY(ret.strictlyEquals(global.property("a")));
    }
}

void tst_QJSEngine::builtinFunctionNames_data()
{
    QTest::addColumn<QString>("expression");
    QTest::addColumn<QString>("expectedName");

    // See ECMA-262 Chapter 15, "Standard Built-in ECMAScript Objects".

    QTest::newRow("parseInt") << QString("parseInt") << QString("parseInt");
    QTest::newRow("parseFloat") << QString("parseFloat") << QString("parseFloat");
    QTest::newRow("isNaN") << QString("isNaN") << QString("isNaN");
    QTest::newRow("isFinite") << QString("isFinite") << QString("isFinite");
    QTest::newRow("decodeURI") << QString("decodeURI") << QString("decodeURI");
    QTest::newRow("decodeURIComponent") << QString("decodeURIComponent") << QString("decodeURIComponent");
    QTest::newRow("encodeURI") << QString("encodeURI") << QString("encodeURI");
    QTest::newRow("encodeURIComponent") << QString("encodeURIComponent") << QString("encodeURIComponent");
    QTest::newRow("escape") << QString("escape") << QString("escape");
    QTest::newRow("unescape") << QString("unescape") << QString("unescape");

    QTest::newRow("Array") << QString("Array") << QString("Array");
    QTest::newRow("Array.prototype.toString") << QString("Array.prototype.toString") << QString("toString");
    QTest::newRow("Array.prototype.toLocaleString") << QString("Array.prototype.toLocaleString") << QString("toLocaleString");
    QTest::newRow("Array.prototype.concat") << QString("Array.prototype.concat") << QString("concat");
    QTest::newRow("Array.prototype.join") << QString("Array.prototype.join") << QString("join");
    QTest::newRow("Array.prototype.pop") << QString("Array.prototype.pop") << QString("pop");
    QTest::newRow("Array.prototype.push") << QString("Array.prototype.push") << QString("push");
    QTest::newRow("Array.prototype.reverse") << QString("Array.prototype.reverse") << QString("reverse");
    QTest::newRow("Array.prototype.shift") << QString("Array.prototype.shift") << QString("shift");
    QTest::newRow("Array.prototype.slice") << QString("Array.prototype.slice") << QString("slice");
    QTest::newRow("Array.prototype.sort") << QString("Array.prototype.sort") << QString("sort");
    QTest::newRow("Array.prototype.splice") << QString("Array.prototype.splice") << QString("splice");
    QTest::newRow("Array.prototype.unshift") << QString("Array.prototype.unshift") << QString("unshift");

    QTest::newRow("Boolean") << QString("Boolean") << QString("Boolean");
    QTest::newRow("Boolean.prototype.toString") << QString("Boolean.prototype.toString") << QString("toString");

    QTest::newRow("Date") << QString("Date") << QString("Date");
    QTest::newRow("Date.prototype.toString") << QString("Date.prototype.toString") << QString("toString");
    QTest::newRow("Date.prototype.toDateString") << QString("Date.prototype.toDateString") << QString("toDateString");
    QTest::newRow("Date.prototype.toTimeString") << QString("Date.prototype.toTimeString") << QString("toTimeString");
    QTest::newRow("Date.prototype.toLocaleString") << QString("Date.prototype.toLocaleString") << QString("toLocaleString");
    QTest::newRow("Date.prototype.toLocaleDateString") << QString("Date.prototype.toLocaleDateString") << QString("toLocaleDateString");
    QTest::newRow("Date.prototype.toLocaleTimeString") << QString("Date.prototype.toLocaleTimeString") << QString("toLocaleTimeString");
    QTest::newRow("Date.prototype.valueOf") << QString("Date.prototype.valueOf") << QString("valueOf");
    QTest::newRow("Date.prototype.getTime") << QString("Date.prototype.getTime") << QString("getTime");
    QTest::newRow("Date.prototype.getYear") << QString("Date.prototype.getYear") << QString("getYear");
    QTest::newRow("Date.prototype.getFullYear") << QString("Date.prototype.getFullYear") << QString("getFullYear");
    QTest::newRow("Date.prototype.getUTCFullYear") << QString("Date.prototype.getUTCFullYear") << QString("getUTCFullYear");
    QTest::newRow("Date.prototype.getMonth") << QString("Date.prototype.getMonth") << QString("getMonth");
    QTest::newRow("Date.prototype.getUTCMonth") << QString("Date.prototype.getUTCMonth") << QString("getUTCMonth");
    QTest::newRow("Date.prototype.getDate") << QString("Date.prototype.getDate") << QString("getDate");
    QTest::newRow("Date.prototype.getUTCDate") << QString("Date.prototype.getUTCDate") << QString("getUTCDate");
    QTest::newRow("Date.prototype.getDay") << QString("Date.prototype.getDay") << QString("getDay");
    QTest::newRow("Date.prototype.getUTCDay") << QString("Date.prototype.getUTCDay") << QString("getUTCDay");
    QTest::newRow("Date.prototype.getHours") << QString("Date.prototype.getHours") << QString("getHours");
    QTest::newRow("Date.prototype.getUTCHours") << QString("Date.prototype.getUTCHours") << QString("getUTCHours");
    QTest::newRow("Date.prototype.getMinutes") << QString("Date.prototype.getMinutes") << QString("getMinutes");
    QTest::newRow("Date.prototype.getUTCMinutes") << QString("Date.prototype.getUTCMinutes") << QString("getUTCMinutes");
    QTest::newRow("Date.prototype.getSeconds") << QString("Date.prototype.getSeconds") << QString("getSeconds");
    QTest::newRow("Date.prototype.getUTCSeconds") << QString("Date.prototype.getUTCSeconds") << QString("getUTCSeconds");
    QTest::newRow("Date.prototype.getMilliseconds") << QString("Date.prototype.getMilliseconds") << QString("getMilliseconds");
    QTest::newRow("Date.prototype.getUTCMilliseconds") << QString("Date.prototype.getUTCMilliseconds") << QString("getUTCMilliseconds");
    QTest::newRow("Date.prototype.getTimezoneOffset") << QString("Date.prototype.getTimezoneOffset") << QString("getTimezoneOffset");
    QTest::newRow("Date.prototype.setTime") << QString("Date.prototype.setTime") << QString("setTime");
    QTest::newRow("Date.prototype.setMilliseconds") << QString("Date.prototype.setMilliseconds") << QString("setMilliseconds");
    QTest::newRow("Date.prototype.setUTCMilliseconds") << QString("Date.prototype.setUTCMilliseconds") << QString("setUTCMilliseconds");
    QTest::newRow("Date.prototype.setSeconds") << QString("Date.prototype.setSeconds") << QString("setSeconds");
    QTest::newRow("Date.prototype.setUTCSeconds") << QString("Date.prototype.setUTCSeconds") << QString("setUTCSeconds");
    QTest::newRow("Date.prototype.setMinutes") << QString("Date.prototype.setMinutes") << QString("setMinutes");
    QTest::newRow("Date.prototype.setUTCMinutes") << QString("Date.prototype.setUTCMinutes") << QString("setUTCMinutes");
    QTest::newRow("Date.prototype.setHours") << QString("Date.prototype.setHours") << QString("setHours");
    QTest::newRow("Date.prototype.setUTCHours") << QString("Date.prototype.setUTCHours") << QString("setUTCHours");
    QTest::newRow("Date.prototype.setDate") << QString("Date.prototype.setDate") << QString("setDate");
    QTest::newRow("Date.prototype.setUTCDate") << QString("Date.prototype.setUTCDate") << QString("setUTCDate");
    QTest::newRow("Date.prototype.setMonth") << QString("Date.prototype.setMonth") << QString("setMonth");
    QTest::newRow("Date.prototype.setUTCMonth") << QString("Date.prototype.setUTCMonth") << QString("setUTCMonth");
    QTest::newRow("Date.prototype.setYear") << QString("Date.prototype.setYear") << QString("setYear");
    QTest::newRow("Date.prototype.setFullYear") << QString("Date.prototype.setFullYear") << QString("setFullYear");
    QTest::newRow("Date.prototype.setUTCFullYear") << QString("Date.prototype.setUTCFullYear") << QString("setUTCFullYear");
    QTest::newRow("Date.prototype.toUTCString") << QString("Date.prototype.toUTCString") << QString("toUTCString");
    QTest::newRow("Date.prototype.toGMTString") << QString("Date.prototype.toGMTString") << QString("toGMTString");

    QTest::newRow("Error") << QString("Error") << QString("Error");
//    QTest::newRow("Error.prototype.backtrace") << QString("Error.prototype.backtrace") << QString("backtrace");
    QTest::newRow("Error.prototype.toString") << QString("Error.prototype.toString") << QString("toString");

    QTest::newRow("EvalError") << QString("EvalError") << QString("EvalError");
    QTest::newRow("RangeError") << QString("RangeError") << QString("RangeError");
    QTest::newRow("ReferenceError") << QString("ReferenceError") << QString("ReferenceError");
    QTest::newRow("SyntaxError") << QString("SyntaxError") << QString("SyntaxError");
    QTest::newRow("TypeError") << QString("TypeError") << QString("TypeError");
    QTest::newRow("URIError") << QString("URIError") << QString("URIError");

    QTest::newRow("Function") << QString("Function") << QString("Function");
    QTest::newRow("Function.prototype.toString") << QString("Function.prototype.toString") << QString("toString");
    QTest::newRow("Function.prototype.apply") << QString("Function.prototype.apply") << QString("apply");
    QTest::newRow("Function.prototype.call") << QString("Function.prototype.call") << QString("call");
/*  In V8, those function are only there for signals
    QTest::newRow("Function.prototype.connect") << QString("Function.prototype.connect") << QString("connect");
    QTest::newRow("Function.prototype.disconnect") << QString("Function.prototype.disconnect") << QString("disconnect");*/

    QTest::newRow("Math.abs") << QString("Math.abs") << QString("abs");
    QTest::newRow("Math.acos") << QString("Math.acos") << QString("acos");
    QTest::newRow("Math.asin") << QString("Math.asin") << QString("asin");
    QTest::newRow("Math.atan") << QString("Math.atan") << QString("atan");
    QTest::newRow("Math.atan2") << QString("Math.atan2") << QString("atan2");
    QTest::newRow("Math.ceil") << QString("Math.ceil") << QString("ceil");
    QTest::newRow("Math.cos") << QString("Math.cos") << QString("cos");
    QTest::newRow("Math.exp") << QString("Math.exp") << QString("exp");
    QTest::newRow("Math.floor") << QString("Math.floor") << QString("floor");
    QTest::newRow("Math.log") << QString("Math.log") << QString("log");
    QTest::newRow("Math.max") << QString("Math.max") << QString("max");
    QTest::newRow("Math.min") << QString("Math.min") << QString("min");
    QTest::newRow("Math.pow") << QString("Math.pow") << QString("pow");
    QTest::newRow("Math.random") << QString("Math.random") << QString("random");
    QTest::newRow("Math.round") << QString("Math.round") << QString("round");
    QTest::newRow("Math.sin") << QString("Math.sin") << QString("sin");
    QTest::newRow("Math.sqrt") << QString("Math.sqrt") << QString("sqrt");
    QTest::newRow("Math.tan") << QString("Math.tan") << QString("tan");

    QTest::newRow("Number") << QString("Number") << QString("Number");
    QTest::newRow("Number.prototype.toString") << QString("Number.prototype.toString") << QString("toString");
    QTest::newRow("Number.prototype.toLocaleString") << QString("Number.prototype.toLocaleString") << QString("toLocaleString");
    QTest::newRow("Number.prototype.valueOf") << QString("Number.prototype.valueOf") << QString("valueOf");
    QTest::newRow("Number.prototype.toFixed") << QString("Number.prototype.toFixed") << QString("toFixed");
    QTest::newRow("Number.prototype.toExponential") << QString("Number.prototype.toExponential") << QString("toExponential");
    QTest::newRow("Number.prototype.toPrecision") << QString("Number.prototype.toPrecision") << QString("toPrecision");

    QTest::newRow("Object") << QString("Object") << QString("Object");
    QTest::newRow("Object.prototype.toString") << QString("Object.prototype.toString") << QString("toString");
    QTest::newRow("Object.prototype.toLocaleString") << QString("Object.prototype.toLocaleString") << QString("toLocaleString");
    QTest::newRow("Object.prototype.valueOf") << QString("Object.prototype.valueOf") << QString("valueOf");
    QTest::newRow("Object.prototype.hasOwnProperty") << QString("Object.prototype.hasOwnProperty") << QString("hasOwnProperty");
    QTest::newRow("Object.prototype.isPrototypeOf") << QString("Object.prototype.isPrototypeOf") << QString("isPrototypeOf");
    QTest::newRow("Object.prototype.propertyIsEnumerable") << QString("Object.prototype.propertyIsEnumerable") << QString("propertyIsEnumerable");
    QTest::newRow("Object.prototype.__defineGetter__") << QString("Object.prototype.__defineGetter__") << QString("__defineGetter__");
    QTest::newRow("Object.prototype.__defineSetter__") << QString("Object.prototype.__defineSetter__") << QString("__defineSetter__");

    QTest::newRow("RegExp") << QString("RegExp") << QString("RegExp");
    QTest::newRow("RegExp.prototype.exec") << QString("RegExp.prototype.exec") << QString("exec");
    QTest::newRow("RegExp.prototype.test") << QString("RegExp.prototype.test") << QString("test");
    QTest::newRow("RegExp.prototype.toString") << QString("RegExp.prototype.toString") << QString("toString");

    QTest::newRow("String") << QString("String") << QString("String");
    QTest::newRow("String.prototype.toString") << QString("String.prototype.toString") << QString("toString");
    QTest::newRow("String.prototype.valueOf") << QString("String.prototype.valueOf") << QString("valueOf");
    QTest::newRow("String.prototype.charAt") << QString("String.prototype.charAt") << QString("charAt");
    QTest::newRow("String.prototype.charCodeAt") << QString("String.prototype.charCodeAt") << QString("charCodeAt");
    QTest::newRow("String.prototype.concat") << QString("String.prototype.concat") << QString("concat");
    QTest::newRow("String.prototype.indexOf") << QString("String.prototype.indexOf") << QString("indexOf");
    QTest::newRow("String.prototype.lastIndexOf") << QString("String.prototype.lastIndexOf") << QString("lastIndexOf");
    QTest::newRow("String.prototype.localeCompare") << QString("String.prototype.localeCompare") << QString("localeCompare");
    QTest::newRow("String.prototype.match") << QString("String.prototype.match") << QString("match");
    QTest::newRow("String.prototype.replace") << QString("String.prototype.replace") << QString("replace");
    QTest::newRow("String.prototype.search") << QString("String.prototype.search") << QString("search");
    QTest::newRow("String.prototype.slice") << QString("String.prototype.slice") << QString("slice");
    QTest::newRow("String.prototype.split") << QString("String.prototype.split") << QString("split");
    QTest::newRow("String.prototype.substring") << QString("String.prototype.substring") << QString("substring");
    QTest::newRow("String.prototype.toLowerCase") << QString("String.prototype.toLowerCase") << QString("toLowerCase");
    QTest::newRow("String.prototype.toLocaleLowerCase") << QString("String.prototype.toLocaleLowerCase") << QString("toLocaleLowerCase");
    QTest::newRow("String.prototype.toUpperCase") << QString("String.prototype.toUpperCase") << QString("toUpperCase");
    QTest::newRow("String.prototype.toLocaleUpperCase") << QString("String.prototype.toLocaleUpperCase") << QString("toLocaleUpperCase");
}

void tst_QJSEngine::builtinFunctionNames()
{
    QFETCH(QString, expression);
    QFETCH(QString, expectedName);
    QJSEngine eng;
    // The "name" property is actually non-standard, but JSC supports it.
    QJSValue ret = eng.evaluate(QString::fromLatin1("%0.name").arg(expression));
    QVERIFY(ret.isString());
    QCOMPARE(ret.toString(), expectedName);
}

#if 0 // ###FIXME: No syntax checking result
void tst_QJSEngine::checkSyntax_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<int>("expectedState");
    QTest::addColumn<int>("errorLineNumber");
    QTest::addColumn<int>("errorColumnNumber");
    QTest::addColumn<QString>("errorMessage");

    QTest::newRow("0")
        << QString("0") << int(QScriptSyntaxCheckResult::Valid)
        << -1 << -1 << "";
    QTest::newRow("if (")
        << QString("if (\n") << int(QScriptSyntaxCheckResult::Intermediate)
        << 0 << -1 << "Uncaught SyntaxError: Unexpected end of input";
    QTest::newRow("if else")
        << QString("\nif else") << int(QScriptSyntaxCheckResult::Error)
        << 2 << 3 << "Uncaught SyntaxError: Unexpected token else";
    QTest::newRow("foo[")
        << QString("foo[") << int(QScriptSyntaxCheckResult::Intermediate)
        << 1 << 4 << "Uncaught SyntaxError: Unexpected end of input";
    QTest::newRow("foo['bar']")
        << QString("foo['bar']") << int(QScriptSyntaxCheckResult::Valid)
        << -1 << -1 << "";

    QTest::newRow("/*")
        << QString("/*") << int(QScriptSyntaxCheckResult::Error)
        << 1 << 0 << "Uncaught SyntaxError: Unexpected token ILLEGAL";
    QTest::newRow("/*\nMy comment")
        << QString("/*\nMy comment") << int(QScriptSyntaxCheckResult::Error)
        << 1 << 0 << "Uncaught SyntaxError: Unexpected token ILLEGAL";
    QTest::newRow("/*\nMy comment */\nfoo = 10")
        << QString("/*\nMy comment */\nfoo = 10") << int(QScriptSyntaxCheckResult::Valid)
        << -1 << -1 << "";
    QTest::newRow("foo = 10 /*")
        << QString("foo = 10 /*") << int(QScriptSyntaxCheckResult::Error)
        << 1 << 9 << "Uncaught SyntaxError: Unexpected token ILLEGAL";
    QTest::newRow("foo = 10; /*")
        << QString("foo = 10; /*") << int(QScriptSyntaxCheckResult::Error)
        << 1 << 10 << "Uncaught SyntaxError: Unexpected token ILLEGAL";
    QTest::newRow("foo = 10 /* My comment */")
        << QString("foo = 10 /* My comment */") << int(QScriptSyntaxCheckResult::Valid)
        << -1 << -1 << "";

    QTest::newRow("/=/")
        << QString("/=/") << int(QScriptSyntaxCheckResult::Valid) << -1 << -1 << "";
    QTest::newRow("/=/g")
        << QString("/=/g") << int(QScriptSyntaxCheckResult::Valid) << -1 << -1 << "";
    QTest::newRow("/a/")
        << QString("/a/") << int(QScriptSyntaxCheckResult::Valid) << -1 << -1 << "";
    QTest::newRow("/a/g")
        << QString("/a/g") << int(QScriptSyntaxCheckResult::Valid) << -1 << -1 << "";
}

void tst_QJSEngine::checkSyntax()
{
    QFETCH(QString, code);
    QFETCH(int, expectedState);
    QFETCH(int, errorLineNumber);
    QFETCH(int, errorColumnNumber);
    QFETCH(QString, errorMessage);

    QScriptSyntaxCheckResult result = QScriptEngine::checkSyntax(code);
    QCOMPARE(int(result.state()), expectedState);
    QCOMPARE(result.errorLineNumber(), errorLineNumber);
    QCOMPARE(result.errorColumnNumber(), errorColumnNumber);
    QCOMPARE(result.errorMessage(), errorMessage);

    // assignment
    {
        QScriptSyntaxCheckResult copy = result;
        QCOMPARE(copy.state(), result.state());
        QCOMPARE(copy.errorLineNumber(), result.errorLineNumber());
        QCOMPARE(copy.errorColumnNumber(), result.errorColumnNumber());
        QCOMPARE(copy.errorMessage(), result.errorMessage());
    }
    {
        QScriptSyntaxCheckResult copy(result);
        QCOMPARE(copy.state(), result.state());
        QCOMPARE(copy.errorLineNumber(), result.errorLineNumber());
        QCOMPARE(copy.errorColumnNumber(), result.errorColumnNumber());
        QCOMPARE(copy.errorMessage(), result.errorMessage());
    }
}
#endif

#if 0 // ###FIXME: No support for canEvaluate
void tst_QJSEngine::canEvaluate_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<bool>("expectSuccess");

    QTest::newRow("") << QString("") << true;
    QTest::newRow("0") << QString("0") << true;
    QTest::newRow("!") << QString("!\n") << false;
    QTest::newRow("if (") << QString("if (\n") << false;
    QTest::newRow("if (10) //") << QString("if (10) //\n") << false;
    QTest::newRow("a = 1; if (") << QString("a = 1;\nif (\n") << false;
    QTest::newRow("./test.js") << QString("./test.js\n") << true;
    QTest::newRow("if (0) print(1)") << QString("if (0)\nprint(1)\n") << true;
    QTest::newRow("0 = ") << QString("0 = \n") << false;
    QTest::newRow("0 = 0") << QString("0 = 0\n") << true;
    QTest::newRow("foo[") << QString("foo[") << false;
    QTest::newRow("foo[") << QString("foo[\n") << false;
    QTest::newRow("foo['bar']") << QString("foo['bar']") << true;

    //v8 does thinks unterminated comments are error rather than unfinished
//    QTest::newRow("/*") << QString("/*") << false;
//    QTest::newRow("/*\nMy comment") << QString("/*\nMy comment") << false;
    QTest::newRow("/*\nMy comment */\nfoo = 10") << QString("/*\nMy comment */\nfoo = 10") << true;
//    QTest::newRow("foo = 10 /*") << QString("foo = 10 /*") << false;
//    QTest::newRow("foo = 10; /*") << QString("foo = 10; /*") << false;
    QTest::newRow("foo = 10 /* My comment */") << QString("foo = 10 /* My comment */") << true;

    QTest::newRow("/=/") << QString("/=/") << true;
    QTest::newRow("/=/g") << QString("/=/g") << true;
    QTest::newRow("/a/") << QString("/a/") << true;
    QTest::newRow("/a/g") << QString("/a/g") << true;
}

void tst_QJSEngine::canEvaluate()
{
    QFETCH(QString, code);
    QFETCH(bool, expectSuccess);

    QScriptEngine eng;
    QCOMPARE(eng.canEvaluate(code), expectSuccess);
}
#endif

void tst_QJSEngine::evaluate_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<int>("lineNumber");
    QTest::addColumn<bool>("expectHadError");
    QTest::addColumn<int>("expectErrorLineNumber");

    QTest::newRow("(newline)") << QString("\n") << -1 << false << -1;
    QTest::newRow("0 //")   << QString("0 //") << -1 << false << -1;
    QTest::newRow("/* */")   << QString("/* */") << -1 << false << -1;
    QTest::newRow("//") << QString("//") << -1 << false << -1;
    QTest::newRow("(spaces)")  << QString("  ") << -1 << false << -1;
    QTest::newRow("(empty)")   << QString("") << -1 << false << -1;
    QTest::newRow("0")     << QString("0")       << -1 << false << -1;
    QTest::newRow("0=1")   << QString("\n0=1;\n") << -1 << true  << 2;
    QTest::newRow("a=1")   << QString("a=1\n")   << -1 << false << -1;
    QTest::newRow("a=1;K") << QString("a=1;\nK") << -1 << true  << 2;

    QTest::newRow("f()") << QString("function f()\n"
                                    "{\n"
                                    "  var a;\n"
                                    "  var b=\";\n" // here's the error
                                    "}\n"
                                    "f();\n")
                         << -1 << true << 4;

    QTest::newRow("0")     << QString("0")       << 10 << false << -1;
    QTest::newRow("0=1")   << QString("\n\n0=1\n") << 10 << true  << 12;
    QTest::newRow("a=1")   << QString("a=1\n")   << 10 << false << -1;
    QTest::newRow("a=1;K") << QString("a=1;\n\nK") << 10 << true  << 12;

    QTest::newRow("f()") << QString("function f()\n"
                                    "{\n"
                                    "  var a;\n"
                                    "\n\n"
                                    "  var b=\";\n" // here's the error
                                    "}\n"
                                    "f();\n")
                         << 10 << true << 15;
    QTest::newRow("functionThatDoesntExist()")
        << QString(";\n;\n;\nfunctionThatDoesntExist()")
        << -1 << true << 4;
    QTest::newRow("for (var p in this) { continue labelThatDoesntExist; }")
        << QString("for (var p in this) {\ncontinue labelThatDoesntExist; }")
        << 4 << true << 5;
    QTest::newRow("duplicateLabel: { duplicateLabel: ; }")
        << QString("duplicateLabel: { duplicateLabel: ; }")
        << 12 << true << 12;

    QTest::newRow("/=/") << QString("/=/") << -1 << false << -1;
    QTest::newRow("/=/g") << QString("/=/g") << -1 << false << -1;
    QTest::newRow("/a/") << QString("/a/") << -1 << false << -1;
    QTest::newRow("/a/g") << QString("/a/g") << -1 << false << -1;
    QTest::newRow("/a/gim") << QString("/a/gim") << -1 << false << -1;
    QTest::newRow("/a/gimp") << QString("/a/gimp") << 1 << true << 1;
}

void tst_QJSEngine::evaluate()
{
    QFETCH(QString, code);
    QFETCH(int, lineNumber);
    QFETCH(bool, expectHadError);
    QFETCH(int, expectErrorLineNumber);

    QJSEngine eng;
    QJSValue ret;
    if (lineNumber != -1)
        ret = eng.evaluate(code, /*fileName =*/QString(), lineNumber);
    else
        ret = eng.evaluate(code);
    QCOMPARE(eng.hasUncaughtException(), expectHadError);
#if 0 // ###FIXME: No support for the line number of an uncaught exception
    QEXPECT_FAIL("f()", "SyntaxError do not report line number", Continue);
    QEXPECT_FAIL("duplicateLabel: { duplicateLabel: ; }", "SyntaxError do not report line number", Continue);
    QCOMPARE(eng.uncaughtExceptionLineNumber(), expectErrorLineNumber);
#endif
    if (eng.hasUncaughtException() && ret.isError()) {
        QEXPECT_FAIL("", "we have no more lineNumber property ", Continue);
        QVERIFY(ret.property("lineNumber").strictlyEquals(QJSValue(&eng, expectErrorLineNumber)));
    } else {
#if 0 // ###FIXME: No support for the backtrace of an uncaught exception
        QVERIFY(eng.uncaughtExceptionBacktrace().isEmpty());
#endif
    }
}

#if 0 // ###FIXME: no support for c-style callbacks
static QScriptValue eval_nested(QScriptContext *ctx, QScriptEngine *eng)
{
    QScriptValue result = eng->newObject();
    eng->evaluate("var bar = 'local';");
    result.setProperty("thisObjectIdBefore", ctx->thisObject().property("id"));
    QScriptValue evaluatedThisObject = eng->evaluate("this");
    result.setProperty("thisObjectIdAfter", ctx->thisObject().property("id"));
    result.setProperty("evaluatedThisObjectId", evaluatedThisObject.property("id"));
    result.setProperty("local_bar", eng->evaluate("bar"));

    return result;
}

// Tests that nested evaluate uses the "this" that was passed.
void tst_QJSEngine::nestedEvaluate()
{
    QScriptEngine eng;
    QScriptValue fun = eng.newFunction(eval_nested);
    eng.globalObject().setProperty("fun", fun);
    // From JS function call
    {
        QScriptValue result = eng.evaluate("o = { id:'foo'}; o.fun = fun; o.fun()");
        QCOMPARE(result.property("local_bar").toString(), QString("local"));
        QCOMPARE(result.property("thisObjectIdBefore").toString(), QString("foo"));
        QCOMPARE(result.property("thisObjectIdAfter").toString(), QString("foo"));
        QCOMPARE(result.property("evaluatedThisObjectId").toString(), QString("foo"));
        QScriptValue bar = eng.evaluate("bar"); // Was introduced in local scope.
        QVERIFY(bar.isError());
        QVERIFY(bar.toString().contains(QString::fromLatin1("ReferenceError")));
    }
    // From QScriptValue::call()
    {
        QScriptValue result = fun.callWithInstance(eng.evaluate("p = { id:'foo' }") , QScriptValueList() );
        QCOMPARE(result.property("local_bar").toString(), QString("local"));
        QCOMPARE(result.property("thisObjectIdBefore").toString(), QString("foo"));
        QCOMPARE(result.property("thisObjectIdAfter").toString(), QString("foo"));
        QCOMPARE(result.property("evaluatedThisObjectId").toString(), QString("foo"));
        QScriptValue bar = eng.evaluate("bar");
        QVERIFY(bar.isError());
        QVERIFY(bar.toString().contains(QString::fromLatin1("ReferenceError")));
    }
}
#endif

#if 0 // ### FIXME: No c-style callbacks
void tst_QJSEngine::uncaughtException()
{
    QScriptEngine eng;
    QScriptValue fun = eng.newFunction(myFunction);
    QScriptValue throwFun = eng.newFunction(myThrowingFunction);
    for (int x = -1; x < 2; ++x) {
        {
            QScriptValue ret = eng.evaluate("a = 10;\nb = 20;\n0 = 0;\n", /*fileName=*/QString(), /*lineNumber=*/x);
            QVERIFY(eng.hasUncaughtException());
            QCOMPARE(eng.uncaughtExceptionLineNumber(), x+2);
            QVERIFY(eng.uncaughtException().strictlyEquals(ret));
            (void)ret.toString();
            QVERIFY(eng.hasUncaughtException());
            QVERIFY(eng.uncaughtException().strictlyEquals(ret));
            QVERIFY(fun.call().isNull());
            QVERIFY(eng.hasUncaughtException());
            QCOMPARE(eng.uncaughtExceptionLineNumber(), x+2);
            QVERIFY(eng.uncaughtException().strictlyEquals(ret));
            eng.clearExceptions();
            QVERIFY(!eng.hasUncaughtException());
            QCOMPARE(eng.uncaughtExceptionLineNumber(), -1);
            QVERIFY(!eng.uncaughtException().isValid());

            eng.evaluate("2 = 3");
            QVERIFY(eng.hasUncaughtException());
            QScriptValue ret2 = throwFun.call();
            QVERIFY(ret2.isError());
            QVERIFY(eng.hasUncaughtException());
            QVERIFY(eng.uncaughtException().strictlyEquals(ret2));
            QCOMPARE(eng.uncaughtExceptionLineNumber(), 0);
            eng.clearExceptions();
            QVERIFY(!eng.hasUncaughtException());
            eng.evaluate("1 + 2");
            QVERIFY(!eng.hasUncaughtException());
        }
        {
            QScriptValue ret = eng.evaluate("a = 10");
            QVERIFY(!eng.hasUncaughtException());
            QVERIFY(!eng.uncaughtException().isValid());
        }
        {
            QScriptValue ret = eng.evaluate("1 = 2");
            QVERIFY(eng.hasUncaughtException());
            eng.clearExceptions();
            QVERIFY(!eng.hasUncaughtException());
        }
        {
            eng.globalObject().setProperty("throwFun", throwFun);
            eng.evaluate("1;\nthrowFun();");
            QVERIFY(eng.hasUncaughtException());
            QCOMPARE(eng.uncaughtExceptionLineNumber(), 2);
            eng.clearExceptions();
            QVERIFY(!eng.hasUncaughtException());
        }
    }
}
#endif

void tst_QJSEngine::errorMessage_QT679()
{
    QJSEngine engine;
    engine.globalObject().setProperty("foo", 15);
    QJSValue error = engine.evaluate("'hello world';\nfoo.bar.blah");
    QVERIFY(error.isError());
    QVERIFY(error.toString().startsWith(QString::fromLatin1("TypeError: ")));
}

struct Foo {
public:
    int x, y;
    Foo() : x(-1), y(-1) { }
};

Q_DECLARE_METATYPE(Foo)
Q_DECLARE_METATYPE(Foo*)

#if 0 // FIXME: No prototype API in QScriptEngine
void tst_QJSEngine::getSetDefaultPrototype_int()
{
    QScriptEngine eng;

    QScriptValue object = eng.newObject();
    QCOMPARE(eng.defaultPrototype(qMetaTypeId<int>()).isValid(), false);
    eng.setDefaultPrototype(qMetaTypeId<int>(), object);
    QCOMPARE(eng.defaultPrototype(qMetaTypeId<int>()).strictlyEquals(object), true);
    QScriptValue value = eng.newVariant(int(123));
    QCOMPARE(value.prototype().isObject(), true);
    QCOMPARE(value.prototype().strictlyEquals(object), true);

    eng.setDefaultPrototype(qMetaTypeId<int>(), QScriptValue());
    QCOMPARE(eng.defaultPrototype(qMetaTypeId<int>()).isValid(), false);
    QScriptValue value2 = eng.newVariant(int(123));
    QCOMPARE(value2.prototype().strictlyEquals(object), false);
}

void tst_QJSEngine::getSetDefaultPrototype_customType()
{
    QScriptEngine eng;

    QScriptValue object = eng.newObject();
    QCOMPARE(eng.defaultPrototype(qMetaTypeId<Foo>()).isValid(), false);
    eng.setDefaultPrototype(qMetaTypeId<Foo>(), object);
    QCOMPARE(eng.defaultPrototype(qMetaTypeId<Foo>()).strictlyEquals(object), true);
    QScriptValue value = eng.newVariant(qVariantFromValue(Foo()));
    QCOMPARE(value.prototype().isObject(), true);
    QCOMPARE(value.prototype().strictlyEquals(object), true);

    eng.setDefaultPrototype(qMetaTypeId<Foo>(), QScriptValue());
    QCOMPARE(eng.defaultPrototype(qMetaTypeId<Foo>()).isValid(), false);
    QScriptValue value2 = eng.newVariant(qVariantFromValue(Foo()));
    QCOMPARE(value2.prototype().strictlyEquals(object), false);
}
#endif

static QJSValue fooToScriptValue(QJSEngine *eng, const Foo &foo)
{
    QJSValue obj = eng->newObject();
    obj.setProperty("x", QJSValue(eng, foo.x));
    obj.setProperty("y", QJSValue(eng, foo.y));
    return obj;
}

static void fooFromScriptValue(const QJSValue &value, Foo &foo)
{
    foo.x = value.property("x").toInt();
    foo.y = value.property("y").toInt();
}

static QJSValue fooToScriptValueV2(QJSEngine *eng, const Foo &foo)
{
    return QJSValue(eng, foo.x);
}

static void fooFromScriptValueV2(const QJSValue &value, Foo &foo)
{
    foo.x = value.toInt();
}

Q_DECLARE_METATYPE(QLinkedList<QString>)
Q_DECLARE_METATYPE(QList<Foo>)
Q_DECLARE_METATYPE(QVector<QChar>)
Q_DECLARE_METATYPE(QStack<int>)
Q_DECLARE_METATYPE(QQueue<char>)
Q_DECLARE_METATYPE(QLinkedList<QStack<int> >)

void tst_QJSEngine::valueConversion_basic()
{
    QJSEngine eng;
    {
        QJSValue num = eng.toScriptValue(123);
        QCOMPARE(num.isNumber(), true);
        QCOMPARE(num.strictlyEquals(QJSValue(&eng, 123)), true);

        int inum = eng.fromScriptValue<int>(num);
        QCOMPARE(inum, 123);

        QString snum = eng.fromScriptValue<QString>(num);
        QCOMPARE(snum, QLatin1String("123"));
    }
    {
        QJSValue num = eng.toScriptValue(123);
        QCOMPARE(num.isNumber(), true);
        QCOMPARE(num.strictlyEquals(QJSValue(&eng, 123)), true);

        int inum = eng.fromScriptValue<int>(num);
        QCOMPARE(inum, 123);

        QString snum = eng.fromScriptValue<QString>(num);
        QCOMPARE(snum, QLatin1String("123"));
    }
    {
        QJSValue num(&eng, 123);
        QCOMPARE(eng.fromScriptValue<char>(num), char(123));
        QCOMPARE(eng.fromScriptValue<unsigned char>(num), (unsigned char)(123));
        QCOMPARE(eng.fromScriptValue<short>(num), short(123));
        QCOMPARE(eng.fromScriptValue<unsigned short>(num), (unsigned short)(123));
        QCOMPARE(eng.fromScriptValue<float>(num), float(123));
        QCOMPARE(eng.fromScriptValue<double>(num), double(123));
        QCOMPARE(eng.fromScriptValue<qlonglong>(num), qlonglong(123));
        QCOMPARE(eng.fromScriptValue<qulonglong>(num), qulonglong(123));
    }
    {
        QJSValue num(123);
        QCOMPARE(eng.fromScriptValue<char>(num), char(123));
        QCOMPARE(eng.fromScriptValue<unsigned char>(num), (unsigned char)(123));
        QCOMPARE(eng.fromScriptValue<short>(num), short(123));
        QCOMPARE(eng.fromScriptValue<unsigned short>(num), (unsigned short)(123));
        QCOMPARE(eng.fromScriptValue<float>(num), float(123));
        QCOMPARE(eng.fromScriptValue<double>(num), double(123));
        QCOMPARE(eng.fromScriptValue<qlonglong>(num), qlonglong(123));
        QCOMPARE(eng.fromScriptValue<qulonglong>(num), qulonglong(123));
    }

    {
        QJSValue num = eng.toScriptValue(Q_INT64_C(0x100000000));
        QCOMPARE(eng.fromScriptValue<qlonglong>(num), Q_INT64_C(0x100000000));
        QCOMPARE(eng.fromScriptValue<qulonglong>(num), Q_UINT64_C(0x100000000));
    }

    {
        QChar c = QLatin1Char('c');
        QJSValue str = QJSValue(&eng, QLatin1String("ciao"));
        QCOMPARE(eng.fromScriptValue<QChar>(str), c);
        QJSValue code = QJSValue(&eng, c.unicode());
        QCOMPARE(eng.fromScriptValue<QChar>(code), c);
        QCOMPARE(eng.fromScriptValue<QChar>(eng.toScriptValue(c)), c);
    }
}

#if 0 // FIXME: No API for custom types
void tst_QJSEngine::valueConversion_customType()
{
    QScriptEngine eng;
    {
        // a type that we don't have built-in conversion of
        // (it's stored as a variant)
        QTime tm(1, 2, 3, 4);
        QScriptValue val = eng.toScriptValue(tm);
        QCOMPARE(eng.fromScriptValue<QTime>(val), tm);
    }

    {
        Foo foo;
        foo.x = 12;
        foo.y = 34;
        QScriptValue fooVal = eng.toScriptValue(foo);
        QCOMPARE(fooVal.isVariant(), true);

        Foo foo2 = eng.fromScriptValue<Foo>(fooVal);
        QCOMPARE(foo2.x, foo.x);
        QCOMPARE(foo2.y, foo.y);
    }

    qScriptRegisterMetaType<Foo>(&eng, fooToScriptValue, fooFromScriptValue);

    {
        Foo foo;
        foo.x = 12;
        foo.y = 34;
        QScriptValue fooVal = eng.toScriptValue(foo);
        QCOMPARE(fooVal.isObject(), true);
        QVERIFY(fooVal.prototype().strictlyEquals(eng.evaluate("Object.prototype")));
        QCOMPARE(fooVal.property("x").strictlyEquals(QScriptValue(&eng, 12)), true);
        QCOMPARE(fooVal.property("y").strictlyEquals(QScriptValue(&eng, 34)), true);
        fooVal.setProperty("x", QScriptValue(&eng, 56));
        fooVal.setProperty("y", QScriptValue(&eng, 78));

        Foo foo2 = eng.fromScriptValue<Foo>(fooVal);
        QCOMPARE(foo2.x, 56);
        QCOMPARE(foo2.y, 78);

        QScriptValue fooProto = eng.newObject();
        eng.setDefaultPrototype(qMetaTypeId<Foo>(), fooProto);
        QScriptValue fooVal2 = eng.toScriptValue(foo2);
        QVERIFY(fooVal2.prototype().strictlyEquals(fooProto));
        QVERIFY(fooVal2.property("x").strictlyEquals(QScriptValue(&eng, 56)));
        QVERIFY(fooVal2.property("y").strictlyEquals(QScriptValue(&eng, 78)));
    }
}

void tst_QJSEngine::valueConversion_sequence()
{
    QScriptEngine eng;
    qScriptRegisterSequenceMetaType<QLinkedList<QString> >(&eng);

    {
        QLinkedList<QString> lst;
        lst << QLatin1String("foo") << QLatin1String("bar");
        QScriptValue lstVal = eng.toScriptValue(lst);
        QCOMPARE(lstVal.isArray(), true);
        QCOMPARE(lstVal.property("length").toInt(), 2);
        QCOMPARE(lstVal.property("0").isString(), true);
        QCOMPARE(lstVal.property("0").toString(), QLatin1String("foo"));
        QCOMPARE(lstVal.property("1").isString(), true);
        QCOMPARE(lstVal.property("1").toString(), QLatin1String("bar"));
    }

    qScriptRegisterSequenceMetaType<QList<Foo> >(&eng);
    qScriptRegisterSequenceMetaType<QStack<int> >(&eng);
    qScriptRegisterSequenceMetaType<QVector<QChar> >(&eng);
    qScriptRegisterSequenceMetaType<QQueue<char> >(&eng);
    qScriptRegisterSequenceMetaType<QLinkedList<QStack<int> > >(&eng);

    {
        QLinkedList<QStack<int> > lst;
        QStack<int> first; first << 13 << 49; lst << first;
        QStack<int> second; second << 99999;lst << second;
        QScriptValue lstVal = eng.toScriptValue(lst);
        QCOMPARE(lstVal.isArray(), true);
        QCOMPARE(lstVal.property("length").toInt(), 2);
        QCOMPARE(lstVal.property("0").isArray(), true);
        QCOMPARE(lstVal.property("0").property("length").toInt(), 2);
        QCOMPARE(lstVal.property("0").property("0").toInt(), first.at(0));
        QCOMPARE(lstVal.property("0").property("1").toInt(), first.at(1));
        QCOMPARE(lstVal.property("1").isArray(), true);
        QCOMPARE(lstVal.property("1").property("length").toInt(), 1);
        QCOMPARE(lstVal.property("1").property("0").toInt(), second.at(0));
        QCOMPARE(qscriptvalue_cast<QStack<int> >(lstVal.property("0")), first);
        QCOMPARE(qscriptvalue_cast<QStack<int> >(lstVal.property("1")), second);
        QCOMPARE(qscriptvalue_cast<QLinkedList<QStack<int> > >(lstVal), lst);
    }

    // pointers
    {
        Foo foo;
        {
            QScriptValue v = eng.toScriptValue(&foo);
            Foo *pfoo = qscriptvalue_cast<Foo*>(v);
            QCOMPARE(pfoo, &foo);
        }
        {
            Foo *pfoo = 0;
            QScriptValue v = eng.toScriptValue(pfoo);
            QCOMPARE(v.isNull(), true);
            QVERIFY(qscriptvalue_cast<Foo*>(v) == 0);
        }
    }

    // QList<int> and QObjectList should be converted from/to arrays by default
    {
        QList<int> lst;
        lst << 1 << 2 << 3;
        QScriptValue val = eng.toScriptValue(lst);
        QVERIFY(val.isArray());
        QCOMPARE(val.property("length").toInt(), lst.size());
        QCOMPARE(val.property(0).toInt(), lst.at(0));
        QCOMPARE(val.property(1).toInt(), lst.at(1));
        QCOMPARE(val.property(2).toInt(), lst.at(2));

        QCOMPARE(qscriptvalue_cast<QList<int> >(val), lst);
    }
    {
        QObjectList lst;
        lst << this;
        QScriptValue val = eng.toScriptValue(lst);
        QVERIFY(val.isArray());
        QCOMPARE(val.property("length").toInt(), lst.size());
        QCOMPARE(val.property(0).toQObject(), (QObject *)this);

        QCOMPARE(qscriptvalue_cast<QObjectList>(val), lst);
    }
}
#endif

void tst_QJSEngine::valueConversion_QVariant()
{
    QJSEngine eng;
    // qScriptValueFromValue() should be "smart" when the argument is a QVariant
    {
        QJSValue val = eng.toScriptValue(QVariant());
        QVERIFY(!val.isVariant());
        QVERIFY(val.isUndefined());
    }
    // Checking nested QVariants
    {
        QVariant tmp1;
        QVariant tmp2(QMetaType::QVariant, &tmp1);
        QVERIFY(QMetaType::Type(tmp2.type()) == QMetaType::QVariant);

        QJSValue val1 = eng.toScriptValue(tmp1);
        QJSValue val2 = eng.toScriptValue(tmp2);
        QVERIFY(val1.isValid());
        QVERIFY(val2.isValid());
        QVERIFY(val1.isUndefined());
        QEXPECT_FAIL("", "Variant are unrwapped, maybe we should not...", Continue);
        QVERIFY(!val2.isUndefined());
        QVERIFY(!val1.isVariant());
        QEXPECT_FAIL("", "Variant are unrwapped, maybe we should not...", Continue);
        QVERIFY(val2.isVariant());
    }
    {
        QVariant tmp1(123);
        QVariant tmp2(QMetaType::QVariant, &tmp1);
        QVariant tmp3(QMetaType::QVariant, &tmp2);
        QVERIFY(QMetaType::Type(tmp1.type()) == QMetaType::Int);
        QVERIFY(QMetaType::Type(tmp2.type()) == QMetaType::QVariant);
        QVERIFY(QMetaType::Type(tmp3.type()) == QMetaType::QVariant);

        QJSValue val1 = eng.toScriptValue(tmp2);
        QJSValue val2 = eng.toScriptValue(tmp3);
        QVERIFY(val1.isValid());
        QVERIFY(val2.isValid());
        QEXPECT_FAIL("", "Variant are unrwapped, maybe we should not...", Continue);
        QVERIFY(val1.isVariant());
        QEXPECT_FAIL("", "Variant are unrwapped, maybe we should not...", Continue);
        QVERIFY(val2.isVariant());
        QVERIFY(val1.toVariant().toInt() == 123);
        QVERIFY(eng.toScriptValue(val2.toVariant()).toVariant().toInt() == 123);
    }
    {
        QJSValue val = eng.toScriptValue(QVariant(true));
        QVERIFY(!val.isVariant());
        QVERIFY(val.isBool());
        QCOMPARE(val.toBool(), true);
    }
    {
        QJSValue val = eng.toScriptValue(QVariant(int(123)));
        QVERIFY(!val.isVariant());
        QVERIFY(val.isNumber());
        QCOMPARE(val.toNumber(), qreal(123));
    }
    {
        QJSValue val = eng.toScriptValue(QVariant(qreal(1.25)));
        QVERIFY(!val.isVariant());
        QVERIFY(val.isNumber());
        QCOMPARE(val.toNumber(), qreal(1.25));
    }
    {
        QString str = QString::fromLatin1("ciao");
        QJSValue val = eng.toScriptValue(QVariant(str));
        QVERIFY(!val.isVariant());
        QVERIFY(val.isString());
        QCOMPARE(val.toString(), str);
    }
    {
        QJSValue val = eng.toScriptValue(qVariantFromValue((QObject*)this));
        QVERIFY(!val.isVariant());
        QVERIFY(val.isQObject());
        QCOMPARE(val.toQObject(), (QObject*)this);
    }
    {
        QVariant var = qVariantFromValue(QPoint(123, 456));
        QJSValue val = eng.toScriptValue(var);
        QVERIFY(val.isVariant());
        QCOMPARE(val.toVariant(), var);
    }

    QCOMPARE(qjsvalue_cast<QVariant>(QJSValue(123)), QVariant(123));
}

#if 0 // FIXME: No support for custom types
void tst_QJSEngine::valueConversion_hooliganTask248802()
{
    QScriptEngine eng;
    qScriptRegisterMetaType<Foo>(&eng, fooToScriptValueV2, fooFromScriptValueV2);
    {
        QScriptValue num(&eng, 123);
        Foo foo = eng.fromScriptValue<Foo>(num);
        QCOMPARE(foo.x, 123);
    }
    {
        QScriptValue num(123);
        Foo foo = eng.fromScriptValue<Foo>(num);
        QCOMPARE(foo.x, -1);
    }
    {
        QScriptValue str(&eng, QLatin1String("123"));
        Foo foo = eng.fromScriptValue<Foo>(str);
        QCOMPARE(foo.x, 123);
    }

}
#endif

void tst_QJSEngine::valueConversion_basic2()
{
    QJSEngine eng;
    // more built-in types
    {
        QJSValue val = eng.toScriptValue(uint(123));
        QVERIFY(val.isNumber());
        QCOMPARE(val.toInt(), 123);
    }
    {
        QJSValue val = eng.toScriptValue(qulonglong(123));
        QVERIFY(val.isNumber());
        QCOMPARE(val.toInt(), 123);
    }
    {
        QJSValue val = eng.toScriptValue(float(123));
        QVERIFY(val.isNumber());
        QCOMPARE(val.toInt(), 123);
    }
    {
        QJSValue val = eng.toScriptValue(short(123));
        QVERIFY(val.isNumber());
        QCOMPARE(val.toInt(), 123);
    }
    {
        QJSValue val = eng.toScriptValue(ushort(123));
        QVERIFY(val.isNumber());
        QCOMPARE(val.toInt(), 123);
    }
    {
        QJSValue val = eng.toScriptValue(char(123));
        QVERIFY(val.isNumber());
        QCOMPARE(val.toInt(), 123);
    }
    {
        QJSValue val = eng.toScriptValue(uchar(123));
        QVERIFY(val.isNumber());
        QCOMPARE(val.toInt(), 123);
    }
}

void tst_QJSEngine::valueConversion_dateTime()
{
    QJSEngine eng;
    {
        QDateTime in = QDateTime::currentDateTime();
        QJSValue val = eng.toScriptValue(in);
        QVERIFY(val.isDate());
        QCOMPARE(val.toDateTime(), in);
    }
    {
        QDate in = QDate::currentDate();
        QJSValue val = eng.toScriptValue(in);
        QVERIFY(val.isDate());
        QCOMPARE(val.toDateTime().date(), in);
    }
}

void tst_QJSEngine::valueConversion_regExp()
{
    QJSEngine eng;
    {
        QRegExp in = QRegExp("foo");
        QJSValue val = eng.toScriptValue(in);
        QVERIFY(val.isRegExp());
        QRegExp out = val.toRegExp();
        QEXPECT_FAIL("", "QTBUG-6136: JSC-based back-end doesn't preserve QRegExp::patternSyntax (always uses RegExp2)", Continue);
        QCOMPARE(out.patternSyntax(), in.patternSyntax());
        QCOMPARE(out.pattern(), in.pattern());
        QCOMPARE(out.caseSensitivity(), in.caseSensitivity());
        QCOMPARE(out.isMinimal(), in.isMinimal());
    }
    {
        QRegExp in = QRegExp("foo", Qt::CaseSensitive, QRegExp::RegExp2);
        QJSValue val = eng.toScriptValue(in);
        QVERIFY(val.isRegExp());
        QCOMPARE(val.toRegExp(), in);
    }
    {
        QRegExp in = QRegExp("foo");
        in.setMinimal(true);
        QJSValue val = eng.toScriptValue(in);
        QVERIFY(val.isRegExp());
        QEXPECT_FAIL("", "QTBUG-6136: JSC-based back-end doesn't preserve QRegExp::minimal (always false)", Continue);
        QCOMPARE(val.toRegExp().isMinimal(), in.isMinimal());
    }
}

#if 0 // FIXME: No qScriptValueFromValue
void tst_QJSEngine::qScriptValueFromValue_noEngine()
{
    QVERIFY(!qScriptValueFromValue(0, 123).isValid());
    QVERIFY(!qScriptValueFromValue(0, QVariant(123)).isValid());
}
#endif

#if 0 // ###FIXME: No QScriptContext
static QScriptValue __import__(QScriptContext *ctx, QScriptEngine *eng)
{
    return eng->importExtension(ctx->argument(0).toString());
}

void tst_QJSEngine::importExtension()
{
    QStringList libPaths = QCoreApplication::instance()->libraryPaths();
    QCoreApplication::instance()->setLibraryPaths(QStringList() << SRCDIR);

    QStringList availableExtensions;
    {
        QScriptEngine eng;
        QVERIFY(eng.importedExtensions().isEmpty());
        QStringList ret = eng.availableExtensions();
        QCOMPARE(ret.size(), 4);
        QCOMPARE(ret.at(0), QString::fromLatin1("com"));
        QCOMPARE(ret.at(1), QString::fromLatin1("com.trolltech"));
        QCOMPARE(ret.at(2), QString::fromLatin1("com.trolltech.recursive"));
        QCOMPARE(ret.at(3), QString::fromLatin1("com.trolltech.syntaxerror"));
        availableExtensions = ret;
    }

    // try to import something that doesn't exist
    {
        QScriptEngine eng;
        QScriptValue ret = eng.importExtension("this.extension.does.not.exist");
        QCOMPARE(eng.hasUncaughtException(), true);
        QCOMPARE(ret.isError(), true);
        QCOMPARE(ret.toString(), QString::fromLatin1("Error: Unable to import this.extension.does.not.exist: no such extension"));
    }

    {
        QScriptEngine eng;
        for (int x = 0; x < 2; ++x) {
            QCOMPARE(eng.globalObject().property("com").isValid(), x == 1);
            QScriptValue ret = eng.importExtension("com.trolltech");
            QCOMPARE(eng.hasUncaughtException(), false);
            QCOMPARE(ret.isUndefined(), true);

            QScriptValue com = eng.globalObject().property("com");
            QCOMPARE(com.isObject(), true);
            QCOMPARE(com.property("wasDefinedAlready")
                     .strictlyEquals(QScriptValue(&eng, false)), true);
            QCOMPARE(com.property("name")
                     .strictlyEquals(QScriptValue(&eng, "com")), true);
            QCOMPARE(com.property("level")
                     .strictlyEquals(QScriptValue(&eng, 1)), true);
            QVERIFY(com.property("originalPostInit").isUndefined());
            QVERIFY(com.property("postInitCallCount").strictlyEquals(1));

            QScriptValue trolltech = com.property("trolltech");
            QCOMPARE(trolltech.isObject(), true);
            QCOMPARE(trolltech.property("wasDefinedAlready")
                     .strictlyEquals(QScriptValue(&eng, false)), true);
            QCOMPARE(trolltech.property("name")
                     .strictlyEquals(QScriptValue(&eng, "com.trolltech")), true);
            QCOMPARE(trolltech.property("level")
                     .strictlyEquals(QScriptValue(&eng, 2)), true);
            QVERIFY(trolltech.property("originalPostInit").isUndefined());
            QVERIFY(trolltech.property("postInitCallCount").strictlyEquals(1));
        }
        QStringList imp = eng.importedExtensions();
        QCOMPARE(imp.size(), 2);
        QCOMPARE(imp.at(0), QString::fromLatin1("com"));
        QCOMPARE(imp.at(1), QString::fromLatin1("com.trolltech"));
        QCOMPARE(eng.availableExtensions(), availableExtensions);
    }

    // recursive import should throw an error
    {
        QScriptEngine eng;
        QVERIFY(eng.importedExtensions().isEmpty());
        eng.globalObject().setProperty("__import__", eng.newFunction(__import__));
        QScriptValue ret = eng.importExtension("com.trolltech.recursive");
        QCOMPARE(eng.hasUncaughtException(), true);
        QVERIFY(ret.isError());
        QCOMPARE(ret.toString(), QString::fromLatin1("Error: recursive import of com.trolltech.recursive"));
        QStringList imp = eng.importedExtensions();
        QCOMPARE(imp.size(), 2);
        QCOMPARE(imp.at(0), QString::fromLatin1("com"));
        QCOMPARE(imp.at(1), QString::fromLatin1("com.trolltech"));
        QCOMPARE(eng.availableExtensions(), availableExtensions);
    }

    {
        QScriptEngine eng;
        eng.globalObject().setProperty("__import__", eng.newFunction(__import__));
        for (int x = 0; x < 2; ++x) {
            if (x == 0)
                QVERIFY(eng.importedExtensions().isEmpty());
            QScriptValue ret = eng.importExtension("com.trolltech.syntaxerror");
            QVERIFY(eng.hasUncaughtException());
            QEXPECT_FAIL("", "JSC throws syntax error eagerly", Continue);
            QCOMPARE(eng.uncaughtExceptionLineNumber(), 4);
            QVERIFY(ret.isError());
            QVERIFY(ret.toString().contains(QLatin1String("SyntaxError")));
        }
        QStringList imp = eng.importedExtensions();
        QCOMPARE(imp.size(), 2);
        QCOMPARE(imp.at(0), QString::fromLatin1("com"));
        QCOMPARE(imp.at(1), QString::fromLatin1("com.trolltech"));
        QCOMPARE(eng.availableExtensions(), availableExtensions);
    }

    QCoreApplication::instance()->setLibraryPaths(libPaths);
}

static QScriptValue recurse(QScriptContext *ctx, QScriptEngine *eng)
{
    Q_UNUSED(eng);
    return ctx->callee().call();
}

static QScriptValue recurse2(QScriptContext *ctx, QScriptEngine *eng)
{
    Q_UNUSED(eng);
    return ctx->callee().callAsConstructor();
}

void tst_QJSEngine::infiniteRecursion()
{
    // Infinite recursion in JS should cause the VM to throw an error
    // when the JS stack is exhausted.
    // The exact error is back-end specific and subject to change.
    const QString stackOverflowError = QString::fromLatin1("RangeError: Maximum call stack size exceeded");
    QScriptEngine eng;
    {
        QScriptValue ret = eng.evaluate("function foo() { foo(); }; foo();");
        QCOMPARE(ret.isError(), true);
        QVERIFY(ret.toString().startsWith(stackOverflowError));
    }
#if 0 //The native C++ stack overflow before the JS stack
    {
        QScriptValue fun = eng.newFunction(recurse);
        QScriptValue ret = fun.call();
        QCOMPARE(ret.isError(), true);
        QCOMPARE(ret.toString(), stackOverflowError);
    }
    {
        QScriptValue fun = eng.newFunction(recurse2);
        QScriptValue ret = fun.callAsConstructor();
        QCOMPARE(ret.isError(), true);
        QCOMPARE(ret.toString(), stackOverflowError);
    }
#endif
}
#endif

struct Bar {
    int a;
};

struct Baz : public Bar {
    int b;
};

Q_DECLARE_METATYPE(Bar*)
Q_DECLARE_METATYPE(Baz*)

Q_DECLARE_METATYPE(QGradient)
Q_DECLARE_METATYPE(QGradient*)
Q_DECLARE_METATYPE(QLinearGradient)

#if 0 // FIXME: No support for default prototypes
class Zoo : public QObject
{
    Q_OBJECT
public:
    Zoo() { }
public slots:
    Baz *toBaz(Bar *b) { return reinterpret_cast<Baz*>(b); }
};

void tst_QJSEngine::castWithPrototypeChain()
{
    QScriptEngine eng;
    Bar bar;
    Baz baz;
    QScriptValue barProto = eng.toScriptValue(&bar);
    QScriptValue bazProto = eng.toScriptValue(&baz);
    eng.setDefaultPrototype(qMetaTypeId<Bar*>(), barProto);
    eng.setDefaultPrototype(qMetaTypeId<Baz*>(), bazProto);

    Baz baz2;
    baz2.a = 123;
    baz2.b = 456;
    QScriptValue baz2Value = eng.toScriptValue(&baz2);
    {
        // qscriptvalue_cast() does magic; if the QScriptValue contains
        // t of type T, and the target type is T*, &t is returned.
        Baz *pbaz = qscriptvalue_cast<Baz*>(baz2Value);
        QVERIFY(pbaz != 0);
        QCOMPARE(pbaz->b, baz2.b);

        Zoo zoo;
        QScriptValue scriptZoo = eng.newQObject(&zoo);
        QScriptValue toBaz = scriptZoo.property("toBaz");
        QVERIFY(toBaz.isCallable());

        // no relation between Bar and Baz's proto --> casting fails
        {
            Bar *pbar = qscriptvalue_cast<Bar*>(baz2Value);
            QVERIFY(pbar == 0);
        }

        {
            QScriptValue ret = toBaz.callWithInstance(scriptZoo, QScriptValueList() << baz2Value);
            QVERIFY(ret.isError());
            QCOMPARE(ret.toString(), QLatin1String("TypeError: incompatible type of argument(s) in call to toBaz(); candidates were\n    toBaz(Bar*)"));
        }

        // establish chain -- now casting should work
        // Why? because qscriptvalue_cast() does magic again.
        // It the instance itself is not of type T, qscriptvalue_cast()
        // searches the prototype chain for T, and if it finds one, it infers
        // that the instance can also be casted to that type. This cast is
        // _not_ safe and thus relies on the developer doing the right thing.
        // This is an undocumented feature to enable qscriptvalue_cast() to
        // be used by prototype functions to cast the JS this-object to C++.
        bazProto.setPrototype(barProto);

        {
            Bar *pbar = qscriptvalue_cast<Bar*>(baz2Value);
            QVERIFY(pbar != 0);
            QCOMPARE(pbar->a, baz2.a);
        }

        {
            QScriptValue ret = toBaz.callWithInstance(scriptZoo, QScriptValueList() << baz2Value);
            QEXPECT_FAIL("", "Cannot convert Baz* to Bar*", Continue);
            QVERIFY(!ret.isError());
            QEXPECT_FAIL("", "Cannot convert Baz* to Bar*", Continue);
            QCOMPARE(qscriptvalue_cast<Baz*>(ret), pbaz);
        }
    }

    bazProto.setPrototype(barProto.prototype()); // kill chain
    {
        Baz *pbaz = qscriptvalue_cast<Baz*>(baz2Value);
        QVERIFY(pbaz != 0);
        // should not work anymore
        Bar *pbar = qscriptvalue_cast<Bar*>(baz2Value);
        QVERIFY(pbar == 0);
    }

    bazProto.setPrototype(eng.newQObject(this));
    {
        Baz *pbaz = qscriptvalue_cast<Baz*>(baz2Value);
        QVERIFY(pbaz != 0);
        // should not work now either
        Bar *pbar = qscriptvalue_cast<Bar*>(baz2Value);
        QVERIFY(pbar == 0);
    }

    {
        QScriptValue b = eng.toScriptValue(QBrush());
        b.setPrototype(barProto);
        // this shows that a "wrong" cast is possible, if you
        // don't play by the rules (the pointer is actually a QBrush*)...
        Bar *pbar = qscriptvalue_cast<Bar*>(b);
        QVERIFY(pbar != 0);
    }

    {
        QScriptValue gradientProto = eng.toScriptValue(QGradient());
        QScriptValue linearGradientProto = eng.toScriptValue(QLinearGradient());
        linearGradientProto.setPrototype(gradientProto);
        QLinearGradient lg(10, 20, 30, 40);
        QScriptValue linearGradient = eng.toScriptValue(lg);
        {
            QGradient *pgrad = qscriptvalue_cast<QGradient*>(linearGradient);
            QVERIFY(pgrad == 0);
        }
        linearGradient.setPrototype(linearGradientProto);
        {
            QGradient *pgrad = qscriptvalue_cast<QGradient*>(linearGradient);
            QVERIFY(pgrad != 0);
            QCOMPARE(pgrad->type(), QGradient::LinearGradient);
            QLinearGradient *plingrad = static_cast<QLinearGradient*>(pgrad);
            QCOMPARE(plingrad->start(), lg.start());
            QCOMPARE(plingrad->finalStop(), lg.finalStop());
        }
    }
}
#endif

class Klazz : public QWidget,
              public QStandardItem,
              public QGraphicsItem
{
    Q_INTERFACES(QGraphicsItem)
    Q_OBJECT
public:
    Klazz(QWidget *parent = 0) : QWidget(parent) { }
    virtual QRectF boundingRect() const { return QRectF(); }
    virtual void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) { }
};

Q_DECLARE_METATYPE(Klazz*)
Q_DECLARE_METATYPE(QStandardItem*)

void tst_QJSEngine::castWithMultipleInheritance()
{
    QJSEngine eng;
    Klazz klz;
    QJSValue v = eng.newQObject(&klz);

    QCOMPARE(qjsvalue_cast<Klazz*>(v), &klz);
    QCOMPARE(qjsvalue_cast<QWidget*>(v), (QWidget *)&klz);
    QCOMPARE(qjsvalue_cast<QObject*>(v), (QObject *)&klz);
    QCOMPARE(qjsvalue_cast<QStandardItem*>(v), (QStandardItem *)&klz);
    QCOMPARE(qjsvalue_cast<QGraphicsItem*>(v), (QGraphicsItem *)&klz);
}

void tst_QJSEngine::collectGarbage()
{
    QJSEngine eng;
    eng.evaluate("a = new Object(); a = new Object(); a = new Object()");
    QJSValue a = eng.newObject();
    a = eng.newObject();
    a = eng.newObject();
    QPointer<QObject> ptr = new QObject();
    QVERIFY(ptr != 0);
    (void)eng.newQObject(ptr);
    collectGarbage_helper(eng);
    if (ptr)
        QGuiApplication::sendPostedEvents(ptr, QEvent::DeferredDelete);
    QVERIFY(ptr == 0);
}

#if 0 // ###FIXME: no reportAdditionalMemoryCost API
void tst_QJSEngine::reportAdditionalMemoryCost()
{
    QScriptEngine eng;
    // There isn't any reliable way to test whether calling
    // this function affects garbage collection responsiveness;
    // the best we can do is call it with a few different values.
    for (int x = 0; x < 100; ++x) {
        eng.reportAdditionalMemoryCost(0);
        eng.reportAdditionalMemoryCost(10);
        eng.reportAdditionalMemoryCost(1000);
        eng.reportAdditionalMemoryCost(10000);
        eng.reportAdditionalMemoryCost(100000);
        eng.reportAdditionalMemoryCost(1000000);
        eng.reportAdditionalMemoryCost(10000000);
        eng.reportAdditionalMemoryCost(-1);
        eng.reportAdditionalMemoryCost(-1000);
        QScriptValue obj = eng.newObject();
        eng.collectGarbage();
    }
}
#endif

void tst_QJSEngine::gcWithNestedDataStructure()
{
    // The GC must be able to traverse deeply nested objects, otherwise this
    // test would crash.
    QJSEngine eng;
    eng.evaluate(
        "function makeList(size)"
        "{"
        "  var head = { };"
        "  var l = head;"
        "  for (var i = 0; i < size; ++i) {"
        "    l.data = i + \"\";"
        "    l.next = { }; l = l.next;"
        "  }"
        "  l.next = null;"
        "  return head;"
        "}");
    QCOMPARE(eng.hasUncaughtException(), false);
    const int size = 200;
    QJSValue head = eng.evaluate(QString::fromLatin1("makeList(%0)").arg(size));
    QCOMPARE(eng.hasUncaughtException(), false);
    for (int x = 0; x < 2; ++x) {
        if (x == 1)
            eng.evaluate("gc()");
        QJSValue l = head;
        // Make sure all the nodes are still alive.
        for (int i = 0; i < 200; ++i) {
            QCOMPARE(l.property("data").toString(), QString::number(i));
            l = l.property("next");
        }
    }
}

#if 0 // ###FIXME: No processEvents handling
class EventReceiver : public QObject
{
public:
    EventReceiver() {
        received = false;
    }

    bool event(QEvent *e) {
        received |= (e->type() == QEvent::User + 1);
        return QObject::event(e);
    }

    bool received;
};

void tst_QJSEngine::processEventsWhileRunning()
{
    for (int x = 0; x < 2; ++x) {
        QScriptEngine eng;
        if (x == 0)
            eng.pushContext();

        // This is running for a silly amount of time just to make sure
        // the script doesn't finish before event processing is triggered.
        QString script = QString::fromLatin1(
            "var end = Number(new Date()) + 2000;"
            "var x = 0;"
            "while (Number(new Date()) < end) {"
            "    ++x;"
            "}");

        EventReceiver receiver;
        QCoreApplication::postEvent(&receiver, new QEvent(QEvent::Type(QEvent::User+1)));

        eng.evaluate(script);
        QVERIFY(!eng.hasUncaughtException());
        QVERIFY(!receiver.received);

        QCOMPARE(eng.processEventsInterval(), -1);
        eng.setProcessEventsInterval(100);
        eng.evaluate(script);
        QVERIFY(!eng.hasUncaughtException());
        QVERIFY(receiver.received);

        if (x == 0)
            eng.popContext();
    }
}

void tst_QJSEngine::processEventsWhileRunning_function()
{
    QScriptEngine eng;
    QScriptValue script = eng.evaluate(QString::fromLatin1(
        "(function() { var end = Number(new Date()) + 2000;"
        "var x = 0;"
        "while (Number(new Date()) < end) {"
        "    ++x;"
        "} })"));

    eng.setProcessEventsInterval(100);

    for (int x = 0; x < 2; ++x) {
        EventReceiver receiver;
        QCoreApplication::postEvent(&receiver, new QEvent(QEvent::Type(QEvent::User+1)));
        QVERIFY(!eng.hasUncaughtException());
        QVERIFY(!receiver.received);
        QCOMPARE(eng.processEventsInterval(), 100);

        if (x) script.call();
        else script.callAsConstructor();

        QVERIFY(!eng.hasUncaughtException());
        QVERIFY(receiver.received);
    }
}


class EventReceiver2 : public QObject
{
public:
    EventReceiver2(QScriptEngine *eng) {
        engine = eng;
    }

    bool event(QEvent *e) {
        if (e->type() == QEvent::User + 1) {
            engine->currentContext()->throwError("Killed");
        }
        return QObject::event(e);
    }

    QScriptEngine *engine;
};

void tst_QJSEngine::throwErrorFromProcessEvents_data()
{
    QTest::addColumn<QString>("script");
    QTest::addColumn<QString>("error");

    QTest::newRow("while (1)")
        << QString::fromLatin1("while (1) { }")
        << QString::fromLatin1("Error: Killed");
    QTest::newRow("while (1) i++")
        << QString::fromLatin1("i = 0; while (1) { i++; }")
        << QString::fromLatin1("Error: Killed");
    // Unlike abortEvaluation(), scripts should be able to catch the
    // exception.
    QTest::newRow("try catch")
        << QString::fromLatin1("try {"
                               "    while (1) { }"
                               "} catch(e) {"
                               "    throw new Error('Caught');"
                               "}")
        << QString::fromLatin1("Error: Caught");
}

void tst_QJSEngine::throwErrorFromProcessEvents()
{
    QFETCH(QString, script);
    QFETCH(QString, error);

    QScriptEngine eng;

    EventReceiver2 receiver(&eng);
    QCoreApplication::postEvent(&receiver, new QEvent(QEvent::Type(QEvent::User+1)));

    eng.setProcessEventsInterval(100);
    QScriptValue ret = eng.evaluate(script);
    QVERIFY(ret.isError());
    QCOMPARE(ret.toString(), error);
}

void tst_QJSEngine::disableProcessEventsInterval()
{
    QScriptEngine eng;
    eng.setProcessEventsInterval(100);
    QCOMPARE(eng.processEventsInterval(), 100);
    eng.setProcessEventsInterval(0);
    QCOMPARE(eng.processEventsInterval(), 0);
    eng.setProcessEventsInterval(-1);
    QCOMPARE(eng.processEventsInterval(), -1);
    eng.setProcessEventsInterval(-100);
    QCOMPARE(eng.processEventsInterval(), -100);
}
#endif


void tst_QJSEngine::stacktrace()
{
    QString script = QString::fromLatin1(
        "function foo(counter) {\n"
        "    switch (counter) {\n"
        "        case 0: foo(counter+1); break;\n"
        "        case 1: foo(counter+1); break;\n"
        "        case 2: foo(counter+1); break;\n"
        "        case 3: foo(counter+1); break;\n"
        "        case 4: foo(counter+1); break;\n"
        "        default:\n"
        "        throw new Error('blah');\n"
        "    }\n"
        "}\n"
        "foo(0);");

    const QString fileName("testfile");

    QStringList backtrace;
    backtrace << "foo(5)@testfile:9"
              << "foo(4)@testfile:7"
              << "foo(3)@testfile:6"
              << "foo(2)@testfile:5"
              << "foo(1)@testfile:4"
              << "foo(0)@testfile:3"
              << "<global>()@testfile:12";

    QJSEngine eng;
    QJSValue result = eng.evaluate(script, fileName);
    QVERIFY(eng.hasUncaughtException());
    QVERIFY(result.isError());

    // QEXPECT_FAIL("", "QTBUG-6139: uncaughtExceptionBacktrace() doesn't give the full backtrace", Abort);
    // ###FIXME: no uncahgutExceptionBacktrace: QCOMPARE(eng.uncaughtExceptionBacktrace(), backtrace);
    QVERIFY(eng.hasUncaughtException());
    QVERIFY(result.strictlyEquals(eng.uncaughtException()));

    // FIXME? it is not standard.
    //QCOMPARE(result.property("fileName").toString(), fileName);
    //QCOMPARE(result.property("lineNumber").toInt(), 9);

    QJSValue stack = result.property("stack");

    // FIXME? it is not standard.
    // QVERIFY(stack.isArray());
    //QCOMPARE(stack.property("length").toInt(), 7);

    QJSValueIterator it(stack);
    int counter = 5;
    while (it.hasNext()) {
        it.next();
        QJSValue obj = it.value();
        QJSValue frame = obj.property("frame");

        QCOMPARE(obj.property("fileName").toString(), fileName);
        if (counter >= 0) {
            QJSValue callee = frame.property("arguments").property("callee");
            QVERIFY(callee.strictlyEquals(eng.globalObject().property("foo")));
            QCOMPARE(obj.property("functionName").toString(), QString("foo"));
            int line = obj.property("lineNumber").toInt();
            if (counter == 5)
                QCOMPARE(line, 9);
            else
                QCOMPARE(line, 3 + counter);
        } else {
            QVERIFY(frame.strictlyEquals(eng.globalObject()));
            QVERIFY(obj.property("functionName").toString().isEmpty());
        }

        --counter;
    }

//    FIXME? it is not standard.
//    {
//        QJSValue bt = result.property("backtrace").call(result);
//        QCOMPARE(qjsvalue_cast<QStringList>(bt), backtrace);
//    }

    // throw something that isn't an Error object
    eng.clearExceptions();
    // ###FIXME: No uncaughtExceptionBacktrace: QVERIFY(eng.uncaughtExceptionBacktrace().isEmpty());
    QString script2 = QString::fromLatin1(
        "function foo(counter) {\n"
        "    switch (counter) {\n"
        "        case 0: foo(counter+1); break;\n"
        "        case 1: foo(counter+1); break;\n"
        "        case 2: foo(counter+1); break;\n"
        "        case 3: foo(counter+1); break;\n"
        "        case 4: foo(counter+1); break;\n"
        "        default:\n"
        "        throw 'just a string';\n"
        "    }\n"
        "}\n"
        "foo(0);");

    QJSValue result2 = eng.evaluate(script2, fileName);
    QVERIFY(eng.hasUncaughtException());
    QVERIFY(!result2.isError());
    QVERIFY(result2.isString());

    // ###FIXME: No uncaughtExceptionBacktrace:  QCOMPARE(eng.uncaughtExceptionBacktrace(), backtrace);
    QVERIFY(eng.hasUncaughtException());

    eng.clearExceptions();
    QVERIFY(!eng.hasUncaughtException());
    // ###FIXME: No uncaughtExceptionBacktrace:  QVERIFY(eng.uncaughtExceptionBacktrace().isEmpty());
}

void tst_QJSEngine::numberParsing_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<qreal>("expect");

    QTest::newRow("decimal 0") << QString("0") << qreal(0);
    QTest::newRow("octal 0") << QString("00") << qreal(00);
    QTest::newRow("hex 0") << QString("0x0") << qreal(0x0);
    QTest::newRow("decimal 100") << QString("100") << qreal(100);
    QTest::newRow("hex 100") << QString("0x100") << qreal(0x100);
    QTest::newRow("octal 100") << QString("0100") << qreal(0100);
    QTest::newRow("decimal 4G") << QString("4294967296") << qreal(Q_UINT64_C(4294967296));
    QTest::newRow("hex 4G") << QString("0x100000000") << qreal(Q_UINT64_C(0x100000000));
    QTest::newRow("octal 4G") << QString("040000000000") << qreal(Q_UINT64_C(040000000000));
    QTest::newRow("0.5") << QString("0.5") << qreal(0.5);
    QTest::newRow("1.5") << QString("1.5") << qreal(1.5);
    QTest::newRow("1e2") << QString("1e2") << qreal(100);
}

void tst_QJSEngine::numberParsing()
{
    QFETCH(QString, string);
    QFETCH(qreal, expect);

    QJSEngine eng;
    QJSValue ret = eng.evaluate(string);
    QVERIFY(ret.isNumber());
    qreal actual = ret.toNumber();
    QCOMPARE(actual, expect);
}

// see ECMA-262, section 7.9
// This is testing ECMA compliance, not our C++ API, but it's important that
// the back-end is conformant in this regard.
void tst_QJSEngine::automaticSemicolonInsertion()
{
    QJSEngine eng;
    {
        QJSValue ret = eng.evaluate("{ 1 2 } 3");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().contains("SyntaxError"));
    }
    {
        QJSValue ret = eng.evaluate("{ 1\n2 } 3");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 3);
    }
    {
        QJSValue ret = eng.evaluate("for (a; b\n)");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().contains("SyntaxError"));
    }
    {
        QJSValue ret = eng.evaluate("(function() { return\n1 + 2 })()");
        QVERIFY(ret.isUndefined());
    }
    {
        eng.evaluate("c = 2; b = 1");
        QJSValue ret = eng.evaluate("a = b\n++c");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 3);
    }
    {
        QJSValue ret = eng.evaluate("if (a > b)\nelse c = d");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().contains("SyntaxError"));
    }
    {
        eng.evaluate("function c() { return { foo: function() { return 5; } } }");
        eng.evaluate("b = 1; d = 2; e = 3");
        QJSValue ret = eng.evaluate("a = b + c\n(d + e).foo()");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 6);
    }
    {
        QJSValue ret = eng.evaluate("throw\n1");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().contains("SyntaxError"));
    }
    {
        QJSValue ret = eng.evaluate("a = Number(1)\n++a");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 2);
    }

    // "a semicolon is never inserted automatically if the semicolon
    // would then be parsed as an empty statement"
    {
        eng.evaluate("a = 123");
        QJSValue ret = eng.evaluate("if (0)\n ++a; a");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 123);
    }
    {
        eng.evaluate("a = 123");
        QJSValue ret = eng.evaluate("if (0)\n --a; a");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 123);
    }
    {
        eng.evaluate("a = 123");
        QJSValue ret = eng.evaluate("if ((0))\n ++a; a");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 123);
    }
    {
        eng.evaluate("a = 123");
        QJSValue ret = eng.evaluate("if ((0))\n --a; a");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 123);
    }
    {
        eng.evaluate("a = 123");
        QJSValue ret = eng.evaluate("if (0\n)\n ++a; a");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 123);
    }
    {
        eng.evaluate("a = 123");
        QJSValue ret = eng.evaluate("if (0\n ++a; a");
        QVERIFY(ret.isError());
    }
    {
        eng.evaluate("a = 123");
        QJSValue ret = eng.evaluate("if (0))\n ++a; a");
        QVERIFY(ret.isError());
    }
    {
        QJSValue ret = eng.evaluate("n = 0; for (i = 0; i < 10; ++i)\n ++n; n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 10);
    }
    {
        QJSValue ret = eng.evaluate("n = 30; for (i = 0; i < 10; ++i)\n --n; n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 20);
    }
    {
        QJSValue ret = eng.evaluate("n = 0; for (var i = 0; i < 10; ++i)\n ++n; n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 10);
    }
    {
        QJSValue ret = eng.evaluate("n = 30; for (var i = 0; i < 10; ++i)\n --n; n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 20);
    }
    {
        QJSValue ret = eng.evaluate("n = 0; i = 0; while (i++ < 10)\n ++n; n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 10);
    }
    {
        QJSValue ret = eng.evaluate("n = 30; i = 0; while (i++ < 10)\n --n; n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 20);
    }
    {
        QJSValue ret = eng.evaluate("o = { a: 0, b: 1, c: 2 }; n = 0; for (i in o)\n ++n; n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 3);
    }
    {
        QJSValue ret = eng.evaluate("o = { a: 0, b: 1, c: 2 }; n = 9; for (i in o)\n --n; n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 6);
    }
    {
        QJSValue ret = eng.evaluate("o = { a: 0, b: 1, c: 2 }; n = 0; for (var i in o)\n ++n; n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 3);
    }
    {
        QJSValue ret = eng.evaluate("o = { a: 0, b: 1, c: 2 }; n = 9; for (var i in o)\n --n; n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 6);
    }
    {
        QJSValue ret = eng.evaluate("o = { n: 3 }; n = 5; with (o)\n ++n; n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 5);
    }
    {
        QJSValue ret = eng.evaluate("o = { n: 3 }; n = 10; with (o)\n --n; n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 10);
    }
    {
        QJSValue ret = eng.evaluate("n = 5; i = 0; do\n ++n; while (++i < 10); n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 15);
    }
    {
        QJSValue ret = eng.evaluate("n = 20; i = 0; do\n --n; while (++i < 10); n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 10);
    }

    {
        QJSValue ret = eng.evaluate("n = 1; i = 0; if (n) i\n++n; n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 2);
    }
    {
        QJSValue ret = eng.evaluate("n = 1; i = 0; if (n) i\n--n; n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 0);
    }

    {
        QJSValue ret = eng.evaluate("if (0)");
        QVERIFY(ret.isError());
    }
    {
        QJSValue ret = eng.evaluate("while (0)");
        QVERIFY(ret.isError());
    }
    {
        QJSValue ret = eng.evaluate("for (;;)");
        QVERIFY(ret.isError());
    }
    {
        QJSValue ret = eng.evaluate("for (p in this)");
        QVERIFY(ret.isError());
    }
    {
        QJSValue ret = eng.evaluate("with (this)");
        QVERIFY(ret.isError());
    }
    {
        QJSValue ret = eng.evaluate("do");
        QVERIFY(ret.isError());
    }
}

#if 0 // ###FIXME: no abortEvaluation API
class EventReceiver3 : public QObject
{
public:
    enum AbortionResult {
        None = 0,
        String = 1,
        Error = 2,
        Number = 3
    };

    EventReceiver3(QScriptEngine *eng) {
        engine = eng;
        resultType = None;
    }

    bool event(QEvent *e) {
        if (e->type() == QEvent::User + 1) {
            switch (resultType) {
            case None:
                engine->abortEvaluation();
                break;
            case String:
                engine->abortEvaluation(QScriptValue(engine, QString::fromLatin1("Aborted")));
                break;
            case Error:
                engine->abortEvaluation(engine->currentContext()->throwError("AbortedWithError"));
                break;
            case Number:
                engine->abortEvaluation(QScriptValue(1234));
            }
        }
        return QObject::event(e);
    }

    AbortionResult resultType;
    QScriptEngine *engine;
};

static QScriptValue myFunctionAbortingEvaluation(QScriptContext *, QScriptEngine *eng)
{
    eng->abortEvaluation();
    return eng->nullValue(); // should be ignored
}

void tst_QJSEngine::abortEvaluation_notEvaluating()
{
    QScriptEngine eng;

    eng.abortEvaluation();
    QVERIFY(!eng.hasUncaughtException());

    eng.abortEvaluation(123);
    {
        QScriptValue ret = eng.evaluate("'ciao'");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("ciao"));
    }
}

void tst_QJSEngine::abortEvaluation_data()
{
    QTest::addColumn<QString>("script");

    QTest::newRow("while (1)")
        << QString::fromLatin1("while (1) { }");
    QTest::newRow("while (1) i++")
        << QString::fromLatin1("i = 0; while (1) { i++; }");
    QTest::newRow("try catch")
        << QString::fromLatin1("try {"
                               "    while (1) { }"
                               "} catch(e) {"
                               "    throw new Error('Caught');"
                               "}");
}

void tst_QJSEngine::abortEvaluation()
{
    QFETCH(QString, script);

    QScriptEngine eng;
    EventReceiver3 receiver(&eng);

    eng.setProcessEventsInterval(100);
    for (int x = 0; x < 4; ++x) {
        QCoreApplication::postEvent(&receiver, new QEvent(QEvent::Type(QEvent::User+1)));
        receiver.resultType = EventReceiver3::AbortionResult(x);
        QScriptValue ret = eng.evaluate(script);
        switch (receiver.resultType) {
        case EventReceiver3::None:
            QVERIFY(!eng.hasUncaughtException());
            QVERIFY(!ret.isValid());
            break;
        case EventReceiver3::Number:
            QVERIFY(!eng.hasUncaughtException());
            QVERIFY(ret.isNumber());
            QCOMPARE(ret.toInt(), 1234);
            break;
        case EventReceiver3::String:
            QVERIFY(!eng.hasUncaughtException());
            QVERIFY(ret.isString());
            QCOMPARE(ret.toString(), QString::fromLatin1("Aborted"));
            break;
        case EventReceiver3::Error:
            QVERIFY(eng.hasUncaughtException());
            QVERIFY(ret.isError());
            QCOMPARE(ret.toString(), QString::fromLatin1("Error: AbortedWithError"));
            break;
        }
    }

}

void tst_QJSEngine::abortEvaluation_tryCatch()
{
    QSKIP("It crashes");
    QScriptEngine eng;
    EventReceiver3 receiver(&eng);
    eng.setProcessEventsInterval(100);
    // scripts cannot intercept the abortion with try/catch
    for (int y = 0; y < 4; ++y) {
        QCoreApplication::postEvent(&receiver, new QEvent(QEvent::Type(QEvent::User+1)));
        receiver.resultType = EventReceiver3::AbortionResult(y);
        QScriptValue ret = eng.evaluate(QString::fromLatin1(
                                            "while (1) {\n"
                                            "  try {\n"
                                            "    (function() { while (1) { } })();\n"
                                            "  } catch (e) {\n"
                                            "    ;\n"
                                            "  }\n"
                                            "}"));
        switch (receiver.resultType) {
        case EventReceiver3::None:
            QVERIFY(!eng.hasUncaughtException());
            QVERIFY(!ret.isValid());
            break;
        case EventReceiver3::Number:
            QVERIFY(!eng.hasUncaughtException());
            QVERIFY(ret.isNumber());
            QCOMPARE(ret.toInt(), 1234);
            break;
        case EventReceiver3::String:
            QVERIFY(!eng.hasUncaughtException());
            QVERIFY(ret.isString());
            QCOMPARE(ret.toString(), QString::fromLatin1("Aborted"));
            break;
        case EventReceiver3::Error:
            QVERIFY(eng.hasUncaughtException());
            QVERIFY(ret.isError());
            break;
        }
    }
}

void tst_QJSEngine::abortEvaluation_fromNative()
{
    QScriptEngine eng;
    QScriptValue fun = eng.newFunction(myFunctionAbortingEvaluation);
    eng.globalObject().setProperty("myFunctionAbortingEvaluation", fun);
    QScriptValue ret = eng.evaluate("myFunctionAbortingEvaluation()");
    QVERIFY(!ret.isValid());
}

class ThreadedEngine : public QThread {
    Q_OBJECT;

private:
    QScriptEngine* m_engine;
protected:
    void run() {
        m_engine = new QScriptEngine();
        m_engine->setGlobalObject(m_engine->newQObject(this));
        m_engine->evaluate("while (1) { sleep(); }");
        delete m_engine;
    }

public slots:
    void sleep()
    {
        QTest::qSleep(25);
        m_engine->abortEvaluation();
    }
};

void tst_QJSEngine::abortEvaluation_QTBUG9433()
{
    ThreadedEngine engine;
    engine.start();
    QVERIFY(engine.isRunning());
    QTest::qSleep(50);
    for (uint i = 0; i < 50; ++i) { // up to ~2500 ms
        if (engine.isFinished())
            return;
        QTest::qSleep(50);
    }
    if (!engine.isFinished()) {
        engine.terminate();
        engine.wait(7000);
        QFAIL("abortEvaluation doesn't work");
    }

}
#endif

#if 0 // ###FIXME: no QScriptEngine::isEvaluating
static QScriptValue myFunctionReturningIsEvaluating(QScriptContext *, QScriptEngine *eng)
{
    return QScriptValue(eng, eng->isEvaluating());
}

class EventReceiver4 : public QObject
{
public:
    EventReceiver4(QScriptEngine *eng) {
        engine = eng;
        wasEvaluating = false;
    }

    bool event(QEvent *e) {
        if (e->type() == QEvent::User + 1) {
            wasEvaluating = engine->isEvaluating();
        }
        return QObject::event(e);
    }

    QScriptEngine *engine;
    bool wasEvaluating;
};

void tst_QJSEngine::isEvaluating_notEvaluating()
{
    QScriptEngine eng;

    QVERIFY(!eng.isEvaluating());

    eng.evaluate("");
    QVERIFY(!eng.isEvaluating());
    eng.evaluate("123");
    QVERIFY(!eng.isEvaluating());
    eng.evaluate("0 = 0");
    QVERIFY(!eng.isEvaluating());
}

void tst_QJSEngine::isEvaluating_fromNative()
{
    QScriptEngine eng;
    QScriptValue fun = eng.newFunction(myFunctionReturningIsEvaluating);
    eng.globalObject().setProperty("myFunctionReturningIsEvaluating", fun);
    QScriptValue ret = eng.evaluate("myFunctionReturningIsEvaluating()");
    QVERIFY(ret.isBool());
    QVERIFY(ret.toBool());
    ret = fun.call();
    QVERIFY(ret.isBool());
    QVERIFY(ret.toBool());
    ret = myFunctionReturningIsEvaluating(eng.currentContext(), &eng);
    QVERIFY(ret.isBool());
    QVERIFY(!ret.toBool());
}

void tst_QJSEngine::isEvaluating_fromEvent()
{
    QScriptEngine eng;
    EventReceiver4 receiver(&eng);
    QCoreApplication::postEvent(&receiver, new QEvent(QEvent::Type(QEvent::User+1)));

    QString script = QString::fromLatin1(
        "var end = Number(new Date()) + 1000;"
        "var x = 0;"
        "while (Number(new Date()) < end) {"
        "    ++x;"
        "}");

    eng.setProcessEventsInterval(100);
    eng.evaluate(script);
    QVERIFY(receiver.wasEvaluating);
}
#endif

static QtMsgType theMessageType;
static QString theMessage;

static void myMsgHandler(QtMsgType type, const char *msg)
{
    theMessageType = type;
    theMessage = QString::fromLatin1(msg);
}

#if 0
void tst_QJSEngine::printFunctionWithCustomHandler()
{
    // The built-in print() function passes the output to Qt's message
    // handler. By installing a custom message handler, the output can be
    // redirected without changing the print() function itself.
    // This behavior is not documented.
    QJSEngine eng;
    QtMsgHandler oldHandler = qInstallMsgHandler(myMsgHandler);
    QVERIFY(eng.globalObject().property("print").isCallable());

    theMessageType = QtSystemMsg;
    QVERIFY(theMessage.isEmpty());
    QVERIFY(eng.evaluate("print('test')").isUndefined());
    QCOMPARE(theMessageType, QtDebugMsg);
    QCOMPARE(theMessage, QString::fromLatin1("test"));

    theMessageType = QtSystemMsg;
    theMessage.clear();
    QVERIFY(eng.evaluate("print(3, true, 'little pigs')").isUndefined());
    QCOMPARE(theMessageType, QtDebugMsg);
    QCOMPARE(theMessage, QString::fromLatin1("3 true little pigs"));

    qInstallMsgHandler(oldHandler);
}

void tst_QJSEngine::printThrowsException()
{
    // If an argument to print() causes an exception to be thrown when
    // it's converted to a string, print() should propagate the exception.
    QJSEngine eng;
    QJSValue ret = eng.evaluate("print({ toString: function() { throw 'foo'; } });");
    QVERIFY(eng.hasUncaughtException());
    QVERIFY(ret.strictlyEquals(QJSValue(&eng, QLatin1String("foo"))));
}
#endif

void tst_QJSEngine::errorConstructors()
{
    QJSEngine eng;
    QStringList prefixes;
    prefixes << "" << "Eval" << "Range" << "Reference" << "Syntax" << "Type" << "URI";
    for (int x = 0; x < 3; ++x) {
        for (int i = 0; i < prefixes.size(); ++i) {
            QString name = prefixes.at(i) + QLatin1String("Error");
            QString code = QString(i+1, QLatin1Char('\n'));
            if (x == 0)
                code += QLatin1String("throw ");
            else if (x == 1)
                code += QLatin1String("new ");
            code += name + QLatin1String("()");
            QJSValue ret = eng.evaluate(code);
            QVERIFY(ret.isError());
            QCOMPARE(eng.hasUncaughtException(), x == 0);
            eng.clearExceptions();
            QVERIFY(ret.toString().startsWith(name));
            //QTBUG-6138: JSC doesn't assign lineNumber when errors are not thrown
            QEXPECT_FAIL("", "we have no more lineNumber property ", Continue);
            QCOMPARE(ret.property("lineNumber").toInt(), i+2);
        }
    }
}

void tst_QJSEngine::argumentsProperty_globalContext()
{
    QJSEngine eng;
    {
        // Unlike function calls, the global context doesn't have an
        // arguments property.
        QJSValue ret = eng.evaluate("arguments");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().contains(QString::fromLatin1("ReferenceError")));
    }
    eng.evaluate("arguments = 10");
    {
        QJSValue ret = eng.evaluate("arguments");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 10);
    }
    QVERIFY(eng.evaluate("delete arguments").toBool());
    QVERIFY(!eng.globalObject().property("arguments").isValid());
}

void tst_QJSEngine::argumentsProperty_JS()
{
    {
        QJSEngine eng;
        eng.evaluate("o = { arguments: 123 }");
        QJSValue ret = eng.evaluate("with (o) { arguments; }");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 123);
    }
    {
        QJSEngine eng;
        QVERIFY(!eng.globalObject().property("arguments").isValid());
        // This is testing ECMA-262 compliance. In function calls, "arguments"
        // appears like a local variable, and it can be replaced.
        QJSValue ret = eng.evaluate("(function() { arguments = 456; return arguments; })()");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 456);
        QVERIFY(!eng.globalObject().property("arguments").isValid());
    }
}

#if 0 // ###FIXME: no QScriptContext API
static QScriptValue argumentsProperty_fun(QScriptContext *, QScriptEngine *eng)
{
    // Since evaluate() is done in the current context, "arguments" should
    // refer to currentContext()->argumentsObject().
    // This is for consistency with the built-in JS eval() function.
    eng->evaluate("var a = arguments[0];");
    eng->evaluate("arguments[0] = 200;");
    return eng->evaluate("a + arguments[0]");
}

void tst_QJSEngine::argumentsProperty_evaluateInNativeFunction()
{
    QScriptEngine eng;
    QScriptValue fun = eng.newFunction(argumentsProperty_fun);
    eng.globalObject().setProperty("fun", eng.newFunction(argumentsProperty_fun));
    QScriptValue result = eng.evaluate("fun(18)");
    QVERIFY(result.isNumber());
    QCOMPARE(result.toInt(), 200+18);
}
#endif

void tst_QJSEngine::jsNumberClass()
{
    // See ECMA-262 Section 15.7, "Number Objects".

    QJSEngine eng;

    QJSValue ctor = eng.globalObject().property("Number");
    QVERIFY(ctor.property("length").isNumber());
    QCOMPARE(ctor.property("length").toNumber(), qreal(1));
    QJSValue proto = ctor.property("prototype");
    QVERIFY(proto.isObject());
    {
        QJSValue::PropertyFlags flags = QJSValue::SkipInEnumeration
                                            | QJSValue::Undeletable
                                            | QJSValue::ReadOnly;
        QCOMPARE(ctor.propertyFlags("prototype"), flags);
        QVERIFY(ctor.property("MAX_VALUE").isNumber());
        QCOMPARE(ctor.propertyFlags("MAX_VALUE"), flags);
        QVERIFY(ctor.property("MIN_VALUE").isNumber());
        QCOMPARE(ctor.propertyFlags("MIN_VALUE"), flags);
        QVERIFY(ctor.property("NaN").isNumber());
        QCOMPARE(ctor.propertyFlags("NaN"), flags);
        QVERIFY(ctor.property("NEGATIVE_INFINITY").isNumber());
        QCOMPARE(ctor.propertyFlags("NEGATIVE_INFINITY"), flags);
        QVERIFY(ctor.property("POSITIVE_INFINITY").isNumber());
        QCOMPARE(ctor.propertyFlags("POSITIVE_INFINITY"), flags);
    }
    QVERIFY(proto.instanceOf(eng.globalObject().property("Object")));
    QCOMPARE(proto.toNumber(), qreal(0));
    QVERIFY(proto.property("constructor").strictlyEquals(ctor));

    {
        QJSValue ret = eng.evaluate("Number()");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toNumber(), qreal(0));
    }
    {
        QJSValue ret = eng.evaluate("Number(123)");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toNumber(), qreal(123));
    }
    {
        QJSValue ret = eng.evaluate("Number('456')");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toNumber(), qreal(456));
    }
    {
        QJSValue ret = eng.evaluate("new Number()");
        QVERIFY(!ret.isNumber());
        QVERIFY(ret.isObject());
        QCOMPARE(ret.toNumber(), qreal(0));
    }
    {
        QJSValue ret = eng.evaluate("new Number(123)");
        QVERIFY(!ret.isNumber());
        QVERIFY(ret.isObject());
        QCOMPARE(ret.toNumber(), qreal(123));
    }
    {
        QJSValue ret = eng.evaluate("new Number('456')");
        QVERIFY(!ret.isNumber());
        QVERIFY(ret.isObject());
        QCOMPARE(ret.toNumber(), qreal(456));
    }

    QVERIFY(proto.property("toString").isCallable());
    {
        QJSValue ret = eng.evaluate("new Number(123).toString()");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("123"));
    }
    {
        QJSValue ret = eng.evaluate("new Number(123).toString(8)");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("173"));
    }
    {
        QJSValue ret = eng.evaluate("new Number(123).toString(16)");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("7b"));
    }
    QVERIFY(proto.property("toLocaleString").isCallable());
    {
        QJSValue ret = eng.evaluate("new Number(123).toLocaleString()");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("123"));
    }
    QVERIFY(proto.property("valueOf").isCallable());
    {
        QJSValue ret = eng.evaluate("new Number(123).valueOf()");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toNumber(), qreal(123));
    }
    QVERIFY(proto.property("toExponential").isCallable());
    {
        QJSValue ret = eng.evaluate("new Number(123).toExponential()");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("1.23e+2"));
    }
    QVERIFY(proto.property("toFixed").isCallable());
    {
        QJSValue ret = eng.evaluate("new Number(123).toFixed()");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("123"));
    }
    QVERIFY(proto.property("toPrecision").isCallable());
    {
        QJSValue ret = eng.evaluate("new Number(123).toPrecision()");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("123"));
    }
}

void tst_QJSEngine::jsForInStatement_simple()
{
    QJSEngine eng;
    {
        QJSValue ret = eng.evaluate("o = { }; r = []; for (var p in o) r[r.length] = p; r");
        QStringList lst = qjsvalue_cast<QStringList>(ret);
        QVERIFY(lst.isEmpty());
    }
    {
        QJSValue ret = eng.evaluate("o = { p: 123 }; r = [];"
                                        "for (var p in o) r[r.length] = p; r");
        QStringList lst = qjsvalue_cast<QStringList>(ret);
        QCOMPARE(lst.size(), 1);
        QCOMPARE(lst.at(0), QString::fromLatin1("p"));
    }
    {
        QJSValue ret = eng.evaluate("o = { p: 123, q: 456 }; r = [];"
                                        "for (var p in o) r[r.length] = p; r");
        QStringList lst = qjsvalue_cast<QStringList>(ret);
        QCOMPARE(lst.size(), 2);
        QCOMPARE(lst.at(0), QString::fromLatin1("p"));
        QCOMPARE(lst.at(1), QString::fromLatin1("q"));
    }
}

void tst_QJSEngine::jsForInStatement_prototypeProperties()
{
    QJSEngine eng;
    {
        QJSValue ret = eng.evaluate("o = { }; o.__proto__ = { p: 123 }; r = [];"
                                        "for (var p in o) r[r.length] = p; r");
        QStringList lst = qjsvalue_cast<QStringList>(ret);
        QCOMPARE(lst.size(), 1);
        QCOMPARE(lst.at(0), QString::fromLatin1("p"));
    }
    {
        QJSValue ret = eng.evaluate("o = { p: 123 }; o.__proto__ = { q: 456 }; r = [];"
                                        "for (var p in o) r[r.length] = p; r");
        QStringList lst = qjsvalue_cast<QStringList>(ret);
        QCOMPARE(lst.size(), 2);
        QCOMPARE(lst.at(0), QString::fromLatin1("p"));
        QCOMPARE(lst.at(1), QString::fromLatin1("q"));
    }
    {
        // shadowed property
        QJSValue ret = eng.evaluate("o = { p: 123 }; o.__proto__ = { p: 456 }; r = [];"
                                        "for (var p in o) r[r.length] = p; r");
        QStringList lst = qjsvalue_cast<QStringList>(ret);
        QCOMPARE(lst.size(), 1);
        QCOMPARE(lst.at(0), QString::fromLatin1("p"));
    }

}

void tst_QJSEngine::jsForInStatement_mutateWhileIterating()
{
    QJSEngine eng;
    // deleting property during enumeration
    {
        QJSValue ret = eng.evaluate("o = { p: 123 }; r = [];"
                                        "for (var p in o) { r[r.length] = p; delete r[p]; } r");
        QStringList lst = qjsvalue_cast<QStringList>(ret);
        QCOMPARE(lst.size(), 1);
        QCOMPARE(lst.at(0), QString::fromLatin1("p"));
    }
    {
        QJSValue ret = eng.evaluate("o = { p: 123, q: 456 }; r = [];"
                                        "for (var p in o) { r[r.length] = p; delete o.q; } r");
        QStringList lst = qjsvalue_cast<QStringList>(ret);
        QCOMPARE(lst.size(), 1);
        QCOMPARE(lst.at(0), QString::fromLatin1("p"));
    }

    // adding property during enumeration
    {
        QJSValue ret = eng.evaluate("o = { p: 123 }; r = [];"
                                        "for (var p in o) { r[r.length] = p; o.q = 456; } r");
        QStringList lst = qjsvalue_cast<QStringList>(ret);
        QCOMPARE(lst.size(), 1);
        QCOMPARE(lst.at(0), QString::fromLatin1("p"));
    }

}

void tst_QJSEngine::jsForInStatement_arrays()
{
    QJSEngine eng;
    {
        QJSValue ret = eng.evaluate("a = [123, 456]; r = [];"
                                        "for (var p in a) r[r.length] = p; r");
        QStringList lst = qjsvalue_cast<QStringList>(ret);
        QCOMPARE(lst.size(), 2);
        QCOMPARE(lst.at(0), QString::fromLatin1("0"));
        QCOMPARE(lst.at(1), QString::fromLatin1("1"));
    }
    {
        QJSValue ret = eng.evaluate("a = [123, 456]; a.foo = 'bar'; r = [];"
                                        "for (var p in a) r[r.length] = p; r");
        QStringList lst = qjsvalue_cast<QStringList>(ret);
        QCOMPARE(lst.size(), 3);
        QCOMPARE(lst.at(0), QString::fromLatin1("0"));
        QCOMPARE(lst.at(1), QString::fromLatin1("1"));
        QCOMPARE(lst.at(2), QString::fromLatin1("foo"));
    }
    {
        QJSValue ret = eng.evaluate("a = [123, 456]; a.foo = 'bar';"
                                        "b = [111, 222, 333]; b.bar = 'baz';"
                                        "a.__proto__ = b; r = [];"
                                        "for (var p in a) r[r.length] = p; r");
        QStringList lst = qjsvalue_cast<QStringList>(ret);
        QCOMPARE(lst.size(), 5);
        QCOMPARE(lst.at(0), QString::fromLatin1("0"));
        QCOMPARE(lst.at(1), QString::fromLatin1("1"));
        QCOMPARE(lst.at(2), QString::fromLatin1("foo"));
        QCOMPARE(lst.at(3), QString::fromLatin1("2"));
        QCOMPARE(lst.at(4), QString::fromLatin1("bar"));
    }
}

void tst_QJSEngine::jsForInStatement_nullAndUndefined()
{
    QJSEngine eng;
    {
        QJSValue ret = eng.evaluate("r = true; for (var p in undefined) r = false; r");
        QVERIFY(ret.isBool());
        QVERIFY(ret.toBool());
    }
    {
        QJSValue ret = eng.evaluate("r = true; for (var p in null) r = false; r");
        QVERIFY(ret.isBool());
        QVERIFY(ret.toBool());
    }
}

void tst_QJSEngine::jsFunctionDeclarationAsStatement()
{
    // ECMA-262 does not allow function declarations to be used as statements,
    // but several popular implementations (including JSC) do. See the NOTE
    // at the beginning of chapter 12 in ECMA-262 5th edition, where it's
    // recommended that implementations either disallow this usage or issue
    // a warning.
    // Since we had a bug report long ago about QtScript not supporting this
    // "feature" (and thus deviating from other implementations), we still
    // check this behavior.

    QJSEngine eng;
    QVERIFY(!eng.globalObject().property("bar").isValid());
    eng.evaluate("function foo(arg) {\n"
                 "  if (arg == 'bar')\n"
                 "    function bar() { return 'bar'; }\n"
                 "  else\n"
                 "    function baz() { return 'baz'; }\n"
                 "  return (arg == 'bar') ? bar : baz;\n"
                 "}");
    QVERIFY(!eng.globalObject().property("bar").isValid());
    QVERIFY(!eng.globalObject().property("baz").isValid());
    QVERIFY(eng.evaluate("foo").isCallable());
    {
        QJSValue ret = eng.evaluate("foo('bar')");
        QVERIFY(ret.isCallable());
        QJSValue ret2 = ret.call();
        QCOMPARE(ret2.toString(), QString::fromLatin1("bar"));
        QVERIFY(!eng.globalObject().property("bar").isValid());
        QVERIFY(!eng.globalObject().property("baz").isValid());
    }
    {
        QJSValue ret = eng.evaluate("foo('baz')");
        QVERIFY(ret.isCallable());
        QJSValue ret2 = ret.call();
        QCOMPARE(ret2.toString(), QString::fromLatin1("baz"));
        QVERIFY(!eng.globalObject().property("bar").isValid());
        QVERIFY(!eng.globalObject().property("baz").isValid());
    }
}

void tst_QJSEngine::stringObjects()
{
    // See ECMA-262 Section 15.5, "String Objects".

    QJSEngine eng;
    QString str("ciao");
    // in C++
    {
        QJSValue obj = eng.evaluate(QString::fromLatin1("new String('%0')").arg(str));
        QCOMPARE(obj.property("length").toInt(), str.length());
        QCOMPARE(obj.propertyFlags("length"), QJSValue::PropertyFlags(QJSValue::Undeletable | QJSValue::SkipInEnumeration | QJSValue::ReadOnly));
        for (int i = 0; i < str.length(); ++i) {
            QString pname = QString::number(i);
            QVERIFY(obj.property(pname).isString());
            QCOMPARE(obj.property(pname).toString(), QString(str.at(i)));
            QEXPECT_FAIL("", "FIXME: This is V8 issue 862. ECMA script standard 15.5.5.2 compliance.", Continue);
            QCOMPARE(obj.propertyFlags(pname), QJSValue::PropertyFlags(QJSValue::Undeletable | QJSValue::ReadOnly));
            obj.setProperty(pname, QJSValue());
            obj.setProperty(pname, QJSValue(&eng, 123));
            QVERIFY(obj.property(pname).isString());
            QCOMPARE(obj.property(pname).toString(), QString(str.at(i)));
        }
        QVERIFY(!obj.property("-1").isValid());
        QVERIFY(!obj.property(QString::number(str.length())).isValid());

        QJSValue val(&eng, 123);
        obj.setProperty("-1", val);
        QVERIFY(obj.property("-1").strictlyEquals(val));
        obj.setProperty("100", val);
        QVERIFY(obj.property("100").strictlyEquals(val));
    }

    {
        QJSValue ret = eng.evaluate("s = new String('ciao'); r = []; for (var p in s) r.push(p); r");
        QVERIFY(ret.isArray());
        QStringList lst = qjsvalue_cast<QStringList>(ret);
        QCOMPARE(lst.size(), str.length());
        for (int i = 0; i < str.length(); ++i)
            QCOMPARE(lst.at(i), QString::number(i));

        QJSValue ret2 = eng.evaluate("s[0] = 123; s[0]");
        QVERIFY(ret2.isString());
        QCOMPARE(ret2.toString().length(), 1);
        QCOMPARE(ret2.toString().at(0), str.at(0));

        QJSValue ret3 = eng.evaluate("s[-1] = 123; s[-1]");
        QVERIFY(ret3.isNumber());
        QCOMPARE(ret3.toInt(), 123);

        QJSValue ret4 = eng.evaluate("s[s.length] = 456; s[s.length]");
        QVERIFY(ret4.isNumber());
        QCOMPARE(ret4.toInt(), 456);

        QJSValue ret5 = eng.evaluate("delete s[0]");
        QVERIFY(ret5.isBool());
        QEXPECT_FAIL("", "FIXME: This is V8 bug, please report it! ECMA script standard 15.5.5.2", Abort);
        QVERIFY(!ret5.toBool());

        QJSValue ret6 = eng.evaluate("delete s[-1]");
        QVERIFY(ret6.isBool());
        QVERIFY(ret6.toBool());

        QJSValue ret7 = eng.evaluate("delete s[s.length]");
        QVERIFY(ret7.isBool());
        QVERIFY(ret7.toBool());
    }
}

void tst_QJSEngine::jsStringPrototypeReplaceBugs()
{
    QJSEngine eng;
    // task 212440
    {
        QJSValue ret = eng.evaluate("replace_args = []; \"a a a\".replace(/(a)/g, function() { replace_args.push(arguments); }); replace_args");
        QVERIFY(ret.isArray());
        int len = ret.property("length").toInt();
        QCOMPARE(len, 3);
        for (int i = 0; i < len; ++i) {
            QJSValue args = ret.property(i);
            QCOMPARE(args.property("length").toInt(), 4);
            QCOMPARE(args.property(0).toString(), QString::fromLatin1("a")); // matched string
            QCOMPARE(args.property(1).toString(), QString::fromLatin1("a")); // capture
            QVERIFY(args.property(2).isNumber());
            QCOMPARE(args.property(2).toInt(), i*2); // index of match
            QCOMPARE(args.property(3).toString(), QString::fromLatin1("a a a"));
        }
    }
    // task 212501
    {
        QJSValue ret = eng.evaluate("\"foo\".replace(/a/g, function() {})");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("foo"));
    }
}

void tst_QJSEngine::getterSetterThisObject_global()
{
    {
        QJSEngine eng;
        // read
        eng.evaluate("__defineGetter__('x', function() { return this; });");
        {
            QJSValue ret = eng.evaluate("x");
            QVERIFY(ret.equals(eng.globalObject()));
        }
        {
            QJSValue ret = eng.evaluate("(function() { return x; })()");
            QVERIFY(ret.equals(eng.globalObject()));
        }
        {
            QJSValue ret = eng.evaluate("with (this) x");
            QVERIFY(ret.equals(eng.globalObject()));
        }
        {
            QJSValue ret = eng.evaluate("with ({}) x");
            QVERIFY(ret.equals(eng.globalObject()));
        }
        {
            QJSValue ret = eng.evaluate("(function() { with ({}) return x; })()");
            QVERIFY(ret.equals(eng.globalObject()));
        }
        // write
        eng.evaluate("__defineSetter__('x', function() { return this; });");
        {
            QJSValue ret = eng.evaluate("x = 'foo'");
            // SpiderMonkey says setter return value, JSC says RHS.
            QVERIFY(ret.isString());
            QCOMPARE(ret.toString(), QString::fromLatin1("foo"));
        }
        {
            QJSValue ret = eng.evaluate("(function() { return x = 'foo'; })()");
            // SpiderMonkey says setter return value, JSC says RHS.
            QVERIFY(ret.isString());
            QCOMPARE(ret.toString(), QString::fromLatin1("foo"));
        }
        {
            QJSValue ret = eng.evaluate("with (this) x = 'foo'");
            // SpiderMonkey says setter return value, JSC says RHS.
            QVERIFY(ret.isString());
            QCOMPARE(ret.toString(), QString::fromLatin1("foo"));
        }
        {
            QJSValue ret = eng.evaluate("with ({}) x = 'foo'");
            // SpiderMonkey says setter return value, JSC says RHS.
            QVERIFY(ret.isString());
            QCOMPARE(ret.toString(), QString::fromLatin1("foo"));
        }
        {
            QJSValue ret = eng.evaluate("(function() { with ({}) return x = 'foo'; })()");
            // SpiderMonkey says setter return value, JSC says RHS.
            QVERIFY(ret.isString());
            QCOMPARE(ret.toString(), QString::fromLatin1("foo"));
        }
    }
}

void tst_QJSEngine::getterSetterThisObject_plain()
{
    {
        QJSEngine eng;
        eng.evaluate("o = {}");
        // read
        eng.evaluate("o.__defineGetter__('x', function() { return this; })");
        QVERIFY(eng.evaluate("o.x === o").toBool());
        QVERIFY(eng.evaluate("with (o) x").equals(eng.evaluate("o")));
        QVERIFY(eng.evaluate("(function() { with (o) return x; })() === o").toBool());
        eng.evaluate("q = {}; with (o) with (q) x").equals(eng.evaluate("o"));
        // write
        eng.evaluate("o.__defineSetter__('x', function() { return this; });");
        // SpiderMonkey says setter return value, JSC says RHS.
        QVERIFY(eng.evaluate("(o.x = 'foo') === 'foo'").toBool());
        QVERIFY(eng.evaluate("with (o) x = 'foo'").equals("foo"));
        QVERIFY(eng.evaluate("with (o) with (q) x = 'foo'").equals("foo"));
    }
}

void tst_QJSEngine::getterSetterThisObject_prototypeChain()
{
    {
        QJSEngine eng;
        eng.evaluate("o = {}; p = {}; o.__proto__ = p");
        // read
        eng.evaluate("p.__defineGetter__('x', function() { return this; })");
        QVERIFY(eng.evaluate("o.x === o").toBool());
        QVERIFY(eng.evaluate("with (o) x").equals(eng.evaluate("o")));
        QVERIFY(eng.evaluate("(function() { with (o) return x; })() === o").toBool());
        eng.evaluate("q = {}; with (o) with (q) x").equals(eng.evaluate("o"));
        eng.evaluate("with (q) with (o) x").equals(eng.evaluate("o"));
        // write
        eng.evaluate("o.__defineSetter__('x', function() { return this; });");
        // SpiderMonkey says setter return value, JSC says RHS.
        QVERIFY(eng.evaluate("(o.x = 'foo') === 'foo'").toBool());
        QVERIFY(eng.evaluate("with (o) x = 'foo'").equals("foo"));
        QVERIFY(eng.evaluate("with (o) with (q) x = 'foo'").equals("foo"));
    }
}

#if 0 // ###FIXME: no QScriptContext API
void tst_QJSEngine::getterSetterThisObject_activation()
{
    {
        QScriptEngine eng;
        QScriptContext *ctx = eng.pushContext();
        QVERIFY(ctx != 0);
        QScriptValue act = ctx->activationObject();
        act.setProperty("act", act);
        // read
        eng.evaluate("act.__defineGetter__('x', function() { return this; })");
        QVERIFY(eng.evaluate("x === act").toBool());
        QEXPECT_FAIL("", "QTBUG-17605: Not possible to implement local variables as getter/setter properties", Abort);
        QVERIFY(!eng.hasUncaughtException());
        QVERIFY(eng.evaluate("with (act) x").equals("foo"));
        QVERIFY(eng.evaluate("(function() { with (act) return x; })() === act").toBool());
        eng.evaluate("q = {}; with (act) with (q) x").equals(eng.evaluate("act"));
        eng.evaluate("with (q) with (act) x").equals(eng.evaluate("act"));
        // write
        eng.evaluate("act.__defineSetter__('x', function() { return this; });");
        QVERIFY(eng.evaluate("(x = 'foo') === 'foo'").toBool());
        QVERIFY(eng.evaluate("with (act) x = 'foo'").equals("foo"));
        QVERIFY(eng.evaluate("with (act) with (q) x = 'foo'").equals("foo"));
        eng.popContext();
    }
}
#endif

void tst_QJSEngine::jsContinueInSwitch()
{
    // This is testing ECMA-262 compliance, not C++ API.

    QJSEngine eng;
    // switch - continue
    {
        QJSValue ret = eng.evaluate("switch (1) { default: continue; }");
        QVERIFY(ret.isError());
    }
    // for - switch - case - continue
    {
        QJSValue ret = eng.evaluate("j = 0; for (i = 0; i < 100000; ++i) {\n"
                                        "  switch (i) {\n"
                                        "    case 1: ++j; continue;\n"
                                        "    case 100: ++j; continue;\n"
                                        "    case 1000: ++j; continue;\n"
                                        "  }\n"
                                        "}; j");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 3);
    }
    // for - switch - case - default - continue
    {
        QJSValue ret = eng.evaluate("j = 0; for (i = 0; i < 100000; ++i) {\n"
                                        "  switch (i) {\n"
                                        "    case 1: ++j; continue;\n"
                                        "    case 100: ++j; continue;\n"
                                        "    case 1000: ++j; continue;\n"
                                        "    default: if (i < 50000) break; else continue;\n"
                                        "  }\n"
                                        "}; j");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 3);
    }
    // switch - for - continue
    {
        QJSValue ret = eng.evaluate("j = 123; switch (j) {\n"
                                        "  case 123:\n"
                                        "  for (i = 0; i < 100000; ++i) {\n"
                                        "    continue;\n"
                                        "  }\n"
                                        "}; i\n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 100000);
    }
    // switch - switch - continue
    {
        QJSValue ret = eng.evaluate("i = 1; switch (i) { default: switch (i) { case 1: continue; } }");
        QVERIFY(ret.isError());
    }
    // for - switch - switch - continue
    {
        QJSValue ret = eng.evaluate("j = 0; for (i = 0; i < 100000; ++i) {\n"
                                        "  switch (i) {\n"
                                        "    case 1:\n"
                                        "    switch (i) {\n"
                                        "      case 1: ++j; continue;\n"
                                        "    }\n"
                                        "  }\n"
                                        "}; j");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 1);
    }
    // switch - for - switch - continue
    {
        QJSValue ret = eng.evaluate("j = 123; switch (j) {\n"
                                        "  case 123:\n"
                                        "  for (i = 0; i < 100000; ++i) {\n"
                                        "    switch (i) {\n"
                                        "      case 1:\n"
                                        "      ++j; continue;\n"
                                        "    }\n"
                                        "  }\n"
                                        "}; i\n");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 100000);
    }
}

void tst_QJSEngine::jsShadowReadOnlyPrototypeProperty()
{
    // SpiderMonkey has different behavior than JSC and V8; it disallows
    // creating a property on the instance if there's a property with the
    // same name in the prototype, and that property is read-only. We
    // adopted that behavior in the old (4.5) QtScript back-end, but it
    // just seems weird -- and non-compliant. Adopt the JSC behavior instead.
    QJSEngine eng;
    QVERIFY(eng.evaluate("o = {}; o.__proto__ = parseInt; o.length").isNumber());
    QCOMPARE(eng.evaluate("o.length = 123; o.length").toInt(), 123);
    QVERIFY(eng.evaluate("o.hasOwnProperty('length')").toBool());
}

void tst_QJSEngine::jsReservedWords_data()
{
    QTest::addColumn<QString>("word");
    QTest::newRow("break") << QString("break");
    QTest::newRow("case") << QString("case");
    QTest::newRow("catch") << QString("catch");
    QTest::newRow("continue") << QString("continue");
    QTest::newRow("default") << QString("default");
    QTest::newRow("delete") << QString("delete");
    QTest::newRow("do") << QString("do");
    QTest::newRow("else") << QString("else");
    QTest::newRow("false") << QString("false");
    QTest::newRow("finally") << QString("finally");
    QTest::newRow("for") << QString("for");
    QTest::newRow("function") << QString("function");
    QTest::newRow("if") << QString("if");
    QTest::newRow("in") << QString("in");
    QTest::newRow("instanceof") << QString("instanceof");
    QTest::newRow("new") << QString("new");
    QTest::newRow("null") << QString("null");
    QTest::newRow("return") << QString("return");
    QTest::newRow("switch") << QString("switch");
    QTest::newRow("this") << QString("this");
    QTest::newRow("throw") << QString("throw");
    QTest::newRow("true") << QString("true");
    QTest::newRow("try") << QString("try");
    QTest::newRow("typeof") << QString("typeof");
    QTest::newRow("var") << QString("var");
    QTest::newRow("void") << QString("void");
    QTest::newRow("while") << QString("while");
    QTest::newRow("with") << QString("with");
}

void tst_QJSEngine::jsReservedWords()
{
    // See ECMA-262 Section 7.6.1, "Reserved Words".
    // We prefer that the implementation is less strict than the spec; e.g.
    // it's good to allow reserved words as identifiers in object literals,
    // and when accessing properties using dot notation.

    QFETCH(QString, word);
    {
        QJSEngine eng;
        QJSValue ret = eng.evaluate(word + " = 123");
        QVERIFY(ret.isError());
        QString str = ret.toString();
        QVERIFY(str.startsWith("SyntaxError") || str.startsWith("ReferenceError"));
    }
    {
        QJSEngine eng;
        QJSValue ret = eng.evaluate("var " + word + " = 123");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().startsWith("SyntaxError"));
    }
    {
        QJSEngine eng;
        QJSValue ret = eng.evaluate("o = {}; o." + word + " = 123");
        // in the old back-end, in SpiderMonkey and in v8, this is allowed, but not in JSC
        QVERIFY(!ret.isError());
        QVERIFY(ret.strictlyEquals(eng.evaluate("o." + word)));
    }
    {
        QJSEngine eng;
        QJSValue ret = eng.evaluate("o = { " + word + ": 123 }");
        // in the old back-end, in SpiderMonkey and in v8, this is allowed, but not in JSC
        QVERIFY(!ret.isError());
        QVERIFY(ret.property(word).isNumber());
    }
    {
        // SpiderMonkey allows this, but we don't
        QJSEngine eng;
        QJSValue ret = eng.evaluate("function " + word + "() {}");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().startsWith("SyntaxError"));
    }
}

void tst_QJSEngine::jsFutureReservedWords_data()
{
    QTest::addColumn<QString>("word");
    QTest::addColumn<bool>("allowed");
    QTest::newRow("abstract") << QString("abstract") << true;
    QTest::newRow("boolean") << QString("boolean") << true;
    QTest::newRow("byte") << QString("byte") << true;
    QTest::newRow("char") << QString("char") << true;
    QTest::newRow("class") << QString("class") << false;
    QTest::newRow("const") << QString("const") << false;
    QTest::newRow("debugger") << QString("debugger") << false;
    QTest::newRow("double") << QString("double") << true;
    QTest::newRow("enum") << QString("enum") << false;
    QTest::newRow("export") << QString("export") << false;
    QTest::newRow("extends") << QString("extends") << false;
    QTest::newRow("final") << QString("final") << true;
    QTest::newRow("float") << QString("float") << true;
    QTest::newRow("goto") << QString("goto") << true;
    QTest::newRow("implements") << QString("implements") << true;
    QTest::newRow("import") << QString("import") << false;
    QTest::newRow("int") << QString("int") << true;
    QTest::newRow("interface") << QString("interface") << true;
    QTest::newRow("long") << QString("long") << true;
    QTest::newRow("native") << QString("native") << true;
    QTest::newRow("package") << QString("package") << true;
    QTest::newRow("private") << QString("private") << true;
    QTest::newRow("protected") << QString("protected") << true;
    QTest::newRow("public") << QString("public") << true;
    QTest::newRow("short") << QString("short") << true;
    QTest::newRow("static") << QString("static") << true;
    QTest::newRow("super") << QString("super") << false;
    QTest::newRow("synchronized") << QString("synchronized") << true;
    QTest::newRow("throws") << QString("throws") << true;
    QTest::newRow("transient") << QString("transient") << true;
    QTest::newRow("volatile") << QString("volatile") << true;
}

void tst_QJSEngine::jsFutureReservedWords()
{
    QSKIP("Fails");
    // See ECMA-262 Section 7.6.1.2, "Future Reserved Words".
    // In real-world implementations, most of these words are
    // actually allowed as normal identifiers.

    QFETCH(QString, word);
    QFETCH(bool, allowed);
    {
        QJSEngine eng;
        QJSValue ret = eng.evaluate(word + " = 123");
        QCOMPARE(!ret.isError(), allowed);
    }
    {
        QJSEngine eng;
        QJSValue ret = eng.evaluate("var " + word + " = 123");
        QCOMPARE(!ret.isError(), allowed);
    }
    {
        // this should probably be allowed (see task 162567)
        QJSEngine eng;
        QJSValue ret = eng.evaluate("o = {}; o." + word + " = 123");
        QCOMPARE(ret.isNumber(), allowed);
        QCOMPARE(!ret.isError(), allowed);
    }
    {
        // this should probably be allowed (see task 162567)
        QJSEngine eng;
        QJSValue ret = eng.evaluate("o = { " + word + ": 123 }");
        QCOMPARE(!ret.isError(), allowed);
    }
}

void tst_QJSEngine::jsThrowInsideWithStatement()
{
    // This is testing ECMA-262 compliance, not C++ API.

    // task 209988
    QJSEngine eng;
    {
        QJSValue ret = eng.evaluate(
            "try {"
            "  o = { bad : \"bug\" };"
            "  with (o) {"
            "    throw 123;"
            "  }"
            "} catch (e) {"
            "  bad;"
            "}");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().contains(QString::fromLatin1("ReferenceError")));
    }
    {
        QJSValue ret = eng.evaluate(
            "try {"
            "  o = { bad : \"bug\" };"
            "  with (o) {"
            "    throw 123;"
            "  }"
            "} finally {"
            "  bad;"
            "}");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().contains(QString::fromLatin1("ReferenceError")));
    }
    {
        eng.clearExceptions();
        QJSValue ret = eng.evaluate(
            "o = { bug : \"no bug\" };"
            "with (o) {"
            "  try {"
            "    throw 123;"
            "  } finally {"
            "    bug;"
            "  }"
            "}");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 123);
        QVERIFY(eng.hasUncaughtException());
    }
    {
        eng.clearExceptions();
        QJSValue ret = eng.evaluate(
            "o = { bug : \"no bug\" };"
            "with (o) {"
            "    throw 123;"
            "}");
        QVERIFY(ret.isNumber());
        QJSValue ret2 = eng.evaluate("bug");
        QVERIFY(ret2.isError());
        QVERIFY(ret2.toString().contains(QString::fromLatin1("ReferenceError")));
    }
}

#if 0 // ###FIXME: No QScriptEngineAgent API
class TestAgent : public QScriptEngineAgent
{
public:
    TestAgent(QScriptEngine *engine) : QScriptEngineAgent(engine) {}
};

void tst_QJSEngine::getSetAgent_ownership()
{
    // engine deleted before agent --> agent deleted too
    QScriptEngine *eng = new QScriptEngine;
    QCOMPARE(eng->agent(), (QScriptEngineAgent*)0);
    TestAgent *agent = new TestAgent(eng);
    eng->setAgent(agent);
    QCOMPARE(eng->agent(), (QScriptEngineAgent*)agent);
    eng->setAgent(0); // the engine maintains ownership of the old agent
    QCOMPARE(eng->agent(), (QScriptEngineAgent*)0);
    delete eng;
}

void tst_QJSEngine::getSetAgent_deleteAgent()
{
    // agent deleted before engine --> engine's agent should become 0
    QScriptEngine *eng = new QScriptEngine;
    TestAgent *agent = new TestAgent(eng);
    eng->setAgent(agent);
    QCOMPARE(eng->agent(), (QScriptEngineAgent*)agent);
    delete agent;
    QCOMPARE(eng->agent(), (QScriptEngineAgent*)0);
    eng->evaluate("(function(){ return 123; })()");
    delete eng;
}

void tst_QJSEngine::getSetAgent_differentEngine()
{
    QScriptEngine eng;
    QScriptEngine eng2;
    TestAgent *agent = new TestAgent(&eng);
    QTest::ignoreMessage(QtWarningMsg, "QScriptEngine::setAgent(): cannot set agent belonging to different engine");
    eng2.setAgent(agent);
    QCOMPARE(eng2.agent(), (QScriptEngineAgent*)0);
}
#endif

#if 0 // ###FIXME: No QScriptString API
void tst_QJSEngine::reentrancy_stringHandles()
{
    QScriptEngine eng1;
    QScriptEngine eng2;
    QScriptString s1 = eng1.toStringHandle("foo");
    QScriptString s2 = eng2.toStringHandle("foo");
    QVERIFY(s1 != s2);
}
#endif

#if 0 // ###FIXME: No processEventsInterval API
void tst_QJSEngine::reentrancy_processEventsInterval()
{
    QScriptEngine eng1;
    QScriptEngine eng2;
    eng1.setProcessEventsInterval(123);
    QCOMPARE(eng2.processEventsInterval(), -1);
    eng2.setProcessEventsInterval(456);
    QCOMPARE(eng1.processEventsInterval(), 123);
}
#endif

#if 0 // FIXME: No support for custom types
void tst_QJSEngine::reentrancy_typeConversion()
{
    QScriptEngine eng1;
    QScriptEngine eng2;
    qScriptRegisterMetaType<Foo>(&eng1, fooToScriptValue, fooFromScriptValue);
    Foo foo;
    foo.x = 12;
    foo.y = 34;
    {
        QScriptValue fooVal = qScriptValueFromValue(&eng1, foo);
        QVERIFY(fooVal.isObject());
        QVERIFY(!fooVal.isVariant());
        QCOMPARE(fooVal.property("x").toInt(), 12);
        QCOMPARE(fooVal.property("y").toInt(), 34);
        fooVal.setProperty("x", 56);
        fooVal.setProperty("y", 78);

        Foo foo2 = eng.fromScriptValue<Foo>(fooVal);
        QCOMPARE(foo2.x, 56);
        QCOMPARE(foo2.y, 78);
    }
    {
        QScriptValue fooVal = qScriptValueFromValue(&eng2, foo);
        QVERIFY(fooVal.isVariant());

        Foo foo2 = eng.fromScriptValue<Foo>(fooVal);
        QCOMPARE(foo2.x, 12);
        QCOMPARE(foo2.y, 34);
    }
    QVERIFY(!eng1.defaultPrototype(qMetaTypeId<Foo>()).isValid());
    QVERIFY(!eng2.defaultPrototype(qMetaTypeId<Foo>()).isValid());
    QScriptValue proto1 = eng1.newObject();
    eng1.setDefaultPrototype(qMetaTypeId<Foo>(), proto1);
    QVERIFY(!eng2.defaultPrototype(qMetaTypeId<Foo>()).isValid());
    QScriptValue proto2 = eng2.newObject();
    eng2.setDefaultPrototype(qMetaTypeId<Foo>(), proto2);
    QVERIFY(eng2.defaultPrototype(qMetaTypeId<Foo>()).isValid());
    QVERIFY(eng1.defaultPrototype(qMetaTypeId<Foo>()).strictlyEquals(proto1));
}
#endif

void tst_QJSEngine::reentrancy_globalObjectProperties()
{
    QJSEngine eng1;
    QJSEngine eng2;
    QVERIFY(!eng2.globalObject().property("a").isValid());
    eng1.evaluate("a = 10");
    QVERIFY(eng1.globalObject().property("a").isNumber());
    QVERIFY(!eng2.globalObject().property("a").isValid());
    eng2.evaluate("a = 20");
    QVERIFY(eng2.globalObject().property("a").isNumber());
    QCOMPARE(eng1.globalObject().property("a").toInt(), 10);
}

void tst_QJSEngine::reentrancy_Array()
{
    // weird bug with JSC backend
    {
        QJSEngine eng;
        QCOMPARE(eng.evaluate("Array()").toString(), QString());
        eng.evaluate("Array.prototype.toString");
        QCOMPARE(eng.evaluate("Array()").toString(), QString());
    }
    {
        QJSEngine eng;
        QCOMPARE(eng.evaluate("Array()").toString(), QString());
    }
}

void tst_QJSEngine::reentrancy_objectCreation()
{
    QJSEngine eng1;
    QJSEngine eng2;
    {
        QJSValue d1 = eng1.newDate(0);
        QJSValue d2 = eng2.newDate(0);
        QCOMPARE(d1.toDateTime(), d2.toDateTime());
        QCOMPARE(d2.toDateTime(), d1.toDateTime());
    }
    {
        QJSValue r1 = eng1.newRegExp("foo", "gim");
        QJSValue r2 = eng2.newRegExp("foo", "gim");
        QCOMPARE(r1.toRegExp(), r2.toRegExp());
        QCOMPARE(r2.toRegExp(), r1.toRegExp());
    }
    {
        QJSValue o1 = eng1.newQObject(this);
        QJSValue o2 = eng2.newQObject(this);
        QCOMPARE(o1.toQObject(), o2.toQObject());
        QCOMPARE(o2.toQObject(), o1.toQObject());
    }
#if 0 // ###FIXME: No QScriptEngine::newQMetaObject API
    {
        QScriptValue mo1 = eng1.newQMetaObject(&staticMetaObject);
        QScriptValue mo2 = eng2.newQMetaObject(&staticMetaObject);
        QCOMPARE(mo1.toQMetaObject(), mo2.toQMetaObject());
        QCOMPARE(mo2.toQMetaObject(), mo1.toQMetaObject());
    }
#endif
}

void tst_QJSEngine::jsIncDecNonObjectProperty()
{
    // This is testing ECMA-262 compliance, not C++ API.

    QJSEngine eng;
    {
        QJSValue ret = eng.evaluate("var a; a.n++");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().contains(QString::fromLatin1("TypeError")));
    }
    {
        QJSValue ret = eng.evaluate("var a; a.n--");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().contains(QString::fromLatin1("TypeError")));
    }
    {
        QJSValue ret = eng.evaluate("var a = null; a.n++");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().contains(QString::fromLatin1("TypeError")));
    }
    {
        QJSValue ret = eng.evaluate("var a = null; a.n--");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().contains(QString::fromLatin1("TypeError")));
    }
    {
        QJSValue ret = eng.evaluate("var a; ++a.n");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().contains(QString::fromLatin1("TypeError")));
    }
    {
        QJSValue ret = eng.evaluate("var a; --a.n");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().contains(QString::fromLatin1("TypeError")));
    }
    {
        QJSValue ret = eng.evaluate("var a; a.n += 1");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().contains(QString::fromLatin1("TypeError")));
    }
    {
        QJSValue ret = eng.evaluate("var a; a.n -= 1");
        QVERIFY(ret.isError());
        QVERIFY(ret.toString().contains(QString::fromLatin1("TypeError")));
    }
    {
        QJSValue ret = eng.evaluate("var a = 'ciao'; a.length++");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 4);
    }
    {
        QJSValue ret = eng.evaluate("var a = 'ciao'; a.length--");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 4);
    }
    {
        QJSValue ret = eng.evaluate("var a = 'ciao'; ++a.length");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 5);
    }
    {
        QJSValue ret = eng.evaluate("var a = 'ciao'; --a.length");
        QVERIFY(ret.isNumber());
        QCOMPARE(ret.toInt(), 3);
    }
}

#if 0 // ###FIXME: no installTranslatorFunctions API
void tst_QJSEngine::installTranslatorFunctions()
{
    QScriptEngine eng;
    QScriptValue global = eng.globalObject();
    QVERIFY(!global.property("qsTranslate").isValid());
    QVERIFY(!global.property("QT_TRANSLATE_NOOP").isValid());
    QVERIFY(!global.property("qsTr").isValid());
    QVERIFY(!global.property("QT_TR_NOOP").isValid());
    QVERIFY(!global.property("qsTrId").isValid());
    QVERIFY(!global.property("QT_TRID_NOOP").isValid());
    QVERIFY(!global.property("String").property("prototype").property("arg").isValid());

    eng.installTranslatorFunctions();
    QVERIFY(global.property("qsTranslate").isCallable());
    QVERIFY(global.property("QT_TRANSLATE_NOOP").isCallable());
    QVERIFY(global.property("qsTr").isCallable());
    QVERIFY(global.property("QT_TR_NOOP").isCallable());
    QVERIFY(global.property("qsTrId").isCallable());
    QVERIFY(global.property("QT_TRID_NOOP").isCallable());
    QVERIFY(global.property("String").property("prototype").property("arg").isCallable());

    {
        QScriptValue ret = eng.evaluate("qsTr('foo')");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("foo"));
    }
    {
        QScriptValue ret = eng.evaluate("qsTranslate('foo', 'bar')");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("bar"));
    }
    {
        QScriptValue ret = eng.evaluate("QT_TR_NOOP('foo')");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("foo"));
    }
    {
        QScriptValue ret = eng.evaluate("QT_TRANSLATE_NOOP('foo', 'bar')");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("bar"));
    }
    {
        QScriptValue ret = eng.evaluate("'foo%0'.arg('bar')");
        QEXPECT_FAIL("Custom global object", "FIXME: why we expect that String prototype exists?", Abort);
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("foobar"));
    }
    {
        QScriptValue ret = eng.evaluate("'foo%0'.arg(123)");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("foo123"));
    }
    {
        // Maybe this should throw an error?
        QScriptValue ret = eng.evaluate("'foo%0'.arg()");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString());
    }

    {
        QScriptValue ret = eng.evaluate("qsTrId('foo')");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("foo"));
    }
    {
        QScriptValue ret = eng.evaluate("QT_TRID_NOOP('foo')");
        QVERIFY(ret.isString());
        QCOMPARE(ret.toString(), QString::fromLatin1("foo"));
    }
    QVERIFY(eng.evaluate("QT_TRID_NOOP()").isUndefined());
}

class TranslationScope
{
public:
    TranslationScope(const QString &fileName)
    {
        translator.load(fileName);
        QCoreApplication::instance()->installTranslator(&translator);
    }
    ~TranslationScope()
    {
        QCoreApplication::instance()->removeTranslator(&translator);
    }

private:
    QTranslator translator;
};

void tst_QJSEngine::translateScript_data()
{
    QTest::addColumn<QString>("expression");
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<QString>("expectedTranslation");

    QString fileName = QString::fromLatin1("translatable.js");
    // Top-level
    QTest::newRow("qsTr('One')@translatable.js")
            << QString::fromLatin1("qsTr('One')") << fileName << QString::fromLatin1("En");
    QTest::newRow("qsTr('Hello')@translatable.js")
            << QString::fromLatin1("qsTr('Hello')") << fileName << QString::fromLatin1("Hallo");
    // From function
    QTest::newRow("(function() { return qsTr('One'); })()@translatable.js")
            << QString::fromLatin1("(function() { return qsTr('One'); })()") << fileName << QString::fromLatin1("En");
    QTest::newRow("(function() { return qsTr('Hello'); })()@translatable.js")
            << QString::fromLatin1("(function() { return qsTr('Hello'); })()") << fileName << QString::fromLatin1("Hallo");
    // From eval
    QTest::newRow("eval('qsTr(\\'One\\')')@translatable.js")
            << QString::fromLatin1("eval('qsTr(\\'One\\')')") << fileName << QString::fromLatin1("En");
    QTest::newRow("eval('qsTr(\\'Hello\\')')@translatable.js")
            << QString::fromLatin1("eval('qsTr(\\'Hello\\')')") << fileName << QString::fromLatin1("Hallo");
    // Plural
    QTest::newRow("qsTr('%n message(s) saved', '', 1)@translatable.js")
            << QString::fromLatin1("qsTr('%n message(s) saved', '', 1)") << fileName << QString::fromLatin1("1 melding lagret");
    QTest::newRow("qsTr('%n message(s) saved', '', 3).arg@translatable.js")
            << QString::fromLatin1("qsTr('%n message(s) saved', '', 3)") << fileName << QString::fromLatin1("3 meldinger lagret");

    // Top-level
    QTest::newRow("qsTranslate('FooContext', 'Two')@translatable.js")
            << QString::fromLatin1("qsTranslate('FooContext', 'Two')") << fileName << QString::fromLatin1("To");
    QTest::newRow("qsTranslate('FooContext', 'Goodbye')@translatable.js")
            << QString::fromLatin1("qsTranslate('FooContext', 'Goodbye')") << fileName << QString::fromLatin1("Farvel");
    // From eval
    QTest::newRow("eval('qsTranslate(\\'FooContext\\', \\'Two\\')')@translatable.js")
            << QString::fromLatin1("eval('qsTranslate(\\'FooContext\\', \\'Two\\')')") << fileName << QString::fromLatin1("To");
    QTest::newRow("eval('qsTranslate(\\'FooContext\\', \\'Goodbye\\')')@translatable.js")
            << QString::fromLatin1("eval('qsTranslate(\\'FooContext\\', \\'Goodbye\\')')") << fileName << QString::fromLatin1("Farvel");

    QTest::newRow("qsTranslate('FooContext', 'Goodbye', '', 'UnicodeUTF8')@translatable.js")
            << QString::fromLatin1("qsTranslate('FooContext', 'Goodbye', '', 'UnicodeUTF8')") << fileName << QString::fromLatin1("Farvel");
    QTest::newRow("qsTranslate('FooContext', 'Goodbye', '', 'CodecForTr')@translatable.js")
            << QString::fromLatin1("qsTranslate('FooContext', 'Goodbye', '', 'CodecForTr')") << fileName << QString::fromLatin1("Farvel");

    QTest::newRow("qsTranslate('FooContext', 'Goodbye', '', 'UnicodeUTF8', 42)@translatable.js")
            << QString::fromLatin1("qsTranslate('FooContext', 'Goodbye', '', 'UnicodeUTF8', 42)") << fileName << QString::fromLatin1("Goodbye");

    QTest::newRow("qsTr('One', 'not the same one')@translatable.js")
            << QString::fromLatin1("qsTr('One', 'not the same one')") << fileName << QString::fromLatin1("Enda en");

    QTest::newRow("qsTr('One', 'not the same one', 42)@translatable.js")
            << QString::fromLatin1("qsTr('One', 'not the same one', 42)") << fileName << QString::fromLatin1("One");

    // Plural
    QTest::newRow("qsTranslate('FooContext', '%n fooish bar(s) found', '', 'UnicodeUTF8', 1)@translatable.js")
            << QString::fromLatin1("qsTranslate('FooContext', '%n fooish bar(s) found', '', 'UnicodeUTF8', 1)") << fileName << QString::fromLatin1("1 fooaktig bar funnet");
    QTest::newRow("qsTranslate('FooContext', '%n fooish bar(s) found', '', 'UnicodeUTF8', 2)@translatable.js")
            << QString::fromLatin1("qsTranslate('FooContext', '%n fooish bar(s) found', '', 'UnicodeUTF8', 2)") << fileName << QString::fromLatin1("2 fooaktige barer funnet");

    // Don't exist in translation
    QTest::newRow("qsTr('Three')@translatable.js")
            << QString::fromLatin1("qsTr('Three')") << fileName << QString::fromLatin1("Three");
    QTest::newRow("qsTranslate('FooContext', 'So long')@translatable.js")
            << QString::fromLatin1("qsTranslate('FooContext', 'So long')") << fileName << QString::fromLatin1("So long");
    QTest::newRow("qsTranslate('BarContext', 'Goodbye')@translatable.js")
            << QString::fromLatin1("qsTranslate('BarContext', 'Goodbye')") << fileName << QString::fromLatin1("Goodbye");

    // Translate strings from the second script (translatable2.js)

    QString fileName2 = QString::fromLatin1("translatable2.js");
    QTest::newRow("qsTr('Three')@translatable2.js")
            << QString::fromLatin1("qsTr('Three')") << fileName2 << QString::fromLatin1("Tre");
    QTest::newRow("qsTr('Happy birthday!')@translatable2.js")
            << QString::fromLatin1("qsTr('Happy birthday!')") << fileName2 << QString::fromLatin1("Gratulerer med dagen!");

    // Not translated because translation is only in translatable.js
    QTest::newRow("qsTr('One')@translatable2.js")
            << QString::fromLatin1("qsTr('One')") << fileName2 << QString::fromLatin1("One");
    QTest::newRow("(function() { return qsTr('One'); })()@translatable2.js")
            << QString::fromLatin1("(function() { return qsTr('One'); })()") << fileName2 << QString::fromLatin1("One");

    // For qsTranslate() the filename shouldn't matter
    QTest::newRow("qsTranslate('FooContext', 'Two')@translatable2.js")
            << QString::fromLatin1("qsTranslate('FooContext', 'Two')") << fileName2 << QString::fromLatin1("To");
    QTest::newRow("qsTranslate('BarContext', 'Congratulations!')@translatable.js")
            << QString::fromLatin1("qsTranslate('BarContext', 'Congratulations!')") << fileName << QString::fromLatin1("Gratulerer!");
}

void tst_QJSEngine::translateScript()
{
    QFETCH(QString, expression);
    QFETCH(QString, fileName);
    QFETCH(QString, expectedTranslation);

    QScriptEngine engine;

    TranslationScope tranScope(":/translations/translatable_la");
    engine.installTranslatorFunctions();

    QCOMPARE(engine.evaluate(expression, fileName).toString(), expectedTranslation);
    QVERIFY(!engine.hasUncaughtException());
}

void tst_QJSEngine::translateScript_crossScript()
{
    QScriptEngine engine;
    TranslationScope tranScope(":/translations/translatable_la");
    engine.installTranslatorFunctions();

    QString fileName = QString::fromLatin1("translatable.js");
    QString fileName2 = QString::fromLatin1("translatable2.js");
    // qsTr() should use the innermost filename as context
    engine.evaluate("function foo(s) { return bar(s); }", fileName);
    engine.evaluate("function bar(s) { return qsTr(s); }", fileName2);
    QCOMPARE(engine.evaluate("bar('Three')", fileName2).toString(), QString::fromLatin1("Tre"));
    QCOMPARE(engine.evaluate("bar('Three')", fileName).toString(), QString::fromLatin1("Tre"));
    QCOMPARE(engine.evaluate("bar('One')", fileName2).toString(), QString::fromLatin1("One"));

    engine.evaluate("function foo(s) { return bar(s); }", fileName2);
    engine.evaluate("function bar(s) { return qsTr(s); }", fileName);
    QCOMPARE(engine.evaluate("bar('Three')", fileName2).toString(), QString::fromLatin1("Three"));
    QCOMPARE(engine.evaluate("bar('One')", fileName).toString(), QString::fromLatin1("En"));
    QCOMPARE(engine.evaluate("bar('One')", fileName2).toString(), QString::fromLatin1("En"));
}

static QScriptValue callQsTr(QScriptContext *ctx, QScriptEngine *eng)
{
    return eng->globalObject().property("qsTr").callWithInstance(ctx->thisObject(), ctx->argumentsObject());
}

void tst_QJSEngine::translateScript_callQsTrFromNative()
{
    QScriptEngine engine;
    TranslationScope tranScope(":/translations/translatable_la");
    engine.installTranslatorFunctions();

    QString fileName = QString::fromLatin1("translatable.js");
    QString fileName2 = QString::fromLatin1("translatable2.js");
    // Calling qsTr() from a native function
    engine.globalObject().setProperty("qsTrProxy", engine.newFunction(callQsTr));
    QCOMPARE(engine.evaluate("qsTrProxy('One')", fileName).toString(), QString::fromLatin1("En"));
    QCOMPARE(engine.evaluate("qsTrProxy('One')", fileName2).toString(), QString::fromLatin1("One"));
    QCOMPARE(engine.evaluate("qsTrProxy('Three')", fileName).toString(), QString::fromLatin1("Three"));
    QCOMPARE(engine.evaluate("qsTrProxy('Three')", fileName2).toString(), QString::fromLatin1("Tre"));
}

void tst_QJSEngine::translateScript_trNoOp()
{
    QScriptEngine engine;
    TranslationScope tranScope(":/translations/translatable_la");
    engine.installTranslatorFunctions();

    QVERIFY(engine.evaluate("QT_TR_NOOP()").isUndefined());
    QCOMPARE(engine.evaluate("QT_TR_NOOP('One')").toString(), QString::fromLatin1("One"));

    QVERIFY(engine.evaluate("QT_TRANSLATE_NOOP()").isUndefined());
    QVERIFY(engine.evaluate("QT_TRANSLATE_NOOP('FooContext')").isUndefined());
    QCOMPARE(engine.evaluate("QT_TRANSLATE_NOOP('FooContext', 'Two')").toString(), QString::fromLatin1("Two"));
}

void tst_QJSEngine::translateScript_callQsTrFromCpp()
{
    QScriptEngine engine;
    TranslationScope tranScope(":/translations/translatable_la");
    engine.installTranslatorFunctions();

    // There is no context, but it shouldn't crash
    QCOMPARE(engine.globalObject().property("qsTr").call(
             QScriptValueList() << "One").toString(), QString::fromLatin1("One"));
}

void tst_QJSEngine::translateWithInvalidArgs_data()
{
    QTest::addColumn<QString>("expression");
    QTest::addColumn<QString>("expectedError");

    QTest::newRow("qsTr()")  << "qsTr()" << "Error: qsTr() requires at least one argument";
    QTest::newRow("qsTr(123)")  << "qsTr(123)" << "Error: qsTr(): first argument (text) must be a string";
    QTest::newRow("qsTr('foo', 123)")  << "qsTr('foo', 123)" << "Error: qsTr(): second argument (comment) must be a string";
    QTest::newRow("qsTr('foo', 'bar', 'baz')")  << "qsTr('foo', 'bar', 'baz')" << "Error: qsTr(): third argument (n) must be a number";
    QTest::newRow("qsTr('foo', 'bar', true)")  << "qsTr('foo', 'bar', true)" << "Error: qsTr(): third argument (n) must be a number";

    QTest::newRow("qsTranslate()")  << "qsTranslate()" << "Error: qsTranslate() requires at least two arguments";
    QTest::newRow("qsTranslate('foo')")  << "qsTranslate('foo')" << "Error: qsTranslate() requires at least two arguments";
    QTest::newRow("qsTranslate(123, 'foo')")  << "qsTranslate(123, 'foo')" << "Error: qsTranslate(): first argument (context) must be a string";
    QTest::newRow("qsTranslate('foo', 123)")  << "qsTranslate('foo', 123)" << "Error: qsTranslate(): second argument (text) must be a string";
    QTest::newRow("qsTranslate('foo', 'bar', 123)")  << "qsTranslate('foo', 'bar', 123)" << "Error: qsTranslate(): third argument (comment) must be a string";
    QTest::newRow("qsTranslate('foo', 'bar', 'baz', 123)")  << "qsTranslate('foo', 'bar', 'baz', 123)" << "Error: qsTranslate(): fourth argument (encoding) must be a string";
    QTest::newRow("qsTranslate('foo', 'bar', 'baz', 'zab', 'rab')")  << "qsTranslate('foo', 'bar', 'baz', 'zab', 'rab')" << "Error: qsTranslate(): fifth argument (n) must be a number";
    QTest::newRow("qsTranslate('foo', 'bar', 'baz', 'zab', 123)")  << "qsTranslate('foo', 'bar', 'baz', 'zab', 123)" << "Error: qsTranslate(): invalid encoding 'zab'";

    QTest::newRow("qsTrId()")  << "qsTrId()" << "Error: qsTrId() requires at least one argument";
    QTest::newRow("qsTrId(123)")  << "qsTrId(123)" << "TypeError: qsTrId(): first argument (id) must be a string";
    QTest::newRow("qsTrId('foo', 'bar')")  << "qsTrId('foo', 'bar')" << "TypeError: qsTrId(): second argument (n) must be a number";
}

void tst_QJSEngine::translateWithInvalidArgs()
{
    QFETCH(QString, expression);
    QFETCH(QString, expectedError);
    QScriptEngine engine;
    engine.installTranslatorFunctions();
    QScriptValue result = engine.evaluate(expression);
    QVERIFY(result.isError());
    QCOMPARE(result.toString(), expectedError);
}

void tst_QJSEngine::translationContext_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("text");
    QTest::addColumn<QString>("expectedTranslation");

    QTest::newRow("translatable.js")  << "translatable.js" << "One" << "En";
    QTest::newRow("/translatable.js")  << "/translatable.js" << "One" << "En";
    QTest::newRow("/foo/translatable.js")  << "/foo/translatable.js" << "One" << "En";
    QTest::newRow("/foo/bar/translatable.js")  << "/foo/bar/translatable.js" << "One" << "En";
    QTest::newRow("./translatable.js")  << "./translatable.js" << "One" << "En";
    QTest::newRow("../translatable.js")  << "../translatable.js" << "One" << "En";
    QTest::newRow("foo/translatable.js")  << "foo/translatable.js" << "One" << "En";
    QTest::newRow("file:///home/qt/translatable.js")  << "file:///home/qt/translatable.js" << "One" << "En";
    QTest::newRow(":/resources/translatable.js")  << ":/resources/translatable.js" << "One" << "En";
    QTest::newRow("/translatable.js.foo")  << "/translatable.js.foo" << "One" << "En";
    QTest::newRow("/translatable.txt")  << "/translatable.txt" << "One" << "En";
    QTest::newRow("translatable")  << "translatable" << "One" << "En";
    QTest::newRow("foo/translatable")  << "foo/translatable" << "One" << "En";

    QTest::newRow("native separators")
        << (QDir::toNativeSeparators(QDir::currentPath()) + QDir::separator() + "translatable.js")
        << "One" << "En";

    QTest::newRow("translatable.js/")  << "translatable.js/" << "One" << "One";
    QTest::newRow("nosuchscript.js")  << "" << "One" << "One";
    QTest::newRow("(empty)")  << "" << "One" << "One";
}

void tst_QJSEngine::translationContext()
{
    TranslationScope tranScope(":/translations/translatable_la");

    QScriptEngine engine;
    engine.installTranslatorFunctions();

    QFETCH(QString, path);
    QFETCH(QString, text);
    QFETCH(QString, expectedTranslation);
    QScriptValue ret = engine.evaluate(QString::fromLatin1("qsTr('%0')").arg(text), path);
    QVERIFY(ret.isString());
    QCOMPARE(ret.toString(), expectedTranslation);
}

void tst_QJSEngine::translateScriptIdBased()
{
    QScriptEngine engine;

    TranslationScope tranScope(":/translations/idtranslatable_la");
    engine.installTranslatorFunctions();

    QString fileName = QString::fromLatin1("idtranslatable.js");

    QHash<QString, QString> expectedTranslations;
    expectedTranslations["qtn_foo_bar"] = "First string";
    expectedTranslations["qtn_needle"] = "Second string";
    expectedTranslations["qtn_haystack"] = "Third string";
    expectedTranslations["qtn_bar_baz"] = "Fourth string";

    QHash<QString, QString>::const_iterator it;
    for (it = expectedTranslations.constBegin(); it != expectedTranslations.constEnd(); ++it) {
        for (int x = 0; x < 2; ++x) {
            QString fn;
            if (x)
                fn = fileName;
            // Top-level
            QCOMPARE(engine.evaluate(QString::fromLatin1("qsTrId('%0')")
                                     .arg(it.key()), fn).toString(),
                     it.value());
            QCOMPARE(engine.evaluate(QString::fromLatin1("QT_TRID_NOOP('%0')")
                                     .arg(it.key()), fn).toString(),
                     it.key());
            // From function
            QCOMPARE(engine.evaluate(QString::fromLatin1("(function() { return qsTrId('%0'); })()")
                                     .arg(it.key()), fn).toString(),
                     it.value());
            QCOMPARE(engine.evaluate(QString::fromLatin1("(function() { return QT_TRID_NOOP('%0'); })()")
                                     .arg(it.key()), fn).toString(),
                     it.key());
        }
    }

    // Plural form
    QCOMPARE(engine.evaluate("qsTrId('qtn_bar_baz', 10)").toString(),
             QString::fromLatin1("10 fooish bar(s) found"));
    QCOMPARE(engine.evaluate("qsTrId('qtn_foo_bar', 10)").toString(),
             QString::fromLatin1("qtn_foo_bar")); // Doesn't have plural
}

// How to add a new test row:
// - Find a nice list of Unicode characters to choose from
// - Write source string/context/comment in .js using Unicode escape sequences (\uABCD)
// - Update corresponding .ts file (e.g. lupdate foo.js -ts foo.ts -codecfortr UTF-8)
// - Enter translation in Linguist
// - Update corresponding .qm file (e.g. lrelease foo.ts)
// - Evaluate script that performs translation; make sure the correct result is returned
//   (e.g. by setting the resulting string as the text of a QLabel and visually verifying
//   that it looks the same as what you entered in Linguist :-) )
// - Generate the expectedTranslation column data using toUtf8().toHex()
void tst_QJSEngine::translateScriptUnicode_data()
{
    QTest::addColumn<QString>("expression");
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<QString>("expectedTranslation");

    QString fileName = QString::fromLatin1("translatable-unicode.js");
    QTest::newRow("qsTr('H\\u2082O')@translatable-unicode.js")
            << QString::fromLatin1("qsTr('H\\u2082O')") << fileName << QString::fromUtf8("\xcd\xbb\xcd\xbc\xcd\xbd");
    QTest::newRow("qsTranslate('\\u010C\\u0101\\u011F\\u0115', 'CO\\u2082')@translatable-unicode.js")
            << QString::fromLatin1("qsTranslate('\\u010C\\u0101\\u011F\\u0115', 'CO\\u2082')") << fileName << QString::fromUtf8("\xd7\x91\xd7\x9a\xd7\xa2");
    QTest::newRow("qsTr('\\u0391\\u0392\\u0393')@translatable-unicode.js")
            << QString::fromLatin1("qsTr('\\u0391\\u0392\\u0393')") << fileName << QString::fromUtf8("\xd3\x9c\xd2\xb4\xd1\xbc");
    QTest::newRow("qsTranslate('\\u010C\\u0101\\u011F\\u0115', '\\u0414\\u0415\\u0416')@translatable-unicode.js")
            << QString::fromLatin1("qsTranslate('\\u010C\\u0101\\u011F\\u0115', '\\u0414\\u0415\\u0416')") << fileName << QString::fromUtf8("\xd8\xae\xd8\xb3\xd8\xb3");
    QTest::newRow("qsTr('H\\u2082O', 'not the same H\\u2082O')@translatable-unicode.js")
            << QString::fromLatin1("qsTr('H\\u2082O', 'not the same H\\u2082O')") << fileName << QString::fromUtf8("\xd4\xb6\xd5\x8a\xd5\x92");
    QTest::newRow("qsTr('H\\u2082O')")
            << QString::fromLatin1("qsTr('H\\u2082O')") << QString() << QString::fromUtf8("\x48\xe2\x82\x82\x4f");
    QTest::newRow("qsTranslate('\\u010C\\u0101\\u011F\\u0115', 'CO\\u2082')")
            << QString::fromLatin1("qsTranslate('\\u010C\\u0101\\u011F\\u0115', 'CO\\u2082')") << QString() << QString::fromUtf8("\xd7\x91\xd7\x9a\xd7\xa2");
}

void tst_QJSEngine::translateScriptUnicode()
{
    QFETCH(QString, expression);
    QFETCH(QString, fileName);
    QFETCH(QString, expectedTranslation);

    QScriptEngine engine;

    TranslationScope tranScope(":/translations/translatable-unicode");
    engine.installTranslatorFunctions();

    QCOMPARE(engine.evaluate(expression, fileName).toString(), expectedTranslation);
    QVERIFY(!engine.hasUncaughtException());
}

void tst_QJSEngine::translateScriptUnicodeIdBased_data()
{
    QTest::addColumn<QString>("expression");
    QTest::addColumn<QString>("expectedTranslation");

    QTest::newRow("qsTrId('\\u01F8\\u01D2\\u0199\\u01D0\\u01E1'')")
            << QString::fromLatin1("qsTrId('\\u01F8\\u01D2\\u0199\\u01D0\\u01E1')") << QString::fromUtf8("\xc6\xa7\xc6\xb0\xc6\x88\xc8\xbc\xc8\x9d\xc8\xbf\xc8\x99");
    QTest::newRow("qsTrId('\\u0191\\u01CE\\u0211\\u0229\\u019C\\u018E\\u019A\\u01D0')")
            << QString::fromLatin1("qsTrId('\\u0191\\u01CE\\u0211\\u0229\\u019C\\u018E\\u019A\\u01D0')") << QString::fromUtf8("\xc7\xa0\xc8\xa1\xc8\x8b\xc8\x85\xc8\x95");
    QTest::newRow("qsTrId('\\u0181\\u01A1\\u0213\\u018F\\u018C', 10)")
            << QString::fromLatin1("qsTrId('\\u0181\\u01A1\\u0213\\u018F\\u018C', 10)") << QString::fromUtf8("\x31\x30\x20\xc6\x92\xc6\xa1\xc7\x92\x28\xc8\x99\x29");
    QTest::newRow("qsTrId('\\u0181\\u01A1\\u0213\\u018F\\u018C')")
            << QString::fromLatin1("qsTrId('\\u0181\\u01A1\\u0213\\u018F\\u018C')") << QString::fromUtf8("\xc6\x91\xc6\xb0\xc7\xb9");
    QTest::newRow("qsTrId('\\u01CD\\u0180\\u01A8\\u0190\\u019E\\u01AB')")
            << QString::fromLatin1("qsTrId('\\u01CD\\u0180\\u01A8\\u0190\\u019E\\u01AB')") << QString::fromUtf8("\xc7\x8d\xc6\x80\xc6\xa8\xc6\x90\xc6\x9e\xc6\xab");
}

void tst_QJSEngine::translateScriptUnicodeIdBased()
{
    QFETCH(QString, expression);
    QFETCH(QString, expectedTranslation);

    QScriptEngine engine;

    TranslationScope tranScope(":/translations/idtranslatable-unicode");
    engine.installTranslatorFunctions();

    QCOMPARE(engine.evaluate(expression).toString(), expectedTranslation);
    QVERIFY(!engine.hasUncaughtException());
}

void tst_QJSEngine::translateFromBuiltinCallback()
{
    QScriptEngine eng;
    eng.installTranslatorFunctions();

    // Callback has no translation context.
    eng.evaluate("function foo() { qsTr('foo'); }");

    // Stack at translation time will be:
    // qsTr, foo, forEach, global
    // qsTr() needs to walk to the outer-most (global) frame before it finds
    // a translation context, and this should not crash.
    eng.evaluate("[10,20].forEach(foo)", "script.js");
}
#endif

#if 0 // ###FIXME: No QScriptValue::scope API
void tst_QJSEngine::functionScopes()
{
    QScriptEngine eng;
    {
        // top-level functions have only the global object in their scope
        QScriptValue fun = eng.evaluate("(function() {})");
        QVERIFY(fun.isCallable());
        QEXPECT_FAIL("", "QScriptValue::scope() is internal, not implemented", Abort);
        QVERIFY(fun.scope().isObject());
        QVERIFY(fun.scope().strictlyEquals(eng.globalObject()));
        QVERIFY(!eng.globalObject().scope().isValid());
    }
    {
        QScriptValue fun = eng.globalObject().property("Object");
        QVERIFY(fun.isCallable());
        // native built-in functions don't have scope
        QVERIFY(!fun.scope().isValid());
    }
    {
        // closure
        QScriptValue fun = eng.evaluate("(function(arg) { var foo = arg; return function() { return foo; }; })(123)");
        QVERIFY(fun.isCallable());
        {
            QScriptValue ret = fun.call();
            QVERIFY(ret.isNumber());
            QCOMPARE(ret.toInt(), 123);
        }
        QScriptValue scope = fun.scope();
        QVERIFY(scope.isObject());
        {
            QScriptValue ret = scope.property("foo");
            QVERIFY(ret.isNumber());
            QCOMPARE(ret.toInt(), 123);
            QCOMPARE(scope.propertyFlags("foo"), QScriptValue::Undeletable);
        }
        {
            QScriptValue ret = scope.property("arg");
            QVERIFY(ret.isNumber());
            QCOMPARE(ret.toInt(), 123);
            QCOMPARE(scope.propertyFlags("arg"), QScriptValue::Undeletable | QScriptValue::SkipInEnumeration);
        }

        scope.setProperty("foo", 456);
        {
            QScriptValue ret = fun.call();
            QVERIFY(ret.isNumber());
            QCOMPARE(ret.toInt(), 456);
        }

        scope = scope.scope();
        QVERIFY(scope.isObject());
        QVERIFY(scope.strictlyEquals(eng.globalObject()));
    }
}
#endif

#if 0 // ###FIXME: No QScriptContext API
static QScriptValue counter_inner(QScriptContext *ctx, QScriptEngine *)
{
     QScriptValue outerAct = ctx->callee().scope();
     double count = outerAct.property("count").toNumber();
     outerAct.setProperty("count", count+1);
     return count;
}

static QScriptValue counter(QScriptContext *ctx, QScriptEngine *eng)
{
     QScriptValue act = ctx->activationObject();
     act.setProperty("count", ctx->argument(0).toInt());
     QScriptValue result = eng->newFunction(counter_inner);
     result.setScope(act);
     return result;
}

static QScriptValue counter_hybrid(QScriptContext *ctx, QScriptEngine *eng)
{
     QScriptValue act = ctx->activationObject();
     act.setProperty("count", ctx->argument(0).toInt());
     return eng->evaluate("(function() { return count++; })");
}

void tst_QJSEngine::nativeFunctionScopes()
{
    QScriptEngine eng;
    {
        QScriptValue fun = eng.newFunction(counter);
        QScriptValue cnt = fun.call(QScriptValueList() << 123);
        QVERIFY(cnt.isCallable());
        {
            QScriptValue ret = cnt.call();
            QVERIFY(ret.isNumber());
            QEXPECT_FAIL("", "QScriptValue::setScope not implemented", Continue);
            QCOMPARE(ret.toInt(), 123);
        }
    }
    {
        QScriptValue fun = eng.newFunction(counter_hybrid);
        QScriptValue cnt = fun.call(QScriptValueList() << 123);
        QVERIFY(cnt.isCallable());
        {
            QScriptValue ret = cnt.call();
            QVERIFY(ret.isNumber());
            QCOMPARE(ret.toInt(), 123);
        }
    }

    //from http://doc.trolltech.com/latest/qtscript.html#nested-functions-and-the-scope-chain
    {
        QScriptEngine eng;
        eng.evaluate("function counter() { var count = 0; return function() { return count++; } }\n"
                     "var c1 = counter();  var c2 = counter(); ");
        QCOMPARE(eng.evaluate("c1()").toString(), QString::fromLatin1("0"));
        QCOMPARE(eng.evaluate("c1()").toString(), QString::fromLatin1("1"));
        QCOMPARE(eng.evaluate("c2()").toString(), QString::fromLatin1("0"));
        QCOMPARE(eng.evaluate("c2()").toString(), QString::fromLatin1("1"));
        QVERIFY(!eng.hasUncaughtException());
    }
    {
        QScriptEngine eng;
        eng.globalObject().setProperty("counter", eng.newFunction(counter));
        eng.evaluate("var c1 = counter();  var c2 = counter(); ");
        QCOMPARE(eng.evaluate("c1()").toString(), QString::fromLatin1("0"));
        QEXPECT_FAIL("", "QScriptValue::setScope not implemented", Continue);
        QCOMPARE(eng.evaluate("c1()").toString(), QString::fromLatin1("1"));
        QCOMPARE(eng.evaluate("c2()").toString(), QString::fromLatin1("0"));
        QEXPECT_FAIL("", "QScriptValue::setScope not implemented", Continue);
        QCOMPARE(eng.evaluate("c2()").toString(), QString::fromLatin1("1"));
        QVERIFY(!eng.hasUncaughtException());
    }
    {
        QScriptEngine eng;
        eng.globalObject().setProperty("counter", eng.newFunction(counter_hybrid));
        eng.evaluate("var c1 = counter();  var c2 = counter(); ");
        QCOMPARE(eng.evaluate("c1()").toString(), QString::fromLatin1("0"));
        QCOMPARE(eng.evaluate("c1()").toString(), QString::fromLatin1("1"));
        QCOMPARE(eng.evaluate("c2()").toString(), QString::fromLatin1("0"));
        QCOMPARE(eng.evaluate("c2()").toString(), QString::fromLatin1("1"));
        QVERIFY(!eng.hasUncaughtException());
    }
}
#endif

#if 0 // ###FIXME: No QScriptProgram API
static QScriptValue createProgram(QScriptContext *ctx, QScriptEngine *eng)
{
    QString code = ctx->argument(0).toString();
    QScriptProgram result(code);
    return qScriptValueFromValue(eng, result);
}

void tst_QJSEngine::evaluateProgram()
{
    QScriptEngine eng;

    {
        QString code("1 + 2");
        QString fileName("hello.js");
        int lineNumber(123);
        QScriptProgram program(code, fileName, lineNumber);
        QVERIFY(!program.isNull());
        QCOMPARE(program.sourceCode(), code);
        QCOMPARE(program.fileName(), fileName);
        QCOMPARE(program.firstLineNumber(), lineNumber);

        QScriptValue expected = eng.evaluate(code);
        for (int x = 0; x < 10; ++x) {
            QScriptValue ret = eng.evaluate(program);
            QVERIFY(ret.equals(expected));
        }

        // operator=
        QScriptProgram sameProgram = program;
        QVERIFY(sameProgram == program);
        QVERIFY(eng.evaluate(sameProgram).equals(expected));

        // copy constructor
        QScriptProgram sameProgram2(program);
        QVERIFY(sameProgram2 == program);
        QVERIFY(eng.evaluate(sameProgram2).equals(expected));

        QScriptProgram differentProgram("2 + 3");
        QVERIFY(differentProgram != program);
        QVERIFY(!eng.evaluate(differentProgram).equals(expected));
    }
}

void tst_QJSEngine::evaluateProgram_customScope()
{
    QScriptEngine eng;
    {
        QScriptProgram program("a");
        QVERIFY(!program.isNull());
        {
            QScriptValue ret = eng.evaluate(program);
            QVERIFY(ret.isError());
            QCOMPARE(ret.toString(), QString::fromLatin1("ReferenceError: a is not defined"));
        }

        QScriptValue obj = eng.newObject();
        obj.setProperty("a", 123);
        QScriptContext *ctx = eng.currentContext();
        ctx->pushScope(obj);
        {
            QScriptValue ret = eng.evaluate(program);
            QVERIFY(!ret.isError());
            QVERIFY(ret.equals(obj.property("a")));
        }

        obj.setProperty("a", QScriptValue());
        {
            QScriptValue ret = eng.evaluate(program);
            QVERIFY(ret.isError());
        }

        QScriptValue obj2 = eng.newObject();
        obj2.setProperty("a", 456);
        ctx->pushScope(obj2);
        {
            QScriptValue ret = eng.evaluate(program);
            QVERIFY(!ret.isError());
            QVERIFY(ret.equals(obj2.property("a")));
        }

        ctx->popScope();
    }
}

void tst_QJSEngine::evaluateProgram_closure()
{
    QScriptEngine eng;
    {
        QScriptProgram program("(function() { var count = 0; return function() { return count++; }; })");
        QVERIFY(!program.isNull());
        QScriptValue createCounter = eng.evaluate(program);
        QVERIFY(createCounter.isCallable());
        QScriptValue counter = createCounter.call();
        QVERIFY(counter.isCallable());
        {
            QScriptValue ret = counter.call();
            QVERIFY(ret.isNumber());
        }
        QScriptValue counter2 = createCounter.call();
        QVERIFY(counter2.isCallable());
        QVERIFY(!counter2.equals(counter));
        {
            QScriptValue ret = counter2.call();
            QVERIFY(ret.isNumber());
        }
    }
}

void tst_QJSEngine::evaluateProgram_executeLater()
{
    QScriptEngine eng;
    // Program created in a function call, then executed later
    {
        QScriptValue fun = eng.newFunction(createProgram);
        QScriptProgram program = qscriptvalue_cast<QScriptProgram>(
            fun.call(QScriptValueList() << "a + 1"));
        QVERIFY(!program.isNull());
        eng.globalObject().setProperty("a", QScriptValue());
        {
            QScriptValue ret = eng.evaluate(program);
            QVERIFY(ret.isError());
            QCOMPARE(ret.toString(), QString::fromLatin1("ReferenceError: a is not defined"));
        }
        eng.globalObject().setProperty("a", 122);
        {
            QScriptValue ret = eng.evaluate(program);
            QVERIFY(!ret.isError());
            QVERIFY(ret.isNumber());
            QCOMPARE(ret.toInt(), 123);
        }
    }
}

void tst_QJSEngine::evaluateProgram_multipleEngines()
{
    QScriptEngine eng;
    {
        QString code("1 + 2");
        QScriptProgram program(code);
        QVERIFY(!program.isNull());
        double expected = eng.evaluate(program).toNumber();
        for (int x = 0; x < 2; ++x) {
            QScriptEngine eng2;
            for (int y = 0; y < 2; ++y) {
                double ret = eng2.evaluate(program).toNumber();
                QCOMPARE(ret, expected);
            }
        }
    }
}

void tst_QJSEngine::evaluateProgram_empty()
{
    QScriptEngine eng;
    {
        QScriptProgram program;
        QVERIFY(program.isNull());
        QScriptValue ret = eng.evaluate(program);
        QVERIFY(!ret.isValid());
    }
}
#endif

#if 0 // ###FIXME: No ScriptOwnership API
void tst_QJSEngine::collectGarbageAfterConnect()
{
    // QTBUG-6366
    QScriptEngine engine;
    QPointer<QWidget> widget = new QWidget;
    engine.globalObject().setProperty(
        "widget", engine.newQObject(widget, QScriptEngine::ScriptOwnership));
    QVERIFY(engine.evaluate("widget.customContextMenuRequested.connect(\n"
                            "  function() { print('hello'); }\n"
                            ");")
            .isUndefined());
    QVERIFY(widget != 0);
    engine.evaluate("widget = null;");
    // The connection should not keep the widget alive.
    collectGarbage_helper(engine);
    QVERIFY(widget == 0);
}
#endif

#if 0 // ###FIXME: No QScriptContext API
void tst_QJSEngine::collectGarbageAfterNativeArguments()
{
    // QTBUG-17788
    QScriptEngine eng;
    QScriptContext *ctx = eng.pushContext();
    QScriptValue arguments = ctx->argumentsObject();
    // Shouldn't crash when marking the arguments object.
    collectGarbage_helper(eng);
}

static QScriptValue constructQObjectFromThisObject(QScriptContext *ctx, QScriptEngine *eng)
{
    if (!ctx->isCalledAsConstructor()) {
        qWarning("%s: ctx->isCalledAsConstructor() returned false", Q_FUNC_INFO);
        return QScriptValue();
    }
    return eng->newQObject(ctx->thisObject(), new QObject, QScriptEngine::ScriptOwnership);
}

void tst_QJSEngine::promoteThisObjectToQObjectInConstructor()
{
    QScriptEngine engine;
    QScriptValue ctor = engine.newFunction(constructQObjectFromThisObject);
    engine.globalObject().setProperty("Ctor", ctor);
    QScriptValue object = engine.evaluate("new Ctor");
    QVERIFY(!object.isError());
    QVERIFY(object.isQObject());
    QVERIFY(object.toQObject() != 0);
    QVERIFY(object.property("objectName").isString());
    QVERIFY(object.property("deleteLater").isCallable());
}
#endif

static QRegExp minimal(QRegExp r) { r.setMinimal(true); return r; }

void tst_QJSEngine::qRegExpInport_data()
{
    QTest::addColumn<QRegExp>("rx");
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("matched");

    QTest::newRow("normal")  << QRegExp("(test|foo)") << "test _ foo _ test _ Foo";
    QTest::newRow("normal2")  << QRegExp("(Test|Foo)") << "test _ foo _ test _ Foo";
    QTest::newRow("case insensitive)")  << QRegExp("(test|foo)", Qt::CaseInsensitive) << "test _ foo _ test _ Foo";
    QTest::newRow("case insensitive2)")  << QRegExp("(Test|Foo)", Qt::CaseInsensitive) << "test _ foo _ test _ Foo";
    QTest::newRow("b(a*)(b*)")  << QRegExp("b(a*)(b*)", Qt::CaseInsensitive) << "aaabbBbaAabaAaababaaabbaaab";
    QTest::newRow("greedy")  << QRegExp("a*(a*)", Qt::CaseInsensitive, QRegExp::RegExp2) << "aaaabaaba";
    // this one will fail because we do not support the QRegExp::RegExp in JSC
    //QTest::newRow("not_greedy")  << QRegExp("a*(a*)", Qt::CaseInsensitive, QRegExp::RegExp) << "aaaabaaba";
    QTest::newRow("willcard")  << QRegExp("*.txt", Qt::CaseSensitive, QRegExp::Wildcard) << "file.txt";
    QTest::newRow("willcard 2")  << QRegExp("a?b.txt", Qt::CaseSensitive, QRegExp::Wildcard) << "ab.txt abb.rtc acb.txt";
    QTest::newRow("slash")  << QRegExp("g/.*/s", Qt::CaseInsensitive, QRegExp::RegExp2) << "string/string/string";
    QTest::newRow("slash2")  << QRegExp("g / .* / s", Qt::CaseInsensitive, QRegExp::RegExp2) << "string / string / string";
    QTest::newRow("fixed")  << QRegExp("a*aa.a(ba)*a\\ba", Qt::CaseInsensitive, QRegExp::FixedString) << "aa*aa.a(ba)*a\\ba";
    QTest::newRow("fixed insensitive")  << QRegExp("A*A", Qt::CaseInsensitive, QRegExp::FixedString) << "a*A A*a A*A a*a";
    QTest::newRow("fixed sensitive")  << QRegExp("A*A", Qt::CaseSensitive, QRegExp::FixedString) << "a*A A*a A*A a*a";
    QTest::newRow("html")  << QRegExp("<b>(.*)</b>", Qt::CaseSensitive, QRegExp::RegExp2) << "<b>bold</b><i>italic</i><b>bold</b>";
    QTest::newRow("html minimal")  << minimal(QRegExp("<b>(.*)</b>", Qt::CaseSensitive, QRegExp::RegExp2)) << "<b>bold</b><i>italic</i><b>bold</b>";
    QTest::newRow("aaa")  << QRegExp("a{2,5}") << "aAaAaaaaaAa";
    QTest::newRow("aaa minimal")  << minimal(QRegExp("a{2,5}")) << "aAaAaaaaaAa";
    QTest::newRow("minimal")  << minimal(QRegExp(".*\\} [*8]")) << "}?} ?} *";
    QTest::newRow(".? minimal")  << minimal(QRegExp(".?")) << ".?";
    QTest::newRow(".+ minimal")  << minimal(QRegExp(".+")) << ".+";
    QTest::newRow("[.?] minimal")  << minimal(QRegExp("[.?]")) << ".?";
    QTest::newRow("[.+] minimal")  << minimal(QRegExp("[.+]")) << ".+";
}

void tst_QJSEngine::qRegExpInport()
{
    QSKIP("Test failing - QTBUG-22238");
    QFETCH(QRegExp, rx);
    QFETCH(QString, string);

    QJSEngine eng;
    QJSValue rexp;
    rexp = eng.newRegExp(rx);

    QCOMPARE(rexp.isValid(), true);
    QCOMPARE(rexp.isRegExp(), true);
    QVERIFY(rexp.isCallable());

    QJSValue func = eng.evaluate("(function(string, regexp) { return string.match(regexp); })");
    QJSValue result = func.call(QJSValueList() << string << rexp);

    rx.indexIn(string);
    for (int i = 0; i <= rx.captureCount(); i++)  {
        QCOMPARE(result.property(i).toString(), rx.cap(i));
    }
}

// QScriptValue::toDateTime() returns a local time, whereas JS dates
// are always stored as UTC. QtScript must respect the current time
// zone, and correctly adjust for daylight saving time that may be in
// effect at a given date (QTBUG-9770).
void tst_QJSEngine::dateRoundtripJSQtJS()
{
    uint secs = QDateTime(QDate(2009, 1, 1)).toUTC().toTime_t();
    QJSEngine eng;
    for (int i = 0; i < 8000; ++i) {
        QJSValue jsDate = eng.evaluate(QString::fromLatin1("new Date(%0)").arg(secs * 1000.0));
        QDateTime qtDate = jsDate.toDateTime();
        QJSValue jsDate2 = eng.newDate(qtDate);
        if (jsDate2.toNumber() != jsDate.toNumber())
            QFAIL(qPrintable(jsDate.toString()));
        secs += 2*60*60;
    }
}

void tst_QJSEngine::dateRoundtripQtJSQt()
{
    QDateTime qtDate = QDateTime(QDate(2009, 1, 1));
    QJSEngine eng;
    for (int i = 0; i < 8000; ++i) {
        QJSValue jsDate = eng.newDate(qtDate);
        QDateTime qtDate2 = jsDate.toDateTime();
        if (qtDate2 != qtDate)
            QFAIL(qPrintable(qtDate.toString()));
        qtDate = qtDate.addSecs(2*60*60);
    }
}

void tst_QJSEngine::dateConversionJSQt()
{
    uint secs = QDateTime(QDate(2009, 1, 1)).toUTC().toTime_t();
    QJSEngine eng;
    for (int i = 0; i < 8000; ++i) {
        QJSValue jsDate = eng.evaluate(QString::fromLatin1("new Date(%0)").arg(secs * 1000.0));
        QDateTime qtDate = jsDate.toDateTime();
        QString qtUTCDateStr = qtDate.toUTC().toString(Qt::ISODate);
        QString jsUTCDateStr = jsDate.property("toISOString").callWithInstance(jsDate).toString();
        jsUTCDateStr.remove(jsUTCDateStr.length() - 5, 4); // get rid of milliseconds (".000")
        if (qtUTCDateStr != jsUTCDateStr)
            QFAIL(qPrintable(jsDate.toString()));
        secs += 2*60*60;
    }
}

void tst_QJSEngine::dateConversionQtJS()
{
    QDateTime qtDate = QDateTime(QDate(2009, 1, 1));
    QJSEngine eng;
    for (int i = 0; i < 8000; ++i) {
        QJSValue jsDate = eng.newDate(qtDate);
        QString jsUTCDateStr = jsDate.property("toISOString").callWithInstance(jsDate).toString();
        jsUTCDateStr.remove(jsUTCDateStr.length() - 5, 4); // get rid of milliseconds (".000")
        QString qtUTCDateStr = qtDate.toUTC().toString(Qt::ISODate);
        if (jsUTCDateStr != qtUTCDateStr)
            QFAIL(qPrintable(qtDate.toString()));
        qtDate = qtDate.addSecs(2*60*60);
    }
}

#if 0 // ###FIXME: No QScriptContext API
static QScriptValue createAnotherEngine(QScriptContext *, QScriptEngine *)
{
    QScriptEngine eng;
    eng.evaluate("function foo(x, y) { return x + y; }" );
    eng.evaluate("hello = 5; world = 6" );
    return eng.evaluate("foo(hello,world)").toInt();
}


void tst_QJSEngine::reentrency()
{
    QScriptEngine eng;
    eng.globalObject().setProperty("foo", eng.newFunction(createAnotherEngine));
    eng.evaluate("function bar() { return foo(); }  hello = 9; function getHello() { return hello; }");
    QCOMPARE(eng.evaluate("foo() + getHello() + foo()").toInt(), 5+6 + 9 + 5+6);
    QCOMPARE(eng.evaluate("foo").call().toInt(), 5+6);
    QCOMPARE(eng.evaluate("hello").toInt(), 9);
    QCOMPARE(eng.evaluate("foo() + hello").toInt(), 5+6+9);
}
#endif

#if 0 // ###FIXME: No QSCriptDeclarativeClass API
void tst_QJSEngine::newFixedStaticScopeObject()
{
    // "Static scope objects" is an optimization we do for QML.
    // It enables the creation of JS objects that can guarantee to the
    // compiler that no properties will be added or removed. This enables
    // the compiler to generate a very simple (fast) property access, as
    // opposed to a full virtual lookup. Due to the inherent use of scope
    // chains in QML, this can make a huge difference (10x improvement for
    // benchmark in QTBUG-8576).
    // Ideally we would not need a special object type for this, and the
    // VM would dynamically optimize it to be fast...
    // See also QScriptEngine benchmark.

    QScriptEngine eng;
    static const int propertyCount = 4;
    QString names[] = { "foo", "bar", "baz", "Math" };
    QScriptValue values[] = { 123, "ciao", true, false };
    QScriptValue::PropertyFlags flags[] = { QScriptValue::Undeletable,
                                            QScriptValue::ReadOnly | QScriptValue::Undeletable,
                                            QScriptValue::SkipInEnumeration | QScriptValue::Undeletable,
                                            QScriptValue::Undeletable };
    QScriptValue scope = QScriptDeclarativeClass::newStaticScopeObject(&eng, propertyCount, names, values, flags);

    // Query property.
    for (int i = 0; i < propertyCount; ++i) {
        for (int x = 0; x < 2; ++x) {
            if (x) {
                // Properties can't be deleted.
                scope.setProperty(names[i], QScriptValue());
            }
            QVERIFY(scope.property(names[i]).equals(values[i]));
            QCOMPARE(scope.propertyFlags(names[i]), flags[i]);
        }
    }

    // Property that doesn't exist.
    QVERIFY(!scope.property("noSuchProperty").isValid());
    QCOMPARE(scope.propertyFlags("noSuchProperty"), QScriptValue::PropertyFlags());

    // Write to writable property.
    {
        QScriptValue oldValue = scope.property("foo");
        QVERIFY(oldValue.isNumber());
        QScriptValue newValue = oldValue.toNumber() * 2;
        scope.setProperty("foo", newValue);
        QVERIFY(scope.property("foo").equals(newValue));
        scope.setProperty("foo", oldValue);
        QVERIFY(scope.property("foo").equals(oldValue));
    }

    // Write to read-only property.
    scope.setProperty("bar", 456);
    QVERIFY(scope.property("bar").equals("ciao"));

    // Iterate.
    {
        QScriptValueIterator it(scope);
        QSet<QString> iteratedNames;
        while (it.hasNext()) {
            it.next();
            iteratedNames.insert(it.name());
        }
        for (int i = 0; i < propertyCount; ++i)
            QVERIFY(iteratedNames.contains(names[i]));
    }

    // Push it on the scope chain of a new context.
    QScriptContext *ctx = eng.pushContext();
    ctx->pushScope(scope);
    QCOMPARE(ctx->scopeChain().size(), 3); // Global Object, native activation, custom scope
    QEXPECT_FAIL("", "activationObject has not been implemented yet", Continue);
    QVERIFY(ctx->activationObject().equals(scope));

    // Read property from JS.
    for (int i = 0; i < propertyCount; ++i) {
        for (int x = 0; x < 2; ++x) {
            if (x) {
                // Property can't be deleted from JS.
                QScriptValue ret = eng.evaluate(QString::fromLatin1("delete %0").arg(names[i]));
                QVERIFY(ret.equals(false));
            }
            QVERIFY(eng.evaluate(names[i]).equals(values[i]));
        }
    }

    // Property that doesn't exist.
    QVERIFY(eng.evaluate("noSuchProperty").equals("ReferenceError: noSuchProperty is not defined"));

    // Write property from JS.
    {
        QScriptValue oldValue = eng.evaluate("foo");
        QVERIFY(oldValue.isNumber());
        QScriptValue newValue = oldValue.toNumber() * 2;
        QVERIFY(eng.evaluate("foo = foo * 2; foo").equals(newValue));
        scope.setProperty("foo", oldValue);
        QVERIFY(eng.evaluate("foo").equals(oldValue));
    }

    // Write to read-only property.
    QVERIFY(eng.evaluate("bar = 456; bar").equals("ciao"));

    // Create a closure and return properties from there.
    {
        QScriptValue props = eng.evaluate("(function() { var baz = 'shadow'; return [foo, bar, baz, Math, Array]; })()");
        QVERIFY(props.isArray());
        // "foo" and "bar" come from scope object.
        QVERIFY(props.property(0).equals(scope.property("foo")));
        QVERIFY(props.property(1).equals(scope.property("bar")));
        // "baz" shadows property in scope object.
        QVERIFY(props.property(2).equals("shadow"));
        // "Math" comes from scope object, and shadows Global Object's "Math".
        QVERIFY(props.property(3).equals(scope.property("Math")));
        QVERIFY(!props.property(3).equals(eng.globalObject().property("Math")));
        // "Array" comes from Global Object.
        QVERIFY(props.property(4).equals(eng.globalObject().property("Array")));
    }

    // As with normal JS, assigning to an undefined variable will create
    // the property on the Global Object, not the inner scope.
    QVERIFY(!eng.globalObject().property("newProperty").isValid());
    QVERIFY(eng.evaluate("(function() { newProperty = 789; })()").isUndefined());
    QVERIFY(!scope.property("newProperty").isValid());
    QVERIFY(eng.globalObject().property("newProperty").isNumber());

    // Nested static scope.
    {
        static const int propertyCount2 = 2;
        QString names2[] = { "foo", "hum" };
        QScriptValue values2[] = { 321, "hello" };
        QScriptValue::PropertyFlags flags2[] = { QScriptValue::Undeletable,
                                                 QScriptValue::ReadOnly | QScriptValue::Undeletable };
        QScriptValue scope2 = QScriptDeclarativeClass::newStaticScopeObject(&eng, propertyCount2, names2, values2, flags2);
        ctx->pushScope(scope2);

        // "foo" shadows scope.foo.
        QVERIFY(eng.evaluate("foo").equals(scope2.property("foo")));
        QVERIFY(!eng.evaluate("foo").equals(scope.property("foo")));
        // "hum" comes from scope2.
        QVERIFY(eng.evaluate("hum").equals(scope2.property("hum")));
        // "Array" comes from Global Object.
        QVERIFY(eng.evaluate("Array").equals(eng.globalObject().property("Array")));

        ctx->popScope();
    }

    QScriptValue fun = eng.evaluate("(function() { return foo; })");
    QVERIFY(fun.isCallable());
    eng.popContext();
    // Function's scope chain persists after popContext().
    QVERIFY(fun.call().equals(scope.property("foo")));
}

void tst_QJSEngine::newGrowingStaticScopeObject()
{
    // The main use case for a growing static scope object is to set it as
    // the activation object of a QScriptContext, so that all JS variable
    // declarations end up in that object. It needs to be "growable" since
    // we don't know in advance how many variables a script will declare.

    QScriptEngine eng;
    QScriptValue scope = QScriptDeclarativeClass::newStaticScopeObject(&eng);

    // Initially empty.
    QVERIFY(!QScriptValueIterator(scope).hasNext());
    QVERIFY(!scope.property("foo").isValid());

    // Add a static property.
    scope.setProperty("foo", 123);
    QVERIFY(scope.property("foo").equals(123));
    QEXPECT_FAIL("", "FIXME: newStaticScopeObject not properly implemented", Abort);
    QCOMPARE(scope.propertyFlags("foo"), QScriptValue::Undeletable);

    // Modify existing property.
    scope.setProperty("foo", 456);
    QVERIFY(scope.property("foo").equals(456));

    // Add a read-only property.
    scope.setProperty("bar", "ciao", QScriptValue::ReadOnly);
    QVERIFY(scope.property("bar").equals("ciao"));
    QCOMPARE(scope.propertyFlags("bar"), QScriptValue::ReadOnly | QScriptValue::Undeletable);

    // Attempt to modify read-only property.
    scope.setProperty("bar", "hello");
    QVERIFY(scope.property("bar").equals("ciao"));

    // Properties can't be deleted.
    scope.setProperty("foo", QScriptValue());
    QVERIFY(scope.property("foo").equals(456));
    scope.setProperty("bar", QScriptValue());
    QVERIFY(scope.property("bar").equals("ciao"));

    // Iterate.
    {
        QScriptValueIterator it(scope);
        QSet<QString> iteratedNames;
        while (it.hasNext()) {
            it.next();
            iteratedNames.insert(it.name());
        }
        QCOMPARE(iteratedNames.size(), 2);
        QVERIFY(iteratedNames.contains("foo"));
        QVERIFY(iteratedNames.contains("bar"));
    }

    // Push it on the scope chain of a new context.
    QScriptContext *ctx = eng.pushContext();
    ctx->pushScope(scope);
    QCOMPARE(ctx->scopeChain().size(), 3); // Global Object, native activation, custom scope
    QVERIFY(ctx->activationObject().equals(scope));

    // Read property from JS.
    QVERIFY(eng.evaluate("foo").equals(scope.property("foo")));
    QVERIFY(eng.evaluate("bar").equals(scope.property("bar")));

    // Write property from JS.
    {
        QScriptValue oldValue = eng.evaluate("foo");
        QVERIFY(oldValue.isNumber());
        QScriptValue newValue = oldValue.toNumber() * 2;
        QVERIFY(eng.evaluate("foo = foo * 2; foo").equals(newValue));
        scope.setProperty("foo", oldValue);
        QVERIFY(eng.evaluate("foo").equals(oldValue));
    }

    // Write to read-only property.
    QVERIFY(eng.evaluate("bar = 456; bar").equals("ciao"));

    // Shadow property.
    QVERIFY(eng.evaluate("Math").equals(eng.globalObject().property("Math")));
    scope.setProperty("Math", "fake Math");
    QVERIFY(eng.evaluate("Math").equals(scope.property("Math")));

    // Variable declarations will create properties on the scope.
    eng.evaluate("var baz = 456");
    QVERIFY(scope.property("baz").equals(456));

    // Function declarations will create properties on the scope.
    eng.evaluate("function fun() { return baz; }");
    QVERIFY(scope.property("fun").isCallable());
    QVERIFY(scope.property("fun").call().equals(scope.property("baz")));

    // Demonstrate the limitation of a growable static scope: Once a function that
    // uses the scope has been compiled, it won't pick up properties that are added
    // to the scope later.
    {
        QScriptValue fun = eng.evaluate("(function() { return futureProperty; })");
        QVERIFY(fun.isCallable());
        QVERIFY(fun.call().toString().contains(QString::fromLatin1("ReferenceError")));
        scope.setProperty("futureProperty", "added after the function was compiled");
        // If scope were dynamic, this would return the new property.
        QVERIFY(fun.call().toString().contains(QString::fromLatin1("ReferenceError")));
    }

    eng.popContext();
}
#endif

#if 0 // ###FIXME: No QScript MetaObject API
QT_BEGIN_NAMESPACE
Q_SCRIPT_DECLARE_QMETAOBJECT(QStandardItemModel, QObject*)
QT_END_NAMESPACE

void tst_QJSEngine::scriptValueFromQMetaObject()
{
    QScriptEngine eng;
    {
        QScriptValue meta = eng.scriptValueFromQMetaObject<QScriptEngine>();
        QVERIFY(meta.isQMetaObject());
        QCOMPARE(meta.toQMetaObject(), &QScriptEngine::staticMetaObject);
        // Because of missing Q_SCRIPT_DECLARE_QMETAOBJECT() for QScriptEngine.
        QEXPECT_FAIL("", "FIXME: because construct never returns invalid values", Continue);
        QVERIFY(!meta.callAsConstructor().isValid());
    }
    {
        QScriptValue meta = eng.scriptValueFromQMetaObject<QStandardItemModel>();
        QVERIFY(meta.isQMetaObject());
        QCOMPARE(meta.toQMetaObject(), &QStandardItemModel::staticMetaObject);
        QScriptValue obj = meta.callAsConstructor(QScriptValueList() << eng.newQObject(&eng));
        QVERIFY(obj.isQObject());
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(obj.toQObject());
        QVERIFY(model != 0);
        QCOMPARE(model->parent(), (QObject*)&eng);
    }
}
#endif

void tst_QJSEngine::functionPrototypeExtensions()
{
    // QJS adds connect and disconnect properties to Function.prototype.
    QJSEngine eng;
    QJSValue funProto = eng.globalObject().property("Function").property("prototype");
    QVERIFY(funProto.isCallable());
    QVERIFY(funProto.property("connect").isCallable());
    QCOMPARE(funProto.propertyFlags("connect"), QJSValue::SkipInEnumeration);
    QVERIFY(funProto.property("disconnect").isCallable());
    QCOMPARE(funProto.propertyFlags("disconnect"), QJSValue::SkipInEnumeration);

    // No properties should appear in for-in statements.
    QJSValue props = eng.evaluate("props = []; for (var p in Function.prototype) props.push(p); props");
    QVERIFY(!eng.hasUncaughtException());
    QVERIFY(props.isArray());
    QCOMPARE(props.property("length").toInt(), 0);
}

class ThreadedTestEngine : public QThread {
    Q_OBJECT;

public:
    int result;

    ThreadedTestEngine()
        : result(0) {}

    void run() {
        QJSEngine firstEngine;
        QJSEngine secondEngine;
        QJSValue value = firstEngine.evaluate("1");
        result = secondEngine.evaluate("1 + " + QString::number(value.toInteger())).toInteger();
    }
};

void tst_QJSEngine::threadedEngine()
{
    ThreadedTestEngine thread1;
    ThreadedTestEngine thread2;
    thread1.start();
    thread2.start();
    thread1.wait();
    thread2.wait();
    QCOMPARE(thread1.result, 2);
    QCOMPARE(thread2.result, 2);
}

QTEST_MAIN(tst_QJSEngine)

#include "tst_qjsengine.moc"

