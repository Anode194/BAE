//! # Mixer

use super::*;

use std::collections::VecDeque;
use std::sync::Arc;
use crate::channels::{Channel, ChannelSP};
use crate::sounds::BlockSP;

/// Struct representing a typical mixer that you might find in a DAW
pub struct Mixer {
    modifier_list: Vec<BlockSP>,
    channel_list: VecDeque<ChannelSP>,
}

impl Mixer {
    /// Creates a new Mixer object with a given number of provided channels.
    /// 
    /// # Parameters
    /// 
    /// * `c` - The base channel type to clone for the channels of the mixer.
    /// Must implement the Clone trait.
    /// * `num` - The number of channels.
    pub fn new<T>(c: T, num: usize) -> Self
        where T: 'static + Channel + Clone
    {
        Mixer {
            modifier_list: Vec::new(),
            channel_list: {
                let mut vd = VecDeque::<ChannelSP>::with_capacity(num);

                for _ in 0..num {
                    vd.push_back(Arc::new(c.clone()));
                }

                vd
            },
        }
    }

    /// Returns an immutable reference to the internal list of [`Modifier`]s.
    /// 
    /// [`Modifier`]: ../../modifiers/trait.Modifier.html
    pub fn modifier_list(&self) -> &Vec<BlockSP> {
        &self.modifier_list
    }

    /// Returns a mutable reference to the internal list of [`Modifier`]s.
    /// 
    /// [`Modifier`]: ../../modifiers/trait.Modifier.html
    pub fn modifier_list_mut(&mut self) -> &mut Vec<BlockSP> {
        &mut self.modifier_list
    }

    /// Returns an immutable reference to the internal deque of [`Channel`]s.
    /// 
    /// [`Channel`]: ../trait.Channel.html
    pub fn channel_list(&self) -> &VecDeque<ChannelSP> {
        &self.channel_list
    }

    /// Returns a mutable reference to the internal deque of [`Channel`]s.
    /// 
    /// [`Channel`]: ../trait.Channel.html
    pub fn channel_list_mut(&mut self) -> &mut VecDeque<ChannelSP> {
        &mut self.channel_list
    }
}
