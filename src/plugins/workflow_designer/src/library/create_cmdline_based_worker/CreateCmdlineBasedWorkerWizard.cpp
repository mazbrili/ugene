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

#include <QMessageBox>

#include <U2Core/GUrlUtils.h>
#include <U2Core/QObjectScopedPointer.h>

#include <U2Gui/DialogUtils.h>

#include <U2Lang/ActorPrototypeRegistry.h>
#include <U2Lang/HRSchemaSerializer.h>
#include <U2Lang/WorkflowEnv.h>
#include <U2Lang/WorkflowSettings.h>

#include "CreateCmdlineBasedWorkerWizard.h"
#include "WorkflowEditorDelegates.h"

namespace U2 {

#ifdef Q_OS_MAC
const QString CreateCmdlineBasedWorkerWizard::PAGE_TITLE_STYLE_SHEET = "QLabel {font-size: 20pt; padding-bottom: 10px; color: #0c3762}";
#else
const QString CreateCmdlineBasedWorkerWizard::PAGE_TITLE_STYLE_SHEET = "QLabel {font-size: 16pt; padding-bottom: 10px; color: #0c3762}";
#endif

const QString CreateCmdlineBasedWorkerWizard::ATTRIBUTES_DATA_FIELD = "attributes-data";
const QString CreateCmdlineBasedWorkerWizard::ATTRIBUTES_NAMES_FIELD = "attributes-names";
const QString CreateCmdlineBasedWorkerWizard::COMMAND_TEMPLATE_DESCRIPTION_FIELD = "command-template-description";
const QString CreateCmdlineBasedWorkerWizard::COMMAND_TEMPLATE_FIELD = "command-template";
const QString CreateCmdlineBasedWorkerWizard::INPUTS_DATA_FIELD = "inputs-data";
const QString CreateCmdlineBasedWorkerWizard::INPUTS_NAMES_FIELD = "inputs-names";
const QString CreateCmdlineBasedWorkerWizard::OUTPUTS_DATA_FIELD = "outputs-data";
const QString CreateCmdlineBasedWorkerWizard::OUTPUTS_NAMES_FIELD = "outputs-names";
const QString CreateCmdlineBasedWorkerWizard::WORKER_DESCRIPTION_FIELD = "worker-description";
const QString CreateCmdlineBasedWorkerWizard::WORKER_NAME_FIELD = "worker-name";

CreateCmdlineBasedWorkerWizard::CreateCmdlineBasedWorkerWizard(ExternalProcessConfig *_initialConfig, QWidget *_parent)
    : QWizard(_parent),
      initialConfig(_initialConfig),
      config(nullptr)
{
    init();
}

CreateCmdlineBasedWorkerWizard::~CreateCmdlineBasedWorkerWizard() {
    delete initialConfig;
    delete config;
}

ExternalProcessConfig *CreateCmdlineBasedWorkerWizard::takeConfig() {
    ExternalProcessConfig *toReturn = nullptr;
    qSwap(toReturn, config);
    return toReturn;
}

namespace {

QString removeEmptyLines(const QString &str) {
    QStringList res;
    foreach(const QString &s, str.split(QRegularExpression("(\n|\r)"))) {
        if (!s.trimmed().isEmpty()) {
            res.append(s);
        }
    }
    return res.join("\r\n");
}

}

void CreateCmdlineBasedWorkerWizard::accept() {
    QScopedPointer<ExternalProcessConfig> actualConfig(createActualConfig());
    CHECK(!actualConfig.isNull(), );

    if (nullptr != initialConfig && *initialConfig != *actualConfig) {
        int res = QMessageBox::question(this,
                                        tr("Warning"),
                                        tr("You have changed the structure of the element (name, slots, parameters' names and types). "
                                           "All elements on the scene would be removed. Do you really want to change it?\n"
                                           "You could also reset the dialog to the initial state."),
                                        QMessageBox::Yes | QMessageBox::No | QMessageBox::Reset,
                                        QMessageBox::No);
        if (QMessageBox::No == res) {
            return;
        } else if (QMessageBox::Reset == res) {
            restart();
            return;
        }
    }

    const QString serializedConfig = HRSchemaSerializer::actor2String(actualConfig.data());
    const QString dirPath = WorkflowSettings::getExternalToolDirectory();
    const QDir dir(dirPath);
    if (!dir.exists()) {
        dir.mkdir(dirPath);
    }

    actualConfig->filePath = GUrlUtils::rollFileName(dirPath + actualConfig->name + ".etc", "_");

    QFile file(actualConfig->filePath);
    file.open(QIODevice::WriteOnly);
    file.write(serializedConfig.toLatin1());
    file.close();

    config = actualConfig.take();
    done(QDialog::Accepted);
}

void CreateCmdlineBasedWorkerWizard::init() {
    addPage(new CreateCmdlineBasedWorkerWizardNamePage(initialConfig));
    addPage(new CreateCmdlineBasedWorkerWizardInputOutputPage(initialConfig));
    addPage(new CreateCmdlineBasedWorkerWizardAttributesPage(initialConfig));
    addPage(new CreateCmdlineBasedWorkerWizardCommandTemplatePage(initialConfig));

    setWizardStyle(ClassicStyle);
    setOption(IndependentPages);

    DialogUtils::setWizardMinimumSize(this);
}

ExternalProcessConfig *CreateCmdlineBasedWorkerWizard::createActualConfig() const {
    ExternalProcessConfig *config = new ExternalProcessConfig();
    config->name = field(WORKER_NAME_FIELD).toString();
    config->description = removeEmptyLines(field(WORKER_DESCRIPTION_FIELD).toString());
    config->templateDescription = removeEmptyLines(field(COMMAND_TEMPLATE_DESCRIPTION_FIELD).toString());
    config->inputs = field(INPUTS_DATA_FIELD).value<QList<DataConfig> >();
    config->outputs = field(OUTPUTS_DATA_FIELD).value<QList<DataConfig> >();
    config->attrs = field(ATTRIBUTES_DATA_FIELD).value<QList<AttributeConfig> >();
    config->cmdLine = field(COMMAND_TEMPLATE_FIELD).toString();
    return config;
}

CreateCmdlineBasedWorkerWizardNamePage::CreateCmdlineBasedWorkerWizardNamePage(ExternalProcessConfig *_initialConfig)
    : QWizardPage(nullptr),
      initialConfig(_initialConfig)
{
    setupUi(this);

    lblTitle->setStyleSheet(CreateCmdlineBasedWorkerWizard::PAGE_TITLE_STYLE_SHEET);

    registerField(CreateCmdlineBasedWorkerWizard::WORKER_NAME_FIELD + "*", leName);
    registerField(CreateCmdlineBasedWorkerWizard::WORKER_DESCRIPTION_FIELD, teDescription, "plainText", SIGNAL(textChanged()));
}

void CreateCmdlineBasedWorkerWizardNamePage::initializePage() {
    CHECK(nullptr != initialConfig, );
    leName->setText(initialConfig->name);
    teDescription->setPlainText(initialConfig->description);
}

bool CreateCmdlineBasedWorkerWizardNamePage::isComplete() const {
    const QString name = leName->text();
    if (name.isEmpty()) {
        return false;
    }

    QRegExp spaces("\\s");
    if (name.contains(spaces)) {
        return false;
    }

    QRegExp invalidSymbols("\\W");
    if (name.contains(invalidSymbols)) {
        return false;
    }

    const bool isEditing = (nullptr != initialConfig);
    if (!isEditing && nullptr != Workflow::WorkflowEnv::getProtoRegistry()->getProto(name)) {
        return false;
    }

    return true;
}

char const * const CreateCmdlineBasedWorkerWizardInputOutputPage::INPUTS_DATA_PROPERTY = "inputs-data-property";
char const * const CreateCmdlineBasedWorkerWizardInputOutputPage::INPUTS_NAMES_PROPERTY = "inputs-names-property";
char const * const CreateCmdlineBasedWorkerWizardInputOutputPage::OUTPUTS_DATA_PROPERTY = "outputs-data-property";
char const * const CreateCmdlineBasedWorkerWizardInputOutputPage::OUTPUTS_NAMES_PROPERTY = "outputs-names-property";

CreateCmdlineBasedWorkerWizardInputOutputPage::CreateCmdlineBasedWorkerWizardInputOutputPage(ExternalProcessConfig *_initialConfig)
    : QWizardPage(nullptr),
      initialConfig(_initialConfig)
{
    setupUi(this);

    lblInputsTitle->setStyleSheet(CreateCmdlineBasedWorkerWizard::PAGE_TITLE_STYLE_SHEET);
    lblOutputsTitle->setStyleSheet(CreateCmdlineBasedWorkerWizard::PAGE_TITLE_STYLE_SHEET);

    connect(pbAddInput, SIGNAL(clicked()), SLOT(sl_addInput()));
    connect(pbDeleteInput, SIGNAL(clicked()), SLOT(sl_deleteInput()));
    connect(this, SIGNAL(si_inputsChanged()), SIGNAL(completeChanged()));

    inputsModel = new CfgExternalToolModel(CfgExternalToolModel::Input);
    connect(inputsModel, SIGNAL(rowsInserted(const QModelIndex &, int, int)), SLOT(sl_updateInputsProperties()));
    connect(inputsModel, SIGNAL(rowsRemoved(const QModelIndex &, int, int)), SLOT(sl_updateInputsProperties()));
    connect(inputsModel, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), SLOT(sl_updateInputsProperties()));

    tvInput->setModel(inputsModel);
    tvInput->setItemDelegate(new ProxyDelegate());
    tvInput->horizontalHeader()->setStretchLastSection(true);
    tvInput->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    connect(pbAddOutput, SIGNAL(clicked()), SLOT(sl_addOutput()));
    connect(pbDeleteOutput, SIGNAL(clicked()), SLOT(sl_deleteOutput()));
    connect(this, SIGNAL(si_outputsChanged()), SIGNAL(completeChanged()));

    outputsModel = new CfgExternalToolModel(CfgExternalToolModel::Output);
    connect(outputsModel, SIGNAL(rowsInserted(const QModelIndex &, int, int)), SLOT(sl_updateOutputsProperties()));
    connect(outputsModel, SIGNAL(rowsRemoved(const QModelIndex &, int, int)), SLOT(sl_updateOutputsProperties()));
    connect(outputsModel, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), SLOT(sl_updateOutputsProperties()));

    tvOutput->setModel(outputsModel);
    tvOutput->setItemDelegate(new ProxyDelegate());
    tvOutput->horizontalHeader()->setStretchLastSection(true);
    tvOutput->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    QFontMetrics fm = QFontMetrics(tvInput->font());
    int columnWidth = static_cast<int>(fm.width(SEQ_WITH_ANNS) * 1.5);
    tvInput->setColumnWidth(1, columnWidth);

    fm = QFontMetrics(tvOutput->font());
    columnWidth = static_cast<int>(fm.width(SEQ_WITH_ANNS) * 1.5);
    tvOutput->setColumnWidth(1, columnWidth);

    registerField(CreateCmdlineBasedWorkerWizard::INPUTS_NAMES_FIELD, this, INPUTS_NAMES_PROPERTY, SIGNAL(si_inputsChanged()));
    registerField(CreateCmdlineBasedWorkerWizard::INPUTS_DATA_FIELD, this, INPUTS_DATA_PROPERTY, SIGNAL(si_inputsChanged()));
    registerField(CreateCmdlineBasedWorkerWizard::OUTPUTS_NAMES_FIELD, this, OUTPUTS_NAMES_PROPERTY, SIGNAL(si_outputsChanged()));
    registerField(CreateCmdlineBasedWorkerWizard::OUTPUTS_DATA_FIELD, this, OUTPUTS_DATA_PROPERTY, SIGNAL(si_outputsChanged()));
}

void CreateCmdlineBasedWorkerWizardInputOutputPage::initializePage() {
    CHECK(nullptr != initialConfig, );
    initModel(inputsModel, initialConfig->inputs);
    initModel(outputsModel, initialConfig->outputs);
}

bool CreateCmdlineBasedWorkerWizardInputOutputPage::isComplete() const {
    bool res = true;
    QRegExp invalidSymbols("\\W");

    QStringList names = field(CreateCmdlineBasedWorkerWizard::INPUTS_NAMES_FIELD).toStringList() +
                        field(CreateCmdlineBasedWorkerWizard::OUTPUTS_NAMES_FIELD).toStringList();
    foreach (const QString &name, names) {
        if (name.isEmpty()) {
            res = false;
        }
        if (name.contains(invalidSymbols)) {
            res = false;
        }
    }

    if (names.removeDuplicates() > 0) {
        res = false;
    }

    if (names.isEmpty()) {
        res = false;
    }

    return res;
}

void CreateCmdlineBasedWorkerWizardInputOutputPage::sl_addInput() {
    const int ignoredRowNumber = 0;
    inputsModel->insertRow(ignoredRowNumber, QModelIndex());
    tvInput->setCurrentIndex(inputsModel->index(inputsModel->rowCount(QModelIndex()) - 1, 0));
}

void CreateCmdlineBasedWorkerWizardInputOutputPage::sl_deleteInput() {
    inputsModel->removeRow(tvInput->currentIndex().row());
}

void CreateCmdlineBasedWorkerWizardInputOutputPage::sl_addOutput() {
    const int ignoredRowNumber = 0;
    outputsModel->insertRow(ignoredRowNumber, QModelIndex());
    tvOutput->setCurrentIndex(outputsModel->index(outputsModel->rowCount(QModelIndex()) - 1, 0));
}

void CreateCmdlineBasedWorkerWizardInputOutputPage::sl_deleteOutput() {
    outputsModel->removeRow(tvOutput->currentIndex().row());
}

void CreateCmdlineBasedWorkerWizardInputOutputPage::sl_updateInputsProperties() {
    QStringList names;
    QList<DataConfig> data;
    foreach (CfgExternalToolItem *item, inputsModel->getItems()) {
        data << item->itemData;
        names << item->getName();
    }
    setProperty(INPUTS_DATA_PROPERTY, QVariant::fromValue<QList<DataConfig> >(data));
    setProperty(INPUTS_NAMES_PROPERTY, names);
    emit si_inputsChanged();
}

void CreateCmdlineBasedWorkerWizardInputOutputPage::sl_updateOutputsProperties() {
    QStringList names;
    QList<DataConfig> data;
    foreach (CfgExternalToolItem *item, outputsModel->getItems()) {
        data << item->itemData;
        names << item->getName();
    }
    setProperty(OUTPUTS_DATA_PROPERTY, QVariant::fromValue<QList<DataConfig> >(data));
    setProperty(OUTPUTS_NAMES_PROPERTY, names);
    emit si_outputsChanged();
}

void CreateCmdlineBasedWorkerWizardInputOutputPage::initModel(QAbstractItemModel *model, const QList<DataConfig> &dataConfigs) {
    model->removeRows(0, model->rowCount());

    int row = 0;
    const int ignoredRowNumber = 0;
    foreach(const DataConfig &dataConfig, dataConfigs) {
        model->insertRow(ignoredRowNumber, QModelIndex());

        QModelIndex index = model->index(row, CfgExternalToolModel::COLUMN_NAME);
        model->setData(index, dataConfig.attrName);

        index = model->index(row, CfgExternalToolModel::COLUMN_DATA_TYPE);
        model->setData(index, dataConfig.type);

        index = model->index(row, CfgExternalToolModel::COLUMN_FORMAT);
        model->setData(index, dataConfig.format);

        index = model->index(row, CfgExternalToolModel::COLUMN_DESCRIPTION);
        model->setData(index, dataConfig.description);

        row++;
    }
}

char const * const CreateCmdlineBasedWorkerWizardAttributesPage::ATTRIBUTES_DATA_PROPERTY = "attributes-data-property";
char const * const CreateCmdlineBasedWorkerWizardAttributesPage::ATTRIBUTES_NAMES_PROPERTY = "attributes-names-property";

CreateCmdlineBasedWorkerWizardAttributesPage::CreateCmdlineBasedWorkerWizardAttributesPage(ExternalProcessConfig *_initialConfig)
    : QWizardPage(nullptr),
      initialConfig(_initialConfig)
{
    setupUi(this);

    lblTitle->setStyleSheet(CreateCmdlineBasedWorkerWizard::PAGE_TITLE_STYLE_SHEET);

    connect(pbAdd, SIGNAL(clicked()), SLOT(sl_addAttribute()));
    connect(pbDelete, SIGNAL(clicked()), SLOT(sl_deleteAttribute()));
    connect(this, SIGNAL(si_attributesChanged()), SIGNAL(completeChanged()));

    model = new CfgExternalToolModelAttributes();
    connect(model, SIGNAL(rowsInserted(const QModelIndex &, int, int)), SLOT(sl_updateAttributes()));
    connect(model, SIGNAL(rowsRemoved(const QModelIndex &, int, int)), SLOT(sl_updateAttributes()));
    connect(model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), SLOT(sl_updateAttributes()));

    tvAttributes->setModel(model);
    tvAttributes->setItemDelegate(new ProxyDelegate());
    tvAttributes->horizontalHeader()->setStretchLastSection(true);
    tvAttributes->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    registerField(CreateCmdlineBasedWorkerWizard::ATTRIBUTES_DATA_FIELD, this, ATTRIBUTES_DATA_PROPERTY);
    registerField(CreateCmdlineBasedWorkerWizard::ATTRIBUTES_NAMES_FIELD, this, ATTRIBUTES_NAMES_PROPERTY, SIGNAL(si_attributesChanged()));
}

void CreateCmdlineBasedWorkerWizardAttributesPage::initializePage() {
    CHECK(nullptr != initialConfig, );
    initModel(model, initialConfig->attrs);
}

bool CreateCmdlineBasedWorkerWizardAttributesPage::isComplete() const {
    bool res = true;

    QRegExp invalidSymbols("\\W");
    QStringList names = field(CreateCmdlineBasedWorkerWizard::ATTRIBUTES_NAMES_FIELD).toStringList();

    foreach (const QString &name, names) {
        if (name.isEmpty()) {
            res = false;
        }
        if (name.contains(invalidSymbols)) {
            res = false;
        }
    }

    names << field(CreateCmdlineBasedWorkerWizard::INPUTS_NAMES_FIELD).toStringList();
    names << field(CreateCmdlineBasedWorkerWizard::OUTPUTS_NAMES_FIELD).toStringList();

    if (names.removeDuplicates() > 0) {
        res = false;
    }

    return res;
}

void CreateCmdlineBasedWorkerWizardAttributesPage::sl_addAttribute() {
    const int ignoredRowNumber = 0;
    model->insertRow(ignoredRowNumber, QModelIndex());
    tvAttributes->setCurrentIndex(model->index(model->rowCount(QModelIndex()) - 1, 0));
}

void CreateCmdlineBasedWorkerWizardAttributesPage::sl_deleteAttribute() {
    model->removeRow(tvAttributes->currentIndex().row());
}

void CreateCmdlineBasedWorkerWizardAttributesPage::sl_updateAttributes() {
    QStringList names;
    QList<AttributeConfig> data;
    foreach (AttributeItem *item, model->getItems()) {
        AttributeConfig attributeConfig;
        attributeConfig.attrName = item->getName();
        attributeConfig.type = item->getDataType();
        attributeConfig.description = item->getDescription();
        data << attributeConfig;
        names << item->getName();
    }
    setProperty(ATTRIBUTES_DATA_PROPERTY, QVariant::fromValue<QList<AttributeConfig> >(data));
    setProperty(ATTRIBUTES_NAMES_PROPERTY, names);
    emit si_attributesChanged();
}

void CreateCmdlineBasedWorkerWizardAttributesPage::initModel(QAbstractItemModel *model, const QList<AttributeConfig> &attributeConfigs) {
    model->removeRows(0, model->rowCount());

    int row = 0;
    const int ignoredRowNumber = 0;
    foreach(const AttributeConfig &attributeConfig, attributeConfigs) {
        model->insertRow(ignoredRowNumber, QModelIndex());

        QModelIndex index = model->index(row, CfgExternalToolModelAttributes::COLUMN_NAME);
        model->setData(index, attributeConfig.attrName);

        index = model->index(row, CfgExternalToolModelAttributes::COLUMN_DATA_TYPE);
        model->setData(index, attributeConfig.type);

        index = model->index(row, CfgExternalToolModelAttributes::COLUMN_DESCRIPTION);
        model->setData(index, attributeConfig.description);

        row++;
    }
}

CreateCmdlineBasedWorkerWizardCommandTemplatePage::CreateCmdlineBasedWorkerWizardCommandTemplatePage(ExternalProcessConfig *_initialConfig)
    : QWizardPage(nullptr),
      initialConfig(_initialConfig)
{
    setupUi(this);

    registerField(CreateCmdlineBasedWorkerWizard::COMMAND_TEMPLATE_FIELD + "*", leTemplate);
    registerField(CreateCmdlineBasedWorkerWizard::COMMAND_TEMPLATE_DESCRIPTION_FIELD, tePrompter, "plainText", SIGNAL(textChanged()));
}

void CreateCmdlineBasedWorkerWizardCommandTemplatePage::initializePage() {
    if (nullptr != initialConfig) {
        leTemplate->setText(initialConfig->cmdLine);
        tePrompter->setPlainText(initialConfig->templateDescription);
    } else {
        QString commandTemplate = "<My tool>";

        const QStringList inputsNames = field(CreateCmdlineBasedWorkerWizard::INPUTS_NAMES_FIELD).toStringList();
        foreach (const QString &name, inputsNames) {
            commandTemplate += " $" + name;
        }

        const QStringList outputsNames = field(CreateCmdlineBasedWorkerWizard::OUTPUTS_NAMES_FIELD).toStringList();
        foreach (const QString &name, outputsNames) {
            commandTemplate += " $" + name;
        }

        const QStringList attributesNames = field(CreateCmdlineBasedWorkerWizard::ATTRIBUTES_NAMES_FIELD).toStringList();
        int i = 0;
        foreach (const QString &name, attributesNames) {
            commandTemplate += " -p" + QString::number(++i) + " $" + name;
        }

        leTemplate->setText(commandTemplate);
    }
}

bool CreateCmdlineBasedWorkerWizardCommandTemplatePage::validatePage() {
    const QString commandTemplate = leTemplate->text();
    QStringList names = field(CreateCmdlineBasedWorkerWizard::INPUTS_NAMES_FIELD).toStringList() +
                        field(CreateCmdlineBasedWorkerWizard::OUTPUTS_NAMES_FIELD).toStringList() +
                        field(CreateCmdlineBasedWorkerWizard::ATTRIBUTES_NAMES_FIELD).toStringList();

    QString parameters;
    foreach(const QString &name, names) {
        if (!commandTemplate.contains("$" + name)) {
            parameters += " - " + name + "\n";
        }
    }

    if (parameters.isEmpty()) {
        return true;
    }

    QObjectScopedPointer<QMessageBox> msgBox = new QMessageBox(this);
    msgBox->setWindowTitle(tr("Create Element"));
    msgBox->setText(tr("You don't use listed parameters in template string. Continue?"));
    msgBox->addButton(tr("Continue"), QMessageBox::ActionRole);
    QPushButton *cancel = msgBox->addButton(tr("Abort"), QMessageBox::ActionRole);
    msgBox->setDetailedText(parameters);
    msgBox->exec();
    CHECK(!msgBox.isNull(), false);
    if (msgBox->clickedButton() == cancel) {
        return false;
    }
    return true;
}

}   // namespace U2
