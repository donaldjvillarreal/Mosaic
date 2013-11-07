/*
 *Submitted by Donald Villareal & Joseph Wagner & Kevin Sekniqi(?)
 */
#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QtGui>
#include <QtWidgets>

class QtWidgets;
class ImageWindow : public QWidget {
    Q_OBJECT
public:
    ImageWindow(QWidget *parent=0, Qt::WindowFlags f=0);

    void	setImage	(const QImage &image);

protected:
    void	resizeEvent	(QResizeEvent *event);
    void	updatePixmap	();

    QPixmap			m_pixmap;
    QLabel		   *m_imageHolder;
private:
};

#endif	// IMAGEWINDOW_H
