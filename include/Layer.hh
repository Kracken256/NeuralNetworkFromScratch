#ifndef __LAYER_HPP__
#define __LAYER_HPP__

#include <Neuron.hh>
#include <memory>
#include <vector>

namespace nnfs
{
    class Layer
    {
        std::vector<std::unique_ptr<INeuron>> m_neurons;

    public:
        Layer() = default;

        template <typename NeuronType>
        static std::unique_ptr<Layer> create(uint32_t size, float defaultValue = 0.0f)
        {
            auto layer = std::make_unique<Layer>();
            for (uint32_t i = 0; i < size; i++)
                layer->AddNeuron<NeuronType>(defaultValue);

            return layer;
        }

        Layer(const Layer &) = delete;
        Layer &operator=(const Layer &) = delete;

        template <typename NeuronType>
        inline void AddNeuron(float value)
        {
            m_neurons.push_back(std::make_unique<NeuronType>(value));
        }

        inline void DumpJson(std::ostream &os) const
        {
            os << "{\"neurons\":[";
            for (size_t i = 0; i < m_neurons.size(); i++)
            {
                m_neurons[i]->DumpJson(os);
                if (i < m_neurons.size() - 1)
                {
                    os << ",";
                }
            }
            os << "]}";
        }

        template <typename NeuronType>
        inline const NeuronType &operator[](size_t index) const { return *m_neurons[index]; }

        template <typename NeuronType>
        inline NeuronType &operator[](size_t index) { return *m_neurons[index]; }

        inline const INeuron &operator[](size_t index) const { return *m_neurons[index]; }

        inline INeuron &operator[](size_t index) { return *m_neurons[index]; }

        inline size_t size() const { return m_neurons.size(); }

        bool operator==(const Layer &other) const
        {
            if (m_neurons.size() != other.m_neurons.size())
                return false;

            for (size_t i = 0; i < m_neurons.size(); i++)
            {
                if (*m_neurons[i] != *other.m_neurons[i])
                    return false;
            }

            return true;
        }
    };
}

namespace std
{
    inline ostream &operator<<(ostream &os, const nnfs::Layer &layer)
    {
        layer.DumpJson(os);
        return os;
    }
}

#endif // __LAYER_HPP__