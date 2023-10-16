#include <iostream>
#include <cmath>
#include <iomanip>

class Integral {
public:
    Integral(double* x_values, double* y_values, int n)
        : x_values(x_values), y_values(y_values), n(n) {}

    double leftRectangleMethod() {
        double sum = 0.0;
        for (int i = 0; i < n - 1; ++i) {
            sum += y_values[i];
        }
        return (x_values[1] - x_values[0]) * sum;
    }

    double middleRectangleMethod(double result_right, double result_left) {
        return (result_left+result_right) / 2;
    }

    double rightRectangleMethod() {
        double sum = 0.0;
        for (int i = 1; i < n; ++i) {
            sum += y_values[i];
        }
        return (x_values[n - 1] - x_values[n - 2]) * sum;
    }

    double trapezoidalMethod() {
        double sum = 0.0;
        for (int i = 1; i < n - 1; ++i) {
            sum += y_values[i];
        }
        return ((x_values[n - 1] - x_values[0]) / (2 * (n - 1))) * (y_values[0] + 2 * sum + y_values[n - 1]);
    }

    double simpsonsMethod() {
        if (n % 2 == 0) {
            std::cerr << "Number of intervals must be odd for Simpson's method." << std::endl;
            return 0.0;
        }

        double sum_even = 0.0;
        double sum_odd = 0.0;
        for (int i = 1; i < n - 1; ++i) {
            if (i % 2 == 0) {
                sum_even += y_values[i];
            }
            else {
                sum_odd += y_values[i];
            }
        }
        return ((x_values[n - 1] - x_values[0]) / (3 * (n - 1))) * (y_values[0] + 4 * sum_odd + 2 * sum_even + y_values[n - 1]);
    }

    double newtonMethod() {
        double result = 0.0;
        for (int i = 0; i < n - 1; ++i) {
            double h = x_values[i + 1] - x_values[i];
            result += h * (y_values[i] + y_values[i + 1]) / 2.0;
        }
        return result;
    }

    void print(double* values, int n) {
        for (int i = 0; i < n; i++)
        {
            std::cout << values[i] << " ";
        }
        std::cout << "\n";
    }

private:
    double* x_values;
    double* y_values;
    int n;
};

int main() {
    int n = 0;  
    std::cin >> n;
    double* x{ new double[n] };
    double* y{ new double[n] };

    for (int i = 0; i < n; i++)
    {
        std::cin >> x[i];
    }
    for (int i = 0; i < n; i++)
    {
        std::cin >> y[i];
    }


    Integral integral(x, y, n);

    double result_left = integral.leftRectangleMethod();
    double result_right = integral.rightRectangleMethod();    
    double result_middle = integral.middleRectangleMethod(result_left, result_right);
    double result_trapezoidal = integral.trapezoidalMethod();
    double result_simpsons = integral.simpsonsMethod();
    double result_newton = integral.newtonMethod(); 

    std::cout << "input= argument ";
    integral.print(x, n);
    std::cout << "function ";
    integral.print(y, n);
    std::cout << "lev priam= " << result_left << std::endl;
    std::cout << "sr priam= " << result_middle << std::endl;
    std::cout << "prav priam= " << result_right << std::endl;
    std::cout << "trapeciy= " << result_trapezoidal << std::endl;
    std::cout << std::setprecision(5) << "Simpson= " << result_simpsons << std::endl;
    std::cout << "Newton " << result_newton << std::endl;

    return 0;
}