// lyra_encoder_wrapper.h
#ifndef C_ENC_WRAPPER_H
#define C_ENC_WRAPPER_H

#include <stdbool.h>  // For the bool type
#include <stdint.h>   // For uint8_t and int16_t

#ifdef __cplusplus
extern "C" {
#endif

/// Method to create a LyraEncoder.
///
/// @param sample_rate_hz Desired sample rate in Hertz. The supported sample
///                       rates are 8000, 16000, 32000 and 48000.
/// @param num_channels Desired number of channels. Currently only 1 is
///                     supported.
/// @param bit_rate Desired bit rate. The supported bit rates are 3200, 6000
///                 and 9200.
/// @param enable_dtx Set to true if discontinuous transmission should be
///                   enabled.
/// @param model_path Path to the model weights. The identifier in the
///                   lyra_config.textproto has to coincide with the
///                   kVersionMinor constant in lyra_config.cc.
/// @return A unique_ptr to a LyraEncoder if all desired params are supported.
///         Else it returns a nullptr.
void* CreateEncoder(int sample_rate_hz, int num_channels, int bitrate, bool enable_dtx, const char* model_path);

// Method to delete a LyraEncoder.
///
/// @param encoder_ptr Pointer to the LyraEncoder to be deleted.
/// @return 0 on success, -1 on failure.
///
int DeleteEncoder(void* encoder_ptr);

/// Encodes the audio samples into a vector wrapped byte array.
///
/// @param audio Span of int16-formatted samples. It is assumed to contain
///              20ms of data at the sample rate chosen at Create time.
/// @return Encoded packet as a vector of bytes if the correct number of
///              of samples are provided, otherwise it returns nullopt.
///              The return vector will be of length zero if discontinuous
///              transmission mode is enabled and the frame contains
///              background noise.
bool Encode(void* encoderPTR, const int16_t* audioPTR, uint8_t* outputBuf, size_t audioLENGTH);

/// Setter for the bitrate.
///
/// @param bitrate Desired bitrate in bps.
/// @return True if the bitrate is supported and set correctly.
bool set_bitrate_encoder(void* encoderPTR, int bitrate);

/// Getter for the sample rate in Hertz.
///
/// @return Sample rate in Hertz.
int get_sample_rate_hz_encoder(void* encoderPTR);

/// Getter for the number of channels.
///
/// @return Number of channels.
int get_num_channels_encoder(void* encoderPTR);

/// Getter for the bitrate.
///
/// @return Bitrate.
int get_bitrate_encoder(void* encoderPTR);

/// Getter for the frame rate.
///
/// @return Frame rate.
int get_frame_rate_encoder(void* encoderPTR);

#ifdef __cplusplus
}
#endif

#endif // LYRA_ENCODER_WRAPPER_H
