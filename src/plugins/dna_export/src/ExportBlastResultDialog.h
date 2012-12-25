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

#ifndef _U2_EXPORT_BLAST_RESULT_DIALOG_H_
#define _U2_EXPORT_BLAST_RESULT_DIALOG_H_

#include <U2Core/global.h>

#include <QtGui/QDialog>
#include <ui/ui_ExportBlastResultDialog.h>

namespace U2 {

class SaveDocumentGroupController;

class ExportBlastResultDialog : public QDialog, Ui_ExportBlastResultDialog {
    Q_OBJECT
public:
    ExportBlastResultDialog(QWidget* p, const QString& defaultUrl = QString() );
    
    void setOkButtonText(const QString& text) const;
    void setFileLabelText(const QString& text) const;

    virtual void accept();


public:    
    QString url;
    DocumentFormatId format;
    bool    addToProjectFlag;
    bool    useGenbankHeader;

private:    
    SaveDocumentGroupController* saveContoller;

};

}//namespace

#endif // _U2_EXPORT_BLAST_RESULT_DIALOG_H_
