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

#include <U2Core/DocumentModel.h>
#include <U2Core/U1AnnotationUtils.h>
#include <U2Core/U2Qualifier.h>
#include <U2Core/U2SafePoints.h>

#include <U2View/SequenceObjectContext.h>

#include "AssemblyAnnotationsTreeItem.h"
#include "AssemblyAnnotationsTreeViewModel.h"

namespace U2 {

AssemblyAnnotationsTreeViewModel::AssemblyAnnotationsTreeViewModel(QObject *parent) : QAbstractItemModel(parent),
                                                                                      ctx(nullptr) {
    QVariantList rootData = { tr("Name"), tr("Value") };
    rootItem = new AssemblyAnnotationsTreeItem(rootData);
}

AssemblyAnnotationsTreeViewModel::~AssemblyAnnotationsTreeViewModel() {
    delete rootItem;
}

QModelIndex AssemblyAnnotationsTreeViewModel::index(int row, int column, const QModelIndex &index) const {
    CHECK(hasIndex(row, column, index), QModelIndex());

    AssemblyAnnotationsTreeItem* parentItem = !index.isValid() ? rootItem
                            : static_cast<AssemblyAnnotationsTreeItem*>(index.internalPointer());
    SAFE_POINT(nullptr != parentItem, "Unexpected nullptr", QModelIndex());

    AssemblyAnnotationsTreeItem* childItem = parentItem->getChild(row);
    CHECK(nullptr != childItem, QModelIndex());

    return createIndex(row, column, childItem);
}

QModelIndex AssemblyAnnotationsTreeViewModel::parent(const QModelIndex &index) const {
    CHECK(index.isValid(), QModelIndex());

    AssemblyAnnotationsTreeItem *item = static_cast<AssemblyAnnotationsTreeItem*>(index.internalPointer());
    SAFE_POINT(nullptr != item, "Unexpected nullptr", QModelIndex());

    AssemblyAnnotationsTreeItem *parentItem = item->getParent();
    CHECK(nullptr != parentItem, QModelIndex());

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

int AssemblyAnnotationsTreeViewModel::rowCount(const QModelIndex &index) const {
    AssemblyAnnotationsTreeItem *indexItem = !index.isValid() ? rootItem
                        : static_cast<AssemblyAnnotationsTreeItem*>(index.internalPointer());
    SAFE_POINT(nullptr != indexItem, "Unexpected nullptr", 0);

    return indexItem->childrenCount();
}

int AssemblyAnnotationsTreeViewModel::columnCount(const QModelIndex &index) const {
    AssemblyAnnotationsTreeItem *indexItem = !index.isValid() ? rootItem
                        : static_cast<AssemblyAnnotationsTreeItem*>(index.internalPointer());
    SAFE_POINT(nullptr != indexItem, "Unexpected nullptr", 0);

    return indexItem->columnCount();
}

void AssemblyAnnotationsTreeViewModel::sl_annotationObjectAdded(AnnotationTableObject *obj) {
    addAnnotationTableObject(obj);
}

void AssemblyAnnotationsTreeViewModel::sl_annotationObjectRemoved(AnnotationTableObject *obj) {
    //Do you guarantee that the order of tables in the context is the same as in the tree view model?
    //If not, then search the item in the model by the pointer. It won't take too much time, there won't be many tables. Otherwise add a SAFE_POINT that the found index is not out of boundaries
    AssemblyAnnotationsTreeItem* item = rootItem->takeChild(ctx->getAnnotationObjects().toList().indexOf(obj));
    CHECK(nullptr != item, );

    delete item;
}

void AssemblyAnnotationsTreeViewModel::sl_contextChanged(SequenceObjectContext* _ctx) {
    //TODO: UGENE-6456
    //cleanAnnotationTree();
    ctx = _ctx;
}

void AssemblyAnnotationsTreeViewModel::addAnnotationTableObject(AnnotationTableObject* newObj) {
    beginInsertRows(QModelIndex(), rootItem->getRowNum(), rootItem->getRowNum());

    QVariantList tableObjData = getTableObjData(newObj);
    AssemblyAnnotationsTreeItem* tableObjItem = new AssemblyAnnotationsTreeItem(tableObjData, rootItem);
    rootItem->addChild(tableObjItem);
    endInsertRows();
    addAnnotations(newObj->getAnnotations(), tableObjItem);
}

void AssemblyAnnotationsTreeViewModel::addAnnotations(const QList<Annotation*>& annotations,
                                                      AssemblyAnnotationsTreeItem* parentItem) {
    CHECK(!annotations.isEmpty(), );

    QModelIndex tableObjectIndex = createIndex(parentItem->getRowNum(), 0, parentItem);
    beginInsertRows(tableObjectIndex, 0, annotations.size() - 1);
    foreach(Annotation* ann, annotations) {
        QVariantList annData = getAnnotationData(ann);
        AssemblyAnnotationsTreeItem* annObjItem = new AssemblyAnnotationsTreeItem(annData, parentItem);
        parentItem->addChild(annObjItem);
        addQualifiers(ann->getQualifiers().toList(), annObjItem);
    }
    endInsertRows();
}

void AssemblyAnnotationsTreeViewModel::addQualifiers(const QList<U2Qualifier>& qualifiers,
                                                     AssemblyAnnotationsTreeItem* parentItem) {
    CHECK(!qualifiers.isEmpty(), );

    QModelIndex annotationObjectIndex = createIndex(parentItem->getRowNum(), 0, parentItem);
    beginInsertRows(annotationObjectIndex, 0, qualifiers.size() - 1);
    foreach(const U2Qualifier& qualifier, qualifiers) {
        QVariantList qualifierData = getQualifierData(qualifier);
        AssemblyAnnotationsTreeItem* qualifierItem = new AssemblyAnnotationsTreeItem(qualifierData, parentItem);
        parentItem->addChild(qualifierItem);
    }
    endInsertRows();
}

QVariantList AssemblyAnnotationsTreeViewModel::getTableObjData(AnnotationTableObject* obj) const {
    const QString annTableObjName = obj->getGObjectName();
    const QString docShortName = obj->getDocument()->getName();
    QVariantList tableObjData = { annTableObjName + " [" + docShortName + "]", "" };

    return tableObjData;
}

QVariantList AssemblyAnnotationsTreeViewModel::getAnnotationData(Annotation* ann) const {
    QVector<U2Region> regions = ann->getRegions();
    QString annRegionString = U1AnnotationUtils::buildLocationString(regions);
    if (regions.size() > 1) {
        annRegionString = QString("join(%1)").arg(annRegionString);
    } else if (ann->getStrand() == U2Strand::Complementary) {
        annRegionString = QString("complementary(%1)").arg(annRegionString);
    }
    QVariantList annData = { ann->getName(), annRegionString };

    return annData;
}

QVariantList AssemblyAnnotationsTreeViewModel::getQualifierData(const U2Qualifier& qualifier) const {
    QVariantList qualifierData = { qualifier.name, qualifier.value };

    return qualifierData;
}

void AssemblyAnnotationsTreeViewModel::cleanAnnotationTree() {
    CHECK(nullptr != ctx, );

    foreach(AnnotationTableObject *obj, ctx->getAnnotationObjects(true)) {
        sl_annotationObjectRemoved(obj);
    }
}

}