// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#ifndef QQMLJSSTORAGEINITIALIZER_P_H
#define QQMLJSSTORAGEINITIALIZER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#include <private/qqmljscompilepass_p.h>

QT_BEGIN_NAMESPACE

class Q_QMLCOMPILER_EXPORT QQmlJSStorageInitializer : public QQmlJSCompilePass
{
public:
    QQmlJSStorageInitializer(const QV4::Compiler::JSUnitGenerator *jsUnitGenerator,
                             const QQmlJSTypeResolver *typeResolver, QQmlJSLogger *logger,
                             QList<QQmlJS::DiagnosticMessage> *errors,
                             const BasicBlocks &basicBlocks,
                             const InstructionAnnotations &annotations)
        : QQmlJSCompilePass(jsUnitGenerator, typeResolver, logger, errors, basicBlocks, annotations)
    {}

    BlocksAndAnnotations run(Function *function);

protected:
    // We don't have to use the byte code here. We only transform the instruction annotations.
    Verdict startInstruction(QV4::Moth::Instr::Type) override { return SkipInstruction; }
    void endInstruction(QV4::Moth::Instr::Type) override {}
};

QT_END_NAMESPACE

#endif // QQMLJSSTORAGEINITIALIZER_P_H
