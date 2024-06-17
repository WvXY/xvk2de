# XEV Root
set(XEV_INCLUDE_DIR
        ${SRC_DIR}/
        ${SRC_DIR}/renderer/
        ${SRC_DIR}/common/
        ${SRC_DIR}/physics/
        ${SRC_DIR}/math/
)

file(GLOB_RECURSE XEV_SRC_FILES
        ${XEV_INCLUDE_DIR}/*.cpp
        ${XEV_INCLUDE_DIR}/*.hpp
        ${XEV_INCLUDE_DIR}/*.h
)



