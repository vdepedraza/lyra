#ifndef LYRA_ENCODER_WRAPPER_H_
#define LYRA_ENCODER_WRAPPER_H_

#include <cstdint>
#include <memory>

#include "absl/types/span.h"
#include "include/ghc/filesystem.hpp"
#include "lyra/lyra_encoder.h"

/// Extern "C" block for C compatibility.
extern "C" {
  
  /// Creates a LyraEncoder instance.
  ///
  /// @param sample_rate_hz Desired sample rate in Hertz. Supported rates: 8000, 16000, 32000, 48000.
  /// @param num_channels Number of channels. Only 1 is currently supported.
  /// @param bitrate Desired bitrate. Supported bitrates: 3200, 6000, 9200.
  /// @param enable_dtx Enables discontinuous transmission if set to true.
  /// @param model_path Path to the model weights file.
  /// @return A pointer to the created LyraEncoder instance if parameters are supported, otherwise nullptr.
  void* Create(int sample_rate_hz, int num_channels, int bitrate, bool enable_dtx, const char* model_path);

  /// Encodes audio samples into a byte array.
  ///
  /// @param encoderPTR Pointer to the LyraEncoder instance.
  /// @param audioPTR Pointer to the int16-formatted audio samples.
  /// @param outputBuf Pointer to the output buffer for encoded data.
  /// @param audioLENGTH Number of samples in the audio buffer.
  /// @return True if encoding was successful, otherwise false.
  bool Encode(void* encoderPTR, const int16_t* audioPTR, uint8_t* outputBuf, size_t audioLENGTH);

  /// Sets the encoder's bitrate.
  ///
  /// @param encoderPTR Pointer to the LyraEncoder instance.
  /// @param bitrate Desired bitrate.
  /// @return True if bitrate is supported and successfully set.
  bool set_bitrate(void* encoderPTR, int bitrate);

  /// Gets the encoder's sample rate.
  ///
  /// @param encoderPTR Pointer to the LyraEncoder instance.
  /// @return Sample rate in Hertz.
  int get_sample_rate_hz(void* encoderPTR);

  /// Gets the encoder's number of channels.
  ///
  /// @param encoderPTR Pointer to the LyraEncoder instance.
  /// @return Number of channels.
  int get_num_channels(void* encoderPTR);

  /// Gets the encoder's bitrate.
  ///
  /// @param encoderPTR Pointer to the LyraEncoder instance.
  /// @return Bitrate.
  int get_bitrate(void* encoderPTR);

  /// Gets the encoder's frame rate.
  ///
  /// @param encoderPTR Pointer to the LyraEncoder instance.
  /// @return Frame rate.
  int get_frame_rate(void* encoderPTR);

}  // extern "C"

#endif  // LYRA_ENCODER_WRAPPER_H_
