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

#include "ABSequenceObjectContext.h"
#include "AssemblyBrowser.h"
#include "annotations/tree_view/AssemblyAnnotationsTreeView.h"
#include "annotations/tree_view/AssemblyAnnotationsTreeViewModel.h"

#include <U2Core/U2SafePoints.h>

namespace U2 {

ABSequenceObjectContext::ABSequenceObjectContext(AssemblyBrowser* v, U2SequenceObject* obj)
    : SequenceObjectContext(obj, nullptr),
    browser(v) {
}

void ABSequenceObjectContext::connectStots() {
    CHECK(nullptr != browser, );

    AssemblyBrowserUi* ui = browser->getMainWidget();
    CHECK(nullptr != ui, );

    AssemblyAnnotationsTreeView* annTreeView = ui->getAnnotationsTreeView();
    SAFE_POINT(nullptr != annTreeView, "Assembly Annotation Tree View is missed", );

    connect(this, SIGNAL(si_annotationSelection(AnnotationSelectionData*)),
            annTreeView, SLOT(sl_annotationSelection(AnnotationSelectionData*)));

    connect(this, SIGNAL(si_clearSelectedAnnotationRegions()),
            annTreeView, SLOT(sl_clearSelectedAnnotations()));

    QAbstractItemModel* annTreeViewModel = annTreeView->model();
    SAFE_POINT(nullptr != annTreeViewModel, "Assembly Annotation Tree View Model is missed", );

    connect(this, SIGNAL(si_annotationObjectAdded(AnnotationTableObject*)),
            annTreeViewModel, SLOT(sl_annotationObjectAdded(AnnotationTableObject*)));
    connect(this, SIGNAL(si_annotationObjectRemoved(AnnotationTableObject*)),
            annTreeViewModel, SLOT(sl_annotationObjectRemoved(AnnotationTableObject*)));
}

} // namespace U2
