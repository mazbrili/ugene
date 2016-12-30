/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2016 UniPro <ugene@unipro.ru>
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

#include <QApplication>
#include <QDesktopServices>
#include <QFile>
#include <QMessageBox>


#if (QT_VERSION < 0x050400) //Qt 5
#include <QtWidgets/QMessageBox>
#include <QtWebKitWidgets/QWebFrame>
#include <QtWidgets/QApplication>
#include <QWebEngineScript>
#else
#include <QtWebSockets/QWebSocketServer>
#include <QtWebChannel/QWebChannel>

#include <QDesktopServices>

#include <U2Gui/WebSocketClientWrapper.h>
#include <U2Gui/WebSocketTransport.h>
#endif // endif



#include <QClipboard>

#include <U2Core/AppContext.h>
#include <U2Core/AppSettings.h>
#include <U2Core/UserApplicationsSettings.h>
#include <U2Core/GUrlUtils.h>
#include <U2Core/ProjectModel.h>
#include <U2Core/Task.h>
#include <U2Core/U2OpStatusUtils.h>
#include <U2Core/U2SafePoints.h>

#include <U2Gui/MainWindow.h>

#include <U2Lang/WorkflowSettings.h>
#include <U2Lang/URLAttribute.h>
#include <U2Lang/URLContainer.h>
#include <U2Lang/WorkflowUtils.h>

#include "Dashboard.h"

namespace U2 {

static const QString REPORT_SUB_DIR("report/");
static const QString DB_FILE_NAME("dashboard.html");
static const QString SETTINGS_FILE_NAME("settings.ini");
static const QString OPENED_SETTING("opened");
static const QString NAME_SETTING("name");

/************************************************************************/
/* Dashboard */
/************************************************************************/
const QString Dashboard::EXT_TOOLS_TAB_ID = "#ext_tools_tab";
const QString Dashboard::OVERVIEW_TAB_ID = "#overview_tab";
const QString Dashboard::INPUT_TAB_ID = "#input_tab";
//const QString Dashboard::OUTPUT_TAB_ID = "#output_tab";

#if (QT_VERSION >= 0x050400) //Qt 5.7
const QString Dashboard::RESOURCE_WIDGET_ID = "resourceWidget";
const QString Dashboard::OUTPUT_WIDGET_ID = "outputWidget";
const QString Dashboard::STATISTICS_WIDGET_ID = "statisticsWidget";
const QString Dashboard::PROBLEMS_WIDGET_ID = "problemsWidget";
const QString Dashboard::PARAMETERS_WIDGET_ID = "parametersWidget";
#endif

Dashboard::Dashboard(const WorkflowMonitor *monitor, const QString &_name, QWidget *parent)
#if (QT_VERSION < 0x050400) //Qt 5.7
    : QWebView(parent)
#else
    : QWebEngineView(parent)
#endif
, loaded(false), name(_name), opened(true), _monitor(monitor), initialized(false), workflowInProgress(true)
{
//    etWidgetController = new ExternalToolsWidgetController();

    connect(this, SIGNAL(loadFinished(bool)), SLOT(sl_loaded(bool)));
    connect(_monitor, SIGNAL(si_report()), SLOT(sl_serialize()));
    connect(_monitor, SIGNAL(si_dirSet(const QString &)), SLOT(sl_setDirectory(const QString &)));
    connect(_monitor, SIGNAL(si_taskStateChanged(Monitor::TaskState)), SLOT(sl_workflowStateChanged(Monitor::TaskState)));
//    connect(_monitor, SIGNAL(si_logChanged(U2::Workflow::Monitor::LogEntry)),
//            etWidgetController, SLOT(sl_onLogChanged(U2::Workflow::Monitor::LogEntry)));

    dashboardPageController = new DashboardPageController(this);
    setContextMenuPolicy(Qt::NoContextMenu);
#if (QT_VERSION < 0x050400) //Qt 5.7
    loadUrl = ":U2Designer/html/Dashboard.html";
#else
    loadUrl = "qrc:///U2Designer/html/Dashboard_webengine.html";
#endif
    loadDocument();
    setObjectName("Dashboard");
#if (QT_VERSION >= 0x050400) //Qt 5.7


#endif
    connect(_monitor, SIGNAL(si_progressChanged(int)), dashboardPageController, SIGNAL(si_progressChanged(int)));
    connect(_monitor, SIGNAL(si_taskStateChanged(Monitor::TaskState)), SLOT(sl_taskStateChanged(Monitor::TaskState)));
    connect(_monitor, SIGNAL(si_newProblem(Problem,int)), SLOT(sl_newProblem(Problem,int)));
    connect(_monitor, SIGNAL(si_workerInfoChanged(const QString &, const U2::Workflow::Monitor::WorkerInfo &)),
        SLOT(sl_workerInfoChanged(const QString &, const U2::Workflow::Monitor::WorkerInfo &)));
    connect(_monitor, SIGNAL(si_updateProducers()), SLOT(sl_workerStatsUpdate()));
    connect(_monitor, SIGNAL(si_newOutputFile(const U2::Workflow::Monitor::FileInfo &)),
        SLOT(sl_newOutputFile(const U2::Workflow::Monitor::FileInfo &)));
    connect(_monitor, SIGNAL(si_logChanged(U2::Workflow::Monitor::LogEntry)), SLOT(sl_onLogChanged(U2::Workflow::Monitor::LogEntry)));
}

Dashboard::Dashboard(const QString &dirPath, QWidget *parent)
#if (QT_VERSION < 0x050400) //Qt 5.7
    : QWebView(parent)
#else
    : QWebEngineView(parent)
#endif
,loaded(false), dir(dirPath), opened(true), _monitor(NULL), initialized(false), workflowInProgress(false)
{
//    etWidgetController = new ExternalToolsWidgetController;
    dashboardPageController = new DashboardPageController(this);
//    channel->registerObject(QString("agent"), dashboardPageController);
    connect(this, SIGNAL(loadFinished(bool)), SLOT(sl_loaded(bool)));
    setContextMenuPolicy(Qt::NoContextMenu);
    loadUrl = dir + REPORT_SUB_DIR + DB_FILE_NAME;
    loadSettings();
    saveSettings();
}

Dashboard::~Dashboard() {
//    delete etWidgetController;
}

void Dashboard::onShow() {
    CHECK(!loaded, );
    loadDocument();
}

void Dashboard::sl_setDirectory(const QString &value) {
    dir = value;
    U2OpStatus2Log os;
    saveSettings();
}

void Dashboard::sl_workflowStateChanged(Monitor::TaskState state) {
    workflowInProgress = (state == Monitor::RUNNING) || (state == Monitor::RUNNING_WITH_PROBLEMS);
    if (!workflowInProgress) {
        emit si_workflowStateChanged(workflowInProgress);
    }
}

void Dashboard::setClosed() {
    opened = false;
    U2OpStatus2Log os;
    saveSettings();
}

QString Dashboard::directory() const {
    return dir;
}

QString Dashboard::getName() const {
    return name;
}

void Dashboard::setName(const QString &value) {
    name = value;
    saveSettings();
}

void Dashboard::loadDocument() {
    loaded = true;
    QFile file(loadUrl);
#if (QT_VERSION < 0x050400) //Qt 5.7
    bool opened = file.open(QIODevice::ReadOnly);
    if (!opened) {
        coreLog.error("Can not load " + loadUrl);
        return;
    }

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QString html = stream.readAll();
    file.close();
    page()->mainFrame()->setHtml(html);
#elif (QT_VERSION < 0x050500) //Qt 5.7
    server = new QWebSocketServer(QStringLiteral("UGENE Standalone Server"), QWebSocketServer::NonSecureMode, this);
    if (!server->listen(QHostAddress::LocalHost, 12346)) {
        return;
    }

    clientWrapper = new WebSocketClientWrapper(server, this);

    channel = new QWebChannel(this);

    QObject::connect(clientWrapper, &WebSocketClientWrapper::clientConnected,
        channel, &QWebChannel::connectTo);

    //channel->registerObject(QString("agent"), this);
#else
    QWebEnginePage *pg = new QWebEnginePage(parentWidget());
    QUrl abs;
    if(!loadUrl.startsWith("qrc")){
        abs = QUrl("file://"+loadUrl);
    }else{
        abs = QUrl(loadUrl);
    }
    pg->load(abs);
    setPage(pg);

    channel = new QWebChannel(page());
    page()->setWebChannel(channel);
    channel->registerObject(QString("agent"), dashboardPageController);
#endif
}

void Dashboard::sl_loaded(bool ok) {
    CHECK(!initialized, );
    SAFE_POINT(ok, "Loaded with errors", );
    initialized = true;
#if (QT_VERSION < 0x050400) //Qt 5.7
    page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    page()->mainFrame()->addToJavaScriptWindowObject("agent", new JavascriptAgent(this));
    doc = page()->mainFrame()->documentElement();
    if (NULL != monitor()) {
        new OutputFilesWidget(addWidget(tr("Output Files"), OverviewDashTab, 0), this);
        new ResourcesWidget(addWidget(tr("Workflow Task"), OverviewDashTab, 1), this);
        new StatisticsWidget(addWidget(tr("Common Statistics"), OverviewDashTab, 1), this);

        sl_runStateChanged(false);
        if (!monitor()->getProblems().isEmpty()) {
            sl_addProblemsWidget();
        }

        new ParametersWidget(addWidget(tr("Parameters"), InputDashTab, 0), this);

        //new OutputFilesWidget(addWidget(tr("Output Files"), OutputDashTab, 0), this);

        createExternalToolTab();

        connect(monitor(), SIGNAL(si_runStateChanged(bool)), SLOT(sl_runStateChanged(bool)));
        connect(monitor(), SIGNAL(si_firstProblem()), SLOT(sl_addProblemsWidget()));
    }

    if (!WorkflowSettings::isShowLoadButtonHint()) {
        page()->mainFrame()->documentElement().evaluateJavaScript("hideLoadBtnHint()");
    }
#else
    if (NULL != monitor()) {
        page()->runJavaScript("parametersWidget = new ParametersWidget(\"parametersWidget\")");
        page()->runJavaScript("outputWidget = new OutputFilesWidget(\"outputWidget\");");
        page()->runJavaScript("statusWidget = new StatusWidget(\"statusWidget\");");
        page()->runJavaScript("statisticsWidget = new StatisticsWidget(\"statisticsWidget\");");
        sl_workerStatsUpdate();

        sl_runStateChanged(false);
        if (!monitor()->getProblems().isEmpty()) {//TODO fix adding problems widget on starting execution
            sl_addProblemsWidget();
        }

        createExternalToolTab();

        connect(monitor(), SIGNAL(si_runStateChanged(bool)), SLOT(sl_runStateChanged(bool)));
        connect(monitor(), SIGNAL(si_firstProblem()), SLOT(sl_addProblemsWidget()));
    }
    if (!WorkflowSettings::isShowLoadButtonHint()) {
        //page()->mainFrame()->documentElement().evaluateJavaScript("hideLoadBtnHint()");
        page()->runJavaScript("document.getElementById('wrapper').hideLoadBtnHint()");
    }
    //assert(false);
#endif
}

void Dashboard::sl_addProblemsWidget() {
#if (QT_VERSION < 0x050400) //Qt 5.7
    // Will be removed by parent
    new ProblemsWidget(addWidget(tr("Problems"), OverviewDashTab), this);
#else
    //addWidget(tr("Problems"), OverviewDashTab);
    //new ProblemsWidget(PROBLEMS_WIDGET_ID, this);
    //assert(false);
    page()->runJavaScript("problemsWidget = new ProblemsWidget(\"problemsWidget\");");
#endif
}

void Dashboard::sl_serialize() {
    QCoreApplication::processEvents();
    QString reportDir = dir + REPORT_SUB_DIR;
    QDir d(reportDir);
    if (!d.exists(reportDir)) {
        bool created = d.mkpath(reportDir);
        if (!created) {
            coreLog.error(tr("Can not create a directory: ") + reportDir);
            return;
        }
    }
    U2OpStatus2Log os;
    serialize(os);
    CHECK_OP(os, );
    saveSettings();
}

void Dashboard::sl_taskStateChanged(TaskState state){
    QString stateStr;
    if (Monitor::RUNNING == state) {
        stateStr = "RUNNING";
    } else if (Monitor::RUNNING_WITH_PROBLEMS == state) {
        stateStr = "RUNNING_WITH_PROBLEMS";
    } else if (Monitor::FINISHED_WITH_PROBLEMS == state) {
        stateStr = "FINISHED_WITH_PROBLEMS";
    } else if (Monitor::FAILED == state) {
        stateStr = "FAILED";
    } else if (Monitor::SUCCESS == state) {
        stateStr = "SUCCESS";
    } else {
        stateStr = "CANCELED";
    }
    emit dashboardPageController->si_taskStateChanged(stateStr);
}

void Dashboard::sl_newProblem(const Problem &info, int count){
    QJsonObject infoJS;
    infoJS["actor"] = monitor()->actorName(info.actor);
    infoJS["type"] = info.type;
    infoJS["message"] = info.message;
    emit dashboardPageController->si_newProblem(infoJS, count);
}

void Dashboard::sl_workerInfoChanged(const QString &actorId, const WorkerInfo &info){
    QJsonObject infoJS;
    infoJS["actor"] = monitor()->actorName(actorId);
    infoJS["timeMks"] = info.timeMks;
    infoJS["countOfProducedData"] = monitor()->getDataProduced(actorId);
    emit dashboardPageController->si_workerStatsInfoChanged(infoJS);
}

void Dashboard::sl_workerStatsUpdate(){
    QJsonArray workersStatisticsInfo;
    QMap<QString, WorkerInfo> infos = monitor()->getWorkersInfo();
    foreach (const QString &actorId, infos.keys()) {
        WorkerInfo &info = infos[actorId];
        QJsonObject infoJS;
        infoJS["actor"] = monitor()->actorName(actorId);
        infoJS["timeMks"] = info.timeMks;
        infoJS["countOfProducedData"] = monitor()->getDataProduced(actorId);
        workersStatisticsInfo.append(infoJS);
    }
    emit dashboardPageController->si_workerStatsUpdate(workersStatisticsInfo);
}

void Dashboard::sl_newOutputFile(const U2::Workflow::Monitor::FileInfo &info){
    QJsonObject infoJS;
    infoJS["actor"] = monitor()->actorName(info.actor);
    infoJS["url"] = info.url;
    infoJS["openBySystem"] = info.openBySystem;
    emit dashboardPageController->si_newOutputFile(infoJS);
}
void Dashboard::sl_onLogChanged(U2::Workflow::Monitor::LogEntry entry){
    QJsonObject entryJS;
    entryJS["toolName"] = entry.toolName;
    entryJS["actorName"] = entry.actorName;
    entryJS["runNumber"] = entry.runNumber;
    entryJS["logType"] = entry.logType;
    entryJS["lastLine"] = entry.lastLine;
    emit dashboardPageController->si_onLogChanged(entryJS);
}
void Dashboard::serialize(U2OpStatus &os) {
#if (QT_VERSION < 0x050400) //Qt 5.7
    QString fileName = dir + REPORT_SUB_DIR + DB_FILE_NAME;
    QFile file(fileName);
    bool opened = file.open(QIODevice::WriteOnly);
    if (!opened) {
        os.setError(tr("Can not open a file for writing: ") + fileName);
        return;
    }
    QString html = page()->mainFrame()->toHtml();

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream << html;
    stream.flush();
    file.close();
#else
    page()->toHtml([this](const QString &result) { return result; });
    connect(this, SIGNAL(si_serializeContent(const QString&)), this, SLOT(sl_serializeContent(const QString&)));
    page()->toHtml([this](const QString& result) mutable {emit si_serializeContent(result);});
#endif
}

void Dashboard::saveSettings() {
    QSettings s(dir + REPORT_SUB_DIR + SETTINGS_FILE_NAME, QSettings::IniFormat);
    s.setValue(OPENED_SETTING, opened);
    s.setValue(NAME_SETTING, name);
    s.sync();
}

void Dashboard::loadSettings() {
    QSettings s(dir + REPORT_SUB_DIR + SETTINGS_FILE_NAME, QSettings::IniFormat);
    opened = true;
    name = s.value(NAME_SETTING).toString();
}

void Dashboard::createExternalToolTab() {
    const WorkflowMonitor* mon = monitor();
    SAFE_POINT(mon, "Monitor is NULL", );

    foreach (const WorkerParamsInfo& info, mon->getWorkersParameters()) {
        SAFE_POINT(info.actor, "Actor is NULL", );
        const ActorPrototype* proto = info.actor->getProto();
        SAFE_POINT(proto, "Actor prototype is NULL", );

        if (!proto->getExternalTools().isEmpty()) {
            QString addTabJs = "addTab('" + EXT_TOOLS_TAB_ID + "','" + tr("External Tools") + "')";
            page()->runJavaScript("externalToolsWidget = externalToolsWidget || new ExternalToolsWidget(\"externalToolsWidget\");");
            break;
        }
    }
}

#if (QT_VERSION < 0x050400) //Qt 5.7
int Dashboard::containerSize(const QWebElement &insideElt, const QString &name) {
    QWebElement cont = insideElt.findFirst(name);
    SAFE_POINT(!cont.isNull(), "NULL container", 0);
    QWebElementCollection children = cont.findAll(".widget");
    return children.count();
}

QWebElement Dashboard::getDocument() {
    return doc;
}

QWebElement Dashboard::addWidget(const QString &title, DashboardTab dashTab, int cntNum) {
    // Find the tab
    QString dashTabId;
    if (OverviewDashTab == dashTab) {
        dashTabId = OVERVIEW_TAB_ID;
    }
    else if (InputDashTab == dashTab) {
        dashTabId = INPUT_TAB_ID;
    }
    /*else if (OutputDashTab == dashTab) {
        dashTabId = OUTPUT_TAB_ID;
    }*/
    else if (ExternalToolsTab == dashTab) {
        dashTabId = EXT_TOOLS_TAB_ID;
    }
    else {
        FAIL("Unexpected dashboard tab ID!", QWebElement());
    }
    QWebElement tabContainer = doc.findFirst(dashTabId);
    SAFE_POINT(!tabContainer.isNull(), "Can't find the tab container!", QWebElement());

    // Specify if the tab has left/right inner containers
    bool hasInnerContainers = true;
    if (InputDashTab == dashTab || ExternalToolsTab == dashTab) {
        hasInnerContainers = false;
    }

    // Get the left or right inner container (if the tab allows),
    // otherwise use the whole tab as a container
    QWebElement mainContainer = tabContainer;

    if (hasInnerContainers) {
        bool left = true;
        if (0 == cntNum) {
            left = true;
        } else if (1 == cntNum) {
            left = false;
        } else if (containerSize(tabContainer, ".left-container") <= containerSize(tabContainer, ".right-container")) {
            left = true;
        } else {
            left = false;
        }

        mainContainer = tabContainer.findFirst(left ? ".left-container" : ".right-container");
        SAFE_POINT(!mainContainer.isNull(), "Can't find a container inside a tab!", QWebElement());
    }

    mainContainer.appendInside(
        "<div class=\"widget\">"
            "<div class=\"title\"><div class=\"title-content\">" + title + "</div></div>"
            "<div class=\"widget-content\"></div>"
        "</div>");

    QWebElement widget = mainContainer.lastChild();
    return widget.findFirst(".widget-content");
}
#else
void Dashboard::addWidget(const QString &title, DashboardTab dashTab, int cntNum, const QString &widgetId) {
    // Find the tab
    QString dashTabId;
    if (OverviewDashTab == dashTab) {
        dashTabId = OVERVIEW_TAB_ID;
    } else if (InputDashTab == dashTab) {
        dashTabId = INPUT_TAB_ID;
    } else if (ExternalToolsTab == dashTab) {
        dashTabId = EXT_TOOLS_TAB_ID;
    } else {
        FAIL("Unexpected dashboard tab ID!", );
    }
    dashTabId.remove("#");
    page()->runJavaScript(QString("addWidget(\"%1\", \"%2\", \"%3\", \"%4\")").arg(title).arg(dashTabId).arg(QString::number(cntNum)).arg(widgetId));
}
#endif

const WorkflowMonitor * Dashboard::monitor() {
    return _monitor;
}

void Dashboard::sl_runStateChanged(bool paused) {
    QString script = paused ? "pauseTimer()" : "startTimer()";
#if (QT_VERSION < 0x050400) //Qt 5.7
    page()->mainFrame()->evaluateJavaScript(script);
#else
    page()->runJavaScript(script);
#endif
}

void Dashboard::loadSchema() {
    QString url = dir + REPORT_SUB_DIR + WorkflowMonitor::WORKFLOW_FILE_NAME;
    emit si_loadSchema(url);
}

void Dashboard::initiateHideLoadButtonHint() {
    WorkflowSettings::setShowLoadButtonHint(false);
    emit si_hideLoadBtnHint();
}

bool Dashboard::isWorkflowInProgress() {
    return workflowInProgress;
}

void Dashboard::sl_hideLoadBtnHint() {
#if (QT_VERSION < 0x050400) //Qt 5.7
    page()->mainFrame()->evaluateJavaScript("hideLoadBtnHint()");
#else
    page()->runJavaScript("hideLoadBtnHint()");
#endif
}

#if (QT_VERSION >= 0x050400) //Qt 5.7
void Dashboard::sl_serializeContent(const QString& content) {
    
    QString fileName = dir + REPORT_SUB_DIR + DB_FILE_NAME;
    QFile file(fileName);
    bool opened = file.open(QIODevice::WriteOnly);
    if (!opened) {
        coreLog.error(tr("Can not open a file for writing: ") + fileName);
        return;
    }

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream << content;
    stream.flush();
    file.close();
}
#endif

DashboardPageController::DashboardPageController(Dashboard* parent) : QObject(parent) {
    monitor = parent->monitor();
    //set language
    lang = AppContext::getAppSettings()->getUserAppsSettings()->getTranslationFile();
    if(lang.isEmpty()){
        lang = "en";
    }else {
        lang = lang.split("_")[1];
    }
    fillWorkerParamsInfo();
}

void DashboardPageController::sl_onJsError(const QString& errorMessage) {
    coreLog.error(errorMessage);
}
void DashboardPageController::sl_checkETsLog(){

}
void DashboardPageController::openUrl(const QString &relative) {
    QString url = absolute(relative);
    QVariantMap hints;
    hints[ProjectLoaderHint_OpenBySystemIfFormatDetectionFailed] = true;
    Task *t = AppContext::getProjectLoader()->openWithProjectTask(url, hints);
    if (t) {
        AppContext::getTaskScheduler()->registerTopLevelTask(t);
    }
}

void DashboardPageController::openByOS(const QString &relative) {
    QString url = absolute(relative);
    if (!QFile::exists(url)) {
        QMessageBox::critical((QWidget*)AppContext::getMainWindow()->getQMainWindow(), tr("Error"), tr("The file does not exist"));
        return;
    }
    QDesktopServices::openUrl(QUrl("file:///" + url));
}

QString DashboardPageController::absolute(const QString &url) {
    if (QFileInfo(url).isAbsolute()) {
        return url;
    }
    return qobject_cast<Dashboard*>(parent())->directory() + url;
}


QString DashboardPageController::getLang(){
    return lang;
}
QJsonArray DashboardPageController::getWorkersParamsInfo(){
    return workersParamsInfo;
}
//Worker parametes initialization
void DashboardPageController::fillWorkerParamsInfo(){
    CHECK(monitor,)
    QList<WorkerParamsInfo> workersParamsList = monitor->getWorkersParameters();
    foreach (WorkerParamsInfo workerInfo, workersParamsList) {
        QJsonObject workerInfoJS;
        workerInfoJS["workerName"] = workerInfo.workerName;
        workerInfoJS["actor"] = workerInfo.actor->getLabel();
        QJsonArray parameters;
        foreach (Attribute* parameter, workerInfo.parameters) {
            QJsonObject parameterJS;
            parameterJS["name"] = parameter->getDisplayName();
            QVariant paramValueVariant = parameter->getAttributePureValue();
            if (paramValueVariant.canConvert< QList<Dataset> >()) {
                QList<Dataset> sets = paramValueVariant.value< QList<Dataset > >();
                foreach (const Dataset &set, sets) {
                    QString paramName = parameter->getDisplayName();
                    if (sets.size() > 1) {
                        paramName += ": <i>" + set.getName() + "</i>";
                    }
                    parameterJS["name"] = paramName;
                    QStringList urls;
                    foreach (URLContainer *c, set.getUrls()) {
                        urls << c->getUrl();
                    }
                    parameterJS["value"] = urls.join(";");
                    parameterJS["isDataset"] = true;
                    parameters.append(parameterJS);
                }
            }else{
                parameterJS["value"] = WorkflowUtils::getStringForParameterDisplayRole(paramValueVariant);
                UrlAttributeType type = WorkflowUtils::isUrlAttribute(parameter, workerInfo.actor);
                if (type == NotAnUrl || QString::compare(paramValueVariant.toString(), "default", Qt::CaseInsensitive) == 0) {
                    parameterJS["isUrl"] = false;
                }else{
                    parameterJS["isUrl"] = true;
                }
                parameters.append(parameterJS);
            }
        }
        workerInfoJS["parameters"] = parameters;
        workersParamsInfo.append(workerInfoJS);
    }
}
/************************************************************************/
/* DashboardWidget */
/************************************************************************/
#if (QT_VERSION < 0x050400) //Qt 5.7
DashboardWidget::DashboardWidget(const QWebElement &_container, Dashboard *parent)
#else
DashboardWidget::DashboardWidget(const QString &_container, Dashboard *parent)
#endif
: QObject(parent), dashboard(parent), container(_container)
{

}

/************************************************************************/
/* JavascriptAgent */
/************************************************************************/
JavascriptAgent::JavascriptAgent(Dashboard *_dashboard)
: QObject(_dashboard), dashboard(_dashboard)
{

}

void JavascriptAgent::loadSchema() {
    dashboard->loadSchema();
}

void JavascriptAgent::hideLoadButtonHint() {
    SAFE_POINT(NULL != dashboard, "NULL dashboard!", );
    dashboard->initiateHideLoadButtonHint();
}
void JavascriptAgent::setClipboardText(const QString &text) {
    QApplication::clipboard()->setText(text);
}

/************************************************************************/
/* LoadDashboardsTask */
/************************************************************************/
ScanDashboardsDirTask::ScanDashboardsDirTask()
: Task(tr("Scan dashboards directory"), TaskFlag_None)
{

}

void ScanDashboardsDirTask::run() {
    QDir outDir(WorkflowSettings::getWorkflowOutputDirectory());
    CHECK(outDir.exists(), );

    QFileInfoList dirs = outDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    foreach (const QFileInfo &info, dirs) {
        QString dirPath = info.absoluteFilePath() + "/";
        DashboardInfo dbi(dirPath);
        if (isDashboardDir(dirPath, dbi)) {
            result << dbi;
            if (dbi.opened) {
                openedDashboards << dirPath;
            }
        }
    }
}

bool ScanDashboardsDirTask::isDashboardDir(const QString &dirPath, DashboardInfo &info) {
    QDir dir(dirPath + REPORT_SUB_DIR);
    CHECK(dir.exists(), false);
    CHECK(dir.exists(DB_FILE_NAME), false);
    CHECK(dir.exists(SETTINGS_FILE_NAME), false);

    QSettings s(dirPath + REPORT_SUB_DIR + SETTINGS_FILE_NAME, QSettings::IniFormat);
    info.opened = s.value(OPENED_SETTING).toBool();
    info.name = s.value(NAME_SETTING).toString();
    return true;
}

QStringList ScanDashboardsDirTask::getOpenedDashboards() const {
    return openedDashboards;
}

QList<DashboardInfo> ScanDashboardsDirTask::getResult() const {
    return result;
}

/************************************************************************/
/* RemoveDashboardsTask */
/************************************************************************/
RemoveDashboardsTask::RemoveDashboardsTask(const QList<DashboardInfo> &_dashboards)
: Task(tr("Remove dashboards"), TaskFlag_None), dashboards(_dashboards)
{

}
void RemoveDashboardsTask::run() {
    foreach (const DashboardInfo &info, dashboards) {
        U2OpStatus2Log os;
        GUrlUtils::removeDir(info.path, os);
    }
}

/************************************************************************/
/* DashboardInfo */
/************************************************************************/
DashboardInfo::DashboardInfo() {

}

DashboardInfo::DashboardInfo(const QString &dirPath, bool _opened)
: path(dirPath), opened(_opened)
{
    dirName = QDir(path).dirName();
}

bool DashboardInfo::operator==(const DashboardInfo &other) const {
    return path == other.path;
}

} // ns

