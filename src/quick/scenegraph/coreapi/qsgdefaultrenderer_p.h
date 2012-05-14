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

#ifndef QMLRENDERER_H
#define QMLRENDERER_H

#include "qsgrenderer_p.h"

#include <QtGui/private/qdatabuffer_p.h>
#include "qsgrendernode_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class Q_QUICK_PRIVATE_EXPORT QSGDefaultRenderer : public QSGRenderer
{
    Q_OBJECT
public:
    class IndexNodePair : public QPair<int, QSGNode *>
    {
    public:
        IndexNodePair(int i, QSGNode *n);
        bool operator < (const IndexNodePair &other) const;
    };


    // Minimum heap.
    class IndexNodePairHeap
    {
    public:
        IndexNodePairHeap();
        void insert(const IndexNodePair &x);
        const IndexNodePair &top() const { return v.first(); }
        IndexNodePair pop();
        bool isEmpty() const { return v.isEmpty(); }
    private:
        static int parent(int i) { return (i - 1) >> 1; }
        static int left(int i) { return (i << 1) | 1; }
        static int right(int i) { return (i + 1) << 1; }
        QDataBuffer<IndexNodePair> v;
    };

    QSGDefaultRenderer(QSGContext *context);

    void render();

    void nodeChanged(QSGNode *node, QSGNode::DirtyState state);

    void setSortFrontToBackEnabled(bool sort);
    bool isSortFrontToBackEnabled() const;

private:
    void buildLists(QSGNode *node);
    void renderNodes(QSGNode *const *nodes, int count);

    const QSGClipNode *m_currentClip;
    QSGMaterial *m_currentMaterial;
    QSGMaterialShader *m_currentProgram;
    const QMatrix4x4 *m_currentMatrix;
    QMatrix4x4 m_renderOrderMatrix;
    QDataBuffer<QSGNode *> m_opaqueNodes;
    QDataBuffer<QSGNode *> m_transparentNodes;
    QDataBuffer<QSGNode *> m_tempNodes;
    struct RenderGroup { int opaqueEnd, transparentEnd; };
    QDataBuffer<RenderGroup> m_renderGroups;
    IndexNodePairHeap m_heap;

    bool m_rebuild_lists;
    bool m_needs_sorting;
    bool m_sort_front_to_back;
    bool m_render_node_added;
    int m_currentRenderOrder;

#ifdef QML_RUNTIME_TESTING
    bool m_render_opaque_nodes;
    bool m_render_alpha_nodes;
#endif
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // QMLRENDERER_H
