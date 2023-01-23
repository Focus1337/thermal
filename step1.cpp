
double avg(double left, double right) {
    return (left + right) / 2;
}

void solveTridiagMatrix(const double* F,
                 const double* lambda,
                 const int length,
                 const double min,
                 const double max,
                 const double step,
                 const double timeStep,
                 double* y) {

    const auto coefficient = 1.0 / (2 * step * step);

    double A[length], B[length], C[length];
    for (int i = 0; i < length; ++i) {
        A[i] = - avg(lambda[i + 1], lambda[i]) / 2 * coefficient;
        B[i] = - avg(lambda[i + 1], lambda[i + 2]) / 2 * coefficient;
        C[i] = 1 / timeStep - A[i] - B[i];
    }

    double alpha[length], beta[length];
    alpha[0] = alpha[length - 1] = 0;
    beta[0] = min;
    beta[length - 1] = max;

    for (int i = 0; i < length - 2; ++i) {
        alpha[i + 1] = - B[i + 1] / (C[i + 1] + A[i + 1] * alpha[i]);
        beta[i + 1] = (F[i + 1] - A[i + 1] * beta[i]) / (C[i + 1] + A[i + 1] * alpha[i]);
    }

    y[length - 1] = max;
    for (int i = length - 2; i >= 0; i--) {
        y[i] = alpha[i] * y[i + 1] + beta[i];
    }
}

void restoreF(const double* y,
              const double* lambda,
              const int size,
              const double step,
              const double timeStep,
              double* F) {
    const double coefficient = 1 / (2 * step * step);
    for (int i = 1; i < size - 1; ++i) {
        double lambdaPlusHalf = avg(lambda[i], lambda[i + 1]);
        double lambdaMinusHalf = avg(lambda[i], lambda[i - 1]);
        double temp = lambdaPlusHalf * (y[i + 1] - y[i]) - lambdaMinusHalf * (y[i] - y[i - 1]);
        F[i] = y[i] / timeStep + temp * coefficient;
    }
}