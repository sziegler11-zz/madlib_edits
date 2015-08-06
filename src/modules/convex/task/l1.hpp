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

template <class Model>
class L1 {
public:
    typedef Model model_type;

    static void clipping(
            model_type                          &incrModel,
            const double                        &lambda, 
            const double                        &stepsize);

    static double loss(
            const model_type                    &model, 
            const double                        &lambda);
};

template <class Model>
void
L1<Model>::clipping(
        model_type                          &incrModel,
        const double                        &lambda, 
        const double                        &stepsize) {
    // implement the Clipping method mentioned in Tsuruoka et al. 2009
    for (Index i = 0; i < incrModel.size(); i++) {
        if (incrModel(i) > lambda * stepsize) {
            incrModel(i) -= lambda * stepsize;
        } else if (incrModel(i) < - lambda * stepsize) {
            incrModel(i) += lambda * stepsize;
        } else { incrModel(i) = 0.; }
    }
}

template <class Model>
double 
L1<Model>::loss(
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


