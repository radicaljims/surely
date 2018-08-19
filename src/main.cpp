#include <iostream>

#include "vec3.h"

using namespace mathy;

int main()
{
    int nx = 200;
    int ny = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    for(int j = ny - 1; j >= 0; j--)
    {
        for(int i = 0; i < nx; i++)
        {
            vec3 c = {
                float(i) / float(nx),
                float(j) / float(ny),
                0.2
            };

            int ir = int(255.99 * c.x);
            int ig = int(255.99 * c.y);
            int ib = int(255.99 * c.z);

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
}
