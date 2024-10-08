#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <memory>
#include <optional>
#include <vector>
#include <span>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "absl/types/span.h"
#include "glog/logging.h"  // IWYU pragma: keep
#include "include/ghc/filesystem.hpp"
#include "lyra/lyra_config.h"
#include "lyra/lyra_encoder.h"
#include "lyra/lyra_decoder.h"
#include "lyra/no_op_preprocessor.h"
#include "lyra/wav_utils.h"

/// Lyra Encoder.
extern "C" {
  /// Static method to create a LyraEncoder.
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
    static void* Create(int sample_rate_hz, int num_channels, int bitrate, bool enable_dtx, const char* model_path){
        std::unique_ptr<chromemedia::codec::LyraEncoder> encoder = chromemedia::codec::LyraEncoder::Create(sample_rate_hz, num_channels, bitrate, enable_dtx, model_path);
        return encoder.get();
    }

  /// Encodes the audio samples into a vector wrapped byte array.
  ///
  /// @param audio Span of int16-formatted samples. It is assumed to contain
  ///              20ms of data at the sample rate chosen at Create time.
  /// @return Encoded packet as a vector of bytes if the correct number of
  ///              of samples are provided, otherwise it returns nullopt.
  ///              The return vector will be of length zero if discontinuous
  ///              transmission mode is enabled and the frame contains
  ///              background noise.
  static bool Encode(void* encoderPTR, const int16_t* audioPTR, uint8_t* outputBuf, size_t audioLENGTH){ 
    chromemedia::codec::LyraEncoder* encoder = (chromemedia::codec::LyraEncoder*) encoderPTR;
    absl::Span<const int16_t> audio(audioPTR, audioLENGTH);
    std::optional<std::vector<uint8_t>> outVec = encoder->Encode(audio);
    if (outVec.has_value()){
        const std::vector<uint8_t>& vec = *outVec;
        // write outbuffer
        std::memcpy(outputBuf, vec.data(), vec.size());
        return true;
    } else {
        return false;
    }
  }

  /// Setter for the bitrate.
  ///
  /// @param bitrate Desired bitrate in bps.
  /// @return True if the bitrate is supported and set correctly.
  bool set_bitrate(void* encoderPTR, int bitrate){
    chromemedia::codec::LyraEncoder* encoder = (chromemedia::codec::LyraEncoder*) encoderPTR;
    return encoder->set_bitrate(bitrate);
  }

  /// Getter for the sample rate in Hertz.
  ///
  /// @return Sample rate in Hertz.
  int get_sample_rate_hz(void* encoderPTR){
    chromemedia::codec::LyraEncoder* encoder = (chromemedia::codec::LyraEncoder*) encoderPTR;
    return encoder->sample_rate_hz();
  }

 /// Getter for the number of channels.
  ///
  /// @return Number of channels.
  int get_num_channels(void* encoderPTR){
    chromemedia::codec::LyraEncoder* encoder = (chromemedia::codec::LyraEncoder*) encoderPTR;
    return encoder->num_channels();
  }

  /// Getter for the bitrate.
  ///
  /// @return Bitrate.
  int get_bitrate(void* encoderPTR){
    chromemedia::codec::LyraEncoder* encoder = (chromemedia::codec::LyraEncoder*) encoderPTR;
    return encoder->bitrate();
  }

  /// Getter for the frame rate.
  ///
  /// @return Frame rate.
  int get_frame_rate(void* encoderPTR){
    chromemedia::codec::LyraEncoder* encoder = (chromemedia::codec::LyraEncoder*) encoderPTR;
    return encoder->frame_rate();
  }
}
