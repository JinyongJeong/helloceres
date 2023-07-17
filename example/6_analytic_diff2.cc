// Ceres Solver - A fast non-linear least squares minimizer
// Copyright 2015 Google Inc. All rights reserved.
// http://ceres-solver.org/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the name of Google Inc. nor the names of its contributors may be
//   used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Author: keir@google.com (Keir Mierle)
//
// A simple example of using the Ceres minimizer.
//
// Minimize 0.5 (10 - x)^2 using analytic jacobian matrix.
#include <vector>
#include <cmath>
#include "ceres/ceres.h"
#include "glog/logging.h"
using ceres::CostFunction;
using ceres::Problem;
using ceres::SizedCostFunction;
using ceres::Solve;
using ceres::Solver;

// 왜 함수의 최소값이 아닌 결과가 0인 값으로 최적화가 될까?

// A CostFunction implementing analytically derivatives for the
// function f(x) = x^3-2x^2+x+10
class QuadraticCostFunction
    : public SizedCostFunction<1 /* number of residuals */,
                               1 /* size of first parameter */> {
 public:
  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    double x = parameters[0][0];
    // f(x) = x^2- 30x + 10
    residuals[0] = ceres::pow(x,2) - 30 *x + 10;
    // f'(x) = 2x - 30. 
    if (jacobians != nullptr && jacobians[0] != nullptr) {
      jacobians[0][0] = 2*x -30;
    }
    return true;
  }
};
int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  // The variable to solve for with its initial value. It will be
  // mutated in place by the solver.
  double x = 0.5;
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