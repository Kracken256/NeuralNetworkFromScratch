#ifndef __ACTIVATION_HPP__
#define __ACTIVATION_HPP__

namespace nnfs
{
    namespace Activation
    {
        float FastSigmoid(float x);
        float FastSigmoidDerivative(float x);
        float ReLU(float x);
        float ReLUDerivative(float x);
        float Sigmoid(float x);
        float SigmoidDerivative(float x);
        float TanH(float x);
        float TanHDerivative(float x);
        float LeakyReLU(float x);
        float LeakyReLUDerivative(float x);
    }
}

#endif // __ACTIVATION_HPP__