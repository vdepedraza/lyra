// c_dec_wrapper.h
#ifndef C_DEC_WRAPPER_H
#define C_DEC_WRAPPER_H

#include <stdbool.h>  // For the bool type
#include <stdint.h>   // For uint8_t and int16_t


#ifdef __cplusplus
extern "C" {
#endif

    // Function to create a new LyraDecoder instance
// Parameters:
// - sample_rate_hz: Sample rate in Hz
// - num_channels: Number of audio channels
// - model_path: Path to the model file
// Returns:
// - A void pointer to the newly created decoder instance, or nullptr if creation failed
void* CreateDecoder(int sample_rate_hz, int num_channels, const char* model_path);

// Function to delete a LyraDecoder instance
// Parameters:
// - decoder_ptr: A void pointer to the decoder instance
// Returns:
// - 0 on success, or -1 if the decoder_ptr is null
int DeleteDecoder(void* decoder_ptr);

// Function to check if comfort noise is enabled
// Parameters:
// - decoderPTR: A void pointer to the decoder instance
// Returns:
// - True if comfort noise is enabled, false otherwise
bool is_comfort_noise_decoder(void* decoderPTR);

// Function to get the sample rate of the decoder
// Parameters:
// - decoderPTR: A void pointer to the decoder instance
// Returns:
// - The sample rate in Hz, or -1 on error
int get_sample_rate_hz_decoder(void* decoderPTR);

// Function to get the number of channels in the decoder
// Parameters:
// - decoderPTR: A void pointer to the decoder instance
// Returns:
// - The number of audio channels, or -1 on error
int get_num_channels_decoder(void* decoderPTR);

// Function to get the frame rate of the decoder
// Parameters:
// - decoderPTR: A void pointer to the decoder instance
// Returns:
// - The frame rate in Hz, or -1 on error
int get_frame_rate_decoder(void* decoderPTR);

// Function to set the encoded packet data in the decoder
// Parameters:  
// - decoderPTR: A void pointer to the decoder instance
// - data: A pointer to the encoded packet data
// - size: The size of the encoded packet data
// Returns:
// - True if the packet was successfully set, false otherwise
bool set_encoded_packet(void* decoderPTR, const uint8_t* data, size_t size);

// Function to decode audio samples from the decoder
// Parameters:
// - decoderPTR: A void pointer to the decoder instance
// - num_samples: The number of samples to decode
// - out_samples: A pointer to the output samples buffer
// - out_size: A pointer to the size of the output samples buffer
// Returns:
// - The number of samples decoded, or -1 on error
int decode_samples(void* decoderPTR, int num_samples, int16_t** out_samples, size_t* out_size);

#ifdef __cplusplus
}
#endif

#endif // C_DEC_WRAPPER_H
