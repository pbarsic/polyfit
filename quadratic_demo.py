import matplotlib.pyplot as plt
import numpy as np


def fit_cubic(xyvals: np.ndarray, pythonic=True):
    if pythonic:
        return fit_pythonic(xyvals)
    else:
        return fit_clike(xyvals[:, 0], xyvals[:, 1])

# this is a more efficient version that takes advantage
# of inherent vectorization in matrix multiplications
def fit_vectorized(xyvals: np.ndarray, degree: int=2):
    ndims = degree+1
    npoints = xyvals.shape[0]
    M = np.zeros([ndims, ndims])
    y = np.zeros(ndims)

    pre_sums = np.zeros([ndims, npoints])
    for ii in range(ndims):
        for jj in range(npoints):
            pre_sums[ii,jj] = xyvals[jj, 0] ** ii

    M = np.matmul(pre_sums , pre_sums.T)

    y = np.matmul(pre_sums, xyvals[:,1])

    polycoeffs = np.matmul(np.linalg.inv(M), y)

    print("fit_vectorized")
    print(f"M:\n{M}")
    print(f"Y:\n{y}")
    print(f"data column sums: {np.sum(xyvals, axis=0)}")
    print(f"   check values: {np.matmul(M, polycoeffs)}")
    print(f"expected values: {y}")
    return polycoeffs


def fit_pythonic(xyvals: np.ndarray):
    M = np.zeros([3, 3])
    y = np.zeros(3)

    for ii in range(M.shape[0]):
        printline = "| "
        for jj in range(M.shape[1]):
            coeff = ii + jj
            printline += f"{coeff} "
            M[ii, jj] = np.sum(xyvals[:, 0] ** coeff)
        print(f"{printline}|")
    for jj in range(y.shape[0]):
        y[jj] = np.sum(xyvals[:, 1] * (xyvals[:, 0] ** jj))

    polycoeffs = np.matmul(np.linalg.inv(M), y)

    print("fit_pythonic")
    print(f"M:\n{M}")
    print(f"Y:\n{y}")
    print(f"data column sums: {np.sum(xyvals, axis=0)}")
    print(f"   check values: {np.matmul(M, polycoeffs)}")
    print(f"expected values: {y}")
    return polycoeffs


def fit_clike(xvalues, yvalues, degree=2):
    M = np.zeros([degree + 1, degree + 1])
    y = np.zeros(degree + 1)
    num_datapoints = xvalues.shape[0]

    for ii in range(degree + 1):
        for jj in range(degree + 1):
            coeff = ii + jj
            for pt in range(num_datapoints):
                M[ii, jj] += xvalues[pt] ** coeff

    for jj in range(degree + 1):
        for pt in range(num_datapoints):
            y[jj] += yvalues[pt] * xvalues[pt] ** jj

    polycoeffs = np.matmul(np.linalg.inv(M), y)

    print("fit_clike")
    print(f"M:\n{M}")
    print(f"Y:\n{y}")
    print(f"data column sums: {np.sum(xvalues)} {np.sum(yvalues)}")
    print(f"   check values: {np.matmul(M, polycoeffs)}")
    print(f"expected values: {y}")
    return polycoeffs

def y_known(a, b, c, x, std=0):
    return a + b * x + c * x**2 + np.random.randn(x.shape[0]) * std


if __name__ == "__main__":
    N = 5
    a = 3
    b = -2
    c = 7.5
    xvals = np.array(sorted(np.random.randn(10) * 4 + 3))

    yvals = y_known(a, b, c, xvals, std=50.2)

    xyvals = np.concatenate([xvals, yvals]).reshape(2, -1).T

    print(f"x: {xvals}\ny: {yvals}\nxy: {xyvals}")

    fit_p = fit_cubic(xyvals, True)
    fit_values = fit_cubic(xyvals, False)
    fit_values = fit_vectorized(xyvals)
    print(f"Fit values: {fit_values}")
    print(f"Expected values: {a}, {b}, {c}")
    yfit = y_known(fit_values[0], fit_values[1], fit_values[2], xvals)

    yclean = y_known(a, b, c, xvals)

    plt.plot(xvals, yclean, "x-", label="clean")
    plt.plot(xvals, yfit, "3-", label="fit")
    plt.plot(xyvals[:, 0], xyvals[:, 1], "2-", label="fit input")
    plt.legend()
    plt.show()
