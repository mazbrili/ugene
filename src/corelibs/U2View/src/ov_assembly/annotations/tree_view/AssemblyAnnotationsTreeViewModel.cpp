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

#include <U2Core/AnnotationTableObject.h>
#include <U2Core/U2SafePoints.h>

#include <U2View/SequenceObjectContext.h>

#include "AssemblyAnnotationsTreeItem.h"
#include "AssemblyAnnotationsTreeViewModel.h"

namespace U2 {

AssemblyAnnotationsTreeViewModel::AssemblyAnnotationsTreeViewModel(QObject *parent) : QAbstractItemModel(parent) {
    QVariantList rootData = { tr("Name"), tr("Value") };
    rootItem = new AssemblyAnnotationsTreeItem(rootData);
    init();
}

AssemblyAnnotationsTreeViewModel::~AssemblyAnnotationsTreeViewModel() {
    delete rootItem;
}

QModelIndex AssemblyAnnotationsTreeViewModel::index(int row, int column, const QModelIndex &parent) const {
    CHECK(hasIndex(row, column, parent), QModelIndex());

    AssemblyAnnotationsTreeItem* parentItem = !parent.isValid() ? rootItem
                            : static_cast<AssemblyAnnotationsTreeItem*>(parent.internalPointer());
    //if (parent.isValid()) {
    //    parentItem = static_cast<AssemblyAnnotationsTreeItem*>(parent.internalPointer());
    //} else {
    //    parentItem = rootItem;
    //}

    AssemblyAnnotationsTreeItem* childItem = parentItem->getChild(row);
    CHECK(nullptr != childItem, QModelIndex());

    return createIndex(row, column, childItem);
}

QModelIndex AssemblyAnnotationsTreeViewModel::parent(const QModelIndex &child) const {
    CHECK(child.isValid(), QModelIndex());

    AssemblyAnnotationsTreeItem *childItem = static_cast<AssemblyAnnotationsTreeItem*>(child.internalPointer());
    AssemblyAnnotationsTreeItem *parentItem = childItem->getParent();
    CHECK(childItem != parentItem, QModelIndex());

    return createIndex(parentItem->getRowNum(), 0, parentItem);
}

QVariant AssemblyAnnotationsTreeViewModel::headerData(int section, Qt::Orientation orientation, int role) const {
    CHECK(role == Qt::DisplayRole, QVariant());
    return rootItem->getData(section);
}

QVariant AssemblyAnnotationsTreeViewModel::data(const QModelIndex &index, int role) const {
    CHECK(index.isValid(), QVariant());
    CHECK(role == Qt::DisplayRole, QVariant());

    AssemblyAnnotationsTreeItem *item = static_cast<AssemblyAnnotationsTreeItem*>(index.internalPointer());
    return item->getData(index.column());
}

int AssemblyAnnotationsTreeViewModel::rowCount(const QModelIndex &parent) const {
    CHECK(parent.column() <= 0, 0);

    AssemblyAnnotationsTreeItem *parentItem = !parent.isValid() ? rootItem
                        : static_cast<AssemblyAnnotationsTreeItem*>(parent.internalPointer());
    //if (parent.column() > 0)
    //    return 0;
    //if (!parent.isValid())
    //    parentItem = rootItem;
    //else
    //    parentItem = static_cast<TreeItem*>(parent.internalPointer());
    return parentItem->childrenCount();
}

int AssemblyAnnotationsTreeViewModel::columnCount(const QModelIndex &parent) const {
    AssemblyAnnotationsTreeItem *parentItem = !parent.isValid() ? rootItem
                        : static_cast<AssemblyAnnotationsTreeItem*>(parent.internalPointer());
    return parentItem->columnCount();
}

//void AssemblyAnnotationsTreeViewModel::sl_objectAdded(GObject *obj) {
//
//}
//
//void AssemblyAnnotationsTreeViewModel::sl_objectRemoved(GObject *obj) {
//
//}

void AssemblyAnnotationsTreeViewModel::init() {



    int i = 0;
}

}