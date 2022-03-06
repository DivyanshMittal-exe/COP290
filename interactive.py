import os
import tensorflow as tf
import numpy as np
from tensorflow.python.ops import gen_audio_ops as audio_ops
import pyaudio
import wave
import subprocess

def record_audio( WAVE_OUTPUT_FILENAME = "interactive_audio.wav"):
    CHUNK = 1024
    FORMAT = pyaudio.paInt16
    CHANNELS = 2
    RATE = 44100
    RECORD_SECONDS = 1
   
    p = pyaudio.PyAudio()


    stream = p.open(format=FORMAT,
                    channels=CHANNELS,
                    rate=RATE,
                    input=True,
                    frames_per_buffer=CHUNK)

    print("* recording")

    frames = []

    for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
        data = stream.read(CHUNK)
        frames.append(data)

    print("* done recording")

    stream.stop_stream()
    stream.close()
    p.terminate()

    wf = wave.open(WAVE_OUTPUT_FILENAME, 'wb')
    wf.setnchannels(CHANNELS)
    wf.setsampwidth(p.get_sample_size(FORMAT))
    wf.setframerate(RATE)
    wf.writeframes(b''.join(frames))
    wf.close()
    return WAVE_OUTPUT_FILENAME

def load_wav_file(wav_filename, desired_samples):
    wav_file = tf.io.read_file(wav_filename)
    decoded_wav = audio_ops.decode_wav(wav_file, desired_channels=1, desired_samples=desired_samples)
    return decoded_wav.audio, decoded_wav.sample_rate


def calculate_mfcc(audio_signal, audio_sample_rate, window_size, window_stride, num_mfcc):
    spectrogram = audio_ops.audio_spectrogram(input=audio_signal, window_size=window_size, stride=window_stride,
                                              magnitude_squared=True)

    mfcc_features = audio_ops.mfcc(spectrogram, audio_sample_rate, dct_coefficient_count=num_mfcc)    
    return mfcc_features


def makeInteractive():
        audio, sample_rate =load_wav_file(record_audio(),16000)
        mfccs = calculate_mfcc(audio, sample_rate, 640,640,10)
        mfccs = tf.reshape(mfccs, [1,250])
        with tf.Session() as sess:
            print(*mfccs.eval()[0]) 
            f = open("interactive_audio.txt","w")
            f.write(*mfccs.eval()[0])
            f.close()
        
        make_process = subprocess.Popen("make interactive", stderr=subprocess.STDOUT)
        if make_process.wait() != 0:
            print("error")
           
if __name__ == '__main__':
    makeInteractive()