#include <Activation.hh>
#include <Network.hh>
#include <iostream>
#include <sstream>

using namespace nnfs;

int main()
{
    auto network = Network::create<Neuron<Activation::TanH, Activation::TanHDerivative>>({12, 6, 6, 8}, 0.12f);

    DNANetworkSerializer::Serialize(*network, std::cout);
    std::cout << std::endl;
    
    Network net;

    std::stringstream ss;
    ss << "ATGATGATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTUAAATGATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTUAAATGATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTUAAATGATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTATTCTTCCTAAGGATTUAAUAA";

    if (!DNANetworkSerializer::Deserialize<Neuron<Activation::TanH, Activation::TanHDerivative>>(net, ss))
    {
        std::cerr << "Failed to deserialize network" << std::endl;
        return 1;
    }

    if (net != *network)
    {
        std::cerr << "Deserialized network does not match original" << std::endl;
        return 1;
    }

    std::cout << "Deserialized network matches original" << std::endl;
    return 0;
}