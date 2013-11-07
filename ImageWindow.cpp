/*
 *Submitted by Donald Villareal & Joseph Wagner & Kevin Sekniqi(?)
 */
#include "ImageWindow.h"

ImageWindow::ImageWindow(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    m_imageHolder = new QLabel("No Image");
    m_imageHolder->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    m_imageHolder->setSizePolicy(QSizePolicy::Expanding,
                                 QSizePolicy::Expanding);
    m_imageHolder->setScaledContents(false);
    m_imageHolder->setMinimumSize(200, 200);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(m_imageHolder);
    setLayout(vbox);
}



void
ImageWindow::setImage(const QImage &image)
{
    m_pixmap = QPixmap::fromImage(image);
    updatePixmap();
}



void
ImageWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updatePixmap();
}



void
ImageWindow::updatePixmap()
{
    // error checking
    if(m_pixmap.isNull())
        return;

    // resize content of m_imageHolder
    int w = m_imageHolder->width();
    int h = m_imageHolder->height();
    if(w < h)
        m_imageHolder->setPixmap(m_pixmap.scaledToWidth(w));
    else	m_imageHolder->setPixmap(m_pixmap.scaledToHeight(h));
}
