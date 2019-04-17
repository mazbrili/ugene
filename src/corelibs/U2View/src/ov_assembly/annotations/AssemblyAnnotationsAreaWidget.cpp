/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2019 UniPro <ugene@unipro.ru>
 * http://ugene.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <QObject>
#include <QPainter>
#include <QVBoxLayout>

#include <U2Gui/GScrollBar.h>

#include "../AssemblyBrowser.h"
#include "AssemblyAnnotationsArea.h"
#include "AssemblyAnnotationsAreaRenderer.h"
#include "AssemblyAnnotationsAreaWidget.h"
#include "AssemblyAnnotationsRenderArea.h"
#include "AssemblyAnnotationsRenderAreaFactory.h"

namespace U2 {

AssemblyAnnotationsAreaWidget::AssemblyAnnotationsAreaWidget
                    (AssemblyBrowser* _browser,
                     AssemblyBrowserUi* _ui,
                     SequenceObjectContext* _ctx,
                     QScrollBar* _vBar)
                        : PanView(_ui,
                                  _ctx,
                                  AssemblyAnnotationsRenderAreaFactory(_ui,
                                                                       _browser)),
                          browser(_browser),
                          browserUi(_ui),
                          renderer(dynamic_cast<AssemblyAnnotationsAreaRenderer*>(getRenderArea()->getRenderer())) {
    setLocalToolbarVisible(false);
    sl_toggleMainRulerVisibility(false);

    scrollBar->hide();
    //rowBar->hide();
    QGridLayout* girdLayout = qobject_cast<QGridLayout*>(contentWidget->layout());
    //int h = rowBar->height();
    //girdLayout->removeWidget(rowBar);
    //delete rowBar;
    //rowBar = _vBar;
    //resize(width(), getRenderArea()->getRowLineHeight() * settings->numLines);
    //update();
    int h = height();
    int i = 0;

    connectSlots();
}

//void AssemblyAnnotationsAreaWidget::pack() {
//    QGridLayout* layout = new QGridLayout();
//    layout->setMargin(0);
//    layout->setSpacing(0);
//    layout->addWidget(renderArea, 0, 0, 1, 1);
//    layout->addWidget(rowBar, 0, 1, 1, 1);
//    //layout->addWidget(scrollBar, 1, 0, 1, 1);
//    setContentLayout(layout);
//
//}

void AssemblyAnnotationsAreaWidget::mouseMoveEvent(QMouseEvent *e) {
    emit si_mouseMovedToPos(e->pos());
    PanView::mouseMoveEvent(e);
}

void AssemblyAnnotationsAreaWidget::sl_zoomPerformed() {
    updateVisibleRange();
    update();
}

void AssemblyAnnotationsAreaWidget::sl_offsetsChanged() {
    updateVisibleRange();
    update();
}

void AssemblyAnnotationsAreaWidget::connectSlots() const {
    connect(this, SIGNAL(si_mouseMovedToPos(const QPoint &)),
            browserUi->getAnnotationsArea(), SIGNAL(si_mouseMovedToPos(const QPoint &)));
    connect(browser, SIGNAL(si_zoomOperationPerformed()), SLOT(sl_zoomPerformed()));
    connect(browser, SIGNAL(si_offsetsChanged()), SLOT(sl_offsetsChanged()));
}

void AssemblyAnnotationsAreaWidget::updateVisibleRange() {
    U2Region visibleBaseReg = browser->getVisibleBasesRegion();
    if (visibleBaseReg != getVisibleRange()) {
        setVisibleRange(visibleBaseReg);
        addUpdateFlags(GSLV_UF_VisibleRangeChanged);
    }
}

} // U2
