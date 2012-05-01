/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2012 UniPro <ugene@unipro.ru>
 * http://ugene.unipro.ru
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

#include "GTTestsFromProjectView.h"
#include "api/GTGlobals.h"
#include "api/GTKeyboardDriver.h"
#include "api/GTMouseDriver.h"
#include "api/GTMenu.h"
#include "GTUtilsProject.h"
#include "GTUtilsDocument.h"
#include "GTUtilsLog.h"
#include "GTUtilsApp.h"
#include "GTUtilsToolTip.h"
#include "GTUtilsDialog.h"
#include "GTUtilsMdi.h"
#include "GTUtilsProjectTreeView.h"
#include "GTUtilsTaskTreeView.h"
#include "GTUtilsSequenceView.h"
#include "api/GTSequenceReadingModeDialogUtils.h"
#include "api/GTTreeWidget.h"
#include "GTUtilsMdi.h"
#include <U2View/AnnotatedDNAViewFactory.h>
#include <U2View/MSAEditorFactory.h>
#include <api/GTFileDialog.h>


namespace U2{

namespace GUITest_common_scenarios_project_sequence_exporting_from_project_view {

GUI_TEST_CLASS_DEFINITION(test_0001) {
	GTUtilsProject::openFiles(os, testDir+"_common_data/scenarios/project/proj4.uprj");

	GTMouseDriver::moveTo(os, GTUtilsProjectTreeView::getItemCenter(os, "NC_001363 sequence"));
	GTMouseDriver::doubleClick(os);
	GTGlobals::sleep(1000);
	GTUtilsDialog::PopupChooser popupChooser(os, QStringList() << ACTION_PROJECT__EXPORT_MENU_ACTION << ACTION_EXPORT_SEQUENCE, GTGlobals::UseMouse);
	GTUtilsDialog::ExportSequenceOfSelectedAnnotationsFiller filler(os,
	testDir+"_common_data/scenarios/sandbox/exp.fasta",
	GTUtilsDialog::ExportSequenceOfSelectedAnnotationsFiller::Fasta,
	GTUtilsDialog::ExportSequenceOfSelectedAnnotationsFiller::SaveAsSeparate
	);
	GTUtilsDialog::preWaitForDialog(os, &popupChooser, GUIDialogWaiter::Popup);
	GTMouseDriver::click(os, Qt::RightButton);
	GTUtilsDialog::preWaitForDialog(os, &filler, GUIDialogWaiter::Modal);
	GTGlobals::sleep(10000);
	GTUtilsDocument::checkDocument(os, "exp.fasta");
}

GUI_TEST_CLASS_DEFINITION(test_0002) {
	GTUtilsProject::openFiles(os, testDir+"_common_data/scenarios/project/proj4.uprj");

	GTMouseDriver::moveTo(os, GTUtilsProjectTreeView::getItemCenter(os, "NC_001363 sequence"));
	GTMouseDriver::doubleClick(os);
	GTGlobals::sleep(1000);
	GTUtilsDialog::PopupChooser popupChooser(os, QStringList() << ACTION_PROJECT__EXPORT_MENU_ACTION << ACTION_EXPORT_SEQUENCE_AS_ALIGNMENT, GTGlobals::UseMouse);
	GTUtilsDialog::ExportSequenceAsAlignmentFiller filler(os,
		testDir+"_common_data/scenarios/sandbox/",
		"exp2.aln",
		GTUtilsDialog::ExportSequenceAsAlignmentFiller::Clustalw
	);
	GTUtilsDialog::preWaitForDialog(os, &popupChooser, GUIDialogWaiter::Popup);
	GTMouseDriver::click(os, Qt::RightButton);
	GTUtilsDialog::preWaitForDialog(os, &filler, GUIDialogWaiter::Modal);
	GTGlobals::sleep(10000);
	GTUtilsProject::openFiles(os, testDir+"_common_data/scenarios/sandbox/exp2.aln");
	GTUtilsDocument::checkDocument(os, "exp2.aln");
}


GUI_TEST_CLASS_DEFINITION(test_0003) {
	GTUtilsDialog::SequenceReadingModeSelectorDialogFiller dialog(os);
	GTUtilsDialog::preWaitForDialog(os, &dialog, GUIDialogWaiter::Modal);
	GTUtilsProject::openFiles(os, testDir + "_common_data/scenarios/project/multiple.fa");
	GTGlobals::sleep(1000);

	GTMouseDriver::moveTo(os, GTUtilsProjectTreeView::getItemCenter(os, "multiple.fa"));
	GTMouseDriver::click(os);
	GTGlobals::sleep(1000);
	GTKeyboardDriver::keyClick(os, 'a', GTKeyboardDriver::key["ctrl"]);
	GTGlobals::sleep(1000);
	GTUtilsDialog::PopupChooser popupChooser(os, QStringList() << ACTION_PROJECT__EXPORT_MENU_ACTION << ACTION_EXPORT_SEQUENCE_AS_ALIGNMENT, GTGlobals::UseMouse);
	GTUtilsDialog::ExportSequenceAsAlignmentFiller filler(os,
		testDir+"_common_data/scenarios/sandbox/",
		"exp2.aln",
		GTUtilsDialog::ExportSequenceAsAlignmentFiller::Clustalw,
		GTGlobals::UseMouse
		);
	GTUtilsDialog::preWaitForDialog(os, &popupChooser, GUIDialogWaiter::Popup);
	GTMouseDriver::click(os, Qt::RightButton);
	GTUtilsDialog::preWaitForDialog(os, &filler, GUIDialogWaiter::Modal);
	GTGlobals::sleep(10000);
	GTUtilsProject::openFiles(os, testDir+"_common_data/scenarios/sandbox/exp2.aln");
	GTUtilsDocument::checkDocument(os, "exp2.aln");
}

GUI_TEST_CLASS_DEFINITION(test_0004) {
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "HIV-1.aln");
    GTGlobals::sleep(1000);
    GTUtilsProject::exportToSequenceFormat(os, "HIV-1.aln", dataDir + " _common_data/scenarios/sandbox/", "export1.fa");
    GTGlobals::sleep(100);
    if (! GTUtilsDocument::getDocument(os, "export1.fa")) {
        GTFileDialog::openFile(os, dataDir + " _common_data/scenarios/sandbox/", "export1.fa");
    }

    QPoint itemPos = GTUtilsProjectTreeView::getItemCenter(os, "export1.fa");
    GTUtilsProjectTreeView::scrollTo(os, "ru131");


    GTKeyboardDriver::keyClick(os, 'w', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep(1000);

    itemPos = GTUtilsProjectTreeView::getItemCenter(os, "ru131");
    GTMouseDriver::moveTo(os, itemPos);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep(1000);

    QWidget *activeWindow =  GTUtilsMdi::activeWindow(os);
    if (! activeWindow->windowTitle().contains("ru131") && !os.hasError()) {
        os.setError("fasta file with sequences has been not opened");
    }

    QString sequence = GTUtilsSequenceView::getEndOfSequenceAsString(os, 1);
    if (sequence.at(0) != '-' && !os.hasError()) {
        os.setError("sequence [s] ru131 has not NOT'-' symbols at the end of sequence");
    }
}

GUI_TEST_CLASS_DEFINITION(test_0006) {
    const QString doc1("1.gb"), doc2("2.gb");

    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/project/", "proj4.uprj");
    GTGlobals::sleep(1000);

    QTreeWidgetItem *item1 = GTUtilsProjectTreeView::findItem(os, doc1);
    QTreeWidgetItem *item2 = GTUtilsProjectTreeView::findItem(os, doc2);
    if (item1 == NULL || item2 == NULL) {
        os.setError("Project view with document \"1.gb\" and \"2.gb\" is not opened");
        return;
    }

    if (GTUtilsDocument::isDocumentLoaded(os, doc1) || GTUtilsDocument::isDocumentLoaded(os, doc2)) {
        os.setError("Documents is not unload");
        return;
    }

    GTUtilsApp::checkUGENETitle(os, "proj4 UGENE");

    QTreeWidget *w = GTUtilsProjectTreeView::getTreeWidget(os);
    QTreeWidgetItem *item = GTUtilsProjectTreeView::findItem(os, "NC_001363 features");

    GTTreeWidget::expand(os, item);
    GTGlobals::sleep(100);
    QPoint itemPos = GTUtilsProjectTreeView::getItemCenter(os, "NC_001363 features");
    GTMouseDriver::moveTo(os, itemPos);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep(1000);

    GObjectViewWindow *activeWindow = qobject_cast<GObjectViewWindow*> (GTUtilsMdi::activeWindow(os));
    if (! activeWindow->getViewName().contains("NC_001363")) {
        os.setError("NC_001363 sequence has been not opened in sequence view");
        return;
    }

    GTUtilsProject::exportSequenceAsAlignment(os, "NC_001363 sequence", dataDir + "_common_data/scenarios/sandbox/",
                                              "exp2.msf", GTUtilsDialog::ExportSequenceAsAlignmentFiller::Msf);
    GTGlobals::sleep(100);

    GTFileDialog::openFile(os, dataDir + "_common_data/scenarios/sandbox/", "exp2.msf");
    GTGlobals::sleep(1000);

    if (GTUtilsProjectTreeView::getSelectedItem(os) != "NC_001363 sequence") {
        os.setError("multiple aligniment view with NC_001363 sequence has been not opened");
    }
}

} // namespace
} // namespace U2
