//! # Modifiers
//! 
//! Module including many of the common/basic filters including lowpass,
//! bandpass, echo, delay, etc.

use super::*;

pub trait Modifier {
	/// Filters the given audio sample.
	/// 
	/// # Parameters
	/// 
	/// * `x` - The "dry" audio sample before filtering.
	fn process(&mut self, x: StereoData) -> StereoData;
}

pub mod adsr;
pub mod bandpass;
pub mod delay;
pub mod echo;
pub mod envelope;
pub mod highpass;

pub use adsr::*;
pub use bandpass::*;
pub use delay::*;
pub use echo::*;
pub use envelope::*;
pub use highpass::*;
