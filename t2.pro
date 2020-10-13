#-------------------------------------------------
#
# Project created by QtCreator 2020-05-02T17:24:08
#
#-------------------------------------------------

QT       += multimedia
QT       += core gui  #曲线部分

QT       += charts
QT       += multimedia multimediawidgets
QT       += network
QT       += axcontainer
QT       += opengl

CONFIG   += release






greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = t2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    callout.cpp \
    chartview.cpp \
    dealthread.cpp

HEADERS += \
        mainwindow.h \
    include/opencv/cv.h \
    include/opencv/cv.hpp \
    include/opencv/cvaux.h \
    include/opencv/cvaux.hpp \
    include/opencv/cvwimage.h \
    include/opencv/cxcore.h \
    include/opencv/cxcore.hpp \
    include/opencv/cxeigen.hpp \
    include/opencv/cxmisc.h \
    include/opencv/highgui.h \
    include/opencv/ml.h \
    include/opencv2/calib3d/calib3d.hpp \
    include/opencv2/calib3d/calib3d_c.h \
    include/opencv2/core/hal/hal.hpp \
    include/opencv2/core/hal/interface.h \
    include/opencv2/core/hal/intrin.hpp \
    include/opencv2/core/hal/intrin_cpp.hpp \
    include/opencv2/core/hal/intrin_neon.hpp \
    include/opencv2/core/hal/intrin_sse.hpp \
    include/opencv2/core/hal/intrin_vsx.hpp \
    include/opencv2/core/utils/logger.hpp \
    include/opencv2/core/utils/trace.hpp \
    include/opencv2/core/affine.hpp \
    include/opencv2/core/base.hpp \
    include/opencv2/core/bufferpool.hpp \
    include/opencv2/core/core.hpp \
    include/opencv2/core/core_c.h \
    include/opencv2/core/cuda.hpp \
    include/opencv2/core/cuda.inl.hpp \
    include/opencv2/core/cuda_stream_accessor.hpp \
    include/opencv2/core/cuda_types.hpp \
    include/opencv2/core/cv_cpu_dispatch.h \
    include/opencv2/core/cv_cpu_helper.h \
    include/opencv2/core/cvdef.h \
    include/opencv2/core/cvstd.hpp \
    include/opencv2/core/cvstd.inl.hpp \
    include/opencv2/core/directx.hpp \
    include/opencv2/core/eigen.hpp \
    include/opencv2/core/fast_math.hpp \
    include/opencv2/core/ippasync.hpp \
    include/opencv2/core/mat.hpp \
    include/opencv2/core/mat.inl.hpp \
    include/opencv2/core/matx.hpp \
    include/opencv2/core/neon_utils.hpp \
    include/opencv2/core/ocl.hpp \
    include/opencv2/core/ocl_genbase.hpp \
    include/opencv2/core/opengl.hpp \
    include/opencv2/core/operations.hpp \
    include/opencv2/core/optim.hpp \
    include/opencv2/core/ovx.hpp \
    include/opencv2/core/persistence.hpp \
    include/opencv2/core/ptr.inl.hpp \
    include/opencv2/core/saturate.hpp \
    include/opencv2/core/softfloat.hpp \
    include/opencv2/core/sse_utils.hpp \
    include/opencv2/core/traits.hpp \
    include/opencv2/core/types.hpp \
    include/opencv2/core/types_c.h \
    include/opencv2/core/utility.hpp \
    include/opencv2/core/va_intel.hpp \
    include/opencv2/core/version.hpp \
    include/opencv2/core/vsx_utils.hpp \
    include/opencv2/core/wimage.hpp \
    include/opencv2/dnn/all_layers.hpp \
    include/opencv2/dnn/dict.hpp \
    include/opencv2/dnn/dnn.hpp \
    include/opencv2/dnn/dnn.inl.hpp \
    include/opencv2/dnn/layer.details.hpp \
    include/opencv2/dnn/layer.hpp \
    include/opencv2/dnn/shape_utils.hpp \
    include/opencv2/features2d/features2d.hpp \
    include/opencv2/flann/all_indices.h \
    include/opencv2/flann/allocator.h \
    include/opencv2/flann/any.h \
    include/opencv2/flann/autotuned_index.h \
    include/opencv2/flann/composite_index.h \
    include/opencv2/flann/config.h \
    include/opencv2/flann/defines.h \
    include/opencv2/flann/dist.h \
    include/opencv2/flann/dummy.h \
    include/opencv2/flann/dynamic_bitset.h \
    include/opencv2/flann/flann.hpp \
    include/opencv2/flann/flann_base.hpp \
    include/opencv2/flann/general.h \
    include/opencv2/flann/ground_truth.h \
    include/opencv2/flann/hdf5.h \
    include/opencv2/flann/heap.h \
    include/opencv2/flann/hierarchical_clustering_index.h \
    include/opencv2/flann/index_testing.h \
    include/opencv2/flann/kdtree_index.h \
    include/opencv2/flann/kdtree_single_index.h \
    include/opencv2/flann/kmeans_index.h \
    include/opencv2/flann/linear_index.h \
    include/opencv2/flann/logger.h \
    include/opencv2/flann/lsh_index.h \
    include/opencv2/flann/lsh_table.h \
    include/opencv2/flann/matrix.h \
    include/opencv2/flann/miniflann.hpp \
    include/opencv2/flann/nn_index.h \
    include/opencv2/flann/object_factory.h \
    include/opencv2/flann/params.h \
    include/opencv2/flann/random.h \
    include/opencv2/flann/result_set.h \
    include/opencv2/flann/sampling.h \
    include/opencv2/flann/saving.h \
    include/opencv2/flann/simplex_downhill.h \
    include/opencv2/flann/timer.h \
    include/opencv2/highgui/highgui.hpp \
    include/opencv2/highgui/highgui_c.h \
    include/opencv2/imgcodecs/imgcodecs.hpp \
    include/opencv2/imgcodecs/imgcodecs_c.h \
    include/opencv2/imgcodecs/ios.h \
    include/opencv2/imgproc/detail/distortion_model.hpp \
    include/opencv2/imgproc/hal/hal.hpp \
    include/opencv2/imgproc/hal/interface.h \
    include/opencv2/imgproc/imgproc.hpp \
    include/opencv2/imgproc/imgproc_c.h \
    include/opencv2/imgproc/types_c.h \
    include/opencv2/ml/ml.hpp \
    include/opencv2/objdetect/detection_based_tracker.hpp \
    include/opencv2/objdetect/objdetect.hpp \
    include/opencv2/objdetect/objdetect_c.h \
    include/opencv2/photo/cuda.hpp \
    include/opencv2/photo/photo.hpp \
    include/opencv2/photo/photo_c.h \
    include/opencv2/shape/emdL1.hpp \
    include/opencv2/shape/hist_cost.hpp \
    include/opencv2/shape/shape.hpp \
    include/opencv2/shape/shape_distance.hpp \
    include/opencv2/shape/shape_transformer.hpp \
    include/opencv2/stitching/detail/autocalib.hpp \
    include/opencv2/stitching/detail/blenders.hpp \
    include/opencv2/stitching/detail/camera.hpp \
    include/opencv2/stitching/detail/exposure_compensate.hpp \
    include/opencv2/stitching/detail/matchers.hpp \
    include/opencv2/stitching/detail/motion_estimators.hpp \
    include/opencv2/stitching/detail/seam_finders.hpp \
    include/opencv2/stitching/detail/timelapsers.hpp \
    include/opencv2/stitching/detail/util.hpp \
    include/opencv2/stitching/detail/util_inl.hpp \
    include/opencv2/stitching/detail/warpers.hpp \
    include/opencv2/stitching/detail/warpers_inl.hpp \
    include/opencv2/stitching/warpers.hpp \
    include/opencv2/superres/optical_flow.hpp \
    include/opencv2/video/background_segm.hpp \
    include/opencv2/video/tracking.hpp \
    include/opencv2/video/tracking_c.h \
    include/opencv2/video/video.hpp \
    include/opencv2/videoio/cap_ios.h \
    include/opencv2/videoio/videoio.hpp \
    include/opencv2/videoio/videoio_c.h \
    include/opencv2/videostab/deblurring.hpp \
    include/opencv2/videostab/fast_marching.hpp \
    include/opencv2/videostab/fast_marching_inl.hpp \
    include/opencv2/videostab/frame_source.hpp \
    include/opencv2/videostab/global_motion.hpp \
    include/opencv2/videostab/inpainting.hpp \
    include/opencv2/videostab/log.hpp \
    include/opencv2/videostab/motion_core.hpp \
    include/opencv2/videostab/motion_stabilizing.hpp \
    include/opencv2/videostab/optical_flow.hpp \
    include/opencv2/videostab/outlier_rejection.hpp \
    include/opencv2/videostab/ring_buffer.hpp \
    include/opencv2/videostab/stabilizer.hpp \
    include/opencv2/videostab/wobble_suppression.hpp \
    include/opencv2/calib3d.hpp \
    include/opencv2/core.hpp \
    include/opencv2/cvconfig.h \
    include/opencv2/dnn.hpp \
    include/opencv2/features2d.hpp \
    include/opencv2/flann.hpp \
    include/opencv2/highgui.hpp \
    include/opencv2/imgcodecs.hpp \
    include/opencv2/imgproc.hpp \
    include/opencv2/ml.hpp \
    include/opencv2/objdetect.hpp \
    include/opencv2/opencv.hpp \
    include/opencv2/opencv_modules.hpp \
    include/opencv2/photo.hpp \
    include/opencv2/shape.hpp \
    include/opencv2/stitching.hpp \
    include/opencv2/superres.hpp \
    include/opencv2/video.hpp \
    include/opencv2/videoio.hpp \
    include/opencv2/videostab.hpp \
    include/opencv2/world.hpp \
    include/c_api.h \
    include/Interface.h \
    include/main_vs.h \
    include/subfunction.h \
    include/tensorflowmodel.h \
    callout.h \
    chartview.h \
    dealthread.h \
    opencv/cv.h \
    opencv/cv.hpp \
    opencv/cvaux.h \
    opencv/cvaux.hpp \
    opencv/cvwimage.h \
    opencv/cxcore.h \
    opencv/cxcore.hpp \
    opencv/cxeigen.hpp \
    opencv/cxmisc.h \
    opencv/highgui.h \
    opencv/ml.h \
    opencv2/calib3d/calib3d.hpp \
    opencv2/calib3d/calib3d_c.h \
    opencv2/core/hal/hal.hpp \
    opencv2/core/hal/interface.h \
    opencv2/core/hal/intrin.hpp \
    opencv2/core/hal/intrin_cpp.hpp \
    opencv2/core/hal/intrin_neon.hpp \
    opencv2/core/hal/intrin_sse.hpp \
    opencv2/core/hal/intrin_vsx.hpp \
    opencv2/core/utils/logger.hpp \
    opencv2/core/utils/trace.hpp \
    opencv2/core/affine.hpp \
    opencv2/core/base.hpp \
    opencv2/core/bufferpool.hpp \
    opencv2/core/core.hpp \
    opencv2/core/core_c.h \
    opencv2/core/cuda.hpp \
    opencv2/core/cuda.inl.hpp \
    opencv2/core/cuda_stream_accessor.hpp \
    opencv2/core/cuda_types.hpp \
    opencv2/core/cv_cpu_dispatch.h \
    opencv2/core/cv_cpu_helper.h \
    opencv2/core/cvdef.h \
    opencv2/core/cvstd.hpp \
    opencv2/core/cvstd.inl.hpp \
    opencv2/core/directx.hpp \
    opencv2/core/eigen.hpp \
    opencv2/core/fast_math.hpp \
    opencv2/core/ippasync.hpp \
    opencv2/core/mat.hpp \
    opencv2/core/mat.inl.hpp \
    opencv2/core/matx.hpp \
    opencv2/core/neon_utils.hpp \
    opencv2/core/ocl.hpp \
    opencv2/core/ocl_genbase.hpp \
    opencv2/core/opengl.hpp \
    opencv2/core/operations.hpp \
    opencv2/core/optim.hpp \
    opencv2/core/ovx.hpp \
    opencv2/core/persistence.hpp \
    opencv2/core/ptr.inl.hpp \
    opencv2/core/saturate.hpp \
    opencv2/core/softfloat.hpp \
    opencv2/core/sse_utils.hpp \
    opencv2/core/traits.hpp \
    opencv2/core/types.hpp \
    opencv2/core/types_c.h \
    opencv2/core/utility.hpp \
    opencv2/core/va_intel.hpp \
    opencv2/core/version.hpp \
    opencv2/core/vsx_utils.hpp \
    opencv2/core/wimage.hpp \
    opencv2/dnn/all_layers.hpp \
    opencv2/dnn/dict.hpp \
    opencv2/dnn/dnn.hpp \
    opencv2/dnn/dnn.inl.hpp \
    opencv2/dnn/layer.details.hpp \
    opencv2/dnn/layer.hpp \
    opencv2/dnn/shape_utils.hpp \
    opencv2/features2d/features2d.hpp \
    opencv2/flann/all_indices.h \
    opencv2/flann/allocator.h \
    opencv2/flann/any.h \
    opencv2/flann/autotuned_index.h \
    opencv2/flann/composite_index.h \
    opencv2/flann/config.h \
    opencv2/flann/defines.h \
    opencv2/flann/dist.h \
    opencv2/flann/dummy.h \
    opencv2/flann/dynamic_bitset.h \
    opencv2/flann/flann.hpp \
    opencv2/flann/flann_base.hpp \
    opencv2/flann/general.h \
    opencv2/flann/ground_truth.h \
    opencv2/flann/hdf5.h \
    opencv2/flann/heap.h \
    opencv2/flann/hierarchical_clustering_index.h \
    opencv2/flann/index_testing.h \
    opencv2/flann/kdtree_index.h \
    opencv2/flann/kdtree_single_index.h \
    opencv2/flann/kmeans_index.h \
    opencv2/flann/linear_index.h \
    opencv2/flann/logger.h \
    opencv2/flann/lsh_index.h \
    opencv2/flann/lsh_table.h \
    opencv2/flann/matrix.h \
    opencv2/flann/miniflann.hpp \
    opencv2/flann/nn_index.h \
    opencv2/flann/object_factory.h \
    opencv2/flann/params.h \
    opencv2/flann/random.h \
    opencv2/flann/result_set.h \
    opencv2/flann/sampling.h \
    opencv2/flann/saving.h \
    opencv2/flann/simplex_downhill.h \
    opencv2/flann/timer.h \
    opencv2/highgui/highgui.hpp \
    opencv2/highgui/highgui_c.h \
    opencv2/imgcodecs/imgcodecs.hpp \
    opencv2/imgcodecs/imgcodecs_c.h \
    opencv2/imgcodecs/ios.h \
    opencv2/imgproc/detail/distortion_model.hpp \
    opencv2/imgproc/hal/hal.hpp \
    opencv2/imgproc/hal/interface.h \
    opencv2/imgproc/imgproc.hpp \
    opencv2/imgproc/imgproc_c.h \
    opencv2/imgproc/types_c.h \
    opencv2/ml/ml.hpp \
    opencv2/objdetect/detection_based_tracker.hpp \
    opencv2/objdetect/objdetect.hpp \
    opencv2/objdetect/objdetect_c.h \
    opencv2/photo/cuda.hpp \
    opencv2/photo/photo.hpp \
    opencv2/photo/photo_c.h \
    opencv2/shape/emdL1.hpp \
    opencv2/shape/hist_cost.hpp \
    opencv2/shape/shape.hpp \
    opencv2/shape/shape_distance.hpp \
    opencv2/shape/shape_transformer.hpp \
    opencv2/stitching/detail/autocalib.hpp \
    opencv2/stitching/detail/blenders.hpp \
    opencv2/stitching/detail/camera.hpp \
    opencv2/stitching/detail/exposure_compensate.hpp \
    opencv2/stitching/detail/matchers.hpp \
    opencv2/stitching/detail/motion_estimators.hpp \
    opencv2/stitching/detail/seam_finders.hpp \
    opencv2/stitching/detail/timelapsers.hpp \
    opencv2/stitching/detail/util.hpp \
    opencv2/stitching/detail/util_inl.hpp \
    opencv2/stitching/detail/warpers.hpp \
    opencv2/stitching/detail/warpers_inl.hpp \
    opencv2/stitching/warpers.hpp \
    opencv2/superres/optical_flow.hpp \
    opencv2/video/background_segm.hpp \
    opencv2/video/tracking.hpp \
    opencv2/video/tracking_c.h \
    opencv2/video/video.hpp \
    opencv2/videoio/cap_ios.h \
    opencv2/videoio/videoio.hpp \
    opencv2/videoio/videoio_c.h \
    opencv2/videostab/deblurring.hpp \
    opencv2/videostab/fast_marching.hpp \
    opencv2/videostab/fast_marching_inl.hpp \
    opencv2/videostab/frame_source.hpp \
    opencv2/videostab/global_motion.hpp \
    opencv2/videostab/inpainting.hpp \
    opencv2/videostab/log.hpp \
    opencv2/videostab/motion_core.hpp \
    opencv2/videostab/motion_stabilizing.hpp \
    opencv2/videostab/optical_flow.hpp \
    opencv2/videostab/outlier_rejection.hpp \
    opencv2/videostab/ring_buffer.hpp \
    opencv2/videostab/stabilizer.hpp \
    opencv2/videostab/wobble_suppression.hpp \
    opencv2/calib3d.hpp \
    opencv2/core.hpp \
    opencv2/cvconfig.h \
    opencv2/dnn.hpp \
    opencv2/features2d.hpp \
    opencv2/flann.hpp \
    opencv2/highgui.hpp \
    opencv2/imgcodecs.hpp \
    opencv2/imgproc.hpp \
    opencv2/ml.hpp \
    opencv2/objdetect.hpp \
    opencv2/opencv.hpp \
    opencv2/opencv_modules.hpp \
    opencv2/photo.hpp \
    opencv2/shape.hpp \
    opencv2/stitching.hpp \
    opencv2/superres.hpp \
    opencv2/video.hpp \
    opencv2/videoio.hpp \
    opencv2/videostab.hpp \
    opencv2/world.hpp \
#    ffmpeg/dev/include/libavcodec/avcodec.h \
#    ffmpeg/dev/include/libavformat/avformat.h \
#    ffmpeg/dev/include/libswscale/swscale.h \
#    ffmpeg/dev/include/libavdevice/avdevice.h \
#    ffmpeg/dev/include/libavformat/version.h \
#    ffmpeg/dev/include/libavutil/time.h \
#    ffmpeg/dev/include/libavutil/mathematics.h

FORMS += \
        mainwindow.ui

RC_ICONS = mouse.ico

INCLUDEPATH += ../include
               ../include/opencv
               ../include/opencv2



#LIBS += $$PWD/ffmpeg/dev/lib/libavcodec.dll.a\
#        $$PWD/ffmpeg/dev/lib/libavdevice.dll.a\
#        $$PWD/ffmpeg/dev/lib/libavfilter.dll.a\
#        $$PWD/ffmpeg/dev/lib/libavformat.dll.a\
#        $$PWD/ffmpeg/dev/lib/libavutil.dll.a\
#        $$PWD/ffmpeg/dev/lib/libswresample.dll.a\
#        $$PWD/ffmpeg/dev/lib/libswscale.dll.a\
#        $$PWD/ffmpeg/dev/lib/libpostproc.dll.a
LIBS += $$PWD/lib/Release/Project7.lib
LIBS += $$PWD/lib/Release/opencv_world331.lib
LIBS += $$PWD/lib/Release/tensorflow.lib

DISTFILES += \
    ../lib/Release/tensorflow.lib \
    ../lib/Release/opencv_world331.lib \
    ../lib/Release/Project7.lib \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
