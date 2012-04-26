include (U2Core.pri)

# Input
HEADERS += src/cmdline/CMDLineCoreOptions.h \
           src/cmdline/CMDLineHelpProvider.h \
           src/cmdline/CMDLineRegistry.h \
           src/cmdline/CMDLineUtils.h \
           src/datatype/AnnotationData.h \
           src/datatype/AnnotationSettings.h \
           src/datatype/BioStruct3D.h \
           src/datatype/DIProperties.h \
           src/datatype/DNAAlphabet.h \
           src/datatype/DNAAlphabetRegistryImpl.h \
           src/datatype/DNAChromatogram.h \
           src/datatype/DNAInfo.h \
           src/datatype/DNAQuality.h \
           src/datatype/DNASequence.h \
           src/datatype/DNATranslation.h \
           src/datatype/DNATranslationImpl.h \
           src/datatype/FeatureColors.h \
           src/datatype/MAlignment.h \
           src/datatype/MAlignmentInfo.h \
           src/datatype/Matrix44.h \
           src/datatype/PFMatrix.h \
           src/datatype/PhyTree.h \
           src/datatype/PWMatrix.h \
           src/datatype/SMatrix.h \
           src/datatype/U2Alphabet.h \
           src/datatype/U2Annotation.h \
           src/datatype/U2Assembly.h \
           src/datatype/U2Attribute.h \
           src/datatype/U2CoreAttributes.h \
           src/datatype/U2Feature.h \
           src/datatype/U2FeatureKeys.h \
           src/datatype/U2Identity.h \
           src/datatype/U2IdTypes.h \
           src/datatype/U2Msa.h \
           src/datatype/U2Range.h \
           src/datatype/U2Region.h \
           src/datatype/U2Sequence.h \
           src/datatype/U2Type.h \
           src/datatype/U2TypeIds.h \
           src/datatype/U2Variant.h \
           src/datatype/Vector3D.h \
           src/dbi/DbiDocumentFormat.h \
           src/dbi/U2AbstractDbi.h \
           src/dbi/U2AnnotationDbi.h \
           src/dbi/U2AssemblyDbi.h \
           src/dbi/U2AttributeDbi.h \
           src/dbi/U2CrossDatabaseReferenceDbi.h \
           src/dbi/U2Dbi.h \
           src/dbi/U2DbiRegistry.h \
           src/dbi/U2DbiUtils.h \
           src/dbi/U2FeatureDbi.h \
           src/dbi/U2FormatCheckResult.h \
           src/dbi/U2MsaDbi.h \
           src/dbi/U2ObjectDbi.h \
           src/dbi/U2SequenceDbi.h \
           src/dbi/U2SqlHelpers.h \
           src/dbi/U2VariantDbi.h \
           src/globals/AppContext.h \
           src/globals/AppGlobalObject.h \
           src/globals/AppResources.h \
           src/globals/AppSettings.h \
           src/globals/AutoAnnotationsSupport.h \
           src/globals/BaseDocumentFormats.h \
           src/globals/Counter.h \
           src/globals/DataBaseRegistry.h \
           src/globals/DBXRefRegistry.h \
           src/globals/DocumentFormatConfigurators.h \
           src/globals/ExternalToolRegistry.h \
           src/globals/FormatSettings.h \
           src/globals/global.h \
           src/globals/GUrl.h \
           src/globals/Identifiable.h \
           src/globals/IdRegistry.h \
           src/globals/L10n.h \
           src/globals/Log.h \
           src/globals/LogCache.h \
           src/globals/NetworkConfiguration.h \
           src/globals/PluginModel.h \
           src/globals/ProjectService.h \
           src/globals/ResourceTracker.h \
           src/globals/ServiceModel.h \
           src/globals/ServiceTypes.h \
           src/globals/Settings.h \
           src/globals/Task.h \
           src/globals/Timer.h \
           src/globals/U2OpStatus.h \
           src/globals/U2SafePoints.h \
           src/globals/UserApplicationsSettings.h \
           src/globals/Version.h \
           src/gobjects/AnnotationTableObject.h \
           src/gobjects/AssemblyObject.h \
           src/gobjects/BioStruct3DObject.h \
           src/gobjects/DNAChromatogramObject.h \
           src/gobjects/DNASequenceObject.h \
           src/gobjects/GObjectRelationRoles.h \
           src/gobjects/GObjectTypes.h \
           src/gobjects/GObjectUtils.h \
           src/gobjects/MAlignmentObject.h \
           src/gobjects/PhyTreeObject.h \
           src/gobjects/TextObject.h \
           src/gobjects/UnloadedObject.h \
           src/io/HttpFileAdapter.h \
           src/io/IOAdapter.h \
           src/io/LocalFileAdapter.h \
           src/io/RingBuffer.h \
           src/io/StringAdapter.h \
           src/io/VFSAdapter.h \
           src/io/VirtualFileSystem.h \
           src/io/ZlibAdapter.h \
           src/models/DocumentImport.h \
           src/models/DocumentModel.h \
           src/models/DocumentUtils.h \
           src/models/GHints.h \
           src/models/GObject.h \
           src/models/GObjectReference.h \
           src/models/ProjectModel.h \
           src/models/StateLockableDataModel.h \
           src/selection/AnnotationSelection.h \
           src/selection/DNASequenceSelection.h \
           src/selection/DocumentSelection.h \
           src/selection/GObjectSelection.h \
           src/selection/LRegionsSelection.h \
           src/selection/SelectionModel.h \
           src/selection/SelectionTypes.h \
           src/selection/SelectionUtils.h \
           src/selection/TextSelection.h \
           src/tasks/AddDocumentTask.h \
           src/tasks/AddSequencesToAlignmentTask.h \
           src/tasks/BackgroundTaskRunner.h \
           src/tasks/CopyDataTask.h \
           src/tasks/CreateAnnotationTask.h \
           src/tasks/DocumentProviderTask.h \
           src/tasks/ExtractAnnotatedRegionTask.h \
           src/tasks/FailTask.h \
           src/tasks/LoadDocumentTask.h \
           src/tasks/LoadRemoteDocumentTask.h \
           src/tasks/ModifySequenceObjectTask.h \
           src/tasks/MultiTask.h \
           src/tasks/RemoveAnnotationsTask.h \
           src/tasks/RemoveDocumentTask.h \
           src/tasks/ReverseSequenceTask.h \
           src/tasks/SaveDocumentStreamingTask.h \
           src/tasks/SaveDocumentTask.h \
           src/tasks/ScriptTask.h \
           src/tasks/SequenceWalkerTask.h \
           src/tasks/TaskSignalMapper.h \
           src/tasks/TaskStarter.h \
           src/tasks/TLSTask.h \
           src/util/FormatUtils.h \
           src/util/GAutoDeleteList.h \
           src/util/GUrlUtils.h \
           src/util/IOAdapterUtils.h \
           src/util/MSAUtils.h \
           src/util/QVariantUtils.h \
           src/util/SequenceUtils.h \
           src/util/TextUtils.h \
           src/util/U1AnnotationUtils.h \
           src/util/U2AlphabetUtils.h \
           src/util/U2AnnotationUtils.h \
           src/util/U2AssemblyReadIterator.h \
           src/util/U2AssemblyUtils.h \
           src/util/U2AttributeUtils.h \
           src/util/U2Bits.h \
           src/util/U2FeatureUtils.h \
           src/util/U2OpStatusUtils.h \
           src/util/U2SequenceUtils.h \
    src/tasks/TmpDirChecker.h
SOURCES += src/cmdline/CMDLineCoreOptions.cpp \
           src/cmdline/CMDLineRegistry.cpp \
           src/cmdline/CMDLineUtils.cpp \
           src/datatype/AnnotationData.cpp \
           src/datatype/AnnotationSettings.cpp \
           src/datatype/BaseAlphabets.cpp \
           src/datatype/BaseTranslations.cpp \
           src/datatype/BioStruct3D.cpp \
           src/datatype/DNAAlphabet.cpp \
           src/datatype/DNAAlphabetRegistryImpl.cpp \
           src/datatype/DNAInfo.cpp \
           src/datatype/DNAQuality.cpp \
           src/datatype/DNASequence.cpp \
           src/datatype/DNATranslation.cpp \
           src/datatype/DNATranslationImpl.cpp \
           src/datatype/FeatureColors.cpp \
           src/datatype/MAlignment.cpp \
           src/datatype/MAlignmentInfo.cpp \
           src/datatype/Matrix44.cpp \
           src/datatype/PFMatrix.cpp \
           src/datatype/PhyTree.cpp \
           src/datatype/PWMatrix.cpp \
           src/datatype/SMatrix.cpp \
           src/datatype/U2Region.cpp \
           src/datatype/Vector3D.cpp \
           src/dbi/DbiDocumentFormat.cpp \
           src/dbi/U2DbiRegistry.cpp \
           src/dbi/U2DbiUtils.cpp \
           src/dbi/U2SqlHelpers.cpp \
           src/globals/AppContext.cpp \
           src/globals/AppGlobalObject.cpp \
           src/globals/AppResources.cpp \
           src/globals/AutoAnnotationsSupport.cpp \
           src/globals/BaseDocumentFormats.cpp \
           src/globals/Counter.cpp \
           src/globals/DataBaseRegistry.cpp \
           src/globals/DBXRefRegistry.cpp \
           src/globals/DocumentFormatConfigurators.cpp \
           src/globals/ExternalToolRegistry.cpp \
           src/globals/FormatSettings.cpp \
           src/globals/GUrl.cpp \
           src/globals/Log.cpp \
           src/globals/LogCache.cpp \
           src/globals/NetworkConfiguration.cpp \
           src/globals/PluginModel.cpp \
           src/globals/ProjectService.cpp \
           src/globals/ResourceTracker.cpp \
           src/globals/ServiceModel.cpp \
           src/globals/Task.cpp \
           src/globals/Timer.cpp \
           src/globals/UserApplicationsSettings.cpp \
           src/globals/Version.cpp \
           src/gobjects/AnnotationTableObject.cpp \
           src/gobjects/AssemblyObject.cpp \
           src/gobjects/BioStruct3DObject.cpp \
           src/gobjects/DNAChromatogramObject.cpp \
           src/gobjects/DNASequenceObject.cpp \
           src/gobjects/GObjectRelationRoles.cpp \
           src/gobjects/GObjectTypes.cpp \
           src/gobjects/GObjectUtils.cpp \
           src/gobjects/MAlignmentObject.cpp \
           src/gobjects/PhyTreeObject.cpp \
           src/gobjects/TextObject.cpp \
           src/gobjects/UnloadedObject.cpp \
           src/io/HttpFileAdapter.cpp \
           src/io/IOAdapter.cpp \
           src/io/LocalFileAdapter.cpp \
           src/io/StringAdapter.cpp \
           src/io/VFSAdapter.cpp \
           src/io/VirtualFileSystem.cpp \
           src/io/ZlibAdapter.cpp \
           src/models/DocumentImport.cpp \
           src/models/DocumentModel.cpp \
           src/models/DocumentUtils.cpp \
           src/models/GHints.cpp \
           src/models/GObject.cpp \
           src/models/ProjectModel.cpp \
           src/models/StateLockableDataModel.cpp \
           src/selection/AnnotationSelection.cpp \
           src/selection/DocumentSelection.cpp \
           src/selection/GObjectSelection.cpp \
           src/selection/LRegionsSelection.cpp \
           src/selection/SelectionModel.cpp \
           src/selection/SelectionTypes.cpp \
           src/selection/SelectionUtils.cpp \
           src/tasks/AddDocumentTask.cpp \
           src/tasks/AddSequencesToAlignmentTask.cpp \
           src/tasks/BackgroundTaskRunner.cpp \
           src/tasks/CopyDataTask.cpp \
           src/tasks/CreateAnnotationTask.cpp \
           src/tasks/DocumentProviderTask.cpp \
           src/tasks/ExtractAnnotatedRegionTask.cpp \
           src/tasks/LoadDocumentTask.cpp \
           src/tasks/LoadRemoteDocumentTask.cpp \
           src/tasks/ModifySequenceObjectTask.cpp \
           src/tasks/MultiTask.cpp \
           src/tasks/RemoveAnnotationsTask.cpp \
           src/tasks/RemoveDocumentTask.cpp \
           src/tasks/ReverseSequenceTask.cpp \
           src/tasks/SaveDocumentStreamingTask.cpp \
           src/tasks/SaveDocumentTask.cpp \
           src/tasks/ScriptTask.cpp \
           src/tasks/SequenceWalkerTask.cpp \
           src/tasks/TaskSignalMapper.cpp \
           src/tasks/TaskStarter.cpp \
           src/tasks/TLSTask.cpp \
           src/util/FormatUtils.cpp \
           src/util/GAutoDeleteList.cpp \
           src/util/GUrlUtils.cpp \
           src/util/IOAdapterUtils.cpp \
           src/util/MSAUtils.cpp \
           src/util/QVariantUtils.cpp \
           src/util/SequenceUtils.cpp \
           src/util/TextUtils.cpp \
           src/util/U1AnnotationUtils.cpp \
           src/util/U2AlphabetUtils.cpp \
           src/util/U2AnnotationUtils.cpp \
           src/util/U2AssemblyReadIterator.cpp \
           src/util/U2AssemblyUtils.cpp \
           src/util/U2AttributeUtils.cpp \
           src/util/U2Bits.cpp \
           src/util/U2FeatureUtils.cpp \
           src/util/U2SequenceUtils.cpp \
    src/tasks/TmpDirChecker.cpp
TRANSLATIONS += transl/chinese.ts \
                transl/czech.ts \
                transl/english.ts \
                transl/russian.ts
