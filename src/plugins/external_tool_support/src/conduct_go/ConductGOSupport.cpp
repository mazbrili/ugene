/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2013 UniPro <ugene@unipro.ru>
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

#include "ConductGOSupport.h"

#include <python/PythonSupport.h>

#include <U2Core/AppContext.h>

namespace U2 {

const QString ConductGOSupport::TOOL_NAME("go_analysis");

ConductGOSupport::ConductGOSupport(const QString &name)
: ExternalTool(name)
{
    initialize();
}

void ConductGOSupport::initialize() {
    if (AppContext::getMainWindow()) {
        icon = QIcon(":external_tool_support/images/cmdline.png");
        grayIcon = QIcon(":external_tool_support/images/cmdline_gray.png");
        warnIcon = QIcon(":external_tool_support/images/cmdline_warn.png");
    }

    toolKitName = "Cistrome";
    description = ConductGOSupport::tr("<i>Conduct GO</i> - For a list of input genes, this tool uses R/BioC packages (GO, GOstats) to identify over represented GO terms.");

    executableFileName = "go_analysis.py";

    toolRunnerProgramm = PYTHON_TOOL_NAME;

    validMessage = "Conduct GO";
    validationArguments << "--version";

    versionRegExp=QRegExp(executableFileName + "\\d+\\.\\d+");

    additionalValidators<<DefaultExternalToolValidations::rValidation();

}

} // U2
