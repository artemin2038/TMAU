#ifndef MODEL_H
#define MODEL_H

// Линейная модель: y_{t+1} = a*y_t + b*u_t
double linear_model(double y, double u, double a, double b);

// Нелинейная модель: y_{t+1} = a*y_t - b*y_{t-1}^2 + c*u_t + d*sin(u_{t-1})
double nonlinear_model(double y, double y_prev, double u, double u_prev, 
                        double a, double b, double c, double d);

#endif // MODEL_H