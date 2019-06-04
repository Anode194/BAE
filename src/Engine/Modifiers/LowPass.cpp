/*! ****************************************************************************
\file             LowPass.cpp
\author           Chyler Morrison
\par    Email:    contact\@chyler.info
\par    Project:  AudioEngine

\copyright        Copyright © 2018 Chyler
*******************************************************************************/

// Include Files                          //////////////////////////////////////

#include "LowPass.hpp"

// Private Macros                         //////////////////////////////////////

// Private Enums                          //////////////////////////////////////

// Private Objects                        //////////////////////////////////////

// Private Function Declarations          //////////////////////////////////////

// Public Functions                       //////////////////////////////////////

namespace AudioEngine
{
namespace Modifier
{

  LowPass::LowPass(Math_t cutoff, Math_t resonance) : Base(false),
    m_Cutoff(2*PI*cutoff), m_Resonance(resonance),
    m_Coefficients(), m_Outputs(), m_Table()
  {
    m_Table["SetCutoff"] = [this](void * c){ SetCutoff(*reinterpret_cast<Math_t*>(c)); };
    m_Table["SetResonance"] = [this](void * r){ SetResonance(*reinterpret_cast<Math_t*>(r)); };

    Reset();
  }

  void LowPass::SetCutoff(Math_t cutoff)
  {
    m_Cutoff = 2*PI*cutoff;
    Reset();
  }

  void LowPass::SetResonance(Math_t resonance)
  {
    m_Resonance = resonance;
    Reset();
  }

  StereoData_t LowPass::FilterSample(StereoData_t const & input)
  {
    StereoData_t output(
      float(m_Coefficients[0] * std::get<0>(input) +
      m_Coefficients[1] * std::get<0>(m_Outputs[0]) +
      m_Coefficients[2] * std::get<0>(m_Outputs[1]) +
      m_Coefficients[3] * std::get<0>(m_Outputs[2])),

      float(m_Coefficients[0] * std::get<1>(input) +
      m_Coefficients[1] * std::get<1>(m_Outputs[0]) +
      m_Coefficients[2] * std::get<1>(m_Outputs[1]) +
      m_Coefficients[3] * std::get<1>(m_Outputs[2]))
    );

    //std::memmove(m_Outputs+1, m_Outputs, sizeof(*m_Outputs));
    for(uint32_t i = sizeof(m_Outputs) / sizeof(*m_Outputs) - 1; i > 0; --i)
    {
      m_Outputs[i] = m_Outputs[i - 1];
    }
    m_Outputs[0] = output;

    return output;
  }

  MethodTable_t const & LowPass::GetMethodTable() const
  {
    return m_Table;
  }

} // namespace Modifier
} // namespace AudioEngine

// Private Functions                      //////////////////////////////////////

namespace AudioEngine
{
namespace Modifier
{

  void LowPass::Reset()
  {
    static double angle, K, T, x, y, z, g;

    angle = (PI/6)*double(4 - m_Resonance);
    K = 1 - 2*std::cos(angle);
    T = double(m_Cutoff) * INC_RATE;
    x = K*T;
    y = K*T*T;
    z = T*T*T;
    g = 1 + x + y + z;

    m_Coefficients[3] =  1/g;
    m_Coefficients[0] =  m_Coefficients[3] * z;
    m_Coefficients[1] =  m_Coefficients[3] * (3 + 2*x + y);
    m_Coefficients[2] = -m_Coefficients[3] * (3 + x);
  }

} // namespace Modifier
} // namespace AudioEngine
