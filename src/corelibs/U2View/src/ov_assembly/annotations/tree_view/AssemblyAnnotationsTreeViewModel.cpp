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
#include <U2Core/DocumentModel.h>
#include <U2Core/U2Qualifier.h>
#include <U2Core/U2SafePoints.h>

#include <U2View/SequenceObjectContext.h>

#include "AssemblyAnnotationsTreeItem.h"
#include "AssemblyAnnotationsTreeViewModel.h"

namespace U2 {

AssemblyAnnotationsTreeViewModel::AssemblyAnnotationsTreeViewModel(QObject *parent) : QAbstractItemModel(parent) {
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

    AssemblyAnnotationsTreeItem* childItem = parentItem->getChild(row);
    CHECK(nullptr != childItem, QModelIndex());

    return createIndex(row, column, childItem);
}

QModelIndex AssemblyAnnotationsTreeViewModel::parent(const QModelIndex &index) const {
    CHECK(index.isValid(), QModelIndex());

    AssemblyAnnotationsTreeItem *item = static_cast<AssemblyAnnotationsTreeItem*>(index.internalPointer());
    AssemblyAnnotationsTreeItem *parentItem = item->getParent();
    //CHECK(item != parentItem, QModelIndex());
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
    //CHECK(index.column() <= 0, 0);
    //int c = index.column();

    AssemblyAnnotationsTreeItem *indexItem = !index.isValid() ? rootItem
                        : static_cast<AssemblyAnnotationsTreeItem*>(index.internalPointer());
    return indexItem->childrenCount();
}

int AssemblyAnnotationsTreeViewModel::columnCount(const QModelIndex &index) const {
    AssemblyAnnotationsTreeItem *indexItem = !index.isValid() ? rootItem
                        : static_cast<AssemblyAnnotationsTreeItem*>(index.internalPointer());
    return indexItem->columnCount();
}

//bool AssemblyAnnotationsTreeViewModel::insertRows(int row, int count, const QModelIndex &parent) {
//    beginInsertRows(parent, row, row + count - 1);
//
//    AnnotationTableObject* newObj = annTableObjects.last();
//    QVariantList tableObjData = getTableObjData(newObj);
//    AssemblyAnnotationsTreeItem* tableObjItem = new AssemblyAnnotationsTreeItem(tableObjData, rootItem);
//    rootItem->addChild(tableObjItem);
//    endInsertRows();
//    addAnnotations(newObj->getAnnotations(), tableObjItem);
//
//    //QModelIndex tableObjectIndex = createIndex(tableObjItem->getRowNum(), 0, tableObjItem);
//    //QList<Annotation*> annList = newObj->getAnnotations();
//    //beginInsertRows(tableObjectIndex, 0, annList.size() - 1);
//    //foreach(Annotation* ann, annList) {
//    //    QVariantList annData = getAnnotationData(ann);
//    //    AssemblyAnnotationsTreeItem* annObjItem = new AssemblyAnnotationsTreeItem(annData, tableObjItem);
//    //    tableObjItem->addChild(annObjItem);
//    //    QModelIndex annotationObjectIndex = createIndex(annObjItem->getRowNum(), 0, annObjItem);
//    //    QVector<U2Qualifier> qualifiers = ann->getQualifiers();
//    //    beginInsertRows(annotationObjectIndex, 0, qualifiers.size() - 1);
//    //    foreach(const U2Qualifier& qualifier, qualifiers) {
//    //        QVariantList qualifierData = getQualifierData(qualifier);
//    //        AssemblyAnnotationsTreeItem* qualifierItem = new AssemblyAnnotationsTreeItem(qualifierData, annObjItem);
//    //        annObjItem->addChild(qualifierItem);
//    //    }
//    //    endInsertRows();
//    //    endInsertRows();
//    //}
//
//
//    return true;
//}

Qt::ItemFlags AssemblyAnnotationsTreeViewModel::flags(const QModelIndex &index) const {
    CHECK(index.isValid(), 0);

    return QAbstractItemModel::flags(index);
}

void AssemblyAnnotationsTreeViewModel::sl_annotationObjectAdded(AnnotationTableObject *obj) {
    addAnnotationTableObject(obj);
}

void AssemblyAnnotationsTreeViewModel::sl_annotationObjectRemoved(AnnotationTableObject *obj) {
    AssemblyAnnotationsTreeItem* item = rootItem->getChild(annTableObjects.indexOf(obj));
    CHECK(nullptr != item, );

    delete item;
    annTableObjects.removeOne(obj);
}

void AssemblyAnnotationsTreeViewModel::sl_contextChanged(SequenceObjectContext* _ctx) {
    ctx = _ctx;
    updateTreeView();
}

void AssemblyAnnotationsTreeViewModel::updateTreeView() {
    CHECK(nullptr != ctx, );

    foreach(AnnotationTableObject* aObj, ctx->getAnnotationObjects()) {
        addAnnotationTableObject(aObj);
    }
}

void AssemblyAnnotationsTreeViewModel::addAnnotationTableObject(AnnotationTableObject* newObj) {
    CHECK(!annTableObjects.contains(newObj), );

    annTableObjects << newObj;

    beginInsertRows(QModelIndex(), 0, 0);

    QVariantList tableObjData = getTableObjData(newObj);
    AssemblyAnnotationsTreeItem* tableObjItem = new AssemblyAnnotationsTreeItem(tableObjData, rootItem);
    rootItem->addChild(tableObjItem);
    endInsertRows();
    addAnnotations(newObj->getAnnotations(), tableObjItem);

    //QVariantList tableObjData = getTableObjData(newObj);
    //AssemblyAnnotationsTreeItem* tableObjItem = new AssemblyAnnotationsTreeItem(tableObjData, rootItem);
    //rootItem->addChild(tableObjItem);
    //addAnnotations(newObj->getAnnotations(), tableObjItem);
}

void AssemblyAnnotationsTreeViewModel::addAnnotations(const QList<Annotation*>& annotations,
                                                      AssemblyAnnotationsTreeItem* parentItem) {
    CHECK(!annotations.isEmpty(), );

    QModelIndex tableObjectIndex = createIndex(parentItem->getRowNum(), 0, parentItem);
    foreach(Annotation* ann, annotations) {
        beginInsertRows(tableObjectIndex, annotations.indexOf(ann), annotations.indexOf(ann));
        QVariantList annData = getAnnotationData(ann);
        AssemblyAnnotationsTreeItem* annObjItem = new AssemblyAnnotationsTreeItem(annData, parentItem);
        parentItem->addChild(annObjItem);
        endInsertRows();

        addQualifiers(ann->getQualifiers().toList(), annObjItem);
        //QModelIndex annotationObjectIndex = createIndex(annObjItem->getRowNum(), 0, annObjItem);
        //QVector<U2Qualifier> qualifiers = ann->getQualifiers();
        //beginInsertRows(annotationObjectIndex, 0, qualifiers.size() - 1);
        //foreach(const U2Qualifier& qualifier, qualifiers) {
        //    QVariantList qualifierData = getQualifierData(qualifier);
        //    AssemblyAnnotationsTreeItem* qualifierItem = new AssemblyAnnotationsTreeItem(qualifierData, annObjItem);
        //    annObjItem->addChild(qualifierItem);
        //}
        //endInsertRows();
    }


    //foreach(Annotation* ann, annotations) {
    //    QVariantList annData = getAnnotationData(ann);
    //    AssemblyAnnotationsTreeItem* annObjItem = new AssemblyAnnotationsTreeItem(annData, parentItem);
    //    parentItem->addChild(annObjItem);
    //    addQualifiers(ann->getQualifiers().toList(), annObjItem);
    //}
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


    //foreach(const U2Qualifier& qualifier, qualifiers) {
    //    QVariantList qualifierData = getQualifierData(qualifier);
    //    AssemblyAnnotationsTreeItem* qualifierItem = new AssemblyAnnotationsTreeItem(qualifierData, parentItem);
    //    parentItem->addChild(qualifierItem);
    //}
}

QVariantList AssemblyAnnotationsTreeViewModel::getTableObjData(AnnotationTableObject* obj) const {
    const QString annTableObjName = obj->getGObjectName();
    const QString docShortName = obj->getDocument()->getName();
    QVariantList tableObjData = { annTableObjName + " [" + docShortName + "]", "" };

    return tableObjData;
}

QVariantList AssemblyAnnotationsTreeViewModel::getAnnotationData(Annotation* ann) const {
    QString annRegionString;
    QVector<U2Region> regions = ann->getRegions();
    if (regions.size() == 1) {
        annRegionString = regions.first().toString(U2Region::FormatDots);
    } else {
        annRegionString = "join(";
        foreach(const U2Region& region, regions) {
            annRegionString += region.toString(U2Region::FormatDots) + ",";
        }
        annRegionString.remove(annRegionString.size() - 1, 1);
        annRegionString += ")";
    }
    annRegionString.remove(" ");
    QVariantList annData = { ann->getName(), annRegionString };

    return annData;
}

QVariantList AssemblyAnnotationsTreeViewModel::getQualifierData(const U2Qualifier& qualifier) const {
    QVariantList qualifierData = { qualifier.name, qualifier.value };

    return qualifierData;
}

}