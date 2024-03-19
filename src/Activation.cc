#include <Activation.hh>
#include <cmath>

float nnfs::Activation::FastSigmoid(float x)
{
    return x / (1 + std::abs(x));
}

float nnfs::Activation::FastSigmoidDerivative(float x)
{
    return 1 - x * x;
}

float nnfs::Activation::ReLU(float x)
{
    return std::max(0.0f, x);
}

float nnfs::Activation::ReLUDerivative(float x)
{
    return x > 0 ? 1 : 0;
}

float nnfs::Activation::Sigmoid(float x)
{
    return 1 / (1 + std::exp(-x));
}

float nnfs::Activation::SigmoidDerivative(float x)
{
    float sig = Sigmoid(x);
    return sig * (1 - sig);
}

float nnfs::Activation::TanH(float x)
{
    return std::tanh(x);
}

float nnfs::Activation::TanHDerivative(float x)
{
    float tanh_x = TanH(x);
    return 1 - tanh_x * tanh_x;
}

float nnfs::Activation::LeakyReLU(float x)
{
    return x > 0 ? x : 0.01f * x;
}

float nnfs::Activation::LeakyReLUDerivative(float x)
{
    return x > 0 ? 1 : 0.01f;
}