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

#include <qpushbutton.h>
#include <QVBoxLayout>
//#include <QPainter>
//
//#include <U2Core/U2OpStatusUtils.h>
#include <U2Core/U2SafePoints.h>
//#include <U2Core/VariantTrackObject.h>
//
#include "..\AssemblyBrowser.h"
#include "../AssemblyModel.h"
#include "AssemblyAnnotationsArea.h"

//#include "AssemblyAnnotationRowManager.h"
#include "AssemblyAnnotationRowManager.h"
namespace U2 {

//const int AssemblyVariantRow::FIXED_HEIGHT = 30;
//const int AssemblyVariantRow::TOP_OFFSET = 13;
/************************************************************************/
/* AssemblyAnnotationRowManager */
/************************************************************************/
AssemblyAnnotationRowManager::AssemblyAnnotationRowManager(AssemblyBrowserUi *_ui)
: ui(_ui), browser(_ui->getWindow()), model(_ui->getModel())
{
    //connect(model.data(), SIGNAL(si_trackAdded(VariantTrackObject*)), SLOT(sl_trackAdded(VariantTrackObject*)));
    //connect(model.data(), SIGNAL(si_trackRemoved(VariantTrackObject*)), SLOT(sl_trackRemoved(VariantTrackObject*)));
}

//void AssemblyAnnotationRowManager::sl_trackRemoved(VariantTrackObject *objToRemove) {
//    AssemblyAnnotationsArea *annotationsArea = ui->getAnnotationsArea();
//
//    QLayout *layout = annotationsArea->layout();
//    QVBoxLayout *vertLayout = qobject_cast<QVBoxLayout*>(layout);
//    SAFE_POINT(NULL != vertLayout, "Internal error: layout problems", );
//
//    //for (int i=0; i<vertLayout->count(); i++) {
//    //    QLayoutItem *it = vertLayout->itemAt(i);
//    //    QWidget *w = it->widget();
//    //    AssemblyVariantRow *row = dynamic_cast<AssemblyVariantRow*>(w);
//    //    if (NULL == row) {
//    //        continue;
//    //    }
//    //    VariantTrackObject *trackObj = row->getTrackObject();
//    //    if (objToRemove == trackObj) {
//    //        vertLayout->removeWidget(row);
//    //        row->hide();
//    //        break;
//    //    }
//    //}
//}

//void AssemblyAnnotationRowManager::sl_trackAdded(VariantTrackObject *newTrackObj) {
//    AssemblyAnnotationsArea *annotationsArea = ui->getAnnotationsArea();
//
//    QLayout *layout = annotationsArea->layout();
//    QVBoxLayout *vertLayout = qobject_cast<QVBoxLayout*>(layout);
//    SAFE_POINT(NULL != vertLayout, "Internal error: layout problems", );
//
//    //AssemblyVariantRow *row = new AssemblyVariantRow(variantsArea, newTrackObj, browser);
//    //vertLayout->addWidget(row);
//
//    //connect(browser, SIGNAL(si_zoomOperationPerformed()), row, SLOT(sl_zoomPerformed()));
//    //connect(browser, SIGNAL(si_offsetsChanged()), row, SLOT(sl_offsetsChanged()));
//    //connect(row, SIGNAL(si_mouseMovedToPos(const QPoint &)), variantsArea, SIGNAL(si_mouseMovedToPos(const QPoint &)));
//    //connect(row, SIGNAL(si_removeRow()), SLOT(sl_removeRow()));
//}

void AssemblyAnnotationRowManager::sl_removeRow() {
    QObject *s = sender();
    //AssemblyVariantRow *row = dynamic_cast<AssemblyVariantRow*>(s);
    //SAFE_POINT(NULL != row, "Internal error: NULL row widget", );

    //model->sl_trackObjRemoved(row->getTrackObject());
}

} // U2
