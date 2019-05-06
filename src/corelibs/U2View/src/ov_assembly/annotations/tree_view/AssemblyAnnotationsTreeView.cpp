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

#include <QItemSelection>
#include <QKeyEvent>

#include "AssemblyAnnotationsTreeView.h"
#include "AssemblyAnnotationsTreeViewModel.h"

#include <U2Core/AnnotationSelection.h>
#include <U2Core/SignalBlocker.h>
#include <U2Core/U2SafePoints.h>

namespace U2 {

AssemblyAnnotationsTreeView::AssemblyAnnotationsTreeView(QWidget *parent) : QTreeView(parent) {
    setSelectionMode(ExtendedSelection);
}

void AssemblyAnnotationsTreeView::keyPressEvent(QKeyEvent *e) {
    int key = e->key();
    bool accepted = false;
    switch (key) {
    case Qt::Key_Escape:
        clearSelection();
        accepted = true;
        break;
    }

    if (accepted) {
        e->accept();
    } else {
        QTreeView::keyPressEvent(e);
    }
}

void AssemblyAnnotationsTreeView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    AssemblyAnnotationsTreeViewModel* treeViewModel = getModel();
    CHECK(nullptr != treeViewModel, );

    treeViewModel->changeSelection(selected.indexes(), deselected.indexes());
    QTreeView::selectionChanged(selected, deselected);
}

void AssemblyAnnotationsTreeView::sl_annotationSelection(AnnotationSelectionData* asd) {
    Annotation* ann = asd->annotation;
    AssemblyAnnotationsTreeViewModel* treeViewModel = getModel();
    CHECK(nullptr != treeViewModel, );

    QModelIndex annotationModelIndex = treeViewModel->getAnnotationModelIndex(ann);
    CHECK(annotationModelIndex.isValid(), );

    QModelIndex parentTableObjectIndex = annotationModelIndex.parent();
    expand(parentTableObjectIndex);

    QModelIndex valueIndex = treeViewModel->index(annotationModelIndex.row(), treeViewModel->columnCount() - 1, parentTableObjectIndex);
    QItemSelection selected(annotationModelIndex, valueIndex);
    selectionChanged(selected, QItemSelection());
    //QRegion vRegion = visualRegionForSelection(QItemSelection(annotationModelIndex, valueIndex));
    //QRect vRect = vRegion.boundingRect();
    //QVector<QRect> rects = vRegion.rects();

    //{
    //    SignalBlocker signalBlocker(selectionModel());
    //    Q_UNUSED(signalBlocker);
    //    setSelection(vRect, QItemSelectionModel::Select);
    //}
}

AssemblyAnnotationsTreeViewModel* AssemblyAnnotationsTreeView::getModel() const {
    QAbstractItemModel* treeViewAbstractModel = model();
    SAFE_POINT(nullptr != treeViewAbstractModel, "Tree View Abstract Model is missed", nullptr);

    AssemblyAnnotationsTreeViewModel* treeViewModel = qobject_cast<AssemblyAnnotationsTreeViewModel*>(treeViewAbstractModel);
    SAFE_POINT(nullptr != treeViewModel, "Assembly Annotations Tree View Model is missed", nullptr);

    return treeViewModel;
}

}