////////////////////////////////////////
// "../../tcc/tcc" -run -I../include -I../include/winapi -I../include/libxml2 -L. -lavcodec-61 -lavformat-61 -lavutil-59 -lswresample-5 -lswscale-8 -lcurl-x64 -lxml2-2 -lportaudio -lglfw3 -lwinpthread-1 main.c
//
// Get-AppxPackage -AllUsers | where-object {$_.name -notlike "*store*"} | Remove-AppxPackage # Remove all except Store
// Computer\HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon -> "Shell" (string type) -> "explorer.exe","YOUR_APP_PATH.exe" (value)
////////////////////////////////////////
#if 1 // Print text

#ifndef ENGINE_PRINT_TEXT
#define ENGINE_PRINT_TEXT

#define PRINT_TEXT_CLEAR "\033[H\033[J"
#define PRINT_TEXT_COLOR_RED "\x1B[31m"
#define PRINT_TEXT_COLOR_GREEN "\x1B[32m"
#define PRINT_TEXT_COLOR_YELOW "\x1B[33m"
#define PRINT_TEXT_COLOR_BLUE "\x1B[34m"
#define PRINT_TEXT_COLOR_MAGENTA "\x1B[35m"
#define PRINT_TEXT_COLOR_CYAN "\x1B[36m"
#define PRINT_TEXT_COLOR_WHITE "\x1B[37m"

#define PRINT_TEXT(text) printf(PRINT_TEXT_COLOR_WHITE "%s:" PRINT_TEXT_COLOR_MAGENTA "%i" PRINT_TEXT_COLOR_WHITE ": in '" PRINT_TEXT_COLOR_BLUE "%s" PRINT_TEXT_COLOR_WHITE "' function: " PRINT_TEXT_COLOR_RED "%s" PRINT_TEXT_COLOR_WHITE "\n", __FILE__, __LINE__, __FUNCTION__, text)

#endif // ENGINE_PRINT_TEXT

#endif // Print text

////////////////////////////////////////
// Wrappers
////////////////////////////////////////
#if 1 // Glad

#ifndef ENGINE_OPENGL_WRAPPER
#define ENGINE_OPENGL_WRAPPER

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

GLuint ogl_texture_create(GLsizei width, GLsizei height, GLenum format, const void* pixels) {
    GLuint texture;

    glGenTextures(1, &texture);

    if (texture != 0) {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    return texture;
}

GLuint ogl_shader_create(GLenum type, const GLchar* const* string) {
    GLuint shader;

    if ((shader = glCreateShader(type)) != 0) {
        glShaderSource(shader, 1, string, NULL);
        glCompileShader(shader);
    }

    return shader;
}

GLuint ogl_program_create(GLuint* shaders, GLuint count) {
    GLuint program;

    if ((program = glCreateProgram()) != 0) {
        for (GLuint i = 0; i < count; ++i) {
            glAttachShader(program, shaders[i]);
        }

        glLinkProgram(program);
    }

    return program;
}

GLuint ogl_buffer_create(GLenum target, GLsizeiptr buffer_size, const void* buffer_data) {
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
    glBindBuffer(target, 0);

    return buffer;
}

void ogl_buffer_attribute(GLenum target, GLuint buffer, GLuint index, GLint size) {
    glBindBuffer(target, buffer);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(target, 0);
}

void ogl_debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param) {
    const char* source_string;

    switch (source) {
        case GL_DEBUG_SOURCE_API: source_string = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: source_string = "WINDOW SYSTEM"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: source_string = "SHADER COMPILER"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY: source_string = "THIRD PARTY"; break;
        case GL_DEBUG_SOURCE_APPLICATION: source_string = "APPLICATION"; break;
        case GL_DEBUG_SOURCE_OTHER: source_string = "OTHER"; break;
        default: source_string = "UNKNOWN"; break;
    }

    const char* type_string;

    switch (type) {
        case GL_DEBUG_TYPE_ERROR: type_string = "ERROR"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_string = "DEPRECATED BEHAVIOR"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: type_string = "UDEFINED BEHAVIOR"; break;
        case GL_DEBUG_TYPE_PORTABILITY: type_string = "PORTABILITY"; break;
        case GL_DEBUG_TYPE_PERFORMANCE: type_string = "PERFORMANCE"; break;
        case GL_DEBUG_TYPE_OTHER: type_string = "OTHER"; break;
        case GL_DEBUG_TYPE_MARKER: type_string = "MARKER"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP: type_string = "PUSH GROUP"; break;
        case GL_DEBUG_TYPE_POP_GROUP: type_string = "POP GROUP"; break;
        default: type_string = "UNKNOWN"; break;
    }

    const char* severity_string;

    switch (severity) {
        case GL_DEBUG_SEVERITY_NOTIFICATION: severity_string = "NOTIFICATION"; break;
        case GL_DEBUG_SEVERITY_HIGH: severity_string = "HIGH"; break;
        case GL_DEBUG_SEVERITY_MEDIUM: severity_string = "MEDIUM"; break;
        case GL_DEBUG_SEVERITY_LOW: severity_string = "LOW"; break;
        default: severity_string = "UNKNOWN"; break;
    }

    PRINT_TEXT(message);
}

#endif // ENGINE_OPENGL_WRAPPER

#endif // Glad

#if 1 // cglm

#ifndef ENGINE_CGLM_WRAPPER
#define ENGINE_CGLM_WRAPPER

#include <cglm/cglm.h>

void cglm_view_rotate(mat4 view, float value, vec3 axis) {
    mat4 rotation_matrix;

    glm_mat4_copy(view, rotation_matrix);
    glm_rotate_make(view, value, axis);
    glm_mul(view, rotation_matrix, view);
}

void cglm_view_move_up(mat4 view, float value) {
    float yaw = -90.0f;
    float pitch = 1.0f;
    vec3 front = {
        cosf(glm_rad(yaw)) * cosf(glm_rad(pitch)),
        sinf(glm_rad(pitch)),
        sinf(glm_rad(yaw)) * cosf(glm_rad(pitch))
    };

    glm_vec3_normalize(front);

    view[3][0] += glm_rad(front[1]) * value;
    view[3][1] += glm_rad(front[2]) * value;
    view[3][2] += glm_rad(front[0]) * value;
}

void cglm_view_move(vec3 axis, mat4 view, float value) {
    float yaw = -90.0f;
    float pitch = 1.0f;
    vec3 front = {
        cosf(glm_rad(yaw)) * cosf(glm_rad(pitch)),
        sinf(glm_rad(pitch)),
        sinf(glm_rad(yaw)) * cosf(glm_rad(pitch))
    };

    glm_vec3_normalize(front);
    glm_vec3_cross(front, axis, front);
    glm_vec3_normalize(front);

    view[3][0] += glm_rad(front[1]) * value;
    view[3][1] += glm_rad(front[2]) * value;
    view[3][2] += glm_rad(front[0]) * value;
}

bool cglm_frustum_culling(mat4 matrix, vec3 box[2]) {
    vec4 planes[6];

    glm_frustum_planes(matrix, planes);
    return glm_aabb_frustum(box, planes);
}

/*
bool cglm_frustum_culling2(mat4 projection, mat4 view, mat4 model) {
    mat4 m;
    vec4 corners[8];
    vec3 box[2];
    vec4 planes[6];

    glm_mat4_identity(m);
    glm_frustum_corners(m, corners);
    glm_frustum_box(corners, model, box);
    glm_mat4_mul(projection, view, m);
    glm_frustum_planes(m, planes);

    return glm_aabb_frustum(box, planes);
}
*/

#endif // ENGINE_CGLM_WRAPPER

#endif // cglm

#if 1 // FFmpeg

#ifndef ENGINE_FFMPEG_WRAPPER
#define ENGINE_FFMPEG_WRAPPER

#include <libavformat/avformat.h>

int ffmpeg_format_context_alloc(AVFormatContext** out_format_context, const char* url, enum AVMediaType media_type, int* out_stream_index) {
    int result;

    if ((result = avformat_open_input(out_format_context, url, NULL, NULL)) == 0) {
        if ((result = avformat_find_stream_info(out_format_context[0], NULL)) >= 0) {
            if ((result = av_find_best_stream(out_format_context[0], media_type, -1, -1, NULL, 0)) >= 0) {
                out_stream_index[0] = result;
                return 0;
            }
        }

        avformat_close_input(out_format_context);
    }

    return result;
}

#include <libavcodec/avcodec.h>

int ffmpeg_codec_context_alloc(AVCodecContext** out_codec_context, const AVCodecParameters* codec_parameters, AVDictionary* options) {
    int result;

    if ((out_codec_context[0] = avcodec_alloc_context3(NULL)) != NULL) {
        if ((result = avcodec_parameters_to_context(out_codec_context[0], codec_parameters)) >= 0) {
            if ((result = avcodec_open2(out_codec_context[0], avcodec_find_decoder(out_codec_context[0]->codec_id), &options)) == 0) {
                return result;
            }
        }

        avcodec_free_context(out_codec_context);
    }
    else {
        result = AVERROR(ENOMEM);
    }

    return result;
}

#include <libswscale/swscale.h>

int ffmpeg_video_context_alloc(struct SwsContext** out_sws_context, AVCodecContext* codec_context, enum AVPixelFormat pixel_format) {
    return (out_sws_context[0] = sws_getCachedContext(out_sws_context[0], codec_context->width, codec_context->height, codec_context->pix_fmt, codec_context->width, codec_context->height, pixel_format, 0, NULL, NULL, NULL)) != NULL ? 0 : AVERROR(ENOMEM);
}

#include <libswresample/swresample.h>

int ffmpeg_audio_context_alloc(struct SwrContext** out_swr_context, AVCodecContext* codec_context, enum AVSampleFormat sample_format) {
    int result;

    // if (channels > 0) {
    //     av_channel_layout_default(&codec_context->ch_layout, channels);
    // }

    if ((result = swr_alloc_set_opts2(out_swr_context, &codec_context->ch_layout, sample_format, codec_context->sample_rate, &codec_context->ch_layout, codec_context->sample_fmt, codec_context->sample_rate, 0, NULL)) == 0) {
        if ((result = swr_init(out_swr_context[0])) == 0) {
            return result;
        }

        swr_free(out_swr_context);
    }

    return result;
}


int ffmpeg_from_memory_alloc(AVFormatContext** out_format_context, void* data, size_t size, enum AVMediaType media_type, int* out_stream_index, AVCodecContext** out_codec_context, AVDictionary* options) {
    unsigned char* buffer;
    int result;

    if ((buffer = av_malloc(size)) != NULL) {
        if ((out_format_context[0] = avformat_alloc_context()) != NULL) {
            out_format_context[0]->flags = AVFMT_FLAG_CUSTOM_IO;

            if (memcpy(buffer, data, size) != NULL) {
                if ((out_format_context[0]->pb = avio_alloc_context(buffer, size, 0, data, NULL, NULL, NULL)) != NULL) {
                    if ((result = ffmpeg_format_context_alloc(out_format_context, NULL, media_type, out_stream_index)) == 0) {
                        if ((result = ffmpeg_codec_context_alloc(out_codec_context, out_format_context[0]->streams[out_stream_index[0]]->codecpar, options)) == 0) {
                            return result;
                        }
                    }
                }
                else {
                    result = AVERROR(ENOMEM);
                }
            }
            else {
                result = AVERROR(ENOMEM);
            }

            avformat_close_input(out_format_context);
        }
        else {
            result = AVERROR(ENOMEM);
        }

        av_freep(&buffer);
    }
    else {
        result = AVERROR(ENOMEM);
    }

    return result;
}


int ffmpeg_get_next_frame(AVFormatContext* format_context, AVPacket* packet, int stream_index, AVCodecContext* codec_context, AVFrame* frame) {
    int result;

    while ((result = av_read_frame(format_context, packet)) == 0) {
        if (packet->stream_index == stream_index) {
            if ((result = avcodec_send_packet(codec_context, packet)) == 0) {
                result = avcodec_receive_frame(codec_context, frame);

                if (result != AVERROR(EAGAIN) && result != AVERROR_EOF) {
                    av_packet_unref(packet);
                    return result;
                }
            }
        }

        av_packet_unref(packet);
    }

    return result;
}

int ffmpeg_seek(const int* run, AVFormatContext* format_context, double seconds, AVPacket* packet, int stream_index, AVCodecContext* codec_context, AVFrame* frame) {
    int result;

    if ((result = avformat_seek_file(format_context, -1, INT64_MIN, AV_TIME_BASE * seconds, INT64_MAX, 0)) >= 0) {
        if (av_q2d(format_context->streams[stream_index]->time_base) * frame->pts < seconds) {
            while (*run == 1 && result == 0 && av_q2d(format_context->streams[stream_index]->time_base) * frame->pts < seconds) {
                result = ffmpeg_get_next_frame(format_context, packet, stream_index, codec_context, frame);
            }
        }
        else if (av_q2d(format_context->streams[stream_index]->time_base) * frame->pts > seconds) {
            while (*run == 1 && result == 0 && av_q2d(format_context->streams[stream_index]->time_base) * frame->pts > seconds) {
                result = ffmpeg_get_next_frame(format_context, packet, stream_index, codec_context, frame);
            }
            while (*run == 1 && result == 0 && av_q2d(format_context->streams[stream_index]->time_base) * frame->pts < seconds) {
                result = ffmpeg_get_next_frame(format_context, packet, stream_index, codec_context, frame);
            }
        }
    }

    return result;
}

#endif // ENGINE_FFMPEG_WRAPPER

#endif // FFmpeg

#if 1 // PortAudio

#ifndef ENGINE_PORTAUDIO_WRAPPER
#define ENGINE_PORTAUDIO_WRAPPER

#include <portaudio.h>

int pa_stream_callback(const void* input, void* output, unsigned long frame_count, const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags status_flags, void* user_data);

PaError pa_audio_start(int channels, PaSampleFormat sample_format, double sample_rate, unsigned long frames_per_buffer, void* user_data) {
    PaError error;

    if ((error = Pa_Initialize()) == paNoError) {
        PaStream* stream;

        if ((error = Pa_OpenDefaultStream(&stream, 0, channels, sample_format, sample_rate, frames_per_buffer, pa_stream_callback, user_data)) == paNoError) {
            if ((error = Pa_StartStream(stream)) == paNoError) {
                while ((error = Pa_IsStreamActive(stream)) == 1) {
                    Pa_Sleep(10);
                }

                if ((error = Pa_StopStream(stream)) != paNoError) {
                    PRINT_TEXT(Pa_GetErrorText(error));
                }
            }

            if ((error = Pa_CloseStream(stream)) != paNoError) {
                PRINT_TEXT(Pa_GetErrorText(error));
            }
        }
        else {
            PRINT_TEXT(Pa_GetErrorText(error));
        }

        if ((error = Pa_Terminate()) != paNoError) {
            PRINT_TEXT(Pa_GetErrorText(error));
        }
    }

    return error;
}

#endif // ENGINE_PORTAUDIO_WRAPPER

#endif // PortAudio

#if 1 // cURL

#ifndef ENGINE_CURL_WRAPPER
#define ENGINE_CURL_WRAPPER

#define __MINGW32__ // tcc: include/curl/system.h:464: error: ';' expected (got "curl_socklen_t")
#include <curl/curl.h>
#undef __MINGW32__

size_t curl_write_function_callback(void* data, size_t size, size_t nmemb, void** out_data) {
    void* reallocated_data;
    size_t data_size;

    data_size = out_data[0] ? *(size_t*)out_data[0] : 0;

    if ((reallocated_data = realloc(out_data[0], size * nmemb + sizeof(size_t) + data_size)) != NULL) {
        out_data[0] = reallocated_data;
        memcpy(out_data[0] + sizeof(size_t) + data_size, data, size * nmemb);
        *(size_t*)out_data[0] = size * nmemb + data_size;
    }
    else {
        PRINT_TEXT(strerror(errno));
    }

    return size * nmemb;
}

// First "sizeof(size_t)" (supposed 8 bytes) in "out_data" - data size.
CURLcode curl_get_url_data(const char* url, void** out_data, long timeout_ms) {
    CURLcode curl_code;

    if ((curl_code = curl_global_init(CURL_GLOBAL_ALL)) == CURLE_OK) {
        CURL* curl;

        if ((curl = curl_easy_init()) != NULL) {
            out_data[0] = NULL;

            if (
                (curl_code = curl_easy_setopt(curl, CURLOPT_URL, url)) == CURLE_OK &&
                (curl_code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_function_callback)) == CURLE_OK &&
                (curl_code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, out_data)) == CURLE_OK &&
                (curl_code = curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, timeout_ms)) == CURLE_OK &&
                (curl_code = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0)) == CURLE_OK &&
                (curl_code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1)) == CURLE_OK &&
                (curl_code = curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/117.0")) == CURLE_OK
            ) {
                curl_code = curl_easy_perform(curl);
            }

            curl_easy_cleanup(curl);
        }
        else {
            curl_code = CURLE_FAILED_INIT;
        }

        curl_global_cleanup();
    }

    return curl_code;
}

#endif // ENGINE_CURL_WRAPPER

#endif // cURL

#if 1 // libxml2

#ifndef ENGINE_LIBXML2_WRAPPER
#define ENGINE_LIBXML2_WRAPPER

// Do not forget about libxml2-2.dll libiconv-2.dll liblzma-5.dll zlib1.dll
#include <libxml/HTMLparser.h>

xmlNode* xml_find(xmlNode* node, const xmlChar* node_name, const xmlChar* prop_name, const xmlChar* prop_value, const xmlChar* content) {
    while (node != NULL) {
        if (node->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(node->name, node_name) == 0) {
                xmlChar* prop_data;
                int is_it;

                prop_data = NULL;
                is_it = 1;

                if (prop_name != NULL) {
                    if ((prop_data = xmlGetProp(node, prop_name)) == NULL) { // Do not forget to free up memory after xmlGetProp.
                        is_it = 0;
                    }
                }

                if (prop_value != NULL) {
                    if (prop_data != NULL) {
                        if (xmlStrcmp(prop_data, prop_value) != 0) {
                            is_it = 0;
                        }
                    }
                }

                if (prop_data != NULL) {
                    xmlFree(prop_data);
                }

                if (content != NULL) {
                    xmlChar* node_content;

                    is_it = 0;

                    if ((node_content = xmlNodeGetContent(node)) != NULL) { // Do not forget to free up memory after xmlNodeGetContent.
                        if (xmlStrstr(node_content, content) != NULL) {
                            is_it = 1;
                        }

                        xmlFree(node_content);
                    }
                }

                if (is_it == 1) {
                    return node;
                }
            }
        }

        xmlNode* result;

        if ((result = xml_find(node->children, node_name, prop_name, prop_value, content)) != NULL) {
            return result;
        }

        node = node->next;
    }

    return NULL;
}

#endif // ENGINE_LIBXML2_WRAPPER

#endif // libxml2

#if 1 // cgltf

#define CGLTF_IMPLEMENTATION
#include <cgltf/cgltf.h>

// accessor - cgltf_accessor pointer.
// num_comp - 1/2/3/4 or 4/9/16, just use graphics_cgltf_type_to_count().
#define GRAPHICS_CGLTF_ACCESSOR_PARSE(accessor, num_comp, data_type, dst_ptr) { \
    cgltf_size _stride_ = 0; \
    data_type* _buffer_ = (data_type*)accessor->buffer_view->buffer->data + accessor->buffer_view->offset / sizeof(data_type) + accessor->offset / sizeof(data_type); \
    for (cgltf_size _i_ = 0; _i_ < accessor->count; ++_i_) { \
        for (cgltf_size _j_ = 0; _j_ < num_comp; ++_j_) { \
            (dst_ptr)[num_comp * _i_ + _j_] = _buffer_[_stride_ + _j_]; \
        } \
        _stride_ += (cgltf_size)(accessor->stride / sizeof(data_type)); \
    } \
}

cgltf_size graphics_cgltf_type_to_count(cgltf_type type) {
    return
        type == cgltf_type_invalid ? 0 :
        type == cgltf_type_scalar ? 1 :
        type == cgltf_type_vec2 ? 2 :
        type == cgltf_type_vec3 ? 3 :
        type == cgltf_type_vec4 ? 4 :
        type == cgltf_type_mat2 ? 4 : // 2 * 2
        type == cgltf_type_mat3 ? 9 : // 3 * 3
        type == cgltf_type_mat4 ? 16 : // 4 * 4
        0;
}

void* graphics_cgltf_alloc_and_parse_accessor_data(const cgltf_accessor* accessor) {
    void* result;

    if ((result = malloc(accessor->buffer_view->size)) != NULL) {
        if (accessor->component_type == cgltf_component_type_r_8) {
            GRAPHICS_CGLTF_ACCESSOR_PARSE(accessor, graphics_cgltf_type_to_count(accessor->type), int8_t, (int8_t*)result);
        }
        else if (accessor->component_type == cgltf_component_type_r_8u) {
            GRAPHICS_CGLTF_ACCESSOR_PARSE(accessor, graphics_cgltf_type_to_count(accessor->type), uint8_t, (uint8_t*)result);
        }
        else if (accessor->component_type == cgltf_component_type_r_16) {
            GRAPHICS_CGLTF_ACCESSOR_PARSE(accessor, graphics_cgltf_type_to_count(accessor->type), int16_t, (int16_t*)result);
        }
        else if (accessor->component_type == cgltf_component_type_r_16u) {
            GRAPHICS_CGLTF_ACCESSOR_PARSE(accessor, graphics_cgltf_type_to_count(accessor->type), uint16_t, (uint16_t*)result);
        }
        else if (accessor->component_type == cgltf_component_type_r_32u) {
            GRAPHICS_CGLTF_ACCESSOR_PARSE(accessor, graphics_cgltf_type_to_count(accessor->type), uint32_t, (uint32_t*)result);
        }
        else if (accessor->component_type == cgltf_component_type_r_32f) {
            GRAPHICS_CGLTF_ACCESSOR_PARSE(accessor, graphics_cgltf_type_to_count(accessor->type), float, (float*)result);
        }
    }

    return result;
}

#endif // cgltf

////////////////////////////////////////
// Sandbox
////////////////////////////////////////
#include <libavutil/imgutils.h>
#include <libavutil/random_seed.h>
#include <libavutil/time.h>

#if 1

htmlDocPtr xml_get_url_data(const char* url, long timeout_ms) {
    void* url_data;
    CURLcode curl_code;

    if ((curl_code = curl_get_url_data(url, &url_data, timeout_ms)) != CURLE_OK) {
        PRINT_TEXT(curl_easy_strerror(curl_code));
        return NULL;
    }

    htmlDocPtr document;
    document = htmlReadMemory(url_data + sizeof(size_t), *(size_t*)url_data, NULL, NULL, HTML_PARSE_NOERROR);
    free(url_data);

    return document;
}


void rule34_xxx_get_base_url_and_pid(char** out_url_to_list, int* out_pid_count) {
    htmlDocPtr document;
    xmlNode* node;
    xmlChar* buffer;
    char* pid_string;

    char url[2048] = "https://rule34.xxx//index.php?page=post&s=list&tags=";

    const char* must_have[] = {
        "sound"
    };

    const char* can_have[] = {
        "rape*"          ,
        "rough*"         ,
        "broken*"        ,
        "torture*"       ,
        "hardc*"         ,

        "secretly*"      ,

        "trap*"          ,
        "futa*"          ,
        "sissy*"         ,
        "girly*"         ,
        "dickg*"         ,
        "tomg*"          ,
        "femb*"          ,
        "shemale"        ,
        "intersex*"      ,
        "newhalf*"       ,
        "femi*"          ,
        "otoko*"         ,
        "transg*"        ,

        "rule_63"        ,

        "camel_toe"      ,
        "cameltoe*"      ,
        "cleft_of_venus" ,
        "mound_of_venus" ,
        "plump_labia"    ,
        "plump_vulva"    ,
        "plump_pussy"    ,
        "plump_camel_toe",
        "fat_mons"       ,
        "fat_pussy"      ,
        "huge_pussy"     ,
        "big_pussy"      ,
        "puffy_pussy"    ,
        "puffy_v*"       ,

        "auto*"          ,
        "self*"          , "-self_upload",

        "ahe*"           ,
        "gap*"           ,
        "moan*"          ,
        "dildo*"         ,
        "incest*"        ,
        "cry*"           ,
        "drug*"          ,
    };

    for (size_t i = 0; i < sizeof(must_have) / sizeof(must_have[0]); ++i) {
        if (i > 0 && i < sizeof(must_have) / sizeof(must_have[0])) {
            strcat(url, "+");
        }

        strcat(url, must_have[i]);
    }

    if (sizeof(can_have) / sizeof(can_have[0]) > 0) {
        strcat(url, "+(+");

        for (size_t i = 0; i < sizeof(can_have) / sizeof(can_have[0]); ++i) {
            if (i > 0 && i < sizeof(can_have) / sizeof(can_have[0])) {
                strcat(url, "+~+");
            }

            strcat(url, can_have[i]);
        }

        strcat(url, "+)");
    }

    if ((out_url_to_list[0] = strdup(url)) == NULL) {
        PRINT_TEXT(strerror(errno));
    }

    if ((document = xml_get_url_data(url, 20000)) != NULL) {
        if ((node = xml_find(xmlDocGetRootElement(document), "a", "alt", "last page", NULL)) != NULL) {
            if ((buffer = xmlGetProp(node, "href")) != NULL) { // Do not forget to free up memory after xmlGetProp.
                if ((pid_string = strrchr(buffer, '=')) != NULL) {
                    ++pid_string;
                    out_pid_count[0] = atoi(pid_string);

                    snprintf(url + strlen(url), sizeof(url) - strlen(url), "%s%i", "&pid=", atoi(pid_string));

                    xmlFreeDoc(document);

                    if ((document = xml_get_url_data(url, 20000)) != NULL) {
                        if ((node = xml_find(xmlDocGetRootElement(document), "div", "class", "image-list", NULL)) != NULL) {
                            out_pid_count[0] += xmlChildElementCount(node);
                        }
                    }
                }

                xmlFree(buffer);
            }
        }
        else {
            if ((node = xml_find(xmlDocGetRootElement(document), "div", "class", "image-list", NULL)) != NULL) {
                out_pid_count[0] = xmlChildElementCount(node);
            }
        }

        if (document != NULL) {
            xmlFreeDoc(document);
        }
    }
}

void rule34_xxx_get_source_url(const char* url_to_list, int pid, char** out_url) {
    htmlDocPtr document;
    xmlNode* node;
    xmlChar* buffer;
    char url[2048];

    snprintf(url, sizeof(url), "%s&pid=%i", url_to_list, pid);

    if ((document = xml_get_url_data(url, 20000)) != NULL) {
        if ((node = xml_find(xmlDocGetRootElement(document), "div", "class", "image-list", NULL)) != NULL) {
            if ((node = xml_find(node, "span", "class", "thumb", NULL)) != NULL) {
                if ((node = xml_find(node, "a", "href", NULL, NULL)) != NULL) {
                    if ((buffer = xmlGetProp(node, "href")) != NULL) { // Do not forget to free up memory after xmlGetProp.
                        snprintf(url, sizeof(url), "%s%s", "https://rule34.xxx", buffer);

                        xmlFreeDoc(document);

                        if ((document = xml_get_url_data(url, 20000)) != NULL) {
                            if ((node = xml_find(xmlDocGetRootElement(document), "li", NULL, NULL, "Original image")) != NULL) {
                                if ((node = xml_find(node, "a", "href", NULL, NULL)) != NULL) {
                                    out_url[0] = xmlGetProp(node, "href"); // Do not forget to free up memory after xmlGetProp.
                                }
                            }
                        }

                        xmlFree(buffer);
                    }
                }
            }
        }

        if (document != NULL) {
            xmlFreeDoc(document);
        }
    }

    if (out_url[0] == NULL) {
        if ((document = xml_get_url_data("https://rule34.xxx/index.php?page=post&s=random", 20000)) != NULL) {
            if ((node = xml_find(xmlDocGetRootElement(document), "li", NULL, NULL, "Original image")) != NULL) {
                if ((node = xml_find(node, "a", "href", NULL, NULL)) != NULL) {
                    out_url[0] = xmlGetProp(node, "href"); // Do not forget to free up memory after xmlGetProp.
                }
            }

            xmlFreeDoc(document);
        }
    }

    // "https://nymp4.rule34.xxx//images/5059/1e105ca5ce2b91ff3ca5567086e61cb8.mp4?5766724";
    // "https://ws-cdn-video.rule34.xxx//images/3750/6750dc9929dda34dbbe904adf191366c.mp4?4243094";
}


void realbooru_com_get_base_url_and_pid(char** out_url_to_list, int* out_pid_count) {
    htmlDocPtr document;
    xmlNode* node;
    xmlChar* buffer;
    char* pid_string;
    char url[2048] = "https://realbooru.com//index.php?page=post&s=list&tags=";

    const char* must_have[] = {
        "sound"
    };


    for (size_t i = 0; i < sizeof(must_have) / sizeof(must_have[0]); ++i) {
        if (i > 0 && i < sizeof(must_have) / sizeof(must_have[0])) {
            strcat(url, "+");
        }

        strcat(url, must_have[i]);
    }

    if ((out_url_to_list[0] = strdup(url)) == NULL) {
        PRINT_TEXT(strerror(errno));
    }

    if ((document = xml_get_url_data(url, 20000)) != NULL) {
        if ((node = xml_find(xmlDocGetRootElement(document), "a", "alt", "last page", NULL)) != NULL) {
            if ((buffer = xmlGetProp(node, "href")) != NULL) { // Do not forget to free up memory after xmlGetProp.
                if ((pid_string = strrchr(buffer, '=')) != NULL) {
                    ++pid_string;
                    out_pid_count[0] = atoi(pid_string);

                    snprintf(url + strlen(url), sizeof(url) - strlen(url), "%s%i", "&pid=", atoi(pid_string));

                    xmlFreeDoc(document);

                    if ((document = xml_get_url_data(url, 20000)) != NULL) {
                        if ((node = xml_find(xmlDocGetRootElement(document), "div", "class", "items", NULL)) != NULL) {
                            out_pid_count[0] += xmlChildElementCount(node);
                        }
                    }
                }

                xmlFree(buffer);
            }
        }
        else {
            if ((node = xml_find(xmlDocGetRootElement(document), "div", "class", "items", NULL)) != NULL) {
                out_pid_count[0] = xmlChildElementCount(node);
            }
        }

        if (document != NULL) {
            xmlFreeDoc(document);
        }
    }
}

void realbooru_com_get_source_url(const char* url_to_list, int pid, char** out_url) {
    htmlDocPtr document;
    xmlNode* node;
    xmlChar* buffer;
    char url[2048];

    snprintf(url, sizeof(url), "%s&pid=%i", url_to_list, pid);

    if ((document = xml_get_url_data(url, 20000)) != NULL) {
        if ((node = xml_find(xmlDocGetRootElement(document), "div", "class", "items", NULL)) != NULL) {
            if ((node = xml_find(node, "div", "class", "col thumb", NULL)) != NULL) {
                if ((node = xml_find(node, "a", "href", NULL, NULL)) != NULL) {
                    if ((buffer = xmlGetProp(node, "href")) != NULL) { // Do not forget to free up memory after xmlGetProp.
                        snprintf(url, sizeof(url), "%s", buffer);

                        xmlFreeDoc(document);

                        if ((document = xml_get_url_data(url, 20000)) != NULL) {
                            if ((node = xml_find(xmlDocGetRootElement(document), "video", "id", "gelcomVideoPlayer", NULL)) != NULL) {
                                if ((node = xml_find(node, "source", "src", NULL, NULL)) != NULL) {
                                    out_url[0] = xmlGetProp(node, "src"); // Do not forget to free up memory after xmlGetProp.
                                }
                            }
                            else if ((node = xml_find(xmlDocGetRootElement(document), "div", "class", "imageContainer", NULL)) != NULL) {
                                if ((node = xml_find(node, "img", "id", "image", NULL)) != NULL) {
                                    out_url[0] = xmlGetProp(node, "src"); // Do not forget to free up memory after xmlGetProp.
                                }
                            }
                        }

                        xmlFree(buffer);
                    }
                }
            }
        }

        if (document != NULL) {
            xmlFreeDoc(document);
        }
    }

    if (out_url[0] == NULL) {
        if ((document = xml_get_url_data("https://realbooru.com/index.php?page=post&s=random", 20000)) != NULL) {
            if ((node = xml_find(xmlDocGetRootElement(document), "li", NULL, NULL, "Original image")) != NULL) {
                if ((node = xml_find(node, "a", "href", NULL, NULL)) != NULL) {
                    out_url[0] = xmlGetProp(node, "href"); // Do not forget to free up memory after xmlGetProp.
                }
            }

            xmlFreeDoc(document);
        }
    }
}

#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <pthread.h>

#if 1

typedef struct video_data {
    AVFormatContext* format_context;
    const char* url;
    int stream_index;
    AVCodecContext* codec_context;
    struct SwsContext* sws_context;
    AVPacket* packet;
    AVFrame* frame;
    int result;
    AVDictionary* options;
    uint8_t* pixels[4];
    int pitch[4];
    int run;
    int update_texture;
} video_data_t;

typedef struct audio_data {
    AVFormatContext* format_context;
    const char* url;
    int stream_index;
    AVCodecContext* codec_context;
    struct SwrContext* swr_context;
    AVPacket* packet;
    AVFrame* frame;
    int result;
    AVDictionary* options;
    float gain;
    int run;
} audio_data_t;

void* ffmpeg_video_thread(void* arg) {
    video_data_t* video_data = arg;

    if ((video_data->result = ffmpeg_format_context_alloc(&video_data->format_context, video_data->url, AVMEDIA_TYPE_VIDEO, &video_data->stream_index)) == 0) {
        if ((video_data->result = ffmpeg_codec_context_alloc(&video_data->codec_context, video_data->format_context->streams[video_data->stream_index]->codecpar, video_data->options)) == 0) {
            if ((video_data->result = ffmpeg_video_context_alloc(&video_data->sws_context, video_data->codec_context, AV_PIX_FMT_RGBA)) == 0) {
                if ((video_data->packet = av_packet_alloc()) != NULL) {
                    if ((video_data->frame = av_frame_alloc()) != NULL) {
                        if ((video_data->pixels[0] = av_malloc(av_image_get_buffer_size(AV_PIX_FMT_RGBA, video_data->codec_context->width, video_data->codec_context->height, 1))) != NULL) {
                            video_data->pitch[0] = video_data->codec_context->width * 4;

                            if ((video_data->result = ffmpeg_get_next_frame(video_data->format_context, video_data->packet, video_data->stream_index, video_data->codec_context, video_data->frame)) == 0) {
                                if ((video_data->result = sws_scale(video_data->sws_context, video_data->frame->data, video_data->frame->linesize, 0, video_data->codec_context->height, video_data->pixels, video_data->pitch)) >= 0) {
                                    video_data->result = 0;

                                    int64_t time_start;
                                    int64_t time_now;

                                    time_start = av_gettime_relative();
                                    video_data->run = 1;

                                    while (video_data->run == 1) {
                                        if (video_data->update_texture == 0) {
                                            time_now = av_gettime_relative();

                                            if (video_data->result == AVERROR_EOF) {
                                                video_data->result = ffmpeg_seek(&video_data->run, video_data->format_context, 0.0, video_data->packet, video_data->stream_index, video_data->codec_context, video_data->frame);
                                                time_start = av_gettime_relative();
                                            }

                                            int count = 0;

                                            while (video_data->result == 0 && av_q2d(video_data->format_context->streams[video_data->stream_index]->time_base) * video_data->frame->pts < ((double)(time_now - time_start) / AV_TIME_BASE) && ++count < 10) {
                                                video_data->result = ffmpeg_get_next_frame(video_data->format_context, video_data->packet, video_data->stream_index, video_data->codec_context, video_data->frame);
                                            }

                                            if (video_data->result == 0 && (video_data->result = sws_scale(video_data->sws_context, video_data->frame->data, video_data->frame->linesize, 0, video_data->codec_context->height, video_data->pixels, video_data->pitch)) >= 0) {
                                                video_data->result = 0;
                                                video_data->update_texture = 1;
                                            }
                                        }

                                        av_usleep(10000);
                                    }
                                }
                            }
                        }
                        else {
                            video_data->result = AVERROR(ENOMEM);
                        }
                    }
                    else {
                        video_data->result = AVERROR(ENOMEM);
                    }
                }
                else {
                    video_data->result = AVERROR(ENOMEM);
                }
            }
        }
    }

    if (video_data->result != 0) {
        PRINT_TEXT(av_err2str(video_data->result));
    }

    return NULL;
}

int pa_stream_callback(const void* input, void* output, unsigned long frame_count, const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags status_flags, void* user_data) {
    audio_data_t* audio_data = user_data;

    if ((audio_data->result = ffmpeg_get_next_frame(audio_data->format_context, audio_data->packet, audio_data->stream_index, audio_data->codec_context, audio_data->frame)) == 0) {
        if ((audio_data->result = swr_convert(audio_data->swr_context, &output, audio_data->frame->nb_samples, audio_data->frame->data, audio_data->frame->nb_samples)) >= 0) {
            for (size_t i = 0; i < audio_data->codec_context->frame_size * audio_data->codec_context->ch_layout.nb_channels; ++i) {
                ((int16_t*)output)[i] *= audio_data->gain;
            }

            audio_data->result = 0;
        }
    }

    if (audio_data->result == AVERROR_EOF) {
        audio_data->result = ffmpeg_seek(&audio_data->run, audio_data->format_context, 0.0, audio_data->packet, audio_data->stream_index, audio_data->codec_context, audio_data->frame);
    }

    return paContinue;
}

void* ffmpeg_audio_thread(void* arg) {
    audio_data_t* audio_data = arg;

    if ((audio_data->result = ffmpeg_format_context_alloc(&audio_data->format_context, audio_data->url, AVMEDIA_TYPE_AUDIO, &audio_data->stream_index)) == 0) {
        if ((audio_data->result = ffmpeg_codec_context_alloc(&audio_data->codec_context, audio_data->format_context->streams[audio_data->stream_index]->codecpar, audio_data->options)) == 0) {
            if ((audio_data->result = ffmpeg_audio_context_alloc(&audio_data->swr_context, audio_data->codec_context, AV_SAMPLE_FMT_S16)) == 0) {
                if ((audio_data->packet = av_packet_alloc()) != NULL) {
                    if ((audio_data->frame = av_frame_alloc()) != NULL) {
                        PaError error;

                        if ((error = Pa_Initialize()) == paNoError) {
                            PaStream* stream;

                            if ((error = Pa_OpenDefaultStream(&stream, 0, audio_data->codec_context->ch_layout.nb_channels, paInt16, audio_data->codec_context->sample_rate, audio_data->codec_context->frame_size, pa_stream_callback, audio_data)) == paNoError) {
                                if ((error = Pa_StartStream(stream)) == paNoError) {
                                    // while ((error = Pa_IsStreamActive(stream)) == 1) {
                                    //     Pa_Sleep(10);
                                    // }

                                    audio_data->run = 1;

                                    while (audio_data->run == 1) {
                                        av_usleep(10000);
                                    }

                                    if ((error = Pa_StopStream(stream)) != paNoError) {
                                        PRINT_TEXT(Pa_GetErrorText(error));
                                    }
                                }

                                if ((error = Pa_CloseStream(stream)) != paNoError) {
                                    PRINT_TEXT(Pa_GetErrorText(error));
                                }
                            }
                            else {
                                PRINT_TEXT(Pa_GetErrorText(error));
                            }

                            if ((error = Pa_Terminate()) != paNoError) {
                                PRINT_TEXT(Pa_GetErrorText(error));
                            }
                        }

                        if (error != paNoError) {
                            PRINT_TEXT(Pa_GetErrorText(error));
                        }
                    }
                    else {
                        audio_data->result = AVERROR(ENOMEM);
                    }
                }
                else {
                    audio_data->result = AVERROR(ENOMEM);
                }
            }
        }
    }

    if (audio_data->result != 0) {
        PRINT_TEXT(av_err2str(audio_data->result));
    }

    return NULL;
}

#endif

#if 1

int ffmpeg_image_load(const char* url, uint8_t** out_pixels, int* out_width, int* out_height) {
    AVFormatContext* format_context = NULL;
    AVCodecContext* codec_context = NULL;
    struct SwsContext* sws_context = NULL;
    AVPacket* packet;
    AVFrame* frame;
    uint8_t* pixels[4] = { NULL, NULL, NULL, NULL };
    int pitch[4] = { 0, 0, 0, 0 };
    int stream_index;
    int result;

    if ((result = ffmpeg_format_context_alloc(&format_context, url, AVMEDIA_TYPE_VIDEO, &stream_index)) == 0) {
        if ((result = ffmpeg_codec_context_alloc(&codec_context, format_context->streams[stream_index]->codecpar, NULL)) == 0) {
            if ((result = ffmpeg_video_context_alloc(&sws_context, codec_context, AV_PIX_FMT_RGBA)) == 0) {
                if ((packet = av_packet_alloc()) != NULL) {
                    if ((frame = av_frame_alloc()) != NULL) {
                        if ((pixels[0] = av_malloc(av_image_get_buffer_size(AV_PIX_FMT_RGBA, codec_context->width, codec_context->height, 1))) != NULL) {
                            pitch[0] = codec_context->width * 4;

                            if ((result = ffmpeg_get_next_frame(format_context, packet, stream_index, codec_context, frame)) == 0) {
                                if ((result = sws_scale(sws_context, frame->data, frame->linesize, 0, codec_context->height, pixels, pitch)) >= 0) {
                                    result = 0;

                                    out_pixels[0] = pixels[0];
                                    out_width[0] = frame->width;
                                    out_height[0] = frame->height;
                                }
                            }
                        }
                        else {
                            result = AVERROR(ENOMEM);
                        }

                        av_frame_free(&frame);
                    }
                    else {
                        result = AVERROR(ENOMEM);
                    }

                    av_packet_free(&packet);
                }
                else {
                    result = AVERROR(ENOMEM);
                }

                sws_freeContext(sws_context);
            }

            avcodec_free_context(&codec_context);
        }

        avformat_close_input(&format_context);
    }

    return result;
}

int ffmpeg_image_from_memory(void* data, size_t size, uint8_t** out_pixels, int* out_width, int* out_height) {
    AVFormatContext* format_context = NULL;
    AVCodecContext* codec_context = NULL;
    struct SwsContext* sws_context = NULL;
    AVPacket* packet;
    AVFrame* frame;
    uint8_t* pixels[4] = { NULL, NULL, NULL, NULL };
    int pitch[4] = { 0, 0, 0, 0 };
    int stream_index;
    int result;

    if ((result = ffmpeg_from_memory_alloc(&format_context, data, size, AVMEDIA_TYPE_VIDEO, &stream_index, &codec_context, NULL)) == 0) {
        if ((result = ffmpeg_video_context_alloc(&sws_context, codec_context, AV_PIX_FMT_RGBA)) == 0) {
            if ((packet = av_packet_alloc()) != NULL) {
                if ((frame = av_frame_alloc()) != NULL) {
                    if ((pixels[0] = av_malloc(av_image_get_buffer_size(AV_PIX_FMT_RGBA, codec_context->width, codec_context->height, 1))) != NULL) {
                        pitch[0] = codec_context->width * 4;

                        if ((result = ffmpeg_get_next_frame(format_context, packet, stream_index, codec_context, frame)) == 0) {
                            if ((result = sws_scale(sws_context, frame->data, frame->linesize, 0, codec_context->height, pixels, pitch)) >= 0) {
                                result = 0;

                                out_pixels[0] = pixels[0];
                                out_width[0] = frame->width;
                                out_height[0] = frame->height;
                            }
                        }
                    }
                    else {
                        result = AVERROR(ENOMEM);
                    }

                    av_frame_free(&frame);
                }
                else {
                    result = AVERROR(ENOMEM);
                }

                av_packet_free(&packet);
            }
            else {
                result = AVERROR(ENOMEM);
            }

            sws_freeContext(sws_context);
        }

        avcodec_free_context(&codec_context);
        avformat_close_input(&format_context);
    }

    return result;
}

int ffmpeg_cgltf_image_parse(const cgltf_image* image, const char* path_to_gltf_folder, uint8_t** out_pixels, int* out_width, int* out_height) {
    int result;

    if (image->uri != NULL) {
        if (strncmp(image->uri, "data:", 5) == 0) {
            const char* comma = strchr(image->uri, ',');

            if (comma != NULL && comma - image->uri >= 7 && strncmp(comma - 7, ";base64", 7) == 0) {
                const char* base64 = comma + 1;
                size_t base64_size = strlen(base64);
                size_t size = base64_size - base64_size / 4;

                if (base64_size >= 2) {
                    size -= base64[base64_size - 2] == '=';
                    size -= base64[base64_size - 1] == '=';
                }

                void* data;
                cgltf_options options = {
                    .type = cgltf_file_type_invalid,
                    .json_token_count = 0,
                    .memory = {
                        .alloc_func = NULL,
                        .free_func = NULL,
                        .user_data = NULL
                    },
                    .file = {
                        .read = NULL,
                        .release = NULL,
                        .user_data = NULL
                    }
                };

                if (cgltf_load_buffer_base64(&options, size, base64, &data) == cgltf_result_success) {
                    result = ffmpeg_image_from_memory(data, image->buffer_view->size, out_pixels, out_width, out_height);
                }
            }
        }
        else {
            if (path_to_gltf_folder == NULL) {
                puts("path_to_gltf_folder is NULL!");
                return -1;
            }

            size_t path_to_gltf_folder_length = strlen(path_to_gltf_folder);
            size_t image_uri_length = strlen(image->uri);
            char image_path[path_to_gltf_folder_length + image_uri_length + 1];

            memcpy(image_path, path_to_gltf_folder, path_to_gltf_folder_length);
            memcpy(image_path + path_to_gltf_folder_length, image->uri, image_uri_length);

            image_path[path_to_gltf_folder_length + image_uri_length] = '\0';

            result = ffmpeg_image_load(image_path, out_pixels, out_width, out_height);
        }
    }
    else if (image->buffer_view->buffer->data != NULL) {
        uint8_t* data;

        if ((data = malloc(image->buffer_view->size)) != NULL) {
            cgltf_size offset = image->buffer_view->offset;
            cgltf_size stride = image->buffer_view->stride ? image->buffer_view->stride : 1;

            for (cgltf_size i = 0; i < image->buffer_view->size; ++i) {
                data[i] = ((uint8_t*)image->buffer_view->buffer->data)[offset];
                offset += stride;
            }

            result = ffmpeg_image_from_memory(data, image->buffer_view->size, out_pixels, out_width, out_height);
            free(data);
        }
        else {
            result = AVERROR(ENOMEM);
        }
    }

    return result;
}


typedef struct ogl_material {
    GLuint program;
    GLuint texture;
} ogl_material_t;

void ogl_material_init(ogl_material_t* material) {
    material->program = 0;
    material->texture = 0;
}

typedef struct ogl_primitive {
    GLuint vertex_array_object;
    GLuint element_buffer_object;
    GLsizei count;
    GLenum type;
    ogl_material_t* material;
    vec3 box[2];
} ogl_primitive_t;

void ogl_primitive_init(ogl_primitive_t* primitive) {
    primitive->vertex_array_object = 0;
    primitive->element_buffer_object = 0;
    primitive->count = 0;
    primitive->type = GL_UNSIGNED_INT;
    primitive->material = NULL;

    glm_vec3_copy((vec3) { 3.402823466e+38f, 3.402823466e+38f, 3.402823466e+38f }, primitive->box[0]);
    glm_vec3_copy((vec3) { -3.402823466e+38f, -3.402823466e+38f, -3.402823466e+38f }, primitive->box[1]);
}

typedef struct ogl_mesh {
    ogl_primitive_t* primitives;
    GLuint primitives_count;
} ogl_mesh_t;

void ogl_mesh_init(ogl_mesh_t* mesh) {
    mesh->primitives = NULL;
    mesh->primitives_count = 0;
}

typedef struct ogl_node ogl_node_t;
typedef struct ogl_node {
    ogl_node_t* children;
    ogl_mesh_t* mesh;
    GLuint children_count;
	GLfloat translation[3];
	GLfloat rotation[4];
	GLfloat scale[3];
	GLfloat matrix[16];
} ogl_node_t;

void ogl_node_init(ogl_node_t* node) {
    node->children = NULL;
    node->mesh = NULL;
    node->children_count = 0;

    glm_vec3_copy(GLM_VEC3_ZERO, node->translation);
    glm_vec4_copy(GLM_VEC4_ZERO, node->rotation);
    glm_vec3_copy(GLM_VEC3_ONE, node->scale);
    glm_mat4_identity(node->matrix);
}

typedef struct ogl_scene {
    ogl_node_t* nodes;
    GLuint nodes_count;
} ogl_scene_t;

void ogl_scene_init(ogl_scene_t* scene) {
    scene->nodes = NULL;
    scene->nodes_count = 0;
}


void ogl_material_parse(const cgltf_material* material, ogl_material_t* ogl_material) {
    // puts("============================================================");
    // printf("Material name: %s\n", material->name);
    // printf("  has_pbr_metallic_roughness: %i\n", material->has_pbr_metallic_roughness);
    // printf("  has_pbr_specular_glossiness: %i\n", material->has_pbr_specular_glossiness);
    // printf("  has_clearcoat: %i\n", material->has_clearcoat);
    // printf("  has_transmission: %i\n", material->has_transmission);
    // printf("  has_volume: %i\n", material->has_volume);
    // printf("  has_ior: %i\n", material->has_ior);
    // printf("  has_specular: %i\n", material->has_specular);
    // printf("  has_sheen: %i\n", material->has_sheen);
    // printf("  has_emissive_strength: %i\n", material->has_emissive_strength);
    // printf("  has_iridescence: %i\n", material->has_iridescence);

    {
        const char* vertex_shader_source =
            "#version 330 core\n"

            "layout (location = 0) in vec3 aPositions;\n"
            "layout (location = 1) in vec3 aNormals;\n"
            "layout (location = 2) in vec3 aTangents;\n"
            "layout (location = 3) in vec2 aTextureCoordinates;\n"
            "layout (location = 4) in vec4 aColors;\n"
            "layout (location = 5) in vec3 aJoints;\n"
            "layout (location = 6) in vec3 aWeights;\n"

            "out vec2 TextureCoordinates;\n"

            "uniform mat4 model;\n"
            "uniform mat4 view;\n"
            "uniform mat4 projection;\n"

            "void main() {\n"
            "    TextureCoordinates = aTextureCoordinates;\n"
            "    gl_Position = projection * view * model * vec4(aPositions, 1.0);\n"
            "}\n"
        ;

        const char* fragment_shader_source =
            "#version 330 core\n"

            "in vec2 TextureCoordinates;\n"

            "out vec4 FragmentColor;\n"

            "uniform sampler2D texture1;\n"

            "void main() {\n"
            "    FragmentColor = texture(texture1, TextureCoordinates);\n"
            "}\n"
        ;

        GLuint shaders[] = {
            ogl_shader_create(GL_VERTEX_SHADER, &vertex_shader_source),
            ogl_shader_create(GL_FRAGMENT_SHADER, &fragment_shader_source)
        };

        ogl_material->program = ogl_program_create(shaders, sizeof(shaders) / sizeof(shaders[0]));

        glDeleteShader(shaders[0]);
        glDeleteShader(shaders[1]);
    }

    if (material->has_pbr_metallic_roughness == 1) {
        if (material->pbr_metallic_roughness.base_color_texture.texture != NULL) {
            if (material->pbr_metallic_roughness.base_color_texture.texture->image != NULL) {
                uint8_t* pixels;
                int width;
                int height;
                int result;

                if ((result = ffmpeg_cgltf_image_parse(material->pbr_metallic_roughness.base_color_texture.texture->image, NULL, &pixels, &width, &height)) == 0) {
                    ogl_material->texture = ogl_texture_create(width, height, GL_RGBA, pixels);
                    av_freep(&pixels);
                }
                else {
                    PRINT_TEXT(av_err2str(result));
                }
            }
        }
    }

    // if (material->has_pbr_specular_glossiness) {
    //     if (material->pbr_specular_glossiness.diffuse_texture.texture) {
    //         if (material->pbr_specular_glossiness.diffuse_texture.texture->image) {
    //             ffmpeg_cgltf_image_parse(material->pbr_specular_glossiness.diffuse_texture.texture->image, NULL, &pixels, &width, &height);
    //         }
    //     }
    //     else {
    //         // printf("pbr_specular_glossiness texcoord: %i\n", material->pbr_specular_glossiness.diffuse_texture.texcoord);
    //     }
    // }

    // if (material->has_specular) {
    //     if (material->specular.specular_texture.texture) {
    //         if (material->specular.specular_texture.texture->image) {
    //             ffmpeg_cgltf_image_parse(material->specular.specular_texture.texture->image, NULL, &pixels, &width, &height);
    //         }
    //     }
    //     if (material->specular.specular_color_texture.texture) {
    //         if (material->specular.specular_color_texture.texture->image) {
    //             ffmpeg_cgltf_image_parse(material->specular.specular_color_texture.texture->image, NULL, &pixels, &width, &height);
    //         }
    //     }
    // }
}

void cglm_set_box(const void* data, size_t count, vec3 out_box[2]) {
    for (size_t i = 0; i < count; i += 3) {
        if (out_box[0][0] > ((float*)data)[i]) {
            out_box[0][0] = ((float*)data)[i];
        }
        if (out_box[0][1] > ((float*)data)[i + 1]) {
            out_box[0][1] = ((float*)data)[i + 1];
        }
        if (out_box[0][2] > ((float*)data)[i + 2]) {
            out_box[0][2] = ((float*)data)[i + 2];
        }

        if (out_box[1][0] < ((float*)data)[i]) {
            out_box[1][0] = ((float*)data)[i];
        }
        if (out_box[1][1] < ((float*)data)[i + 1]) {
            out_box[1][1] = ((float*)data)[i + 1];
        }
        if (out_box[1][2] < ((float*)data)[i + 2]) {
            out_box[1][2] = ((float*)data)[i + 2];
        }
    }
}

void ogl_primitive_parse(const cgltf_primitive* primitive, ogl_primitive_t* out_primitive) {
    glGenVertexArrays(1, &out_primitive->vertex_array_object);

    if (primitive->indices != NULL) {
        void* accessor_data;

        if ((accessor_data = graphics_cgltf_alloc_and_parse_accessor_data(primitive->indices)) != NULL) {
            glBindVertexArray(out_primitive->vertex_array_object);
            out_primitive->element_buffer_object = ogl_buffer_create(GL_ELEMENT_ARRAY_BUFFER, primitive->indices->buffer_view->size, accessor_data);
            glBindVertexArray(0);

            free(accessor_data);
        }

        out_primitive->count = primitive->indices->count;
        out_primitive->type =
            primitive->indices->component_type == cgltf_component_type_r_8u ? GL_UNSIGNED_BYTE :
            primitive->indices->component_type == cgltf_component_type_r_16u ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
    }

    for (cgltf_size i = 0; i < primitive->attributes_count; ++i) {
        void* accessor_data;
        GLuint vertex_buffer_object;

        glBindVertexArray(out_primitive->vertex_array_object);

        if ((accessor_data = graphics_cgltf_alloc_and_parse_accessor_data(primitive->attributes[i].data)) != NULL) {
            if (primitive->attributes[i].type == cgltf_attribute_type_position) {
                vertex_buffer_object = ogl_buffer_create(GL_ARRAY_BUFFER, primitive->attributes[i].data->buffer_view->size, accessor_data);
                ogl_buffer_attribute(GL_ARRAY_BUFFER, vertex_buffer_object, 0, 3);

                cglm_set_box(accessor_data, primitive->attributes[i].data->buffer_view->size / sizeof(float), out_primitive->box);
            }
            else if (primitive->attributes[i].type == cgltf_attribute_type_normal) {
                vertex_buffer_object = ogl_buffer_create(GL_ARRAY_BUFFER, primitive->attributes[i].data->buffer_view->size, accessor_data);
                ogl_buffer_attribute(GL_ARRAY_BUFFER, vertex_buffer_object, 1, 3);
            }
            else if (primitive->attributes[i].type == cgltf_attribute_type_tangent) {
                vertex_buffer_object = ogl_buffer_create(GL_ARRAY_BUFFER, primitive->attributes[i].data->buffer_view->size, accessor_data);
                ogl_buffer_attribute(GL_ARRAY_BUFFER, vertex_buffer_object, 2, 3);
            }
            else if (primitive->attributes[i].type == cgltf_attribute_type_texcoord) {
                vertex_buffer_object = ogl_buffer_create(GL_ARRAY_BUFFER, primitive->attributes[i].data->buffer_view->size, accessor_data);
                ogl_buffer_attribute(GL_ARRAY_BUFFER, vertex_buffer_object, 3, 2);
            }
            else if (primitive->attributes[i].type == cgltf_attribute_type_color) {
                if (primitive->attributes[i].data->component_type == cgltf_component_type_r_16u) {
                    float* color;

                    if ((color = malloc(primitive->attributes[i].data->count * 4 * sizeof(float))) != NULL) {
                        if (primitive->attributes[i].data->type == cgltf_type_vec4) {
                            for (cgltf_size i = 0; i < primitive->attributes[i].data->count * 4; ++i) {
                                color[i] = ((uint16_t*)accessor_data + i)[0] / 65535.0f;
                            }
                        }
                        else if (primitive->attributes[i].data->type == cgltf_type_vec3) {
                            for (cgltf_size i = 0; i < primitive->attributes[i].data->count * 4; ++i) {
                                if (i > 0 && i % 4 == 0) {
                                    color[i] = 1.0f;
                                }
                                else {
                                    color[i] = ((uint16_t*)accessor_data + i)[0] / 65535.0f;
                                }
                            }
                        }

                        free(accessor_data);
                        accessor_data = color;
                    }
                }

                vertex_buffer_object = ogl_buffer_create(GL_ARRAY_BUFFER, (primitive->attributes[i].data->count * 4 * sizeof(float)), accessor_data);
                ogl_buffer_attribute(GL_ARRAY_BUFFER, vertex_buffer_object, 4, 4);
            }
            else if (primitive->attributes[i].type == cgltf_attribute_type_joints) {
                vertex_buffer_object = ogl_buffer_create(GL_ARRAY_BUFFER, primitive->attributes[i].data->buffer_view->size, accessor_data);
                ogl_buffer_attribute(GL_ARRAY_BUFFER, vertex_buffer_object, 5, 3);
            }
            else if (primitive->attributes[i].type == cgltf_attribute_type_weights) {
                vertex_buffer_object = ogl_buffer_create(GL_ARRAY_BUFFER, primitive->attributes[i].data->buffer_view->size, accessor_data);
                ogl_buffer_attribute(GL_ARRAY_BUFFER, vertex_buffer_object, 6, 3);
            }

            free(accessor_data);
        }

        glBindVertexArray(0);
        glDeleteBuffers(1, &vertex_buffer_object);
    }

    if (primitive->material != NULL) {
        if ((out_primitive->material = malloc(sizeof(ogl_material_t))) != NULL) {
            ogl_material_init(out_primitive->material);
            ogl_material_parse(primitive->material, out_primitive->material);
        }
    }
}

void ogl_mesh_parse(const cgltf_mesh* mesh, ogl_mesh_t* out_mesh) {
    if ((out_mesh->primitives = malloc(sizeof(ogl_primitive_t) * mesh->primitives_count)) != NULL) {
        out_mesh->primitives_count = mesh->primitives_count;

        for (cgltf_size i = 0; i < mesh->primitives_count; ++i) {
            ogl_primitive_init(&out_mesh->primitives[i]);
            ogl_primitive_parse(&mesh->primitives[i], &out_mesh->primitives[i]);
        }
    }
}

void ogl_node_parse(const cgltf_node* node, ogl_node_t* out_node) {
    if (node->has_translation == 1) {
        glm_vec3_copy(node->translation, out_node->translation);
    }
    if (node->has_rotation == 1) {
        glm_vec4_copy(node->rotation, out_node->rotation);
    }
    if (node->has_scale == 1) {
        glm_vec3_copy(node->scale, out_node->scale);
    }
    if (node->has_matrix == 1) {
        glm_mat4_copy(node->matrix, out_node->matrix);
        cgltf_node_transform_world(node, out_node->matrix);
    }

    if (node->mesh != NULL) {
        if ((out_node->mesh = malloc(sizeof(ogl_mesh_t))) != NULL) {
            ogl_mesh_init(out_node->mesh);
            ogl_mesh_parse(node->mesh, out_node->mesh);
        }
    }

    if (node->children != NULL) {
        if ((out_node->children = malloc(sizeof(ogl_node_t) * node->children_count)) != NULL) {
            out_node->children_count = node->children_count;

            for (cgltf_size i = 0; i < node->children_count; ++i) {
                ogl_node_init(&out_node->children[i]);
                ogl_node_parse(node->children[i], &out_node->children[i]);
            }
        }
    }
}

void ogl_scene_parse(const cgltf_scene* scene, ogl_scene_t* out_scene) {
    if ((out_scene->nodes = malloc(sizeof(ogl_node_t) * scene->nodes_count)) != NULL) {
        out_scene->nodes_count = scene->nodes_count;

        for (cgltf_size i = 0; i < scene->nodes_count; ++i) {
            ogl_node_init(&out_scene->nodes[i]);
            ogl_node_parse(scene->nodes[i], &out_scene->nodes[i]);
        }
    }
}

cgltf_result ogl_gltf_load(const char* url, ogl_scene_t* scene) {
    cgltf_result result;
    cgltf_options options = {
        .type = cgltf_file_type_invalid,
        .json_token_count = 0,
        .memory = {
            .alloc_func = NULL,
            .free_func = NULL,
            .user_data = NULL
        },
        .file = {
            .read = NULL,
            .release = NULL,
            .user_data = NULL
        }
    };
    cgltf_data* data;

    if (strncmp(url, "http", 4) == 0) {
        void* url_data;
        CURLcode curl_code;

        if ((curl_code = curl_get_url_data(url, &url_data, 60000)) == CURLE_OK) {
            if ((result = cgltf_parse(&options, url_data + sizeof(size_t), *((size_t*)url_data), &data)) == cgltf_result_success) {
                if ((result = cgltf_load_buffers(&options, data, NULL)) == cgltf_result_success) {
                    if (data->scene != NULL) {
                        ogl_scene_parse(data->scene, scene);
                    }
                }

                cgltf_free(data);
            }

            free(url_data);
        }
        else {
            PRINT_TEXT(curl_easy_strerror(curl_code));
        }
    }
    else {
        if ((result = cgltf_parse_file(&options, url, &data)) == cgltf_result_success) {
            if ((result = cgltf_load_buffers(&options, data, url)) == cgltf_result_success) {
                if (data->scene != NULL) {
                    ogl_scene_parse(data->scene, scene);
                }
            }

            cgltf_free(data);
        }
    }

    return result;
}

void ogl_draw_node(const ogl_node_t* node, mat4 projection, mat4 view) {
    if (node->mesh != NULL) {
        mat4 matrix;
        glm_mat4_mul(projection, view, matrix);

        for (GLuint i = 0; i < node->mesh->primitives_count; ++i) {
            if (cglm_frustum_culling(matrix, node->mesh->primitives[i].box) == false) {
                printf("[%i]SKIP", i);
                continue;
            }

            if (node->mesh->primitives[i].material != NULL) {
                if (node->mesh->primitives[i].material->program != 0) {
                    glUseProgram(node->mesh->primitives[i].material->program);
                    glUniformMatrix4fv(glGetUniformLocation(node->mesh->primitives[i].material->program, "projection"), 1, GL_FALSE, projection);
                    glUniformMatrix4fv(glGetUniformLocation(node->mesh->primitives[i].material->program, "view"), 1, GL_FALSE, view);
                    glUniformMatrix4fv(glGetUniformLocation(node->mesh->primitives[i].material->program, "model"), 1, GL_FALSE, node->matrix);
                }

                // glPointSize(8.0f); glBegin(GL_POINTS); for (int i = 0; i < sizeof(box) / sizeof(box[0]); ++i) { glVertex3fv(box[i]); } glEnd();
                // glBegin(GL_LINES); for (int i = 0; i < sizeof(box) / sizeof(box[0]); ++i) { glVertex3fv(box[i]); } glEnd();

                if (node->mesh->primitives[i].material->texture != 0) {
                    glBindTexture(GL_TEXTURE_2D, node->mesh->primitives[i].material->texture);
                }
            }

            glBindVertexArray(node->mesh->primitives[i].vertex_array_object);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, node->mesh->primitives[i].element_buffer_object);
                    glDrawElements(GL_TRIANGLES, node->mesh->primitives[i].count, node->mesh->primitives[i].type, NULL);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            glBindTexture(GL_TEXTURE_2D, 0);
            glUseProgram(0);
        }
    }

    for (GLuint i = 0; i < node->children_count; ++i) {
        ogl_draw_node(&node->children[i], projection, view);
    }
}

void ogl_scene_draw(const ogl_scene_t* scene, mat4 projection, mat4 view) {
    for (GLuint i = 0; i < scene->nodes_count; ++i) {
        ogl_draw_node(&scene->nodes[i], projection, view);
    }
}

#endif

void glfw_error_callback(int error_code, const char* description) {
    PRINT_TEXT(description);
}

void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    glm_perspective(GLM_PI_4f, (float)width / height, 0.01f, 3.402823466e+38f, glfwGetWindowUserPointer(window));
}


int main(int argc, char** argv) {
    glfwSetErrorCallback(glfw_error_callback);

    if (glfwInit() == GLFW_TRUE) {
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

        GLFWwindow* window;

    #if 1
        {
            GLFWmonitor* monitor;
            const GLFWvidmode* mode;

            if ((monitor = glfwGetPrimaryMonitor()) != NULL) {
                if ((mode = glfwGetVideoMode(monitor)) != NULL) {
                    if ((window = glfwCreateWindow(mode->width - mode->width * 0.1f, mode->height - mode->height * 0.1f, "Engine", NULL, NULL)) != NULL) {
                        glfwSetWindowPos(window, mode->width * 0.05f, mode->height * 0.05f);
                    }
                }
            }
        }
    #endif

        if (window != NULL) {
            glfwMakeContextCurrent(window);

            glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);

            if (gladLoadGL(glfwGetProcAddress) != 0) {
                glDebugMessageCallback(ogl_debug_message_callback, NULL);
                glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
                glFrontFace(GL_CCW);

                glEnable(GL_DEPTH_TEST);

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


                int window_width;
                int window_height;

                glfwGetWindowSize(window, &window_width, &window_height);

                mat4 projection = GLM_MAT4_IDENTITY_INIT;
                mat4 view = GLM_MAT4_IDENTITY_INIT;
                {
                    glm_perspective(GLM_PI_4f, (float)window_width / window_height, 0.01f, 3.402823466e+38f, projection);
                    glfwSetWindowUserPointer(window, projection);
                }

                double cursor_position_x;
                double cursor_position_y;


                ogl_scene_t scene;
                ogl_gltf_load("https://github.com/KhronosGroup/glTF-Sample-Models/raw/main/2.0/Corset/glTF-Binary/Corset.glb", &scene);


                while (glfwWindowShouldClose(window) == 0) {
                    glfwWaitEventsTimeout(0.001);

                #if 1
                    glfwGetWindowSize(window, &window_width, &window_height);
                    glfwGetCursorPos(window, &cursor_position_x, &cursor_position_y);

                    float move_speed = 1.0f;
                    float mouse_sensitivity = 1.0f;

                    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
                        move_speed *= 10.0f;
                        mouse_sensitivity *= 10.0f;
                    }
                    else if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
                        move_speed /= 10.0f;
                        mouse_sensitivity /= 10.0f;
                    }

                    static double last_time = 0.0;

                    if (glfwGetTime() - last_time > 0.01) {
                        last_time = glfwGetTime();

                        static int first_person_view = 0;
                        static double first_person_view_change_last_delay = 0.0f;

                        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
                            if (last_time - first_person_view_change_last_delay > 0.5) {
                                first_person_view = (first_person_view + 1) % 2;

                                if (first_person_view == 1) {
                                    glfwSetCursorPos(window, window_width / 2.0, window_height / 2.0);
                                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
                                }
                                else {
                                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                                }

                                first_person_view_change_last_delay = last_time;
                            }
                        }

                        if (first_person_view == 1) {
                            if ((int)cursor_position_x != window_width / 2 || (int)cursor_position_y != window_height / 2) {
                                cglm_view_rotate(view, glm_rad((cursor_position_x - window_width / 2) * mouse_sensitivity / 100.0f), (vec3) { 0.0f, 1.0f, 0.0f });
                                cglm_view_rotate(view, glm_rad((cursor_position_y - window_height / 2) * mouse_sensitivity / 100.0f), (vec3) { 1.0f, 0.0f, 0.0f });

                                glfwSetCursorPos(window, window_width / 2.0, window_height / 2.0);
                            }
                        }

                        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                            cglm_view_move((vec3) { 1.0f, 0.0f, 0.0f }, view, -move_speed);
                        }
                        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                            cglm_view_move((vec3) { 1.0f, 0.0f, 0.0f }, view, move_speed);
                        }

                        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
                            cglm_view_move_up(view, -move_speed);
                        }
                        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
                            cglm_view_move_up(view, move_speed);
                        }

                        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                            cglm_view_move((vec3) { 0.0f, 0.0f, 1.0f }, view, move_speed);
                        }
                        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                            cglm_view_move((vec3) { 0.0f, 0.0f, 1.0f }, view, -move_speed);
                        }

                        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
                            glm_mat4_identity(view);
                            glm_perspective(GLM_PI_4f, (float)window_width / window_height, 0.01f, 3.402823466e+38f, projection);
                        }
                    }
                #endif

                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                        glm_translate(scene.nodes[0].matrix, (vec3) { -0.01f, 0.0f, 0.0f });
                        scene.nodes[0].mesh->primitives[0].box[0][0] -= 0.01f;
                        scene.nodes[0].mesh->primitives[0].box[1][0] -= 0.01f;
                    }

                    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                        glm_translate(scene.nodes[0].matrix, (vec3) { 0.01f, 0.0f, 0.0f });
                        scene.nodes[0].mesh->primitives[0].box[0][0] += 0.01f;
                        scene.nodes[0].mesh->primitives[0].box[1][0] += 0.01f;
                    }

                    ogl_scene_draw(&scene, projection, view);

                    glfwSwapBuffers(window);

                    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                        glfwSetWindowShouldClose(window, GLFW_TRUE);
                    }
                }
            }

            glfwDestroyWindow(window);
        }

        glfwTerminate();
    }

    return 0;
}

#if 0

void engine_print_log(engine_t* engine) {
    printf(
        "\033[H\033[J"
        TEXT_COLOR_BLUE "%s\n"
        TEXT_COLOR_RED "%*s%*s%*s%*s%*s%*s%*s\n"
        TEXT_COLOR_NORMAL "%*.3f%*s%*.3f%*s%*.3f%*s%*.3f%*s%*.2f%*s%*i%*s%*i%*i%*s%*i\n"
        TEXT_COLOR_CYAN "%s" TEXT_COLOR_RED "&pid=" TEXT_COLOR_NORMAL "%i\n",

        // Source link
        engine->url ? engine->url : "No source URL",

        // Text
        10 - 2, "Time",
        10, "Video",
        10, "Audio",
        10, "Duration",
        10, "Volume",
        10, "Size",
        15, "Index",

        // Time
        10 - 2, engine->time_run == 1 ? (double)(engine->time_now - engine->time_start) / AV_TIME_BASE : 0.0,
        0, TEXT_COLOR_RED "s" TEXT_COLOR_NORMAL,

        // Video
        10 - 1, engine->video_run == 1 && engine->video_frame->pts >= 0 ? av_q2d(engine->video_format_context->streams[engine->video_stream_index]->time_base) * engine->video_frame->pts : 0.0,
        0, TEXT_COLOR_RED "s" TEXT_COLOR_NORMAL,

        // Audio
        10 - 1, engine->audio_run == 1 && engine->audio_frame->pts >= 0 ? av_q2d(engine->audio_format_context->streams[engine->audio_stream_index]->time_base) * engine->audio_frame->pts : 0.0,
        0, TEXT_COLOR_RED "s" TEXT_COLOR_NORMAL,

        // Duration
        10 - 1, engine->video_run == 1 && engine->video_format_context->duration > 0 ? (double)engine->video_format_context->duration / AV_TIME_BASE : 0,
        0, TEXT_COLOR_RED "s" TEXT_COLOR_NORMAL,

        // Volume
        10 - 1, engine->audio_run == 1 ? engine->audio_gain * 100.0f : 0.0f,
        0, TEXT_COLOR_RED "%" TEXT_COLOR_NORMAL,

        // Size
        10 - 1, engine->video_run == 1 ? engine->video_codec_context->width : 0,
        0, TEXT_COLOR_RED "x" TEXT_COLOR_NORMAL,
        0, engine->video_run == 1 ? engine->video_codec_context->height : 0,

        // Index
        10, engine->pid_count > 0 ? engine->pid_current + 1 : 0,
        0, TEXT_COLOR_RED "/" TEXT_COLOR_NORMAL,
        0, engine->pid_count,

        // Link to list
        engine->url_to_list ? engine->url_to_list : "No link to list",
        engine->pid_current
    );
}

int audio_thread(void* data) {
    engine_t* engine;

    engine = data;

    if ((engine->audio_result = media_open(&engine->audio_format_context, engine->url, AVMEDIA_TYPE_AUDIO, &engine->audio_stream_index, &engine->audio_codec_context, NULL)) == 0) {
        if ((engine->audio_result = ffmpeg_audio_context_alloc(&engine->audio_swr_context, engine->audio_codec_context, AV_SAMPLE_FMT_S16)) == 0) {
            if ((engine->audio_packet = av_packet_alloc()) != NULL) {
                if ((engine->audio_frame = av_frame_alloc()) != NULL) {
                    SDL_AudioStream* audio_stream;
                    SDL_AudioSpec audio_spec;
                    SDL_AudioDeviceID audio_device_id;

                    audio_spec.format = SDL_AUDIO_S16;
                    audio_spec.channels = engine->audio_codec_context->ch_layout.nb_channels;
                    audio_spec.freq = engine->audio_codec_context->sample_rate;

                    if ((audio_stream = SDL_CreateAudioStream(&audio_spec, &audio_spec)) != NULL) {
                        if ((audio_device_id = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_OUTPUT, &audio_spec)) != 0) {
                            if (SDL_BindAudioStream(audio_device_id, audio_stream) == 0) {
                                uint8_t* audio_data;

                                if ((audio_data = malloc(engine->audio_codec_context->frame_size * engine->audio_codec_context->ch_layout.nb_channels * sizeof(int16_t))) != NULL) {
                                    engine->audio_run = 1;

                                    while (engine->audio_run == 1) {
                                        if (engine->audio_time_seek > 0.0) {
                                            engine->audio_result = ffmpeg_seek(&engine->audio_run, engine->audio_format_context, engine->audio_time_seek, engine->audio_packet, engine->audio_stream_index, engine->audio_codec_context, engine->audio_frame);
                                            engine->audio_time_seek = 0.0;
                                        }

                                        while (engine->audio_run == 1 && engine->video_run == 1 && engine->video_time_seek > 0.0) {
                                            av_usleep(10000);
                                        }

                                        if (engine->audio_run == 1 && engine->audio_result == 0 && av_q2d(engine->audio_format_context->streams[engine->audio_stream_index]->time_base) * engine->audio_frame->pts < (double)(engine->time_now - engine->time_start) / AV_TIME_BASE) {
                                            engine->audio_result = ffmpeg_get_next_frame(engine->audio_format_context, engine->audio_packet, engine->audio_stream_index, engine->audio_codec_context, engine->audio_frame);
                                        }

                                        if (engine->audio_result == 0) {
                                            if ((engine->audio_result = swr_convert(engine->audio_swr_context, &audio_data, engine->audio_frame->nb_samples, engine->audio_frame->data, engine->audio_frame->nb_samples)) >= 0) {
                                                engine->audio_result = 0;

                                                for (int i = 0; i < engine->audio_codec_context->frame_size * engine->audio_codec_context->ch_layout.nb_channels; ++i) {
                                                    ((int16_t*)audio_data)[i] *= engine->audio_gain * min(1.0f, glm_vec3_distance(G_POSITION, (vec3) { -1.0f, 0.0f, 0.0f }));

                                                    if (engine->audio_codec_context->ch_layout.nb_channels == 2) {
                                                        ++i;
                                                        ((int16_t*)audio_data)[i] *= engine->audio_gain * min(1.0f, glm_vec3_distance(G_POSITION, (vec3) { 1.0f, 0.0f, 0.0f }));
                                                    }
                                                }

                                                if (SDL_PutAudioStreamData(audio_stream, audio_data, engine->audio_codec_context->frame_size * engine->audio_codec_context->ch_layout.nb_channels * sizeof(int16_t)) == 0) {
                                                    while (engine->audio_run == 1 && SDL_GetAudioStreamQueued(audio_stream) > engine->audio_codec_context->frame_size * engine->audio_codec_context->ch_layout.nb_channels * sizeof(int16_t)) {
                                                        SDL_DelayNS(10000000);
                                                    }
                                                }
                                            }
                                        }
                                        else if (engine->audio_result == AVERROR_EOF) {
                                            avcodec_flush_buffers(engine->audio_codec_context);
                                            engine->audio_time_seek = 0.000001;

                                            if (engine->video_run == 1) {
                                                engine->video_time_seek = 0.000001;
                                            }
                                        }
                                    }

                                    free(audio_data);
                                }
                                else {
                                    engine->audio_result = AVERROR(ENOMEM);
                                }
                            }

                            SDL_CloseAudioDevice(audio_device_id);
                        }

                        SDL_DestroyAudioStream(audio_stream);
                    }
                    else {
                        PRINT_TEXT(SDL_GetError());
                    }

                    av_frame_free(&engine->audio_frame);
                }
                else {
                    engine->audio_result = AVERROR(ENOMEM);
                }

                av_packet_free(&engine->audio_packet);
            }
            else {
                engine->audio_result = AVERROR(ENOMEM);
            }

            swr_free(&engine->audio_swr_context);
        }

        avcodec_free_context(&engine->audio_codec_context);
        avformat_close_input(&engine->audio_format_context);
    }

    engine->audio_run = 0;

    return engine->audio_result;
}

int node_sort_transparent_nodes_to_draw_correctly(const void* a, const void* b) {
    return
        ((node_t**)a)[0]->distance < ((node_t**)b)[0]->distance ? -1 :
        ((node_t**)a)[0]->distance > ((node_t**)b)[0]->distance ?  1 :
        0;
}

#endif
