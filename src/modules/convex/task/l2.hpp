/* ----------------------------------------------------------------------- *//**
 *
 * @file l2.hpp
 *
 *//* ----------------------------------------------------------------------- */

#ifndef MADLIB_MODULES_CONVEX_TASK_L2_HPP_
#define MADLIB_MODULES_CONVEX_TASK_L2_HPP_

#include <dbconnector/dbconnector.hpp>

namespace madlib {

namespace modules {

namespace convex {

// Use Eigen
using namespace madlib::dbal::eigen_integration;

template <class Model, class Hessian = Matrix>
class L2 {
public:
    typedef Model model_type;
    typedef Hessian hessian_type;

    static void gradient(
            const model_type                    &model,
            const double                        &lambda,
            model_type                          &gradient);

    static void gradientInPlace(
            model_type                          &incrModel,
            const double                        &lambda, 
            const double                        &stepsize);

    static void hessian(
            const model_type                    &model,
            const double                        &lambda,
            hessian_type                        &hessian);

    static double loss(
            const model_type                    &model,
            const double                        &lambda);
};

template <class Model, class Hessian>
void
L2<Model, Hessian>::gradient(
        const model_type                    &model,
        const double                        &lambda,
        model_type                          &gradient) {
    for (Index i = 0; i < model.size(); i++) {
        gradient(i) += 2 * lambda * model(i);
    }
}

template <class Model, class Hessian>
void
L2<Model, Hessian>::gradientInPlace(
        model_type                          &incrModel,
        const double                        &lambda, 
        const double                        &stepsize) {
    incrModel *= 1 - 2 * lambda * stepsize;
}

template <class Model, class Hessian>
void
L2<Model, Hessian>::hessian(
        const model_type                    &model,
        const double                        &lambda,
        hessian_type                        &hessian) {
    int n = model.size();
    hessian += 2 * lambda * hessian.Identity(n, n);
}

template <class Model, class Hessian>
double
L2<Model, Hessian>::loss(
        const model_type                    &model,
        const double                        &lambda) {
    double s = 0.;
    for (Index i = 0; i < model.size(); i ++) {
        s += model(i) * model(i);
    }
    return lambda * s;
}

} // namespace convex

} // namespace modules

} // namespace madlib

#endif


