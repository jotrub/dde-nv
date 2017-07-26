#include <math.h>

void ManifoldEquation (
  double *x,
  double *alpha,
  double omega,
  double *w1,
  double *w2,
  double *v1,
  double *v2,
  double g1,
  double g2,
  double *u,
  double *r,
  double residuum[10])
{
  residuum[0] = g1 * w1[0] + g2 * w2[0] + omega * v2[0] + alpha[1] * v1[0];
  residuum[1] = -cos(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * v1[0] + alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * v1[1]) + sin(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * v2[0] + alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * v2[1]) - (alpha[0] + 0.5e0 * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1]) * v1[0] - (-0.5e0 * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] - 0.2e1 * x[1]) * v1[1] + omega * v2[1] + g1 * w1[1] + g2 * w2[1];
  residuum[2] = g1 * w2[0] + g2 * w1[0] - omega * v1[0] + alpha[1] * v2[0];
  residuum[3] = -cos(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * v2[0] + alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * v2[1]) - sin(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * v1[0] + alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * v1[1]) - (alpha[0] + 0.5e0 * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1]) * v2[0] - (-0.5e0 * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] - 0.2e1 * x[1]) * v2[1] - omega * v1[1] + g1 * w2[1] + g2 * w1[1];
  residuum[4] = w1[0] * v1[0] + w1[1] * v1[1] + w2[0] * v2[0] + w2[1] * v2[1] - 0.1e1;
  residuum[5] = -v1[0] * w2[0] - v1[1] * w2[1] + v2[0] * w1[0] + v2[1] * w1[1] + (-v1[0] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1] + v1[1] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1]) * sin(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (0.15e1 - 0.5e0 * exp(-x[1])) - (-v1[0] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1] + v1[1] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1]) * cos(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (0.15e1 - 0.5e0 * exp(-x[1])) + (-v2[0] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1] + v2[1] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1]) * sin(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (0.15e1 - 0.5e0 * exp(-x[1])) + (-v2[0] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1] + v2[1] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1]) * cos(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (0.15e1 - 0.5e0 * exp(-x[1]));
  residuum[6] = -alpha[1] * u[0];
  residuum[7] = -alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * u[0] + alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * u[1] - cos(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (0.5e0 * v1[0] * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1] - 0.5e0 * v1[1] * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1]) + sin(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-0.5e0 * omega * v1[0] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1] * exp(-x[1]) + 0.5e0 * omega * v1[1] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1] * exp(-x[1])) - sin(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (0.5e0 * v1[0] * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1] - 0.5e0 * v1[1] * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1]) - cos(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-0.5e0 * omega * v1[0] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1] * exp(-x[1]) + 0.5e0 * omega * v1[1] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1] * exp(-x[1])) - cos(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (0.5e0 * v2[0] * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1] - 0.5e0 * v2[1] * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1]) + sin(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-0.5e0 * omega * v2[0] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1] * exp(-x[1]) + 0.5e0 * omega * v2[1] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1] * exp(-x[1])) + sin(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (0.5e0 * v2[0] * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1] - 0.5e0 * v2[1] * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1]) + cos(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-0.5e0 * omega * v2[0] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1] * exp(-x[1]) + 0.5e0 * omega * v2[1] * alpha[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1] * exp(-x[1])) + (alpha[0] + 0.5e0 * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1]) * u[0] + (-0.5e0 * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] - 0.2e1 * x[1]) * u[1] - v1[0] * (-0.5e0 * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] - 0.25e0 * alpha[0] * pow(alpha[1], 0.2e1) * pow(exp(-x[1]), 0.2e1) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1]) * w1[1] - v1[1] * (0.5e0 * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] + 0.25e0 * alpha[0] * pow(alpha[1], 0.2e1) * pow(exp(-x[1]), 0.2e1) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] - 0.2e1) * w1[1] - v2[0] * (-0.5e0 * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] - 0.25e0 * alpha[0] * pow(alpha[1], 0.2e1) * pow(exp(-x[1]), 0.2e1) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1]) * w2[1] - v2[1] * (0.5e0 * alpha[0] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] + 0.25e0 * alpha[0] * pow(alpha[1], 0.2e1) * pow(exp(-x[1]), 0.2e1) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] - 0.2e1) * w2[1];
  residuum[8] = -cos(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-v1[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1] + v1[1] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1]) - sin(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-v1[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1] + v1[1] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1]) - cos(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-v2[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1] + v2[1] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1]) + sin(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-v2[0] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1] + v2[1] * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1]) + (x[1] - exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1]) * u[0] + exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] * u[1] - v1[0] * (0.1e1 + 0.5e0 * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1]) * w1[1] + 0.5e0 * v1[1] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] * w1[1] - v2[0] * (0.1e1 + 0.5e0 * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1]) * w2[1] + 0.5e0 * v2[1] * alpha[1] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] * w2[1] + r[0];
  residuum[9] = -cos(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-v1[0] * alpha[0] * (-0.15e1 + 0.5e0 * exp(-x[1])) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1] + v1[1] * alpha[0] * (-0.15e1 + 0.5e0 * exp(-x[1])) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1]) - sin(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-v1[0] * alpha[0] * (-0.15e1 + 0.5e0 * exp(-x[1])) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1] + v1[1] * alpha[0] * (-0.15e1 + 0.5e0 * exp(-x[1])) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1]) - cos(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-v2[0] * alpha[0] * (-0.15e1 + 0.5e0 * exp(-x[1])) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1] + v2[1] * alpha[0] * (-0.15e1 + 0.5e0 * exp(-x[1])) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w2[1]) + sin(omega * (0.15e1 - 0.5e0 * exp(-x[1]))) * (-v2[0] * alpha[0] * (-0.15e1 + 0.5e0 * exp(-x[1])) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1] + v2[1] * alpha[0] * (-0.15e1 + 0.5e0 * exp(-x[1])) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * w1[1]) + (-x[0] - alpha[0] * (-0.15e1 + 0.5e0 * exp(-x[1])) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1]) * u[0] + alpha[0] * (-0.15e1 + 0.5e0 * exp(-x[1])) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] * u[1] - v1[0] * (-w1[0] + (0.5e0 * alpha[0] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] + 0.5e0 * alpha[0] * alpha[1] * exp(-x[1]) * (-0.15e1 + 0.5e0 * exp(-x[1])) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1]) * w1[1]) - v1[1] * (-0.5e0 * alpha[0] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] - 0.5e0 * alpha[0] * alpha[1] * exp(-x[1]) * (-0.15e1 + 0.5e0 * exp(-x[1])) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1]) * w1[1] - v2[0] * (-w2[0] + (0.5e0 * alpha[0] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] + 0.5e0 * alpha[0] * alpha[1] * exp(-x[1]) * (-0.15e1 + 0.5e0 * exp(-x[1])) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1]) * w2[1]) - v2[1] * (-0.5e0 * alpha[0] * exp(-x[1]) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1] - 0.5e0 * alpha[0] * alpha[1] * exp(-x[1]) * (-0.15e1 + 0.5e0 * exp(-x[1])) * exp(-alpha[1] * (0.15e1 - 0.5e0 * exp(-x[1]))) * x[1]) * w2[1] + r[1];
}
