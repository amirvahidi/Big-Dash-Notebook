typedef complex<double> point;
#define X real()
#define Y imag()
a + b // vector addition
r * a // scalar multiplication
double dot(point a, point b) { return (conj(a) * b).X;}
double cross(point a, point b) { return (conj(a) * b).Y;}
double squared_dist(point a, point b) { return norm(a - b);}
double dist(point a, point b) {return abs(a - b);} // abs = rad(norm)
double angle(point a, point b) {return arg(b - a);}
double slope(point a, point b) {return tan(arg(b - a));}
polar(r, theta); // polar to cartesian
point(abs(p), arg(p)); // cartesian to polar
point rotate(point a, double theta) {return a * polar(1.0, theta);}
point rotate(point a, double theta, point p) {return p + rotate(a-p, theta);} // rotate about p
point angle(point a, point b, point c) {abs(remainder(arg(a-b) - arg(c-b), 2.0) * M_PI);}
point project(point p, point v) {return v * dot(p, v) / norm(v);} // project p in vector v
point project(point p, point a, point b) {return a + project(p - a, b - a);} // project p in line (a, b)
point reflect(point p, point a, point b) {return a + conj((p - a) / (b - a)) * (b - a);}
point intersection(point a, point b, point p, point q) {
    double c1 = cross(p - a, b - a), c2 = cross(q - a, b - a);
    return (c1 * q - c2 * p) / (c1 - c2); // undefined if parallel
}