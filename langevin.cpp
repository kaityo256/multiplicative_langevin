#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

std::vector<double> normal_langevin() {
  std::mt19937 mt;
  const double dt = 0.01;
  double x = 0.0;
  double t = 0.0;
  std::vector<double> data;
  std::normal_distribution<double> nd(0.0, sqrt(2.0 * dt));
  const int N = 100000;
  for (int i = 0; i < N; i++) {
    x += -x * dt;
    x += nd(mt);
    t += dt;
    data.push_back(x);
  }
  return data;
}

std::vector<double> multiplicative_langevin() {
  std::mt19937 mt1(1), mt2(2);
  const double dt = 0.01;
  double x = 0.0;
  double t = 0.0;
  std::vector<double> data;
  std::normal_distribution<double> nd(0.0, sqrt(2.0 * dt));
  const int N = 100000;
  for (int i = 0; i < N; i++) {
    x += -x * x * x * dt;
    x += x * nd(mt1);
    x += nd(mt2);
    t += dt;
    data.push_back(x);
  }
  return data;
}

void plot(std::vector<double> data, std::string filename) {
  const int N = data.size();
  std::sort(data.begin(), data.end());
  std::vector<double> xv, yv;
  const int NAVE = 100;
  for (int i = 0; i < N / NAVE; i++) {
    double x = 0.0;
    double y = 0.0;
    for (int j = 0; j < NAVE; j++) {
      x += data[i * NAVE + j];
      y += static_cast<double>(i * NAVE + j) / N;
    }
    x /= NAVE;
    y /= NAVE;
    xv.push_back(x);
    yv.push_back(y);
  }
  std::ofstream ofs(filename);
  for (size_t i = 0; i < xv.size() - 1; i++) {
    double v = (yv[i + 1] - yv[i]) / (xv[i + 1] - xv[i]);
    double x = (xv[i] + xv[i + 1]) * 0.5;
    ofs << x << " " << v << std::endl;
  }
}

int main() {
  plot(normal_langevin(), "additive.dat");
  plot(multiplicative_langevin(), "multiplicative.dat");
}
