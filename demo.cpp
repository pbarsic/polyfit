#include <iostream>
#include <opencv2/core.hpp>

#include "polyfit.hpp"

int main() {
  // application to demonstrate the polynomial fit
  int npts = 10;
  std::vector<double> input_coeffs{73, 14, -2.8};
  std::vector<double> xpoints;
  double xmin = -4.5, xdelta = 2.1;
  std::vector<cv::Point2d> xypoints;
  double std = 5.0;
  std::vector<double> fit_coeffs;
  std::vector<cv::Point2d> model_points;
  std::vector<cv::Point2d> clean_points;

  for (int i = 0; i < 10; i++) {
    xpoints.push_back(xmin + i * xdelta);
  }

  make_poly(xpoints, input_coeffs, std, &xypoints);
  make_poly(xpoints, input_coeffs, 0, &clean_points);

  polyfit(xypoints, &fit_coeffs);
  make_poly(xpoints, fit_coeffs, std, &model_points);

  std::cout << "x, y(x) + noise, y(x), fit(x)" << std::endl;
  for (int ii = 0; ii < xpoints.size(); ii++) {
    std::cout << xpoints.at(ii) << ", " << xypoints.at(ii).y << ", "
              << clean_points.at(ii).y << ", " << model_points.at(ii).y
              << std::endl;
  }

  return 0;
}
