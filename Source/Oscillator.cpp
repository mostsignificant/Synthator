#include "Oscillator.hpp"

Oscillator::Oscillator() : formula("tanh(sin(x))")
{
    initChaiscript();
    initOscillator();
}

void Oscillator::setFormula(String formula)
{
    this->formula = formula;
    initOscillator();
}

void Oscillator::initChaiscript()
{
    constexpr const auto pi = 3.14159265358979f;

    chai.add(chaiscript::const_var(pi), "pi");
    chai.add(chaiscript::var(std::ref(var)), "x");

    chai.add(chaiscript::fun([](float x) { return std::cos(x); }), "cos");
    chai.add(chaiscript::fun([](float x) { return std::cosh(x); }), "cosh");
    chai.add(chaiscript::fun([](float x) { return (0.0f < x) - (x < 0.0f); }), "sgn");
    chai.add(chaiscript::fun([](float x) { return (0.0f < x) - (x < 0.0f); }), "signum");
    chai.add(chaiscript::fun([](float x) { return std::sin(x); }), "sin");
    chai.add(chaiscript::fun([](float x) { return std::sinh(x); }), "sinh");
    chai.add(chaiscript::fun([](float x) { return std::tan(x); }), "tan");
    chai.add(chaiscript::fun([](float x) { return std::tanh(x); }), "tanh");
}

void Oscillator::initOscillator()
{
    initialise(
        [this](float x) {
            this->var = x;

            try
            {
                const auto sample = static_cast<float>(chai.eval<float>(formula.toRawUTF8()));
                return sample;
            }
            catch (const chaiscript::exception::eval_error &error)
            {
            }
            catch (const std::exception &ex)
            {
            }
            catch (...)
            {
            }
            return 0.0F;
        },
        128);
}
