/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2014 UniPro <ugene@unipro.ru>
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

#ifndef _U2_WMETADIALOG_H_
#define _U2_WMETADIALOG_H_

#include "ui/ui_WorkflowMetaDialog.h"

#include <U2Lang/ActorModel.h>
#include <U2Lang/Schema.h>

namespace U2 {
using namespace Workflow;
class WorkflowMetaDialog : public QDialog, public Ui_WorkflowMetaDialog {
    Q_OBJECT

public:
    WorkflowMetaDialog(QWidget * p, const Workflow::Metadata& meta);

public:
    Workflow::Metadata meta;

private slots:

    void sl_onBrowse();
    void sl_onSave();
    void sl_onURLChanged(const QString & text);

private:
    QPushButton* cancelButton;
    QPushButton* okButton;
};

}//namespace

#endif
