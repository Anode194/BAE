/*! ****************************************************************************
\file             LowPass.hpp
\author           Chyler Morrison
\par    Email:    contact\@chyler.info
\par    Project:  Audio Engine

\copyright        Copyright © 2019 Chyler Morrison
*******************************************************************************/

#ifndef __LOW_PASS_HPP
#define __LOW_PASS_HPP

// Include Files                ////////////////////////////////////////////////

#include "../Engine.hpp"

#include "ModifierBase.hpp"

// Public Macros                ////////////////////////////////////////////////

// Forward References           ////////////////////////////////////////////////

// Public Enums                 ////////////////////////////////////////////////

// Public Objects               ////////////////////////////////////////////////

namespace OCAE
{
namespace Modifier
{
	/*! ************************************************************************
	\brief
	***************************************************************************/
	class LowPass : public ModifierBase
	{
	private:

		// Members              ///////////////////////

		Math_t m_Cutoff;
		Math_t m_Resonance;
		Math_t m_Coefficients[4];
		StereoData m_Outputs[3];

	public:

		// Con-/De- structors   ///////////////////////

		LowPass(LowPass const & other) = delete;
		LowPass(LowPass && other) noexcept = default;

		/*! ********************************************************************
		\brief
			Default destructor.
		***********************************************************************/
		virtual ~LowPass() = default;

		LowPass & operator=(LowPass const & rhs) = delete;
		LowPass & operator=(LowPass && rhs) noexcept = default;

		// Operators            ///////////////////////

		// Accossors/Mutators   ///////////////////////

		/*! ********************************************************************
		\brief
			Sets the cutoff frequency of the filter.

		\param cutoff
			The cutoff frequency.
		***********************************************************************/
		void SetCutoff(Math_t cutoff);

		/*! ********************************************************************
		\brief
			Sets the resonance angle of the filter.

		\param resonance
			The resonance angle, in range [0,1/6]. No safety checks are
			performed.
		***********************************************************************/
		void SetResonance(Math_t resonance);

		// Functions            ///////////////////////

		/*! ********************************************************************
		\brief
			Takes input sample and filters it, returning the result.

		\param input
			The input sample.

		\return
			The filtered sample.
		***********************************************************************/
		virtual StereoData FilterSample(StereoData const & input);

		virtual bool IsBase() { return false; };

		friend class ModifierFactory;

	protected:

		// Functions                  ///////////////////////

		/*! ********************************************************************
		\brief
			Constructor.

		\param cutoff
			The cutoff frequency in Hz.

		\param resonance
			The resonance angle of the filter, value can be in range [0,1/6]. No
			safety checks are performed.
		***********************************************************************/
		LowPass(Math_t cutoff, Math_t resonance);

		virtual std::vector<std::tuple<std::string, Void_fn>> CreateMethodList();

		void Reset();

	}; // class LowPass
	TYPEDEF_SHARED(LowPass);
} // namespace Modifier
} // namespace OCAE

// Public Functions             ////////////////////////////////////////////////

#endif // __LOW_PASS_HPP
