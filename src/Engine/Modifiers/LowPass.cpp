/*! ****************************************************************************
\file             LowPass.cpp
\author           Chyler Morrison
\par    Email:    contact\@chyler.info
\par    Project:  Audio Engine

\copyright        Copyright © 2019 Chyler Morrison
*******************************************************************************/

// Include Files                          //////////////////////////////////////

#include "LowPass.hpp"

// Private Macros                         //////////////////////////////////////

// Private Enums                          //////////////////////////////////////

// Private Objects                        //////////////////////////////////////

// Private Function Declarations          //////////////////////////////////////

// Public Functions                       //////////////////////////////////////

namespace OCAE
{
namespace Modifier
{
	LowPass::LowPass(Math_t cutoff, Math_t resonance) : ModifierBase(),
		m_Cutoff(OCAE_PI2*cutoff), m_Resonance(resonance),
		m_Coefficients(), m_Outputs()
	{
		RegisterMethods(CreateMethodList());
		Reset();
	}

	void LowPass::SetCutoff(Math_t cutoff)
	{
		m_Cutoff = 2*OCAE_PI*cutoff;
		Reset();
	}

	void LowPass::SetResonance(Math_t resonance)
	{
		m_Resonance = resonance;
		Reset();
	}

	StereoData LowPass::FilterSample(StereoData const & input)
	{
		StereoData output(
			SampleType(m_Coefficients[0] * Math_t(Left(input)) +
					   m_Coefficients[1] * Math_t(Left(m_Outputs[0])) +
					   m_Coefficients[2] * Math_t(Left(m_Outputs[1])) +
					   m_Coefficients[3] * Math_t(Left(m_Outputs[2]))),

			SampleType(m_Coefficients[0] * Math_t(Right(input)) +
					   m_Coefficients[1] * Math_t(Right(m_Outputs[0])) +
					   m_Coefficients[2] * Math_t(Right(m_Outputs[1])) +
					   m_Coefficients[3] * Math_t(Right(m_Outputs[2])))
		);

		//std::memmove(m_Outputs+1, m_Outputs, sizeof(*m_Outputs));
		for(uint32_t i = sizeof(m_Outputs) / sizeof(*m_Outputs) - 1; i > 0; --i)
		{
			m_Outputs[i] = m_Outputs[i - 1];
		}
		m_Outputs[0] = output;

		return output;
	}

	Tools::MethodTable::MethodList_t LowPass::CreateMethodList()
	{
		return {
			std::make_tuple(
				std::string("SetCutoff"),
				Tools::MethodTable::Void_fn(
					[this](void * p){
						SetCutoff(
							std::get<0>(
								*reinterpret_cast<
									std::tuple<OCAE_METHOD_PARAM_T(Math_t)>*
								>(p)
							)
						);
					}
				)
			),
			std::make_tuple(
				std::string("SetResonance"),
				Tools::MethodTable::Void_fn(
					[this](void * p){
						SetResonance(
							std::get<0>(
								*reinterpret_cast<
									std::tuple<OCAE_METHOD_PARAM_T(Math_t)>*
								>(p)
							)
						);
					}
				)
			)
		};
	}

	void LowPass::Reset()
	{
		static Math_t angle, K, T, g;

		angle = (OCAE_PI/6)*Math_t(4 - m_Resonance);
		K = 1 - 2*std::cos(angle);
		T = m_Cutoff * OCAE_INC_RATE;
		g = 1.0/(T*T*T + K*T*T + K*T + 1);
		

		// m_Coefficients[3] =  1/g;
		// m_Coefficients[0] =  m_Coefficients[3] * z;
		// m_Coefficients[1] =  m_Coefficients[3] * (3 + 2*x + y);
		// m_Coefficients[2] = -m_Coefficients[3] * (3 + x);

		m_Coefficients[0] = T*T*T;
		m_Coefficients[1] = (K*T*T + 2*K*T + 3) * g;
		m_Coefficients[2] = (-K*T-3) * g;
		m_Coefficients[3] = g;
	}
} // namespace Modifier
} // namespace OCAE

// Private Functions                      //////////////////////////////////////
