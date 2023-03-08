#include <png++/png.hpp>

#include "dexter_sparse_vector.hxx"
#include <vector>
#include <thread>
#include <exception>


int main(int argc, char *argv[])
{
  dexter::sparse::vector<int> v(0, 10);

  std::cout << v << std::endl;

  // png::image<png::rgba_pixel> img(512, 512);

  // for(png::uint_32 y = 0; y < img.get_height(); ++y) {
  //   for(png::uint_32 x = 0; x < img.get_width(); ++x) {

  //     img[x][y] = png::rgba_pixel(
  //       x,     // red
  //       y,     // green
  //       x + y, // blue
  //       255    // alpha
  //     );
  //     // img.set_pixel(x, y, png::rgba_pixel(x, y, x + y, 255));
  //   }
  // }

  // img.write("test.png");

  return 0;
}