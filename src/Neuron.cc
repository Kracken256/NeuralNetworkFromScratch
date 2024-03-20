#include <Neuron.hh>

std::map<float, std::unique_ptr<nnfs::ConstantInit>> nnfs::ConstantInit::m_cache;
std::map<std::pair<float, float>, std::unique_ptr<nnfs::UniformInit>> nnfs::UniformInit::m_cache;
