/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2017 UniPro <ugene@unipro.ru>
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

#ifndef _U2_HMMER_SEARCH_TASK_H_
#define _U2_HMMER_SEARCH_TASK_H_

#include <U2Core/ExternalToolRunTask.h>

#include "HmmerSearchSettings.h"

namespace U2 {

class AnnotationTableObject;
class HmmerParseSearchResultsTask;
class SaveSequenceTask;

class HmmerSearchTask : public ExternalToolSupportTask {
    Q_OBJECT
public:
    HmmerSearchTask(const HmmerSearchSettings &settings);

    QList<SharedAnnotationData> getAnnotations() const;

private:
    void prepare();
    QList<Task *> onSubTaskFinished(Task *subTask);
    QString generateReport() const;

    void prepareWorkingDir();
    void removeTempDir() const;
    QStringList getArguments() const;

    void prepareSequenceSaveTask();
    void prepareHmmerTask();
    void prepareParseTask();

    HmmerSearchSettings settings;

    SaveSequenceTask *saveSequenceTask;
    ExternalToolRunTask *hmmerTask;
    HmmerParseSearchResultsTask *parseTask;
    bool removeWorkingDir;

    static const QString INPUT_SEQUENCE_FILENAME;
    static const QString PER_DOMAIN_HITS_FILENAME;
};

}   // namespace U2

#endif // _U2_HMMER_SEARCH_TASK_H_
