#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>

#include "polyfit.hpp"

int main() {
  // application to demonstrate the polynomial fit
  // and also provide the amount of time to compute
  int npts = 100;
  int num_iterations = 1000;
  cv::TickMeter tm;
  std::vector<double> input_coeffs{73, 14, -2.8};
  std::vector<double> xpoints;
  double xmin = -4.5, xdelta = 2.1;
  std::vector<cv::Point2d> xypoints;
  double std = 5.0;
  std::vector<double> fit_coeffs;
  std::vector<cv::Point2d> model_points;
  std::vector<cv::Point2d> clean_points;
  int num_points = 10;

  for (int i = 0; i < num_points; i++) {
    xpoints.push_back(xmin + i * xdelta);
  }

  make_poly(xpoints, input_coeffs, std, &xypoints);
  make_poly(xpoints, input_coeffs, 0, &clean_points);

  for (int ii = 0; ii < num_iterations; ii++) {
    tm.start();
    polyfit(xypoints, &fit_coeffs);
    tm.stop();
  }
  double avg_time_milli =
      tm.getTimeMilli() / static_cast<double>(num_iterations);
  std::cout << "Average time per " << npts
            << "-point polynomial fit in milliseconds: " << avg_time_milli
            << std::endl;

  make_poly(xpoints, fit_coeffs, std, &model_points);

  std::cout << "x, y(x) + noise, y(x), fit(x)" << std::endl;
  float error = 0;
  for (int ii = 0; ii < xpoints.size(); ii++) {
    std::cout << xpoints.at(ii) << ", " << xypoints.at(ii).y << ", "
              << clean_points.at(ii).y << ", " << model_points.at(ii).y
              << std::endl;
    error += pow((model_points.at(ii).y - clean_points.at(ii).y), 2);
  }
  error = pow(error / static_cast<double>(num_points), 0.5);
  std::cout << "RMS error (fit vs. clean): " << error << std::endl;

  return 0;
}
