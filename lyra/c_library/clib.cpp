#include "lyra/cli_example/encoder_main_lib.h"

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

/// Lyra Decoder.
extern "C" {

    /// Static method to create a LyraDecoder.
    ///
    /// @param sample_rate_hz Desired sample rate in Hertz. The supported sample
    ///                       rates are 8000, 16000, 32000 and 48000.
    /// @param num_channels Desired number of channels. Currently only 1 is
    ///                     supported.
    /// @param bit_rate Desired bit rate. The supported bit rates are 3200, 6000
    ///                 and 9200.
    /// @param model_path Path to the model weights. The identifier in the
    ///                   lyra_config.textproto has to coincide with the
    ///                   kVersionMinor constant in lyra_config.cc.
    /// @return ptr to a LyraDecoder or NULL on error.
    static void* Create(int sample_rate_hz, int num_channels, int bitrate, const char* model_path){
        std::unique_ptr<chromemedia::codec::LyraDecoder> decoder = chromemedia::codec::LyraDecoder::Create(sample_rate_hz, num_channels, model_path);
        return decoder.get();
    }

    /// Getter for the sample rate in Hertz.
    ///
    /// @param decoderPTR Pointer returned by Create
    /// @return Sample rate in Hertz.
    int get_sample_rate_hz(void* decoderPTR){
        chromemedia::codec::LyraDecoder* decoder = (chromemedia::codec::LyraDecoder*) decoderPTR;
        return decoder->sample_rate_hz();
    }

    /// Getter for the number of channels.
    ///
    /// @param decoderPTR Pointer returned by Create
    /// @return Number of channels.
    int get_num_channels(void* decoderPTR){
        chromemedia::codec::LyraDecoder* decoder = (chromemedia::codec::LyraDecoder*) decoderPTR;
        return decoder->num_channels();
    }

    /// Getter for the frame rate.
    ///
    /// @param decoderPTR Pointer returned by Create
    /// @return Frame rate.
    int get_frame_rate(void* decoderPTR){
        chromemedia::codec::LyraDecoder* decoder = (chromemedia::codec::LyraDecoder*) decoderPTR;
        return decoder->frame_rate();
    }

    /// Checks if the decoder is in comfort noise generation mode.
    ///
    /// @param decoderPTR Pointer returned by Create
    /// @return True if the decoder is in comfort noise generation mode.
    bool is_comfort_noise(void* decoderPTR){
        chromemedia::codec::LyraDecoder* decoder = (chromemedia::codec::LyraDecoder*) decoderPTR;
        return decoder->is_comfort_noise();
    }

    /// Parses a packet and prepares to decode samples from the payload.
    ///
    /// @param decoderPTR Pointer returned by Create
    ///
    /// @param encodedPTR Encoded packet as an array of bytes.
    /// @param encodedLENGTH Encoded packet length.
    /// @return True if the provided packet is a valid Lyra packet.
    bool SetEncodedPacket(void* decoderPTR, const uint8_t* encodedPTR, size_t encodedLENGTH){
        chromemedia::codec::LyraDecoder* decoder = (chromemedia::codec::LyraDecoder*) decoderPTR;

        absl::Span<const uint8_t> encoded(encodedPTR, encodedLENGTH);

        return decoder->SetEncodedPacket(encoded);
    }

    /// Decodes samples.
    ///
    /// If more samples are requested for decoding than are available from the
    /// payloads set by |SetEncodedPacket|, this will generate samples in packet
    /// loss mode. Packet loss mode will first attempt to conceal the lost packets
    /// and then transition to comfort noise.
    ///
    /// @param decoderPTR Pointer returned by Create
    /// @param outputBuf Output buffer where the samples will be placed.
    /// @param num_samples Number of samples to, must less or equal to outputBuf length.
    ///
    /// @return true on success, false on failure.
    bool DecodeSamples(void* decoderPTR, int16_t* outputBuf ,int num_samples){
        chromemedia::codec::LyraDecoder* decoder = (chromemedia::codec::LyraDecoder*) decoderPTR;

        std::optional<std::vector<int16_t>> outVec = decoder->DecodeSamples(num_samples);
        if (outVec.has_value()){
            const std::vector<int16_t>& vec = *outVec;
            // write outbuffer
            std::memcpy(outputBuf, vec.data(), num_samples*sizeof(int16_t));

            return true;
        } else {
            return false;
        }
    }
}
