/*
 *Submitted by Donald Villareal & Joseph Wagner & Kevin Sekniqi(?)
 */

#include "MainWindow.h"
#include "Globals.h"

using namespace std;

MainWindow	*g_mainWindow = NULL;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::MainWindow:
//
// Constructor. Initialize user-interface elements.
//

MainWindow::MainWindow ()
           :QMainWindow(),
           m_frameInput	 (NULL),
           m_frameOutput (NULL),
           m_framePalette(NULL),
           m_frameInfo	 (NULL),
           m_controlPanel(NULL),
           m_tabPreview	 (NULL)
{
    // set g_mainWindow
    g_mainWindow = this;

    //SETUP gui WITH actions, menus, and widgets
    createActions();
    createMenus();
    createWidgets();
    createToolBars();

    //set window size
    setWindowTitle  (tr("Tessera"));
    setMinimumSize  (600,600);
    resize          (800, 600);
}


MainWindow::~MainWindow() {}

void
MainWindow::createActions()
{
    //file menu
    m_actionNewProject=              new QAction(    "&New Project",     this        );
    m_actionNewProject->             setIcon(QIcon(  ":/icons/icons/file-new.png")   );
    m_actionNewProject->             setShortcut(    tr("Ctrl+N")                    );
    m_actionNewProject->             setStatusTip(   "Create a new file"             );
    connect(m_actionNewProject, SIGNAL(triggered()), this, SLOT(s_newProject()));

    m_actionOpenExample=             new QAction(   "&Open Examples",    this        );
    m_actionOpenExample->            setShortcut(    tr("Ctrl+O")                    );
    m_actionOpenExample->            setStatusTip(   "Open Example"                  );
    //connect(m_actionOpenExample, SIGNAL(triggered()), this, SLOT(openExample()));

    m_actionLoadProject=             new QAction(    "&Load Project",    this        );
    m_actionLoadProject->            setIcon(QIcon(  ":/icons/icons/file-load.png")  );
    m_actionLoadProject->            setShortcut(    tr("Ctrl+L")                    );
    m_actionLoadProject->            setStatusTip(   "Open Existing Project"         );
    //connect(m_actionLoadProject, SIGNAL(triggered()), this, SLOT(openFile()));

    m_actionSaveProject=             new QAction(    "&Save",            this        );
    m_actionSaveProject->            setIcon(QIcon(  ":/icons/icons/file-save.png")  );
    m_actionSaveProject->            setShortcut(    tr("Ctrl+S")                    );
    m_actionSaveProject->            setStatusTip(   "Save your current file"        );
    //connect(m_actionSaveProject, SIGNAL(triggered()), this, SLOT(saveFile()));

    m_actionSaveAs=           new QAction(    "Save As...",       this        );
    m_actionSaveAs->          setShortcut(    tr("Ctrl+Shift+S")              );
    m_actionSaveAs->          setStatusTip(   "Save file with new name"       );
    //connect(m_actionSaveAs, SIGNAL(triggered()), this, SLOT(saveAsFile()));

    m_actionSavePalette=      new QAction(    "Save &Palette",    this        );
    m_actionSavePalette->     setShortcut(    tr("Ctrl+P")                    );
    m_actionSavePalette->     setStatusTip(   "Save your current palette"     );
    //connect(m_actionSavePalette, SIGNAL(triggered()), this, SLOT(savePalette()));

    m_actionLoadPalette=      new QAction(    "Load Palette",     this        );
    m_actionLoadPalette->     setShortcut(     tr("Ctrl+G")                   );
    m_actionLoadPalette->     setStatusTip(    "Load an existing palette"     );
    //connect(m_actionLoadPalette, SIGNAL(triggered()), this, SLOT(loadPalette()));

    m_actionExport=           new QAction(    "&Export",          this        );
    m_actionExport->          setShortcut(    tr("Ctrl+E")                    );
    m_actionExport->          setStatusTip(   "Export project"                );
    //connect(m_actionExport, SIGNAL(triggered()), this, SLOT(fileexport()));

    m_actionQuit=             new QAction(    "&Quit",            this        );
    m_actionQuit->            setShortcut(    tr("Ctrl+Q")                    );
    m_actionQuit->            setStatusTip(   "Quit Program"                  );
    //connect(m_actionQuit, SIGNAL(triggered()), this, SLOT(filequit()));


    //edit menu
    m_actionUndo=             new QAction(    "Undo",             this        );
    m_actionUndo->            setIcon(QIcon(  ":/icons/icons/tool-eraser-22.png"));
    m_actionUndo->            setShortcut(    tr("Ctrl+Z")                    );
    m_actionUndo->            setStatusTip(   "Undo previous action"          );
    //connect(m_actionUndo, SIGNAL(triggered()), this, SLOT(undo()));

    m_actionRedo=             new QAction(    "Redo",             this        );
    m_actionRedo->            setIcon(QIcon(  ":/icons/icons/tool-pencil-22.png"));
    m_actionRedo->            setShortcut(    tr("Ctrl+Y")                    );
    m_actionRedo->            setStatusTip(   "Redo action"                   );
    //connect(m_actionRedo, SIGNAL(triggered()), this, SLOT(redo()));

    m_actionCut=              new QAction(    "Cut",              this        );
    m_actionCut->             setShortcut(    tr("Ctrl+X")                    );
    m_actionCut->             setStatusTip(   "Cut selection"                 );
    //connect(m_actionCut, SIGNAL(triggered()), this, SLOT(cut()));

    m_actionCopy=             new QAction(    "&Copy",            this        );
    m_actionCopy->            setIcon(QIcon(  ":/icons/icons/tool-by-color-select-22.png"));
    m_actionCopy->            setShortcut(    tr("Ctrl+C")                    );
    m_actionCopy->            setStatusTip(   "Cut selection"                 );
    //connect(m_actionCopy, SIGNAL(triggered()), this, SLOT(copy()));

    m_actionPaste=            new QAction(    "Paste",            this        );
    m_actionPaste->           setShortcut(    tr("Ctrl+V")                    );
    m_actionPaste->           setStatusTip(   "Paste selection"               );
    //connect(m_actionPaste, SIGNAL(triggered()), this, SLOT(paste()));

    m_actionFillSelection=    new QAction(    "Fill Selection",   this        );
    m_actionFillSelection->   setIcon(QIcon(  ":/icons/icons/tool-bucket-fill-22.png"));
    m_actionFillSelection->   setShortcut(    tr("Ctrl+I")                    );
    m_actionFillSelection->   setStatusTip(   "Fill selection"                );
    //connect(m_actionFillSelection, SIGNAL(triggered()), this, SLOT(fillSelection()));

    m_actionBlendTool=        new QAction(    "Blen&d Tool",      this        );
    m_actionBlendTool->       setIcon(QIcon(  ":/icons/icons/tool-color-picker-22.png"));
    m_actionBlendTool->       setShortcut(    tr("Ctrl+D")                    );
    m_actionBlendTool->       setStatusTip(   "Blend selection"               );
    //connect(m_actionBlendTool, SIGNAL(triggered()), this, SLOT(blendTool()));

    m_actionCopyCurrLayer=    new QAction(    "&Copy Current Layer",  this    );
    //m_actionCopyCurrLayer-> setIcon();
    m_actionCopyCurrLayer->   setShortcut(    tr("Ctrl+Shift+C")              );
    m_actionCopyCurrLayer->   setStatusTip(   "Copy current layer"            );
    //connect(m_actionCopyCurrLayer, SIGNAL(triggered()), this, SLOT(copyCurrLayer()));

    m_actionResetParam=       new QAction(    "Reset &All Parameters",this    );
    m_actionResetParam->      setIcon(QIcon(  ":/icons/icons/tool-none-icon.png"));
    m_actionResetParam->      setShortcut(    tr("Ctrl+A")                    );
    m_actionResetParam->      setStatusTip(   "Reset all parameters"          );
    //connect(m_actionResetParam, SIGNAL(triggered()), this, SLOT(resetParam()));

    m_actionCropInput=        new QAction(    "C&rop Input",          this    );
    m_actionCropInput->       setIcon(QIcon(  ":/icons/icons/tool-rect-select-22.png"));
    m_actionCropInput->       setShortcut(    tr("Ctrl+R")                    );
    m_actionCropInput->       setStatusTip(   "Crop Input"                    );
    //connect(m_actionCropInput, SIGNAL(triggered()), this, SLOT(cropInput()));

    m_actionCropOutput=       new QAction(    "Crop Outpu&t",         this    );
    m_actionCropOutput->      setIcon(QIcon(  ":/icons/icons/tool-fuzzy-select-22.png"));
    m_actionCropOutput->      setShortcut(    tr("Ctrl+T")                    );
    m_actionCropOutput->      setStatusTip(   "Crop Output"                   );
    //connect(m_actionCropOutput, SIGNAL(triggered()), this, SLOT(cropOutput()));


    //view menu
    m_actionZoomIn=           new QAction(    "Zoom In",              this    );
    m_actionZoomIn->          setIcon(QIcon(  ":/icons/icons/view-zoomin.png"));
    m_actionZoomIn->          setShortcut(    tr("Ctrl+=")                    );
    m_actionZoomIn->          setStatusTip(   "Zoom In"                       );
    //connect(m_actionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));

    m_actionZoomOut=          new QAction(    "Zoom Out",             this    );
    m_actionZoomOut->         setIcon(QIcon(  ":/icons/icons/view-zoomout.png"));
    m_actionZoomOut->         setShortcut(tr( "Ctrl+-")                       );
    m_actionZoomOut->         setStatusTip(   "Zoom Out"                      );
    //connect(m_actionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));

    m_actionFitWindow=        new QAction(    "Fit Window",           this    );
    //m_actionFitWindow->     setIcon();
    m_actionFitWindow->       setShortcut(    tr("Ctrl+W")                    );
    m_actionFitWindow->       setStatusTip(   "Fit Window"                    );
    //connect(m_actionFitWindow, SIGNAL(triggered()), this, SLOT(fitWindow()));

    m_actionFullscreen=       new QAction(    "&Fullscreen",          this    );
    //m_actionFullscreen->setIcon();
    m_actionFullscreen->      setShortcut(    tr("Ctrl+F")                    );
    m_actionFullscreen->      setStatusTip(   "Set to fullscreen view"        );
    //connect(m_actionFullscreen, SIGNAL(triggered()), this, SLOT(zfullscreen()));

    m_actionToggle=           new QAction(    "Toggle Sections",      this    );
    //m_actionZoomIn->        setIcon();
    m_actionToggle->          setShortcut(    tr("Ctrl+B")                    );
    m_actionToggle->          setStatusTip(   "Toggle Section"                );
    //connect(toggleInAction, SIGNAL(triggered()), this, SLOT(toggle()));

    m_actionLayerMngr=        new QAction(    "Show Layer &Manager",  this    );
    m_actionLayerMngr->       setIcon(QIcon(  ":/icons/icons/view-layer-manager.png"));
    m_actionLayerMngr->       setShortcut(    tr("Ctrl+M")                    );
    m_actionLayerMngr->       setStatusTip(   "Show Layer Manager"            );
    //connect(m_actionLayerMngr, SIGNAL(triggered()), this, SLOT(layerMngr()));

    m_actionInput=            new QAction(    "Input",                this    );
    //m_actionInput->         setIcon();
    m_actionInput->           setShortcut(    tr("1")                         );
    m_actionInput->           setStatusTip(   "Input"                         );
    //connect(m_actionInput, SIGNAL(triggered()), this, SLOT(input()));

    m_actionOutput=           new QAction(    "Output",               this    );
    //m_actionOutput->        setIcon();
    m_actionOutput->          setShortcut(    tr("2")                         );
    m_actionOutput->          setStatusTip(   "Output"                        );
    //connect(m_actionOutput, SIGNAL(triggered()), this, SLOT(output()));

    m_actionPalette=          new QAction(    "Palette",              this    );
    //m_actionPalette->       setIcon();
    m_actionPalette->         setShortcut(    tr("3")                         );
    m_actionOutput->          setStatusTip(   "Palette"                       );
    //connect(m_actionPalette, SIGNAL(triggered()), this, SLOT(palette()));

    m_actionInfo=             new QAction(    "Info",                 this    );
    //m_actionInfo->          setIcon();
    m_actionInfo->            setShortcut(    tr("4")                         );
    m_actionInfo->            setStatusTip(   "Info"                          );
    //connect(m_actionInfo, SIGNAL(triggered()), this, SLOT(info()));
}


void MainWindow::createMenus()
{
    //file menu
    QMenu *fileMenu = new QMenu;
    fileMenu=   menuBar()->     addMenu(    "&File"   );
    fileMenu->  addAction(      m_actionNewProject    );
    fileMenu->  addAction(      m_actionOpenExample   );
    fileMenu->  addAction(      m_actionLoadProject   );
    fileMenu->  addSeparator(                         );
    fileMenu->  addAction(      m_actionSaveProject   );
    fileMenu->  addAction(      m_actionSaveAs        );
    fileMenu->  addSeparator(                         );
    fileMenu->  addAction(      m_actionSavePalette   );
    fileMenu->  addAction(      m_actionLoadPalette   );
    fileMenu->  addSeparator(                         );
    fileMenu->  addAction(      m_actionExport        );
    fileMenu->  addSeparator(                         );
    fileMenu->  addAction(      m_actionQuit          );

    //edit menu
    QMenu *editMenu = new QMenu;
    editMenu=   menuBar()->     addMenu(    "&Edit"   );
    editMenu->  addAction(      m_actionUndo          );
    editMenu->  addAction(      m_actionRedo          );
    editMenu->  addSeparator(                         );
    editMenu->  addAction(      m_actionCut           );
    editMenu->  addAction(      m_actionCopy          );
    editMenu->  addAction(      m_actionPaste         );
    editMenu->  addAction(      m_actionFillSelection );
    editMenu->  addAction(      m_actionBlendTool     );
    editMenu->  addAction(      m_actionCopyCurrLayer );
    editMenu->  addSeparator(                         );
    editMenu->  addAction(      m_actionResetParam    );
    editMenu->  addSeparator(                         );
    editMenu->  addAction(      m_actionCropInput     );
    editMenu->  addAction(      m_actionCropOutput    );

    //view menu
    QMenu *viewMenu = new QMenu;
    viewMenu=   menuBar()->     addMenu(    "&View"   );
    viewMenu->  addAction(      m_actionZoomIn        );
    viewMenu->  addAction(      m_actionZoomOut       );
    viewMenu->  addAction(      m_actionFitWindow     );
    viewMenu->  addAction(      m_actionFullscreen    );
    viewMenu->  addSeparator(                         );
    viewMenu->  addAction(      m_actionToggle        );
    viewMenu->  addAction(      m_actionLayerMngr     );
    viewMenu->  addSeparator(                         );
    viewMenu->  addAction(      m_actionInput         );
    viewMenu->  addAction(      m_actionOutput        );
    viewMenu->  addAction(      m_actionPalette       );
    viewMenu->  addAction(      m_actionInfo          );
}

void MainWindow::createToolBars()
{
    // file tool bar
    QToolBar *fileToolBar = new QToolBar;
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(m_actionNewProject);
    fileToolBar->addAction(m_actionLoadProject);
    fileToolBar->addAction(m_actionSaveProject);

    // view tool bar
    QToolBar *viewToolBar = new QToolBar;
    viewToolBar = addToolBar(tr("View"));
    viewToolBar->addAction(m_actionZoomIn);
    viewToolBar->addAction(m_actionZoomOut);

    // edit tool bar
    QToolBar *editToolBar = new QToolBar;
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(m_actionRedo);
    editToolBar->addAction(m_actionUndo);
    editToolBar->addAction(m_actionCropOutput);
    editToolBar->addAction(m_actionCopy);
    editToolBar->addAction(m_actionFillSelection);
    editToolBar->addAction(m_actionBlendTool);
    editToolBar->addAction(m_actionCropInput);
    editToolBar->addSeparator();
    editToolBar->addAction(m_actionResetParam);

}

void MainWindow::createWidgets()
{

        m_tabPreview = new QTabWidget;
        m_tabPreview->setMinimumSize(512,512);
        m_tabPreview->setContentsMargins(0,0,0,0);
        m_frameInput    = new ImageWindow;
        m_frameOutput 	= new QWidget;
        m_framePalette	= new QWidget;
        m_frameInfo     = new QWidget;
        m_tabPreview->addTab(m_frameInput,	"Input");
        m_tabPreview->addTab(m_frameOutput,	"Output");
        m_tabPreview->addTab(m_framePalette,"Palette");
        m_tabPreview->addTab(m_frameInfo,	"Info");
        m_controlPanel = new ControlPanel;
        m_controlPanel->setMinimumSize(300, QSizePolicy::Expanding);

        QHBoxLayout *hbox = new QHBoxLayout;
        hbox->addWidget(m_tabPreview);
        hbox->addWidget(m_controlPanel);
        hbox->setContentsMargins(0, 0, 0, 0);

        QWidget *w = new QWidget;
        w->setLayout(hbox);
        setCentralWidget(w);
        w->setContentsMargins(0, 0, 0, 0);

}

void
MainWindow::updateInputFrame()
{
    m_frameInput->setImage(m_params.image());
}

TesseraParameters&
MainWindow::parameters()
{
    return m_params;
}

// Slot functions
void
MainWindow::s_newProject()
{
    // prompt for input filename
    QFileDialog dialog(this);

    // open the last known working directory
    if(!m_currentInDir.isEmpty())
        dialog.setDirectory(m_currentInDir);

    // display existing files and directories
    dialog.setFileMode(QFileDialog::ExistingFile);

    // invoke native file browser to select file
    QString sel("Images");
    QString file =  dialog.getOpenFileName(this,
                 "Open File", m_currentInDir,
                 "Images (*.jpg *.jpeg *.png *.bmp *.tiff *.tif);;"
                  "All files (*)", &sel);

    // no file selected.. return
    if(file.isNull())
        return;

    // update location of current directory
    m_currentInDir = QFileInfo(file).dir().absolutePath();

    // load input image
    QImage image = QImage(file);

    // check whether image could be read
    if(image.isNull()) {
        QMessageBox::critical(this,
                              "Error",
                              "Image could not be read",
                              QMessageBox::Ok);
        return;
    }
    m_params.reset();
    m_params.setOriginalImage(image);
    m_params.setImage(image);
    m_controlPanel->resetControls();
    updateInputFrame();
}

void MainWindow::s_loadProject()	{}
void MainWindow::s_saveProject()	{}
void MainWindow::s_undo()		{}
void MainWindow::s_redo()		{}
void MainWindow::s_zoomIn()		{}
void MainWindow::s_zoomOut()		{}

void MainWindow::s_showInputTab()  {m_tabPreview->setCurrentIndex(0);}
void MainWindow::s_showOutputTab() {m_tabPreview->setCurrentIndex(1);}
void MainWindow::s_showPaletteTab(){m_tabPreview->setCurrentIndex(2);}
void MainWindow::s_showInfoTab()   {m_tabPreview->setCurrentIndex(3);}
