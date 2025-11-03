#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QDir>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QScrollBar>
#include <QMap>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , nextTabId(0)
    , transpilationProcess(nullptr)
    , simulatorProcess(nullptr)
    , validationProcess(nullptr)
    , transpilationSuccess(false)
{
    setWindowTitle("IDE Agricultura - DSL Compiler");
    resize(1400, 900);
    
    // =====================================================
// CONFIGURAR RUTA DEL TRANSPILADOR PARA WINDOWS
// =====================================================
// El IDE busca el transpilador en la carpeta hermana
// Estructura esperada:
//   Agricultura-DSL/
//   ├── IDE/bin/IDE-Agricultura.exe
//   └── transpilador/transpilador.exe

QString appDir = QCoreApplication::applicationDirPath();
transpiladorPath = QDir(appDir + "/../../transpilador").absolutePath();

// Verificar si existe el transpilador
QString transpiladorExe = transpiladorPath + "/transpilador.exe";
if (!QFile::exists(transpiladorExe)) {
    // Intentar ruta alternativa (mismo directorio)
    QString altPath = QDir(appDir + "/transpilador").absolutePath();
    if (QFile::exists(altPath + "/transpilador.exe")) {
        transpiladorPath = altPath;
    }
}
    
    setupUI();
    setupMenuBar();
    setupConnections();
    
    // Crear primera pestaña vacía
    createNewTab("sin título.agro");
}

MainWindow::~MainWindow()
{
    if (transpilationProcess) delete transpilationProcess;
    if (simulatorProcess) delete simulatorProcess;
    if (validationProcess) delete validationProcess;
    
    // Limpiar timers de validación
    for (auto &tab : editorTabsMap) {
        if (tab.validationTimer) delete tab.validationTimer;
    }
}

void MainWindow::setupUI()
{
    // Widget central
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    // Splitter horizontal para editores y panel de errores
    QSplitter *horizontalSplitter = new QSplitter(Qt::Horizontal, this);
    
    // Widget de pestañas para EDITORES (múltiples archivos)
    editorTabs = new QTabWidget(this);
    editorTabs->setTabsClosable(true);
    editorTabs->setMovable(true);
    QFont font("Courier", 11);
    
    // Panel de errores en tiempo real (lado derecho)
    errorPanel = new QTextEdit(this);
    errorPanel->setReadOnly(true);
    errorPanel->setFont(font);
    errorPanel->setStyleSheet("background-color: #2b2b2b; color: #ffaa00;");
    errorPanel->setMaximumWidth(350);
    errorPanel->setPlaceholderText("Los errores del archivo actual\naparecerán aquí en tiempo real...");
    
    horizontalSplitter->addWidget(editorTabs);
    horizontalSplitter->addWidget(errorPanel);
    horizontalSplitter->setStretchFactor(0, 3);
    horizontalSplitter->setStretchFactor(1, 1);
    
    // Splitter vertical para editor+errores y salidas
    mainSplitter = new QSplitter(Qt::Vertical, this);
    mainSplitter->addWidget(horizontalSplitter);
    
    // Widget de pestañas para las SALIDAS (simplificado a 3 pestañas)
    outputTabs = new QTabWidget(this);
    outputTabs->setTabPosition(QTabWidget::North);
    
    // 1. Salida del Programa
    outputConsole = new QTextEdit(this);
    outputConsole->setReadOnly(true);
    outputConsole->setFont(font);
    outputConsole->setStyleSheet("background-color: #1e1e1e; color: #00ff00;");
    
    // 2. Log de Procesos
    processLog = new QTextEdit(this);
    processLog->setReadOnly(true);
    processLog->setFont(font);
    processLog->setStyleSheet("background-color: #1e1e1e; color: #88ccff;");
    
    // 3. Código C++ Generado
    cppCodeView = new QTextEdit(this);
    cppCodeView->setReadOnly(true);
    cppCodeView->setFont(font);
    cppCodeView->setStyleSheet("background-color: #282c34; color: #abb2bf;");
    
    // Agregar pestañas
    outputTabs->addTab(outputConsole, "▶️ Salida");
    outputTabs->addTab(processLog, "📋 Proceso");
    outputTabs->addTab(cppCodeView, "⚙️ Código C++");
    
    mainSplitter->addWidget(outputTabs);
    mainSplitter->setStretchFactor(0, 2);
    mainSplitter->setStretchFactor(1, 1);
    
    mainLayout->addWidget(mainSplitter);
    
    // Barra de estado
    statusBar()->showMessage("Listo - Crea o abre archivos para comenzar | Validación en tiempo real: ✓");
}

void MainWindow::setupMenuBar()
{
    // Menú Archivo
    QMenu *fileMenu = menuBar()->addMenu("&Archivo");
    
    actionNew = new QAction("&Nuevo", this);
    actionNew->setShortcut(QKeySequence::New);
    fileMenu->addAction(actionNew);
    
    actionOpen = new QAction("&Abrir...", this);
    actionOpen->setShortcut(QKeySequence::Open);
    fileMenu->addAction(actionOpen);
    
    actionSave = new QAction("&Guardar", this);
    actionSave->setShortcut(QKeySequence::Save);
    fileMenu->addAction(actionSave);
    
    actionSaveAs = new QAction("Guardar &Como...", this);
    actionSaveAs->setShortcut(QKeySequence::SaveAs);
    fileMenu->addAction(actionSaveAs);
    
    fileMenu->addSeparator();
    
    actionExecute = new QAction("▶️ &Ejecutar", this);
    actionExecute->setShortcut(QKeySequence("F5"));
    fileMenu->addAction(actionExecute);
    
    fileMenu->addSeparator();
    
    actionExit = new QAction("&Salir", this);
    actionExit->setShortcut(QKeySequence::Quit);
    fileMenu->addAction(actionExit);
    
    // Menú Ayuda
    QMenu *helpMenu = menuBar()->addMenu("&Ayuda");
    
    actionAbout = new QAction("&Acerca de...", this);
    helpMenu->addAction(actionAbout);
}

void MainWindow::setupConnections()
{
    connect(actionNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(actionSaveAs, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(actionExecute, &QAction::triggered, this, &MainWindow::executeAll);
    connect(actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(actionExit, &QAction::triggered, this, &QWidget::close);
    
    // Conectar señales de las pestañas
    connect(editorTabs, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(editorTabs, &QTabWidget::currentChanged, this, &MainWindow::tabChanged);
}

// ============================================
// FUNCIONES AUXILIARES
// ============================================

void MainWindow::setCurrentFile(const QString &fileName)
{
    // Esta función ahora está manejada por las pestañas individuales
    Q_UNUSED(fileName);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::about()
{
    QMessageBox::about(this, "Acerca de IDE Agricultura",
        "IDE Multi-Archivo\n"
        "Lenguaje Específico de Dominio (DSL)\n"
        "de Agricultura Automatizada\n\n"
        "Características:\n"
        "✓ Editor multi-pestaña\n"
        "✓ Validación en tiempo real\n"
        "✓ Transpilación a C++\n"
        "✓ Simulación integrada\n"
        "✓ Vista de código C++ generado\n\n"
        "Versión 4.0");
}

// ============================================
// DE MANEJO DE PESTAÑAS
// ============================================

int MainWindow::createNewTab(const QString &title)
{
    // Crear nuevo editor
    CodeEditor *editor = new CodeEditor(this);
    QFont font("Courier", 11);
    editor->setFont(font);
    
    // Crear timer para validación
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(1000);
    
    // Crear estructura de pestaña
    EditorTab tab;
    tab.editor = editor;
    tab.filePath = "";
    tab.isModified = false;
    tab.validationTimer = timer;
    
    int tabId = nextTabId++;
    editorTabsMap[tabId] = tab;
    
    // Agregar al widget de pestañas
    int index = editorTabs->addTab(editor, title);
    editorTabs->setCurrentIndex(index);
    editorTabs->setTabToolTip(index, "Nuevo archivo");
    
    // Conectar señales
    connect(editor, &QPlainTextEdit::textChanged, this, &MainWindow::onTextChanged);
    connect(timer, &QTimer::timeout, this, &MainWindow::validateSyntaxRealTime);
    
    return index;
}

CodeEditor* MainWindow::getCurrentEditor()
{
    int index = editorTabs->currentIndex();
    if (index < 0) return nullptr;
    return qobject_cast<CodeEditor*>(editorTabs->widget(index));
}

QString MainWindow::getCurrentFilePath()
{
    int index = editorTabs->currentIndex();
    if (index < 0) return "";
    
    // Buscar en el mapa
    for (auto it = editorTabsMap.begin(); it != editorTabsMap.end(); ++it) {
        if (editorTabs->indexOf(it.value().editor) == index) {
            return it.value().filePath;
        }
    }
    return "";
}

int MainWindow::findTabByPath(const QString &filePath)
{
    for (auto it = editorTabsMap.begin(); it != editorTabsMap.end(); ++it) {
        if (it.value().filePath == filePath) {
            return editorTabs->indexOf(it.value().editor);
        }
    }
    return -1;
}

void MainWindow::newFile()
{
    createNewTab("sin título.agro");
    statusBar()->showMessage("Nuevo archivo creado");
}

void MainWindow::openFile()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
        "Abrir Archivos", "",
        "Archivos DSL Agricultura (*.agro);;Todos los archivos (*)");
    
    for (const QString &fileName : fileNames) {
        if (!fileName.isEmpty()) {
            // Verificar si ya está abierto
            int existingTab = findTabByPath(fileName);
            if (existingTab >= 0) {
                editorTabs->setCurrentIndex(existingTab);
                statusBar()->showMessage("Archivo ya está abierto");
                continue;
            }
            
            // Crear nueva pestaña y cargar archivo
            createNewTab(strippedName(fileName));
            loadFile(fileName);
        }
    }
}

void MainWindow::saveFile()
{
    int index = editorTabs->currentIndex();
    if (index < 0) return;
    
    QString filePath = getCurrentFilePath();
    
    if (filePath.isEmpty()) {
        saveFileAs();
    } else {
        saveTabFile(index, filePath);
    }
}

void MainWindow::saveFileAs()
{
    int index = editorTabs->currentIndex();
    if (index < 0) return;
    
    QString fileName = QFileDialog::getSaveFileName(this,
        "Guardar Archivo Como", "",
        "Archivos DSL Agricultura (*.agro);;Todos los archivos (*)");
    
    if (!fileName.isEmpty()) {
        if (!fileName.endsWith(".agro")) {
            fileName += ".agro";
        }
        saveTabFile(index, fileName);
    }
}

void MainWindow::closeTab(int index)
{
    if (index < 0 || index >= editorTabs->count()) return;
    
    if (maybeSaveTab(index)) {
        // Buscar y eliminar del mapa
        CodeEditor *editor = qobject_cast<CodeEditor*>(editorTabs->widget(index));
        for (auto it = editorTabsMap.begin(); it != editorTabsMap.end(); ++it) {
            if (it.value().editor == editor) {
                if (it.value().validationTimer) {
                    delete it.value().validationTimer;
                }
                editorTabsMap.erase(it);
                break;
            }
        }
        
        editorTabs->removeTab(index);
        
        // Si no quedan pestañas, crear una nueva
        if (editorTabs->count() == 0) {
            createNewTab("sin título.agro");
        }
    }
}

void MainWindow::tabChanged(int index)
{
    if (index < 0) return;
    
    QString filePath = getCurrentFilePath();
    if (!filePath.isEmpty()) {
        setWindowTitle(strippedName(filePath) + " - IDE Agricultura");
        statusBar()->showMessage("Archivo: " + filePath);
    } else {
        setWindowTitle("sin título - IDE Agricultura");
        statusBar()->showMessage("Archivo nuevo sin guardar");
    }
    
    // Limpiar panel de errores y revalidar
    errorPanel->clear();
    validateSyntaxRealTime();
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "IDE Agricultura",
            "No se puede leer el archivo " + fileName + ":\n" + file.errorString());
        return;
    }
    
    QTextStream in(&file);
    CodeEditor *editor = getCurrentEditor();
    if (editor) {
        editor->setPlainText(in.readAll());
    }
    file.close();
    
    // Actualizar información de la pestaña
    int index = editorTabs->currentIndex();
    for (auto it = editorTabsMap.begin(); it != editorTabsMap.end(); ++it) {
        if (editorTabs->indexOf(it.value().editor) == index) {
            it.value().filePath = fileName;
            it.value().isModified = false;
            break;
        }
    }
    
    editorTabs->setTabText(index, strippedName(fileName));
    editorTabs->setTabToolTip(index, fileName);
    setWindowTitle(strippedName(fileName) + " - IDE Agricultura");
    statusBar()->showMessage("Archivo cargado: " + fileName, 2000);
}

bool MainWindow::saveTabFile(int index, const QString &fileName)
{
    CodeEditor *editor = qobject_cast<CodeEditor*>(editorTabs->widget(index));
    if (!editor) return false;
    
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "IDE Agricultura",
            "No se puede escribir el archivo " + fileName + ":\n" + file.errorString());
        return false;
    }
    
    QTextStream out(&file);
    out << editor->toPlainText();
    file.close();
    
    // Actualizar información de la pestaña
    for (auto it = editorTabsMap.begin(); it != editorTabsMap.end(); ++it) {
        if (it.value().editor == editor) {
            it.value().filePath = fileName;
            it.value().isModified = false;
            break;
        }
    }
    
    editorTabs->setTabText(index, strippedName(fileName));
    editorTabs->setTabToolTip(index, fileName);
    setWindowTitle(strippedName(fileName) + " - IDE Agricultura");
    statusBar()->showMessage("Archivo guardado: " + fileName, 2000);
    return true;
}

bool MainWindow::maybeSaveTab(int index)
{
    CodeEditor *editor = qobject_cast<CodeEditor*>(editorTabs->widget(index));
    if (!editor) return true;
    
    // Verificar si está modificado
    bool isModified = false;
    for (auto it = editorTabsMap.begin(); it != editorTabsMap.end(); ++it) {
        if (it.value().editor == editor) {
            isModified = it.value().isModified;
            break;
        }
    }
    
    if (!isModified) return true;
    
    QMessageBox::StandardButton ret = QMessageBox::warning(this,
        "IDE Agricultura",
        "El archivo '" + editorTabs->tabText(index) + "' ha sido modificado.\n¿Deseas guardar los cambios?",
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    
    if (ret == QMessageBox::Save) {
        editorTabs->setCurrentIndex(index);
        saveFile();
        return true;
    } else if (ret == QMessageBox::Cancel) {
        return false;
    }
    return true;
}

bool MainWindow::maybeSave()
{
    return maybeSaveTab(editorTabs->currentIndex());
}

void MainWindow::onTextChanged()
{
    int index = editorTabs->currentIndex();
    if (index < 0) return;
    
    // Marcar como modificado
    CodeEditor *editor = getCurrentEditor();
    for (auto it = editorTabsMap.begin(); it != editorTabsMap.end(); ++it) {
        if (it.value().editor == editor) {
            it.value().isModified = true;
            
            // Agregar asterisco al título
            QString title = editorTabs->tabText(index);
            if (!title.endsWith("*")) {
                editorTabs->setTabText(index, title + "*");
            }
            
            // Reiniciar timer de validación
            if (it.value().validationTimer) {
                it.value().validationTimer->stop();
                it.value().validationTimer->start();
            }
            break;
        }
    }
}

// ============================================
// EJECUCIÓN Y TRANSPILACIÓN
// ============================================

void MainWindow::executeAll()
{
    // Verificar que hay una pestaña activa
    CodeEditor *editor = getCurrentEditor();
    if (!editor) {
        QMessageBox::warning(this, "IDE Agricultura",
            "No hay ningún archivo abierto para ejecutar");
        return;
    }
    
    // Obtener ruta del archivo actual
    QString currentFilePath = getCurrentFilePath();
    
    // Si no está guardado, pedir que lo guarde
    if (currentFilePath.isEmpty()) {
        QMessageBox::StandardButton ret = QMessageBox::question(this, "IDE Agricultura",
            "El archivo debe estar guardado para ejecutarse.\n¿Deseas guardarlo ahora?",
            QMessageBox::Save | QMessageBox::Cancel);
        
        if (ret == QMessageBox::Save) {
            saveFile();
            currentFilePath = getCurrentFilePath();
            if (currentFilePath.isEmpty()) {
                return; // Usuario canceló el guardado
            }
        } else {
            return;
        }
    } else {
        // Guardar cambios actuales
        saveFile();
    }
    
    // Limpiar todas las pestañas
    clearAllTabs();
    
    // Ir a la pestaña de proceso
    outputTabs->setCurrentIndex(1);
    
    // Iniciar transpilación
    statusBar()->showMessage("⏳ Ejecutando: " + strippedName(currentFilePath));
    executeTranspilation();
}

void MainWindow::clearAllTabs()
{
    outputConsole->clear();
    processLog->clear();
    cppCodeView->clear();
}

void MainWindow::executeTranspilation()
{
    QString currentFile = getCurrentFilePath();
    
    processLog->append("╔══════════════════════════════════════════════════╗");
    processLog->append("║   PROCESO DE COMPILACIÓN Y EJECUCIÓN            ║");
    processLog->append("╚══════════════════════════════════════════════════╝");
    processLog->append("");
    processLog->append("📝 Archivo: " + strippedName(currentFile));
    processLog->append("⏱️  Inicio: " + QDateTime::currentDateTime().toString("hh:mm:ss"));
    processLog->append("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    
    if (transpilationProcess) delete transpilationProcess;
    transpilationProcess = new QProcess(this);
    transpilationProcess->setWorkingDirectory(transpiladorPath);
    
    connect(transpilationProcess, &QProcess::readyReadStandardOutput, this, &MainWindow::readProcessOutput);
    connect(transpilationProcess, &QProcess::readyReadStandardError, this, &MainWindow::readProcessOutput);
    connect(transpilationProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &MainWindow::processFinished);
    
    processLog->append("\n1️⃣ Validando sintaxis...");

// IMPORTANTE: En Windows usar transpilador.exe
QString transpiladorExe = transpiladorPath + "/transpilador.exe";

if (!QFile::exists(transpiladorExe)) {
    processLog->append("<span style='color: #ff5555;'>   ❌ ERROR: No se encuentra transpilador.exe en:</span>");
    processLog->append("<span style='color: #ff5555;'>   " + transpiladorPath + "</span>");
    processLog->append("<span style='color: #ffaa00;'>   💡 Asegúrate de haber compilado el transpilador primero</span>");
    QMessageBox::critical(this, "Error", 
        "No se encuentra el transpilador.\n\n"
        "Ubicación esperada:\n" + transpiladorExe + "\n\n"
        "Por favor compila el transpilador primero con compile.bat");
    return;
}

transpilationProcess->start(transpiladorExe, QStringList() << currentFile);
}

void MainWindow::readProcessOutput()
{
    QProcess *process = qobject_cast<QProcess*>(sender());
    if (process) {
        QString output = process->readAllStandardOutput();
        QString error = process->readAllStandardError();
        
        if (!output.isEmpty()) {
            // Filtrar mensajes relevantes
            QStringList lines = output.split('\n');
            for (const QString &line : lines) {
                if (line.contains("Análisis") || line.contains("Generando") || 
                    line.contains("✓") || line.contains("Error")) {
                    processLog->append("   " + line);
                }
            }
        }
        
        if (!error.isEmpty()) {
            processLog->append("<span style='color: #ff5555;'>   ❌ " + error + "</span>");
        }
    }
}

void MainWindow::processFinished(int exitCode, QProcess::ExitStatus status)
{
    if (status == QProcess::NormalExit && exitCode == 0) {
        processLog->append("   ✅ Transpilación exitosa");
        processLog->append("\n2️⃣ Compilando C++...");
        
        // COMPILAR C++ EN WINDOWS
QProcess compileProcess;
compileProcess.setWorkingDirectory(transpiladorPath);

// Usar g++ de MinGW/MSYS2
compileProcess.start("g++", QStringList() 
    << "salida.cpp" 
    << "-o" 
    << "simulador.exe");  // ← Importante: .exe en Windows
compileProcess.waitForFinished();
        
        if (compileProcess.exitCode() == 0) {
            processLog->append("   ✅ Compilación C++ exitosa");
            processLog->append("\n3️⃣ Ejecutando simulación...");
            processLog->append("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
            
            // Mostrar código C++ generado
            showGeneratedCode();
            
            // Ejecutar simulador
            if (simulatorProcess) delete simulatorProcess;
            simulatorProcess = new QProcess(this);
            simulatorProcess->setWorkingDirectory(transpiladorPath);
            
            connect(simulatorProcess, &QProcess::readyReadStandardOutput, this, &MainWindow::readSimulatorOutput);
            connect(simulatorProcess, &QProcess::readyReadStandardError, this, &MainWindow::readSimulatorOutput);
            connect(simulatorProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                    this, &MainWindow::simulatorFinished);
            
            // Cambiar a pestaña de salida
outputTabs->setCurrentIndex(0);

QString simuladorExe = transpiladorPath + "/simulador.exe";
simulatorProcess->start(simuladorExe, QStringList());
            
        } else {
            processLog->append("   ❌ Error en compilación C++");
            QString errors = compileProcess.readAllStandardError();
            processLog->append("<span style='color: #ff5555;'>" + errors + "</span>");
            statusBar()->showMessage("❌ Error en compilación");
        }
    } else {
        processLog->append("\n   ❌ Error en transpilación");
        processLog->append("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
        statusBar()->showMessage("❌ Error en transpilación");
        
        QMessageBox::critical(this, "Error",
            "Se encontraron errores durante la transpilación.\n"
            "Revisa el panel de errores en tiempo real.");
    }
}

void MainWindow::readSimulatorOutput()
{
    QProcess *process = qobject_cast<QProcess*>(sender());
    if (process) {
        QString output = process->readAllStandardOutput();
        QString error = process->readAllStandardError();
        
        if (!output.isEmpty()) {
            outputConsole->append(output);
        }
        if (!error.isEmpty()) {
            outputConsole->append("<span style='color: #ff5555;'>" + error + "</span>");
        }
    }
}

void MainWindow::simulatorFinished(int exitCode, QProcess::ExitStatus status)
{
    if (status == QProcess::NormalExit && exitCode == 0) {
        processLog->append("\n✅ PROCESO COMPLETADO EXITOSAMENTE");
        processLog->append("⏱️  Finalizado: " + QDateTime::currentDateTime().toString("hh:mm:ss"));
        statusBar()->showMessage("✅ Ejecución completada exitosamente!");
        
        outputConsole->append("\n\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
        outputConsole->append("\n✅ Programa ejecutado correctamente");
        
    } else {
        processLog->append("\n❌ Error durante la ejecución");
        statusBar()->showMessage("❌ Error durante la ejecución");
    }
}

void MainWindow::showGeneratedCode()
{
    QString cppFile = transpiladorPath + "/salida.cpp";
    QFile file(cppFile);
    
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&file);
        cppCodeView->setPlainText(in.readAll());
        file.close();
    } else {
        cppCodeView->setPlainText("// No se pudo cargar el código C++ generado");
    }
}

// ============================================
// VALIDACIÓN EN TIEMPO REAL
// ============================================

void MainWindow::validateSyntaxRealTime()
{
    CodeEditor *editor = getCurrentEditor();
    if (!editor) return;
    
    // Si el archivo está vacío, no validar
    if (editor->toPlainText().trimmed().isEmpty()) {
        errorPanel->clear();
        errorPanel->append("📝 Escribe código para ver errores en tiempo real...");
        statusBar()->showMessage("Listo - Sin errores");
        return;
    }
    
    // Guardar temporalmente el contenido actual
    QString tempFile = transpiladorPath + "/temp_validate.agro";
    QFile file(tempFile);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << editor->toPlainText();
        file.close();
    } else {
        return;
    }
    
    errorPanel->clear();
    errorPanel->append("🔍 Validando sintaxis...\n");
    
    // Ejecutar validación rápida
    if (validationProcess) {
        validationProcess->kill();
        validationProcess->deleteLater();
    }
    
    validationProcess = new QProcess(this);
    validationProcess->setWorkingDirectory(transpiladorPath);
    
    // Capturar todas las variables necesarias en la lambda
    connect(validationProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [this, validationProcess = validationProcess, errorPanel = errorPanel, transpiladorPath = transpiladorPath](int exitCode, QProcess::ExitStatus status) {
        QString output = validationProcess->readAllStandardOutput();
        QString errorOut = validationProcess->readAllStandardError();
        
        errorPanel->clear();
        
        // Analizar errores
        bool hasErrors = false;
        QStringList lines = (output + "\n" + errorOut).split('\n');
        
        errorPanel->append("━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
        errorPanel->append("⚡ VALIDACIÓN EN TIEMPO REAL");
        errorPanel->append("━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        
        for (const QString &line : lines) {
            if (line.contains("Error en línea") || 
                line.contains("syntax error") ||
                line.contains("Carácter no reconocido")) {
                hasErrors = true;
                errorPanel->append("<span style='color: #ff5555;'>❌ " + line + "</span>");
            }
        }
        
        if (!hasErrors && (status == QProcess::NormalExit && exitCode == 0)) {
            errorPanel->append("<span style='color: #55ff55;'>✅ Sin errores detectados</span>");
            errorPanel->append("<span style='color: #55ff55;'>✅ La sintaxis es correcta</span>");
            statusBar()->showMessage("✓ Sin errores - Código válido");
        } else if (!hasErrors) {
            errorPanel->append("<span style='color: #ffaa00;'>⚠️ Advertencia: El análisis no finalizó correctamente</span>");
            statusBar()->showMessage("⚠️ Advertencia en validación");
        } else {
            errorPanel->append("\n<span style='color: #ff5555;'>━━━━━━━━━━━━━━━━━━━━━━━━━━━</span>");
            errorPanel->append("<span style='color: #ff5555;'>❌ Se encontraron errores</span>");
            statusBar()->showMessage("❌ Errores detectados");
        }
        
        // Limpiar archivo temporal
        QFile::remove(transpiladorPath + "/temp_validate.agro");
    });
    
    // Ejecutar transpilador en modo validación
    QString transpiladorExe = transpiladorPath + "/transpilador.exe";

if (!QFile::exists(transpiladorExe)) {
    errorPanel->clear();
    errorPanel->append("❌ No se encuentra transpilador.exe");
    errorPanel->append("\n📁 Ubicación esperada:");
    errorPanel->append(transpiladorPath);
    return;
}

validationProcess->start(transpiladorExe, QStringList() << tempFile);
}

// ============================================
// FUNCIONES
