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

#include <QApplication>
#include <QItemSelection>
#include <QKeyEvent>

#include "../AssemblyAnnotationsAreaUtils.h"
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

    expand(annotationModelIndex.parent());

    QItemSelectionModel* selModel = selectionModel();
    SAFE_POINT(nullptr != selModel, "Selection Model is missed", );

    QModelIndexList selectedAnnotationModelIndexList = selModel->selectedRows();
    QItemSelectionModel::SelectionFlag clickedModelIndexFlag = QItemSelectionModel::NoUpdate;
    QModelIndexList toDeselect;
    AssemblyAnnotationsAreaUtils::collectSelectionInfo<QModelIndex>(annotationModelIndex,
                                                                    selectedAnnotationModelIndexList,
                                                                    clickedModelIndexFlag,
                                                                    toDeselect);
    QItemSelection clickedRow = AssemblyAnnotationsAreaUtils::rowSelection(treeViewModel, annotationModelIndex);
    QItemSelection deselectRows;
    foreach(const QModelIndex& index, toDeselect) {
        QItemSelection rowToDeselect = AssemblyAnnotationsAreaUtils::rowSelection(treeViewModel, index);
        deselectRows.merge(rowToDeselect, QItemSelectionModel::Select);
    }

    QItemSelection selected;
    QItemSelection deselected;
    switch (clickedModelIndexFlag) {
    case QItemSelectionModel::Select:
        selected = clickedRow;
        deselected = deselectRows;
        break;
    case QItemSelectionModel::Deselect:
        deselected = deselectRows;
        deselected.merge(clickedRow, QItemSelectionModel::Select);
        break;
    case QItemSelectionModel::NoUpdate:
        deselected = deselectRows;
        break;
    default:
        FAIL("Unexpected Selection Flag", );
    }

    {
        SignalBlocker signalBlocker(selectionModel());
        Q_UNUSED(signalBlocker);
        selModel->select(selected, QItemSelectionModel::Select);
        selModel->select(deselected, QItemSelectionModel::Deselect);
        QTreeView::selectionChanged(selected, deselected);

    }
}

void AssemblyAnnotationsTreeView::sl_clearSelectedAnnotations() {
    clearSelection();
}

AssemblyAnnotationsTreeViewModel* AssemblyAnnotationsTreeView::getModel() const {
    QAbstractItemModel* treeViewAbstractModel = model();
    SAFE_POINT(nullptr != treeViewAbstractModel, "Tree View Abstract Model is missed", nullptr);

    AssemblyAnnotationsTreeViewModel* treeViewModel = qobject_cast<AssemblyAnnotationsTreeViewModel*>(treeViewAbstractModel);
    SAFE_POINT(nullptr != treeViewModel, "Assembly Annotations Tree View Model is missed", nullptr);

    return treeViewModel;
}

}