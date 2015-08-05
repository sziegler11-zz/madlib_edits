/* ----------------------------------------------------------------------- *//**
 * 
 * @file l1.hpp
 *
 *//* ----------------------------------------------------------------------- */

#ifndef MADLIB_MODULES_CONVEX_TASK_L1_HPP_
#define MADLIB_MODULES_CONVEX_TASK_L1_HPP_

#include <dbconnector/dbconnector.hpp>

namespace madlib {

namespace modules {

namespace convex {

// Use Eigen
using namespace madlib::dbal::eigen_integration;

template <class Model, class Hessian = Matrix>
class L1 {
public:
    typedef Model model_type;
    typedef Hessian hessian_type;

    static void gradient(
            const model_type                    &model,
            const double                        &lambda, 
            model_type                          &gradient);

    static void gradientInPlace(
            const model_type                    &model,
            const double                        &lambda, 
            const double                        &stepsize);

    static double loss(
            const model_type                    &model, 
            const double                        &lambda);
};

template <class Model, class Hessian>
void
L1<Model, Hessian>::gradient(
        const model_type                    &model,
        const double                        &lambda, 
        model_type                          &gradient) {
}

template <class Model, class Hessian>
void
L1<Model, Hessian>::hessian(
        const model_type                    &model,
        const double                        &lambda, 
        const double                        &stepsize) {
}

template <class Model, class Hessian>
double 
L1<Model, Hessian>::loss(
        const model_type                    &model, 
        const double                        &lambda) {
    double s = 0.;
    for (Index i = 0; i < model.size(); i++)
        s += abs(model(i));
    return lambda * s;
}

} // namespace convex

} // namespace modules

} // namespace madlib

#endif


