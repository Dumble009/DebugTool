cmake_minimum_required(VERSION 3.14)

project(copy_root)

file(GLOB HEADER_FILES "*.h")

message(STATUS "run root")

foreach(HEADER_FILE ${HEADER_FILES})

message(STATUS ${HEADER_FILE})

# フォルダ名、拡張子を除いたファイル名を変数TEMP_TARGETに代入
get_filename_component(TEMP_TARGET ${HEADER_FILE} NAME_WE)
# TEMP_TARGETの頭にcopy_header_を追加
set(TEMP_TARGET "copy_header_${TEMP_TARGET}")

# コピー対象のフォルダ名を除いた拡張子込みのファイル名を取得
get_filename_component(FNAME ${HEADER_FILE} NAME)

add_custom_target(
    ${TEMP_TARGET}
    COMMAND 
    ${CMAKE_COMMAND} -E copy "${HEADER_FILE}" "C:/MyLib/DebugTool/include/${FNAME}"
)

add_dependencies(${LibraryName} ${TEMP_TARGET})

endforeach(HEADER_FILE ${HEADER_FILES})