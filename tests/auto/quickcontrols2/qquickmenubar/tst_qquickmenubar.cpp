/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtTest>
#include <QtQml>
#include <QtQuickTestUtils/private/qmlutils_p.h>
#include <QtQuickTestUtils/private/visualtestutils_p.h>
#include <QtQuickTemplates2/private/qquickapplicationwindow_p.h>
#include <QtQuickTemplates2/private/qquickbutton_p.h>
#include <QtQuickTemplates2/private/qquickmenu_p.h>
#include <QtQuickTemplates2/private/qquickmenubar_p.h>
#include <QtQuickTemplates2/private/qquickmenubaritem_p.h>
#include <QtQuickTemplates2/private/qquickmenuitem_p.h>
#include <QtQuickControlsTestUtils/private/qtest_quickcontrols_p.h>

using namespace QQuickVisualTestUtils;

class tst_qquickmenubar : public QQmlDataTest
{
    Q_OBJECT

public:
    tst_qquickmenubar();

private slots:
    void delegate();
    void mouse();
    void keys();
    void mnemonics();
    void addRemove();
    void checkHighlightWhenMenuDismissed();
};

tst_qquickmenubar::tst_qquickmenubar()
    : QQmlDataTest(QT_QMLTEST_DATADIR)
{
}

void tst_qquickmenubar::delegate()
{
    QQmlApplicationEngine engine(testFileUrl("empty.qml"));
    QScopedPointer<QQuickMenuBar> menuBar(qobject_cast<QQuickMenuBar *>(engine.rootObjects().value(0)));
    QVERIFY(menuBar);

    QQmlComponent *delegate = menuBar->delegate();
    QVERIFY(delegate);

    QScopedPointer<QQuickMenuBarItem> item(qobject_cast<QQuickMenuBarItem *>(delegate->create()));
    QVERIFY(item);
}

void tst_qquickmenubar::mouse()
{
    if ((QGuiApplication::platformName() == QLatin1String("offscreen"))
        || (QGuiApplication::platformName() == QLatin1String("minimal")))
        QSKIP("Mouse highlight not functional on offscreen/minimal platforms");

    QQmlApplicationEngine engine(testFileUrl("menubar.qml"));

    QScopedPointer<QQuickApplicationWindow> window(qobject_cast<QQuickApplicationWindow *>(engine.rootObjects().value(0)));
    QVERIFY(window);

    centerOnScreen(window.data());
    moveMouseAway(window.data());
    QVERIFY(QTest::qWaitForWindowActive(window.data()));

    QQuickMenuBar *menuBar = window->property("header").value<QQuickMenuBar *>();
    QVERIFY(menuBar);

    QQuickMenu *fileMenuBarMenu = menuBar->menuAt(0);
    QQuickMenu *editMenuBarMenu = menuBar->menuAt(1);
    QQuickMenu *viewMenuBarMenu = menuBar->menuAt(2);
    QQuickMenu *helpMenuBarMenu = menuBar->menuAt(3);
    QVERIFY(fileMenuBarMenu && editMenuBarMenu && viewMenuBarMenu && helpMenuBarMenu);

    QQuickMenuBarItem *fileMenuBarItem = qobject_cast<QQuickMenuBarItem *>(fileMenuBarMenu->parentItem());
    QQuickMenuBarItem *editMenuBarItem = qobject_cast<QQuickMenuBarItem *>(editMenuBarMenu->parentItem());
    QQuickMenuBarItem *viewMenuBarItem = qobject_cast<QQuickMenuBarItem *>(viewMenuBarMenu->parentItem());
    QQuickMenuBarItem *helpMenuBarItem = qobject_cast<QQuickMenuBarItem *>(helpMenuBarMenu->parentItem());
    QVERIFY(fileMenuBarItem && editMenuBarItem && viewMenuBarItem && helpMenuBarItem);

    // highlight a menubar item
    QTest::mouseMove(window.data(), fileMenuBarItem->mapToScene(QPointF(fileMenuBarItem->width() / 2, fileMenuBarItem->height() / 2)).toPoint());
    QVERIFY(fileMenuBarItem->isHighlighted());
    QVERIFY(!fileMenuBarMenu->isVisible());

    // highlight another menubar item
    QTest::mouseMove(window.data(), editMenuBarItem->mapToScene(QPointF(editMenuBarItem->width() / 2, editMenuBarItem->height() / 2)).toPoint());
    QVERIFY(!fileMenuBarItem->isHighlighted());
    QVERIFY(editMenuBarItem->isHighlighted());
    QVERIFY(!fileMenuBarMenu->isVisible());
    QVERIFY(!editMenuBarMenu->isVisible());

    // trigger a menubar item to open a menu
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier, editMenuBarItem->mapToScene(QPointF(editMenuBarItem->width() / 2, editMenuBarItem->height() / 2)).toPoint());
    QVERIFY(editMenuBarItem->isHighlighted());
    QVERIFY(editMenuBarMenu->isVisible());
    QTRY_VERIFY(editMenuBarMenu->isOpened());

    // re-trigger a menubar item to hide the menu
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier, editMenuBarItem->mapToScene(QPointF(editMenuBarItem->width() / 2, editMenuBarItem->height() / 2)).toPoint());
    QVERIFY(editMenuBarItem->isHighlighted());
    QVERIFY(editMenuBarItem->hasActiveFocus());
    QTRY_VERIFY(!editMenuBarMenu->isVisible());

    // re-trigger a menubar item to show the menu again
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier, editMenuBarItem->mapToScene(QPointF(editMenuBarItem->width() / 2, editMenuBarItem->height() / 2)).toPoint());
    QVERIFY(editMenuBarItem->isHighlighted());
    QVERIFY(editMenuBarMenu->isVisible());
    QTRY_VERIFY(editMenuBarMenu->isOpened());

    // highlight another menubar item to open another menu
    QTest::mouseMove(window.data(), helpMenuBarItem->mapToScene(QPointF(helpMenuBarItem->width() / 2, helpMenuBarItem->height() / 2)).toPoint());
    QVERIFY(!fileMenuBarItem->isHighlighted());
    QVERIFY(!editMenuBarItem->isHighlighted());
    QVERIFY(!viewMenuBarItem->isHighlighted());
    QVERIFY(helpMenuBarItem->isHighlighted());
    QVERIFY(!fileMenuBarMenu->isVisible());
    QVERIFY(!viewMenuBarMenu->isVisible());
    QVERIFY(helpMenuBarMenu->isVisible());
    QTRY_VERIFY(!editMenuBarMenu->isVisible());
    QTRY_VERIFY(helpMenuBarMenu->isOpened());

    // trigger a menu item to close the menu
    QQuickMenuItem *aboutMenuItem = qobject_cast<QQuickMenuItem *>(helpMenuBarMenu->itemAt(0));
    QVERIFY(aboutMenuItem);
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier, aboutMenuItem->mapToScene(QPointF(aboutMenuItem->width() / 2, aboutMenuItem->height() / 2)).toPoint());
    QVERIFY(!helpMenuBarItem->isHighlighted());
    QTRY_VERIFY(!helpMenuBarMenu->isVisible());

    // highlight a menubar item
    QTest::mouseMove(window.data(), editMenuBarItem->mapToScene(QPointF(editMenuBarItem->width() / 2, editMenuBarItem->height() / 2)).toPoint());
    QVERIFY(editMenuBarItem->isHighlighted());
    QVERIFY(!helpMenuBarItem->isHighlighted());
    QVERIFY(!editMenuBarMenu->isVisible());
    QVERIFY(!helpMenuBarMenu->isVisible());

    // trigger a menubar item to open a menu
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier, viewMenuBarItem->mapToScene(QPointF(viewMenuBarItem->width() / 2, viewMenuBarItem->height() / 2)).toPoint());
    QVERIFY(!editMenuBarItem->isHighlighted());
    QVERIFY(viewMenuBarItem->isHighlighted());
    QVERIFY(viewMenuBarMenu->isVisible());
    QTRY_VERIFY(viewMenuBarMenu->isOpened());

    // trigger a menu item to open a sub-menu
    QQuickMenuItem *alignmentSubMenuItem = qobject_cast<QQuickMenuItem *>(viewMenuBarMenu->itemAt(0));
    QVERIFY(alignmentSubMenuItem);
    QQuickMenu *alignmentSubMenu = alignmentSubMenuItem->subMenu();
    QVERIFY(alignmentSubMenu);
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier, alignmentSubMenuItem->mapToScene(QPointF(alignmentSubMenuItem->width() / 2, alignmentSubMenuItem->height() / 2)).toPoint());
    QVERIFY(viewMenuBarMenu->isVisible());
    QVERIFY(alignmentSubMenu->isVisible());
    QTRY_VERIFY(alignmentSubMenu->isOpened());

    // trigger a menu item to open a sub-sub-menu
    QQuickMenuItem *verticalSubMenuItem = qobject_cast<QQuickMenuItem *>(alignmentSubMenu->itemAt(1));
    QVERIFY(verticalSubMenuItem);
    QQuickMenu *verticalSubMenu = verticalSubMenuItem->subMenu();
    QVERIFY(verticalSubMenu);
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier, verticalSubMenuItem->mapToScene(QPointF(verticalSubMenuItem->width() / 2, verticalSubMenuItem->height() / 2)).toPoint());
    QVERIFY(viewMenuBarMenu->isVisible());
    QVERIFY(alignmentSubMenu->isVisible());
    QVERIFY(verticalSubMenu->isVisible());
    QTRY_VERIFY(verticalSubMenu->isOpened());

    // trigger a menu item to close the whole chain of menus
    QQuickMenuItem *centerMenuItem = qobject_cast<QQuickMenuItem *>(verticalSubMenu->itemAt(1));
    QVERIFY(centerMenuItem);
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier, centerMenuItem->mapToScene(QPointF(centerMenuItem->width() / 2, centerMenuItem->height() / 2)).toPoint());
    QVERIFY(!viewMenuBarItem->isHighlighted());
    QTRY_VERIFY(!viewMenuBarMenu->isVisible());
    QTRY_VERIFY(!alignmentSubMenu->isVisible());
    QTRY_VERIFY(!verticalSubMenu->isVisible());

    // re-highlight the same menubar item
    QTest::mouseMove(window.data(), viewMenuBarItem->mapToScene(QPointF(viewMenuBarItem->width() / 2, viewMenuBarItem->height() / 2)).toPoint());
    QVERIFY(viewMenuBarItem->isHighlighted());

    // re-open the chain of menus
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier, viewMenuBarItem->mapToScene(QPointF(viewMenuBarItem->width() / 2, viewMenuBarItem->height() / 2)).toPoint());
    QTRY_VERIFY(viewMenuBarMenu->isOpened());
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier, alignmentSubMenuItem->mapToScene(QPointF(alignmentSubMenuItem->width() / 2, alignmentSubMenuItem->height() / 2)).toPoint());
    QTRY_VERIFY(alignmentSubMenu->isOpened());
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier, verticalSubMenuItem->mapToScene(QPointF(verticalSubMenuItem->width() / 2, verticalSubMenuItem->height() / 2)).toPoint());
    QTRY_VERIFY(verticalSubMenu->isOpened());

    // click outside to close the whole chain of menus
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier, QPoint(window->width() - 1, window->height() - 1));
    QVERIFY(!viewMenuBarItem->isHighlighted());
    QTRY_VERIFY(!viewMenuBarMenu->isVisible());
    QTRY_VERIFY(!alignmentSubMenu->isVisible());
    QTRY_VERIFY(!verticalSubMenu->isVisible());
}

void tst_qquickmenubar::keys()
{
    QQmlApplicationEngine engine(testFileUrl("menubar.qml"));

    QScopedPointer<QQuickApplicationWindow> window(qobject_cast<QQuickApplicationWindow *>(engine.rootObjects().value(0)));
    QVERIFY(window);

    centerOnScreen(window.data());
    moveMouseAway(window.data());
    QVERIFY(QTest::qWaitForWindowActive(window.data()));

    QQuickMenuBar *menuBar = window->property("header").value<QQuickMenuBar *>();
    QVERIFY(menuBar);

    QQuickMenu *fileMenuBarMenu = menuBar->menuAt(0);
    QQuickMenu *editMenuBarMenu = menuBar->menuAt(1);
    QQuickMenu *viewMenuBarMenu = menuBar->menuAt(2);
    QQuickMenu *helpMenuBarMenu = menuBar->menuAt(3);
    QVERIFY(fileMenuBarMenu && editMenuBarMenu && viewMenuBarMenu && helpMenuBarMenu);

    QQuickMenuBarItem *fileMenuBarItem = qobject_cast<QQuickMenuBarItem *>(fileMenuBarMenu->parentItem());
    QQuickMenuBarItem *editMenuBarItem = qobject_cast<QQuickMenuBarItem *>(editMenuBarMenu->parentItem());
    QQuickMenuBarItem *viewMenuBarItem = qobject_cast<QQuickMenuBarItem *>(viewMenuBarMenu->parentItem());
    QQuickMenuBarItem *helpMenuBarItem = qobject_cast<QQuickMenuBarItem *>(helpMenuBarMenu->parentItem());
    QVERIFY(fileMenuBarItem && editMenuBarItem && viewMenuBarItem && helpMenuBarItem);

    // trigger a menubar item to open a menu
    editMenuBarItem->forceActiveFocus();
    QTest::keyClick(window.data(), Qt::Key_Space);
    QVERIFY(editMenuBarItem->isHighlighted());
    QVERIFY(editMenuBarMenu->isVisible());
    QTRY_VERIFY(editMenuBarMenu->isOpened());
    QVERIFY(editMenuBarMenu->hasActiveFocus());

    // navigate down to the menu
    QQuickMenuItem *cutMenuItem = qobject_cast<QQuickMenuItem *>(editMenuBarMenu->itemAt(0));
    QVERIFY(cutMenuItem);
    QVERIFY(!cutMenuItem->isHighlighted());
    QVERIFY(!cutMenuItem->hasActiveFocus());
    QTest::keyClick(window.data(), Qt::Key_Down);
    QVERIFY(cutMenuItem->isHighlighted());
    QVERIFY(cutMenuItem->hasActiveFocus());

    // navigate up, back to the menubar
    QTest::keyClick(window.data(), Qt::Key_Up);
    QVERIFY(editMenuBarItem->isHighlighted());
    QVERIFY(editMenuBarItem->hasActiveFocus());
    QTRY_VERIFY(!editMenuBarMenu->isVisible());
    QVERIFY(!cutMenuItem->isHighlighted());
    QVERIFY(!cutMenuItem->hasActiveFocus());

    // navigate down to re-open the menu
    QTest::keyClick(window.data(), Qt::Key_Down);
    QVERIFY(editMenuBarItem->isHighlighted());
    QVERIFY(!editMenuBarItem->hasActiveFocus());
    QVERIFY(editMenuBarMenu->isVisible());
    QTRY_VERIFY(editMenuBarMenu->isOpened());
    QVERIFY(editMenuBarMenu->hasActiveFocus());
    QVERIFY(cutMenuItem->isHighlighted());
    QVERIFY(cutMenuItem->hasActiveFocus());

    // navigate left in popup mode (menu open)
    QTest::keyClick(window.data(), Qt::Key_Left);
    QVERIFY(fileMenuBarItem->isHighlighted());
    QVERIFY(!editMenuBarItem->isHighlighted());
    QVERIFY(fileMenuBarMenu->isVisible());
    QTRY_VERIFY(fileMenuBarMenu->isOpened());
    QTRY_VERIFY(!editMenuBarMenu->isVisible());

    // navigate left in popup mode (wrap)
    QTest::keyClick(window.data(), Qt::Key_Left);
    QVERIFY(helpMenuBarItem->isHighlighted());
    QVERIFY(!fileMenuBarItem->isHighlighted());
    QVERIFY(helpMenuBarMenu->isVisible());
    QTRY_VERIFY(helpMenuBarMenu->isOpened());
    QTRY_VERIFY(!fileMenuBarMenu->isVisible());

    // navigate up to close the menu
    QTest::keyClick(window.data(), Qt::Key_Up);
    QVERIFY(helpMenuBarItem->isHighlighted());
    QTRY_VERIFY(!helpMenuBarMenu->isVisible());

    // navigate right in non-popup mode (wrap)
    QTest::keyClick(window.data(), Qt::Key_Right);
    QVERIFY(fileMenuBarItem->isHighlighted());
    QVERIFY(!helpMenuBarItem->isHighlighted());
    QVERIFY(!fileMenuBarMenu->isVisible());
    QVERIFY(!helpMenuBarMenu->isVisible());

    // navigate right in non-popup mode (menu closed)
    QTest::keyClick(window.data(), Qt::Key_Right);
    QVERIFY(!fileMenuBarItem->isHighlighted());
    QVERIFY(editMenuBarItem->isHighlighted());
    QVERIFY(!fileMenuBarMenu->isVisible());
    QVERIFY(!editMenuBarMenu->isVisible());

    // open a menu
    viewMenuBarItem->forceActiveFocus();
    QTest::keyClick(window.data(), Qt::Key_Space);
    QVERIFY(viewMenuBarItem->isHighlighted());
    QVERIFY(viewMenuBarMenu->isVisible());
    QTRY_VERIFY(viewMenuBarMenu->isOpened());
    QVERIFY(!viewMenuBarItem->hasActiveFocus());
    QVERIFY(viewMenuBarMenu->hasActiveFocus());

    // open a sub-menu
    QQuickMenuItem *alignmentSubMenuItem = qobject_cast<QQuickMenuItem *>(viewMenuBarMenu->itemAt(0));
    QVERIFY(alignmentSubMenuItem);
    QQuickMenu *alignmentSubMenu = alignmentSubMenuItem->subMenu();
    QVERIFY(alignmentSubMenu);
    QTest::keyClick(window.data(), Qt::Key_Down);
    QVERIFY(alignmentSubMenuItem->isHighlighted());
    QVERIFY(!alignmentSubMenu->isVisible());
    QTest::keyClick(window.data(), Qt::Key_Right);
    QVERIFY(alignmentSubMenu->isVisible());
    QTRY_VERIFY(alignmentSubMenu->isOpened());

    // open a sub-sub-menu
    QQuickMenuItem *horizontalSubMenuItem = qobject_cast<QQuickMenuItem *>(alignmentSubMenu->itemAt(0));
    QVERIFY(horizontalSubMenuItem);
    QVERIFY(horizontalSubMenuItem->isHighlighted());
    QQuickMenu *horizontalSubMenu = horizontalSubMenuItem->subMenu();
    QVERIFY(horizontalSubMenu);
    QTest::keyClick(window.data(), Qt::Key_Right);
    QVERIFY(viewMenuBarMenu->isVisible());
    QVERIFY(alignmentSubMenu->isVisible());
    QVERIFY(horizontalSubMenu->isVisible());
    QTRY_VERIFY(horizontalSubMenu->isOpened());

    // navigate left to close a sub-menu
    QTest::keyClick(window.data(), Qt::Key_Left);
    QTRY_VERIFY(!horizontalSubMenu->isVisible());
    QVERIFY(viewMenuBarMenu->isVisible());
    QVERIFY(alignmentSubMenu->isVisible());

    // navigate right to re-open the sub-menu
    QTest::keyClick(window.data(), Qt::Key_Right);
    QVERIFY(horizontalSubMenuItem->isHighlighted());
    QVERIFY(horizontalSubMenu->isVisible());
    QTRY_VERIFY(horizontalSubMenu->isOpened());

    // navigate right to the next menubar menu
    QTest::keyClick(window.data(), Qt::Key_Right);
    QVERIFY(!viewMenuBarItem->isHighlighted());
    QVERIFY(helpMenuBarItem->isHighlighted());
    QVERIFY(helpMenuBarMenu->isVisible());
    QTRY_VERIFY(!viewMenuBarMenu->isVisible());
    QTRY_VERIFY(!alignmentSubMenu->isVisible());
    QTRY_VERIFY(!horizontalSubMenu->isVisible());
    QTRY_VERIFY(helpMenuBarMenu->isOpened());

    // navigate back
    QTest::keyClick(window.data(), Qt::Key_Left);
    QVERIFY(!helpMenuBarItem->isHighlighted());
    QVERIFY(viewMenuBarItem->isHighlighted());
    QVERIFY(viewMenuBarMenu->isVisible());
    QTRY_VERIFY(!helpMenuBarMenu->isVisible());
    QTRY_VERIFY(viewMenuBarMenu->isOpened());

    // re-open the chain of menus
    QTest::keyClick(window.data(), Qt::Key_Down);
    QVERIFY(alignmentSubMenuItem->isHighlighted());
    QTest::keyClick(window.data(), Qt::Key_Right);
    QTRY_VERIFY(alignmentSubMenu->isOpened());
    QTest::keyClick(window.data(), Qt::Key_Right);
    QTRY_VERIFY(horizontalSubMenu->isOpened());

    // repeat escape to close the whole chain of menus one by one
    QTest::keyClick(window.data(), Qt::Key_Escape);
    QTRY_VERIFY(!horizontalSubMenu->isVisible());
    QVERIFY(viewMenuBarItem->isHighlighted());
    QVERIFY(viewMenuBarMenu->isVisible());
    QVERIFY(alignmentSubMenu->isVisible());

    QTest::keyClick(window.data(), Qt::Key_Escape);
    QTRY_VERIFY(!alignmentSubMenu->isVisible());
    QVERIFY(viewMenuBarItem->isHighlighted());
    QVERIFY(viewMenuBarMenu->isVisible());

    QTest::keyClick(window.data(), Qt::Key_Escape);
    QVERIFY(!viewMenuBarItem->isHighlighted());
    QTRY_VERIFY(!viewMenuBarMenu->isVisible());
}

void tst_qquickmenubar::mnemonics()
{
#ifdef Q_OS_MACOS
    QSKIP("Mnemonics are not used on macOS");
#endif

    QQmlApplicationEngine engine(testFileUrl("menubar.qml"));

    QScopedPointer<QQuickApplicationWindow> window(qobject_cast<QQuickApplicationWindow *>(engine.rootObjects().value(0)));
    QVERIFY(window);

    centerOnScreen(window.data());
    moveMouseAway(window.data());
    QVERIFY(QTest::qWaitForWindowActive(window.data()));

    MnemonicKeySimulator keySim(window.data());

    QQuickMenuBar *menuBar = window->property("header").value<QQuickMenuBar *>();
    QVERIFY(menuBar);

    QQuickMenu *fileMenuBarMenu = menuBar->menuAt(0);
    QQuickMenu *editMenuBarMenu = menuBar->menuAt(1);
    QQuickMenu *viewMenuBarMenu = menuBar->menuAt(2);
    QQuickMenu *helpMenuBarMenu = menuBar->menuAt(3);
    QVERIFY(fileMenuBarMenu && editMenuBarMenu && viewMenuBarMenu && helpMenuBarMenu);

    QQuickMenuBarItem *fileMenuBarItem = qobject_cast<QQuickMenuBarItem *>(fileMenuBarMenu->parentItem());
    QQuickMenuBarItem *editMenuBarItem = qobject_cast<QQuickMenuBarItem *>(editMenuBarMenu->parentItem());
    QQuickMenuBarItem *viewMenuBarItem = qobject_cast<QQuickMenuBarItem *>(viewMenuBarMenu->parentItem());
    QQuickMenuBarItem *helpMenuBarItem = qobject_cast<QQuickMenuBarItem *>(helpMenuBarMenu->parentItem());
    QVERIFY(fileMenuBarItem && editMenuBarItem && viewMenuBarItem && helpMenuBarItem);

    QQuickButton *oopsButton = window->property("oopsButton").value<QQuickButton *>();
    QVERIFY(oopsButton);
    QSignalSpy oopsButtonSpy(oopsButton, &QQuickButton::clicked);
    QVERIFY(oopsButtonSpy.isValid());

    // trigger a menubar item to open a menu
    keySim.press(Qt::Key_Alt);
    keySim.click(Qt::Key_E); // "&Edit"
    keySim.release(Qt::Key_Alt);
    QVERIFY(editMenuBarItem->isHighlighted());
    QVERIFY(!editMenuBarItem->hasActiveFocus());
    QVERIFY(editMenuBarMenu->isVisible());
    QTRY_VERIFY(editMenuBarMenu->isOpened());
    QVERIFY(editMenuBarMenu->hasActiveFocus());

    // press Alt to hide the menu
    keySim.click(Qt::Key_Alt);
    QVERIFY(!editMenuBarItem->isHighlighted());
    QVERIFY(!editMenuBarItem->hasActiveFocus());
    QVERIFY(!editMenuBarMenu->hasActiveFocus());
    QTRY_VERIFY(!editMenuBarMenu->isVisible());

    // re-trigger a menubar item to show the menu again
    keySim.press(Qt::Key_Alt);
    keySim.click(Qt::Key_E); // "&Edit"
    keySim.release(Qt::Key_Alt);
    QVERIFY(editMenuBarItem->isHighlighted());
    QVERIFY(editMenuBarMenu->isVisible());
    QTRY_VERIFY(editMenuBarMenu->isOpened());
    QVERIFY(editMenuBarMenu->hasActiveFocus());
    QVERIFY(!editMenuBarItem->hasActiveFocus());

    // trigger another menubar item to open another menu, leave Alt pressed
    keySim.press(Qt::Key_Alt);
    QTRY_VERIFY(!editMenuBarMenu->isVisible());
    keySim.click(Qt::Key_H); // "&Help"
    QVERIFY(!editMenuBarItem->isHighlighted());
    QVERIFY(helpMenuBarItem->isHighlighted());
    QVERIFY(!viewMenuBarMenu->isVisible());
    QVERIFY(helpMenuBarMenu->isVisible());
    QTRY_VERIFY(helpMenuBarMenu->isOpened());

    // trigger a menu item to close the menu
    keySim.click(Qt::Key_A); // "&About"
    keySim.release(Qt::Key_Alt);
    QVERIFY(!helpMenuBarItem->isHighlighted());
    QTRY_VERIFY(!helpMenuBarMenu->isVisible());

    // trigger a menubar item to open a menu, leave Alt pressed
    keySim.press(Qt::Key_Alt);
    keySim.click(Qt::Key_V); // "&View"
    QVERIFY(!editMenuBarItem->isHighlighted());
    QVERIFY(viewMenuBarItem->isHighlighted());
    QVERIFY(viewMenuBarMenu->isVisible());
    QTRY_VERIFY(viewMenuBarMenu->isOpened());

    // trigger a menu item to open a sub-menu, leave Alt pressed
    QQuickMenuItem *alignmentSubMenuItem = qobject_cast<QQuickMenuItem *>(viewMenuBarMenu->itemAt(0));
    QVERIFY(alignmentSubMenuItem);
    QQuickMenu *alignmentSubMenu = alignmentSubMenuItem->subMenu();
    QVERIFY(alignmentSubMenu);
    keySim.click(Qt::Key_A); // "&Alignment"
    QVERIFY(viewMenuBarMenu->isVisible());
    QVERIFY(alignmentSubMenu->isVisible());
    QTRY_VERIFY(alignmentSubMenu->isOpened());

    // trigger a menu item to open a sub-sub-menu, leave Alt pressed
    QQuickMenuItem *verticalSubMenuItem = qobject_cast<QQuickMenuItem *>(alignmentSubMenu->itemAt(1));
    QVERIFY(verticalSubMenuItem);
    QQuickMenu *verticalSubMenu = verticalSubMenuItem->subMenu();
    QVERIFY(verticalSubMenu);
    keySim.click(Qt::Key_V); // "&Vertical"
    QVERIFY(viewMenuBarMenu->isVisible());
    QVERIFY(alignmentSubMenu->isVisible());
    QVERIFY(verticalSubMenu->isVisible());
    QTRY_VERIFY(verticalSubMenu->isOpened());

    // trigger a menu item to close the whole chain of menus
    keySim.click(Qt::Key_C); // "&Center"
    keySim.release(Qt::Key_Alt);
    QVERIFY(!viewMenuBarItem->isHighlighted());
    QTRY_VERIFY(!viewMenuBarMenu->isVisible());
    QTRY_VERIFY(!alignmentSubMenu->isVisible());
    QTRY_VERIFY(!verticalSubMenu->isVisible());

    // trigger a menubar item to open a menu, leave Alt pressed
    keySim.press(Qt::Key_Alt);
    keySim.click(Qt::Key_F); // "&File"
    QVERIFY(fileMenuBarItem->isHighlighted());
    QVERIFY(fileMenuBarMenu->isVisible());
    QTRY_VERIFY(fileMenuBarMenu->isOpened());
    QVERIFY(fileMenuBarMenu->hasActiveFocus());

    // trigger a menu item to close the menu, which shouldn't trigger a button
    // action behind the menu (QTBUG-86276)
    QCOMPARE(oopsButtonSpy.count(), 0);
    keySim.click(Qt::Key_O); // "&Open..."
    keySim.release(Qt::Key_Alt);
    QVERIFY(!fileMenuBarItem->isHighlighted());
    QVERIFY(!fileMenuBarMenu->isOpened());
    QTRY_VERIFY(!fileMenuBarMenu->isVisible());
    QCOMPARE(oopsButtonSpy.count(), 0);

    // trigger a button action while menu is closed
    keySim.press(Qt::Key_Alt);
    keySim.click(Qt::Key_O); // "&Oops"
    keySim.release(Qt::Key_Alt);
    QCOMPARE(oopsButtonSpy.count(), 1);
}

void tst_qquickmenubar::addRemove()
{
    QQmlApplicationEngine engine(testFileUrl("empty.qml"));

    QScopedPointer<QQuickMenuBar> menuBar(qobject_cast<QQuickMenuBar *>(engine.rootObjects().value(0)));
    QVERIFY(menuBar);

    QQmlComponent component(&engine);
    component.setData("import QtQuick.Controls; Menu { }", QUrl());

    QPointer<QQuickMenu> menu1(qobject_cast<QQuickMenu *>(component.create()));
    QVERIFY(!menu1.isNull());
    menuBar->addMenu(menu1.data());
    QCOMPARE(menuBar->count(), 1);
    QCOMPARE(menuBar->menuAt(0), menu1.data());

    QPointer<QQuickMenuBarItem> menuBarItem1(qobject_cast<QQuickMenuBarItem *>(menuBar->itemAt(0)));
    QVERIFY(menuBarItem1);
    QCOMPARE(menuBarItem1->menu(), menu1.data());
    QCOMPARE(menuBar->itemAt(0), menuBarItem1.data());

    QScopedPointer<QQuickMenu> menu2(qobject_cast<QQuickMenu *>(component.create()));
    QVERIFY(!menu2.isNull());
    menuBar->insertMenu(0, menu2.data());
    QCOMPARE(menuBar->count(), 2);
    QCOMPARE(menuBar->menuAt(0), menu2.data());
    QCOMPARE(menuBar->menuAt(1), menu1.data());

    QPointer<QQuickMenuBarItem> menuBarItem2(qobject_cast<QQuickMenuBarItem *>(menuBar->itemAt(0)));
    QVERIFY(menuBarItem2);
    QCOMPARE(menuBarItem2->menu(), menu2.data());
    QCOMPARE(menuBar->itemAt(0), menuBarItem2.data());
    QCOMPARE(menuBar->itemAt(1), menuBarItem1.data());

    // takeMenu(int) does not destroy the menu, but does destroy the respective item in the menubar
    QCOMPARE(menuBar->takeMenu(1), menu1.data());
    QCOMPARE(menuBar->count(), 1);
    QVERIFY(!menuBar->menuAt(1));
    QVERIFY(!menuBar->itemAt(1));
    QCoreApplication::sendPostedEvents(menu1.data(), QEvent::DeferredDelete);
    QVERIFY(!menu1.isNull());
    QCoreApplication::sendPostedEvents(menuBarItem1, QEvent::DeferredDelete);
    QVERIFY(menuBarItem1.isNull());

    // addMenu(Menu) re-creates the respective item in the menubar
    menuBar->addMenu(menu1.data());
    QCOMPARE(menuBar->count(), 2);
    menuBarItem1 = qobject_cast<QQuickMenuBarItem *>(menuBar->itemAt(1));
    QVERIFY(!menuBarItem1.isNull());

    // removeMenu(Menu) destroys both the menu and the respective item in the menubar
    menuBar->removeMenu(menu1.data());
    QCOMPARE(menuBar->count(), 1);
    QVERIFY(!menuBar->itemAt(1));
    QCoreApplication::sendPostedEvents(menu1.data(), QEvent::DeferredDelete);
    QVERIFY(menu1.isNull());
    QCoreApplication::sendPostedEvents(menuBarItem1, QEvent::DeferredDelete);
    QVERIFY(menuBarItem1.isNull());
}

void tst_qquickmenubar::checkHighlightWhenMenuDismissed()
{
    if ((QGuiApplication::platformName() == QLatin1String("offscreen"))
        || (QGuiApplication::platformName() == QLatin1String("minimal")))
        QSKIP("Mouse highlight not functional on offscreen/minimal platforms");

    QQmlApplicationEngine engine(testFileUrl("checkHighlightWhenDismissed.qml"));
    QScopedPointer<QQuickApplicationWindow> window(qobject_cast<QQuickApplicationWindow *>(engine.rootObjects().value(0)));
    QVERIFY(window);

    centerOnScreen(window.data());
    moveMouseAway(window.data());
    QVERIFY(QTest::qWaitForWindowActive(window.data()));

    QQuickMenuBar *menuBar = window->findChild<QQuickMenuBar *>("menuBar");
    QVERIFY(menuBar);

    QQuickMenu *staticMenu = menuBar->menuAt(0);
    QQuickMenu *dynamicMenu = menuBar->menuAt(1);
    QVERIFY(staticMenu && dynamicMenu);
    QQuickMenuBarItem *staticMenuBarItem = qobject_cast<QQuickMenuBarItem *>(staticMenu->parentItem());
    QQuickMenuBarItem *dynamicMenuBarItem = qobject_cast<QQuickMenuBarItem *>(dynamicMenu->parentItem());
    QVERIFY(staticMenuBarItem && dynamicMenuBarItem);

    // highlight the static MenuBarItem and open the menu
    QTest::mouseMove(window.data(), staticMenuBarItem->mapToScene(
        QPointF(staticMenuBarItem->width() / 2, staticMenuBarItem->height() / 2)).toPoint());
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier,
        staticMenuBarItem->mapToScene(QPointF(staticMenuBarItem->width() / 2, staticMenuBarItem->height() / 2)).toPoint());
    QCOMPARE(staticMenuBarItem->isHighlighted(), true);
    QCOMPARE(staticMenu->isVisible(), true);
    QTRY_COMPARE(staticMenu->isOpened(), true);

    // click a menu item to dismiss the menu and unhighlight the static MenuBarItem
    QQuickMenuItem *menuItem = qobject_cast<QQuickMenuItem *>(staticMenu->itemAt(0));
    QVERIFY(menuItem);
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier,
        menuItem->mapToScene(QPointF(menuItem->width() / 2, menuItem->height() / 2)).toPoint());
    QCOMPARE(staticMenuBarItem->isHighlighted(), false);

    // highlight the dynamic MenuBarItem and open the menu
    QTest::mouseMove(window.data(), dynamicMenuBarItem->mapToScene(
        QPointF(dynamicMenuBarItem->width() / 2, dynamicMenuBarItem->height() / 2)).toPoint());
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier,
        dynamicMenuBarItem->mapToScene(QPointF(dynamicMenuBarItem->width() / 2, dynamicMenuBarItem->height() / 2)).toPoint());
    QCOMPARE(dynamicMenuBarItem->isHighlighted(), true);
    QCOMPARE(dynamicMenu->isVisible(), true);
    QTRY_COMPARE(dynamicMenu->isOpened(), true);

    // click a menu item to dismiss the menu and unhighlight the dynamic MenuBarItem
    menuItem = qobject_cast<QQuickMenuItem *>(dynamicMenu->itemAt(0));
    QVERIFY(menuItem);
    QTest::mouseClick(window.data(), Qt::LeftButton, Qt::NoModifier,
        menuItem->mapToScene(QPointF(menuItem->width() / 2, menuItem->height() / 2)).toPoint());
    QCOMPARE(dynamicMenuBarItem->isHighlighted(), false);
}

QTEST_QUICKCONTROLS_MAIN(tst_qquickmenubar)

#include "tst_qquickmenubar.moc"
