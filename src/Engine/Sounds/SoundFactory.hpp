/*! ****************************************************************************
\file             SoundFactory.hpp
\author           Chyler Morrison
\par    Email:    contact\@chyler.info
\par    Project:  Audio Engine

\copyright        Copyright © 2019 Chyler Morrison
*******************************************************************************/

#ifndef __STUB_HPP
#define __STUB_HPP

// Include Files                ////////////////////////////////////////////////

#include "../Engine.hpp"

#include "../Modifiers/ModifierBase.hpp"
#include "../Generators/GeneratorBase.hpp"
#include "Sound.hpp"

// Public Macros                ////////////////////////////////////////////////

// Forward References           ////////////////////////////////////////////////

// Public Enums                 ////////////////////////////////////////////////

// Public Objects               ////////////////////////////////////////////////

namespace OCAE
{
namespace Sound
{
	/*! ************************************************************************
	\brief
	***************************************************************************/
	class SoundFactory
	{
	private:

		// Members              ///////////////////////

	public:

		// Functions            ///////////////////////

		static SoundPtr CreateEmptySound();
		static SoundPtr CreateBasicGenerator(Generator::GeneratorBasePtr const &);
		static SoundPtr CreateBasicModifier(Modifier::ModifierBasePtr const &);

		static BlockPtr CreateBlock(Generator::GeneratorBasePtr const &);
		static BlockPtr CreateBlock(Modifier::ModifierBasePtr const &);
		static BlockPtr CreateBlock(Generator::GeneratorBasePtr const &, Modifier::ModifierBasePtr const &);
		static BlockPtr CreateBlock(Generator::GeneratorBasePtr const &, Modifier::ModifierBasePtr const &, Block::Interaction_f const & interactor);

		~SoundFactory() = delete;

	private:

		// Functions                  ///////////////////////

	}; // class SoundFactory
} // namespace Sound
} // namespace OCAE

// Public Functions             ////////////////////////////////////////////////

#endif // __STUB_HPP
