#ifndef COLORSCALE_H
#define COLORSCALE_H

#include <QColor>

class ColorScale
{
public:
	ColorScale();

	ColorScale(const QColor& pColor, double pStart, double pEnd );

	double start() const { return mStart; }
	void start(double val) { mStart = val; }

	double end() const { return mEnd; }
	void end(double val) { mEnd = val; }

	QColor color() const { return mColor; }
	void color(QColor val) { mColor = val; }

private:
	double mStart;
	double mEnd;
	QColor mColor;
};

#endif // COLORSCALE_H
