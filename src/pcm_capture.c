// #include "pcm_capture.h"

// #define CHANNEL_COUNT 1

// static int init_pcm_params(snd_pcm_t *pcm_hndl,
//                            snd_pcm_hw_params_t *pcm_params,
//                            snd_pcm_uframes_t pcm_frames);

// static int read_pcm_frames(snd_pcm_t *pcm_hndl,
//                            snd_pcm_uframes_t pcm_frames);

// /* static functions declarations */
// static int init_pcm_params(snd_pcm_t *pcm_hndl,
//                            snd_pcm_hw_params_t *pcm_params,
//                            snd_pcm_uframes_t pcm_frames)
// {
//     int rc;
//     int dir;
//     unsigned int sampling_rate = SAMPLING_RATE;

//     /* in case of problem with hardware use this one "$ arecord -l" */

//     // TODO configurable pcm source
//     //      use "$ arecord -l" for device id
//     rc = snd_pcm_open(&pcm_hndl, "default", SND_PCM_STREAM_CAPTURE, 0);
//     if (rc < 0) {
//         fprintf(stderr, "Unable to open pcm device: %s\n", snd_strerror(rc));
//         exit(1);
//     }

//     snd_pcm_hw_params_alloca(&pcm_params);
//     snd_pcm_hw_params_any(pcm_hndl, pcm_params);
//     snd_pcm_hw_params_set_access(pcm_hndl, pcm_params, SND_PCM_ACCESS_RW_INTERLEAVED);
//     snd_pcm_hw_params_set_format(pcm_hndl, pcm_params, SND_PCM_FORMAT_S16_LE);
//     snd_pcm_hw_params_set_channels(pcm_hndl, pcm_params, CHANNEL_COUNT);

//     snd_pcm_hw_params_set_rate_near(pcm_hndl, pcm_params, &sampling_rate, &dir);
//     if (SAMPLING_RATE != sampling_rate) {
//         fprintf(stderr, "The rate %d Hz is not supported, using %d Hz instead\n", SAMPLING_RATE, sampling_rate);
//     }

//     snd_pcm_hw_params_set_period_size_near(pcm_hndl, pcm_params, &pcm_frames, &dir);
//     rc = snd_pcm_hw_params(pcm_hndl, pcm_params);
//     if (rc < 0) {
//         fprintf(stderr, "unable to set hw parameters: %s \n", snd_strerror(rc));
//         exit(1);
//     }
//     return 0;
// }

// int static read_pcm_frames(snd_pcm_t *pcm_hndl,
//                            snd_pcm_uframes_t pcm_frames)
// {
//     int rc;

//     pthread_mutex_lock(&signal_buffer_lock);
//     rc = snd_pcm_readi(pcm_hndl, real_buffer, pcm_frames);
//     pthread_mutex_unlock(&signal_buffer_lock);
//     if (rc == -EPIPE) {
//         fprintf(stderr, "[PCM Read] Overrun\n");
//         snd_pcm_prepare(pcm_hndl);
//         return FAILURE;
//     }
//     else if (rc < 0) {
//         fprintf(stderr, "[PCM Read] Error while reading: %s\n", snd_strerror(rc));
//         return FAILURE;
//     }
//     return SUCCESS;
// }

// void* pcm_sampling_thrd()
// {
//     int status;

//     snd_pcm_t *pcm_hndl;
//     snd_pcm_hw_params_t *pcm_params;
//     snd_pcm_uframes_t pcm_frames = FFT_POINTS;

//     init_pcm_params(pcm_hndl, pcm_params, pcm_frames);
//     real_buffer = (short *) malloc((int)pcm_frames * 2);    // frames * short size

//     while (1) {
//         // todo: deadlock if read fail
//         printf("loop\n");
//         sem_wait(&sx_vadLock2);
//         status = read_pcm_frames(pcm_hndl, pcm_frames);
//         if (status == SUCCESS) {
//             sem_post(&sx_vadLock1);
//         }
//         else {
//             // skip
//         }
//     }
// }
