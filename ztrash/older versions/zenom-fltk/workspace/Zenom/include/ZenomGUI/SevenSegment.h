//
// "$Id SevenSegment.h Thu Feb 2 2006 z_hossain $"
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

#ifndef fltk_SevenSegment_h
#define fltk_SevenSegment_h

#include <fltk/Widget.h>

#define DATA_SIZE 21
#define ARRAY_SIZE 32

namespace fltk {

class SevenSegment : public Widget {
	static const uchar data_seg[DATA_SIZE];
	int unit_w_, unit_h_;
	short thick_;
	short seg_gap_;
	short unit_gap_;
	short dot_len_;
	Color seg_color_;
	uchar align_;
	char *value_;
	
	void draw_seg(uchar a, int x, int y, int w, int h);
	
public:
	SevenSegment(int x, int y, int w, int h, const char *l=0);
	~SevenSegment();
	
	void draw();
	const char *value() const; 
	void value(const char *a);
	int unit_w() const { return unit_w_; }
	void unit_w(int w) { unit_w_ = w; }
	int unit_h() const { return unit_h_; }
	void unit_h(int h) { unit_h_ = h; }
	short thickness() const { return thick_; }
	void thickness(short t) { thick_ = t & ~0x01; }//force even
	Flags align_text() const { return align_; }
	void align_text(Flags a) { align_ = a; }
	short segment_gap() const { return seg_gap_; }
	void segment_gap(short g) { seg_gap_ = g; }
	short unit_gap() const { return unit_gap_; }
	void unit_gap(short g) { unit_gap_ = g; }
	short dot_len() const { return dot_len_; }
	void dot_len(short l) { dot_len_ = l; }
};

}
#endif

//
// End of "$Id SevenSegment.h Thu Feb 2 2006 z_hossain $".
//
