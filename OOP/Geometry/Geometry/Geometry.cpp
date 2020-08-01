#include "Vector.h"
#include <amp_graphics.h>
int main() {
	Vector a, b(0, 2), c(2, 0);

	std::cout << a.len() << '\n';
	std::cout << b.len() << '\n';
	std::cout << c.len() << '\n';
	std::cout << a * c << '\n';
	std::cout << (b + c).len() << '\n';
	std::cout << (b + c) << '\n';
	std::cout << b.rotate(180) << '\n';

	
}