/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_AUTO_GL_H_
#define ANDROID_AUTO_GL_H_

#include <memory>
#define EGL_EGLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

// TODO(zachr): use hwc_drm_bo to turn buffer handles into textures
#ifndef EGL_NATIVE_HANDLE_ANDROID_NVX
#define EGL_NATIVE_HANDLE_ANDROID_NVX 0x322A
#endif

namespace android {

#if defined(__GNUC__)
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=60168
#define AUTO_GL_TYPE(name, type, zero, deleter) \
  struct name##Pointer {                        \
    type _v;                                    \
    name##Pointer() : _v(zero) {}               \
    name##Pointer(const type v) : _v(v) {}      \
    operator type() const { return _v; }        \
  };                                            \
  struct name##Deleter {                        \
    typedef name##Pointer pointer;              \
                                                \
    void operator()(pointer ptr) const {        \
      type& p = ptr._v;                         \
      if (p != zero) {                          \
        deleter;                                \
      }                                         \
    }                                           \
  };                                            \
  } /* namespace android */                     \
  namespace std {                               \
    inline bool                                 \
    operator !=(const android::name##Pointer& x,\
                const std::nullptr_t& y)        \
               noexcept                         \
    {                                           \
      return x._v != zero;                      \
    }                                           \
  } /* namespace std */                         \
  inline bool                                   \
  operator ==(const android::name##Pointer& x,  \
              type y)                           \
  {                                             \
    return x._v == y;                           \
  }                                             \
  inline bool                                   \
  operator !=(const android::name##Pointer& x,  \
              type y)                           \
  {                                             \
    return x._v != y;                           \
  }                                             \
  namespace android {                           \
  typedef std::unique_ptr<name##Pointer, name##Deleter> name;
#else
#define AUTO_GL_TYPE(name, type, zero, deleter) \
  struct name##Deleter {                        \
    typedef type pointer;                       \
                                                \
    void operator()(pointer p) const {          \
      if (p != zero) {                          \
        deleter;                                \
      }                                         \
    }                                           \
  };                                            \
  typedef std::unique_ptr<type, name##Deleter> name;
#endif

AUTO_GL_TYPE(AutoGLFramebuffer, GLuint, 0, glDeleteFramebuffers(1, &p))
AUTO_GL_TYPE(AutoGLBuffer, GLuint, 0, glDeleteBuffers(1, &p))
AUTO_GL_TYPE(AutoGLTexture, GLuint, 0, glDeleteTextures(1, &p))
AUTO_GL_TYPE(AutoGLShader, GLint, 0, glDeleteShader(p))
AUTO_GL_TYPE(AutoGLProgram, GLint, 0, glDeleteProgram(p))

struct AutoEGLDisplayImage {
  AutoEGLDisplayImage() = default;

  AutoEGLDisplayImage(EGLDisplay display, EGLImageKHR image)
      : display_(display), image_(image) {
  }

  AutoEGLDisplayImage(const AutoEGLDisplayImage& rhs) = delete;
  AutoEGLDisplayImage(AutoEGLDisplayImage&& rhs) {
    display_ = rhs.display_;
    image_ = rhs.image_;
    rhs.display_ = EGL_NO_DISPLAY;
    rhs.image_ = EGL_NO_IMAGE_KHR;
  }

  ~AutoEGLDisplayImage() {
    clear();
  }

  AutoEGLDisplayImage& operator=(const AutoEGLDisplayImage& rhs) = delete;
  AutoEGLDisplayImage& operator=(AutoEGLDisplayImage&& rhs) {
    clear();
    std::swap(display_, rhs.display_);
    std::swap(image_, rhs.image_);
    return *this;
  }

  void reset(EGLDisplay display, EGLImageKHR image) {
    clear();
    display_ = display;
    image_ = image;
  }

  void clear() {
    if (image_ != EGL_NO_IMAGE_KHR) {
      eglDestroyImageKHR(display_, image_);
      display_ = EGL_NO_DISPLAY;
      image_ = EGL_NO_IMAGE_KHR;
    }
  }

  EGLImageKHR image() const {
    return image_;
  }

 private:
  EGLDisplay display_ = EGL_NO_DISPLAY;
  EGLImageKHR image_ = EGL_NO_IMAGE_KHR;
};

struct AutoEGLImageAndGLTexture {
  AutoEGLDisplayImage image;
  AutoGLTexture texture;
};
}

#endif
