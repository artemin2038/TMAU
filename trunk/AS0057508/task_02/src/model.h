#ifndef MODEL_H
#define MODEL_H

// Функция для расчета одного шага линейной модели
double calculateLinearStep(double y_curr, double u_curr, double a, double b);

// Функция для расчета одного шага нелинейной модели
double calculateNonlinearStep(double y_curr, double y_prev, double u_curr, double u_prev, double a, double b, double c, double d);

#endif
