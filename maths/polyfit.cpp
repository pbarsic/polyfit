#include <opencv2/core.hpp>
#include <random>

/*
 * \brief fit a polynomial to the input vector of points
 * @param xypoints: vector of input points
 * @param polycoeffs: output coefficients, sorted by increasing degree
 * @param degree: highest degree of fit polynomial, defaults to quadratic
 */
void polyfit(std::vector<cv::Point2d> &xypoints,
             std::vector<double> *polycoeffs, int degree = 2) {
  int num_points = xypoints.size();
  int num_dims = degree + 1;

  cv::Point2d xy;

  cv::Mat M(num_points, num_dims, CV_64F);
  cv::Mat Y(num_points, 1, CV_64F);
  cv::Mat coeffs(num_dims + 1, 1, CV_64F);

  for (int ii = 0; ii < num_points; ii++) {
    xy = xypoints.at(ii);
    Y.at<double>(ii, 0) = xy.y;
    for (int jj = 0; jj < num_dims; jj++) {
      M.at<double>(ii, jj) = pow(xy.x, jj);
    }
  }

  coeffs = (M.t() * M).inv() * M.t() * Y;
  polycoeffs->clear();
  for (int d = 0; d < num_dims; d++) {
    polycoeffs->push_back(coeffs.at<double>(d, 0));
  }
}

/*
 * \brief make a polynomial with Gaussian noise
 * \param xpoints Input x-axis
 * \param coeffs Coefficients for fit polynomial ordered by increasing degree,
 * polynmoial degree is coeffs.size() - 1 \param std Standard deviation for the
 * zero-centerd Gaussian noise you wish to add to the y-values \param xypoints
 * Output vector of (x, y(x))
 */
void make_poly(std::vector<double> &xpoints, std::vector<double> coeffs,
               double std, std::vector<cv::Point2d> *xypoints) {
  auto noise = std::bind(std::normal_distribution<double>{0, std},
                         std::mt19937(std::random_device{}()));

  xypoints->clear();
  float yvalue;
  for (auto xvalue : xpoints) {
    yvalue = noise();
    for (int d = 0; d < coeffs.size(); d++) {
      yvalue += coeffs.at(d) + pow(xvalue, d);
    }
    xypoints->push_back(cv::Point2d(xvalue, yvalue));
  }
}
