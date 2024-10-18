
#include "lyra/lyra_decoder.h"
#include "c_dec.h"

namespace chromemedia {
namespace codec {
/// Lyra Decoder.
extern "C" { 
    
    void* CreateDecoder(int sample_rate_hz, int num_channels, int bitrate, const char* model_path) {      
        std::unique_ptr<LyraDecoder> decoder = LyraDecoder::Create(sample_rate_hz, num_channels, model_path);        
        if (!decoder) {
          return nullptr; // Return nullptr if creation failed
        } 

      // Release ownership of the decoder and return the raw pointer
      return decoder.release(); 
    }

    int DeleteDecoder(void* decoder_ptr) {
        if (decoder_ptr == nullptr) {
            return -1; // Return an error code if the pointer is null
        }
        
        delete static_cast<LyraDecoder*>(decoder_ptr);
        return 0; // Return 0 on success
    }

  bool is_comfort_noise_decoder(void* decoderPTR){
    chromemedia::codec::LyraDecoder* decoder = (chromemedia::codec::LyraDecoder*) decoderPTR;
    return decoder->is_comfort_noise();
    // return false;
  }

  int get_sample_rate_hz_decoder(void* decoderPTR){
    chromemedia::codec::LyraDecoder* decoder = (chromemedia::codec::LyraDecoder*) decoderPTR;
    return decoder->sample_rate_hz();
  }

  int get_num_channels_decoder(void* decoderPTR){
    chromemedia::codec::LyraDecoder* decoder = (chromemedia::codec::LyraDecoder*) decoderPTR;
    return decoder->num_channels();
  }

  int get_frame_rate_decoder(void* decoderPTR){
    chromemedia::codec::LyraDecoder* decoder = (chromemedia::codec::LyraDecoder*) decoderPTR;
    return decoder->frame_rate();
  }

  // Sets the encoded packet.
  bool set_encoded_packet(void* decoderPTR, const uint8_t* data, size_t size) {
      chromemedia::codec::LyraDecoder* decoder = (chromemedia::codec::LyraDecoder*) decoderPTR;
      absl::Span<const uint8_t> span(data, size);
      return decoder->SetEncodedPacket(span);
  }

  // Decodes samples.
  int decode_samples(void* decoderPTR, int num_samples, int16_t** out_samples, size_t* out_size) {
      chromemedia::codec::LyraDecoder* decoder = (chromemedia::codec::LyraDecoder*) decoderPTR;
      auto decoded_samples = decoder->DecodeSamples(num_samples);
      if (decoded_samples) {
          *out_size = decoded_samples->size();
          *out_samples = new int16_t[*out_size];
          std::copy(decoded_samples->begin(), decoded_samples->end(), *out_samples);
          return 1; // Success
      } else {
          *out_samples = nullptr; // In case of failure, set output to null.
          *out_size = 0;
          return 0; // Failure
      }
  }

}
}}  // namespace chromemedia::codec
