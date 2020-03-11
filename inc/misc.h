#ifndef MISC_H
#define MISC_H

namespace Misc {
	typedef struct {
		double x, y;
	} Vector2_t;
	
	inline double Determinant(double a, double b, double c, double d) {
		return (a * d) - (b * c);
	}
}
#endif
