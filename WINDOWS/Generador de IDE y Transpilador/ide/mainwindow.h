#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QProcess>
#include <QSplitter>
#include <QToolBar>
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QFont>
#include <QFile>
#include <QTextStream>
#include <QTabWidget>
#include <QTimer>
#include <QMap>
#include "codeeditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Estructura para manejar cada archivo
struct EditorTab {
    CodeEditor* editor;
    QString filePath;
    bool isModified;
    QTimer* validationTimer;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void closeTab(int index);
    void tabChanged(int index);
    void executeAll();
    void about();
    void onTextChanged();
    void validateSyntaxRealTime();

private:
    void setupUI();
    void setupMenuBar();
    void setupConnections();
    void readProcessOutput();
    void readSimulatorOutput();
    void processFinished(int exitCode, QProcess::ExitStatus status);
    void simulatorFinished(int exitCode, QProcess::ExitStatus status);
    bool maybeSave();
    bool maybeSaveTab(int index);
    void loadFile(const QString &fileName);
    bool saveTabFile(int index, const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    void clearAllTabs();
    void executeTranspilation();
    void showGeneratedCode();
    
    // Funciones para manejo de pestañas
    int createNewTab(const QString &title = "sin título");
    CodeEditor* getCurrentEditor();
    QString getCurrentFilePath();
    int findTabByPath(const QString &filePath);

private:
    Ui::MainWindow *ui;
    
    // Widgets principales
    QTabWidget *editorTabs;  // Pestañas de editores
    QTabWidget *outputTabs;  // Pestañas de salida
    QTextEdit *outputConsole;     // Salida del programa
    QTextEdit *processLog;        // Log de procesos
    QTextEdit *cppCodeView;       // Código C++ generado
    QTextEdit *errorPanel;
    QSplitter *mainSplitter;
    
    // Barra de herramientas
    QToolBar *toolBar;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionClose;
    QAction *actionExecute;
    QAction *actionAbout;
    QAction *actionExit;
    
    // Mapa de pestañas de editor
    QMap<int, EditorTab> editorTabsMap;
    int nextTabId;
    
    // Procesos para cada fase
    QProcess *transpilationProcess;
    QProcess *simulatorProcess;
    QProcess *validationProcess;
    
    // Directorio del transpilador
    QString transpiladorPath;
    
    // Control de fases
    bool transpilationSuccess;
};

#endif // MAINWINDOW_H
