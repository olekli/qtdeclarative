/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtQuick module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QQUICKOPENGLSHADEREFFECT_P_H
#define QQUICKOPENGLSHADEREFFECT_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtQuick/qquickitem.h>

#include <QtQuick/qsgmaterial.h>
#include <private/qtquickglobal_p.h>
#include <private/qsgadaptationlayer_p.h>
#include <private/qquickopenglshadereffectnode_p.h>
#include "qquickshadereffect_p.h"
#include "qquickshadereffectmesh_p.h"

#include <QtCore/qpointer.h>

QT_BEGIN_NAMESPACE

class QSGContext;
class QSignalMapper;
class QQuickOpenGLCustomMaterialShader;

// Common class for QQuickOpenGLShaderEffect and QQuickCustomParticle.
struct Q_QUICK_PRIVATE_EXPORT QQuickOpenGLShaderEffectCommon
{
    typedef QQuickOpenGLShaderEffectMaterialKey Key;
    typedef QQuickOpenGLShaderEffectMaterial::UniformData UniformData;

    ~QQuickOpenGLShaderEffectCommon();
    void disconnectPropertySignals(QQuickItem *item, Key::ShaderType shaderType);
    void connectPropertySignals(QQuickItem *item, Key::ShaderType shaderType);
    void updateParseLog(bool ignoreAttributes);
    void lookThroughShaderCode(QQuickItem *item, Key::ShaderType shaderType, const QByteArray &code);
    void updateShader(QQuickItem *item, Key::ShaderType shaderType);
    void updateMaterial(QQuickOpenGLShaderEffectNode *node, QQuickOpenGLShaderEffectMaterial *material,
                        bool updateUniforms, bool updateUniformValues, bool updateTextureProviders);
    void updateWindow(QQuickWindow *window);

    // Called by slots in QQuickOpenGLShaderEffect:
    void sourceDestroyed(QObject *object);
    void propertyChanged(QQuickItem *item, int mappedId, bool *textureProviderChanged);

    Key source;
    QVector<QByteArray> attributes;
    QVector<UniformData> uniformData[Key::ShaderTypeCount];
    QVector<QSignalMapper *> signalMappers[Key::ShaderTypeCount];
    QString parseLog;
};


class Q_QUICK_PRIVATE_EXPORT QQuickOpenGLShaderEffect : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QByteArray fragmentShader READ fragmentShader WRITE setFragmentShader NOTIFY fragmentShaderChanged)
    Q_PROPERTY(QByteArray vertexShader READ vertexShader WRITE setVertexShader NOTIFY vertexShaderChanged)
    Q_PROPERTY(bool blending READ blending WRITE setBlending NOTIFY blendingChanged)
    Q_PROPERTY(QVariant mesh READ mesh WRITE setMesh NOTIFY meshChanged)
    Q_PROPERTY(CullMode cullMode READ cullMode WRITE setCullMode NOTIFY cullModeChanged)
    Q_PROPERTY(QString log READ log NOTIFY logChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(bool supportsAtlasTextures READ supportsAtlasTextures WRITE setSupportsAtlasTextures NOTIFY supportsAtlasTexturesChanged REVISION 1)

public:
    enum CullMode
    {
        NoCulling = QQuickShaderEffect::NoCulling,
        BackFaceCulling = QQuickShaderEffect::BackFaceCulling,
        FrontFaceCulling = QQuickShaderEffect::FrontFaceCulling
    };
    Q_ENUM(CullMode)

    enum Status
    {
        Compiled,
        Uncompiled,
        Error
    };
    Q_ENUM(Status)

    QQuickOpenGLShaderEffect(QQuickItem *parent = 0);
    ~QQuickOpenGLShaderEffect();

    QByteArray fragmentShader() const { return m_common.source.sourceCode[Key::FragmentShader]; }
    void setFragmentShader(const QByteArray &code);

    QByteArray vertexShader() const { return m_common.source.sourceCode[Key::VertexShader]; }
    void setVertexShader(const QByteArray &code);

    bool blending() const { return m_blending; }
    void setBlending(bool enable);

    QVariant mesh() const;
    void setMesh(const QVariant &mesh);

    CullMode cullMode() const { return m_cullMode; }
    void setCullMode(CullMode face);

    QString log() const { return m_log; }
    Status status() const { return m_status; }

    bool supportsAtlasTextures() const { return m_supportsAtlasTextures; }
    void setSupportsAtlasTextures(bool supports);

    QString parseLog();

    bool event(QEvent *) Q_DECL_OVERRIDE;

Q_SIGNALS:
    void fragmentShaderChanged();
    void vertexShaderChanged();
    void blendingChanged();
    void meshChanged();
    void cullModeChanged();
    void logChanged();
    void statusChanged();
    void supportsAtlasTexturesChanged();

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) Q_DECL_OVERRIDE;
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) Q_DECL_OVERRIDE;
    void componentComplete() Q_DECL_OVERRIDE;
    void itemChange(ItemChange change, const ItemChangeData &value) Q_DECL_OVERRIDE;

private Q_SLOTS:
    void updateGeometry();
    void updateGeometryIfAtlased();
    void updateLogAndStatus(const QString &log, int status);
    void sourceDestroyed(QObject *object);
    void propertyChanged(int mappedId);

private:
    friend class QQuickCustomMaterialShader;
    friend class QQuickOpenGLShaderEffectNode;

    typedef QQuickOpenGLShaderEffectMaterialKey Key;
    typedef QQuickOpenGLShaderEffectMaterial::UniformData UniformData;

    QSize m_meshResolution;
    QQuickShaderEffectMesh *m_mesh;
    QQuickGridMesh m_defaultMesh;
    CullMode m_cullMode;
    QString m_log;
    Status m_status;

    QQuickOpenGLShaderEffectCommon m_common;

    uint m_blending : 1;
    uint m_dirtyUniforms : 1;
    uint m_dirtyUniformValues : 1;
    uint m_dirtyTextureProviders : 1;
    uint m_dirtyProgram : 1;
    uint m_dirtyParseLog : 1;
    uint m_dirtyMesh : 1;
    uint m_dirtyGeometry : 1;
    uint m_customVertexShader : 1;
    uint m_supportsAtlasTextures : 1;
};

QT_END_NAMESPACE

#endif // QQUICKOPENGLSHADEREFFECT_P_H
