// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#include "qqmljstyperesolver_p.h"

#include "qqmljsimporter_p.h"
#include "qqmljsimportvisitor_p.h"
#include "qqmljslogger_p.h"
#include "qqmljsutils_p.h"
#include <private/qv4value_p.h>

#include <private/qduplicatetracker_p.h>

#include <QtCore/qloggingcategory.h>

QT_BEGIN_NAMESPACE

using namespace Qt::StringLiterals;

Q_STATIC_LOGGING_CATEGORY(lcTypeResolver, "qt.qml.compiler.typeresolver", QtInfoMsg);

static inline void assertExtension(const QQmlJSScope::ConstPtr &type, QLatin1String extension)
{
    Q_ASSERT(type);
    Q_ASSERT(type->extensionType().scope->internalName() == extension);
    Q_ASSERT(type->extensionIsJavaScript());
}

QQmlJSTypeResolver::QQmlJSTypeResolver(QQmlJSImporter *importer)
    : m_imports(importer->builtinInternalNames()),
      m_trackedTypes(std::make_unique<QHash<QQmlJSScope::ConstPtr, TrackedType>>())
{
    const QQmlJSImporter::ImportedTypes &builtinTypes = m_imports;

    m_voidType = builtinTypes.type(u"void"_s).scope;
    assertExtension(m_voidType, "undefined"_L1);

    m_nullType = builtinTypes.type(u"std::nullptr_t"_s).scope;
    Q_ASSERT(m_nullType);

    m_realType = builtinTypes.type(u"double"_s).scope;
    assertExtension(m_realType, "Number"_L1);

    m_floatType = builtinTypes.type(u"float"_s).scope;
    assertExtension(m_floatType, "Number"_L1);

    m_int8Type = builtinTypes.type(u"qint8"_s).scope;
    assertExtension(m_int8Type, "Number"_L1);

    m_uint8Type = builtinTypes.type(u"quint8"_s).scope;
    assertExtension(m_uint8Type, "Number"_L1);

    m_int16Type = builtinTypes.type(u"short"_s).scope;
    assertExtension(m_int16Type, "Number"_L1);

    m_uint16Type = builtinTypes.type(u"ushort"_s).scope;
    assertExtension(m_uint16Type, "Number"_L1);

    m_int32Type = builtinTypes.type(u"int"_s).scope;
    assertExtension(m_int32Type, "Number"_L1);

    m_uint32Type = builtinTypes.type(u"uint"_s).scope;
    assertExtension(m_uint32Type, "Number"_L1);

    m_int64Type = builtinTypes.type(u"qlonglong"_s).scope;
    Q_ASSERT(m_int64Type);

    m_uint64Type = builtinTypes.type(u"qulonglong"_s).scope;
    Q_ASSERT(m_uint64Type);

    m_sizeType = builtinTypes.type(u"qsizetype"_s).scope;
    assertExtension(m_sizeType, "Number"_L1);

    // qsizetype is either a 32bit or a 64bit signed integer. We don't want to special-case it.
    Q_ASSERT(m_sizeType == m_int32Type || m_sizeType == m_int64Type);

    m_boolType = builtinTypes.type(u"bool"_s).scope;
    assertExtension(m_boolType, "Boolean"_L1);

    m_stringType = builtinTypes.type(u"QString"_s).scope;
    assertExtension(m_stringType, "String"_L1);

    m_stringListType = builtinTypes.type(u"QStringList"_s).scope;
    assertExtension(m_stringListType, "Array"_L1);

    m_byteArrayType = builtinTypes.type(u"QByteArray"_s).scope;
    assertExtension(m_byteArrayType, "ArrayBuffer"_L1);

    m_urlType = builtinTypes.type(u"QUrl"_s).scope;
    assertExtension(m_urlType, "URL"_L1);

    m_dateTimeType = builtinTypes.type(u"QDateTime"_s).scope;
    assertExtension(m_dateTimeType, "Date"_L1);

    m_dateType = builtinTypes.type(u"QDate"_s).scope;
    Q_ASSERT(m_dateType);

    m_timeType = builtinTypes.type(u"QTime"_s).scope;
    Q_ASSERT(m_timeType);

    m_variantListType = builtinTypes.type(u"QVariantList"_s).scope;
    assertExtension(m_variantListType, "Array"_L1);

    m_variantMapType = builtinTypes.type(u"QVariantMap"_s).scope;
    Q_ASSERT(m_variantMapType);
    m_varType = builtinTypes.type(u"QVariant"_s).scope;
    Q_ASSERT(m_varType);

    m_jsValueType = builtinTypes.type(u"QJSValue"_s).scope;
    Q_ASSERT(m_jsValueType);

    m_qObjectType = builtinTypes.type(u"QObject"_s).scope;
    assertExtension(m_qObjectType, "Object"_L1);

    m_qObjectListType = builtinTypes.type(u"QObjectList"_s).scope;
    assertExtension(m_qObjectListType, "Array"_L1);

    m_qQmlScriptStringType = builtinTypes.type(u"QQmlScriptString"_s).scope;
    Q_ASSERT(m_qQmlScriptStringType);

    m_functionType = builtinTypes.type(u"function"_s).scope;
    Q_ASSERT(m_functionType);

    m_numberPrototype = builtinTypes.type(u"NumberPrototype"_s).scope;
    Q_ASSERT(m_numberPrototype);

    m_arrayPrototype = builtinTypes.type(u"ArrayPrototype"_s).scope;
    Q_ASSERT(m_arrayPrototype);

    m_listPropertyType = m_qObjectType->listType();
    Q_ASSERT(m_listPropertyType->internalName() == u"QQmlListProperty<QObject>"_s);
    Q_ASSERT(m_listPropertyType->accessSemantics() == QQmlJSScope::AccessSemantics::Sequence);
    Q_ASSERT(m_listPropertyType->valueTypeName() == u"QObject"_s);
    assertExtension(m_listPropertyType, "Array"_L1);

    QQmlJSScope::Ptr emptyType = QQmlJSScope::create();
    emptyType->setAccessSemantics(QQmlJSScope::AccessSemantics::None);
    m_emptyType = emptyType;

    QQmlJSScope::Ptr jsPrimitiveType = QQmlJSScope::create();
    jsPrimitiveType->setInternalName(u"QJSPrimitiveValue"_s);
    jsPrimitiveType->setFilePath(u"qjsprimitivevalue.h"_s);
    jsPrimitiveType->setAccessSemantics(QQmlJSScope::AccessSemantics::Value);
    m_jsPrimitiveType = jsPrimitiveType;

    QQmlJSScope::Ptr metaObjectType = QQmlJSScope::create();
    metaObjectType->setInternalName(u"const QMetaObject"_s);
    metaObjectType->setFilePath(u"qmetaobject.h"_s);
    metaObjectType->setAccessSemantics(QQmlJSScope::AccessSemantics::Reference);
    m_metaObjectType = metaObjectType;

    m_jsGlobalObject = importer->jsGlobalObject();

    QQmlJSScope::Ptr forInIteratorPtr = QQmlJSScope::create();
    forInIteratorPtr->setAccessSemantics(QQmlJSScope::AccessSemantics::Value);
    forInIteratorPtr->setFilePath(u"qjslist.h"_s);
    forInIteratorPtr->setInternalName(u"QJSListForInIterator::Ptr"_s);
    m_forInIteratorPtr = forInIteratorPtr;

    QQmlJSScope::Ptr forOfIteratorPtr = QQmlJSScope::create();
    forOfIteratorPtr->setAccessSemantics(QQmlJSScope::AccessSemantics::Value);
    forOfIteratorPtr->setFilePath(u"qjslist.h"_s);
    forOfIteratorPtr->setInternalName(u"QJSListForOfIterator::Ptr"_s);
    m_forOfIteratorPtr = forOfIteratorPtr;

    // We use this as scope type quite often, and it should always be the same scope type.
    m_jsGlobalObjectContent = globalType(m_jsGlobalObject);
}

/*!
    \internal

    Initializes the type resolver. As part of that initialization, makes \a
    visitor traverse the program when given.
*/
void QQmlJSTypeResolver::init(QQmlJSImportVisitor *visitor, QQmlJS::AST::Node *program)
{
    m_logger = visitor->logger();

    m_objectsById.clear();
    m_objectsByLocation.clear();
    m_imports.clear();
    m_signalHandlers.clear();

    if (program)
        program->accept(visitor);

    m_objectsById = visitor->addressableScopes();
    m_objectsByLocation = visitor->scopesBylocation();
    m_signalHandlers = visitor->signalHandlers();
    m_imports = visitor->imports();
    m_seenModuleQualifiers = visitor->seenModuleQualifiers();
}

QQmlJSScope::ConstPtr QQmlJSTypeResolver::mathObject() const
{
    return jsGlobalObject()->property(u"Math"_s).type();
}

QQmlJSScope::ConstPtr QQmlJSTypeResolver::consoleObject() const
{
    return jsGlobalObject()->property(u"console"_s).type();
}

QQmlJSScope::ConstPtr
QQmlJSTypeResolver::scopeForLocation(const QV4::CompiledData::Location &location) const
{
    // #if required for standalone DOM compilation against Qt 6.2
    qCDebug(lcTypeResolver()).nospace()
            << "looking for object at " << location.line() << ':' << location.column();
    return m_objectsByLocation[location];
}

QQmlJSScope::ConstPtr QQmlJSTypeResolver::typeFromAST(QQmlJS::AST::Type *type) const
{
    const QString typeId = QmlIR::IRBuilder::asString(type->typeId);
    if (!type->typeArgument)
        return m_imports.type(typeId).scope;
    if (typeId == u"list"_s) {
        if (const QQmlJSScope::ConstPtr typeArgument = typeForName(type->typeArgument->toString()))
            return typeArgument->listType();
    }
    return QQmlJSScope::ConstPtr();
}

QQmlJSScope::ConstPtr QQmlJSTypeResolver::typeForConst(QV4::ReturnedValue rv) const
{
    QV4::Value value = QV4::Value::fromReturnedValue(rv);
    if (value.isUndefined())
        return voidType();

    if (value.isInt32())
        return int32Type();

    if (value.isBoolean())
        return boolType();

    if (value.isDouble())
        return realType();

    if (value.isNull())
        return nullType();

    if (value.isEmpty())
        return emptyType();

    return {};
}

QQmlJSRegisterContent
QQmlJSTypeResolver::typeForBinaryOperation(QSOperator::Op oper, const QQmlJSRegisterContent &left,
                                           const QQmlJSRegisterContent &right) const
{
    Q_ASSERT(left.isValid());
    Q_ASSERT(right.isValid());

    switch (oper) {
    case QSOperator::Op::Equal:
    case QSOperator::Op::NotEqual:
    case QSOperator::Op::StrictEqual:
    case QSOperator::Op::StrictNotEqual:
    case QSOperator::Op::Lt:
    case QSOperator::Op::Gt:
    case QSOperator::Op::Ge:
    case QSOperator::Op::In:
    case QSOperator::Op::Le:
        return globalType(boolType());
    case QSOperator::Op::BitAnd:
    case QSOperator::Op::BitOr:
    case QSOperator::Op::BitXor:
    case QSOperator::Op::LShift:
    case QSOperator::Op::RShift:
        return builtinType(int32Type());
    case QSOperator::Op::URShift:
        return builtinType(uint32Type());
    case QSOperator::Op::Add: {
        const auto leftContents = left.containedType();
        const auto rightContents = right.containedType();
        if (equals(leftContents, stringType()) || equals(rightContents, stringType()))
            return builtinType(stringType());

        const QQmlJSScope::ConstPtr result = merge(leftContents, rightContents);
        if (equals(result, boolType()))
            return builtinType(int32Type());
        if (isNumeric(result))
            return builtinType(realType());

        return builtinType(jsPrimitiveType());
    }
    case QSOperator::Op::Sub:
    case QSOperator::Op::Mul:
    case QSOperator::Op::Exp: {
        const QQmlJSScope::ConstPtr result = merge(left.containedType(), right.containedType());
        return builtinType(equals(result, boolType()) ? int32Type() : realType());
    }
    case QSOperator::Op::Div:
    case QSOperator::Op::Mod:
        return builtinType(realType());
    case QSOperator::Op::As:
        return right;
    default:
        break;
    }

    return merge(left, right);
}

QQmlJSRegisterContent QQmlJSTypeResolver::typeForArithmeticUnaryOperation(
        UnaryOperator op, const QQmlJSRegisterContent &operand) const
{
    switch (op) {
    case UnaryOperator::Not:
        return builtinType(boolType());
    case UnaryOperator::Complement:
        return builtinType(int32Type());
    case UnaryOperator::Plus:
        if (isIntegral(operand))
            return operand;
        Q_FALLTHROUGH();
    default:
        if (equals(operand.containedType(), boolType()))
            return builtinType(int32Type());
        break;
    }

    return builtinType(realType());
}

bool QQmlJSTypeResolver::isPrimitive(const QQmlJSRegisterContent &type) const
{
    return isPrimitive(type.containedType());
}

bool QQmlJSTypeResolver::isNumeric(const QQmlJSRegisterContent &type) const
{
    return isNumeric(type.containedType());
}

bool QQmlJSTypeResolver::isIntegral(const QQmlJSRegisterContent &type) const
{
    return isIntegral(type.containedType());
}

bool QQmlJSTypeResolver::isIntegral(const QQmlJSScope::ConstPtr &type) const
{
    // Only types of length <= 32bit count as integral
    return isSignedInteger(type) || isUnsignedInteger(type);
}

bool QQmlJSTypeResolver::isPrimitive(const QQmlJSScope::ConstPtr &type) const
{
    return isNumeric(type)
            || equals(type, m_boolType) || equals(type, m_voidType) || equals(type, m_nullType)
            || equals(type, m_stringType) || equals(type, m_jsPrimitiveType);
}

bool QQmlJSTypeResolver::isNumeric(const QQmlJSScope::ConstPtr &type) const
{
    return QQmlJSUtils::searchBaseAndExtensionTypes(
            type, [&](const QQmlJSScope::ConstPtr &scope, QQmlJSScope::ExtensionKind mode) {
                if (mode == QQmlJSScope::ExtensionNamespace)
                    return false;
                return equals(scope, m_numberPrototype);
    });
}

bool QQmlJSTypeResolver::isSignedInteger(const QQmlJSScope::ConstPtr &type) const
{
    return equals(type, m_int8Type)
            || equals(type, m_int16Type)
            || equals(type, m_int32Type)
            || equals(type, m_int64Type);
}

bool QQmlJSTypeResolver::isUnsignedInteger(const QQmlJSScope::ConstPtr &type) const
{
    return equals(type, m_uint8Type)
            || equals(type, m_uint16Type)
            || equals(type, m_uint32Type)
            || equals(type, m_uint64Type);
}

bool QQmlJSTypeResolver::isNativeArrayIndex(const QQmlJSScope::ConstPtr &type) const
{
    return (equals(type, m_uint8Type)
            || equals(type, m_int8Type)
            || equals(type, m_uint16Type)
            || equals(type, m_int16Type)
            || equals(type, m_uint32Type)
            || equals(type, m_int32Type));
}

QQmlJSScope::ConstPtr QQmlJSTypeResolver::trackedType(const QQmlJSScope::ConstPtr &type) const
{
    if (m_cloneMode == QQmlJSTypeResolver::DoNotCloneTypes)
        return type;

    // If origin is in fact an already tracked type, track the original of that one instead.
    const auto it = m_trackedTypes->find(type);
    QQmlJSScope::ConstPtr orig = (it == m_trackedTypes->end()) ? type : it->original;

    QQmlJSScope::Ptr clone = QQmlJSScope::clone(orig);
    m_trackedTypes->insert(clone, { std::move(orig), QQmlJSScope::ConstPtr(), clone });
    return clone;
}

QQmlJSRegisterContent QQmlJSTypeResolver::shallowTransformed(
        const QQmlJSRegisterContent &origin,
        QQmlJSScope::ConstPtr (QQmlJSTypeResolver::*op)(const QQmlJSScope::ConstPtr &) const,
        const QQmlJSRegisterContent &transformedScope) const
{
    if (origin.isType()) {
        return QQmlJSRegisterContent::create(
                (this->*op)(origin.type()), origin.resultLookupIndex(), origin.variant(),
                transformedScope);
    }

    if (origin.isProperty()) {
        QQmlJSMetaProperty prop = origin.property();
        prop.setType((this->*op)(prop.type()));
        return QQmlJSRegisterContent::create(
                prop, origin.baseLookupIndex(), origin.resultLookupIndex(), origin.variant(),
                transformedScope);
    }

    if (origin.isEnumeration()) {
        QQmlJSMetaEnum enumeration = origin.enumeration();
        enumeration.setType((this->*op)(enumeration.type()));
        return QQmlJSRegisterContent::create(
                enumeration, origin.enumMember(), origin.variant(),
                transformedScope);
    }

    if (origin.isMethod()) {
        return QQmlJSRegisterContent::create(
                origin.method(), (this->*op)(origin.methodType()), origin.variant(),
                transformedScope);
    }

    if (origin.isImportNamespace()) {
        return QQmlJSRegisterContent::create(
                origin.importNamespace(), (this->*op)(origin.importNamespaceType()),
                origin.variant(), transformedScope);
    }

    if (origin.isConversion()) {
        // When retrieving the originals we want a deep retrieval.
        // When tracking a new type, we don't want to re-track its originals, though.

        const QList<QQmlJSScope::ConstPtr> origins = origin.conversionOrigins();
        QList<QQmlJSRegisterContent> transformedOrigins;
        if (op == &QQmlJSTypeResolver::trackedType) {
            transformedOrigins = syntheticTypes(origins);
        } else {
            transformedOrigins.reserve(origins.length());
            for (const QQmlJSScope::ConstPtr &origin: origins)
                transformedOrigins.append(syntheticType((this->*op)(origin)));

        }

        return QQmlJSRegisterContent::create(
                transformedOrigins,
                (this->*op)(origin.conversionResult()),
                shallowTransformed(
                        origin.conversionResultScope(), op,
                        origin.conversionResultScope().scopeType()),
                origin.variant(), transformedScope);
    }

    Q_UNREACHABLE_RETURN({});
}

QQmlJSRegisterContent QQmlJSTypeResolver::transformed(
        const QQmlJSRegisterContent &origin,
        QQmlJSScope::ConstPtr (QQmlJSTypeResolver::*op)(const QQmlJSScope::ConstPtr &) const) const
{
    // We transform one level deep for now.
    // TODO: This is quite arbitrary, but it will fix itself
    //       once we re-organize the transformations.
    const QQmlJSRegisterContent transformedScope
            = shallowTransformed(origin.scopeType(), op, origin.scopeType().scopeType());

    return shallowTransformed(origin, op, transformedScope);
}

QQmlJSScope::ConstPtr QQmlJSTypeResolver::containedTypeForName(const QString &name) const
{
    QQmlJSScope::ConstPtr type = typeForName(name);

    if (!type || type->isSingleton() || type->isScript())
        return type;

    switch (type->accessSemantics()) {
    case QQmlJSScope::AccessSemantics::Reference:
        if (const auto attached = type->attachedType())
            return genericType(attached) ? attached : QQmlJSScope::ConstPtr();
        return metaObjectType();
    case QQmlJSScope::AccessSemantics::None:
        return metaObjectType();
    case QQmlJSScope::AccessSemantics::Sequence:
    case QQmlJSScope::AccessSemantics::Value:
        return canAddressValueTypes() ?  metaObjectType() : QQmlJSScope::ConstPtr();
    }

    Q_UNREACHABLE_RETURN(QQmlJSScope::ConstPtr());
}

QQmlJSRegisterContent QQmlJSTypeResolver::registerContentForName(
        const QString &name, const QQmlJSRegisterContent &scopeType,
        bool hasObjectModulePrefix) const
{
    QQmlJSScope::ConstPtr type = typeForName(name);
    if (!type)
        return QQmlJSRegisterContent();

    if (type->isSingleton()) {
        return QQmlJSRegisterContent::create(
                type, QQmlJSRegisterContent::InvalidLookupIndex,
                QQmlJSRegisterContent::Singleton, scopeType);
    }

    if (type->isScript()) {
        return QQmlJSRegisterContent::create(
                type, QQmlJSRegisterContent::InvalidLookupIndex,
                QQmlJSRegisterContent::Script, scopeType);
    }

    const QQmlJSRegisterContent namedType = QQmlJSRegisterContent::create(
            type, QQmlJSRegisterContent::InvalidLookupIndex, QQmlJSRegisterContent::TypeByName,
            scopeType);

    if (const auto attached = type->attachedType()) {
        if (!genericType(attached)) {
            m_logger->log(u"Cannot resolve generic base of attached %1"_s.arg(
                                  attached->internalName()),
                          qmlCompiler, attached->sourceLocation());
            return {};
        } else if (type->accessSemantics() != QQmlJSScope::AccessSemantics::Reference) {
            m_logger->log(u"Cannot retrieve attached object for non-reference type %1"_s.arg(
                                  type->internalName()),
                          qmlCompiler, type->sourceLocation());
            return {};
        } else {
            // We don't know yet whether we need the attached or the plain object. In direct
            // mode, we will figure this out using the scope type and access any enums of the
            // plain type directly. In indirect mode, we can use enum lookups.
            return QQmlJSRegisterContent::create(
                        attached, QQmlJSRegisterContent::InvalidLookupIndex,
                        hasObjectModulePrefix
                            ? QQmlJSRegisterContent::ObjectAttached
                            : QQmlJSRegisterContent::ScopeAttached, namedType);
        }
    }

    switch (type->accessSemantics()) {
    case QQmlJSScope::AccessSemantics::None:
    case QQmlJSScope::AccessSemantics::Reference:
        // A plain reference to a non-singleton, non-attached type.
        // We may still need the plain type reference for enum lookups,
        // Store it as QMetaObject.
        // This only works with namespaces and object types.
        return QQmlJSRegisterContent::create(
                metaObjectType(), QQmlJSRegisterContent::InvalidLookupIndex,
                QQmlJSRegisterContent::MetaType, namedType);
    case QQmlJSScope::AccessSemantics::Sequence:
    case QQmlJSScope::AccessSemantics::Value:
        if (canAddressValueTypes()) {
            return QQmlJSRegisterContent::create(
                    metaObjectType(), QQmlJSRegisterContent::InvalidLookupIndex,
                    QQmlJSRegisterContent::MetaType, namedType);
        }
        // Else this is not actually a type reference. You cannot get the metaobject
        // of a value type in QML and sequences don't even have metaobjects.
        break;
    }

    return QQmlJSRegisterContent();
}

QQmlJSRegisterContent QQmlJSTypeResolver::original(const QQmlJSRegisterContent &type) const
{
    return transformed(type, &QQmlJSTypeResolver::originalType);
}

QQmlJSRegisterContent QQmlJSTypeResolver::tracked(const QQmlJSRegisterContent &type) const
{
    return transformed(type, &QQmlJSTypeResolver::trackedType);
}

QQmlJSScope::ConstPtr QQmlJSTypeResolver::trackedContainedType(
        const QQmlJSRegisterContent &container) const
{
    const QQmlJSScope::ConstPtr type = container.containedType();
    return m_trackedTypes->contains(type) ? type : QQmlJSScope::ConstPtr();
}

QQmlJSScope::ConstPtr QQmlJSTypeResolver::originalContainedType(
        const QQmlJSRegisterContent &container) const
{
    return originalType(container.containedType());
}

bool QQmlJSTypeResolver::adjustTrackedType(
        const QQmlJSScope::ConstPtr &tracked, const QQmlJSScope::ConstPtr &conversion) const
{
    if (m_cloneMode == QQmlJSTypeResolver::DoNotCloneTypes)
        return true;

    const auto it = m_trackedTypes->find(tracked);
    Q_ASSERT(it != m_trackedTypes->end());

    // If we cannot convert to the new type without the help of e.g. lookupResultMetaType(),
    // we better not change the type.
    if (!canPrimitivelyConvertFromTo(tracked, conversion)
           && !canPopulate(conversion, tracked, nullptr)
           && !selectConstructor(conversion, tracked, nullptr).isValid()) {
        return false;
    }

    it->replacement = comparableType(conversion);
    *it->clone = std::move(*QQmlJSScope::clone(conversion));
    return true;
}

bool QQmlJSTypeResolver::adjustTrackedType(
        const QQmlJSScope::ConstPtr &tracked, const QList<QQmlJSScope::ConstPtr> &conversions) const
{
    if (m_cloneMode == QQmlJSTypeResolver::DoNotCloneTypes)
        return true;

    const auto it = m_trackedTypes->find(tracked);
    Q_ASSERT(it != m_trackedTypes->end());
    QQmlJSScope::Ptr mutableTracked = it->clone;
    QQmlJSScope::ConstPtr result;
    for (const QQmlJSScope::ConstPtr &type : conversions)
        result = merge(type, result);

    // If we cannot convert to the new type without the help of e.g. lookupResultMetaType(),
    // we better not change the type.
    if (!canPrimitivelyConvertFromTo(tracked, result)
            && !canPopulate(result, tracked, nullptr)
            && !selectConstructor(result, tracked, nullptr).isValid()) {
        return false;
    }

    it->replacement = comparableType(result);
    *mutableTracked = std::move(*QQmlJSScope::clone(result));
    return true;
}

void QQmlJSTypeResolver::adjustOriginalType(
        const QQmlJSScope::ConstPtr &tracked, const QQmlJSScope::ConstPtr &conversion) const
{
    if (m_cloneMode == QQmlJSTypeResolver::DoNotCloneTypes)
        return;

    const auto it = m_trackedTypes->find(tracked);
    Q_ASSERT(it != m_trackedTypes->end());

    it->original = conversion;
    *it->clone = std::move(*QQmlJSScope::clone(conversion));
}

void QQmlJSTypeResolver::generalizeType(const QQmlJSScope::ConstPtr &type) const
{
    if (m_cloneMode == QQmlJSTypeResolver::DoNotCloneTypes)
        return;

    const auto it = m_trackedTypes->find(type);
    Q_ASSERT(it != m_trackedTypes->end());
    *it->clone = std::move(*QQmlJSScope::clone(genericType(type)));
    if (it->replacement)
        it->replacement = genericType(it->replacement);
    it->original = genericType(it->original);
}

bool QQmlJSTypeResolver::canConvertFromTo(const QQmlJSScope::ConstPtr &from,
                                          const QQmlJSScope::ConstPtr &to) const
{
    if (canPrimitivelyConvertFromTo(from, to)
            || canPopulate(to, from, nullptr)
            || selectConstructor(to, from, nullptr).isValid()) {
        return true;
    }

    // ### need a generic solution for custom cpp types:
    // if (from->m_hasBoolOverload && equals(to, boolType))
    //    return true;

    // All of these types have QString conversions that require a certain format
    // TODO: Actually verify these strings or deprecate them.
    //       Some of those type are builtins or should be builtins. We should add code for them
    //       in QQmlJSCodeGenerator::conversion().
    if (equals(from, m_stringType) && !to.isNull()) {
        const QString toTypeName = to->internalName();
        if (toTypeName == u"QPoint"_s || toTypeName == u"QPointF"_s
                || toTypeName == u"QSize"_s || toTypeName == u"QSizeF"_s
                || toTypeName == u"QRect"_s || toTypeName == u"QRectF"_s) {
            return true;
        }
    }

    return false;
}

bool QQmlJSTypeResolver::canConvertFromTo(const QQmlJSRegisterContent &from,
                                          const QQmlJSRegisterContent &to) const
{
    return canConvertFromTo(from.containedType(), to.containedType());
}

static QQmlJSRegisterContent::ContentVariant mergeVariants(QQmlJSRegisterContent::ContentVariant a,
                                                           QQmlJSRegisterContent::ContentVariant b)
{
    return (a == b) ? a : QQmlJSRegisterContent::Unknown;
}

QQmlJSRegisterContent QQmlJSTypeResolver::merge(const QQmlJSRegisterContent &a,
                                                const QQmlJSRegisterContent &b) const
{
    if (a == b)
        return a;

    QList<QQmlJSScope::ConstPtr> origins;

    QQmlJSRegisterContent aResultScope;
    if (a.isConversion()) {
        origins.append(a.conversionOrigins());
        aResultScope = a.conversionResultScope();
    } else {
        origins.append(a.containedType());
        aResultScope = a.scopeType();
    }

    QQmlJSRegisterContent bResultScope;
    if (b.isConversion()) {
        origins.append(b.conversionOrigins());
        bResultScope = b.conversionResultScope();
    } else {
        origins.append(b.containedType());
        bResultScope = b.scopeType();
    }

    std::sort(origins.begin(), origins.end());
    const auto erase = std::unique(origins.begin(), origins.end());
    origins.erase(erase, origins.end());

    return QQmlJSRegisterContent::create(
            syntheticTypes(origins),
            merge(a.containedType(), b.containedType()),
            merge(aResultScope, bResultScope),
            mergeVariants(a.variant(), b.variant()),
            merge(a.scopeType(), b.scopeType()));
}

QQmlJSScope::ConstPtr QQmlJSTypeResolver::merge(const QQmlJSScope::ConstPtr &a,
                                                const QQmlJSScope::ConstPtr &b) const
{
    if (a.isNull())
        return b;

    if (b.isNull())
        return a;

    const auto commonBaseType = [this](
            const QQmlJSScope::ConstPtr &a, const QQmlJSScope::ConstPtr &b) {
        for (QQmlJSScope::ConstPtr aBase = a; aBase; aBase = aBase->baseType()) {
            for (QQmlJSScope::ConstPtr bBase = b; bBase; bBase = bBase->baseType()) {
                if (equals(aBase, bBase))
                    return aBase;
            }
        }

        return QQmlJSScope::ConstPtr();
    };


    if (equals(a, b))
        return a;

    if (equals(a, jsValueType()) || equals(a, varType()))
        return a;
    if (equals(b, jsValueType()) || equals(b, varType()))
        return b;

    const auto isInt32Compatible = [&](const QQmlJSScope::ConstPtr &type) {
        return (isIntegral(type) && !equals(type, uint32Type())) || equals(type, boolType());
    };

    if (isInt32Compatible(a) && isInt32Compatible(b))
        return int32Type();

    const auto isUInt32Compatible = [&](const QQmlJSScope::ConstPtr &type) {
        return isUnsignedInteger(type) || equals(type, boolType());
    };

    if (isUInt32Compatible(a) && isUInt32Compatible(b))
        return uint32Type();

    if (isNumeric(a) && isNumeric(b))
        return realType();

    if (isPrimitive(a) && isPrimitive(b))
        return jsPrimitiveType();

    if (auto commonBase = commonBaseType(a, b))
        return commonBase;

    if ((equals(a, nullType()) || equals(a, boolType())) && b->isReferenceType())
        return b;

    if ((equals(b, nullType()) || equals(b, boolType())) && a->isReferenceType())
        return a;

    return varType();
}

bool QQmlJSTypeResolver::canHold(
        const QQmlJSScope::ConstPtr &container, const QQmlJSScope::ConstPtr &contained) const
{
    if (equals(container, contained)
            || equals(container, m_varType)
            || equals(container, m_jsValueType)) {
        return true;
    }

    if (equals(container, m_jsPrimitiveType))
        return isPrimitive(contained);

    if (equals(container, m_variantListType))
        return contained->accessSemantics() == QQmlJSScope::AccessSemantics::Sequence;

    if (equals(container, m_qObjectListType) || equals(container, m_listPropertyType)) {
        if (contained->accessSemantics() != QQmlJSScope::AccessSemantics::Sequence)
            return false;
        if (QQmlJSScope::ConstPtr value = contained->valueType())
            return value->isReferenceType();
        return false;
    }

    if (QQmlJSUtils::searchBaseAndExtensionTypes(
                container, [&](const QQmlJSScope::ConstPtr &base) {
        return equals(base, contained);
    })) {
        return true;
    }

    if (container->isReferenceType()) {
        if (QQmlJSUtils::searchBaseAndExtensionTypes(
                    contained, [&](const QQmlJSScope::ConstPtr &base) {
            return equals(base, container);
        })) {
            return true;
        }
    }

    return false;
}


bool QQmlJSTypeResolver::canHoldUndefined(const QQmlJSRegisterContent &content) const
{
    const auto canBeUndefined = [this](const QQmlJSScope::ConstPtr &type) {
        return equals(type, m_voidType) || equals(type, m_varType)
                || equals(type, m_jsValueType) || equals(type, m_jsPrimitiveType);
    };

    if (!canBeUndefined(content.containedType()))
        return false;

    if (!content.isConversion())
        return true;

    const auto origins = content.conversionOrigins();
    for (const auto &origin : origins) {
        if (canBeUndefined(origin))
            return true;
    }

    return false;
}

bool QQmlJSTypeResolver::isOptionalType(const QQmlJSRegisterContent &content) const
{
    if (!content.isConversion())
        return false;

    const auto origins = content.conversionOrigins();
    if (origins.length() != 2)
        return false;

    return equals(origins[0], m_voidType) || equals(origins[1], m_voidType);
}

QQmlJSScope::ConstPtr QQmlJSTypeResolver::extractNonVoidFromOptionalType(
        const QQmlJSRegisterContent &content) const
{
    if (!isOptionalType(content))
        return QQmlJSScope::ConstPtr();

    const auto origins = content.conversionOrigins();
    const QQmlJSScope::ConstPtr result = equals(origins[0], m_voidType) ? origins[1] : origins[0];
    Q_ASSERT(!equals(result, m_voidType));
    return result;
}

QQmlJSScope::ConstPtr QQmlJSTypeResolver::genericType(
        const QQmlJSScope::ConstPtr &type,
        ComponentIsGeneric allowComponent) const
{
    if (type->isScript())
        return m_jsValueType;

    if (equals(type, m_metaObjectType))
        return m_metaObjectType;

    if (type->accessSemantics() == QQmlJSScope::AccessSemantics::Reference) {
        QString unresolvedBaseTypeName;
        for (auto base = type; base;) {
            // QObject and QQmlComponent are the two required base types.
            // Any QML type system has to define those, or use the ones from builtins.
            // As QQmlComponent is derived from QObject, we can restrict ourselves to the latter.
            // This results in less if'ery when retrieving a QObject* from somewhere and deciding
            // what it is.
            if (base->internalName() == u"QObject"_s) {
                return base;
            } else if (allowComponent == ComponentIsGeneric::Yes
                       && base->internalName() == u"QQmlComponent"_s) {
                return base;
            }

            if (auto baseBase = base->baseType()) {
                base = baseBase;
            } else {
                unresolvedBaseTypeName = base->baseTypeName();
                break;
            }
        }

        // Reference types that are not QObject or QQmlComponent are likely JavaScript objects.
        // We don't want to deal with those, but m_jsValueType is the best generic option.
        if (type->filePath().isEmpty())
            return m_jsValueType;

        m_logger->log(u"Object type %1 is not derived from QObject or QQmlComponent. "
                      "You may need to fully qualify all names in C++ so that moc can see them. "
                      "You may also need to add qt_extract_metatypes(<target containing %2>)."_s
                      .arg(type->internalName(), unresolvedBaseTypeName),
                      qmlCompiler, type->sourceLocation());

        // If it does have a filePath, it's some C++ type which we haven't fully resolved.
        return m_jsValueType;
    }

    if (type->isListProperty())
        return m_listPropertyType;

    if (type->scopeType() == QQmlSA::ScopeType::EnumScope)
        return type->baseType();

    if (isPrimitive(type)) {
        // If the filePath is set, the type is storable and we can just return it.
        if (!type->filePath().isEmpty())
            return type;

        // If the type is JavaScript's 'number' type, it's not directly storable, but still
        // primitive. We use C++ 'double' then.
        if (isNumeric(type))
            return m_realType;

        // Otherwise we use QJSPrimitiveValue.
        // TODO: JavaScript's 'string' and 'boolean' could be special-cased here.
        return m_jsPrimitiveType;
    }

    for (const QQmlJSScope::ConstPtr &builtin : {
                 m_realType, m_floatType, m_int8Type, m_uint8Type, m_int16Type, m_uint16Type,
                 m_int32Type, m_uint32Type, m_int64Type, m_uint64Type, m_boolType, m_stringType,
                 m_stringListType, m_byteArrayType, m_urlType, m_dateTimeType, m_dateType,
                 m_timeType, m_variantListType, m_variantMapType, m_varType, m_jsValueType,
                 m_jsPrimitiveType, m_listPropertyType, m_qObjectType, m_qObjectListType,
                 m_metaObjectType, m_forInIteratorPtr, m_forOfIteratorPtr }) {
        if (equals(type, builtin) || equals(type, builtin->listType()))
            return type;
    }

    return m_varType;
}

QQmlJSRegisterContent QQmlJSTypeResolver::builtinType(const QQmlJSScope::ConstPtr &type) const
{
    Q_ASSERT(storedType(type) == type);
    return QQmlJSRegisterContent::create(
            type, QQmlJSRegisterContent::InvalidLookupIndex, QQmlJSRegisterContent::Builtin);
}

QQmlJSRegisterContent QQmlJSTypeResolver::globalType(const QQmlJSScope::ConstPtr &type) const
{
    return QQmlJSRegisterContent::create(
            type, QQmlJSRegisterContent::InvalidLookupIndex,
            QQmlJSRegisterContent::Unknown);
}

static QQmlJSRegisterContent::ContentVariant scopeContentVariant(QQmlJSScope::ExtensionKind mode,
                                                                 bool isMethod)
{
    switch (mode) {
    case QQmlJSScope::NotExtension:
    case QQmlJSScope::ExtensionType:
    case QQmlJSScope::ExtensionJavaScript:
        return isMethod ? QQmlJSRegisterContent::ScopeMethod : QQmlJSRegisterContent::ScopeProperty;
    case QQmlJSScope::ExtensionNamespace:
        break;
    }
    Q_UNREACHABLE_RETURN(QQmlJSRegisterContent::Unknown);
}

static bool isRevisionAllowed(int memberRevision, const QQmlJSScope::ConstPtr &scope)
{
    Q_ASSERT(scope->isComposite());
    const QTypeRevision revision = QTypeRevision::fromEncodedVersion(memberRevision);

    // If the memberRevision is either invalid or 0.0, then everything is allowed.
    if (!revision.isValid() || revision == QTypeRevision::zero())
        return true;

    const QTypeRevision typeRevision = QQmlJSScope::nonCompositeBaseRevision(
                {scope->baseType(), scope->baseTypeRevision()});

    // If the revision is not valid, we haven't found a non-composite base type.
    // There is nothing we can say about the property then.
    return typeRevision.isValid() && typeRevision >= revision;
}

QQmlJSScope::ConstPtr QQmlJSTypeResolver::resolveParentProperty(
        const QString &name, const QQmlJSScope::ConstPtr &base,
        const QQmlJSScope::ConstPtr &propType) const
{
    if (m_parentMode != UseDocumentParent || name != base->parentPropertyName())
        return propType;

    const QQmlJSScope::ConstPtr baseParent = base->parentScope();
    if (!baseParent || !baseParent->inherits(propType))
        return propType;

    const QString defaultPropertyName = baseParent->defaultPropertyName();
    if (defaultPropertyName.isEmpty()) // no reason to search for bindings
        return propType;

    const QList<QQmlJSMetaPropertyBinding> defaultPropBindings
            = baseParent->propertyBindings(defaultPropertyName);
    for (const QQmlJSMetaPropertyBinding &binding : defaultPropBindings) {
        if (binding.bindingType() == QQmlSA::BindingType::Object
                && equals(binding.objectType(), base)) {
            return baseParent;
        }
    }

    return propType;
}

/*!
 * \internal
 *
 * Retrieves the type of whatever \a name signifies in the given \a scope.
 * \a name can be an ID, a property of the scope, a singleton, an attachment,
 * a plain type reference or a JavaScript global.
 *
 * TODO: The lookup is actually wrong. We cannot really retrieve JavaScript
 *       globals here because any runtime-inserted context property would
 *       override them. We still do because we don't have a better solution for
 *       identifying e.g. the console object, yet.
 *
 * \a options tells us whether to consider components as bound. If components
 * are bound we can retrieve objects identified by ID in outer contexts.
 *
 * TODO: This is also wrong because we should alternate scopes and contexts when
 *       traveling the scope/context hierarchy. Currently we have IDs from any
 *       context override all scope properties if components are considered
 *       bound. This is mostly because we don't care about outer scopes at all;
 *       so we cannot determine with certainty whether an ID from a far outer
 *       context is overridden by a property of a near outer scope. To
 *       complicate this further, user context properties can also be inserted
 *       in outer contexts at run time, shadowing names in further removed outer
 *       scopes and contexts. What we need to do is determine where exactly what
 *       kind of property can show up and defend against that with additional
 *       pragmas.
 *
 * Note: It probably takes at least 3 nested bound components in one document to
 *       trigger the misbehavior.
 */
QQmlJSScope::ConstPtr QQmlJSTypeResolver::scopedType(
        const QQmlJSScope::ConstPtr &scope, const QString &name,
        QQmlJSScopesByIdOptions options) const
{
    if (QQmlJSScope::ConstPtr identified = m_objectsById.scope(name, scope, options))
        return identified;

    if (QQmlJSScope::ConstPtr base = QQmlJSScope::findCurrentQMLScope(scope)) {
        QQmlJSScope::ConstPtr result;
        if (QQmlJSUtils::searchBaseAndExtensionTypes(
                    base, [&](const QQmlJSScope::ConstPtr &found, QQmlJSScope::ExtensionKind mode) {
            if (mode == QQmlJSScope::ExtensionNamespace) // no use for it here
                return false;

            if (found->hasOwnProperty(name)) {
                const QQmlJSMetaProperty prop = found->ownProperty(name);
                if (!isRevisionAllowed(prop.revision(), scope))
                    return false;

                result = resolveParentProperty(name, base, prop.type());
                return true;
            }

            if (found->hasOwnMethod(name)) {
                const auto methods = found->ownMethods(name);
                for (const auto &method : methods) {
                    if (isRevisionAllowed(method.revision(), scope)) {
                        result = jsValueType();
                        return true;
                    }
                }
            }

            return false;
        })) {
            return result;
        }
    }

    if (QQmlJSScope::ConstPtr result = containedTypeForName(name))
        return result;

    if (m_jsGlobalObject->hasProperty(name))
        return m_jsGlobalObject->property(name).type();

    if (m_jsGlobalObject->hasMethod(name))
        return jsValueType();

    return {};
}

/*!
 * \internal
 *
 * Same as the other scopedType method, but accepts a QQmlJSRegisterContent and
 * also returns one. This way you not only get the type, but also the content
 * variant and various meta info.
 */
QQmlJSRegisterContent QQmlJSTypeResolver::scopedType(const QQmlJSRegisterContent &scope,
                                                     const QString &name, int lookupIndex,
                                                     QQmlJSScopesByIdOptions options) const
{
    const QQmlJSScope::ConstPtr contained = scope.containedType();
    if (QQmlJSScope::ConstPtr identified = m_objectsById.scope(name, contained, options)) {
        return QQmlJSRegisterContent::create(
                identified, lookupIndex, QQmlJSRegisterContent::ObjectById, scope);
    }

    if (QQmlJSScope::ConstPtr base = QQmlJSScope::findCurrentQMLScope(contained)) {
        QQmlJSRegisterContent result;
        if (QQmlJSUtils::searchBaseAndExtensionTypes(
                    base, [&](const QQmlJSScope::ConstPtr &found, QQmlJSScope::ExtensionKind mode) {
            if (mode == QQmlJSScope::ExtensionNamespace) // no use for it here
                return false;

            const QQmlJSRegisterContent resultScope = mode == QQmlJSScope::NotExtension
                    ? scope
                    : extensionType(found, scope);

            if (found->hasOwnProperty(name)) {
                QQmlJSMetaProperty prop = found->ownProperty(name);
                if (!isRevisionAllowed(prop.revision(), contained))
                    return false;

                prop.setType(resolveParentProperty(name, base, prop.type()));
                result = QQmlJSRegisterContent::create(
                        prop, QQmlJSRegisterContent::InvalidLookupIndex, lookupIndex,
                        scopeContentVariant(mode, false), resultScope);
                return true;
            }

            if (found->hasOwnMethod(name)) {
                auto methods = found->ownMethods(name);
                for (auto it = methods.begin(); it != methods.end();) {
                    if (!isRevisionAllowed(it->revision(), contained))
                        it = methods.erase(it);
                    else
                        ++it;
                }
                if (methods.isEmpty())
                    return false;
                result = QQmlJSRegisterContent::create(
                        methods, jsValueType(), scopeContentVariant(mode, true), resultScope);
                return true;
            }

            // Unqualified enums are not allowed
            return false;
        })) {
            return result;
        }
    }

    QQmlJSRegisterContent result = registerContentForName(name);

    if (result.isValid())
        return result;

    if (m_jsGlobalObject->hasProperty(name)) {
        return QQmlJSRegisterContent::create(
                m_jsGlobalObject->property(name), QQmlJSRegisterContent::InvalidLookupIndex,
                lookupIndex, QQmlJSRegisterContent::JavaScriptGlobal, m_jsGlobalObjectContent);
    } else if (m_jsGlobalObject->hasMethod(name)) {
        return QQmlJSRegisterContent::create(
                m_jsGlobalObject->methods(name), jsValueType(),
                QQmlJSRegisterContent::JavaScriptGlobal, m_jsGlobalObjectContent);
    }

    return {};
}

/*!
 * \fn QQmlJSScope::ConstPtr typeForId(const QQmlJSScope::ConstPtr &scope, const QString &name, QQmlJSScopesByIdOptions options) const
 *
 * \internal
 *
 * Same as scopedType(), but assumes that the \a name is an ID and only searches
 * the context.
 *
 * TODO: This is just as wrong as scopedType() in that it disregards both scope
 *       properties overriding context properties and run time context
 *       properties.
 */

bool QQmlJSTypeResolver::checkEnums(
        const QQmlJSRegisterContent &scope, const QString &name,
        QQmlJSRegisterContent *result) const
{
    // You can't have lower case enum names in QML, even if we know the enums here.
    if (name.isEmpty() || !name.at(0).isUpper())
        return false;

    const auto enums = scope.containedType()->ownEnumerations();
    for (const auto &enumeration : enums) {
        if ((enumeration.isScoped() || enumeration.isQml()) && enumeration.name() == name) {
            *result = QQmlJSRegisterContent::create(
                    enumeration, QString(),
                    QQmlJSRegisterContent::ObjectEnum,
                    scope);
            return true;
        }

        if ((!enumeration.isScoped() || enumeration.isQml()
             || !scope.containedType()->enforcesScopedEnums()) && enumeration.hasKey(name)) {
            *result = QQmlJSRegisterContent::create(
                    enumeration, name,
                    QQmlJSRegisterContent::ObjectEnum,
                    scope);
            return true;
        }
    }

    return false;
}

bool QQmlJSTypeResolver::canPopulate(
        const QQmlJSScope::ConstPtr &type, const QQmlJSScope::ConstPtr &passedArgumentType,
        bool *isExtension) const
{
    // TODO: We could allow QVariantMap and QVariantHash to be populated, but that needs extra
    //       code in the code generator.

    if (type.isNull()
            || canHold(passedArgumentType, type)
            || isPrimitive(passedArgumentType)
            || type->accessSemantics() != QQmlJSScope::AccessSemantics::Value
            || !type->isStructured()) {
        return false;
    }

    if (isExtension)
        *isExtension = !type->extensionType().scope.isNull();

    return true;
}

QQmlJSMetaMethod QQmlJSTypeResolver::selectConstructor(
        const QQmlJSScope::ConstPtr &type, const QQmlJSScope::ConstPtr &passedArgumentType,
        bool *isExtension) const
{
    // If the "from" type can hold the target type, we should not try to coerce
    // it to any constructor argument.
    if (type.isNull()
            || canHold(passedArgumentType, type)
            || type->accessSemantics() != QQmlJSScope::AccessSemantics::Value
            || !type->isCreatable()) {
        return QQmlJSMetaMethod();
    }

    auto doSelectConstructor = [&](const QQmlJSScope::ConstPtr &type) {
        QQmlJSMetaMethod candidate;

        const auto ownMethods = type->ownMethods();
        for (const QQmlJSMetaMethod &method : ownMethods) {
            if (!method.isConstructor())
                continue;

            const auto index = method.constructorIndex();
            Q_ASSERT(index != QQmlJSMetaMethod::RelativeFunctionIndex::Invalid);

            const auto methodArguments = method.parameters();
            if (methodArguments.size() != 1)
                continue;

            const QQmlJSScope::ConstPtr methodArgumentType = methodArguments[0].type();

            if (equals(passedArgumentType, methodArgumentType))
                return method;

            // Do not select further ctors here. We don't want to do multi-step construction as that
            // is confusing and easily leads to infinite recursion.
            if (!candidate.isValid()
                && canPrimitivelyConvertFromTo(passedArgumentType, methodArgumentType)) {
                candidate = method;
            }
        }

        return candidate;
    };

    if (QQmlJSScope::ConstPtr extension = type->extensionType().scope) {
        const QQmlJSMetaMethod ctor = doSelectConstructor(extension);
        if (ctor.isValid()) {
            if (isExtension)
                *isExtension = true;
            return ctor;
        }
    }

    if (isExtension)
        *isExtension = false;

    return doSelectConstructor(type);
}

bool QQmlJSTypeResolver::areEquivalentLists(
        const QQmlJSScope::ConstPtr &a, const QQmlJSScope::ConstPtr &b) const
{
    const QQmlJSScope::ConstPtr equivalentLists[2][2] = {
        { m_stringListType, m_stringType->listType() },
        { m_variantListType, m_varType->listType() }
    };

    for (const auto eq : equivalentLists) {
        if ((equals(a, eq[0]) && equals(b, eq[1])) || (equals(a, eq[1]) && equals(b, eq[0])))
            return true;
    }

    return false;
}

bool QQmlJSTypeResolver::isTriviallyCopyable(const QQmlJSScope::ConstPtr &type) const
{
    // pointers are trivially copyable
    if (type->isReferenceType())
        return true;

    // Enum values are trivially copyable
    if (type->scopeType() == QQmlSA::ScopeType::EnumScope)
        return true;

    for (const QQmlJSScope::ConstPtr &trivial : {
            m_nullType, m_voidType,
            m_boolType, m_metaObjectType,
            m_realType, m_floatType,
            m_int8Type, m_uint8Type,
            m_int16Type, m_uint16Type,
            m_int32Type, m_uint32Type,
            m_int64Type, m_uint64Type }) {
        if (equals(type, trivial))
            return true;
    }

    return false;
}

bool QQmlJSTypeResolver::inherits(const QQmlJSScope::ConstPtr &derived, const QQmlJSScope::ConstPtr &base) const
{
    const bool matchByName = !base->isComposite();
    for (QQmlJSScope::ConstPtr derivedBase = derived; derivedBase;
            derivedBase = derivedBase->baseType()) {
        if (equals(derivedBase, base))
            return true;
        if (matchByName
                && !derivedBase->isComposite()
                && derivedBase->internalName() == base->internalName()) {
            return true;
        }
    }
    return false;
}

bool QQmlJSTypeResolver::canPrimitivelyConvertFromTo(
        const QQmlJSScope::ConstPtr &from, const QQmlJSScope::ConstPtr &to) const
{
    if (equals(from, to))
        return true;
    if (equals(from, m_varType) || equals(to, m_varType))
        return true;
    if (equals(from, m_jsValueType) || equals(to, m_jsValueType))
        return true;
    if (equals(to, m_qQmlScriptStringType))
        return true;
    if (isNumeric(from) && isNumeric(to))
        return true;
    if (isNumeric(from) && equals(to, m_boolType))
        return true;
    if (from->accessSemantics() == QQmlJSScope::AccessSemantics::Reference
            && (equals(to, m_boolType) || equals(to, m_stringType))) {
        return true;
    }

    // Yes, our String has number constructors.
    if (isNumeric(from) && equals(to, m_stringType))
        return true;

    // We can convert strings to numbers, but not to enums
    if (equals(from, m_stringType) && isNumeric(to))
        return to->scopeType() != QQmlJSScope::ScopeType::EnumScope;

    // We can always convert between strings and urls.
    if ((equals(from, m_stringType) && equals(to, m_urlType))
            || (equals(from, m_urlType) && equals(to, m_stringType))) {
        return true;
    }

    // We can always convert between strings and byte arrays.
    if ((equals(from, m_stringType) && equals(to, m_byteArrayType))
            || (equals(from, m_byteArrayType) && equals(to, m_stringType))) {
        return true;
    }

    if (equals(to, m_voidType))
        return true;

    if (to.isNull())
        return equals(from, m_voidType);

    const auto types = { m_dateTimeType, m_dateType, m_timeType, m_stringType };
    for (const auto &originType : types) {
        if (!equals(from, originType))
            continue;

        for (const auto &targetType : types) {
            if (equals(to, targetType))
                return true;
        }

        if (equals(to, m_realType))
            return true;

        break;
    }

    if (equals(from, m_nullType)
            && to->accessSemantics() == QQmlJSScope::AccessSemantics::Reference) {
        return true;
    }

    if (equals(from, m_jsPrimitiveType)) {
        // You can cast any primitive to a nullptr
        return isPrimitive(to) || to->accessSemantics() == QQmlJSScope::AccessSemantics::Reference;
    }

    if (equals(to, m_jsPrimitiveType))
        return isPrimitive(from);

    if (equals(from, m_variantListType))
        return to->accessSemantics() == QQmlJSScope::AccessSemantics::Sequence;

    const bool matchByName = !to->isComposite();
    Q_ASSERT(!matchByName || !to->internalName().isEmpty());
    for (auto baseType = from; baseType; baseType = baseType->baseType()) {
        if (equals(baseType, to))
            return true;
        if (matchByName && baseType->internalName() == to->internalName())
            return true;
    }

    // We can convert anything that fits into QJSPrimitiveValue
    if (canConvertFromTo(from, m_jsPrimitiveType) && canConvertFromTo(m_jsPrimitiveType, to))
        return true;

    // We can convert everything to bool.
    if (equals(to, m_boolType))
        return true;

    if (areEquivalentLists(from, to))
        return true;

    if (from->isListProperty()
            && to->accessSemantics() == QQmlJSScope::AccessSemantics::Sequence
            && canConvertFromTo(from->valueType(), to->valueType())) {
        return true;
    }

    if (equals(to, m_stringType)
            && from->accessSemantics() == QQmlJSScope::AccessSemantics::Sequence) {
        return canConvertFromTo(from->valueType(), m_stringType);
    }

    return false;
}

QQmlJSRegisterContent QQmlJSTypeResolver::lengthProperty(
        bool isWritable, const QQmlJSRegisterContent &scope) const
{
    QQmlJSMetaProperty prop;
    prop.setPropertyName(u"length"_s);
    prop.setTypeName(u"qsizetype"_s);
    prop.setType(sizeType());
    prop.setIsWritable(isWritable);
    return QQmlJSRegisterContent::create(
            prop, QQmlJSRegisterContent::InvalidLookupIndex,
            QQmlJSRegisterContent::InvalidLookupIndex, QQmlJSRegisterContent::Builtin, scope);
}

QQmlJSRegisterContent QQmlJSTypeResolver::memberType(
        const QQmlJSRegisterContent &type, const QString &name, int baseLookupIndex,
        int resultLookupIndex) const
{
    QQmlJSRegisterContent result;
    const QQmlJSScope::ConstPtr contained = type.containedType();

    // If we got a plain type reference we have to check the enums of the _scope_.
    if (equals(contained, metaObjectType()))
        return {};

    if (equals(contained, variantMapType())) {
        QQmlJSMetaProperty prop;
        prop.setPropertyName(name);
        prop.setTypeName(u"QVariant"_s);
        prop.setType(varType());
        prop.setIsWritable(true);
        return QQmlJSRegisterContent::create(
                prop, baseLookupIndex, resultLookupIndex,
                QQmlJSRegisterContent::GenericObjectProperty, type);
    }

    if (equals(contained, jsValueType())) {
        QQmlJSMetaProperty prop;
        prop.setPropertyName(name);
        prop.setTypeName(u"QJSValue"_s);
        prop.setType(jsValueType());
        prop.setIsWritable(true);
        return QQmlJSRegisterContent::create(
                prop, baseLookupIndex, resultLookupIndex,
                QQmlJSRegisterContent::GenericObjectProperty, type);
    }

    if ((equals(contained, stringType())
            || contained->accessSemantics() == QQmlJSScope::AccessSemantics::Sequence)
            && name == u"length"_s) {
        return lengthProperty(!equals(contained, stringType()), type);
    }

    const auto check = [&](const QQmlJSScope::ConstPtr &scope, QQmlJSScope::ExtensionKind mode) {
        const QQmlJSRegisterContent resultScope = mode == QQmlJSScope::NotExtension
                ? syntheticType(scope)
                : extensionType(scope, type);

        if (mode != QQmlJSScope::ExtensionNamespace) {
            if (scope->hasOwnProperty(name)) {
                const auto prop = scope->ownProperty(name);
                result = QQmlJSRegisterContent::create(
                        prop, baseLookupIndex, resultLookupIndex,
                        QQmlJSRegisterContent::ObjectProperty,
                        resultScope);
                return true;
            }

            if (scope->hasOwnMethod(name)) {
                const auto methods = scope->ownMethods(name);
                result = QQmlJSRegisterContent::create(
                        methods, jsValueType(),
                        QQmlJSRegisterContent::ObjectMethod,
                        resultScope);
                return true;
            }
        }

        return checkEnums(resultScope, name, &result);
    };

    if (QQmlJSUtils::searchBaseAndExtensionTypes(type.containedType(), check))
        return result;

    for (auto scope = contained;
         scope && (scope->scopeType() == QQmlSA::ScopeType::JSFunctionScope
                   || scope->scopeType() == QQmlSA::ScopeType::JSLexicalScope);
         scope = scope->parentScope()) {
        if (auto ownIdentifier = scope->ownJSIdentifier(name)) {
            QQmlJSMetaProperty prop;
            prop.setPropertyName(name);
            prop.setTypeName(u"QJSValue"_s);
            prop.setType(jsValueType());
            prop.setIsWritable(!(ownIdentifier.value().isConst));

            return QQmlJSRegisterContent::create(
                    prop, baseLookupIndex, resultLookupIndex,
                    QQmlJSRegisterContent::JavaScriptObject, syntheticType(scope));
        }
    }

    if (QQmlJSScope::ConstPtr attachedBase = typeForName(name)) {
        if (QQmlJSScope::ConstPtr attached = attachedBase->attachedType()) {
            if (!genericType(attached)) {
                m_logger->log(u"Cannot resolve generic base of attached %1"_s.arg(
                                      attached->internalName()),
                              qmlCompiler, attached->sourceLocation());
                return {};
            } else if (contained->accessSemantics() != QQmlJSScope::AccessSemantics::Reference) {
                m_logger->log(u"Cannot retrieve attached object for non-reference type %1"_s.arg(
                                      contained->internalName()),
                              qmlCompiler, contained->sourceLocation());
                return {};
            } else {
                const QQmlJSRegisterContent namedType = QQmlJSRegisterContent::create(
                        attachedBase, QQmlJSRegisterContent::InvalidLookupIndex,
                        QQmlJSRegisterContent::TypeByName, type);

                return QQmlJSRegisterContent::create(
                        attached, resultLookupIndex, QQmlJSRegisterContent::ObjectAttached,
                        namedType);
            }
        }
    }

    return {};
}

QQmlJSRegisterContent QQmlJSTypeResolver::memberEnumType(
        const QQmlJSRegisterContent &type, const QString &name) const
{
    QQmlJSRegisterContent result;

    if (QQmlJSUtils::searchBaseAndExtensionTypes(
                type.containedType(),
                [&](const QQmlJSScope::ConstPtr &scope, QQmlJSScope::ExtensionKind mode) {
                    return checkEnums(mode == QQmlJSScope::NotExtension
                                              ? syntheticType(scope)
                                              : extensionType(scope, type),
                                      name, &result);
                })) {
        return result;
    }

    return {};
}

QQmlJSRegisterContent QQmlJSTypeResolver::memberType(
        const QQmlJSRegisterContent &type, const QString &name, int lookupIndex) const
{
    if (type.isType()) {
        const auto content = type.type();
        const auto result = memberType(type, name, type.resultLookupIndex(), lookupIndex);
        if (result.isValid())
            return result;

        // If we didn't find anything and it's an attached type,
        // we might have an enum of the attaching type.
        return memberEnumType(type.scopeType(), name);
    }
    if (type.isProperty())
        return memberType(type, name, type.resultLookupIndex(), lookupIndex);
    if (type.isEnumeration()) {
        const auto enumeration = type.enumeration();
        if (!type.enumMember().isEmpty() || !enumeration.hasKey(name))
            return {};
        return QQmlJSRegisterContent::create(
                enumeration, name, QQmlJSRegisterContent::ObjectEnum,
                type.scopeType());
    }
    if (type.isMethod()) {
        QQmlJSMetaProperty prop;
        prop.setTypeName(u"QJSValue"_s);
        prop.setPropertyName(name);
        prop.setType(jsValueType());
        prop.setIsWritable(true);
        return QQmlJSRegisterContent::create(
                prop, QQmlJSRegisterContent::InvalidLookupIndex, lookupIndex,
                QQmlJSRegisterContent::GenericObjectProperty, type);
    }
    if (type.isImportNamespace()) {
        if (type.scopeType().containedType()->accessSemantics()
                != QQmlJSScope::AccessSemantics::Reference) {
            m_logger->log(u"Cannot use a non-QObject type %1 to access prefixed import"_s.arg(
                                  type.scopeType().containedType()->internalName()),
                          qmlPrefixedImportType,
                          type.scopeType().containedType()->sourceLocation());
            return {};
        }

        return registerContentForName(
                    name, type.scopeType(),
                    type.variant() == QQmlJSRegisterContent::ObjectModulePrefix);
    }
    if (type.isConversion()) {
        if (const auto result = memberType(
                    type, name, type.resultLookupIndex(), lookupIndex);
            result.isValid()) {
            return result;
        }

        if (const auto result = memberEnumType(type.scopeType(), name); result.isValid())
            return result;

        // If the conversion consists of only undefined and one actual type,
        // we can produce the members of that one type.
        // If the value is then actually undefined, the result is an exception.

        auto origins = type.conversionOrigins();
        const auto begin = origins.begin();
        const auto end = std::remove_if(begin, origins.end(),
                       [this](const QQmlJSScope::ConstPtr &origin) {
            return equals(origin, m_voidType);
        });

        // If the conversion cannot hold the original type, it loses information.
        return (end - begin == 1 && canHold(type.conversionResult(), *begin))
                ? memberType(syntheticType(*begin), name, type.resultLookupIndex(), lookupIndex)
                : QQmlJSRegisterContent();
    }

    Q_UNREACHABLE_RETURN({});
}

QQmlJSRegisterContent QQmlJSTypeResolver::valueType(const QQmlJSRegisterContent &list) const
{
    QQmlJSScope::ConstPtr value;

    auto valueType = [&](const QQmlJSScope::ConstPtr &scope) {
        if (scope->accessSemantics() == QQmlJSScope::AccessSemantics::Sequence)
            return scope->valueType();

        if (equals(scope, m_forInIteratorPtr))
            return m_sizeType;

        if (equals(scope, m_forOfIteratorPtr))
            return list.scopeType().containedType()->valueType();

        if (equals(scope, m_jsValueType) || equals(scope, m_varType))
            return m_jsValueType;

        if (equals(scope, m_stringType))
            return m_stringType;

        return QQmlJSScope::ConstPtr();
    };

    if (list.isType())
        value = valueType(list.type());
    else if (list.isConversion())
        value = valueType(list.conversionResult());
    else if (list.isProperty())
        value = valueType(list.property().type());

    if (value.isNull())
        return {};

    QQmlJSMetaProperty property;
    property.setPropertyName(u"[]"_s);
    property.setTypeName(value->internalName());
    property.setType(value);

    return QQmlJSRegisterContent::create(
            property, QQmlJSRegisterContent::InvalidLookupIndex,
            QQmlJSRegisterContent::InvalidLookupIndex, QQmlJSRegisterContent::ListValue,
            list);
}

QQmlJSRegisterContent QQmlJSTypeResolver::returnType(
        const QQmlJSScope::ConstPtr &type, QQmlJSRegisterContent::ContentVariant variant,
        const QQmlJSRegisterContent &scope) const
{
    Q_ASSERT(variant == QQmlJSRegisterContent::MethodReturnValue
             || variant == QQmlJSRegisterContent::JavaScriptReturnValue);
    return QQmlJSRegisterContent::create(
            type, QQmlJSRegisterContent::InvalidLookupIndex, variant, scope);
}

QQmlJSRegisterContent QQmlJSTypeResolver::extensionType(
        const QQmlJSScope::ConstPtr &extension, const QQmlJSRegisterContent &base) const
{
    return QQmlJSRegisterContent::create(
            extension, base.resultLookupIndex(), QQmlJSRegisterContent::Extension, base);
}

QQmlJSRegisterContent QQmlJSTypeResolver::iteratorPointer(
        const QQmlJSRegisterContent &listType, QQmlJS::AST::ForEachType type,
        int lookupIndex) const
{
    const QQmlJSScope::ConstPtr value = (type == QQmlJS::AST::ForEachType::In)
            ? m_int32Type
            : valueType(listType).containedType();

    QQmlJSScope::ConstPtr iteratorPointer = type == QQmlJS::AST::ForEachType::In
            ? m_forInIteratorPtr
            : m_forOfIteratorPtr;

    QQmlJSMetaProperty prop;
    prop.setPropertyName(u"<>"_s);
    prop.setTypeName(iteratorPointer->internalName());
    prop.setType(iteratorPointer);
    return QQmlJSRegisterContent::create(
            prop, lookupIndex,
            QQmlJSRegisterContent::InvalidLookupIndex, QQmlJSRegisterContent::ListIterator,
            listType);
}

bool QQmlJSTypeResolver::registerContains(const QQmlJSRegisterContent &reg,
                                          const QQmlJSScope::ConstPtr &type) const
{
    if (reg.isType())
        return equals(reg.type(), type);
    if (reg.isConversion())
        return equals(reg.conversionResult(), type);
    if (reg.isProperty())
        return equals(type, reg.property().type());
    if (reg.isEnumeration())
        return equals(type, reg.enumeration().type());
    if (reg.isMethod())
        return equals(type, jsValueType());
    return false;
}

QQmlJSScope::ConstPtr QQmlJSTypeResolver::storedType(const QQmlJSScope::ConstPtr &type) const
{
    if (type.isNull())
        return {};
    if (equals(type, voidType()))
        return type;
    if (type->isScript())
        return jsValueType();
    if (type->isComposite()) {
        if (const QQmlJSScope::ConstPtr nonComposite = QQmlJSScope::nonCompositeBaseType(type))
            return nonComposite;

        // If we can't find the non-composite base, we really don't know what it is.
        return genericType(type);
    }
    if (type->filePath().isEmpty())
        return genericType(type);
    return type;
}

QQmlJSScope::ConstPtr QQmlJSTypeResolver::originalType(const QQmlJSScope::ConstPtr &type) const
{
    const auto it = m_trackedTypes->find(type);
    return it == m_trackedTypes->end() ? type : it->original;
}

/*!
 * \internal
 *
 * Compares the origin types of \a a and \a b. A straight a == b would compare the identity
 * of the pointers. However, since we clone types to keep track of them, we need a separate
 * way to compare the clones. Usually you'd do *a == *b for that, but as QQmlJSScope is rather
 * large, we offer an optimization here that uses the type tracking we already have in place.
 */
bool QQmlJSTypeResolver::equals(const QQmlJSScope::ConstPtr &a, const QQmlJSScope::ConstPtr &b) const
{
    return comparableType(a) == comparableType(b);
}

QQmlJSRegisterContent QQmlJSTypeResolver::convert(
        const QQmlJSRegisterContent &from, const QQmlJSRegisterContent &to) const
{
    if (from.isConversion()) {
        return QQmlJSRegisterContent::create(
                syntheticTypes(from.conversionOrigins()), to.containedType(),
                to.scopeType().isValid()
                        ? to.scopeType()
                        : from.conversionResultScope(),
                from.variant(), from.scopeType());
    }

    return QQmlJSRegisterContent::create(
            QList<QQmlJSRegisterContent>{from},
            to.containedType(), to.scopeType(), from.variant(),
            from.scopeType());
}

QQmlJSRegisterContent QQmlJSTypeResolver::cast(
        const QQmlJSRegisterContent &from, const QQmlJSScope::ConstPtr &to) const
{
    return from.castTo(to);
}

QQmlJSScope::ConstPtr QQmlJSTypeResolver::comparableType(const QQmlJSScope::ConstPtr &type) const
{
    const auto it = m_trackedTypes->constFind(type);
    if (it == m_trackedTypes->constEnd())
        return type;
    return it->replacement ? it->replacement : it->original;
}

QT_END_NAMESPACE
