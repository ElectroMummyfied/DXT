#pragma region constants {

#define M_E        2.71828182845904523536   // e
#define M_LOG2E    1.44269504088896340736   // log2(e)
#define M_LOG10E   0.434294481903251827651  // log10(e)
#define M_LN2      0.693147180559945309417  // ln(2)
#define M_LN10     2.30258509299404568402   // ln(10)
#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2
#define M_PI_4     0.785398163397448309616  // pi/4
#define M_1_PI     0.318309886183790671538  // 1/pi
#define M_2_PI     0.636619772367581343076  // 2/pi
#define M_2_SQRTPI 1.12837916709551257390   // 2/sqrt(pi)
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#define M_SQRT1_2  0.707106781186547524401  // 1/sqrt(2)

#pragma endregion } constants
#pragma region headers {

#include <numeric>
#include <limits>
#include <ctgmath>

#include <set>

#include <vector>
#include <algorithm>

#include <filesystem>
#include <iostream>
#include <fstream>

#include <Eigen/Dense>

#pragma endregion } headers
#pragma region definitions {
struct stl_reader {
  struct graph {
    std::vector<float> m_pnts;
    std::vector<std::uint32_t> m_fcts;
  };
  struct rle_cuboid_model {
    std::vector<std::uint16_t> m_model; // 2d index(idx, idy), reentrancy count
  };


  struct facet {
    std::array<float, 3> n;
    std::array<float, 3> u;
    std::array<float, 3> v;
    std::array<float, 3> w;
    std::uint16_t attr;
  };
  typedef std::vector<facet> facets_t;

  char m_header[81];
  facets_t m_facets;
  graph m_graph;

  float m_min_length;
  std::array<float, 3> m_min;
  std::array<float, 3> m_max;
  std::array<float, 3> m_mid;

  float m_scale;
  std::array<float, 3> m_rotation;
  // std::array<float, 3> m_translation;

  stl_reader(const char* filepath);

  private:
    float min_length(std::size_t i) ;
    graph generate_graph();
  public:
    void graph_to_RLEdCuboidModel(std::uint16_t resolution);
};

std::vector<std::uint32_t>
render_triangle (
  Eigen::Matrix3f const &T,
  Eigen::Vector3f l1,
  Eigen::Vector3f l2,
  std::uint16_t width,
  std::uint16_t height
);

bool save_img(
  std::vector<std::uint32_t> const &img,
  std::uint16_t w,
  std::uint16_t h
);
#pragma endregion } definitions

int main(int argc, char *argv[]) {
  Eigen::Matrix3f T;
  Eigen::Vector3f l1 = {0.0f,  0.0f, -1.0f};
  Eigen::Vector3f l2 = {0.0f,  0.0f,  1.0f};

  stl_reader stl(argv[1]);

  // T.col(0) <<
  //   -0.75f,
  //   -0.75f,
  //   -1.0f;

  // T.col(1) <<
  //   0.75f,
  //   -0.5f,
  //   0.0f;

  // T.col(2) <<
  //   0.0f,
  //   0.9f,
  //   1.0f;

  std::uint16_t width, height;
  width = height = 32;
  std::vector<std::uint32_t> img(width*height, 0);

  for(std::uint32_t i = 0; i < stl.m_graph.m_fcts.size(); i++) {
     = render_triangle (
      T, l1, l2, width , height  );
  }

  if(!save_img(img, width, height)) {
    std::cout << "could not save image\n";
    return -1;
  }

  return 0;
}

#pragma region implementations {

#pragma region stl_reader {

float stl_reader::min_length(std::size_t i) {
  float dst;
  Eigen::Vector3f
    u(this->m_facets[i].u.data()),
    v(this->m_facets[i].v.data()),
    w(this->m_facets[i].w.data());

  dst = std::min({
    (u - v).norm(),
    (v - w).norm(),
    (w - u).norm(),
    this->m_min_length});

  return dst;
};
stl_reader::stl_reader(const char* filepath) {
  namespace fs = std::filesystem;

  std::ifstream file;
  std::uint32_t num_facets = 0;
  std::uint64_t file_size = 0;

  fs::path fp(filepath);
  file.exceptions(std::ios::badbit | std::ios::failbit);
  file.open(
    fs::canonical(fp)
    , std::ios::binary | std::ios::in);

  file.seekg(0, std::ios::end);
  file_size = file.tellg();
  file.seekg(0, std::ios::beg);

  if(file_size < 85)
    file.setstate(std::ios::failbit);

  file
    .read(reinterpret_cast<char *>(&this->m_header[0]),80)
    .read(reinterpret_cast<char *>(&num_facets),4);
  this->m_header[80] = '\n';

  if((file_size - 84)/num_facets != 50)
    file.setstate(std::ios::failbit);

  this->m_facets.resize(num_facets);
  this->m_min_length =
      std::numeric_limits<float>::max();
  for(std::uint8_t j = 0; j < 3; j++) {
    this->m_min[j] =
      std::numeric_limits<float>::max();
    this->m_max[j] =
      std::numeric_limits<float>::min();
  }

  for(std::size_t i = 0; i < num_facets; i++) {
    file.read(reinterpret_cast<char *>(&this->m_facets[i]), 50);
    for(std::uint8_t j = 0; j < 3; j++) {
      this->m_min[j] = std::min({
        this->m_facets[i].u[j],
        this->m_facets[i].v[j],
        this->m_facets[i].w[j],
        this->m_min[j]  });

      this->m_max[j] = std::max({
        this->m_facets[i].u[j],
        this->m_facets[i].v[j],
        this->m_facets[i].w[j],
        this->m_max[j]  });
    }
    this->m_min_length = this->min_length(i);
  }
  file.close();

  this->m_mid[0] = (this->m_max[0] + this->m_min[0])/2;
  this->m_mid[1] = (this->m_max[1] + this->m_min[1])/2;
  this->m_mid[2] = (this->m_max[2] + this->m_min[2])/2;

  float ep = std::numeric_limits<float>::epsilon();
  // cube side length
  this->m_scale = std::max({
    this->m_max[0] - this->m_min[0],
    this->m_max[1] - this->m_min[1],
    this->m_max[2] - this->m_min[2]}
  )/(1.0f - 2.0f*ep);

  this->m_graph = this->generate_graph();
}

stl_reader::graph stl_reader::generate_graph() {
  using namespace Eigen;
  graph dst;

  std::set<std::array<float, 3>> pnt_set;
  /* initializing STL point set */ {
    for(std::size_t i = 0; i < this->m_facets.size(); i++) {
      pnt_set.insert(this->m_facets[i].u);
      pnt_set.insert(this->m_facets[i].v);
      pnt_set.insert(this->m_facets[i].w);
    }
  }

  std::vector<std::array<float, 3>> pnts(pnt_set.size());
  /* initializing intermidiate STL vector points */ {
    auto it = pnt_set.begin();
    for(std::size_t i = 0; i < pnt_set.size(); i++) {
      pnts[i][0] = it->at(0);
      pnts[i][1] = it->at(1);
      pnts[i][2] = it->at(2);
      it++;
    }
  }
  pnt_set.clear();

  std::set<std::array<std::uint32_t, 3>> fct_set;
  /* initializing STL facet set */ {
    std::array<std::uint32_t, 3> fct;
    decltype(pnts)::iterator _s, _e;
    for(std::size_t i = 0; i < this->m_facets.size(); i++) {
      /* insert first point */ {
        auto pnt = this->m_facets[i].u;

        _s = std::lower_bound(
          pnts.begin(),
          pnts.end(),
          pnt);
        if(_s == pnts.end()) continue;

        _e = std::upper_bound(
          pnts.begin(),
          pnts.end(),
          pnt);
        if(std::distance(_s, _e) != 1) continue;
        fct[0] = std::distance(pnts.begin(), _s);
      }
      /* insert second point*/ {
        auto pnt = this->m_facets[i].v;

        _s = std::lower_bound (
          pnts.begin(),
          pnts.end(),
          pnt);
        if(_s == pnts.end()) continue;

        _e = std::upper_bound (
          pnts.begin(),
          pnts.end(),
          pnt);
        if(std::distance(_s, _e) != 1) continue;
        fct[1] = std::distance(pnts.begin(), _s);
      }
      /* insert third point */ {
        auto pnt = this->m_facets[i].w;

        _s = std::lower_bound(
          pnts.begin(),
          pnts.end(),
          pnt);
        if(_s == pnts.end()) continue;

        _e = std::upper_bound(
          pnts.begin(),
          pnts.end(),
          pnt);
        if(std::distance(_s, _e) != 1) continue;
        fct[2] = std::distance(pnts.begin(), _s);
      }

      std::sort(
        fct.begin(),
        fct.end());
      fct_set.insert({fct[0], fct[1], fct[2]});
    }
  }
  if(fct_set.size() != this->m_facets.size()) {
    std::runtime_error err(
      "Something went wrong while"
      "generating triangulation graph"  );
    throw err;
  }
  this->m_facets.clear();

  /* initializing graph points */ {
    dst.m_pnts.resize(3*pnts.size());
    Eigen::Map<Eigen::MatrixXf> P(
      dst.m_pnts.data(),
      pnts.size(), 3  );
    for(std::size_t i = 0; i < pnts.size(); i++) {
      P(i, 0) = pnts[i][0];
      P(i, 1) = pnts[i][1];
      P(i, 2) = pnts[i][2];
    }
  }
  pnts.clear();

  /* initializing graph triangles */{
    auto it = fct_set.begin();
    dst.m_fcts.resize(3*fct_set.size());
    Map<Matrix<std::uint32_t, Dynamic, Dynamic>> T(
      dst.m_fcts.data(),
      fct_set.size(), 3  );
    for(std::size_t i = 0; i < fct_set.size(); i++) {
      T(i, 0) = it->at(0);
      T(i, 1) = it->at(1);
      T(i, 2) = it->at(2);
      it++;
    }
  }
  fct_set.clear();


  return dst;
}

void stl_reader::graph_to_RLEdCuboidModel(
  std::uint16_t resolution
) {
  using namespace Eigen;


  Map<Matrix<float, Dynamic, Dynamic>> points(
    this->m_graph.m_pnts.data(),
    this->m_graph.m_pnts.size()/3, 3  );
  Map<Matrix<std::uint32_t, Dynamic, Dynamic>> triangles(
    this->m_graph.m_fcts.data(),
    this->m_graph.m_fcts.size()/3, 3  );

  // auto it =  triangles.rowwise().begin();
  // std::sort(
  //   triangles.rowwise().begin(),
  //   triangles.rowwise().end(),
  //   [](decltype(triangles)::RowwiseReturnType lhs, auto rhs) {
  //     lhs
  //   });
  // std::sort(
  //   triangles.rowWise()
  // );


  // Map<Vector3f> t(this->m_translation.data());
  // Map<Vector3f> h(this->m_min.data());
  // t = -h;


}

#pragma endregion } stl_reader
#pragma region render_triangle {

std::vector<std::uint32_t>
render_triangle (
  Eigen::Matrix3f const &T,
  Eigen::Vector3f l1,
  Eigen::Vector3f l2,
  std::uint16_t width,
  std::uint16_t height
) {
  std::vector<std::uint32_t> img;

  bool c1, c2, c3, call;
  float xmin, xmax, ymin, ymax;

  std::uint16_t is, js, ie, je;

  Eigen::Matrix3f M;
  Eigen::Vector3f lp;

  std::tie(xmin, xmax) = std::minmax({T(0,0), T(0,1), T(0,2)});
  std::tie(ymax, ymin) = std::minmax({T(1,0), T(1,1), T(1,2)});
  ymin *= -1.0f;
  ymax *= -1.0f;

  // std::cout <<
  //   "x-min: " << xmin << "\n" <<
  //   "x-max: " << xmax << "\n" <<
  //   "y-min: " << ymin << "\n" <<
  //   "y-max: " << ymax << "\n";

  is =  width*((std::remainder(xmin, 2.0f) + 1.0f)/2.0f);
  ie =  width*((std::remainder(xmax, 2.0f) + 1.0f)/2.0f);
  js = height*((std::remainder(ymin, 2.0f) + 1.0f)/2.0f);
  je = height*((std::remainder(ymax, 2.0f) + 1.0f)/2.0f);

  is = is >= width ? 0 : is;
  ie = ie >= width ? width : ie;

  js = js >= height ? 0 : js;
  je = je >= height ? height : je;

  // std::cout <<
  //   "is: " << is << "\n" <<
  //   "ie: " << ie << "\n" <<
  //   "js: " << js << "\n" <<
  //   "je: " << je << "\n";

  M.col(1) = (T.col(1) - T.col(0));
  M.col(2) = (T.col(2) - T.col(0));

  std::uint8_t *color;
  img.assign(width*height, 0);
  for(std::uint16_t i = is; i < ie; i++) {
    for(std::uint16_t j = js; j < je; j++) {
      color = reinterpret_cast<std::uint8_t*>(
        &img[i + j*width]
      );

      float x = 2.0f*i/width - 1.0f,
            y = 1.0f - 2.0f*j/height;

      l1(0) = l2(0) = x;
      l1(1) = l2(1) = y;

      M.col(0) = (l1 - l2);

      lp = M.inverse() * (l1 - T.col(0));

      c1 = 0.0f < lp(1) && lp(1) < 1.0f;
      c2 = 0.0f < lp(2) && lp(2) < 1.0f;
      c3 = (lp(1) + lp(2)) < 1.0f;
      call = c1 && c2 && c3;

      // color[0] = 128.0f*std::remainderf(2.0f*lp(0) -1.0f, 2.0f) + 128.0f;
      // color[1] = 128.0f*std::remainderf(2.0f*lp(0) -1.0f, 2.0f) + 128.0f;
      // color[2] = 128.0f*std::remainderf(2.0f*lp(0) -1.0f, 2.0f) + 128.0f;

      color[0] += call ? 5 : 0;
      color[1] += call ? 5 : 0;
      color[2] += call ? 5 : 0;

      color[3] = call ? 255 : 0;
    }
  }

  return img;
}

#pragma endregion } render_triangle
#pragma region save_img {

bool save_img (
  std::vector<std::uint32_t> const &img,
  std::uint16_t w,
  std::uint16_t h
) {
  std::fstream file;
  file.open("matrix.pam",
    std::ios::binary | std::ios::ate | std::ios::out );

  if(!file.is_open()) return false;

  file << "P7\n"
    << "WIDTH " << w << "\n"
    << "HEIGHT "<< h << "\n"
    << "DEPTH 4\n"
    << "MAXVAL 255\n"
    << "TUPLTYPE RGB_ALPHA\n"
    << "ENDHDR\n";

  file.write(
    reinterpret_cast<char const*>(img.data()),
    sizeof(std::uint32_t)*img.size());
  file.close();

  return true;
}

#pragma endregion } save_img

#pragma endregion } implementations