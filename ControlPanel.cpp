/*
 *Submitted by Donald Villareal & Joseph Wagner & Kevin Sekniqi(?)
 */
#include "MainWindow.h"
#include "ControlPanel.h"
#include "Globals.h"
#include "HSL.h"

ControlPanel::ControlPanel(QWidget *parent, Qt::WindowFlags f)
        :QWidget(parent, f)
{
    createPanelTree();
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(m_tree);
    setLayout(vbox);
}


void ControlPanel::createPanelTree()
{
    // make a tree widget and set its properties
    m_tree = new QTreeWidget();
    m_tree->setHeaderHidden(true);	// hide tree header
    m_tree->setColumnCount(1);	// one-column tree
    m_tree->setIndentation(10);	// children indentation
    m_tree->setAnimated(true);	// animate expand/collapse
    m_tree->setSelectionMode(QAbstractItemView::NoSelection);
    m_tree->setFocusPolicy(Qt::NoFocus);
    m_tree->setSizePolicy(	QSizePolicy::Minimum,
                            QSizePolicy::Expanding);

    // create control panel groupboxes
    m_group.push_back(createGroupInput());
    m_group.push_back(createGroupSize());
    m_group.push_back(createGroupRender());
    m_group.push_back(createGroupTile());
    m_group.push_back(createGroupGrout());

    // init font and string list for control panel tree widget
    QFont headerFont("Arial", 13, QFont::Bold);
    QStringList treeNameList;
    treeNameList 	<< " Input Settings"; //add other treeItems
    treeNameList 	<< " Group Size";
    treeNameList    << " Mosaic Rendering";
    treeNameList    << " Tile Palette";
    treeNameList    << " Grout";

    // create each control panel in tree
    for(int i = 0; i < m_group.size(); ++i) {
    // make control panel header and widget
        m_header.push_back(new QTreeWidgetItem(m_tree));
        m_item.push_back(new QTreeWidgetItem(m_header[i]));

        // make pushbutton to expand/collapse control panel; set its properties
        m_button.push_back(new QPushButton(treeNameList[i]));
        m_button[i]->setFlat(true);
        m_button[i]->setFont(headerFont);
        m_button[i]->setStyleSheet("text-align: left");

        // set the header item to be a pushbutton
        m_group[i]->setMinimumWidth(300);
        m_tree->setItemWidget(m_header[i], 0, m_button[i]);

        // set the widget item to be a groupbox
        m_tree->setItemWidget(m_item[i], 0, m_group[i]);

        // init signal/slot connections to allow
        // expansion/collapse when headers are pressed
        connect(m_button[i], SIGNAL(pressed()),
                this,        SLOT (expandPanels()));
    }

    // start up with some expanded panels
    m_header[0]->setExpanded(true);
}

QGroupBox*
ControlPanel::createGroupInput()
{
    // init group box
    QGroupBox *groupBox = new QGroupBox;

    // create reset pushbuttons
    for(int i=0; i<5; i++)
        m_buttonIn[i] = new QPushButton("Reset");

    // pushbutton for resetting all parameters
    QPushButton *revertOriginal = new QPushButton("Revert to Original");

    // init slider labels
    QLabel      *label[5];
    label[0] = new QLabel("Brightness");
    label[1] = new QLabel("Contrast");
    label[2] = new QLabel("Hue");
    label[3] = new QLabel("Saturation");
    label[4] = new QLabel("Lightness");

    // create brightness/contrast sliders
    for(int i=0; i<5; ++i) {
        // create slider and init value
        m_sliderIn[i] = new QSlider(Qt::Horizontal); //create
        m_sliderIn[i]->setValue(0); //initialize

        // set range of slider values
        switch(i) {
            case 0: m_sliderIn[i]->setRange(-128, 128); break; // brightness
            case 1: m_sliderIn[i]->setRange(-100, 100); break; // contrast
            case 2: m_sliderIn[i]->setRange(-180, 180); break; // hue
            case 3: m_sliderIn[i]->setRange(-100, 100); break; // saturation
            case 4: m_sliderIn[i]->setRange(-100, 100); break; // lightness
        }

        // init label for slider value
        m_labelIn[i] = new QLabel(QString("%1").arg(0, 5));
        m_labelIn[i]->setAlignment(Qt::AlignCenter);

        // set width of reset buttons
        m_buttonIn[i]->setFixedWidth(70);
    }

    // create brightness/contrast widget
    QWidget *bcWidget = new QWidget;

    // asssemble widgets in grid
    QGridLayout *gridBC = new QGridLayout; //grid == gridBC
    gridBC->setColumnMinimumWidth(2, 35);

    for(int i = 0; i < 2; ++i) {
        gridBC->addWidget(label       [i], i, 0);
        gridBC->addWidget(m_sliderIn  [i], i, 1);
        gridBC->addWidget(m_labelIn   [i], i, 2);
        gridBC->addWidget(m_buttonIn  [i], i, 3);
    }
    bcWidget->setLayout(gridBC);

    // create hue/saturation widget
    QWidget *hslWidget = new QWidget;

    // assemble widgets in grid
    QGridLayout *gridHS = new QGridLayout;
    gridHS->setColumnMinimumWidth(2, 35);
    for(int i=2; i<5; i++) {
        gridHS->addWidget(label     [i], i, 0);
        gridHS->addWidget(m_sliderIn[i], i, 1);
        gridHS->addWidget(m_labelIn [i], i, 2);
        gridHS->addWidget(m_buttonIn[i], i, 3);
    }
    hslWidget->setLayout(gridHS); //grid2 == gridHS

    // create tab widget
    m_stackWidgetIn = new QStackedWidget;

    // create radio buttons for switching between RGB and HSL
    m_radioIn[0] = new QRadioButton("Brightness-Contrast");
    m_radioIn[0]->setChecked(true);
    m_radioIn[1] = new QRadioButton("Hue-Saturation");

    // create button group and insert the two radio buttons into it
    QButtonGroup *buttonGroupBCHS = new QButtonGroup;
    buttonGroupBCHS->addButton(m_radioIn[0], 0);
    buttonGroupBCHS->addButton(m_radioIn[1], 1);

    // add both radio buttons into a widget having a horizontal layout
    QHBoxLayout *hBoxRadio = new QHBoxLayout;
    hBoxRadio->setContentsMargins(0, 0, 0, 0);
    hBoxRadio->addWidget(m_radioIn[0]);
    hBoxRadio->addWidget(m_radioIn[1]);

    // add radio buttons, stack widget, and revertOriginal pushButton into a vbox layout
    QWidget *w = new QWidget;
    w->setContentsMargins(0, 0, 0 ,0);
    w->setLayout(hBoxRadio);

    QVBoxLayout *vBoxTop = new QVBoxLayout;
    vBoxTop->setContentsMargins(0, 0, 0, 0);
    vBoxTop->addWidget(w);
    vBoxTop->addWidget(m_stackWidgetIn);
    vBoxTop->addWidget(revertOriginal);

    m_stackWidgetIn->addWidget(bcWidget);
    m_stackWidgetIn->addWidget(hslWidget);

    groupBox->setLayout(vBoxTop); //set return value

    // Brightness/Contrast connections
    connect(buttonGroupBCHS,     SIGNAL(buttonClicked   (int)),
            m_stackWidgetIn,     SLOT  (setCurrentIndex (int)));
    connect(m_sliderIn[0],       SIGNAL(valueChanged    (int)),
            this,                SLOT  (changeBrightness(int)));
    connect(m_sliderIn[1],       SIGNAL(valueChanged    (int)),
            this,                SLOT  (changeContrast  (int)));
    connect(m_buttonIn[0],       SIGNAL(clicked            ()),
            this,                SLOT  (resetBrightness    ()));
    connect(m_buttonIn[1],       SIGNAL(clicked            ()),
            this,                SLOT  (resetContrast      ()));

    // Hue/Saturation connections
    connect(m_buttonIn[2], SIGNAL(clicked            ()),
            this,          SLOT  (resetHue           ()));
    connect(m_buttonIn[3], SIGNAL(clicked            ()),
            this,          SLOT  (resetSaturation    ()));
    connect(m_buttonIn[4], SIGNAL(clicked            ()),
            this,          SLOT  (resetLightness     ()));
    connect(m_sliderIn[2], SIGNAL(valueChanged    (int)),
            this,          SLOT  (changeHue       (int)));
    connect(m_sliderIn[3], SIGNAL(valueChanged    (int)),
            this,          SLOT  (changeSaturation(int)));
    connect(m_sliderIn[4], SIGNAL(valueChanged    (int)),
            this,          SLOT  (changeLightness (int)));

    // Revert Push Button
    connect(revertOriginal, SIGNAL(clicked()),
            this,           SLOT  (revertOriginal()));

    return groupBox;
}

QGroupBox*
ControlPanel::createGroupSize()
{
    QLabel *label[2];
    label[0] = new QLabel("Width");
    label[1] = new QLabel("Height");
    for(int i=0; i<2; i++)
    {
        label[i]->setAlignment(Qt::AlignLeft);
        label[i]->setAlignment(Qt::AlignBottom);
    }

    QTextEdit *input[2];
    for(int i=0; i<2; i++)
    {
        input[i] = new QTextEdit;
        input[i]->setFixedHeight(20);
        input[i]->verticalScrollBar()->hide();
        input[i]->setAlignment(Qt::AlignLeft);
        input[i]->setAlignment(Qt::AlignBottom);
    }

    QStackedWidget *stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(new QLabel("in"));
    stackedWidget->addWidget(new QLabel("cm"));
    stackedWidget->addWidget(new QLabel("tiles"));

    QStackedWidget *stackedWidget2 = new QStackedWidget;
    stackedWidget2->addWidget(new QLabel("in"));
    stackedWidget2->addWidget(new QLabel("cm"));
    stackedWidget2->addWidget(new QLabel("tiles"));


    QGridLayout *grid = new QGridLayout;
    grid->setColumnMinimumWidth(2,40);
    for(int i=0; i<2; i++)
    {
        grid->addWidget(label[i],i,0);
        grid->addWidget(input[i],i,1);
    }
    grid->addWidget(stackedWidget,0,2);
    grid->addWidget(stackedWidget2,1,2);

    QRadioButton *radioUS = new QRadioButton("US");
    radioUS-> setChecked(true);
    QRadioButton *radioM = new QRadioButton("Metric");
    radioM-> setChecked(false);
    QRadioButton *radioT = new QRadioButton("Tiles");
    radioT-> setChecked(false);

    QButtonGroup *bGroup = new QButtonGroup;
    QVBoxLayout *layoutRadio = new QVBoxLayout;
    layoutRadio->addWidget(radioUS);
    layoutRadio->addWidget(radioM);
    layoutRadio->addWidget(radioT);
    bGroup->addButton(radioUS,0);
    bGroup->addButton(radioM,1);
    bGroup->addButton(radioT,2);
    bGroup->setExclusive(true);

    QHBoxLayout *finalLayout = new QHBoxLayout;
    finalLayout->addLayout(grid);
    finalLayout->addLayout(layoutRadio);

    QGroupBox *groupBox = new QGroupBox;
    groupBox->setLayout(finalLayout);

    connect(bGroup,                 SIGNAL(buttonClicked(int)),
            stackedWidget,          SLOT(setCurrentIndex(int)));
    connect(bGroup,                 SIGNAL(buttonClicked(int)),
            stackedWidget2,         SLOT(setCurrentIndex(int)));

    return groupBox;
}


QGroupBox*
ControlPanel::createGroupRender()
{
    QLabel *label[4];
    label[0] = new QLabel("Style");
    label[0]->setAlignment(Qt::AlignLeft);
    label[1] = new QLabel("Dither");
    label[1]->setAlignment(Qt::AlignLeft);
    label[2] = new QLabel("0");
    label[2]->setAlignment(Qt::AlignRight);
    label[3] = new QLabel("%");
    label[3]->setAlignment(Qt::AlignLeft);
    QHBoxLayout *dithLabel = new QHBoxLayout;
    dithLabel->addWidget(label[2]);
    dithLabel->addWidget(label[3]);

    QSlider *dithslider = new QSlider(Qt::Horizontal);
    dithslider->setValue(0);
    dithslider->setRange(0, 100);

    QComboBox *comboBox = new QComboBox;
    comboBox->addItem("Standard");

    QGridLayout *grid = new QGridLayout;
    grid->setColumnMinimumWidth(2,35);
    for(int i=0; i<2; i++)
    {
        grid->addWidget(label[i],i,0);
    }
    grid->addWidget(comboBox,0,1);
    grid->addWidget(dithslider,1,1);
    grid->addLayout(dithLabel,1,2);

    QGroupBox *groupBox = new QGroupBox;
    groupBox->setLayout(grid);

    connect(dithslider,         SIGNAL(sliderMoved(int)),
            label[2],           SLOT(setNum(int)));
    return groupBox;
}

QGroupBox*
ControlPanel::createGroupTile()
{
    QComboBox *comboBox = new QComboBox;
    comboBox->addItem("0.375 -VG in");
    comboBox->addItem("0.5   -PG in");
    comboBox->addItem("0.5   -SG in");
    comboBox->addItem("0.5   -UP in");
    comboBox->addItem("0.5625-ST in");
    comboBox->addItem("0.75  -VG in");
    comboBox->addItem("1     -SG in");
    comboBox->addItem("1     -UP in");

    QHBoxLayout *tileSize = new QHBoxLayout;
    tileSize->addWidget(new QLabel("Tile Size"));
    tileSize->addWidget(comboBox);

    QRadioButton *radioAll = new QRadioButton("All");
    radioAll-> setChecked(true);
    QRadioButton *radioAvail = new QRadioButton("Available");
    radioAvail-> setChecked(false);
    QRadioButton *radioUsed = new QRadioButton("Used");
    radioUsed-> setChecked(false);

    QButtonGroup *bGroup = new QButtonGroup;
    QHBoxLayout *layoutRadio = new QHBoxLayout;
    layoutRadio->addWidget(radioAll);
    layoutRadio->addWidget(radioAvail);
    layoutRadio->addWidget(radioUsed);
    bGroup->addButton(radioAll,0);
    bGroup->addButton(radioAvail,1);
    bGroup->addButton(radioUsed,2);
    bGroup->setExclusive(true);

    QTreeWidget *tileTree = new QTreeWidget();
    tileTree->setHeaderHidden(false);	// hide tree header
    //tileTree->setIndentation(10);	// children indentation
    tileTree->setAnimated(true);	// animate expand/collapse
    tileTree->setSelectionMode(QAbstractItemView::NoSelection);
    tileTree->setFocusPolicy(Qt::NoFocus);
    tileTree->setSizePolicy(QSizePolicy::Minimum,
                            QSizePolicy::Expanding);

    QStringList headerLabels;
    headerLabels.push_back("  ");
    headerLabels.push_back("Tile");
    headerLabels.push_back("id");
    headerLabels.push_back("Avail");
    headerLabels.push_back("Used");

    tileTree->setColumnCount(headerLabels.count());
    tileTree->setHeaderLabels(headerLabels);
    tileTree->setColumnWidth(0,25);
    tileTree->setColumnWidth(1,80);
    tileTree->setColumnWidth(2,40);
    tileTree->setColumnWidth(3,50);
    tileTree->setColumnWidth(4,50);

    QStringList VGNameList;
    VGNameList 	<< " Vitreous Glass";
    VGNameList 	<< " Vitreous Glass - gold";
    VGNameList    << " Vitreous Glass - metallic";
    VGNameList    << " Vitreous Glass - opalescent";
    VGNameList    << " Vitreous Glass - silver";

    QVBoxLayout *paletteLayout = new QVBoxLayout;
    paletteLayout->addLayout(tileSize);
    paletteLayout->addLayout(layoutRadio);
    paletteLayout->addWidget(tileTree);

    QGroupBox *groupBox = new QGroupBox;
    groupBox->setLayout(paletteLayout);
    return groupBox;
}

QGroupBox*
ControlPanel::createGroupGrout()
{
    // init group box
    QGroupBox *groupBox = new QGroupBox;
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(new QPushButton("Empty"));
    groupBox->setLayout(vbox);
    return groupBox;
}

void
ControlPanel::expandPanels()
{
    for(int i=0; i<m_group.size(); ++i) {
        if(m_button[i]->isDown()) {
            if(m_header[i]->isExpanded())
                m_header[i]->setExpanded(false);
            else
                m_header[i]->setExpanded(true);
        }
    }
}


// ============================================================
// BC/HSL related slots

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ControlPanel::resetBrightness:
//
// Set brightness to 0
//
void
ControlPanel::resetBrightness()
{
    changeBrightness(0);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ControlPanel::resetContrast:
//
// Set contrast to 0
//
void
ControlPanel::resetContrast()
{
    changeContrast(0);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ControlPanel::resetHue:
//
// Set hue to 0
//
void
ControlPanel::resetHue()
{
    changeHue(0);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ControlPanel::resetSaturation:
//
// Set saturation to 0
//
void
ControlPanel::resetSaturation()
{
    changeSaturation(0);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ControlPanel::resetLightness:
//
// Set lightness to 0
//
void
ControlPanel::resetLightness()
{
    changeLightness(0);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ControlPanel::changeBrightness:
//
// Change brightness to user-specified value
//
void
ControlPanel::changeBrightness(int val)
{
    blockSignals(true);

    m_sliderIn[0]->setValue(val);
    m_labelIn[0]->setText(QString::number(val));
    g_mainWindow->parameters().setBrightness(val);
    updateInputImage(TesseraParameters::RGB);

    blockSignals(false);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ControlPanel::changeContrast:
//
// Change contrast to user-specified value
//
void
ControlPanel::changeContrast(int val)
{
    blockSignals(true);

    m_sliderIn[1]->setValue(val);
    m_labelIn[1]->setText(QString::number(val));
    g_mainWindow->parameters().setContrast(val);
    updateInputImage(TesseraParameters::RGB);

    blockSignals(false);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ControlPanel::changeHue:
//
// Change hue to user-specified value
//
void
ControlPanel::changeHue(int val)
{
    blockSignals(true);

    m_sliderIn[2]->setValue(val);
    m_labelIn[2]->setText(QString::number(val));
    g_mainWindow->parameters().setHue(val);
    updateInputImage(TesseraParameters::HSL);

    blockSignals(false);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ControlPanel::changeSaturation:
//
// Change saturation to user-specified value
//
void
ControlPanel::changeSaturation(int val)
{
    blockSignals(true);

    m_sliderIn[3]->setValue(val);
    m_labelIn[3]->setText(QString::number(val));
    g_mainWindow->parameters().setSaturation(val);
    updateInputImage(TesseraParameters::HSL);

    blockSignals(false);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ControlPanel::changeLightness:
//
// Change lightness to user-specified value
//
void
ControlPanel::changeLightness(int val)
{
    blockSignals(true);

    m_sliderIn[4]->setValue(val);
    m_labelIn[4]->setText(QString::number(val));
    g_mainWindow->parameters().setLightness(val);
    updateInputImage(TesseraParameters::HSL);

    blockSignals(false);
}



void
ControlPanel::resetImage()
{
    m_image = QImage();
}



void
ControlPanel::resetControls()
{
    resetInputControls();
}



void
ControlPanel::resetInputControls()
{
    blockSignals(true);

    for(int i=0; i<5; ++i)
    {
        m_sliderIn[i]->setValue(0);
        m_labelIn[i]->setText(QString::number(0));
    }
    resetImage();

    blockSignals(false);
}



void
ControlPanel::revertOriginal()
{
    // error checking
    TesseraParameters &params = g_mainWindow->parameters();
    const QImage &origImage = params.originalImage();
    const QImage &curImage = params.image();
    if(origImage.isNull() || curImage.isNull())
    {
        for(int i=0; i<5; ++i)
        {
            m_sliderIn[i]->setValue(0);
            m_labelIn[i]->setText(QString::number(0));
        }
        return;
    }

    g_mainWindow->parameters().setBrightness(0);
    g_mainWindow->parameters().setContrast	(0);
    g_mainWindow->parameters().setHue       (0);
    g_mainWindow->parameters().setSaturation(0);
    g_mainWindow->parameters().setLightness	(0);
    resetInputControls();

    m_image = origImage;
    params.setImage(m_image);
    g_mainWindow->updateInputFrame();
}



int
ControlPanel::updateInputImage(TesseraParameters::ColorMode mode)
{
    // error checking
    TesseraParameters &params = g_mainWindow->parameters();
    const QImage &origImage = params.originalImage();
    const QImage &curImage = params.image();
    if(origImage.isNull() || curImage.isNull())
        return 0;

    if(m_image.isNull())
        m_image = origImage;

    // update colormode and current image
    if(params.colorMode() != mode)
        m_image = curImage;
    params.setColorMode(mode);

    QImage inImage = m_image;
    QImage outImage;
    if(params.colorMode() == TesseraParameters::RGB)
    {   // brightness-contrast
        // get contrast and brightness
        int	contrast	= params.contrast();
        int	brightness	= params.brightness();

        // init slope of intensity ramp
        double	c;
        if(contrast >= 0)
            c = contrast/25. + 1.0;   // slope: 1 to 5
        else	c = 1. + (contrast/133.); // slope: 1 to 0

        // init lookup table: multiply by contrast; add brightness
        int lut[256];
        for(int v=0; v<256; v++) {
            int i = (v - 128)*c + (128 + brightness);
            lut[v] = CLIP(i, 0, 255); // over 205, all will get the same value=255
        }

        // init input dimensions
        int w = inImage.width ();
        int h = inImage.height();

        // create output image
        outImage = QImage(w, h, QImage::Format_RGB32);

        // apply lookup table to source image to make input image
        for(int y=0; y<h; y++) {
            const QRgb *src = (const QRgb*) inImage.scanLine(y);
            QRgb *out  = (QRgb*) outImage.scanLine(y);
            for(int x=0; x<w; x++) {
                // set transparent pixels to white
                if(qAlpha(src[x]) < 128) {
                    *out++ = qRgb(255, 255, 255);
                } else {
                    *out++ = qRgb(lut[qRed  (src[x])],
                                  lut[qGreen(src[x])],
                                  lut[qBlue (src[x])]);
                }
            }
        }
    }
    else
    {	// hue-saturation
        double h = params.hue() / 180.0;
        double s = params.saturation() / 100.0;
        double l = params.lightness() / 100.0;
        HSL hsl;
        hsl.setHue	 (HSL::AllHues, h);
        hsl.setSaturation(HSL::AllHues, s);
        hsl.setLightness (HSL::AllHues, l);
        hsl.adjustHueSaturation(inImage, outImage);
    }
    params.setImage(outImage);
    g_mainWindow->updateInputFrame();

    return 1;
}
