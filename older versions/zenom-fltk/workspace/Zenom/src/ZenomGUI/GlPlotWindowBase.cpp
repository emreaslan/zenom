#include "GlPlotWindowBase.h"


//==============================================================================
// GlPlotWindowBase::GlPlotWindowBase
//==============================================================================
GlPlotWindowBase::GlPlotWindowBase(int x,int y,int w,int h,const char *l)
  : fltk::GlWindow(x,y,w,h,l)
{
  zoomX = 1;
  zoomY = 1;
  scaleX = 1;
  scaleY = 1;

  selectRectangle = NULL;

  autoScale = false;

  autoTranslate = false;

  LogVariableGUIArray = NULL;
}


//==============================================================================
// GlPlotWindow::drawGrid
//==============================================================================
void GlPlotWindowBase::drawGrid(double xRangeMax , double xRangeMin , double yRangeMax , double yRangeMin)
{
    double diffAxisY = yRangeMax - yRangeMin ;
    double diffAxisX = xRangeMax - xRangeMin ;


    //cout << "diffAxisY : " << diffAxisY << endl;
    //cout << "diffAxisX : " << diffAxisX << endl;

    if(std::isnan(diffAxisX) || diffAxisX == 0.0000f )
        diffAxisX = 1;
    else
        calculateDiffAxis(diffAxisX);


    if(std::isnan(diffAxisY) || diffAxisY == 0.0000f )
        diffAxisY = 1;
    else
        calculateDiffAxis(diffAxisY);


    double xBeginValue = calculateBeginValue( xRangeMin,diffAxisX );
    double yBeginValue = calculateBeginValue( yRangeMin,diffAxisY );

    

    //cout << "diffAxisY : " << diffAxisY << endl;
    //cout << "diffAxisX : " << diffAxisX << endl;


    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    fltk::glsetcolor(fltk::BLACK);

    char buf[15];

    fltk::glsetfont(labelfont(), 10 );
    // X eksenindeki degerler
    for (double counter = xBeginValue ; counter < xRangeMax+1 ; counter += diffAxisX)
    {
        if( (int)diffAxisX <= 0 )
        {
            sprintf(buf,"%.4f",counter);
            for(int i = strlen(buf)-1 ; ;--i )
                if( buf[i] == '0' )
                    buf[i] = '\000';
                else
                    break;
            fltk::gldrawtext(buf,strlen(buf),counter,yRangeMin ,0);
        }
        else
        {
            sprintf(buf,"%d",(int)counter);
            fltk::gldrawtext(buf,strlen(buf),counter,yRangeMin ,0);
        }
    }


    fltk::glsetfont(labelfont(), 10 );
    // Y eksenindeki degerler
    for (double counter = yBeginValue ; counter < yRangeMax+1 ; counter += diffAxisY )
    {
        if( (int)diffAxisY <= 0 )
        {
            sprintf(buf,"%.4f",counter);
            for(int i = strlen(buf)-1 ; ;--i )
                if( buf[i] == '0' )
                    buf[i] = '\000';
                else
                    break;

            fltk::gldrawtext(buf,strlen(buf),xRangeMin,counter,0);
        }
        else
        {
            sprintf(buf,"%d",(int)counter);
            fltk::gldrawtext(buf,strlen(buf),xRangeMin,counter,0);
        }
    }
    // X eksenine paralel Dogrular
    glColor3f(0.9,0.9,0.9);
    glBegin(GL_LINES);
    for (double counter = yBeginValue ; counter < yRangeMax+1 ; counter += diffAxisY)
    {
        glVertex2f(  xRangeMin , counter );
        glVertex2f( xRangeMax ,counter  );
    }

    glEnd();


    // Y Eksenine paralel Dogrular
    glColor3f(0.9,0.9,0.9);
    glBegin(GL_LINES);
    for (double counter = xBeginValue ; counter < xRangeMax+1 ; counter += diffAxisX )
    {
        glVertex2f( counter,yRangeMin  );
        glVertex2f( counter ,yRangeMax  );
    }

    glEnd();

        // 0 Dogrusu
    glColor3f(0.2,0.2,0.2);
    glBegin(GL_LINES);
      glVertex2f(  xRangeMin , 0 );
      glVertex2f( xRangeMax ,0  );
    glEnd();
    sprintf(buf,"%d",0);
    fltk::gldrawtext(buf,strlen(buf),xRangeMin,0,0);


    if( selectRectangle != NULL )
    {
        selectRectangle->setRanges(xRangeMin, xRangeMax, yRangeMin, yRangeMax);
        selectRectangle->draw();
    }


}


//==============================================================================
// GlPlotWindow::calculateDiffAxis
//==============================================================================
void GlPlotWindowBase::calculateDiffAxis(double& diff)
{
    int diffExp = 0;
    int multiplier = 1;

    for(int counter = -10 ; counter <= 10 ; ++counter)
        if( pow (10,counter) > diff )
        {
            diffExp = counter - 1 ;
            break;
        }

    multiplier = diff / pow(10,diffExp);

    if( multiplier < 2 )
        diff = pow(10,diffExp-1);
    else if ( multiplier < 5 )
        diff = 5 * pow(10,diffExp-1);
    else
        diff = pow(10,diffExp);

}



//==============================================================================
// GlPlotWindow::calculateDiffAxis
//==============================================================================
double GlPlotWindowBase::calculateBeginValue(double beginRange, double diff)
{
    double value;
    if( beginRange < 0 )
    {
        for (value = 0 ; value > beginRange ; value -= diff ) ;
        
    }
    else
    {
        for (value = 0 ; value < beginRange ; value += diff ) ;
    }

    return value;

}

//==============================================================================
// GlPlotWindowBase::handle
//==============================================================================
int GlPlotWindowBase::handle(int e)
{
    
    switch(e)
    {
        case MOUSEWHEEL:
            autoScale = false;
            autoTranslate = false;

            parent()->handle(2);


            
            if( fltk::event_dy() == -1)
            {
                setZoomX(getZoomX()*1.1);
                setZoomY(getZoomY()*1.1);
            }
            else if(fltk::event_dy() == 1)
            {
                setZoomX(getZoomX()/1.1);
                setZoomY(getZoomY()/1.1);
            }            
            break;

        case DRAG:
            if( fltk::RightButton == fltk::event_button() )
            {
                selectRectangle->setLastPoint( mousePosX(), mousePosY());
                
            }
            else if( fltk::LeftButton == fltk::event_button() )
            {
                autoScale = false;
                autoTranslate = false;
                parent()->handle(2);
                int diffX = preMousePosX - fltk::event_x();
                int diffY = preMousePosY - fltk::event_y();
                preMousePosX = fltk::event_x();
                preMousePosY = fltk::event_y();

                setTranslateX( calculateTransDiffX(diffX) );
                setTranslateY( calculateTransDiffY(-diffY) );

                
            }
            parent()->handle(200);

            //cout << "Drag X: " << mousePosX() << " Y: " << mousePosY() << endl;
            break;

        case RELEASE:
            if( fltk::RightButton == fltk::event_button() )
            {
                autoScale = false;
                autoTranslate = false;
                parent()->handle(2);
                setTranslateX(selectRectangle->getTranslateX());
                setTranslateY(selectRectangle->getTranslateY());
                setZoomX(selectRectangle->getScaleX());
                setZoomY(selectRectangle->getScaleY());

                delete selectRectangle;
                selectRectangle = NULL;
            }
            cursor(fltk::CURSOR_ARROW);
            break;
            
        case PUSH:
            if( fltk::RightButton == fltk::event_button() )
            {
                selectRectangle = new PlotRectangle (mousePosX(),mousePosY());
                selectRectangle->setWindowSize( w(), h() );
                cursor(fltk::CURSOR_CROSS);
            }
            else if( fltk::LeftButton == fltk::event_button() )
            {
                preMousePosX = fltk::event_x();
                preMousePosY = fltk::event_y();
                cursor(fltk::CURSOR_MOVE);
            }
            //cout << "Push X: " << mousePosX() << " Y: " << mousePosY() << endl;
            return 1;
            break;

         case MOVE:
            parent()->handle(200);
            break;
    }
    
    return fltk::Window::handle(e);
}

//==============================================================================
// GlPlotWindowBase::mousePosX
//==============================================================================
int GlPlotWindowBase::mousePosX()
{
    if( fltk::event_x() > w() )
        return w();
    else if(fltk::event_x() < 0)
        return 0;
    else
        return fltk::event_x();

}

//==============================================================================
// GlPlotWindowBase::mousePosY
//==============================================================================
int GlPlotWindowBase::mousePosY()
{
    if( fltk::event_y() > h() )
        return h();
    else if(fltk::event_y() < 0)
        return 0;
    else
        return fltk::event_y();
}

//==============================================================================
// GlPlotWindowBase::calculateTransDiffX
//==============================================================================
double GlPlotWindowBase::calculateTransDiffX(int diff)
{
    double diffValue = ( (double)diff / w()) / (getZoomX()*0.5);

    return getTranslateX() + diffValue;
}

//==============================================================================
// GlPlotWindowBase::calculateTransDiffY
//==============================================================================
double GlPlotWindowBase::calculateTransDiffY(int diff)
{
    double diffValue = ( (double)diff / h()) / (getZoomY()*0.5);

    return getTranslateY() + diffValue;
}


//==============================================================================
// GlPlotWindowBase::calculateX
//==============================================================================
double GlPlotWindowBase::calculateX()
{
    double Xrange = 1 / getZoomX() ;


    double rangeMaxX = getTranslateX() + Xrange ;
    double rangeMinX = getTranslateX() - Xrange ;


    double mouseX = rangeMinX + ( (rangeMaxX-rangeMinX)/w() * mousePosX() );

    return mouseX;

}

//==============================================================================
// GlPlotWindowBase::calculateY
//==============================================================================
double GlPlotWindowBase::calculateY()
{
    double Yrange = 1 / getZoomY() ;
    double rangeMaxY = getTranslateY() + Yrange;
    double rangeMinY = getTranslateY() - Yrange ;

    double mouseY = rangeMaxY - ( (rangeMaxY-rangeMinY)/h() * mousePosY() );

    return mouseY;

}

void GlPlotWindowBase::printLinesToMatlabFile(ofstream& pOutputFile)
{

}
