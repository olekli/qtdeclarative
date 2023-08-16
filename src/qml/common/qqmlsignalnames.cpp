// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "qqmlsignalnames_p.h"
#include <iterator>
#include <algorithm>
#include <optional>
#include <string>

QT_BEGIN_NAMESPACE

using namespace Qt::Literals;

static std::optional<qsizetype> firstLetterIdx(QStringView name, qsizetype removePrefix = 0,
                                               qsizetype removeSuffix = 0)
{
    auto end = std::prev(name.cend(), removeSuffix);
    auto result = std::find_if(std::next(name.cbegin(), removePrefix), end,
                               [](const QChar &c) { return c.isLetter(); });
    if (result != end)
        return std::distance(name.begin(), result);

    return {};
}

static std::optional<QChar> firstLetter(QStringView name, qsizetype removePrefix = 0,
                                        qsizetype removeSuffix = 0)
{
    if (auto idx = firstLetterIdx(name, removePrefix, removeSuffix))
        return name[*idx];
    return {};
}

enum ChangeCase { ToUpper, ToLower };
static void changeCaseOfFirstLetter(QString &name, ChangeCase option, qsizetype removePrefix = 0,
                                    qsizetype removeSuffix = 0)
{
    auto idx = firstLetterIdx(name, removePrefix, removeSuffix);
    if (!idx)
        return;

    QChar &changeMe = name[*idx];
    changeMe = option == ToUpper ? changeMe.toUpper() : changeMe.toLower();
};

static std::optional<QString> toQStringData(std::optional<QStringView> view)
{
    if (view)
        return view->toString();
    return std::nullopt;
}

static QByteArray toUtf8Data(QUtf8StringView view)
{
    return QByteArray(view.data(), view.size());
}

static std::optional<QByteArray> toUtf8Data(std::optional<QUtf8StringView> view)
{
    if (view)
        return toUtf8Data(*view);
    return std::nullopt;
}

/*!
\internal
\class QQmlSignalNames

QQmlSignalNames contains a list of helper methods to manipulate signal names.
Always try to use the most specific one, as combining them might lead to incorrect
results like wrong upper/lower case, for example.
*/

/*!
\internal
Concatenate a prefix to a property name and uppercases the first letter of the property name.
*/
QString QQmlSignalNames::addPrefixToPropertyName(QStringView prefix, QStringView propertyName)
{
    QString result = prefix.toString().append(propertyName);
    changeCaseOfFirstLetter(result, ToUpper, prefix.size());
    return result;
}

QString QQmlSignalNames::propertyNameToChangedSignalName(QStringView property)
{
    return property.toString().append(u"Changed"_s);
}

QByteArray QQmlSignalNames::propertyNameToChangedSignalName(QUtf8StringView property)
{
    return toUtf8Data(property).append("Changed"_ba);
}

QString QQmlSignalNames::propertyNameToChangedHandlerName(QStringView property)
{
    return propertyNameToChangedSignalName(signalNameToHandlerName(property));
}

template<typename View>
std::optional<View> changedSignalNameToPropertyNameTemplate(View changeSignal)
{
    constexpr qsizetype changedLen =
            static_cast<qsizetype>(std::char_traits<char>::length("Changed"));
    if (changeSignal.size() < changedLen
        || changeSignal.last(changedLen).compare("Changed"_L1) != 0)
        return std::nullopt;

    const View result = changeSignal.sliced(0, changeSignal.length() - changedLen);
    if (!result.isEmpty())
        return result;

    return {};
}

/*!
\internal
Obtain a propertyName from its changed signal handler.
Do not call this on a value obtained from handlerNameToSignalName! Instead use
changedHandlerNameToPropertyName() directly. Otherwise you might end up with a wrong
capitalization of _Changed for "on_Changed", for example.
*/

std::optional<QString> QQmlSignalNames::changedSignalNameToPropertyName(QStringView signalName)
{
    return toQStringData(changedSignalNameToPropertyNameTemplate(signalName));
}
std::optional<QByteArray>
QQmlSignalNames::changedSignalNameToPropertyName(QUtf8StringView signalName)
{
    return toUtf8Data(changedSignalNameToPropertyNameTemplate(signalName));
}

/*!
\internal
Returns a property name from \a changedHandler.
This fails for property names starting with an upper-case letter, as it will lower-case it in the
process.
*/
std::optional<QString> QQmlSignalNames::changedHandlerNameToPropertyName(QStringView handler)
{
    if (!isChangedHandlerName(handler))
        return {};

    if (auto withoutChangedSuffix = changedSignalNameToPropertyName(handler)) {
        return handlerNameToSignalName(*withoutChangedSuffix);
    }
    return {};
}

QString QQmlSignalNames::signalNameToHandlerName(QAnyStringView signal)
{
    QString handlerName;
    signal.visit([&handlerName](auto &&s) { handlerName = u"on"_s.append(s); });

    changeCaseOfFirstLetter(handlerName, ToUpper, strlen("on"));
    return handlerName;
}

enum HandlerType { ChangedHandler, Handler };

static std::optional<QString> handlerNameToSignalNameHelper(QStringView handler, HandlerType type)
{
    if (!QQmlSignalNames::isHandlerName(handler))
        return {};

    QString signalName = handler.sliced(strlen("on")).toString();
    if (signalName.isEmpty())
        return {};

    changeCaseOfFirstLetter(signalName, ToLower, 0, type == ChangedHandler ? strlen("Changed") : 0);
    return signalName;
}

/*!
\internal
Returns a signal name from \a handlerName string. Do not use it on changed handlers, see
changedHandlerNameToSignalName for that!
*/
std::optional<QString> QQmlSignalNames::handlerNameToSignalName(QStringView handler)
{
    return handlerNameToSignalNameHelper(handler, Handler);
}

/*!
\internal
Returns a signal name from \a changedHandlerName string. Makes sure not to lowercase the 'C' from
Changed.
*/
std::optional<QString> QQmlSignalNames::changedHandlerNameToSignalName(QStringView handler)
{
    return handlerNameToSignalNameHelper(handler, ChangedHandler);
}

bool QQmlSignalNames::isChangedSignalName(QStringView signalName)
{
    const qsizetype smallestAllowedSize = strlen("XChanged");
    if (signalName.size() < smallestAllowedSize || !signalName.endsWith(u"Changed"_s))
        return false;

    if (auto letter = firstLetter(signalName, 0, strlen("Changed")))
        return letter->isLower();

    return true;
}

bool QQmlSignalNames::isChangedHandlerName(QStringView signalName)
{
    const qsizetype smallestAllowedSize = strlen("onXChanged");
    if (signalName.size() < smallestAllowedSize || !signalName.startsWith(u"on"_s)
        || !signalName.endsWith(u"Changed"_s))
        return false;

    if (auto letter = firstLetter(signalName, strlen("on"), strlen("Changed")))
        return letter->isUpper();

    return true;
}

bool QQmlSignalNames::isHandlerName(QStringView signalName)
{
    const qsizetype smallestAllowedSize = strlen("onX");
    if (signalName.size() < smallestAllowedSize || !signalName.startsWith(u"on"_s))
        return false;

    if (auto letter = firstLetter(signalName, strlen("on")))
        return letter->isUpper();

    return true;
}

QT_END_NAMESPACE
