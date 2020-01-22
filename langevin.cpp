#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

const int N = 10000000;
const int NAVE = 10000;

// Euler-Maruyama for additive noise
std::vector<double> additive() {
  std::mt19937 mt;
  const double h = 0.01;
  double x = 0.0;
  double t = 0.0;
  std::vector<double> data;
  std::normal_distribution<double> nd(0.0, sqrt(2.0 * h));
  for (int i = 0; i < N; i++) {
    double w = nd(mt);
    x += -x * h;
    x += w;
    t += h;
    data.push_back(x);
  }
  return data;
}

// Euler-Maruyama with Ito prescription
std::vector<double> multiplicative_ito() {
  std::mt19937 mt1(1), mt2(2);
  const double h = 0.01;
  double x = 0.0;
  double t = 0.0;
  std::vector<double> data;
  std::normal_distribution<double> nd(0.0, sqrt(2.0 * h));
  for (int i = 0; i < N; i++) {
    double w1 = nd(mt1);
    double w2 = nd(mt2);
    x += -x * x * x * h;
    x += x * w1;
    x += w2;
    t += h;
    data.push_back(x);
  }
  return data;
}

// Euler-Maruyama with Stratonovich prescription
std::vector<double> multiplicative_stratonovich() {
  std::mt19937 mt1(1), mt2(2);
  const double h = 0.01;
  double x = 0.0;
  double t = 0.0;
  std::vector<double> data;
  std::normal_distribution<double> nd(0.0, sqrt(2.0 * h));
  for (int i = 0; i < N; i++) {
    double w1 = nd(mt1);
    double w2 = nd(mt2);
    x += -(x * x * x - x) * h;
    x += x * w1;
    x += w2;
    t += h;
    data.push_back(x);
  }
  return data;
}

// Milstein method
std::vector<double> multiplicative_milstein() {
  std::mt19937 mt1(1), mt2(2);
  const double h = 0.01;
  double x = 0.0;
  double t = 0.0;
  std::vector<double> data;
  std::normal_distribution<double> nd(0.0, sqrt(2.0 * h));
  for (int i = 0; i < N; i++) {
    double w1 = nd(mt1);
    double w2 = nd(mt2);
    x += (-x * x * x) * h;
    x += x * w1;
    x += 0.5 * x * w1 * w1;
    x += w2;
    t += h;
    data.push_back(x);
  }
  return data;
}

// Two-step scheme
std::vector<double> multiplicative_twostep() {
  std::mt19937 mt1(1), mt2(2);
  const double h = 0.01;
  double x = 0.0;
  double t = 0.0;
  std::vector<double> data;
  std::normal_distribution<double> nd(0.0, sqrt(2.0 * h));
  for (int i = 0; i < N; i++) {
    double w1 = nd(mt1);
    double w2 = nd(mt2);
    double x_i = x + (-x * x * x) * h + x * w1 + w2;
    x = x + (-x * x * x) * h + (x + x_i) * 0.5 * w1 + w2;
    t += h;
    data.push_back(x);
  }
  return data;
}

void plot(std::vector<double> data, std::string filename) {
  const int N = data.size();
  std::sort(data.begin(), data.end());
  std::vector<double> xv, yv;
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
  std::cout << filename << std::endl;
}

int main() {
  plot(additive(), "additive.dat");
  plot(multiplicative_ito(), "ito.dat");
  plot(multiplicative_stratonovich(), "stratonovich.dat");
  plot(multiplicative_milstein(), "milstein.dat");
  plot(multiplicative_twostep(), "twostep.dat");
}
