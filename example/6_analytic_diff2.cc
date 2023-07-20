// Minimize 0.5 (x^2- 30x + 10)^2 using analytic jacobian matrix.
// Tutor: jjy0923@gmail.com (JinyongJeong)

#include <cmath>
#include <vector>
#include "ceres/ceres.h"
#include "glog/logging.h"
using ceres::CostFunction;
using ceres::Problem;
using ceres::SizedCostFunction;
using ceres::Solve;
using ceres::Solver;

// 왜 함수의 최소값이 아닌 결과가 0인 값으로 최적화가 될까?

// A CostFunction implementing analytically derivatives for the
// function f(x) = x^2- 30x + 10
class QuadraticCostFunction
    : public SizedCostFunction<1 /* number of residuals */,
                               1 /* size of first parameter */> {
 public:
  bool Evaluate(double const* const* parameters, double* residuals,
                double** jacobians) const override {
    double x = parameters[0][0];
    // f(x) = x^2- 30x + 10
    residuals[0] = ceres::pow(x, 2) - 30 * x + 10;
    // f'(x) = 2x - 30.
    if (jacobians != nullptr && jacobians[0] != nullptr) {
      jacobians[0][0] = 2 * x - 30;
    }
    return true;
  }
};
int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  // The variable to solve for with its initial value. It will be
  // mutated in place by the solver.
  double x = 5.0;
  const double initial_x = x;
  // Build the problem.
  Problem problem;
  // Set up the only cost function (also known as residual).
  CostFunction* cost_function = new QuadraticCostFunction;
  problem.AddResidualBlock(cost_function, nullptr, &x);
  // Run the solver!
  Solver::Options options;
  options.minimizer_progress_to_stdout = true;
  Solver::Summary summary;
  Solve(options, &problem, &summary);
  std::cout << summary.BriefReport() << "\n";
  std::cout << "x : " << initial_x << " -> " << x << "\n";
  return 0;
}