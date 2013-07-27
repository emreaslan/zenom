#include "TextDisplayWidget.h"

TextBuffer* TextDisplayWidget::mOutputBuffer = NULL;
TextDisplay* TextDisplayWidget::mTextDisplay = NULL;

TextDisplayWidget::TextDisplayWidget()
{    
}

TextDisplayWidget::~TextDisplayWidget()
{
}

void TextDisplayWidget::initialize(const int pWindowX, const int pWindowY)
{
    if ( mTextDisplay != NULL)
        return;

    //  --- Output --
    mOutputBuffer = new TextBuffer();
    // progamda ne olup bittini gosteren obje yaratilir
    mTextDisplay = new TextDisplay( pWindowX + 10, pWindowY + 115, 370, 170 );

    // buffer ona gosterilir, ve renk ve buyuklukler ayarlanir
    mTextDisplay->buffer( mOutputBuffer );
    mTextDisplay->color( BLACK );
    mTextDisplay->textcolor( YELLOW );
    mTextDisplay->textsize( 10 );
    mTextDisplay->append( getDateAndTime() );
    mTextDisplay->move_left();
    mTextDisplay->insert( "         Welcome to Zenom 0.99" );
    mTextDisplay->append( getDateAndTime() );
    mTextDisplay->move_left();
    mTextDisplay->insert( "  is free software and you use it freely");
    mTextDisplay->append( "\n" );
    mTextDisplay->append( getDateAndTime() );
    mTextDisplay->move_left();
    mTextDisplay->insert( "   Configuration file not loaded yet" );
    mTextDisplay->box(fltk::PLASTIC_DOWN_BOX);
}

void TextDisplayWidget::printText( const char* pInfo, int pErrCode )
{
    mTextDisplay->append( getDateAndTime() );
    mTextDisplay->move_left();
    mTextDisplay->insert("   ");

    int len = strlen( pInfo );

    if( len <= 40 )
        mTextDisplay->insert( pInfo );
    else{

        char temp[2];
        temp[1] = 0;
        for( int i = 0; i < len; ++i ){

            snprintf( temp, 2, "%c", pInfo[i]);
            mTextDisplay->insert(temp);

            if( (i + 1) % 40 == 0 )
                mTextDisplay->insert("\n                                              ");

        }

    }
    if( pErrCode != 0 ){

        mTextDisplay->insert("\n                                            ");
        mTextDisplay->insert( strerror(pErrCode) );

    }

    mTextDisplay->scroll( mTextDisplay->size(), 0 );
    mTextDisplay->redraw();
}

void TextDisplayWidget::destroy()
{
    delete mTextDisplay;
    delete mOutputBuffer;
}

//==============================================================================
// Zenom::getDateAndTime
//==============================================================================
const char *TextDisplayWidget::getDateAndTime()
{
    time_t rawtime;
    struct tm *timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    return asctime( timeinfo );
}


