if(SMTG_AAX_SDK_PATH AND SMTG_ADD_VSTGUI)
  include(AddAAXLibrary)
  set(
    base_sources
    ${SDK_ROOT}/public.sdk/source/vst/basewrapper/basewrapper.sdk.cpp
  )
  set(
    Delay770_aax_sources
    source/aax.cpp
    ../Delay770/include/buffer.h
    ../Delay770/include/controller.h
    ../Delay770/include/id.h
    ../Delay770/include/parameter.h
    ../Delay770/include/processor.h
    ../Delay770/include/version.h
    ../Delay770/source/buffer.cpp
    ../Delay770/source/controller.cpp
    ../Delay770/source/factory.cpp
    ../Delay770/source/parameter.cpp
    ../Delay770/source/processor.cpp
  )
  set(Delay770_sources ${Delay770_aax_sources} ${base_sources})
  set(target Delay770aax)
  smtg_add_aaxplugin(${target} ${Delay770_sources})
  target_include_directories(${target} PUBLIC ../Delay770/include)
  target_include_directories(${target} PUBLIC ../Delay770/source)
  target_include_directories(${target} PUBLIC ${VSTGUI_ROOT}/vstgui4)
  target_link_libraries(${target} PRIVATE base sdk vstgui_support aaxwrapper)

  smtg_add_vst3_resource(${target} "../Delay770/resource/main.uidesc")

  smtg_add_vst3_resource(${target} "../Delay770/image/knob_1x.png")
  smtg_add_vst3_resource(${target} "../Delay770/image/knob_2x.png")
  smtg_add_vst3_resource(${target} "../Delay770/image/knob_3x.png")

  if(SMTG_MAC)
    smtg_set_bundle(${target} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/../Delay770/resource/Info.plist" PREPROCESS)
  elseif(SMTG_WIN)
    target_sources(${target} PRIVATE ../Delay770/resource/Plugin.rc)
  endif()
endif()
