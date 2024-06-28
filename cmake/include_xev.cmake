# XEV Root
set(XEV_INCLUDE_ROOT ${ICD_DIR}/xev/)

set(XEV_INCLUDE_DIR
        ${XEV_INCLUDE_ROOT}
        ${XEV_INCLUDE_ROOT}/renderer/
        ${XEV_INCLUDE_ROOT}/common/
        ${XEV_INCLUDE_ROOT}/physics/
        ${XEV_INCLUDE_ROOT}/math/
)

file(GLOB_RECURSE XEV_INCLUDE_FILES
        ${XEV_INCLUDE_DIR}/*.hpp
        ${XEV_INCLUDE_DIR}/*.h
)
