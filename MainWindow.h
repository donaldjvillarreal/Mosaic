/*
 *Submitted by Donald Villareal & Joseph Wagner & Kevin Sekniqi(?)
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtWidgets>
#include "TesseraParameters.h"
#include "ControlPanel.h"
#include "ImageWindow.h"

///////////////////////////////////////////////////////////////////////////////
///
/// \class MainWindow
/// \brief Tessera main window.
///
/// The Tessera main window consists of two main areas: a tab widget
/// on the left side, and a toolbox on the right side.
///
///////////////////////////////////////////////////////////////////////////////

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    //! Constructor.
    MainWindow();

    TesseraParameters&	parameters		();
    void			updateInputFrame	();

    //! Destructor.
    ~MainWindow();

public slots:
    // slots
    void    s_newProject        ();
    void    s_loadProject       ();
    void    s_saveProject       ();
    void    s_undo              ();
    void    s_redo              ();
    void    s_zoomIn            ();
    void    s_zoomOut           ();
    void    s_showInputTab      ();
    void    s_showOutputTab     ();
    void    s_showPaletteTab	();
    void    s_showInfoTab       ();

private:
    // create widgets
    void	createWidgets		();
    void    createToolBars      ();

    // create actions
    void	createActions		();
    void	createActionsFile	();
    void	createActionsEdit	();
    void	createActionsView	();

    // create menus
    void	createMenus         ();
    void	createMenuFile		();
    void	createMenuEdit		();
    void	createMenuView		();

    // actions
    QAction		*m_actionNewProject;
    QAction		*m_actionLoadProject;
    QAction		*m_actionSaveProject;
    QAction		*m_actionQuit;
    QAction		*m_actionUndo;
    QAction		*m_actionRedo;
    QAction		*m_actionZoomIn;
    QAction		*m_actionZoomOut;
    QAction     *m_actionFitWindow;
    QAction		*m_actionShowInputTab;
    QAction		*m_actionShowOutputTab;
    QAction		*m_actionShowPaletteTab;
    QAction		*m_actionShowInfoTab;

    //

    QAction     *m_actionOpenExample;
    QAction     *m_actionSaveAs;
    QAction     *m_actionSavePalette;
    QAction     *m_actionLoadPalette;
    QAction     *m_actionExport;
    QAction     *m_actionCut;
    QAction     *m_actionCopy;
    QAction     *m_actionPaste;
    QAction     *m_actionFillSelection;
    QAction     *m_actionBlendTool;
    QAction     *m_actionCopyCurrLayer;
    QAction     *m_actionResetParam;
    QAction     *m_actionCropInput;
    QAction     *m_actionCropOutput;
    QAction     *m_actionFullscreen;
    QAction     *m_actionToggle;
    QAction     *m_actionLayerMngr;
    QAction     *m_actionInput;
    QAction     *m_actionOutput;
    QAction     *m_actionPalette;
    QAction     *m_actionInfo;
    QString      m_currentInDir;


    //
    // widgets
    ImageWindow	*m_frameInput;
    QWidget		*m_frameOutput;
    QWidget		*m_framePalette;
    QWidget		*m_frameInfo;
    ControlPanel*m_controlPanel;
    QTabWidget	*m_tabPreview;

    // other stuff
    TesseraParameters m_params;
};

#endif // MAINWINDOW_H
