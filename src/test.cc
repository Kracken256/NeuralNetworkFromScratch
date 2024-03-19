#include <Neuron.hh>
#include <Activation.hh>
#include <iostream>

using namespace nnfs;

int main()
{
    std::cout << Neuron<Activation::FastSigmoid, Activation::FastSigmoidDerivative>(1.5) << std::endl;
    std::cout << Neuron<Activation::ReLU, Activation::ReLUDerivative>(1.5) << std::endl;
    std::cout << Neuron<Activation::Sigmoid, Activation::SigmoidDerivative>(1.5) << std::endl;
    std::cout << Neuron<Activation::TanH, Activation::TanHDerivative>(1.5) << std::endl;
    std::cout << Neuron<Activation::LeakyReLU, Activation::LeakyReLUDerivative>(1.5) << std::endl;
    return 0;
}