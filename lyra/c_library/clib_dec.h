#ifndef LYRA_DECODER_WRAPPER_H_
#define LYRA_DECODER_WRAPPER_H_

#include <cstdint>
#include <memory>
#include <cstddef>

#include "lyra/lyra_decoder.h"

/// Extern "C" block for C compatibility.
extern "C" {
  
  /// Creates a LyraDecoder instance.
  ///
  /// @param sample_rate_hz Desired sample rate in Hertz. Supported rates: 8000, 16000, 32000, 48000.
  /// @param num_channels Number of channels. Only 1 is currently supported.
  /// @param bitrate Desired bitrate. Supported bitrates: 3200, 6000, 9200.
  /// @param model_path Path to the model weights file.
  /// @return A pointer to the created LyraDecoder instance if parameters are supported, otherwise nullptr.
  void* Create(int sample_rate_hz, int num_channels, int bitrate, const char* model_path);

  /// Gets the decoder's sample rate.
  ///
  /// @param decoderPTR Pointer to the LyraDecoder instance.
  /// @return Sample rate in Hertz.
  int get_sample_rate_hz(void* decoderPTR);

  /// Gets the decoder's number of channels.
  ///
  /// @param decoderPTR Pointer to the LyraDecoder instance.
  /// @return Number of channels.
  int get_num_channels(void* decoderPTR);

  /// Gets the decoder's frame rate.
  ///
  /// @param decoderPTR Pointer to the LyraDecoder instance.
  /// @return Frame rate.
  int get_frame_rate(void* decoderPTR);

  /// Checks if the decoder is in comfort noise generation mode.
  ///
  /// @param decoderPTR Pointer to the LyraDecoder instance.
  /// @return True if the decoder is in comfort noise generation mode.
  bool is_comfort_noise(void* decoderPTR);

  /// Sets an encoded packet for decoding.
  ///
  /// @param decoderPTR Pointer to the LyraDecoder instance.
  /// @param encodedPTR Pointer to the encoded packet data.
  /// @param encodedLENGTH Length of the encoded packet.
  /// @return True if the packet is valid and successfully set.
  bool SetEncodedPacket(void* decoderPTR, const uint8_t* encodedPTR, size_t encodedLENGTH);

  /// Decodes audio samples from the set encoded packet.
  ///
  /// If more samples are requested than are available, packet loss mode is used
  /// to generate samples, which will attempt to conceal lost packets and transition to comfort noise.
  ///
  /// @param decoderPTR Pointer to the LyraDecoder instance.
  /// @param outputBuf Pointer to the output buffer where decoded samples will be stored.
  /// @param num_samples Number of samples to decode; must be less than or equal to the length of outputBuf.
  /// @return True on successful decoding, otherwise false.
  bool DecodeSamples(void* decoderPTR, int16_t* outputBuf, int num_samples);

}  // extern "C"

#endif  // LYRA_DECODER_WRAPPER_H_
