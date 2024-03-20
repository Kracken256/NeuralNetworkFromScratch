#ifndef __NEURON_HPP__
#define __NEURON_HPP__

#include <functional>
#include <iostream>

namespace nnfs
{
    typedef std::function<float(float)> ActivationFunction;
    typedef std::function<float(float)> ActivationFunctionDerivative;

    /// @brief Neuron interface
    class INeuron
    {
    public:
        virtual ~INeuron() = default;

        /// @brief Returns the neuron value
        /// @return The neuron value
        virtual float GetValue() const = 0;

        /// @brief Returns the activation value
        /// @return The activation value
        virtual float GetActivation() const = 0;

        /// @brief Returns the derived value
        /// @return The derived value
        virtual float GetDerived() const = 0;

        virtual ActivationFunction GetActivationFunction() const = 0;
        virtual ActivationFunctionDerivative GetActivationFunctionDerivative() const = 0;

        /// @brief Get string representation of the neural type
        /// @return The string representation of the neural type
        virtual const char *GetNeuronType() const { return "INeuron"; }

        /// @brief Dump the neuron state in JSON format
        virtual void DumpJson(std::ostream &os) const = 0;

        virtual bool operator==(const INeuron &n) const = 0;
    };

    template <float (*A)(float), float (*D)(float)>
    class Neuron : public INeuron
    {
        float m_value;
        float m_activation;
        float m_derived;

    public:
        Neuron() = default;

        inline Neuron(float value)
        {
            m_value = value;
            m_activation = A(m_value);
            m_derived = D(m_activation);
        }

        inline float GetValue() const override { return m_value; }
        inline float GetActivation() const override { return m_activation; }
        inline float GetDerived() const override { return m_derived; }

        inline ActivationFunction GetActivationFunction() const override { return A; }
        inline ActivationFunctionDerivative GetActivationFunctionDerivative() const override { return D; }
        inline const char *GetNeuronType() const override { return "StdNeuron0"; }

        inline void DumpJson(std::ostream &os) const override
        {
            os << "{\"v\":" << m_value << ",\"a\":" << m_activation << ",\"d\":" << m_derived << "}";
        }

        inline bool operator==(const INeuron &n) const override
        {
            constexpr auto epsilon = 0.0001f;

            return (m_value - n.GetValue()) < epsilon;
        }
    };

    template <float (*A)(float), float (*D)(float)>
    class LSTMNeuron : public INeuron
    {
        /// TODO: Learn about AI. Then implement this class.
    };

    template <float (*A)(float), float (*D)(float)>
    class GRUNeuron : public INeuron
    {
        /// TODO: Learn about AI. Then implement this class.
    };

    template <float (*A)(float), float (*D)(float)>
    class RNNNeuron : public INeuron
    {
        /// TODO: Learn about AI. Then implement this class.
    };

    template <float (*A)(float), float (*D)(float)>
    class CNNNeuron : public INeuron
    {
        /// TODO: Learn about AI. Then implement this class.
    };
} // namespace nnfs

namespace std
{
    ostream &operator<<(ostream &os, const nnfs::INeuron &n)
    {
        n.DumpJson(os);
        return os;
    }
} // namespace std

#endif // __NEURON_HPP__