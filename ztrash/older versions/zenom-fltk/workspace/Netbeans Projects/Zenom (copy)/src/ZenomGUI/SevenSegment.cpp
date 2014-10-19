//
// "$Id SevenSegment.cxx Thu Feb 2 2006 z_hossain $"
//
// Seven segment for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2005 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to: 
//
//             md_z_hossain@yahoo.com
//

#include <fltk/Box.h>
#include <fltk/draw.h>
#include <fltk/Widget.h>
#include <string.h>

#include "SevenSegment.h"

using namespace fltk;

/*! \class fltk::SevenSegment

	Display decimal and hexadecimal integer and floating point number 
	with usual seven segment look

	you can precisely control the format of representation because it 
	takes the value as character pointer.
	
	\image html sevenseg.gif
*/

/*! \fn Flags SevenSegment::align_text() const
	Returns the alignment value
	\sa void SevenSegment::align_text(Flags a)
*/

/*! \fn void SevenSegment::align_text(Flags a)
	Sets the alignment value
	The value can be any of these constants
		- FL_ALIGN_LEFT
		- FL_ALIGN_RIGHT
		- FL_ALIGN_CENTER
*/
						
/*! \fn int SevenSegment::unit_w() const
	Return the width of a unit seven segment cell.
*/

/*! \fn void SevenSegment::unit_w(int w)
	Set the width \a w of a unit seven segment cell.
*/

/*! \fn int SevenSegment::unit_h() const
	Returns the height of a unit seven segment cell.
*/

/*! \fn void SevenSegment::unit_h(int h)
	Sets the width \a h of a unit seven segment cell.
*/

/*! \fn short SevenSegment::unit_gap() const
	Returns the gap between two unit cells
*/

/*! \fn void SevenSegment::unit_gap(short g)
	Sets the gap \a g between two unit cells
*/

/*! \fn short SevenSegment::segment_gap() const
	Returns the gap between any two segments
*/

/*! \fn void SevenSegment::segment_gap(short g)
	Sets the gap \a g between any two segments
*/

/*! \fn short SevenSegment::thickness() const
	Returns the segment line width or thickness
*/

/*! \fn void SevenSegment::thickness(short t)
	Sets the segment line width or thickness \a t.
*/

/*! \fn short SevenSegment::dot_len() const
	Returns the square one edge length of decimal point
*/

/*! \fn void SevenSegment::dot_len(short l)
	Sets the square one edge length \a l of decimal point
*/

/*
      a
   IIIIIII
 f I     I  b
   I  g  I
   IIIIIII
 e I     I  c
   I     I
   IIIIIII
      d

0abcdefg
01111110 = 7E = 0
00110000 = 30 = 1
01101101 = 6D = 2
01111001 = 79 = 3
00110011 = 33 = 4
01011011 = 5B = 5
01011111 = 5F = 6
01110000 = 70 = 7
01111111 = 7F = 8
01111011 = 7B = 9
00010101 = 15 = n
.
.
.
*/
const uchar SevenSegment::data_seg[DATA_SIZE] = {
	0x00,
	0x7E,						//0
	0x30,						//1
	0x6D,						//2
	0x79,						//3
	0x33,						//4
	0x5B,						//5
	0x5F,						//6
	0x70,						//7
	0x7F,						//8
	0x7B,						//9
	0x77,						//A
	0x1F,						//B
	0x4E,						//C
	0x3D,						//D
	0x4F,						//E
	0x47,						//F
	0x01,						//-
	0xA0,						//.
        0x15,						//n
	0x00,						//' '  repeat the first one
};

/*!
	Construct a seven segment
*/
SevenSegment::SevenSegment(int x, int y, int w, int h, const char *l) : Widget(x, y, w, h, l) {
	unit_h_ = (int)(SevenSegment::h() * (7.00 / 10.00));
	unit_w_ = (int)(unit_h_ * (3.00 / 5.00));
	seg_color_ = BLACK;
	align_ = ALIGN_CENTER;
	box(fltk::ENGRAVED_BOX);
	thickness((int)(unit_w_ * (3.00 / 10.00)));
	seg_gap_ = 0;
	unit_gap_ = 4;
	dot_len_ = int((unit_w_ + 2)/ 3.0);
        value_ = NULL;
	value(" ");
}

/*!
	Sets the string to display. The character must be any of [0-9], 
	[A-F], [a-f], -, space. In short any hexadecimal digit.
*/
void SevenSegment::value(const char *a) {
	int i = strlen(a);
	if(value_ != 0) {
		if( i > ARRAY_SIZE && (unsigned)i > strlen(value_)) {
			delete [] value_;
			value_ = new char[i];
		}
	}
	else {
		value_ = new char[i > ARRAY_SIZE ? i : ARRAY_SIZE];
	}
	for(i = 0; a[i]; i++) {
		if(a[i] >= 0x30 && a[i] <= 0x39) {
			value_[i] = a[i] - 0x2F;
		}
		else if(a[i] >= 0x41 && a[i] <= 0x46) {
			value_[i] = a[i] - 0x36;
		}
		else if(a[i] >= 0x61 && a[i] <= 0x66) {
			value_[i] = a[i] - 0x56;
		}
		else if(a[i] == '-') {
			value_[i] = 0x11;
		}
		else if(a[i] == ' ') {
			value_[i] = 0x13;
		}
		else if(a[i] == '.') {
			value_[i] = 0x12;
		}
                else if(a[i] == 'n' || a[i] == 'N') {
			value_[i] = 19;
		}
		else {
			value_[i] = 0x13;
		}
	}
	value_[i] = '\0';
	redraw();
}

void SevenSegment::draw() {
	drawstyle(style(), flags());
	
	Rectangle r(w(), h());
	Box* box_ = box();
	box_->draw(r);
	box_->inset(r);

	if (!box_->fills_rectangle()) draw_background();
	push_clip(r);

	int txtw = (unit_w_ + unit_gap_) * strlen(value_) - unit_gap_;
	for(int i = 0; value_[i]; i++) {//in case many decimal points
		if(value_[i] == 0x12) txtw -= unit_w_ - dot_len_; 
	}
	switch(align_) {
		case ALIGN_LEFT:
			break;
		case ALIGN_RIGHT:
			r.move_x(r.w() - txtw);
			break;
		case ALIGN_CENTER:
			r.move_x((r.w() - txtw) / 2);
			break;
	}
	r.move_y((r.h() - unit_h_) / 2);
	
	setcolor(active_r() ? textcolor() : inactive(seg_color_));
	int xx = r.x();
	
	for(int i = 0; value_[i]; i++) {
		if(value_[i] == 0x12) {
			fillrect(Rectangle(xx, r.y() + unit_h_ + 1 - dot_len_, dot_len_, dot_len_));//you may use pie
			xx += (dot_len_ + unit_gap_);
		}
		else {
			draw_seg(data_seg[(int)value_[i]], xx, r.y(), unit_w_, unit_h_); //casting just to avoid warring
			xx += (unit_w_ + unit_gap_);
		}
	}
	pop_clip();
}

void SevenSegment::draw_seg(uchar a, int x, int y, int w, int h) {
	int h2 = h >> 1;
	int thick_2 = thick_ >> 1;
	int vertices_[6][2];
	
	if(a & 0x40) {
		vertices_[0][0] = x + seg_gap_;
		vertices_[0][1] = y;
		vertices_[1][0] = vertices_[0][0] + thick_;
		vertices_[1][1] = vertices_[0][1] + thick_;
		vertices_[2][0] = x + w - thick_ - seg_gap_;
		vertices_[2][1] = vertices_[1][1];
		vertices_[3][0] = vertices_[2][0] + thick_;
		vertices_[3][1] = vertices_[0][1];
	
		addvertices(4, vertices_);
		fillpath();
	}
	if(a & 0x20) {
		vertices_[0][0] = x + w;
		vertices_[0][1] = y + seg_gap_;
		vertices_[1][0] = vertices_[0][0] - thick_;
		vertices_[1][1] = vertices_[0][1] + thick_;
		vertices_[2][0] = vertices_[1][0];
		vertices_[2][1] = y + h2 - thick_2 - seg_gap_;
		vertices_[3][0] = vertices_[0][0];
		vertices_[3][1] = vertices_[2][1] + thick_2;
		
		addvertices(4, vertices_);
		fillpath();
	}
	if(a & 0x10) {
		vertices_[0][0] = x + w;
		vertices_[0][1] = y + h2 + seg_gap_;
		vertices_[1][0] = vertices_[0][0] - thick_;
		vertices_[1][1] = vertices_[0][1] + thick_2;
		vertices_[2][0] = vertices_[1][0];
		vertices_[2][1] = y + h - thick_ - seg_gap_;
		vertices_[3][0] = vertices_[0][0];
		vertices_[3][1] = vertices_[2][1] + thick_;
		
		addvertices(4, vertices_);
		fillpath();
	}
	if(a & 0x08) {
		vertices_[0][0] = x + seg_gap_;
		vertices_[0][1] = y + h;
		vertices_[1][0] = vertices_[0][0] + thick_;
		vertices_[1][1] = vertices_[0][1] - thick_;
		vertices_[2][0] = x + w - thick_ - seg_gap_;
		vertices_[2][1] = vertices_[1][1];
		vertices_[3][0] = vertices_[2][0] + thick_;
		vertices_[3][1] = vertices_[0][1];
		
		addvertices(4, vertices_);
		fillpath();
	}
	if(a & 0x04) {
		vertices_[0][0] = x;
		vertices_[0][1] = y + h2 + seg_gap_;
		vertices_[1][0] = vertices_[0][0] + thick_;
		vertices_[1][1] = vertices_[0][1] + thick_2;
		vertices_[2][0] = vertices_[1][0];
		vertices_[2][1] = y + h - thick_ - seg_gap_;
		vertices_[3][0] = vertices_[0][0];
		vertices_[3][1] = vertices_[2][1] + thick_;
		
		addvertices(4, vertices_);
		fillpath();
	}
	if(a & 0x02) {
		vertices_[0][0] = x;
		vertices_[0][1] = y + seg_gap_;
		vertices_[1][0] = vertices_[0][0] + thick_;
		vertices_[1][1] = vertices_[0][1] + thick_;
		vertices_[2][0] = vertices_[1][0];
		vertices_[2][1] = y + h2 - thick_2 - seg_gap_;
		vertices_[3][0] = vertices_[0][0];
		vertices_[3][1] = vertices_[2][1] + thick_2;
		
		addvertices(4, vertices_);
		fillpath();
	}
	if(a & 0x01) {
		vertices_[0][0] = x + seg_gap_;
		vertices_[0][1] = y + h2;
		vertices_[1][0] = vertices_[0][0] + thick_;
		vertices_[1][1] = vertices_[0][1] - thick_2;
		vertices_[2][0] = vertices_[1][0] + w - thick_ * 2 - seg_gap_ * 2;
		vertices_[2][1] = vertices_[1][1];
		vertices_[3][0] = x + w - seg_gap_;
		vertices_[3][1] = y + h2;
		vertices_[4][0] = vertices_[2][0];
		vertices_[4][1] = vertices_[2][1] + thick_;
		vertices_[5][0] = vertices_[1][0];
		vertices_[5][1] = vertices_[1][1] + thick_;
		
		addvertices(6, vertices_);
		fillpath();
	}
}

/*!
	Returns the string equivalent of display
*/
const char * SevenSegment::value() const {
	int len = strlen(value_);
	char *buf = new char[len + 1];
	for(int i = 0; i < len; i++) {
		if(value_[i] >= 0x1 && value_[i] <= 0xA) {
			buf[i] = value_[i] + 0x2F;
		}
		else if(value_[i] >= 0xB && value_[i] <= 0x10) {
			buf[i] = value_[i] + 0x36;
		}
		else if(value_[i] == 0x11) {
			buf[i] = '-';
		}
		else if(value_[i] == 0x12) {
			buf[i] = '.';
		}
		else if(value_[i] == 0x13) {
			buf[i] = ' ';
		}
		else {
			buf[i] = value_[i];
		}
	}
	buf[len] = '\0';
	return buf;
}

SevenSegment::~SevenSegment() {
	delete [] value_;
}

//
// End of "$Id SevenSegment.cxx Thu Feb 2 2006 z_hossain $".
//
