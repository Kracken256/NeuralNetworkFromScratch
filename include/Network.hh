#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__

#include <Layer.hh>
#include <cstring>

namespace nnfs
{
    class Network
    {
        std::vector<std::unique_ptr<Layer>> m_layers;

    public:
        Network() = default;

        Network(const Network &) = delete;
        Network &operator=(const Network &) = delete;

        template <typename NeuronType>
        static std::unique_ptr<Network> create(std::vector<uint32_t> topology, IInit &init = InitZero::Get())
        {
            auto network = std::make_unique<Network>();
            for (size_t i = 0; i < topology.size(); i++)
            {
                network->AddLayer<NeuronType>(topology[i], init);
            }
            return network;
        }

        template <typename NeuronType>
        inline void AddLayer(uint32_t size, IInit &init = InitZero::Get())
        {
            m_layers.push_back(Layer::create<NeuronType>(size, init));
        }

        inline void DumpJson(std::ostream &os) const
        {
            os << "{\"layers\":[";
            for (size_t i = 0; i < m_layers.size(); i++)
            {
                m_layers[i]->DumpJson(os);
                if (i < m_layers.size() - 1)
                {
                    os << ",";
                }
            }
            os << "]}";
        }

        template <typename NeuronType>
        inline const Layer &operator[](size_t index) const { return *m_layers[index]; }

        template <typename NeuronType>
        inline Layer &operator[](size_t index) { return *m_layers[index]; }

        inline const Layer &operator[](size_t index) const { return *m_layers[index]; }

        inline Layer &operator[](size_t index) { return *m_layers[index]; }

        inline size_t size() const { return m_layers.size(); }

        inline bool operator==(const Network &other) const
        {
            if (m_layers.size() != other.m_layers.size())
            {
                return false;
            }

            for (size_t i = 0; i < m_layers.size(); i++)
            {
                if (*m_layers[i] != *other.m_layers[i])
                {
                    return false;
                }
            }

            return true;
        }
    };

    class DNANetworkSerializer
    {
        inline static void FloatToDNA(float value, std::ostream &os)
        {
            union
            {
                float f;
                uint32_t i;
            } u;
            const char *nucleotides = "ACGT";

            u.f = value;

            // Calculate number of digits required for fixed width output
            const int width = (sizeof(uint32_t) * 8) / 2; // Each base4 digit corresponds to 2 bits

            for (int i = width - 1; i >= 0; --i)
            {
                uint32_t mask = 0b11 << (2 * i);
                uint8_t digit = (u.i & mask) >> (2 * i);
                os << nucleotides[digit];
            }
        }

        inline static bool DNAToFloat(float &value, std::istream &is)
        {
            std::string nucleotides = "ACGT";

            union
            {
                float f;
                uint32_t i;
            } u;
            u.i = 0;

            const int width = (sizeof(uint32_t) * 8) / 2;

            char c[width];

            is.read(c, width);

            for (char base : c)
            {
                uint8_t digit = nucleotides.find(base);
                if (digit == std::string::npos)
                    return false;
                u.i <<= 2;    // Shift left by 2 bits to make space for new digit
                u.i |= digit; // Add the new digit
            }

            value = u.f;

            return true;
        }

    public:
        static void Serialize(const Network &network, std::ostream &os)
        {
            os << "ATG";

            for (size_t i = 0; i < network.size(); i++)
            {
                const Layer &layer = network[i];

                os << "ATG";

                for (size_t j = 0; j < layer.size(); j++)
                    FloatToDNA(layer[j].GetValue(), os);

                os << "UAA";
            }

            os << "UAA";
        }

        template <typename Neuron>
        inline static bool Deserialize(Network &network, std::istream &is)
        {
            char c[3];
            size_t l = 0;
            try
            {
                is.read(c, 3);
                if (memcmp(c, "ATG", 3) != 0)
                {
                    std::cerr << "Expected ATG" << std::endl;
                    return false;
                }

                while (true)
                {
                    is.read(c, 3);
                    if (memcmp(c, "UAA", 3) == 0)
                        break;

                    network.AddLayer<Neuron>(0);

                    while (true)
                    {
                        float value;
                        if (!DNAToFloat(value, is))
                        {
                            std::cerr << "Expected DNA" << std::endl;
                            return false;
                        }

                        network[l].AddNeuron<Neuron>(value);

                        c[0] = is.peek();
                        if (c[0] == 'U')
                        {
                            is.read(c, 3);
                            if (memcmp(c, "UAA", 3) == 0)
                                break;
                        }
                    }

                    l++;
                }

                return true;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                return false;
            }
        }
    };
}

namespace std
{
    inline ostream &operator<<(ostream &os, const nnfs::Network &n)
    {
        n.DumpJson(os);
        return os;
    }
}

#endif // __NETWORK_HPP__