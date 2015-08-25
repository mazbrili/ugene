/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2015 UniPro <ugene@unipro.ru>
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

#include "GTTestsMsaEditor.h"
#include "api/GTAction.h"
#include "api/GTComboBox.h"
#include "api/GTMouseDriver.h"
#include "api/GTKeyboardDriver.h"
#include "api/GTMenu.h"
#include "api/GTFile.h"
#include "api/GTFileDialog.h"
#include "api/GTClipboard.h"
#include "api/GTToolbar.h"
#include "api/GTLineEdit.h"
#include "api/GTSpinBox.h"
#include "GTUtilsMdi.h"
#include "GTUtilsMsaEditorSequenceArea.h"
#include "GTUtilsProjectTreeView.h"
#include "GTUtilsLog.h"
#include "GTUtilsBookmarksTreeView.h"
#include "GTUtilsProject.h"
#include "GTUtilsTaskTreeView.h"
#include "GTUtilsOptionPanelMSA.h"
#include "runnables/qt/DefaultDialogFiller.h"
#include "runnables/qt/PopupChooser.h"
#include "runnables/qt/MessageBoxFiller.h"
#include "runnables/qt/FontDialogFiller.h"
#include "runnables/ugene/corelibs/U2Gui/PositionSelectorFiller.h"
#include "runnables/ugene/plugins/dna_export/ExportMSA2MSADialogFiller.h"
#include "runnables/ugene/plugins/dna_export/ExportSelectedSequenceFromAlignmentDialogFiller.h"
#include "runnables/ugene/plugins_3rdparty/kalign/KalignDialogFiller.h"
#include "runnables/ugene/plugins_3rdparty/umuscle/MuscleDialogFiller.h"
#include "runnables/ugene/corelibs/U2Gui/util/RenameSequenceFiller.h"
#include "runnables/ugene/corelibs/U2Gui/ExportDocumentDialogFiller.h"
#include "runnables/ugene/corelibs/U2Gui/ExportImageDialogFiller.h"
#include "runnables/ugene/corelibs/U2Gui/ProjectTreeItemSelectorDialogFiller.h"
#include "runnables/ugene/corelibs/U2Gui/RangeSelectionDialogFiller.h"
#include "runnables/ugene/corelibs/U2View/ov_msa/BuildTreeDialogFiller.h"
#include "runnables/ugene/corelibs/U2View/ov_msa/DeleteGapsDialogFiller.h"
#include "runnables/ugene/corelibs/U2View/ov_msa/DistanceMatrixDialogFiller.h"
#include "runnables/ugene/corelibs/U2View/ov_msa/ExportHighlightedDialogFiller.h"
#include "runnables/ugene/corelibs/U2View/ov_msa/GenerateAlignmentProfileDialogFiller.h"
#include "runnables/ugene/plugins/workflow_designer/WizardFiller.h"

#include <U2Gui/ToolsMenu.h>

#include <U2View/MSAEditor.h>
#include <U2View/MSAEditorNameList.h>
#include <U2View/ADVConstants.h>


namespace U2 {

namespace GUITest_common_scenarios_msa_editor {

GUI_TEST_CLASS_DEFINITION(test_0001) {

    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
    GTGlobals::sleep();

    int length = GTUtilsMSAEditorSequenceArea::getLength(os);
    CHECK_SET_ERR(length == 14, "Wrong length");

    int leftOffest = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(leftOffest == 1, "Wrong left offset");

    int rightOffest = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    CHECK_SET_ERR(rightOffest == 14, "Wrong right offset");
}

GUI_TEST_CLASS_DEFINITION(test_0001_1) {

    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma.aln");
    GTGlobals::sleep();

    int length = GTUtilsMSAEditorSequenceArea::getLength(os);
    CHECK_SET_ERR(length == 12, "Wrong length");

    int leftOffest = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(leftOffest == 1, "Wrong left offset");

    int rightOffest = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    CHECK_SET_ERR(rightOffest == 12, "Wrong right offset");
}

GUI_TEST_CLASS_DEFINITION(test_0001_2) {

    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gap_col.aln");
    GTGlobals::sleep();

    GTUtilsMdi::click(os, GTGlobals::Maximize);
    GTGlobals::sleep();

    int length = GTUtilsMSAEditorSequenceArea::getLength(os);
    CHECK_SET_ERR(length == 14, "Wrong length");

    int leftOffest = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(leftOffest == 1, "Wrong left offset");

    int rightOffest = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    CHECK_SET_ERR(rightOffest == 14, "Wrong right offset");
}

GUI_TEST_CLASS_DEFINITION(test_0001_3) {

    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "revcompl.aln");
    GTGlobals::sleep();

    GTUtilsMdi::click(os, GTGlobals::Minimize);
    GTGlobals::sleep();

    int length = GTUtilsMSAEditorSequenceArea::getLength(os);
    CHECK_SET_ERR(length == 6, "Wrong length");

    int leftOffest = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(leftOffest == 1, "Wrong left offset");

    int rightOffest = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    CHECK_SET_ERR(rightOffest == 6, "Wrong right offset");
}

GUI_TEST_CLASS_DEFINITION(test_0001_4) {

    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "translations_nucl.aln", GTFileDialog::Cancel);
    GTGlobals::sleep();
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "translations_nucl.aln", GTFileDialog::Open);
    GTGlobals::sleep();

    int length = GTUtilsMSAEditorSequenceArea::getLength(os);
    CHECK_SET_ERR(length == 3, "Wrong length");

    int leftOffest = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(leftOffest == 1, "Wrong left offset");

    int rightOffest = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    CHECK_SET_ERR(rightOffest == 3, "Wrong right offset");
}

GUI_TEST_CLASS_DEFINITION(test_0002) {

    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
    GTGlobals::sleep(1000);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "show_offsets"));

    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep();
    GTGlobals::sleep();

    bool offsetsVisible = GTUtilsMSAEditorSequenceArea::offsetsVisible(os);
    CHECK_SET_ERR(offsetsVisible == false, "Offsets are visible");


    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "show_offsets"));

    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep();
    GTGlobals::sleep();

    offsetsVisible = GTUtilsMSAEditorSequenceArea::offsetsVisible(os);
    CHECK_SET_ERR(offsetsVisible == true, "Offsets are not visible");

}

GUI_TEST_CLASS_DEFINITION(test_0002_1) {
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma.aln");
    GTGlobals::sleep(1000);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "show_offsets"));

    GTUtilsMdi::click(os, GTGlobals::Maximize);
    GTGlobals::sleep();

    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep();
    GTGlobals::sleep();

    bool offsetsVisible = GTUtilsMSAEditorSequenceArea::offsetsVisible(os);
    CHECK_SET_ERR(offsetsVisible == false, "Offsets are visible");


    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "show_offsets"));

    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep();
    GTGlobals::sleep();

    offsetsVisible = GTUtilsMSAEditorSequenceArea::offsetsVisible(os);
    CHECK_SET_ERR(offsetsVisible == true, "Offsets are not visible");
}

GUI_TEST_CLASS_DEFINITION(test_0002_2) {
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gap_col.aln");
    GTGlobals::sleep(1000);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "show_offsets"));

    GTUtilsMdi::click(os, GTGlobals::Maximize);
    GTGlobals::sleep();

    GTMenu::showMainMenu(os, MWMENU_ACTIONS);
    GTGlobals::sleep();
    GTGlobals::sleep();

    bool offsetsVisible = GTUtilsMSAEditorSequenceArea::offsetsVisible(os);
    CHECK_SET_ERR(offsetsVisible == false, "Offsets are visible");


    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "show_offsets"));

    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep();
    GTGlobals::sleep();

    offsetsVisible = GTUtilsMSAEditorSequenceArea::offsetsVisible(os);
    CHECK_SET_ERR(offsetsVisible == true, "Offsets are not visible");
}

GUI_TEST_CLASS_DEFINITION(test_0002_3) {
    GTUtilsMdi::click(os, GTGlobals::Close);
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "revcompl.aln");
    GTGlobals::sleep(1000);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "show_offsets"));

    QWidget *mdiWindow = GTUtilsMdi::activeWindow(os);
    CHECK_SET_ERR(mdiWindow != NULL, "MDI window == NULL");
    GTMenu::showMainMenu(os, MWMENU_ACTIONS);
    GTGlobals::sleep();
    GTGlobals::sleep();

    bool offsetsVisible = GTUtilsMSAEditorSequenceArea::offsetsVisible(os);
    CHECK_SET_ERR(offsetsVisible == false, "Offsets are visible");

    GTUtilsMdi::click(os, GTGlobals::Close);
    GTGlobals::sleep();

    mdiWindow = GTUtilsMdi::activeWindow(os, false);
    CHECK_SET_ERR(mdiWindow == NULL, "There is an MDI window");

    QPoint p = GTUtilsProjectTreeView::getItemCenter(os, "revcompl");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "show_offsets"));

    GTMenu::showMainMenu(os, MWMENU_ACTIONS);
    GTGlobals::sleep();
    GTGlobals::sleep();

    offsetsVisible = GTUtilsMSAEditorSequenceArea::offsetsVisible(os);
    CHECK_SET_ERR(offsetsVisible == true, "Offsets are not visible");
}

GUI_TEST_CLASS_DEFINITION(test_0002_4) {
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "revcompl.aln");
    GTGlobals::sleep(1000);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "show_offsets"));

    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep();
    GTGlobals::sleep();

    bool offsetsVisible = GTUtilsMSAEditorSequenceArea::offsetsVisible(os);
    CHECK_SET_ERR(offsetsVisible == false, "Offsets are visible");

    GTUtilsMdi::click(os, GTGlobals::Close);
    GTGlobals::sleep();

    QPoint p = GTUtilsProjectTreeView::getItemCenter(os, "revcompl");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    GTUtilsMdi::click(os, GTGlobals::Maximize);
    GTGlobals::sleep();

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "show_offsets"));

    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep();
    GTGlobals::sleep();

    offsetsVisible = GTUtilsMSAEditorSequenceArea::offsetsVisible(os);
    CHECK_SET_ERR(offsetsVisible == true, "Offsets are not visible");
}

GUI_TEST_CLASS_DEFINITION(test_0003) {
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
    GTGlobals::sleep();

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "action_sort_by_name"));
    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep();

    GTUtilsMSAEditorSequenceArea::checkSorted(os);
}

GUI_TEST_CLASS_DEFINITION(test_0003_1) {
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
    GTGlobals::sleep();

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "action_sort_by_name"));
    GTMenu::showMainMenu(os, MWMENU_ACTIONS);
    GTGlobals::sleep();

    GTUtilsMSAEditorSequenceArea::checkSorted(os);
}

GUI_TEST_CLASS_DEFINITION(test_0003_2) {
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "revcompl.aln");
    GTGlobals::sleep();

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "action_sort_by_name"));
    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep();

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "action_sort_by_name"));
    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep();

    GTUtilsMSAEditorSequenceArea::checkSorted(os);
}

GUI_TEST_CLASS_DEFINITION(test_0003_3) {
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gap_col.aln");
    GTGlobals::sleep();

    GTUtilsMSAEditorSequenceArea::checkSorted(os, false);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "action_sort_by_name"));
    GTMenu::showMainMenu(os, MWMENU_ACTIONS);
    GTGlobals::sleep();

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "show_offsets"));

    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep();
    GTGlobals::sleep();

    GTUtilsMdi::click(os, GTGlobals::Maximize);
    GTGlobals::sleep();

    GTUtilsMSAEditorSequenceArea::checkSorted(os);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "show_offsets"));
    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0003_4) {
    GTUtilsMdi::click(os, GTGlobals::Close);
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma.aln");
    GTGlobals::sleep();

    GTUtilsMSAEditorSequenceArea::checkSorted(os, false);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "action_sort_by_name"));
    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep();

    GTUtilsMdi::click(os, GTGlobals::Close);
    GTGlobals::sleep(1000);
#ifdef Q_OS_MAC
    GTMouseDriver::click(os);
    GTGlobals::sleep(1000);
#endif
    QWidget* mdiWindow = GTUtilsMdi::activeWindow(os, false);
    CHECK_SET_ERR(mdiWindow == NULL, "There is an MDI window");

    QPoint p = GTUtilsProjectTreeView::getItemCenter(os, "ma");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    GTUtilsMSAEditorSequenceArea::checkSorted(os);
}

GUI_TEST_CLASS_DEFINITION(test_0004)
{
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
    GTGlobals::sleep(1000);

    QWidget *mdiWindow = GTUtilsMdi::activeWindow(os);
    CHECK_SET_ERR(mdiWindow != NULL, "MDI window == NULL");

    GTUtilsDialog::waitForDialog(os, new GoToDialogFiller(os, 6));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "action_go_to_position"));

    GTMenu::showContextMenu(os, mdiWindow);
    GTGlobals::sleep();
    GTGlobals::sleep();

    QRect expectedRect(5, 0, 1, 1);
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, expectedRect);

    GTUtilsDialog::waitForDialog(os, new GoToDialogFiller(os, 6));
    GTKeyboardDriver::keyClick(os, 'g', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();

    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, expectedRect);
}

GUI_TEST_CLASS_DEFINITION(test_0004_1)
{
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
    GTGlobals::sleep(1000);

    QWidget *mdiWindow = GTUtilsMdi::activeWindow(os);
    CHECK_SET_ERR(mdiWindow != NULL, "MDI window == NULL");

    GTUtilsDialog::waitForDialog(os, new GoToDialogFiller(os, 6));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "action_go_to_position"));

    GTMenu::showContextMenu(os, mdiWindow);
    GTGlobals::sleep();
    GTGlobals::sleep();

    QRect expectedRect(5, 0, 1, 1);
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, expectedRect);

    GTUtilsDialog::waitForDialog(os, new GoToDialogFiller(os, 6));
    GTKeyboardDriver::keyClick(os, 'g', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();

    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, expectedRect);
}

GUI_TEST_CLASS_DEFINITION(test_0004_2)
{
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
    GTGlobals::sleep(1000);

    QWidget *mdiWindow = GTUtilsMdi::activeWindow(os);
    CHECK_SET_ERR(mdiWindow != NULL, "MDI window == NULL");

    GTUtilsDialog::waitForDialog(os, new GoToDialogFiller(os, 6));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "action_go_to_position"));

    GTMenu::showContextMenu(os, mdiWindow);
    GTGlobals::sleep();
    GTGlobals::sleep();

    QRect expectedRect(5, 0, 1, 1);
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, expectedRect);

    GTUtilsDialog::waitForDialog(os, new GoToDialogFiller(os, 6));
    GTKeyboardDriver::keyClick(os, 'g', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();

    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, expectedRect);
}

GUI_TEST_CLASS_DEFINITION(test_0005) {
// Check maligniment view status bar coordinates

// 1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");

// Expected state: Alignment length 14, left offset 1, right offset 14
    GTGlobals::sleep();
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getLength(os) == 14, "Wrong length");
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getLeftOffset(os) == 1, "Wrong left offset");
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getRightOffset(os) == 14, "Wrong right offset");

    QWidget *msaEditorStatusBar = GTWidget::findWidget(os, "msa_editor_status_bar");
    CHECK_SET_ERR(msaEditorStatusBar != NULL, "MSAEditorStatusBar is NULL");

    QLabel* line = qobject_cast<QLabel*>(GTWidget::findWidget(os, "Line", msaEditorStatusBar));
    CHECK_SET_ERR(line != NULL, "Line of MSAEditorStatusBar is NULL");
    QLabel* column = qobject_cast<QLabel*>(GTWidget::findWidget(os, "Column", msaEditorStatusBar));
    CHECK_SET_ERR(column != NULL, "Column of MSAEditorStatusBar is NULL");

// 2. Put cursor in 5th symbol for Tettigonia_virdissima sequence.
    GTUtilsMSAEditorSequenceArea::click(os, QPoint(4, 3));
// Expected state: coordinates in status bar Ln 4/10 Col 5/14
    CHECK_SET_ERR(line->text() == "Ln 4 / 10", "Line is " + line->text());
    CHECK_SET_ERR(column->text() == "Col 5 / 14", "Column is " + column->text());

// 3. Put cursor in 2nd symbol for Podisma_sapporensis sequence.
    GTUtilsMSAEditorSequenceArea::click(os, QPoint(1, 8));
// Expected state: coordinates in status bar Ln 9/10 Col 2/14
    CHECK_SET_ERR(line->text() == "Ln 9 / 10", "Line is " + line->text());
    CHECK_SET_ERR(column->text() == "Col 2 / 14", "Column is " + column->text());

// 4. Select area from 8th symbol for Tettigonia_virdissima sequence(top left corner) to 13th symbol for Podisma_sapporensis sequence.
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(7, 3), QPoint(12, 7));
// Expected state: coordinates in status bar Ln 4/10 Col 8/14
    CHECK_SET_ERR(line->text() == "Ln 4 / 10", "Line is " + line->text());
    CHECK_SET_ERR(column->text() == "Col 8 / 14", "Column is " + column->text());
}

GUI_TEST_CLASS_DEFINITION(test_0005_1) {
// Check maligniment view status bar coordinates

// 1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");

// Expected state: Alignment length 14, left offset 1, right offset 14
    GTGlobals::sleep();
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getLength(os) == 14, "Wrong length");
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getLeftOffset(os) == 1, "Wrong left offset");
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getRightOffset(os) == 14, "Wrong right offset");

    QWidget *msaEditorStatusBar = GTWidget::findWidget(os, "msa_editor_status_bar");
    CHECK_SET_ERR(msaEditorStatusBar != NULL, "MSAEditorStatusBar is NULL");

    QLabel* line = qobject_cast<QLabel*>(GTWidget::findWidget(os, "Line", msaEditorStatusBar));
    CHECK_SET_ERR(line != NULL, "Line of MSAEditorStatusBar is NULL");
    QLabel* column = qobject_cast<QLabel*>(GTWidget::findWidget(os, "Column", msaEditorStatusBar));
    CHECK_SET_ERR(column != NULL, "Column of MSAEditorStatusBar is NULL");

// CHANGES: click order changed
// 3. Put cursor in 2nd symbol for Podisma_sapporensis sequence.
    GTUtilsMSAEditorSequenceArea::click(os, QPoint(1, 8));
// Expected state: coordinates in status bar Ln 9/10 Col 2/14
    CHECK_SET_ERR(line->text() == "Ln 9 / 10", "Line is " + line->text());
    CHECK_SET_ERR(column->text() == "Col 2 / 14", "Column is " + column->text());

// 2. Put cursor in 5th symbol for Tettigonia_virdissima sequence.
    GTUtilsMSAEditorSequenceArea::click(os, QPoint(4, 3));
// Expected state: coordinates in status bar Ln 4/10 Col 5/14
    CHECK_SET_ERR(line->text() == "Ln 4 / 10", "Line is " + line->text());
    CHECK_SET_ERR(column->text() == "Col 5 / 14", "Column is " + column->text());

// 4. Select area from 8th symbol for Tettigonia_virdissima sequence(top left corner) to 13th symbol for Podisma_sapporensis sequence.
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(7, 3), QPoint(12, 7));
// Expected state: coordinates in status bar Ln 4/10 Col 8/14
    CHECK_SET_ERR(line->text() == "Ln 4 / 10", "Line is " + line->text());
    CHECK_SET_ERR(column->text() == "Col 8 / 14", "Column is " + column->text());
}

GUI_TEST_CLASS_DEFINITION(test_0005_2) {
// Check maligniment view status bar coordinates

// 1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");

// Expected state: Alignment length 14, left offset 1, right offset 14
    GTGlobals::sleep();
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getLength(os) == 14, "Wrong length");
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getLeftOffset(os) == 1, "Wrong left offset");
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getRightOffset(os) == 14, "Wrong right offset");

    QWidget *msaEditorStatusBar = GTWidget::findWidget(os, "msa_editor_status_bar");
    CHECK_SET_ERR(msaEditorStatusBar != NULL, "MSAEditorStatusBar is NULL");

    QLabel* line = qobject_cast<QLabel*>(GTWidget::findWidget(os, "Line", msaEditorStatusBar));
    CHECK_SET_ERR(line != NULL, "Line of MSAEditorStatusBar is NULL");
    QLabel* column = qobject_cast<QLabel*>(GTWidget::findWidget(os, "Column", msaEditorStatusBar));
    CHECK_SET_ERR(column != NULL, "Column of MSAEditorStatusBar is NULL");

// 2. Put cursor in 5th symbol for Tettigonia_virdissima sequence.
    GTUtilsMSAEditorSequenceArea::click(os, QPoint(4, 3));
// Expected state: coordinates in status bar Ln 4/10 Col 5/14
    CHECK_SET_ERR(line->text() == "Ln 4 / 10", "Line is " + line->text());
    CHECK_SET_ERR(column->text() == "Col 5 / 14", "Column is " + column->text());

// CHANGES: close and open MDI window, hide projectTreeView
    GTUtilsMdi::click(os, GTGlobals::Close);
    GTGlobals::sleep();

    GTMouseDriver::moveTo(os, GTUtilsProjectTreeView::getItemCenter(os, "ma2_gapped"));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    GTUtilsProjectTreeView::toggleView(os);
    GTGlobals::sleep();

    msaEditorStatusBar = GTWidget::findWidget(os, "msa_editor_status_bar");
    CHECK_SET_ERR(msaEditorStatusBar != NULL, "MSAEditorStatusBar is NULL");

    line = qobject_cast<QLabel*>(GTWidget::findWidget(os, "Line", msaEditorStatusBar));
    CHECK_SET_ERR(line != NULL, "Line of MSAEditorStatusBar is NULL");
    column = qobject_cast<QLabel*>(GTWidget::findWidget(os, "Column", msaEditorStatusBar));
    CHECK_SET_ERR(column != NULL, "Column of MSAEditorStatusBar is NULL");

// 3. Put cursor in 2nd symbol for Podisma_sapporensis sequence.
    GTUtilsMSAEditorSequenceArea::click(os, QPoint(1, 8));
// Expected state: coordinates in status bar Ln 9/10 Col 2/14
    CHECK_SET_ERR(line->text() == "Ln 9 / 10", "Line is " + line->text());
    CHECK_SET_ERR(column->text() == "Col 2 / 14", "Column is " + column->text());

// 4. Select area from 8th symbol for Tettigonia_virdissima sequence(top left corner) to 13th symbol for Podisma_sapporensis sequence.
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(7, 3), QPoint(12, 7));
// Expected state: coordinates in status bar Ln 4/10 Col 8/14
    CHECK_SET_ERR(line->text() == "Ln 4 / 10", "Line is " + line->text());
    CHECK_SET_ERR(column->text() == "Col 8 / 14", "Column is " + column->text());
}


GUI_TEST_CLASS_DEFINITION(test_0006) {
    // Check find from status bar

    // 1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");

    // Expected state: Aligniment length 14, left offset 1, right offset 14
    GTGlobals::sleep();
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getLength(os) == 14, "Wrong length");
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getLeftOffset(os) == 1, "Wrong left offset");
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getRightOffset(os) == 14, "Wrong right offset");

    QWidget *msaEditorStatusBar = GTWidget::findWidget(os, "msa_editor_status_bar");
    CHECK_SET_ERR(msaEditorStatusBar != NULL, "MSAEditorStatusBar is NULL");

    QLineEdit *searchEdit = qobject_cast<QLineEdit*>(GTWidget::findWidget(os, "searchEdit", msaEditorStatusBar));
    QWidget *findForward = GTWidget::findWidget(os, "Find forward", msaEditorStatusBar);
    QWidget *findBackward = GTWidget::findWidget(os, "Find backward", msaEditorStatusBar);

    // 2. Put AAGT in text field at status bar. Click Find next button.
    GTLineEdit::setText(os, searchEdit, "AAGT");
    GTWidget::click(os, findForward);
    // Expected state: find result sequence Tettigonia_viridissima region 1..4
    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 3, 4, 1));

    // 3. Click Find next button.
    GTWidget::click(os, findForward);
    // Expected state: find result sequence Mecopoda_elongata__Ishigaki__J region 1..4
    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 7, 4, 1));

    // 4. Click Find previous button.
    GTWidget::click(os, findBackward);
    // Expected state: find result sequence Tettigonia_viridissima region 1..4
    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 3, 4, 1));
}

GUI_TEST_CLASS_DEFINITION(test_0006_1) {
    // Check find from status bar

    // 1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");

    // Expected state: Aligniment length 14, left offset 1, right offset 14
    GTGlobals::sleep();
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getLength(os) == 14, "Wrong length");
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getLeftOffset(os) == 1, "Wrong left offset");
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getRightOffset(os) == 14, "Wrong right offset");

    QWidget *msaEditorStatusBar = GTWidget::findWidget(os, "msa_editor_status_bar");
    CHECK_SET_ERR(msaEditorStatusBar != NULL, "MSAEditorStatusBar is NULL");

    QLineEdit *searchEdit = qobject_cast<QLineEdit*>(GTWidget::findWidget(os, "searchEdit", msaEditorStatusBar));
    QWidget *findForward = GTWidget::findWidget(os, "Find forward", msaEditorStatusBar);
    QWidget *findBackward = GTWidget::findWidget(os, "Find backward", msaEditorStatusBar);

    // 2. Put AAGT in text field at status bar. Click Find next button.
    GTLineEdit::setText(os, searchEdit, "AAGT");
    GTWidget::click(os, findForward);
    // Expected state: find result sequence Tettigonia_viridissima region 1..4
    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 3, 4, 1));

    // 3. Click Find next button. CHANGES: click 3 times
    GTWidget::click(os, findForward);
    GTWidget::click(os, findForward);
    GTWidget::click(os, findForward);
    // Expected state: find result sequence Mecopoda_elongata__Ishigaki__J region 1..4
    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 7, 4, 1));

    // 4. Click Find previous button. CHANGES: click 3 times
    GTWidget::click(os, findBackward);
    GTWidget::click(os, findBackward);
    GTWidget::click(os, findBackward);
    // Expected state: find result sequence Tettigonia_viridissima region 1..4
    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 3, 4, 1));
}

GUI_TEST_CLASS_DEFINITION(test_0006_2) {
    // Check find from status bar

    // 1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");

    // Expected state: Aligniment length 14, left offset 1, right offset 14
    GTGlobals::sleep();
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getLength(os) == 14, "Wrong length");
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getLeftOffset(os) == 1, "Wrong left offset");
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getRightOffset(os) == 14, "Wrong right offset");

    QWidget *msaEditorStatusBar = GTWidget::findWidget(os, "msa_editor_status_bar");
    CHECK_SET_ERR(msaEditorStatusBar != NULL, "MSAEditorStatusBar is NULL");

    QLineEdit *searchEdit = qobject_cast<QLineEdit*>(GTWidget::findWidget(os, "searchEdit", msaEditorStatusBar));
    QWidget *findForward = GTWidget::findWidget(os, "Find forward", msaEditorStatusBar);
    QWidget *findBackward = GTWidget::findWidget(os, "Find backward", msaEditorStatusBar);

    // 2. Put AAGT in text field at status bar. Click Find next button.
    GTLineEdit::setText(os, searchEdit, "AAGT");
    GTWidget::click(os, findForward);
    // Expected state: find result sequence Tettigonia_viridissima region 1..4
    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 3, 4, 1));

    // CHANGES: clear search text, click Find forward and check that selection wasn't changed; set AAGT again
    GTLineEdit::setText(os, searchEdit, "");
    GTWidget::click(os, findForward);
    // Expected state: find result sequence Tettigonia_viridissima region 1..4
    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 3, 4, 1));
    GTLineEdit::setText(os, searchEdit, "AAGT");
    GTGlobals::sleep();

    // 3. Click Find next button.
    GTWidget::click(os, findForward);
    // Expected state: find result sequence Mecopoda_elongata__Ishigaki__J region 1..4
    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 7, 4, 1));

    // CHANGES: clear search text, click Find backward and check that selection wasn't changed; set AAGT again
    GTLineEdit::setText(os, searchEdit, "");
    GTWidget::click(os, findBackward);
    // Expected state: find result sequence Mecopoda_elongata__Ishigaki__J region 1..4
    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 7, 4, 1));
    GTLineEdit::setText(os, searchEdit, "AAGT");
    GTGlobals::sleep();

    // 4. Click Find previous button.
    GTWidget::click(os, findBackward);
    // Expected state: find result sequence Tettigonia_viridissima region 1..4
    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 3, 4, 1));
}

GUI_TEST_CLASS_DEFINITION(test_0007) {
    //1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
    GTGlobals::sleep(1000);

    QWidget *mdiWindow = GTUtilsMdi::activeWindow(os);
    CHECK_SET_ERR(mdiWindow != NULL, "MDI window == NULL");

    //Expected state: Aligniment length 14, left offset 1, right offset 14

    //2. Do double click on Tettigonia_viridissima sequence name.
    //Expected state: Rename dialog appears
    //3. Put "Sequence_a" into text field. Click OK.

    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "Sequence_a", "Tettigonia_viridissima"));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,3));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    //Expected state: Tettigonia_viridissima renamed to Sequence_a
    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "Sequence_a", "Sequence_a"));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,3));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    //4. Rlick Undo button.
    QAbstractButton *undo= GTAction::button(os,"msa_action_undo");
    GTWidget::click(os,undo);
    //GTKeyboardDriver::keyClick(os, 'z', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();

    //Expected state: Tettigonia_viridissima renamed back
    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "Tettigonia_viridissima", "Tettigonia_viridissima"));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,3));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0007_1) {
    //1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
    GTGlobals::sleep(1000);

    QWidget *mdiWindow = GTUtilsMdi::activeWindow(os);
    CHECK_SET_ERR(mdiWindow != NULL, "MDI window == NULL");

    //Expected state: Aligniment length 14, left offset 1, right offset 14

    //2. Do double click on Tettigonia_viridissima sequence name.
    //Expected state: Rename dialog appears
    //3. Put "Sequence_a" into text field. Click OK.

    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "Sequence_a", "Tettigonia_viridissima"));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,3));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    //Expected state: Tettigonia_viridissima renamed to Sequence_a

    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "Sequence_a", "Sequence_a"));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,3));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    //4. Rlick Undo button. CHANGES: clicking undo by mouse
    GTWidget::click(os, GTToolbar::getWidgetForActionName(os, GTToolbar::getToolbar(os, "mwtoolbar_activemdi"), "msa_action_undo"));
    GTGlobals::sleep();

    //Expected state: Tettigonia_viridissima renamed back
    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "Tettigonia_viridissima", "Tettigonia_viridissima"));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,3));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0007_2) {
    //1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
    GTGlobals::sleep(1000);

    QWidget *mdiWindow = GTUtilsMdi::activeWindow(os);
    CHECK_SET_ERR(mdiWindow != NULL, "MDI window == NULL");

    //Expected state: Aligniment length 14, left offset 1, right offset 14

    //2. Do double click on Tettigonia_viridissima sequence name. CHANGES: another sequence renamed
    //Expected state: Rename dialog appears
    //3. Put "Sequence_a" into text field. Click OK.

    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "Sequence_a", "Bicolorana_bicolor_EF540830"));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,2));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    //Expected state: Tettigonia_viridissima renamed to Sequence_a
    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "Sequence_a", "Sequence_a"));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,2));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    //4. Rlick Undo button.
    GTKeyboardDriver::keyClick(os, 'z', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();

    //Expected state: Tettigonia_viridissima renamed back
    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "Bicolorana_bicolor_EF540830", "Bicolorana_bicolor_EF540830"));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,2));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0007_3) {
    //1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
    GTGlobals::sleep(1000);

    QWidget *mdiWindow = GTUtilsMdi::activeWindow(os);
    CHECK_SET_ERR(mdiWindow != NULL, "MDI window == NULL");

    //Expected state: Aligniment length 14, left offset 1, right offset 14

    //2. Do double click on Tettigonia_viridissima sequence name. CHANGES: another sequence renamed
    //Expected state: Rename dialog appears
    //3. Put "Sequence_a" into text field. Click OK.

    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "Sequence_a", "Phaneroptera_falcata"));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,0));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    //Expected state: Tettigonia_viridissima renamed to Sequence_a
    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "Sequence_a", "Sequence_a"));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,0));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    //4. Rlick Undo button.
    GTKeyboardDriver::keyClick(os, 'z', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();

    //Expected state: Tettigonia_viridissima renamed back
    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "Phaneroptera_falcata", "Phaneroptera_falcata"));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,0));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0007_4) {
    //1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
    GTGlobals::sleep(1000);

    QWidget *mdiWindow = GTUtilsMdi::activeWindow(os);
    CHECK_SET_ERR(mdiWindow != NULL, "MDI window == NULL");

    //Expected state: Aligniment length 14, left offset 1, right offset 14

    //2. Do double click on Tettigonia_viridissima sequence name. CHANGES: another sequence renamed
    //Expected state: Rename dialog appears
    //3. Put "Sequence_a" into text field. Click OK.

    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "Sequence_a", "Conocephalus_sp."));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,5));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    //Expected state: Tettigonia_viridissima renamed to Sequence_a
    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "Sequence_a", "Sequence_a"));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,5));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    //4. Rlick Undo button.
    GTKeyboardDriver::keyClick(os, 'z', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();

    //Expected state: Tettigonia_viridissima renamed back
    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "Conocephalus_sp.", "Conocephalus_sp."));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,5));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0008) {

//     1. Open document samples\CLUSTALW\COI.aln

    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
    GTGlobals::sleep();

//     2. Create bookmark. Rename "New bookmark" to "start bookmark"
    QPoint p = GTUtilsBookmarksTreeView::getItemCenter(os, "COI [m] COI");
    GTMouseDriver::moveTo(os, p);
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ACTION_ADD_BOOKMARK, GTGlobals::UseMouse));
    GTMouseDriver::click(os, Qt::RightButton);
    GTGlobals::sleep();

    GTKeyboardDriver::keyClick(os, 'a', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keySequence(os, "start bookmark");
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["enter"]);
    GTGlobals::sleep();

    int startRO = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    int startLO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);

//     3. Scroll msa to the middle.
    GTUtilsDialog::waitForDialog(os, new GoToDialogFiller(os, 300));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "action_go_to_position"));

    QWidget *mdiWindow = GTUtilsMdi::activeWindow(os);
    GTMenu::showContextMenu(os, mdiWindow);
    GTGlobals::sleep();

//     4. Create bookmark. Rename "New bookmark" to "middle bookmark"
    GTMouseDriver::moveTo(os, p);
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ACTION_ADD_BOOKMARK, GTGlobals::UseMouse));
    GTMouseDriver::click(os, Qt::RightButton);
    GTGlobals::sleep();

    GTKeyboardDriver::keyClick(os, 'a', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keySequence(os, "middle bookmark");
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["enter"]);
    GTGlobals::sleep();

    int midRO = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    int midLO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
//
//     5. Scroll msa to the end.
    GTUtilsDialog::waitForDialog(os, new GoToDialogFiller(os, 550));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "action_go_to_position"));

    GTMenu::showContextMenu(os, mdiWindow);
    GTGlobals::sleep();
//     6. Create bookmark. Rename "New bookmark" to "end bookmark"
    GTMouseDriver::moveTo(os, p);
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ACTION_ADD_BOOKMARK, GTGlobals::UseMouse));
    GTMouseDriver::click(os, Qt::RightButton);
    GTGlobals::sleep();

    GTKeyboardDriver::keyClick(os, 'a', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keySequence(os, "end bookmark");
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["enter"]);
    GTGlobals::sleep();

    int endRO = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    int endLO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);

//     Expected state: clicking on each bookmark will recall corresponding MSA position
    p = GTUtilsBookmarksTreeView::getItemCenter(os, "start bookmark");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    int RO = GTUtilsMSAEditorSequenceArea::getRightOffset(os), LO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(startRO == RO && startLO == LO, "start bookmark offsets doesnt equal");

    p = GTUtilsBookmarksTreeView::getItemCenter(os, "middle bookmark");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    RO = GTUtilsMSAEditorSequenceArea::getRightOffset(os), LO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(midRO == RO && midLO == LO, "mid bookmark offsets doesnt equal");

    p = GTUtilsBookmarksTreeView::getItemCenter(os, "end bookmark");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    RO = GTUtilsMSAEditorSequenceArea::getRightOffset(os), LO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(endRO == RO && endLO == LO, "end bookmark offsets doesnt equal");

//     7. Delete Start bookmark
    p = GTUtilsBookmarksTreeView::getItemCenter(os, "start bookmark");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::click(os);
    GTKeyboardDriver::keyClick(os,GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep(500);

//     Expected state: start bookmark doesn't present
    QTreeWidgetItem* start = GTUtilsBookmarksTreeView::findItem(os,"start bookmark", GTGlobals::FindOptions(false));
    CHECK_SET_ERR(start==NULL, "Start bookmark not deleted");
}

GUI_TEST_CLASS_DEFINITION(test_0008_1) {  //CHANGES: default names used

    //     1. Open document samples\CLUSTALW\COI.aln

    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
    GTGlobals::sleep();

    //     2. Create bookmark. Rename "New bookmark" to "start bookmark"
    QPoint p = GTUtilsBookmarksTreeView::getItemCenter(os, "COI [m] COI");
    GTMouseDriver::moveTo(os, p);
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ACTION_ADD_BOOKMARK, GTGlobals::UseMouse));
    GTMouseDriver::click(os, Qt::RightButton);
    GTGlobals::sleep();

    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["enter"]);
    GTGlobals::sleep();

    int startRO = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    int startLO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);

    //     3. Scroll msa to the middle.
    GTUtilsDialog::waitForDialog(os, new GoToDialogFiller(os, 300));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "action_go_to_position"));

    QWidget *mdiWindow = GTUtilsMdi::activeWindow(os);
    GTMenu::showContextMenu(os, mdiWindow);
    GTGlobals::sleep();

    //     4. Create bookmark. Rename "New bookmark" to "middle bookmark"
    GTMouseDriver::moveTo(os, p);
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ACTION_ADD_BOOKMARK, GTGlobals::UseMouse));
    GTMouseDriver::click(os, Qt::RightButton);
    GTGlobals::sleep();

    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["enter"]);
    GTGlobals::sleep();

    int midRO = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    int midLO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    //
    //     5. Scroll msa to the end.
    GTUtilsDialog::waitForDialog(os, new GoToDialogFiller(os, 550));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "action_go_to_position"));

    GTMenu::showContextMenu(os, mdiWindow);
    GTGlobals::sleep();
    //     6. Create bookmark. Rename "New bookmark" to "end bookmark"
    GTMouseDriver::moveTo(os, p);
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ACTION_ADD_BOOKMARK, GTGlobals::UseMouse));
    GTMouseDriver::click(os, Qt::RightButton);
    GTGlobals::sleep();

    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["enter"]);
    GTGlobals::sleep();

    int endRO = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    int endLO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);

    //     Expected state: clicking on each bookmark will recall corresponding MSA position
    p = GTUtilsBookmarksTreeView::getItemCenter(os, "New bookmark");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    int RO = GTUtilsMSAEditorSequenceArea::getRightOffset(os), LO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(startRO == RO && startLO == LO, "start bookmark offsets doesnt equal");

    p = GTUtilsBookmarksTreeView::getItemCenter(os, "New bookmark 2");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    RO = GTUtilsMSAEditorSequenceArea::getRightOffset(os), LO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(midRO == RO && midLO == LO, "mid bookmark offsets doesnt equal");

    p = GTUtilsBookmarksTreeView::getItemCenter(os, "New bookmark 3");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    RO = GTUtilsMSAEditorSequenceArea::getRightOffset(os), LO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(endRO == RO && endLO == LO, "end bookmark offsets doesnt equal");

//     7. Delete Start bookmark
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList()<<ACTION_REMOVE_BOOKMARK));
    p = GTUtilsBookmarksTreeView::getItemCenter(os, "New bookmark");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::click(os,Qt::RightButton);
    GTGlobals::sleep(500);

//     Expected state: start bookmark doesn't present
    QTreeWidgetItem* start = GTUtilsBookmarksTreeView::findItem(os,"New bookmark", GTGlobals::FindOptions(false));
    CHECK_SET_ERR(start==NULL, "bookmark not deleted");
}

GUI_TEST_CLASS_DEFINITION(test_0008_2) { //CHANGES: mid and end coordinates changed

    //     1. Open document samples\CLUSTALW\COI.aln

    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
    GTGlobals::sleep();

    //     2. Create bookmark. Rename "New bookmark" to "start bookmark"
    QPoint p = GTUtilsBookmarksTreeView::getItemCenter(os, "COI [m] COI");
    GTMouseDriver::moveTo(os, p);
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ACTION_ADD_BOOKMARK, GTGlobals::UseMouse));
    GTMouseDriver::click(os, Qt::RightButton);
    GTGlobals::sleep();

    GTKeyboardDriver::keyClick(os, 'a', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keySequence(os, "start bookmark");
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["enter"]);
    GTGlobals::sleep();

    int startRO = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    int startLO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);

    //     3. Scroll msa to the middle.
    GTUtilsDialog::waitForDialog(os, new GoToDialogFiller(os, 200));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "action_go_to_position"));

    QWidget *mdiWindow = GTUtilsMdi::activeWindow(os);
    GTMenu::showContextMenu(os, mdiWindow);
    GTGlobals::sleep();

    //     4. Create bookmark. Rename "New bookmark" to "middle bookmark"
    GTMouseDriver::moveTo(os, p);
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ACTION_ADD_BOOKMARK, GTGlobals::UseMouse));
    GTMouseDriver::click(os, Qt::RightButton);
    GTGlobals::sleep();

    GTKeyboardDriver::keyClick(os, 'a', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keySequence(os, "middle bookmark");
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["enter"]);
    GTGlobals::sleep();

    int midRO = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    int midLO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    //
    //     5. Scroll msa to the end.
    GTUtilsDialog::waitForDialog(os, new GoToDialogFiller(os, 510));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "action_go_to_position"));

    GTMenu::showContextMenu(os, mdiWindow);
    GTGlobals::sleep();
    //     6. Create bookmark. Rename "New bookmark" to "end bookmark"
    GTMouseDriver::moveTo(os, p);
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ACTION_ADD_BOOKMARK, GTGlobals::UseMouse));
    GTMouseDriver::click(os, Qt::RightButton);
    GTGlobals::sleep();

    GTKeyboardDriver::keyClick(os, 'a', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keySequence(os, "end bookmark");
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["enter"]);
    GTGlobals::sleep();

    int endRO = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    int endLO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);

    //     Expected state: clicking on each bookmark will recall corresponding MSA position
    p = GTUtilsBookmarksTreeView::getItemCenter(os, "start bookmark");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    int RO = GTUtilsMSAEditorSequenceArea::getRightOffset(os), LO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(startRO == RO && startLO == LO, "start bookmark offsets doesnt equal");

    p = GTUtilsBookmarksTreeView::getItemCenter(os, "middle bookmark");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    RO = GTUtilsMSAEditorSequenceArea::getRightOffset(os), LO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(midRO == RO && midLO == LO, "mid bookmark offsets doesnt equal");

    p = GTUtilsBookmarksTreeView::getItemCenter(os, "end bookmark");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    RO = GTUtilsMSAEditorSequenceArea::getRightOffset(os), LO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(endRO == RO && endLO == LO, "end bookmark offsets doesnt equal");
}

GUI_TEST_CLASS_DEFINITION(test_0008_3) { //CHANGES: mid and end coordinates changed, used another file

    //     1. Open document samples\CLUSTALW\COI.aln

    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "HIV-1.aln");
    GTGlobals::sleep();

    //     2. Create bookmark. Rename "New bookmark" to "start bookmark"
    QPoint p = GTUtilsBookmarksTreeView::getItemCenter(os, "HIV-1 [m] HIV-1");
    GTMouseDriver::moveTo(os, p);
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ACTION_ADD_BOOKMARK, GTGlobals::UseMouse));
    GTMouseDriver::click(os, Qt::RightButton);
    GTGlobals::sleep();

    GTKeyboardDriver::keyClick(os, 'a', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keySequence(os, "start bookmark");
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["enter"]);
    GTGlobals::sleep();

    int startRO = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    int startLO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);

    //     3. Scroll msa to the middle.
    GTUtilsDialog::waitForDialog(os, new GoToDialogFiller(os, 600));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "action_go_to_position"));

    QWidget *mdiWindow = GTUtilsMdi::activeWindow(os);
    GTMenu::showContextMenu(os, mdiWindow);
    GTGlobals::sleep();

    //     4. Create bookmark. Rename "New bookmark" to "middle bookmark"
    GTMouseDriver::moveTo(os, p);
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ACTION_ADD_BOOKMARK, GTGlobals::UseMouse));
    GTMouseDriver::click(os, Qt::RightButton);
    GTGlobals::sleep();

    GTKeyboardDriver::keyClick(os, 'a', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keySequence(os, "middle bookmark");
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["enter"]);
    GTGlobals::sleep();

    int midRO = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    int midLO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    //
    //     5. Scroll msa to the end.
    GTUtilsDialog::waitForDialog(os, new GoToDialogFiller(os, 1000));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "action_go_to_position"));

    GTMenu::showContextMenu(os, mdiWindow);
    GTGlobals::sleep();
    //     6. Create bookmark. Rename "New bookmark" to "end bookmark"
    GTMouseDriver::moveTo(os, p);
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << ACTION_ADD_BOOKMARK, GTGlobals::UseMouse));
    GTMouseDriver::click(os, Qt::RightButton);
    GTGlobals::sleep();

    GTKeyboardDriver::keyClick(os, 'a', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep();
    GTKeyboardDriver::keySequence(os, "end bookmark");
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["enter"]);
    GTGlobals::sleep();

    int endRO = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    int endLO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);

    //     Expected state: clicking on each bookmark will recall corresponding MSA position
    p = GTUtilsBookmarksTreeView::getItemCenter(os, "start bookmark");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    int RO = GTUtilsMSAEditorSequenceArea::getRightOffset(os), LO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(startRO == RO && startLO == LO, "start bookmark offsets doesnt equal");

    p = GTUtilsBookmarksTreeView::getItemCenter(os, "middle bookmark");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    RO = GTUtilsMSAEditorSequenceArea::getRightOffset(os), LO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(midRO == RO && midLO == LO, "mid bookmark offsets doesnt equal");

    p = GTUtilsBookmarksTreeView::getItemCenter(os, "end bookmark");
    GTMouseDriver::moveTo(os, p);
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    RO = GTUtilsMSAEditorSequenceArea::getRightOffset(os), LO = GTUtilsMSAEditorSequenceArea::getLeftOffset(os);
    CHECK_SET_ERR(endRO == RO && endLO == LO, "end bookmark offsets doesnt equal");
}

GUI_TEST_CLASS_DEFINITION(test_0009) {

    //1. Open ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "ma2_gapped.aln");
    GTGlobals::sleep();

    //2. Select a trailing region length=3 (all gaps) for Isophia_altiacaEF540820
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(11, 1), QPoint(13, 1));
    GTGlobals::sleep();

    //3. Do context menu {Align-> Align with MUSCLE}  use "column range"
    GTUtilsDialog::waitForDialog(os, new MuscleDialogFiller(os));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_ALIGN << "Align with muscle", GTGlobals::UseMouse));
    GTWidget::click(os, GTUtilsMdi::activeWindow(os), Qt::RightButton);
    GTGlobals::sleep();
    //GTGlobals::sleep();

    //Expected state: Column range = 12-14
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(11, 0), QPoint(13, 9));
    GTKeyboardDriver::keyClick(os, 'c', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();


    QString clipboardText = GTClipboard::text(os);
    QString expectedMSA = "TAA\n---\nTAA\nTAA\n---\n---\n---\nTAA\nTTA\n---";


    CHECK_SET_ERR(clipboardText == expectedMSA, "Clipboard string and expected MSA string differs\n"+clipboardText);

    GTGlobals::sleep();

    //4. Press Align
    //Expected state: After aligning with 'stable' option the order must not change
}

GUI_TEST_CLASS_DEFINITION(test_0009_1) {

    //1. Open ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "ma2_gapped.aln");
    GTGlobals::sleep();

    //2. Select a trailing region length=3 (all gaps) for Isophia_altiacaEF540820
    //CHANGES: selection from right to left
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(13, 1), QPoint(11, 1));
    GTGlobals::sleep();

    //3. Do context menu {Align-> Align with MUSCLE}  use "column range"
    GTUtilsDialog::waitForDialog(os, new MuscleDialogFiller(os));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_ALIGN << "Align with muscle", GTGlobals::UseMouse));
    GTWidget::click(os, GTUtilsMdi::activeWindow(os), Qt::RightButton);
    GTGlobals::sleep();
    //GTGlobals::sleep();

    //Expected state: Column range = 12-14
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(11, 0), QPoint(13, 9));
    GTKeyboardDriver::keyClick(os, 'c', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();

    QString clipboardText = GTClipboard::text(os);
    QString expectedMSA = "TAA\n---\nTAA\nTAA\n---\n---\n---\nTAA\nTTA\n---";

    CHECK_SET_ERR(clipboardText == expectedMSA, "Clipboard string and expected MSA string differs");

    GTGlobals::sleep();

    //4. Press Align
    //Expected state: After aligning with 'stable' option the order must not change
}

GUI_TEST_CLASS_DEFINITION(test_0009_2) {

    //1. Open ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "ma2_gapped.aln");
    GTGlobals::sleep();

    //2. Select a trailing region length=3 (all gaps) for Isophia_altiacaEF540820
    //CHANGES: another region selected
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(11, 4), QPoint(13, 4));
    GTGlobals::sleep();

    //3. Do context menu {Align-> Align with MUSCLE}  use "column range"
    GTUtilsDialog::waitForDialog(os, new MuscleDialogFiller(os));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_ALIGN << "Align with muscle", GTGlobals::UseMouse));
    GTWidget::click(os, GTUtilsMdi::activeWindow(os), Qt::RightButton);
    GTGlobals::sleep();
    //GTGlobals::sleep();

    //Expected state: Column range = 12-14
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(11, 0), QPoint(13, 9));
    GTKeyboardDriver::keyClick(os, 'c', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();

    QString clipboardText = GTClipboard::text(os);
    QString expectedMSA = "TAA\n---\nTAA\nTAA\n---\n---\n---\nTAA\nTTA\n---";

    CHECK_SET_ERR(clipboardText == expectedMSA, "Clipboard string and expected MSA string differs");

    GTGlobals::sleep();

    //4. Press Align
    //Expected state: After aligning with 'stable' option the order must not change
}

GUI_TEST_CLASS_DEFINITION(test_0010) {

// 1. Open file _common_data\scenarios\msa\translations_nucl.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "translations_nucl.aln");

// 2. Do document context menu {Export->Export aligniment to amino format}
// 3. Translate with default settings
    GTUtilsDialog::waitForDialog(os, new ExportMSA2MSADialogFiller(os));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "amino_translation_of_alignment_rows"));
    GTWidget::click(os, GTUtilsMdi::activeWindow(os), Qt::RightButton);
    GTGlobals::sleep();

    GTGlobals::sleep();

    GTUtilsMSAEditorSequenceArea::selectArea(os);
    GTGlobals::sleep();
// copy to clipboard
//    GTKeyboardDriver::keyClick(os, 'c', GTKeyboardDriver::key["ctrl"]);
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "MSAE_MENU_COPY" << "copy_selection"));
    GTMouseDriver::click(os, Qt::RightButton);
    GTGlobals::sleep();

// Expected state: every sequense name the same as it amino translation
    QString clipboardText = GTClipboard::text(os);
    QString expectedMSA = "L\nS\nD\nS\nP\nK";

    CHECK_SET_ERR(clipboardText == expectedMSA, clipboardText);

    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0010_1) {

// 1. Open file _common_data\scenarios\msa\translations_nucl.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "translations_nucl.aln");

// 2. Do document context menu {Export->Export aligniment to amino format}
// 3. Translate with default settings
    GTUtilsDialog::waitForDialog(os, new ExportMSA2MSADialogFiller(os));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "amino_translation_of_alignment_rows"));
    GTWidget::click(os, GTUtilsMdi::activeWindow(os), Qt::RightButton);
    GTGlobals::sleep();

    GTGlobals::sleep();

    GTUtilsMSAEditorSequenceArea::selectArea(os);
// copy to clipboard
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_COPY << "copy_selection"));
    GTMouseDriver::click(os, Qt::RightButton);

// Expected state: every sequense name the same as it amino translation
    QString clipboardText = GTClipboard::text(os);
    QString expectedMSA = "L\nS\nD\nS\nP\nK";

    CHECK_SET_ERR(clipboardText == expectedMSA, "Clipboard string and expected MSA string differs");

    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0010_2) {

// 1. Open file _common_data\scenarios\msa\translations_nucl.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "translations_nucl.aln");

// 2. Do document context menu {Export->Export aligniment to amino format}
// 3. Translate with default settings
    GTUtilsDialog::waitForDialog(os, new ExportMSA2MSADialogFiller(os));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "amino_translation_of_alignment_rows"));
    GTWidget::click(os, GTUtilsMdi::activeWindow(os), Qt::RightButton);
    GTGlobals::sleep();

    GTGlobals::sleep();

    GTUtilsMSAEditorSequenceArea::selectArea(os);
// copy to clipboard
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_COPY << "copy_selection"));
    GTMouseDriver::click(os, Qt::RightButton);

// Expected state: every sequense name the same as it amino translation
    QString clipboardText = GTClipboard::text(os);
    QString expectedMSA = "L\nS\nD\nS\nP\nK";
    CHECK_SET_ERR(clipboardText == expectedMSA, "Clipboard string and expected MSA string differs");

    QStringList nameList = GTUtilsMSAEditorSequenceArea::getNameList(os);
    QStringList expectedNameList = QStringList() << "L" << "S" << "D" << "S" << "P" << "K";

    CHECK_SET_ERR(nameList == expectedNameList, "name lists differ");

    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0011) {
// In-place reverse complement replace in MSA Editor (0002425)

// 1. Open file _common_data\scenarios\msa\translations_nucl.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "translations_nucl.aln");

// 2. Select first sequence and do context menu {Edit->Replace selected rows with reverce complement}
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EDIT << "replace_selected_rows_with_reverse-complement"));
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0, 0), QPoint(-1, 0));
    GTMouseDriver::click(os, Qt::RightButton);

// Expected state: sequence changed from TTG -> CAA
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, 'c', GTKeyboardDriver::key["ctrl"]);

    GTGlobals::sleep();
    QString clipboardText = GTClipboard::text(os);
    CHECK_SET_ERR(clipboardText == "CAA", "Clipboard string and expected MSA string differs");

//                 sequence name  changed from L -> L|revcompl
    QStringList nameList = GTUtilsMSAEditorSequenceArea::getNameList(os);
    CHECK_SET_ERR(nameList.size() >= 2, "nameList doesn't contain enough strings");
    CHECK_SET_ERR(nameList[0] == "L|revcompl", "There are no 'L|revcompl' in nameList");

// 3. Do step 2 again
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EDIT << "replace_selected_rows_with_reverse-complement"));
    GTMouseDriver::click(os, Qt::RightButton);

// Expected state: sequence changed from CAA -> TTG
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, 'c', GTKeyboardDriver::key["ctrl"]);

    GTGlobals::sleep();
    clipboardText = GTClipboard::text(os);
    CHECK_SET_ERR(clipboardText == "TTG", "Clipboard string and expected MSA string differs");

//                 sequence name changed from L|revcompl ->
    nameList = GTUtilsMSAEditorSequenceArea::getNameList(os);
    CHECK_SET_ERR(nameList.size() >= 2, "nameList doesn't contain enough strings");
    CHECK_SET_ERR(!nameList.contains("L|revcompl"), "There are 'L|revcompl' in nameList");

    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0011_1) {
// In-place reverse complement replace in MSA Editor (0002425)

// 1. Open file _common_data\scenarios\msa\translations_nucl.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "translations_nucl.aln");

// 2. Select first sequence and do context menu {Edit->Replace selected rows with reverce complement}
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EDIT << "replace_selected_rows_with_reverse-complement"));
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0, 0), QPoint(-1, 0));
    GTMouseDriver::click(os, Qt::RightButton);

// Expected state: sequence changed from TTG -> CAA
// CHANGES: copy by context menu
    GTGlobals::sleep();
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_COPY << "copy_selection"));
    GTMouseDriver::click(os, Qt::RightButton);

    GTGlobals::sleep();
    QString clipboardText = GTClipboard::text(os);
    CHECK_SET_ERR(clipboardText == "CAA", "Clipboard string and expected MSA string differs");

//                 sequence name  changed from L -> L|revcompl
    QStringList nameList = GTUtilsMSAEditorSequenceArea::getNameList(os);
    CHECK_SET_ERR(nameList.size() >= 2, "nameList doesn't contain enough strings");
    CHECK_SET_ERR(nameList[0] == "L|revcompl" , "There are no 'L|revcompl' in nameList");

// 3. Do step 2 again
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EDIT << "replace_selected_rows_with_reverse-complement"));
    GTMouseDriver::click(os, Qt::RightButton);

// Expected state: sequence changed from CAA -> TTG
    GTGlobals::sleep();
// CHANGES: copy by context menu
    GTGlobals::sleep();
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_COPY << "copy_selection"));
    GTMouseDriver::click(os, Qt::RightButton);

    GTGlobals::sleep();
    clipboardText = GTClipboard::text(os);
    CHECK_SET_ERR(clipboardText == "TTG", "Clipboard string and expected MSA string differs");

//                 sequence name changed from L|revcompl ->
    nameList = GTUtilsMSAEditorSequenceArea::getNameList(os);
    CHECK_SET_ERR(nameList.size() >= 2, "nameList doesn't contain enough strings");
    CHECK_SET_ERR(!nameList.contains("L|revcompl"), "There are 'L|revcompl' in nameList");

    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0011_2) {
// In-place reverse complement replace in MSA Editor (0002425)

// 1. Open file _common_data\scenarios\msa\translations_nucl.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "translations_nucl.aln");

// 2. Select first sequence and do context menu {Edit->Replace selected rows with reverce complement}
// CHANGES: using main menu
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EDIT << "replace_selected_rows_with_reverse-complement"));
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0, 0), QPoint(-1, 0));
    GTMenu::showMainMenu(os, MWMENU_ACTIONS);
    GTGlobals::sleep();
    //GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0, 0), QPoint(-1, 0));
// Expected state: sequence changed from TTG -> CAA
    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(0, 0));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_COPY << "copy_selection"));
    GTMouseDriver::click(os, Qt::RightButton);

    GTGlobals::sleep();
    QString clipboardText = GTClipboard::text(os);
    CHECK_SET_ERR(clipboardText == "CAA", "Clipboard string and expected MSA string differs"+clipboardText);

//                 sequence name  changed from L -> L|revcompl
    QStringList nameList = GTUtilsMSAEditorSequenceArea::getNameList(os);
    CHECK_SET_ERR(nameList.size() >= 2, "nameList doesn't contain enough strings");
    CHECK_SET_ERR(nameList[0] == "L|revcompl" , "There are no 'L|revcompl' in nameList");

// 3. Do step 2 again
// CHANGES: using main menu
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EDIT << "replace_selected_rows_with_reverse-complement"));
    GTMenu::showMainMenu(os, MWMENU_ACTIONS);
    GTGlobals::sleep();

// Expected state: sequence changed from CAA -> TTG
    //GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0, 0), QPoint(-1, 0));
    GTGlobals::sleep();
    GTKeyboardDriver::keyClick(os, 'c', GTKeyboardDriver::key["ctrl"]);

    GTGlobals::sleep();
    clipboardText = GTClipboard::text(os);
    CHECK_SET_ERR(clipboardText == "TTG", "Clipboard string and expected MSA string differs");

//                 sequence name changed from L|revcompl ->
    nameList = GTUtilsMSAEditorSequenceArea::getNameList(os);
    CHECK_SET_ERR(nameList.size() >= 2, "nameList doesn't contain enough strings");
    CHECK_SET_ERR(!nameList.contains("L|revcompl"), "There are 'L|revcompl' in nameList");

    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0012) {
// Add tests on alignment translation features (0002432)

// 1. Open file _common_data\scenarios\msa\revcompl.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "revcompl.aln");

// 2. Select all sequences and do context menu {Edit->Replace selected rows with reverce complement}
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EDIT << "replace_selected_rows_with_reverse-complement"));

    GTUtilsMSAEditorSequenceArea::selectArea(os);
    GTMouseDriver::click(os, Qt::RightButton);
    GTWidget::click(os,GTUtilsMdi::activeWindow(os));

// Expected state: result alignement must be
// CAA---
// --TGA-
// ---ATC

    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0, -1), QPoint(-1, 0));
// copy to clipboard

    GTKeyboardDriver::keyClick(os, 'c', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();

// Expected state: every sequense name the same as it amino translation
    QString clipboardText = GTClipboard::text(os);
    QString expectedMSA = "CAA---\n--TGA-\n---ATC";

    CHECK_SET_ERR(clipboardText == expectedMSA, "Clipboard string and expected MSA string differs");

    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0012_1) {
// Add tests on alignment translation features (0002432)

// 1. Open file _common_data\scenarios\msa\revcompl.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "revcompl.aln");

// 2. Select all sequences and do context menu {Edit->Replace selected rows with reverce complement}
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EDIT << "replace_selected_rows_with_reverse-complement"));

    GTUtilsMSAEditorSequenceArea::selectArea(os);
    GTMouseDriver::click(os, Qt::RightButton);
    GTWidget::click(os,GTUtilsMdi::activeWindow(os));

// Expected state: result alignement must be
// CAA---
// --TGA-
// ---ATC

    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0, -1), QPoint(-1, 0));
// copy to clipboard. CHANGES: copy by context menu
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_COPY << "copy_selection"));
    GTMouseDriver::click(os, Qt::RightButton);

// Expected state: every sequense name the same as it amino translation
    QString clipboardText = GTClipboard::text(os);
    QString expectedMSA = "CAA---\n--TGA-\n---ATC";

    CHECK_SET_ERR(clipboardText == expectedMSA, "Clipboard string and expected MSA string differs");

    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0012_2) {
// Add tests on alignment translation features (0002432)

// 1. Open file _common_data\scenarios\msa\revcompl.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "revcompl.aln");

// 2. Select all sequences and do context menu {Edit->Replace selected rows with reverce complement}
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EDIT << "replace_selected_rows_with_reverse-complement"));

    GTUtilsMSAEditorSequenceArea::selectArea(os);
    GTMouseDriver::click(os, Qt::RightButton);

// CHANGES: close and open MDI window
    GTUtilsMdi::click(os, GTGlobals::Close);
    GTGlobals::sleep();

    GTMouseDriver::moveTo(os, GTUtilsProjectTreeView::getItemCenter(os, "revcompl"));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

// Expected state: result alignement must be
// CAA---
// --TGA-
// ---ATC

    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0, -1), QPoint(-1, 0));
// copy to clipboard. CHANGES: copy by context menu
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_COPY << "copy_selection"));
    GTMouseDriver::click(os, Qt::RightButton);

// Expected state: every sequense name the same as it amino translation
    QString clipboardText = GTClipboard::text(os);
    QString expectedMSA = "CAA---\n--TGA-\n---ATC";

    CHECK_SET_ERR(clipboardText == expectedMSA, "Clipboard string and expected MSA string differs");

    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0013) {
// Kalign crashes on amino alignment that was generated from nucleotide alignment (0002658)

// 1. Open file data/samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");

// 2. Convert alignment to amino. Use context menu {Export->Amino translation of alignment rows}
    GTUtilsDialog::waitForDialog(os, new ExportMSA2MSADialogFiller(os));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "amino_translation_of_alignment_rows"));
    GTWidget::click(os, GTUtilsMdi::activeWindow(os), Qt::RightButton);
    GTGlobals::sleep();

    GTGlobals::sleep();

// 3. Open converted alignment. Use context menu {Align->Align with Kalign}
    GTUtilsDialog::waitForDialog(os, new KalignDialogFiller(os));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_ALIGN << "align_with_kalign"));
    GTWidget::click(os, GTUtilsMdi::activeWindow(os), Qt::RightButton);
    GTGlobals::sleep();
    GTGlobals::sleep();

// Expected state: UGENE not crash
    GTGlobals::sleep(5000);
}

GUI_TEST_CLASS_DEFINITION(test_0013_1) {

// Kalign crashes on amino alignment that was generated from nucleotide alignment (0002658)

// 1. Open file data/samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");

// 2. Convert alignment to amino. Use context menu {Export->Amino translation of alignment rows}
    GTUtilsDialog::waitForDialog(os, new ExportMSA2MSADialogFiller(os,-1,testDir + "_common_data/scenarios/sandbox/COI_transl.aln"));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "amino_translation_of_alignment_rows"));
    GTWidget::click(os, GTUtilsMdi::activeWindow(os), Qt::RightButton);
    GTGlobals::sleep();

    GTGlobals::sleep();

// CHANGES: close and open MDI window
    GTUtilsMdi::click(os, GTGlobals::Close);
    GTGlobals::sleep();

    GTMouseDriver::moveTo(os, GTUtilsProjectTreeView::getItemCenter(os, "COI_transl.aln"));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();


// 3. Open converted alignment. Use context menu {Align->Align with Kalign}
    GTUtilsDialog::waitForDialog(os, new KalignDialogFiller(os));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_ALIGN << "align_with_kalign"));
    GTWidget::click(os, GTUtilsMdi::activeWindow(os), Qt::RightButton);
    GTGlobals::sleep();
    GTGlobals::sleep();

// Expected state: UGENE not crash
    GTGlobals::sleep(5000);
}

GUI_TEST_CLASS_DEFINITION(test_0013_2) {
// Kalign crashes on amino alignment that was generated from nucleotide alignment (0002658)

// 1. Open file data/samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");

// 2. Convert alignment to amino. Use context menu {Export->Amino translation of alignment rows}
    GTUtilsDialog::waitForDialog(os, new ExportMSA2MSADialogFiller(os));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "amino_translation_of_alignment_rows"));
    GTWidget::click(os, GTUtilsMdi::activeWindow(os), Qt::RightButton);
    GTGlobals::sleep();

    GTGlobals::sleep();

// 3. Open converted alignment. Use context menu {Align->Align with Kalign}
    GTUtilsDialog::waitForDialog(os, new KalignDialogFiller(os));

// CHANGES: using main menu
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_ALIGN << "align_with_kalign"));
    GTMenu::showMainMenu(os, MWMENU_ACTIONS);
    GTGlobals::sleep();
    GTGlobals::sleep();

// Expected state: UGENE not crash
    GTGlobals::sleep(5000);
}

GUI_TEST_CLASS_DEFINITION(test_0014) {
// UGENE crashes in malignment editor after aligning (UGENE-6)

// 1. Do menu tools->multiple alignment->kalign, set input alignment "data/samples/CLUSTALW/COI.aln" and press Align button
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");

    GTUtilsDialog::waitForDialog(os, new KalignDialogFiller(os));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_ALIGN << "align_with_kalign"));
    GTWidget::click(os, GTUtilsMdi::activeWindow(os), Qt::RightButton);
    GTGlobals::sleep();
    GTGlobals::sleep();

// 2. after kalign finishes and msa opens insert gaps and click in alignment
    GTGlobals::sleep(5000);

    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(0, 0));
    GTMouseDriver::click(os);
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["space"]);
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["space"]);
    GTGlobals::sleep();

    GTMouseDriver::click(os);

// Expected state: UGENE not crash
    GTGlobals::sleep(5000);
}

GUI_TEST_CLASS_DEFINITION(test_0014_1) {
// UGENE crashes in malignment editor after aligning (UGENE-6)

// 1. Do menu tools->multiple alignment->kalign, set input alignment "data/samples/CLUSTALW/COI.aln" and press Align button
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");

    GTUtilsDialog::waitForDialog(os, new KalignDialogFiller(os));

// CHANGES: using main menu
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_ALIGN << "align_with_kalign"));
    GTMenu::showMainMenu(os, MWMENU_ACTIONS);
    GTGlobals::sleep();
    GTGlobals::sleep();

// 2. after kalign finishes and msa opens insert gaps and click in alignment
    GTGlobals::sleep(5000);

    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(0, 0));
    GTMouseDriver::click(os);
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["space"]);
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["space"]);
    GTGlobals::sleep();

    GTMouseDriver::click(os);

// Expected state: UGENE not crash
    GTGlobals::sleep(5000);
}

GUI_TEST_CLASS_DEFINITION(test_0014_2) {
// UGENE crashes in malignment editor after aligning (UGENE-6)

// 1. Do menu tools->multiple alignment->kalign, set input alignment "data/samples/CLUSTALW/COI.aln" and press Align button
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");

// CHANGES: close and open MDI window, close Project tree view
    GTUtilsMdi::click(os, GTGlobals::Close);
    GTGlobals::sleep();
    GTMouseDriver::moveTo(os, GTUtilsProjectTreeView::getItemCenter(os, "COI"));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();
    GTUtilsProjectTreeView::toggleView(os);
    GTGlobals::sleep();

    GTUtilsDialog::waitForDialog(os, new KalignDialogFiller(os));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_ALIGN << "align_with_kalign"));
    GTWidget::click(os, GTUtilsMdi::activeWindow(os), Qt::RightButton);
    GTGlobals::sleep();
    GTGlobals::sleep();

// 2. after kalign finishes and msa opens insert gaps and click in alignment
    GTGlobals::sleep(5000);

    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(0, 0));
    GTMouseDriver::click(os);
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["space"]);
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["space"]);
    GTGlobals::sleep();

    GTMouseDriver::click(os);

// Expected state: UGENE not crash
    GTGlobals::sleep(5000);
}

GUI_TEST_CLASS_DEFINITION(test_0015) {
// ugene crashes when removing document after kalign (UGENE-36)
//
// 1. create empty project
// 2. do menu {tools->multiple alignment->kalign}, set aligned document samples/CLUSTALW/COI.aln

    GTUtilsDialog::waitForDialog(os, new KalignDialogFiller(os));
    GTUtilsDialog::waitForDialog(os, new GTFileDialogUtils(os, dataDir + "samples/CLUSTALW/", "COI.aln"));
    GTMenu::clickMenuItemByName(os, GTMenu::showMainMenu(os, MWMENU_TOOLS), QStringList() << ToolsMenu::MALIGN_MENU << ToolsMenu::MALIGN_KALIGN);
    GTGlobals::sleep();

// 3. aligned document opens
    GTGlobals::sleep(5000);
    GTUtilsMdi::activeWindow(os);

// 4. select document in project and press del
    GTMouseDriver::moveTo(os, GTUtilsProjectTreeView::getItemCenter(os, "COI.aln"));
    GTMouseDriver::click(os);
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep();

// Expected state: UGENE not crash
    GTGlobals::sleep(5000);
}

GUI_TEST_CLASS_DEFINITION(test_0015_1) {
// ugene crashes when removing document after kalign (UGENE-36)
//
// 1. create empty project
// 2. do menu {tools->multiple alignment->kalign}, set aligned document samples/CLUSTALW/COI.aln

// CHANGES: opens file, Kalign by popup menu
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
    GTGlobals::sleep();

    GTUtilsDialog::waitForDialog(os, new KalignDialogFiller(os));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_ALIGN << "align_with_kalign"));
    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep();

// 3. aligned document opens
    GTGlobals::sleep(5000);
    GTUtilsMdi::activeWindow(os);

// 4. select document in project and press del
    GTMouseDriver::moveTo(os, GTUtilsProjectTreeView::getItemCenter(os, "COI.aln"));
    GTMouseDriver::click(os);
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep();

// Expected state: UGENE not crash
    GTGlobals::sleep(5000);
}

GUI_TEST_CLASS_DEFINITION(test_0015_2) {
// ugene crashes when removing document after kalign (UGENE-36)
//
// 1. create empty project
// 2. do menu {tools->multiple alignment->kalign}, set aligned document samples/CLUSTALW/COI.aln

    GTUtilsDialog::waitForDialog(os, new KalignDialogFiller(os));
    GTUtilsDialog::waitForDialog(os, new GTFileDialogUtils(os, dataDir + "samples/CLUSTALW/", "COI.aln"));
    GTMenu::clickMenuItemByName(os, GTMenu::showMainMenu(os, MWMENU_TOOLS), QStringList() <<  ToolsMenu::MALIGN_MENU << ToolsMenu::MALIGN_KALIGN);
    GTGlobals::sleep();

// 3. aligned document opens
    GTGlobals::sleep(5000);
    GTUtilsMdi::activeWindow(os);

// CHANGES: close MDI window
    GTUtilsMdi::click(os, GTGlobals::Close);
    GTGlobals::sleep();

// 4. select document in project and press del
    GTMouseDriver::moveTo(os, GTUtilsProjectTreeView::getItemCenter(os, "COI.aln"));
    GTMouseDriver::click(os);
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep();

// Expected state: UGENE not crash
    GTGlobals::sleep(5000);
}

GUI_TEST_CLASS_DEFINITION(test_0016) {

// 1. Run Ugene. Open file _common_data\scenarios\msa\ma2_gapped.aln
    GTFile::copy(os, testDir + "_common_data/scenarios/msa/ma2_gapped.aln", sandBoxDir + "ma2_gapped.aln");
    GTFile::copy(os, testDir + "_common_data/scenarios/msa/ma2_gapped_edited.aln", sandBoxDir + "ma2_gapped_edited.aln");
    GTFileDialog::openFile(os, sandBoxDir, "ma2_gapped.aln");
    GTGlobals::sleep();

// 2. Open same file in text editor. Change first 3 bases of 'Phaneroptera_falcata'
//    from 'AAG' to 'CTT' and save file.
//CHANGES: backup old file, copy changed file
//    GTFile::backup(os, testDir + "_common_data/scenarios/msa/ma2_gapped.aln");
    GTUtilsDialog::waitForDialog(os, new MessageBoxDialogFiller(os, QMessageBox::Yes));
    GTFile::copy(os, sandBoxDir + "ma2_gapped.aln", sandBoxDir + "ma2_gapped_old.aln");
    GTFile::copy(os, sandBoxDir + "ma2_gapped_edited.aln", sandBoxDir + "ma2_gapped.aln");

//    Expected state: Dialog suggesting to reload modified document has appeared.
// 3. Press 'Yes'.
    GTGlobals::sleep(10000);

//    Expected state: document was reloaded, view activated.
//    'Phaneroptera_falcata' starts with CTT.
    GTGlobals::sleep();
    GTUtilsMdi::activeWindow(os);

    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0, 0), QPoint(2, 0));
// copy to clipboard
//    GTKeyboardDriver::keyClick(os, 'c', GTKeyboardDriver::key["ctrl"]);
    GTUtilsDialog::waitForDialog(os,new PopupChooser(os,QStringList()<<MSAE_MENU_COPY<<"copy_selection"));
    GTMouseDriver::click(os,Qt::RightButton);
    GTGlobals::sleep();

    QString clipboardText = GTClipboard::text(os);
    CHECK_SET_ERR(clipboardText == "CTT", "MSA part differs from expected");
    GTGlobals::sleep(3000);
}

GUI_TEST_CLASS_DEFINITION(test_0016_1) {
// 1. Run Ugene. Open file _common_data\scenarios\msa\ma2_gapped.aln
    GTFile::copy(os, testDir + "_common_data/scenarios/msa/ma2_gapped.aln", sandBoxDir + "ma2_gapped.aln");
    GTFile::copy(os, testDir + "_common_data/scenarios/msa/ma2_gapped_edited.aln", sandBoxDir + "ma2_gapped_edited.aln");
    GTFileDialog::openFile(os, sandBoxDir, "ma2_gapped.aln");
    GTGlobals::sleep();

// CHANGES: insert gaps in the beginning
    GTUtilsMSAEditorSequenceArea::click(os, QPoint(0, 0));
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["space"]);
    GTGlobals::sleep(200);
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["space"]);
    GTGlobals::sleep(200);
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["space"]);
    GTGlobals::sleep();

// 2. Open same file in text editor. Change first 3 bases of 'Phaneroptera_falcata'
//    from 'AAG' to 'CTT' and save file.
//CHANGES: backup old file, copy changed file
    //GTFile::backup(os, testDir + "_common_data/scenarios/msa/ma2_gapped.aln");
    GTUtilsDialog::waitForDialog(os, new MessageBoxDialogFiller(os, QMessageBox::Yes));
    GTFile::copy(os, sandBoxDir + "ma2_gapped.aln", sandBoxDir + "ma2_gapped_old.aln");
    GTFile::copy(os, sandBoxDir + "ma2_gapped_edited.aln", sandBoxDir + "ma2_gapped.aln");
//    Expected state: Dialog suggesting to reload modified document has appeared.
// 3. Press 'Yes'.
    GTGlobals::sleep(10000);

//    Expected state: document was reloaded, view activated.
//    'Phaneroptera_falcata' starts with CTT.
    GTUtilsMdi::activeWindow(os);

    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0, 0), QPoint(2, 0));
    GTGlobals::sleep();
// copy to clipboard
    GTKeyboardDriver::keyClick(os, 'c', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();

    QString clipboardText = GTClipboard::text(os);

    CHECK_SET_ERR(clipboardText == "CTT", "MSA part differs from expected. Expected: CTT, actual: " + clipboardText);
    GTGlobals::sleep(3000);
}

GUI_TEST_CLASS_DEFINITION(test_0016_2) {
// 1. Run Ugene. Open file _common_data\scenarios\msa\ma2_gapped.aln
    GTFile::copy(os, testDir + "_common_data/scenarios/msa/ma2_gapped.aln", sandBoxDir + "ma2_gapped.aln");
    GTFile::copy(os, testDir + "_common_data/scenarios/msa/ma2_gapped_edited.aln", sandBoxDir + "ma2_gapped_edited.aln");
    GTFileDialog::openFile(os, sandBoxDir, "ma2_gapped.aln");
    GTGlobals::sleep();

// 2. Open same file in text editor. Change first 3 bases of 'Phaneroptera_falcata'
//    from 'AAG' to 'CTT' and save file.
//CHANGES: backup old file, copy changed file
    GTUtilsDialog::waitForDialog(os, new MessageBoxDialogFiller(os, QMessageBox::Yes));
    GTFile::copy(os, sandBoxDir + "ma2_gapped.aln", sandBoxDir + "ma2_gapped_old.aln");
    GTFile::copy(os, sandBoxDir + "ma2_gapped_edited.aln", sandBoxDir + "ma2_gapped.aln");

//    Expected state: Dialog suggesting to reload modified document has appeared.
// 3. Press 'Yes'.
    GTGlobals::sleep(10000);

//    Expected state: document was reloaded, view activated.
//    'Phaneroptera_falcata' starts with CTT.
    GTUtilsMdi::activeWindow(os);

    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0, 0), QPoint(2, 0));
// copy to clipboard
    GTKeyboardDriver::keyClick(os, 'c', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep();

    QString clipboardText = GTClipboard::text(os);
    CHECK_SET_ERR(clipboardText == "CTT", "MSA part differs from expected");

// CHANGES: select item in project tree view and press delete
    GTMouseDriver::moveTo(os, GTUtilsProjectTreeView::getItemCenter(os, "ma2_gapped.aln"));
    GTMouseDriver::click(os);
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
    GTGlobals::sleep(5000);
}

GUI_TEST_CLASS_DEFINITION(test_0017) {
// Add a molecule from project  (UGENE-288)
//
// 1. Open file data/samples/Genbank/murine.gb
    GTFileDialog::openFile(os, dataDir + "samples/Genbank/", "murine.gb");
    GTGlobals::sleep();

// 2. Open file data/samples/MSF/HMA.msf
    GTFileDialog::openFile(os, dataDir + "samples/MSF/", "HMA.msf");
    GTGlobals::sleep();

// 3. On MSA editor {Context Menu->Add->Sequence from current project}
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_LOAD << "Sequence from current project"));

// 4. Select item dialog appeared
// Expected state: loaded sequences present in list
    GTUtilsDialog::waitForDialog(os, new ProjectTreeItemSelectorDialogFiller(os, "murine.gb", "NC_001363"));

    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0017_1) {
// Add a molecule from project  (UGENE-288)
//
// 1. Open file data/samples/Genbank/murine.gb
    GTFileDialog::openFile(os, dataDir + "samples/Genbank/", "murine.gb");
    GTGlobals::sleep();

// 2. Open file data/samples/MSF/HMA.msf
    GTFileDialog::openFile(os, dataDir + "samples/MSF/", "HMA.msf");
    GTGlobals::sleep();

// 3. On MSA editor {Context Menu->Add->Sequence from current project}
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_LOAD << "Sequence from current project"));

// 4. Select item dialog appeared
// Expected state: loaded sequences present in list
    GTUtilsDialog::waitForDialog(os, new ProjectTreeItemSelectorDialogFiller(os, "murine.gb", "NC_001363"));

// CHANGES: using main menu instead of popup
    GTMenu::showMainMenu(os, MWMENU_ACTIONS);
    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0017_2) {
// Add a molecule from project  (UGENE-288)
//
// 1. Open file data/samples/Genbank/murine.gb
    GTFileDialog::openFile(os, dataDir + "samples/Genbank/", "murine.gb");
    GTGlobals::sleep();

// CHANGES: close MDI window of murine.gb
    GTUtilsMdi::click(os, GTGlobals::Close);
    GTGlobals::sleep();

// 2. Open file data/samples/MSF/HMA.msf
    GTFileDialog::openFile(os, dataDir + "samples/MSF/", "HMA.msf");
    GTGlobals::sleep();

// 3. On MSA editor {Context Menu->Add->Sequence from current project}
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_LOAD << "Sequence from current project"));

// 4. Select item dialog appeared
// Expected state: loaded sequences present in list
    GTUtilsDialog::waitForDialog(os, new ProjectTreeItemSelectorDialogFiller(os, "murine.gb", "NC_001363"));

// CHANGES: using main menu instead of popup
    GTMenu::showMainMenu(os, MWMENU_ACTIONS);
    GTGlobals::sleep();
}

GUI_TEST_CLASS_DEFINITION(test_0018) {
// Shifting sequences in the Alignment Editor (UGENE-238)
//
// 1. Open file data/samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");

// 2. Click on some row in sequence names area
    GTUtilsMSAEditorSequenceArea::click(os, QPoint(-10, 2));
// Expected state: row became selected
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 2, 604, 1));

// 3. Click & drag selected row in sequence names area
    QStringList list1 = GTUtilsMSAEditorSequenceArea::getNameList(os);
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(-10, 2), QPoint(-10, 3));
// Expected state: row order changes respectively
    QStringList list2 = GTUtilsMSAEditorSequenceArea::getNameList(os);
    CHECK_SET_ERR(list1 != list2, "Name list wasn't changed");

// 4. Click & drag on unselected area
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(-10, 0), QPoint(-9, 1));
// Expected state: multiple rows selected
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 0, 604, 2));

// 5. Click & drag selected block
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(-10, 0), QPoint(-9, 1));
// Expected state: whole selected block shifted
    QStringList list3 = GTUtilsMSAEditorSequenceArea::getNameList(os);
    CHECK_SET_ERR(list2 != list3, "Name list wasn't changed");

// 6. Click on some row in selected block
    GTUtilsMSAEditorSequenceArea::click(os, QPoint(-9, 1));
// Expected state: selection falls back to one row
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 1, 604, 1));
}

GUI_TEST_CLASS_DEFINITION(test_0018_1) {
// Shifting sequences in the Alignment Editor (UGENE-238)
//
// 1. Open file data/samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");

// 2. Click on some row in sequence names area
    GTUtilsMSAEditorSequenceArea::click(os, QPoint(-10, 2));
// Expected state: row became selected
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 2, 604, 1));

// 3. Click & drag selected row in sequence names area
    QStringList list1 = GTUtilsMSAEditorSequenceArea::getNameList(os);
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(-10, 2), QPoint(-10, 3));
// Expected state: row order changes respectively
    QStringList list2 = GTUtilsMSAEditorSequenceArea::getNameList(os);
    CHECK_SET_ERR(list1 != list2, "Name list wasn't changed");

// 4. Click & drag on unselected area
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(-10, 0), QPoint(-9, 1));
// Expected state: multiple rows selected
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 0, 604, 2));

// 5. Click & drag selected block
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(-10, 0), QPoint(-9, 1));
// Expected state: whole selected block shifted
    QStringList list3 = GTUtilsMSAEditorSequenceArea::getNameList(os);
    CHECK_SET_ERR(list2 != list3, "Name list wasn't changed");

// 6. Click on some row in selected block
    GTUtilsMSAEditorSequenceArea::click(os, QPoint(-9, 1));
// Expected state: selection falls back to one row
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 1, 604, 1));
}

GUI_TEST_CLASS_DEFINITION(test_0018_2) {
// Shifting sequences in the Alignment Editor (UGENE-238)
//
// 1. Open file data/samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");

// 2. Click on some row in sequence names area
    GTUtilsMSAEditorSequenceArea::click(os, QPoint(-10, 2));
// Expected state: row became selected
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 2, 604, 1));

// 3. Click & drag selected row in sequence names area
    QStringList list1 = GTUtilsMSAEditorSequenceArea::getNameList(os);
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(-10, 2), QPoint(-10, 3));
// Expected state: row order changes respectively
    QStringList list2 = GTUtilsMSAEditorSequenceArea::getNameList(os);
    CHECK_SET_ERR(list1 != list2, "Name list wasn't changed");

// 4. Click & drag on unselected area
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(-10, 0), QPoint(-9, 1));
// Expected state: multiple rows selected
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 0, 604, 2));

// 5. Click & drag selected block
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(-10, 0), QPoint(-9, 1));
// Expected state: whole selected block shifted
    QStringList list3 = GTUtilsMSAEditorSequenceArea::getNameList(os);
    CHECK_SET_ERR(list2 != list3, "Name list wasn't changed");

// 6. Click on some row in selected block
    GTUtilsMSAEditorSequenceArea::click(os, QPoint(-9, 1));
// Expected state: selection falls back to one row
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 1, 604, 1));
}

GUI_TEST_CLASS_DEFINITION(test_0019) {
// UGENE-79 In MSA editor support rows collapsing mode
//
// 1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");

    QStringList preList = GTUtilsMSAEditorSequenceArea::getVisibaleNames(os);
// 2. Press button Enable collapsing
    GTWidget::click(os, GTToolbar::getWidgetForActionName(os, GTToolbar::getToolbar(os, "mwtoolbar_activemdi"), "Enable collapsing"));

// Expected state: Mecopoda_elongata__Ishigaki__J and Mecopoda_elongata__Sumatra_ folded together
    QStringList postList = GTUtilsMSAEditorSequenceArea::getVisibaleNames(os);
    CHECK_SET_ERR(preList.size() == postList.size() + 1, "Name lists differs not by 1");
}

GUI_TEST_CLASS_DEFINITION(test_0019_1) {
// UGENE-79 In MSA editor support rows collapsing mode
//
// 1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");

    QStringList preList = GTUtilsMSAEditorSequenceArea::getVisibaleNames(os);
// 2. Press button Enable collapsing
    GTWidget::click(os, GTToolbar::getWidgetForActionName(os, GTToolbar::getToolbar(os, "mwtoolbar_activemdi"), "Enable collapsing"));

// Expected state: Mecopoda_elongata__Ishigaki__J and Mecopoda_elongata__Sumatra_ folded together
    QStringList postList = GTUtilsMSAEditorSequenceArea::getVisibaleNames(os);
    CHECK_SET_ERR(preList.size() == postList.size() + 1, "Name lists differs not by 1");
}

GUI_TEST_CLASS_DEFINITION(test_0019_2) {
// UGENE-79 In MSA editor support rows collapsing mode
//
// 1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");

    QStringList preList = GTUtilsMSAEditorSequenceArea::getVisibaleNames(os);
// 2. Press button Enable collapsing
    GTWidget::click(os, GTToolbar::getWidgetForActionName(os, GTToolbar::getToolbar(os, "mwtoolbar_activemdi"), "Enable collapsing"));

// Expected state: Mecopoda_elongata__Ishigaki__J and Mecopoda_elongata__Sumatra_ folded together
    QStringList postList = GTUtilsMSAEditorSequenceArea::getVisibaleNames(os);
    CHECK_SET_ERR(preList.size() == postList.size() + 1, "Name lists differs not by 1");
}

GUI_TEST_CLASS_DEFINITION(test_0020) {
// UGENE crashes when all columns in MSAEditor are deleted (UGENE-329)
//
// 1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "ma2_gapped.aln");
// 2. Select Edit -> remove columns of gaps -> remove columns with number of gaps 1.
// 3. Click OK
    GTUtilsDialog::waitForDialog(os, new DeleteGapsDialogFiller(os));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "MSAE_MENU_EDIT" << "remove_columns_of_gaps"));
    GTMouseDriver::click(os, Qt::RightButton);

// Expected state: UGENE not crashes, deletion is not performed
    GTGlobals::sleep();
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0,0),QPoint(0,9));
    GTGlobals::sleep(500);
    GTKeyboardDriver::keyClick(os,'c',GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep(500);
    QString text = GTClipboard::text(os);
    QString expected = "A\nA\nT\nA\nT\nT\nT\nA\nA\nA";
    CHECK_SET_ERR(text == expected, "expected: " + expected + "found: " + text);
}

GUI_TEST_CLASS_DEFINITION(test_0020_1) {
// UGENE crashes when all columns in MSAEditor are deleted (UGENE-329)
//
// 1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/", "ma2_gapped.aln");

// 2. Insert some gaps to the first column. Ensure, that every column has a gap
    GTUtilsMSAEditorSequenceArea::click(os, QPoint(0, 0));
    GTGlobals::sleep();
    for (int i=0; i<6; i++) {
        GTKeyboardDriver::keyClick(os, ' ');
        GTGlobals::sleep(100);
    }
// 3. Select Edit -> remove columns of gaps -> remove columns with number of gaps 1.
    GTWidget::click(os,GTWidget::findWidget(os, "msa_editor_sequence_area"));
    GTUtilsMSAEditorSequenceArea::selectArea(os,QPoint(0,0),QPoint(19,9));
    GTKeyboardDriver::keyClick(os,'c',GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep(200);
    QString initial = GTClipboard::text(os);
// 4. Click OK
    GTUtilsDialog::waitForDialog(os, new DeleteGapsDialogFiller(os));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << "MSAE_MENU_EDIT" << "remove_columns_of_gaps"));
    GTMouseDriver::click(os, Qt::RightButton);

// Expected state: UGENE not crashes, deletion is not performed
    GTWidget::click(os,GTWidget::findWidget(os, "msa_editor_sequence_area"));
    GTGlobals::sleep(500);

    GTUtilsMSAEditorSequenceArea::selectArea(os,QPoint(0,0),QPoint(19,9));
    GTKeyboardDriver::keyClick(os,'c',GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep(200);
    QString final = GTClipboard::text(os);

    CHECK_SET_ERR(initial == final, "msa area was changed");
}

GUI_TEST_CLASS_DEFINITION(test_0021) {
// MSA editor zoom bug (UGENE-520)
//
// 1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
    GTGlobals::sleep();

// 2. zoom MSA to maximum
    for (int i=0; i<8; i++) {
        GTWidget::click(os, GTToolbar::getWidgetForActionName(os, GTToolbar::getToolbar(os, "mwtoolbar_activemdi"), "Zoom In"));
    }

// Expected state: top sequence not overlaps with ruler
    GTGlobals::sleep();

    for (int i=0; i<8; i++) {
        GTWidget::click(os, GTToolbar::getWidgetForActionName(os, GTToolbar::getToolbar(os, "mwtoolbar_activemdi"), "Zoom Out"));
    }
}

GUI_TEST_CLASS_DEFINITION(test_0021_1) {
// MSA editor zoom bug (UGENE-520)
//
// 1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
    GTGlobals::sleep();

// 2. zoom MSA to maximum
    for (int i=0; i<8; i++) {
        GTWidget::click(os, GTToolbar::getWidgetForActionName(os, GTToolbar::getToolbar(os, "mwtoolbar_activemdi"), "Zoom In"));
    }

// Expected state: top sequence not overlaps with ruler
    GTGlobals::sleep();

    for (int i=0; i<8; i++) {
        GTWidget::click(os, GTToolbar::getWidgetForActionName(os, GTToolbar::getToolbar(os, "mwtoolbar_activemdi"), "Zoom Out"));
    }
}

GUI_TEST_CLASS_DEFINITION(test_0021_2) {
// MSA editor zoom bug (UGENE-520)
//
// 1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
    GTGlobals::sleep();

// 2. zoom MSA to maximum
    for (int i=0; i<8; i++) {
        GTWidget::click(os, GTToolbar::getWidgetForActionName(os, GTToolbar::getToolbar(os, "mwtoolbar_activemdi"), "Zoom In"));
    }

// Expected state: top sequence not overlaps with ruler
    GTGlobals::sleep();

    for (int i=0; i<8; i++) {
        GTWidget::click(os, GTToolbar::getWidgetForActionName(os, GTToolbar::getToolbar(os, "mwtoolbar_activemdi"), "Zoom Out"));
    }
}

GUI_TEST_CLASS_DEFINITION(test_0022){
//1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//2. Select character â„–3 in "Phaneroptera_falcata"(G)
    GTUtilsMSAEditorSequenceArea::click(os,QPoint(2,0));
    QLabel* posLabel = qobject_cast<QLabel*>(GTWidget::findWidget(os,"Position"));
    CHECK_SET_ERR(posLabel, "Position label not found");
    CHECK_SET_ERR(posLabel->text()=="Pos 3 / 14", "Expected text: Pos 3/14. Found: " + posLabel->text());
//Expected state: Statistics "Pos" in right bottom is "Pos 3/14"

//3. Insert 3 gaps to first three positoons in "Phaneroptera_falcata"
    GTUtilsMSAEditorSequenceArea::click(os,QPoint(0,0));
    for(int i=0;i<3;i++){
        GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["space"]);
        GTGlobals::sleep(200);
    }
//4. Select char at 4 position in "Phaneroptera_falcata"(A)
    GTUtilsMSAEditorSequenceArea::click(os,QPoint(3,0));
    CHECK_SET_ERR(posLabel->text()=="Pos 1 / 14", "Expected text: Pos 1/14. Found: " + posLabel->text());
//Expected state: Gaps are inserted, statistics "Pos" in right bottom is "Pos 1/14"
}

GUI_TEST_CLASS_DEFINITION(test_0022_1){//DIFFERENCE: Column label is tested
//1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//2. Select character â„–3 in "Phaneroptera_falcata"(G)
    GTUtilsMSAEditorSequenceArea::click(os,QPoint(2,0));
    QLabel* colLabel = qobject_cast<QLabel*>(GTWidget::findWidget(os,"Column"));
    CHECK_SET_ERR(colLabel, "Column label not found");
    CHECK_SET_ERR(colLabel->text()=="Col 3 / 14", "Expected text: Col 3/14. Found: " + colLabel->text());
//Expected state: Statistics "Pos" in right bottom is "Pos 3/14"

//3. Insert 3 gaps to first three positoons in "Phaneroptera_falcata"
    GTUtilsMSAEditorSequenceArea::click(os,QPoint(0,0));
    for(int i=0;i<3;i++){
        GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["space"]);
        GTGlobals::sleep(200);
    }
//4. Select char at 4 position in "Phaneroptera_falcata"(A)
    GTUtilsMSAEditorSequenceArea::click(os,QPoint(3,0));
    CHECK_SET_ERR(colLabel->text()=="Col 4 / 17", "Expected text: Col 4 / 17. Found: " + colLabel->text());
//Expected state: Gaps are inserted, statistics "Pos" in right bottom is "Pos 1/14"
}

GUI_TEST_CLASS_DEFINITION(test_0022_2){//DIFFERENCE: Line label is tested
//1. Open document _common_data\scenarios\msa\ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//2. Select character â„–3 in "Phaneroptera_falcata"(G)
    GTUtilsMSAEditorSequenceArea::click(os,QPoint(2,0));
    QLabel* lineLabel = qobject_cast<QLabel*>(GTWidget::findWidget(os,"Line"));
    CHECK_SET_ERR(lineLabel, "Line label not found");
    CHECK_SET_ERR(lineLabel->text()=="Ln 1 / 10", "Expected text: Ln 1 / 10. Found: " + lineLabel->text());
//Expected state: Statistics "Pos" in right bottom is "Pos 3/14"

//3. Insert 3 gaps to first three positoons in "Phaneroptera_falcata"
    GTUtilsMSAEditorSequenceArea::selectArea(os,QPoint(-5,0),QPoint(-5,4));
    GTKeyboardDriver::keyClick(os,GTKeyboardDriver::key["delete"]);

//4. Select char at 4 position in "Phaneroptera_falcata"(A)
    GTUtilsMSAEditorSequenceArea::click(os,QPoint(3,0));
    CHECK_SET_ERR(lineLabel->text()=="Ln 1 / 5", "Expected text: Ln 1 / 5. Found: " + lineLabel->text());
//Expected state: Gaps are inserted, statistics "Pos" in right bottom is "Pos 1/14"
}

GUI_TEST_CLASS_DEFINITION(test_0023){
//    1. Open file data/samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
    GTGlobals::sleep(500);
//    2. Do context menu->Add->sequence from file
    GTFileDialogUtils *ob = new GTFileDialogUtils(os,dataDir + "samples/Genbank/", "CVU55762.gb");
    GTUtilsDialog::waitForDialog(os, ob);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList()<<MSAE_MENU_LOAD<<"Sequence from file"));
    GTMenu::showContextMenu(os,GTWidget::findWidget(os, "msa_editor_sequence_area"));
//    3. Select data/samples/GENBANK/CVU55762_new.fa
    GTUtilsDialog::waitForDialog(os, new RenameSequenceFiller(os, "CVU55762", "CVU55762"));
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(-10,18));
    GTMouseDriver::doubleClick(os);
//    Expected state: CVU55762 presents in list
}

GUI_TEST_CLASS_DEFINITION(test_0024){
//1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//2. select first symbol of first sequence
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(0,0));
    GTMouseDriver::click(os);
//3. press toolbar button "zoom to selection"
    int initOffset  = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    //offsets are used to check zooming
    QAbstractButton* zoom_to_sel = GTAction::button(os,"Zoom To Selection");
    GTWidget::click(os,zoom_to_sel);

    int finOffset  = GTUtilsMSAEditorSequenceArea::getRightOffset(os);
    CHECK_SET_ERR(initOffset>=(finOffset*2-8), "inital offset: " + QString().setNum(initOffset) + " final offset: " + QString().setNum(finOffset));
//Expected state: MSA is zoomed

//4. press toolbar button "Reset zoom"
    GTGlobals::sleep();
    QAbstractButton* reset_zoom = GTAction::button(os,"Reset Zoom");
    GTWidget::click(os,reset_zoom);
    GTGlobals::sleep(500);
    CHECK_SET_ERR(GTUtilsMSAEditorSequenceArea::getRightOffset(os)==initOffset, "MSA is not zoomed back");
//Expected state: MSA is zoomed back

}

// linux test
GUI_TEST_CLASS_DEFINITION(test_0025){
//    1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//    2. press "change font button" on toolbar
    GTUtilsDialog::waitForDialog(os, new FontDialogFiller(os));

    QAbstractButton* change_font = GTAction::button(os,"Change Font");
    GTWidget::click(os,change_font);
    GTGlobals::sleep(500);

    QWidget* nameListWidget = GTWidget::findWidget(os,"msa_editor_COI");
    MSAEditorUI* ui = qobject_cast<MSAEditorUI*>(nameListWidget);

    QFont f = ui->getEditor()->getFont();
    QString expectedFont = "Verdana,10,-1,5,50,0,0,0,0,0";

    CHECK_SET_ERR(f.toString() == expectedFont,"Expected: " + expectedFont + "found: " + f.toString())
    ;
//    Expected state: change font dialog appeared

//    3. choose some font, press OK
//    Expected state: font is changed
}

// windows test
GUI_TEST_CLASS_DEFINITION(test_0025_1){
//    1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//    2. press "change font button" on toolbar
    GTUtilsDialog::waitForDialog(os, new FontDialogFiller(os));

    QAbstractButton* change_font = GTAction::button(os,"Change Font");
    GTWidget::click(os,change_font);
    GTGlobals::sleep(500);

    QWidget* nameListWidget = GTWidget::findWidget(os,"msa_editor_COI");
    MSAEditorUI* ui = qobject_cast<MSAEditorUI*>(nameListWidget);

    QFont f = ui->getEditor()->getFont();
    QString expectedFont = "Verdana,10,-1,5,50,0,0,0,0,0";

    CHECK_SET_ERR(f.toString() == expectedFont,"Expected: " + expectedFont + "found: " + f.toString())
    ;
//    Expected state: change font dialog appeared

//    3. choose some font, press OK
//    Expected state: font is changed
}

GUI_TEST_CLASS_DEFINITION(test_0026){
//    1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//    2. press "export as image" on toolbar
    GTUtilsDialog::waitForDialog(os, new ExportImage(os,testDir + "_common_data/scenarios/sandbox/image.bmp"));
    GTUtilsDialog::waitForDialog(os, new MessageBoxDialogFiller(os, QMessageBox::Ok));

    QAbstractButton* saveImage = GTAction::button(os,"Export as image");
    CHECK_SET_ERR(saveImage, "Save as image button not found");

    GTWidget::click(os,saveImage);
//    Expected state: export dialog appeared

//    3. fill dialog:
//    file name: test/_common_data/scenarios/sandbox/image.bmp
//    press OK
    GTFileDialog::openFile(os,testDir + "_common_data/scenarios/sandbox/","image.bmp");
//    Expected state: image is exported
}

GUI_TEST_CLASS_DEFINITION(test_0026_1){//DIFFERENCE: context menu is used
//    1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//    2. press "export as image" on toolbar
    GTUtilsDialog::waitForDialog(os, new ExportImage(os,testDir + "_common_data/scenarios/sandbox/image.bmp"));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList()<<MSAE_MENU_EXPORT<<"Export as image"));
    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
//    Expected state: export dialog appeared

//    3. fill dialog:
//    file name: test/_common_data/scenarios/sandbox/image.bmp
//    press OK
//    Expected state: image is exported
}

GUI_TEST_CLASS_DEFINITION(test_0026_2_linux){
//    1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//    2. press "export as image" on toolbar
    GTUtilsDialog::waitForDialog(os, new ExportImage(os,testDir + "_common_data/scenarios/sandbox/bigImage.bmp", "jpeg" ,100));
    //GTUtilsDialog::waitForDialog(os, new MessageBoxDialogFiller(os, QMessageBox::Ok));

    QAbstractButton* saveImage = GTAction::button(os,"Export as image");
    CHECK_SET_ERR(saveImage, "Save as image button not found");

    GTWidget::click(os,saveImage);
//    Expected state: export dialog appeared
    GTUtilsDialog::waitForDialog(os, new ExportImage(os,testDir + "_common_data/scenarios/sandbox/smallImage.bmp","jpeg",50));
    GTWidget::click(os,saveImage);
    GTGlobals::sleep(500);
//    3. fill dialog:
//    file name: test/_common_data/scenarios/sandbox/image.bmp
//    press OK
    qint64 bigSize = GTFile::getSize(os,testDir + "_common_data/scenarios/sandbox/bigImage.jpeg");
    qint64 smallSize = GTFile::getSize(os,testDir + "_common_data/scenarios/sandbox/smallImage.jpeg");

    CHECK_SET_ERR(bigSize==5131839 && smallSize==1012686, QString().setNum(bigSize) + "  " + QString().setNum(smallSize));
//    Expected state: image is exported
}

GUI_TEST_CLASS_DEFINITION(test_0026_2_windows){
//    1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//    2. press "export as image" on toolbar
    GTUtilsDialog::waitForDialog(os, new ExportImage(os,testDir + "_common_data/scenarios/sandbox/bigImage.bmp","jpeg",100));
    //GTUtilsDialog::waitForDialog(os, new MessageBoxDialogFiller(os, QMessageBox::Ok));

    QAbstractButton* saveImage = GTAction::button(os,"Export as image");
    CHECK_SET_ERR(saveImage, "Save as image button not found");

    GTWidget::click(os,saveImage);
//    Expected state: export dialog appeared
    GTUtilsDialog::waitForDialog(os, new ExportImage(os,testDir + "_common_data/scenarios/sandbox/smallImage.bmp","jpeg",50));
    GTWidget::click(os,saveImage);
//    3. fill dialog:
//    file name: test/_common_data/scenarios/sandbox/image.bmp
//    press OK
    qint64 bigSize = GTFile::getSize(os,testDir + "_common_data/scenarios/sandbox/bigImage.jpeg");
    qint64 smallSize = GTFile::getSize(os,testDir + "_common_data/scenarios/sandbox/smallImage.jpeg");

    CHECK_SET_ERR(bigSize > 4000000 && bigSize < 5500000  && smallSize > 800000 && smallSize < 1500000, QString().setNum(bigSize) + "  " + QString().setNum(smallSize));
//    Expected state: image is exported
}

GUI_TEST_CLASS_DEFINITION(test_0027){
//    1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//    2. select element 4 in sequence 3
    GTUtilsMSAEditorSequenceArea::click(os,QPoint(3,2));
//    3. Move selected left using mouse by 6
    GTUtilsMSAEditorSequenceArea::selectArea(os,QPoint(3,2),QPoint(9,2));
    GTGlobals::sleep(500);

    GTUtilsMSAEditorSequenceArea::selectArea(os,QPoint(3,2),QPoint(8,2));
    GTKeyboardDriver::keyClick(os, 'c', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep(500);
    QString clipboardText = GTClipboard::text(os);
    CHECK_SET_ERR(clipboardText == "------", "Expected: ------ Found: " + clipboardText);
//    Expected stste: area is moved,position 4-9 filled with gaps
}

GUI_TEST_CLASS_DEFINITION(test_0027_1){
//    1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//    2. select element 4 in sequence 3
    GTUtilsMSAEditorSequenceArea::selectArea(os,QPoint(3,2),QPoint(3,3));
//    3. Move selected left using mouse by 6
    GTUtilsMSAEditorSequenceArea::selectArea(os,QPoint(3,2),QPoint(9,2));
    GTGlobals::sleep(500);

    GTUtilsMSAEditorSequenceArea::selectArea(os,QPoint(3,2),QPoint(8,3));
    GTKeyboardDriver::keyClick(os, 'c', GTKeyboardDriver::key["ctrl"]);
    GTGlobals::sleep(500);
    QString clipboardText = GTClipboard::text(os);
    CHECK_SET_ERR(clipboardText == "------\n------", "Expected: ------\n------ Found: " + clipboardText);
//    Expected stste: area is moved,position 4-9 filled with gaps
}

GUI_TEST_CLASS_DEFINITION(test_0028_linux){
//    1. Open document "samples/CLUSTALW/COI.aln"
    GTFileDialog::openFile( os, dataDir + "samples/CLUSTALW/", "COI.aln");

//    2. Context menu -- "Export as image"
    GTUtilsDialog::waitForDialog(os,new ExportMsaImage(os, testDir + "_common_data/scenarios/sandbox/test.svg", QString("svg")));
    GTUtilsDialog::waitForDialog( os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "Export as image"));
    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));

//    3. Fill dialog: svg format, output file
    qint64 fileSize = GTFile::getSize(os,testDir + "_common_data/scenarios/sandbox/test.svg");
    CHECK_SET_ERR(fileSize > 7600000 && fileSize < 8000000, "Current size: " + QString().setNum(fileSize));
//    Expected state:  SVG is exported
}

GUI_TEST_CLASS_DEFINITION(test_0028_windows){
//    1. Open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile( os, dataDir + "samples/CLUSTALW/", "COI.aln");

//    2. Context menu -- "Export as image"
    GTUtilsDialog::waitForDialog(os,new ExportMsaImage(os, testDir + "_common_data/scenarios/sandbox/test.svg", QString("svg")));
    GTUtilsDialog::waitForDialog( os, new PopupChooser( os, QStringList() << MSAE_MENU_EXPORT << "Export as image"));
    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));

//    3. Fill dialog: svg format, output file
    qint64 fileSize = GTFile::getSize(os,testDir + "_common_data/scenarios/sandbox/test.svg");
    CHECK_SET_ERR(fileSize > 7400000 && fileSize < 9800000, "Current size: " + QString().setNum(fileSize));
//    Expected state:  SVG is exported

}

GUI_TEST_CLASS_DEFINITION(test_0029){
    //    1. open document samples/CLUSTALW/COI.aln
        GTUtilsProject::openFiles(os, dataDir + "samples/CLUSTALW/COI.aln");
    //    2. Select first sequence
        GTUtilsMSAEditorSequenceArea::click(os,QPoint(0,0));
        GTUtilsDialog::waitForDialog(os, new PopupChooser(os,QStringList()<<MSAE_MENU_EXPORT<<"Save sequence",GTGlobals::UseMouse));
        Runnable* r = new ExportSelectedSequenceFromAlignment(os,testDir + "_common_data/scenarios/sandbox/export.fasta",ExportSelectedSequenceFromAlignment::FASTA,true);
        GTUtilsDialog::waitForDialog(os, r);

        GTMenu::showContextMenu(os,GTUtilsMdi::activeWindow(os));
        //GTMouseDriver::click(os,Qt::RightButton);

        GTMouseDriver::moveTo(os,GTUtilsProjectTreeView::getItemCenter(os,"export.fasta"));
        GTMouseDriver::moveTo(os,GTUtilsProjectTreeView::getItemCenter(os,"Phaneroptera_falcata"));
        GTGlobals::sleep();

        GTUtilsDialog::waitForDialog(os, new selectSequenceRegionDialogFiller(os,42,44));
        GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList()<<"Select"<< "Sequence region",GTGlobals::UseMouse));
        GTMenu::showContextMenu(os, GTWidget::findWidget(os,"ADV_single_sequence_widget_0"));

        GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList()<<ADV_MENU_COPY<< "Copy sequence",GTGlobals::UseMouse));
        GTMenu::showContextMenu(os, GTWidget::findWidget(os,"ADV_single_sequence_widget_0"));

        QString clipboardText = GTClipboard::text(os);
        CHECK_SET_ERR(clipboardText == "---", "Expected: TAGTTTATTAA, Found: " + clipboardText);
    //    3. use MSA area context menu->export->save sequence
    //    Exptcted state: Export sequence dialog appeared

    //    4. fill dialog:
    //    Export to file: test/_common_data/scenarios/sandbox/sequence.fa(use other extensions is branches)
    //    Add to project: checked
    //    Gap characters: keep
    //    Expectes state: sequence added to project
}

GUI_TEST_CLASS_DEFINITION(test_0029_1){//DIFFERENCE:gaps are trimmed, FASTQ format is used
//    1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//    2. Select first sequence
    GTUtilsMSAEditorSequenceArea::click(os,QPoint(0,2));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os,QStringList()<<MSAE_MENU_EXPORT<<"Save sequence",GTGlobals::UseMouse));
    Runnable* r = new ExportSelectedSequenceFromAlignment(os,testDir + "_common_data/scenarios/sandbox/export.fasta",ExportSelectedSequenceFromAlignment::FASTQ,false);
    GTUtilsDialog::waitForDialog(os, r);

    GTMouseDriver::click(os,Qt::RightButton);

    GTMouseDriver::moveTo(os,GTUtilsProjectTreeView::getItemCenter(os,"export.fastq"));
    GTMouseDriver::moveTo(os,GTUtilsProjectTreeView::getItemCenter(os,"Bicolorana_bicolor_EF540830"));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep();

    GTUtilsDialog::waitForDialog(os, new selectSequenceRegionDialogFiller(os));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList()<<"Select"<< "Sequence region",GTGlobals::UseMouse));
    GTMenu::showContextMenu(os, GTWidget::findWidget(os,"ADV_single_sequence_widget_0"));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList()<<ADV_MENU_COPY<< "Copy sequence",GTGlobals::UseMouse));
    GTMenu::showContextMenu(os, GTWidget::findWidget(os,"ADV_single_sequence_widget_0"));

    QString clipboardText = GTClipboard::text(os);
    CHECK_SET_ERR(clipboardText == "TAGTTTATTAA", "Expected: TAGTTTATTAA, Found: " + clipboardText);
//    3. use MSA area context menu->export->save sequence
//    Exptcted state: Export sequence dialog appeared

//    4. fill dialog:
//    Export to file: test/_common_data/scenarios/sandbox/sequence.fa(use other extensions is branches)
//    Add to project: checked
//    Gap characters: keep
//    Expectes state: sequence added to project
}

GUI_TEST_CLASS_DEFINITION(test_0029_2){
//    1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//    2. Select first sequence
    GTUtilsMSAEditorSequenceArea::click(os,QPoint(0,2));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os,QStringList()<<MSAE_MENU_EXPORT<<"Save sequence",GTGlobals::UseMouse));
    Runnable* r = new ExportSelectedSequenceFromAlignment(os,testDir + "_common_data/scenarios/sandbox/export.fasta",ExportSelectedSequenceFromAlignment::Genbank,true,false);
    GTUtilsDialog::waitForDialog(os, r);

    GTMouseDriver::click(os,Qt::RightButton);

    GTFileDialog::openFile(os,testDir + "_common_data/scenarios/sandbox/","export.gb");
//    3. use MSA area context menu->export->save sequence
//    Exptcted state: Export sequence dialog appeared

//    4. fill dialog:
//    Export to file: test/_common_data/scenarios/sandbox/sequence.fa(use other extensions is branches)
//    Add to project: checked
//    Gap characters: keep
//    Expectes state: sequence added to project
}

GUI_TEST_CLASS_DEFINITION(test_0031){//TODO: check statistic result
//    1. Open document test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//    2. Do MSA area context menu->Statistics->generate grid profile
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os,QStringList()<<MSAE_MENU_STATISTICS<<"Generate grid profile",GTGlobals::UseMouse));
    GTUtilsDialog::waitForDialog(os, new GenerateAlignmentProfileDialogFiller(os));
    GTMenu::showContextMenu(os,GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep(500);
//    Exptcted state: generate alignment profile dialog appeared

//    3. Fill dialog: Profile mode:Counts. Click "Generate"
    QWidget* profile = GTWidget::findWidget(os, "Alignment profile for ma2_gapped");
    CHECK_SET_ERR(profile, "Alignment profile widget not found");
//    Expected state: Alignment profile generated

}

GUI_TEST_CLASS_DEFINITION(test_0031_1){//DIFFERENCE: Percentage is used
//    1. Open document test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//    2. Do MSA area context menu->Statistics->generate grid profile
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os,QStringList()<<MSAE_MENU_STATISTICS<<"Generate grid profile",GTGlobals::UseMouse));
    GTUtilsDialog::waitForDialog(os, new GenerateAlignmentProfileDialogFiller(os,false));
    GTMenu::showContextMenu(os,GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep(500);
//    Exptcted state: generate alignment profile dialog appeared

//    3. Fill dialog: Profile mode:Counts. Click "Generate"
    QWidget* profile = GTWidget::findWidget(os, "Alignment profile for ma2_gapped");
    CHECK_SET_ERR(profile, "Alignment profile widget not found");
//    Expected state: Alignment profile generated

}

GUI_TEST_CLASS_DEFINITION(test_0031_2){//TODO: check statistic result
//    1. Open document test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//    2. Do MSA area context menu->Statistics->generate grid profile
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os,QStringList()<<MSAE_MENU_STATISTICS<<"Generate grid profile",GTGlobals::UseMouse));
    GTUtilsDialog::waitForDialog(os, new GenerateAlignmentProfileDialogFiller(os,true,false,false));
    GTMenu::showContextMenu(os,GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep(500);
//    Exptcted state: generate alignment profile dialog appeared

//    3. Fill dialog: Profile mode:Counts. Click "Generate"
    QWidget* profile = GTWidget::findWidget(os, "Alignment profile for ma2_gapped");
    CHECK_SET_ERR(profile, "Alignment profile widget not found");
//    Expected state: Alignment profile generated

}

GUI_TEST_CLASS_DEFINITION(test_0031_3){//TODO: check statistic result
//    1. Open document test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//    2. Do MSA area context menu->Statistics->generate grid profile
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os,QStringList()<<MSAE_MENU_STATISTICS<<"Generate grid profile",GTGlobals::UseMouse));
    GTUtilsDialog::waitForDialog(os, new GenerateAlignmentProfileDialogFiller(os,false,true,false));
    GTMenu::showContextMenu(os,GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep(500);
//    Exptcted state: generate alignment profile dialog appeared

//    3. Fill dialog: Profile mode:Counts. Click "Generate"
    QWidget* profile = GTWidget::findWidget(os, "Alignment profile for ma2_gapped");
    CHECK_SET_ERR(profile, "Alignment profile widget not found");
//    Expected state: Alignment profile generated

}

GUI_TEST_CLASS_DEFINITION(test_0031_4){//TODO: check statistic result
//    1. Open document test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//    2. Do MSA area context menu->Statistics->generate grid profile
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os,QStringList()<<MSAE_MENU_STATISTICS<<"Generate grid profile",GTGlobals::UseMouse));
    GTUtilsDialog::waitForDialog(os, new GenerateAlignmentProfileDialogFiller(os,false,false,true));
    GTMenu::showContextMenu(os,GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep(500);
//    Exptcted state: generate alignment profile dialog appeared

//    3. Fill dialog: Profile mode:Counts. Click "Generate"
    QWidget* profile = GTWidget::findWidget(os, "Alignment profile for ma2_gapped");
    CHECK_SET_ERR(profile, "Alignment profile widget not found");
//    Expected state: Alignment profile generated

}

GUI_TEST_CLASS_DEFINITION(test_0032){
//    1. Open document test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//    2. Do MSA area context menu->Statistics->generate grid profile
//    Exptcted state: generata alignment profile dialog appeared
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os,QStringList()<<MSAE_MENU_STATISTICS<<"Generate grid profile",GTGlobals::UseMouse));
    GTUtilsDialog::waitForDialog(os, new GenerateAlignmentProfileDialogFiller(os,true,GenerateAlignmentProfileDialogFiller::HTML,
                                                                              testDir + "_common_data/scenarios/sandbox/stat.html"));
    GTMenu::showContextMenu(os,GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep(500);

    qint64 size = 0;
    size = GTFile::getSize(os, testDir + "_common_data/scenarios/sandbox/stat.html");
    CHECK_SET_ERR(size > 0, "file not found");
//    3. Fill dialog: Profile mode:Counts
//            Save profile to file: checked
//            file path: test/_common_data/scenarios/sandbox/stat.html(stat.csv)
//            Click "Generate"
//    Expected state: Alignment profile file created
}

GUI_TEST_CLASS_DEFINITION(test_0032_1){//DIFFERENCE: csv format is used
//    1. Open document test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//    2. Do MSA area context menu->Statistics->generate grid profile
//    Exptcted state: generata alignment profile dialog appeared
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os,QStringList()<<MSAE_MENU_STATISTICS<<"Generate grid profile",GTGlobals::UseMouse));
    GTUtilsDialog::waitForDialog(os, new GenerateAlignmentProfileDialogFiller(os,true,GenerateAlignmentProfileDialogFiller::CSV,
                                                                              testDir + "_common_data/scenarios/sandbox/stat.html"));
    GTMenu::showContextMenu(os,GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep(500);

    qint64 size = 0;
    size = GTFile::getSize(os, testDir + "_common_data/scenarios/sandbox/stat.csv");
    CHECK_SET_ERR(size > 0, "file not found");
//    3. Fill dialog:Profile mode:Counts
//            Save profile to file: checked
//            file path: test/_common_data/scenarios/sandbox/stat.html(stat.csv)
//            Click "Generate"
//    Expected state: Alignment profile file created
}

GUI_TEST_CLASS_DEFINITION(test_0033){
//1. Open document test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//2. Do MSA area context menu->Statistics->generate distance matrix
    GTUtilsDialog::waitForDialog(os, new DistanceMatrixDialogFiller(os,true,true,true));
    Runnable* pop = new PopupChooser(os,QStringList()<<MSAE_MENU_STATISTICS<<"Generate distance matrix",GTGlobals::UseMouse);
    GTUtilsDialog::waitForDialog(os, pop);
    GTMenu::showContextMenu(os,GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep(500);
//Exptcted state: generata distance matrix dialog appeared

//3. Fill dialog: Distance Algorithm: Hamming dissimilarity(Simple similiraty)
//        Profile mode: Counts
//        Exclude gakls: checked
//        Click "Generate"
    QWidget* profile = GTWidget::findWidget(os, "Distance matrix for ma2_gapped");
    CHECK_SET_ERR(profile, "Alignment profile widget not found");
//Expected state: Alignment profile file created
}

GUI_TEST_CLASS_DEFINITION(test_0033_1){
//1. Open document test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//2. Do MSA area context menu->Statistics->generate distance matrix
    GTUtilsDialog::waitForDialog(os, new DistanceMatrixDialogFiller(os,false,true,true));
    Runnable* pop = new PopupChooser(os,QStringList()<<MSAE_MENU_STATISTICS<<"Generate distance matrix",GTGlobals::UseMouse);
    GTUtilsDialog::waitForDialog(os, pop);
    GTMenu::showContextMenu(os,GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep(500);
//Exptcted state: generata distance matrix dialog appeared

//3. Fill dialog: Distance Algorithm: Hamming dissimilarity(Simple similiraty)
//        Profile mode: Counts
//        Exclude gakls: checked
//        Click "Generate"
    QWidget* profile = GTWidget::findWidget(os, "Distance matrix for ma2_gapped");
    CHECK_SET_ERR(profile, "Alignment profile widget not found");
//Expected state: Alignment profile file created
}

GUI_TEST_CLASS_DEFINITION(test_0034){
//1. Open document test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//2. Do MSA area context menu->Statistics->generate distance matrix
    GTUtilsDialog::waitForDialog(os, new DistanceMatrixDialogFiller(os,true,false,true));
    Runnable* pop = new PopupChooser(os,QStringList()<<MSAE_MENU_STATISTICS<<"Generate distance matrix",GTGlobals::UseMouse);
    GTUtilsDialog::waitForDialog(os, pop);
    GTMenu::showContextMenu(os,GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep(500);
//Exptcted state: generata distance matrix dialog appeared

//3. Fill dialog: Distance Algorithm: Hamming dissimilarity
//        Profile mode: Counts(Percents)
//        Exclude gakls: checked(unchecked)
//        Click "Generate"
    QWidget* profile = GTWidget::findWidget(os, "Distance matrix for ma2_gapped");
    CHECK_SET_ERR(profile, "Alignment profile widget not found");
//Expected state: Alignment profile file created

}

GUI_TEST_CLASS_DEFINITION(test_0034_1){
//1. Open document test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//2. Do MSA area context menu->Statistics->generate distance matrix
    GTUtilsDialog::waitForDialog(os, new DistanceMatrixDialogFiller(os,true,true,false));
    Runnable* pop = new PopupChooser(os,QStringList()<<MSAE_MENU_STATISTICS<<"Generate distance matrix",GTGlobals::UseMouse);
    GTUtilsDialog::waitForDialog(os, pop);
    GTMenu::showContextMenu(os,GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep(500);
//Exptcted state: generata distance matrix dialog appeared

//3. Fill dialog: Distance Algorithm: Hamming dissimilarity
//        Profile mode: Counts(Percents)
//        Exclude gakls: checked(unchecked)
//        Click "Generate"
    QWidget* profile = GTWidget::findWidget(os, "Distance matrix for ma2_gapped");
    CHECK_SET_ERR(profile, "Alignment profile widget not found");
//Expected state: Alignment profile file created

}

GUI_TEST_CLASS_DEFINITION(test_0035){
//1. Open document test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/" , "ma2_gapped.aln");
//2. Do MSA area context menu->Statistics->generate distance matrix
    Runnable* dis = new DistanceMatrixDialogFiller(os,DistanceMatrixDialogFiller::HTML,testDir + "_common_data/scenarios/sandbox/matrix.html");
    GTUtilsDialog::waitForDialog(os, dis);
    Runnable* pop = new PopupChooser(os,QStringList()<<MSAE_MENU_STATISTICS<<"Generate distance matrix",GTGlobals::UseMouse);
    GTUtilsDialog::waitForDialog(os, pop);
    GTMenu::showContextMenu(os,GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep(500);
//Exptcted state: generata distance matrix dialog appeared

//3. Fill dialog: Distance Algorithm: Hamming dissimilarity
//        Profile mode: Counts
//        Exclude gakls: checked
//        Save profile to file: checked
//        File path: test/_common_data/scenarios/sandbox/matrix.html(matrix.csv)
//        Click "Generate"
    qint64 size = GTFile::getSize(os,testDir + "_common_data/scenarios/sandbox/matrix.html");
    CHECK_SET_ERR(size!=0,"file not created");
//Expected state: Alignment profile file created
}

GUI_TEST_CLASS_DEFINITION(test_0035_1){
//1. Open document test/_common_data/scenarios/msa/ma2_gapped.aln
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa/","ma2_gapped.aln");
//2. Do MSA area context menu->Statistics->generate distance matrix
    Runnable* dis = new DistanceMatrixDialogFiller(os,DistanceMatrixDialogFiller::CSV,testDir + "_common_data/scenarios/sandbox/matrix.html");
    GTUtilsDialog::waitForDialog(os, dis);
    Runnable* pop = new PopupChooser(os,QStringList()<<MSAE_MENU_STATISTICS<<"Generate distance matrix",GTGlobals::UseMouse);
    GTUtilsDialog::waitForDialog(os, pop);
    GTMenu::showContextMenu(os,GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep(500);
//Exptcted state: generata distance matrix dialog appeared

//3. Fill dialog: Distance Algorithm: Hamming dissimilarity
//        Profile mode: Counts
//        Exclude gakls: checked
//        Save profile to file: checked
//        File path: test/_common_data/scenarios/sandbox/matrix.html(matrix.csv)
//        Click "Generate"
    qint64 size = GTFile::getSize(os,testDir + "_common_data/scenarios/sandbox/matrix.csv");
    CHECK_SET_ERR(size!=0,"file not created");
//Expected state: Alignment profile file created
}

GUI_TEST_CLASS_DEFINITION(test_0036){
//1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
    GTGlobals::sleep(500);
//2. Press "build tree" button on toolbar
    GTUtilsDialog::waitForDialog(os, new BuildTreeDialogFiller(os, testDir + "_common_data/scenarios/sandbox/COI.nwk",0));
    QAbstractButton *tree= GTAction::button(os,"Build Tree");
    GTWidget::click(os,tree);
    GTUtilsTaskTreeView::waitTaskFinished(os);
//Expected state: build tree dialog appeared

//3. Fill dialog:
//    Distanse matrix model: F84(Kimura/Jukes-Cantor/LogDet)
//    Press "Build"
    QGraphicsView* treeView = qobject_cast<QGraphicsView*>(GTWidget::findWidget(os, "treeView"));
    CHECK_SET_ERR(treeView!=NULL,"TreeView not found")
//Expected state: tree appeared
}

GUI_TEST_CLASS_DEFINITION(test_0036_1){
//1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
    GTGlobals::sleep(500);
//2. Press "build tree" button on toolbar
//Expected state: build tree dialog appeared
    //3. Fill dialog:
    //    Distanse matrix model: F84(Kimura/Jukes-Cantor/LogDet)
    //    Press "Build"
    GTUtilsDialog::waitForDialog(os, new BuildTreeDialogFiller(os, testDir + "_common_data/scenarios/sandbox/COI.nwk",1));
    QAbstractButton *tree= GTAction::button(os,"Build Tree");
    GTWidget::click(os,tree);

    GTUtilsTaskTreeView::waitTaskFinished(os);

//Expected state: tree appeared
    QGraphicsView* treeView = qobject_cast<QGraphicsView*>(GTWidget::findWidget(os, "treeView"));
    CHECK_SET_ERR(treeView!=NULL,"TreeView not found")
}

GUI_TEST_CLASS_DEFINITION(test_0036_2){
//1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
    GTGlobals::sleep(500);
//2. Press "build tree" button on toolbar
    GTUtilsDialog::waitForDialog(os, new BuildTreeDialogFiller(os, testDir + "_common_data/scenarios/sandbox/COI.nwk",2));
    QAbstractButton *tree= GTAction::button(os,"Build Tree");
    GTWidget::click(os,tree);
    GTGlobals::sleep(500);
//Expected state: build tree dialog appeared

//3. Fill dialog:
//    Distanse matrix model: F84(Kimura/Jukes-Cantor/LogDet)
//    Press "Build"
    QGraphicsView* treeView = qobject_cast<QGraphicsView*>(GTWidget::findWidget(os, "treeView"));
    CHECK_SET_ERR(treeView!=NULL,"TreeView not found")
//Expected state: tree appeared
}

GUI_TEST_CLASS_DEFINITION(test_0036_3){
//1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
    GTGlobals::sleep(500);
//2. Press "build tree" button on toolbar
    GTUtilsDialog::waitForDialog(os, new BuildTreeDialogFiller(os, testDir + "_common_data/scenarios/sandbox/COI.nwk",3));
    QAbstractButton *tree= GTAction::button(os,"Build Tree");
    GTWidget::click(os,tree);
    GTGlobals::sleep(500);
//Expected state: build tree dialog appeared

//3. Fill dialog:
//    Distanse matrix model: F84(Kimura/Jukes-Cantor/LogDet)
//    Press "Build"
    QGraphicsView* treeView = qobject_cast<QGraphicsView*>(GTWidget::findWidget(os, "treeView"));
    CHECK_SET_ERR(treeView!=NULL,"TreeView not found")
//Expected state: tree appeared
}

GUI_TEST_CLASS_DEFINITION(test_0037){
//1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//2. Press "build tree" button on toolbar
    GTUtilsDialog::waitForDialog(os, new BuildTreeDialogFiller(os, testDir + "_common_data/scenarios/sandbox/COI.nwk",0,0.5));
    QAbstractButton *tree= GTAction::button(os,"Build Tree");
    GTWidget::click(os,tree);
    GTGlobals::sleep(500);
//Expected state: build tree dialog appeared

//3. Fill dialog:
//    Distanse matrix model: F84
//    Gamma distributed rates across sites: checked
//    Coefficient of variation: 0.50(50.00/99.00)
//    Press "Build"
    QGraphicsView* treeView = qobject_cast<QGraphicsView*>(GTWidget::findWidget(os, "treeView"));
    CHECK_SET_ERR(treeView!=NULL,"TreeView not found")
//Expected state: tree appeared
}

GUI_TEST_CLASS_DEFINITION(test_0037_1){
//1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//2. Press "build tree" button on toolbar
    GTUtilsDialog::waitForDialog(os, new BuildTreeDialogFiller(os, testDir + "_common_data/scenarios/sandbox/COI.nwk",0,50));
    QAbstractButton *tree= GTAction::button(os,"Build Tree");
    GTWidget::click(os,tree);
    GTGlobals::sleep();
//Expected state: build tree dialog appeared

//3. Fill dialog:
//    Distanse matrix model: F84
//    Gamma distributed rates across sites: checked
//    Coefficient of variation: 0.50(50.00/99.00)
//    Press "Build"
    QGraphicsView* treeView = qobject_cast<QGraphicsView*>(GTWidget::findWidget(os, "treeView"));
    CHECK_SET_ERR(treeView!=NULL,"TreeView not found")
//Expected state: tree appeared
}

GUI_TEST_CLASS_DEFINITION(test_0037_2){
//1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//2. Press "build tree" button on toolbar
    GTUtilsDialog::waitForDialog(os, new BuildTreeDialogFiller(os, testDir + "_common_data/scenarios/sandbox/COI.nwk",0,99));
    QAbstractButton *tree= GTAction::button(os,"Build Tree");
    GTWidget::click(os,tree);
    GTGlobals::sleep();
//Expected state: build tree dialog appeared

//3. Fill dialog:
//    Distanse matrix model: F84
//    Gamma distributed rates across sites: checked
//    Coefficient of variation: 0.50(50.00/99.00)
//    Press "Build"
    QGraphicsView* treeView = qobject_cast<QGraphicsView*>(GTWidget::findWidget(os, "treeView"));
    CHECK_SET_ERR(treeView!=NULL,"TreeView not found")
//Expected state: tree appeared
}

GUI_TEST_CLASS_DEFINITION(test_0038){
//1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//2. Press "build tree" button on toolbar
    GTUtilsDialog::waitForDialog(os, new BuildTreeDialogFiller(os,100,testDir + "_common_data/scenarios/sandbox/COI.nwk",
                                                               5,BuildTreeDialogFiller::MAJORITYEXT));

    QAbstractButton *tree= GTAction::button(os,"Build Tree");
    GTWidget::click(os,tree);
    GTUtilsTaskTreeView::waitTaskFinished(os);//some time is needed to build tree
//Expected state: build tree dialog appeared

//3. Fill dialog:
//    Distanse matrix model: F84
//    Gamma distributed rates across sites: unchecked
//    Bootatraping and consensus tree: checked
//    Number of replications: 100
//    Seed: 5
//    Consensus type: Majority Rule extended(Strict/Majority Rule/M1)
//    Press "Build"
    QGraphicsView* treeView = qobject_cast<QGraphicsView*>(GTWidget::findWidget(os, "treeView"));
    CHECK_SET_ERR(treeView!=NULL,"TreeView not found")
//Expected state: tree appeared
}

GUI_TEST_CLASS_DEFINITION(test_0038_1){
//1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//2. Press "build tree" button on toolbar
    GTUtilsDialog::waitForDialog(os, new BuildTreeDialogFiller(os,100,testDir + "_common_data/scenarios/sandbox/COI.nwk",
                                                               5,BuildTreeDialogFiller::STRICTCONSENSUS));

    QAbstractButton *tree= GTAction::button(os,"Build Tree");
    GTWidget::click(os,tree);
    GTUtilsTaskTreeView::waitTaskFinished(os);//some time is needed to build tree
//Expected state: build tree dialog appeared

//3. Fill dialog:
//    Distanse matrix model: F84
//    Gamma distributed rates across sites: unchecked
//    Bootatraping and consensus tree: checked
//    Number of replications: 100
//    Seed: 5
//    Consensus type: Majority Rule extended(Strict/Majority Rule/M1)
//    Press "Build"
    QGraphicsView* treeView = qobject_cast<QGraphicsView*>(GTWidget::findWidget(os, "treeView"));
    CHECK_SET_ERR(treeView!=NULL,"TreeView not found")
//Expected state: tree appeared
}

GUI_TEST_CLASS_DEFINITION(test_0038_2){
//1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//2. Press "build tree" button on toolbar
    GTUtilsDialog::waitForDialog(os, new BuildTreeDialogFiller(os,100,testDir + "_common_data/scenarios/sandbox/COI.nwk",
                                                               5,BuildTreeDialogFiller::MAJORITY));

    QAbstractButton *tree= GTAction::button(os,"Build Tree");
    GTWidget::click(os,tree);
//Expected state: build tree dialog appeared

//3. Fill dialog:
//    Distanse matrix model: F84
//    Gamma distributed rates across sites: unchecked
//    Bootatraping and consensus tree: checked
//    Number of replications: 100
//    Seed: 5
//    Consensus type: Majority Rule extended(Strict/Majority Rule/M1)
//    Press "Build"

    GTUtilsTaskTreeView::waitTaskFinished(os);

    QGraphicsView* treeView = qobject_cast<QGraphicsView*>(GTWidget::findWidget(os, "treeView"));
    CHECK_SET_ERR(treeView!=NULL,"TreeView not found")
//Expected state: tree appeared
}

GUI_TEST_CLASS_DEFINITION(test_0038_3){
//1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//2. Press "build tree" button on toolbar
    GTUtilsDialog::waitForDialog(os, new BuildTreeDialogFiller(os,100,testDir + "_common_data/scenarios/sandbox/COI.nwk",
                                                               5,BuildTreeDialogFiller::M1));
    QAbstractButton *tree= GTAction::button(os,"Build Tree");
    GTWidget::click(os,tree);
//Expected state: build tree dialog appeared

//3. Fill dialog:
//    Distanse matrix model: F84
//    Gamma distributed rates across sites: unchecked
//    Bootatraping and consensus tree: checked
//    Number of replications: 100
//    Seed: 5
//    Consensus type: Majority Rule extended(Strict/Majority Rule/M1)
//    Press "Build"
    GTUtilsTaskTreeView::waitTaskFinished(os);

    QGraphicsView* treeView = qobject_cast<QGraphicsView*>(GTWidget::findWidget(os, "treeView"));
    CHECK_SET_ERR(treeView!=NULL,"TreeView not found")
//Expected state: tree appeared
}

GUI_TEST_CLASS_DEFINITION(test_0038_4){
//1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
//2. Press "build tree" button on toolbar
    GTUtilsDialog::waitForDialog(os, new BuildTreeDialogFiller(os,100,testDir + "_common_data/scenarios/sandbox/COI.nwk",
                                                               5,BuildTreeDialogFiller::M1,1));
    QAbstractButton *tree= GTAction::button(os,"Build Tree");
    GTWidget::click(os,tree);
//Expected state: build tree dialog appeared

//3. Fill dialog:
//    Distanse matrix model: F84
//    Gamma distributed rates across sites: unchecked
//    Bootatraping and consensus tree: checked
//    Number of replications: 100
//    Seed: 5
//    Consensus type: Majority Rule extended(Strict/Majority Rule/M1)
//    Press "Build"

    GTUtilsTaskTreeView::waitTaskFinished(os);

    QGraphicsView* treeView = qobject_cast<QGraphicsView*>(GTWidget::findWidget(os, "treeView"));
    CHECK_SET_ERR(treeView!=NULL,"TreeView not found")
//Expected state: tree appeared
}

void test_0039_function(U2OpStatus &os, int comboNum, QString extention){
    //1. open document samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, GUITest::dataDir + "samples/CLUSTALW/", "COI.aln");

    //2. Use project tree context menu->Export/Import->Export Nucleic Alignment to Amino Translation
    //Expected state: Export Nucleic Alignment to Amino Translation dialog appeared
    //3.Fill dialog:
    //    File name: test/_common_data/scenarios/sandbox/transl.aln
    //    File format: CLUSTALW(use other formats too, check extension change)
    //    Amino translation: Standart genetic code
    //    Add document to project: checked
    GTMouseDriver::moveTo(os,GTUtilsProjectTreeView::getItemCenter(os,"COI"));
    GTUtilsDialog::waitForDialog(os, new ExportMSA2MSADialogFiller(os, comboNum, GUITest::testDir + "_common_data/scenarios/sandbox/COI_transl.aln"));
    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList()<<ACTION_PROJECT__EXPORT_IMPORT_MENU_ACTION<<ACTION_PROJECT__EXPORT_TO_AMINO_ACTION));
    GTMouseDriver::click(os,Qt::RightButton);
    GTGlobals::sleep(500);

    //Expected state: transl.aln appeared in project
    GTMouseDriver::moveTo(os,GTUtilsProjectTreeView::getItemCenter(os,"COI_transl." + extention));

}

GUI_TEST_CLASS_DEFINITION(test_0039){
//    QMap<int,QString> extMap;
//    extMap[0] = "aln";
//    extMap[1] = "fa";
//    extMap[2] = "msf";
//    extMap[3] = "meg";
//    extMap[4] = "nex";
//    extMap[5] = "phy";
//    extMap[6] = "phy";
//    extMap[7] = "sto";
    test_0039_function(os, 0, "aln");
}

GUI_TEST_CLASS_DEFINITION(test_0039_1){
    test_0039_function(os, 1, "fa");
}

GUI_TEST_CLASS_DEFINITION(test_0039_2){
    test_0039_function(os, 2, "msf");
}

GUI_TEST_CLASS_DEFINITION(test_0039_3){
    test_0039_function(os, 3, "meg");
}

GUI_TEST_CLASS_DEFINITION(test_0039_4){
    test_0039_function(os, 4, "nex");
}

GUI_TEST_CLASS_DEFINITION(test_0039_5){
    test_0039_function(os, 5, "phy");
}

GUI_TEST_CLASS_DEFINITION(test_0039_6){
    test_0039_function(os, 6, "phy");
}

GUI_TEST_CLASS_DEFINITION(test_0039_7){
    test_0039_function(os, 7, "sto");
}

GUI_TEST_CLASS_DEFINITION(test_0040){//UGENE crashes when opening several files
    QFile human_T1(dataDir + "/samples/FASTA/human_T1.fa");
    human_T1.copy(dataDir + "/samples/CLUSTALW/human_T1.fa");
    GTFileDialog::openFileList(os,dataDir + "samples/CLUSTALW/",QStringList()<<"COI.aln"<<"human_T1.fa");

    //GTUtilsDialog::waitForDialog(os, new MessageBoxDialogFiller(os,QMessageBox::No));
    GTUtilsProjectTreeView::findIndex(os,"human_T1.fa");//checks inside
    GTUtilsProjectTreeView::findIndex(os,"COI.aln");

    GTUtilsDialog::waitForDialog(os, new MessageBoxDialogFiller(os, QMessageBox::No));
    GTGlobals::sleep(500);
    QFile(dataDir + "/samples/CLUSTALW/human_T1.fa").remove();
    GTGlobals::sleep(5000);

}

GUI_TEST_CLASS_DEFINITION(test_0041) {
    // Shifting region in the Alignment Editor (UGENE-2127)
    //
    // 1. Open file data/samples/CLUSTALW/COI.aln
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
    int oldLength = GTUtilsMSAEditorSequenceArea::getLength(os);
    // 2. Select the first column.
    GTUtilsMSAEditorSequenceArea::selectColumnInConsensus(os, 0);
    // Expected state: column became selected
    GTUtilsMSAEditorSequenceArea::checkSelectedRect(os, QRect(0, 0, 1, 18));

    // 3. Drag the selection with mouse to 5 bases to the right.
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(0,0));
    GTMouseDriver::press(os);
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(5,0));
    GTMouseDriver::release(os);
    // Expected state: alignment moved to 5 bases to the right.

    // 4. Drag the selection with mouse to one base to the left.
    GTMouseDriver::press(os);
    GTUtilsMSAEditorSequenceArea::moveTo(os, QPoint(4,0));
    GTMouseDriver::release(os);
    // Expected state: alignment  moved to one bases to the left.

    // Check results
    int newLength = GTUtilsMSAEditorSequenceArea::getLength(os);
    CHECK_SET_ERR(4 == newLength - oldLength, QString("Wrong length of changed alignment"));
}

GUI_TEST_CLASS_DEFINITION(test_0042) {
    // default msa export
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList()<< MSAE_MENU_EXPORT << "Export as image"));
    GTUtilsDialog::waitForDialog(os, new ExportMsaImage(os, testDir + "_common_data/scenarios/sandbox/test_0042.png"));

    GTMenu::showContextMenu(os, GTWidget::findWidget(os,"msa_editor_sequence_area"));
}

GUI_TEST_CLASS_DEFINITION(test_0042_1) {
    // "all included" export
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "Export as image"));
    GTUtilsDialog::waitForDialog(os, new ExportMsaImage(os,
                                                        testDir + "_common_data/scenarios/sandbox/test_0042_1.png",
                                                        ExportMsaImage::Settings(true, true, true)/*include all*/));
    GTMenu::showContextMenu(os, GTWidget::findWidget(os, "msa_editor_sequence_area"));
}

GUI_TEST_CLASS_DEFINITION(test_0042_2) {
    // slightly modified export
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "Export as image"));
    GTUtilsDialog::waitForDialog(os, new ExportMsaImage(os,
                                                        testDir + "_common_data/scenarios/sandbox/test_0042_1",
                                                        ExportMsaImage::Settings(true, false, true)/*include all*/,
                                                        true,
                                                        false, RegionMsa(),
                                                        "bmp"));
    GTMenu::showContextMenu(os, GTWidget::findWidget(os, "msa_editor_sequence_area"));
}

GUI_TEST_CLASS_DEFINITION(test_0043) {
    // select a few sequences
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");

    QStringList sequences;
    sequences << "Montana_montana"
              << "Conocephalus_percaudata"
              << "Podisma_sapporensis";

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList()<< MSAE_MENU_EXPORT << "Export as image"));
    GTUtilsDialog::waitForDialog(os, new ExportMsaImage(os, testDir + "_common_data/scenarios/sandbox/test_0043.png",
                                                        ExportMsaImage::Settings(), false, false,
                                                        RegionMsa(U2Region(1, 594), sequences)));

    GTMenu::showContextMenu(os, GTWidget::findWidget(os,"msa_editor_sequence_area"));
}

GUI_TEST_CLASS_DEFINITION(test_0044) {
    // export selected region
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");

    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(5, 2), QPoint(25, 8));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList()<< MSAE_MENU_EXPORT << "Export as image"));
    GTUtilsDialog::waitForDialog(os, new ExportMsaImage(os, testDir + "_common_data/scenarios/sandbox/test_0044.png",
                                                        ExportMsaImage::Settings(true, true, true),
                                                        false, true));

    GTMenu::showContextMenu(os, GTWidget::findWidget(os,"msa_editor_sequence_area"));
}

GUI_TEST_CLASS_DEFINITION(test_0045) {
    // check the connection between export comboBox and selectRegion dialog
    // there should be no selection
    class ExportDialogChecker : public Filler {
    public:
        ExportDialogChecker(U2OpStatus &os)
            : Filler(os, "ImageExportForm") {}
        virtual void run() {
            QWidget* dialog = QApplication::activeModalWidget();
            CHECK_SET_ERR(dialog != NULL, "activeModalWidget is NULL");

            GTUtilsDialog::waitForDialog(os, new DefaultDialogFiller(os, "SelectSubalignmentDialog", QDialogButtonBox::Cancel));
            QComboBox* exportType = dialog->findChild<QComboBox*>("comboBox");
            GTComboBox::setIndexWithText(os, exportType, "Custom region", false);

            GTGlobals::sleep();
            CHECK_SET_ERR(exportType->currentText() == "Whole alignment", "Wrong combo box text!");
            GTUtilsDialog::clickButtonBox(os, dialog, QDialogButtonBox::Cancel);
        }
    };

    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "Export as image"));
    GTUtilsDialog::waitForDialog(os, new ExportDialogChecker(os));

    GTMenu::showContextMenu(os, GTWidget::findWidget(os,"msa_editor_sequence_area"));
}

GUI_TEST_CLASS_DEFINITION(test_0045_1) {
    // check the connection between export comboBox and selectRegion dialog
    // there should be no selection

    class ExportChecker : public Filler {
    public:
        ExportChecker(U2OpStatus &os)
            : Filler(os, "ImageExportForm") {}
        virtual void run() {
            QWidget* dialog = QApplication::activeModalWidget();
            CHECK_SET_ERR(dialog != NULL, "activeModalWidget is NULL");

            QComboBox* exportType = dialog->findChild<QComboBox*>("comboBox");
            CHECK_SET_ERR(exportType->currentText() == "Whole alignment", "Wrong combo box text!");

            GTUtilsDialog::waitForDialog(os,
                                         new SelectSubalignmentFiller(os,
                                                                      RegionMsa(U2Region(1, 593),
                                                                                QStringList() << "Montana_montana"
                                                                                << "Conocephalus_percaudata")));
            QPushButton* select = dialog->findChild<QPushButton*>("selectRegionButton");
            GTWidget::click(os, select);

            GTGlobals::sleep();
            CHECK_SET_ERR(exportType->currentText() == "Custom region", "Wrong combo box text!");

            GTUtilsDialog::clickButtonBox(os, dialog, QDialogButtonBox::Cancel);
        }
    };

    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "Export as image"));
    GTUtilsDialog::waitForDialog(os, new ExportChecker(os));

    GTMenu::showContextMenu(os, GTWidget::findWidget(os,"msa_editor_sequence_area"));
}

GUI_TEST_CLASS_DEFINITION(test_0046) {
    // check quality
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");
    GTWidget::click(os, GTWidget::findWidget(os, "msa_editor_sequence_area"));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "Export as image"));
    GTUtilsDialog::waitForDialog(os, new ExportMsaImage(os,
                                                        testDir + "_common_data/scenarios/sandbox/test_0046",
                                                        "jpg", 50));
    GTMenu::showContextMenu(os, GTWidget::findWidget(os, "msa_editor_sequence_area"));
}

GUI_TEST_CLASS_DEFINITION(test_0047) {
    // check select subalignment dialog

    class SelectSubalignmentChecker : public Filler {
    public:
        SelectSubalignmentChecker(U2OpStatus &os)
            : Filler(os, "SelectSubalignmentDialog") {}

        virtual void run() {
            QWidget* dialog = QApplication::activeModalWidget();
            CHECK_SET_ERR(dialog != NULL, "activeModalWidget is NULL");
            QDialogButtonBox* box = dialog->findChild<QDialogButtonBox*>("buttonBox");
            CHECK_SET_ERR(box != NULL, "buttonBox is NULL");
            QPushButton* ok = box->button(QDialogButtonBox::Ok);
            CHECK_SET_ERR(ok !=NULL, "ok button is NULL");

            QSpinBox* startPosBox = dialog->findChild<QSpinBox*>("startPosBox");
            CHECK_SET_ERR(startPosBox != NULL, "startPosBox is NULL");
            GTSpinBox::setValue(os, startPosBox, 10);

            QSpinBox* endPosBox = dialog->findChild<QSpinBox*>("endPosBox");
            CHECK_SET_ERR(endPosBox != NULL, "endPoxBox is NULL");
            GTSpinBox::setValue(os, endPosBox, 5);

            GTUtilsDialog::waitForDialog(os, new MessageBoxDialogFiller(os, QMessageBox::Ok));
            GTWidget::click(os, ok);

            GTSpinBox::setValue(os, endPosBox, 15);

            QWidget *noneButton = dialog->findChild<QWidget*>("noneButton");
            CHECK_SET_ERR(noneButton != NULL, "noneButton is NULL");
            GTWidget::click(os, noneButton);

            GTUtilsDialog::waitForDialog(os, new MessageBoxDialogFiller(os, QMessageBox::Ok));
            GTWidget::click(os, ok);

            GTGlobals::sleep();
            GTUtilsDialog::clickButtonBox(os, dialog, QDialogButtonBox::Cancel);
        }
    };

    class ExportChecker : public Filler {
    public:
        ExportChecker(U2OpStatus &os)
            : Filler(os, "ImageExportForm") {}
        virtual void run() {
            QWidget* dialog = QApplication::activeModalWidget();
            CHECK_SET_ERR(dialog != NULL, "activeModalWidget is NULL");

            GTUtilsDialog::waitForDialog(os, new SelectSubalignmentChecker(os));
            QPushButton* select = dialog->findChild<QPushButton*>("selectRegionButton");
            GTWidget::click(os, select);

            GTGlobals::sleep();
            GTUtilsDialog::clickButtonBox(os, dialog, QDialogButtonBox::Cancel);
        }
    };

    GTFileDialog::openFile(os, testDir + "_common_data/clustal", "align.aln");
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(1,1), QPoint(1,1));

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "Export as image"));
    GTUtilsDialog::waitForDialog(os, new ExportChecker(os));
    GTMenu::showContextMenu(os, GTWidget::findWidget(os, "msa_editor_sequence_area"));
}

GUI_TEST_CLASS_DEFINITION(test_0048) {
    // fail to export big alignment
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa", "big.aln");
    GTUtilsTaskTreeView::waitTaskFinished(os);

    class CustomFiller_0048 : public Filler {
    public:
        CustomFiller_0048(U2OpStatus &os)
            : Filler(os, "ImageExportForm") {}
        virtual void run() {
            QWidget* dialog = QApplication::activeModalWidget();
            CHECK_SET_ERR(dialog != NULL, "activeModalWidget is NULL");

            QComboBox* exportType = dialog->findChild<QComboBox*>("comboBox");
            CHECK_SET_ERR( exportType != NULL, "Cannot find comboBox");
            CHECK_SET_ERR( exportType->currentText() == "Whole alignment", "Wrong combo box text!");

            QLabel* hintLabel = dialog->findChild<QLabel*>("hintLabel");
            CHECK_SET_ERR( hintLabel != NULL, "Cannot find hintLabel");
            CHECK_SET_ERR( hintLabel->isVisible(), "Warning message is hidden!");

            QDialogButtonBox* buttonBox = dialog->findChild<QDialogButtonBox*>("buttonBox");
            CHECK_SET_ERR(buttonBox != NULL, "Cannot find buttonBox");
            QPushButton* exportButton = buttonBox->button(QDialogButtonBox::Ok);
            CHECK_SET_ERR( exportButton != NULL, "Cannot find Export button");
            CHECK_SET_ERR( !exportButton->isEnabled(), "Export button is enabled");

            GTUtilsDialog::clickButtonBox(os, dialog, QDialogButtonBox::Cancel);
        }
    };


    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList()<< MSAE_MENU_EXPORT << "Export as image"));
    GTUtilsDialog::waitForDialog(os, new CustomFiller_0048(os));

    GTMenu::showContextMenu(os, GTWidget::findWidget(os,"msa_editor_sequence_area"));
}

GUI_TEST_CLASS_DEFINITION(test_0049){
    //save alignment buttons test
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "COI.aln");
    GTUtilsDialog::waitForDialog(os, new ExportDocumentDialogFiller(os, sandBoxDir, "COI_test_0049.aln",
                                                                    ExportDocumentDialogFiller::CLUSTALW));\
    GTWidget::click(os, GTAction::button(os, "Save alignment as"));
    GTUtilsProjectTreeView::click(os, "COI.aln");
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);

    GTFileDialog::openFile(os, sandBoxDir, "COI_test_0049.aln");
    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0,0), QPoint(10,10));
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);

    GTWidget::click(os, GTAction::button(os, "Save alignment"));
    GTUtilsProjectTreeView::click(os, "COI_test_0049.aln");
    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);

    GTFileDialog::openFile(os, sandBoxDir, "COI_test_0049.aln");
    GTUtilsMSAEditorSequenceArea::checkSelection(os, QPoint(0,0), QPoint(10,0), "ATTCGAGCCGA");
}

GUI_TEST_CLASS_DEFINITION(test_0050){
    //    1. Open "COI.aln"
    //    2. Set any reference sequence
    //    3. Open context menu, open the "Highlighting" submenu, set the "Agreements" type
    //    4. Open context menu again, open the "Export" submenu, choose the "Export highlighted" menu item
    //    Expected state: the "Export highlighted to file" dialog appears - there is a checkbox 'transpose output'
    //    5. Click "Export"
    //    Expected state: result file contain columns of sequences
    //    6. Repeat 3-4
    //    7. Deselect 'Transpose output' and click 'Export'
    //    Expected state: result file contain rowa of sequences

        GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");
        GTUtilsDialog::waitForDialog(os, new PopupChooserbyText(os, QStringList() << "Set this sequence as reference"));
        GTWidget::click(os, GTUtilsMSAEditorSequenceArea::getSequenceArea(os), Qt::RightButton, QPoint(10, 10));

        GTUtilsDialog::waitForDialog(os, new PopupChooserbyText(os, QStringList() << "Highlighting" << "Agreements"));
        GTWidget::click(os, GTUtilsMSAEditorSequenceArea::getSequenceArea(os), Qt::RightButton);

        GTUtilsDialog::waitForDialog(os, new PopupChooserbyText(os, QStringList() << "Export" << "Export highlighted"));
        GTUtilsDialog::waitForDialog(os, new ExportHighlightedDialogFiller(os, sandBoxDir + "common_msa_test_0050_1.txt"));
        GTWidget::click(os, GTUtilsMSAEditorSequenceArea::getSequenceArea(os), Qt::RightButton);
        GTGlobals::sleep();

        CHECK_SET_ERR( GTFile::equals(os, sandBoxDir + "common_msa_test_0050_1.txt",
                                      testDir + "_common_data/clustal/COI_highlighted_1"),
                       "Transposed export is incorrect");

        GTUtilsDialog::waitForDialog(os, new PopupChooserbyText(os, QStringList() << "Export" << "Export highlighted"));
        GTUtilsDialog::waitForDialog(os, new ExportHighlightedDialogFiller(os, sandBoxDir + "common_msa_test_0050_2.txt", false));
        GTWidget::click(os, GTUtilsMSAEditorSequenceArea::getSequenceArea(os), Qt::RightButton);
        GTGlobals::sleep();

        CHECK_SET_ERR( GTFile::equals(os, sandBoxDir + "common_msa_test_0050_2.txt",
                                      testDir + "_common_data/clustal/COI_highlighted_2"),
                       "Export is incorrect");
}

GUI_TEST_CLASS_DEFINITION(test_0051){
/* 1. Open samples/CLUSTALW/ty3.aln.gz
 * 2. Open context menu, open "View" and choose "Sort sequences by name"
 *   Expected state: Sequences sorted case insensitive by name
*/
    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/msa", "ma_unsorted.aln");
    GTUtilsTaskTreeView::waitTaskFinished(os);

    GTUtilsDialog::waitForDialog(os, new PopupChooser(os, QStringList() << MSAE_MENU_VIEW << "action_sort_by_name"));
    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
    GTGlobals::sleep(200);

    QStringList names = GTUtilsMSAEditorSequenceArea::getNameList(os);

    CHECK_SET_ERR( names.length() == 4, "Count of sequences in MSA incorrect");
    CHECK_SET_ERR( names.at(0) == "a", "At positoin 0 not showed 'a' name");
    CHECK_SET_ERR( names.at(1) == "C", "At positoin 1 not showed 'C' name");
    CHECK_SET_ERR( names.at(2) == "D", "At positoin 2 not showed 'D' name");
    CHECK_SET_ERR( names.at(3) == "d", "At positoin 3 not showed 'd' name");
}

GUI_TEST_CLASS_DEFINITION(test_0052){
//    1. Open "_common_data/clustal/3000_sequences.aln"
//    2. Context menu -- Export as ImageExport
//    Expected state: export dialog appeared, there is a warning message and Export button is disabled
//    3. Select smalle region
//    Expected state: warning is gone, export is enabled
    GTFileDialog::openFile(os, testDir + "_common_data/clustal/3000_sequences.aln");
    GTUtilsTaskTreeView::waitTaskFinished(os);

    class CustomFiller_0052 : public Filler {
    public:
        CustomFiller_0052(U2OpStatus &os)
            : Filler(os, "ImageExportForm") {}
        virtual void run() {
            QWidget* dialog = QApplication::activeModalWidget();
            CHECK_SET_ERR(dialog != NULL, "activeModalWidget is NULL");

            QComboBox* exportType = dialog->findChild<QComboBox*>("comboBox");
            CHECK_SET_ERR( exportType != NULL, "Cannot find comboBox");
            CHECK_SET_ERR( exportType->currentText() == "Whole alignment", "Wrong combo box text!");

            QLabel* hintLabel = dialog->findChild<QLabel*>("hintLabel");
            CHECK_SET_ERR( hintLabel != NULL, "Cannot find hintLabel");
            CHECK_SET_ERR( hintLabel->isVisible(), "Warning message is hidden!");

            QDialogButtonBox* buttonBox = dialog->findChild<QDialogButtonBox*>("buttonBox");
            CHECK_SET_ERR(buttonBox != NULL, "Cannot find buttonBox");
            QPushButton* exportButton = buttonBox->button(QDialogButtonBox::Ok);
            CHECK_SET_ERR( exportButton != NULL, "Cannot find Export button");
            CHECK_SET_ERR( !exportButton->isEnabled(), "Export button is enabled");

            GTUtilsDialog::waitForDialog(os,
                                         new SelectSubalignmentFiller(os,
                                                                      RegionMsa(U2Region(1, 593),
                                                                                QStringList() << "Sequence__1"
                                                                                << "Sequence__2" << "Sequnce__3" << "Sequence__4")));

            QPushButton* select = dialog->findChild<QPushButton*>("selectRegionButton");
            GTWidget::click(os, select);

            GTGlobals::sleep();
            CHECK_SET_ERR(exportType->currentText() == "Custom region", "Wrong combo box text!");

            CHECK_SET_ERR( !hintLabel->isVisible(), "Warning is visible");
            CHECK_SET_ERR( exportButton->isEnabled(), "Export button is disabled");

            GTUtilsDialog::clickButtonBox(os, dialog, QDialogButtonBox::Cancel);
        }
    };

    GTUtilsDialog::waitForDialog(os, new CustomFiller_0052(os));
    GTUtilsDialog::waitForDialog( os, new PopupChooser(os, QStringList() << MSAE_MENU_EXPORT << "Export as image"));
    GTMenu::showContextMenu(os, GTUtilsMdi::activeWindow(os));
}

GUI_TEST_CLASS_DEFINITION(test_0053){
        //Copied formatted (context menu)
        //1. Open amples\CLUSTALW\COI.aln
        //2. Select the first three letters TAA
        //3. Context menue {Copy-><<Copy formatted}
        //Expected state: the buffer contatin the sequence in CLUSTALW format
        GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");
        GTGlobals::sleep();

        GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0, 0), QPoint(2, 0));

        GTUtilsDialog::waitForDialog(os,new PopupChooser(os,QStringList()<<MSAE_MENU_COPY<<"copy_formatted"));
        GTMouseDriver::click(os,Qt::RightButton);
        GTGlobals::sleep(3000);

        QString clipboardText = GTClipboard::text(os);

        CHECK_SET_ERR(clipboardText.contains("TAA"), clipboardText);
        GTGlobals::sleep(3000);
}

GUI_TEST_CLASS_DEFINITION(test_0053_1){
    //Copied formatted (context menu), the format is changable
    //1. Open samples\CLUSTALW\COI.aln
    //2. Select the first three letters TAA
    //3. In the general tab of the options panel find the Copy Type combobox and select the Mega format
    //4. Context menu {Copy->Copy formatted}
    //Expected state: the buffer contatin the sequence in Mega format
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");
    GTGlobals::sleep();

    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::General);
    GTGlobals::sleep(200);

    QComboBox* copyType = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "copyType"));
    CHECK_SET_ERR(copyType != NULL, "copy combobox not found");

    GTComboBox::setIndexWithText(os, copyType, "Mega");

    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0, 0), QPoint(2, 0));

    GTUtilsDialog::waitForDialog(os,new PopupChooser(os,QStringList()<<MSAE_MENU_COPY<<"copy_formatted"));
    GTMouseDriver::click(os,Qt::RightButton);
    GTGlobals::sleep(3000);

    QString clipboardText = GTClipboard::text(os);

    CHECK_SET_ERR(clipboardText.contains("mega"), clipboardText);
    CHECK_SET_ERR(clipboardText.contains("TAA"), clipboardText);

    GTGlobals::sleep(3000);
}

GUI_TEST_CLASS_DEFINITION(test_0053_2){
    //Copied formatted (toolbar), the format is changable
    //1. Open samples\CLUSTALW\COI.aln
    //2. Select the first three letters TAA
    //3. In the general tab of the options panel find the Copy Type combobox and select the CLUSTALW format
    //4. Toolbar {Copy->Copy formatted}
    //Expected state: the buffer contatin the sequence in CLUSTALW format
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");
    GTGlobals::sleep();

    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::General);
    GTGlobals::sleep(200);

    QComboBox* copyType = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "copyType"));
    CHECK_SET_ERR(copyType != NULL, "copy combobox not found");

    GTComboBox::setIndexWithText(os, copyType, "CLUSTALW");

    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0, 0), QPoint(2, 0));

    GTWidget::click(os, GTToolbar::getWidgetForActionName(os, GTToolbar::getToolbar(os, MWTOOLBAR_ACTIVEMDI), "copy_formatted"));
    GTGlobals::sleep(3000);

    QString clipboardText = GTClipboard::text(os);

    CHECK_SET_ERR(clipboardText.contains("CLUSTAL W 2.0 multiple sequence alignment"), clipboardText);
    CHECK_SET_ERR(clipboardText.contains("TAA"), clipboardText);

    GTGlobals::sleep(3000);
}

GUI_TEST_CLASS_DEFINITION(test_0053_3){
        //Copied formatted (context menu) for a big alignment
        //1. Open _common_data/clustal/100_sequences.aln
        //2. Select the whole alignment
        //3. Context menue {Copy->Copy formatted}
        //Expected state: the buffer contatin the sequences in CLUSTALW format
        GTFileDialog::openFile(os, testDir + "_common_data/clustal/100_sequences.aln");
        GTGlobals::sleep();

        QStringList names = GTUtilsMSAEditorSequenceArea::getNameList(os);
        CHECK_SET_ERR(!names.isEmpty(), "the alignment is empty");
        GTUtilsMSAEditorSequenceArea::selectSequence(os, names.first());

        GTUtilsDialog::waitForDialog(os,new PopupChooser(os,QStringList()<<MSAE_MENU_COPY<<"copy_formatted"));
        GTMouseDriver::click(os,Qt::RightButton);
        GTGlobals::sleep(3000);

        QString clipboardText = GTClipboard::text(os);

        CHECK_SET_ERR(clipboardText.contains("ACCAGGCTTGGCAATGCGTATC"), clipboardText);
        GTGlobals::sleep(3000);
}

GUI_TEST_CLASS_DEFINITION(test_0053_4){
        //Copied formatted (action is disabled when no selection
        //1. Open samples\CLUSTALW\COI.aln
        //2. Try context menue {Copy->Copy formatted}
        //Expected state: the action is disabled
        GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");
        GTGlobals::sleep();

        QWidget* w = GTToolbar::getWidgetForActionName(os, GTToolbar::getToolbar(os, MWTOOLBAR_ACTIVEMDI), "copy_formatted");
        CHECK_SET_ERR(w!=NULL, "no copy action on the toolbar");
        CHECK_SET_ERR(w->isEnabled() == false, "selection is empty but the action is enabled");
}

GUI_TEST_CLASS_DEFINITION(test_0053_5){
    //Copied formatted (toolbar), the format is changable to RTF
    //1. Open samples\CLUSTALW\COI.aln
    //2. Select the first three letters TAA
    //3. In the general tab of the options panel find the Copy Type combobox and select the RTF format
    //4. Toolbar {Copy->Copy formatted}
    //Expected state: the buffer contatin the sequence in RTF format
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW", "COI.aln");
    GTGlobals::sleep();

    GTUtilsOptionPanelMsa::openTab(os, GTUtilsOptionPanelMsa::General);
    GTGlobals::sleep(200);

    QComboBox* copyType = qobject_cast<QComboBox*>(GTWidget::findWidget(os, "copyType"));
    CHECK_SET_ERR(copyType != NULL, "copy combobox not found");

    GTComboBox::setIndexWithText(os, copyType, "Rich text (HTML)");

    GTUtilsMSAEditorSequenceArea::selectArea(os, QPoint(0, 0), QPoint(2, 0));

    GTWidget::click(os, GTToolbar::getWidgetForActionName(os, GTToolbar::getToolbar(os, MWTOOLBAR_ACTIVEMDI), "copy_formatted"));
    GTGlobals::sleep(3000);

    QString clipboardText = GTClipboard::text(os);

    CHECK_SET_ERR(clipboardText.contains("<span style=\"font-size:10pt; font-family:Verdana;\">"), clipboardText);
    CHECK_SET_ERR(clipboardText.contains("<p><span style=\"background-color:#ff99b1;\">T</span><span style=\"background-color:#fcff92;\">A</span><span style=\"background-color:#fcff92;\">A</span></p>"), clipboardText);



    GTGlobals::sleep(3000);
}


GUI_TEST_CLASS_DEFINITION(test_fake) {
    Q_UNUSED(os);
}

} // namespace GUITest_common_scenarios_msa_editor
} // namespace U2
