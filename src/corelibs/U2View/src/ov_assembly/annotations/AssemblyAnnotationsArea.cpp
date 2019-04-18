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

#include <QSharedPointer>

#include <U2Core/U2SafePoints.h>

#include <U2View/SequenceObjectContext.h>

#include "../AssemblyBrowser.h"
#include "../AssemblyModel.h"

#include "AssemblyAnnotationsArea.h"
#include "AssemblyAnnotationsAreaWidget.h"

namespace U2 {

AssemblyAnnotationsArea::AssemblyAnnotationsArea(AssemblyBrowserUi* _ui, QScrollBar* _vBar)
                    : browserUi(_ui),
                        seqCtx(nullptr),
                        widget(nullptr),
                        vBar(_vBar) {
    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    this->setLayout(vLayout);
    vLayout->setMargin(0);
    vLayout->setSpacing(0);
    connectSignals();
}

AssemblyAnnotationsArea::~AssemblyAnnotationsArea() {
    delete widget;
}

void AssemblyAnnotationsArea::sl_contextChanged(SequenceObjectContext* ctx) {
    SAFE_POINT(nullptr != ctx, tr("Sequence Object Context is absent"), );
    seqCtx = ctx;

    AssemblyAnnotationsArea* annotatiomnArea = browserUi->getAnnotationsArea();
    SAFE_POINT(nullptr != annotatiomnArea, tr("Assembly Annotations Area widget is missed"), );

    QLayout *layout = annotatiomnArea->layout();
    QVBoxLayout *vertLayout = qobject_cast<QVBoxLayout*>(layout);
    SAFE_POINT(nullptr != vertLayout, tr("Internal error: layout problems"), );

    AssemblyBrowser* browser = browserUi->getWindow();
    SAFE_POINT(nullptr != browser, tr("Assembly Browser is missed"), );

    if (nullptr != widget) {
        delete widget;
    }
    widget = new AssemblyAnnotationsAreaWidget(browser, browserUi, seqCtx, vBar);
    vertLayout->addWidget(widget);
    //ctx->getA
}

void AssemblyAnnotationsArea::connectSignals() {
    SAFE_POINT(nullptr != browserUi, tr("Assembly browser widget is missed"), );

    AssemblyModel* model = browserUi->getModel().data();
    SAFE_POINT(nullptr != model, tr("Annotation model is missed"), );

    connect(model, SIGNAL(si_contectChanged(SequenceObjectContext*)), SLOT(sl_contextChanged(SequenceObjectContext*)));
}

} // U2
