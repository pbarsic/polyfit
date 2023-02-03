#include <opencv2/core.hpp>

/*
 * \brief fit a polynomial to the input vector of points
 * @param xypoints: vector of input points
 * @param polycoeffs: output coefficients, sorted by increasing degree
 * @param degree: highest degree of fit polynomial, defaults to quadratic
 */
void polyfit(std::vector<cv::Point2d> &xypoints,
             std::vector<double> *polycoeffs, int degree = 2);

/*
 * \brief make a polynomial with Gaussian noise
 * \param xpoints Input x-axis
 * \param coeffs Coefficients for fit polynomial ordered by increasing degree,
 * polynmoial degree is coeffs.size() - 1 \param std Standard deviation for the
 * zero-centerd Gaussian noise you wish to add to the y-values \param xypoints
 * Output vector of (x, y(x))
 */
void make_poly(std::vector<double> &xpoints, std::vector<double> coeffs,
               double std, std::vector<cv::Point2d> *xypoints);
