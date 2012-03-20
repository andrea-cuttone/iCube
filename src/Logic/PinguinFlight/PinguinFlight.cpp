#include "PinguinFlight.h"
#include <cstdio>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtGui/QTransform>
#include <QtCore/QRect>
#include <QThread>
#include <opencv/highgui.h>

// Here goes member definition


//---------------------------------------------------------------
// Slot to subscribe for event.
// Expects to receive array of pointers on quadrilaterals instances which were recognized
//---------------------------------------------------------------

PinguinFlight::PinguinFlight()
{
	penguin0 = QImage("./Logic/PinguinFlight/pinguin0.png");
	penguin90 = QImage("./Logic/PinguinFlight/pinguin90.png");
	penguin180 = QImage("./Logic/PinguinFlight/pinguin180.png");
	penguin270 = QImage("./Logic/PinguinFlight/pinguin270.png");
}

void PinguinFlight::ProcessSquares (const Square *recognizedSquares, int size)
{
	//printf("IN PENGUIN: %d\n", QThread::currentThreadId());
	Image *images = new Image [size];
	for (int i=0; i < size; i++)
	{
		QImage *img;
		if(recognizedSquares[i].GetAngle() == 0) {
			img = &penguin0;
		}
		else if(recognizedSquares[i].GetAngle() == 90) {
			img = &penguin90;
		}
		else if(recognizedSquares[i].GetAngle() == 180) {
			img = &penguin180;
		}
		else if(recognizedSquares[i].GetAngle() == 270) {
			img = &penguin270;
		}
		CvPoint centCoord = recognizedSquares [i].GetCenterCoordinates ();
		centCoord.x = centCoord.x * 6;
		centCoord.y = centCoord.y * 4;
		images[i] = Image (*img, QPoint (centCoord.x, centCoord.y));
	}
	
	emit SquaresProcessed (images, size);
	delete [] images;
}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

PinguinFlight::~PinguinFlight ()
{

}

//void GetColor()
