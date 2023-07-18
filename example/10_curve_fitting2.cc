// Tutorial Author: jjy0923@gmail.com

#include <chrono>
#include <functional>
#include <random>
#include <utility>
#include <vector>

#include "ceres/ceres.h"
#include "glog/logging.h"
using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solve;
using ceres::Solver;

std::vector<std::pair<double, double>> GenerateData(
    double start, double end, double interval,
    std::function<double(double)> function, double noise = 0.0) {
  std::vector<std::pair<double, double>> result;
  for (double i = start; i < end; i = i + interval) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> dist(0.0, noise);
    double noise_val = dist(generator);
    double calc = function(i) + noise_val;
    result.push_back({i, calc});
  }
  return result;
}

// Visualize Data (https://www.rapidtables.com/tools/scatter-plot.html)
// clang-format on
struct CustomResidual {
  CustomResidual(double x, double y) : x_(x), y_(y) {}
  template <typename T>
  bool operator()(const T* const a, const T* const b, const T* const c,
                  T* residual) const {
    residual[0] = y_ - (a[0] * ceres::pow(x_, 2) + b[0] * x_ + c[0]);
    return true;
  }

 private:
  const double x_;
  const double y_;
};
int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);

  double a = 0.0;
  double b = 0.0;
  double c = 0.0;

  // Define function => a * x^2 + b * x + c
  std::function<double(double)> function = [](double x) {
    return 2 * std::pow(x, 2) + 3 * x + 1;
  };

  std::vector<std::pair<double, double>> data =
      GenerateData(-10.0, 10.0, 0.3, function, 5.0);

  for (int i = 0; i < data.size(); i++) {
    std::cout << data[i].first << " " << data[i].second << " " << std::endl;
  }
  Problem problem;
  for (int i = 0; i < data.size(); i++) {
    problem.AddResidualBlock(
        new AutoDiffCostFunction<CustomResidual, 1, 1, 1,
                                 1>(  // 1 residual, 3 variable
            new CustomResidual(data[i].first, data[i].second)),
        nullptr, &a, &b, &c);
  }
  Solver::Options options;
  options.max_num_iterations = 100;
  options.linear_solver_type = ceres::DENSE_QR;
  options.minimizer_progress_to_stdout = true;
  Solver::Summary summary;
  Solve(options, &problem, &summary);
  std::cout << summary.BriefReport() << "\n";
  std::cout << "Initial a: " << 0.0 << " b: " << 0.0 << "c: " << 0.0 << "\n";
  std::cout << "Final a: " << a << " b: " << b << " c: " << c << "\n";

  return 0;
}